/* -*-c++-*- */
#ifndef CAAxPDMConnectCmd_H 
#define CAAxPDMConnectCmd_H
// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATStateCommand.h"

class CATUnicodeString;
class CATDialogAgent;
class CAAxPDMConnectPanel;

class  CAAxPDMConnectCmd: public CATStateCommand
{
	CATDeclareClass;
   //CmdDeclareResource(CAAxPDMConnectCmd,CATStateCommand)
	CmdDeclareResourceFile(ConnectToPX1,CAAxPDMConnectCmd,CATStateCommand);
   
public:
   CAAxPDMConnectCmd();
   virtual ~CAAxPDMConnectCmd();
   void BuildGraph();
   CATStatusChangeRC     Activate(CATCommand *, CATNotification *);
   CATStatusChangeRC     Cancel(CATCommand *, CATNotification *);

   boolean Connect(void*);
   boolean Quit(void*);


private:
   //------------------------------------------------------------------------
   // Agents
   //------------------------------------------------------------------------
   CATDialogAgent*             _PanelOKAcq,*_PanelCANCELAcq;

   //------------------------------------------------------------------------
   // Panel
   //------------------------------------------------------------------------
   CAAxPDMConnectPanel*        _Panel;

   static CATUnicodeString     _User;

};

#endif
