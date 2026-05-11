// COPYRIGHT DASSAULT SYSTEMES 2002

// Local Framework
#include "CAAEPstINFEditPoint.h"
#include "CAAPstINFEditCmdPoint.h"
#include "CAAIPstINFPoint.h"

// ApplicationFrame Framework
#include "CATIEdit.h"

// System framework 
#include "CATErrorDef.h"  // To use the SUCCEEDED macro

// Others
#include "iostream.h"

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIEdit.h"
TIE_CATIEdit(CAAEPstINFEditPoint);

// To declare that the class is a data extension of CAAPstINFPoint
//
CATImplementClass(CAAEPstINFEditPoint,
				  DataExtension, 
				  CATBaseUnknown, 
				  CAAPstINFPoint);

// To declare that CAAEPstINFEditPoint implements CATIEdit for the CAAPstINFPoint
// component, insert the following line in the interface dictionary:
//
//  CAAPstINFPoint CATIEdit  libCAAPstINFCommands
//
//------------------------------------------------------------------------------------------

CAAEPstINFEditPoint::CAAEPstINFEditPoint()
{
  cout << "CAAEPstINFEditPoint::CAAEPstINFEditPoint" << endl;
}

//------------------------------------------------------------------------------------------

CAAEPstINFEditPoint::~CAAEPstINFEditPoint()
{
  cout << "CAAEPstINFEditPoint::~CAAEPstINFEditPoint" << endl;
}

//------------------------------------------------------------------------------------------
// Define the command that is to be executed to handle the edition of the point.
//------------------------------------------------------------------------------------------
CATCommand  * CAAEPstINFEditPoint::Activate(CATPathElement *pPath)
{
  cout << "*****CAAEPstINFEditPoint::Activate" << endl;

  CAAPstINFEditCmdPoint *pCommandToLaunch = NULL;

  // Gets the CAAIPstINFPoint interface pointer
  CAAIPstINFPoint *piPstINFPointEdit = NULL;                
  HRESULT rc = QueryInterface(IID_CAAIPstINFPoint,
	                          (void**)&piPstINFPointEdit);
  if (SUCCEEDED(rc))
  {
     // Creates the command 
     pCommandToLaunch = new CAAPstINFEditCmdPoint(piPstINFPointEdit);

     piPstINFPointEdit -> Release();
     piPstINFPointEdit = NULL ;
  }

  // Returns the CATCommand to edit the selected point.
  return (CATCommand*) pCommandToLaunch;
}

