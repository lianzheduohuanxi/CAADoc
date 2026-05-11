// COPYRIGHT DASSAULT SYSTEMES 2000
//============================================================================================
// Sample code for : Drafting Interfaces
// Mission         : Reads a drawing and annotates the active view points
//
// Type            : Batch program
// Inputs          : The drawing file path.
// Outputs         : Return code is O if program worked Ok, >0 otherwise
// Run command     : mkrun -c cmd
//                   launch CAADrwCoordinates CAADrwCoordinates.CATDrawing Result.CATDrawing 
//                   CAADrwCoordinates.CATDrawing is delivered in
//                   CAADraftingInterfaces/CNext/resources/graphics directory.
//                   Result.CATDrawing is the Drawing model containing the annotations.  
// Illustrates     : o Drawing document creation 
//                   o The Drawing, sheet and view interfaces
//                   o The way to get the view gemetry
//                   o The text creation and text properties
//============================================================================================

// System
#include <iostream.h>
#include "CATLib.h" 
#include "CATUnicodeString.h"

// ObjectSpecsModeler
#include "CATISpecObject.h"

// ObjectModelerBase
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATSessionServices.h" 

// SketcherInterfaces
#include "CATI2DPoint.h"

// MechanicalModeler
#include "CATIDescendants.h"

// DraftingInterfaces
#include "CATIDftDocumentServices.h"
#include "CATIDrawing.h"
#include "CATISheet.h"
#include "CATIView.h"
#include "CATIDrwAnnotationFactory.h"
#include "CATIDftText.h"
#include "CATIDftTextProperties.h"
#include "CATIDrwSubString.h"

// ----------------------------------------------------------------------------

int main(int    iArgc,   // Number of arguments (1) 
         char** iArgv)   // Path to the *.CATDrawing document
{
   // Check arguments
   if(3 != iArgc) return 1;
   const char *fileName = iArgv[1];
   const char *fileNameOut = iArgv[2];

   // READ THE DRAWING DOCUMENT
   // =========================

   // creates a session
   CATSession *pSampleSession = NULL;
   HRESULT hr = ::Create_Session("SampleSession",pSampleSession);
   if (FAILED(hr)) return 1;

   // read the document
   CATDocument* pDoc = NULL;
   if (!SUCCEEDED(CATDocumentServices::OpenDocument(fileName, pDoc)))
   {
      // Ends session
      ::Delete_Session("SampleSession");
      return 2;
   }

   // ACTIVE VIEW RETRIEVAL
   // =====================

   // Gets the drawing feature using the CATIDftDocumentServices interface
   CATIDrawing *piDrawing = NULL;
   CATIDftDocumentServices *piDftDocServices = NULL;
   if (SUCCEEDED(pDoc->QueryInterface(IID_CATIDftDocumentServices, (void **)&piDftDocServices)))
   {
      piDftDocServices->GetDrawing(IID_CATIDrawing, (void **)&piDrawing);
      piDftDocServices->Release(); piDftDocServices=NULL;
   }

   if (NULL == piDrawing)
      return 3;

   // We can get the current sheet
   CATISheet_var spSheet = piDrawing->GetCurrentSheet();
   // And the sheet current view
   CATIView_var spCurrentView = spSheet->GetCurrentView();

   // Memory cleaning
   piDrawing->Release(); piDrawing=NULL;
   

   // GEOMETRY RETRIEVAL
   // ==================

   // Now we do seek all the points in the view
   CATIDescendants_var spDesc = spCurrentView;
   CATListValCATISpecObject_var pointList;
   spDesc->GetDirectChildren ("CATI2DPoint",pointList);


   // TEXT CREATION
   // =============

   // loop on points 
   for (int ii=1; ii<=pointList.Size(); ii++)
   {
      // Gets the coordinates
      CATI2DPoint_var spPoint = pointList[ii];
      double coord[2];
      spPoint->GetPointData(coord);
      // Compute the string
      CATUnicodeString textString("Point ");
      CATUnicodeString index;
      index.BuildFromNum(ii);
      textString += index;
      int titleLength = textString.GetLengthInChar();
      textString.Append("\n");
      textString.Append("X = ");
      CATUnicodeString coordText[2];
      coordText[0].BuildFromNum(coord[0]);
      textString.Append(coordText[0]);
      textString.Append("\n");
      textString.Append("Y = ");
      coordText[1].BuildFromNum(coord[1]);
      textString.Append(coordText[1]);

      // Creates the Text
      CATIDrwAnnotationFactory_var spAnnFactory = spCurrentView;
      CATIDftText *piDftText = NULL;
      const double txtpos[2] = {coord[0]+10.0,coord[1]+10.0};
      if (SUCCEEDED(spAnnFactory->CreateDftText(txtpos, &piDftText)))
      {
         wchar_t *ptxtChar = new wchar_t[textString.GetLengthInChar()+1];
         textString.ConvertToWChar(ptxtChar);
         piDftText->SetString(ptxtChar);
         delete [] ptxtChar;
         ptxtChar = NULL; 
         CATIDrwSubString *piDrwSubString = NULL;
         if (SUCCEEDED(piDftText->QueryInterface(IID_CATIDrwSubString,(void **)&piDrwSubString)))
         {
            // Select the sub string to modifiable.
            piDrwSubString->SetSelection(1,8);

            // Modify the properties
            CATIDftTextProperties *piTextProp = NULL;
            if (SUCCEEDED(piDftText->GetTextProperties(&piTextProp)))
            {
               piTextProp->SetBold(TRUE);
               piTextProp->SetUnderline(TRUE);
               piTextProp->Release();piTextProp=NULL;
            }
            piDrwSubString->Release();piDrwSubString=NULL;
         }
         piDftText->Release();piDftText=NULL;
      }
   }
   // Save the result
   hr = CATDocumentServices::SaveAs(*pDoc, (char *)fileNameOut);
   if (FAILED(hr)) return 4;

   // Ends session and drops document	
   CATDocumentServices::Remove (*pDoc);
   ::Delete_Session("SampleSession");

   return 0;
}
