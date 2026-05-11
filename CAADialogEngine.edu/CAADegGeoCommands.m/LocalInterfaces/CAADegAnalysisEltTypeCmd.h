#ifndef CAADegAnalysisEltTypeCmd_h
#define CAADegAnalysisEltTypeCmd_h

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
//  State command which highlights the objects of a given type.
//
//  Illustrates:
//
//     - Creation of a State command
//     - Use of CATPathElementAgent and CATDialogAgent 
//     - Use of the CATPSO
//     - Creation of a contextual menu
//
//  Usage:
//
//     Right click ==> A contextual menu displays a list of object types.
//     Select a type ==> The objects of this type are highlighted.
//
//  Graph:
//
//     Is composed of one state containing 2 agents:
//         - a CATPathElementAgent to react to right clicks on an object
//         - a CATDialogAgent to react to other right clicks
//          (so on the background)
//     Any right click triggers a transition which displays the contextual
//     menu.
//     Each menu item is associated with a callback which highlights the
//     the objects of the specified type by putting this objects into the
//     Set of Prehighlighted Objects (CATPSO).
//     The CATPSO is emptied at the end of the command.
//     The command ends when the user selects another command.
//
//       +--------------------------+<--+
//       ! PathAgent   DialogAgent  !   !  CreateCntxMenu
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
//  CreateCntxMenu : Display the contextual menu
//  ShowLine, ShowPoint, ShowCircle, ShowEllipse ShowPlane: callbacks associated
//                    the menu items. Highlight the objects of a given type.
//
//===========================================================================
//DialogEngine Framework
#include "CATStateCommand.h"   // Needed to derive from CATStateCommand

//Visualization Framework
#include "CATPathElement.h"    // Needed for the UI Active path 

//DialogEngine Framework
class CATPathElementAgent ;    // Dialog Agent used in BuildGraph 
// Visualization Framework
class CATPSO              ;    

class CAADegAnalysisEltTypeCmd : public CATStateCommand
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAADegAnalysisEltTypeCmd.CATNls 
  //    
  // the beginning of the format of each line in the NLS file is :
  //
  //     CAADegAnalysisEltTypeCmd.
  //
  CmdDeclareResource(CAADegAnalysisEltTypeCmd,CATStateCommand);

  public :

    // Manages the lifecyle of the command.
    //
    CAADegAnalysisEltTypeCmd();
    virtual ~CAADegAnalysisEltTypeCmd(); 

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

    // CreateCntxMenu
    // --------------
    // Adds new item in a contextual menu.  
    // It's an action method.
    //
    CATBoolean  CreateCntxMenu(void * iUsefulData);

    // ShowEltCmd
    // ----------
    // Shows all objects of a certain type chosen by the contextual menu
    // 
    void ShowPoint  (CATCommand           *iPublishingCommand, 
                     CATNotification      *iNotification, 
                     CATCommandClientData  iUsefulData);
    void ShowLine   (CATCommand           *iPublishingCommand, 
                     CATNotification      *iNotification, 
                     CATCommandClientData  iUsefulData);
    void ShowCircle (CATCommand           *iPublishingCommand, 
                     CATNotification      *iNotification, 
                     CATCommandClientData  iUsefulData);
    void ShowEllipse(CATCommand           *iPublishingCommand, 
                     CATNotification      *iNotification, 
                     CATCommandClientData  iUsefulData);
    void ShowPlane  (CATCommand           *iPublishingCommand, 
                     CATNotification      *iNotification, 
                     CATCommandClientData  iUsefulData);

  private :

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegAnalysisEltTypeCmd(const CAADegAnalysisEltTypeCmd &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegAnalysisEltTypeCmd & operator = (const CAADegAnalysisEltTypeCmd &iObjectToCopy);

  private :

    // Dialog Agent used in the BuildGraph Method
    CATPathElementAgent  * _daPathElement ;   
    CATDialogAgent       * _daDialog      ;

    // To see in highlight the objects 
    CATPSO               * _pPSO ;

    // The container contains all objects of the current UI active object
    CATBaseUnknown       * _pContainer ;  
    CATPathElement         _UIActivePath ;
    

};
#endif
