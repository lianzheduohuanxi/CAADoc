#ifndef CAADegCreateTriangleCmd_h
#define CAADegCreateTriangleCmd_h

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
//  State command which creates a triangle from three selected points.
//
//  Illustrates:
//
//     - Creation of a State command
//     - Use of a CATPathElementAgent several times
//     - Use of the CATCSO (Set of Current Objects)
//     - Undo/Redo management
//     - This state command can be used as agent of an another state command
//        (see CAADegCreatePolyline2TrianglesCmd )
//          - this state command has a constructor which creates the command
//            in undefined mode. ==> Mandatory 
//          - We have implemented BeforeUndo and BeforeRedo because your modele
//            is not transactionnel. In this last case implemented these methods
//            (as AfterUndo and AfterRedo) is not nessessary if you have only 
//             to undo/redo element of the model.  
//  Usage:
//
//     Select a point
//     Select a second point ==> A temporary line is created between the
//                               two selected points 
//     Select a third point  ==> The triangle is created and becomes 
//                               the current selected object.
//
//  Graph:
//
//     Is composed of 3 states containing the same CATPathElement agent
//     expecting a point.
//     These states are consecutive. One transition enables to progress
//     from one state to the following. 
//     The third transition leaves the third states and reaches the NULL
//     state to end the command. 
//     Undo/Redo is managed at local and global levels. 
//
//       +------------------+
//       !  PointPathAgent  !   
//       +--------+---------+
//                !   RetrievePoint 
//       +--------V---------+
//       !  PointPathAgent  !   
//       +--------+---------+
//                !   RetrievePoint 
//       +--------V---------+
//       !  PointPathAgent  !   
//       +--------+---------+
//                !   CreateTriangle
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
//  BuilGraph     : Implements the state chart
//  RetrievePoint : Retrieves the point coordinates.
//  CreateTriangle: Creates the triangle.
//
//===========================================================================
// DialogEngine Framework
#include "CATStateCommand.h"  // Needed to derive from CATStateCommand
// Mathematics Framework
#include "CATMathPoint.h"

// DialogEngine Framework
class CATPathElementAgent ;   // Acquisition agent

// CAASystem.edu Framework
class CAAISysLine            ;   // Needed to create the temporary line
class CAAISysPolyline        ;   // Needed for the global Undo/Redo

// Visualization Framework
class CATISO              ;   // Needed to create the temporary line

class CAADegCreateTriangleCmd : public CATStateCommand
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAADegCreateTriangleCmd.CATNls
  //    
  // the beginning of the format of each line in the NLS file is :
  //
  //     CAADegCreateTriangleCmd.
  //
  CmdDeclareResource(CAADegCreateTriangleCmd,CATStateCommand);

  public :

    // Manage the lifecyle of the command
    CAADegCreateTriangleCmd();

	// This constructeur is mandatory to used this state command as agent
	// In this constructeur, the CATCommand is created in Undefined mode
	// not exclusif and not shared.
	CAADegCreateTriangleCmd(const int iDummy);
    
	virtual ~CAADegCreateTriangleCmd();

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
    CATBoolean  CheckPoint1(void * iUsefulData) ;
    CATBoolean  CheckPoint2(void * iUsefulData) ;
    CATBoolean  CheckPoint3(void * iUsefulData) ;

    // CreatePoint
    // -----------
    // Keeps the first point of the triangle
    //
    CATBoolean  CreatePoint(void * iUsefulData);

    // CreateLine
    // ----------
    // Keeps the second point of the triangle and creates a 
    // temporary line from the two first points.
    //
    CATBoolean  CreateLine(void * iUsefulData);

    // CreateTriangle
    // ---------------
    //  Keeps the third point of the triangle and calls NewTriangle
    //
    CATBoolean  CreateTriangle(void * iUsefulData);

    // It's action methods for the local Undo/Redo
    CATBoolean  UndoCreateLine(void * iUsefulData);
    CATBoolean  RedoCreateLine(void * iUsefulData);
    CATBoolean  UndoCreatePoint(void * iUsefulData);
    CATBoolean  RedoCreatePoint(void * iUsefulData);

	// Methods to manage the Undo/Redo as agent of an another CATStateCommand
	// ----------------------------------------------------------------------
	// These 2 methods ( as AfterUndo and AfterRedo) have been implemented 
	// while your model is not transactionnel. 
	// 
	void BeforeUndo();
	void BeforeRedo();

	// GetValue
	// --------
	// When this command is an agent, this method allows you to
	// retrieve the created triangle.
	// if the triangle is valid, HRESULT is S_OK and oTriangle is valuated by
	// _piEltTriangle, else HRESULT is E_FAIL . 
	// _IsAgentValuated is set TRUE when the triangle is created 
	// and at each Redo, but set a FALSE at the beginning of the command and at
	// each Undo. 
	// GetValue takes account of this value to give the response. 
	//
	HRESULT GetValue(CAAISysPolyline ** oTriangle) ;
	
    // GetGlobalUndo 
    // -------------
    // Gives to the dialog engine the methods name to call for the
    // global Undo and Redo, and to release the triangle. 
    //
    // To redefine to have Undo/Redo on the command. It is called 
    // just after the Cncel method of the command. UndoCreateTriangle, 
    // RedoCreateTriangle and DesallocatTriangle are static methods because
    // the command will be deleted.
    //
    CATCommandGlobalUndo * GetGlobalUndo();

    // DesallocatTriangle
    // ----------------
    // Static method called when Redo/Undo for it is no more possible.
    // You have staked more than 10 Undo/Redo, or the stack is unstaked, or
    // the model has been modified after the Redo.
    //
    static void             DesallocatTriangle(void * iUsefulData); 

    // UndoCreateTriangle  
    // -------------------
    // Static method called when the command is ended. 
    // Must undo the command so it removes the triangle of the document
    //
    static void             UndoCreateTriangle(void * iUsefulData);
    
    // RedoCreateTriangle
    // ----------------
    // Static method called when the command is ended. 
    // Must redo the command so it adds the triangle into the document
    //
    static void             RedoCreateTriangle(void * iUsefulData); 
	
  private :

    // Creates a new triangle in the document 
    void                   NewTriangle()  ;

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegCreateTriangleCmd(const CAADegCreateTriangleCmd &iObjectToCopy);

	// Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegCreateTriangleCmd & operator = (const CAADegCreateTriangleCmd &iObjectToCopy);

	void Init() ;

  private :

    //  Dialog agent to select points 
    CATPathElementAgent  * _daPathElement ;   

    // Retrieves from selected points
    CATMathPoint           _aPoint[3] ;
	
    // ISO managment
    CATISO               * _pISO ;
    CAAISysLine          * _piTemporaryLine ;

    // To create an element in a document
    CATBaseUnknown       * _pUIActiveObject ;      
    CATBaseUnknown       * _pContainer ;  

    // The triangle created in CreateTriangle is kept for the global Undo/Redo.
    // With this value it's possible to remove it from the document (Undo),
    // or to add it (Redo)
    // It will be deleted in the DesallocatTriangle method.
    //
    CAAISysPolyline      * _piEltTriangle ;

	// _IsAgentValuated is set TRUE when the triangle is created 
	// and at each Redo, but set a FALSE at the beginning of the command and at
	// each Undo. 
	CATBoolean             _IsAgentValuated ;
};
#endif
