// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CAAVisManagerDocument.h"

//Visualization FrameWork
#include "CATCreate.h"
#include "CATIModelEvents.h"

// Local FrameWork
#include "CAAVisModelCGRObject.h"
#include "CAAIVisModelObject.h"
#include "CAAIVisModelSetOfObject.h"
#include "CAAVisManagerCmdSelector.h"
#include "CAAIVisModelCGRObject.h"
#include "CAAVisManagerEditor.h"
#include "CAAVisManagerWindow.h"

// System Framework
#include "CATErrorDef.h"  // for SUCCEEDED/FAILED macros
#include "CATUnicodeString.h"

// C++ Standard Library
#include <iostream.h>

int CAAVisManagerDocument::_ViewIndice = 0;

//-------------------------------------------------------------------------------

CAAVisManagerDocument::CAAVisManagerDocument(const CATString & iTitle):
                                 _pRootContainer(NULL),
                                 _Title(iTitle),
                                 _pEditor(NULL)

{
   cout << "CAAVisManagerDocument::CAAVisManagerDocument()"<< endl;

   _pEditor = new CAAVisManagerEditor(this);
}


//----------------------------------------------------------------------------

CAAVisManagerDocument::~CAAVisManagerDocument()
{
   cout << "CAAVisManagerDocument::~CAAVisManagerDocument()"<< endl;

   if ( NULL != _pRootContainer )
   {
      // Clean the tree
      CleanModel(_pRootContainer);

      _pRootContainer->Release();
      _pRootContainer = NULL ;
   }

   if ( NULL != _pEditor )
   {
      _pEditor->Release();
      _pEditor = NULL ;
   }
}

//-----------------------------------------------------------------------------

void CAAVisManagerDocument::CleanModel(CATBaseUnknown * ioChild)
{
   if ( NULL != ioChild) 
   {
      CAAIVisModelSetOfObject *piVisSet= NULL ;
      HRESULT rc = ioChild->QueryInterface(IID_CAAIVisModelSetOfObject,(void **)&piVisSet);
      if ( SUCCEEDED(rc) )
      {

         CAAIVisModelObject *piVisModel= NULL ;
         HRESULT rc = ioChild->QueryInterface(IID_CAAIVisModelObject,(void **)&piVisModel);
         if ( SUCCEEDED(rc) )
         {
            list<CATBaseUnknown> * listchildren = piVisModel->GetChildren();
            if ( NULL != listchildren )
            {
               while ( 0 != listchildren->length() )
               {
                  CATBaseUnknown *child = (*listchildren)[0] ;
                  CleanModel(child);

                  piVisModel->RemChild(child);
               }
            }

            piVisModel->Release();
            piVisModel= NULL ;
         }
         piVisSet->Release();
         piVisSet= NULL ;
      }
   }
}

//-----------------------------------------------------------------------------

CATBaseUnknown *CAAVisManagerDocument::GetRootContainer() const
{
  return _pRootContainer;
}

//-----------------------------------------------------------------------------

HRESULT CAAVisManagerDocument::InsertCGR(const char *iName)
{
   HRESULT rc = S_OK;

   // we create a CGR object.
   CAAVisModelCGRObject * newobj = new  CAAVisModelCGRObject();
   
   // Read the CGR file given in argument
   CAAIVisModelCGRObject *piVisOnCGR = NULL ;
   HRESULT rc0 = newobj->QueryInterface(IID_CAAIVisModelCGRObject,(void **)&piVisOnCGR);
   if ( SUCCEEDED(rc0) )
   {
      piVisOnCGR->ReadCGRFile(iName);

      piVisOnCGR->Release();
      piVisOnCGR = NULL ;
   }

   // we add it to the root container.
   CAAIVisModelObject *pVMO = NULL;
   if (_pRootContainer)
   {
      rc = _pRootContainer->QueryInterface(IID_CAAIVisModelObject,(void **)&pVMO);
      if ( SUCCEEDED(rc) )
      {
         // we add the new object as child of the Root Container. 
         // This operation increases the number of references
         // of the new object.
         //
         rc = pVMO->AddChild(newobj);

         pVMO->Release();
         pVMO = NULL ;
      }
   }

   // we send a CATCreate visu event in order to warn to update the visualization.
   CATIModelEvents *piModelEvents=NULL;
   if (_pRootContainer)
   {
      HRESULT rc1 = _pRootContainer->QueryInterface(IID_CATIModelEvents,(void **)&piModelEvents);
      if ( SUCCEEDED(rc1) )
      {
         CATCreate notif (newobj,_pRootContainer);
         piModelEvents->Dispatch(notif);

         piModelEvents->Release();
         piModelEvents = NULL ;
      }
   }
   // we do not need this object anymore
   newobj->Release();
   newobj = NULL ;

   return rc;
}

//-----------------------------------------------------------------------------
CAAVisManagerWindow * CAAVisManagerDocument::CreateDefaultWindow()
{
   CAAVisManagerWindow * pWindowToReturn = NULL ;

   // It's important that the Id of the Window shoud be different 
   // at each new 
   char WindowId[20];
 
   sprintf(WindowId, "View%d", _ViewIndice);
   _ViewIndice++;

   pWindowToReturn = new CAAVisManagerWindow(_pEditor,WindowId);

   pWindowToReturn->Build() ;

   // It'a not an NLS Title, but the class of the Document
   CATUnicodeString Title = _Title.ConvertToChar() ;
   pWindowToReturn->SetTitle(Title) ;

   pWindowToReturn->SetVisibility(CATDlgShow) ;

   return pWindowToReturn ; 

}
