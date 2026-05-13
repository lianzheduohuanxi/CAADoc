---
```vbscript
title: "Using XML in V5"
category: tech-article
module: "CAAXmlTechArticles"
tags: ["CATIDOMElement", "CATIDOM", "CATIXMLSAXFactory_var", "CATISAXDocumentHandler", "CATIXML", "CATIDOMNode_var", "CATISAXAttributeList_var", "CATIDOMImplementation", "CATIDOMDocument_var", "CATISAXErrorHandler", "CATISAXInputSource_var", "CATIDOMXXX_var", "CATIXMLSAXFactory", "CATISAXYYY_var", "CATIXMLDOMDocumentBuilder", "CATISAXInputSource", "CATIDOMDocumentType_var", "CATIDOMElement_var", "CATIXMLDOMDocumentBuilder_var", "CATISAXEntityResolver"]
source_file: "Doc/online/CAAXmlTechArticles/CAAXmlV5Overview.htmmd"
converted: "2026-05-11T17:33:45.712135"
```

---
# 3D PLM Enterprise Architecture

|
## Middleware Abstraction

|
### Using XML in V5

_Description of the XML infrastructure available in V5_
---|---|---
Technical Article

* * *
### Abstract

This article explains what is an XML parser. It describes the parsers available in V5, lists their capabilities and discusses how to create them. It also discusses how these V5 parsers integrate existing XML standards.

  * **V5 XML parser Components**
    * Support for Multiple Parsers
    * Choosing the Right Parser
  * **Use of XML Standards in V5**
    * V5 C++ Bindings for DOM
    * V5 C++ Bindings for SAX
  * **Supported XML Encodings**
    * UTF-8
    * Other Supported Encodings

---

* * *
### V5 XML Parser Components

The component, which processes raw XML content and allows the developer to access and manipulate this content from a DOM or a SAX API is called an XML parser. Rather than developing its own XML parser, Dassault Systèmes chooses to rely on its software partners and integrate existing parsers. All these parsers support the DOM and SAX APIs, but there are differences between them:

  * They do not use the C++ language in the same way: due to the lack of universal conventions in C++, each parser defines its own string class, its own way to manage errors, its own way to represent an interface, etc.
  * They have different features: support for DTD validation, support for schema validation, availability for a given operating system, etc.

To make the development of XML-based solutions easier for CAA developers, the XMLParser framework provides CAA developers with the following functionality:

  * An API to instantiate the various XML parsers available in V5.
  * A set of V5 interfaces (based on the DOM or the SAX models) to access all the parsers in a uniform, v5-friendly way.
  * An adaptor layer which makes the various XML parsers accessible through the V5 interfaces in a uniform way.

![xmlparsers.png /(9296 bytes/)](images/xmlparsers.png)
#### Support for Multiple Parsers

Each parser component in the XMLParser framework is identified by a GUID. To instantiate the parser, developers invoke a global function, passing it the identifier of the parser they want to use. Since there are two families of APIs (DOM and SAX), there are two global functions. If the developer fails to pass an identifier, a default value is used (corresponding to the XML4C3 parser).

The following sample shows how to instantiate a DOM parser backed by the XML4C5 parser component:

    #include "CATIXMLDOMDocumentBuilder.h"  // To create the DOM objects

The following sample shows how to instantiate a DOM parser backed by the XML4C5 parser component:
    CATIXMLDOMDocumentBuilder_var builder;
    HRESULT hr = CreateCATIXMLDOMDocumentBuilder(builder, CLSID_XML4C5_DOM);

---

CATIXMLDOMDocumentBuilder_var builder;
HRESULT hr = CreateCATIXMLDOMDocumentBuilder(builder, CLSID_XML4C5_DOM);
The following sample shows how to instantiate a SAX parser backed by the XML4C5 parser component:

    #include "CATIXMLSAXFactory.h"       // To create the SAX objects

The following sample shows how to instantiate a SAX parser backed by the XML4C5 parser component:
    CATIXMLSAXFactory_var factory;
    HRESULT hr = CreateCATIXMLSAXFactory(factory, CLSID_XML4C5_SAX);

---

CATIXMLSAXFactory_var factory;
HRESULT hr = CreateCATIXMLSAXFactory(factory, CLSID_XML4C5_SAX);
_Compatibility between parsers_

![warning.gif /(206 bytes/)](../CAAIcons/images/warning.gif) DOM V5 components have dependencies on SAX V5 components. For instance a DOM parser needs to be able to fetch XML from various physical sources (an HTTP server, a file, a relational database, etc.); rather than defining yet another interface for input sources, the V5 DOM parser accepts parsing from a CATISAXInputSource; to create such input sources, one uses the V5 SAX component.

![warning.gif /(206 bytes/)](../CAAIcons/images/warning.gif) V5 parsers are not interoperable: you cannot append a _CATIDOMElement_ created with XML4C3 to a _CATIDOMElement_ created with XML4C5. However, several parsers can coexist in the same process.

[Top]
#### Choosing the Right Parser

The following table gives an overview of the features supported by each parser.

  | X4C3 | X4C5 | MSXML3 | MSXML4 | MSXML5
---|---|---|---|---|---
The following table gives an overview of the features supported by each parser.
DOM level 1 and 2 | Yes | Yes | Yes (1) | Yes (1) | Yes (1)
DOM traversal | Yes | Yes | Yes (2) | Yes (2) | Yes (2)
SAX 1 | Yes | Yes | Yes (3)(2) | Yes (4)(2) | Yes (4)(2)
SAX 2 | Yes (5) | Yes | Yes (5) | Yes (6) | Yes (6)
DTD validation | Yes | Yes | Yes (7) | Yes (7) | Yes (7)
XSD schema validation | No | Yes | No | Yes | Yes
Unix availability | Yes | Yes | No | No | No
Windows availability | Yes | Yes | Yes | Yes | Yes

  1. Some functions are emulated in the V5 adapter
  2. Emulated in the V5 adapter
  3. DTD and XSD schema validation is not supported
  4. XSD Schema validation is not supported
  5. DTD and XSD schema validation is not supported
  6. Schema validation is not supported
  7. Not supported for SAX1 and SAX2

In summary, you can use the following rules to choose the parser, which best suits your needs:

  * **Use XML4C3:** for simple DOM or SAX1 applications, which do not require XSD schema validation.
  * **Use XML4C5:** for DOM or SAX2 applications, which require XSD schema validation.
  * **Use MSXML, with the highest possible level installed on the machine:** for Windows-only applications, which download code and want to minize the downloaded code size (browser plug-ins). Indeed, these parsers are often pre-installed with Windows.

[Top]
### Use of XML Standards in V5

The XMLParser framework defines two classes of XML APIs: standard APIs and additional APIs created by Dassault Systèmes.

  * The standard APIs are the exact image of the W3C DOM specification or the SAX specification. Nothing has been added to or removed from the specification. Therefore, the information you can find on DOM or SAX in books, magazine or on-line tutorials can directly be put in practice in a V5 context using these APIs. To recognize these APIs more easily, the following naming patterns are used: DOM interfaces use the prefix **CATIDOM** ; DOM classes use the prefix **CATDOM** ; SAX interfaces use the prefix **CATISAX** ; SAX classes use the prefix **CATSAX**.
  * Additional APIs were created by Dassault Systèmes to fulfil two needs. First, fill the gaps of the DOM and SAX standards, which do not define the mechanisms to create a DOM or a SAX parsers or to configure them. Second, add useful functionalities, which were missing from the standard, for instance the capabilty to create an XML document from a DOM tree. To recognize these APIs more easily, the following naming pattern is used: additional XML interfaces use the prefix **CATIXML**.

The following two sections give you more information as to how XML standard specifications have been adapted for V5.

[Top]
#### V5 C++ Bindings for DOM

The following two sections give you more information as to how XML standard specifications have been adapted for V5.
The DOM specification uses OMG IDL to define its APIs in an abstract, platform-neutral way. It is then up to each platform to define a binding, that is a concrete version of the APIs using the language and data types native to the platform. The following table explains how this is done for V5 in C++.

OMG IDL | V5 C++ | Comment

The DOM specification uses OMG IDL to define its APIs in an abstract, platform-neutral way. It is then up to each platform to define a binding, that is a concrete version of the APIs using the language and data types native to the platform. The following table explains how this is done for V5 in C++.
OMG IDL | V5 C++ | Comment
DOMString | CATUnicodeString | All the strings obtained from parsing an XML document are represented as _CATUnicodeStrings_ : element names, attribute values, characters, entity names, etc.
DOM exception | HRESULT + CATError | The usage for V5 code is to signal errors using _HRESULTs_. Additional information about the error can be obtained using the CATError mechanism. See [1] for more information.
interface XXX | V5 interface handler CATIDOMXXX_var | All DOM interfaces are represented by V5 interface handlers. The V5 naming conventions are respected by prepending the "CATIDOM" prefix to the original DOM name (Thus, the _Node_ interface from the specification is mapped to _CATIDOMNode_var_ interface handler in V5 C++, the _Element_ interface is mapped to the _CATIDOMElement_var_ interface handler and so on).
rettype method(arg1, arg2, ..., argN) raises DOMException | HRESULT Method(arg1, arg2, ..., argN, rettype) | Methods bear the same name in V5 as in the specification, with the first letter in capital to obey the V5 naming convention. If the specification indicates a return value for the method, the corresponding V5 method will have an additional out parameter to return this argument. The exceptions declared by the method are replaced by a _HRESULT_.
boolean | CATBoolean |
unsigned long | unsigned int |

As a concrete example of how the binding works, please consider the abstract definition of the DOMImplementation extracted from DOM specification.

    interface DOMImplementation {
     boolean hasFeature(
               in DOMString feature,
               in DOMString version);

     // Introduced in DOM Level 2:
interface DOMImplementation {
boolean hasFeature(
in DOMString feature,
in DOMString version);
     DocumentType createDocumentType(
                    in DOMString qualifiedName,
                    in DOMString publicId,
                    in DOMString systemId) raises(DOMException);

     // Introduced in DOM Level 2:
DocumentType createDocumentType(
in DOMString qualifiedName,
in DOMString publicId,
in DOMString systemId) raises(DOMException);
     Document createDocument(
                 in DOMString namespaceURI,
                 in DOMString qualifiedName,
                 in DocumentType doctype) raises(DOMException);

    };

---

In V5, you will manipulate the following V5 interface

In V5, you will manipulate the following V5 interface
    class CATIDOMImplementation : public CATBaseUnknown {
     virtual HRESULT HasFeature(
                       const CATUnicodeString& iFeature,
                       const CATUnicodeString& iVersion,
                       CATBoolean& oResult) = 0;

     // Introduced in DOM Level 2:
virtual HRESULT HasFeature(
const CATUnicodeString& iFeature,
const CATUnicodeString& iVersion,
CATBoolean& oResult) = 0;
     virtual HRESULT CreateDocumentType(
                      const CATUnicodeString& iQualifiedName,
                      const CATUnicodeString& iPublicId,
                      const CATUnicodeString& iSystemId,
                      CATIDOMDocumentType_var& oDocumentType) = 0;

     // Introduced in DOM Level 2:
const CATUnicodeString& iQualifiedName,
const CATUnicodeString& iPublicId,
const CATUnicodeString& iSystemId,
CATIDOMDocumentType_var& oDocumentType) = 0;
     virtual HRESULT CreateDocument(
                      const CATUnicodeString& iNamespaceURI,
                      const CATUnicodeString& iQualifiedName,
                      const CATIDOMDocumentType_var& iDocumentType,
                      CATIDOMDocument_var& oDocument) = 0;

    };

---

[Top]
#### V5 C++ Bindings for SAX

The SAX specification uses Java to define its APIs. Platforms, which do not use Java as their programming language define a binding for their language, that is a version of the APIs using the language and data types native to the platform. The following table explains how this is done for V5 in C++.

The SAX specification uses Java to define its APIs. Platforms, which do not use Java as their programming language define a binding for their language, that is a version of the APIs using the language and data types native to the platform. The following table explains how this is done for V5 in C++.
Java SAX definition | V5 C++ | Comment

The SAX specification uses Java to define its APIs. Platforms, which do not use Java as their programming language define a binding for their language, that is a version of the APIs using the language and data types native to the platform. The following table explains how this is done for V5 in C++.
Java SAX definition | V5 C++ | Comment
java.lang.String | CATUnicodeString | All the strings obtained from parsing an XML document are represented as _CATUnicodeStrings_ : element names, attribute values, characters, entity names, etc.
java.io.Exception
org.xml.sax.SAXException | HRESULT + CATError | The usage for V5 code is to signal errors using _HRESULTs_. Additional information about the error can be obtained using the CATError mechanism. See [1] for more information.
interface YYY | V5 interface handler CATISAXYYY_var | All SAX interfaces are represented by V5 interface handlers. The V5 naming conventions are respected by prepending the "CATISAX" prefix to the original SAX name (Thus, the _ErrorHandler_ interface from the specification is mapped to _CATISAXErrorHandler_var_ interface handler in V5 C++, the _AttributeList_ interface is mapped to the _CATISAXAttributeList_var_ interface handler and so on).
rettype method(arg1, arg2, ..., argN) throws SAXException | HRESULT Method(arg1, arg2, ..., argN, rettype) | Methods bear the same name in V5 as in the specification, with the first letter in capital to obey the V5 naming convention. If the specification indicates a return value for the method, the corresponding V5 method will have an additional out parameter to return this argument. The exceptions declared by the method are replaced by a _HRESULT_.
org.xml.sax.HandlerBase
org.xml.sax.DefaultHandler
org.xml.sax.DefaultXMLFilter | CATSAXHandlerBase
CATSAXDefaultHandler
CATSAXDefaultXMLFilter | Classes providing a default implementation for SAX interfaces are represented in V5 by a V5 component providing a default implementation for the same SAX interface. The V5 naming conventions are respected by prepending the "CATSAX" prefix to the original SAX name. Thus, the _HandlerBase_ Java class, which implements the _DocumentHandler_ , _DTDHandler_ , _EntityResolver_ and _ErrorHandler_ Java SAX interfaces is mapped to the _CATSAXHandlerBase_ V5 component, which implements the _CATISAXDocumentHandler_ , _CATISAXDTDHandler_ , _CATISAXEntityResolver_ and _CATISAXErrorHandler_ V5 interfaces
boolean | CATBoolean |
int | unsigned int |

As a concrete example of how the binding works, please consider the Java definition of the EntityResolver extracted from SAX specification.

    package org.xml.sax;
    public interface EntityResolver {
     InputSource resolveEntity(
       String publicId,
       String systemId) throws SAXException, IOException;

    }

---

In V5, you will manipulate the following V5 interface

In V5, you will manipulate the following V5 interface
    class CATISAXEntityResolver: public CATBaseUnknown {
     virtual HRESULT ResolveEntity(
                       const CATUnicodeString & iPublicId,
                       const CATUnicodeString & iSystemId,
                       CATISAXInputSource_var & oInputSource) = 0;

    };

---

[Top]
### Supported XML Encodings

The XML specification defines the XML syntax using the character model defined by the Unicode specification. XML contents however can be stored in text using any encoding (code page) provided that the underlying parsers support them. To use a given encoding for an XML file, you need to:

The XML specification defines the XML syntax using the character model defined by the Unicode specification. XML contents however can be stored in text using any encoding (code page) provided that the underlying parsers support them. To use a given encoding for an XML file, you need to:
  1. Encode the file with this encoding.
  2. Indicate in the XML declaration the encoding you have used.

    <?xml version='1.0' encoding='UTF-8'?>
    ... content encoded in UTF-8 ...

---

[Top]
#### UTF-8

The XML specification mandates that XML parsers support UTF-8. Therefore, this encoding is universally available. Furthermore, this encoding supports the whole Unicode standard, which guarantees that national characters can be read and written on any machine in the world without loss or corruption, or need to install a specific code page configuration file.

![warning.gif /(206 bytes/)](../CAAIcons/images/warning.gif)When you have the choice of the encoding, use the UTF-8 encoding.

[Top]
#### Other Supported Encodings

A few other encodings are also supported by the XMLParser framework.

A few other encodings are also supported by the XMLParser framework.
UTF-16
    Can sometimes be more compact that UTF-8 for eastern languages.
ISO-8859-1
    Can be used for XML, which contains only characters from the Latin 1 character set.
SHIFT_JIS
    Can be used for XML, which contains Japanese characters.

[Top]

* * *
### In Short

The XMLParser framework provides several parsers. All these parsers are accessible through the same V5 DOM or SAX APIs. Choice of the parser depends on requirements of the target application.

[Top]

* * *
### References

[1] | [ Managing Errors Using HRESULT](../CAASysTechArticles/CAASysErrors.md)
---|---

* * *
### History

Version: **1** [Apr 2005] | Document created
---|---
[Top]

* * *

_Copyright 2005, Dassault Systmes. All rights reserved._
