#ifndef CAADegAnalysisLogCmd_h
#define CAADegAnalysisLogCmd_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Application using a new document (CAAGeometry) with its own workshop 
//  (CAAAfrGeometryWks) and its own commands.
//     
//  CAAGeometry and CAAAfrGeometryWks are described in the 
//      
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  State command which creates a temporary point on a selected line, at 
//  at a given location.
//
//  Illustrates:
//
//     - Creation of a State command
//     - Use of CATPathElementAgent 
//     - Use of the CATISO
//     - Creation of a contextual menu
//
//  Usage:
//
//     Right click on a line ==> A contextual menu displays a choice of 
//                3 points: Start point, Medium point, End point.
//     Select a point type ==> A temporary point is created at the 
//                             specified location.
//
//  Graph:
//
//     Is composed of one state containing 1 agent:
//         - a CATPathElementAgent which reacts to right clicks on lines
//     A right click on a line triggers a transition which displays the 
//     contextual menu.
//     Each menu item is associated with a callback which creates a
//     temporary point at the requested location and puts it into the
//     Set of Interactive Objects (CATISO).
//     The CATISO is emptied at the end of the command.
//     The command ends when the user selects another command.
//
//       +--------------------------+<--+
//       !         PathAgent        !   !  CreateCntxMenu
//       +--------------------------+---+
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
//  BuilGraph
//  CreateCntxMenu: Display the contextual menu
//  StartPoint, MediumPoint, EndPoint: callbacks associated
//          the menu items. Creates the temporary point.
//
//===========================================================================
//DialogEngine Framework
#include "CATStateCommand.h"  // Needed to derive from CATStateCommand

//DialogEngine Framework
class CATPathElementAgent ;   // Dialog agent for lines. 

//Visualization Framework
class CATISO              ;   // Needed to show the temporary point

// CAASystem.edu Framework
class CAAISysPoint           ;   // Needed to show the temporary point

// Mathematics Framework
class CATMathPoint           ;

class CAADegAnalysisLogCmd : public CATStateCommand
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAADegAnalysisLogCmd.CATNls 
  //    
  // the beginning of the format of each line in the NLS file is :
  //
  //     CAADegAnalysisLogCmd.
  //
  CmdDeclareResource(CAADegAnalysisLogCmd,CATStateCommand);

  public :

    // Manages the command lifecyle.
    //
    CAADegAnalysisLogCmd();
    virtual           ~CAADegAnalysisLogCmd(); 

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
    CATStatusChangeRC Activate   ( CATCommand * iCmd,CATNotification * iNotif);

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
    CATStatusChangeRC Cancel     ( CATCommand * iCmd,CATNotification * iNotif);

    // Deactivate
    // ----------
    // Called when the command selector freezes this command to give
    // the focus to a shared command. When the shared command completes, this
    // frozen command will be reactivated from its current state. 
    //  
    CATStatusChangeRC Desactivate( CATCommand * iCmd,CATNotification * iNotif);

    // BuildGraph
    // -----------
    // Implements the statechart. 
    //
    virtual void BuildGraph() ;

    // CreateCntxMenu
    // --------------
    // Adds new item in a contextual menu.  
    // It's an action method.
    //
    CATBoolean  CreateCntxMenu(void * iUsefulData);

    // PointLineCmd
    // ------------
    // Shows the choosen point thanks to the contextual menu 
    // 
    void StartPoint  (CATCommand           *iPublishingCommand, 
                     CATNotification      *iNotification, 
                     CATCommandClientData  iUsefulData);
    void MediumPoint  (CATCommand           *iPublishingCommand, 
                     CATNotification      *iNotification, 
                     CATCommandClientData  iUsefulData);
    void EndPoint  (CATCommand           *iPublishingCommand, 
                     CATNotification      *iNotification, 
                     CATCommandClientData  iUsefulData);
  
  private :

    // Creates and shows the temporary point
    void ShowPoint(CATMathPoint &iPoint);

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegAnalysisLogCmd(const CAADegAnalysisLogCmd &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegAnalysisLogCmd & operator = (const CAADegAnalysisLogCmd &iObjectToCopy);

 private :

    // Dialog Agent for the lines 
    CATPathElementAgent  * _daPathElement ;    

    // ISO Managment 
    CATISO               * _pISO ;
    CAAISysPoint         * _piTemporaryPoint ;

    // The container allows to create temporary point
    CATBaseUnknown       * _pContainer;      

};
#endif
