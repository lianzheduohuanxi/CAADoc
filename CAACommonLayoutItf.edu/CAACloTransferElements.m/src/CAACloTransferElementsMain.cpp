// COPYRIGHT DASSAULT SYSTEMES 2008
//=============================================================================
//
// CAACloTransferElementsMain
//
//  This sample illustrates how to use the CAA CommonLayout interfaces to transfer elements.
//
//

#include <iostream.h>
#include <string.h>

// This framework
#include "CAACloTransferElements.h"

// System
#include "CATErrorMacros.h"
#include "CATUnicodeString.h"
#include "CATError.h"

//=============================================================================
//   Main
//=============================================================================
int main (int argc, char **argv)
{
  cout << "Start main CAACloTransferElements" << endl;

  int rc = 0;
  HRESULT rcError = CATReturnFailure;

  CATUnicodeString FileToBeLoaded = NULL;
  CAACloTransferElements myObject;


  CATTry 
  {
    if (argc > 1)
    {
      FileToBeLoaded = argv[1];
    }

    if (FileToBeLoaded.IsNull())
    {
       cout << "**** must input the file name of " << endl;
       cout << "a CATProduct " << endl;
    }
    else
    {
      cout << "FileToBeLoaded = " << FileToBeLoaded << endl;
      rcError = myObject.DoSample(FileToBeLoaded);
    }
  }

	CATCatch (CATError, pError)
	{
    cout << "error in main " << endl;

    rcError = CATReturnError(pError);
	} // end CATCatch

  CATEndTry;

  cout << "CAACloTransferElements rcError = " << rcError << endl;
  if (FAILED(rcError))
  { 
    rc = 999;
    CATError *pError = CATError::CATGetLastError(rcError);
    if (pError)
    {
      cout << pError;
      Flush(pError);
    }
  }

  cout << "CAACloTransferElements rc = " << rc << endl;
  cout << "End main CAACloTransferElements" << endl;
  return rc;
}
