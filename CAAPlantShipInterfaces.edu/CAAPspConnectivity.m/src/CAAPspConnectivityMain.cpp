// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
//
// CAAPspConnectivityMain
//
//  This sample illustrates how to use the CAA Plant Ship interfaces to:
//
//  1. List the connectors of a part.
//  2. Query part connectors, conect and disconnect connectors.
//  3. Query connections.
//
//  Prerequisite: 
//  -------------------
//  This sample uses the input drawing CAAPspEduIn.CATProduct.
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  
//        mkrun -c "CAAPspConnectivity CAAPspEduIn.CATProduct"
//  
//  where "CAAPspEduIn.CATProduct" is the full path name of the input drawing.
//
//=============================================================================
//
#include <iostream.h>
#include <string.h>

// This framework
#include "CAAPspConnectivity.h"

// System
#include "CATErrorMacros.h"
#include "CATUnicodeString.h"

//=============================================================================
//   Main
//=============================================================================
int main (int argc, char **argv)
{
  cout << "Start main CAAPspConnectivity" << endl;

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
    CAAPspConnectivity myObject;
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

  cout << "End main CAAPspConnectivity" << endl;
  return rc;
}
