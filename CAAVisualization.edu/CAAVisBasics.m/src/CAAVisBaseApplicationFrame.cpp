// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAVisBaseApplicationFrame.h"
#include "CAAVisBaseInsertNotification.h"
#include "CAAVisBaseOpenNotification.h"
#include "CAAVisBaseRenderBENotification.h"
#include "CAAVisBaseReframeNotification.h"
#include "CAAVisBaseModifyViewpointNotification.h"
#include "CAAVisBaseExitNotification.h"
#include "CAAVisBaseManipulatorNotification.h"
#include "CAAVisBaseCreateObjectNotification.h"

//Dialog Framework
#include "CATDlgBarMenu.h"
#include "CATDlgSubMenu.h"
#include "CATDlgFile.h"
#include "CATDlgPushItem.h"
#include "CATDlgCheckItem.h"
#include "CATInteractiveApplication.h"

//-------------------------------------------------------------------------------

CAAVisBaseApplicationFrame::CAAVisBaseApplicationFrame(CATInteractiveApplication *iParent, 
                                                       const CATString &iDialogObjectName, 
                                                       CATDlgStyle iStyle)
:CATDlgDocument(iParent, iDialogObjectName, iStyle)
{
  _pRenderBEChkItem = NULL;
  _pManipulatorChkItem = NULL;
  _pFileSelectorBox = NULL;
  _BEStatesArraySize = 10;
  _ManipulatorStatesArraySize = 10;
  _aBEStates = (int *)malloc(_BEStatesArraySize*sizeof(int));
  _aBEStates[0] = 0;
  _aManipulatorStates = (int *)malloc(_ManipulatorStatesArraySize*sizeof(int));
  _aManipulatorStates[0] = 0;
  _NumberOfDocuments = 1;
  _ActiveDocIndex = 0;
  _pApplication = iParent;
}

//-------------------------------------------------------------------------------

CAAVisBaseApplicationFrame::~CAAVisBaseApplicationFrame()
{
  // All the dialog's children are automatically released by the dialog.
  // That's why the menu widgets are not deallocated here.
  // The subscriptions by AddAnalyseNotificationCB are also cancelled 
  // automatically.
  
  if(_aBEStates)
    {
      free(_aBEStates);
      _aBEStates = NULL;
    }

  if(_aManipulatorStates)
    {
      free(_aManipulatorStates);
      _aManipulatorStates = NULL;
    }
  _pRenderBEChkItem = NULL;
  _pManipulatorChkItem = NULL;
  _pFileSelectorBox = NULL;
  _pApplication = NULL;
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplicationFrame::Build()
{
  //Every dialog objects created here, are not explicitly
  //deleted in this class. Indeed, dialog objects deletion is
  //managed by an application global mechanism, and must never be
  //deleted by the class which allocated them.
  
  //menu bar
  CATDlgBarMenu *pMenuBar = new CATDlgBarMenu(this, "MenuBar");

  // File menu:
  // - Open
  // - Insert
  // - Exit
  CATDlgSubMenu *pFileMenu = new CATDlgSubMenu(pMenuBar, "File");

  CATDlgPushItem *pOpen = new CATDlgPushItem(pFileMenu, "Open");
  AddAnalyseNotificationCB(pOpen, pOpen->GetMenuIActivateNotification(),
                           (CATCommandMethod)& CAAVisBaseApplicationFrame::OpenCB,
                           NULL);

  CATDlgPushItem *pInsert = new CATDlgPushItem(pFileMenu, "Insert");
  AddAnalyseNotificationCB(pInsert, pInsert->GetMenuIActivateNotification(),
                           (CATCommandMethod)& CAAVisBaseApplicationFrame::InsertCB,
                           NULL);
  
  CATDlgPushItem *pExit = new CATDlgPushItem(pFileMenu, "Exit");
  AddAnalyseNotificationCB(pExit, pExit->GetMenuIActivateNotification(),
                           (CATCommandMethod)& CAAVisBaseApplicationFrame::ExitCB,
                           NULL);

  // Render menu:
  // - Render bounding boxes
  CATDlgSubMenu *pRenderMenu = new CATDlgSubMenu(pMenuBar, "Render");

  _pRenderBEChkItem = new CATDlgCheckItem(pRenderMenu, "RenderBE");
  AddAnalyseNotificationCB(_pRenderBEChkItem, _pRenderBEChkItem->GetChkIModifyNotification(),
                           (CATCommandMethod)& CAAVisBaseApplicationFrame::RenderBECB,
                           NULL);

  // Viewpoint menu:
  // - Reframe
  // - Modify viewpoint
  CATDlgSubMenu *pViewpointMenu = new CATDlgSubMenu(pMenuBar, "Viewpoint");

  CATDlgPushItem *pReframeButton = new CATDlgPushItem(pViewpointMenu, "Reframe");
  AddAnalyseNotificationCB(pReframeButton, pReframeButton->GetMenuIActivateNotification(),
                           (CATCommandMethod)& CAAVisBaseApplicationFrame::ReframeCB,
                           NULL);

  CATDlgPushItem *pModifyVPButton = new CATDlgPushItem(pViewpointMenu, "ModifyViewpoint");
  AddAnalyseNotificationCB(pModifyVPButton, pModifyVPButton->GetMenuIActivateNotification(),
                           (CATCommandMethod)& CAAVisBaseApplicationFrame::ModifyViewpointCB,
                           NULL);

  // Manipulator menu
  // - Manipulator
  CATDlgSubMenu *pManipulatorMenu = new CATDlgSubMenu(pMenuBar, "Manipulator");

  _pManipulatorChkItem = new CATDlgCheckItem(pManipulatorMenu, "Manipulator");
  AddAnalyseNotificationCB(_pManipulatorChkItem, _pManipulatorChkItem->GetChkIModifyNotification(),
                           (CATCommandMethod)& CAAVisBaseApplicationFrame::ManipulatorCB,
                           NULL);
 
  // VisuObjects menu:
  CATDlgSubMenu *pVisuObjectsMenu = new CATDlgSubMenu(pMenuBar, "VisuObjects");

  CATDlgPushItem *pSurfacicRepButton = new CATDlgPushItem(pVisuObjectsMenu, "CATSurfacicRep");
  AddAnalyseNotificationCB(pSurfacicRepButton , pSurfacicRepButton ->GetMenuIActivateNotification(),
                           (CATCommandMethod)& CAAVisBaseApplicationFrame::CreateVisuObjectCB,
                           CATINT32ToPtr(CAAVisSurfacicRep));

  // For the Close Button 
  AddAnalyseNotificationCB(this,
                            GetWindCloseNotification(),
                           (CATCommandMethod)&CAAVisBaseApplicationFrame::ExitCB, NULL); 
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplicationFrame::OnWindowActivated(int iActiveDocIndex)
{
  //updates the active document index:
  _ActiveDocIndex = iActiveDocIndex;
  
  //When a document is activated, we must restore
  //the states in which were the check items.
  //For example, if the bounding boxes were rendered for the document
  //which window becomes active, the _pRenderBEChkItem must be
  //checked on.
  //
  //BE Render check item
  if(1 == _aBEStates[iActiveDocIndex])
    _pRenderBEChkItem->SetState(CATDlgCheck, 0); //0 not to be notified 
  else
    _pRenderBEChkItem->SetState(CATDlgUncheck, 0);  //0 not to be notified 

  //Manipulator check item
  if(1 == _aManipulatorStates[iActiveDocIndex])
    _pManipulatorChkItem->SetState(CATDlgCheck, 0);  //0 not to be notified 
  else
    _pManipulatorChkItem->SetState(CATDlgUncheck, 0);  //0 not to be notified 
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplicationFrame::OnDeleteWindow(int iActiveDocIndex)
{
  //A window is deleted. That means that a document is closed.
  //We have to update our check items states.

  //updates the _pRenderBEChkItem check item states:
  int *aTempArray = (int *)malloc((_NumberOfDocuments-1)*sizeof(int));
  int i;
  for(i=0; i<_NumberOfDocuments; i++)
    {
      if(i != iActiveDocIndex)
        aTempArray[i] = _aBEStates[i];
    }
  
  for(i=0; i<_NumberOfDocuments-1; i++)
    {
      _aBEStates[i] = aTempArray[i];
    }
  
  //updates the _pManipulatorChkItem check item states:
  for(i=0; i<_NumberOfDocuments; i++)
    {
      if(i != iActiveDocIndex)
        aTempArray[i] = _aManipulatorStates[i];
    }
  
  for(i=0; i<_NumberOfDocuments-1; i++)
    {
      _aManipulatorStates[i] = aTempArray[i];
    }
  
  free(aTempArray);
  aTempArray = NULL;

  //Updates the numnber of opened documents:
  _NumberOfDocuments--;
  
  //If no more doucment is opened:
  if(0 == _NumberOfDocuments)
    {
      _pRenderBEChkItem->SetState(CATDlgUncheck);
      _pManipulatorChkItem->SetState(CATDlgUncheck);
    }

  _ActiveDocIndex = 0;
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplicationFrame::OpenCB(CATCommand *iPublisher,
                                   CATNotification *iNotification,
                                   CATCommandClientData  iData)
{
  if(NULL != _pFileSelectorBox)
    return;

  _pFileSelectorBox = new CATDlgFile(this, "FileBrowser");

  // Sets the search filter. Only CGR files are allowed.
#ifdef _WINDOWS_SOURCE

  CATUnicodeString nameExtension = CATUnicodeString("CGR File (*.cgr)");
  CATString filterExtension = CATString("*.cgr");
 _pFileSelectorBox->SetFilterStrings(&nameExtension, &filterExtension, 1);

#else

  _pFileSelectorBox->SetFilterPattern("*.cgr");
 
#endif
 
  AddAnalyseNotificationCB(_pFileSelectorBox, _pFileSelectorBox->GetDiaOKNotification(),
                           (CATCommandMethod)& CAAVisBaseApplicationFrame::LoadOKCB, NULL);
  AddAnalyseNotificationCB(_pFileSelectorBox, _pFileSelectorBox->GetDiaCANCELNotification(),
                           (CATCommandMethod)& CAAVisBaseApplicationFrame::LoadCANCELCB, NULL);
  _pFileSelectorBox->SetVisibility(CATDlgShow);
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplicationFrame::LoadOKCB(CATCommand *iPublisher,
                                     CATNotification *iNotification,
                                     CATCommandClientData  iData)
{
  //Updates the number of opened documents:
  _NumberOfDocuments++;

  //If necessary, doubles the check items arrays size:
  //For the _pRenderBEChkItem
  if(_NumberOfDocuments > _BEStatesArraySize)
    {
      _BEStatesArraySize += _BEStatesArraySize;
      _aBEStates = (int *)realloc(_aBEStates, _BEStatesArraySize);
    }

  //For the _pManipulatorChkItem
  if(_NumberOfDocuments > _ManipulatorStatesArraySize)
    {
      _ManipulatorStatesArraySize += _ManipulatorStatesArraySize;
      _aManipulatorStates = (int *)realloc(_aManipulatorStates, _ManipulatorStatesArraySize);
    }

  //Initializes the check item state:
  _aBEStates[_NumberOfDocuments-1]          = 0;
  _aManipulatorStates[_NumberOfDocuments-1] = 0;
  

  //Updates the active document index:
  _ActiveDocIndex = _NumberOfDocuments - 1;


  char *pFileName = NULL;
  CATUnicodeString sel;

  _pFileSelectorBox->GetSelection(sel);

  pFileName = (char *)sel.ConvertToChar();
  
  // Warns the application that it has to Open the pFileName CGR file
  //
  // Notice: No need to destroy notification because 
  // it will be destroyed automatically .
  //
  CAAVisBaseOpenNotification *pNotification = new CAAVisBaseOpenNotification(pFileName);
  SendNotification(_pApplication, pNotification);

  LoadCANCELCB(iPublisher, iNotification, iData);
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplicationFrame::LoadCANCELCB(CATCommand *iPublisher,
                                         CATNotification *iNotification,
                                         CATCommandClientData  iData)
{
  _pFileSelectorBox->RequestDelayedDestruction();
  _pFileSelectorBox = NULL;
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplicationFrame::InsertCB(CATCommand *iPublisher,
                                     CATNotification *iNotification,
                                     CATCommandClientData  iData)
{
  //If no document is opened, we can't insert any CGR.
   if(0 == _NumberOfDocuments)
    return;
  
  if(NULL != _pFileSelectorBox)
    return;
 
  _pFileSelectorBox = new CATDlgFile(this, "FileBrowser");

#ifdef _WINDOWS_SOURCE

  CATUnicodeString nameExtension = CATUnicodeString("CGR File (*.cgr)");
  CATString filterExtension = CATString("*.cgr");
 _pFileSelectorBox->SetFilterStrings(&nameExtension, &filterExtension, 1);

#else

  _pFileSelectorBox->SetFilterPattern("*.cgr");
 
#endif

  AddAnalyseNotificationCB(_pFileSelectorBox, _pFileSelectorBox->GetDiaOKNotification(),
                           (CATCommandMethod)& CAAVisBaseApplicationFrame::InsertOKCB, NULL);
  AddAnalyseNotificationCB(_pFileSelectorBox, _pFileSelectorBox->GetDiaCANCELNotification(),
                           (CATCommandMethod)& CAAVisBaseApplicationFrame::LoadCANCELCB, NULL);
  _pFileSelectorBox->SetVisibility(CATDlgShow);
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplicationFrame::InsertOKCB(CATCommand *iPublisher,
                                       CATNotification *iNotification,
                                       CATCommandClientData  iData)
{
  char * pFileName = NULL;
  CATUnicodeString sel;

  _pFileSelectorBox->GetSelection(sel);

  pFileName = (char *)sel.ConvertToChar();

  //Warns the application that it has to insert the pFileName CGR file
  //
  // Notice: No need to destroy notification because 
  // it will be destroyed automatically .
  //
  CAAVisBaseInsertNotification *pNotification = new CAAVisBaseInsertNotification(pFileName);
  SendNotification(_pApplication, pNotification);
  
  LoadCANCELCB(iPublisher, iNotification, iData);
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplicationFrame::ExitCB(CATCommand *iPublisher,
                                   CATNotification *iNotification,
                                   CATCommandClientData  iData)
{
  //All the deletion work is done in CAAVisBaseApplication::DestroyApplication
  //
  // Notice: No need to destroy notification because 
  // it will be destroyed automatically .
  //
  CAAVisBaseExitNotification *pNotification = new CAAVisBaseExitNotification();
  SendNotification(_pApplication, pNotification);
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplicationFrame::RenderBECB(CATCommand *iPublisher,
                                       CATNotification *iNotification,
                                       CATCommandClientData  iData)
{
  //If no document is opened, do nothing:
  if(0 == _NumberOfDocuments)
    return;
  
  int itemChecked = 0;
  //If the _pRenderBEChkItem has been checked on, we have to
  //render the bounding boxes.
  if(_pRenderBEChkItem->GetState() == CATDlgCheck)
    {
      itemChecked = 1;
      //Update of the _pRenderBEChkItem states, for the active document.
      _aBEStates[_ActiveDocIndex] = 1;
      
    }
  else
    {
      itemChecked = 0;
      //Update of the _pRenderBEChkItem:
      _aBEStates[_ActiveDocIndex] = 0;
    }

  //Warns the application that it has to render the Bounding Elements:
  //
  // Notice: No need to destroy notification because 
  // it will be destroyed automatically .
  //
  CAAVisBaseRenderBENotification *pNotification = new CAAVisBaseRenderBENotification(itemChecked);
  SendNotification(_pApplication, pNotification);
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplicationFrame::ReframeCB(CATCommand *iPublisher,
                                      CATNotification *iNotification,
                                      CATCommandClientData  iData)
{
  //If no document is opened, do nothing:
  if(0 == _NumberOfDocuments)
    return;

  //Warns the application that it has to reframe the active document:
  //
  // Notice: No need to destroy notification because 
  // it will be destroyed automatically .
  //
  CAAVisBaseReframeNotification *pNotification = new CAAVisBaseReframeNotification();
  SendNotification(_pApplication, pNotification);  
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplicationFrame::ModifyViewpointCB(CATCommand *iPublisher,
                                              CATNotification *iNotification,
                                              CATCommandClientData  iData)
{
  //If no document is opened, do nothing:
  if(0 == _NumberOfDocuments)
    return;

  //Warns the application that it has to modify the active document's viewpoint:
  //
  // Notice: No need to destroy notification because 
  // it will be destroyed automatically .
  //
  CAAVisBaseModifyViewpointNotification *pNotification = new CAAVisBaseModifyViewpointNotification();
  SendNotification(_pApplication, pNotification);
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplicationFrame::ManipulatorCB(CATCommand *iPublisher,
                                               CATNotification *iNotification,
                                               CATCommandClientData  iData)
{
  //If no document is opened, do nothing:
  if(0 == _NumberOfDocuments)
    return;
  
  int itemChecked = 0;
  //If the _pManipulatorChkItem has been checked on, we have to
  //add manipulator.
  if(CATDlgCheck == _pManipulatorChkItem->GetState())
    {
      itemChecked = 1;
      //Update of the _pManipulatorChkItem states, for the active document.
      _aManipulatorStates[_ActiveDocIndex] = 1;
      
    }
  else
    {
      itemChecked = 0;
      //Update of the _pManipulatorChkItem:
      _aManipulatorStates[_ActiveDocIndex] = 0;
    }

  //Warns the application that it has to add manipulator:
  //
  // Notice: No need to destroy notification because 
  // it will be destroyed automatically .
  //
  CAAVisBaseManipulatorNotification *pNotification = new CAAVisBaseManipulatorNotification(itemChecked);
  SendNotification(_pApplication, pNotification);
}

void CAAVisBaseApplicationFrame::CreateVisuObjectCB(CATCommand *iPublisher,
                                                    CATNotification *iNotification,
                                                    CATCommandClientData  iData)
{
   CATINT32 visuObject = CATPtrToINT32(iData);

   CAAVisObjectType objectType = (CAAVisObjectType)visuObject;
   
   //Warns the application that it has to create a visualization object:
   //
   // Notice: No need to destroy notification because 
   // it will be destroyed automatically .
   //
   CAAVisBaseCreateObjectNotification *pNotification = new CAAVisBaseCreateObjectNotification(objectType);
   SendNotification(_pApplication, pNotification);
}
