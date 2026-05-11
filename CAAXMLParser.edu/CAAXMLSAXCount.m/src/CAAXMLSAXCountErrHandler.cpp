// COPYRIGHT DASSAULT SYSTEMES 2002

// Local framework
#include "CAAXMLSAXCountErrHandler.h"

// System framework
#include "CATUnicodeString.h"     // For NLS string operations

// XMLParser framework
#include "CATSAXParseException.h" // To represent SAX parse errors.
#include "CATError.h"             // V5 error handling functions

// Standard C++ library
#include <iostream.h>

// Declare the class as a V5 component derived from CATSAXHandlerBase
CATImplementClass( CAAXMLSAXCountErrHandler, Implementation, CATSAXHandlerBase, CATnull );

// Implement the CATISAXErrorHandler interface
#include "TIE_CATISAXErrorHandler.h"
TIE_CATISAXErrorHandler(CAAXMLSAXCountErrHandler);

CAAXMLSAXCountErrHandler::CAAXMLSAXCountErrHandler() {
}

CAAXMLSAXCountErrHandler::~CAAXMLSAXCountErrHandler() {
}


HRESULT CAAXMLSAXCountErrHandler::Error ( 
	CATSAXParseException* iException) {

	// This event is sent by the CATISAXParser when a recoverable
	// (validation) error is met. It is sent only if the parser was created with the
	// CATDoValidation option.

	CATUnicodeString errorMessage = "Error : ";
	if (iException != NULL) {
		errorMessage.Append(iException->GetNLSMessage());
	}
	cerr << errorMessage.ConvertToChar() << endl;

	// Let the parser continue the parsing (if we returned E_FAIL, parsing would stop)
	return S_OK;
}

HRESULT CAAXMLSAXCountErrHandler::FatalError ( 
	CATSAXParseException* iException) {

	// This event is sent by the CATISAXParser when an irrecoverable error
	// is met.

	CATUnicodeString errorMessage = "Fatal error : ";
	if (iException != NULL) {
		errorMessage.Append(iException->GetNLSMessage());
	}
	cerr << errorMessage.ConvertToChar() << endl;

	// Stop the parsing. The CATISAXParser will stop anyway since this is a FatalError.
	return E_FAIL;
}

