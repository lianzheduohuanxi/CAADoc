---
title: "Reading XML from a custom source"
category: "use case"
module: "CAAXmlUseCases"
tags: ["CATISAXXMLReader", "CATIXMLInputStream_var", "CAAXMLParser", "CATIXMLSAXFactory", "CATIXMLInputStream", "CAAXMLMultiFileStream", "CATIXMLDOMDocumentBuilder", "CATISAXParser", "CATIXMLDOMDocumentBuilder_var", "CATISAXInputSource", "CATIDOMDocument_var", "CATISAXInputSource_var", "CATIXMLSAXFactory_var", "CAAXMLCustomStream"]
source_file: "Doc/online/CAAXmlUseCases/CAAXMLCustomStream.md"
converted: "2026-05-11T17:33:45.595301"
---
# 3D PLM Enterprise Architecture

| 
## Middleware Abstraction

| 
### Reading XML from a Custom Source

_Parsing XML from a user-defined source with DOM or SAX_  
---|---|---  
Use Case  
  
* * *
### Abstract

This article shows how to create your own XML source to feed XML directly to a DOM or a SAX parser.

  * **What You Will Learn With This Use Case**
  * **The CAAXMLCustomStream Use Case**
    * What Does CAAXMLCustomStream Do
    * How to Launch CAAXMLCustomStream
    * Where to Find the CAAXMLCustomStream Code
  * **Step-by-Step**
  * **In Short**
  * **References**

  
---  
  
* * *
### What You Will Learn With This Use Case

The XML parsers provided in the XMLParser framework know how to parse XML from various sources: files, URLs and memory buffers. This use case shows how to create your own XML sources and use them with a DOM or a SAX parser. This use case also shows you how to save your DOM tree as XML in a memory buffer.

[Top]
### The CAAXMLCustomStream Use Case

The CAAXMLCustomStream Use Case is a use case of the CAAXMLParser.edu framework that illustrates XMLParser framework capabilities.

[Top]
#### What Does CAAXMLCustomStream Do

This use case provides an implementation of a new XML source. The XML source is capable of fetching a large XML document split over several files (each file contains a chunk of the complete XML document). The use case instantiates a DOM parser, instantiates the XML source with the files passed as an argument in the command line, parses the contents of the supplied source to build a DOM tree, and finally dumps the content of the DOM tree in the console.

[Top]
#### How to Launch CAAXMLCustomStream

To launch CAAXMLCustomStream, you will need to set up the build time environment, then compile CAAXMLCustomStream along with its prerequisites, set up the run time environment, and then execute the use case [1].

The use case should be launched as follows from the command line:
    
    
    CAAXMLCustomStream <file1> ... <fileN>

where `<file1>` is the path of the file containing the first XML chunk, `<fileN>` is the path of the file containing the last XML chunk.

A sample XML file split in three chunks is provided with the use case. To use it, launch the following command from the command line:

Windows | `cd InstallRoot\OS\resources\xml\CAAXMLCustomStream  
CAAXMLCustomStream caaxmlchunk1.xml caaxmlchunk2.xml caaxmlchunk3.xml`  
---|---  
Unix | `cd InstallRoot/OS/resources/xml/CAAXMLCustomStream ; CAAXMLCustomStream caaxmlchunk1.xml caaxmlchunk2.xml caaxmlchunk3.xml`  
  
where:

  * `InstallRoot` is the directory in which you have installed the run time part or the product line
  * `OS` is the directory containing the installed code 
    * `aix_a` for 32-bit AIX
    * `hpux_b` for HP-UX
    * `solaris_a` for Solaris
    * `intel_a` for 32-bit Windows
    * `win_b64` for 64-bit Windows

[Top]
#### Where to Find the CAAXMLCustomStream Code

The CAAXMLCustomStream use case is made of several classes located in the CAAXMLCustomStream.m module of the CAAXMLParser.edu framework:

Windows | `InstallRootDirectory\CAAXMLParser.edu\CAAXMLCustomStream.m\`  
---|---  
Unix | `InstallRootDirectory/CAAXMLParser.edu/CAAXMLCustomStream.m/`  
  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

To create your own XML source and use it to parse XML, there are six main steps:
# |  Step  
---|---  
1 | Implement an XML Custom Stream  
2 | Create a V5 DOM Component and a V5 SAX Component  
3 | Use the V5 SAX Component to Create a SAX Input Source Based on Your XML Stream  
4 | Parse the Custom Source Using DOM  
5 | Dump Your DOM Tree in the Console  
6 | Manage Errors  
  
Please note that most of the APIs from the XMLParser framework return a _HRESULT_. To avoid excessive indentation of the code, which would cause poor readibility, the following coding style has been used: all the code is put in a `do {} while(0)` loop; if one of the APIs returns a bad _HRESULT_ , the execution is stopped with a `break` and the error handler is invoked.
    
    
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
#### Implement an XML Custom Stream

Custom streams enable you to access XML, which is stored in a location you cannot access with the default types of input sources available in the XMLParser framework, such as a relational database or an encrypted file. In theory, the same result can be achieved by first fetching the whole XML into a memory buffer and then parsing the XML from that memory buffer. However, such a solution creates memory peaks and does not perform as well as the custom stream approach. To create a custom stream, you need to declare and define a V5 component, which implements the _CATIXMLInputStream_ interface.
    
    
    // CAAXMLMultiFileStream.h
    ...
    class CAAXMLMultiFileStream : **public CATBaseUnknown** {
        **CATDeclareClass** ;
        public:
            ...
            // Implement the CATIXMLInputStream interface.
            **virtual HRESULT Read(
                unsigned char* ioByteArray,
                unsigned int iByteArrayCapacity,
                unsigned int & oSizeRead);**
    };
      
  
---  
      
    
    // CAAXMLMultiFileStream.cpp
    #include "CAAXMLMultiFileStream.h" // Import the definition of the component
    
    // Declare the class as a V5 component
    **CATImplementClass( CAAXMLMultiFileStream, Implementation, CATBaseUnknown, CATnull );**
    
    // Implement the CATIXMLInputStream interface
    **#include "TIE_CATIXMLInputStream.h"
    TIE_CATIXMLInputStream(CAAXMLMultiFileStream);**
    			  
  
---  
  
The _CATIXMLInputStream_ interface contains just one method, called `Read`. You use this method to return fragments of XML to parser. The parser calls this method repeatedly, any time it has finished analyzing the current XML fragment and needs the next one to be fetched. You never call this method directly: you pass your implementation of _CATIXMLInputStream_ to the parser and the parser will call it automatically when it needs it.
    
    
    // CAAXMLMultiFileStream.cpp
    HRESULT CAAXMLMultiFileStream::**Read(
        unsigned char* ioByteArray,
        unsigned int iByteArrayCapacity,
        unsigned int & oSizeRead)** {
        ...
    }  
  
---  
  
The method accepts the following parameters:

`ioByteArray` | A buffer where you must put the XML fragment.  
---|---  
`iByteArrayCapacity` | The size of the `ioByteArray` buffer.  
`oSizeRead` | The size of the fragment returned to the parser. Returning a zero-length read size signals the end of the XML input to the parser.  
  
[Top]
#### Create a V5 DOM Component and a V5 SAX Component
    
    
    ...
    CATIXMLDOMDocumentBuilder_var builder;
    hr = **::CreateCATIXMLDOMDocumentBuilder**(builder);
    ...  
  
---  
  
To parse the XML, you will use a DOM parser, so the next step is to instantiate a V5 DOM component. The V5 DOM component can be created by calling the `CreateCATIXMLDOMDocumentBuilder` global function. This function returns a V5 handler on the _CATIXMLDOMDocumentBuilder_ interface, which is the main interface for the V5 DOM component. Using this interface you will be able to create documents (either by parsing an XML input source, as here, or from scratch) and save existing documents to disk.
    
    
    ...
    CATIXMLSAXFactory_var factory;
    hr = **::CreateCATIXMLSAXFactory**(factory);
    ...  
  
---  
  
To provide the XML, you will need to provide a custom input source to the DOM parser. Custom input source are created by the _CATIXMLSAXFactory_ interface, so you will also need a V5 SAX component. The V5 SAX component can be created by calling the `CreateCATIXMLSAXFactory` global function. This function returns a V5 handler on the _CATIXMLSAXFactory_ interface, which is the main interface for the V5 SAX component. Using this interface you will be able to create SAX1 and SAX2 parsers and to create input source to feed XML to the parser.

Note that the above code does not specify the CLSID of the component to use, so the default DOM and SAX components (XML4C3) will be used. See [3] and [4] if you want to use another V5 DOM or SAX component.

[Top]
#### Use the V5 SAX Component to Create a SAX Input Source Based on Your XML Stream
    
    
    ...
    CAAXMLMultiFileStream* customStreamImpl = new CAAXMLMultiFileStream(files);
    CATIXMLInputStream_var customStream = customStreamImpl;
    customStreamImpl->Release();
    customStreamImpl = NULL;
    ...
    CATISAXInputSource_var source;
    hr = factory->**CreateInputSourceFromStream**(customStream, "MyCustomSource", source);
    ...  
  
---  
  
To create a custom XML source, you first need to instantiate your custom XML stream component by doing a `new` of its main implementation class and getting its _CATIXMLInputStream_ handle. Then, you use the `CreateInputSourceFromStream` method from the _CATISAXInputSource_ interface to create the custom XML source. The methods takes as a parameter your custom implementation of the _CATIXMLInputStream_ interface. It uses this implementation to obtain the XML content to parse. ![catixmlinputstream.png \(1853 bytes\)](images/catixmlinputstream.png)

![warning.gif \(206 bytes\)](../CAAIcons/images/warning.gif) The lifecycle of your _CATIXMLInputStream_ implementation depends on the lifecycle the _CATISAXInputSource_ object. As soon as the _CATISAXInputSource_ goes out of scope, the destructor of the _CATIXMLInputStream_ implementation will be called, provided that you do not have any other references on it. You can they perform cleanup and release resources in this destructor.

[Top]
#### Parse the Custom Source Using DOM
    
    
    ...
    CATListOfCATUnicodeString readOptions;
    readOptions.Append(**"CATDoValidation"**);
    CATListOfCATUnicodeString readOptionValues;
    readOptionValues.Append(**"false"**);
    
    CATIDOMDocument_var document;
    hr = builder->**Parse**(source, document, readOptions, readOptionValues);
    ...  
  
---  
  
To parse the custom input source, you need to invoke the `Parse` method of the _CATIXMLDOMDocumentBuilder_ interface. If you want to parse using SAX, you can just as well pass the input to the `Parse` method of a _CATISAXParser_ (SAX1) or a _CATISAXXMLReader_ (SAX2).

The DOM parser can run in two modes: non-validating and validating. You determine what mode is used in the `Parse` method using the `"CATDoValidation"` option. Options are passed to the parser using two _CATListOfCATUnicodeStrings_. The first one contains the option names, the second one contains the option values. For a discussion of non-validating parsers versus validating parsers and how to choose which parser to instantiate, please see [3] and [4].

[Top]
#### Dump Your DOM Tree in the Console
    
    
    ...
    CATUnicodeString rawOutput;
    hr = builder->**Write**(document, rawOutput);
    ...
    cout << rawOutput.ConvertToChar() << endl;
    ...  
  
---  
  
To obtain an XML representation of your DOM tree, call the `Write` method of the _CATIXMLDOMDocumentBuilder_ interface. The resulting XML is returned in a CATUnicodeString. For a discussion of supported encodings and write options, see [3] and [4].

[Top]
#### Manage Errors

The XMLParser framework uses the _HRESULT_ / _CATError_ mechanism to manage errors. Make sure to use the `CATError::CATGetLastError` to obtain all the available error diagnostics when using XMLParser. More information about V5 error management is available here [2] and [4].

[Top]
### In Short

This use case shows you how to create your own XML sources and use them with a DOM or a SAX parser.

[Top]

* * *
### References

[1] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] | [ Managing Errors Using HRESULT](../CAASysTechArticles/CAASysErrors.md)  
[3] | [ Using XML in V5](../CAAXmlTechArticles/CAAXmlV5Overview.md)  
[4] | [XML Tips and Tricks](../CAAXmlTechArticles/CAAXmlTipsAndTricks.md)  
[Top]  
  
* * *
### History

Version: **1** [May 2005] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2005, Dassault Systmes. All rights reserved._
