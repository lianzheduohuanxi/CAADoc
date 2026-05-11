---
title: "The XML IdentityCard Special File"
category: "use-case"
module: "CAABtlTechArticles"
tags: []
source_file: "Doc/online/CAABtlTechArticles/CAABtlMANIdCardXMLV5.htm"
converted: "2026-05-11T17:33:46.062618"
---

RADE |  Multi-Workspace Application Builder |  The XML IdentityCard Special File _Purpose and use_  
---|---|---  
Technical Article  
  
* * *

Abstract The XML **IdentityCard** file is one of the files needed to build a program using the Rich Application Builder mkmk. The aim of this article is to explain the purpose of this file, how to write it and where it must be installed in the file tree.

  * Purpose
  * Location
  * Content
    * Syntax
    * Framework Prerequisite Compatibility
    * Prerequisite Completeness
  * Examples
    * Example 1: Basic Use Case
    * Example 2: Prerequisite Completeness
  * References

  
---  
Purpose Since almost all components (frameworks) are built upon other components, it is necessary:

  * To include at compile time the corresponding header files.
  * To reference at link time the corresponding libraries.

However the source files of a given component may include a lot of header files and, without the **IdentityCard** file, we must browse all the files to know the names of included header files and then find the names of the corresponding components. The IdentityCard file synthesizes these relationships between frameworks in order to get quickly the prerequisite frameworks. **Warning** : The **IdentityCard** file of any framework must at least contain a statement to set the **System** framework as a prerequisite framework up to its public part, as follows:
    
    
    ...
      <prerequisite name="System" access ="Public" />
    ...

You must be aware that a user has often not all frameworks in his/her own workspace, and that most of the prerequisite frameworks he/she needs are located in other workspaces. Thanks to the IdentityCard file(s), tools like mkmk gain an easy way to determine and then access prerequisite frameworks. The figure below gives a summary of the use of IdentityCard files. An application is made of components:

  * Built or not upon other components.
  * Using the architecture each component is known as a framework possibly having prerequisite frameworks
  * Prerequisite frameworks of a given framework are specified in its IdentityCard file.

 A logical view of the architecture, seen from the application standpoint  
---|---  
Each framework owns an IdentityCard file which declares its prerequisite frameworks.  
A framework having no prerequisite at all has an empty IdentityCard file.  
Note also that:  
Each framework has an IdentityCard file which can be empty if it does not need other component to implement its services. [Top] Location Each framework must have an Identity Card file, named IdentityCard.xml. This file is located in the folder IdentityCard, just below the framework root folder itself. This file allows the framework to declare (the list of) its prerequisite frameworks. ![IdentityCard Folder](images/CAABtlIdCard19V5.png) Conversely, to export a service, a framework must just store the header file of its service in its PublicInterfaces folder. [Top] Content This section describes the Identity Card content. Note that you can use mkCreateIC [2] to create an empty and valid Identity Card XM file, and mkICE to edit it [3]. Syntax The IdentityCard.xml file is a text file containing dependencies of the current framework. The syntax to declare a dependency is:
    
    
    **< prerequisite name="**_framework name_ " [**a****ccess** ="_itfScope_ "] [**expose** ="_exposeScope_ "] [**export** ="_exportScope_ "] /> 

Attribute | Value | Description | Required | Default Value  
---|---|---|---|---  
`name` | `framework name` | The name of the prerequisite frameworks. | Yes | None  
`access` | `itfScope` | The scope of interfaces required (**Public** , **Protected** , **Private**). For example, **Public** will give access to all interfaces in the PublicInterfaces folder of the prerequisite framework. **Protected** will give access to all interfaces in the ProtectedInterfaces and PublicInterfaces folders of the prerequisite framework.  
When you set a prerequisite to a Dassault Systèmes framework, this must always be set to **Public**. | No | Public  
`expose` | `exposeScope` | Specifies whether the current framework exposes the headers of its prerequisite. In other words, specifies whether the client frameworks of the current one may also need the prerequisite to build. If so, use the value **ExposePrereq** , and this prerequisite is silently added to those of the client frameworks. Otherwise, use **DoNotExposePrereq**. | No | ExposePrereq  
`export` | `exportScope` | Specifies whether the current framework exports its prerequisite for link-edit purposes. **Internal. Do not use.** This is useful for modularization purposes, when a module is broken into several ones among which some are moved to other frameworks. In this case, these other frameworks are added to the prerequisites of the current ones, and using **AddToClientPrereqs** for each of them, they are also added to the prerequisites of its clients, avoiding them to be broken at link-edit time. Otherwise, set it to **DoNotAddToClientPrereqs**. | No | AddToClientPrereqs  
Framework Prerequisite Compatibility For architecture matter, any type of framework (code, test, education) cannot declare a prerequisite on any type of framework. The following table specifies prerequisite composition rules depending on framework type.  
The table indicate if a framework of type (Row header) can have a prerequisite on a framework of type (Column header).  Framework type | Code | Test (.tst) | Edu (.edu)  
---|---|---|---  
Code | Yes | No | No  
Test (.tst) | Yes | Yes | Yes  
Edu (.edu) | Yes | No | Yes  
Prerequisite Completeness A framework must declare Frameworks prerequisites are explicit, you need to specify all frameworks you will need (directly or not) to compile. Please refer to Example 2 for more details Export and Expose Those concepts exist to ensure stability or architecture and are mostly used when frameworks are layered. A framework required by others frameworks (its clients) must as much as possible prevents its clients to break when it changes or at least detect a possibility of breaking its clients.  By specifying export with the value of AddToClientPrereqs for a prerequisite, all clients of the framework will also inherit that prerequisite. If the value is DoNotAddToClientPrereqs, the client will have to declare it if it needs it to build.  A framework expose or not interfaces from its prerequisite. If in its own Public, Protected or Private interfaces a framework reference an header from its prerequisite then its clients will also need it to build. In this case, the framework must declare the prerequisite as exposed by specifying expose with the value of ExposePrereq. Exposing headers from its prerequisites but not declaring them is considering to be an architecture error and will provoke a BAD004 error to appear during build.  [Top] Examples Example 1: Basic Use Case In the following example, the source file myObject.cpp in Framework1/Module1 includes the header file ExposedService.h __ which is neither in module Module1, nor in Framework1, but in another framework named Framework2. Thus, Framework1 needs to declare Framework2 as a prerequisite in its IdentityCard.xml file: ![Example](images/CAABtlIdCard01V5.png) The schema above gives an example of a prerequisite between two code frameworks. You can also have:

  * A prerequisite between an education framework (.edu) and a code framework, when the education framework contains code samples which need code frameworks to be implemented.
  * A prerequisite between an education framework and other education frameworks, if the first framework contains files which refer to files located in other frameworks.

Example 2: Prerequisite Completeness A framework must declare as a prerequisite any framework it will need to be built. In the following example, Framework1 must declare a prerequisite on DirectPrereqFW1 and DirectPrereqFW2 because it's header and source directly reference a .h from those frameworks but it also need to declare IndirectPrereqFW1 and IndirectPrereqFW2 because those framework will also be needed to build.  ![Prerequisite Completeness](images/CAABtlIdCard03V5.png) **Note** : Framework1 must also declare DirectPrereqFW1 as exposed but not DirectPrereqFW2. This way, the architecture is more explicit and the build is safer. **Note** : The `AddToClientPrereqs` value modifies this behavior. See [1] for guidelines on how and when to use it. [Top] References [1] |  Framework Architecture Rules  
---|---  
[2] | [mkCreateIC](../CAABtlQuickRefs/CAABtlMkCreateICV5.md)  
[3] | [mkICE](../CAABtlQuickRefs/CAABtlMkICEV5.md)  
History Version: **1** [Jun 2011] | Document created  
---|---  
[Top] _Copyright 2013, Dassault Systmes. All rights reserved._
