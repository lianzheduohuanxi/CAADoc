// COPYRIGHT DASSAULT SYSTEMES 2000
//============================================================================================
// Sample code for : Sketcher
// Mission         : Create a isocontrained sketch in part with basic geometries,
//                   operation (corner) and constraints
//
// Type            : Batch program
// Inputs          : The new part file path.
// Outputs         : Return code is O if program worked Ok, >0 otherwise
// Run command     : ex : mkrun -c CAASkiBasicGeometries C:\CAASkiBasicGeometries.CATPart  
//
// Illustrates     : o Part document creation 
//                   o Sketch creation
//                   o Geometries creation 
//                   o Constraints creation
//============================================================================================

// System

// ObjectSpecsModeler
#include "CATISpecObject.h"

// ObjectModelerBase
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATSession.h" 
#include "CATSessionServices.h" 
#include "CATIContainer.h"
#include "CATInit.h"

// MecModInterfaces Framework
#include "CATIPrtContainer.h"

// SketcherInterfaces
#include "CATISketch.h"
#include "CATISketchFactory.h"
#include "CATI2DWFFactory.h"
#include "CATI2DConstraintFactory.h"
#include "CATI2DWFFactory.h"
#include "CATI2DWFGeometry.h"
#include "CATI2DPoint.h"
#include "CATI2DLine.h"
#include "CATI2DCurve.h"
#include "CATI2DAxis.h"
#include "CATI2DTopologicalOperators.h"

#include "CATLISTV_CATISpecObject.h"
#include "CATIContainerOfDocument.h"
#include "CATIPrtPart.h"

int main(int    iArgc,   // Number of arguments (1) 
         char** iArgv)   // Path to the new *.CATPart document
{
  //--------------------------------------------------------------------
  // Check arguments
  //--------------------------------------------------------------------
  if(iArgc>2) return 1;
  char *pFileName = iArgv[1];
  char *pSessionIdent = "SampleSession";

  //------------------------------------------------------------------------------------------
  // PART DOCUMENT CREATION
  //------------------------------------------------------------------------------------------
  CATSession *pSession = NULL;
  Create_Session(pSessionIdent,pSession);
  CATDocument *pDocument = NULL;
  CATDocumentServices::New("CATPart",pDocument);
  if ( NULL == pDocument ) return 1;
  CATInit_var spInit (pDocument);
  if( NULL_var == spInit ) return 3; 
  spInit->Init(TRUE); 
  
  CATIContainerOfDocument_var spDoc = pDocument;
	CATIContainer *piContainer = NULL;
  if ( FAILED(spDoc->GetSpecContainer( piContainer)) ) return 4;
  CATIPrtContainer *piPrtContainer = NULL;
  HRESULT hr = piContainer->QueryInterface( IID_CATIPrtContainer, (void **)&piPrtContainer );
  if ( FAILED(hr) ) return 5;
  CATIPrtPart_var spPart(piPrtContainer->GetPart());
  piPrtContainer->Release();
  
  CATLISTV(CATISpecObject_var) spRefPlanes = spPart->GetReferencePlanes();

  //------------------------------------------------------------------------------------------
  // SKETCH CREATION and EDIT:Instantiates the sketch with the plane XY (refPlanes[1])
  //------------------------------------------------------------------------------------------
  CATISketchFactory_var spSketchFactory(piContainer);
  if ( NULL_var == spSketchFactory ) return 6;
  CATISketch_var spSketch(spSketchFactory->CreateSketch(spRefPlanes[1]));
  if ( NULL_var == spSketch ) return 7;
	spSketch->OpenEdition();

  //------------------------------------------------------------------------------------------
  // Creates the elements of the sketch
  //------------------------------------------------------------------------------------------
  CATI2DWFFactory_var sketch2DFactory(spSketch); // Retrieves the 2D factory to create elements
  CATI2DPoint_var spPt_bottom_left, spPt_bottom_right, spPt_top_right, spPt_top_left;
  CATI2DLine_var spLine1, spLine2, spLine3, spLine4;
	double pt_bottom_left[2]  = {10., 10.};
  double pt_bottom_right[2] = {50., 10.};
  double pt_top_right[2]    = {50., 50.};
  double pt_top_left[2]     = {10., 50.};
  
  spPt_bottom_left = sketch2DFactory->CreatePoint(pt_bottom_left);
  spPt_bottom_right = sketch2DFactory->CreatePoint(pt_bottom_right);
  spPt_top_right = sketch2DFactory->CreatePoint(pt_top_right);
  spPt_top_left = sketch2DFactory->CreatePoint(pt_top_left);
	spLine1 = sketch2DFactory->CreateLine(pt_bottom_left,pt_bottom_right);
  spLine2 = sketch2DFactory->CreateLine(pt_bottom_right,pt_top_right);
  spLine3 = sketch2DFactory->CreateLine(pt_top_right,pt_top_left);
  spLine4 = sketch2DFactory->CreateLine(pt_top_left,pt_bottom_left);
  
  // connectivity
	CATI2DCurve_var spCurve1 (spLine1);
	CATI2DCurve_var spCurve2 (spLine2);
	CATI2DCurve_var spCurve3 (spLine3);
	CATI2DCurve_var spCurve4 (spLine4);
	spCurve1->SetStartPoint(spPt_bottom_left); 
  spCurve1->SetEndPoint(spPt_bottom_right);
	spCurve2->SetStartPoint(spPt_bottom_right); 
  spCurve2->SetEndPoint(spPt_top_right);
	spCurve3->SetStartPoint(spPt_top_right); 
  spCurve3->SetEndPoint(spPt_top_left);
	spCurve4->SetStartPoint(spPt_top_left); 
  spCurve4->SetEndPoint(spPt_bottom_left);

  // Constraints
  CATI2DConstraintFactory_var spConstraint2DFactory(spSketch);
  spConstraint2DFactory->CreateConstraint( spLine1, NULL, NULL, NULL, NULL, NULL, NULL, 
                                           Cst2DType_Horizontal, 0, 0 );
  spConstraint2DFactory->CreateConstraint( spLine2, NULL, NULL, NULL, NULL, NULL, NULL, 
                                           Cst2DType_Vertical, 0, 0 );
  spConstraint2DFactory->CreateConstraint( spLine3, NULL, NULL, NULL, NULL, NULL, NULL, 
                                           Cst2DType_Horizontal, 0, 0 );
  spConstraint2DFactory->CreateConstraint( spLine4, NULL, NULL, NULL, NULL, NULL, NULL, 
                                           Cst2DType_Vertical, 0, 0 );
  spConstraint2DFactory->CreateConstraint( spLine2, NULL, NULL, NULL, NULL, NULL, NULL, 
                                           Cst2DType_Length, 0, 0 );
  spConstraint2DFactory->CreateConstraint( spLine2, NULL, spLine4, NULL, NULL, NULL, NULL, 
                                           Cst2DType_Distance, 0, 0 );

	pt_bottom_left[0]  = 20.;
	pt_bottom_left[1]  = 20.;
  spPt_bottom_left->SetPointData(pt_bottom_left);
  // Geometry evaluation with soft reference element (spPt_bottom_left), solver tries to keep
  // fixed these elements (point1 is the more prioritary).
  CATLISTV(CATI2DWFGeometry_var) spSoftReferences(1);
  spSoftReferences.Append(spPt_bottom_left);
  spSketch->Evaluate(spSoftReferences);
 
  // position the point on H and V
  CATI2DAxis_var spSupport;
  spSketch->GetAbsolute2DAxis(spSupport);
  spConstraint2DFactory->CreateConstraint( spPt_bottom_left, NULL, spSupport->GetHDirection(), NULL, NULL, NULL, NULL,
                                           Cst2DType_Distance, 0, 0 );
  spConstraint2DFactory->CreateConstraint( spPt_bottom_left, NULL, spSupport->GetVDirection(), NULL, NULL, NULL, NULL,
                                           Cst2DType_Distance, 0, 0 );

  // Creates corner + constraints
  double radius = 10.;
	double pt_center[2]  = {70., 40.};
  CATI2DCurve_var spCurve5 = sketch2DFactory->CreateCorner(spCurve3, spCurve4, pt_center, &radius);
  CATI2DTopologicalOperators_var spOperateur = spSketch;
  // specifies relimitations
  spOperateur->InsertCorner(spCurve5,spLine3,1,spLine4,1);
  spConstraint2DFactory->CreateConstraint( spLine3, NULL, spCurve5, NULL, NULL, NULL, NULL, 
                                           Cst2DType_Tangent, 0, 0);
  spConstraint2DFactory->CreateConstraint( spCurve5, NULL, spLine4, NULL, NULL, NULL, NULL, 
                                           Cst2DType_Tangent, 0, 0);
  spConstraint2DFactory->CreateConstraint( spCurve5, NULL, NULL, NULL, NULL, NULL, NULL, 
                                           Cst2DType_Radius, 0, 1);

  // Closes the sketch edition
	spSketch->CloseEdition();

  //------------------------------------------------------------------------------------------
  // SAVE PART / CLOSE PART DOCUMENT
  //------------------------------------------------------------------------------------------
  CATDocumentServices::SaveAs(*pDocument,pFileName);
  if (NULL != pSession)
    pSession->Delete_Session(pSessionIdent);

  // Memory cleaning
  piContainer->Release();

  return 0;
}
