// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//
// CAASchAppSample2
//
//  This sample illustrates how to use the CAA Schematics Interfaces to:
//
//  1. Create a component with multiple Graphical Representations (GRRs).
//  2. Activate a second representation of the component.
//  3. Switch all representations for the component to the same GRR
//  
//  Prerequisite: 
//  -------------------
//  Launch mkrtv to create a run-time environment.
//  
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  
//    mkrun -c "CAASchAppSample2 CAASchEduIn2.CATProduct CAASchEduOut2.CATProduct"
//  
//  where "CAASchEduIn2.CATProduct" is the full path name of the input drawing, and
//  "CAASchEduOut2.CATProduct" is the full path name of the output drawing.
//
//=============================================================================
//
#include <iostream.h>
#include <string.h>

// This framework
#include "CAASchAppSample2.h"

// System
#include "CAASchAppErrors.h"
#include "CATLib.h"

//=============================================================================
//   Main
//=============================================================================
int main (int argc, char **argv)
{
  cout << "Start main CAASchAppSample2" << endl;

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
    if (!pFileToBeLoaded)
    {
       cout << "**** must input the file name of " << endl;
       cout << "CATProduct with a application reference object " << endl;
    }
    CAASchAppSample2 myObject;
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

  cout << "End main CAASchAppSample2" << endl;
	return rc;
}
