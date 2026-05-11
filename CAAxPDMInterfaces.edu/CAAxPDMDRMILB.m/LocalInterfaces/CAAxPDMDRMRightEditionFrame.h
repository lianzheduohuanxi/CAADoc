/* -*-c++-*- */
#ifndef CAAxPDMDRMRightEditionFrame_H 
#define CAAxPDMDRMRightEditionFrame_H 
// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATDlgFrame.h"
#include "CATListOfCATString.h"

class CATDlgLabel;
class CATDlgMultiList;
class CATDlgPushButton;
class CATDlgRadioButton;

//========================================================================
// Edition Panel
//========================================================================
class CAAxPDMDRMRightEditionFrame : public CATDlgFrame
{
   CATDeclareClass;
   DeclareResource(CAAxPDMDRMTemplatePanel,CATDlgFrame)
public:
   CAAxPDMDRMRightEditionFrame(CATDialog*);
   ~CAAxPDMDRMRightEditionFrame();
   void BuildPanel();

   HRESULT Init(const void *iDRMAuthorization, size_t iDRMAuthorizationSize);
   HRESULT InitWithDefault();
   HRESULT RefreshDisplay(CATUnicodeString * DRMUser,DWORD* DRMRight, int DRMUserNb);

   HRESULT GetAuthorization(CATUnicodeString *&DRMUser, DWORD *&DRMRight, int& DRMUserNb);
   HRESULT GetAuthorizations(void *& iDRMAuthorization, size_t& iDRMAuthorizationSize);
   HRESULT ValidateToDefault();

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
   CATUnicodeString strTRUE;

};

#endif
