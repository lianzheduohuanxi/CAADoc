// COPYRIGHT DASSAULT SYSTEMES 2000
//============================================================================================
// Sample code for : Drafting Interfaces
// Mission         : Shows the needed APIs to create dimensions on 2D geometry
//
// Type            : Batch program
// Inputs          : The new drawing file path.
// Outputs         : Return code is O if program worked Ok, >0 otherwise
// Run command     : mkrun -c CAADrwCreateDim C:\Test.CATDrawing    
//// Run command     : mkrun -c cmd
//                   launch  CAADrwCreateDim ResultWithDimension.CATDrawing.
//                   ResultWithDimension.CATDrawing is the Drawing model containing the
//                   dimensionb created by this batch.
// Illustrates     : o Drawing document creation.
//                   o Annotation Standard creation.  
//                   o Geometry creation in the main view.
//                   o Get Annotation Factory.
//                   o Create dimensions on created geometry.
//============================================================================================

// System
#include "CATLib.h" 
#include "CATUnicodeString.h"
#include "CATIUnknownListImpl.h"
#include "CATIUnknownList.h"
#include "IUnknown.h" 
#include "CATErrorDef.h"
#include "CATIStringList.h"

// ObjectSpecsModeler
#include "CATISpecObject.h"

// ObjectModelerBase
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATSessionServices.h" 
#include "CATIContainer.h"

// SketcherInterfaces
#include "CATI2DWFFactory.h"

// DraftingInterfaces
#include "CATIDftStandardManager.h"
#include "CATIDftDocumentServices.h"
#include "CATISheet.h"
#include "CATIView.h"
#include "CATIDrwAnnotationFactory.h"
#include "CATDimDefinition.h"
#include "CATDrwUtility.h"

// ----------------------------------------------------------------------------

int main(int    iArgc,   // Number of arguments (1) 
         char** iArgv)   // Path to the new *.CATDrawing document
{
   // Check arguments
   if(2 != iArgc) return 1;
   const char *pfileNameOut = iArgv[1];
   
   
   // CREATE THE SESSION
   // ==================
   
   CATSession *pSampleSession = NULL;
   HRESULT hr = ::Create_Session("SampleSession",pSampleSession);
   if (FAILED(hr)) return 1;
   
   
   // DRAWING DOCUMENT CREATION
   // =========================
   
   CATDocument* pDoc = NULL;
   hr = CATDocumentServices::New("CATDrawing", pDoc); 
   if (FAILED(hr) || !pDoc)
   {
	   // Ends session
	   ::Delete_Session("SampleSession");
	   return 2;
   }
   
   
   // DRAWING STANDARD CREATION
   // =========================
   
   // Gets the drawing feature using the CATIDftDocumentServices interface
   CATIDrawing *piDrawing = NULL;
   CATIDftDocumentServices *piDftDocServices = NULL;
   CATIContainer_var spDrwcont;
   CATISpecObject_var spSpecObj;
   if (SUCCEEDED(pDoc->QueryInterface(IID_CATIDftDocumentServices, (void **)&piDftDocServices)))
   {
	   piDftDocServices->GetDrawing(IID_CATIDrawing, (void **)&piDrawing);
	   piDftDocServices->Release(); piDftDocServices = NULL;
	   spSpecObj=piDrawing;
	   if (spSpecObj != NULL_var) spDrwcont = spSpecObj->GetFeatContainer();
   }
   else
   {
	   CATDocumentServices::Remove (*pDoc);
	   ::Delete_Session("SampleSession");
	   return 3;
   }
   
   if (spDrwcont != NULL_var) 
   {
	   CATIDftStandardManager *piStdmgr = NULL;
	   HRESULT rc = spDrwcont->QueryInterface(IID_CATIDftStandardManager,(void**)&piStdmgr);
	   if (SUCCEEDED(rc))
	   {
		   //  Find a standard in the list of allowed standards (ie. the list of .CATDrwSTD files in the reffiles directory)
		   CATIStringList *piListstd = NULL;
		   if ( SUCCEEDED(piStdmgr->GetAvailableStandards(&piListstd)) && piListstd )
		   {
			   unsigned int  nbrstd = 0;
			   piListstd->Count(&nbrstd);
			   for (unsigned int indice = 0; indice < nbrstd; indice ++)
			   {
				   wchar_t  *wstd = NULL;
				   if ( SUCCEEDED ( piListstd->Item ( indice, &wstd ) )  && wstd )
				   {
					   CATUnicodeString stdname;
					   const CATUnicodeString ANSI_UncS = "ANSI";
                                 stdname.BuildFromWChar(wstd);
					   if ( stdname == ANSI_UncS )  
					   {
						   // Import the ANSI standard in the document
						   piStdmgr->ImportStandard (wstd);
						   break;
					   }
				   }
               if (wstd) {delete[] wstd; wstd = NULL;}
			   }
			   piListstd->Release(); piListstd=NULL;            
		   }
		   piStdmgr->Release (); piStdmgr=NULL;
	   }
   }
   
   
   // MAIN VIEW RETRIEVAL
   // ===================
   
   // We are working in main view of the current sheet
   CATISheet_var spSheet;
   if (piDrawing)
   {
	   spSheet = piDrawing->GetCurrentSheet();
	   piDrawing->Release(); piDrawing = NULL;
   }
   CATIView_var spMainView;
   if ( spSheet != NULL_var) spMainView = spSheet->GetMainView();
   
   
   // GEOMETRY CREATION
   // =================
   // We now can create geometries in the main view after :
   //   - Setting the view as the current one
   //   - Getting the view geometry factory interface
   if (spSheet != NULL_var) spSheet->SetCurrentView(spMainView);
   CATI2DWFFactory_var spGeomFactory = spMainView;
   
   double X[2] = { 100.0, 200.0};
   double Z[2] ={ 50.0, 130.0};
   double startPoint[2], endPoint[2];
   
   // Creation of lines
   startPoint[0] = X[0];
   startPoint[1] = Z[0];
   endPoint[0] = X[1];
   endPoint[1] = Z[0];
   CATISpecObject_var spLine1;
   if (spGeomFactory != NULL_var) spLine1 = spGeomFactory->CreateLine(startPoint, endPoint);
   
   startPoint[0] = X[0];
   startPoint[1] = Z[1];
   endPoint[0] = X[1];
   endPoint[1] = Z[1];
   CATISpecObject_var spLine2;
   if (spGeomFactory != NULL_var) spLine2 = spGeomFactory->CreateLine(startPoint, endPoint);
   
   
   // DIMENSION CREATION
   // ==================
   
   // Gets the view annotation factory
   CATIDrwAnnotationFactory_var spAnnFactory = spMainView;
   
   // Vertical distance dimension creation between Line1 and Line2
   CATDrwDimType dimType = DrwDimDistance;
   CATDimDefinition dimDef;
   CATIUnknownList * piSelectionsList =NULL;
   CATIUnknownListImpl * piListsel = new CATIUnknownListImpl();
   piListsel->QueryInterface(IID_CATIUnknownList, (void **) &piSelectionsList);
   piListsel->Release(); piListsel=NULL;
   
   IUnknown * piLine1 = NULL;
   IUnknown * piLine2 = NULL;
   if (spLine1 != NULL_var) spLine1->QueryInterface(IID_IUnknown, (void **)&piLine1);
   if (spLine2 != NULL_var) spLine2->QueryInterface(IID_IUnknown, (void **)&piLine2);
   if (piSelectionsList)
   {
	   piSelectionsList->Add(0, piLine1);
	   piSelectionsList->Add(1, piLine2);
   }
   
   CATIDrwDimDimension * piDimHoriz = NULL;
   double pt1[2] = {10.0, 15.0};
   double pt2[2] = {0.0, 10.0};
   double  * pts[2] = { NULL, NULL };
   pts[0] = pt1;
   pts[1] = pt2;

   dimDef.Orientation = DrwDimAuto;
   if (spAnnFactory != NULL_var)  hr = spAnnFactory->CreateDimension(piSelectionsList,pts,dimType,&dimDef,&piDimHoriz);
   
   if (piLine1) { piLine1->Release(); piLine1 = NULL;}
   if (piLine2) { piLine2->Release(); piLine2 = NULL;}
   if (piDimHoriz) {piDimHoriz->Release(); piDimHoriz = NULL;}
   if (piSelectionsList) {piSelectionsList->Release(); piSelectionsList = NULL;}
   
   // SAVE THE RESULT
   // ===============
   CATDocumentServices::SaveAs(*pDoc, (char *)pfileNameOut);
   CATDocumentServices::Remove (*pDoc);
   //Ends session and drops document	
   ::Delete_Session("SampleSession");
   
   return 0;
}
