#ifndef CAAECafGeoDocument_H
#define CAAECafGeoDocument_H

// COPYRIGHT DASSAULT SYSTEMES 1999
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Class which implements a new document type (CAAGeometry)
//  It is a data extension of a late type (CAAGeomety)
//  representing the document type. 
//
//  In this document, the document identifier equals the document suffix
//  (CAAGeometry).
//  So all these interfaces are implemented by a data extension of the
//  same late type (CAAGeometry).
//  
//  Illustrates:
//     - implementation of the following interfaces to create a new document
//        CATIDocAlias
//        CATIEditor
//        CATIDocumentEdit
//        CATInit
//
//  CATIDocAlias and CATIEditor are implemented in CAAApplicationFrame.edu
//===========================================================================
//  Usage:
//  ------
//  Launch CATIA V5, File/New In the Dialog Box the new document type  
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
//  Activate
//  Deactivate
//  MemoryDraw
//
//===========================================================================

// System framework
#include "CATBaseUnknown.h"   // Needed to derive from CATBaseUnknown

// Visualization framework
#include "CATPathElement.h"   // Needed by GetActiveObject 

// ApplicationFrame framework
class     CATFrmEditor ;      //Needed by CreateDefaultWindow 
class     CATFrmWindow ;      //Needed by CreateDefaultWindow 


class CAAECafGeoDocument: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:
    CAAECafGeoDocument();
    virtual ~CAAECafGeoDocument();

  // CATIDocumentEdit 
   
    // CreateDefaultWindow
    // -------------------
    // Creates the window dedicated to display and manipulate the document.
    //
    // This method is called by the File->New and the File->Open dialog boxes.

    // The document references its editor, that can reference one or more windows 
    // each displaying this document. 
    // 
    CATFrmWindow*            CreateDefaultWindow(CATFrmEditor *iEditor);

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

    CATPathElement           GetActiveObject();

    // Useless
    void                     Activate();
    void                     Deactivate();

    // MemoryDraw 
    // ----------
    // This method is used to display the viewer image using a metafile in an  
    // OLE document. It can be used with Windows NT only. 
    //
    void *                   MemoryDraw(unsigned short iFormat, int iWidth, int iHeight );

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAECafGeoDocument(const CAAECafGeoDocument &iObjectToCopy);

    // Assigment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAECafGeoDocument & operator = (const CAAECafGeoDocument &iObjectToCopy);

  private:

    // The path to the active object 
    // 
    CATPathElement    _ActivePath ; 

     
};
#endif
