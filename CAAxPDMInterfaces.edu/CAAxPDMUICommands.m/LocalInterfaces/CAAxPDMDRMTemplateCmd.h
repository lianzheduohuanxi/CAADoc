/* -*-c++-*- */
#ifndef CAAxPDMDRMTemplateCmd_H 
#define CAAxPDMDRMTemplateCmd_H
// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATStateCommand.h"

class CATUnicodeString;
class CATDialogAgent;
class CAAxPDMDRMTemplatePanel;

class  CAAxPDMDRMTemplateCmd: public CATStateCommand
{
	CATDeclareClass;
   //CmdDeclareResource(CAAxPDMDRMTemplateCmd,CATStateCommand)
   CmdDeclareResourceFile(DRMTemplate,CAAxPDMDRMTemplateCmd,CATStateCommand);
   
public:
   CAAxPDMDRMTemplateCmd();
   virtual ~CAAxPDMDRMTemplateCmd();
   void BuildGraph();
   CATStatusChangeRC     Activate(CATCommand *, CATNotification *);
   CATStatusChangeRC     Cancel(CATCommand *, CATNotification *);

private:
   //------------------------------------------------------------------------
   // Dialog Management
   //------------------------------------------------------------------------
   //Quit
   boolean  Quit(void*);
   boolean  Validate(void*);

   //------------------------------------------------------------------------
   // Agents
   //------------------------------------------------------------------------
   CATDialogAgent*             _PanelCANCELAcq;
   CATDialogAgent*             _PanelOKAcq;

   //------------------------------------------------------------------------
   // Panel
   //------------------------------------------------------------------------
   CAAxPDMDRMTemplatePanel*       _Panel;

};

#endif
