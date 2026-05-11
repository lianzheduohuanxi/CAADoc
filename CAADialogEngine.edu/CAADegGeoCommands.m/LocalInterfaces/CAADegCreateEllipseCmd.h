#ifndef CAADegCreateEllipseCmd_h
#define CAADegCreateEllipseCmd_h

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
//  State command which creates an ellipse from a selected plane, an indication
//  for the center and radius values entered in a dialog box.
//
//  Illustrates:
//
//     - Creation of a State command
//     - Use of CATPathElementAgent and CATIndicationAgent 
//     - Use of a Camera
//     - Use of the CATCSO (Set of Current Objects)
//     - Use of a dialog which does not have effect upon the dialog.
//
//  Usage:
//     S
//     the center indication.
//     Select a plane ==> The viewpoint is modified. 
//     Click in the background ==> A temporary point is created for the 
//                                 ellipse center
//     Moreover, a dialog box enables to enter the two radius at any moment
//     before the circle indication (so either before or after the plane 
//     selection).
//     As soon as the center is indicated, an ellipse is created with the 
//     radius values from the dialog box. If you haven't entered such values,
//     default values (1,1) are taken instead.
//     The ellipse becomes the current selected object.
// 
//  Graph:
//     Is composed of 2 states:
//       * stGetPlane containing one agent
//         - a CATPathElementAgent to react to plane selection
//       * stGetEllipse containing one agent
//         - a CATIndicationAgent to react to indication
//
//      These states are consecutive. The first transition enables to progress
//      from the frist state to the second one. 
//      The last transition leaves the stGetEllipse and reaches the NULL
//      state to end the command. 
//
//       +------------------+
//       ! PlanePathAgent   !   
//       +--------+---------+
//                !   CreateCamera 
//       +--------V---------+
//       ! CenterIndicAgent !   
//       +--------+---------+
//                !   CreateEllipse
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
//  BuilGraph    :Implements the statechart
//  CreateCamera :Changes the viewpoint to make the selected plane and the 
//                 screen plane coincide.
//  CreateEllipse:Creates the ellipse.
//
//===========================================================================
// DialogEngine Framework
#include "CATStateCommand.h"  //Needed to derive from CATStateCommand

// Mathematics Framework
#include "CATMathPoint.h"     //Needed by NewEllispe
#include "CATMathPlane.h"     //Needed to the plane projection

// DialogEngine Framework
class CATPathElementAgent ;   //Needed to get the plane
class CATIndicationAgent ;    //Needed to get the center ellipse

// Local Framework
class CAADegRadiusEllipseEditor ;//The dialog box to edit radius

class CAADegCreateEllipseCmd : public CATStateCommand
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAADegCreateEllipseCmd.CATNls 
  //    
  // the beginning of the format of each line in the NLS file is :
  //
  //     CAADegCreateEllipseCmd.
  //
  CmdDeclareResource(CAADegCreateEllipseCmd,CATStateCommand);

  public :

    // Manage the lifecyle of the command
    //
    CAADegCreateEllipseCmd();
    virtual ~CAADegCreateEllipseCmd(); 

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
    // It is called once, even if the command is in repeat mode
    // 
    virtual void BuildGraph() ;

    // CreateCamera
    // -----------
    // Retrieves  the CATMathPlane from the selected plane, and sets 
    // the projection plane for the indicator agent. Changes the viewpoint
    // to make the selected plane and the screen plane coincide.
    //
    CATBoolean  CreateCamera(void * iUsefulData);

    // CreateEllipse
    // -------------
    // Calls NewEllipse with the selected point as center.  
    //
    CATBoolean  CreateEllipse(void * iUsefulData);

  private :

    // Creates ellipse in the document 
    void        NewEllipse(const CATMathPoint iCenter,
                           const float        iUvalues, 
                           const float        iVvalues);

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegCreateEllipseCmd(const CAADegCreateEllipseCmd &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegCreateEllipseCmd & operator = (const CAADegCreateEllipseCmd &iObjectToCopy);

  private :

    // Dialog Agent
    CATPathElementAgent            * _daPathEltPlane        ; 
    CATIndicationAgent             * _daIndicEllipseCenter  ; 

    // Dialog box to get the large and small radius 
    CAADegRadiusEllipseEditor      * _pRadiusEditor ;

    // The plane projection
    CATMathPlane                     _ProjPlane       ;   

    // To create elements in the document
    CATBaseUnknown                 * _pUIActiveObject ;      
    CATBaseUnknown                 * _pContainer ;   

};
#endif
