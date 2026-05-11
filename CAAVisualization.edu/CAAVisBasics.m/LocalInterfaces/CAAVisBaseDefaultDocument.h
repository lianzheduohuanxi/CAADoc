#ifndef CAAVisBaseDefaultDocument_h
#define CAAVisBaseDefaultDocument_h

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Default document class.
//  At the launching of the application, a default document
//  containing the representation of a torus is opened. This class
//  represents this document. Its CreateModel method illustrates
//  the way to build a graphical representation and to deal with the
//  corresponding Level Of Details creation.
//
//===========================================================================
//  Inheritance:
//  ------------
//           CAAVisBaseDefaultDocument
//             CAAVisBaseDocument
//               CATCommand (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  CreateModel   : Creates the torus model.
//
//  AddLod        : Adding of a Level Of Detail to the model.
//
//===========================================================================

//Loacl Framework
#include "CAAVisBaseDocument.h"

//Visualization Framework
class CAT3DLodRep;

class CAAVisBaseDefaultDocument : public CAAVisBaseDocument
{
public:

  // Constructs the document from the parent application, the parent dialog and a title.
  // Parameters
  //   iDialogParent
  //     The dialog parent. Here, the application frame.
  //   iDocumentname
  //     The document's name.
  CAAVisBaseDefaultDocument(CATDialog  *iDialogParent,
                            const char *iDocumentName);

  //destructor
  virtual ~CAAVisBaseDefaultDocument();

protected:

  //Creates the torus model.
  virtual void CreateModel();

private:

  //Defult constructor
  CAAVisBaseDefaultDocument();

  //Copy constructor
  CAAVisBaseDefaultDocument(const CAAVisBaseDefaultDocument &iBrother);
  
  //Assignment operator 
  CAAVisBaseDefaultDocument & operator = (const CAAVisBaseDefaultDocument &iBrother);
  
  //Adds a Level Of Details to the model.
  void AddLOD(float iSag, int *iColor);
  
  
private:

  CAT3DLodRep *_pTorus;
};

#endif
