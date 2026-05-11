// COPYRIGHT DASSAULT SYSTEMES 2000
//============================================================================================
// Sample code for : Drafting Interfaces
// Mission         : Shows the needed APIs to create a drawing with a title block
//
// Type            : Batch program
// Inputs          : The new drawing file path.
// Outputs         : Return code is O if program worked Ok, >0 otherwise
// Run command     : mkrun -c CAADrwTitleBlock C:\Test.CATDrawing    
//
// Illustrates     : o Drawing document creation 
//                   o The background view usage
//                   o Texts creation
//                   o Geometriy creation 
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
#include "CATIContainer.h"

// SketcherInterfaces
#include "CATI2DWFFactory.h"

// DraftingInterfaces
#include "CATIDftDocumentServices.h"
#include "CATIDrawing.h"
#include "CATISheet.h"
#include "CATIView.h"
#include "CATIDrwAnnotationFactory.h"
#include "CATIDftText.h"
#include "CATIDrwSubString.h"
#include "CATIDftTextProperties.h"
#include "CATDrwUtility.h"

// ----------------------------------------------------------------------------

int main(int    iArgc,   // Number of arguments (1) 
         char** iArgv)   // Path to the new *.CATDrawing document
{
   // Check arguments
   if(3 != iArgc) return 1;
   const char *fileName = iArgv[1];
   const char *fileNameOut = iArgv[2];


   // CREATE THE SESSION
   // ==================

   CATSession *pSampleSession = NULL;
   HRESULT hr = ::Create_Session("SampleSession",pSampleSession);
   if (FAILED(hr)) return 1;


   // READ THE DRAWING DOCUMENT
   // =========================
  
   CATDocument* pDoc = NULL;
   if (!SUCCEEDED(CATDocumentServices::OpenDocument(fileName, pDoc)))
   {
      // Ends session
      ::Delete_Session("SampleSession");
      return 2;
   }


   // BACKGROUND VIEW RETRIEVAL
   // =========================

   // Gets the drawing feature using the CATIDftDocumentServices interface
   CATIDrawing *piDrawing = NULL;
   CATIDftDocumentServices *piDftDocServices = NULL;
   if (SUCCEEDED(pDoc->QueryInterface(IID_CATIDftDocumentServices, (void **)&piDftDocServices)))
   {
      piDftDocServices->GetDrawing(IID_CATIDrawing, (void **)&piDrawing);
      piDftDocServices->Release();
      piDftDocServices=NULL;
   }

   if (NULL == piDrawing)
      return 1;

   // We can get the current sheet
   CATISheet_var spSheet = piDrawing->GetCurrentSheet();
   // And the sheet bacground-view
   CATIView_var spBgView = spSheet->GetBackgroundView();

   // Memory cleaning
   piDrawing->Release();
   piDrawing=NULL;
   
   // GEOMETRY CREATION
   // =================

   // We now can create geometries in the view after :
   //   - Setting the view as the current one
   //   - Getting the view geometry factory interface
   spSheet->SetCurrentView(spBgView);
   CATI2DWFFactory_var spGeomFactory = spBgView;
   
   double X[8] = { 936.0, 949.0, 963.0, 1010.0, 1062.0, 1093.0, 1157.0, 1176.0};
   double Z[11] ={ 17.0, 22.0, 35.0, 48.0, 53.0, 58.0, 63.0, 68.0, 73.0, 78.0, 88.0};
   double PtTmp[6];
     
   double startPoint[2], endPoint[2];
   
   // Creation of horizontal lines
   PtTmp[0]=Z[0];
   PtTmp[1]=Z[1];
   PtTmp[2]=Z[3];
   PtTmp[3]=Z[5];
   PtTmp[4]=Z[7];
   PtTmp[5]=Z[10];
   int i = 0;
   for (;i < 6; i++)
   {
       startPoint[0] = X[0];
       startPoint[1] = PtTmp[i];
       endPoint[0] = X[7];
       endPoint[1] = PtTmp[i];
       spGeomFactory->CreateLine(startPoint, endPoint);
   }
   startPoint[0] = X[3];
   startPoint[1] = Z[2];
   endPoint[0] = X[7];
   endPoint[1] = Z[2];
   spGeomFactory->CreateLine(startPoint, endPoint);

   startPoint[0] = X[0];
   startPoint[1] = Z[9];
   endPoint[0] = X[5];
   endPoint[1] = Z[9];
   spGeomFactory->CreateLine(startPoint, endPoint);

   PtTmp[0]=Z[4];
   PtTmp[1]=Z[6];
   PtTmp[2]=Z[8];
   for (i= 0;i < 3; i++)
   {
       startPoint[0] = X[3];
       startPoint[1] = PtTmp[i];
       endPoint[0] = X[5];
       endPoint[1] = PtTmp[i];
       spGeomFactory->CreateLine(startPoint, endPoint);
   }

   // Creation of vertical lines
   PtTmp[0]=X[0];
   PtTmp[1]=X[7];
   for (i= 0;i < 2; i++)
   {
       startPoint[0] = PtTmp[i];
       startPoint[1] = Z[0];
       endPoint[0] = PtTmp[i];
       endPoint[1] = Z[10];
       spGeomFactory->CreateLine(startPoint, endPoint);
   }

   startPoint[0] = X[3];
   startPoint[1] = Z[1];
   endPoint[0] = X[3];
   endPoint[1] = Z[10];
   spGeomFactory->CreateLine(startPoint, endPoint);
 
   startPoint[0] = X[5];
   startPoint[1] = Z[3];
   endPoint[0] = X[5];
   endPoint[1] = Z[10];
   spGeomFactory->CreateLine(startPoint, endPoint);

   PtTmp[0]=X[4];
   PtTmp[1]=X[6];
   for (i= 0;i < 2; i++)
   {
       startPoint[0] = PtTmp[i];
       startPoint[1] = Z[1];
       endPoint[0] = PtTmp[i];
       endPoint[1] = Z[2];
       spGeomFactory->CreateLine(startPoint, endPoint);
   }

   startPoint[0] = X[1];
   startPoint[1] = Z[5];
   endPoint[0] = X[1];
   endPoint[1] = Z[7];
   spGeomFactory->CreateLine(startPoint, endPoint);

   startPoint[0] = X[2];
   startPoint[1] = Z[5];
   endPoint[0] = X[2];
   endPoint[1] = Z[9];
   spGeomFactory->CreateLine(startPoint, endPoint);

   //  Lines and circles creation for projection mode symbol.
   double X1[3] = { 941.0, 949.0, 955.0};
   double Z1[5] ={ 70.0, 71.0, 73.0, 75.0, 76.0};
   startPoint[0] = X1[0];
   startPoint[1] = Z1[1];
   endPoint[0] = X1[0];
   endPoint[1] = Z1[3];
   spGeomFactory->CreateLine(startPoint, endPoint);    

   startPoint[0] = X1[0];
   startPoint[1] = Z1[3];
   endPoint[0] = X1[1];
   endPoint[1] = Z1[4];
   CATISpecObject_var Line1 = spGeomFactory->CreateLine(startPoint, endPoint);    

   startPoint[0] = X1[1];
   startPoint[1] = Z1[4];
   endPoint[0] = X1[1];
   endPoint[1] = Z1[0];
   spGeomFactory->CreateLine(startPoint, endPoint);    

   startPoint[0] = X1[1];
   startPoint[1] = Z1[0];
   endPoint[0] = X1[0];
   endPoint[1] = Z1[1];
   CATISpecObject_var Line2 = spGeomFactory->CreateLine(startPoint, endPoint);    

   // Creation of two concentric circles:
   double center[2];
   center[0]=X1[2];
   center[1]=Z1[2];
   double radius = 3.0;
   CATISpecObject_var Cercle1 = spGeomFactory->CreateCircle(center,radius);

   radius = 2.0;
   spGeomFactory->CreateCircle(center,radius);

   // DRESSUP CREATION
   // ================

   // Gets the view annotation factory
   CATIDrwAnnotationFactory_var spAnnFactory = spBgView;

   // Texts creation
   CATIDftText *piDftText = NULL;
   const double txtpos1[2] = {1013.,45.};
   if (SUCCEEDED(spAnnFactory->CreateDftText(txtpos1,&piDftText)))
   {
      // Set String
      CATUnicodeString textString("TITLE BLOCK PERFORMED BY CAA2 APPLICATION");
      wchar_t *ptxtChar = new wchar_t[textString.GetLengthInChar() + 1];
      textString.ConvertToWChar(ptxtChar);
      piDftText->SetString(ptxtChar);
      delete [] ptxtChar;
      ptxtChar = NULL; 
      // Text properties modification: Set bold and italic
      CATIDftTextProperties *piDftTextProp = NULL;
      if (SUCCEEDED(piDftText->GetTextProperties(&piDftTextProp)))
      {
         piDftTextProp->SetBold(TRUE);
         piDftTextProp->SetItalic(TRUE);

         piDftTextProp->Release();piDftTextProp=NULL;
      }
      piDftText->Release();piDftText=NULL;
   }
   const double txtpos2[2] = {940., 40.};
   if (SUCCEEDED(spAnnFactory->CreateDftText(txtpos2,&piDftText)))
   {
      // Set String
      CATUnicodeString textString("DASSAULT \nSYSTEMES");
      wchar_t *ptxtChar = new wchar_t[textString.GetLengthInChar() +1];
      textString.ConvertToWChar(ptxtChar);
      piDftText->SetString(ptxtChar);
      delete [] ptxtChar;
      ptxtChar = NULL; 
      CATIDftTextProperties *piDftTextProp = NULL;
      // Text properties modification: Set bold and italic
      if (SUCCEEDED(piDftText->GetTextProperties(&piDftTextProp)))
      {
         piDftTextProp->SetBold(TRUE);
         piDftTextProp->SetItalic(TRUE);
         piDftTextProp->Release();piDftTextProp=NULL;
      }
      piDftText->Release();piDftText=NULL;
   }
   const double txtpos3[2] = {940., 54.};
   if (SUCCEEDED(spAnnFactory->CreateDftText(txtpos3,&piDftText)))
   {
      // Set String
      CATUnicodeString textString("Date : 07 - 31 - 2000");
      wchar_t *ptxtChar = new wchar_t[textString.GetLengthInChar() +1];
      textString.ConvertToWChar(ptxtChar);
      piDftText->SetString(ptxtChar);
      delete [] ptxtChar;
      ptxtChar = NULL; 
      // Text properties modification: Set bold and italic
      CATIDftTextProperties *piDftTextProp = NULL;
      if (SUCCEEDED(piDftText->GetTextProperties(&piDftTextProp)))
      {
         piDftTextProp->SetBold(TRUE);
         piDftTextProp->SetItalic(TRUE);

         CATIDrwSubString *piDrwSubString = NULL;
         if (SUCCEEDED(piDftText->QueryInterface(IID_CATIDrwSubString,(void **)&piDrwSubString)))
         {
            // Select the sub string to modifiable.
            piDrwSubString->SetSelection(1,21);
            piDftTextProp->SetFontSize(3.5);
            piDrwSubString->Release();piDrwSubString=NULL;
         }
         piDftTextProp->Release();piDftTextProp=NULL;
      }
      piDftText->Release();piDftText=NULL;
   }

   // axis line and center line creation
   CATIDrwAxisLine_var axisline = spAnnFactory->CreateDrwAxisLine(Line1,Line2);
   CATIDrwCenterLine_var centerline = spAnnFactory->CreateDrwCenterLine(Cercle1);


   // SAVE THE RESULT
   // ===============
   cout << "sauvegarde du document " << endl;
   CATDocumentServices::SaveAs(*pDoc, (char *)fileNameOut);
	CATDocumentServices::Remove (*pDoc);
   // Ends session and drops document	
   ::Delete_Session("SampleSession");


   return 0;
}
