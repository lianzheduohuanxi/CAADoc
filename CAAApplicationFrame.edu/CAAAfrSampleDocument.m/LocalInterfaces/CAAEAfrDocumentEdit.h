#ifndef CAAEAfrDocumentEdit_H
#define CAAEAfrDocumentEdit_H

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Application using a new document type (CAASample).
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Class which implements the CATIDocumentEdit interface of a new document
//  type (CAASample)
//  It is a data extension of a late type (CAADoc) which is the document 
//  suffix. 
//
//  Illustrates:
//     - implementation of the CATIDocumentEdit to define a new document
//       type
//     - Creation of non standard main window composed of three viewers.
//
//===========================================================================
//  Usage:
//  ------
//  Launch CATIA V5, File/New. In the Dialog Box the new document type  
//  appears.
//  
//===========================================================================
//  Inheritance:
//  ------------
//         CATBaseUnknown (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  CreateDefaultWindow  
//  GetActiveObject
//
//===========================================================================
// System Framework
#include "CATBaseUnknown.h"   // Needed to derive from CATBaseUnknown

// Visualization Framework
#include "CATPathElement.h"   // Needed by GetActiveObject 

// ApplicationFrame Framework
class CATFrmWindow ;          // Needed by CreateDefaultWindow 
class CATFrmEditor ;          // Needed by CreateDefaultWindow 

  
class CAAEAfrDocumentEdit: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAEAfrDocumentEdit();
    virtual ~CAAEAfrDocumentEdit();

    // CreateDefaultWindow
    // -------------------
    // Creates the window dedicated to display and manipulate the document.
    //
    // This method is called by the File->New and the File->Open dialog boxes.

    // The document references its editor, that can reference one or more windows 
    // each displaying this document. 
    // 
    CATFrmWindow *    CreateDefaultWindow(CATFrmEditor *iEditor);
   
    // GetActivePath
    // -------------
    // Returns a path to the first object to ui-activate.
    // The ui-activation manager can't know about the initial
    // object to ui-activate for a newly opened or created document.
    // The purpose of this method is to create a new CATPathElement
    // containing a path in the model to the first ui-activable object to 
    // ui-activate.
    //
    // Warning : Never used this method after the creation of the document 
    //
    CATPathElement GetActiveObject();

    // Useless
    void             Activate();
    void             Deactivate();

    // MemoryDraw 
    // ----------
    // This method is used to display the viewer image using a metafile in an  
    // OLE document. It can be used with Windows NT only. 
    //
    void *           MemoryDraw(unsigned short iFormat,
                                           int iWidth, int iHeight );
  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrDocumentEdit(const CAAEAfrDocumentEdit &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrDocumentEdit & operator = (const CAAEAfrDocumentEdit &iObjectToCopy);


  private:

    // The path to the active object 
    // 
    CATPathElement  _ActivePath ; 


};
#endif 

