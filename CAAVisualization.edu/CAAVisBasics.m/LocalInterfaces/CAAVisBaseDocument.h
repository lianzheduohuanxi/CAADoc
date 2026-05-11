#ifndef CAAVisBaseDocument_h
#define CAAVisBaseDocument_h

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Document base class.
//  Each document of our application inherits from CAAVisBaseDocument.
//  The documents are created by the application (CAAVisBaseApplication).
//  Each document has an associated view (CAAVisBaseView) to graphically display
//  its data.
//  The main role of the document is to manage our model, which is a tree
//  of CATRep objects, stored as a CAT3DBagRep * _pRootContainer data member.
//
//===========================================================================
//  Inheritance:
//  ------------
//           CAAVisBaseDocument
//             CATBaseUnknown (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  CreateDocView : Creates the document view (CAAVisBaseView).
//
//  DeleteDocView : Deletes the document view.
//
//  CreateModel   : Creates the model, which is in fact a graphical
//                  representation, that will be visualized in the view.
//
//  DeleteModel   : Deallocates resources used for the model.
//
//  AddRepToViewer: Adds our graphical representation to the viewer.
//                  This method allows our model to be represented in the view.
//
//===========================================================================

//System Framework
#include "CATBaseUnknown.h"

//Local Framework
class CAAVisBaseView;

//Visualization Framework
class CAT3DBagRep;

//Dialog Framework
class CATDialog;

//System Framework
class CATCommand;

class CAAVisBaseDocument : public CATBaseUnknown
{
public:

  // Constructs the document from the application, the parent
  // dialog object (the main frame), and a title.
  // Parameters
  //   iDialogParent
  //     The parent dialog object. Here, it is the view
  //     of our application, the application frame.
  //   iDocumentName
  //     The document name.
  CAAVisBaseDocument(CATDialog *iDialogParent,
                     const char *iDocumentName);

  //destructor
  virtual ~CAAVisBaseDocument();

  // Gets the view associated to the document. There is
  // only one view per document.
  virtual CAAVisBaseView * GetView();

  //Gets the root container of the representation.
  CAT3DBagRep * GetModel();

  //Inserts a graphical representation read from a CGR file
  //into the model.
  virtual void InsertModel(const char *iCGRFileName);

protected:
  
  // Adds our model's graphical representation into the
  // view.
  virtual void AddRepToViewer();

  // Creates the model. This method depends on the kind of document we're
  // dealing with, and must be overridden by inherited class.
  // Anyway, the created model will remain persistent thanks to the
  // <tt>_pRootContainer</tt> data member.
  virtual void CreateModel() = 0;

  // Deletes the model associated to our document, and
  // stored in <tt>_pRootContainer</tt>.
  virtual void DeleteModel();

private:

  //Default constructor
  CAAVisBaseDocument();

  //Copy constructor
  CAAVisBaseDocument(const CAAVisBaseDocument &iBrother);

  //Assignment operator
  CAAVisBaseDocument & operator = (const CAAVisBaseDocument &iBrother);

  // Creates the view (dialog object), associated to the document.
  // Parameters
  //   iDialogParent
  //     The parent dialog object, which is the view object parent. Here,
  //     it is the application frame.
  //   iDocViewName
  //     The name given to the document's view. This is the name which will
  //     appear on top of the window.
  virtual void CreateDocView(CATDialog *iDialogParent, const char *iDocViewName);
  
protected:

  // Document's view
  CAAVisBaseView *_pView;

  // Model.
  CAT3DBagRep    *_pRootContainer;

  //View name
  static int      _ViewName;
};

#endif
