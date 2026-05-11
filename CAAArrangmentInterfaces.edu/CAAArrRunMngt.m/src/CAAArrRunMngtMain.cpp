// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
//
// CAAArrRunMngtMain
//
//  This sample illustrates how to insert, delete and modify nodes/segments on a ArrRun.
//
//  This sample will open an input document containing a RUN's,
//
//  Prerequisite: 
//  -------------------
//  This sample uses the input drawing CAAArrRunMngt.CATProduct.
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  
//  mkrun -c "CAAArrRunMngt CAAArrRunMngt.CATProduct"
//     where "CAAArrRunMngt.CATProduct" is the full path name of the input drawing.
//
//=============================================================================
//
#include <iostream.h>
#include <string.h>

// This framework
#include "CAAArrRunMngt.h"

// System
#include "CATErrorMacros.h"
#include "CATUnicodeString.h"

//	LIST of return codes
//	Return Code			Reason
//	020					Pointer to current Document is KO
//	021					Root Product of Document could not be obtained
//	022					Children of the RootProduct could not be obtained
//	023					Child No. FOUR 04 within Root Document could not be obtained
//	024					Handle to CATIArrSegmentsString from ArrRun04 could not be obtained
//	025					Handle to CATIArrSegmentsStringMngt from ArrRun04 could not be obtained
//	026					Child No. THREE 03 within Root Document could not be obtained
//	027					Handle to CATIArrSegmentsString from ArrRun03 could not be obtained
//	030					Handle to CATIArrSegmentsStringMngt from ArrRun03 could not be obtained
//	031					Child No. TWO 02 within Root Document could not be obtained
//	032					Handle to CATIArrSegmentsString from ArrRun02 could not be obtained
//	033					Handle to CATIArrSegmentsMngt from ArrSegment could not be obtained
//	034					Child No. ONE within Root Document could not be obtained
//	035					Handle to CATIArrSegmentsString from  ArrRun could not be obtained
//	036					Handle to CATIArrNodeMngt from ArrNode could not be obtained
//	999					Error in main method

//=============================================================================
//   Main
//=============================================================================
int main (int argc, char **argv)
{
  cout << "Start main CAAArrRunMngt" << endl;

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
    CAAArrRunMngt myObject;
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

  cout << "End main CAAArrRunMngt" << endl;
  return rc;
}
