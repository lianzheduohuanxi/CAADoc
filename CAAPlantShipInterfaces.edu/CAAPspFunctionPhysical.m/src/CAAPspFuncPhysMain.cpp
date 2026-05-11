// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
//
// CAAPspFuncPhysMain
//
//  This sample illustrates how to use the CAA Plant Ship interfaces to:
//
//  1. Query functional objects.
//  2. Query physical objects.
//  3. Query spatial objects.
//
//  Prerequisite: 
//  -------------------
//  This sample uses the input drawing CAAPspEduIn.CATProduct.
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  
//        mkrun -c "CAAPspFunctionPhysical CAAPspEduIn.CATProduct"
//  
//  where "CAAPspEduIn.CATProduct" is the full path name of the input drawing.
//
//=============================================================================
//
#include <iostream.h>
#include <string.h>

// This framework
#include "CAAPspFunctionPhysical.h"

// System
#include "CATErrorMacros.h"
#include "CATUnicodeString.h"

//=============================================================================
//   Main
//=============================================================================
int main (int argc, char **argv)
{
  cout << "Start main CAAPspFunctionPhysical" << endl;

  CATUnicodeString FileToBeLoaded = NULL;

  if (argc > 1)
  {
    FileToBeLoaded = argv[1];
  }

  int rc = 0;

  CATTry 
  {
    if (!FileToBeLoaded.GetLengthInChar())
    {
       cout << "**** must input the file name of " << endl;
       cout << "a CATProduct with Piping application objects " << endl;
    }
    CAAPspFunctionPhysical myObject;
    rc = myObject.DoSample(FileToBeLoaded);
  }

  CATCatch (CATError, error)
  {
    cout << "error in main " << endl;
    cout << "error message : "
         << (error->GetNLSMessage()).ConvertToChar()
         << endl;
    delete error;
    rc = 999;
  } 
  CATEndTry;

  cout << "End main CAAPspFunctionPhysical" << endl;
  return rc;
}
