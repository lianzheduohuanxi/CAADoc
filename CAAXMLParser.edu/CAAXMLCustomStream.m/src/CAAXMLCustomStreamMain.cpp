
// COPYRIGHT DASSAULT SYSTEMES 2005

//=============================================================================
//
// This program uses a custom input stream to parse XML content split over
// several files and prints the resulting XML document to the console.
//
//  Illustrates:
//     1 - How to create create a custom input stream to fetch XML content
//         from an arbitrary source. In this sample, the source is a set
//         of files. Each file contains a piece of a large XML document. 
//     2 - How to create an input source from a custom input stream. This
//         input source can be used just like any classic (URL-based or memory-based)
//         input sources.
//     3 - How to create a DOM from an input source.
//     4 - How to create raw XML from a DOM.
//    
//=============================================================================

// C++ Standard library
#include <iostream.h>

// Local Framework
#include "CAAXMLMultiFileStream.h"      // To implement the custom XML input stream

// XMLParser Framework
#include "CATIXMLInputStream.h"         // To define custom input streams
#include "CATISAXInputSource.h"         // To define XML input sources
#include "CATIXMLSAXFactory.h"          // To create input sources
#include "CATIXMLDOMDocumentBuilder.h"  // To create the DOM objects
#include "CATIDOMDocument.h"            // To represent an XML document in DOM form

// System Framework
#include "CATListOfCATUnicodeString.h"  // To specify options to the parser
#include "CATError.h"                   // V5 error handling functions

int main(int argc, char ** argv) {
	// Make sure the input parameters are correct, otherwise display
	// the usage message.
	if (argc <= 1) {
		cerr << "Usage: CAAXMLCustomStream <file1> ... <fileN>" << endl;
		return 1;
	}

	// Create a list of file names. Each file contains a piece of a the XML document.
	CATListOfCATUnicodeString files;
	for (int i = 1; i < argc; i++) {
		files.Append(argv[i]);
	}

	HRESULT hr = E_FAIL;
	
	// All the statements are put in a do-while loop and execute just once.
	// Any time we encounter an error, we will break from the loop and
	// report the error. This technique is well suited for a sample as
	// it makes the code more readable.
	do {
		// Step 2
		// Instantiate the builder. The builder knows how to create DOMs
		// from an XML input source
		CATIXMLDOMDocumentBuilder_var builder;
		hr = ::CreateCATIXMLDOMDocumentBuilder(builder);
		if (FAILED(hr) || (builder == NULL_var)) { break ; }

		// Instantiate the factory. The factory knows how to create 
		// XML input sources
		CATIXMLSAXFactory_var factory;
		hr = ::CreateCATIXMLSAXFactory(factory);
		if (FAILED(hr) || (factory == NULL_var)) { break ; }

		// Step 3
		// Create the custom input stream.
		CAAXMLMultiFileStream* customStreamImpl = new CAAXMLMultiFileStream(files);
		CATIXMLInputStream_var customStream = customStreamImpl;
		customStreamImpl->Release();
		customStreamImpl = NULL;
		if (customStream == NULL_var) { break ; }

		// Create an XML input source based on the stream.
		CATISAXInputSource_var source;
		hr = factory->CreateInputSourceFromStream(customStream, "MyCustomSource", source);
		if (FAILED(hr) || (source == NULL_var)) { break ; }

		// Step 4
		// Prepare the options to pass to the builder for reading. The parser receives
		// its options in the form of (optionName, optionValue) pairs.
		// By default, the builder attempts to validate documents. In this
		// sample, we want to turn off this feature.
		CATListOfCATUnicodeString readOptions;
		readOptions.Append("CATDoValidation");
		CATListOfCATUnicodeString readOptionValues;
		readOptionValues.Append("false");

		CATIDOMDocument_var document;
		hr = builder->Parse(source, document, readOptions, readOptionValues);
		if (FAILED(hr) || (document == NULL_var)) { break ; }

		// Step 5
		// Write the resulting document to a raw XML string
		// Use the default options (UTF-8 encoding)
		CATUnicodeString rawOutput;
		hr = builder->Write(document, rawOutput);
		if (FAILED(hr)) { break ; }

		// Write the result in the console.
		cout << "=== Start of XML stream ===" << endl;
		cout << rawOutput.ConvertToChar() << endl;
		cout << "=== End of XML stream ===" << endl;

	} while(0);

	// Step 6
	// Print error messages if an error has occurred
	if (FAILED(hr)) {
		CATUnicodeString message = "CAAXMLCustomStream has failed:\n";
		CATError* error = CATError::CATGetLastError(hr);
		if (error != NULL) {
			message.Append(error->GetNLSMessage());
			error->Release();
			error = NULL;
		}
		CATError::CATCleanLastError();
		cerr << message.ConvertToChar() << endl;
		return 1;
	}
	return 0;
}

