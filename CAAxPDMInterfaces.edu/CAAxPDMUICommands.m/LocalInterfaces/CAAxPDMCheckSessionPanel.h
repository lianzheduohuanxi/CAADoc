/* -*-c++-*- */
#ifndef CAAxPDMCheckSessionPanel_H 
#define CAAxPDMCheckSessionPanel_H 
// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATDlgDialog.h"
#include "CATListOfCATString.h"

class CATDlgMultiList;
class CATDlgLabel;
class CATListValCATIxPDMItem_var;

//========================================================================
// Edition Panel
//========================================================================
class CAAxPDMCheckSessionPanel : public CATDlgDialog
{
   DeclareResource(CAAxPDMCheckSessionPanel,CATDlgDialog)
public:
   CAAxPDMCheckSessionPanel(CATDialog*);
   ~CAAxPDMCheckSessionPanel();
   void BuildPanel();

   void SetListInfo(const CATListOfCATUnicodeString& ListName,
      const CATListOfCATUnicodeString& ListError,
      const CATListOfCATUnicodeString& ListStatus,
      CATListValCATIxPDMItem_var* _oItemsWithError);

   void SelectLineCB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData);
   void ActivateLineCB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData);


private:

   CATDlgLabel*                _errorhelp;
   CATDlgMultiList*            _list;
   CATListValCATIxPDMItem_var* _oItemsWithError;
};

#endif
