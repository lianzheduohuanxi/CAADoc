---
```vbscript
title: "CAA V5R16 News Highlights"
category: "use-case"
module: "CAACenQuickRefs"
tags: ["CATIParameterEditor", "CATIIniSearchSymbolCriterion", "CATIXMLSAXFactory", "CATIBehOperationManagement", "CATIEwrFilter", "CATIxPDMSendToService", "CATIXMLDOMDocumentBuilder", "CATIVizVisualizationSettingAtt", "CATIVariableManagement", "CATICafSearchSettingAtt", "CATIA"]
source_file: "Doc/online/CAACenQuickRefs/CAACenNewsR16.htm"
converted: "2026-05-11T17:33:47.006273"
```

---
tags: ["CATIParameterEditor", "CATIIniSearchSymbolCriterion", "CATIXMLSAXFactory", "CATIBehOperationManagement", "CATIEwrFilter", "CATIxPDMSendToService", "CATIXMLDOMDocumentBuilder", "CATIVizVisualizationSettingAtt", "CATIVariableManagement", "CATICafSearchSettingAtt", "CATIA"]
source_file: "Doc/online/CAACenQuickRefs/CAACenNewsR16.htm"
converted: "2026-05-11T17:33:47.006273"
CAA V5 Encyclopedia |  |  CAA V5R16 News Highlights _News in CAA V5R16 C++ and Java_

converted: "2026-05-11T17:33:47.006273"
CAA V5 Encyclopedia |  |  CAA V5R16 News Highlights _News in CAA V5R16 C++ and Java_
Technical Article

* * *

Abstract Here are the CAA V5R16 news highlighted per solution and modeler. This article lists them, and points to the corresponding documentation.

  * **CAA V5R16 Detailed News**
    * Web Services
    * Enterprise Architecture
    * PPR Hub
    * Product Synthesis & Knowledgeware
    * Analysis
    * Equipment & Systems
    * RADE
  * **References**

---

* * *

CAA V5R16 News The following is new with CAA V5R16. Web Services

  * Web services. Refer to the [Web Services home page](../CAACenWeb/CAACenWSHome.md).

[Top] Enterprise Architeture

  * XML API enhancements In CAA V5R15, there were only two ways to feed XML to the DOM or SAX parsers: either the XML had to be in a file, or it had to be in a buffer in memory. CAA V5R16 introduces a third form of customizable input source which enables you to inject XML in a DOM or SAX parser without the overhead of copying the whole content to a previously allocated memory buffer. This user-defined input sources are instantiated by calling the  CreateInputSourceFromStream method from the already CAA  CATIXMLSAXFactory interface. New detection functions enables you to know at runtime if a particular XML API implementation is available.
    1. DetectCATIXMLDOMDocumentBuilder to find out DOM implementations
    2. DetectCATIXMLSAXFactory to find out SAX implementations
Using these functions, you can then devise a strategy for a web browser plug-in, in which you first attempt to use a pre-installed implementation if available (MSXML5.0), and fall back to the default implementation if this fails. The CLSID for MSXML5.0 and the detection functions for parsers are declared in the CATIXMLSAXFactory and CATIXMLDOMDocumentBuilder headers which are already CAA. New articles and use cases are created to support the XMLParser framework usage and are available from the [XML home page](../CAACenWeb/CAACenV5MiddlewareXML.md).

  * Settings Backface culling mode setting is enriched to manage new values. An algorithm called “back face culling” has been created to enhance rendering performance by not drawing the internal faces of solids. This algorithm is systematically applied on solids but, for stand-alone faces and surfaces, the choice is left to the end user through a setting. In V5R16, a new setting provides a way to disable the use of the “back face culling” algorithm for all the objects so that, even when navigating inside the model and entering solid objects, these ones are rendered with all their faces. This new possibility will help customers during interactive navigation and product analysis by displaying all the faces associated to objects. This is managed thanks to the  CATIVizVisualizationSettingAtt interface.
  * Workbench ordering in the Start menu Your workbenches can now be ordered in the Start menu according to your own criteria, and sub menus can be created. For example, workbenches of the Equipment & Systems solution have used this capability. This facilitates the access to a workbench since it will be logically classified and positioned. The enhancement enables you to:
1. DetectCATIXMLDOMDocumentBuilder to find out DOM implementations
2. DetectCATIXMLSAXFactory to find out SAX implementations
Using these functions, you can then devise a strategy for a web browser plug-in, in which you first attempt to use a pre-installed implementation if available (MSXML5.0), and fall back to the default implementation if this fails. The CLSID for MSXML5.0 and the detection functions for parsers are declared in the CATIXMLSAXFactory and CATIXMLDOMDocumentBuilder headers which are already CAA. New articles and use cases are created to support the XMLParser framework usage and are available from the [XML home page](../CAACenWeb/CAACenV5MiddlewareXML.md).
    1. Classify items inside a menu
    2. Create sub-menus
    3. Automatically rearrange the Tools/Options graph according to the changes of the Start menu presentation.
This is done in the workbench resource file.

[Top] PPR Hub

  * Send to C++ API  Send to enables you to copy a V5 document, along with all the other V5 documents it is linked to, to another folder, keeping link consistency, for example, to send that set of documents to a supplier. The Send to capability was up to now provided using an IDL interface to be used from Automation. A C++ counterpart,  CATIxPDMSendToService, is delivered in V5R16 to be used with the existing interfaces and classes of the CATxPDMInterfaces framework. This capability requires a CATIA - PPR PDM Gateway 1 Product (PX1) license.
  * New style for native parameter editor  Thanks to the style customization available through the interface  CATIParameterEditor, you will be able to unset a parameter with the contextual menu of the parameter editor.
  * Settings: Search command  The Search and Power Input functionnalities offer new capabilities for a better operability, in particular for most common queries in order to enhance productivity. This is managed through two new settings interfaces:  CATICafSearchSettingAtt and  CATIIniSearchSymbolCriterion.

[Top] Product Synthesis & Knowledgeware In Business Knowledge Templates (BKT), two new interfaces to manage and access characteristics of main BKT objects:

  1. CATIVariableManagement is available on the BKT types, the typed objects and the behaviors. It contains a set of methods to access the variables of these objects
1. CATIVariableManagement is available on the BKT types, the typed objects and the behaviors. It contains a set of methods to access the variables of these objects
  2. CATIBehOperationManagement manages the different states of a behavior (Done, Started, Suspended, and Canceled).

These two interfaces will allow clients to create they own commands and use them in a BKT process. [Top] Analysis DS command reusability in customers' workbenches: you can now programmatically insert identified DS commands into your own workbenches. This is restricted to commands and workbenches of the Analysis solution. See [ Command Access](../CAAAniQuickRefs/CAAAniCommandAccess.md) for additional information and the list of commands you can reuse. [Top] Equipement & Systems To help DMU review of Electrical Harness by configuration, it is currently possible to interactively filter a 150% harness (also named the maximum configuration) by implementing some User Interface Program (UIP) than enables the end user to get, for a given harness, the list of criteria (can be a configuration) and to retrieve from a particular criteria the list of active wires. The new filtering interface  CATIEwrFilter enables you now to do this from a program. [Top] RADE When creating Web applications, you can use input and output parameters to interact with Modular 3d com. Creating an Application to be Integrated to Modular 3Dcom](../CAADkiUseCases/CAADkiIdentityCard.md) [Top]

* * *

References [1] | [What's New](CAACenWhatsNew.md)
---|---
[Top]

* * *

History Version: **1** [Jun 2005] | Document created
---|---
[Top]

* * *

_Copyright 1994-2005, Dassault Systmes. All rights reserved._
