// COPYRIGHT DASSAULT SYSTEMES 2002

// Local framework
#include "CAAXMLSAXResolverHandlers.h"

// System framework
#include "CATUnicodeString.h"     // For NLS string operations

// XMLParser framework
#include "CATIXMLSAXFactory.h"    // To create the SAX objects
#include "CATISAXInputSource.h"   // To represent an XML entity
#include "CATSAXParseException.h" // To represent SAX parse errors.
#include "CATSAXException.h"      // To represent SAX errors.
#include "CATError.h"             // V5 error handling functions

// Standard C++ library
#include <iostream.h>

// Declare the class as a V5 component derived from CATSAXHandlerBase
CATImplementClass( CAAXMLSAXResolverHandlers, Implementation, CATSAXHandlerBase, CATnull );

// Implement the CATISAXEntityResolver interface
#include "TIE_CATISAXEntityResolver.h"
TIE_CATISAXEntityResolver(CAAXMLSAXResolverHandlers);

// Implement the CATISAXErrorHandler interface
#include "TIE_CATISAXErrorHandler.h"
TIE_CATISAXErrorHandler(CAAXMLSAXResolverHandlers);

CAAXMLSAXResolverHandlers::CAAXMLSAXResolverHandlers(
	const CATUnicodeString& iDatabaseDir) {

	_databaseDir = iDatabaseDir;
}

CAAXMLSAXResolverHandlers::~CAAXMLSAXResolverHandlers() {
}

HRESULT CAAXMLSAXResolverHandlers::ResolveEntity(
	const CATUnicodeString & iPublicId, 
	const CATUnicodeString & iSystemId, 
	CATISAXInputSource_var& oInputSource) {

	CATUnicodeString message = "ResolveEntity(";
	message.Append(iPublicId);
	message.Append(", ");
	message.Append(iSystemId);
	message.Append(")");
	cout << message.ConvertToChar() << endl;

	CATSAXException* error = NULL;
	HRESULT hr = E_FAIL;

	// All system IDs must begin with this prefix
	CATUnicodeString prefix = "sql://";

	// Make sure the system ID has the expected form
	if (iSystemId.SubString(0, prefix.GetLengthInChar()) != prefix) {
		// Create an error and return it to the user.
		CATSAXException::CreateError(
			"CAAXMLSAXResolverHandlers::ResolveEntity",
			"invalid system ID",
			error);
	} else {
		CATIXMLSAXFactory_var factory;
		HRESULT hr2 = ::CreateCATIXMLSAXFactory(factory);
		if (SUCCEEDED(hr2) && (factory != NULL_var)) {
			// Compute the file path where the DTD is located.
			CATUnicodeString filePath = _databaseDir;
#ifdef _WINDOWS_SOURCE
			filePath.Append("\\");
#else
			filePath.Append("/");
#endif // _WINDOWS_SOURCE
			filePath.Append(iSystemId.SubString(prefix.GetLengthInChar(), iSystemId.GetLengthInChar() - prefix.GetLengthInChar()));
			
			// Create a SAX input source
			hr = factory->CreateInputSourceFromFile(filePath, "", oInputSource);
		}
	}

	// Handle possible errors.
	if (FAILED(hr)) {
		if (error != NULL) {
			return CATReturnError(error);
		} else {
			return CATReturnFailure;
		}
	} else {
		return CATReturnSuccess;
	}
}


HRESULT CAAXMLSAXResolverHandlers::Error ( 
	CATSAXParseException* iException) {

	// This event is sent by the CATISAXParser when an recoverable
	// (validation) error is met. 

	CATUnicodeString errorMessage = "Error : ";
	if (iException != NULL) {
		errorMessage.Append(iException->GetNLSMessage());
	}
	cerr << errorMessage.ConvertToChar() << endl;

	// Let the parser continue the parsing (if we returned E_FAIL, parsing would stop)
	return S_OK;
}

HRESULT CAAXMLSAXResolverHandlers::FatalError ( 
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

