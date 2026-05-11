// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
//
// CAAArrPathwayRunMain
//
//  This sample illustrates how to create and read an ArrPathway / ArrRun.
//
//  This sample will open an input document containing a Pathway,
//
//  Prerequisite: 
//  -------------------
//  This sample uses the input drawing CAAArrPathwayRun.CATProduct.
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  
//  mkrun -c "CAAArrPathwayRun CAAArrPathwayRun.CATProduct"
//     where "CAAArrPathwayRun.CATProduct" is the full path name of the input drawing.
//
//=============================================================================
//
#include <iostream.h>
#include <string.h>

// This framework
#include "CAAArrPathwayRun.h"

// System
#include "CATErrorMacros.h"
#include "CATUnicodeString.h"

//=============================================================================
//   Main
//=============================================================================
int main (int argc, char **argv)
{
  cout << "Start main CAAArrPathwayRun" << endl;

  CATUnicodeString FileToBeLoaded;

  cout<<"argc = "<<argc<<endl;
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
       cout << "a CATProduct with objects to attach " << endl;
    }
    CAAArrPathwayRun myObject;
    rc = myObject.DoSample(FileToBeLoaded);

    cout << "\n rc ============== " << rc << endl;
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

  cout << "End main CAAArrPathwayRun" << endl;
  return rc;
}
