#ifndef CAAMmrBrowserCmdDlg_H_
#define CAAMmrBrowserCmdDlg_H_

// COPYRIGHT DASSAULT SYSTEMES 2002

// Dialog Framework
#include "CATDlgDialog.h" // To derive from
class CATDlgEditor; 
class CATDlgPushButton;
class CATDlgRadioButton;
class CATDlgCheckButton;
class CATDlgFrame;
class CATDlgPushButton;

// ApplicationFrame Framework
class CATFrmEditor ;

// ComponentsCatalogsInterfaces framework 
class CATICatalogBrowser ;

class CAAMmrBrowserCmdDlg : public CATDlgDialog
{

  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAAMmrBrowserCmdDlg.CATNls 
  //    
  DeclareResource(CAAMmrBrowserCmdDlg,CATDlgDialog) ;

public:

  CAAMmrBrowserCmdDlg(CATDialog * iParent);

  ~CAAMmrBrowserCmdDlg();

  // Constructs the dialog object
  void Build();

private:

  // Method to close the Catalog Browser
  void CloseCatalog();

  // Callbacks awake by notifications from the Catalog browser
  void OKCatalog        (CATCommand* iFrom, CATNotification* iNotif, CATCommandClientData iData);
  void CancelCatalog    (CATCommand* iFrom, CATNotification* iNotif, CATCommandClientData iData);
  void ChangeChapter    (CATCommand* iFrom, CATNotification* iNotif, CATCommandClientData iData);
  void SelectDescription(CATCommand* iFrom, CATNotification* iNotif, CATCommandClientData iData);
  
  // Callbacks awake by notifications from the current dialog box
  void ChangeCatalogAuthorization (CATCommand* iFrom, CATNotification* iNotif, CATCommandClientData iData);
  void InstantiationAuthorization (CATCommand* iFrom, CATNotification* iNotif, CATCommandClientData iData);
  void DrapAndDropAuthorization   (CATCommand* iFrom, CATNotification* iNotif, CATCommandClientData iData);
  void ChangeQuery                (CATCommand* iFrom, CATNotification* iNotif, CATCommandClientData iData);
  void LaunchInstantiation        (CATCommand* iFrom, CATNotification* iNotif, CATCommandClientData iData);
  void CreateBrowser              (CATCommand* iFrom, CATNotification* iNotif, CATCommandClientData iData);

private:

  // Dialog Objects
  CATDlgEditor           * _pDescEditor;
  CATDlgEditor           * _pCatalogEditor;
  CATDlgEditor           * _pQueryEditor ;
  CATDlgEditor           * _pQueryResultEditor  ;

  CATDlgCheckButton      * _pModalButton ;
  CATDlgCheckButton      * _pWithTreeButton;
  CATDlgCheckButton      * _pInstantiateStateButton   ;
  CATDlgCheckButton      * _pChgtCatalogStateButton  ;
  CATDlgCheckButton      * _pQueryStateButton  ;

  CATDlgRadioButton      * _pWithOkButton;
  CATDlgRadioButton      * _pWithCloseButton;
  CATDlgRadioButton      * _pWithSmallIconsButton;
  CATDlgRadioButton      * _pWithLargeIconsButton;
  CATDlgRadioButton      * _pWithDetailsButton;

  CATDlgPushButton       * _pInstButton  ;
  CATDlgPushButton       * _pOpenBrowserButton ;

  CATDlgFrame            * _pBrowserOptionsFrame ;
  CATDlgFrame            * _pBrowserQueryFrame ;
  CATDlgFrame            * _pInstFrame ;

  // The editor of the document
  // it is useful to create the Catalog browser
  // because this object implements the CATICatalogBrowserFactory 
  // interface
  CATFrmEditor           * _pDocumentEditor ;

  // At the first Catalog browser opening
  // a specific catalog is set current
  // 
  CATBoolean               _FirstOpen ;

  // Pointer on the Catalog Browser
  //
  CATICatalogBrowser     * _pICatalogBrowser;

  // Notifications from the Catalog Browser 
  //
  CATNotification        * _pOKNotif ;
  CATNotification        * _pCancelNotif;
  CATNotification        * _pCloseNotif;
  CATNotification        * _pSelectNotif;
  CATNotification        * _pChangeNotif;
  
};
#endif
