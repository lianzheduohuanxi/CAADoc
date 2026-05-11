---
title: "The Prerequisites on Windows NT"
category: "use-case"
module: "CAABtlTechArticles"
tags: []
source_file: "Doc/online/CAABtlTechArticles/CAABtlMANPrereqNT.md"
converted: "2026-05-11T17:33:46.125203"
---

RADE |  Multi-Workspace Application Builder |  The Prerequisites on Windows NT _Explicitly declaring DLL_  
---|---|---  
Technical Article  
  
* * *

Abstract An inherent mechanism on Windows NT imposes that the shared librairies (dll) declare explicitly what they import and what they export.

  * **How to Define Prerequisites between Frameworks**
  * **Generic Solution through mkmk**

  
---  
How to Define Prerequisites between Frameworks When a framework exports services, it must explicitly declare them. If you omit that, the other frameworks cannot import the exported services. The following figure explains what is mandatory to declare for using services from a DLL in a prerequisite framework. FW1 framework exports services through visu.h header file. The themine.cpp file of FW2 needs services from FW1. ![](images/FileTree5.gif) [Top] Generic Solution through mkmk Given this architecture, a generic mechanism has been set to discharge the developer to deal with these export-import issues. Here is the declarative section that should be added to every header file which belongs to a PublicInterfaces directory. ![](images/prereqNT.gif) At compile time, when it is operated on Windows NT, mkmk defines /D option _WINDOWS_SOURCE. It does not do so on Unix. Furthermore, when mkmk processes the module owner of the header, it defines variable __<modulename>. [Top]

* * *

History Version: **1** [Mar 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
