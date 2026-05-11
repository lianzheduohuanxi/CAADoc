// COPYRIGHT DASSAULT SYSTEMES 2001
//============================================================================================
// Sample code for : Drafting Interfaces
// Mission         : Shows the needed APIs to create hatching pattern on 2D geometry
//
// Type            : Batch program
// Inputs          : The new drawing file path.
// Outputs         : Return code is O if program worked Ok, >0 otherwise
// Run command     : mkrun -c cmd
//                   launch  CAADrwCreatePattern CAADrwCreatePattern.CATDrawing Result.CATDrawing
//                   CAADrwCreatePattern.CATDrawing is delivered in
//                   CAADraftingInterfaces/CNext/resources/graphics directory.
//                   Result.CATDrawing is the Drawing model containing the areafill                
//
// Illustrates     : o Drawing document reading.
//                   o Get dress up factory.
//                   o Get geometry for areafill definition
//                   o Create hatching pattern on created geometry.
//                   o Create areafill from geometry and pattern.
//============================================================================================

// Mathematic constants
#include "CATMathDef.h"

// System
#include "CATUnicodeString.h"
#include "CATErrorDef.h"

// ObjectSpecsModeler
#include "CATISpecObject.h"

// ObjectModelerBase
#include "CATIAlias.h"
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATSessionServices.h" 
#include "CATIContainer.h"

// SketcherInterfaces
#include "CATI2DWFGeometry.h"
#include "CATI2DCurve.h"

// DraftingInterfaces
#include "CATISheet.h"
#include "CATIView.h"
#include "CATIDrwFactory.h"
#include "CATIDftDocumentServices.h"
#include "CATIDrwAnnotationFactory.h"
#include "CATIDftHatchingPattern.h"
#include "CATIDrwBreakElem.h"
#include "CATIDrwBreakElemFactory.h"

// ----------------------------------------------------------------------------

int main(int    iArgc,   // Number of arguments (1) 
         char** iArgv)   // Path to the new *.CATDrawing document
{
   // Check arguments
   if(3 != iArgc) return 1;
   const char *pfileName = iArgv[1];
   const char *pfileNameOut = iArgv[2];


   // CREATE THE SESSION
   // ==================

   CATSession *pSampleSession = NULL;
   HRESULT hr = ::Create_Session("SampleSession",pSampleSession);
   if (FAILED(hr)) return 1;


   // READ THE DRAWING DOCUMENT
   // =========================

   CATIDrawing *piDrawing = NULL;
   CATIDftDocumentServices *piDftDocServices = NULL;
   CATDocument* pDoc = NULL;
   CATIContainer_var spDrwcont;
   CATISpecObject_var spSpecObj;
   CATIDrwFactory_var spDrwFact;
   if (FAILED(CATDocumentServices::OpenDocument(pfileName, pDoc)) || !pDoc)
   {
     // Ends session
      ::Delete_Session("SampleSession");
      return 2;
   }

   if (SUCCEEDED(pDoc->QueryInterface(IID_CATIDftDocumentServices, (void **)&piDftDocServices)))
   {
      piDftDocServices->GetDrawing(IID_CATIDrawing, (void **)&piDrawing);
      piDftDocServices->Release(); piDftDocServices = NULL;
      spSpecObj=piDrawing;
      if (spSpecObj != NULL_var) spDrwcont = spSpecObj->GetFeatContainer();
      spDrwFact = spDrwcont;
   }
   else 
   {
	   CATDocumentServices::Remove (*pDoc);
      // Ends session
      ::Delete_Session("SampleSession");
      return 3;  
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
   if (spSheet != NULL_var) spMainView = spSheet->GetMainView();
   
   
   // GEOMETRY READING IN THE MAIN VIEW
   // =================================
   // The drawing startup model contains a profile made of lines and circles. So these
   // elements are arranged.
   
   if ( spSheet !=NULL_var) spSheet->SetCurrentView(spMainView);
   CATISketch_var spSketch = spMainView;
   CATLISTV(CATISpecObject_var) ListValidElem;
   CATListValCATI2DWFGeometry_var spListElem;
   CATUnicodeString namealias;
   if (spSketch != NULL_var) hr = spSketch->GetComponents(CATI2DCurve::ClassName(),spListElem);
   if (SUCCEEDED ( hr))
   {
	   for (int i=1; i<=spListElem.Size(); i++)
	   {
		   // Get all geometric elements containing the string "area" in their external name. 
		   CATIAlias_var spALias(spListElem[i]);
		   if (spALias != NULL_var)
		   {
			   namealias = spALias->GetAlias();
			   if (namealias.SearchSubString("area") != -1)
			   {
				   ListValidElem.Append(spListElem[i]);
			   }
		   }
	   }
   }

   // HATCHING PATTERN CREATION 
   // =========================
   
   CATIDftHatchingPattern *iHatching = NULL;
   
   if (spDrwFact != NULL_var)
   {
	   if (NULL_var!=spDrwFact && SUCCEEDED( spDrwFact->CreateHatchingPattern(IID_CATIDftHatchingPattern, (void **) &iHatching) ))
	   {
		   hr = iHatching->SetOffset(15.0);
		   hr = iHatching->SetAngle ((double)  ( CATRadianToDegree * CATPIBY4));
		   hr = iHatching->SetPitch (8.0);
		   hr = iHatching->SetTexture (1);
		   hr = iHatching->SetThikness(1);
		   hr = iHatching->SetColor(4);
		   
	   }  
	   else 
	   {
		   CATDocumentServices::Remove (*pDoc);
		   // Ends session
		   ::Delete_Session("SampleSession");
		   return 4;
	   }
   }

   // Break Elements CREATION 
   // =======================
      
   // BreakElem are relimited elements to create the areafill domain.
   
   // Gets the BreakElem factory
   CATIDrwBreakElemFactory_var spBreakElemfact;
   if (spDrwcont != NULL_var) 
	   spBreakElemfact = spDrwcont;
   else
   {
	   if (iHatching) { iHatching->Release(); iHatching = NULL;}
	   CATDocumentServices::Remove (*pDoc);
	   // Ends session
	   ::Delete_Session("SampleSession");
	   return 5;
   }
 
   CATLISTV(CATISpecObject_var) ListBreakElem;
   CATI2DCurve_var spCurveElm;
   double pStartParam, pEndParam, pInter ;
   int index=0, creation=0, containment=0;
   
   // Loop on geometry elements 
   for (int i=1; i<=spListElem.Size(); i++)
   {
      spCurveElm = spListElem[i];
      if (spCurveElm != NULL_var) spCurveElm->GetParamExtents(&pStartParam,&pEndParam);
      
      if (pStartParam > pEndParam)
      {
         pInter = pStartParam;
         pStartParam = pEndParam;
         pEndParam = pInter;						
      }
      
      CATIDrwBreakElem_var spBreakElem = spBreakElemfact-> CreateBreakElem(spCurveElm,pStartParam,pEndParam,"",index,creation,containment);
      ListBreakElem.Append(spBreakElem);
   }

   // AREAFILL CREATION 
   // =================
   
   // Notes: The areafill object will be correctly created if BreakElem elements are
   // arranged in the ListeBreakElem list.

   // Gets the annotation factory
   CATIDrwAnnotationFactory_var spAnnFactory = spMainView;

   CATIDrwAreaFill_var AreaFill;
   
   CATISpecObject *piSpecObj = NULL;
   if (iHatching)
   {
	   if (SUCCEEDED(iHatching->QueryInterface(IID_CATISpecObject, (void **)&piSpecObj)))
	   {
		   if (spAnnFactory != NULL_var) AreaFill = spAnnFactory -> CreateDrwAreaFill(ListBreakElem, piSpecObj, "");
		   piSpecObj->Release(); piSpecObj  = NULL;
	   }
	   else
	   {
		   if (iHatching) { iHatching->Release(); iHatching = NULL;}
		   CATDocumentServices::Remove (*pDoc);
		   // Ends session
		   ::Delete_Session("SampleSession");
		   return 5;   
	   }
   }

   // memory cleaning
   if (iHatching) {iHatching->Release(); iHatching = NULL;}
   

   // SAVE THE RESULT
   // ===============

   CATDocumentServices::SaveAs(*pDoc, (char *)pfileNameOut);
   CATDocumentServices::Remove (*pDoc);
   //Ends session and drops document	
   ::Delete_Session("SampleSession");
   
   return 0;
}
 
