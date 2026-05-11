// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAADlgDemoWindow.h"
#include "CAADlgMoreButtonDlg.h"
#include "CAADlgMoreRadioDlg.h"
#include "CAADlgFrameReplaceDlg.h"

// Dialog Framework
#include "CATInteractiveApplication.h"    // For the current application to destroy
#include "CATDlgBarMenu.h"
#include "CATDlgSubMenu.h"
#include "CATDlgPushItem.h"  
#include "CATDlgLabel.h" 
#include "CATDlgGridConstraints.h"

// C++ Standard library
#include "iostream.h"

//--------------------------------------------------------------------------------------
CAADlgDemoWindow::CAADlgDemoWindow(CATInteractiveApplication * iParentCommand)                              
: CATDlgDocument(iParentCommand, "CAADlgDemoWindowId"),_pApplication(iParentCommand)

{
   cout << "CAADlgDemoWindow::CAADlgDemoWindow" << endl;

   // Don't construct any Dialog's Object child in the constructor 
   // Use the Build Method to do this.

}

//--------------------------------------------------------------------------------------

CAADlgDemoWindow::~CAADlgDemoWindow()
{ 
   cout << "CAADlgDemoWindow::~CAADlgDemoWindow" << endl; 
   _pApplication = NULL ;
}

//--------------------------------------------------------------------------------------

void CAADlgDemoWindow::Build()
{
  cout << "CAADlgDemoWindow::Build" << endl;

   // On the Window Close 
   AddAnalyseNotificationCB(this,
                            GetWindCloseNotification(),
                           (CATCommandMethod)&CAADlgDemoWindow::Exit, NULL);

   // A label with an icon set in the resource/graphic directory
   CATDlgLabel * pLabelBackground= NULL ;
   pLabelBackground  = new CATDlgLabel(this, "LabelBackground");
   pLabelBackground->SetIconName("CAADlgDemonstratorBackground");
   Attach4Sides(pLabelBackground);

   // Menu Bar 
   CATDlgBarMenu * pMenuBar = NULL ;
   pMenuBar  = new CATDlgBarMenu(this, "MenuBar");
   
      CATDlgSubMenu * pFileMenu = NULL ;
      pFileMenu = new CATDlgSubMenu(pMenuBar, "File");

         CATDlgPushItem * pPushItemFileExit = NULL ;
         pPushItemFileExit = new CATDlgPushItem(pFileMenu, "Exit"); 

         AddAnalyseNotificationCB(pPushItemFileExit, 
                                  pPushItemFileExit->GetMenuIActivateNotification(),
                                  (CATCommandMethod)&CAADlgDemoWindow::Exit, NULL);
      
      CATDlgSubMenu * pTabulationMenu = NULL ;
      pTabulationMenu = new CATDlgSubMenu(pMenuBar, "Tabulation");
              
         CATDlgPushItem * pMoreRadioButtonMenu = NULL ;
         pMoreRadioButtonMenu = new CATDlgPushItem(pTabulationMenu, "MoreRadioButton"); 

         AddAnalyseNotificationCB(pMoreRadioButtonMenu, 
                                  pMoreRadioButtonMenu->GetMenuIActivateNotification(),
                                  (CATCommandMethod)&CAADlgDemoWindow::MoreRadioButton, NULL);


         CATDlgPushItem * pMoreLessMoreButtonMenu = NULL ;
         pMoreLessMoreButtonMenu = new CATDlgPushItem(pTabulationMenu, "MoreLessPushButton"); 

         AddAnalyseNotificationCB(pMoreLessMoreButtonMenu, 
                                  pMoreLessMoreButtonMenu->GetMenuIActivateNotification(),
                                  (CATCommandMethod)&CAADlgDemoWindow::MoreLessMoreButton, NULL);

        CATDlgPushItem * pFrameReplaceMenu = NULL ;
        pFrameReplaceMenu = new CATDlgPushItem(pTabulationMenu, "FrameReplace"); 

         AddAnalyseNotificationCB(pFrameReplaceMenu, 
                                  pFrameReplaceMenu->GetMenuIActivateNotification(),
                                  (CATCommandMethod)&CAADlgDemoWindow::FrameReplace, NULL);
}

//--------------------------------------------------------------------------------------

void CAADlgDemoWindow::Exit(CATCommand         * iSendingCommand, 
                           CATNotification    * iSentNotification, 
                           CATCommandClientData iUsefulData)
{
   _pApplication->Destroy();
   _pApplication = NULL ;
}


//--------------------------------------------------------------------------------------

void CAADlgDemoWindow::MoreRadioButton(CATCommand         * iSendingCommand, 
                           CATNotification    * iSentNotification, 
                           CATCommandClientData iUsefulData)
{

    CAADlgMoreRadioDlg * pRadioButtonDlg = new CAADlgMoreRadioDlg(this);
    pRadioButtonDlg->Build();
}

//--------------------------------------------------------------------------------------

void CAADlgDemoWindow::MoreLessMoreButton(CATCommand         * iSendingCommand, 
                           CATNotification    * iSentNotification, 
                           CATCommandClientData iUsefulData)
{
    CAADlgMoreButtonDlg * pMoreButtonDlg = new CAADlgMoreButtonDlg(this);
    pMoreButtonDlg->Build(); 
}

//--------------------------------------------------------------------------------------

void CAADlgDemoWindow::FrameReplace(CATCommand         * iSendingCommand, 
                           CATNotification    * iSentNotification, 
                           CATCommandClientData iUsefulData)
{
    CAADlgFrameReplaceDlg * pFrameReplaceDlg = new CAADlgFrameReplaceDlg(this);
    pFrameReplaceDlg->Build(); 
}


