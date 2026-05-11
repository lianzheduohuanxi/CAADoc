#ifndef CAADegCreateRectangleCmd_h
#define CAADegCreateRectangleCmd_h

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
//  State command which creates a rectangle from a selected plane and two
//  indications.
//
//  Illustrates:
//
//     - Creation of a State command
//     - Use of CATPathElementAgent and CATIndicationAgent
//     - Use of the CATCSO (Set of Current Objects)
//     - Use of the CATISO for tht temporary objects
//          
//  Usage:
//
//     Select a plane: The plane becomes perpendicular to the camera.
//     Click in the background ==> A temporary point is created. 
//     Move the mouse => Temporary rectangles are created successively to 
//                       follow the mouse. 
//     Click in the background => The final rectangle is created and becomes 
//                                the current selected object.
//
//  Graph:
//
//     Is composed of 3 states:
//       * stPlaneState containing one agent
//         - a CATPathElementAgent to react to plane selection
//       * stGetFirstPointState containing one agent
//         - a CATIndicationAgent to react to indication
//       * stGetLastPointState containing one agent
//         - a CATIndicationAgent to react to indication
//     These states are consecutive. One transition enables to progress
//     from one state to the following. 
//     The last transition leaves the stGetLastPointState and reaches the 
//     NULL state to end the command. 
//     Another transition loops on the stGetLastPointState state to manage 
//     rubber banding.
//
//       +------------------+
//       ! PlanePathAgent   !   
//       +--------+---------+
//                !   CreateCamera 
//       +--------V---------+
//       ! Point1IndicAgent !   
//       +--------+---------+
//                !   CreatePoint
//       +--------V---------+<--+
//       ! Point2IndicAgent !   ! UpdateRectangle   
//       +--------+---------+---+
//                !   NewRectangle
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
//  BuilGraph      : Implements the state chart
//  CreateCamera   : Changes the viewpoint to make the selected plane and the 
//                   screen plane coincide.
//  CreatePoint    : Creates a temporary point.
//  UpdateRectangle: Creates temporary rectangles which follow the mouse
//  NewRectangle   : Creates the final rectangle.
//
//===========================================================================
//DialogEngine Framework
#include "CATStateCommand.h"  // Needed to derive from CATStateCommand
//Mathematics Framework
#include "CATMathPoint.h"     // Needed to manage temporary objects
#include "CATMathPlane.h"     // Projection plane

//DialogEngine Framework
class CATIndicationAgent ;    // Dialog agent to begin/end the rectangle
class CATPathElementAgent ;   // Dialog agent to select the plane

// CAASystem.edu Framework
class CAAISysPoint ;             // Needed to manage temporary objects
class CAAISysPolyline ;          // Needed to manage temporary objects

// Visualization Framework
class CATISO ;                // Needed to visualize temporary objects

class CAADegCreateRectangleCmd : public CATStateCommand
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAADegCreateRectangleCmd.CATNls 
  CmdDeclareResource(CAADegCreateRectangleCmd,CATStateCommand);

  public :

    // Manages the lifecyle of the command.
    //
    CAADegCreateRectangleCmd();
    virtual ~CAADegCreateRectangleCmd();  

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
    //  1- Creates the dialog agents 
    //  2- Creates states
    //  3- Defines transitions  
    //
    virtual void BuildGraph() ;

    // TestPoint(1&2)
    // ----------
    // Test indicated points 
    //
    CATBoolean  TestPoint1(void * iUsefulData);
    CATBoolean  TestPoint2(void * iUsefulData);

    // CreateCamera
    // -----------
    // Retrieves  the CATMathPlane from the selected plane, and sets 
    // the projection plane for the indicator agent. Changes the viewpoint
    // to make the selected plane and the screen plane coincide.
    //
    CATBoolean  CreateCamera    (void * iUsefulData);

    // CreatePoint 
    // -----------
    // Projects the indicated point in the plane, and determines _P1
    // a point of the rectangle. A temporary point is added in the 
    // ISO and a default recantgle to. 
    //
    CATBoolean  CreatePoint    (void * iUsefulData);

    // UpdateRectangle
    // ---------------
    // Determines a new rectangle from the mouse position.
    //
    CATBoolean  UpdateRectangle(void * iUsefulData);

    // NewRectangle
    // ------------
    // Creates a new rectangle ( a closed polyline ) in the document
    //
    CATBoolean  NewRectangle   (void * iUsefulData);

  private :

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegCreateRectangleCmd(const CAADegCreateRectangleCmd &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegCreateRectangleCmd & operator = (const CAADegCreateRectangleCmd &iObjectToCopy);

  private :

    // Dialog Agent
    CATIndicationAgent  * _daIndicationP1 ; 
    CATIndicationAgent  * _daIndicationP2 ;
    CATPathElementAgent * _daPathEltPlane ;

    // Plane for the IndicationAgent
    CATMathPlane          _ProjPlane  ;   

    // Values to manage the rectangle
    CATMathPoint          _P1;
    CATMathPoint          _P2;
    CATMathPoint          _P3;
    CATMathPoint          _P4;
    CAAISysPoint        * _piTemporaryPoint;
    CAAISysPolyline     * _piTemporaryRect;
    CATISO              * _pISO ;

    // To create elements in the document
    CATBaseUnknown      * _pUIActiveObject    ;   
    CATBaseUnknown      * _pContainer ;   

};
#endif
