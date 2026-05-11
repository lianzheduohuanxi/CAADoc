// COPYRIGHT DASSAULT SYSTEMES 2002

#ifndef CAAXMLSAXResolverHandlers_h
#define CAAXMLSAXResolverHandlers_h

// System framework
#include "CATUnicodeString.h"  // For NLS string operations

// XMLParser framework
class CATSAXParseException;    // To represent SAX parse errors.
#include "CATSAXHandlerBase.h" // A default implementation of all SAX handler
                               // interfaces from which it is convenient to
                               // derive

/**
 * Step 1
 * Class to implement a custom handler for entity events and error events generated
 * by a CATISAXParser.
 */
class CAAXMLSAXResolverHandlers : public CATSAXHandlerBase {
	CATDeclareClass;
	public:
		/**
		 * Constructor
		 * @param iDatabaseDir
		 * The directory where the handler will look for DTD files.
		 */
		CAAXMLSAXResolverHandlers(
			const CATUnicodeString& iDatabaseDir);

		/**
		 * Destructor
		 */
		virtual ~CAAXMLSAXResolverHandlers();

		// Override the default implementation of the
		// CATISAXErrorHandler methods we are interested in.
		virtual HRESULT ResolveEntity(
			const CATUnicodeString & iPublicId, 
			const CATUnicodeString & iSystemId, 
			CATISAXInputSource_var& oInputSource);
		virtual HRESULT Error ( 
			CATSAXParseException* iException);
		virtual HRESULT FatalError ( 
			CATSAXParseException* iException);

	private:
		CATUnicodeString _databaseDir;

};

#endif // CAAXMLSAXResolverHandlers_h
