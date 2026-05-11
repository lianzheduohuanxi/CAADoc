// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CAAVisManagerCmdSelector.h"

//Visualization FrameWork
#include "CATManipulatorNotification.h"
#include "CATManipulator.h"
#include "CATIndicator.h"
#include "CATMultiSel.h"
#include "CATSO.h"
#include "CATPathElement.h"
#include "CATViewer.h"

//Local FrameWork
#include "CAAVisManagerCxtMenu.h"

//C++ Standard Library
#include <iostream.h>

CAAVisManagerCmdSelector::CAAVisManagerCmdSelector(CATHSO &iHso,CATPSO&iPso): _Hso(iHso),_Pso(iPso)
{
   cout <<" CAAVisManagerCmdSelector::CAAVisManagerCmdSelector"<< endl;
   _pCxtMenu = NULL;
   iHso.AddRef();
   iPso.AddRef();
}

CAAVisManagerCmdSelector::~CAAVisManagerCmdSelector()
{
   cout <<" CAAVisManagerCmdSelector::~CAAVisManagerCmdSelector"<< endl;
   _Hso.Release();
   _Pso.Release();
   _pCxtMenu = NULL;
}


CATNotifPropagationMode CAAVisManagerCmdSelector::AnalyseNotification(
                                                   CATCommand * iFromClient,
                                                   CATNotification * iNotification)
{
   CATNotifPropagationMode propMode = CATNotifTransmitToFather ;

   // we catch every manipulating events send by its children in order to process them.
   // As for the other events the current document send them up to the chain of responsability
   // thru the default CATCommand::AnalyseNotification method.

  
   cout <<"CAAVisManagerCmdSelector::AnalyseNotification " << endl ;

   if ( (NULL == iFromClient ) || ( NULL == iNotification ) )
   {
      return CATNotifTransmitToFather ;
   }

   cout <<" Notification = "<< iNotification->GetNotificationName() << endl;

   if ( iNotification->IsAKindOf("CATManipulatorNotification") )
   {
      propMode =  CATNotifDontTransmitToFather;

      if  ( iNotification->IsAKindOf(CATManipulator::GetCATPreactivate()) )
      {
         CATPathElement * pPath = NULL ;

         if ( NULL != pPath )
         {
            _Pso.AddElement(pPath);
            pPath->Release();
         }

      }
      else if ( iNotification->IsAKindOf(CATManipulator::GetCATEndPreactivate()) )
      {
         CATPathElement * pPath = NULL ;
         pPath = (CATPathElement *)iFromClient->SendCommandSpecificObject(
                                      CATPathElement::ClassName(),iNotification);
         if ( NULL != pPath )
         {
            _Pso.RemoveElement(pPath);
            pPath->Release();
         }
      }
      else if ( iNotification->IsAKindOf(CATManipulator::GetCATActivate()) )
      {
         CATPathElement * pPath = NULL ;
         pPath = (CATPathElement *)iFromClient->SendCommandSpecificObject(
                                      CATPathElement::ClassName(),iNotification);

         // we empty the HSO since it is a new selection that has been performed
         _Hso.Empty();

         if ( NULL != pPath ) 
         {
            // there is something under the mouse device.
            _Hso.AddElement(pPath);
            pPath->Release();
         }
         else 
         {
          // there is nothing under the mouse device ==> user clicks into the background
          // that means that everything is unselected.
            _Pso.Empty();
            _Hso.Empty();
         }

      }
      else if ( iNotification->IsAKindOf(CATManipulator::GetCATEndActivate()) )
      {
         CATPathElement * pPath = NULL ;
         pPath = (CATPathElement *)iFromClient->SendCommandSpecificObject(
                                      CATPathElement::ClassName(),iNotification);
         if ( NULL != pPath )
         {
            _Hso.RemoveElement(pPath);
            pPath->Release();
         }
      }
      else if ( iNotification->IsAKindOf(CATManipulator::GetCATMove()) )
      {
         _Pso.Empty();
         CATPathElement * pPath = NULL ;
         pPath = (CATPathElement *)iFromClient->SendCommandSpecificObject(
                                      CATPathElement::ClassName(),iNotification);
         if ( NULL != pPath )
         {
            _Pso.AddElement(pPath);
            pPath->Release();
         }

      }
      else if ( iNotification->IsAKindOf(CATManipulator::GetCATBeginManipulate()) )
      {
         
      }
      else if ( iNotification->IsAKindOf(CATManipulator::GetCATManipulate()) )
      {
         
      }
      else if ( iNotification->IsAKindOf(CATManipulator::GetCATEndManipulate()) )
      {
         
      }
      else if ( iNotification->IsAKindOf(CATManipulator::GetCATContext()) )
      {
         
         // we decode the path which under the mouse
         CATPathElement *pPath = (CATPathElement *) 
               iFromClient->SendCommandSpecificObject(CATPathElement::ClassName(),iNotification);

         if ( NULL != pPath) 
         {		
            // there is something under the mouse.
            CATBaseUnknown *lastobj_of_path = (*pPath)[pPath->GetSize()-1];

            if (NULL != lastobj_of_path )
            {
               // we create a contextual menu.
               CATViewer * pViewer = (CATViewer *) 
                      iFromClient->SendCommandSpecificObject(CATViewer::ClassName(),
                                                             iNotification);
               if ( NULL != pViewer)
               {
                  // we first empty the PSO and the HSO
                  _Pso.Empty();
                  _Hso.Empty();
                  _Hso.AddElement(pPath);
                 _pCxtMenu = new CAAVisManagerCxtMenu(this,"Context", pPath,pViewer);
                 _pCxtMenu->Build();

                 pViewer->Release() ;
                 pViewer = NULL ;

               }

            }else
            {
               // nothing under the mouse 
               propMode =  CATNotifTransmitToFather;
            }

            // we release the decoded path.
            pPath->Release();
            pPath = NULL ;

         }
               
      }
      else if ( iNotification->IsAKindOf(CATManipulator::GetCATEndContext()) )
      {
        
        if ( NULL != _pCxtMenu )
        {
            _Hso.Empty();

            _pCxtMenu->RequestDelayedDestruction();
            _pCxtMenu = NULL ;
        }
      }
   }
   else  if ( iNotification->IsAKindOf("CATMultiSel") )
   {
      propMode =  CATNotifDontTransmitToFather;

      // we ask for decoding all the pathes of the mutiselection performed by the user.
      CATSO * setofobject = (CATSO *) iFromClient->SendCommandSpecificObject(
                                         CATPathElement::ClassName(),iNotification);
      if  ( NULL != setofobject)
      {
         // in order to optimize the addition of all the selected pathes into the CATHSO
         // we make use of the AddElements (with an 's') instead of the 
         // AddElement(without 's') method.
         // 
         // The work is really performed when you call the EndAddElements method at the end. So de not
         // forget to call it when using AddElements/RemoveElements methods.
         //
          CATBaseUnknown *obj = NULL ;
          int ii;
          for (ii=0; obj = (*setofobject)[ii];ii++)
          {
             _Hso.AddElements(obj);
          }
          _Hso.EndAddElements();

         setofobject->Release();
         setofobject = NULL ;
      }
      
   }
   
   return propMode ;
}
