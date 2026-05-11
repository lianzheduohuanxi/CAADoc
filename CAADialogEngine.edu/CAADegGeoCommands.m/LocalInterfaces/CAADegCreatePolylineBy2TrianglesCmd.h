#ifndef CAADegCreatePolylineBy2TrianglesCmd_h
#define CAADegCreatePolylineBy2TrianglesCmd_h

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
//  State command which creates a polyline from 2 triangles created by the
//  CAADegCreateTriangleCmd command during this command. 
//  At the end of the command we have 3 new elements in the model: the 2 news 
//  triangles and the new polyline. The polyline is created from the 6 points.
//    
//
//  Illustrates:
//
//     - Creation of a State command 
//     - Use of an agent which is a CATStateCommand too
//     - Undo/Redo management
//          
//
//  Graph:
//
//     Is composed of 2 states containing each an agent to create a 
//     Triangle. 
//     These states are consecutive. One transition enables to progress
//     from one state to the following. 
//     The second transition leaves the second state and reaches the NULL
//     state to end the command. 
//     Undo/Redo is managed at local and global levels. 
//
//       +---------------------------+
//       !  CAADegCreateTriangleCmd  !   
//       +--------+------------------+
//                !   
//       +--------V------------------+
//       !  CAADegCreateTriangleCmd  !   
//       +--------+------------------+
//                !   
//                !   CreatePolyline
//                V
//               NULL
//
//
//===========================================================================
// DialogEngine Framework
#include "CATStateCommand.h"  // Needed to derive from CATStateCommand

// CAASystem.edu Framework
class CAAISysPolyline        ;   // Needed for the global Undo/Redo

class CAADegCreateTriangleCmd ;  // To create the triangle

// ApplicationFrame Framework
class CATLISTP(CATBaseUnknown) ;

class CAADegCreatePolylineBy2TrianglesCmd : public CATStateCommand
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAADegCreatePolylineBy2TrianglesCmd.CATNls
  //    
  // the beginning of the format of each line in the NLS file is :
  //
  //     CAADegCreatePolylineBy2TrianglesCmd.
  //
  CmdDeclareResource(CAADegCreatePolylineBy2TrianglesCmd,CATStateCommand);

  public :

    // Manage the lifecyle of the command
    CAADegCreatePolylineBy2TrianglesCmd();
    virtual ~CAADegCreatePolylineBy2TrianglesCmd();

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


    // CreatePolyline
    // ---------------
    // From the 2 triangles we have 6 points. The polyline is created from 
	// these 6 points.
    //
    CATBoolean  CreatePolyline(void * iUsefulData);

    // GetGlobalUndo 
    // -------------
    // Gives to the dialog engine the methods name to call for the
    // global Undo and Redo, and to release the Polyline. 
    //
    // To redefine to have Undo/Redo on the command. It is called 
    // just after the Cncel method of the command. UndoCreatePolyline, 
    // RedoCreatePolyline and DesallocatPolyline are static methods because
    // the command will be deleted.
    //
    CATCommandGlobalUndo * GetGlobalUndo();

    // DesallocatParent
    // ----------------
    // Static method called when Redo/Undo for it is no more possible.
    // You have staked more than 10 Undo/Redo, or the stack is unstaked, or
    // the model has been modified after the Redo.
    //
    static void             DesallocatPolyline(void * iUsefulData); 

    // UndoCreateParent  
    // -------------------
    // Static method called when the command is ended. 
    // Must undo the command so it removes the Polyline and the
	// the 2 triangles of the document
    //
    static void             UndoCreatePolyline(void * iUsefulData);
    
    // RedoCreateParent
    // ----------------
    // Static method called when the command is ended. 
    // Must redo the command so it adds the Polyline and the
	// the 2 triangles of the document
    static void             RedoCreatePolyline(void * iUsefulData); 
	
  private :


    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegCreatePolylineBy2TrianglesCmd(const CAADegCreatePolylineBy2TrianglesCmd &iObjectToCopy);

	// Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegCreatePolylineBy2TrianglesCmd & operator = (const CAADegCreatePolylineBy2TrianglesCmd &iObjectToCopy);


	// AddPoints
	// -----------
	// Gets the points of the triangle  to form the polyline
	//
	void AddPoints(CAAISysPolyline * piPolylineToCreate, CAAISysPolyline * piTriangle);

  private :

    //  Dialog agent to select Triangle 
    CAADegCreateTriangleCmd  * _pCmdTr2 ; 
	CAADegCreateTriangleCmd  * _pCmdTr1 ;


    // To create an element in a document
    CATBaseUnknown       * _pUIActiveObject ;      
    CATBaseUnknown       * _pContainer ;  


	// This list contains 3 objects to remove/add from the model
	//    - the polyline 
	//    - les 2 triangles
	// 
	CATLISTP(CATBaseUnknown) *  _pListeForUndoRedoElement  ;
};
#endif
