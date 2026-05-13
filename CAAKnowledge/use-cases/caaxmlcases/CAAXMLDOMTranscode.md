---
title: "Reading and writing XML documents with DOM"
category: "use-case case"
module: "CAAXmlUseCases"
tags: "["CAAXMLParser", "CATIXMLDOMDocumentBuilder", "CATIXMLDOMDocumentBuilder_var", "CATIDOMDocument_var", "CAAXMLDOMTranscode_utf16", "CAAXMLDOMTranscode"]"
source_file: "Doc/online/CAAXmlUseCases/CAAXMLDOMTranscode.htm"
converted: "2026-05-11T17:33:45.623063"
---
# 3D PLM Enterprise Architecture

|
## Middleware Abstraction

|
### Reading and Writing XML Documents with DOM

_Using the DOM API to parse existing XML files and saving DOM trees as XML files using various encodings_
---|---|---
Use Case

* * *
### Abstract

This article shows how to parse existing XML files using the DOM API and how to save a DOM tree to disk as an XML file with the proper encoding.

  * **What You Will Learn With This Use Case**
  * **The CAAXMLDOMTranscode Use Case**
    * What Does CAAXMLDOMTranscode Do
    * How to Launch CAAXMLDOMTranscode
    * Where to Find the CAAXMLDOMTranscode Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

This use case shows how to go back and forth between XML files and in-memory DOM trees. You will first learn to construct an in-memory DOM tree from an XML file using a DOM parser. You will learn to configure the parser to make it validating or non validating. The use case will then show you how to create an XML file from an in-memory DOM tree. It will show you how to configure the parser to obtain an XML file with the encoding you want.

[Top]
### The CAAXMLDOMTranscode Use Case

The CAAXMLDOMTranscode Use Case is a use case of the CAAXMLParser.edu framework that illustrates XMLParser framework capabilities.

[Top]
#### What Does CAAXMLDOMTranscode Do

This use case implements a simple XML file transcoder: a program, which converts XML files from one encoding to another. The transcoder parses an existing XML file using the DOM API, then saves it under the specified name using the requested encoding.

[Top]
#### How to Launch CAAXMLDOMTranscode

This use case implements a simple XML file transcoder: a program, which converts XML files from one encoding to another. The transcoder parses an existing XML file using the DOM API, then saves it under the specified name using the requested encoding.
To launch CAAXMLDOMTranscode, you will need to set up the build time environment, then compile CAAXMLDOMTranscode along with its prerequisites, set up the run time environment, and then execute the use case [1].

The use case should be launched as follows from the command line:

    CAAXMLDOMTranscode (-utf8|-utf16) <infilepath> <outfilepath>

where:

  * `(-utf8|-utf16)` is the choice of the encoding to use for the transcoded XML file.
  * `<infilepath>` is the path of the XML file which you want to read.
  * `<outfilepath>` is the path where the transcoded XML file will be saved.

A sample XML file is provided with the use case. To use it, launch the following command from the command line:

Windows | `CAAXMLDOMTranscode -utf16 InstallRoot/OS/resources/xml/CAAXMLDOMTranscode/CAAXMLDOMTranscode.xml C/TEMP/CAAXMLDOMTranscode_utf16.xml`

A sample XML file is provided with the use case. To use it, launch the following command from the command line:
Windows | `CAAXMLDOMTranscode -utf16 InstallRoot/OS/resources/xml/CAAXMLDOMTranscode/CAAXMLDOMTranscode.xml C/TEMP/CAAXMLDOMTranscode_utf16.xml`
Unix | `CAAXMLDOMTranscode -utf16 InstallRoot/OS/resources/xml/CAAXMLDOMTranscode/CAAXMLDOMTranscode.xml /tmp/CAAXMLDOMTranscode_utf16.xml`

where:

  * `InstallRoot` is the directory in which you have installed the run time part or the product line
  * `OS` is the directory containing the installed code
    * `aix_a` for 32-bit AIX
    * `hpux_b` for HP-UX
    * `solaris_a` for Solaris
    * `intel_a` for 32-bit Windows
    * `win_b64` for 64-bit Windows

[Top]
#### Where to Find the CAAXMLDOMTranscode Code

The CAAXMLDOMTranscode use case is made of one file located in the CAAXMLDOMTranscode.m module of the CAAXMLParser.edu framework:

Windows | `InstallRootDirectory/CAAXMLParser.edu/CAAXMLDOMTranscode.m/`

The CAAXMLDOMTranscode use case is made of one file located in the CAAXMLDOMTranscode.m module of the CAAXMLParser.edu framework:
Windows | `InstallRootDirectory/CAAXMLParser.edu/CAAXMLDOMTranscode.m/`
Unix | `InstallRootDirectory/CAAXMLParser.edu/CAAXMLDOMTranscode.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

To parse a DOM document and save it to disk, there are four main steps:
# |  Step
---|---
To parse a DOM document and save it to disk, there are four main steps:
1 | Create the V5 DOM Component
2 | Parse the XML Document Without Validation
3 | Write DOM Tree With the Proper Encoding
4 | Manage Errors

[Top]
#### Create the V5 DOM Component

    CATIXMLDOMDocumentBuilder_var builder;
    HRESULT hr = **::CreateCATIXMLDOMDocumentBuilder**(builder);
    ...

---

The first step to work with DOM is to instantiate the V5 DOM component. The V5 DOM component can be created by calling the `CreateCATIXMLDOMDocumentBuilder` global function. This function returns a V5 handler on the _CATIXMLDOMDocumentBuilder_ interface, which is the main interface for the V5 DOM component. Using this interface you will be able to create documents (either by parsing an existing XML file, as here, or from scratch) and save existing documents to disk. Note that the code above does not specify the CLSID of the component to use, so the default DOM component (XML4C3) will be used. See [3] and [4] if you want to use another V5 DOM component.

[Top]
#### Parse the XML Document Without Validation

    ...
    CATListOfCATUnicodeString readOptions;
    readOptions.Append("CATDoValidation");
    CATListOfCATUnicodeString readOptionValues;
    readOptionValues.Append("false");

    CATIDOMDocument_var document;
```vbscript
    hr = builder->**Parse**(inputFile, document, readOptions, readOptionValues);

```

    ...

---

To parse an XML document, invoke the `Parse` method from the _CATIXMLDOMDocumentBuilder_ interface. The parser can run in two modes: non-validating and validating. You determine what mode is used in the `Parse` method using the `"CATDoValidation"` option. Options are passed to the parser using two _CATListOfCATUnicodeStrings_. The first one contains the option names, the second one contains the option values. For the purpose of this use case, we just want to transcode the XML file from one encoding to another, so we will disconnect XML validation. For a discussion of non-validating parsers versus validating parsers and how to choose which parser to instantiate, please see [3] and [4].

[Top]
#### Write DOM Tree With the Proper Encoding

    ...
    CATListOfCATUnicodeString writeOptions;
    writeOptions.Append(**"CATEncoding"**);
    CATListOfCATUnicodeString writeOptionValues;
    if (strcmp(argv[1], "-utf8") == 0) {
    	writeOptionValues.Append(**"UTF-8"**);

    } else {
writeOptions.Append(**"CATEncoding"**);
CATListOfCATUnicodeString writeOptionValues;
if (strcmp(argv[1], "-utf8") == 0) {
writeOptionValues.Append(**"UTF-8"**);
    	writeOptionValues.Append(**"UTF-16"**);

    }
```vbscript
if (strcmp(argv[1], "-utf8") == 0) {
writeOptionValues.Append(**"UTF-8"**);
writeOptionValues.Append(**"UTF-16"**);
    hr = builder->**WriteToFile**(document, outputFile, writeOptions, writeOptionValues);
```

    ...

---

hr = builder->**WriteToFile**(document, outputFile, writeOptions, writeOptionValues);
To create the XML document, which corresponds to the DOM tree, call the `WriteToFile` method. It takes as a parameter the path of the XML document to be created. The `WriteToFile` method also accepts the `CATEncoding` option to control the encoding used in the resulting file. Options are passed to the parser using two _CATListOfCATUnicodeStrings_. The first one contains the option names, the second one contains the option values.

```cpp
If the `CATEncoding` option is not specified, the resulting document will use the default (UTF-8) encoding. Note that the "encoding" attribute will not be specified in the XML declaration. However, the XML specification indicates that if the encoding attribute is not specified, XML parsers should consider that the document uses the UTF-8 encoding. Not all encodings are supported by the parser. For a discussion of supported encodings and write options, see [3] and [4].

```

[Top]
#### Manage Errors

The XMLParser framework uses the _HRESULT_ / _CATError_ mechanism to manage errors. Make sure to use the `CATError::CATGetLastError` to obtain all the available error diagnostics when using XMLParser. More information about V5 error management is available here [2] and [4].

[Top]
### In Short

This use case shows you how to read and write XML documents using the DOM API.

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
