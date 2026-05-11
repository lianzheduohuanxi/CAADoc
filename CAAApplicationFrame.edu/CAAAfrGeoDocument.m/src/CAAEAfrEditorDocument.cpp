// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework 
#include "CAAEAfrEditorDocument.h"

// ApplicationFrame Framework 
#include "CATFrmEditor.h"       
#include "CATFrmObjectEditor.h"

// C++ standrad library 
#include <iostream.h>  

//
//  _______________ Extension of a CAAGeometry Document  _______________
//

#include "TIE_CATIEditor.h"          
TIE_CATIEditor(CAAEAfrEditorDocument);   

// To declare that the class is a data extension of (the late type) CAAGeom
// (which is the document suffix), see the CAAEAfrAliasDocument.cpp
//
CATImplementClass(CAAEAfrEditorDocument, DataExtension, CATBaseUnknown,CAAGeom);

//  _______________ Dictionary to modify   _____________________________
// 
// To declare that CAAEAfrEditorDocument implements CATIEditor insert 
// the following lines in the interface dictionary:
//
//    CAAGeom CATIEditor        libCAAAfrGeoDocument
//
// _______________ Constructor - Destructor _____________________________
//

CAAEAfrEditorDocument::CAAEAfrEditorDocument(): _pEditor(NULL)
{
  cout << "Constructing CAAEAfrEditorDocument"  << endl;
}

CAAEAfrEditorDocument::~CAAEAfrEditorDocument()
{ 
  cout << "Destructing CAAEAfrEditorDocument"  << endl;    
   //
   // _Editor is a data member of the current extension but should not be deleted here.
   //
   // When the document is closed, CATFrmEditor::Close() is called, which in turn  
   // calls RequestDelayedDestruction on _Editor. 
   _pEditor = NULL ;
}

//
// _______________ CATIEditor _____________________________
//

CATFrmEditor * CAAEAfrEditorDocument::GetEditor()
{ 
  cout << "CAAEAfrEditorDocument::GetEditor"  << endl;

  CATBaseUnknown * pBUnk = NULL;
  if (SUCCEEDED(QueryInterface(IID_CATBaseUnknown, (void**)&pBUnk)))
  {
    if ( NULL == _pEditor ) 
    {
       // Editor and Document should know each other, so the pointer to the document
       // is passed as the parameter of the editor's constructor. 
       _pEditor =  new CATFrmObjectEditor((CATDocument *) pBUnk) ;


	  // The editor is deleted by the CATFrmEditor class. So to set this value
      // to NULL, we set a callback to be prevent.
      // CATFrmLayout send an event EDITOR_CLOSE_ENDED in the CATFrmEditor::Close
      // method before to delete the editor. 
      // When the layout send the event, it set the event publisher to the editor. 
      // So in the SetEditorToNullWhenClosed method, iFrom is the editor.  
      //
      ::AddCallback(this,
                  CATFrmLayout::GetCurrentLayout(),
		  CATFrmEditor::EDITOR_CLOSE_ENDED(),
		  (CATSubscriberMethod)&CAAEAfrEditorDocument::SetEditorToNullWhenClosed,
		  NULL);
      
    }
    pBUnk -> Release();
    pBUnk = NULL ;
  }

  return _pEditor ;
}

//-------------------------------------------------------------------------

void CAAEAfrEditorDocument::SetEditorToNullWhenClosed(CATCallbackEvent  iEvent, 
                                              void            * iFrom,
                                              CATNotification * iNotification,
                                              CATSubscriberData iClientData,
                                              CATCallback       iCallBack ) 
{
   cout << "CAAEAfrEditorDocument::SetEditorToNullWhenDeleted"  << endl;

   // iFrom is the editor which is closed 
   if ( _pEditor == iFrom )
   {
      cout << "Editor for the CAAGeometry document is set to null "<< endl;

      // Now this extension will receive any message.
      //
      ::RemoveSubscriberCallbacks(this,CATFrmLayout::GetCurrentLayout());

      _pEditor = NULL ; 
   }
}

//-------------------------------------------------------------------------





