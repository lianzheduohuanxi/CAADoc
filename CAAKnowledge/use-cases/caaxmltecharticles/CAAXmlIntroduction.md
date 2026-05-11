---
title: "Introduction to XML"
category: "general"
module: "CAAXmlTechArticles"
tags: ["CATIDOMElements", "CATIDOMText"]
source_file: "Doc\online\CAAXmlTechArticles\CAAXmlIntroduction.htm"
converted: "2026-05-11T17:33:45.680797"
---

# 3D PLM Enterprise Architecture

| 

## Middleware Abstraction

| 

### Introduction to XML

_Quick overview of XML fundamentals_  
---|---|---  
Technical Article  
  
* * *

### Abstract

This article explains what XML is. It gives an overview of the standards governing the various aspects of XML. It shows how XML can be used from the developer's point of view.

  * **What Is XML ?**
    * Anatomy of an XML Document
    * Well-formedness and Validity
  * **Presentation of the Core XML Standards**
    * De Jure Standards (W3C): XML 1.0, Schemas 1.0, DOM
    * De Facto Standards: SAX
  * **XML for the Developer**
    * A Document-oriented API: DOM
    * An Event-oriented API: SAX
  * **Choosing the Right API**
    * DOM Versus SAX
    * DTDs Versus Schemas

  
---  
  
* * *

### What Is XML ?

XML (Extensible Markup Language) is a data description language. XML has many strengths, which account for its great popularity and large availability:  


  * It has a simple text syntax based on elements identified by start and end tags. One can read or create XML easily with just a simple text editor.
  * It supports pluggable grammars (called DTDs or XSD schemas), which enable the creation of tag vocabularies for any domain.
  * It is very strictly standardized by the W3C (World Wide Web Consortium), which makes XML the ideal vehicle to exchange data among heterogeneous systems.



#### Anatomy of an XML Document

XML documents are composed of elements, delimited by a start tag (of the form `**<** element_name**>**`) and an end tag (of the form `**< /**element_name**>**`). Elements can contain either other elements or free text. Every XML document has one and only one root element, which contains all the other elements. The following XML sample is provided to illustrate the anatomy of an XML document.

![xmlsample.png \(15916 bytes\)](images/xmlsample.png)

The following syntactic constructs are the most common in XML documents.

The XML declaration
    It identifies the document as XML. Note the mandatory XML version number (1.0) and the description of the encoding (UTF-8) used by the document. XML documents can use any encoding, provided that the XML parser used to process the document knows how to deal with the encoding.
The document type declaration
    It identifies the DTD (tag vocabulary) used by the XML document and the tag name for the root element ("car"). This vocabulary is stored in an external file with the .dtd extension (automotive.dtd), though it can also be in-lined in the document. The document type declaration is optional and tends to be gradually replaced by another equivalent but more powerful mechanism, called XSD schemas.
The root element
    An XML has one and only one root element (called "car" here).
Elements
    An element is identified by a start tag and an end tag. If the element has no sub-elements, the syntax can optionally be abbreviated to just one tag, as for the "wheel" element. Notice the trailing '/' in this case.
Attributes
    The start tag can contain attributes, which are (name, value) pairs qualifying the element. Attribute names are unique within the tag scope. Attribute values appear within quotes. "body" is the value of the attribute called "name" of the "part" element.
Characters
    XML elements can also contain free text.
Entities
    XML use entities to escape reserved characters or specify characters not supported by the document code page. The "&lt;" entity is use here to escape the "<" reserved character.
Comments
    XML documents can be annotated with comments.

Other syntactic constructs (CDATA sections, processing instructions, etc.) can occasionally appear in XML documents. For a complete description of the XML syntax, please refer to [1].

[Top]

#### Well-formedness and Validity

XML files follow syntactic rules, some of which were just described in the previous section: there must be one and only one root element; attribute names must be unique within an element start tag scope; reserved XML characters such as '&' and '<' must be properly escaped, etc. An XML document, which obeys these syntactic rules is said to be **well formed**.
    
    
    <?xml version='1.0' encoding='UTF-8'?>
    <car><part name="engine"></car></part>
                                    ^
                                    |
       Not well-formed XML: the tags are not properly nested.
                
  
---  
  
The elements, which are allowed to appear in an XML documents and the order in which these elements are allowed to appear is described by a grammar file, called a DTD or an XSD schema. An XML document, which obeys all the rules specified by its associated grammar file is said to be **valid**.
    
    
    <?xml version='1.0' encoding='UTF-8'?>
    <!DOCTYPE car SYSTEM "automotive.dtd">
    <car>
     <part name="engine"></part>
     <aeroplane name="spitfire"/>
    </car>     ^
               |
               |
     Well-formed but invalid XML: aeroplane is not defined in the automotive DTD.
                
  
---  
  
[Top]

### Presentation of the Core XML Standards

The W3C (World Wide Web Consortium) is the standard body in charge of XML. The W3C does not only take care of the standardization of the language itself (see [1]); it also offers standardized programming APIs to manipulate XML documents. Aside from the W3C, other programming APIs have become very popular to the point of becoming de facto standards. Note that though XML is very stable and upward compatibility will be assured, the standard keeps evolving with revisions of the specifications (XML 1.1, XSD 1.1) or the apparition of newer programming paradigms.

[Top]

#### De Jure Standards (W3C): XML 1.0, Schemas 1.0, DOM

The following list presents the official W3C standards:

XML 1.0
    XML 1.0 specifies the syntax for the XML language. It also specifies the syntax of the historic XML grammar format, known as DTDs (Document Type Definition). For more information, see [1].
XML namespaces
    XML namespaces are a set of element naming patterns and attribute naming patterns. They enable the creation of documents, which mix elements from several vocabularies. Through the use of a prefix-based syntax and URIs, which uniquely identify vocabularies, namespaces avoid name clashes between identically named elements originating from different vocabularies. For more information, see [2].
XSD 1.0 schemas
    The XSD specification (XML Schema Definition) was designed as a replacement for DTDs. Schemas represent an improvement over DTDs in several areas. First, XSD schemas are XML files themselves, which provides greater coherency. Second, XSD schemas have a very sophisticated type system and can express constraints using regular expressions or define relational integrity constraints. For more information, see [3].
DOM 1.0, 2.0 and 3.0
    DOM (Document Object Model) is a programming API to read, manipulate and write XML documents. The core specification explains how to operate on XML documents as if they were trees of typed nodes. Complementary extensions to the specifications cover related utility APIs. For instance, extensions include "DOM traversal" (iterations through a XML document), "DOM range" (definition of selections), "DOM load/save" (persistence). For more information, see [4].

[Top]

#### De Facto Standards: SAX

Originally invented by David Megginson as a library for the Java programming language, the SAX API has become very popular and can be considered as a de facto standard. Many vendors provide their own implementation of SAX for various languages and the specification has already undergone one major evolution (SAX 2.0). For more information, see [6].

[Top]

### XML for the Developer

Developers wanting to create, access or manipulate data stored in XML have APIs at their disposal. This section gives an overview of the DOM and the SAX APIs, while the next section discusses the strengths and weaknesses of each API.

[Top]

#### A Document-oriented API: DOM

The DOM API uses an object-oriented approach to describe XML documents. The DOM API defines interfaces to represent each of the constructs available in the XML language: elements, attributes, documents, characters, entities, comments, etc. These interfaces have inheritance relationship (a "comment" is a specialized form of "character data"). The inheritance hierarchy is rooted at the abstract "node" class. The following diagram shows the DOM V5 interface hierarchy.

![domhierarchy.png \(8328 bytes\)](images/domhierarchy.png)

The DOM API views XML documents as a tree of XML nodes. The root element of the XML document corresponds to the root of the DOM tree. The sub-elements of the root element are the children of this root node. The following sample shows the DOM tree which corresponds to a sample XML document.
    
    
    <?xml version="1.0"?>
    <!DOCTYPE car SYSTEM "automotive.dtd">
    <car>
     <!--list of parts for a convertible car-->
     <part name="seat" quantity="2"></part>
     <part name="wheel" quantity="4"/>
     <part name="engine" quantity="1">low consumption engine</part>
     <part name="body" quantity="1">weight must be &lt; 1200 kg</part>
    </car>  
  
---  
  
![dominstance.png \(7116 bytes\)](images/dominstance.png)

The DOM API defines methods to parse documents (build the in-memory tree, which corresponds to an XML document), manipulate document (insert elements, edit attribute values, copy or delete sub-trees, etc.), and write documents (generate XML from an in-memory DOM tree).

[Top]

#### An Event-oriented API: SAX

The SAX API uses an event-oriented API to process XML documents. The XML SAX parser reads XML documents sequentially and emits one typed event for each XML construct it comes across: start of the document, start of an element, end of an element, comment, characters, etc. Programmers register callback functions with the SAX parser for the events they are interested in. Usually, programmers will need to store the generated events in a stack in order to keep track of the location of the event in the XML tree. The following list shows the SAX events, which are generated for a sample document.
    
    
    <?xml version="1.0"?>
    <!DOCTYPE car SYSTEM "automotive.dtd">
    <car>
     <!--list of parts for a convertible car-->
     <part name="seat" quantity="2"></part>
     <part name="wheel" quantity="4"/>
     <part name="engine" quantity="1">low consumption engine</part>
     <part name="body" quantity="1">weight must be &lt; 1200 kg</part>
    </car>  
  
---  
      
    
    1. Start document
    2. Start element "car"
    3. Start element "part", attributes {"name=seat", "quantity=2"}
    4. End element "part"
    5. Start element "part", attributes {"name=wheel", "quantity=4"}
    6. End element "part"
    7. Start element "part", attributes {"name=engine", "quantity=1"}
    8. Characters "low consumption engine"
    9. End element "part"
    10. Start element "part", attributes {"name=body", "quantity=1"}
    11. Characters "weight must be < 1200 kg"
    12. End element "part"
    13. End element "car"
    14. End document
                
  
---  
  
[Top]

### Choosing the Right API

XML often provides more than one mechanism to address the same problem. Choosing the right mechanism is a matter of understanding its trade-offs in terms of performance, ease of development, supported features, etc.

[Top]

#### DOM Versus SAX

The main advantages of DOM are:

  * DOM is easy to understand.
  * You do not have to create an object model of your own to store the data in memory, since DOM already provides one with its tree model.
  * DOM is very good at document manipulation: removing a sub-tree, changing attribute values or duplicating a portion of one document in another is very easy with DOM.
  * DOM lets you create XML documents, not just read existing ones.



The main weaknesses of DOM are:

  * DOM uses a lot of memory.
  * DOM cannot work with not well-formed or invalid XML data. If the document is not well-formed, the DOM tree cannot be built.
  * Navigation in the DOM tree can be tricky. For instance, if two elements are separated by white space in an XML document (even a carriage return), a CATIDOMText will be inserted between the two CATIDOMElements, which is not very intuitive (humans have a natural tendency to skip the white space and consider the elements consecutive).



The main advantages of SAX are:

  * SAX can parse arbitrarily big XML files. It does not use a lot of memory and is faster than DOM.
  * SAX can recover from errors (not all of them though) and allow the processing of incorrect XML documents to continue.



The main weaknesses of SAX are:

  * SAX does not support the creation of XML files. It is designed for parsing only.
  * SAX is not as widespread as DOM and has no standard body backing it. Some platforms (.NET for instance) do not support it.



In summary, **use DOM if** you need to manipulate files no larger than a few megabytes or if your application uses XML itself as the data model. Typical candidates would be storing settings in XML, or manipulating contents in XHTML. **Use SAX if** you need to manipulate arbitrary large files or if you need to map you own object model to XML. Typical candidates would be persistency of an object graph in XML, or processing large log files containing events generated by a server.

[Top]

#### DTDs Versus Schemas

DTD and schemas address the same problem: defining tag vocabularies (grammars) for XML documents. They are to XML documents what the description of tables and relationships is to a relational database. The following example shows how an XML grammar defined as a DTD. The grammar defines two elements (car and part). The part element element can have two attributes ("name" and "quantity"). Several "part" elements can be nested inside a "car" element. Part elements can contain text.
    
    
    <!ELEMENT car (part)+>
    <!ELEMENT part (#PCDATA)>
    <!ATTLIST part name ID #REQUIRED
              quantity CDATA #IMPLIED>  
  
---  
  
Here is an equivalent grammar defined as an XSD schema:
    
    
    <?xml version="1.0" encoding="UTF-8"?>
    <xsd:schema xmlns:xsd="http://www.w3.org/2001/XMLSchema" 
     elementFormDefault="qualified" 
     targetNamespace="urn:com:dassault_systemes:automotive" 
     xmlns:tns="urn:com:dassault_systemes:automotive">
     <xsd:element name="car">
      <xsd:complexType>
       <xsd:sequence maxOccurs="unbounded">
        <xsd:element name="part" type="tns:partType"/>
       </xsd:sequence>
      </xsd:complexType>
     </xsd:element>
     <xsd:complexType name="partType">
      <xsd:simpleContent>
       <xsd:extension base="xsd:string">
        <xsd:attribute name="name" type="xsd:ID" use="required"/>
        <xsd:attribute name="quantity" type="xsd:positiveInteger"/>
       </xsd:extension>
      </xsd:simpleContent>
     </xsd:complexType>
    </xsd:schema>  
  
---  
  
The main advantages of DTDs are:

  * DTDs are simple and easy to understand.
  * DTD is the historic grammar format for XML and has thus good diffusion and broad support.



The main weaknesses of DTDs are:

  * DTDs use yet another syntax.
  * DTDs cannot express complex relationships or type constraints. DTDs do not have the concept of data type so everything is viewed as text.



The main advantages of XSD schemas are:

  * Schemas are very powerful. They have a rich type system. They have a relational integrity constraint definition mechanism close to the one of a relational database. They support regular expressions.
  * Schemas are written in XML themselves. All the XML manipulation tools can thus be reused for schemas.
  * Schemas can be created to replace existing DTDs: All the DTD constructs have an equivalent XSD schema construct. Tools exist to do the conversion automatically.



The main weaknesses of XSD schemas are:

  * XSD is a complex standard. Writing good XSD schemas requires experience and tools. A good introductory text for XSD schemas is referenced here [5]



In summary, your choice for DTDs or schemas will first depend on what is available: make the list of the products you need to integrate and choose a grammar language supported by all the systems. **Use DTDs if** if you are new to XML and want to get started quickly; if you need to develop a prototype and do not want to spend much time on a grammar; if you need to integrate with a system, which only supports DTDs. **Use schemas if** you need a precise definition of your data model; you have tools or expertise to help you define the schema.

[Top]

* * *

### In Short

XML is a data description language. Its simplicity, strict standardization, broad availability, and tools support make it a good vehicle to exchange data among heterogeneous systems.

[Top]

* * *

### References

[1] | Extensible Markup Language (XML) 1.0 (Third Edition) - W3C Recommendation 04 February 2004  
---|---  
[2] | Namespaces in XML  
[3] | XML Schema - W3C schema home page February 2004  
[4] |  Document Object Model (DOM) Technical Reports - W3C DOM home page  
[5] |  XML Schema Part 0: Primer Second Edition  
[6] |  XML SAX (Simple API for XML)  
[Top]  
  
* * *

### History

Version: **1** [Apr 2005] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2005, Dassault Systmes. All rights reserved._
