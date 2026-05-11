#ifndef CAADegAnalysisNumericCmd_h
#define CAADegAnalysisNumericCmd_h

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
//  State command to display the count of selected elements
//
//  Illustrates:
//
//     - Creation of a State command
//     - Use of CATPathElementAgent and CATDialogAgent 
//     - Use of the CATCSO
//     - Use of multi acquisition behavior 
//        - CATDlgEngMultiAcquisitionSelModes,CATDlgEngMultiAcquisitionCtrl,
//          CATDlgEngMultiAcquisitionUserCtrl
//
//  Usage:
//
//     Choose the behavior of the CATPathElementAgent agent in the dialog box
//
//     make selections ==> The objects of this type are highlighted.
//                                    and in the dialog box the count of each
//                                   element selected are displayed
//
//  Graph
//     Is composed of 5 states: 
//
//       * stChoiceBehaviorState containing three agents
//         - three CATDialogAgent to react to events sent by
//           the CATDlgChoiceBehaviorDlg dialog box
//             - Close or Cancel event -> Null state
//             - OK -> depends on the choice we go to:
//                     stMultiAcquisitionSelModesState or stMultiAcquisitionCtrlState 
//                     or stMultiAcquisitionuserCtrlState
//
//       * sMultiAcquisitionSelModesState containing three agents
//         - two CATDialogAgent to react to events sent by
//           the CATDlgAnalysisNumericDlg dialog box
//             - Close or Cancel event -> Null state
//         - one CATPathElementAgent to react to the multi-sel -> stEndState
//
//       * stMultiAcquisitionCtrlState containing three agents
//         - two CATDialogAgent to react to events sent by
//           the CATDlgAnalysisNumericDlg dialog box
//             - Close or Cancel event -> Null state
//         - one CATPathElementAgent to react to the multi-sel -> stEndState
//
//       * stMultiAcquisitionuserCtrlState containing three agents
//         - two CATDialogAgent to react to events sent by
//           the CATDlgAnalysisNumericDlg dialog box
//             - Close or Cancel event -> Null state
//         - one CATPathElementAgent to react to the multi-sel -> stEndState  
//
//       * stEndState containing two agents 
//         - two CATDialogAgent to react to events sent by
//           the CATDlgAnalysisNumericDlg dialog box
//             - Close or Cancel event -> Null state
// 
//
//===========================================================================
//  Inheritance:
//  ------------
//              CATStateCommand (DialogEngine Framework)
//                CATCommand (System Framework)
//                  CATEventSubscriber (System Framework)
//                    CATBaseUnknown (System Framework)
//
//
//===========================================================================
//DialogEngine Framework
#include "CATStateCommand.h"   // Needed to derive from CATStateCommand

//DialogEngine Framework
class CATPathElementAgent ;    // Dialog Agent used in BuildGraph              
class CATDialogAgent ; 

// local framework
class CAADegAnalysisNumericDlg ;  // to display the count of selected element
class CAADegChoiceBehaviorDlg ;   // to choose the behavior of the selection agent

class CAADegAnalysisNumericCmd : public CATStateCommand
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAADegAnalysisNumericCmd.CATNls 
  //    
  // the beginning of the format of each line in the NLS file is :
  //
  //     CAADegAnalysisNumericCmd.
  //
  CmdDeclareResource(CAADegAnalysisNumericCmd,CATStateCommand);

  public :

    // Manages the lifecyle of the command.
    //
    CAADegAnalysisNumericCmd();
    virtual ~CAADegAnalysisNumericCmd(); 

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
    CATStatusChangeRC Activate   (CATCommand *iCmd,CATNotification *iNotif);

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
    CATStatusChangeRC Cancel     (CATCommand *iCmd,CATNotification *iNotif);

    // Deactivate
    // ----------
    // Called when the command selector freezes this command to give
    // the focus to a shared command. When the shared command completes, this
    // frozen command will be reactivated from its current state. 
    //  
    CATStatusChangeRC Desactivate(CATCommand *iCmd,CATNotification *iNotif);

    // BuildGraph
    // -----------
    // Implements the statechart. 
    // Shows a contextual menu only when you click in the background viewer.
    //
    virtual void BuildGraph() ;

    // DisplaySelectedElement
    // ---------------------- 
    // It's an action method to refresh in the 
    // CAADegAnalysisNumericDlg dialog box the count of 
    // selected element.
    //
    CATBoolean  DisplaySelectedElement(void * iUsefulData);

    // CheckCase
    // --------------
    // It is an condition method which tests the _Choice value and
    // the data set to the transition in the buildgraph method. 
    // It enables to trigger the good transition in taken account
    // the end user choice.
    //
    CATBoolean  CheckCase(void * iUsefulData);

    // EndChoice
    // --------------
    // It's an action method to keep the choice, _Choice, for the 
    // behavior of the selection agent, and hide 
    // the CAADegChoiceBehaviorDlg dialog box
    // and show the CAADegAnalysisNumericDlg dialog box
    //
    CATBoolean  EndChoice(void * iUsefulData);

  private :

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegAnalysisNumericCmd(const CAADegAnalysisNumericCmd &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegAnalysisNumericCmd & operator = (const CAADegAnalysisNumericCmd &iObjectToCopy);

  private :

    // Dialog Agents used to make the selection
    CATPathElementAgent  * _daMultiAcquisitionSelModes ;  
    CATPathElementAgent  * _daMultiAcquisitionCtrl ;
    CATPathElementAgent  * _daMultiAcquisitionUserCtrl ;

    // Dialog Agents to react at the notifications
    // sent by the CAADegAnalysisNumericDlg dialog box
    CATDialogAgent       * _daCAADegAnalysisNumericDlgDiaClose ;   
    CATDialogAgent       * _daCAADegAnalysisNumericDlgWndClose ; 

    // Dialog Agents to react at the notifications
    // sent by the CAADegChoiceBehaviorDlg dialog box
    CATDialogAgent       * _daCAADegChoiceBehaviorDlgWndClose ;   
    CATDialogAgent       * _daCAADegChoiceBehaviorDlgDiaCancel ; 
    CATDialogAgent       * _daCAADegChoiceBehaviorDlgDiaOk ; 

    // The dialog box which displays the count of selected elements
    CAADegAnalysisNumericDlg * _pCAADegAnalysisNumericDlg ;

    // The dialog box to choose the behavior of the selection's agent.
    CAADegChoiceBehaviorDlg  * _pCAADegChoiceBehaviorDlg ;

    // The choice of behavior of the end user for the CATPathElementAgent 
    // 1 : _daMultiAcquisitionSelModes will be used 
    // 2 : _daMultiAcquisitionCtrl  will be used 
    // 3 : _daMultiAcquisitionUserCtrl will be used
    // 0 : The behavior is not yet choosen
    //
    int                    _Choice ;
};
#endif
