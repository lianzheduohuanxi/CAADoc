// COPYRIGHT Dassault Systemes 2005
//===================================================================
// CATIA ShapeDesign And Styling  
// ------------------------------------------------------------------
//
// CAAEGSMCircleSweepTgBuild.cpp
// Provide implementation to interface
//    CATIBuild
//
//===================================================================
//
// Usage notes:
//
// (note) - Tass the journal - this must be done prior to 
//        reading the journal otherwise the journal might contain 
//        instructions at different levels and sub-levels
// (note) - Dump the journal / CGM Provide Journal Dump in standard output 
//       Fw CAATopologicalOperators.edu / Module CAATopDumpJournal.m / Method  CAATopDumpJournal
//       Use it for Dump of journal is needed 
//       Dumping the journal allows you to get a first idea of how you
//       can retrieve a topology object (in the present application
//       the edge which lies on the tangency surface).
//

//===================================================================
//June 2006 : Creation CAA Sample 
//===================================================================
// MINC 
#include "CATBoolean.h"
#include "CATCell.h"
#include "CATDataType.h"
#include "CATDomain.h"
#include "CATGeometry.h"
#include "CATPointOnSurface.h"
#include "CATTopDefine.h"
#include "CATUnicodeString.h"

#include "CAAEGSMCircleSweepTgBuild.h"
#include "CAAIGSMCircleSweepTg.h"

//CAA Tools 
#include "CAAGsiServicesBody.h" 
#include "CAAGsiFeaturesSplModel.h" 

//System 
#include "CATBaseUnknown.h"   
#include "CATLISTV_CATBaseUnknown.h"   
#include "CATListOfCATUnicodeString.h" 

// MechanicalModeler Framework
#include "CATIContainer.h" 
#include "CATIPrtContainer.h"
#include "CATISpecObject.h" 
#include "CATIMfProcReport.h"          
#include "CATMfBRepDefs.h"            
#include "CATIMfBRep.h"             

#include "CATMfErrUpdate.h"            
#include "CATIUpdateError.h"           
#include "CATIGeometricalElement.h"

// AdvancedtopologicalOpe
#include "CATTopMultiResult.h" 
#include "CreateTopSweepCircleWireSkin.h"  // Create the sweep operator 
#include "CATTopSweepWireSkinCircle.h"     // Sweep operator

#include "CATSkillValue.h"
#include "CATCreateTopBoolean.h"        // For the split  
#include "CATHybSplit.h"

#include "CATHybAssemble.h"


#include "CATMathPlane.h"
#include "CATMathPoint.h"
#include "CATMathDirection.h"
#include "CATMathVector.h"


// Topological Operator 
#include "CATGeoFactory.h"
#include "CATSoftwareConfiguration.h"
#include "CATTopData.h" 
#include "CATCGMJournal.h"
#include "CATCGMJournalList.h"
#include "CATCGMJournalItem.h"
#include "CATCGMJournalInfo.h"

//GeometricObjects
#include "CATPoint.h"
#include "CATSurface.h"
#include "CATFace.h"
#include "CATHybDef.h"

#include "CATSurLimits.h"
#include "CATSurParam.h"
#include "CATCurve.h"
#include "CATCrvLimits.h"
#include "CATCrvParam.h"
#include "CATEdgeCurve.h"
#include "CATEdge.h"
#include "CATDistanceMinPtSur.h"
#include "CreateDistanceMinPtSur.h" 
#include "CATLaw.h"

// NewTopologicalObjects
#include "CATBody.h"                       // Body
#include "CATEdge.h" 
#include "ListPOfCATBody.h"                // List of bodies

#define  V5R17_CONFIG_MNGT 
#ifdef V5R17_CONFIG_MNGT 
#include "CATMmrAlgoConfigServices.h" 
#endif  


//#define DEBUG_GSD_CAASAMPLE 
#ifdef DEBUG_GSD_CAASAMPLE 
#include "iostream.h" 
#endif 

#ifdef DEBUG_GSD_CAASAMPLE 
void  DumpCoord (CATUnicodeString Str, CATMathVector  iVect )
{
	double X = iVect .GetX();
	double Y = iVect .GetY();
	double Z = iVect .GetZ(); 
	cout << Str.ConvertToChar() << " = ( " << X << ", "<< Y << ", "<< Z << " ) " <<endl ; 
}
#endif 
//
// ---------------------------------------------------------------------------
// GetTangent : Gets the tgte a Body Surface, On one of its border edge  
// ---------------------------------------------------------------------------

HRESULT GetTangent(CATBody *pBody , CATEdge* pEdge, CATMathPoint &oMidPoint, CATMathVector& oTangentVector)
{

#ifdef DEBUG_TOPOLOGY 
	cout << "******************** (GetTangent) "<<endl;
#endif 
	HRESULT rc = CATReturnSuccess; 

	CATLONG32  iRank = 0 ; 
	int Dimension =1 ; 

	CATOrientation OrientationFace; 
	CATOrientation OrientationLoop;

	CATCell_var Cellule;

	if (!pEdge) return CATReturnFailure;
	if (!pBody) return CATReturnFailure;
	Cellule = (CATCell *) pEdge ; 

	// Body Surfacic / Recup du Shell 
	CATDomain_var Domain;
	Domain = pBody -> GetDomain(1);

	if (!!Domain )
	{
		//  Le Shell est composé de face 
		CATLISTP(CATCell) listCells;
		CATLONG32 nbCells = Domain ->GetNbCellUses();

#ifdef DEBUG_TOPOLOGY 
		cout << "(GetTangent)-  Nbre de cellulle de dimension 2   " <<  nbCells  <<  endl;
#endif 

		if ( nbCells > 0 )    {
			for (int jj=1 ; jj <= nbCells ; jj ++ ) {

				CATCell * pFaceCell = Domain ->GetCell(jj, & OrientationFace);
				if  (pFaceCell != NULL)   {

					// Recuperation de la Loop 
					int nbDomain = pFaceCell->GetNbDomains();
					for (int kk=1 ; (kk <= nbDomain) && (iRank == 0 )   ; kk  ++ ) {

						CATDomain_var  piDomain = pFaceCell->GetDomain(kk);
						// Shell .: is made of faces (dimension 2) .
						// CATLONG32 DimLoop  = piDomain->GetLowDimension();


						// Identificaction de l'edge dans la loop 
						iRank = piDomain -> GetCellRank(Cellule, &OrientationLoop);
#ifdef DEBUG_TOPOLOGY 
						cout << "(GetTangent)- Edge location  " << endl;
						cout << "(GetTangent)- Rank  " << iRank << " / Orientation = " << OrientationLoop << endl;
#endif 
						if (iRank >0) {

							//CATVertex *pStartVertex=NULL, *pEndVertex=NULL; 
							//pEdge->GetVertices( &pStartVertex, &pEndVertex);
							//if((NULL==pStartVertex)||(NULL==pEndVertex)) return CATReturnFailure;

							// Retrouve l'EdgeCurve.
							CATOrientation OrientationEdgeCurve=CATOrientationUnknown; 
							CATEdgeCurve* pEdgeCurve=pEdge->GetCurve(&OrientationEdgeCurve);
							if( (pEdgeCurve) && (OrientationEdgeCurve!=CATOrientationUnknown)) {


								CATCrvParam ExtCrvParam[2];
								pEdge->GetVerticesParamsOnEdgeCurve(&ExtCrvParam[0], &ExtCrvParam[1]);
								CATCrvParam CrvParam(.5, ExtCrvParam[0], ExtCrvParam[1]);   // Middle Point parameter 

								pEdgeCurve->Eval(CrvParam, CATCrvEvalCommand::EvalPoint, &oMidPoint); // Tangent on Middle point 
								pEdgeCurve->Eval(CrvParam, CATCrvEvalCommand::EvalFirstDerivative, NULL, &oTangentVector);

								/*cout<<"Edge."<<pEdge->GetPersistentTag()<<" tangent(Vertex."<<pVertex->GetPersistentTag()<<")"<<endl; 
								cout<<"  Orientation1 : "<<Orientation<<endl; 
								cout<<"  Orientation2 : "<<(pVertex==pStartVertex)<<endl; 
								cout<<"  "<<oTangentVector<<endl;*/

								CATOrientation Orientation=CATOrientationUnknown;
								Orientation = OrientationEdgeCurve * OrientationLoop * OrientationFace ; 
#ifdef DEBUG_TOPOLOGY 
								cout << "(GetTangent)- OrientationFace       " << OrientationFace << endl;
								cout << "(GetTangent)- OrientationLoop       " << OrientationLoop << endl;
								cout << "(GetTangent)- OrientationEdgeCurve  " << OrientationEdgeCurve << endl;
								cout << "(GetTangent)- Orientation           " << Orientation << endl;
#endif 
								oTangentVector=(Orientation==CATOrientationPositive)?oTangentVector:-oTangentVector;
							}
							else { 
								rc = CATReturnFailure; 
							}
						} // Rank 
					} // Face domain 
				} // Face Loop
			}   // Cells of the domains 
		}// Number of cells 
	} // Domain 

	return rc;  
}
//
//
// ---------------------------------------------------------------------------
// GetNormalOnSurf  : Gets the normale on a surface on the nearest point to Input Pt 
// ---------------------------------------------------------------------------

HRESULT GetNormaleOnSurf ( CATGeoFactory * piGeomFactory, CATBody * pBodySurf,CATMathPoint& pRefSurfacePnt , CATMathPoint& oPt,CATMathVector& oNormalVector)
{

	HRESULT rc = CATReturnFailure; 
	double MinDist                  = 1.0e35;
	CATBoolean    iSearchOnBoundary = TRUE;
	CATSkillValue iProjectMode  = BASIC;
	CATOrientation       OrientationBody;
	CATOrientation       OrientationSur;

	if (!pBodySurf) return CATReturnFailure;

	CATLISTP(CATCell)	SurfList;
	pBodySurf->GetAllCells(SurfList, 2);

	int Dimension   = 2 ; 
	CATOrientation Ori;

	CATDomain_var Domain;
	Domain = pBodySurf -> GetDomain(1);
	if (!!Domain )
	{

		CATLISTP(CATCell)	SurfList;
		pBodySurf->GetAllCells(SurfList, Dimension);
		// cout << "(GetNormaleOnSurf)- Surf Liste =   " << SurfList.Size() << endl;
		for(int ii=1; ii<=SurfList.Size(); ii++){

			CATLONG32 iRank = Domain -> GetCellRank(SurfList[ii], &Ori);

#ifdef DEBUG_TOPOLOGY 
			cout << "(GetNormaleOnSurf)- Surf [" << ii << " ] " << endl;
			cout << "(GetNormaleOnSurf)- Rank  " << iRank << " / Orientation = " << Ori << endl;
#endif 
			CATFace *pSurfFace = (CATFace*)(SurfList[ii]);
			if (pSurfFace){
				CATSurface *pSurface  = pSurfFace->GetSurface(&OrientationSur);
				if (pSurface){

					OrientationBody = OrientationSur * Ori ; 
#ifdef DEBUG_TOPOLOGY 
					cout << "(GetNormaleOnSurf)- Ori          " << Ori             << endl;    
					cout << "(GetNormaleOnSurf)- Orientation  " << OrientationSur  << endl;    
					cout << "(GetNormaleOnSurf)- Orient Body  " << OrientationBody  << endl;
#endif 

					CATSoftwareConfiguration * pLocalConfig = new CATSoftwareConfiguration();
					CATSurParam SurfParm;
					CATDistanceMinPtSur *pProjectionOpe = CATCreateDistanceMin(piGeomFactory,pLocalConfig ,
						(const CATMathPoint)pRefSurfacePnt,
						(const CATSurface*)pSurface,
						iSearchOnBoundary,
						iProjectMode);

					if(pProjectionOpe){

						SurfParm    = pProjectionOpe->GetSurParam();
						double SurfDist = pProjectionOpe->GetDistance();

						CATPointOnSurface *pOnSurfacePnt = pProjectionOpe->GetPointOnSurface();
						CATPoint *pOnSurfPnt = (CATPoint*)pOnSurfacePnt;
						if (pOnSurfPnt){
							CATMathPoint pMathPntOnSurface = pOnSurfPnt->GetMathPoint();



							CATMathDirection SurfNorDir;
							pSurface ->EvalNormal(SurfParm, SurfNorDir);
							CATMathVector FaceNorVec = 
								(OrientationBody==CATOrientationPositive)?SurfNorDir:-SurfNorDir;;
							// (CATMathVector)SurfNorDir * OrientationSur


							if(SurfDist  < MinDist) {

#ifdef DEBUG_TOPOLOGY 
								cout << "(GetNormaleOnSurf) dist["<<ii<<"]  =  " << SurfDist << endl;
#endif 
								MinDist       = SurfDist ;
								oPt           = pMathPntOnSurface; 
								oNormalVector = FaceNorVec;
								rc = CATReturnSuccess; 
							}
						} // Point Ok = Pt Proj 
						// Modif 1 
						delete pProjectionOpe ; pProjectionOpe =NULL;
						if (pLocalConfig) pLocalConfig -> Release() ; pLocalConfig = NULL; 

					} // Proj Ope 
				}
			} // Surface 
		} // Loop on Surface Liste 
	} // Domain 
	return rc ;

}

CATImplementClass( CAAEGSMCircleSweepTgBuild,CodeExtension, CATBaseUnknown, CAACircleSweepTg );

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIBuild.h"
TIE_CATIBuild( CAAEGSMCircleSweepTgBuild);


//-----------------------------------------------------------------------------
// CAAEGSMCircleSweepTgBuild : constructor
//-----------------------------------------------------------------------------
CAAEGSMCircleSweepTgBuild::CAAEGSMCircleSweepTgBuild():
CAAGSMBuildBasic()
{
	// ("CAAEGSMCircleSweepTgBuild - Constructor");
}

//-----------------------------------------------------------------------------
// CAAEGSMCircleSweepTgBuild : destructor
//-----------------------------------------------------------------------------
CAAEGSMCircleSweepTgBuild::~CAAEGSMCircleSweepTgBuild()
{
	// ("CAAEGSMCircleSweepTgBuild - Destructor");
}
//-----------------------------------------------------------------------------
// Implements CATIBuild::Build
//-----------------------------------------------------------------------------
HRESULT CAAEGSMCircleSweepTgBuild::Build ()
{
	// ("Entering CAAEGSMCircleSweepTgBuild::Build()");


#ifdef DEBUG_GSD_CAASAMPLE 
	cout << " (CAAEGSMCircleSweepTgBuild::Build) Build Feature  " <<   endl;
#endif     
	//===============================================================================================
	//
	// The build method takes place as follows :
	//
	//     o -1- Removing all possible update error associated with the Sew Skin
	//     o -2- Retrieving the two input surfaces
	//     o -3- Retrieving the two bodies corresponding to the two input surfaces 
	//     o -4- Defining the procedural report
	//     o -5- Sew the Skin 
	//     o -6- Storing the procedural report
	//     o -7- Managing errors
	//
	//===============================================================================================

	//===============================================================================================
	//
	// -0- Removing all possible update error associated with the Sew Skin
	//
	//===============================================================================================

	// Gets a pointer on CATIUpdateError
	CATIUpdateError *piUpdateError = NULL;

	HRESULT rc = QueryInterface( IID_CATIUpdateError , (void**) &piUpdateError);

	if ( FAILED(rc) )
		return E_FAIL;


	// removes all error associated to the Combined Curve
	piUpdateError->UnsetUpdateError();

	//===============================================================================================
	//
	// -1- Activate/Inactivate 
	//
	//===============================================================================================

	int DeActivationStatus = BuildGeneralizedInactiveResult(); 
	if (DeActivationStatus == 1 ){
		return S_OK; 
	}


	//===============================================================================================
	//
	// -2- Retrieving the two input surfaces
	//
	//===============================================================================================

	// Gets pointer on CAAIGSMCircleSweepTg 
	CAAIGSMCircleSweepTg *piGSMCircleSweepTg = NULL;

	rc = QueryInterface( IID_CAAIGSMCircleSweepTg , (void**) &piGSMCircleSweepTg );

	if ( FAILED(rc) ) 
	{
		// Releases useless pointers.
		piUpdateError->Release();       piUpdateError = NULL ;
		return E_FAIL;
	}

	// Retrieves curves and directions
	CATISpecObject_var spiSpecOnCurveRef   ;
	CATISpecObject_var spiSpecOnSurfaceSupport  ;

	piGSMCircleSweepTg->GetCurveRef   ( spiSpecOnCurveRef);
#ifdef DEBUG_GSD_CAASAMPLE 
	cout << " - " << spiSpecOnCurveRef->GetName().ConvertToChar() << endl;
#endif          

	piGSMCircleSweepTg->GetSurfaceSupport  ( spiSpecOnSurfaceSupport);
#ifdef DEBUG_GSD_CAASAMPLE 
	cout << " - " <<  spiSpecOnSurfaceSupport->GetName().ConvertToChar() << endl;
#endif     

	if ( (!spiSpecOnCurveRef) ||  (!spiSpecOnSurfaceSupport )  ) 
	{
		// Releases useless pointers.
		piUpdateError->Release();        piUpdateError = NULL ;
		piGSMCircleSweepTg->Release();        piGSMCircleSweepTg = NULL ;

		return E_FAIL;
	}


	//===============================================================================================
	//
	// -3- Retrieving the two bodies corresponding to the two input surfaces 
	//
	//===============================================================================================

	// Curve Ref 
	// ---------------------------------
	CATBody_var spiBodyOfCurveRef ;
	// gets a pointer on CATIGeometricalElement on the first input curve
	CATIGeometricalElement *piGeometricalElementOnCurveRef= NULL;
	CATIMfBRep *piBRepElementOnCurveRef= NULL;

	if ( SUCCEEDED(spiSpecOnCurveRef->QueryInterface ( IID_CATIGeometricalElement , (void**) &piGeometricalElementOnCurveRef)) ) {
		// uses GetBodyResult body
		spiBodyOfCurveRef= piGeometricalElementOnCurveRef->GetBodyResult();
		if ( piGeometricalElementOnCurveRef) 
			piGeometricalElementOnCurveRef->Release();    piGeometricalElementOnCurveRef= NULL ;
	}
	else if ( SUCCEEDED(spiSpecOnCurveRef->QueryInterface ( IID_CATIMfBRep  , (void**) &piBRepElementOnCurveRef))  ) {
		// uses GetBody to retrieve  body
		spiBodyOfCurveRef= piBRepElementOnCurveRef->GetBody();
		piBRepElementOnCurveRef->Release();   piBRepElementOnCurveRef= NULL ;
		if (piBRepElementOnCurveRef) 
			piBRepElementOnCurveRef->Release();   piBRepElementOnCurveRef = NULL ;

	}
	else {
		// Releases useless pointers.
		piUpdateError->Release();         piUpdateError = NULL ;
		piGSMCircleSweepTg->Release();        piGSMCircleSweepTg = NULL ;
		return E_FAIL;
	}


	// Surface Support 
	// ---------------------------------
	CATBody_var spiBodyOfSurfaceSupport;
	// gets a pointer on CATIGeometricalElement on the second input curve
	CATIGeometricalElement *piGeometricalElementOnSurfaceSupport = NULL;
	CATIMfBRep *piBRepElementOnSurfaceSupport= NULL;


	if ( SUCCEEDED(spiSpecOnSurfaceSupport->QueryInterface ( IID_CATIGeometricalElement , (void**) &piGeometricalElementOnSurfaceSupport)) ) {
		// uses GetBodyResult body
		spiBodyOfSurfaceSupport= piGeometricalElementOnSurfaceSupport->GetBodyResult();
		if ( piGeometricalElementOnSurfaceSupport) 
			piGeometricalElementOnSurfaceSupport->Release();    piGeometricalElementOnSurfaceSupport= NULL ;
	}
	else if ( SUCCEEDED(spiSpecOnSurfaceSupport->QueryInterface ( IID_CATIMfBRep  , (void**) &piBRepElementOnSurfaceSupport))  ) {
		// uses GetBody to retrieve  body
		spiBodyOfSurfaceSupport= piBRepElementOnSurfaceSupport->GetBody();
		if (piBRepElementOnSurfaceSupport) 
			piBRepElementOnSurfaceSupport->Release();   piBRepElementOnSurfaceSupport = NULL ;

	}
	else {
		// Releases useless pointers.
		piUpdateError->Release();         piUpdateError = NULL ;
		piGSMCircleSweepTg->Release();        piGSMCircleSweepTg = NULL ;
		return E_FAIL;
	}

	// Parameters 
	// ---------------------------------

#ifdef DEBUG_GSD_CAASAMPLE 
	cout << " OK Body read " << endl;
#endif     

	int Solution = 0 ;
	if (NULL !=  piGSMCircleSweepTg ) { 
		piGSMCircleSweepTg->GetSolution(Solution);
#ifdef DEBUG_GSD_CAASAMPLE 
		cout << " Solution  = " << Solution  << endl;
#endif     
	}

	double dRadius  = 0.0 ;
	if (NULL !=  piGSMCircleSweepTg ) { 
		piGSMCircleSweepTg->GetRadius (dRadius);
#ifdef DEBUG_GSD_CAASAMPLE 
		cout << " Radius = " << dRadius   << endl;
#endif     

	}

	int TrimmingMode = 0 ; 
	if (NULL !=  piGSMCircleSweepTg ) { 
		piGSMCircleSweepTg->GetTrimMode(TrimmingMode );
#ifdef DEBUG_GSD_CAASAMPLE 
		cout << " TrimMode = " << TrimmingMode  << endl;
#endif     

	}

	//===============================================================================================
	//
	// -4- Defining the procedural report
	//
	//===============================================================================================

	// gets a pointer on CATIMfProcReport
	CATIMfProcReport *piProcReport = NULL;

	rc = piGSMCircleSweepTg->QueryInterface( IID_CATIMfProcReport , (void**) &piProcReport );



	if ( FAILED(rc) ) 
	{
		// Releases useless pointers.
		piUpdateError->Release();
		piUpdateError = NULL ;

		return E_FAIL;
	}

	// defines which specifications take part in the creation of the report
	CATLISTV(CATBaseUnknown_var) ListSpec;
	CATListOfCATUnicodeString    ListKeys;

	ListSpec.Append( spiSpecOnCurveRef    ); 
	ListKeys.Append( MfKeyNone          );

	ListSpec.Append( spiSpecOnSurfaceSupport     ); 
	ListKeys.Append( MfKeyNone          );

	// creates the procedural report
	piProcReport->CreateProcReport(ListSpec,ListKeys); 

	// Gets a pointer to the topological journal which contains the description 
	// of all basic topological operations.
	CATCGMJournalList *pCGMJournalList = piProcReport->GetCGMJournalList();
	// So far this journal is still empty, it will be filled by the topological operators that use it.


	//===============================================================================================
	//
	// -5- Sweep Circle 
	//
	//===============================================================================================

	// First, finds a geometric factory :

	// Gets a pointer on CATISpecObject.
	CATISpecObject *piSpecOnGSMCircleSweepTg = NULL;
	rc = QueryInterface( IID_CATISpecObject , (void**)& piSpecOnGSMCircleSweepTg );
	if ( FAILED(rc) )
	{
		// Releases useless pointers.
		piUpdateError->Release();        piUpdateError = NULL ;
		piProcReport->Release();        piProcReport = NULL ;

		return E_FAIL;
	}

	// Retrieves the feature container.
	CATIContainer_var spiFeatContainer = piSpecOnGSMCircleSweepTg->GetFeatContainer();

	piSpecOnGSMCircleSweepTg->Release();
	piSpecOnGSMCircleSweepTg = NULL ;

	if(  NULL_var == spiFeatContainer )
	{
		// Releases useless pointers.
		piUpdateError->Release();
		piUpdateError = NULL ;

		piProcReport->Release();
		piProcReport = NULL ;

		return E_FAIL;
	}

	// Gets a pointer on CATIPrtContainer from the feature container
	CATIPrtContainer *piPartContainer = NULL;
	rc = spiFeatContainer->QueryInterface( IID_CATIPrtContainer , (void**) &piPartContainer );
	if ( FAILED(rc) ) 
	{
		// Releases useless pointers.
		piUpdateError->Release();
		piUpdateError = NULL ;

		piProcReport->Release();
		piProcReport = NULL ;

		return E_FAIL;
	}

	// Retrieves the geometry container from the pointer on CATIPrtContainer
	CATIContainer_var spiGeomContainer = piPartContainer->GetGeometricContainer(); 

	// Releases useless pointer
	piPartContainer->Release();
	piPartContainer = NULL ;

	// Gets a pointer on CATGeoFactory to extrude the curves.
	CATGeoFactory *piGeomFactory = NULL;

	rc = spiGeomContainer->QueryInterface( IID_CATGeoFactory , (void**) &piGeomFactory );

	if ( FAILED(rc) ) 
	{
		// Releases useless pointers.
		piUpdateError->Release();
		piUpdateError = NULL ;

		piProcReport->Release();
		piProcReport = NULL ;

		return E_FAIL;
	}


	// ------------------------------------------------------
	// Load the ncgm input file (boundary.ncgm)
	//     and retrieve the input data 
	// ------------------------------------------------------
	//
#ifdef V5R17_CONFIG_MNGT 
	CATSoftwareConfiguration * pConfig = NULL;
	int IsConfigToStore = 0; 

	// Configuration Data
	CAAIGSMCircleSweepTg_var spGSMCircleSweepTg = piGSMCircleSweepTg ; 
	CATISpecObject_var spCurrentFeature = spGSMCircleSweepTg ; 
	rc = CATMmrAlgoConfigServices::GetConfiguration(spCurrentFeature, pConfig , IsConfigToStore);
#else 
	CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
#endif 

	// Top Data 
	CATTopData topdata(pConfig,pCGMJournalList);





	CATTry 
	{ 

		int ReportOK=0; 
		HRESULT rcTg  = E_FAIL; 
		HRESULT rcNor = E_FAIL; 



		// -----------------------------------------------------------------------------
		//  -  Create the sweep circle 
		// -----------------------------------------------------------------------------

		CATCGMJournalList* pJournalList10 = new CATCGMJournalList(pConfig,NULL);
		CATTopData topdata1(pConfig, pJournalList10) ;

		CATBody * pSweepCircleBody = NULL;
		//
		// (a) - Create the constant law
		//
		CATLaw * radiusLaw = ((CATLaw*)(piGeomFactory -> CreateConstantLaw(0.0, 1.0, dRadius)));


		// (b) - Create the CATTopSweepWireSkinCircle operator
		//
		CATTopMultiResult * piMultiResCircleSweepOpe =
			CATCreateTopSweepWireSkinCircleVariable (piGeomFactory, &topdata1, 
			spiBodyOfSurfaceSupport,  spiBodyOfCurveRef, spiBodyOfCurveRef, radiusLaw);


		// (c) - Run the operator
		//
		if (NULL != piMultiResCircleSweepOpe){ 
			piMultiResCircleSweepOpe->Run();


			// (d) - Retrieve the second body and generate the journal
			//
			piMultiResCircleSweepOpe->BeginningResult();
			int nbBodies = piMultiResCircleSweepOpe->GetNumberOfResults();
			for (int iBody = 1 ; iBody <= nbBodies ; iBody ++)
			{
				piMultiResCircleSweepOpe->NextResult();
				if (iBody == Solution )
				{
					pSweepCircleBody = piMultiResCircleSweepOpe->GetResult(pJournalList10);
				}
			} 

			// (note) - Tass the journal - this must be done prior to 
			//        reading the journal otherwise the journal might contain 
			//        instructions at different levels and sub-levels
			if (pJournalList10) pJournalList10->Tass();

			delete piMultiResCircleSweepOpe;			piMultiResCircleSweepOpe=NULL;
		}

		// -----------------------------------------------------------------------------
		// Test if circle sweep succeed (correct radius ?) 
		// -----------------------------------------------------------------------------
		if (NULL != pSweepCircleBody)  {

			// -----------------------------------------------------------------------------
			//  - No Trim with Support Suface 
			// -----------------------------------------------------------------------------

			if ( ! TrimmingMode  ){
#ifdef DEBUG_GSD_CAASAMPLE 
				cout << " MO TRIM MODE   "  << endl;
#endif 

				if (NULL!= pCGMJournalList) {
					// (e) - Scan the journal
					// Insert Journal 
					pCGMJournalList ->InsertJournal (pJournalList10);
					pCGMJournalList->Tass();

				}               


				ReportOK=1; 
				piProcReport->StoreProcReport(pSweepCircleBody,NoCopy);


			}  // End for no-Trim 

			//  - Trim with Support Suface 
			// -----------------------------------------------------------------------------
			else {

#ifdef DEBUG_GSD_CAASAMPLE 
				cout << " TRIMMING MODE   "  << endl;
#endif 

				// =========== EXRAPOL BODY ================
				// -----------------------------------------------------------------------------
				//  - Analyse Sweep Journal to retrieve , Edge on Suport 
				// -----------------------------------------------------------------------------
				//


				//  - Search for the edge located the tangency surface
				// The edge with info 3 (take a look at the dumped journal before).

				CATGeometry                    * pGeometry1 =NULL;
				CATEdge                        * pEdgeOnTheTangencySurface =NULL;
				CATCGMJournalItem              * pJournalItem1 = NULL;
				CATCGMJournal                  * pJournal1 =NULL;
				const CATCGMJournalInfo        * pInfo1 = NULL;

				//  - Put the edge into a body
				// FINAL VERSION 
				// -----------------------------------------------------------------------
				//  Note =  Info=3 means edge is lying Edge on support (Specific for Sweep Circle Journal) 
				// -----------------------------------------------------------------------
				CATBody * pExtrapolBody =  piGeomFactory->CreateBody();
				CATDomain *pWireDomain = pExtrapolBody->CreateDomain(1); // domain for edge

				while (pJournal1 = pJournalList10->Next(pJournal1)) 
				{
					pJournalItem1 = pJournal1->CastToReportItem();
					pInfo1 = pJournalItem1->GetAssociatedInfo(); 

					// info == 3 : Edge on surface 
					if (pInfo1 && (pInfo1->GetNumber()==3 ))
					{
						pGeometry1 = pJournalItem1->GetConstructedObject();
						if (pGeometry1 !=NULL && pGeometry1->IsATypeOf(CATEdgeType))
						{
							pEdgeOnTheTangencySurface =(CATEdge *)pGeometry1;
							pWireDomain->AddCell(pEdgeOnTheTangencySurface);
#ifdef DEBUG_GSD_CAASAMPLE 
							cout << "Edge number "  << pEdgeOnTheTangencySurface->GetPersistentTag() ;
							cout << " is on the tangency surface" << endl;
#endif 
						}

					}

				}
				pExtrapolBody->AddDomain(pWireDomain);
				CATLONG32 nbDomain = pWireDomain->GetNbCellUses();
#ifdef DEBUG_GSD_CAASAMPLE 
				cout << "nbDomain for Edge on surface = " <<nbDomain <<endl ; 
#endif 



				// (e) - Scan the journal
				// Insert Journal 
                if (pCGMJournalList) { 
                    pCGMJournalList ->InsertJournal (pJournalList10);
                    pCGMJournalList ->Tass();
                }
                // Clean Up pJournal1 
				// if (NULL!= pJournal1) {delete pJournal1; pJournal1 = NULL;}	



#ifdef DEBUG_GSD_CAASAMPLE 
				cout << " Test Insert Read Journal  "  << endl;
#endif 


				// -----------------------------------------------------------------------------
				//  - Compute Tangent on edge on surface Sweep 
				// -----------------------------------------------------------------------------


				//(a) Point on common Edge curve 
				CATLISTP(CATCell) CellList;
				pExtrapolBody ->GetAllCells(CellList, 1);

#ifdef DEBUG_GSD_CAASAMPLE 
				cout << "Nb Cell in extrapolated Body " <<  CellList.Size() <<endl ; 
#endif 
				CATEdge *pInputEdge1 = (CATEdge*)(CellList[1]);
				CATMathPoint pRefSurfacePnt;
				CATMathVector  pRefTangent ;



				//Tgt on Edge Curve 
				rcTg = 				GetTangent (pSweepCircleBody,pInputEdge1, pRefSurfacePnt,pRefTangent) ; 
#ifdef DEBUG_GSD_CAASAMPLE
				if (SUCCEEDED(rcTg) ) { 
					DumpCoord (" ==> OK pRefTangent " ,pRefTangent);
				}
				else{ 
					DumpCoord (" ==>  KO pRefTangent " ,pRefTangent);
				}
#endif 

				// cout << "- Topo Get Normal on Sweep at pt Ref    " << endl;
				//Norm of Sweep on Edge Curve 
				CATMathPoint SweepPt ;
				CATMathVector SweepNorVec ;
				rcNor = GetNormaleOnSurf( piGeomFactory,  pSweepCircleBody, pRefSurfacePnt, SweepPt, SweepNorVec);
#ifdef DEBUG_GSD_CAASAMPLE
				if (SUCCEEDED(rcNor) ) { 
					DumpCoord (" ==> OK pNormVector " ,SweepNorVec);
				}
				else{ 
					DumpCoord (" ==>  KO pNormVector " ,SweepNorVec);
				}
#endif 


				CATMathVector SweepRefVec = SweepNorVec ^ pRefTangent;


#ifdef DEBUG_GSD_CAASAMPLE 
				DumpCoord ("SweepRefVec " ,SweepRefVec);
#endif             

				// =========== SPLIT  ================
				// -----------------------------------------------------------------------------
				//  - Compute both Side 
				// -----------------------------------------------------------------------------
				// (b) - Split the surface by the edge
				CATBody *pSplitBody = NULL;
				//	CATHybSelectionMode iRemainSide = POSITIVE_NEGATIVE_SIDE;
				CATHybSelectionMode iRemainSide1 = POSITIVE_NEGATIVE_SIDE;
				CATHybSelectionMode iRemainSide2 = NEGATIVE_POSITIVE_SIDE;
				CATHybExtrapolationMode iExtrapolMode = TANGENT_DIRECTION;


				CATCGMJournalList* pJournalList21 = new CATCGMJournalList(pConfig,NULL);
				CATTopData topdata01(pConfig, pJournalList21) ;
				CATCGMJournalList* pJournalList22 = new CATCGMJournalList(pConfig,NULL);
				CATTopData topdata02(pConfig, pJournalList22) ;



				CATHybSplit *splitOpe1 = NULL;
				CATHybSplit *splitOpe2 = NULL;
#ifdef DEBUG_GSD_CAASAMPLE 
				cout << "- Split 1    " << endl;
#endif             
				splitOpe1 = CATCreateTopSplitShell(	piGeomFactory,
					&topdata01,
					spiBodyOfSurfaceSupport, pExtrapolBody,
					iRemainSide1,
					iExtrapolMode	);
#ifdef DEBUG_GSD_CAASAMPLE 
				cout << "- Split 2    " << endl;
#endif             
				splitOpe2 = CATCreateTopSplitShell(	piGeomFactory,
					&topdata02,
					spiBodyOfSurfaceSupport, pExtrapolBody,
					iRemainSide2,
					iExtrapolMode	);



				if(splitOpe1 && splitOpe2){


					CATLISTP(CATGeometry) pEdges ; 
					CATEdge * pFromEdge1=NULL;
					int nbresult = 0; 
					int i =0 ; 

					CATSkillValue iMode1 = BASIC;

					// --------------------------------------------------------------------------
					//- Analyse Split1 Result 
					// --------------------------------------------------------------------------

#ifdef DEBUG_GSD_CAASAMPLE 
					cout <<  endl ;
					cout << "======================= Get Normale on Split 1     " << endl;
#endif             
					splitOpe1->Run();

					CATBody * pBodySplit1 = splitOpe1->GetResult();
					CATMathPoint Split1Pt ;
					CATMathVector Split1NorVec ;
					rcNor= GetNormaleOnSurf( piGeomFactory, pBodySplit1, pRefSurfacePnt, Split1Pt , Split1NorVec);
#ifdef DEBUG_GSD_CAASAMPLE
					if (SUCCEEDED(rcNor) ) { 
						DumpCoord (" ==> OK pNormSplit1" , Split1NorVec);
					}
					else{ 
						DumpCoord (" ==>  KO pNormSplit1 " , Split1NorVec);
					}
#endif 




					//  Retrieves all the objects created or modified from piHeight1
					//  first, in pJournal
					pJournalList21->Tass();


					pJournalList21 ->FindLasts (pInputEdge1,pEdges,ThroughCreateAndModify);

					nbresult = pEdges.Size();
					//  cout << "- Edge from initial Split 1 = " << nbresult << endl;
					CATMathPoint  pRefPtOnEdgeLoop1 ;
					CATMathVector pRefVecOnEdgeLoopTangent1;
					// Retrieves the object that is a face.
					// for (i=1 ; i <= nbresult ; i++) 
					for (i=1 ; (i <= nbresult) && (pFromEdge1== NULL) ; i++) 
					{

						CATGeometry * pLocalGeometry = pEdges[i];

#ifdef DEBUG_GSD_CAASAMPLE 
						if ( NULL != pLocalGeometry){
							// ==============
							cout << "[" ;
							char * str1 = " ";
							if      (pLocalGeometry->IsATypeOf(CATFaceType))   { str1 = "Face_";               }
							else if (pLocalGeometry->IsATypeOf(CATEdgeType))   { str1 = "Edge_";               }    
							else if (pLocalGeometry->IsATypeOf(CATVertexType)) { str1 = "Vertex_";             }
							else                                               { str1 = "UnauthorizedType_";   }
							cout << str1;

							CATULONG32  persTag = pLocalGeometry->GetPersistentTag() ;
							cout <<  persTag;
							cout << "]"<<endl;
							// ==============
						}
#endif             

						if ( NULL != pLocalGeometry && pLocalGeometry->IsATypeOf(CATEdgeType)) { 

							pFromEdge1=(CATEdge *)pLocalGeometry;

							if (NULL!=pFromEdge1) 
							{
								//Tgt on Edge Curve 
								// cout << "/////// Get Tg Split 1 " << i << endl;
								rcTg = GetTangent ( pBodySplit1, pFromEdge1 , pRefPtOnEdgeLoop1 ,pRefVecOnEdgeLoopTangent1) ;
#ifdef DEBUG_GSD_CAASAMPLE 
								if (SUCCEEDED(rcTg) ) { 
									DumpCoord ("  OK TgtEdge Split 1 " , pRefVecOnEdgeLoopTangent1);
								}
								else{ 
									DumpCoord ("  KO TgtEdge Split 1 " , pRefVecOnEdgeLoopTangent1);
								}
#endif             

							}  // Identified Edge 
						}  // Type Edge 
					}
					pEdges.RemoveAll();
					CATMathVector Split1RefVec = Split1NorVec ^ pRefVecOnEdgeLoopTangent1;
#ifdef DEBUG_GSD_CAASAMPLE 

					DumpCoord ("Split1RefVec " , Split1RefVec);
#endif                 
					delete splitOpe1;         splitOpe1=NULL;


					// --------------------------------------------------------------------------
					//- Analyse Split2 Result 
					// --------------------------------------------------------------------------
#ifdef DEBUG_GSD_CAASAMPLE 
					cout <<  endl ;
					cout << "======================= Get Normale on Split 2     " << endl;
#endif             

					splitOpe2->Run();
					CATBody * pBodySplit2 = splitOpe2->GetResult();



					CATMathPoint Split2Pt ;
					CATMathVector Split2NorVec ;
					GetNormaleOnSurf(piGeomFactory, pBodySplit2, pRefSurfacePnt, Split2Pt , Split2NorVec);
#ifdef DEBUG_GSD_CAASAMPLE
					if (SUCCEEDED(rcNor) ) { 
						DumpCoord (" ==> OK pNormSplit2" , Split2NorVec);
					}
					else{ 
						DumpCoord (" ==>  KO pNormSplit2 " , Split2NorVec);
					}
#endif 


					//  Retrieves all the objects created or modified from piHeight1
					//  first, in pJournal
					pJournalList22->Tass();
         

					pJournalList22 ->FindLasts (pInputEdge1,pEdges,ThroughCreateAndModify);

					nbresult = pEdges.Size();
					//cout << "- Edge from initial Split 2 = " << nbresult << endl;


					pFromEdge1 = NULL;   
					CATMathPoint  pRefPtOnEdgeLoop2 ;
					CATMathVector pRefVecOnEdgeLoopTangent2;
					// Retrieves the object that is a face.
					for (i=1 ; (i <= nbresult) && (pFromEdge1== NULL) ; i++) 
						//for (i=1 ; i <= nbresult ; i++) 
					{
						CATGeometry * pLocalGeometry = pEdges[i];

#ifdef DEBUG_GSD_CAASAMPLE 
						if ( NULL != pLocalGeometry){
							// ==============
							cout << "[" ;
							char * str1 = " ";
							if      (pLocalGeometry->IsATypeOf(CATFaceType))   { str1 = "Face_";               }
							else if (pLocalGeometry->IsATypeOf(CATEdgeType))   { str1 = "Edge_";               }    
							else if (pLocalGeometry->IsATypeOf(CATVertexType)) { str1 = "Vertex_";             }
							else                                               { str1 = "UnauthorizedType_";   }
							cout << str1;

							CATULONG32  persTag = pLocalGeometry->GetPersistentTag() ;
							cout <<  persTag;
							cout << "]"<<endl;
							// ==============
						}
#endif 

						if ( NULL != pLocalGeometry && pLocalGeometry->IsATypeOf(CATEdgeType)) { 
							pFromEdge1=(CATEdge *)pLocalGeometry;

							if (NULL!=pFromEdge1) 
							{
								//Tgt on Edge Curve 
								// cout << "/////// Get Tg Split 2  " << i << endl;
								rcTg = GetTangent ( pBodySplit2,pFromEdge1 , pRefPtOnEdgeLoop2 ,pRefVecOnEdgeLoopTangent2) ; 
#ifdef DEBUG_GSD_CAASAMPLE 
								if (SUCCEEDED(rcTg) ) { 
									DumpCoord (" OK TgtEdge Split 2 " , pRefVecOnEdgeLoopTangent2);
								}
								else{ 
									DumpCoord (" KO TgtEdge Split 2 " , pRefVecOnEdgeLoopTangent2);
								}
#endif 
							}  // Identified Edge 
						}  // Type Edge 
					}
					pEdges.RemoveAll();
					CATMathVector Split2RefVec = Split2NorVec ^ pRefVecOnEdgeLoopTangent2;
#ifdef DEBUG_GSD_CAASAMPLE 
					DumpCoord ("Split2RefVec " , Split2RefVec);
#endif 

					delete splitOpe2;               splitOpe2=NULL;

					// --------------------------------------------------------------------------
					//- Choose correct splitted side 
					// --------------------------------------------------------------------------

#ifdef DEBUG_GSD_CAASAMPLE 
					cout << endl ;
					cout << "- Pdt scalaire 1 = "<<   Split1RefVec* SweepRefVec<< endl;
					cout << "- Pdt scalaire 2 = "<<   Split2RefVec* SweepRefVec<< endl;
#endif 
					if (NULL!= pCGMJournalList){   
						// Get the correct result 
						if (Split1RefVec* SweepRefVec < 0 ) {

							// cout << "- Store Journal Split1    " << endl;
							pCGMJournalList ->InsertJournal (pJournalList21);
							pSplitBody = pBodySplit1 ;
							piGeomFactory->Remove(pBodySplit2,CATICGMContainer::RemoveDependancies);
							if (NULL!= pJournalList22) {delete pJournalList22; pJournalList22 = NULL;}		

						}
						else {
							// cout << "- Store Journal Split2    " << endl;
							pCGMJournalList ->InsertJournal (pJournalList22);
							pSplitBody = pBodySplit2 ;
							piGeomFactory->Remove(pBodySplit1,CATICGMContainer::RemoveDependancies);
							if (NULL!= pJournalList21) {delete pJournalList21; pJournalList21 = NULL;}			

						} 

						pCGMJournalList->Tass();
                   
					}
				}    // End Split evaluations 

				// ================= ASSEMBLE ========================
				// --------------------------------------------------------------------------
				// Assemble(Join) the Fillet RIBBON and the Split Body
				// --------------------------------------------------------------------------
				//
				CATCGMJournalList* pJournalList30 = new CATCGMJournalList(pConfig,NULL);
				CATTopData topdata3(pConfig, pJournalList30) ;

				CATBody *pAssembleBody = NULL;  
				//
#ifdef DEBUG_GSD_CAASAMPLE 
				cout << "--------- Assemble  " << endl;
#endif             


				ListPOfCATBody pListAsmBody;
				pListAsmBody.Append(pSweepCircleBody);
				pListAsmBody.Append(pSplitBody);

				CATHybAssemble *AssembleOpe = CATCreateTopAssemble(	piGeomFactory,
					&topdata3,
					&pListAsmBody );

				if( NULL != AssembleOpe ){

					AssembleOpe->Run();
					pAssembleBody = AssembleOpe->GetResult();
					delete AssembleOpe;		AssembleOpe = NULL;

					pJournalList30->Tass();
					if(NULL != pAssembleBody ){

						if (NULL != pCGMJournalList) { 
							pCGMJournalList ->InsertJournal (pJournalList30);
							pCGMJournalList->Tass();
                

						}

						CATLISTV(CATBaseUnknown_var) ListNoCopySpec;
						CATListOfCATUnicodeString    ListNoCopyKeys;

						ListNoCopySpec.Append( spiSpecOnCurveRef     ); 
						ListNoCopyKeys.Append( MfKeyNone          );

						ReportOK = 1; 
						//		piProcReport->StoreProcReport(pAssembleBody); // Only No Trim
						piProcReport->StoreProcReport(pAssembleBody, ListNoCopySpec, ListNoCopyKeys);

						//
					}
				} // End Assemble 

				piGeomFactory->Remove(pSweepCircleBody,CATICGMContainer::RemoveDependancies);
				piGeomFactory->Remove(pExtrapolBody,CATICGMContainer::RemoveDependancies);
				piGeomFactory->Remove(pSplitBody,CATICGMContainer::RemoveDependancies);
				//	piGeomFactory->Remove(spiBodyOfCurve2);


			} // End for Trimming

		}  // Test Sweep Result OK 

#ifdef V5R17_CONFIG_MNGT 
		// Configuration Data
		if (IsConfigToStore && ReportOK ==1   ) { 
			rc = CATMmrAlgoConfigServices::StoreConfiguration(spCurrentFeature, pConfig);
		}
#endif  

		// -----------------------------------------------------------------------------
		//  - Errror 
		// -----------------------------------------------------------------------------
		if ( 0== ReportOK){ 

#ifdef DEBUG_GSD_CAASAMPLE 
			cout << " FAILED to create Swskin "<<endl; 
#endif 

			// creates an error if the intersection failed
			CATMfErrUpdate *pErrorNoIntersection = new CATMfErrUpdate();
			CATUnicodeString Diagnostic("Error Build of Feature. Check radius value ");
			pErrorNoIntersection->SetDiagnostic(1,Diagnostic);
			CATThrow(pErrorNoIntersection);

		}

	} // End Try 
	//===============================================================================================
	//
	// -7- Managing errors
	//
	//===============================================================================================

	CATCatch ( CATMfErrUpdate , pUpdateError)
	{
		//------------------------------------------------------------------------------
		// Catches CATMfErrUpdate errors
		//------------------------------------------------------------------------------
#ifdef DEBUG_GSD_CAASAMPLE 
		cout << " === UPDATE ERROR =="<<endl; 
#endif 
		// Builds a new update error.
		CATMfErrUpdate *pErrorToThrow = new CATMfErrUpdate();
		// Add it the diagnostic comming from the error previously caugth.
		pErrorToThrow->SetDiagnostic(1,pUpdateError->GetDiagnostic());
		// Destroys the previous error.
		::Flush(pUpdateError);
		// Associates the error with the Combined Curve.
		if(NULL != piUpdateError) piUpdateError->SetUpdateError(pErrorToThrow);



		if (pConfig!= NULL)   {pConfig->Release(); pConfig = NULL ; } 
	
		// Releases useless pointers.
		if(NULL != piUpdateError) piUpdateError->Release();
		piUpdateError = NULL ;
		if(NULL != piProcReport) piProcReport->Release();
		piProcReport = NULL ;
		if(NULL != piGeomFactory) piGeomFactory->Release();
		piGeomFactory = NULL ;

		// Dispatches the error.
		// In interactive mode, this errror will be caught by CATPrtUpdateCom that
		// knows how to handle such errors.
		CATThrow(pErrorToThrow);
	}

	CATCatch ( CATError , pError) 
	{
#ifdef DEBUG_GSD_CAASAMPLE 
		cout << " === ERROR =="<<endl; 
#endif 
		CATMfErrUpdate *pErrorToThrow = new CATMfErrUpdate();
		pErrorToThrow->SetDiagnostic(1,pError->GetNLSMessage());
		::Flush(pError);
		if(NULL != piUpdateError) piUpdateError->SetUpdateError(pErrorToThrow);


		if (pConfig!= NULL)   {pConfig->Release(); pConfig = NULL ; } 
		// Releases useless pointers.
		if(NULL != piUpdateError) piUpdateError->Release();
		piUpdateError = NULL ;
		if(NULL != piProcReport) piProcReport->Release();
		piProcReport = NULL ;
		if(NULL != piGeomFactory) piGeomFactory->Release();
		piGeomFactory = NULL ;

		CATThrow(pErrorToThrow);
	}   


	CATEndTry;

	if (pConfig!= NULL)   {pConfig->Release(); pConfig = NULL ; } 
	// if (NULL!= topdata) {delete topdata; topdata = NULL;}			


	if(NULL != piUpdateError) piUpdateError->Release();
	piUpdateError = NULL ;

	if(NULL != piProcReport)  piProcReport->Release();
	piProcReport = NULL ;

	if (NULL != piGSMCircleSweepTg ) { 
		piGSMCircleSweepTg->Release();	piGSMCircleSweepTg = NULL ;
	}
	if(NULL != piGeomFactory) piGeomFactory->Release();
	piGeomFactory = NULL ;

#ifdef DEBUG_GSD_CAASAMPLE 
	cout << " (CAAEGSMCircleSweepTgBuild::Build) Exit   " <<   endl;
#endif     
	// ("Exiting CAAEGSMCircleSweepTgBuild::Build()");
	return S_OK;
}

