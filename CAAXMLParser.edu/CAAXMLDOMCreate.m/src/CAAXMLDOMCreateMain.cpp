
// COPYRIGHT DASSAULT SYSTEMES 2002

//=============================================================================
//
// This program creates a DOM document from scratch and writes it to a file.
//
//  Illustrates:
//     1 - How to create DOM document from scratch
//     2 - How to specify the DOM document type
//     3 - How to populate the DOM document with elements, attributes and text
//     4 - How to create an XML output file from a DOM
//    
//=============================================================================

// C++ Standard library
#include <iostream.h>

// XMLParser Framework
#include "CATIXMLDOMDocumentBuilder.h"  // To create the DOM objects
#include "CATIDOMImplementation.h"      // To instantiates DOM documents and DTDs
#include "CATIDOMDocument.h"            // To represent an XML document in DOM form
#include "CATIDOMDocumentType.h"        // To represent an XML DTD in DOM form
#include "CATIDOMElement.h"             // To represent an XML element in DOM form
#include "CATIDOMAttr.h"                // To represent an XML attribute in DOM form
#include "CATIDOMText.h"                // To represent an XML text in DOM form
#include "CATIDOMComment.h"             // To represent an XML comment in DOM form

// System Framework
#include "CATError.h"                  // V5 error handling functions

int main(int argc, char ** argv) {
	// Make sure the input parameters are correct, otherwise display
	// the usage message.
	if (argc != 2) {
		cerr << "Usage: CAAXMLDOMCreate <outfilepath>" << endl;
		return 1;
	}

	// The name of the output file
	CATUnicodeString outputFile = argv[1];


	// Step 1
	// Instantiate the builder. The builder knows how to create all the
	// DOM objects pertaining to a specific implementation of the
	// CAA XMLParser DOM API
	CATIXMLDOMDocumentBuilder_var builder;
	HRESULT hr = ::CreateCATIXMLDOMDocumentBuilder(builder);
	if (SUCCEEDED(hr) && (builder != NULL_var)) {

		// All the statements are put in a do-while loop execute just once.
		// Any time we encounter an error, we will break from the loop and
		// report the error. This technique is well suited for a sample as
		// it makes the code more readable.
		do {
			// Step 2
			// Get the DOM implementation. The DOM implementation knows how
			// to create document types and documents.
			CATIDOMImplementation_var implementation;
			hr = builder->GetDOMImplementation(implementation);
			if (FAILED(hr) || (implementation == NULL_var)) { break ; }
			
			// Use the DOM implementation to instantiate a document type (an external DTD). 
			// This DTD lets you write car specifications
			CATIDOMDocumentType_var docType;
			hr = implementation->CreateDocumentType("car", "", "automotive.dtd", docType);
			if (FAILED(hr) || (docType == NULL_var)) { break ; }
			
			// Step 3
			// Use the DOM implementation to instantiate a new document
			// with the document type we have just specified.
			CATIDOMDocument_var document;
			hr = implementation->CreateDocument("", "car", docType, document);
			if (FAILED(hr) || (document == NULL_var)) { break ; }

			// Step 4
			// Create elements, text nodes and comments
			CATIDOMElement_var car;
			hr = document->CreateElement("car", car);
			if (FAILED(hr) || (car == NULL_var)) { break ; }

			CATIDOMElement_var engine;
			hr = document->CreateElement("part", engine);
			if (FAILED(hr) || (engine == NULL_var)) { break ; }
			hr = engine->SetAttribute("name", "engine");
			if (FAILED(hr)) { break; }
			hr = engine->SetAttribute("quantity", "1");
			if (FAILED(hr)) { break; }

			CATIDOMElement_var seat;
			hr = document->CreateElement("part", seat);
			if (FAILED(hr) || (seat == NULL_var)) { break ; }
			hr = seat->SetAttribute("name", "seat");
			if (FAILED(hr)) { break; }
			hr = seat->SetAttribute("quantity", "2");
			if (FAILED(hr)) { break; }

			CATIDOMElement_var wheel;
			hr = document->CreateElement("part", wheel);
			if (FAILED(hr) || (wheel == NULL_var)) { break ; }
			hr = wheel->SetAttribute("name", "wheel");
			if (FAILED(hr)) { break; }
			hr = wheel->SetAttribute("quantity", "4");
			if (FAILED(hr)) { break; }

			CATIDOMElement_var body;
			hr = document->CreateElement("part", body);
			if (FAILED(hr) || (body == NULL_var)) { break ; }
			hr = body->SetAttribute("name", "body");
			if (FAILED(hr)) { break; }
			hr = body->SetAttribute("quantity", "1");
			if (FAILED(hr)) { break; }

			CATIDOMText_var engineText;
			hr = document->CreateTextNode("low consumption engine", engineText);
			if (FAILED(hr) || (engineText == NULL_var)) { break ; }

			CATIDOMText_var bodyText;
			hr = document->CreateTextNode("weight must be < 1200 kg", bodyText);
			if (FAILED(hr) || (bodyText == NULL_var)) { break ; }

			CATIDOMComment_var comment;
			hr = document->CreateComment("list of parts for a convertible car", comment);
			if (FAILED(hr) || (comment == NULL_var)) { break ; }

			// Step 5
			// Position the created nodes with respect to each other
			// Insert the root element in the document
			hr = document->AppendChild(car);
			if (FAILED(hr)) { break; }

			// Now create a few part elements and add them to the car
			hr = car->AppendChild(seat);
			if (FAILED(hr)) { break; }

			hr = car->AppendChild(wheel);
			if (FAILED(hr)) { break; }

			hr = car->AppendChild(engine);
			if (FAILED(hr)) { break; }

			hr = engine->AppendChild(engineText);
			if (FAILED(hr)) { break; }

			hr = car->AppendChild(body);
			if (FAILED(hr)) { break; }

			hr = body->AppendChild(bodyText);
			if (FAILED(hr)) { break; }

			// Insert the comment before the first part
			hr = car->InsertBefore(comment, seat);
			if (FAILED(hr)) { break; }

			// Step 6
			// Write the resulting document to the supplied file
			// Use the default options (UTF-8 encoding)
			hr = builder->WriteToFile(document, outputFile);

		} while(0);
	}
	// Step 7
	// Print error messages if an error has occurred
	if (FAILED(hr)) {
		CATUnicodeString message = "CAAXMLDOMTranscode has failed:\n";
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

