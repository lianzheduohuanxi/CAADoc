// COPYRIGHT DASSAULT SYSTEMES 2011
//=============================================================================
//
// CAACloPspSpatialPhysicalMain 
// This sample illustrates how to use the CAA Plant Ship interfaces to:
// 1.Query spatial objects.
//
//
//  Prerequisite: 
//  -------------------
//  This sample uses the input product CAACloPspEduIn.CATProduct.
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  
//       mkrun -c "CAACloPspSpatialPhysical CAACloPspEduIn.CATProduct" 
//        
//  where "CAACloPspEduIn.CATProduct" is the full path name of the input product.
//
//=============================================================================
//

#include <iostream.h>
#include <string.h>

// This framework
#include "CAACloPspSpatialPhysical.h"

// System
#include "CATErrorMacros.h"
#include "CATUnicodeString.h"

//=============================================================================
//   Main
//=============================================================================

int main (int argc, char **argv)
{
  cout << "Start main CAACloPspSpatialPhysical" << endl;

  CATUnicodeString FileToBeLoaded = NULL;

  int rc = 0;

  CATTry 
  {
    if (argc > 1)
    {
      FileToBeLoaded = argv[1];
    }
    if (!FileToBeLoaded.GetLengthInChar())
    {
      cout << "**** must input the file name of " << endl;
      cout << "a CATProduct with Piping application objects " << endl;
    }
    else
    {
      CAACloPspSpatialPhysical myObject;
      cout << "FileToBeLoaded = " << FileToBeLoaded << endl;
      rc = myObject.DoSample(FileToBeLoaded);
    }
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

  cout << "End main CAACloPspSpatialPhysical" << endl;
  return rc;
}
