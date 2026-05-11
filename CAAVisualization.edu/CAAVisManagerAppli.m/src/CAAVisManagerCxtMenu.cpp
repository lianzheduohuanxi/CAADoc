// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CAAVisManagerCxtMenu.h"


//Local FrameWork
#include "CAAVisManagerCmdSelector.h"
#include "CAAIVisModelObject.h"
#include "CAAIVisModelSetOfObject.h"
#include "CAAVisModelSetOfObject.h"

//Dialog FrameWork
#include "CATDlgPushItem.h"
#include "CATDlgSubMenu.h"
#include "CATDlgContextualMenu.h"
#include "CATDlgDialog.h"
#include "CATMsgCatalog.h"    // To set Nls Title for each item of the menu

//System FrameWork
#include "CATNotification.h"

//Visualization FrameWork
#include "CATViewer.h"
#include "CATIModelEvents.h"
#include "CATCreate.h"
#include "CATDelete.h"
#include "CATRep.h"
#include "CAT3DBagRep.h"
#include "CATViewer.h"
#include "CAT4x4Matrix.h"
#include "CATVisManager.h"
#include "CAT3DViewpoint.h"

// Local Framework
#include "CAAIVisModelObject.h"

// C++ standard library
#include <iostream.h>


//-------------------------------------------------------------------------------

CAAVisManagerCxtMenu::CAAVisManagerCxtMenu(CAAVisManagerCmdSelector *iFather, 
                                           const CATString& iName, CATPathElement *iPath, 
                                           CATViewer *iViewer) : CATCommand(iFather),
                                           _pViewer(iViewer),
                                           _pOldFather(NULL)
{
   cout << "CAAVisManagerCxtMenu::CAAVisManagerCxtMenu"<< endl;

   if (NULL != iViewer)
   {
      // Retrieves the contextual menu of the viewer 
      _pCxtMenu = iViewer->GetContextualMenu();

      //  The viewer provides a context menu.
      //  Event from context menu go to the viewer. In order to
      //  receive these events, we have to set the father of the
      //  viewer to the CATCommand who subscibes to the 
      //  contextual menu's callbacks
      //  Later, we restore old father his rightfull kin

      // Old Father to restore at the end ( it's the window )
      _pOldFather = iViewer->GetFather();

      // This receives events from the contextual menu
      iViewer->SetFather(this);

   }

   if (NULL != iPath) 
   {
      // Each CATBaseUnknown of iPath is AddRef'ed 
      _Path = *iPath;
      cout << "The Length of the Path is="<< _Path.GetSize() << endl;
   }

}

//-------------------------------------------------------------------------------

CAAVisManagerCxtMenu::~CAAVisManagerCxtMenu()
{
   cout << "CAAVisManagerCxtMenu::~CAAVisManagerCxtMenu"<< endl;

   _pCxtMenu = NULL;

   if (NULL != _pViewer)
   {
      // Restore The Old Father of the wiever ( the window )
      _pViewer->SetFather(_pOldFather);

      _pViewer = NULL;
 
   }

   _pOldFather = NULL;
  
}

//-------------------------------------------------------------------------------
void CAAVisManagerCxtMenu::Build()
{
  CATUnicodeString Title ;
 
  CATDlgPushItem * pItemDelete = new CATDlgPushItem(_pCxtMenu,"ItemDelete");
  AddAnalyseNotificationCB( pItemDelete, 
    pItemDelete->GetMenuIActivateNotification(), 
    (CATCommandMethod) &CAAVisManagerCxtMenu::OnDeletingCB, NULL );

  // Retrieves the Nls Title , set in the CAAVisManagerCxtMenu.CATNls File 
  // This file is set in the CNext/Resouces/msgcatalog directory 
  // 
  Title = CATMsgCatalog::BuildMessage("CAAVisManagerCxtMenu","ItemDelete",NULL,0,"Delete");
  pItemDelete->SetTitle(Title);

  CATBaseUnknown * pObj = _Path[_Path.GetSize()-1];

  if ( NULL != pObj )
  {
     CAAIVisModelSetOfObject *piVisSet= NULL ;
     HRESULT rc = pObj->QueryInterface(IID_CAAIVisModelSetOfObject,(void **)&piVisSet);
     if ( SUCCEEDED(rc) )
     {
        //
        // The sub menu Add appears only for a Set Object
        //
        CATDlgSubMenu * pSubMenuAdd = new CATDlgSubMenu(_pCxtMenu,"SubMenuAdd");
     
        // Retrieves the Nls Title , set in the CAAVisManagerCxtMenu.CATNls File 
        // This file is set in the CNext/Resouces/msgcatalog directory 
        // 
        Title = CATMsgCatalog::BuildMessage("CAAVisManagerCxtMenu","SubMenuAdd",NULL,0,"Add");
        pSubMenuAdd->SetTitle(Title);


        CATDlgPushItem * pItemNewSet = new CATDlgPushItem(pSubMenuAdd,"ItemNewSet");
        AddAnalyseNotificationCB( pItemNewSet, 
           pItemNewSet->GetMenuIActivateNotification(), 
           (CATCommandMethod) &CAAVisManagerCxtMenu::OnAddingNewSetCB, NULL );
 
        // Retrieves the Nls Title , set in the CAAVisManagerCxtMenu.CATNls File 
        // This file is set in the CNext/Resouces/msgcatalog directory 
        // 
        Title = CATMsgCatalog::BuildMessage("CAAVisManagerCxtMenu","ItemNewSet",NULL,0,"Set");
        pItemNewSet->SetTitle(Title);

        piVisSet->Release();
        piVisSet = NULL ;
     }
  }

  CATDlgPushItem * pItemEdit = new CATDlgPushItem(_pCxtMenu,"ItemEdit");
  AddAnalyseNotificationCB( pItemEdit, 
    pItemEdit->GetMenuIActivateNotification(), 
    (CATCommandMethod) &CAAVisManagerCxtMenu::OnEditingCB, NULL );

  // Retrieves the Nls Title , set in the CAAVisManagerCxtMenu.CATNls File 
  // This file is set in the CNext/Resouces/msgcatalog directory 
  // 
  Title = CATMsgCatalog::BuildMessage("CAAVisManagerCxtMenu","ItemEdit",NULL,0,"Edit");
  pItemEdit->SetTitle(Title);

}

//-------------------------------------------------------------------------------

void CAAVisManagerCxtMenu::OnDeletingCB (CATCommand *iPublishCmd,  
                                           CATNotification *iNotification, CATCommandClientData iData)
{
   // we get the selected object
   CATBaseUnknown * pObj = _Path[_Path.GetSize()-1];
   if (NULL != pObj)
   {
      // The selected component will be destroyed.
      // -----------------------------------------

      // But before deleting it, we have to warn all its visualization representations (2D and 3D)
      // by sending a visualization event CATDelete.
      // -------------------------------------------
      CATIModelEvents *pME = NULL;
      HRESULT rc1 = pObj->QueryInterface(IID_CATIModelEvents,(void **) &pME);
      if (SUCCEEDED(rc1))
      {
         CATDelete notif(pObj);
         pME->Dispatch(notif);

         pME->Release();
         pME= NULL ;
      }
      
      // Delete the object from the model
      // --------------------------------

      // 1- Deletion of its child  
      DeleteChildren(pObj);

      // 2- Update the father if it exists
      if (  _Path.GetSize() > 1 )
      {
         // The selected object is attached to a father 
         CATBaseUnknown * pObjFather = _Path[_Path.GetSize()-2];
         if ( NULL != pObjFather )
         {

            CAAIVisModelObject *piVisModel= NULL ;
            HRESULT rc = pObjFather->QueryInterface(IID_CAAIVisModelObject,(void **)&piVisModel);
            if ( SUCCEEDED(rc) )
            {
               // The object selected is no more a child of its father.
               piVisModel->RemChild(pObj);

               piVisModel->Release();
               piVisModel = NULL ;
            }
         }
      }

   }
   
}

//-------------------------------------------------------------------------------

void CAAVisManagerCxtMenu::DeleteChildren(CATBaseUnknown * iObject)
{
   if ( NULL != iObject )
   {
      CAAIVisModelObject *piVisModel= NULL ;
      HRESULT rc = iObject->QueryInterface(IID_CAAIVisModelObject,(void **)&piVisModel);
      if ( SUCCEEDED(rc) )
      {
         list<CATBaseUnknown> * listchildren = piVisModel->GetChildren();
         if ( NULL != listchildren )
         {
            while ( 0 != listchildren->length() )
            {
               CATBaseUnknown *child = (*listchildren)[0] ;
               DeleteChildren(child);

               piVisModel->RemChild(child);
            }
         }

         piVisModel->Release();
         piVisModel= NULL ;
      }
   }
}

//-------------------------------------------------------------------------------

void CAAVisManagerCxtMenu::OnAddingNewSetCB (CATCommand *iPublishCmd,  
                                           CATNotification *iNotification, CATCommandClientData iData)
{
   // we get the selected object
   CATBaseUnknown * pObj = _Path[_Path.GetSize()-1];
   if (NULL != pObj)
   {
      // we test whether or not the selected object is a bag
      CAAIVisModelSetOfObject *piVisSet= NULL ;
      HRESULT rc = pObj->QueryInterface(IID_CAAIVisModelSetOfObject,(void **)&piVisSet);
      if ( SUCCEEDED(rc) )
      {
         CAAVisModelSetOfObject * newobj = new CAAVisModelSetOfObject;

         CAAIVisModelObject * pVMO = NULL;
         HRESULT rc = pObj->QueryInterface(IID_CAAIVisModelObject, (void **) &pVMO);
         if ( SUCCEEDED (rc) )
         {
            // we add a new object to the selected object thru the dedicated interface
            pVMO->AddChild(newobj);

            // we warn the visualization world by sending a visualization event of creation.
            CATIModelEvents *pME = NULL;
            HRESULT rc1 = pObj->QueryInterface(IID_CATIModelEvents,(void **) &pME);
            if (SUCCEEDED(rc1))
            {
               CATCreate notif(newobj,pObj);
               pME->Dispatch(notif);

               pME->Release();
               pME = NULL ;
            }

            newobj->Release();
            newobj = NULL ;
            
            pVMO->Release();
            pVMO = NULL ;
         }

         piVisSet->Release();
         piVisSet= NULL ;
      }
   }

}

//-------------------------------------------------------------------------------


void CAAVisManagerCxtMenu::OnEditingCB (CATCommand *iPublishCmd,  
                                           CATNotification *iNotification, CATCommandClientData iData)
{

   CATBaseUnknown * pObj = _Path[_Path.GetSize()-1];
   if (NULL != pObj)
   {
      // Case of a bag 
      CAAIVisModelSetOfObject *piVisSet= NULL ;
      HRESULT rc = pObj->QueryInterface(IID_CAAIVisModelSetOfObject,(void **)&piVisSet);
      if ( SUCCEEDED(rc) )
      {
         EditSet();

         piVisSet->Release();
         piVisSet = NULL ;
      }
   }
}

//-------------------------------------------------------------------------------

void CAAVisManagerCxtMenu::EditSet()
{

   CATBaseUnknown * obj = _Path[_Path.GetSize()-1];
   if (NULL != obj)
   {
      // in order to fechting the matrix of the current component, 
      // we need its 3D graphical representation. Notice that the matrix should 
      // be recorded into the modeling structure itself.
      //
      // Getting the 3D graphical representation is possible by using a service 
      // provided bythe VisManager : the GenerateRepPathFromPathElement method.
      //
      // We also need the viewpoint into which the 3D graphical representation of the component is 
      // visualized.
      //
      CATVisManager * vm = CATVisManager::GetVisManager();
      if (NULL != vm)
      {         
         if (NULL != _pViewer)
         {
            // extract the 3D viewpoint from the current viewer
            CAT3DViewpoint & vpt = _pViewer->GetMain3DViewpoint();

            // we create the output structure that the VisManager will fill in.
            CATRepPath rep_path;
            vm->GenerateRepPathFromPathElement(_Path,&vpt,rep_path);

            // we get the positionning matrix of the last graphical repreesntation
            CATRep * bag = rep_path[rep_path.Size() - 1];

            // we test whether or not it is a graphical representation bag
            if (bag && bag->IsAKindOf("CAT3DBagRep") )
            {
               // we extract the 3D positionning matrix
               const CAT4x4Matrix *mat = ((CAT3DBagRep *) bag)->GetMatrix();

               if ( NULL != mat )
               {
                  cout << "The Matrix of the set is=" << endl;
                  CATMathVectorf U,V,W ;
                  CATMathPointf  T ;
                  mat->GetComponents(U,V,W,T);
                  cout << "U= " << U.x << " " << U.y << " " << U.z << endl ;
                  cout << "V= " << V.x << " " << V.y << " " << V.z << endl ;
                  cout << "W= " << W.x << " " << W.y << " " << W.z << endl ;
                  cout << "T= " << T.x << " " << T.y << " " << T.z << endl ;
               }else
               {
                  cout << "Set without matrix "<< endl;
               }
            }
         }
      }
   }
}
