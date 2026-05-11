#ifndef CAAVisBaseVisuObjectDocument_h
#define CAAVisBaseVisuObjectDocument_h

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  CGR Document class.
//  When opening a CGR file, this document is created to manage the
//  model read from this file.
//  It inherits from CAAVisBaseDocument, so, it also have
//  an associated view.
//
//===========================================================================
//  Inheritance:
//  ------------
//           CAAVisBaseVisuObjectDocument 
//             CAAVisBaseDocument
//               CATCommand (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  CreateModel   : Creates the model, which is in fact a graphical
//                  representation, that will be visualized in the view.
//                  The creation of the model is here reduced to the
//                  reading of the CGR file.
//
//  OpenCGR       : The effective reading of the CGR file.
//
//===========================================================================

//Local Framework
#include "CAAVisBaseDocument.h"
#include "CAAVisObjectType.h"

class CATSurfacicRep;

class CAAVisBaseVisuObjectDocument : public CAAVisBaseDocument
{
public:

  // Constructs the document from a CGR file name, an application,
  // a dialog parent and a title.
  // Parameters
  //   iFileName
  //     The name of the CGR file to read.
  //   iDialogParent
  //     The dialog parent. Here, the application frame.
  //   iDocumentName
  //     The name given to the opened document.
  CAAVisBaseVisuObjectDocument( CAAVisObjectType iObjectType,
                                CATDialog  *iDialogParent,
                                const char *iDocumentName);

  //destructor
  virtual ~CAAVisBaseVisuObjectDocument();

  //Creates the model. Here, it is just a call to OpenCGR.
  virtual void CreateModel();

protected:

   CATSurfacicRep * CreateSurfacicRep();

private:

  //Default constructor
  CAAVisBaseVisuObjectDocument();

  //Copy constructor
  CAAVisBaseVisuObjectDocument(const CAAVisBaseVisuObjectDocument &iBrother);
  
  //Assignment operator
  CAAVisBaseVisuObjectDocument & operator = (const CAAVisBaseVisuObjectDocument &iBrother);
  
private:

  // Type of object to create
  CAAVisObjectType _objectType;
};

#endif
