#ifndef CAADegHistogramChartWindowCmd_h
#define CAADegHistogramChartWindowCmd_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Application using a new document (CAAGeometry) with its own workshop 
//  (CAAAfrGeometryWks) and its own commands.
//     
//  CAAGeometry and CAAAfrGeometryWks are described in the 
//  CAAApplicationFrame.edu FW, and state commands are described in this FW
//      
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  State command which creates a window with a Histogram Chart. This window
//  is dedicated to the current document.  
//
//  Illustrates:
//
//     - Creation of a State command
//     - Use of a CATPanelState
//
//  Usage:
//
//   
//
//  Graph:
//
//     Is composed of 1 state which is a CATPanelState. It's a state associated 
//     with 3 transitions created beforehand and linked to the Ok, Apply, Cancel
//     buttons of a given dialog.
//     The transition triggered by the Ok button goes to the NULL state.
//     The transition triggered by the Cancel button goes to the Cancel state.
//     The Cancel states ends the command and execute a global undo on the 
//     command. 
//
//
//       +------------------+
//       !                  !   
//       !                  !
//       ! IndicationAgent  !   
//       !                  !
//       !                  !   
//       +----+--------+----+
//            !        !     
//     Cancel !        ! Ok: CreateWindow
//            !        !     
//            V        V
//          Cancel    NULL
//
//===========================================================================
//  Inheritance:
//  ------------
//              CATStateCommand (DialogEngine Framework)
//                CATCommand (System Framework)
//                  CATEventSubscriber (System Framework)
//                    CATBaseUnknown (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  BuildGraph             : Implements the state chart
//  CreateWindow           : Creates the window
//
//===========================================================================

// DialogEngine Framework
#include "CATStateCommand.h"  //Needed to derive from CATStateCommand

// DialogEngine Framework
class CATDialogAgent ;        //Dialog agent 

// Local Framework
class CAADegHstChartWndDlg;     //The dialog box to customize the window


class CAADegHistogramChartWindowCmd : public CATStateCommand
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAADegHistogramChartWindowCmd.CATNls 
  CmdDeclareResource(CAADegHistogramChartWindowCmd,CATStateCommand);

  public :

    // Manages the lifecyle of the command.
    //
    CAADegHistogramChartWindowCmd();
    virtual ~CAADegHistogramChartWindowCmd();  

    // Activate
    // --------
    // Called when the command selector gives the focus to this command. 
    // Two cases can happen:
    //  -The command starts from the beginning.
    //  -The command restarts at the state that was current when a shared command 
    //   took the focus from it.
    //
    // These two cases can be distinguished thanks to the notification type.
    //
    CATStatusChangeRC Activate   (CATCommand * iCmd,CATNotification * iNotif);

    // Cancel
    // --------
    // Called when the command selector gives the focus to an exclusive command,
    // or if this command completes. In this latter case, the focus is given to 
    // the default command (usually Select). 
    // You should not take care of the command destruction. This is done
    // by the dialog state command engine.
    // 
    // If the end user selects this command again, it is recreated. 
    //
    CATStatusChangeRC Cancel     (CATCommand * iCmd,CATNotification * iNotif);

    // Deactivate
    // ----------
    // Called when the command selector freezes this command to give
    // the focus to a shared command. When the shared command completes, this
    // frozen command will be reactivated from its current state. 
    //  
    CATStatusChangeRC Desactivate(CATCommand * iCmd,CATNotification * iNotif);

    // BuildGraph
    // -----------
    // Implements the statechart. 
    // It is called once, even if the command is in repeat mode
    // 
    //  Creates the dialog to customize the window 
    //  Creates the State associated with the dialog box 
    //  Completes the Ok transition
    //
    virtual void BuildGraph() ;

    // Editor1 selected
    // -----------
    // 
    //
    CATBoolean  Editor1Selected(void * iUsefulData);

     // Editor1 selected
    // -----------
    // 
    //
    CATBoolean  Editor1Deselected(void * iUsefulData);


    // CreateWindow   
    // -------------
    // 
    //
    CATBoolean  CreateHistogramChartWindow  (void * iDummy);

  private :

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegHistogramChartWindowCmd(const CAADegHistogramChartWindowCmd &iObjectToCopy);

  private :
	
    // Dialog box to entry coordinates
    CAADegHstChartWndDlg   * _pHstChartWndDlg ;

    CATDialogAgent         * _daEditor1Selected ;
    CATDialogAgent         * _daEditor1Deselected ;

};
#endif
