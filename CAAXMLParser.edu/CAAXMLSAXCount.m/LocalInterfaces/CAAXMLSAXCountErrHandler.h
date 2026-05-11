// COPYRIGHT DASSAULT SYSTEMES 2002

#ifndef CAAXMLSAXCountErrHandler_h
#define CAAXMLSAXCountErrHandler_h

// System framework
class CATUnicodeString;        // For NLS string operations

// XMLParser framework
class CATSAXParseException;    // To represent SAX parse errors.
#include "CATSAXHandlerBase.h" // A default implementation of all SAX handler
                               // interfaces from which it is convenient to
                               // derive

/**
 * Step 2
 * Class to implement a custom handler for error events generated
 * by a CATISAXParser.
 */
class CAAXMLSAXCountErrHandler : public CATSAXHandlerBase {
	CATDeclareClass;
	public:
		/**
		 * Constructor
		 */
		CAAXMLSAXCountErrHandler();

		/**
		 * Destructor
		 */
		virtual ~CAAXMLSAXCountErrHandler();

		// Override the default implementation of the
		// CATISAXErrorHandler methods we are interested in.
		virtual HRESULT Error ( 
			CATSAXParseException* iException);
		virtual HRESULT FatalError ( 
			CATSAXParseException* iException);

};

#endif // CAAXMLSAXCountErrHandler_h
