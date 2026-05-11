#ifndef CAADegCreatePolylineCmd_h
#define CAADegCreatePolylineCmd_h

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
//  State command which creates a polyline from point selections, indications and
//  point coordinates entered in a dialog window.
//
//  Illustrates:
//
//     - Creation of a State command
//     - Use of CATPathElementAgent, CATIndicationAgent and CATDialogAgnt
//     - Use of the CATISO for the temporary objects
//     - Reaction to mouse move
//     - Use of the CATCSO (Set of Current Objects)
//     - Use of a dialog window in a state command
//
//  Usage:
//
//     To specify the points which compose the polyline, you can either
//        - select an existing point 
//        - click in the background 
//        - enter the x,y,z coordinates of a point in the dialog box 
//     At each point specification, a temporary point is created if the point
//     doesn't exist yet and a temporary line is created between the point and 
//     the previous one. Moreover, rubber banding is managed with temporary
//     lines created at each mouse move.
//     To end the polyline, right click in the background. 
//     The final polyline is created and becomes the current selected object.
//
//  Graph:
//
//     Is composed of 2 states:
//       * stStartState containing 3 agents
//         - a CATPathElementAgent to react to point selection
//         - a CATIndicationAgent to react to indication
//         - a CATDialogAgent to react to coordinates entered in the dialog box
//       * stRepeatState containing 4 agents
//         - the same CATPathElementAgent as in stStartState
//         - a CATIndicationAgent to react to indication and mouse moves.
//         - the same CATDialogAgent as in stStartState
//         - a CATDialogAgent to react to right click
//      
//      The first state is only used to get the first point. 
//      Then the second state enables to manage rubber banding and allows to
//      to end the command.
//      Undo/Redo is managed al global and local levels.
//       
//       +--------------------------------------------------+
//       ! PointPathAgent   IndicationAgent     EditorAgent !   
//       +-------+-----------------+-----------------+------+
//               !                 !                 !
//               ! CreatePoint     ! CreatePoint     ! CreatePoint
//               ! BySelect        ! ByIndication    ! ByBox
//               !                 !                 !
//       +-------V-----------------V-----------------V------------------+
//       ! PointPathAgent   IndicationAgent     EditorAgent    EndAgent !   
//       +-+--A-----+--A---------+--A-------------+--A------------+-----+
//    Move !  !     !  !         !  !             !  !            !
//         +--+     +--+         +--+             +--+            !
//     RubberLine  CreatePoint  CreatePoint     CreatePoint       ! Create
//                 BySelect     ByIndication    ByBox             ! Polyline
//                                                                V
//                                                               NULL
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
//  CreatePointBySelect
//  CreatePointByIndication
//  CreatePointByBox
//  CreatePolyline
//
//===========================================================================

// DialogEngine Framework
#include "CATStateCommand.h"  // Needed to derive from CATStateCommand
// Mathematics Framework
#include "CATMathPoint.h"
#include "CATMathPlane.h"

// DialogEngine Framework
class CATPathElementAgent ;   // Acquisition agent
class CATDialogAgent      ;   // Acquisition agent
class CATIndicationAgent  ;   // Acquisition agent

// Local Framework
class CAADegPointEditor      ;   // Needed to enter points coordinates 

// CAASystem.edu Framework
class CAAISysLine            ;   // Needed to create temporary lines
class CAAISysPoint           ;   // Needed to create temporary points
class CAAISysPolyline        ;   // Needed for the global Undo/Redo

// Visualization Framework
class CATISO                 ;   // Needed to show temporary elements


class CAADegCreatePolylineCmd : public CATStateCommand
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAADegCreatePolylineCmd.CATNls 
  //    
  // the beginning of the format of each line in the NLS file is :
  //
  //     CAADegCreatePolylineCmd.
  //
  CmdDeclareResource(CAADegCreatePolylineCmd,CATStateCommand);

  public :

    // Manage the lifecyle of the command
    CAADegCreatePolylineCmd();
    virtual ~CAADegCreatePolylineCmd();

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
    virtual void BuildGraph() ;

    // It's condition methods 
    CATBoolean  CheckPointNumber   (void * iUsefulData) ;
    CATBoolean  CheckFirstPoint    (void * iUsefulData) ;
    CATBoolean  CheckPointBySelect (void * iUsefulData) ;
    CATBoolean  CheckPointByBox    (void * iUsefulData) ;
    CATBoolean  CheckPointByIndic  (void * iUsefulData) ;

    // CreateFirstPointByxxx
    // ---------------------
    // For each agent, retrieves the 3D point and calls NewTemporaryPoint
    // to create a temporary point.
    //
    CATBoolean  CreateFirstPointBySelect(void * iUsefulData);
    CATBoolean  CreateFirstPointByIndic (void * iUsefulData);
    CATBoolean  CreateFirstPointByBox   (void * iUsefulData);

    // RubberBending
    // -------------
    // Create/Update a temporary line when the mouse moves
    //
    CATBoolean  RubberLine        (void * iUsefulData);

    // CreateLineByxxx
    // ---------------
    // For each agent, retrieves the new 3D point and calls NewTemporaryLine 
    // to create a temporary point and a temporary line from the last 
    // point to the new.
    //
    CATBoolean  CreateLineBySelect(void * iUsefulData);
    CATBoolean  CreateLineByIndic (void * iUsefulData);
    CATBoolean  CreateLineByBox   (void * iUsefulData);

    // CreatePolyline
    // --------------
    // Creates a new polyline in the document 
    //
    CATBoolean  CreatePolyline(void * iUsefulData)  ;


    // Local Undo/Redo
    // ----------------
    // Undo, removes objects from the ISO
    // Redo, readds objects in the ISO.
    // 
    CATBoolean  UndoCreateLine(void * iUsefulData);
    CATBoolean  RedoCreateLine(void * iUsefulData);
    CATBoolean  UndoCreateFirstPoint(void * iUsefulData);
    CATBoolean  RedoCreateFirstPoint(void * iUsefulData);

    // GetGlobalUndo 
    // -------------
    // Gives to the dialog engine the methods name to call for the
    // global Undo and Redo, and to release the polyline. 
    //
    // Must be redefined to have Undo/Redo on the command. It is called
    // just after the Cancel method.
    // UndoCreatePolyline, RedoCreatePolyline and DesallocatPolyline are static 
    // methods because will be deallocated before they are called..
    //
    CATCommandGlobalUndo * GetGlobalUndo();

    // Called for the global Undo/Redo when the command is deleted.
    // 
    // DesallocatPolyline
    // ----------------
    // Static method called when Redo/Undo is no more possible.
    // You have staked more than 10 Undo/Redo, or the stack is unstaked, or 
    // model ojects have been modified after a Redo. 
    //
    static void             DesallocatPolyline(void * iUsefulData); 

    // UndoCreatePolyline
    // -------------------
    // Static method called to undo the command.
    // Removes the polyline from the document
    //
    static void             UndoCreatePolyline(void * iUsefulData);

    // RedoCreatePolyline
    // ------------------  
    // Static method called to redo the command. 
    // Puts the polyline back into the document
    //
    static void             RedoCreatePolyline(void * iUsefulData); 
	
  private :

    // NewTemporaryFirstPoint
    // ----------------------
    // Creates a first temporary point,common job for 
    // the CreateFirstPointByxxx methods 
    //
    CATBoolean NewTemporaryFirstPoint(CATMathPoint & iPoint);

    // NewTemporaryLine
    // ----------------
    // Creates a temporary point and a temporary line, common 
    // job for the CreateLineByxxx methods
    //
    CATBoolean NewTemporaryLine      (CATMathPoint & iPoint);

    // GetValuePathElement
    // -------------------
    // Encapsulates the GetValue method of a CATPathElementAgent
    //
    CATBoolean GetValuePathElement(CATMathPoint & ioPoint);

    // TestAllPoints
    // -------------
    // Checks if the current point ( the last given by the end user) is not
    // equal to a previous one .
    //
    CATBoolean TestAllPoints(CATMathPoint & iPoint);

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegCreatePolylineCmd(const CAADegCreatePolylineCmd &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegCreatePolylineCmd & operator = (const CAADegCreatePolylineCmd &iObjectToCopy);

  private :

    //  Dialog agents to give points 
    CATPathElementAgent  * _daPathElement ; 
    CATIndicationAgent   * _daIndicationP ;
    CATIndicationAgent   * _daIndicationP1;
    CATDialogAgent       * _daEditor      ;
    CATDialogAgent       * _daDialogEnd   ;

    // Dialog box to enter coordinates
    CAADegPointEditor    * _pPointEditor   ;

    // Interactiv Set Object: to show temporary elements
    CATISO               * _pISO ;

    // Planar projection for the 2D indication agents 
    CATMathPlane           _ProjPlane ;

    // To manage temporary lines and points 
    CAAISysLine          * _piTemporaryLine[100] ;
    CAAISysPoint         * _piTemporaryPoint[100] ;
    int                    _nbPoint  ;

    // When a temporary point in created maxpoint=nbpoint, but
    // during local undo/redo can _nbPoint change then _maxPoint 
    // is always  constant.
    int                    _maxPoint ;

    // The dotted line to have a rubber bending effect
    CAAISysLine          * _piMouseLine ;

    // To create an element in a document
    CATBaseUnknown       * _pUIActiveObject ;      
    CATBaseUnknown       * _pContainer ;  

    // The Polyline created in CreatePolyline is kept for the global Undo/Redo.
    // With this value it's possible to remove it from the document (Undo),
    // or to add it (Redo)
    // It will be released in the DesallocatPolyline method.
    //
    CAAISysPolyline      * _piEltPolyline ;

};
#endif
