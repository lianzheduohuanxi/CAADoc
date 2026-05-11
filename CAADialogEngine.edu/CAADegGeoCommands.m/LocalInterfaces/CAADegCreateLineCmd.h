#ifndef CAADegCreateLineCmd_h
#define CAADegCreateLineCmd_h

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
//  State command which creates a line from two indications.
//
//  Illustrates:
//
//     - Creation of a State command
//     - Use of CATIndicationAgent 
//     - Use of the CATISO for the temporary objects
//    
//  Usage:
//     Click in the background ==> A temporary point is created.
//     Click in the background => The line is created between the two 
//                                selected points
//
//  Graph:
//     Is composed of 2 states:
//       * stStartState containing one agent
//         - a CATIndicationAgent to react to the first point indication
//       * stEndState containing one agent
//         - the same CATIndicationAgent to react to the second point 
//           indication
//     These states are consecutive. One transition enables to progress
//     from the first state to the second one. 
//     Another transition leaves the stEndState and reaches the NULL
//     state to end the command. 
//
//       +------------------+
//       ! IndicationAgent  !   
//       +--------+---------+
//                !   CreatePoint 
//       +--------V---------+
//       ! IndicationAgent  !   
//       +--------+---------+
//                !   CreateLine
//                V
//               NULL
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
//  BuilGraph   : Implement the state chart
//  CreatePoint : Creates a temporary point at the start point of the line
//  CreateLine  : Creates the line between the two selected points.
//
//===========================================================================
// DialogEngine Framework
#include "CATStateCommand.h"  //Needed to derive from CATStateCommand

// Mathematics Framework
#include "CATMathPoint.h"     //Needed by NewPoint and NewLine 

// Visualization Framework
class CATISO ;                // Needed to visualize the first point
// DialogEngine Framework
class CATIndicationAgent ;    // Dialog agent 
// CAASystem.edu Framework
class CAAISysPoint ;          // First point indicated 

class CAADegCreateLineCmd : public CATStateCommand
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAADegCreateLineCmd.CATNls
  //    
  // the beginning of the format of each line in the NLS file is :
  //
  //     CAADegCreateLineCmd.
  //
  CmdDeclareResource(CAADegCreateLineCmd,CATStateCommand);

  public :

    // Manages the lifecyle of the command.
    //
    CAADegCreateLineCmd();
    virtual ~CAADegCreateLineCmd(); 

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
    CATStatusChangeRC Activate( CATCommand *iCmd,CATNotification *iNotif);

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
    CATStatusChangeRC Cancel( CATCommand *iCmd,CATNotification *iNotif);

    // Deactivate
    // ----------
    // Called when the command selector freezes this command to give
    // the focus to a shared command. When the shared command completes, this
    // frozen command will be reactivated from its current state. 
    //  
    CATStatusChangeRC Desactivate( CATCommand *iCmd,CATNotification *iNotif);

    // BuildGraph
    // -----------
    // Implements the statechart. 
    // It is called once, even if the command is in repeat mode
    //
    //  1- Creates the Dialog Agent 
    //  2- Creates the Start state
    //  3- Creates the End   state
    //  4- Defines a transition from Start to End State
    //  5- Defines a transition from End To Final State 
    //
    virtual void BuildGraph() ;

    // CheckStartPoint
    // ---------------
    // Tests if the root object exists otherwise the line and the first 
    // point should not be created.
    //
    CATBoolean  CheckStartPoint(void * iUsefulData) ;

    // CheckEndPoint
    // -------------
    // Tests if the first point exists and tests if the two points 
    // are not the same.
    //
    CATBoolean  CheckEndPoint(void * iUsefulData) ;


    // CreatePoint
    // -----------
    // Gets the 2D point indicated, projects it in the plane 
    // to have a 3D point and creates a temporary point in the ISO
    //
    CATBoolean  CreatePoint(void * iUsefulData);

    // CreateLine
    // -----------
    // Gets the 2D point indicated, projects it in the plane 
    // to have a 3D point and calls NewLine.
    //
    CATBoolean  CreateLine(void * iUsefulData);


  private :

    // Creates a new line in the document 
    void        NewLine(const CATMathPoint &iPoint)  ;

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegCreateLineCmd(const CAADegCreateLineCmd &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegCreateLineCmd & operator = (const CAADegCreateLineCmd &iObjectToCopy);

  private :

    // We use the same agent for the two indication 
    CATIndicationAgent  * _daIndication ;  
	
    // To create an element in a document
    CATBaseUnknown      * _pUIActiveObject ; 
    CATBaseUnknown      * _pContainer  ; 

    // The first indicated point is added in the ISO 
    CAAISysPoint        * _piFirstPoint ;      
   
    // To show the temporary point ( the first point)
    CATISO              * _pISO ;

};
#endif
