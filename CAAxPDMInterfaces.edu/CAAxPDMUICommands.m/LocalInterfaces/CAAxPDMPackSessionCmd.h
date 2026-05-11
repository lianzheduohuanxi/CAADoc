/* -*-c++-*- */
#ifndef CAAxPDMPackSessionCmd_H 
#define CAAxPDMPackSessionCmd_H
// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATStateCommand.h"

class CATUnicodeString;
class CATDialogAgent;
class CAAxPDMPackSessionPanel;
class CAAxPDMCheckSessionPanel;
class CATListValCATIxPDMItem_var;
class CATIReporter;

class  CAAxPDMPackSessionCmd: public CATStateCommand
{
	CATDeclareClass;
   //CmdDeclareResource(CAAxPDMPackSessionCmd,CATStateCommand)
	CmdDeclareResourceFile(SaveSession,CAAxPDMPackSessionCmd,CATStateCommand);
   
public:
   CAAxPDMPackSessionCmd();
   virtual ~CAAxPDMPackSessionCmd();
   void BuildGraph();
   CATStatusChangeRC     Activate(CATCommand *, CATNotification *);
   CATStatusChangeRC     Cancel(CATCommand *, CATNotification *);

private:
   //------------------------------------------------------------------------
   // Dialog Management
   //------------------------------------------------------------------------
   boolean  RefreshPanel();
   boolean  RefreshCheckPanel(CATListValCATIxPDMItem_var* oItemsWithError,CATIReporter* oReporter);
   //Quit
   boolean  Quit(void*);
   //OK
   boolean  CheckOnly(void*);
   boolean  Validate(void*);
   boolean  Execute(void*);
   boolean  ExecuteEnd(void*);

   boolean  ValidateChecks(void*);
   boolean  RefuseChecks(void*);


   //------------------------------------------------------------------------
   // Agents
   //------------------------------------------------------------------------
   CATDialogAgent*        _PanelOKAcq,*_PanelAPPLYAcq,*_PanelCANCELAcq;
   CATDialogAgent*        _PanelCheckOKAcq,*_PanelCheckCANCELAcq;

   //------------------------------------------------------------------------
   // Panel
   //------------------------------------------------------------------------
   CAAxPDMPackSessionPanel*       _Panel;
   CAAxPDMCheckSessionPanel*      _PanelCheck;

   //------------------------------------------------------------------------
   // 
   //------------------------------------------------------------------------
   CATListValCATIxPDMItem_var* _ListItem;


};

#endif
