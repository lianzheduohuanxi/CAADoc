#ifndef CAAVisBaseCGRDocument_h
#define CAAVisBaseCGRDocument_h

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
//           CAAVisBaseCGRDocument 
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


class CAAVisBaseCGRDocument : public CAAVisBaseDocument
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
  CAAVisBaseCGRDocument(const char *iFileName,
                        CATDialog  *iDialogParent,
                        const char *iDocumentName);

  //destructor
  virtual ~CAAVisBaseCGRDocument();

  //Creates the model. Here, it is just a call to OpenCGR.
  virtual void CreateModel();

  // Opens a CGR file and extracts the graphical representation
  // stored in it. This graphical representation is our document's model.
  // Parameters
  //   iFileName
  //     The name of the CGR file to load.
  void OpenCGR(const char *iFileName);

private:

  //Default constructor
  CAAVisBaseCGRDocument();

  //Copy constructor
  CAAVisBaseCGRDocument(const CAAVisBaseCGRDocument &iBrother);
  
  //Assignment operator
  CAAVisBaseCGRDocument & operator = (const CAAVisBaseCGRDocument &iBrother);
  
private:

  char *_pFileToOpen;
};

#endif
