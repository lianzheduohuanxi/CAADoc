// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAEAfrEditPlane.h"
#include "CAAAfrPlaneEditCmd.h"

//CAASystem.edu Framework 
#include "CAAISysPlane.h"

//Applicatio Frame Framework
#include "CATApplicationFrame.h"

//C++ Standard library
#include "iostream.h"


//----------------------------------------------------------------------------
// To create the TIE Object
#include "TIE_CATIEdit.h"
TIE_CATIEdit(CAAEAfrEditPlane);

// Declared that the class is a data extension of CAASysPlane
//
CATImplementClass(CAAEAfrEditPlane, DataExtension, CATBaseUnknown, CAASysPlane);

// 
// To declare that CAAEAfrEditPlane implements CATIEdit, insert 
// the following line in the interface dictionary:
//
//    CAASysPlane CATIEdit  libCAAAfrGeoEdition
//
//-----------------------------------------------------------------------------

CAAEAfrEditPlane::CAAEAfrEditPlane()
{
  cout << "CAAEAfrEditPlane::CAAEAfrEditPlane" << endl;
}

//-----------------------------------------------------------------------------

CAAEAfrEditPlane::~CAAEAfrEditPlane()
{
  cout << "CAAEAfrEditPlane::~CAAEAfrEditPlane" << endl;
}

// ----------------------------------------------------------------------------
CATCommand  * CAAEAfrEditPlane::Activate(CATPathElement * iPath)
{
  cout << "CAAEAfrEditPlane::Activate" << endl;

  CAAAfrPlaneEditCmd * EditWindow = NULL;

  // Retrieves the CAAISysPlane interface pointer 
  //
  CAAISysPlane * piSysPlaneEdit = NULL;                
  HRESULT rc = QueryInterface(IID_CAAISysPlane, (void**)&piSysPlaneEdit);
  if (SUCCEEDED(rc))
  {
     // Parent Dialog  of this dialog box 
     // This dialog entity is the dialog object dedicated to the document
     // 
     //
     CATApplicationFrame * pFrame = CATApplicationFrame::GetFrame() ;
     if ( NULL != pFrame )
     {
        CATDialog * pParent = pFrame->GetMainWindow() ;

        if ( NULL != pParent )
        {
  
           // Style of the dialog box
           CATDlgStyle style = CATDlgGridLayout| CATDlgWndBtnOKCancelPreview ;
 
           // Creation of the command to return
           EditWindow = new CAAAfrPlaneEditCmd(pParent,"EditPlane",style,piSysPlaneEdit);
           EditWindow->Build();
      }
   }
   
   // Done with the pointer
   piSysPlaneEdit -> Release();
   piSysPlaneEdit = NULL ;
  }

  return (CATCommand*) EditWindow;

}

