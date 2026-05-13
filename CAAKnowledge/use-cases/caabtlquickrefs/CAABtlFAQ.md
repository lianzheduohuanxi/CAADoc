---
```vbscript
title: "Frequently Asked Questions"
category: "use-case"
module: "CAABtlQuickRefs"
tags: ["CATIA", "CATIAB12", "CAADrwCreateDim", "CATIUnknownList"]
source_file: "Doc/online/CAABtlQuickRefs/CAABtlFAQ.htmmd"
converted: "2026-05-11T17:33:49.934183"
```

---
tags: ["CATIA", "CATIAB12", "CAADrwCreateDim", "CATIUnknownList"]
source_file: "Doc/online/CAABtlQuickRefs/CAABtlFAQ.htmmd"
converted: "2026-05-11T17:33:49.934183"
RADE |  Multi-Workspace Application Builder |  Frequently Asked Questions _Find answers to usual questions regarding mkmk family tools_

converted: "2026-05-11T17:33:49.934183"
RADE |  Multi-Workspace Application Builder |  Frequently Asked Questions _Find answers to usual questions regarding mkmk family tools_
Quick Reference

* * *

Abstract This article gathers answers to usual problems one user may encounter when using mkmk and related commands. Answers are grouped by topics listed below.
    * **Warnings Issued by Underlying Compilers and Linkers**
    * **Why Should I Avoid Unloading and Loading Modules?**
    * **Using /clr option is not supported**
---

* * *

Warnings Issued by Underlying Compilers and Linkers Warning on VC60.pdb on Windows The following warning is often issued: `Creating library E/TESTB12//./intel_a/code/bin/CAADrwCreateDim.lib and object E/TESTB12//./intel_a/code/bin/CAADrwCreateDim.exp SystemUUID.lib(CATIUnknownList.obj) : warning LNK4099: PDB "vc60.pdb" was not found with "E/CATIAB12//./intel_a/code/lib/SystemUUID.lib" or at "E/TESTB12/intel_a/code/bin/vc60.pdb"; linking object as if no debug info` It is due to the fact that some archives only contain UUID definitions which confuses the windows link-editor. This warning can be safely ignored. [Top] Why Should I Avoid Unloading and Loading Modules? Unloading a DLL while CATIA is running, and then reloading it is technically possible thanks to some system calls. Nevertheless, this may lead to unpredictable results such as memory corruptions, memory leaks, or even process crashes. This may happen because the unloaded DLL is reloaded at a different memory address. All the dynamic bindings set, for example, through QueryInterface, before the DLL unload and that might be held by objects in the other DLLs will now point to invalid addresses where no DLL is mapped any longer. When these objects are used, the application cannot thus behave as expected.

* * *

Using /clr is not supported. When building C++ modules, the /clr option can't be used. It is not compatible with the options used to build the V5 client applications, so such a module would not run in a V5 session.

* * *

History Version: **1** [Dec 2003] | Document created
---|---
[Top]

* * *

_Copyright 2003, Dassault Systmes. All rights reserved._
