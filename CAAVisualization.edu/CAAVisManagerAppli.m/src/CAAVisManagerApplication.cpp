// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CAAVisManagerApplication.h"

//Dialog FrameWork
#include "CATDlgBarMenu.h"
#include "CATDlgSubMenu.h"
#include "CATDlgPushItem.h"
#include "CATDlgFile.h"

// Visualization FrameWork
#include "CATManipulatorNotification.h"

// Local FrameWork
#include "CAAVisManagerEditor.h"
#include "CAAVisManagerDocument.h"
#include "CAAVisManagerDefaultDocument.h"
#include "CAAVisManagerCGRDocument.h"
#include "CAAVisManagerApplicationFrame.h"
#include "CAAVisManagerWindowDeleteNotif.h"
#include "CAAVisManagerWindowActivateNotif.h"

#include <iostream.h>

//-------------------------------------------------------------------------------

static CATDlgDocument * _pApplicationFrame = NULL ;

//-------------------------------------------------------------------------------

CAAVisManagerApplication::CAAVisManagerApplication(const CATString &iIdentifier): 
                     CATInteractiveApplication(NULL, iIdentifier),
                                  _pFileSelectorBox(NULL),
                                  _ActiveDoc(NULL),
                                  _TypeOfInput(0)
{
}

//-------------------------------------------------------------------------------

void CAAVisManagerApplication::BeginApplication()
{
   // Here is created the application frame, with
   // menu bars, and so on.
   CreateLayout();

   // Default document is created
   _ActiveDoc = new CAAVisManagerDefaultDocument();
   
   // The Application keeps the list of all documents created 
   _DocumentList += _ActiveDoc;

   // Creation of the first vue  
   CAAVisManagerWindow * pWindow = _ActiveDoc->CreateDefaultWindow();

   // The Application keeps the list of all windows created 
   _WindowList += pWindow;
}

//-------------------------------------------------------------------------------

int CAAVisManagerApplication::EndApplication()
{ 
 return (0);
}

//-------------------------------------------------------------------------------

CAAVisManagerApplication::~CAAVisManagerApplication()
{
   cout << " CAAVisManagerApplication::~CAAVisManagerApplication" << endl;
   _ActiveDoc = NULL;
   _pApplicationFrame = NULL;
   _pFileSelectorBox = NULL;

   // dialog objects ' cycle life depends on their parent cycle life: the death of the parent
   // will automatically yields to the deatf of its children. Therefore there is no need to destroy
   // the dialog object of the application since application is a dialog object itself.
}

//-------------------------------------------------------------------------------

void CAAVisManagerApplication::CreateLayout()
{
    // we create the application frame.
   _pApplicationFrame = new CAAVisManagerApplicationFrame(this,
                                     "VisApplicationId", 
                                      CATDlgWndFrameMDI);


   // Mandatory for Unix System to set dimension of the Document 
   _pApplicationFrame->SetRectDimensions(0,0,800,1000) ;

   // The CATDlgDocument is visible
   _pApplicationFrame->SetVisibility(CATDlgShow) ;

   // Adds a menu bar 
   CATDlgBarMenu  * pMenuBar  = new CATDlgBarMenu(_pApplicationFrame, "MenuBar");
   
      CATDlgSubMenu  * pFileMenu = new CATDlgSubMenu(pMenuBar, "File");
         CATDlgPushItem * pOpen = new CATDlgPushItem(pFileMenu,"Open");
         CATDlgPushItem * pInsert = new CATDlgPushItem(pFileMenu,"Insert");
         CATDlgPushItem * pExit = new CATDlgPushItem(pFileMenu,"Exit");
      CATDlgSubMenu  * pPptyMenu = new CATDlgSubMenu(pMenuBar, "Views");
      CATDlgSubMenu  * pCmdMenu  = new CATDlgSubMenu(pMenuBar, "Commands");

   // Adds callback to the items of the menu bar
   
   AddAnalyseNotificationCB(pOpen,pOpen->GetMenuIActivateNotification(),
      (CATCommandMethod) &CAAVisManagerApplication::OpenCB,
      NULL);
     
   AddAnalyseNotificationCB(pInsert,pInsert->GetMenuIActivateNotification(),
      (CATCommandMethod) &CAAVisManagerApplication::InsertCB,
      NULL);
   
   AddAnalyseNotificationCB(pExit,pExit->GetMenuIActivateNotification(),
      (CATCommandMethod) &CAAVisManagerApplication::ExitCB,
      NULL);

   // For the close button
   AddAnalyseNotificationCB(_pApplicationFrame,_pApplicationFrame->GetWindCloseNotification(), (CATCommandMethod) &CAAVisManagerApplication::ExitCB,
      NULL);
   
}

//-------------------------------------------------------------------------------
CATDlgDocument * CAAVisManagerApplication::GetFrame()

{
   return _pApplicationFrame ;
}

//-------------------------------------------------------------------------------

void CAAVisManagerApplication::ExitCB ( CATCommand *iCmd, CATNotification *iNotif, CATCommandClientData iData)
{
  // Delete all windows 
  int i;
  for(i=0; i <_WindowList.length(); i++)
  {
      if (NULL != _WindowList[i])
      {
          CAAVisManagerWindow * pWindow = _WindowList[i];
          pWindow->DeleteWindow();
      }
  }

  // Destroy every document
  for(i=0 ; i <_DocumentList.length(); i++)
  {
      if (NULL != _DocumentList[i])
      {
          CAAVisManagerDocument * pDocumentToRelease = _DocumentList[i];
          if ( NULL != pDocumentToRelease )
          {
             pDocumentToRelease->Release();
             pDocumentToRelease = NULL ;
          }
      }
  }

  // Destroy of the interactive application
  Destroy();
}

//-------------------------------------------------------------------------------

void CAAVisManagerApplication::OpenCB ( CATCommand *iCmd, CATNotification *iNotif, CATCommandClientData iData)
{
  if (NULL == _pFileSelectorBox)
  {
     // we create a file browser .... 
      _pFileSelectorBox = new CATDlgFile(_pApplicationFrame, "FileBrowser");
  
#ifdef _WINDOWS_SOURCE

      CATUnicodeString nameExtension = CATUnicodeString("CGR File (*.cgr)");
      CATString filterExtension = CATString("*.cgr");
     _pFileSelectorBox->SetFilterStrings(&nameExtension, &filterExtension, 1);

#else

     _pFileSelectorBox->SetFilterPattern("*.cgr");
 
#endif

     // ... and  we put callbacks to this file selector,
     _TypeOfInput = 0 ;
     AddAnalyseNotificationCB(_pFileSelectorBox, _pFileSelectorBox->GetDiaOKNotification(), (CATCommandMethod)& CAAVisManagerApplication::LoadOKCB,&_TypeOfInput);

     AddAnalyseNotificationCB(_pFileSelectorBox, _pFileSelectorBox->GetDiaCANCELNotification(), (CATCommandMethod)& CAAVisManagerApplication::LoadCANCELCB, NULL);
  
     _pFileSelectorBox->SetVisibility(CATDlgShow);
  }

}

//-------------------------------------------------------------------------------

void CAAVisManagerApplication::InsertCB ( CATCommand *iCmd, CATNotification *iNotif, CATCommandClientData iData)
{
   if(NULL == _pFileSelectorBox)
   {
      // we create a file browser .... 
      _pFileSelectorBox = new CATDlgFile(_pApplicationFrame, "FileBrowser");
   
#ifdef _WINDOWS_SOURCE

      CATUnicodeString nameExtension = CATUnicodeString("CGR File (*.cgr)");
      CATString filterExtension = CATString("*.cgr");
     _pFileSelectorBox->SetFilterStrings(&nameExtension, &filterExtension, 1);

#else

      _pFileSelectorBox->SetFilterPattern("*.cgr");
 
#endif
   
      // ... and  we put callbacks to this file selector,
      _TypeOfInput = 1 ; 
      AddAnalyseNotificationCB(_pFileSelectorBox, _pFileSelectorBox->GetDiaOKNotification(), (CATCommandMethod)& CAAVisManagerApplication::LoadOKCB, &_TypeOfInput);

      AddAnalyseNotificationCB(_pFileSelectorBox, _pFileSelectorBox->GetDiaCANCELNotification(), (CATCommandMethod)& CAAVisManagerApplication::LoadCANCELCB, NULL);
   
      _pFileSelectorBox->SetVisibility(CATDlgShow);
   }
}

//-------------------------------------------------------------------------------

void CAAVisManagerApplication::LoadOKCB(CATCommand *iPublisher,
                                     CATNotification *iNotification,
                                     CATCommandClientData  iData)
{
  char * filename = NULL ;
  CATUnicodeString sel   ;

  // we get back the selected CGR file
  _pFileSelectorBox->GetSelection(sel);
  filename = (char *)sel.ConvertToChar();
   
  int data = *((int *) iData);
  
  switch(data)
  {
  case 0:  // we open a new CGR document
     OpenCGR(filename);
     break;
  case 1: // we insert a CGR to the current document.
     InsertCGR(filename);
     break;
  }

  // To Delete the File Selection Box
  CloseFileBox();
}

//-------------------------------------------------------------------------------

void CAAVisManagerApplication::LoadCANCELCB(CATCommand *iPublisher,
                                         CATNotification *iNotification,
                                         CATCommandClientData  iData)
{
   CloseFileBox();
}

//-------------------------------------------------------------------------------

void CAAVisManagerApplication::CloseFileBox()
{
  _pFileSelectorBox->RequestDelayedDestruction();
  _pFileSelectorBox = NULL;
}

//-------------------------------------------------------------------------------

HRESULT CAAVisManagerApplication::OpenCGR(const char * iFileName)
{
  HRESULT rc = E_FAIL ;

  if( NULL != iFileName)
  {
     // CGR document is created ( and becomes active )
     _ActiveDoc = new CAAVisManagerCGRDocument(iFileName);
   
     // The Application keeps the list of all documents created 
     _DocumentList += _ActiveDoc;

     // Creation of the first vue  
     CAAVisManagerWindow * pWindow = _ActiveDoc->CreateDefaultWindow();

     // The Application keeps the list of all windows created 
     _WindowList += pWindow;

     rc = S_OK ;
  }

  return rc;
}

//-------------------------------------------------------------------------------

HRESULT CAAVisManagerApplication::InsertCGR(const char * iFileName)
{
   if( NULL == iFileName)
   {
      return E_FAIL;
   }

   _ActiveDoc->InsertCGR(iFileName);
   
   return S_OK;
}

//-------------------------------------------------------------------------------

CATNotifPropagationMode CAAVisManagerApplication::AnalyseNotification(
                                       CATCommand * iFromClient,
                                       CATNotification * iNotification)
{
   // we catch every manipulating events send by its children in order to process them.
   // As for the other events the current document send them up to the chain 
   // of responsability thru the default CATCommand::AnalyseNotification method.

   CATNotifPropagationMode rc = CATNotifTransmitToFather;

   if ( NULL != iNotification)
   {
      if ( iNotification->IsAKindOf("CAAVisManagerWindowDeleteNotif"))
      {
         WindowDeleted((CAAVisManagerWindow*)iFromClient) ; 
         rc =  CATNotifDontTransmitToFather;
      }
      else if ( iNotification->IsAKindOf("CAAVisManagerWindowActivateNotif"))
      {
         WindowActivated((CAAVisManagerWindow*)iFromClient) ; 
         rc =  CATNotifDontTransmitToFather;
      }
   }else
   {
         rc =  CATNotifDontTransmitToFather;
   }
   return  rc;
}


//-------------------------------------------------------------------------------
void CAAVisManagerApplication :: WindowDeleted(CAAVisManagerWindow * iWindow)
{
   if ( NULL != iWindow )
   {
      // Cleans the Window
      iWindow->DeleteWindow();

      // Removes the window from the list
      _WindowList -= iWindow ;

      // here test if that's the last window  of the document
      CATBoolean LastWindow = TRUE ;

      if ( TRUE == LastWindow ) 
      {
         CAAVisManagerEditor * pEditor = iWindow->GetEditor();
         if ( NULL != pEditor )
         {
            // Retrieves the document attached to this window
            CAAVisManagerDocument * pDocument = pEditor->GetDocument();
            if ( NULL != pDocument )
            {
               _DocumentList -= pDocument;
               if (_ActiveDoc == pDocument)
               {
                  _ActiveDoc = NULL;
               }
               pDocument->Release();
               pDocument = NULL ;
           }
        }
     }
     
     iWindow->RequestDelayedDestruction();
   }
}

//-------------------------------------------------------------------------------
void CAAVisManagerApplication ::WindowActivated(CAAVisManagerWindow * iWindow)
{
   if ( NULL != iWindow )
   {
      CAAVisManagerEditor * pEditor = iWindow->GetEditor();
      if ( NULL != pEditor )
      {
         CAAVisManagerDocument * pDocument = pEditor->GetDocument();
         if ( NULL != pDocument )
         {
            _ActiveDoc = pDocument;
         }
      }
   }
}
//-------------------------------------------------------------------------------
// ****************************************************************
//***                          ignition                    
// ****************************************************************


// application class instance creation
CAAVisManagerApplication ApplicationInstance("CAAVisManagerApplication");

