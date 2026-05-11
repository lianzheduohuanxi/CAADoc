// COPYRIGHT DASSAULT SYSTEMES 2004
//============================================================================================
// Sample code for : Drafting Interfaces
// Mission         : Shows the needed APIs to create view from 3D.
//
// Type            : Batch program
// Inputs          : The PadWith3DAnnotations.CATPart document containing 3D Annotations delivered in
//                         CAADraftingInterfaces.edu/CNEXT/resources/graphic folder.
// Outputs         : A new Drawing document in which a Generative Drawing View has been Created
//                          Return code is O if program worked Ok, >0 otherwise
// Run command     : mkrun -c CAADrwCreateViewFrom3D C:\PadWith3DAnnotations.CATPart C:\TestResult.CATDrawing      
//                   
// Illustrates     : 
//                   o Drawing document creation.
//                   o Get a Part document and open it.       
//                   o Get TPS Active view in TPS application
//                   o Create a Drawing View from TPS view.
//                   o Save the Drawing document.
//============================================================================================

// System
#include "CATIStringList.h" 
#include "CATUnicodeString.h"
#include "IUnknown.h" 

// ObjectModelerBase 
#include "CATSession.h" 
#include "CATSessionServices.h" 
#include "CATInit.h"
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATIContainer.h"
#include "CATISpecObject.h"

// DraftingInterfaces 
#include "CATIDftDocumentServices.h"
#include "CATIDftDrawing.h"
#include "CATIDftSheet.h"
#include "CATIDftGenViewFactory.h"
#include "CATIDftView.h"
#include "CATIDftStandardManager.h"

// Tolerancing
#include "CATITPSDocument.h"
#include "CATITPSList.h"
#include "CATITPSComponent.h"
#include "CATITPSSet.h"
#include "CATITPSView.h"

// Sub program to create a Drawing Generative View from TPS View.
// =========================================================
HRESULT CreateViewFrom3DInDrawingDoc(CATDocument *ipNewDoc, CATITPSView *ipiTPSActiveView)
{
   HRESULT hr = E_FAIL;

   if (ipNewDoc && ipiTPSActiveView)
   {
      // DRAWING STANDARD CREATION
      // ===============================
      
      // Gets the drawing feature using the CATIDftDocumentServices interface
      CATIDftDrawing *piDftDrawing = NULL;
      CATIDftDocumentServices *piDftDocServices = NULL;
      CATIContainer_var spDrwCont;
      if (SUCCEEDED(ipNewDoc->QueryInterface(IID_CATIDftDocumentServices, (void **)&piDftDocServices)))
      {
         piDftDocServices->GetDrawing(IID_CATIDftDrawing, (void **)&piDftDrawing);
         piDftDocServices->Release(); 
         piDftDocServices = NULL;
         if (piDftDrawing)
         {
            CATISpecObject *piDrawingSO=NULL;
            if (SUCCEEDED(piDftDrawing->QueryInterface(IID_CATISpecObject,(void **)&piDrawingSO)))
            {
               spDrwCont = piDrawingSO->GetFeatContainer();
               if (NULL_var != spDrwCont)
               {
                  CATIDftStandardManager *piStdmgr = NULL;
                  hr = spDrwCont->QueryInterface(IID_CATIDftStandardManager,(void**)&piStdmgr);
                  if (SUCCEEDED(hr))
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
                              const CATUnicodeString ISO_UncS = "ISO";
                              stdname.BuildFromWChar(wstd);
                              if ( stdname == ISO_UncS )  
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
               
               // Creation of new generative view from TPS view in the active sheet of the Drawing Document
               CATIDftView *piDftViewFrom3D = NULL;
               CATIDftSheet  *piDftSheet = NULL;
               if (SUCCEEDED(piDftDrawing->GetActiveSheet(&piDftSheet)))
               {
                  // View anchor point definition
                  double ptOrigin[2] = {150.0,150.0};
                  IUnknown *pTPSViewUk = NULL;
                  if (SUCCEEDED(ipiTPSActiveView->QueryInterface(IID_IUnknown,(void **)&pTPSViewUk)))
                  {
                     CATIDftGenViewFactory *piDftGenViewFact = NULL;
                     if (SUCCEEDED(piDftSheet->QueryInterface(IID_CATIDftGenViewFactory,(void **)&piDftGenViewFact))) 
                     {
                        hr = piDftGenViewFact->CreateViewFrom3D(ptOrigin, pTPSViewUk, &piDftViewFrom3D);
                        if (SUCCEEDED(hr) && piDftViewFrom3D)
                           hr =S_OK;
                        else
                           hr =E_FAIL;

                        piDftGenViewFact->Release();piDftGenViewFact=NULL;
                     }
                     pTPSViewUk->Release();
                     pTPSViewUk=NULL;
                  }
                  piDftSheet->Release();
                  piDftSheet=NULL;
               }
               piDrawingSO->Release();
               piDrawingSO=NULL;
            }
            piDftDrawing->Release(); 
            piDftDrawing = NULL;
         }
      }
   }   
   return hr;
}


// -------------------------------------------------------------------------------------------------------------------------------------------------------
// Main program

int main(int    iArgc,   // Number of arguments (2) 
         char** iArgv)   // Path to the new *.CATDrawing document
{
   // Check arguments
   if(3 != iArgc) return 1;
   const char *pfileNamePart = iArgv[1];
   const char *pfileNameOut = iArgv[2];
   int code_err = 1;

   
   // CREATE THE SESSION
   // ==================
   CATSession *pSampleSession = NULL;
   HRESULT hr = ::Create_Session("SampleSession",pSampleSession);
   if (FAILED(hr)) return 1;
   
   
   // DRAWING DOCUMENT CREATION
   // ===============================
   CATDocument* pNewDoc = NULL;
   CATDocumentServices::New("CATDrawing", pNewDoc); 
   

   // READ THE PART DOCUMENT AND GET ACTIVE TPS VIEW
   // ====================================================
   CATDocument *pDocPart = NULL;
   if( SUCCEEDED(CATDocumentServices::OpenDocument(pfileNamePart, pDocPart)) )
   {
      CATInit *piDocAsInit = 0;
      if( SUCCEEDED(pDocPart->QueryInterface(IID_CATInit, (void**)&piDocAsInit)) )
      {
         CATITPSDocument *piTPSDoc= NULL;
         if (SUCCEEDED(piDocAsInit->QueryInterface(IID_CATITPSDocument,(void **)&piTPSDoc)))
         {
            CATITPSList *piTPSList = NULL;
            if (SUCCEEDED(piTPSDoc->GetSets(&piTPSList)))
            {
               unsigned int nbSet;
               piTPSList->Count(&nbSet);
               if (nbSet > 0)
               {
                  CATITPSComponent *piTPSCmp = NULL;
                  if (SUCCEEDED(piTPSList->Item(0,&piTPSCmp)))
                  {
                     if (piTPSCmp)
                     {
                        CATITPSSet *piTPSSet = NULL;
                        if (SUCCEEDED(piTPSCmp->QueryInterface(IID_CATITPSSet,(void **)&piTPSSet)))
                        {
                           CATITPSView *piTPSActiveView = NULL;
                           if (SUCCEEDED(piTPSSet->GetActiveView (&piTPSActiveView)) && piTPSActiveView)
                           {
                              IUnknown *pTPSViewUk = NULL;
                              if (SUCCEEDED(piTPSActiveView->QueryInterface(IID_IUnknown,(void **)&pTPSViewUk)))
                              {
                                 // Call a Sub Program to Create a Drawing View from TPS View in a Drawing Document
                                // =========================================================================
                                 hr = CreateViewFrom3DInDrawingDoc(pNewDoc,piTPSActiveView);

                                 pTPSViewUk->Release();
                                 pTPSViewUk=NULL;
                              }
                              piTPSActiveView->Release();
                              piTPSActiveView=NULL;
                           }
                           piTPSSet->Release();
                           piTPSSet=NULL;
                        }
                        piTPSCmp->Release();
                        piTPSCmp=NULL;
                     }
                  }
               }
               piTPSList->Release();
               piTPSList=NULL;
            }
            piTPSDoc->Release();
            piTPSDoc=NULL;
         }
         piDocAsInit->Release();
         piDocAsInit=NULL;
      }
   }

   // SAVE THE RESULT
   // =================
   if (pNewDoc)
   {
      CATDocumentServices::SaveAs(*pNewDoc, (char *)pfileNameOut);
      CATDocumentServices::Remove (*pNewDoc);
   }

   //ENDS SESSION AND DROPS DOCUMENT
   //===================================== 
   if (pDocPart)
      CATDocumentServices::Remove (*pDocPart);
   
   ::Delete_Session("SampleSession");
   return hr;
}
