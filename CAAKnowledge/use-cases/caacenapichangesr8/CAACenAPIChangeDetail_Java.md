---
```vbscript
title: "Detail Of API Changes"
category: "api-changes"
module: "CAACenAPIChangesR8"
version: "V5R8"
tags: []
source_file: "Doc/online/CAACenAPIChangesR8/CAACenAPIChangeDetail_Java.htm"
converted: "2026-05-11T17:33:52.399807"
```

---
|  |  Detail Of V5R8 Java API Changes _What changes in the API compared with CAA V5R7_
---|---|---
Technical Article

* * *

Abstract This article presents by frameworks the detail of CAA Java resources modified in V5R8 and how to modify your code accordingly.Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities.

---

* * *

PortalBase: com.dassault_systemes.catweb.base.net.registry.PortalMIMECommand.java | method **PortalMIMECommand.setAssociatedMIMEType (com.dassault_systemes.catweb.base.net.registry.PortalMIMETypes)** is excluded while present in reference API | This whole class is exposed with read access only. This write method was exposed by error and was so removed accordingly.  Check that you don't use it.
---|---
PortalBase: com.dassault_systemes.catweb.base.net.registry.PortalMIMECommand.java | method **PortalMIMECommand.setAssociatedMIMEType (com.dassault_systemes.catweb.base.net.registry.PortalMIMETypes)** is excluded while present in reference API | This whole class is exposed with read access only. This write method was exposed by error and was so removed accordingly.  Check that you don't use it.
com.dassault_systemes.catweb.base.net.registry.PortalMIMETypes.java method **PortalMIMETypes.addExtension (java.lang.String)** is excluded while present in reference API | This whole class is exposed with read access only. Those write methods were exposed by error and were so removed accordingly.  Check that you don't use them.

PortalBase: com.dassault_systemes.catweb.base.net.registry.PortalMIMECommand.java | method **PortalMIMECommand.setAssociatedMIMEType (com.dassault_systemes.catweb.base.net.registry.PortalMIMETypes)** is excluded while present in reference API | This whole class is exposed with read access only. This write method was exposed by error and was so removed accordingly.  Check that you don't use it.
com.dassault_systemes.catweb.base.net.registry.PortalMIMETypes.java method **PortalMIMETypes.addExtension (java.lang.String)** is excluded while present in reference API | This whole class is exposed with read access only. Those write methods were exposed by error and were so removed accordingly.  Check that you don't use them.
method **PortalMIMETypes.addOptionalExtension (java.lang.String)** is excluded while present in reference API
method **PortalMIMETypes.addCommand (com.dassault_systemes.catweb.base.net.registry.PortalMIMECommand)** is excluded while present in reference API
method **PortalMIMETypes.insertCommand (com.dassault_systemes.catweb.base.net.registry.PortalMIMECommand, int)** is excluded while present in reference API

* * *

References |
---|---
[Top]

* * *

History Version: **1** [Dec 2001] | Document created
---|---
[Top]

* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
