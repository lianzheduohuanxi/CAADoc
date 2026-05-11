// COPYRIGHT DASSAULT SYSTEMES 2002

#ifndef CAAXMLSAXCountDocHandler_h
#define CAAXMLSAXCountDocHandler_h

// System framework
class CATUnicodeString;        // For NLS string operations

// XMLParser framework
class CATISAXAttributeList_var;
#include "CATSAXHandlerBase.h" // A default implementation of all SAX handler
                               // interfaces from which it is convenient to
                               // derive

/**
 * Step 1
 * Class to implement a custom handler for document events generated
 * by a CATISAXParser. The handler simply counts the occurrences of
 * various XML constructs in an XML document.
 */
class CAAXMLSAXCountDocHandler : public CATSAXHandlerBase {
	CATDeclareClass;
	public:
		/**
		 * Constructor
		 */
		CAAXMLSAXCountDocHandler();

		/**
		 * Destructor
		 */
		virtual ~CAAXMLSAXCountDocHandler();

		// Override the default implementation of the
		// CATISAXDocumentHandler methods we are interested in.
		virtual HRESULT Characters(
			const CATUnicodeString & iCharacters);
		
		virtual HRESULT EndDocument();
			
		virtual HRESULT IgnorableWhiteSpace(
			const CATUnicodeString & iCharacters);
		
		virtual HRESULT ProcessingInstruction(
			const CATUnicodeString & iTarget,
			const CATUnicodeString & iData);
		
		virtual HRESULT StartElement(
			const CATUnicodeString & iName, 
			const CATISAXAttributeList_var& iAttributes);

	private:
		unsigned int _characterCount;	// The number of text characters
		unsigned int _spaceCount;		// The number of ignorable space characters
		unsigned int _eltsCount;		// The number of elements
		unsigned int _attrCount;		// The number of attributes
		unsigned int _piCount;			// The number of processing instructions

};

#endif // CAAXMLSAXCountDocHandler_h
