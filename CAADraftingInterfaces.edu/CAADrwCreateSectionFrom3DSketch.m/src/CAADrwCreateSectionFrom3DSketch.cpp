// COPYRIGHT DASSAULT SYSTEMES 2004
//============================================================================================
// Sample code for : Drafting Interfaces
// Mission         : Shows the needed APIs to create a section view defined by a cutting profile associative to 3D Sketch.
//
// Type            : Batch program
// Inputs         : The CATPart document containing a Pad with an additional Sketch (SketchForSection).
//                      PartWithPlaneAndSketchForSectionView.CATPart is delivered in CAADraftingInterfaces/CNext/resources/graphic directory.
// Outputs      : A new Drawing document in which a Generative Drawing Section View has been Created
//                          Return code is O if program worked Ok, <>0 otherwise
// Run command :
//                      mkrun -c CAADrwCreateSectionFrom3DSketch C:\PartWithPlaneAndSketchForSectionView.CATPart C:\TestResult.CATDrawing      
//                     
// Illustrates  : 
//                   o Drawing document creation.
//                   o Get a Part document and open it.       
//                   o Get Apporpriate sketch (SketchForSection).
//                   o Create a Drawing View with a standalone Section view associative to the 3D Sketch.
//                   o Save the Drawing document.
//============================================================================================

// System
#include "CATIStringList.h" 
#include "CATUnicodeString.h"
#include "IUnknown.h" 
#include "CATListPV.h" 

// ObjectModelerBase 
#include "CATSession.h" 
#include "CATSessionServices.h" 
#include "CATInit.h"
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATIContainer.h"
#include "CATIAlias.h"

// ObjectSpecsModeler
#include "CATISpecObject.h"
#include "CATIDescendants.h"
#include "CATLISTV_CATISpecObject.h"

// ProductStructure
#include "CATIProduct.h"

// MechModInterfaces
#include "CATIPrtContainer.h"
#include "CATIPrtPart.h"

// NewTopologicalObjects
#include "CATBody.h"
#include "CATCell.h"

// SketcherInterfaces
#include "CATISketch.h"
#include "CATI2DLine.h"
#include "CATI2DWFGeometry.h" 

// DraftingInterfaces 
#include "CATIDftDocumentServices.h"
#include "CATIDftDrawing.h"
#include "CATIDftSheet.h"
#include "CATIDftGenViewFactory.h"
#include "CATIDftView.h"
#include "CATIDftStandardManager.h"

// Mathematic
#include "CATMathDirection.h"
#include "CATPlane.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATMathPlane.h"

// -------------------------------------------------------------------------------------------------------------------------------------------------------
// Sub program to create a Drawing Generative View from 3D Sketch.
// -------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CreateSectionViewFromSketchInDrawingDoc(CATDocument *ipNewDoc, CATISketch *ipi3DSketch)
{
   HRESULT hr = E_FAIL;
   
   if (ipNewDoc && ipi3DSketch)
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
                                 // Import the ISO standard in the document
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
               
               // Creation of new generative  seection view from 3D Sketch in the active sheet of the Drawing Document
               CATIDftView *piDftSectionViewFrom3D = NULL;
               CATIDftSheet  *piDftSheet = NULL;
               if (SUCCEEDED(piDftDrawing->GetActiveSheet(&piDftSheet)))
               {
                  // View anchor point definition
                  double ptOrigin[2] = {150.0,150.0};
                  CATMathVector normalSketch;
                  CATI2DLine_var spFirstLine;
                  double pOrthoDirection[2];
                  
                  CATIDftGenViewFactory *piDftGenViewFact = NULL;
                  if (SUCCEEDED(piDftSheet->QueryInterface(IID_CATIDftGenViewFactory,(void **)&piDftGenViewFact))) 
                  {
                     // vecPro argument compute:
                     // VecPro must be a direction perpandicular to the first line in the sketch defining the section profile.
                     // The Vecpro orientation informs the system which part will be drawn in the section view.
                     CATLISTV (CATI2DWFGeometry_var )  GeomList;
                     if (SUCCEEDED(ipi3DSketch->GetComponents(CATI2DWFGeometry::ClassName(),GeomList)))
                     {
                        if (GeomList.Size()  > 1)
                        {
                           int indice=1;
                           while (indice < GeomList.Size())
                           {
                              spFirstLine = GeomList[indice];
                              if (NULL_var != spFirstLine)
                              {
                                 double pOrigin[2],pDirection[2];
                                 spFirstLine->GetLineData(pOrigin, pDirection);
                                 pOrthoDirection[0] = pDirection[1];
                                 pOrthoDirection[1] = -pDirection[0];  
                                 break;
                              }
                              indice++;
                           }
                        }
                     }
                     CATISpecObject_var spPlanarSupport;
                     if (SUCCEEDED(ipi3DSketch->GetPlanarSupport(spPlanarSupport )))
                     {
                        CATPlane_var spPlane= spPlanarSupport;
                        if(NULL_var != spPlane)
                        {
                           CATMathPlane mathPlaneSk;
                           spPlane->GetAxis(mathPlaneSk);
                           CATMathPoint ThePoint;
                           mathPlaneSk.EvalPoint(pOrthoDirection[0],pOrthoDirection[1],ThePoint); 
                           double XCoord = ThePoint.GetX();
                           double YCoord = ThePoint.GetY();
                           double ZCoord = ThePoint.GetZ();
                           
                           CATMathDirection vecPro;
                           vecPro.SetCoord(XCoord,YCoord,ZCoord);
                           
                           // Offset Profile
                           int viewProfile = 0;
                           
                           // Section View defined by a Sketch
                           CATCell *piPlaneElem = NULL;
                           CATBody *piBody= NULL;
                           CATMathPoint iLimitPoints[2];
                           
                           // Sketch defined in Part Document
                           CATIProduct *piProduct= NULL;
                           
                           // Creation of the section view associaitive to 3D Sketch
                           hr = piDftGenViewFact->CreateStandAloneSectionView(ptOrigin, DftSectionView, vecPro,viewProfile, ipi3DSketch,piPlaneElem,piBody,iLimitPoints,piProduct,
                              &piDftSectionViewFrom3D);
                           if (SUCCEEDED(hr) && piDftSectionViewFrom3D)
                              hr = S_OK;
                           else
                              hr = E_FAIL;
                           piDftGenViewFact->Release();piDftGenViewFact=NULL;
                        }
                     }
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
// -------------------------------------------------------------------------------------------------------------------------------------------------------

int main(int    iArgc,   // Number of arguments (2) 
         char** iArgv)   // Path to the new *.CATDrawing document
{
   // Check arguments
   if(3 != iArgc) return 1;
   const char *pfileNamePart = iArgv[1];
   const char *pfileNameOut = iArgv[2];
   int code_err = 1;

   
   // CREATE THE SESSION
   // =====================
   CATSession *pSampleSession = NULL;
   HRESULT hr = ::Create_Session("SampleSession",pSampleSession);
   if (FAILED(hr)) return 1;
   
   
   // DRAWING DOCUMENT CREATION
   // ===============================
   CATDocument* pNewDoc = NULL;
   CATDocumentServices::New("CATDrawing", pNewDoc); 
   

   // READ THE PART DOCUMENT AND GET THE APPROPRIATE SKETCH
   // =============================================================
   CATDocument *pDocPart = NULL;
   if( SUCCEEDED(CATDocumentServices::OpenDocument(pfileNamePart, pDocPart)) && pDocPart)
   {
      CATInit_var spInitOnDoc(pDocPart);
      if(NULL_var != spInitOnDoc)
      {
         // Retrieves the root container
         CATIPrtContainer * piPrtCont =  (CATIPrtContainer*) spInitOnDoc->GetRootContainer("CATIPrtContainer");	
         if (piPrtCont)
         {
            // Get the part feature of the container.
            CATIPrtPart_var spPart = piPrtCont->GetPart();
            
            // Get the appropriate sketch 
            CATIDescendants *piDescPart=NULL;
            if (SUCCEEDED(spPart->QueryInterface(IID_CATIDescendants,(void**)&piDescPart)))
            {
               CATListValCATISpecObject_var listFeatures;
               
               piDescPart->GetAllChildren ("CATISketch",listFeatures)  ;
               
               int nbChilds = listFeatures.Size();
               CATISketch* piSketch = NULL;
               CATISpecObject_var spFeat;
               for (int i = 1; i <= nbChilds; i++)
               {
                  spFeat = listFeatures[i]; 
                  if (NULL_var != spFeat)
                  {
                     if (SUCCEEDED(spFeat->QueryInterface(IID_CATISketch, (void**)&piSketch)))
                     {
                        CATIAlias *piSketchAlias = NULL;
                        if (SUCCEEDED(piSketch->QueryInterface(IID_CATIAlias, (void**)&piSketchAlias)))
                        {
                           CATUnicodeString SketchName = piSketchAlias->GetAlias();
                           const  CATUnicodeString SketchSection_UC = "SketchForSection";
                           if (SketchName == SketchSection_UC)
                              hr = CreateSectionViewFromSketchInDrawingDoc(pNewDoc, piSketch);

                           piSketchAlias->Release();piSketchAlias = NULL;
                        }
                        piSketch->Release();piSketch=NULL;
                     }
                  }
               }
               piDescPart->Release();piDescPart=NULL;
            }
            piPrtCont->Release();piPrtCont=NULL;
         }
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
