/* -*-c++-*- */
#ifndef CAAxPDMPropertyCmd_H 
#define CAAxPDMPropertyCmd_H
// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATStateCommand.h"
#include "CATIxPDMItem.h"

class CATUnicodeString;
class CATDialogAgent;
class CATPathElementAgent;
class CAAxPDMPropertyPanel;

class  CAAxPDMPropertyCmd: public CATStateCommand
{
	CATDeclareClass;
   //CmdDeclareResource(CAAxPDMPropertyCmd,CATStateCommand)
	CmdDeclareResourceFile(DisplayProperty,CAAxPDMPropertyCmd,CATStateCommand);
   
public:
   CAAxPDMPropertyCmd();
   virtual ~CAAxPDMPropertyCmd();
   void BuildGraph();
   CATStatusChangeRC     Activate(CATCommand *, CATNotification *);
   CATStatusChangeRC     Cancel(CATCommand *, CATNotification *);

private:
   //------------------------------------------------------------------------
   // Dialog Management
   //------------------------------------------------------------------------
   boolean  RefreshPanel(CATIxPDMItem_var & oItem);
   //Quit
   boolean  Quit(void*);
   //Select Element
   boolean  SelectElement(void*);

   boolean  ActivateInstance(void*);
   boolean  DeactivateInstance(void*);

   //------------------------------------------------------------------------
   // Agents
   //------------------------------------------------------------------------
   CATDialogAgent*             _PanelCANCELAcq;
   CATDialogAgent*             _PanelDeactivateInstance;
   CATDialogAgent*             _PanelActivateInstance;
   CATPathElementAgent*        _ElementAcq;

   //------------------------------------------------------------------------
   // Panel
   //------------------------------------------------------------------------
   CAAxPDMPropertyPanel*       _Panel;

};

#endif
