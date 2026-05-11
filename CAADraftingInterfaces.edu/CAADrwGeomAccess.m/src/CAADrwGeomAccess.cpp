// COPYRIGHT DASSAULT SYSTEMES 2001
//============================================================================================
// Sample code for : Drafting Interfaces
// Mission         : Shows the needed APIs to access and manage generated Geometry.
//
// Type            : Batch program
// Inputs          : The drawing document containing a generative view file path.
// Outputs         : Return code is O if program worked Ok, >0 otherwise
// Run command     : mkrun -c CAADrwGeomAccess C:\Test.CATDrawing  C:\TestResult.CATDrawing      
// Run command     : mkrun -c cmd
//                   Before running this batch:
//                         - Create a CATPart document contenaing a Part 
//                         - Save this document.
//                         - Create a CATDrawing document with a  Front View of that Part.
//                         - Save the CATDrawing document.
//                   launch  CAADrwGeomAccess C:\Test.CATDrawing C:\TestResult.CATDrawing.
//                   Test.CATDrawing is the Drawing model containing built the Generated Geometry 
//                   TestResult.CATDrawing is the Drawing model containing the Generated Geometry 
//                   modified by this batch.
//                   
// Illustrates     : 
//                   o Drawing document reading.
//                   o Get the generative active view.  
//                   o Get the Part document pointed by the generative view and open it.       
//                   o Scan all the generated geometry of the view
//                   o Modify the color of the generated geometry.
//                   o Save the Drawing document.
//============================================================================================

// System
#include "CATUnicodeString.h"
#include "CATIUnknownListImpl.h"
#include "CATIUnknownList.h"
#include "IUnknown.h" 

// ObjectModelerBase (To open documents)
#include "CATInit.h"
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATSessionServices.h" 
#include "CATIContainer.h"

// DraftingInterfaces 
#include "CATIDrawing.h"
#include "CATISheet.h"
#include "CATIView.h"
#include "CATILinkableObject.h"
#include "CATIDftDocumentServices.h"
#include "CATIDftSheet.h"
#include "CATIDftView.h"
#include "CATIDftGenView.h"
#include "CATIDftGenGeomAccess.h"
#include "CATIDftGenGeom.h"

// MecModInterfaces (Part Access)
#include "CATIPrtContainer.h"
#include "CATIPrtPart.h"

// Visualization (To modify generated geometry visualization)
#include "CATIVisProperties.h"
#include "CATIVisPropertiesAbstract.h"
#include "CATVisPropertiesValues.h" 
#include "CATVisPropertyType.h"

// GeometricElement
#include "CATCurve.h"

// ----------------------------------------------------------------------------

int main(int    iArgc,   // Number of arguments (2) 
         char** iArgv)   // Path to the new *.CATDrawing document
{
   // Check arguments
   if(3 != iArgc) return 1;
   const char *pfileNameDrawing = iArgv[1];
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
   CATDocument* pDocDrawing = NULL;

   if (FAILED(CATDocumentServices::OpenDocument(pfileNameDrawing, pDocDrawing)))
   {
      // Ends session
      ::Delete_Session("SampleSession");
      return 2;
   }

   if (SUCCEEDED(pDocDrawing->QueryInterface(IID_CATIDftDocumentServices, (void **)&piDftDocServices)))
   {
      if (SUCCEEDED(piDftDocServices->GetDrawing(IID_CATIDrawing, (void **)&piDrawing)))
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
   
   // We are working in front view of the current sheet
   CATISheet_var spSheet = piDrawing->GetCurrentSheet();
   piDrawing->Release();
   piDrawing=NULL;

   CATIDftSheet *piSheet = NULL;
   CATIDftView *piCurrentView = NULL;

   if (SUCCEEDED(spSheet->QueryInterface(IID_CATIDftSheet,(void**) & piSheet) ) )
   {
      piSheet->GetDefaultActiveView (&piCurrentView);
      piSheet->Release();
      piSheet=NULL;
   }


   // READ THE PART DOCUMENT POINTED BY CURRENT VIEW
   // =====================================================

    // A link is created between a generative view  and the CATPart document associated 
   //  to keep the 2D/3D associativity. So, we can find the CATPart document from this link.
   CATIView_var spCurrentView = spSheet->GetCurrentView();
   CATILinkableObject_var spLink;
   CATDocument* pDocPart = NULL; 
   if (NULL_var != spCurrentView)
      spLink = spCurrentView->GetDoc();

   if (NULL_var != spLink)
       pDocPart = spLink->GetDocument();

   if (pDocPart)
   {
      CATInit_var spInitOnDoc(pDocPart);
      if(NULL_var == spInitOnDoc) return 5;
      
      // Retrieves the root container
      CATIPrtContainer * piPrtCont =  (CATIPrtContainer*) spInitOnDoc->GetRootContainer("CATIPrtContainer");	
      if (!piPrtCont)
      {
         // Ends session
         ::Delete_Session("SampleSession");
         return 6;
      }
      // Get the part feature of the container.
      CATIPrtPart_var spPart = piPrtCont->GetPart();
      piPrtCont->Release();
      piPrtCont=NULL;
   }


   // GENERATED GEOMETRY READING IN THE VIEW
   // ============================================
   
   CATIDftGenGeomAccess *piGenGeomAccess = NULL;
   IUnknown *piGenView = NULL;
   if (NULL != piCurrentView) 
   {
      if (SUCCEEDED( piCurrentView->GetApplicativeExtension(IID_CATIDftGenView,&piGenView)))
      {
         if (SUCCEEDED( piGenView->QueryInterface(IID_CATIDftGenGeomAccess, (void**) & piGenGeomAccess) ) )
         {
            CATIUnknownList * piList = NULL;
            
            // Get a list containing all Generated Geometry of the view.
            if( SUCCEEDED( piGenGeomAccess->GetAllGeneratedItems(IID_CATIDftGenGeom, &piList) ) )
            {
               unsigned int piListSize = 0;
               piList->Count(&piListSize);
               
               CATIDftGenGeom * piGenGeom = NULL;
               IUnknown * item = NULL;
               CATUnicodeString  PartName;
               CATIVisProperties *piVisProp = NULL;
               CATVisPropertiesValues ioValues;
               CATVisPropertyType       iPropertyType = CATVPColor;
               
               // Loop on all Generated Geometry of the view.
               for(unsigned int i=0 ; i<piListSize ; i++)
               {
                  if( SUCCEEDED( piList->Item(i, &item) ) )
                  {
                     if(SUCCEEDED( item->QueryInterface(IID_CATIDftGenGeom, (void**) & piGenGeom) ) )
                     {
                        CATCurve * Curve = NULL;
                        if (SUCCEEDED(piGenGeom->GetUnderlyingGeometry(&Curve))) 
                        {
                           // Color modification
                           if(SUCCEEDED( piGenGeom->QueryInterface(IID_CATIVisProperties, (void**) & piVisProp) ) )
                           {
                              CATBoolean cutInfo = FALSE;
                              if (SUCCEEDED(piGenGeom->IsCut(&cutInfo)))
                              {
                                 // Red color is applied for generated geometry coming from section 
                                 if (cutInfo)
                                    ioValues.SetColor( 255,0,0);
                                 // Greeen color is applied for generated geometry coming from projection
                                 else
                                    ioValues.SetColor( 0,255,0);
                              
                                 piVisProp->SetPropertiesAtt(  ioValues, iPropertyType, CATVPLine);
                              }
                              piVisProp->Release();
                              piVisProp=NULL;                         
                           }
                           
                           Curve->Release(); Curve = NULL;
                        }
                        
                        // Memory clean                     
                        piGenGeom->Release(); piGenGeom = NULL;
                        item->Release(); item = NULL;
                     }
                  }
               }
               // Memory clean                     
               piList->Release(); piList = NULL;	
            }
            // Memory clean                     
            piGenGeomAccess->Release(), piGenGeomAccess = NULL;
         }
         // Memory clean                     
         piGenView->Release() , piGenView=NULL;
      }
      // Memory clean                     
      piCurrentView->Release() , piCurrentView=NULL;
   }

   
   // SAVE THE RESULT
   // ===============
   if (pDocDrawing)
   {
      CATDocumentServices::SaveAs(*pDocDrawing, (char *)pfileNameOut);
      CATDocumentServices::Remove (*pDocDrawing);
   }
   if (pDocPart)
      CATDocumentServices::Remove (*pDocPart);
   //Ends session and drops document	
   ::Delete_Session("SampleSession");
   
   return 0;
}
