#ifndef CAAMmrBrowserCmd_h
#define CAAMmrBrowserCmd_h

// COPYRIGHT DASSAULT SYSTEMES 2002

//===========================================================================
//  Abstract of the class :
//  ----------------------
//
//      
//===========================================================================

//DialogEngine Framework
#include "CATStateCommand.h"  // to derive from

//DialogEngine Framework
class CATDialogAgent;         // agent of the CATStateCommand

//Local Framework
class CAAMmrBrowserCmdDlg;  // The dialog box to manage the Browser dialog box

class CAAMmrBrowserCmd : public CATStateCommand
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAAMmrBrowserCmd.CATNls 
  //    
  // the beginning of the format of each line in the NLS file is :
  //
  //     CAAMmrBrowserCmd.
  //
  CmdDeclareResource(CAAMmrBrowserCmd,CATStateCommand);


public: 

   CAAMmrBrowserCmd();

   ~CAAMmrBrowserCmd();
    
   // BuildGraph
   // -----------
   // Implements the statechart. 
   // It is called once, even if the command is in repeat mode
   // 
   //  1- Creates the Dialog Agent 
   //  2- Creates the state 
   //  3- Defines the two transitions 
   //
   void BuildGraph();

   CATStatusChangeRC     Activate(CATCommand * iCmd,CATNotification * iNotif);
   CATStatusChangeRC     Desactivate(CATCommand * iCmd,CATNotification * iNotif);

private:
   
   // Copy constructor, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAAMmrBrowserCmd(const CAAMmrBrowserCmd &iObjectToCopy);

   // Assignment operator, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAAMmrBrowserCmd & operator = (const CAAMmrBrowserCmd &iObjectToCopy);

   // Quit
   // -----
   // Action method executed when the end user clicks the cancel button
   // of the CAAMmrBrowserCmdDlg dialog box, or when he closes it.
   // All the instantiations done during the command are canceled.
   //
   CATBoolean Quit(void *iUsefulData);


private:

   //------------------------------------------------------------------------
   // Agents 
   //------------------------------------------------------------------------
   CATDialogAgent*        _pPanelOKAcq;
   CATDialogAgent*        _pPanelCANCELAcq;

   //------------------------------------------------------------------------
   // The dialog box to manage the Catalog Browser dialog box
   //------------------------------------------------------------------------
   CAAMmrBrowserCmdDlg*       _pPanel;
};

#endif
