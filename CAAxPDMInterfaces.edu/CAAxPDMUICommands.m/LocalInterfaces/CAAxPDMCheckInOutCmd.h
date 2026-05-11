/* -*-c++-*- */
#ifndef CAAxPDMCheckInOutCmd_H 
#define CAAxPDMCheckInOutCmd_H
// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATStateCommand.h"

class CATUnicodeString;
class CATString;

class  CAAxPDMCheckInOutCmd: public CATStateCommand
{
	CATDeclareClass;
   //CmdDeclareResource(CAAxPDMCheckInOutCmd,CATStateCommand)
	CmdDeclareResourceFile(CheckInOutPX1,CAAxPDMCheckInOutCmd,CATStateCommand);
   
public:
   CAAxPDMCheckInOutCmd(CATString*);
   virtual ~CAAxPDMCheckInOutCmd();
   void BuildGraph();
   CATStatusChangeRC     Activate(CATCommand *, CATNotification *);
   CATStatusChangeRC     Cancel(CATCommand *, CATNotification *);
   	
private:
   int _mode;
};

#endif
