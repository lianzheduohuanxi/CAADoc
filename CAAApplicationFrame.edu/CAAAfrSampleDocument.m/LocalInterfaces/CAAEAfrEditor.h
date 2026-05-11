#ifndef CAAEAfrEditor_H
#define CAAEAfrEditor_H

// COPYRIGHT DASSAULT SYSTEMES 1999

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
//  Class which implements the CATIEditor interface of a new document
//  type (CAASample)
//  It is a data extension of a late type (CAADoc) which is the document 
//  suffix. 
//  The aim of CATIEditor interface is to return the editor of the document.
//
//  Illustrates:
//     - implementation of the CATIEditor to return the editor
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
//  GetEditor
//
//===========================================================================
// System Framework
#include "CATBaseUnknown.h"     // Needed to derive from CATBaseUnknown
#include "CATEventSubscriber.h" // to set the callback

// ApplicationFrame framework
class CATFrmEditor ;          // Needed by GetEditor 


class CAAEAfrEditor: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAEAfrEditor();
    virtual ~CAAEAfrEditor();

    // GetEditor
    // ---------
    // Retrieves the editor of the document made active. 
    //
    // This method is called by the File->New and the File->Open dialog boxes
    // and when swapping from a document to another. 
    // 
    //
    // The editor is created the first time that GetEditor is called, and is 
    // kept as a data member for next calls. 
  
    CATFrmEditor * GetEditor();


    void SetEditorToNullWhenClosed          (CATCallbackEvent  iEvent,
                           void             *iFrom,
                           CATNotification  *iNotification,
                           CATSubscriberData iData,
                           CATCallback       iCallBack );
  private :

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrEditor(const CAAEAfrEditor &iObjectToCopy);
  
    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrEditor & operator = (const CAAEAfrEditor &iObjectToCopy);
  
  private :

    // The value created by GetEditor 
    CATFrmEditor * _pEditor; 

};
#endif
