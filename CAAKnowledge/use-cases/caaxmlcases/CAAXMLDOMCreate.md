---
title: "Creating XML documents with DOM"
category: "use case"
module: "CAAXmlUseCases"
tags: ["CATIDOMElement", "CAAXMLParser", "CAAXMLDOMCreate", "CATIDOMComment", "CATIXMLDOMDocumentBuilder", "CATIDOMImplementation", "CATIXMLDOMDocumentBuilder_var", "CATIDOMDocument_var", "CATIDOMDocument", "CATIDOMImplementation_var", "CATIDOMDocumentType_var", "CATIDOMText_var", "CATIDOMComment_var", "CATIDOMText", "CATIDOMElement_var"]
source_file: "Doc\online\CAAXmlUseCases\CAAXMLDOMCreate.htm"
converted: "2026-05-11T17:33:45.610569"
---

# 3D PLM Enterprise Architecture

| 

## Middleware Abstraction

| 

### Creating XML Documents with DOM

_Creating a new XML document from scratch using the DOM API_  
---|---|---  
Use Case  
  
* * *

### Abstract

This article shows how to create a new DOM tree from scratch using the DOM API and how to save it to disk as an XML file.

  * **What You Will Learn With This Use Case**
  * **The CAAXMLDOMCreate Use Case**
    * What Does CAAXMLDOMCreate Do
    * How to Launch CAAXMLDOMCreate
    * Where to Find the CAAXMLDOMCreate Code
  * **Step-by-Step**
  * **In Short**
  * **References**

  
---  
  
* * *

### What You Will Learn With This Use Case

This use case shows how to create XML documents from scratch using the DOM API. You will learn to create the most common XML constructs: document type declarations, elements, attributes, comments, and text nodes. You will learn how to save these constructs to disk to obtain an XML file.

[Top]

### The CAAXMLDOMCreate Use Case

The CAAXMLDOMCreate Use Case is a use case of the CAAXMLParser.edu framework that illustrates XMLParser framework capabilities.

[Top]

#### What Does CAAXMLDOMCreate Do

This use case creates a new XML document in memory, then saves it to disk under the specified name. Upon completion, you will obtain an XML file describing a car, created programmatically through DOM, with the following content:
    
    
    <?xml version="1.0"?>
    <!DOCTYPE car SYSTEM "automotive.dtd">
    <car>
     <!--list of parts for a convertible car-->
     <part name="seat" quantity="2"></part>
     <part name="wheel" quantity="4"/>
     <part name="engine" quantity="1">low consumption engine</part>
     <part name="body" quantity="1">weight must be < 1200 kg</part>
    </car>  
  
---  
  
[Top]

#### How to Launch CAAXMLDOMCreate

To launch CAAXMLDOMCreate, you will need to set up the build time environment, then compile CAAXMLDOMCreate along with its prerequisites, set up the run time environment, and then execute the use case [1].

The use case should be launched as follows from the command line:
    
    
    CAAXMLDOMCreate <outfilepath>

where `<outfilepath>` is the path of the XML file, which will be created.

[Top]

#### Where to Find the CAAXMLDOMCreate Code

The CAAXMLDOMCreate use case is made of one file located in the CAAXMLDOMCreate.m module of the CAAXMLParser.edu framework:

Windows | `InstallRootDirectory\CAAXMLParser.edu\CAAXMLDOMCreate.m\`  
---|---  
Unix | `InstallRootDirectory/CAAXMLParser.edu/CAAXMLDOMCreate.m/`  
  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]

### Step-by-Step

To create a blank XML document, populate it and save it to disk, there are seven main steps:

# |  Step  
---|---  
1 | Create the V5 DOM Component  
2 | Obtain the DOM Implementation  
3 | Use the DOM Implementation to Create a Document With the Proper Document Type  
4 | Use the Document to Create Elements, Texts, and Comments  
5 | Create the Tree Structure by Positionning the Elements, Texts, and Comments with Respect to Each Other  
6 | Save the Document as an XML File  
7 | Manage Errors  
  
Please note that most of the APIs from the XMLParser framework return a _HRESULT_. To avoid excessive indentation of the code, which would cause poor readibility, the following coding style has been used: the whole code is put in a `do {} while(0)` loop; if one of the APIs returns a bad HRESULT, the execution is stopped with a `break` and the error handler is invoked.
    
    
    HRESULT hr = E_FAIL;
    do {
        hr = XMLParserAPI_1();
        if (FAILED(hr)) { break; }
        hr = XMLParserAPI_2();
        if (FAILED(hr)) { break; }
        ...
        hr = XMLParserAPI_N();
        if (FAILED(hr)) { break; }
    } while(0);
    if (FAILED(hr)) {
        // Error handling code.
    }  
  
---  
  
[Top]

#### Create the V5 DOM Component
    
    
    ...
    CATIXMLDOMDocumentBuilder_var builder;
    HRESULT hr = **::CreateCATIXMLDOMDocumentBuilder**(builder);
    ...  
  
---  
  
The first step to work with DOM is to instantiate the V5 DOM component. The V5 DOM component can be created by calling the `CreateCATIXMLDOMDocumentBuilder` global function. This function returns a V5 handler on the _CATIXMLDOMDocumentBuilder_ interface, which is the main interface for the V5 DOM component. Using this interface you will be able to create documents (either from scratch, as here, or by parsing an existing XML file) and save existing documents to disk. Note that the code above does not specify the CLSID of the component to use, so the default DOM component (XML4C3) will be used. See [3] and [4] if you want to use another V5 DOM component.

[Top]

#### Obtain the DOM Implementation
    
    
    ...
    CATIDOMImplementation_var implementation;
    hr = builder->**GetDOMImplementation**(implementation);
    ...  
  
---  
  
To create document types and documents, one uses an object, which implements the _CATIDOMImplementation_ interface. This object is obtained from the _CATIXMLDOMDocumentBuilder_ by invoking its `GetDOMImplementation` method.

[Top]

#### Use the DOM Implementation to Create a Document with the Proper Document Type
    
    
    ...
    CATIDOMDocumentType_var docType;
    hr = implementation->**CreateDocumentType**("car", "", "automotive.dtd", docType);
    ...
    
    CATIDOMDocument_var document;
    hr = implementation->**CreateDocument**("", "car", docType, document);
    ...  
  
---  
  
The _CATIDOMImplementation_ interface acts as a factory to create DOM document types and DOM documents. The `CreateDocumentType` creates a new document type declaration and accepts the following parameters:

`"car"` | The name of the root element  
---|---  
`""` | A public id (not used here)  
`"automotive.dtd"` | The name of an external file, which contains all the grammatical constructs  
`docType` | the resulting document type returned by reference.  
  
Note that the `CreateDocumentType` method only creates the document type declaration (ie: the line `<!DOCTYPE car SYSTEM "automotive.dtd">)`, not the external DTD file. Since such a file is not in XML, it is usually created by other means (a text editor or a more powerful tool) by the developer in charge of creating the grammar to describe the targeted domain.

The `CreateDocument` method creates a new DOM document. It accepts the following parameters:

`""` | The namespace of root element  
---|---  
`"car"` | The name of the root element  
`docType` | The previously created document type. Passing `NULL_var` will cause the document type declaration to be omitted in the generated XML  
`document` | the resulting document returned by reference.  
  
[Top]

#### Use the Document to Create Elements, Texts, and Comments
    
    
    ...
    CATIDOMElement_var car;
    hr = document->**CreateElement**("car", car);
    ...
    CATIDOMElement_var seat;
    hr = document->**CreateElement**("part", seat);
    ...
    CATIDOMElement_var engine;
    hr = document->**CreateElement**("part", engine);
    ...
    hr = engine->SetAttribute("name", "engine");
    ...
    hr = engine->SetAttribute("quantity", "1");
    ...
    CATIDOMText_var engineText;
    hr = document->**CreateTextNode**("low consumption engine", engineText);
    ...
    CATIDOMComment_var comment;
    hr = document->**CreateComment**("list of parts for a convertible car", comment);
    ...  
  
---  
  
The _CATIDOMDocument_ interface acts as a factory to create all the other XML constructs: elements, text nodes, comments, processing instructions, etc. Elements can be created with the `CreateElement` method; text nodes can be created with the `CreateText` method; comments can be created with the `CreateComment` method. Each of these method returns a object, which implements the corresponding DOM interface (_CATIDOMElement_ , _CATIDOMText_ , _CATIDOMComment_). Using these interfaces, the created DOM nodes can then be further customized: for instance, calling the `SetAttribute` method of a _CATIDOMElement_ lets you set the value of this element's attributes.

Note that the DOM nodes, which we have created are just isolated building blocks at this stage. They are not yet attached to the DOM document. If we were to save the document at this point, they would not appear in the resulting XML file, since only the nodes, which are children of the document are actually saved.

[Top]

#### Create the Tree Structure by Positionning the Elements, Texts, and Comments with Respect to Each Other
    
    
    ...
    hr = document->**AppendChild**(car);
    ...
    hr = car->**AppendChild**(seat);
    ...
    hr = car->**AppendChild**(engine);
    ...
    hr = engine->**AppendChild**(engineText);
    ...
    hr = car->**InsertBefore**(comment, seat);
    ...  
  
---  
  
In this step, we assemble the building blocks we have created in the previous step to create a DOM tree. The DOM API views XML documents as a tree of XML nodes. The root element of the XML document corresponds to the root of the DOM tree. The sub-elements of the root element are the children of this root node. We use the `AppendChild` and `InsertBefore` methods to nest the nodes with respect to one another.

Note that the DOM API will perform tests on the fly to ensure that the resulting document is well-formed. If you try to perform the following operation, you will get a FAILED HRESULT with an associated CATDOMException warning you that the operation is impossible since it would break the DOM hierarchy.
    
    
    hr = comment->AppendChild(seat);
    // Will return E_FAIL since this would result in a not well-formed document  
  
---  
  
However, DOM does not guarantee validity. Nothing will prevent you to perform the following operation, which will result in a well-formed, but invalid XML document (a part element cannot contain car element as per the `automotive.dtd` grammar).
    
    
    hr = seat->AppendChild(car);
    // Will return S_OK since DOM does not verify validity.  
  
---  
  
[Top]

#### Save the Document as an XML File
    
    
    ...
    hr = builder->**WriteToFile**(document, outputFile);
    ...  
  
---  
  
To create the XML document, which corresponds to the DOM tree, call the `WriteToFile` method. It takes as a parameter the path of the XML document to be created.

By default, the resulting document will use the default (UTF-8) encoding. Note that the "encoding" attribute will not be specified in the XML declaration. However, the XML specification indicates that if the encoding attribute is not specified, XML parsers should consider the document uses the UTF-8 encoding. See [2] and [4] for more information on XML encodings.

[Top]

#### Manage Errors

The XMLParser framework uses the _HRESULT_ / _CATError_ mechanism to manage errors. Make sure to use the `CATError::CATGetLastError` to obtain all the available error diagnostics when using XMLParser. More information about V5 error management is available here [2] and [4].

[Top]

### In Short

This use case shows you how to create XML documents from scratch using the DOM API.

[Top]

* * *

### References

[1] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.htm)  
---|---  
[2] | [ Managing Errors Using HRESULT](../CAASysTechArticles/CAASysErrors.htm)  
[3] | [ Using XML in V5](../CAAXmlTechArticles/CAAXmlV5Overview.htm)  
[4] | [XML Tips and Tricks](../CAAXmlTechArticles/CAAXmlTipsAndTricks.htm)  
[Top]  
  
* * *

### History

Version: **1** [May 2005] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2005, Dassault Systmes. All rights reserved._
