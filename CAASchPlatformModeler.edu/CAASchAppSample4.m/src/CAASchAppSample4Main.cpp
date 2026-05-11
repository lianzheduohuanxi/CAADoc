//======================================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015
//======================================================================================================
//
// CAASchAppSample4
//
//  This sample illustrates how to create a schematic document from xml document 
//  containing Piping/Tubing/HVAC data, using the CAA Schematics Interfaces.
//
//  Prerequisite: 
//  -------------------
//  Launch mkrtv to create a run-time environment.
//  
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  
//        mkrun -c "CAASchAppSample4 ...\26PHB2_DS_Format.xml ...\"
//        mkrun -c "CAASchAppSample4 ...\76PHVV_DS_Format.xml ...\"
//  
//  where "...\26PHB2_DS_Format.xml" is the absolute path of the input xml document, and
//  "...\" is the absolute path of directory, where the newly created schematic product should be saved.
//
//======================================================================================================

#include <iostream.h>

// This framework
#include "CAASchAppSample4.h"

//=============================================================================
//   Main
//=============================================================================
int main (int argc, char **argv)
{
	cout << "Start main CAASchAppSample4" << endl;

	CATUnicodeString pFileToBeLoaded;
	CATUnicodeString pPathToOutputFile;

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
		if (pFileToBeLoaded.IsNull())
		{
			cout << "**** must input the file name of " << endl;
			cout << "CATProduct with an application reference object " << endl;
		}
		else
		{
			CAASchAppSample4 myObject;
			rc = myObject.DoSample(pFileToBeLoaded,pPathToOutputFile);
		}
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

	cout << "End main CAASchAppSample4" << endl;
	return rc;
}
