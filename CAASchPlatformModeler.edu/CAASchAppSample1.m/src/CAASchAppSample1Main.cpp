// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//
// CAASchAppSample1
//
//  This sample illustrates how to create a component with connectors using
//  the CAA Schematics Interfaces.
//
//  This sample will create a schematic component (feature reference) 
//  with two connectors and an internal flow.  An instance of the component is
//  then created on the main sheet of the output drawing.
//  
//  Prerequisite: 
//  -------------------
//  Launch mkrtv to create a run-time environment.
//  
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  
//        mkrun -c "CAASchAppSample1 CAASchEduIn.CATProduct CAASchEduOut1.CATProduct"
//  
//  where "CAASchEduIn.CATProduct" is the full path name of the input drawing, and
//  "CAASchEduOut1.CATProduct" is the full path name of the output drawing.
//
//=============================================================================
//
#include <iostream.h>
#include <string.h>

// This framework
#include "CAASchAppSample1.h"

// System
#include "CAASchAppErrors.h"

//=============================================================================
//   Main
//=============================================================================
int main (int argc, char **argv)
{
  cout << "Start main CAASchAppSample1" << endl;

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
     // Test Sample1
     //------------------------------------------------------------------------
        if (!pFileToBeLoaded)
        {
           cout << "**** must input the file name of " << endl;
           cout << "CATProduct with an application reference object " << endl;
        }
        CAASchAppSample1 myObject;
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

  cout << "End main CAASchAppSample1" << endl;
	return rc;
}
