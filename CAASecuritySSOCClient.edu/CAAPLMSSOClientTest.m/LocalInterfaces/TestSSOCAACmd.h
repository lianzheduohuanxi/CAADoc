#ifndef TestSSOCAACmd_H
#define TestSSOCAACmd_H
#include "CATStateCommand.h"

#include "CATCommand.h" // for CATStatusChangeRC
#include "CATBoolean.h"

class CATMsgCatalog;

class TestSSOCAACmd : public CATStateCommand
{    
public:

  //constructor of the command
  TestSSOCAACmd (); 
  virtual ~TestSSOCAACmd (); //destructor of the command
  
  virtual void BuildGraph (); //called when the command is instantiated
//  CATStatusChangeRC Activate (CATCommand * iFrom, CATNotification * iNotif);
//  CATStatusChangeRC Cancel (CATCommand * iFrom, CATNotification * iNotif);

private:

 //used to retrieve errors when one occurs within the CAASSOClient object
  CATUnicodeString HandleError(HRESULT iStatus); 

  //used to Display Msg in a Display Blocked Box
  void DisplayMessage(CATUnicodeString &iMessage,int iIsError);
  CATMsgCatalog *m_msgCat; //MsgCatalog Object to retrieve NLS msg from TestSSOCAACmd.CATNls int the RTV
};

#endif
