/* -*-c++-*- */
#ifndef CAAxPDMDRMTemplatePanel_H 
#define CAAxPDMDRMTemplatePanel_H 
// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATDlgDialog.h"
#include "CATListOfCATString.h"

class CATDlgLabel;
class CATDlgMultiList;
class CATDlgPushButton;
class CATDlgRadioButton;

//========================================================================
// Edition Panel
//========================================================================
class CAAxPDMDRMTemplatePanel : public CATDlgDialog
{
   DeclareResource(CAAxPDMDRMTemplatePanel,CATDlgDialog)
public:
   CAAxPDMDRMTemplatePanel(CATDialog*);
   ~CAAxPDMDRMTemplatePanel();
   void BuildPanel();


   void Refresh();
   void Validate();

protected:
   void Add1CB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData);
   void Add2CB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData);
   void Add3CB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData);
   void RemoveCB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData);
   void SelectCB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData);
   void ActivateCB (CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData);

private:
   CATDlgMultiList* _Multi;
   CATDlgPushButton* _RemoveBut;
   CATDlgRadioButton*  _rad0,*_rad1,*_rad2;
   CATUnicodeString strTRUE;

};

#endif
