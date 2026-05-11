// COPYRIGHT DASSAULT SYSTEMES 2003
//============================================================================================
// Sample code for : Drafting Interfaces
// Mission         : Shows the needed APIs to access and manage generated shape.
//
// Type            : Batch program
// Inputs          : The drawing document containing a generative view file path.
// Outputs         : Return code is O if program worked Ok, >0 otherwise
// Run command     : mkrun -c CAADrwGenShape DrawingForGenShapeUseCase.CATDrawing      
//                               The drawing document file path is CAADraftingInterfaces.edu/FunctionTests/inputData
//                   
// Illustrates     : 
//                   o Drawing document reading.
//                   o Get all points of generated shape in the current section view.
//                   o Get part instance name on which generative shape is associated.
//                   o Get pattern associated to genshape.  
//============================================================================================

// System
#include <iostream.h>
#include "CATUnicodeString.h"
#include "CATIUnknownListImpl.h"
#include "CATIUnknownList.h"
#include "IUnknown.h" 
#include "CATListOfInt.h"

// Mathematics
#include "CATMathPoint2D.h"
#include "CATLISTP_CATMathPoint2D.h"

// ObjectModelerBase (To open documents)
#include "CATInit.h"
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATSessionServices.h" 
#include "CATIContainer.h" 

// DraftingInterfaces 
#include "CATIDftDocumentServices.h"
#include "CATIDftDrawing.h"
#include "CATIDftView.h"
#include "CATIDrwGenDrawShape.h"
#include "CATIDftPattern.h"

// ProductStructure
#include "CATIProduct.h"

// NewTopologicalObjects
#include "CATBody.h"

// ----------------------------------------------------------------------------

int main(int    iArgc,   // Number of arguments (2) 
         char** iArgv)   // Path to the exisiting *.CATDrawing document
{
   // Check arguments
   if(2 != iArgc) return 1;
   const char *pfileNameDrawing = iArgv[1];

   // return code error
   int rc =0;

   // CREATE THE SESSION
   // ==================

   CATSession *pSampleSession = NULL;
   HRESULT hr = ::Create_Session("SampleSession",pSampleSession);
   if (FAILED(hr)) return 1;


   // READ THE DRAWING DOCUMENT
   // =========================

   CATIDftDrawing *piDrawing = NULL;
   CATIDftDocumentServices *piDftDocServices = NULL;
   CATDocument* pDocDrawing = NULL;

   if (FAILED(CATDocumentServices::OpenDocument(pfileNameDrawing, pDocDrawing)))
   {
      // Ends session
      ::Delete_Session("SampleSession");
      return 2;
   }

   if (SUCCEEDED(pDocDrawing->QueryInterface(IID_CATIDftDocumentServices, (void **)&piDftDocServices)))
   {
      if (SUCCEEDED(piDftDocServices->GetDrawing(IID_CATIDftDrawing, (void **)&piDrawing)))
      {
         piDftDocServices->Release();
         piDftDocServices=NULL;
      }
      else
      {
         piDftDocServices->Release();
         piDftDocServices=NULL;

         // Ends session
         ::Delete_Session("SampleSession");
         return 3;
      }
   }
   else 
   {
      // Ends session
      ::Delete_Session("SampleSession");
      return 3;  
   }

   // ACTIVE VIEW RETRIEVAL
   // ========================
   if (piDrawing)
   {
     CATIDftView *piCurrentView = NULL;
     if (SUCCEEDED(piDrawing->GetActiveView(&piCurrentView)))
     {
       // RETRIEVE GENERATED SHAPES  IN THE VIEW
       // ==========================================
       if (NULL != piCurrentView) 
       {
         CATIUnknownList * piList = NULL;
         if (SUCCEEDED( piCurrentView->GetComponents(IID_CATIDrwGenDrawShape,&piList)))
         {
           if (piList)
           {
             unsigned int piListSize = 0;
             piList->Count(&piListSize);
             
             CATIDrwGenDrawShape * piGenShape = NULL;
             IUnknown * item = NULL;
             CATUnicodeString  PartName;
             
             // Loop on all Generated shapes of the view.
             for(unsigned int i=0 ; i<piListSize ; i++)
             {
               if( SUCCEEDED( piList->Item(i, &item) ) )
               {
                 if(SUCCEEDED( item->QueryInterface(IID_CATIDrwGenDrawShape, (void**) & piGenShape) ) )
                 {
                   CATListOfInt  ListOfNbPtPerContour;
                   CATListPtrCATMathPoint2D ListOfPoints;
                   int NbContour=0;
                   if (piGenShape && SUCCEEDED(piGenShape->GetDescription(NbContour, ListOfNbPtPerContour, ListOfPoints)))
                   {
                     // Check geometry
                     for (int numcont=1 ; numcont<=NbContour ; numcont++)
                     {
                       int NbPtcnt = ListOfNbPtPerContour[numcont];
                       for (int numpt=1 ; numpt<=NbPtcnt ; numpt++)
                       {
                         // Get coordinates of the shape
                         CATMathPoint2D *tmpt = ListOfPoints[numpt];
                         if (tmpt) 
                         {
                           cerr << " Number point = " << numpt << " X= = "<< tmpt->GetX() << "Y = " << tmpt->GetY()  <<  endl;
                           // Memory clean
                           delete tmpt ; tmpt=NULL;
                         }
                       }
                     }
                   }
                   IUnknown *piUnk=NULL;
                   if (SUCCEEDED(piGenShape->GetProduct(IID_CATIProduct,&piUnk)))
                   {
                     CATIProduct *piProd =NULL;
                     if (SUCCEEDED(piUnk->QueryInterface(IID_CATIProduct,(void **)&piProd)))
                     {
                       CATUnicodeString instanceName;
                       
                       // Get part instance name on which generative shape is associated.
                       if (SUCCEEDED (piProd->GetPrdInstanceName( instanceName ) ))
                       {
                         cerr << "Part instance name"<< instanceName.ConvertToChar() <<endl;
                       }
                       piProd->Release();piProd=NULL;
                     }
                     piUnk->Release();piUnk=NULL;
                   }
                   
                   // GetBody
                   CATBody *piBody=NULL;
                   if (SUCCEEDED(piGenShape->GetBody(&piBody)))
                   {
                     piBody->Release();
                     piBody=NULL;
                   }
                   
                   // Get Pattern used by the generative shape,
                   CATIDftPattern *piDftPattern=NULL;
                   if (SUCCEEDED(piGenShape->GetPattern(&piDftPattern)))
                   { 
                     int patternType=0;
                     piDftPattern->GetPatternType(&patternType);
                     if (patternType == 1) 
                       cerr << "Hatching Pattern found" << endl;
                     else
                       rc = 4;
                     
                     piDftPattern->Release();piDftPattern=NULL;
                   }
                   
                   // Memory clean                     
                   piGenShape->Release(); piGenShape = NULL;
                   item->Release(); item = NULL;
                 }
               }
             }
             // Memory clean                     
             piList->Release(); piList = NULL;	
           }
         }
         // Memory clean                     
         piCurrentView->Release(); piCurrentView=NULL;
       }
     }
     piDrawing->Release();
     piDrawing = NULL;
   }   

   // CLOSE THE SESSION
   // ====================
   CATDocumentServices::Remove (*pDocDrawing);
   //Ends session and drops document	
   ::Delete_Session("SampleSession");
   
   return rc;
}
