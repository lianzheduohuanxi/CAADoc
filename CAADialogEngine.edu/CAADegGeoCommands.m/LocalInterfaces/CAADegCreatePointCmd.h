#ifndef CAADegCreatePointCmd_h
#define CAADegCreatePointCmd_h

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
//  State command which creates a point from an indication or from coordinates
//  entered in a dialog window.
//
//  Illustrates:
//
//     - Creation of a State command
//     - Use of a CATIndicationAgent
//     - Use of a CATPanelState
//
//  Usage:
//
//     To create a point, you can either 
//        - click in the background 
//        - or enter the x,y,z coordinates of a point in the dialog box 
//     You can create as many points as you like. The commands loops on the same
//     dialog until you select Cancel or Ok in the dialog window, or you select
//     another command.
//
//  Graph:
//
//     Is composed of 1 state which is a CATPanelState. It's a state associated 
//     with 3 transitions created beforehand and linked to the Ok, Apply, Cancel
//     buttons of a given dialog.
//     The transition triggered by the Ok button goes to the NULL state.
//     The transition triggered by the Cancel button goes to the Cancel state.
//     The Cancel states ends the command and execute a global undo on the 
//     command. However, in the CAADegCreatePointCmd, Undo/Redo is not programmed.
//     The transition triggered by the Apply button loops on the state.
//
//     In this command, the state contains one agent
//         - a CATIndicationAgent to react to indication
//     and is associated with the dialog expecting point coordinates.
//
//       +------------------+<--+
//       !                  !   ! Apply: CreatePointByBox
//       !                  !---+
//       ! IndicationAgent  !   
//       !                  !<--+
//       !                  !   ! Indication: CreatePointByIndicattion
//       +----+--------+----+---+
//            !        !     
//     Cancel !        ! Ok: CreatePointByBox
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
//  BuilGraph              : Implements the state chart
//  CreatePointByIndication: Creates a point from an indication
//  CreatePointByBox       : Creates a point from coordinates entered in the dialog window
//
//===========================================================================

// DialogEngine Framework
#include "CATStateCommand.h"  //Needed to derive from CATStateCommand

// Mathematics Framework 
#include "CATMathPoint.h"     //Needed by NewPoint 

// DialogEngine Framework
class CATIndicationAgent ;    //Dialog agent 
class CATDialogAgent ;        //Dialog agent 

// Local Framework
class CAADegPointEditor ;     //The dialog box to entry the point coordinates


class CAADegCreatePointCmd : public CATStateCommand
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAADegFileCmd.CATNls  
  // 
  // the beginning of the format of each line in the NLS file is :
  //
  //     CAADegFileCmd.CAADegCreatePointCmd.

  CmdDeclareResourceFile(CAADegFileCmd,CAADegCreatePointCmd,CATStateCommand);

  public :

    // Manages the lifecyle of the command.
    //
    CAADegCreatePointCmd();
    virtual ~CAADegCreatePointCmd();  

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
    //  1- Creates the Indication Agent 
    //  2- Creates the dialog box to input xyz 
    //  3- Creates the State associated with the dialog box and 
    //     containing the Indication Agent
    //  4- Defines the transition triggered by the Indication Agent
    //  5- Completes the Apply transition
    //  6- Completes the Ok transition
    //
    virtual void BuildGraph() ;

    // CheckPoint
    // ----------
    // Tests if the root object exists else the point should not be 
    // created.
    //
    CATBoolean  CheckPoint(void * iBidon);

    // CreatePointByIndication
    // -----------------------
    // Gets the 2D point indicated, projects it in the plane 
    // to have a 3D point and calls NewPoint to create a point 
    // in the document.
    //
    CATBoolean  CreatePointByIndication(void * iDummy);

    // CreatePointByBox   
    // -----------------------
    // Calls NewPoint with the point got from the dialog box
    //
    CATBoolean  CreatePointByBox       (void * iDummy);

  private :

    // Creates a new point in the document
    void               NewPoint(const CATMathPoint &iPoint) ;

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegCreatePointCmd(const CAADegCreatePointCmd &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegCreatePointCmd & operator = (const CAADegCreatePointCmd &iObjectToCopy);

  private :

    // Dialog agents 
    CATIndicationAgent  * _daIndication ; 
	
    // Dialog box to entry coordinates
    CAADegPointEditor   * _pPointEditor ;

    // To create an element in a document
    CATBaseUnknown      * _pUIActiveObject    ;   
    CATBaseUnknown      * _pContainer     ; 


};
#endif
