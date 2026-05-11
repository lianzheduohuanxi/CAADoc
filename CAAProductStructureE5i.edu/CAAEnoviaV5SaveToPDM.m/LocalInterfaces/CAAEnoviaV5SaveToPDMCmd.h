// COPYRIGHT Dassault Systemes 2008
//===================================================================
//
// CAAEnoviaV5SaveToPDMCmd.h
// Creation : BZQ - 08.29.2007
// Reused   : ZPL - 08.06.2008 For new HL "SaveToPDM"
//
//===================================================================

#ifndef CAAEnoviaV5SaveToPDMCmd_H
#define CAAEnoviaV5SaveToPDMCmd_H

#include "CATStateCommand.h"
#include "CATBoolean.h"

class CATCommand;
class CATDlgNotify;
class CATDialogAgent;
class CATDocument;
class CATIProduct_var;
class CATListPtrCATDocument;
class CATUnicodeString;

class CAAEnoviaV5SaveToPDMCmd : public CATStateCommand
{
  // Define the Cmd Resources in "CAACV5EV5IntegrationToolbar.CATNls"
  DeclareResource(CAAEnoviaV5SaveToPDMCmd, CATStateCommand)
  
public:
  
  // Standard Constructors & Destructors
  CAAEnoviaV5SaveToPDMCmd();
  virtual ~CAAEnoviaV5SaveToPDMCmd();

  // Define the Cmd State Sharts
  virtual void BuildGraph();

  // Action Triggered when the Command Gains Focus
  virtual CATStatusChangeRC Activate(CATCommand *iFromClient, CATNotification *iEvtDat);

  // Actions Triggered when the Command Loses Focus
  virtual CATStatusChangeRC Desactivate(CATCommand *iFromClient, CATNotification *iEvtDat);
  virtual CATStatusChangeRC Cancel(CATCommand *iFromClient, CATNotification *iEvtDat);

  // Action Triggered when Get to State2 to State1
  CATBoolean OnOKSelected(void *data);
  
private:

  // Copy Constructor & Equal Operator
  CAAEnoviaV5SaveToPDMCmd(const CAAEnoviaV5SaveToPDMCmd &);
  CAAEnoviaV5SaveToPDMCmd & operator=(const CAAEnoviaV5SaveToPDMCmd &);

  // Misc Services
  HRESULT EditDocument(CATDocument *pToBeEditedDoc);
  HRESULT GetDocumentRootProdRef(CATDocument *ipDoc, CATIProduct_var &ohRefProd);
  HRESULT TraceDocumentName(CATLISTP(CATDocument)* pDocsList);
  HRESULT InsertDocument(CATDocument* ipDocFather, CATDocument* ipDocSon, CATIProduct_var &ohInstProd);
  HRESULT ComputeDataPath(CATUnicodeString &iDocName, int iDocFuturVaultMode, CATUnicodeString &oDocPath);

  // Notification Panel (Displayed before Interactive Save Command Trigger)
  CATDlgNotify *_pEV5SaveDlgNfy;

  // Command Agents (Inform the cmd of the state of the notification panel)
  CATDialogAgent *_pCancelNfyAgent;
  CATDialogAgent *_pOKNfyAgent;

};

#endif
