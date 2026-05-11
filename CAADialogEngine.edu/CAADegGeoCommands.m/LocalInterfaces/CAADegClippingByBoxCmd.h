#ifndef CAADegClippingByBoxCmd_h
#define CAADegClippingByBoxCmd_h

// COPYRIGHT DASSAULT SYSTEMES 2004

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
//  State command which deletes the objects (only points) of the document which 
//  are not into a bounding box defined by the end user. 
//
//  Illustrates:
//
//     - Creation of a state command
//     - Use of CATPathElementAgent and CATIndicationAgent
//     - Creation of temporary objects, three cases of component:
//         - an instance of CATModelFor3DRep
//            for a component just visualizable
//
//         - a component which derives from CATModelFor3DRep 
//            for a component easily selectable with a specific interface
//             
//         - a component implementing CATI3DGeoVisu
//            for a component whose the graphic representation is modified 
//            during the command
//
//     - Usage of the CATISO (furtive or not) to display temporary objects
//          
//  Usage:
//
//     Select a point: The point is the center of the bounding box.
//     Move the mouse => Temporary bounding box appears 
//     Click in the background => The final bounding box dimension is defined
//                                and all points outside this box are deleted
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
// local Framework
class CAADegTemporaryText ;   


// CAAVisualization.edu Framework
class CAAIVisTextModel ;      // Interface to handle a temporary object 
class CAAIVisWireBox ;        // Interface to handle a temporary object 

//DialogEngine Framework
#include "CATStateCommand.h"  // Needed to derive from CATStateCommand

//Mathematics Framework
#include "CATMathPoint.h"     
#include "CATMathPoint2D.h"   

// ApplicationFrame Framework
class CATISO ;                // Needed to visualize the center box/bounding box

//DialogEngine Framework
class CATIndicationAgent ;    // Dialog agent to end the bounding box
class CATPathElementAgent ;   // Dialog agent to select the center box

// Visualization Framework
class CATModelForRep3D ;      // Needed to create temporary objects
class CAT3DCustomRep ;        // Graphic representation used to visualize temp. obj.

// System Framework
#include "CATBoolean.h"

class CAADegClippingByBoxCmd : public CATStateCommand
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAADegClippingByBoxCmd.CATNls 
  CmdDeclareResource(CAADegClippingByBoxCmd,CATStateCommand);

  public :

    // Manages the lifecyle of the command.
    //
    CAADegClippingByBoxCmd();
    virtual ~CAADegClippingByBoxCmd();  

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

    // Do/Undo/Redo action methods to select the center box
    // --------------------------------------------------------
    //  -CreateCenterBox calls CreateRepForCenterBox to create the graphic 
    //                   representation (rep) associated with the center box. 
    //                   It is three fixed arrow graphic primitives. _pCenterBoxModel, 
    //                   the center box component is set in the ISO
    //
    //  -UndoCreateCenterBox removes from the ISO the center box component. Its
    //                       rep is automatically destroyed. It also removes
    //                       the bounding box which already exist.
    //
    //  -RedoCreateCenterBox calls back CreateRepForCenterBox to re-create a rep
    //                         for the center box, and sets it back in the ISO
    //
    CATBoolean  CreateCenterBox(void * iUsefulData);
    CATBoolean  UndoCreateCenterBox(void * iUsefulData);
    CATBoolean  RedoCreateCenterBox(void * iUsefulData);

    // CreateRepForCenterBox
    // ---------------------
    // Creates a CAT3DCustomRep and three CAT3DFixedArrowGP. The color of
    // these arrows are defined by the current color in the combo set in the
    // "Tools Palette" toolbar. See CAAApplicationFrame.edu FW and its 
    // CAAAfrPaletteOptions.m module.
    // 
    HRESULT     CreateRepForCenterBox() ;

    // UpdateClippingBox
    // -----------------
    // Action method of the transition to create the bounding box.
    // If _FirstTime is TRUE the CreateRepForBox is called otherwise
    // UpdateRepForBox is called.
    //
    CATBoolean  UpdateClippingBox(void * iUsefulData);

    // CreateRepForText
    // ----------------
    // This method is called once during the command, at the first activation 
    // of the command. It enables us to create the graphic representation 
    // which has a text as graphic primitive. 
    // 
    HRESULT     CreateRepForText();


    // Do/Undo/Redo action methods to select the Text
    // --------------------------------------------------------
    // 
    CATBoolean  DisplayDialogBox(void * iUsefulData);
    CATBoolean  UndoSelText(void * iUsefulData);
    CATBoolean  RedoSelText(void * iUsefulData);


    // ClippingByBox
    // -------------
    // The last action method to delete the objects outside the bounding box.
    // 
    CATBoolean  ClippingByBox   (void * iUsefulData);

  private :

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegClippingByBoxCmd(const CAADegClippingByBoxCmd &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegClippingByBoxCmd & operator = (const CAADegClippingByBoxCmd &iObjectToCopy);

  private :

    // Dialog Agent
    CATIndicationAgent  * _daIndication ; 
    CATPathElementAgent * _daForBoxCenter ;
    CATPathElementAgent * _daTextSel ;

    // Values to manage the rectangle
    CATMathPoint          _CenterBox;
 
    // Interactive Set of Objects and Set of Highlighted Objects
    CATISO              * _pISO ;
    CATISO              * _pFurtiveISO ;

    // Temporary object to visualize the center of the box
    // The component is created in the constructor class, 
    // and its graphic representations is created into
    // the action method (CreateCenterBox) depending on 
    // the selected point (_daForBoxCenter)
    //
    CATModelForRep3D    * _pCenterBoxModel ;

    // Temporary object to visualize the box itself
    // The component is created in the constructor class
    // This component implements CATI3DGeoVisu which 
    // builds the graphic representation, when the component
    // is set or updated in the ISO.
    //
    CAAIVisWireBox      * _pIWireBox ;

    // Temporary object to visualize a text. 
    // The component is created in the constructor class, and 
    // displayed in the first activation of the command. This text
    // must be selected by the end user to follow up the command.
    // This temporary object is a text ("ISO Selection")
    // displayed in (0,0,0) of the model.
    //
    CAAIVisTextModel    * _pITextToSelectModel ;

    // To manage the temporary bouding box dimension
    CATMathPoint2D        _PreviousPointInScreenPlane ;
    CATBoolean            _FirstTime ;
    CATBoolean            _CenterBoxModelToRestore ;
    CATBoolean            _TextModelToRestore ;


    // To work with the CAAGeometry document
    CATBaseUnknown      * _pUIActiveObject ; 
    CATBaseUnknown      * _pContainer  ; 

};
#endif
