---
```vbscript
title: "Type Libraries in C++ for Windows"
category: "use-case"
module: "CAABtlTechArticles"
tags: []
source_file: "Doc/online/CAABtlTechArticles/CAABtlMANtlb.htmmd"
converted: "2026-05-11T17:33:46.134211"
```

---
tags: []
source_file: "Doc/online/CAABtlTechArticles/CAABtlMANtlb.htmmd"
converted: "2026-05-11T17:33:46.134211"
RADE |  Multi-Workspace Application Builder |  Type Libraries in C++ for Windows _Support of type libraries import in C++ sources for Windows_

converted: "2026-05-11T17:33:46.134211"
RADE |  Multi-Workspace Application Builder |  Type Libraries in C++ for Windows _Support of type libraries import in C++ sources for Windows_
Technical Article

* * *

The **#import** directive is used to reference type libraries. It is possible to import files named "**.olb** " or "**.tlb** ". The C++ compiler will generate two files named "**.tlh** " and "**.tli** " for each **#import** directive found. Those two files are standard C++ header used to compile C++ source code. 1 - C++ sources named ".tlbcpp" that imports the type libraries are built and header files are generated. During the "grammar1st" step of mkmk, files named "**.tlbcpp "** will be compiled as C++ sources. Because those sources use some **#import** directive, files named "**.tlh** " and "**.tli** " will be generated in addition to the "**.obj** ". All of these "**.tlh** " and "**.tli** " files will be moved to the generated interfaces directory according to a variable named **TLB_GENERATED_PATH,   **defined in the Imakefile.mk, that specify the level of their exposition.

  * **TLB_GENERATED_PATH = Public** to generated interfaces in PublicGenerated of the framework.
  * **TLB_GENERATED_PATH** = **Protected** to generated interfaces in ProtectedGenerated of the framework.
  * **TLB_GENERATED_PATH** = **Private** to generated interfaces in PrivateGenerated of the framework.
  * **TLB_GENERATED_PATH** = **Local** to generated interfaces in LocalGenerated of the module, **the default.**

All the imported files, "**.dll** ", "**.olb** " and "**.tlb** ", must be delivered as header in interfaces directories (PublicInterfaces, ProtectedInterfaces, PrivateInterfaces, LocalInterfaces). The compiler will search for them as a standard include file. Then, as the #include directive, the #import must reference imported files without any path name (i.e. #import "foo.olb"). **Attention** : Because this compilation occurs during the grammar1st step of mkmk, the "**.tlbcpp "** cannot contain more than the **#import** directives. Remember that many generated interfaces may not exist at this time. 2 -  C++ sources that include the generated files are compiled As "**.tlh** " and "**.tli** " files has been moved in generated interfaces directories, a ".cpp" file can #include these headers as other headers. [Top]

* * *

History Version: **1** [Jun 2003] | Document created
---|---
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
