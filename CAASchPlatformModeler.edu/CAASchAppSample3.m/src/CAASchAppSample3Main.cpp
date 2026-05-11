// COPYRIGHT DASSAULT SYSTEMES  2001+
//=============================================================================
//
// CAASchAppSample3
//
//  This sample illustrates how to use the CAA Schematics Interfaces to:
//
//  1. Create a route by points.
//  2. Create a route by primitives.
//  
//  Prerequisite: 
//  -------------------
//  Launch mkrtv to create a run-time environment.
//  (This sample uses the same input drawing as CAASchAppSample1.)
//  
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  
//    mkrun -c "CAASchAppSample3 CAASchEduIn.CATProduct CAASchEduOut3.CATProduct"
//  
//  where "CAASchEduIn.CATProduct" is the full path name of the input drawing, and
//  "CAASchEduOut3.CATProduct" is the full path name of the output drawing.
//
//=============================================================================
//
#include <iostream.h>
#include <string.h>

// This framework
#include "CAASchAppSample3.h"

// System
#include "CAASchAppErrors.h"

//=============================================================================
//   Main
//=============================================================================
int main (int argc, char **argv)
{
  cout << "Start main CAASchAppSample3" << endl;

  char *pFileToBeLoaded = NULL;
  char *pPathToOutputFile = NULL;

  if (argc > 1)
  {
    pFileToBeLoaded = argv[1];
  }
  
  if (argc > 2)
  {
    pPathToOutputFile = argv[2];
  }

  int rc = 0;

  CATTry 
	{
     //------------------------------------------------------------------------
     // Test Sample3
     //------------------------------------------------------------------------
        if (!pFileToBeLoaded)
        {
           cout << "**** must input the file name of " << endl;
           cout << "CATProduct with a application reference object " << endl;
        }
        CAASchAppSample3 myObject;
        rc = myObject.DoSample(pFileToBeLoaded,pPathToOutputFile);
  }

  CATCatch (CATError, error)
	{
    cout << "error in main " << endl;
    cout << "error message : "
         << (error->GetNLSMessage()).CastToCharPtr()
         << endl;
    delete error;
    rc = 999;
	}	
  CATEndTry;

  cout << "End main CAASchAppSample3" << endl;
	return rc;
}
