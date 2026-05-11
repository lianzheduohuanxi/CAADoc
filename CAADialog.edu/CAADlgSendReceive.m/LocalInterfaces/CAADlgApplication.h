#ifndef CAADlgApplication_H
#define CAADlgApplication_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//==============================================================================
//  Abstract of the sample:
//  ----------------------
//
//  This sample program illustrates the Send/Receive mechanism.
//  It shows:
//   
//    - How commands deal with events using notifications
//    - How to create, send and analyze notifications
//    - A command that takes and releases the focus
//    - The path of a notification 
//   
//==============================================================================
//  How to launch:
//  -------------
//
//  Type: CAADlgSendReceive
//
//==============================================================================
//  Abstract of the class:
//  ---------------------
//   
//  The CAADlgApplication class runs the sample scenario using its
//  BeginApplication method. The scenario uses the following classes:
//
//  - A container (CAADlgContainer) that contains a model (CAADlgModel)
//    that in turn contains elements (CAADlgElement)
//  - Two views to draw the model:
//    - A screen view (CAADlgViewScreen) 
//    - A plotted view (CAADlgViewPlot)
//  - Three notifications that each represents an event type:
//    - An element is added to the model (CAADlgAddNotification)
//    - An element is removed from the model (CAADlgRemoveNotification)
//    - An error has occurred (CAADlgErrorNotification). For example, an error
//      notification is sent when the application requests to remove an
//      element that doesn't any longer exist in the model
//
//  Container, model, and view classes derive from CATCommand to take advantage
//  of the Send/Receive mechanism. The container is the command parent of the
//  model. No parent is explicitely assigned to other commands, meaning that
//  this parent is the command selector. The command tree structure is
//  as follows: 
//
//             CATCommandSelector
//                /          \
//               /            \             
//     CAADlgContainer       CAADlgViewScreen (active command)
//             /             CAADlgViewPlotter
//            / 
//    CAADlgModel
//
//  The sample scenario is as follows:
//  First the views, the container, and the model are instantiated. Then
//  elements are created and the screen takes the focus. A line and a point are
//  added to the model, and the line is removed from the model. For each added
//  or removed element, the model sends a notification.
//
//             CATCommandSelector
//                /    ^     \  4
//               /     ^      \ v            
//     CAADlgContainer ^     CAADlgViewScreen (active command)
//          ^  / 2     ^     CAADlgViewPlotter
//          1 /  v     3
//      CAADlgModel
//  
//  A- Let's detail what's happen when an element is added to or removed from
//     the model 
//     1 The model sends a notification to its parent: the container 
//     2 The container informs the model that is is not interested with this
//       notification
//     3 The model resends the notification to the container's parent, that is,
//       the command selector
//     4 The command selector resends the notification to the active command,
//       namely the screen.
//       The screen is interested with the notification and requests the
//       sending command to send a pointer to the object involved in the
//       notifiation creation. This is requested using the SendObject method
//       that calls the SendCommandSpecificObject method redefined by the model
//
//  The plotter takes the focus, and becomes the active command in place
//  of the view. Elements are added and removed, and everthing happens as
//  above.
//
//  B- When an error occurs, an error notification is sent. Error
//     notifications are is caught by the container that requests the model
//     to stop the notification propagation. The active command is then never
//     informed of errors, since error notifications cannot reach it. 
//  
//
//==============================================================================
//  Inheritance:
//  ------------
//           CATInteractiveApplication (Dialog Framework)
//              CATApplication (System Framework)
//
//==============================================================================
//  Main Method:
//  ------------
//
//  BeginApplication: Contains the whole application code.
//
//
//==============================================================================

// Dialog Framework
#include "CATInteractiveApplication.h"

class CAADlgApplication: public CATInteractiveApplication 
{
  public:
   /*
    * Constructor. No initialization is actually done in it.
    * The real initialization is done in the BeginApplication method.
    */
    CAADlgApplication();
    virtual ~CAADlgApplication();

   /*
    * Initializes the Application. 
    */
    void BeginApplication();

   /*
    * Returns the application return code.
    */
    int EndApplication();
  
  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgApplication(const CAADlgApplication &iObjectToCopy);
  
    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgApplication & operator = (const CAADlgApplication &iObjectToCopy);
  
  private:

    CATCommand * _pCommandWithFocus;
};

#endif
