---
title: "Detail Of API Changes"
category: "api-changes"
module: "CAACenAPIChangesR9"
tags: "[]"
source_file: "Doc/online/CAACenAPIChangesR9/CAACenAPIChangeDetail_Java.htm"
converted: "2026-05-11T17:33:52.828206"
---
|  |  Detail Of V5R9 Java API Changes _What changes in the API compared with CAA V5R8_
---|---|---
Technical Article

* * *

Abstract This article presents by frameworks the detail of CAA Java resources modified in V5R9 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities.

---

* * *

com.dassault_systemes.enovaultclientjava.vdk0vaultclient.ENOVIVaultUserSession.java  | interface **ENOVIVaultUserSession** has 10 more method(s) than in reference APImethod  | Implement new methods.
---|---
com.dassault_systemes.catweb.documents.DocumentsV4.java method **DocumentV4.MainDraft (com.dassault_systemes.catweb.documents)** is excluded while present in reference API | This whole class is exposed with read access only. This write method was exposed by error and was so removed accordingly.  Check that you don't use it.
---|---

* * *

References |
---|---
[Top]

* * *

History Version: **1** [Mar 2002] | Document created
---|---
[Top]

* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
