#ifndef CAAVisBaseApplicationFrame_h
#define CAAVisBaseApplicationFrame_h

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
// Frame of the application.
// This frame is made with a menu bar, itself made with
// a file menu, a render menu, a viewpoint menu, a manipulator menu.
//
//===========================================================================
//  Inheritance:
//  ------------
//           CAAVisBaseApplicationFrame
//             CATDlgDocument (Dialog Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//
//===========================================================================

#include "CATDlgDocument.h"

//Dialog Framework
class CATDlgFile;
class CATDlgCheckItem;

class CAAVisBaseApplicationFrame : public CATDlgDocument
{
  // Declares the CAAVisBaseApplicationFrame.CATNls file as the dialog message catalog
  DeclareResource(CAAVisBaseApplicationFrame, CATDlgDocument)
    
public:
  
  // Constructs the application frame from the main application and
  // a title
  //   Parameters
  //     iParent
  //       The parent class in the CATCommand agregation 
  //       hierarchy. Here, our main application.
  //     iDialogObjectName
  //       The dialog object name. 
  //     iStyle
  //       The application window style.
  CAAVisBaseApplicationFrame(CATInteractiveApplication *iParent, 
                             const CATString &iDialogObjectName, 
                             CATDlgStyle iStyle = CATDlgWndFrameMDI|CATDlgShow);

  //Destructor
  virtual ~CAAVisBaseApplicationFrame();

  // Builds the frame, with all its dialog components:
  // - A menu bar:
  //     - A File menu
  //     - A Render menu
  //     - A Viewpoint menu
  void Build();

  //When a window is activated.
  void OnWindowActivated(int iActiveDocIndex);

  //Warns the frame that a window
  //is being closed. The associated
  //layout's elements must be updated.
  void OnDeleteWindow(int iActiveDocIndex);


private:

  //Default constructor
  CAAVisBaseApplicationFrame();

  //Copy constructor
  CAAVisBaseApplicationFrame(const CAAVisBaseApplicationFrame &iBrother);
  
  //Assignment operator
  CAAVisBaseApplicationFrame & operator = (const CAAVisBaseApplicationFrame &iBrother);

  //Layout's Callbacks
  //
  //Opens a CGR file in a new document.
  void OpenCB           (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);
  void LoadOKCB         (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);
  void LoadCANCELCB     (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);
  //Inserts a graphical representation read from a CGR file into
  //the active document.
  void InsertCB         (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);
  void InsertOKCB       (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);
  //To exit the application
  void ExitCB           (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);
  //Renders the bounding boxes on the active document's scene.
  void RenderBECB       (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);
  //Reframes the active document's scene.
  void ReframeCB        (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);
  //Modifies the active document's main 3D viewpoint parameters, thanks to a dialog box.
  void ModifyViewpointCB(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);
  //Adds a manipulator to the active document's representation
  void ManipulatorCB    (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);
  //Creates a specific visualization object
  void CreateVisuObjectCB(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);

private:

  //Layout's dialog elements
  //We need to store the check items dialog object.
  //Indeed, we have to keep track of their states for each document.
  CATDlgCheckItem *_pRenderBEChkItem;
  CATDlgCheckItem *_pManipulatorChkItem;
  
  //The file selector box must also br stored
  CATDlgFile *_pFileSelectorBox;
  
  //Array to store the _RenderBEChkItem check item state for
  //each opened document
  int *_aBEStates;
  int _BEStatesArraySize;

  //Array to store the _RenderBEChkItem check item state for
  //each opened document
  int * _aManipulatorStates;
  int _ManipulatorStatesArraySize;

  //Keeps track of the number of opened documents:
  int _NumberOfDocuments;

  //Keeps track of the current active document index:
  int _ActiveDocIndex;

  //Pointer on the parent application:
  CATInteractiveApplication *_pApplication;
};

#endif
