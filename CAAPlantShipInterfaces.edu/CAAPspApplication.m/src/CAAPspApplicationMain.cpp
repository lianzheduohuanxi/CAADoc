// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
//
// CAAPspApplicationMain
//
//  This sample illustrates how to initialize a domain and application resources,
//  and how to extract information for a specific domain and application.
//
//  This sample will open an input document, initialize the Piping application resources,
//  and query for domain and application information.
//
//  Prerequisite: 
//  -------------------
//  This sample uses the input drawing CAAPspEduIn.CATProduct.
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  
//        mkrun -c "CAAPspApplication CAAPspEduIn.CATProduct"
//  
//  where "CAAPspEduIn.CATProduct" is the full path name of the input drawing.
//
//=============================================================================
//
#include <iostream.h>
#include <string.h>

// This framework
#include "CAAPspApplication.h"

// System
#include "CATErrorMacros.h"
#include "CATUnicodeString.h"

//=============================================================================
//   Main
//=============================================================================
int main (int argc, char **argv)
{
  cout << "Start main CAAPspApplication" << endl;

  CATUnicodeString FileToBeLoaded;

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
    CAAPspApplication myObject;
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

  cout << "End main CAAPspApplication" << endl;
  return rc;
}
