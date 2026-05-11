/* -*-c++-*- */
#ifndef CAAxPDMPackSessionPanel_H 
#define CAAxPDMPackSessionPanel_H 
// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATDlgDialog.h"
#include "CATListOfCATString.h"

class CATDlgEditor;
class CATDlgPushButton;
class CATDlgMultiList;
class CATDlgFile;
class CATDlgCheckButton;
class CATListValCATIxPDMItem_var;
class CAAxPDMItemPreviewFrame;

//========================================================================
// Edition Panel
//========================================================================
class CAAxPDMPackSessionPanel : public CATDlgDialog
{
   DeclareResource(CAAxPDMPackSessionPanel,CATDlgDialog)
public:
   CAAxPDMPackSessionPanel(CATDialog*);
   ~CAAxPDMPackSessionPanel();
   void BuildPanel();


   void SetListInfo(const CATListOfCATUnicodeString& ListName,const CATListOfCATUnicodeString& ListStatus,
      const CATListOfCATString& ListAccess);
   void SetCurrentPath(const CATUnicodeString& iCurEnv);
   boolean RefreshPanel(CATListValCATIxPDMItem_var* ListItem);

   CATUnicodeString GetCurrentPath();
   CATListOfCATUnicodeString GetListOfRenamedItems();
   CATListOfCATString GetListOfChecks();

   void SelectDirCB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData);
   void DirSelectedCB (CATCommand*, CATNotification* iNotif, CATCommandClientData iData);
   void DirCancelledCB (CATCommand*, CATNotification* iNotif, CATCommandClientData iData);
   void ActivateLineCB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData);

private:
   CATDlgEditor*     _edt;
   CATDlgMultiList*  _list;
   CATDlgPushButton* _but1;
   CATDlgCheckButton* _chk1,*_chk2,*_chk3,*_chk4,*_chk5,*_chk6,*_chk7;
   CATDlgFile*       _dirSelPopup;

   CAAxPDMItemPreviewFrame* _previewframe;
   CATListValCATIxPDMItem_var * _itemlist;
};

#endif
