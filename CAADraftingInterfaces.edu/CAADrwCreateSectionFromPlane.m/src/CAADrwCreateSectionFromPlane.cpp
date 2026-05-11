// COPYRIGHT DASSAULT SYSTEMES 2004
//============================================================================================
// Sample code for : Drafting Interfaces
// Mission         : Shows the needed APIs to create a section view defined by a cutting profile associative to a Plan.
//
// Type            : Batch program
// Inputs         : A CATPart document containing a Pad with an additional Plane (PlaneForSection).
//                      PartWithPlaneAndSketchForSectionView.CATPart is delivered in CAADraftingInterfaces/CNext/resources/graphic directory.
// Outputs         : A new Drawing document in which a Generative Drawing Section View has been Created
//                          Return code is O if program worked Ok, <>0 otherwise
// Run command     : mkrun -c CAADrwCreateSectionFrom3DPlane C:\PartWithPlaneAndSketchForSectionView.CATPart C:\TestResult.CATDrawing      
//                   
// Illustrates     : 
//                   o Drawing document creation.
//                   o Get a Part document and open it.       
//                   o Retrieve the plane "PlaneForSection".
//                   o Create a Drawing Document with a standalone Section view associative to the Plane.
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
#include "CATIBRepAccess.h"
#include "CATIPrtContainer.h"
#include "CATIPrtPart.h"
#include "CATBody.h"

//GeometricObject
#include "CATPlane.h"
#include "CATFace.h"
#include "CATCell.h"
#include "CATIGeometricalElement.h"

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
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATMathPlane.h"

// -------------------------------------------------------------------------------------------------------------------------------------------------------
// Sub program to create an associative section view from Plane.
// -------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CreateSectionViewFromPlanInDrawingDoc(CATDocument *ipNewDoc, CATPlane*ipiPlane)
{
   HRESULT hr = E_FAIL;
   
   if (ipNewDoc && ipiPlane)
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
                  
                  CATIDftGenViewFactory *piDftGenViewFact = NULL;
                  if (SUCCEEDED(piDftSheet->QueryInterface(IID_CATIDftGenViewFactory,(void **)&piDftGenViewFact))) 
                  {
                     // vecPro argument compute:
                     // VecPro must be a direction perpandicular to the direction of the cutting profile defined by two extremities points and included in the plane.
                     CATIGeometricalElement *piGeomElem = NULL;
                     if (SUCCEEDED(ipiPlane->QueryInterface(CATIGeometricalElement::ClassId(), (void**) &piGeomElem)))
                     {
                        CATCell_var spCell;
                        CATBody_var spBody;
                        spBody = piGeomElem->GetBodyResult();
                        spCell = piGeomElem->GetGeometryResult();
                        if (NULL_var == spCell && NULL_var != spBody)
                        {
                           CATLISTP(CATCell) AllFaces;
                           spBody->GetAllCells(AllFaces, 2);
                           int FaceCount = AllFaces.Size();
                           for (int i = 1 ; i <= FaceCount; i++)
                           {
                              if (AllFaces[i])
                              {
                                 spCell = CATCell_var(AllFaces[i]);
                                 break;
                              }
                           }
                        }
                        CATMathPlane mathPlane;
                        ipiPlane->GetAxis(mathPlane);
                        CATMathPoint iLimitPoints[2];
                        
                        double Pt1Coord[2] = {-100.0,0.0};
                        double Pt2Coord[2] = {100.0,0.0};
                        mathPlane.EvalPoint(Pt1Coord[0],Pt1Coord[1],iLimitPoints[0]); 
                        mathPlane.EvalPoint(Pt2Coord[0],Pt2Coord[1],iLimitPoints[1]); 
                        CATMathVector vecProfile = iLimitPoints[1] - iLimitPoints[0];
                        CATMathVector vecNormalToPlane;
                        mathPlane.GetNormal (vecNormalToPlane);
                        CATMathVector ProVec = vecNormalToPlane^vecProfile;
                        CATMathDirection vecPro;
                        vecPro.SetCoord(ProVec.GetX(),ProVec.GetY(),ProVec.GetZ());
                        
                        // Offset
                        int viewProfile = 0;
                        
                        // Section View defined by a plane
                        CATISketch *ipi3DSketch = NULL;
                        
                        // Plane defined in Part Document
                        CATIProduct *piProduct= NULL;
                        hr = piDftGenViewFact->CreateStandAloneSectionView(ptOrigin, DftSectionView, vecPro,viewProfile, ipi3DSketch,spCell,spBody,iLimitPoints, piProduct,
                           &piDftSectionViewFrom3D);
                        piGeomElem->Release();piGeomElem=NULL;
                     }
                     piDftGenViewFact->Release();piDftGenViewFact=NULL;
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
   // ==================
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
            
            // Get the appropriate plane
            CATIDescendants *piDescPart=NULL;
            if (SUCCEEDED(spPart->QueryInterface(IID_CATIDescendants,(void**)&piDescPart)))
            {
               CATListValCATISpecObject_var listFeatures;
               
               piDescPart->GetAllChildren ("CATPlane",listFeatures)  ;
               
               int nbChilds = listFeatures.Size();
               CATISpecObject_var spFeat;
               for (int i = 1; i <= nbChilds; i++)
               {
                  spFeat = listFeatures[i]; 
                  if (NULL_var != spFeat)
                  {
                     CATPlane* piPlane = NULL;
                     if (SUCCEEDED(spFeat->QueryInterface(IID_CATPlane, (void**)&piPlane)))
                     {
                        CATIAlias *piPlaneAlias = NULL;
                        if (SUCCEEDED(piPlane->QueryInterface(IID_CATIAlias, (void**)&piPlaneAlias)))
                        {
                           CATUnicodeString PlaneName = piPlaneAlias->GetAlias();
                           const  CATUnicodeString PlaneSection_UC = "PlaneForSection";
                           if (PlaneName == PlaneSection_UC)
                              hr = CreateSectionViewFromPlanInDrawingDoc(pNewDoc, piPlane);

                           piPlaneAlias->Release();piPlaneAlias = NULL;
                        }
                        piPlane->Release();piPlane=NULL;
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
