#ifndef CAAVisBaseView_h
#define CAAVisBaseView_h

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Document view class.
//
//  This is a dialog object, which contains a viewer in which
//  every 3D graphical representations are displayed.
//  
//===========================================================================
//  Inheritance:
//  ------------
//           CAAVisBaseView
//             CATDlgDialog (Dialog Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  CreateViewer: creates the viewer in which the 3D scene is dispayed.
//
//  Add3DRep    : to visualize in the viewer the CAT3DRep given as an argument.
//
//===========================================================================

//Dialog Framework
#include "CATDlgDialog.h"

//Visulization Framework
class CATNavigation3DViewer;
class CAT3DRep;
class CATViewer;
class CATDlgDocument ;

class CAAVisBaseView : public CATDlgDialog
{
  
public:

  CATDeclareCBEvent(WINDOW_ACTIVATED);
  CATDeclareCBEvent(WINDOW_DELETED);
       
  // Constructs a view of a document, from a dialog object parent,
  // a name, and the style wanted for the window.
  // Parameters
  //   iParent
  //     The dialog parent of the window. Here, it is
  //     the main frame of the application.
  //   iName
  //     The name of the view. It appears on the top
  //     of the window.

  CAAVisBaseView(CATDialog *iDialogParent,
                 CATBaseUnknown *iDocument, 
                 const char *iName ) ;

  virtual ~CAAVisBaseView();

  // Adds a 3D representation into the viewer, so that it could
  // be visualized.
  // Parameters
  //   iRoot
  //     The CAT3DRep to add.
  void Add3DRep(CAT3DRep *iRoot);

  // Gets a pointer onto the 3D viewer which remains into the window.
  CATViewer * GetViewer();

  //Gets the document
  CATBaseUnknown * GetDocument();
  
  // Constructs The 3D Viewer 
  void Build();

private:

  //Default constructor
  CAAVisBaseView();

  //Copy constructor
  CAAVisBaseView(const CAAVisBaseView &iBrother);
  
  //Assignment constructor
  CAAVisBaseView & operator = (const CAAVisBaseView &iBrother);

  // Creates the viewer associated to the window, in which every 3D objects
  // are displayed.
  void CreateViewer();

  // Deletes the document's view.
  void DeleteView();

  // Adds callbacks, dealing with the multi documents configuration,
  // to the document's view on these events:
  // - The window closing
  // - The window activation
  // - The window maximization
  // - The window minimization
  // - The window restoration
  void AddMDICallbacks();
  
  //The Callback managing the multi documents configuration events.
  void MDICB(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);

  //Warns other objects that the window has beem activated.
  void OnWindowActivated();
  
private:

  //The viewer in which the 3D scene is visualized
  CATNavigation3DViewer *_pViewer;

  //Keeps a pointer on the associated document
  CATBaseUnknown *_pDocument;

  // The CATDlgDocument with the MDI style
  CATDlgDocument * _pDlgDocument ;

};
#endif
