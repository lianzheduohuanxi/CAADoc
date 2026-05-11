
// COPYRIGHT DASSAULT SYSTEMES 2005

//=============================================================================
//
// This program displays the list of DOM and SAX parsers currently installed
// on the host.
//  Illustrates:
//     1 - How to use parser detection function to find out if a particular
//         parser implementation is available. 
//    
//=============================================================================

// C++ Standard library
#include <iostream.h>

// XMLParser Framework
#include "CATIXMLSAXFactory.h"          // For SAX parser detection functions
#include "CATIXMLDOMDocumentBuilder.h"  // For DOM parser detection functions

int main(int argc, char ** argv) {
	int count = 5;

	// Declare an array of names of XML implementations currently recognized in V5
	CATUnicodeString* parserArray = new CATUnicodeString[count];
	parserArray[0] = "XML4C version 5.0";
	parserArray[1] = "XML4C version 3.0.1";
	parserArray[2] = "MSXML version 5.0";
	parserArray[3] = "MSXML version 4.0";
	parserArray[4] = "MSXML version 3.0";

	// Declare an array of CLSID of DOM parsers currently recognized in V5
	CLSID *domClsidArray = new CLSID[count];
	domClsidArray[0] = CLSID_XML4C5_DOM;
	domClsidArray[1] = CLSID_XML4C_DOM;
	domClsidArray[2] = CLSID_MSXML5_DOM;
	domClsidArray[3] = CLSID_MSXML4_DOM;
	domClsidArray[4] = CLSID_MSXML3_DOM;

	// Declare an array of CLSID of SAX parsers currently recognized in V5
	CLSID *saxClsidArray = new CLSID[5];
	saxClsidArray[0] = CLSID_XML4C5_SAX;
	saxClsidArray[1] = CLSID_XML4C_SAX;
	saxClsidArray[2] = CLSID_MSXML5_SAX;
	saxClsidArray[3] = CLSID_MSXML4_SAX;
	saxClsidArray[4] = CLSID_MSXML3_SAX;

	// Step 1
	cout << "DOM parsers on the host:" << endl;
	int i = 0;
 for (; i < count; i++) {
		unsigned int implIndex = 1;
		// Call the detection function with a CLSID array of size 1.
		// The function will succeed if it finds a suitable DOM parser in the array
		// and fail otherwise.
		HRESULT hr = DetectCATIXMLDOMDocumentBuilder(&domClsidArray[i], 1, implIndex);
		CATUnicodeString status = (SUCCEEDED(hr)) ? "Installed" : "Not installed";
		cout << parserArray[i].ConvertToChar() << " : " << status.ConvertToChar() << endl;
	}

	// Step 2
	cout << "SAX parsers on the host:" << endl;
	for (i = 0; i < count; i++) {
		// Call the detection function with a CLSID array of size 1.
		// The function will succeed if it finds a suitable SAX parser in the array
		// and fail otherwise.
		unsigned int implIndex = 1;
		HRESULT hr = DetectCATIXMLSAXFactory(&saxClsidArray[i], 1, implIndex);
		CATUnicodeString status = (SUCCEEDED(hr)) ? "Installed" : "Not installed";
		cout << parserArray[i].ConvertToChar() << " : " << status.ConvertToChar() << endl;
	}

	return 0;
}

