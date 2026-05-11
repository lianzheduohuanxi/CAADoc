#ifndef CAAVisBaseApplication_h
#define CAAVisBaseApplication_h

// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Sample demonstrating the basic Visualization functionnalities. These
//  functionnalities can be divided into two parts:
//
//  I. Visualizing graphical representations
//
//    - Creating a viewer into a document
//    - Creating graphical representations from an existing tessellation
//    - Managing levels of details for graphical representations on your own
//    - Adding a graphical representation to a viewer/viewpoint
//    - Creating a render
//    - Modifying the viewpoint.
//
//  II. Manipulating visualized graphical representations
//
//    - Attaching a manipulator to a graphical representation
//    - Manipulating graphical representations using manipulators
//    - Attaching an indicator to a viewer
//    - Activating the multiselection by trap selection
//    - Decoding information held by a manipulator's event.
//  
//===========================================================================
//  Usage:
//  ------
//
//  Type:
//    CAAVisBase
//
//  A frame with a menu bar is displayed. This
//  frame is a multi document frame. A default document
//  is opened: it displays a 3D viewer containing a 3D torus.
//
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Application class.
//
//  This is the main object in the process. It avoids writing a main function.
//  The event loop is managed automatically by deriving from 
//  CATInteractiveApplication. 
//  It contains the ignition and end steps.
//
//===========================================================================
//  Inheritance:
//  ------------
//           CAAVisBaseApplication
//             CATInteractiveApplication (Dialog Framework)
//               CATApplication (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  BeginApplication: Contains the whole application code.
//  EndApplication
//
//===========================================================================


//Dialog Framework
#include "CATInteractiveApplication.h"

//Visualization Framework
#include "list.h"

//Local Framework
class CAAVisBaseDocument; //Our documents base class
class CAAVisBaseApplicationFrame;

//Visualization Framework
class CAT3DBagRep;
class CAT3DManipulator;

class CAAVisBaseApplication : public CATInteractiveApplication
{
public:

  // Constructs the application
  CAAVisBaseApplication();
  
  virtual ~CAAVisBaseApplication();

  //Build and destroy the application
  virtual void BeginApplication();

  //Returns the application return code.
  virtual int EndApplication();

private:

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAVisBaseApplication(const CAAVisBaseApplication &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAVisBaseApplication & operator = (const CAAVisBaseApplication &iObjectToCopy);

  // Opens a new CAAVisBaseCGRDocument. The data
  // is read from the indicated CGR file.
  // Parameters
  //   iFileName
  //     The CGR file name.
  void OpenCGR(const char *iFileName);
  
  // Inserts a model in the active document.
  // Parameters
  //   iFileName
  //     The file name of the CGR file from
  //     which the model to insert is read.
  void InsertModel(const char *iFileName);
  
  // Renders the bounding boxes on the active
  // document's scene.
  // Parameters
  //   iTemChecked
  //     Indicates whether the "BE Render" check item
  //     was checked or unchecked.
  //     Legal values :
  //       0 Unchecked
  //       1 Checked
  void RenderBE(int iItemChecked);

  // Reframes the active document's viewpoint
  void Reframe();

  // Modifies the viewpoint parameters
  void ModifyViewpoint();

  // Adds or remove manipulator onto the active document's scene
  // Parameters
  //   iTemChecked
  //     Indicates whether we must
  //     add or remove manipulator
  //     Legal values :
  //       0 remove
  //       1 add
  void AddManipulator(int iItemChecked);

  // Called when the Exit is asked.
  // Deletes all elements manipulated in this application
  //
  void DestroyApplicationObjects();

  // Creates the frame's layout:
  // - A menu bar:
  //     - A File menu
  //     - A Render menu
  //     - A Viewpoint menu
  void CreateLayout();
  
  // Multi Documents related callback
  void AddMDICallbacks(CAAVisBaseDocument *iDocument);

  //Removes callbacks added.
  void RemoveMDICallbacks(CAAVisBaseDocument *iDocument);

  // Multi Documents related callback
  void WindowMDICB(CATCallbackEvent   iEvent,
                   void              *iPublisher,
                   CATNotification   *iNotification,
                   CATSubscriberData  iData,
                   CATCallback        iCallbackId);

  //When a window is activated.
  void OnWindowActivated(CAAVisBaseDocument *iDocument);

  //Warns the application that a window
  //is being closed. The associated document
  //must be deleted.
  void OnDeleteWindow(CAAVisBaseDocument *iDocument);

  //Inserts a graphical representation read from a CGR file into
  //the active document.
  void InsertCB         (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);

  //Opens a CGR file in a new document.
  void OpenCB           (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);

  //Renders the bounding boxes on the active document's scene.
  void RenderBECB       (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);

  //Reframes the active document's scene.
  void ReframeCB        (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);

  //Modifies the active document's main 3D viewpoint parameters, thanks to a dialog box.
  void ModifyViewpointCB(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);

  //To exit the application
  void ExitCB           (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);

  //When the viewpoint is modified through the CAAVisBaseViewpointDlg dialog box
  void NewViewpointCB   (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);

  //When the "Manipulator" push item is activated:
  void ManipulatorCB    (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);

  //When the manipulator is manipulated
  void OnManipulateCB   (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);
  
  //VisuObjects creation
  void CreateObjectCB   (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);
  
private:

  //Frame 
  CAAVisBaseApplicationFrame *_pApplicationFrame;

  //Pointer to the current active document
  CAAVisBaseDocument *_pActiveDoc;
  
  //Opened documents list
  list<CAAVisBaseDocument> _Documents;
  
  //Active document index
  int _ActiveDocIndex;
  
  //List of bag reps containing the bounding boxes
  //of every opened documents
  list<CAT3DBagRep> _BoxesBags;

  //Manipulators. One potential manipulator by opened
  //document.
  list<CAT3DManipulator> _Manipulators;
  
};

#endif
