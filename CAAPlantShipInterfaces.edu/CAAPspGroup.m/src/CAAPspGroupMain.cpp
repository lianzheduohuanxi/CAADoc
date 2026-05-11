// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
//
// CAAPspGroupMain
//
//  This sample illustrates how to use the CAA Plant Ship interfaces to:
//
//  1. List the members of a group, add and remove members to a group
//  2. Query a member of a group
//  3. Instanciate a logical line from the active logical line catalog
//  6. Create a group in a CATProduct document.
//  4. List the group and logical line instances in a CATProduct document
//  5. Delete a group or logical line instance.
//  7. Delete a part instance.
//
//  Prerequisite: 
//  -------------------
//  This sample uses the input drawing CAAPspEduIn.CATProduct.
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  
//        mkrun -c "CAAPspGroup CAAPspEduIn.CATProduct"
//  
//  where "CAAPspEduIn.CATProduct" is the full path name of the input drawing.
//
//=============================================================================
//
#include <iostream.h>
#include <string.h>

// This framework
#include "CAAPspGroup.h"

// System
#include "CATErrorMacros.h"
#include "CATUnicodeString.h"

//=============================================================================
//   Main
//=============================================================================
int main (int argc, char **argv)
{
  cout << "Start main CAAPspGroup" << endl;

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
    CAAPspGroup myObject;
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

  cout << "End main CAAPspGroup" << endl;
  return rc;
}
