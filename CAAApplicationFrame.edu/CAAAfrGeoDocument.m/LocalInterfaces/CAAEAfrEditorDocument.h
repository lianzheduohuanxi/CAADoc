#ifndef CAAEAfrEditorDocument_H
#define CAAEAfrEditorDocument_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Application using a new document type (CAAGeometry) with its own workshop
//  and commands.
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data Extension of the Late type CAAGeom. 
//
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
//  GetEditor
//
//===========================================================================

// System framework
#include "CATBaseUnknown.h"       // Needed to derive from CATBaseUnknown
#include "CATEventSubscriber.h"   // Needed for the callback
// ApplicationFrame framework
class     CATFrmEditor ;      // CATIEditor 


class CAAEAfrEditorDocument: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAEAfrEditorDocument();
    virtual ~CAAEAfrEditorDocument();

    // GetEditor
    // ---------
    // Retrieves the editor of the document made active. 
    //
    // This method is called by the File->New and the File->Open dialog boxes
    // and when swapping from a document to another. 
    // 
    //
    // The editor is created the first time that GetEditor is called, and is 
    // kept as
    //
    CATFrmEditor *           GetEditor();

    // SetEditorToNullWhenClosed
    // --------------------------
    // To set to NULL, _Editor when the editor is closed
    //
    void SetEditorToNullWhenClosed          (CATCallbackEvent  iEvent,
                           void             *iFrom,
                           CATNotification  *iNotification,
                           CATSubscriberData iData,
                           CATCallback       iCallBack );
  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrEditorDocument(const CAAEAfrEditorDocument &iObjectToCopy);
  
    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrEditorDocument & operator = (const CAAEAfrEditorDocument &iObjectToCopy);
  
  private:

    // The value created by GetEditor 
    CATFrmEditor    * _pEditor ; 

     
};
#endif
