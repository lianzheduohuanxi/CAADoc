/* -*-c++-*- */
#ifndef CAAxPDMDisconnectCmd_H 
#define CAAxPDMDisconnectCmd_H
// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATStateCommand.h"

class CATUnicodeString;
class CATDialogAgent;
class CAAxPDMPackSessionPanel;
class CAAxPDMCheckSessionPanel;
class CATListValCATIxPDMItem_var;
class CATIReporter;

class  CAAxPDMDisconnectCmd: public CATStateCommand
{
	CATDeclareClass;
   //CmdDeclareResource(CAAxPDMDisconnectCmd,CATStateCommand)
	CmdDeclareResourceFile(DisconnectFromPX1,CAAxPDMDisconnectCmd,CATStateCommand);
   
public:
   CAAxPDMDisconnectCmd();
   virtual ~CAAxPDMDisconnectCmd();
   void BuildGraph();
   CATStatusChangeRC     Activate(CATCommand *, CATNotification *);
   CATStatusChangeRC     Cancel(CATCommand *, CATNotification *);

private:
};

#endif
