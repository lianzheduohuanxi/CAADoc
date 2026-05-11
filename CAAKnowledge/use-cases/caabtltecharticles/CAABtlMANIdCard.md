---
title: "The IdentityCard.h Special File"
category: "use-case"
module: "CAABtlTechArticles"
tags: []
source_file: "Doc/online/CAABtlTechArticles/CAABtlMANIdCard.md"
converted: "2026-05-11T17:33:46.051073"
---

RADE |  Multi-Workspace Application Builder |  The IdentityCard.h Special File _Purpose and use_  
---|---|---  
Technical Article  
  
* * *

**Warning** : The IdentityCard.h file format is **deprecated** starting with V5R24, and is replaced with XML. You should convert your IdentityCard.h files to XML ones. Refer to [Migrating Your Identity Cards to XML](CAABtlMANIdCardXMLV5Mig.md). The following commands help you to do this:

  * The [mkICE](../CAABtlQuickRefs/CAABtlMkICEV5.md) command enables you to interactively edit an XML Identity Card, or open a .h Identity Card to save it as an XML one.
  * The [mkCreateIC](../CAABtlQuickRefs/CAABtlMkCreateICV5.md) command enables you to create an empty Identity Card ready to be edited using mkICE.
  * The [mkIc2Xml](../CAABtlQuickRefs/CAABtlMkIc2XmlV5.md) command enables you to convert a .h Identity Card to an XML one.

  
---  
Abstract The **IdentityCard.h** file is one of the files needed to build a program using the CAA Multi-Workspace Application Builder mkmk. The aim of this article is to explain the purpose of this file, how to write it and where it must be installed in the CAA FileTree.

  * **Purpose**
  * **Location**
  * **Content**

  
Purpose Since almost all components (frameworks) are built upon other components, it is necessary:

  * To include at compile time the corresponding header files
  * To reference at link time the corresponding libraries.

However the source files of a given component may include a lot of header files and, without the **IdentityCard** file, we must browse all the files to know the names of included header files and then find the names of the corresponding components. The IdentityCard file synthesizes these relationships between frameworks in order to get quickly the prerequisite frameworks. **Warning** : The **IdentityCard** file of any framework must at least contain a statement to set the **System** framework as a prerequisite framework up to its public part, as follows: `**AddPrereqComponent ( "System", Public);**` You must be aware that a user has often not all frameworks in his/her own workspace, and that most of the prerequisite frameworks he/she needs are located in other workspaces. Thanks to the IdentityCard file(s), tools like mkmk gain an easy way to determine and then access prerequisite frameworks. Basically The figure below gives a summary of the use of IdentityCard files. An application is made of components:

  * Built or not upon other components.
  * Using the CAA architecture each component is known as a framework possibly having prerequisite frameworks
  * Prerequisite frameworks of a given framework are specified in its IdentityCard file.

![](images/IdCard2.gif) Note also that:

  * Every framework has an IdentityCard file which can be empty if it does not need other component to implement its services. _This is not shown in the figure._
  * Only frameworks that are directly used are specified in an IdentityCard file.  
Remember the notions of public and private parts of a component: you don't know how a framework is implemented, so you shouldn't know its own prerequisites.

Top] Location Every framework must have an Identity Card file, named _IdentityCard.h_. This file is stored in directory _IdentityCard_ , right under the framework root directory itself:. This file allows the framework to declare (the list of) its prerequisite frameworks. ![](images/FileTree18.gif) Conversely, to export a service a framework must just store the header file of its service in its _PublicInterfaces_ directory. Content Syntax and rules The IdentityCard.h file is a text file containing depencies of the current framework. The syntax to declare a dependency is:
    
    
    **_AddPrereqComponent( "_**_< framework name>_**_" , Public);_**

```vbscript
For architecture matter, any type of framework (code, test, education) cannot declare a prerequisite on any type of framework. The following table specifies prerequisite composition rules depending on framework type.  
```

The table indicate if a a framework of type (Row header) can have a prerequisite on a framework of type (Column header).  Framework type| Code| Test (.tst)| Edu (.edu)  
---|---|---|---  
Code| YES| NO| NO  
Test (.tst)| YES| YES| YES  
Edu (.edu)| YES| NO| YES  
Examples In the following example, source _themine.cpp_ in _framework1/module1_ needs header _otherservice.h_ which is neither in module _module1_ , nor in _framework1_ , but in another framework named _framework2_. Thus, _framework1_ needs to declare _framework2_ as a prerequisite in its identity card: ![](images/IdCard.gif) The previous schema gives an example of a prerequisite between code frameworks, you can also have:

  * A prerequisite between an education framework (.edu) and a code framework - when the education framework contains code samples which need code frameworks to be implemented.
  * A prerequisite between an education framework and others education frameworks - if the first framework contains documents which refer to documents managed in others frameworks.

[Top]

* * *

History Version: **1** [Mar 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
