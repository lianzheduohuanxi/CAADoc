// COPYRIGHT DASSAULT SYSTEMES 2003
//============================================================================================
// Sample code for : Drafting Interfaces
// Mission         : Shows the needed APIs to access to callout defined in generative view.
//
// Type            : Batch program
// Inputs          : The drawing document containing generative views file path.
// Outputs         : Return code is O if program worked Ok, >0 otherwise
// Run command     : mkrun -c CAADrwCallout DrawingForCalloutUseCase.CATDrawing
//                               The drawing document file path is CAADraftingInterfaces.edu/FunctionTests/inputData 
//                   
// Illustrates     : 
//                   o Drawing document reading.
//                   o Get all callouts in all views.
//                   o Get callout informations.
//                   o Get generative view from a Callout.
//                   o Get geometric informations of profile associated to a generative view.
//                   o Get/Set callout properties parameters.
//============================================================================================

// System
#include <iostream.h>
#include "CATUnicodeString.h"
#include "CATIUnknownListImpl.h"
#include "CATIUnknownList.h"
#include "IUnknown.h" 
#include "CATListOfDouble.h" 

// ObjectModelerBase (To open document)
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATSessionServices.h" 
#include "CATLISTV_CATISpecObject.h"

// DraftingInterfaces 
#include "CATIDftDrawing.h"
#include "CATIDftDocumentServices.h"
#include "CATIDftView.h"
#include "CATIDrwCalloutAccess.h"
#include "CATIDrwSubText.h"
#include "CATIDrwSimpleText.h"
#include "CATIDftText.h"
#include "CATIDrwAnnotationComponent.h"
#include "CATDftArrowEnum.h"
#include "CATIGenerSpec.h" 

// SketcherInterfaces 
#include "IDMCurve2D.h"

// Mathematic
#include "CATMathPoint2D.h"
#include "CATMathDirection.h" 
#include "CATMathCircle.h" 

// Internal method managing callout representation
HRESULT ApplyCalloutStyle(CATIDrwCalloutAccess* piCallout);


// ----------------------------------------------------------------------------

int main(int    iArgc,   // Number of arguments (3) 
         char** iArgv)   // Path to the existing file *.CATDrawing document
{
   // Check arguments
   if(3 != iArgc) return 1;
   const char *pfileNameDrawing = iArgv[1];
   const char *pfileNameOut = iArgv[2];

   // return code error
   int rc =0;

   // CREATE THE SESSION
   // =====================

   CATSession *pSampleSession = NULL;
   HRESULT hr = ::Create_Session("SampleSession",pSampleSession);
   if (FAILED(hr)) return 1;


   // READ THE DRAWING DOCUMENT
   // ===============================

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

   if (piDrawing)
   {
     // LOOP ON ALL VIEWS IN DRAWING
     // ================================
     CATIUnknownList * piListOfView = NULL;
     
     if (SUCCEEDED(piDrawing->GetViews(&piListOfView)))
     {
       unsigned int piViewListSize = 0;
       piListOfView->Count(&piViewListSize);
       
       IUnknown * itemView = NULL;
       CATIDftView *piCurrentView = NULL;
       
       // Loop on all callouts of the processed view 
       // -----------------------------------------------
       for(unsigned int numview=0 ; numview<piViewListSize ; numview++)
       {
         if( SUCCEEDED( piListOfView->Item(numview, &itemView) ) )
         {
           if (itemView)
           {
             if (SUCCEEDED(itemView->QueryInterface(IID_CATIDftView,(void **)&piCurrentView)))
             {
               // Get the view name
               // ---------------------
               IUnknown *piGenView = NULL;
               wchar_t *pViewName=NULL;
               piCurrentView->GetViewName(&pViewName);
               CATUnicodeString ViewName;
               ViewName.BuildFromWChar(pViewName);
               cerr << " View name processed = " << ViewName.ConvertToChar() << endl << endl;
               if (pViewName) delete[]  pViewName;  pViewName = NULL;
               
               CATIUnknownList * piListOfCallout = NULL;
               
               // Get list of callouts of the view processed
               // ----------------------------------------------
               if( SUCCEEDED( piCurrentView->GetComponents(IID_CATIDrwCalloutAccess, &piListOfCallout) ) )
               {
                 if (piListOfCallout)
                 {
                   unsigned int piListSize = 0;
                   piListOfCallout->Count(&piListSize);
                   
                   CATIDrwCalloutAccess* piCallout = NULL;
                   IUnknown * item = NULL;
                   CATUnicodeString  PartName;
                   
                   // Loop on all callouts of the view processed
                   // ----------------------------------------------
                   for(unsigned int i=0 ; i<piListSize ; i++)
                   {
                     if( SUCCEEDED( piListOfCallout->Item(i, &item) ) )
                     {
                       if(SUCCEEDED( item->QueryInterface(IID_CATIDrwCalloutAccess, (void**) & piCallout) ) )
                       {
                         // Get callout type
                         // -------------------
                         CATIDrwCalloutAccess::CATDrwCalloutType calloutType;
                         piCallout->GetCalloutType(calloutType);
                         cerr << endl << "Callout type = " << calloutType << endl;

                         // Get geometric informations about Breakview 
                         // ---------------------------------------------------
                         if (calloutType ==CATIDrwCalloutAccess::BreakCallout)
                         {
                           CATIGenerSpec *piGenerSpecCurrentView=NULL;
                           if (SUCCEEDED(piCurrentView->GetGenerSpec(&piGenerSpecCurrentView)))
                           {
                             CATMathVector2D Vecdir;
                             CATLISTV(CATISpecObject_var) Liste1_skElem, Liste2_skElem;
                             CATListOfDouble translation1, translation2;
                             if (SUCCEEDED(piGenerSpecCurrentView->GetBreakViewInfo(Vecdir,Liste1_skElem, Liste2_skElem,translation1, translation2)))
                             {
                               cerr <<  "Get geometric informations about breakview " << endl;
                               double directionBreakout[2];
                               Vecdir.GetCoord(directionBreakout[0],directionBreakout[1]);
                               cerr <<  "direction of the break X=  " << directionBreakout[0] << " , Y =  " << directionBreakout[1] << endl;

                               int nbelem = Liste1_skElem.Size();
                               int numelem = 1;
                               for (;  numelem <= nbelem ; numelem++)
                               {
                                 CATISpecObject_var spElem = Liste1_skElem[numelem];
                                 if (NULL_var != spElem )
                                 {
                                   IDMCurve2D *piIDMCurve2D = NULL;
                                   if (SUCCEEDED(spElem->QueryInterface(IID_IDMCurve2D,(void **)&piIDMCurve2D)))
                                   {
                                     double pStartPoint[2],pEndPoint[2];
                                     if (SUCCEEDED(piIDMCurve2D->GetEndPoints(pStartPoint,pEndPoint)))
                                     {
                                       cerr << "number of the break element of the first list = "<< numelem << endl;
                                       cerr << " pStartPoint: X = " << pStartPoint[0]  << " , Y=  " << pStartPoint[1]   << endl;
                                       cerr << " pEndPoint: X = " << pEndPoint[0]  << " , Y= " << pEndPoint[1]   << endl;
                                     }
                                     piIDMCurve2D->Release();piIDMCurve2D=NULL;
                                   }
                                 }
                               }
                               nbelem = Liste2_skElem.Size();
                               for (numelem = 1 ;  numelem <= nbelem ; numelem++)
                               {
                                 CATISpecObject_var spElem = Liste2_skElem[numelem];
                                 if (NULL_var != spElem )
                                 {
                                   IDMCurve2D *piIDMCurve2D = NULL;
                                   if (SUCCEEDED(spElem->QueryInterface(IID_IDMCurve2D,(void **)&piIDMCurve2D)))
                                   {
                                     double pStartPoint[2],pEndPoint[2];
                                     if (SUCCEEDED(piIDMCurve2D->GetEndPoints(pStartPoint,pEndPoint)))
                                     {
                                       cerr << "number of break element of the second list = "<< numelem << endl;
                                       cerr << " pStartPoint: X = " << pStartPoint[0]  << " , Y = " << pStartPoint[1]   << endl;
                                       cerr << " pEndPoint: X= " << pEndPoint[0]  << " , Y= " << pEndPoint[1]   << endl;
                                     }
                                     piIDMCurve2D->Release();piIDMCurve2D=NULL;
                                   }
                                 }
                               }
                               nbelem = translation1.Size();
                               for (numelem = 1 ;  numelem <= nbelem ; numelem++)
                                  cerr << " translation associated with the element number  " <<numelem << " of the first list = " << translation1[numelem] << endl;

                               nbelem = translation2.Size();
                               for (numelem = 1 ;  numelem <= nbelem ; numelem++)
                                  cerr << " translation associated with the element number  " <<numelem << " of the second list = " << translation2[numelem] << endl;

                             }
                             piGenerSpecCurrentView->Release();
                             piGenerSpecCurrentView=NULL;
                           }
                         }
                         
                         // Get the view associated to the callout
                         // -------------------------------------------
                         CATIDftView *piDefView=NULL;

                         if (calloutType !=CATIDrwCalloutAccess::BreakCallout)
                         {
                           if (SUCCEEDED(piCallout->GetAssociatedView(&piDefView)))
                           {
                             piDefView->GetViewName(&pViewName);
                             ViewName.BuildFromWChar(pViewName);
                             cerr << " View name associated to the processed callout: " << ViewName.ConvertToChar() << endl;
                             if (pViewName) delete[]  pViewName;  pViewName = NULL;
                             
                             CATIGenerSpec *piGenerSpec=NULL;
                             if (SUCCEEDED(piDefView->GetGenerSpec(&piGenerSpec)))
                             {
                               if (calloutType == CATIDrwCalloutAccess::SectionCallout)
                               {
                                 CATListPtrCATMathPoint2D ListOfPoints;
                                 int depli=0;
                                 CATMathDirection vecpro;
                                 
                                 // Get geometric informations about section profile
                                 // ---------------------------------------------------------
                                 if (SUCCEEDED(piGenerSpec->GetSectionProfile(ListOfPoints,depli,vecpro)))
                                 {
                                   int NbPt = ListOfPoints.Size();
                                   for (int numpt=1 ; numpt<=NbPt ; numpt++)
                                   {
                                     CATMathPoint2D *tmpt = ListOfPoints[numpt];
                                     cerr << " Number point = " << numpt << ",   X=  "<< tmpt->GetX() << "Y = " << tmpt->GetY()  <<  endl;
                                     
                                     // Memory clean
                                     if (tmpt) delete tmpt , tmpt=NULL;
                                   }
                                 }                
                               }
                               else if (calloutType ==CATIDrwCalloutAccess::DetailCallout)
                               {
                                 CATBoolean isCircleProfile = FALSE;
                                 CATListPtrCATMathPoint2D ListOfPoints;
                                 double radius=0.;
                                 
                                 // Get geometric informations about detail profile
                                 // -------------------------------------------------------
                                 if (SUCCEEDED(piGenerSpec->GetDetailProfile(isCircleProfile,ListOfPoints,radius)))
                                 {
                                   int NbPt = ListOfPoints.Size();
                                   cerr << " number of points in the list  = " << NbPt << endl;
                                   if (isCircleProfile)
                                   {
                                     cerr << " Detail profile is defined by a circle "<< endl;
                                     cerr << " radius of Detail View = " << radius << endl;
                                     CATMathPoint2D *tmpt = ListOfPoints[1];
                                     if (tmpt)
                                     {
                                       cerr << " center of circle :   X= "<< tmpt->GetX() << "Y = " << tmpt->GetY()  <<  endl;
                                       // Memory clean
                                       if (tmpt) delete tmpt , tmpt=NULL;
                                     }
                                   }  
                                   else
                                   {
                                     cerr << " Detail profile is a profile "<< endl;
                                     for (int numpt=1 ; numpt<=NbPt ; numpt++)
                                     {
                                       // Get coordinates of the profile
                                       CATMathPoint2D *tmpt = ListOfPoints[numpt];
                                       if (tmpt)
                                       {
                                         cerr << " Number point = " << numpt << ",   X=  "<< tmpt->GetX() << "Y = " << tmpt->GetY()  <<  endl;
                                         delete tmpt , tmpt=NULL;
                                       }
                                     }
                                   }
                                 }
                               }
                               else if (calloutType ==CATIDrwCalloutAccess::ProjectionCallout)
                               {
                                 int depli=0;
                                 CATMathDirection vecpro;
                                 CATMathPoint pts[2];
                                 
                                 // Get geometric informations about projection profile of auxiliary view
                                 // --------------------------------------------------------------------------------
                                 if (SUCCEEDED(piGenerSpec->GetProjectionProfile(pts, vecpro)))
                                 {
                                   cerr << "  " <<  endl;
                                   cerr << "  point  1 = " << "  X=  "<< pts[0].GetX() << ", Y = " << pts[0].GetY()  <<  endl;
                                   cerr << "  point  2 = " << "  X= "<< pts[1].GetX() << ", Y = " << pts[1].GetY()  <<  endl;
                                 }
                               }
                               piGenerSpec->Release();piGenerSpec=NULL;
                             }
                             // piDefView->Release();piDefView=NULL;
                           }
                         
                           // Get informations about callout
                           if (FAILED(ApplyCalloutStyle(piCallout)))
                           {
                             rc = 4;
                           }
                         }
                         piCallout->Release();piCallout=NULL;
                       }
                       item->Release(); item = NULL;
                     }
                   }
                   piListOfCallout->Release(); piListOfCallout = NULL;	
                 }
               }
               piCurrentView->Release() , piCurrentView=NULL;
             }
             itemView->Release();itemView=NULL;
           }
         }
      }
      piListOfView->Release();piListOfView=NULL;
    }
   // Memory clean
   piDrawing->Release();
   piDrawing=NULL;

   }
   // SAVE THE RESULT
   // ===============
   CATDocumentServices::SaveAs(*pDocDrawing, (char *)pfileNameOut);
   CATDocumentServices::Remove (*pDocDrawing);
   //Ends session and drops document	
   ::Delete_Session("SampleSession");
   
   return rc;
}


HRESULT ApplyCalloutStyle(CATIDrwCalloutAccess* piCallout)
{
  HRESULT rc = E_FAIL;
  if (piCallout)
  {
    int thickness;
    rc = piCallout->GetProfileThickness(thickness);
    if (SUCCEEDED(rc))
      cerr << " Profile thickness = " << thickness << endl;

    thickness = 2;
    rc = piCallout->SetProfileThickness(thickness);
    if (SUCCEEDED(rc))
      cerr << " Profile thickness modification successfully " << endl;
    
    int linetype;
    rc = piCallout->GetProfileLineType(linetype);
    if (SUCCEEDED(rc))
      cerr << " Profile linetype = " << linetype << endl;

    linetype = 3;
    rc = piCallout->SetProfileLineType(linetype);
    if (SUCCEEDED(rc))
      cerr << " Profile linetype modification successfully " << endl;

    int NbTexts;
    rc = piCallout->GetNumberOfTexts(NbTexts);
    if (SUCCEEDED(rc))
    {
      cerr << " Number of texts = "<< NbTexts << endl;
      
      for (int iNumText = 1; iNumText <= NbTexts ; iNumText++)
      {
        CATIDrwAnnotationComponent *piAnnot=NULL;
        rc = piCallout->GetCalloutText(iNumText,&piAnnot);
        if (SUCCEEDED(rc))
        {
          CATIDrwSimpleText *piText=NULL;
          CATIDftText *piDftText = NULL;
          // Callout texts may be based on simple text instance until CXR13 CATIA level.
          if (SUCCEEDED(piAnnot->QueryInterface(IID_CATIDrwSimpleText,(void **)&piText)))
          {
            CATIDrwSubText_var spSubText;
            spSubText = piText->GetSubText(1);
            CATUnicodeString textName = spSubText->GetText();
            cerr << " texte name = " << textName.ConvertToChar() << endl;
            
            piText->Release(); piText=NULL;
          }
          else if(SUCCEEDED(piAnnot->QueryInterface(IID_CATIDftText,(void **)&piDftText)))
          {
            wchar_t *ptextName=NULL;
            if (SUCCEEDED(piDftText->GetString(&ptextName)))
            {
              CATUnicodeString strTextName;
              strTextName.BuildFromWChar(ptextName);
              cerr << " texte name = " <<strTextName.ConvertToChar() << endl;
              if (ptextName) delete[] ptextName; ptextName = NULL;
            }
            piDftText->Release();piDftText=NULL;
          }
          piAnnot->Release();piAnnot=NULL;
        }
      }
    }
    int NbArrows;
    rc =piCallout->GetNumberOfArrow(NbArrows);
    if (SUCCEEDED(rc))
    {
      cerr << " Number of arrows  = "<< NbArrows<< endl;
      
      for (int iNumArrow = 1; iNumArrow <= NbArrows ; iNumArrow++)
      {
        double  ArrowLength,ArrowLengthSymb,ArrowAngleSymb,ArrowOrientation;
        double *ptPos = new double[2];
        CATSymbolType ArrowTypeSymb;
        rc = piCallout->GetInfoOfArrow(iNumArrow,ptPos,ArrowOrientation,ArrowLength,ArrowTypeSymb,ArrowLengthSymb,ArrowAngleSymb);
        if (SUCCEEDED(rc))
        {
          cerr << " info Arrows: Length = " << ArrowLength << " , Symbol type = "  << ArrowTypeSymb <<" , Length of symbol =  "  << ArrowLengthSymb << " , Angle of symbol =  "<< ArrowAngleSymb << endl;
          cerr << " ptPos = " << ptPos[0] << " ,  " <<  ptPos[1] << endl;
          cerr << " Orientation = " << ArrowOrientation << endl;
        }
        if (ptPos) delete []  ptPos, ptPos = NULL;
        ArrowLength=35.0;
        ArrowTypeSymb=FILLED_ARROW;
        ArrowLengthSymb=6.0;
        ArrowAngleSymb=45.0;
        
        rc = piCallout->SetInfoOfArrow(iNumArrow,ArrowLength,ArrowTypeSymb,ArrowLengthSymb,ArrowAngleSymb);
        if (SUCCEEDED(rc))
          cerr << " info Arrows: Length = " << ArrowLength << " , Symbol type = "  << ArrowTypeSymb <<" , Length of symbol =  "  << ArrowLengthSymb << " , Angle of symbol =  "<< ArrowAngleSymb << endl;
        
      }

      if (NbArrows != 0)
      {
        CATDftArrowExtremity calloutAttachment;
        rc = piCallout->GetArrowsAttachment(calloutAttachment);
        if (SUCCEEDED(rc))
          cerr << "  calloutAttachment  = "<< calloutAttachment<< endl;
        
        calloutAttachment= CATDftArrowTail;
        rc = piCallout->SetArrowsAttachment(calloutAttachment);
        if (SUCCEEDED(rc))
          cerr << "  calloutAttachment  = "<< calloutAttachment<< endl;
      }
    }
  }
  return rc;
}
