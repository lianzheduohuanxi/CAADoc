// COPYRIGHT DASSAULT SYSTEMES 2002

// Local Framework
#include "CAAMmrBrowserCmdDlg.h"

// ObjectModelerBase Framework
#include "CATIAlias.h"
#include "CATIDocId.h"
#include "CATOmbDocIdFinder.h"

// Dialog Framework
#include "CATDlgFrame.h"
#include "CATDlgEditor.h"
#include "CATDlgLabel.h"
#include "CATDlgPushButton.h"
#include "CATDlgCheckButton.h"
#include "CATDlgRadioButton.h"
#include "CATDlgGridConstraints.h"

// ApplicationFrame Framework
#include "CATFrmEditor.h"              // The document editor implements CATICatalogBrowserFactory

// Catalog Framework
#include "CATICatalogBrowserFactory.h" // To create a Catalog browser 
#include "CATICatalogBrowser.h"        // The Catalog browser
#include "CATICatalogDescription.h"    // The current description selected by the end user
#include "CATICatalogChapter.h"        // To retrieve the name of the current chapter
#include "CATICatalogQueryResult.h"    // To display the filter used on the chapter
#include "CATICatalogLink.h"           // To make an instantiation
#include "CATICatalogInstantiation.h"  // To make an instantiation

// ComponentsCatalogsIterfaces
#include "CATCatalogDisplayOptions.h"

//System framework
#include "CATGetEnvValue.h"  
#include "CATLib.h"
#include "CATUnicodeString.h"
#include "CATCollec.h"

// Standard C++ library
#include "iostream.h"

//---------------------------------------------------------------------
CAAMmrBrowserCmdDlg::CAAMmrBrowserCmdDlg(CATDialog* iParent)
 : CATDlgDialog (iParent, "CAAMmrBrowserCmdDlg", 
                 CATDlgWndBtnOKCancel|CATDlgWndAutoResize|CATDlgGridLayout)
 , _pDescEditor       (NULL)
 , _pCatalogEditor    (NULL)
 , _pQueryEditor      (NULL)
 , _pQueryResultEditor(NULL)

 , _pModalButton            (NULL)
 , _pWithOkButton           (NULL)
 , _pWithCloseButton        (NULL)
 , _pWithTreeButton         (NULL)
 , _pWithSmallIconsButton   (NULL)
 , _pWithLargeIconsButton   (NULL)
 , _pWithDetailsButton      (NULL)
 , _pInstantiateStateButton (NULL)
 , _pChgtCatalogStateButton (NULL)
 , _pOpenBrowserButton   (NULL)
 , _pQueryStateButton    (NULL)
 , _pInstButton          (NULL)

 , _pBrowserQueryFrame   (NULL)
 , _pInstFrame           (NULL)
 , _pBrowserOptionsFrame (NULL)

 , _pOKNotif               (NULL)
 , _pCancelNotif           (NULL)
 , _pCloseNotif            (NULL)
 , _pSelectNotif           (NULL)
 , _pChangeNotif           (NULL)

 , _pDocumentEditor      (NULL)
 , _pICatalogBrowser     (NULL)
 , _FirstOpen            (TRUE) 

{
  cout <<" CAAMmrBrowserCmdDlg::CAAMmrBrowserCmdDlg" << endl;
  
  // The editor associated with the current document
  // Keep this value at the beginning of the command
  //
  _pDocumentEditor = CATFrmEditor::GetCurrentEditor();
 
  // To avoid to close the window 
  // when the end user clicks enter in a CATDlgEditor
  //
  SetDefaultButton(NULL);
}

CAAMmrBrowserCmdDlg::~CAAMmrBrowserCmdDlg()
{
  cout <<"CAAMmrBrowserCmdDlg::~CAAMmrBrowserCmdDlg" << endl;

  CloseCatalog();

  _pDescEditor        = NULL;
  _pCatalogEditor     = NULL ;
  _pQueryResultEditor = NULL ;
  _pQueryEditor       = NULL ;

  _pModalButton            = NULL;
  _pWithOkButton           = NULL;
  _pWithCloseButton        = NULL;
  _pWithTreeButton         = NULL;
  _pWithSmallIconsButton   = NULL;
  _pWithLargeIconsButton   = NULL;
  _pWithDetailsButton      = NULL;
  _pInstantiateStateButton = NULL ;
  _pChgtCatalogStateButton = NULL ;
  _pQueryStateButton       = NULL ;
  _pInstButton             = NULL ;
  _pOpenBrowserButton      = NULL ;
 
  _pBrowserOptionsFrame = NULL ;
  _pBrowserQueryFrame   = NULL ;
  _pInstFrame           = NULL ;

  _pDocumentEditor      = NULL;
  _pICatalogBrowser     = NULL;

  _pOKNotif             = NULL;
  _pCancelNotif         = NULL;
  _pCloseNotif          = NULL;
  _pSelectNotif         = NULL;
  _pChangeNotif         = NULL;

}


//------------------------------------------------------------------------
void CAAMmrBrowserCmdDlg::Build()
{

   //1- Dialog Object Construction

   //1-1 Catalog's browser Properties frame

   CATDlgFrame* pBrowserFrame = new CATDlgFrame (this, "FrameBrowser", CATDlgGridLayout);

      //1-1-1 Catalog's browser options - options used for open 
      _pBrowserOptionsFrame = new CATDlgFrame (pBrowserFrame, "FrameBrowserOptions", CATDlgGridLayout);
         
         CATDlgLabel* pBehaviorLabel = new CATDlgLabel (_pBrowserOptionsFrame, "BehaviorLabel");
         _pModalButton = new CATDlgCheckButton (_pBrowserOptionsFrame, "ModalCheckButton");

         CATDlgLabel* pButtonLabel = new CATDlgLabel (_pBrowserOptionsFrame, "ButtonLabel");
         CATDlgFrame* pButtonFrame = new CATDlgFrame (_pBrowserOptionsFrame, "ButtonFrame", CATDlgFraNoFrame|CATDlgGridLayout);
           _pWithOkButton    = new CATDlgRadioButton (pButtonFrame, "WithOK");
           _pWithCloseButton = new CATDlgRadioButton (pButtonFrame, "WithClose");
           _pWithCloseButton->SetState (CATDlgCheck);

         CATDlgLabel* pDisplayOptionsLabel = new CATDlgLabel (_pBrowserOptionsFrame, "DisplayOptionsLabel");
         CATDlgFrame* pDisplayOptionsFrame = new CATDlgFrame (_pBrowserOptionsFrame, "DispOpFrame", CATDlgFraNoFrame|CATDlgGridLayout);
       
           _pWithTreeButton       = new CATDlgCheckButton (pDisplayOptionsFrame, "Tree");
           _pWithSmallIconsButton = new CATDlgRadioButton (pDisplayOptionsFrame, "Small");
           _pWithSmallIconsButton->SetState (CATDlgCheck);
           _pWithLargeIconsButton = new CATDlgRadioButton (pDisplayOptionsFrame, "Large");
           _pWithDetailsButton    = new CATDlgRadioButton (pDisplayOptionsFrame, "Detail");


      //1-1-2 Options for Instantiation
      CATDlgFrame* pBrowserInstMngtFrame = new CATDlgFrame (pBrowserFrame, "FrameBrowserInstMngt", CATDlgGridLayout);
         _pInstantiateStateButton = new CATDlgCheckButton (pBrowserInstMngtFrame, "InstantiateState");
   
      //1-1-3 Authorize or not the catalog changement- 
      _pChgtCatalogStateButton = new CATDlgCheckButton (pBrowserFrame, "ChgtCatalogState");

      //1-1-4 Button to open the Catalog Browser
      _pOpenBrowserButton = new CATDlgPushButton (pBrowserFrame, "ButtonOpenBrowser");
      
      //1-1-5 Filtering 
      _pBrowserQueryFrame = new CATDlgFrame (pBrowserFrame, "FrameBrowserQuery", CATDlgGridLayout);
      _pBrowserQueryFrame->SetSensitivity(CATDlgDisable);

         CATDlgLabel* pQueryLabel = new CATDlgLabel (_pBrowserQueryFrame, "QueryLabel");
        _pQueryEditor = new CATDlgEditor (_pBrowserQueryFrame, "EditorQuery");
        _pQueryEditor->SetVisibleTextWidth (25);
        _pQueryStateButton = new CATDlgCheckButton (_pBrowserQueryFrame, "QueryState");
        _pQueryStateButton->SetState(CATDlgCheck); // Default behavior 
        CATDlgLabel * pQueryResultLabel = new CATDlgLabel (_pBrowserQueryFrame, "QueryResultLabel");
        _pQueryResultEditor = new CATDlgEditor (_pBrowserQueryFrame, "QueryResultEditor",CATDlgEdtReadOnly);
              
   // 1-2 Instantiation Frame 

   _pInstFrame = new CATDlgFrame (this, "FrameInst", CATDlgGridLayout);
   _pInstFrame->SetSensitivity(CATDlgDisable);

   CATDlgLabel* pCatalogLabel = new CATDlgLabel (_pInstFrame, "CatalogLabel");
     _pCatalogEditor = new CATDlgEditor (_pInstFrame, "EditorCatalog");
     _pCatalogEditor->SetVisibleTextWidth (25);

     CATDlgLabel* pDescLabel = new CATDlgLabel (_pInstFrame,"DescLabel");
     _pDescEditor = new CATDlgEditor (_pInstFrame,"EditorDesc");
     _pDescEditor->SetVisibleTextWidth (25);

     _pInstButton = new CATDlgPushButton (_pInstFrame,"InstButton");
     _pInstButton->SetSensitivity(CATDlgDisable);

   //2- Dialog Box Layout
   
   SetGridRowResizable    (1, 1);
   SetGridColumnResizable (0, 1);

   // 2-1 Inside Catalog's browser Properties frame 
   pBrowserFrame->SetGridConstraints (0, 0, 1, 1, CATGRID_4SIDES);
   _pInstFrame->SetGridConstraints (1, 0, 1, 1, CATGRID_4SIDES);
   _pInstFrame->SetGridColumnResizable (1, 1);

   // 2-2 Inside Catalog Browser Properties
   
   _pBrowserOptionsFrame->SetGridConstraints (0, 0, 1, 1, CATGRID_4SIDES);
   pBrowserInstMngtFrame->SetGridConstraints (1, 0, 1, 1, CATGRID_4SIDES);
   _pChgtCatalogStateButton->SetGridConstraints (2, 0, 1, 1, CATGRID_4SIDES);
   _pOpenBrowserButton->SetGridConstraints (3, 0, 1, 1, CATGRID_4SIDES);
   _pBrowserQueryFrame->SetGridConstraints (4, 0, 1, 1, CATGRID_4SIDES);

   // 2-2-1 Inside Catalog Browser Options frame
   pBehaviorLabel->SetGridConstraints (0, 0, 1, 1, CATGRID_LEFT|CATGRID_RIGHT|CATGRID_TOP);
   _pModalButton->SetGridConstraints (0, 1, 1, 1, CATGRID_4SIDES);

   pButtonLabel->SetGridConstraints (1, 0, 1, 1, CATGRID_LEFT|CATGRID_RIGHT|CATGRID_TOP);
   pButtonFrame->SetGridConstraints (1, 1, 1, 1, CATGRID_4SIDES);
   pButtonFrame->SetGridColumnResizable (0, 1);

   pDisplayOptionsLabel->SetGridConstraints (2, 0, 1, 1, CATGRID_LEFT|CATGRID_RIGHT|CATGRID_TOP);
   pDisplayOptionsFrame ->SetGridConstraints (2, 1, 1, 1, CATGRID_4SIDES);
   pDisplayOptionsFrame->SetGridColumnResizable (0, 1);

   // 2-2-1-a Inside the Button frame
   _pWithOkButton    ->SetGridConstraints (0, 0, 1, 1, CATGRID_4SIDES);
   _pWithCloseButton ->SetGridConstraints (1, 0, 1, 1, CATGRID_4SIDES);

   // 2-2-1-b Inside the Display Option frame
   _pWithTreeButton      ->SetGridConstraints (0, 0, 1, 1, CATGRID_4SIDES);
   _pWithSmallIconsButton->SetGridConstraints (1, 0, 1, 1, CATGRID_4SIDES);
   _pWithLargeIconsButton->SetGridConstraints (2, 0, 1, 1, CATGRID_4SIDES);
   _pWithDetailsButton   ->SetGridConstraints (3, 0, 1, 1, CATGRID_4SIDES);
   
   // 2-2-2 Inside the Catalog Browser Managment
   _pInstantiateStateButton->SetGridConstraints (1, 0, 1, 1, CATGRID_4SIDES);
 
   // 2-2-2 Inside the Catalog Browser Query
   pQueryLabel->SetGridConstraints (0, 0, 1, 1, CATGRID_4SIDES);
   _pQueryEditor->SetGridConstraints (0, 1, 1, 1, CATGRID_4SIDES);
   _pQueryStateButton->SetGridConstraints (1, 0, 1, 1, CATGRID_4SIDES);
   pQueryResultLabel->SetGridConstraints (2, 0, 1, 1, CATGRID_4SIDES);
   _pQueryResultEditor->SetGridConstraints (2, 1, 1, 1, CATGRID_4SIDES);

   // 2-2 Inside Instantiation Frame
   pCatalogLabel->SetGridConstraints (0, 0, 1, 1, CATGRID_4SIDES);
   _pCatalogEditor->SetGridConstraints (0, 1, 1, 1, CATGRID_4SIDES);
   pDescLabel->SetGridConstraints (1, 0, 1, 1, CATGRID_4SIDES); 
   _pDescEditor->SetGridConstraints (1, 1, 1, 1, CATGRID_4SIDES);
   _pInstButton ->SetGridConstraints (2, 0, 1, 1, CATGRID_4SIDES);

   //3- Dialog Box Callbacks

   AddAnalyseNotificationCB (_pOpenBrowserButton, _pOpenBrowserButton->GetPushBActivateNotification(),
                               (CATCommandMethod) &CAAMmrBrowserCmdDlg::CreateBrowser,
                               (CATCommandClientData) NULL);
   
   AddAnalyseNotificationCB (_pInstantiateStateButton, _pInstantiateStateButton->GetChkBModifyNotification (),
                               (CATCommandMethod) &CAAMmrBrowserCmdDlg::InstantiationAuthorization,
                               (CATCommandClientData) NULL);
   
   AddAnalyseNotificationCB (_pChgtCatalogStateButton, _pChgtCatalogStateButton->GetChkBModifyNotification (),
                               (CATCommandMethod) &CAAMmrBrowserCmdDlg::ChangeCatalogAuthorization,
                               (CATCommandClientData) NULL);

   AddAnalyseNotificationCB (_pQueryEditor, _pQueryEditor->GetEditModifyExtNotification(),
                               (CATCommandMethod) &CAAMmrBrowserCmdDlg::ChangeQuery,
                               (CATCommandClientData) NULL);

   AddAnalyseNotificationCB (_pInstButton, _pInstButton->GetPushBActivateNotification (),
                               (CATCommandMethod) &CAAMmrBrowserCmdDlg::LaunchInstantiation,
                               (CATCommandClientData) NULL);
}


//------------------------------------------------------------------------

void CAAMmrBrowserCmdDlg::CreateBrowser(CATCommand* iFrom,CATNotification* iNotif, CATCommandClientData iData)
{
   // 1- Reading current options
   CATCciCatalogBrowserDisplayOptions options = CATCatalogDisplayCombo ;
   if ( NULL != _pModalButton)
    options |= (_pModalButton         ->GetState() == CATDlgCheck) ? CATCatalogDisplayWndModal       : NULL;
   if ( NULL != _pWithOkButton)
    options |= (_pWithOkButton        ->GetState() == CATDlgCheck) ? CATCatalogDisplayWndBtnOKCancel : NULL;
   if (NULL != _pWithTreeButton)
    options |= (_pWithTreeButton      ->GetState() == CATDlgCheck) ? CATCatalogDisplayTree           : NULL;
   if (NULL != _pWithSmallIconsButton)
    options |= (_pWithSmallIconsButton->GetState() == CATDlgCheck) ? CATCatalogDisplayWithSmallIcons : NULL;
   if (NULL != _pWithLargeIconsButton)
    options |= (_pWithLargeIconsButton->GetState() == CATDlgCheck) ? CATCatalogDisplayWithLargeIcons : NULL;
   if (NULL != _pWithDetailsButton)
    options |= (_pWithDetailsButton   ->GetState() == CATDlgCheck) ? CATCatalogDisplayWithDetails    : NULL;
   
   // Drag and Drog is not possible because
   // CAAMmrBrowserCmd is not undefined
   // Drag and Drog is only possible when the Select command is the active one
   //
   int DragAndDropAuthorized   = 0 ;
         
   int InstantiationAuthorized = 0 ;
    InstantiationAuthorized = (_pInstantiateStateButton ->GetState() == CATDlgCheck) ? 1: 0;
         
   // 2- Creating the catalog browser
   if ( NULL != _pDocumentEditor)
   {
      CATICatalogBrowserFactory * pICatalogBrowserFactory = NULL;
      HRESULT rc = _pDocumentEditor->QueryInterface (IID_CATICatalogBrowserFactory, 
                                              (void**) &pICatalogBrowserFactory);
      if (SUCCEEDED(rc))
      {
         // 2-1 Catalog browser creation with the options 
         pICatalogBrowserFactory->OpenCatalogBrowser (_pICatalogBrowser, 
                                                      options, 
                                                      DragAndDropAuthorized, 
                                                      InstantiationAuthorized);
         if ( NULL != _pICatalogBrowser)
         {
            CATDlgDialog* window = NULL;
            if (SUCCEEDED (_pICatalogBrowser->GetFatherWindow (window)) && window)
            {
               // 2-2 Reparent the CATCommand in order to manage the 
               //     notification sent by the browser
               window->SetFather (this);
               window->SetVisibility (CATDlgShow);

               // 2-3 Add Callbacks
               if (SUCCEEDED (_pICatalogBrowser->GetOKNotification (_pOKNotif))                    && _pOKNotif)
                  AddAnalyseNotificationCB (window, _pOKNotif    ,
                                      (CATCommandMethod) &CAAMmrBrowserCmdDlg::OKCatalog,
                                      NULL);
               if (SUCCEEDED (_pICatalogBrowser->GetCancelNotification (_pCancelNotif))            && _pCancelNotif)
                  AddAnalyseNotificationCB (window, _pCancelNotif,
                                      (CATCommandMethod) &CAAMmrBrowserCmdDlg::CancelCatalog,
                                      NULL);
               if (SUCCEEDED (_pICatalogBrowser->GetCloseNotification (_pCloseNotif))              && _pCloseNotif)
                   AddAnalyseNotificationCB (window, _pCloseNotif ,
                                      (CATCommandMethod) &CAAMmrBrowserCmdDlg::CancelCatalog,
                                      NULL);
               if (SUCCEEDED (_pICatalogBrowser->GetChangeChapterNotification (_pChangeNotif))     && _pChangeNotif)
                   AddAnalyseNotificationCB (window, _pChangeNotif ,
                                      (CATCommandMethod) &CAAMmrBrowserCmdDlg::ChangeChapter,
                                      NULL);
               if (SUCCEEDED (_pICatalogBrowser->GetSelectDescriptionNotification (_pSelectNotif)) && _pSelectNotif)
                   AddAnalyseNotificationCB (window, _pSelectNotif ,
                                      (CATCommandMethod) &CAAMmrBrowserCmdDlg::SelectDescription,
                                      NULL);
            }
            // 2-4 Authorize or nor the Catalog changement
            if ( NULL != _pChgtCatalogStateButton )
            {
               if ( _pChgtCatalogStateButton->GetState() == CATDlgCheck )
               {
                  _pICatalogBrowser->AuthorizeChangeCatalog(1) ;
               }else
               {
                  _pICatalogBrowser->AuthorizeChangeCatalog(0) ;
               }
            }

            //2-5 At the first open we set some valued
            if ( TRUE == _FirstOpen )
            {
               // 2-5-1 The catalog 
               char * pCAACatalogFileName = NULL ;
               CATLibStatus result = ::CATGetEnvValue("CAACatalogFileName",&pCAACatalogFileName); 
               
               if ( (CATLibSuccess == result) && ( NULL != pCAACatalogFileName) )
               {   
                  CATUnicodeString CatalogName = pCAACatalogFileName ;
                  free (pCAACatalogFileName) ;
                  pCAACatalogFileName = NULL ;
                  cout <<" The catalog path" << CatalogName.ConvertToChar() << endl;

                  CATIDocId * pIDocId = NULL ;
                  rc = CATOmbDocIdFinder::RecoverDocId("File",CatalogName,"catalog",&pIDocId);
                  if ( SUCCEEDED(rc) && ( NULL !=pIDocId) )
                  {
                     rc = _pICatalogBrowser->SetCurrentCatalogDocId(pIDocId);
                  }
                  if ( FAILED(rc) )
                  {
                      cout <<" Error with the catalog path" << CatalogName.ConvertToChar() << endl;
                  }
                  if ( NULL != pIDocId)
                  {
                      pIDocId->Release();
                      pIDocId = NULL ;
                  }
               }

               //2-5-2 The chapter  
               CATListOfCATUnicodeString * pList = NULL ;
               rc = _pICatalogBrowser->BuildCurrentChapterString(pList);
               if ( SUCCEEDED(rc) && ( NULL!= pList))
               {
                  pList->Append ("Nuts");
                  _pICatalogBrowser->SetCurrentChapter (pList);
                  delete pList;
                  pList = NULL ;
               }

               _FirstOpen = FALSE ;
            }
         }

         pICatalogBrowserFactory->Release();
         pICatalogBrowserFactory = NULL ;
      }
   } 

   // 3- Dialog Box Managment
   if ( NULL !=  _pICatalogBrowser )
   {
      // 3-1 The Query frame can be enable
      if ( NULL != _pBrowserQueryFrame)
      {
         _pBrowserQueryFrame->SetSensitivity(CATDlgEnable);
      }
      // 3-2 The Instantiation frame can be enable
      if ( NULL != _pInstFrame )
      {
         _pInstFrame->SetSensitivity(CATDlgEnable);
      }
      // 3-3 The Open button is disable
      if ( NULL != _pOpenBrowserButton )
      {
         _pOpenBrowserButton->SetSensitivity(CATDlgDisable);
      }
      // 3-3 The Options & Display  frame is disable
      if ( NULL != _pBrowserOptionsFrame )
      {
         _pBrowserOptionsFrame->SetSensitivity(CATDlgDisable);
      }
   }
}

//------------------------------------------------------------------------

void CAAMmrBrowserCmdDlg::ChangeChapter(CATCommand* iFrom, CATNotification* iNotif, CATCommandClientData iData)
{
   cout <<"CAAMmrBrowserCmdDlg::ChangeChapter" << endl;

   if ( NULL != _pICatalogBrowser )
   { 
      // Update the name of the catalog
      if ( NULL != _pCatalogEditor )
      {
         CATIDocId * pIDocId = NULL;
         HRESULT rc = _pICatalogBrowser->GetCurrentCatalogDocId(&pIDocId);

         if ( SUCCEEDED(rc) && (NULL !=pIDocId) )
         {
            CATUnicodeString CatalogName ;
            pIDocId->GetIdentifier(CatalogName);
            
            _pCatalogEditor->SetText(CatalogName);
         }else 
         {
            _pCatalogEditor->SetText("");
         }

         if ( NULL != pIDocId )
         {
             pIDocId->Release();
             pIDocId = NULL ;
         }
      }

      // Empty the result query field
      if ( NULL != _pQueryResultEditor)
      {
         CATICatalogQueryResult * pIQueryResult = NULL ;
         HRESULT rc = _pICatalogBrowser->GetCurrentQueryResult(pIQueryResult);
         if ( SUCCEEDED(rc) && ( NULL!=pIQueryResult))
         {
            CATUnicodeString ResultExpression ;
            ResultExpression = pIQueryResult->GetQuery();
          
            _pQueryResultEditor->SetText(ResultExpression) ;

            pIQueryResult->Release();
            pIQueryResult = NULL ;
         } 
      }
   }
}

//------------------------------------------------------------------------

void CAAMmrBrowserCmdDlg::SelectDescription(CATCommand* iFrom, CATNotification* iNotif, CATCommandClientData iData)
{
   cout <<"CAAMmrBrowserCmdDlg::SelectDescription" << endl;

   if ( NULL != _pICatalogBrowser )
   {
     CATICatalogDescription* pICatalogDescription = NULL;
     HRESULT rc = _pICatalogBrowser->GetSelectedDescription (pICatalogDescription);
     if (SUCCEEDED(rc))
     {
        if (pICatalogDescription->IsObjectASubchapter())
        {
           // Case of a chapter selection
           CATICatalogChapter* pICatalogChapter = NULL;
           pICatalogChapter = pICatalogDescription->GetSubChapter();
           if ( NULL != pICatalogChapter )
           {
              CATUnicodeString chap_name  ;

              chap_name  = pICatalogChapter->GetChapterName();
              pICatalogChapter->Release(); 
              pICatalogChapter = NULL;

              _pDescEditor->SetText (chap_name);
           }
           // The description cannot be instantiated
           if (NULL != _pInstButton)
           {
              _pInstButton->SetSensitivity(CATDlgDisable);
           }
           // The OK button cannot be accessible in the Catalog Browser
           if (NULL != _pWithOkButton)
           {
               if ( CATDlgCheck == _pWithOkButton->GetState() )
               {
                  _pICatalogBrowser->OKActivationMode(0);
               }
           }
        }else
        {
           // Case of a component selection (decription of a end chapter)
           CATBaseUnknown * pObject = NULL ;
           rc = pICatalogDescription->GetObject(pObject);
           if ( SUCCEEDED(rc) )
           {
              CATIAlias * pIAliasOnObject = NULL ;
              rc = pObject->QueryInterface(IID_CATIAlias,(void**) & pIAliasOnObject);
              if ( SUCCEEDED(rc) )
              {
                  CATUnicodeString obj_name = pIAliasOnObject->GetAlias();
                  
                  // Display the object name
                  _pDescEditor->SetText (obj_name); 

                  // The description can be instantiated
                  if ( NULL != _pInstButton )
                  {
                     _pInstButton->SetSensitivity(CATDlgEnable);
                  }
                  // The OK button can be accessible in the Catalog Browser
                  if (NULL != _pWithOkButton)
                  {
                     if ( CATDlgCheck == _pWithOkButton->GetState() )
                     {
                        _pICatalogBrowser->OKActivationMode(1);
                     }
                  }

                  pIAliasOnObject->Release();
                  pIAliasOnObject = NULL ;
              }
              pObject->Release();
              pObject= NULL ;
           }
        }

        pICatalogDescription->Release();
        pICatalogDescription = NULL ;
     }
   }
}

//------------------------------------------------------------------------

void CAAMmrBrowserCmdDlg::CancelCatalog(CATCommand* iFrom, CATNotification* iNotif, CATCommandClientData iData)
{
   cout <<"CancelCatalog" << endl;

   CloseCatalog();
}

//------------------------------------------------------------------------

void CAAMmrBrowserCmdDlg::OKCatalog(CATCommand* iFrom, CATNotification* iNotif, CATCommandClientData iData)
{
   cout <<"OKCatalog" << endl;

   CloseCatalog(); 
}

//------------------------------------------------------------------------

void CAAMmrBrowserCmdDlg::CloseCatalog()
{
  cout <<" CAAMmrBrowserCmdDlg::CloseCatalog" << endl;

  if ( NULL != _pICatalogBrowser )
  {
      // Remove Callbacks
      if ( NULL != _pOKNotif)
        RemoveAnalyseNotificationCB (this, _pOKNotif     , NULL);
      if (NULL !=_pCancelNotif)
        RemoveAnalyseNotificationCB (this, _pCancelNotif , NULL);
      if (NULL !=_pChangeNotif)
        RemoveAnalyseNotificationCB (this, _pChangeNotif , NULL);
      if (NULL !=_pSelectNotif)
        RemoveAnalyseNotificationCB (this, _pSelectNotif  , NULL);
      if (NULL !=_pCloseNotif)
        RemoveAnalyseNotificationCB (this, _pCloseNotif  , NULL);

      _pOKNotif = _pCancelNotif = _pCloseNotif = _pSelectNotif = _pChangeNotif = NULL ;

    // The catalog browser will be deleted
    _pICatalogBrowser->CloseBrowser();
    _pICatalogBrowser->Release();
    _pICatalogBrowser = NULL ;

    // Update the result query field
    if ( NULL != _pQueryResultEditor)
    {
        _pQueryResultEditor->SetText("");
    }

    // The Query frame is disable
    if ( NULL != _pBrowserQueryFrame)
    {
       _pBrowserQueryFrame->SetSensitivity(CATDlgDisable);
    }
    // The Instantiation frame can be disable
    if ( NULL != _pInstFrame )
    {
       _pInstFrame->SetSensitivity(CATDlgDisable);
    }
    // The Open button is enable
    if ( NULL != _pOpenBrowserButton )
    {
       _pOpenBrowserButton->SetSensitivity(CATDlgEnable);
    }
    // The Options & Display  frame is enable
    if ( NULL != _pBrowserOptionsFrame )
    {
       _pBrowserOptionsFrame->SetSensitivity(CATDlgEnable);
    }

  }
}

//------------------------------------------------------------------------

void CAAMmrBrowserCmdDlg::InstantiationAuthorization(CATCommand* iFrom, CATNotification* iNotif, CATCommandClientData iData)
{
   cout <<"InstantiationAuthorization" << endl;

   if ( (NULL != _pInstantiateStateButton) && (NULL != _pICatalogBrowser) )
   {
      if ( _pInstantiateStateButton->GetState() == CATDlgCheck )
      {
         _pICatalogBrowser->AuthorizeInstantiation(1) ;
      }else
      {
         _pICatalogBrowser->AuthorizeInstantiation(0) ;
      }
   }     
}

//------------------------------------------------------------------------
void CAAMmrBrowserCmdDlg::ChangeCatalogAuthorization(CATCommand* iFrom, CATNotification* iNotif, CATCommandClientData iData)
{
   cout <<"ChangeCatalogAuthorization" << endl;

   if ( (NULL != _pChgtCatalogStateButton) && (NULL != _pICatalogBrowser))
   {
      if ( _pChgtCatalogStateButton->GetState() == CATDlgCheck )
      {
         _pICatalogBrowser->AuthorizeChangeCatalog(1) ;
      }else
      {
         _pICatalogBrowser->AuthorizeChangeCatalog(0) ;
      }
   }   
}

//------------------------------------------------------------------------
void CAAMmrBrowserCmdDlg::ChangeQuery(CATCommand* iFrom, CATNotification* iNotif, CATCommandClientData iData)
{
    cout <<" CAAMmrBrowserCmdDlg::ChangeQuery" << endl;

    if ( NULL != _pICatalogBrowser )
    {
       // Retrieve the text of the query in the editor
       CATUnicodeString Query ;
       Query = _pQueryEditor->GetText();

       // Retrieve the type of query: interne or user
       int UserQuery = 1;
       if (NULL != _pQueryStateButton)
          UserQuery = (_pQueryStateButton ->GetState() == CATDlgCheck) ? 1: 0;

       // Apply the query
       HRESULT rc = _pICatalogBrowser->SetCurrentQuery(Query,UserQuery);
       if ( FAILED(rc) )
       {
          cout <<" Error with the query" << endl;
       }

       // Update the editor with the complete filter
       // The internal filter and/or the user filter
       //
       CATICatalogQueryResult * pIQueryResult = NULL ;
       rc = _pICatalogBrowser->GetCurrentQueryResult(pIQueryResult);
       if ( SUCCEEDED(rc) && ( NULL!=pIQueryResult))
       {
          CATUnicodeString ResultExpression ;
          ResultExpression = pIQueryResult->GetQuery();
          
          _pQueryResultEditor->SetText(ResultExpression) ;

          pIQueryResult->Release();
          pIQueryResult = NULL ;
       }
       
    }

}

//------------------------------------------------------------------------
void CAAMmrBrowserCmdDlg::LaunchInstantiation(CATCommand* iFrom, CATNotification* iNotif, CATCommandClientData iData)
{
   cout <<" CAAMmrBrowserCmdDlg::LaunchInstantiation" << endl;
   
   HRESULT rc = E_FAIL;
   
   if ( NULL != _pICatalogBrowser )
   {
      CATICatalogDescription * piCatalogDesc = NULL ;
      rc = _pICatalogBrowser->GetSelectedDescription (piCatalogDesc);
      if ( SUCCEEDED(rc) )
      {
         int RepeatMode = 0 ;     // The command launched by RunInstantiationCmd is not repeated 
         int InstantiateMode = 1 ; // Keeping the link 
         piCatalogDesc->RunInstantiationCmd(_pICatalogBrowser, InstantiateMode,RepeatMode);
         
         piCatalogDesc->Release();
         piCatalogDesc = NULL ;
      }
   }
   
}

