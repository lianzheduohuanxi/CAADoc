#ifndef CAADegClippingBySphereCmd_h
#define CAADegClippingBySphereCmd_h

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
//  State command which 
//
//  Illustrates:
//
//     - Creation of a State command
//     - Use of a CATPathElementAgent 
//     - Use acquisition filter 
//     - Undo/Redo management
//          
//  Usage:
//
//     Select a point
//     Select a second point ==>
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
//       !  CenterPathAgent  !   
//       +--------+---------+
//                !   
//       +--------V---------+
//       !  RadiusPathAgent  !   
//       +--------+---------+
//                !   Clipped the element out the sphere 
//                V
//               NULL
//
//===========================================================================
// DialogEngine Framework
#include "CATStateCommand.h"  // Needed to derive from CATStateCommand

// Mathematics Framework
#include "CATMathPoint.h"

// Visualization Framework
#include "CAT3DBoundingSphere.h"
class CAT3DRep ;

// ApplicationFrame framework
class CATLISTP(CATBaseUnknown);

// DialogEngine Framework
class CATPathElementAgent ;   // Acquisition agent
class CAAISysCollection ;     // To keep the clipped element

class CAADegClippingBySphereCmd : public CATStateCommand
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAADegClippingBySphereCmd.CATNls
  //    
  // the beginning of the format of each line in the NLS file is :
  //
  //     CAADegClippingBySphereCmd.
  //
  CmdDeclareResource(CAADegClippingBySphereCmd,CATStateCommand);

  public :

    // Manage the lifecyle of the command
    CAADegClippingBySphereCmd();
    virtual ~CAADegClippingBySphereCmd();

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

    // ClippingBySphereTheModel
    // ----------
    // 
    CATBoolean  ClippingBySphereTheModel(void * iUsefulData);


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

    // DesallocatListOfDeletedElement
    // ------------------------------
    // Static method called when Redo/Undo for it is no more possible.
    // You have staked more than 10 Undo/Redo, or the stack is unstaked, or
    // the model has been modified after the Redo.
    //
    static void             DesallocatListOfDeletedElement(void * iUsefulData); 

    // UndoClippingBySphereTheModel  
    // -------------------
    // Static method called when the command is ended. 
    // Must undo the command so it removes the triangle of the document
    //
    static void             UndoClippingBySphereTheModel(void * iUsefulData);
    
    // RedoClippingBySphereTheModel
    // ----------------
    // Static method called when the command is ended. 
    // Must redo the command so it adds the triangle into the document
    //
    static void             RedoClippingBySphereTheModel(void * iUsefulData); 

	// TestRadiusPoint
    // ----------------
	// Filter to test the point which gives the radius 
	// of the clipping bounding sphere
	//
	CATBoolean              TestRadiusPoint( CATDialogAgent * iAgent, void *iUsefulData);

  private :

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegClippingBySphereCmd(const CAADegClippingBySphereCmd &iObjectToCopy);

	HRESULT Get3DRep(CATBaseUnknown *iObject, CAT3DRep ** oRep);

	CATBoolean IsElementInSphere(CATMathPoint & iClippingSphereCenter,
								double iClippingSphereRadius,
								CAT3DBoundingSphere &  iElementBoundingSphere);

	CATBoolean ClippingModel(CATMathPoint & iCenter,CATMathPoint & iRadius ) ;
													
  private :

    //  Dialog agent to select points 
    CATPathElementAgent  * _daCenterPathElement ;   
    CATPathElementAgent  * _daRadiusPathElement ;   

    // Each element of the model are kept in this container
	// the first elt is the UIactive object. 
    CAAISysCollection    * _pICollectionModelContainer ;  

    // The List of clipped element , clipped in the ClippingBySphereTheModel are kept 
	// for the global Undo/Redo.
    // With this value it's possible to readd it from the document (Undo),
    // or to remove back it (Redo)
    // 
    //
    CATLISTP(CATBaseUnknown) *  _pListeForClippedElement  ;
};
#endif
