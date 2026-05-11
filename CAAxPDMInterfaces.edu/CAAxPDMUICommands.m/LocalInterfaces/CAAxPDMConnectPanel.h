/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
#ifndef CATPLMTestConnect_H 
#define CATPLMTestConnect_H

#include "CATDlgDialog.h"
#include "CATDlgEditor.h"

class CATUnicodeString;
class CATDlgCombo;

class CAAxPDMConnectPanel : public CATDlgDialog
{
   DeclareResource(CAAxPDMConnectPanel,CATDlgDialog)
public:
   CAAxPDMConnectPanel(CATDialog*);
   ~CAAxPDMConnectPanel();
   void BuildPanel();
   //User Info
   CATUnicodeString GetUserId() {CATUnicodeString sortie; if (_edt1) sortie=_edt1->GetText(); return sortie;};
   CATUnicodeString GetPassword() {CATUnicodeString sortie; if (_edt2) sortie=_edt2->GetText(); return sortie;};
   int GetRole();

protected:
   void ChangeRole(CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData);

private:
   CATDlgEditor* _edt1,*_edt2;
   CATDlgCombo*  _cmb1;
};


#endif
