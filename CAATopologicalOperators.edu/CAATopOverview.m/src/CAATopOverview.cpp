/**
* @quickReview CRE 04:12:02
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2000
//
// Sample code for : Geometric Modeler
// Mission         : Use of the topological operators: 
//                   creates a body by chaining several topological operators
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Illustrates     : 1- Creates the geometric factory
//                   2- Creates a skin body creation: CATTopOperator
//                   3- Creates a prism: CATTopPrism
//                   4- Creates primitives: CATSolidCylinder and CATSolidCuboid 
//                   5- Runs Boolean operations: CATDynBoolean
//                   6- Filleting: CATDynFillet
//                   7- Shelling: CATDynShell
//                   8- Gets the volume: CATMassProperties3D
//                   9- Closes the factory. 
//
// How to run it   : CAATopOverview           // to run whithout storing the NCGM file
//                   CAATopOverview file.NCGM // to run and store the result in file.NCGM                       
//=============================================================================

#include <iostream.h>
#include <iomanip.h>
#include "fstream.h"


// Mathematics
#include "CATMathConstant.h"           // CATPI definition
#include "CATMathPoint.h"              // mathematical point
#include "CATMathDirection.h"          // mathematical unitary vector
#include "CATMathPlane.h"              // mathematical plane
#include "CATSoftwareConfiguration.h"  // Configuration of the operator

// GeometricObjects
#include "CATGeoFactory.h"             // Geometry factory 
#include "CATCGMContainerMngt.h"       // Geometry factory management

#include "CATSurParam.h"               // Surface parameter
#include "CATCrvLimits.h"              // Curve limits
#include "CATPlane.h"                  // Geometric plane
#include "CATPCurve.h"                 // Curve on a surface 
#include "CATPCircle.h"                // Circle on a surface
#include "CATPLine.h"                  // Line on a surface

// TopologicalObjects
#include "CATBody.h"                   // body
#include "CATDomain.h"                 // domain (boundary of a cell) 
#include "CATCell.h"                   // cell 
#include "CATEdge.h"                   // edge
#include "ListPOfCATEdge.h"            // list of edges
#include "CATListOfCATCells.h"         // list of cells
#include "CATTopData.h"                // TopData of an operator

// TopologicalOperators
#include "CATTopPrism.h"               // Prism operator
#include "CATSolidCuboid.h"            // Box primitive
#include "CATSolidCylinder.h"          // Culinder primitive
#include "CATDynBoolean.h"             // Boolean operator
#include "CATDynFillet.h"              // Filleting operator 
#include "CATDynFilletRibbon.h"        // one fillet operation
#include "CATDynFilletRadius.h"        // radius definition
#include "CATDynShell.h"               // Shelling operator

#include "CATTopSkin.h"                // Skin body creation
#include "CATDynMassProperties3D.h"    // Body properties 


//------------------------------------------------------------------------------
// The return code of the main is null if the execution is OK, not null if some
// problem has been detected
int main(int    iArgc,   // Number of arguments (0) or (1) 
         char** iArgv)   // Path to the *.NCGM document that will contain the result of the main.
{
    int rc=0;
    if(2<iArgc) return (1);
	
    char *pfileName = NULL;
    int  toStore = 0;
    if (2==iArgc) 
    {
		toStore = 1; 
		pfileName = iArgv[1];
    }
	
	//---------------------------------------------------------------------------
	// 1-Initializes the factory 
	//---------------------------------------------------------------------------
	
	CATGeoFactory* piGeomFactory = CATCreateCGMContainer() ;
    if (NULL == piGeomFactory) return (1);
    
		//---------------------------------------------------------------------------
	// 2- Creates the lines and circles of the profile
	//---------------------------------------------------------------------------
	
	CATPlane * piPlane = piGeomFactory->CreatePlane(CATMathOIJ);		// Geometrical plan
    if (NULL == piPlane)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
	
	CATMathPoint mathOrigin;
	CATMathDirection mathU, mathV;
	
	// ----------- Retrieves the mathematical definition of the geometrical plane
	piPlane->GetAxis(mathOrigin,mathU,mathV);
	
	// ----------- Defines points on the plane
    // Notice that we do not make any assumption on the plane parameterization.
    // The use of GetParam is allowed here, because the 3D points belong to the plane
    // by construction
	CATSurParam p1, p2, p3, p4, c1, c2;
	piPlane->GetParam(mathOrigin, p1);
	piPlane->GetParam(mathOrigin - 20*mathU                      , p2);
	
	/** @c++ansi mcf 2004-10-08.12:16:00 ['sqrt' : ambiguous call to overloaded function] **/
	piPlane->GetParam(mathOrigin - 10*mathU +    10*sqrt(3.f)  *mathV, p3);
	piPlane->GetParam(mathOrigin            +    10*sqrt(3.f)  *mathV, p4);
	piPlane->GetParam(mathOrigin - 20*mathU +    10          *mathV, c1);
	piPlane->GetParam(mathOrigin - 10*mathU + (10+10*sqrt(3.f))*mathV, c2);
	
	
	// ----------- Defines the curves of the profile
	const int nbPCurves = 5;
    CATPCurve *  aPCurves[nbPCurves];
	CATCrvLimits aLimits[nbPCurves];
	short        aOrientations[nbPCurves];
	aPCurves[0]=  piGeomFactory->CreatePLine   (p1, p2, piPlane );
	aPCurves[0] ->GetLimits(aLimits[0]);
	
	aPCurves[1]=  piGeomFactory->CreatePCircle (10, c1, CATPI/3, 3*CATPI/2, piPlane);
	aPCurves[1] ->GetLimits(aLimits[1]);
	
	aPCurves[2]=  piGeomFactory->CreatePCircle (10, c2, 4*CATPI/3, 3*CATPI/2, piPlane);
	aPCurves[2] ->GetLimits(aLimits[2]);
	
	aPCurves[3]=  piGeomFactory->CreatePLine   (p3, p4, piPlane );
	aPCurves[3] ->GetLimits(aLimits[3]);
	
	aPCurves[4]=  piGeomFactory->CreatePLine   (p4, p1, piPlane );
	aPCurves[4] ->GetLimits(aLimits[4]);
    int i = 0;
for (; i<nbPCurves; i++)
    {
		if (NULL==aPCurves[i])
		{
			::CATCloseCGMContainer(piGeomFactory);
			return (1);
		}
    }
	
	// Defines the orientations of the curves
    // This is needed by the CATTopSkin
	
	aOrientations[0] = 1;
	aOrientations[1] = 1;
	aOrientations[2] = 1;
	aOrientations[3] = 1;
	aOrientations[4] = 1;
	
	CATCrvParam low,high;
	CATMathPoint m1start, m1end, aPoints[2];
	
	// first checks the first two curves
	aLimits[0].GetExtremities(low,high);
	aPCurves[0]->Eval(low , CATCrvEvalCommand::EvalPoint, &m1start);
    aPCurves[0]->Eval(high, CATCrvEvalCommand::EvalPoint, &m1end);
	
    aLimits[1].GetExtremities(low,high);
	aPCurves[1]->Eval(low , CATCrvEvalCommand::EvalPoint, &(aPoints[0]));
    aPCurves[1]->Eval(high, CATCrvEvalCommand::EvalPoint, &(aPoints[1]));
	
    int index1, index2;
	double d1 = m1start.DistanceTo(aPoints,2,index1);
	double d2 =   m1end.DistanceTo(aPoints,2,index2);
	
    if (d1 < d2 )     // the orientation of the first curve is inverted
	{
		aOrientations[0] = -1; 
		if (1==index1) aOrientations[1] = -1;  // the orientation of the second curve is inverted
	}
	else
	{
		if (1==index2) aOrientations[1]= -1;  // the orientation of the second curve is inverted
	}
	
    // Checks now the other curves
	for (i=2;i<5;i++)
	{ 
		m1end   = aPoints [1];
		if (-1==aOrientations[i-1]) m1end   = aPoints [0];
		
		aLimits[i].GetExtremities(low,high);
		aPCurves[i]->Eval(low , CATCrvEvalCommand::EvalPoint, &(aPoints[0]));
		aPCurves[i]->Eval(high, CATCrvEvalCommand::EvalPoint, &(aPoints[1]));
		
		d2 =   m1end.DistanceTo(aPoints,2,index2);
		if (1==index2) aOrientations[i]= -1;
	}
	
	// ---------- Builds the skin
    // Creates the operator
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    CATTopData topdata(pConfig);
    CATTopSkin * pSkinOp = ::CATCreateTopSkin (piGeomFactory,
		&topdata,
		piPlane,
		nbPCurves, 
		aPCurves,
		aLimits,
		aOrientations);
    if (NULL==pSkinOp)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
	
    // Runs
	pSkinOp->Run();
	
    // Gets the resulting body
	CATBody * piSkinBody = pSkinOp->GetResult();
    if (NULL==piSkinBody)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
    
    // Deletes the operator
	delete pSkinOp;
	pSkinOp = NULL;
	
	//---------------------------------------------------------------------------
	// 3- Creates a prism by using a topological operator
	//---------------------------------------------------------------------------
	CATMathDirection   zDir(0., 0., 1.);
	double startOffset = 10.;
    double endOffset   = 30.;
    CATTopPrism       *pPrismOp = ::CATCreateTopPrism (piGeomFactory,
		&topdata,
		piSkinBody,
		&zDir,
		startOffset,
		endOffset);
	
    if (NULL==pPrismOp)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
	
	// Runs
    pPrismOp->Run();
    
    // Gets the resulting body 
    CATBody * piMainBody1=NULL;
	piMainBody1 = pPrismOp->GetResult();
    if (NULL==piMainBody1)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
	
    // Deletes the operator
	delete pPrismOp;
	pPrismOp = NULL;
	
	
	//---------------------------------------------------------------------------
	// 4- Creates a box primitive, a cylinder primitive: CATSolidPrimitive
	//---------------------------------------------------------------------------
	// ---------- Box
	CATMathPoint vO( -2., 2., 28.),  vOI(-2., 15., 28.), vOJ(-15., 2., 28.),  vOK(-2., 2., 35.);
	
    CATSolidCuboid *pCuboidOp = ::CATCreateSolidCuboid( piGeomFactory, 
		&topdata, 
		vO, 
		vOI, 
		vOJ, 
		vOK);
    if (NULL==pCuboidOp)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
	
    // Gets the result (the operator is run at is creation)
	CATBody *piCuboidBody=NULL;
	piCuboidBody = pCuboidOp->GetResult();
    if (NULL==piCuboidBody)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
	
    // Deletes the operator
	delete pCuboidOp;
	pCuboidOp = NULL;	
	
	// ---------- Cylinder
	CATMathPoint axisStart ( -20,  10,  20 ),  axisEnd( -20,  10, 32 );
	double       radius = 4.0; 
	
    CATSolidCylinder *pCylinderOp = ::CATCreateSolidCylinder(piGeomFactory, 
		&topdata, 
		axisStart, 
		axisEnd, 
		radius);
    if (NULL==pCylinderOp)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
	
    // Gets the resulting body (the operator is run at its creation)
	CATBody *piCylinderBody = NULL;
	piCylinderBody = pCylinderOp->GetResult();
    if (NULL==piCylinderBody)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
	
    // Deletes the operator
	delete pCylinderOp;
	pCylinderOp = NULL;
	
	//---------------------------------------------------------------------------
	// 5- Adds and Subtracts: Boolean operators
	//---------------------------------------------------------------------------
    CATDynBoolean* pBoolOp = ::CATCreateDynBoolean (piGeomFactory,
		&topdata,
		CATBoolUnion, 
		piMainBody1, 
		piCuboidBody);
    if (NULL==pBoolOp)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
	
    // Runs
    pBoolOp->Run();
	
    // Gets the resulting body 
    CATBody * piMainBody2 = NULL;
	piMainBody2 = pBoolOp->GetResult();
    if (NULL==piMainBody2)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
	
    // Deletes the operator
	delete pBoolOp;
	pBoolOp = NULL;
	
	piGeomFactory->Remove(piCuboidBody);			// Asks the factory to proceed the deletion (CATBody) 
    piCuboidBody = NULL;
	piGeomFactory->Remove(piMainBody1);
	piMainBody1 = NULL;
	
	// The removal
    pBoolOp = ::CATCreateDynBoolean (piGeomFactory,
		&topdata,
		CATBoolRemoval, 
		piMainBody2, 
		piCylinderBody);
    if (NULL==pBoolOp)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
	
    // Runs
	pBoolOp->Run();
	
    // Gets the resulting body
    CATBody * piMainBody3 = NULL;
	piMainBody3 = pBoolOp->GetResult();
    if (NULL==piMainBody3)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
	
    // Deletes the operator
	delete pBoolOp;
	pBoolOp = NULL;
	
	piGeomFactory->Remove(piCylinderBody);
	piCylinderBody = NULL;
	piGeomFactory->Remove(piMainBody2);
	piMainBody2 = NULL;
	
    //---------------------------------------------------------------------------
	// 6- Filleting
	//---------------------------------------------------------------------------
	
    // ---------- defines the edges to fillet
	CATLISTP(CATCell) listC;
	CATLISTP(CATCell) listFaces;
	piMainBody3 ->GetAllCells(listFaces, 2 );
	int nbFaces=listFaces.Size();	
	CATCell * piFace = NULL;
	
	// ---------- Recovers the only face with 2 internal loops
	
	for ( i=1;i<=nbFaces;i++)
	{
		CATCell * pLocalCell = listFaces[i];
		if (pLocalCell && 3 == (pLocalCell->GetNbDomains()) ) piFace = pLocalCell;
	}
	
	// ---------- and the loop with 5 edges
	CATDomain * piLoop = NULL;	
	CATLISTP(CATEdge) listEdges;	
	int numberOfEdges;
	
	if (NULL != piFace)
	{
		for (i=1;i<=3;i++)
		{
			piLoop = piFace->GetDomain(i);
			if (NULL==piLoop)
			{
				::CATCloseCGMContainer(piGeomFactory);
				return (1);
			}
			else
			{
				piLoop->GetAllCells(listC, 1);      
				numberOfEdges = listC.Size();
				if (5==listC.Size())
				{
					for (int j=1;j<=numberOfEdges;j++)
					{listEdges.Append((CATEdge *)listC[j]);}
				}
				
			}
		}
	}
	else // problem in the definition of the body
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (2);
    }
	
	// ---------- Defines the radius and ribbon
    // for a constant radius, only the first argument is useful
	CATDynFilletRadius * pRadius = new CATDynFilletRadius(1.,    // radius value
		NULL,  // the cell on which the radius is defined
		NULL,  // The ratio of the edge length defining the point
		NULL); // must be kept to NULL
    if (NULL==pRadius)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
	
	CATLISTP(CATDynFilletRadius)	listRadius;		
	listRadius.Append(pRadius);		
	CATDynEdgeFilletRibbon * pRibbon = new 	CATDynEdgeFilletRibbon(listEdges, listRadius);
    if (NULL==pRibbon)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
	
	
    pRibbon ->SetSegmentationMode(CATDynTrim);
	
	// ----------- Creates the operator
    //
	CATDynFillet * pFilletOp = CATCreateDynFillet(piGeomFactory,&topdata,piMainBody3);
    if (NULL==pFilletOp)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
	
	
    // Appends the ribbon
    pFilletOp ->Append(pRibbon);
	
    // Runs
    pFilletOp ->Run(); 
	
    // Gets the resulting body
    CATBody * piMainBody4 = NULL;
	piMainBody4 = pFilletOp->GetResult();
	
    if (NULL==piMainBody4)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
	
    // Deletes the operator
	delete pFilletOp;
	pFilletOp = NULL;
	
	if (NULL != pRadius) delete pRadius;
	pRadius = NULL;
	if (NULL != pRibbon) delete pRibbon;
	pRibbon = NULL;
	
	piGeomFactory->Remove(piMainBody3);
	piMainBody3 = NULL;
	
	//---------------------------------------------------------------------------
	// 7- Shelling
	//---------------------------------------------------------------------------
	// ----------- Recovers the only face with 5 edges and without any internal loops
	//             that will be the opening of the shell
	listEdges.RemoveAll();
	piFace = NULL;
	for (i=1;i<=nbFaces;i++)
	{
		CATCell * pLocalCell = listFaces[i];
		if ( pLocalCell && 1 == (pLocalCell->GetNbDomains()) ) 
		{
			piLoop = pLocalCell->GetDomain(1);
			if (NULL==piLoop)
			{
				::CATCloseCGMContainer(piGeomFactory);
				return (1);
			}
			else {
			piLoop ->GetAllCells(listC, 1);      
			numberOfEdges = listC.Size();
			if (5==listC.Size())
			{
				piFace=pLocalCell;
			}
			}
		}
	}
	
	if (NULL == piFace) return (3);
	
    // --------- Creates the shelling operator
    //
	CATDynShell* pShellOp = CATCreateDynShell (piGeomFactory,
		&topdata,
		piMainBody4,
		-1.,           // the first offset value
		0.);           // the second offset value
    if (NULL==pShellOp)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }	
    // Sets the opening faces
    CATLISTP(CATFace) openings;
	openings.Append((CATFace*)piFace);
    pShellOp-> Append(openings); 
    
    // Runs
	pShellOp->Run();
	
    // Gets the resulting body
    CATBody * piMainBody5 = NULL;
    piMainBody5 = pShellOp->GetResult();
    if (NULL==piMainBody5)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
	
    // Deletes the operator
	delete pShellOp;
    pShellOp = NULL;
	
	piGeomFactory->Remove(piMainBody4,CATICGMContainer::RemoveDependancies);
	piMainBody4 = NULL;
	
	//---------------------------------------------------------------------------
	// 8- Gets the volume of the resulting body
	//--------------------------------------------------------------------------- 
	CATDynMassProperties3D *pPropOp = CATDynCreateMassProperties3D (&topdata, piMainBody5);
	if (NULL != pPropOp)
	{
		cout << "Volume of the final object" << pPropOp->GetVolume() << endl;
		delete pPropOp;
		pPropOp = NULL;
	}
	
    // Releases the configuration
    pConfig->Release();
	
	//---------------------------------------------------------------------------
	// 9- Writes the model
	//---------------------------------------------------------------------------
	cout << "Writing the model" << endl;
    if(1==toStore)
    {
		cout << "Writing the model" << endl;
#ifdef _WINDOWS_SOURCE
		ofstream filetowrite(pfileName, ios::binary ) ;
#else
		ofstream filetowrite(pfileName,ios::out,filebuf::openprot) ;
#endif
		
		::CATSaveCGMContainer(piGeomFactory,filetowrite);
		filetowrite.close();
    }	
	//
	// Closes the container
	//
    ::CATCloseCGMContainer(piGeomFactory);
	return (rc);
}

