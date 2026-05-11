// COPYRIGHT Dassault Systemes 2007
//===================================================================
//
// CAAEnoviaV5SaveCmd.h
// Creation : BZQ - 08.29.2007
//
//===================================================================

#ifndef CAAEnoviaV5SaveCmd_H
#define CAAEnoviaV5SaveCmd_H

#include "CATStateCommand.h"
#include "CATBoolean.h"

class CATCommand;
class CATDlgNotify;
class CATDialogAgent;
class CATDocument;
class CATIProduct_var;
class CATListPtrCATDocument;
class CATUnicodeString;

class CAAEnoviaV5SaveCmd : public CATStateCommand
{
  // Define the Cmd Resources in "CAACV5EV5IntegrationToolbar.CATNls"
   DeclareResource(CAAEnoviaV5SaveCmd, CATStateCommand)
  
public:
  
  // Standard Constructors & Destructors
  CAAEnoviaV5SaveCmd();
  virtual ~CAAEnoviaV5SaveCmd();

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
  CAAEnoviaV5SaveCmd(const CAAEnoviaV5SaveCmd &);
  CAAEnoviaV5SaveCmd & operator=(const CAAEnoviaV5SaveCmd &);

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
