// COPYRIGHT DASSAULT SYSTEMES 2005

#ifndef CAAXMLMultiFileStream_h
#define CAAXMLMultiFileStream_h

// System framework
class CATUnicodeString;                 // For NLS string operations
#include "CATListOfCATUnicodeString.h"  // To specify a list of files
#include "CATBaseUnknown.h"             // Base class for V5 components

/**
 * Step 1
 * Class to implement a custom input stream to parse XML content split over
 * several files.
 */
class CAAXMLMultiFileStream : public CATBaseUnknown {
	CATDeclareClass;
	public:
		/**
		 * Constructor
		 * @param iFiles
		 * The files to be read by this input stream.
		 */
		CAAXMLMultiFileStream(
			const CATListOfCATUnicodeString& iFiles);

		/**
		 * Destructor
		 */
		virtual ~CAAXMLMultiFileStream();

		// Implement the CATIXMLInputStream interface.
		virtual HRESULT Read(
			unsigned char* ioByteArray,
			unsigned int iByteArrayCapacity,
			unsigned int& oSizeRead);

	private:
		CATListOfCATUnicodeString _files;  // A list of files. Each file contains a piece of a large XML document.
		unsigned int _currentFile;         // The list index of the file currently being read.
		FILE* _fileDescriptor;             // The file descriptor of the file currently being read.

};

#endif // CAAXMLMultiFileStream_h
