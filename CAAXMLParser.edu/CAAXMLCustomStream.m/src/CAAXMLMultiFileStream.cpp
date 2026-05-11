// COPYRIGHT DASSAULT SYSTEMES 2005

// Local framework
#include "CAAXMLMultiFileStream.h" // Import the definition of the component

// System framework
#include "CATUnicodeString.h"     // For NLS string operations

// XMLParser framework
#include "CATSAXParseException.h" // To represent SAX parse errors.
#include "CATError.h"             // V5 error handling functions

// Standard C++ library
#include <iostream.h>
#include <stdio.h>

// Declare the class as a V5 component
CATImplementClass( CAAXMLMultiFileStream, Implementation, CATBaseUnknown, CATnull );

// Implement the CATIXMLInputStream interface
#include "TIE_CATIXMLInputStream.h"
TIE_CATIXMLInputStream(CAAXMLMultiFileStream);

CAAXMLMultiFileStream::CAAXMLMultiFileStream(
	const CATListOfCATUnicodeString& iFiles) {

	_files = iFiles;
	_currentFile = 0;
	_fileDescriptor = 0;
}

CAAXMLMultiFileStream::~CAAXMLMultiFileStream() {
	// Close pending open files if any.
	if (_fileDescriptor != 0) {
		fclose(_fileDescriptor);
		_fileDescriptor = 0;
	}
}

HRESULT CAAXMLMultiFileStream::Read(
	unsigned char* ioByteArray,
	unsigned int iByteArrayCapacity,
	unsigned int& oSizeRead) {

	HRESULT hr = S_OK;
	oSizeRead = 0; 

	// Attempt to read as much XML as asked by the parser.
	while (oSizeRead < iByteArrayCapacity) {
		// All the pieces of XML have been read already.
		if (_currentFile >= _files.Size()) {
			break;
		}

		// Open the next file if there is no current file.
		if (_fileDescriptor == 0) {
			_fileDescriptor = fopen(_files[_currentFile + 1].ConvertToChar(), "rb");
			if (_fileDescriptor == 0) {
				hr = E_FAIL;
				break;
			}
		}

		// Read as much XML as possible to saturate the buffer passed by the XML parser.
		unsigned int sizeRead = fread((char*)ioByteArray + oSizeRead, sizeof(char), iByteArrayCapacity - oSizeRead, _fileDescriptor);
		if (ferror(_fileDescriptor)) {
			hr = E_FAIL;
			break;
		}
		oSizeRead += sizeRead;

		// Close the current file once it has been exhausted and move to the next file.
		if (sizeRead == 0) {
			fclose(_fileDescriptor);
			_fileDescriptor = 0;
			_currentFile++;
		}
	}
	return hr;
}



