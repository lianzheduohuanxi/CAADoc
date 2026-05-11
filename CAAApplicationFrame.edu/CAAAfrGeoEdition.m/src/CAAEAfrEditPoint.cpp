// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAEAfrEditPoint.h"
#include "CAAAfrPointEditCmd.h"

// CAASystem.edu Framework
#include "CAAISysPoint.h"

//System framework 
#include "CATErrorDef.h"  // To use the SUCCEEDED macro

//C++ Standard library
#include "iostream.h"


//------------------------------------------------------------------------------------------
// To create the TIE Object
#include "TIE_CATIEdit.h"
TIE_CATIEdit(CAAEAfrEditPoint);

// To declare that the class is a data extension of CAASysPoint
//
CATImplementClass(CAAEAfrEditPoint, DataExtension, CATBaseUnknown, CAASysPoint);

// 
// To declare that CAAEAfrEditPoint implements CATIEdit, insert 
// the following line in the interface dictionary:
//
//  CAASysPoint CATIEdit  libCAAAfrGeoEdition
//
//------------------------------------------------------------------------------------------

CAAEAfrEditPoint::CAAEAfrEditPoint()
{
  cout << "CAAEAfrEditPoint::CAAEAfrEditPoint" << endl;
}

//------------------------------------------------------------------------------------------

CAAEAfrEditPoint::~CAAEAfrEditPoint()
{
  cout << "CAAEAfrEditPoint::~CAAEAfrEditPoint" << endl;
}

//------------------------------------------------------------------------------------------

CATCommand  * CAAEAfrEditPoint::Activate(CATPathElement * iPath)
{
  cout << "CAAEAfrEditPoint::Activate" << endl;

  CAAAfrPointEditCmd *  pCommandToLaunch = NULL;

  // Gets the CAAISysPoint interface pointer
  CAAISysPoint * pSysPointEdit = NULL;                
  HRESULT rc = QueryInterface(IID_CAAISysPoint, (void**)&pSysPointEdit);
  if (SUCCEEDED(rc))
  {
     // Creates the command 
     pCommandToLaunch = new CAAAfrPointEditCmd(pSysPointEdit);

     pSysPointEdit -> Release();
     pSysPointEdit = NULL ;
  }

  // Returns the CATCommand to edit the selected point.
  return (CATCommand*) pCommandToLaunch;
}

