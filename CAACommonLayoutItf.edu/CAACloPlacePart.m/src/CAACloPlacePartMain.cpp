// COPYRIGHT DASSAULT SYSTEMES 2008
//=============================================================================
//
// CAACloPlacePartMain
//
//  This sample illustrates how to use the CAA Plant Ship interfaces to place parts.
//
//
//  Prerequisite: 
//  -------------------
//  This sample uses the input drawing CAACloEduRuns.CATProduct.
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  
//        CAACloPlacePart MyRootDirectory/CAAPlantShipInterfaces.edu/CNext/graphic/CAACloEduRuns/CAACloEduRuns.CATProduct
//  
//  where MyRootDirectory is the pathname of the root directory where you copied and built the use case.
//
//=============================================================================
//
#include <iostream.h>
#include <string.h>

// This framework
#include "CAACloPlacePart.h"

// System
#include "CATErrorMacros.h"
#include "CATUnicodeString.h"

//=============================================================================
//   Main
//=============================================================================
int main (int argc, char **argv)
{
  cout << "Start main CAACloPlacePart" << endl;

  int rc = 0;
  HRESULT rcError = CATReturnFailure;

  CATUnicodeString FileToBeLoaded = NULL;
  CAACloPlacePart myObject;


  CATTry 
  {
    if (argc > 1)
    {
      FileToBeLoaded = argv[1];
    }

    if (FileToBeLoaded.IsNull())
    {
       cout << "**** must input the file name of " << endl;
       cout << "a CATProduct with Piping application objects " << endl;
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

  cout << "CAACloPlacePart rcError = " << rcError << endl;
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

  cout << "CAACloPlacePart rc = " << rc << endl;
  cout << "End main CAACloPlacePart" << endl;
  return rc;
}
