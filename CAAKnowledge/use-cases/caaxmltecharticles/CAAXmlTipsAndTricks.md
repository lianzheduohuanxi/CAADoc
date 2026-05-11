---
```vbscript
title: "XML tips and tricks"
category: "use-case"
module: "CAAXmlTechArticles"
tags: ["CATISAXParser_var", "CATIXMLSAXFactory", "CATIndentationCharacter", "CATIXMLDOMDocumentBuilder", "CATIXMLDOMDocumentBuilder_var", "CATIndentation", "CATISAXEntityResolver", "CATIDOMText", "CATIXMLSAXFactory_var"]
source_file: "Doc/online/CAAXmlTechArticles/CAAXmlTipsAndTricks.htm"
converted: "2026-05-11T17:33:45.696790"
```

---
# 3D PLM Enterprise Architecture

|
## Middleware Abstraction

|
### XML Tips and Tricks

_Tips for making the best use of the XMLParser framework_
---|---|---
Technical Article

* * *
### Abstract

This article presents several tips to help you make the best use of the XMLParser framework.

  * **Frequently used Patterns**
    * Manage Errors Using the V5 HRESULT / CATError Pattern
    * Use CLSIDs to Create the Right Parser component
    * Pass Options Using CATListOfCATUnicodeStrings
  * **Validation Tips**
    * Default Parsers Are Validating
    * How to Reference a DTD
    * How to Reference an XSD Schema
  * **XML Generation Tips**
    * Encoding Defaults to UTF-8
    * Use the CATIndentation and CATIndentationCharacter Options to Control Formatting
    * Use CATSortAttributes for Stable Output

---

* * *
### Frequently used Patterns

The XMLParser framework uses several patterns to help you get used to the API more quickly.

[Top]
#### Manage Errors Using the V5 HRESULT / CATError Pattern

The XMLParser framework uses the HRESULT / CATError mechanism to manage errors.

The XMLParser framework uses the HRESULT / CATError mechanism to manage errors.
    if (FAILED(hr)) {
        CATUnicodeString message = "XMLParser call has failed/n";
        CATError* error = **CATError::CATGetLastError**(hr);
        if (error != NULL) {
            message.Append(error->GetNLSMessage());
            error->Release();
            error = NULL;

        }
```vbscript
if (error != NULL) {
message.Append(error->GetNLSMessage());
error->Release();
error = NULL;
        CATError::CATCleanLastError();
        cerr << message.ConvertToChar() << endl;
```

    }

---

XML parsers have rich error reporting capabilities and will often give you a precise diagnostic when an operation fails. For instance, when parsing an XML file, the parser will give you a message like the one below telling you:

  * the URI of the invalid XML resource.
  * a line and column number to locate the error precisely.
  * an error message to help you to fix the not well-formed or invalid XML input.

    XMLParser call has failed:
    SAX parse exception : Expected an attribute name
    SystemId : car_invalid.xml
    Line : 6
    Column : 12

---

Line : 6
Column : 12
In the same way, when you are building a DOM tree, the parser will also tell you precisely which well-formedness rule has been broken if you try to make an incorrect operation. Make sure to use the `CATError::CATGetLastError` function to obtain the associated CATError to help you debug your XML developments. More information about V5 error management is available here [1].

[Top]
#### Use CLSIDs to Create the Right Parser Component

The XMLParser framework provides several V5 DOM components, which all implement the _CATIXMLDOMDocumentBuilder_ interface, but offer different features (DTD validation, XSD schema validation). If you do not specify which component to use, the default DOM component (XML4C3) will be used.

The XMLParser framework provides several V5 DOM components, which all implement the _CATIXMLDOMDocumentBuilder_ interface, but offer different features (DTD validation, XSD schema validation). If you do not specify which component to use, the default DOM component (XML4C3) will be used.
    CATIXMLDOMDocumentBuilder_var builder;
    HRESULT hr = **::CreateCATIXMLDOMDocumentBuilder**(builder);

    ...

---

```vbscript
If you want to use a specific V5 DOM component (say XML4C5 since you want DOM with schema validation), add the CLSID of the component as an extra parameter to your call to `CreateCATIXMLDOMDocumentBuilder`.

```

```vbscript
If you want to use a specific V5 DOM component (say XML4C5 since you want DOM with schema validation), add the CLSID of the component as an extra parameter to your call to `CreateCATIXMLDOMDocumentBuilder`.
    CATIXMLDOMDocumentBuilder_var builder;
    HRESULT hr = ::CreateCATIXMLDOMDocumentBuilder(builder**, CLSID_XML4C5_DOM**);
```

    ...

---

SAX components use the same pattern. The following code instantiates the default SAX component (XML4C3):

SAX components use the same pattern. The following code instantiates the default SAX component (XML4C3):
    CATIXMLSAXFactory_var factory;
```vbscript
    hr = **::CreateCATIXMLSAXFactory**(factory);

```

    ...

---

To use a specific V5 SAX component (say XML4C5 since you want SAX with schema validation), add the CLSID of the component as an extra parameter to your call to `CreateCATIXMLSAXFactory`.

To use a specific V5 SAX component (say XML4C5 since you want SAX with schema validation), add the CLSID of the component as an extra parameter to your call to `CreateCATIXMLSAXFactory`.
    CATIXMLSAXFactory_var factory;
    HRESULT hr = ::CreateCATIXMLSAXFactory(factory, **CLSID_XML4C5_SAX**);

    ...

---

![warning.gif \(206 bytes\)](../CAAIcons/images/warning.gif) Note that some DOM methods take as a parameter objects coming from the SAX object model. DOM and SAX V5 component can work together only if they are backed by the same parser (XML4C3 DOM can work with XML4C3 SAX, but not with XML4C5 SAX). For more details on V5 DOM and SAX components, see [2].

[Top]
#### Pass Options Using CATListOfCATUnicodeStrings

Several methods of the XMLParser framework (for instance: `CATIXMLDOMDocumentBuilder::Parse`, `CATIXMLDOMDocumentBuilder::Write`, `CATIXMLSAXFactory::CreateParser`) accept options. Options are passed to these methods using two _CATListOfCATUnicodeStrings_. The first one contains the option names, the second one contains the option values. For instance, the following code instructs a DOM component to generate a file, which uses the UTF-16 encoding and indents the output with one TAB character per indentation level:

Several methods of the XMLParser framework (for instance: `CATIXMLDOMDocumentBuilder::Parse`, `CATIXMLDOMDocumentBuilder::Write`, `CATIXMLSAXFactory::CreateParser`) accept options. Options are passed to these methods using two _CATListOfCATUnicodeStrings_. The first one contains the option names, the second one contains the option values. For instance, the following code instructs a DOM component to generate a file, which uses the UTF-16 encoding and indents the output with one TAB character per indentation level:
    CATIXMLDOMDocumentBuilder_var builder;

    ...
Several methods of the XMLParser framework (for instance: `CATIXMLDOMDocumentBuilder::Parse`, `CATIXMLDOMDocumentBuilder::Write`, `CATIXMLSAXFactory::CreateParser`) accept options. Options are passed to these methods using two _CATListOfCATUnicodeStrings_. The first one contains the option names, the second one contains the option values. For instance, the following code instructs a DOM component to generate a file, which uses the UTF-16 encoding and indents the output with one TAB character per indentation level:
CATIXMLDOMDocumentBuilder_var builder;
    CATListOfCATUnicodeString writeOptions;
    writeOptions.Append(**"CATEncoding"**);
    writeOptions.Append(**"CATIndentation"**);
    writeOptions.Append(**"CATIndentationCharacter"**);
    CATListOfCATUnicodeString writeOptionValues;
    writeOptionValues.Append("UTF-16");
    writeOptionValues.Append("1");
    writeOptionValues.Append("\t");
```vbscript
    hr = builder->WriteToFile(document, outputFile, **writeOptions, writeOptionValues**);

```

    ...

---

[Top]
### Validation Tips

When parsing XML files, you will have to decide if you want to use the grammar validation capabilities of the parser, or not. This section explains how to turn validation on and off.

[Top]
#### Default Parsers Are Validating

DOM and SAX parsers can run in two modes: non-validating and validating. Non validating parsers just verify that the XML document is well-formed, whereas validating parsers verify that that the XML document is both well-formed and valid. To activate/deactivate validation, use the `CATDoValidation` option. The following code shows how to turn off validation for a SAX1 parser:

    ...
    **CATListOfCATUnicodeString options;
DOM and SAX parsers can run in two modes: non-validating and validating. Non validating parsers just verify that the XML document is well-formed, whereas validating parsers verify that that the XML document is both well-formed and valid. To activate/deactivate validation, use the `CATDoValidation` option. The following code shows how to turn off validation for a SAX1 parser:
    CATListOfCATUnicodeString optionValues;
    options.Append("CATDoValidation");
    optionValues.Append("false");**
    CATISAXParser_var parser;
```vbscript
    hr = factory->CreateParser(parser, **options** , **optionValues**);

```

    ...

---

![warning.gif \(206 bytes\)](../CAAIcons/images/warning.gif)If no option is specified, a validating parser will be used. A validating parser requires the document to have an associated DTD or XSD schema at a location the parser can access. If the document does not specify its DTD or XSD schema, the parsing will fail. For instance the following XML document cannot be parsed by a validating parser, but will work fine with a non-validating parser.

    <?xml version="1.0"?>
    <car/>
        ^
        |
    Cannot be validated because there is no reference to an XSD schema or a DTD

---

[Top]
#### How to Reference a DTD

To use a validating parser, you need to pass to the parser a document which references a grammar. If your grammar is a DTD, this reference takes the form of a document type declaration. This declaration appears on the second line of the XML document, after the XML declaration and can take one of three forms:

    <!DOCTYPE car SYSTEM "automotive.dtd">
    <!-- System ID -->

---

    <!DOCTYPE car PUBLIC "automotive" "automotive.dtd">
    <!-- Combination of a public and system ID -->

---

    <!DOCTYPE car [
    <!ELEMENT car (part)+>
    <!ELEMENT part (#PCDATA)>
    <!ATTLIST part name ID #REQUIRED
              quantity CDATA #IMPLIED>]>
    <!-- Embedded DTD -->

---

```vbscript
If the DTD is specified in an external resource, as in the two first forms, the parser will use the system ID to try to locate the resource. The system ID can be either a URI relative to the position of the XML document, or an absolute URI. You can also use a _CATISAXEntityResolver_ to help the parser locate the external resource. For more information on this possibility, see [4].

```

[Top]
#### How to Reference an XSD Schema

To use a validating parser, you need to pass to the parser a document which references a grammar. If your grammar is an XSD schema, this reference takes the form of special attributes of the `http://www.w3.org/2001/XMLSchema-instance` namespace. These attributes appear in the start tag of the first element defined in the grammar. There are two attributes, depending on whether several XSDs need to be imported.

    <?xml version='1.0' ?>
    <car xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
      **xsi:noNamespaceSchemaLocation="automotive.xsd"**
      xmlns="urn:com:dassault_systemes:automotive">...</car>
    <!-- without namespaces -->

---

    <?xml version='1.0' ?>
    <car xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
      **xsi:schemaLocation="urn:com:dassault_systemes:automotive automotive.xsd"**
      xmlns="urn:com:dassault_systemes:automotive">...</car>
    <!-- with namespaces -->

---

The schema is always specified in an external resource. The parser will use the value of the system ID contained in the `noNamespaceSchemaLocation` and `schemaLocation` attributes to try to locate the resource. The system ID can be either a URI relative to the position of the XML document, or an absolute URI. You can also use a _CATISAXEntityResolver_ to help the parser locate the external resource. For more information on this possibility, see [4].

![warning.gif \(206 bytes\)](../CAAIcons/images/warning.gif) Note that schema validation depends on namespaces. Make sure to activate the `CATEnableNameSpaces` option in the `CATIXMLDOMDocumentBuilder::Parse` and `CATIXMLSAXFactory::CreateParser` when using schemas.

[Top]
### XML Generation Tips

This section explains how to customize XML documents generated by the `CATIXMLDOMDocumentBuilder::Write` and `CATIXMLDOMDocumentBuilder::WriteToFile` methods.

[Top]
#### Encoding Defaults to UTF-8

The `CATIXMLDOMDocumentBuilder::WriteToFile` method accepts the "CATEncoding" option to explicitely specify the encoding used by the resulting document. If you do not specify this option, you will have an XML file with no `encoding` attribute specified in the XML declaration. The file itself uses the UTF-8 encoding. This corresponds to the default behavior of XML parsers as per the section F1 of the XML specification. See [3] for more information.

    <?xml version="1.0"?>

---

```vbscript
If you use the "CATEncoding" option, you will have an XML file with an `encoding` attribute set to "UTF-8". This second approach is recommended.

```

    <?xml version="1.0" **encoding="UTF-8"**?>

---

[Top]
#### Use the CATIndentation and CATIndentationCharacter Options to Control Formatting

Humans and XML parsers tend not to treat white space (indentations, line feeds) in the same way. Whereas humans view it as a hint of the structure of the underlying XML document, they are just wasted space for an XML parser. If you open XML files, which contain no white space in a text editor, they will look like this:

    <?xml version="1.0"?>
    <!DOCTYPE car SYSTEM "automotive.dtd"><car><!--list of part
Humans and XML parsers tend not to treat white space (indentations, line feeds) in the same way. Whereas humans view it as a hint of the structure of the underlying XML document, they are just wasted space for an XML parser. If you open XML files, which contain no white space in a text editor, they will look like this:
    s for a convertible car--><part name="seat" quantity="2"></
    part><part name="wheel" quantity="4"/><part name="engine" q
    uantity="1">low consumption engine</part><part name="body"
    quantity="1">weight must be < 1200 kg</part></car>

---

uantity="1">low consumption engine</part><part name="body"
quantity="1">weight must be < 1200 kg</part></car>
```vbscript
If your XML files need to be manually edited by humans or for debugging purposes, you might want to use the `CATIndentation` and `CATIndentationCharacter` options of the `CATIXMLDOMDocumentBuilder::WriteToFile` and `CATIXMLDOMDocumentBuilder::Write` methods. These options enable you to indent the generated XML, making it much easier to read. The `CATIndentationCharacter` specifies the character to use for indentation (tabulation or space), whereas the `CATIndentation` option is a positive integer specifying how many indentation characters to use for each level. Using these options, you will get a more readable XML file:

```

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

![warning.gif \(206 bytes\)](../CAAIcons/images/warning.gif) Note however that these two XML files are not equivalent. If you use the `CATIndentation` and `CATIndentationCharacter` options, white space is inserted in the XML document. Depending on the grammar file, this might or might not be allowed. Furthermore, the resuting DOM structure will be altered, since _CATIDOMText_ nodes will be inserted at various places in the DOM tree to represent this white space. An alternative approach to these options is not to display XML in the console or a text editor, but to use an XML-enabled tool to view the XML, such as a web browser, or a dedicated XML editor.

[Top]
#### Use CATSortAttributes for Stable Output

The XML specification does not mandate that XML attributes appear in a specific order within a tag. Therefore, XML attributes are often stored internally in hashtables by parser implementations. The consequence of this implementation choice is that the ordering of XML attributes is not preserved when reading an XML file and writing it back to disk. This can be a problem if you want to make comparisons between two XML files. To avoid this problem, the `CATIXMLDOMDocumentBuilder::WriteToFile` supports the `"CATSortAttributes"` option. If you use this option, attributes will be sorted in ascending order by qualified name.

[Top]

* * *
### In Short

This article presents several tips to help you make the best use of the XMLParser framework.

[Top]

* * *
### References

[1] | [ Managing Errors Using HRESULT](../CAASysTechArticles/CAASysErrors.md)
---|---
[2] | [Using XML in V5](../CAAXmlTechArticles/CAAXmlV5Overview.md)
[3] | Extensible Markup Language (XML) 1.0 (Third Edition) - W3C Recommendation 04 February 2004
[4] | [Fetching an External Entity with SAX](../CAAXmlUseCases/CAAXMLSAXResolver.md)

* * *
### History

Version: **1** [Apr 2005] | Document created
---|---
[Top]

* * *

_Copyright 2005, Dassault Systmes. All rights reserved._
