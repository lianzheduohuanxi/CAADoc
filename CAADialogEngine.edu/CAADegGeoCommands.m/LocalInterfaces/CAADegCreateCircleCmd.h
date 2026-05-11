#ifndef CAADegCreateCircleCmd_h
#define CAADegCreateCircleCmd_h

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
//  State command which creates a circle from a selected plane and two
//  indications.
//
//  Illustrates:
//
//     - Creation of a State command
//     - Use of CATPathElementAgent and CATIndicationAgent 
//     - Use of the CATISO for the temporary objects
//     - Use of a Camera
//     - Reaction to mouse move
//     - Use of the CATCSO (Set of Current Objects)
//
//  Usage:
//     Select a plane ==> The viewpoint is modified. 
//     Click in the background ==> A temporary point is created for the 
//                                 circle center
//     Move the mouse => Temporary circles are created successively to 
//                       follow the mouse. 
//     Click in the background => The final circle is created and becomes 
//                                the current selected object.
//
//  Graph:
//     Is composed of 3 states:
//       * stGetPlane containing one agent
//         - a CATPathElementAgent to react to plane selection
//       * stGetCenter containing one agent
//         - a CATIndicationAgent to react to indication
//       * stGetRadius containing one agent
//         - a CATIndicationAgent to react to indication
//      These states are consecutive. One transition enables to progress
//      from one state to the following. 
//      The last transition leaves the stGetRadius and reaches the NULL
//      state to end the command. 
//      Another transition loops on the stGetRadius state to manage rubber
//      banding.
//
//       +------------------+
//       ! PlanePathAgent   !   
//       +--------+---------+
//                !   CreateCamera 
//       +--------V---------+
//       ! CenterIndicAgent !   
//       +--------+---------+
//                !   CreateCircleCenter
//       +--------V---------+<--+
//       ! RadiusIndicAgent !   ! UpdateCircle   
//       +--------+---------+---+
//                !   NewCircle
//                V
//               NULL
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
//===========================================================================
//  Main Method:
//  ------------
//
//  BuildGraph        : Implements the statechart
//  CreateCamera      : Changes the viewpoint to make the selected plane and the 
//                      screen plane coincide.
//  CreateCircleCenter: Creates a temporary point at the circle center.
//  UpdateCircle      : Creates temporary circles which follow the mouse
//  NewCircle         : Creates the final circle.
//
//===========================================================================
// DialogEngine Framework
#include "CATStateCommand.h"  //Needed to derive from CATStateCommand

// Mathematics Framework
#include "CATMathPoint.h"     //Needed for the circle center
#include "CATMathPlane.h"     //Needed to the plane projection

// CAASystem.edu Framework
class CAAISysPoint ;             //Needed for temporary circle center
class CAAISysCircle ;            //Needed for temporary circle 

// Visualization Framework
class CATISO ;                //Needed to visualize the temporaries elements

// DialogEngine Framework
class CATPathElementAgent ;   //Needed to get the plane 
class CATIndicationAgent ;    //Needed to get the circle 

class CAADegCreateCircleCmd : public CATStateCommand
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAADegCreateCircleCmd.CATNls
  //    
  // the beginning of the format of each line in the NLS file is :
  //
  //     CAADegCreateCircleCmd.
  //
  CmdDeclareResource(CAADegCreateCircleCmd,CATStateCommand);

  public :

    // Manages the lifecyle of the command
    //
    CAADegCreateCircleCmd();
    virtual ~CAADegCreateCircleCmd(); 

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
    CATStatusChangeRC Activate   ( CATCommand *iCmd,CATNotification *iNotif);
    
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
    CATStatusChangeRC Cancel     ( CATCommand *iCmd,CATNotification *iNotif);
    
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
    //  1- Creates dialog agents 
    //  2- Creates states 
    //  3- Defines transitions 
    //
    virtual void BuildGraph() ;

    // CreateCamera 
    // ------------
    // Retrieves  the CATMathPlane from the selected plane, and sets 
    // the projection plane for the indicator agent. Changes the viewpoint
    // to make the selected plane and the screen plane coincide.
    //
    CATBoolean  CreateCamera       (void * iUsefulData);

    // CreateCircleCenter
    // ------------------
    // Retrieves the 3D point for the circle center from the
    // indicator agent, and creates a temporary point and a 
    // a temporary circle of 0 radius. 
    //
    CATBoolean  CreateCircleCenter(void * iUsefulData);

    // UpdateCircle  
    // ------------
    // The mouse position gives a new radius, the radius 
    // of the temporary circle is updated
    //
    CATBoolean  UpdateCircle      (void * iUsefulData);

    // NewCircle
    // ----------
    // Creates a new circle in the document
    //
    CATBoolean  NewCircle         (void * iUsefulData);

    // CheckCircleCenter
    // -----------------
    // Verifies if model data exists ( Root Object ... )
    //
    CATBoolean  CheckCircleCenter (void * iUsefulData);

  private :

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegCreateCircleCmd(const CAADegCreateCircleCmd &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegCreateCircleCmd & operator = (const CAADegCreateCircleCmd &iObjectToCopy);

  private :

    // Dialog Agents
    CATPathElementAgent     * _daPathEltPlane        ; 
    CATIndicationAgent      * _daIndicCircleCenter  ; 
    CATIndicationAgent      * _daIndicRadius  ;

    // Values for the circle
    CATMathPoint              _CircleCenter ;
    float                     _Radius      ;
  
    // Temporary objects 
    CAAISysPoint            * _piTemporaryPoint ;
    CAAISysCircle           * _piTemporaryCircle ;
    CATISO                  * _pISO ;

    // The projection plane 
    CATMathPlane              _ProjPlane       ;   

    // To create objects in the document
    CATBaseUnknown          * _pUIActiveObject ;      
    CATBaseUnknown          * _pContainer ;   

};
#endif
