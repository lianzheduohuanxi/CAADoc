/* -*-c++-*- */
#ifndef CAAxPDMDeactivateImpactPanel_H 
#define CAAxPDMDeactivateImpactPanel_H 
// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATDlgDialog.h"
#include "CATListOfCATString.h"

class CATDlgMultiList;
class CATDlgLabel;
class CATListValCATIxPDMItem_var;

//========================================================================
// Edition Panel
//========================================================================
class CAAxPDMDeactivateImpactPanel : public CATDlgDialog
{
   DeclareResource(CAAxPDMDeactivateImpactPanel,CATDlgDialog)
public:
   CAAxPDMDeactivateImpactPanel(CATDialog*);
   ~CAAxPDMDeactivateImpactPanel();
   void BuildPanel();

   void SetListInfo(const CATListOfCATUnicodeString& ListName,
      const CATListOfCATUnicodeString& ListError,
      const CATListOfCATUnicodeString& ListStatus,
      CATListValCATIxPDMItem_var* _oItemsWithError);

   void SelectLineCB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData);
   void ActivateLineCB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData);
   void Quit(CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData);


private:

   CATDlgLabel*                _errorhelp;
   CATDlgMultiList*            _list;
   CATListValCATIxPDMItem_var* _oItemsWithError;
};

#endif
