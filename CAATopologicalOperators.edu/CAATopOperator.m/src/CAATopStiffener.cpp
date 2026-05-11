/**
* @quickReview CRE 04:03:11
*/

// COPYRIGHT DASSAULT SYSTEMES  2000

#include <iostream.h>
#include "CATErrorMacros.h"            // error management

// Mathematics
#include "CATMathVector.h"             // mathematical vector
#include "CATMathDirection.h"          // for the constuctor of a direction from a vector
#include "CATSoftwareConfiguration.h"  // the software configuration
#include "CATDataType.h"

// GeometricObjects
#include "CATGeoFactory.h"             // geometry factory
#include "CATSurface.h"                // surface 
#include "CATSurParam.h"               // surface parameter
#include "CATPCircle.h"                // circle on a surface
#include "CATGeometry.h"
#include "CATTopDefine.h"

#include "CATCGMJournalList.h"         // a set of journal items 

// NewTopologicalObjects
#include "CATBody.h"                   // body      
#include "CATDomain.h"                 // domain
#include "CATCell.h"                   // cell
#include "CATFace.h"                   // face 
#include "CATEdge.h"                   // edges
#include "CATListOfCATCells.h"         // list of cells (to use during the search inside the journal)
#include "ListPOfCATEdge.h"            // list of edges  (to use during the filleting operation)
#include "CATBoundaryIterator.h"       // to search for the boundary of a cell
#include "CATTopData.h"                // the journal and the configuration 

// TopologicalOperators
#include "CATTopPrism.h"               // Prisl operator
#include "CATDynFillet.h"              // Filleting operator 
#include "CATDynFilletRibbon.h"        // one fillet operation
#include "CATDynFilletRadius.h"        // radius definition
#include "CATDynMassProperties3D.h"    // length computation

// CAATopologicalOperators.edu
#include "CAATopStiffener.h"           // the new CAA operator

//-----------------------------
// macros for error management
// These macros delete the allocated objects and remove the intermediates created bodies or geometry
// The number of the macros refers to type of cleaning
//-----------------------------
#define CAAErrorTopStif7(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt,piPCircle1,piPCircle2,pRadius,pRibbon,pFilletOp) \
  {if (pRibbon!=NULL) delete pRibbon;\
  if (pFilletOp!=NULL) delete pFilletOp;\
CAAErrorTopStif6(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt,piPCircle1,piPCircle2,pRadius)}

#define CAAErrorTopStif6(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt,piPCircle1,piPCircle2,pRadius) \
  {if (pRadius!=NULL) delete pRadius;\
CAAErrorTopStif5(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt,piPCircle1,piPCircle2)}

#define CAAErrorTopStif5(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt,piPCircle1,piPCircle2) \
  {if (piPCircle2!=NULL) piGeomFactory->Remove(piPCircle2, \
  CATICGMContainer::RemoveDependancies);\
CAAErrorTopStif4(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt,piPCircle1)}

#define CAAErrorTopStif4(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt,piPCircle1) \
  {if (piPCircle1!=NULL) piGeomFactory->Remove(piPCircle1, \
  CATICGMContainer::RemoveDependancies);\
CAAErrorTopStif3(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt)}

#define CAAErrorTopStif3(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt) \
  {if (pBoundaryIt != NULL) delete pBoundaryIt;\
CAAErrorTopStif2(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation) }


#define CAAErrorTopStif2(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation) \
  {if (pPrismOp != NULL) delete pPrismOp;\
  if (piMainBody1!=NULL) piGeomFactory->Remove(piMainBody1,\
  CATICGMContainer::RemoveDependancies);\
  if (piWithoutOperation!=NULL) piGeomFactory->Remove(piWithoutOperation,\
  CATICGMContainer::RemoveDependancies);\
CAAErrorTopStif1(rc,pJournal)}

#define CAAErrorTopStif1(rc,pJournal) \
  { if (pJournal != NULL) delete pJournal; \
return (rc);}


//-------------------------------------------------------------------------------------
// Deletion
//-------------------------------------------------------------------------------------
CAATopStiffener::~CAATopStiffener()
{
	// if the resulting body is created, and is never retrieved (GetResult), deletes it
	if(NULL != _piGeomFactory && NULL != _piResultingBody) _piGeomFactory->Remove(_piResultingBody, CATICGMContainer::RemoveDependancies);
	_piResultingBody  = NULL;
	_piGeomFactory    = NULL;
	_piFirstLimitBody = NULL;
	_piSecondLimitBody= NULL;
	_piSkinBody       = NULL;
	_pData            = NULL;
	
}

//-------------------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------------------
CAATopStiffener::CAATopStiffener (CATGeoFactory     * iFactory,
                                  CATTopData        * iData,
                                  CATBody           * iFirstLimitBody,
                                  CATBody           * iSecondLimitBody,
                                  CATBody           * iSkinProfile,
                                  CATMathVector       iDirection)
{
	_piGeomFactory    = iFactory;
	_piFirstLimitBody = iFirstLimitBody;
	_piSecondLimitBody= iSecondLimitBody;
	_piSkinBody       = iSkinProfile;
	_direction        = iDirection;
	_piResultingBody  = NULL;
	_pData            = iData;
	
}

//-------------------------------------------------------------------------------------
// Run
//-------------------------------------------------------------------------------------
int CAATopStiffener::Run()

{
	int rc=0; // return code
	
	//-------------------------------------------------------------------------------
	// 1- Tests the inputs
	//-------------------------------------------------------------------------------  
	
	// ---------- Avoids to run twice
	CATBody * piResultingBody = _piResultingBody;
	if (NULL != piResultingBody) return(2);
	
	// ---------- Tests the null pointers
	//
	CATGeoFactory * piGeomFactory = _piGeomFactory;
	if (NULL == piGeomFactory ) return (1);
	
	// ---------- First limit <> Second Limit
	//
	CATBody *   piFirstLimitBody =_piFirstLimitBody;
	if (NULL == piFirstLimitBody) return (1);
	CATBody *   piSecondLimitBody =_piSecondLimitBody;
	if (NULL == piSecondLimitBody) return (1);
	if (piFirstLimitBody == piSecondLimitBody) return (3); 
	
	// ---------- Tests whether the input profile body has one domain, containing faces
	//   
	// The skin body to extrude 
	CATBody * piSkinBody = _piSkinBody; 
	if (NULL == piSkinBody ) return (1); 
	// Tests the skin body (mono-domain)
	CATLONG32 nbDomains  = piSkinBody->GetNbDomains();
	if (1!=nbDomains) return (5);                    // one domain
	// Retrieves the domain 
	CATDomain* piShell=piSkinBody->GetDomain(1);       
	if(NULL==piShell) return(1);
	if (2 != piShell->GetLowDimension()) return(4);  // of faces (dimension = 2)
	CATLONG32 nbCells = piShell->GetNbCellUses();         // count of faces
	if (1!=nbCells) { return(4);} 
	CATFace * piFace = (CATFace *) (piShell->GetCell(1));
	if (NULL == piFace) return(4);                   // the face of the shell
	
	//-------------------------------------------------------------------------------
	// 2- Runs the CATTopPrism operator
	//-------------------------------------------------------------------------------
	// Direction of extrusion
	CATMathDirection direction (_direction);
	
	// Offset (not used here)
	double offset = 0.;
	
	// Journal and configuration
	CATTopData internalTopdata(*_pData);       // input configuration
	CATSoftwareConfiguration * pConfig = internalTopdata.GetSoftwareConfiguration();
	CATCGMJournalList* pJournal = new CATCGMJournalList(pConfig,NULL);
	
	internalTopdata.SetJournal(pJournal);    // the journal for the internal operations 
	// --------- Creates the operator
	//
	CATTopPrism  *pPrismOp = ::CATCreateTopPrism (piGeomFactory,
		&internalTopdata, 
		piSkinBody,
		&direction,
		offset, // non significative: the limits are defined later
		offset); // non significative: the limits are defined later
	if (NULL==pPrismOp) return (1);
	
	// --------- Sets options
	//
	// Sets the relimiting body
	
	pPrismOp->SetTrim(piFirstLimitBody);
	
	// Asks for the Boolean union with the relimiting body
	pPrismOp->SetOperation(CatBoolUnion);
	
	// Asks to also retrieve the result of the Booleean operation
	pPrismOp->SetResultMode(TRUE);
	
	// Sets the until limits: first limit
	pPrismOp->SetLimit(CatLimStart,           // first limit
		CatLimUntil,           // until option
		TRUE ,                 // same orientation as the axis one
		offset,                // non significative (until limits)
		piFirstLimitBody,      // the limiting geometry: here a body
		piFirstLimitBody,      // for the propagation
		CatPropagSingle);      // no propagation
	
	// Sets the until limits: second limit
	pPrismOp->SetLimit(CatLimEnd,
		CatLimUntil, 
		TRUE , 
		offset, 
		piSecondLimitBody, 
		piSecondLimitBody, 
		CatPropagSingle);
	
	// --------- Runs
	//
	CATTry
	{
		pPrismOp ->Run(); 
	}
	CATCatch(CATError,error)
	{
		cout << (error->GetNLSMessage()).ConvertToChar() << endl;
		rc = 20; 
		Flush(error);
	}
	CATEndTry
		
		if (rc!=0) CAAErrorTopStif1(rc,pJournal)
			
			// --------- Gets the resulting body 
			//
			CATBody * piMainBody1=NULL;
		piMainBody1 = pPrismOp->GetBooleanResult();
		
		// gets the prism before the union
		CATBody * piWithoutOperation = pPrismOp->GetResult();
		
		
		
		if (NULL==piMainBody1 || NULL==piWithoutOperation)
		{
			rc = 20;
			CAAErrorTopStif2(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation)
		}
		
		// gets the journal of the boolean operation
		CATCGMJournalList * pBooleanJournal = pPrismOp->GetBooleanJournal(); 
		if ( NULL==pBooleanJournal) 
		{
			rc = 20;
			//CAAErrorTopStif2(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation)
			
			if (pPrismOp != NULL) delete pPrismOp; 
			if (piMainBody1!=NULL) piGeomFactory->Remove(piMainBody1, 
				CATICGMContainer::RemoveDependancies); 
			if (piWithoutOperation!=NULL) piGeomFactory->Remove(piWithoutOperation, 
				CATICGMContainer::RemoveDependancies); 
			if (pJournal != NULL) delete pJournal;  
			return (rc);
		}
		
		//-------------------------------------------------------------------------------
		// 3- Searches for the face of the stiffener generated by a CATLONG32 side of the profile (piHeight1).
		//-------------------------------------------------------------------------------
		
		// Creates the boundary iterator on the edge of the initial face (of the skin to extrude)
		CATBoundaryIterator  *  pBoundaryIt =  piFace->CreateBoundaryIterator();
		CATCell * piHeight1 = NULL, *piHeight2 = NULL;
		double height=0; 
		double l1=0.,l2=0.;
		
		if (NULL!=pBoundaryIt)
		{
			// Computes the length of an edge
			CATSide side;
			CATCell*  piE1 = pBoundaryIt->Next(&side,NULL);
			if (NULL!=piE1)
			{
				CATDynMassProperties3D * lenghOpe =:: CATDynCreateMassProperties3D(&internalTopdata, (CATEdge * )piE1 );
				// l1= ((CATEdge * )piE1 )->CalcLength(); /* deprecated */
				if (NULL == lenghOpe ) 
				{
					return (1);
				}
				else
				{
					l1= lenghOpe->GetLength();
					delete lenghOpe;
				}

			}
			
			// Computes the length of the next  edge
			CATCell*  piE2 = pBoundaryIt->Next(&side,NULL);
			if (NULL!=piE2)
			{
				// l2=((CATEdge * )piE2)->CalcLength(); /* deprecated */
               CATDynMassProperties3D * lenghOpe =:: CATDynCreateMassProperties3D(&internalTopdata, (CATEdge * )piE2);
			   if (NULL == lenghOpe ) {
				   return (1);
			   }
			   else
			   {
				   l2= lenghOpe->GetLength();
				   delete lenghOpe;
			   }
			}
			
			// Defines the height according to l1 and l2 values.
			//  
			if ( l1 < l2 )
			{
				height    = l2;
				piHeight1 = piE2;
				piHeight2 = pBoundaryIt->Next(&side,NULL);
			}
			else
			{
				height    = l1;
				piHeight1 = piE1;
				piHeight2 = pBoundaryIt->Next(&side,NULL); 
			}
			
			delete pBoundaryIt;
			pBoundaryIt=NULL;
		}
		else
		{
			rc =1;
			CAAErrorTopStif2(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation)  
		}
		
		//------------------------------------------------------------------------------------
		// 4- Searches inside the journal for the face of the prism generated from piHeight1
		//------------------------------------------------------------------------------------
		
		//  Retrieves all the objects created or modified from piHeight1
		//  first, in pJournal
		CATLISTP(CATGeometry) pFaces; 
		pJournal->FindLasts (piHeight1,pFaces,ThroughCreateAndModify);
		
		CATFace * piFromHeight1=NULL;
		int nbresult = pFaces.Size();
		
		// Retrieves the object that is a face.
		int i = 1;
for (; (i <= nbresult) && (piFromHeight1 == NULL) ; i++) 
		{
			CATGeometry * pLocalGeometry = pFaces[i];
			if (pLocalGeometry->IsATypeOf(CATFaceType)) { piFromHeight1=(CATFace *)pLocalGeometry;}
			
		}
		if (NULL==piFromHeight1) 
		{
			rc =21;
			CAAErrorTopStif3(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt)
		}
		else {
			
			//  now, in pBooleanJournal
			pFaces.RemoveAll();
			pBooleanJournal->FindLasts (piFromHeight1,pFaces,ThroughModify);
			CATFace * piBooleanFromHeight1=NULL;
			nbresult = pFaces.Size();
			
			// Retrieves the object that is a face.
			for (i=1 ; (i <= nbresult) && (piBooleanFromHeight1 == NULL) ; i++) 
			{
				CATGeometry * pLocalGeometry = pFaces[i];
				if (pLocalGeometry->IsATypeOf(CATFaceType))	 { piBooleanFromHeight1=(CATFace *)pLocalGeometry;}
			}
			
			if (NULL==piBooleanFromHeight1) 
			{
				rc =21;
				CAAErrorTopStif3(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt)
			}
			else {
				//------------------------------------------------------------------------------------
				// 5- Creates a circle on the underlying surface of the face
				//------------------------------------------------------------------------------------
				
				// Gets the surface of the face  
				CATOrientation orientation;
				CATSurface * piSurfaceFromHeight = piBooleanFromHeight1->GetSurface(&orientation);
				if (NULL==piSurfaceFromHeight) 
				{
					rc =1;
					CAAErrorTopStif3(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt)
				}
				
				
				// Estimates the center of the face  
				CATSurParam centerParam;
				piFromHeight1->EstimateCenterParam (centerParam);
				
				// Creates a circle on the surface
				CATPCircle * piPCircle1 = piGeomFactory -> CreatePCircle( height/3.,centerParam, piSurfaceFromHeight);
				if (NULL==piPCircle1) 
				{
					rc =1;
					CAAErrorTopStif3(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt)
				}
				
				//------------------------------------------------------------------------------------
				// Seaches inside the journal for the face of the prism generated from piHeight2
				//------------------------------------------------------------------------------------
				
				//  retrieves all the objects created or modified from piHeight2
				pFaces.RemoveAll();
				pJournal->FindLasts (piHeight2,pFaces,ThroughCreateAndModify);
				CATFace * piFromHeight2=NULL;
				nbresult = pFaces.Size();
				
				// Retrieves the object that is a face.
				for ( i=1 ; (i <= nbresult) && (piFromHeight2 == NULL) ; i++) 
				{
					CATGeometry * pLocalGeometry = pFaces[i];
					if (pLocalGeometry->IsATypeOf(CATFaceType)) { piFromHeight2=(CATFace *)pLocalGeometry;}
					
					
				}
				if (NULL==piFromHeight2) 
				{
					rc =21;
					CAAErrorTopStif4(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt,piPCircle1)
				}
				else{
					
					pFaces.RemoveAll();
					pBooleanJournal->FindLasts (piFromHeight2,pFaces,ThroughModify);
					CATFace * piBooleanFromHeight2=NULL;
					nbresult = pFaces.Size();
					
					
					// Retrieves the object that is a face.
					for (i=1 ; (i <= nbresult) && (piBooleanFromHeight2 == NULL) ; i++) 
					{
						CATGeometry * pLocalGeometry = pFaces[i];
						if (pLocalGeometry->IsATypeOf(CATFaceType)) { piBooleanFromHeight2=(CATFace *)pLocalGeometry;}
						
					}
					if (NULL==piBooleanFromHeight2) 
					{
						rc =21;
						CAAErrorTopStif4(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt,piPCircle1)
					}
					else
					{
						//------------------------------------------------------------------------------------
						// Creates a circle on the underlying surface of the face
						//------------------------------------------------------------------------------------
						
						
						// Gets the surface of the face
						piSurfaceFromHeight = piBooleanFromHeight2->GetSurface(&orientation);
						if (NULL==piSurfaceFromHeight) 
						{
							rc =21;
							CAAErrorTopStif4(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt,piPCircle1)
						}
						
						// Estimates the center of the face
						piFromHeight2->EstimateCenterParam (centerParam);
						
						// Creates a circle on the surface
						CATPCircle * piPCircle2 = piGeomFactory -> CreatePCircle( height/3.,centerParam, piSurfaceFromHeight);
						if (NULL==piPCircle2) 
						{
							rc=1;
							CAAErrorTopStif4(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt,piPCircle1)
						}
						
						// Deletes the unused body
						pBooleanJournal-> Duplicate(pJournal);
						piGeomFactory->Remove(piWithoutOperation,CATICGMContainer::RemoveDependancies);
						piWithoutOperation=NULL;
						
						
						//------------------------------------------------------------------------------------
						// 6- Searches inside the journal for the face on the wing.
						//------------------------------------------------------------------------------------
						
						CATLISTP(CATCell) listCells;
						piFirstLimitBody->GetAllCells(listCells,2);  // gets all the faces of FirstlimitBody
						nbCells = listCells.Size();
						
						CATFace * piFromBody1=NULL;
						int iok=0;
						for (i=1;(i <= nbCells)  ;i++)
						{    
							pFaces.RemoveAll();                          // voids the list
							pBooleanJournal -> FindLasts (listCells[i],pFaces,ThroughModify);
							nbresult = pFaces.Size();
							for (int j=1; (j <= nbresult) && (piFromBody1 == NULL) ; j++)
								
							{
								CATGeometry * pLocalGeometry = pFaces[j];
								if (pLocalGeometry 
									&& pLocalGeometry->IsATypeOf(CATFaceType)  // searches for a face
									&& pLocalGeometry != listCells[i] )        // different from the initial one
								{ 
									piFromBody1=(CATFace *)pLocalGeometry;
									iok = iok + 1;
									
								}
							} 
						}
						if ((NULL==piFromBody1)||(1!=iok) )
						{
							rc=30;
							CAAErrorTopStif5(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt,piPCircle1,piPCircle2) 
						}
						else{
							
							// ---------- Deletes the operator
							delete pPrismOp;
							pPrismOp = NULL;
							// and deletes pBooleanJournal that is no more used
							delete pBooleanJournal;
							pBooleanJournal=NULL;
							
							
							
							
							//------------------------------------------------------------------------------------
							// 7- Fillets  
							//------------------------------------------------------------------------------------
							// ---------- Defines the radius and ribbon
							// for a constant radius, only the first argument is useful
							
							CATDynFilletRadius * pRadius = new CATDynFilletRadius(5.,    // radius value
								NULL,  // the cell on which the radius is defined
								NULL,  // The ratio of the edge length defining the point
								NULL); // must be kept to NULL
							if (NULL==pRadius)
							{
								rc=1;
								CAAErrorTopStif5(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt,piPCircle1,piPCircle2) 
							}
							
							CATLISTP(CATDynFilletRadius)	listRadius;		
							listRadius.Append(pRadius);
							// first edge to fillet
							piFromBody1->GetCommonBorderCells( piBooleanFromHeight1,     // the other face
								1,                        // must be put to 1
								listCells,                // the common cells
								1);                       // edge (dimension 1)  
							
							if (1!=listCells.Size() )
							{  
								rc=10;
								CAAErrorTopStif6(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt,piPCircle1,piPCircle2,pRadius) 
							}
							CATLISTP(CATEdge) listEdges;
							listEdges.Append((CATEdge *)(listCells[1]));
							
							
							// second edge to fillet
							listCells.RemoveAll();
							piFromBody1->GetCommonBorderCells( piBooleanFromHeight2,     // the other face
								1,                        // must be put to 1
								listCells,                // the common cells
								1);                       // edge (dimension 1)  
							
							if (1!=listCells.Size() )
							{  
								rc=10;
								CAAErrorTopStif6(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt,piPCircle1,piPCircle2,pRadius) 
							}
							listEdges.Append((CATEdge *)(listCells[1]));
							
							// the ribbon
							
							CATDynEdgeFilletRibbon * pRibbon = new 	CATDynEdgeFilletRibbon(listEdges, listRadius);
							if (NULL==pRibbon)
							{  
								rc=1;
								CAAErrorTopStif6(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt,piPCircle1,piPCircle2,pRadius) 
							}
							
							// trim option
							pRibbon ->SetSegmentationMode(CATDynTrim);
							
							// ----------- Creates the operator
							//
							CATDynFillet * pFilletOp = ::CATCreateDynFillet(piGeomFactory,&internalTopdata,piMainBody1);
							if (NULL==pFilletOp)
							{  
								rc=1;
								CAAErrorTopStif7(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt,piPCircle1,piPCircle2,pRadius,pRibbon,pFilletOp) 
							}
							
							// Appends the ribbon
							else {
								pFilletOp ->Append(pRibbon);
								
								// Runs
								CATTry
								{
									pFilletOp ->Run(); 
								}
								CATCatch(CATError,error)
								{
									cout << (error->GetNLSMessage()).ConvertToChar() << endl; 
									rc=20;
									Flush(error);
									CAAErrorTopStif7(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt,piPCircle1,piPCircle2,pRadius,pRibbon,pFilletOp) 
								}
								CATEndTry
									
									// Gets the resulting body
									CATBody * piMainBody2  = pFilletOp->GetResult();
								
								
								if (NULL==piMainBody2)
								{  
									rc=1;
									CAAErrorTopStif7(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation,pBoundaryIt,piPCircle1,piPCircle2,pRadius,pRibbon,pFilletOp) 
								}
								
								// Deletes the operator
								delete pFilletOp;
								pFilletOp = NULL;
								
								if (NULL != pRadius) delete pRadius;
								pRadius = NULL;
								if (NULL != pRibbon) delete pRibbon;
								pRibbon = NULL;
								
								// Deletes the unused body
								piGeomFactory->Remove(piMainBody1,CATICGMContainer::RemoveDependancies);
								_piResultingBody = piMainBody2;
								
								// Fills the output journal if needed
								CATCGMJournalList * pDataJournal = NULL;
								pDataJournal=(NULL != _pData)?_pData->GetJournal():NULL;
								if (NULL!= pDataJournal)
								{
									pJournal->Duplicate(pDataJournal);
								}
								delete pJournal;
								pJournal=NULL;
							}
		}
		}
		}
		}
		}
		
		return (rc);
		
		
}


//---------------------------------------------------------------------------------------
// GetResult
//---------------------------------------------------------------------------------------
CATBody * CAATopStiffener::GetResult()  
{
	CATBody * piReturned = _piResultingBody;
	_piResultingBody = NULL;    // GetResult must only be called once
	return (piReturned);
}

