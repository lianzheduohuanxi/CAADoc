---
title: "Resolving external entities with SAX"
category: "use case"
module: "CAAXmlUseCases"
tags: ["CAAXMLSAXResolverMain", "CATISAXParser_var", "CAAXMLParser", "CATIXMLSAXFactory", "CATISAXEntityResolver_var", "CAAXMLSAXResolverHandlers", "CATISAXParser", "CATISAXInputSource", "CATISAXEntityResolver", "CAAXMLSAXResolver", "CATISAXErrorHandler_var", "CATISAXErrorHandler", "CATISAXInputSource_var", "CATIXMLSAXFactory_var", "CATISAXDTDHandler", "CATISAXDocumentHandler"]
source_file: "Doc\online\CAAXmlUseCases\CAAXMLSAXResolver.htm"
converted: "2026-05-11T17:33:45.664165"
---

# 3D PLM Enterprise Architecture

| 

## Middleware Abstraction

| 

### Fetching an External Entity with SAX

_Using a SAX entity resolver to fetch an external entity_  
---|---|---  
Use Case  
  
* * *

### Abstract

This article shows how to specify an entity resolver and how to use it with a SAX parser. Entity resolvers are invoked by the XML parser to obtain the source of external entities they cannot find by themselves.

  * **What You Will Learn With This Use Case**
  * **The CAAXMLSAXResolver Use Case**
    * What Does CAAXMLSAXResolver Do
    * How to Launch CAAXMLSAXResolver
    * Where to Find the CAAXMLSAXResolver Code
  * **Step-by-Step**
  * **In Short**
  * **References**

  
---  
  
* * *

### What You Will Learn With This Use Case

This use case shows how to specify an entity resolver and how to use it with a SAX parser. You will learn to create two different kinds of event handlers for SAX: **error handlers** are invoked to process errors raised by the parser if the XML input is not well-formed or is invalid; **entity resolvers** are invoked when the parser encounters an external entity reference it cannot find by itself. You will learn how to register your handlers with the parser. Finally, the use case will show you how to run the SAX parser configurated with your handlers to parse a file with validation.

[Top]

### The CAAXMLSAXResolver Use Case

The CAAXMLSAXResolver Use Case is a use case of the CAAXMLParser.edu framework that illustrates XMLParser framework capabilities.

[Top]

#### What Does CAAXMLSAXResolver Do

This use case reads an existing XML file using SAX and validates it with a DTD stored in a database. The SAX parser has to use an entity resolver to fetch the DTD from the database. For the sake of simplicity, the database is just a directory somewhere on the disk. The system ID of the DTDs must begin with the string: "sql://". If the document is not well formed or invalid, the program displays an error message in the console.

[Top]

#### How to Launch CAAXMLSAXResolver

To launch CAAXMLSAXResolver, you will need to set up the build time environment, then compile CAAXMLSAXResolver along with its prerequisites, set up the run time environment, and then execute the use case [1].

The use case should be launched as follows from the command line:
    
    
    CAAXMLSAXResolver <databasedir> <filepath>

where `<databasedir>` is the path of the directory, which contains the DTDs and `<filepath>` is the path of the XML file, which will be parsed.

A sample XML file and a sample DTD are provided with the use case. To use them, launch the following command from the command line:

Windows | `CAAXMLSAXResolver InstallRoot\OS\resources\xml\CAAXMLSAXResolver\database InstallRoot\OS\resources\xml\CAAXMLSAXResolver\car.xml`  
---|---  
Unix | `CAAXMLSAXResolver InstallRoot/OS/resources/xml/CAAXMLSAXResolver/database InstallRoot/OS/resources/xml/CAAXMLSAXResolver/car.xml`  
  
where:

  * `InstallRoot` is the directory in which you have installed the run time part or the product line
  * `OS` is the directory containing the installed code 
    * `aix_a` for 32-bit AIX
    * `hpux_b` for HP-UX
    * `solaris_a` for Solaris
    * `intel_a` for 32-bit Windows
    * `win_b64` for 64-bit Windows



[Top]

#### Where to Find the CAAXMLSAXResolver Code

The CAAXMLSAXResolver use case is made of several classes located in the CAAXMLSAXResolver.m module of the CAAXMLParser.edu framework:

Windows | `InstallRootDirectory\CAAXMLParser.edu\CAAXMLSAXResolver.m\`  
---|---  
Unix | `InstallRootDirectory/CAAXMLParser.edu/CAAXMLSAXResolver.m/`  
  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]

### Step-by-Step

To create a SAX parser, create and register event handlers with this parser, and parse a file, there are six main steps:

# |  Step  
---|---  
1 | Implement a V5 Entity Resolver and Error Handler component  
2 | Create a V5 SAX Component  
3 | Create and Configure a V5 SAX Parser  
4 | Create the Entity Resolver and Error Handler Components and Register Them With the Parser  
5 | Parse the XML File  
6 | Manage Errors  
  
[Top]

#### Implement a V5 Entity Resolver and Error Handler Component

The SAX API uses an event-oriented API to process XML documents. The XML SAX parser reads XML documents sequentially and invokes callback functions to indicate the XML construct it comes across. Each invocation is called a SAX event. The SAX API defines V5 interfaces, which specify the signature of the SAX callback functions and group them per theme. The _CATISAXEntityResolver_ interface defines the `ResolveEntity` function. This function is invoked by the parser when it encounters an external entity reference it cannot find by itself. The function must fetch the external entity and return it to the parser in the form of a SAX input source. Other SAX interfaces (_CATISAXDTDHandler_ , _CATISAXErrorHandler_ , _CATISAXDocumentHandler_) define additional events. To make the work easier for the developer, the SAX API provides a _CATSAXHandlerBase_ component, which already provides an empty implementation of all the SAX interfaces. ![saxhandlerbase.png \(3148 bytes\)](images/saxhandlerbase.png).

Therefore, to write a SAX document handler, all you need to do is to create a new V5 component which inherits from _CATSAXHandlerBase_ and override the methods to answer to the events, which are relevant to your application. The following code declares and defines a _CAAXMLSAXResolverHandlers_ V5 component which inherits from _CATSAXHandlerBase_ and re-implements _CATISAXEntityResolver_ and _CATISAXErrorHandler_.
    
    
    // CAAXMLSAXResolverHandlers.h
    #include "CATSAXHandlerBase.h"
    class CAAXMLSAXResolverHandlers : **public CATSAXHandlerBase** {
        **CATDeclareClass;**
        public:
            ...
            // Override the default implementation of the
            // CATISAXEntityResolver interface.
            virtual HRESULT **ResolveEntity**(
                const CATUnicodeString & iPublicId, 
                const CATUnicodeString & iSystemId, 
                CATISAXInputSource_var& oInputSource);
    
            // Override part of the default implementation of the
            // CATISAXErrorHandler interface.
            virtual HRESULT **Error**( 
                CATSAXParseException* iException);
            virtual HRESULT **FatalError**( 
                CATSAXParseException* iException);
            ...
    };
     			  
  
---  
      
    
    // CAAXMLSAXResolverHandlers.cpp
    #include "CAAXMLSAXResolverHandlers.h"
    
    // Declare the class as a V5 component derived from CATSAXHandlerBase
    **CATImplementClass( CAAXMLSAXResolverHandlers, Implementation, CATSAXHandlerBase, CATnull );**
    
    // Implement the CATISAXEntityResolver interface
    **#include "TIE_CATISAXEntityResolver.h"
    TIE_CATISAXEntityResolver(CAAXMLSAXResolverHandlers);**
    
    // Implement the CATISAXErrorHandler interface
    **#include "TIE_CATISAXErrorHandler.h"
    TIE_CATISAXErrorHandler(CAAXMLSAXResolverHandlers);**
    			  
  
---  
  
The next step is to provide an implementation for each of the SAX events you want to catch. The following code shows how the `ResolveEntity` event callback function is implemented. This method receives the name of the external entity to resolve as a _CATUnicodeString_. In the use case, the method will be invoked when the parser reads the document type declaration an cannot find the entity called `"sql://automotive.dtd"`.
    
    
    <!DOCTYPE car SYSTEM **"sql://automotive.dtd"** >
    			  
  
---  
  
The method must return the source of the corresponding entity in the form of a _CATISAXInputSource_ object. In this case, the entity consist of a DTD file stored in the database directory of the disk.
    
    
    // CAAXMLSAXResolverHandlers.cpp
    HRESULT CAAXMLSAXResolverHandlers::ResolveEntity(
        const CATUnicodeString & iPublicId, 
        const CATUnicodeString & iSystemId, 
        CATISAXInputSource_var& oInputSource) {
    
        ...
        // All system IDs must begin with this prefix
        CATUnicodeString prefix = "sql://";
    
        CATIXMLSAXFactory_var factory;
        HRESULT hr2 = **::CreateCATIXMLSAXFactory**(factory);
        if (SUCCEEDED(hr2) && (factory != NULL_var)) {
            // Compute the file path where the DTD is located.
            CATUnicodeString filePath = _databaseDir;
    #ifdef _WINDOWS_SOURCE
            filePath.Append("\\");
    #else // _WINDOWS_SOURCE
            filePath.Append("/");
    #endif // _WINDOWS_SOURCE
            filePath.Append(iSystemId.SubString(prefix.GetLengthInChar(), iSystemId.GetLengthInChar() - prefix.GetLengthInChar()));
                
            // Create a SAX input source
            hr = factory->**CreateInputSourceFromFile**(filePath, "", oInputSource);
        }
        ...
    }
      
  
---  
  
To create an input source for this file, invoke the `CreateInputSourceFromFile` of the _CATIXMLSAXFactory_ object. To get a _CATIXMLSAXFactory_ object, use the global function **CreateCATIXMLSAXFactory** (more on this in the next section).

[Top]

#### Create a V5 SAX Component
    
    
    ...
    // CAAXMLSAXResolverMain.cpp
    CATIXMLSAXFactory_var factory;
    HRESULT hr = **::CreateCATIXMLSAXFactory****(factory);
    ...****  
  
---  
  
To work with SAX, you need to instantiate the V5 SAX component. The V5 SAX component can be created by calling the `CreateCATIXMLSAXFactory` global function. This function returns a V5 handler on the _CATIXMLSAXFactory_ interface, which is the main interface for the V5 SAX component. Using this interface you will be able to create SAX1 and SAX2 parsers and to create input source to feed XML to the parser. Note that the code above does not specify the CLSID of the component to use, so the default SAX component (XML4C3) will be used. See [3] and [4] if you want to use another V5 SAX component.

[Top]

#### Create and Configure a V5 SAX Parser
    
    
    CATISAXParser_var parser;
    hr = factory->**CreateParser**(parser);
    ...  
  
---  
  
To create a SAX1 parser, one simply invokes the `CreateParser` on the _CATIXMLSAXFactory_ object. There are two kinds of SAX1 parsers, non-validating SAX1 parsers and validating SAX1 parsers. If you do specify optional arguments to your `CreateParser` call, a validating parser will be created. See [3] and [4] if you want to use another V5 SAX component.

[Top]

#### Create the Entity Resolver and Error Handler Components and Register Them With the Parser

The SAX1 parser created in the previous section is not yet usable as it does not yet know any other objects to which it can send the events it generates. The SAX1 parser can accept up to four event handlers (one for each event interface), as shown in the diagram below. ![saxsaxparser.png \(3115 bytes\)](images/saxparser.png)
    
    
    ...
    CAAXMLSAXResolverHandlers *handlersImpl = new CAAXMLSAXResolverHandlers(databaseDir);
    CATISAXEntityResolver_var entityHandler = handlersImpl;
    CATISAXErrorHandler_var errHandler = handlersImpl;
    handlersImpl->Release();
    handlersImpl = NULL;  
  
---  
  
To instantiate the entity resolver and the error handler you have defined in the previous section, simply do a `new` of the main implementation class, then get interface handles of the right type on the component.
    
    
    ...
    hr = parser->**SetEntityResolver**(entityHandler);
    ...
    hr = parser->**SetErrorHandler**(errHandler);
    ...  
  
---  
  
To register your entityResolver handler, call the `SetEntityResolver` method of the _CATISAXParser_ interface. To register your error handler, call the `SetErrorHandler` method of the _CATISAXParser_ interface. Passing `NULL_var` to these methods unregisters the previously registered handlers.

[Top]

#### Parse the XML File
    
    
    hr = parser->**Parse**(filePath);  
  
---  
  
To parse the XML file, call the `Parse` method of the _CATISAXParser_ interface. Pass the path of the file to read as a parameter. The method will read the file from top to bottom and generate the corresponding events, calling your event handlers for all the events you want to manage.

[Top]

#### Manage Errors

The XMLParser framework uses the _HRESULT_ / _CATError_ mechanism to manage errors. Make sure to use the `CATError::CATGetLastError` to obtain all the available error diagnostics when using XMLParser. More information about V5 error management is available here [2] and [4].

[Top]

### In Short

This use case shows you how to parse XML documents using the SAX API.

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
