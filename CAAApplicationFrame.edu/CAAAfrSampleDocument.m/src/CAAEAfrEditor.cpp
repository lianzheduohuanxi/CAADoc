// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAEAfrEditor.h"

// ApplicationFrame Framework 
#include "CATFrmObjectEditor.h"  

// C++ Standrad library 
#include <iostream.h>

//-------------------------------------------------------------------------
// To create the TIE Object
#include "TIE_CATIEditor.h"          
TIE_CATIEditor(CAAEAfrEditor);   

// To declare that the class is a data extension of (the late type) CAADoc
// (which is the document suffix), see the CAAEAfrDocAlias.cpp
//
CATImplementClass(CAAEAfrEditor, DataExtension, CATBaseUnknown, CAADoc);

// 
// To declare that CAAEAfrEditor implements CATIEditor, insert 
// the following line in the interface dictionary:
//
//    CAADoc CATIEditor  libCAAAfrSampleDocument
//
//-------------------------------------------------------------------------

CAAEAfrEditor::CAAEAfrEditor():_pEditor(NULL)
{
  cout << "Constructing CAAEAfrEditor"  << endl;
  // This constructor should not be explicitly called.
}

//-------------------------------------------------------------------------

CAAEAfrEditor::~CAAEAfrEditor()
{ 
  cout << "Destructing CAAEAfrEditor"  << endl; 
  // This destructor should not be explicitly called.

  //
  // _pEditor is a data member of the current extension but should not be deleted here.
  //
  // When the document is closed, CATFrmEditor::Close() is called, which in turn  
  // calls RequestDelayedDestruction on _pEditor. 

  _pEditor = NULL ;
}

//-------------------------------------------------------------------------

CATFrmEditor * CAAEAfrEditor::GetEditor()
{ 
   cout << "CAAEAfrEditor::GetEditor"  << endl;

  // Editor and Document should know each other, so the pointer to the document
  // is passed as the parameter of the editor's constructor. 

  CATBaseUnknown * Unk = NULL;
  if (SUCCEEDED(QueryInterface(IID_CATBaseUnknown, (void**)&Unk)))
  {
    if ( NULL == _pEditor ) 
    {
      _pEditor =  new CATFrmObjectEditor((CATDocument *) Unk);

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
		  (CATSubscriberMethod)&CAAEAfrEditor::SetEditorToNullWhenClosed,
		  NULL);

      
    }
    Unk -> Release();
    Unk = NULL ;
  }
  return _pEditor ;
}

//-------------------------------------------------------------------------

void CAAEAfrEditor::SetEditorToNullWhenClosed(CATCallbackEvent  iEvent, 
                                              void            * iFrom,
                                              CATNotification * iNotification,
                                              CATSubscriberData iClientData,
                                              CATCallback       iCallBack ) 
{
   cout << "CAAEAfrEditor::SetEditorToNullWhenDeleted"  << endl;

   // iFrom is the editor which is closed 
   if ( _pEditor == iFrom )
   {
      cout << "Editor for the CAASample document is set to null "<< endl;

      // Now this extension will receive any message.
      //
      ::RemoveSubscriberCallbacks(this,CATFrmLayout::GetCurrentLayout());

      _pEditor = NULL ; 
   }
}

//-------------------------------------------------------------------------
