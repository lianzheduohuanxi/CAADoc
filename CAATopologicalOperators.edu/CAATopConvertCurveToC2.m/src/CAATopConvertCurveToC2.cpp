/**
* @quickReview CRE 06:07:24
*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2002
//
// Sample code for : Geometric Modeler
// Mission         : Explains how to break a CATNurbsCurve which is C1 continuous 
//                   into C2 curves 
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Illustrates     : 1- Get the input data from an ncgm file 
//   how to          2- Check the curve to be broken 
//                   3- Break the curve into C2 pieces
//                      Reconcatenate the C2 pieces
//                   4- Write the model and close the container 
//
// How to run it   : CAATopConvertTCurveToC2 inputfile.NCGM outputfile.ncgm  
//                   You can use the RationalNurbsCurveC1.ncgm file as input file
//                   It is made up of three arcs and is C2 discontinuous
//                   Degree is 3 - Multiplicities are 4, 2 ,2, 4
//==================================================================
#include <iostream.h>
#include <iomanip.h>
#include "fstream.h"

// Mathematics
#include "CATMathPoint.h"              // Mathematical point
#include "CATSoftwareConfiguration.h"  // Configuration of the operator

// GeometricObjects
#include "CATGeoFactory.h"             // Geometry factory
#include "CATCGMContainerMngt.h"       // Management of the geometry factory
#include "CATNurbsCurve.h"           // NURBS curve
#include "CATKnotVector.h"             // Knot vector
#include "CATCurve.h" 
#include "CATICGMObject.h" 
#include "CATTopData.h" 

// GeometricOperators
#include "CATNurbsCurveTools.h"
#include "CATMathNurbsCurveTools.h"
#include "CATConcatenateNurbsTool.h"
//------------------------------------------------------------------------------
// The return code of the main is null if the execution is OK, not null if some
// problem has been detected
int main(int    iArgc,   // Number of arguments (0) or (1) 
         char** iArgv)   // Path to the *.NCGM document that will contain the result of the main.
{
	int rc=0;
	if(3<iArgc) return (1);

	char *pFileName1 = 0;
	int  toStore = 0;


	char *pFileName = NULL;
	if( 3 != iArgc ) 
	{
		cout << "one .ncgm file is missing" << endl;
		return (1);
	}
	else
	{
		toStore = 1; 
		pFileName = iArgv[1];
		pFileName1 = iArgv[2];
	}
    
    
#ifdef _WINDOWS_SOURCE
    ifstream filetoread(pFileName, ios::binary ) ;
#else
    ifstream filetoread(pFileName) ;
#endif

	// 1 - Get the input data
	//
	//     (a) - Loads the ncgm container where a C1 curve has been stored
	//           for the purpose of this use case
	CATGeoFactory* piGeomFactory = CATLoadCGMContainer(filetoread);
	if (NULL == piGeomFactory) return (1);
	// 
	//     (b) - Retrieves the Nurbs to be broken into C2 pieces
	CATICGMObject * piCGMObj1 = piGeomFactory->FindObjectFromTag(1);
	if (piCGMObj1 == NULL) cout << "No object with the specified tag" <<endl;
	CATNurbsCurve * pNurbs = (CATNurbsCurve *) piCGMObj1;
	if (NULL==pNurbs)
	{
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
	}
	CATCurve * pC1Nurbs = (CATCurve *) pNurbs;
	if (NULL==pC1Nurbs)
	{
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
	}
	// 2 - Creates the CATNurbsCurveTools operators to check the input curve
	//
	//     (a) - Creates the configuration and CATTopData
	CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
	CATTopData topdata(pConfig);
	// 
	//     (b) - Creates the CATNurbsCurveTools operator itself
	CATNurbsCurveTools  * pNurbsTool3D  =::CATCreateNurbsCurveTools(piGeomFactory, pConfig, pC1Nurbs);
	if (NULL==pNurbsTool3D)
	{
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
	}
	//     (c) - Checks the input curve continuity
	CATNurbsToolsInfo infoContinuity = pNurbsTool3D->Check();
	if (infoContinuity != Info_InternalContinuity) 
	{
		cout << "The curve is C2 discontinuous" << endl; 
		// 3 - Breaks the curve by using the CATMathNurbsCurveTools operator
		//
		// (a) - Retrieves the input parameters of the operator
		const CATKnotVector * inputKV = pC1Nurbs->GetKnotVector();  // the knot vector
		CATLONG32  NbCp  =  inputKV->GetNumberOfControlPoints();    // the number of control points 
		// Retrieves the set of control points 
		CATMathSetOfPoints ctlPts  (NbCp);  
		CATMathPoint  pt;
		CATLONG32  i=0;
		for  (i=0;i<NbCp;i++)  
		{  
			pNurbs->GetOneControlPoint(i+1,pt);  
			ctlPts.SetPoint(pt,i);  
		}
		// Retrieves the weights
		double * aWeights = new double[NbCp];
		for  (i=0;i<NbCp;i++)  
		{  
			aWeights[i] = pNurbs->GetOneWeight(i+1);  
		}
		// (b) - Creates the CATMathNurbsCurveTools operator
		CATMathNurbsCurveTools  * pMathNurbsTool3D  =::CATCreateMathNurbsCurveTools( *inputKV,pNurbs->IsRational(),
			ctlPts,CATMathNurbsFull3D, aWeights);
		if (NULL==pMathNurbsTool3D)
		{
			delete [] aWeights;
			aWeights = NULL;
			::CATCloseCGMContainer(piGeomFactory);
			return (1);
		}
		CATLISTP(CATCurve) listOfC2Curves;
		// (c) - Creates the C2 curves
		pMathNurbsTool3D->ConvertToC2NurbsCurves(piGeomFactory,listOfC2Curves);
		cout << listOfC2Curves.Size() << " C2 curves are generated" << endl;
		// (d) - If need be, reconcatenate
		//       By doing this, you don't create a new curve (it is not supported in V5)
		//       but you generate the parameters allowing you to rebuild 
		//       a Nurbs in a different system
		CATMathSetOfPoints * oNewCtlPts = NULL;
		double * oNewWeights = NULL;
		CATKnotVector * oKnotVector = NULL; 
		CATBoolean concatCurves = CATConcatenateNurbsCurves(&listOfC2Curves, oNewCtlPts, oNewWeights, oKnotVector);
		if  (concatCurves != TRUE) return (1);
		if (oNewCtlPts) delete oNewCtlPts; oNewCtlPts = NULL;
		if (oNewWeights) delete [] oNewWeights; oNewWeights = NULL;
	    delete [] aWeights; aWeights = NULL;
		delete pNurbsTool3D; pNurbsTool3D=NULL;
        delete pMathNurbsTool3D; pMathNurbsTool3D=NULL;
	}
	else
	{
		delete pNurbsTool3D; pNurbsTool3D=NULL;
	}
	//-----------------------------------------------------------------------------
	// 4- Writes the model and close the container
	//-----------------------------------------------------------------------------
	//
	pConfig->Release();
	if(1==toStore)
	{
#ifdef _WINDOWS_SOURCE
        ofstream filetowrite(pFileName1, ios::binary ) ;
#else
        ofstream filetowrite(pFileName1,ios::out,filebuf::openprot) ;
#endif
        
        ::CATSaveCGMContainer(piGeomFactory,filetowrite);
        filetowrite.close();
    }	
    
    ::CATCloseCGMContainer(piGeomFactory);
    
    return (rc);
}
