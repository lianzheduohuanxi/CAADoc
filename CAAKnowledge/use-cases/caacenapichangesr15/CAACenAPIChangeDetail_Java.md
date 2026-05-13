---
title: "Detail Of API Changes"
category: "use-case"
module: "CAACenAPIChangesR15"
tags: "[]"
source_file: "Doc/online/CAACenAPIChangesR15/CAACenAPIChangeDetail_Java.htm"
converted: "2026-05-11T17:33:51.035437"
---
#

|
##

|
### Detail Of V5R15 Java API Changes

_What changes in the API compared with CAA V5R14_
---|---|---
Technical Article

* * *
### Abstract

This article presents by frameworks the detail of CAA Java resources modified in V5R15 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities.

---

* * *
## com.dassault_systemes.catjdialog.CATViewer

| Methods **saveState(#)** , **restoreState(java.lang.Object)** and ._internalRecordState(com.dassault_systemes.catjdialog.CATRecord, boolean) have been removed. None of them was meant to be used by CAA applications. The two first ones were used by the JVM to manage persistency, the last one was used by test tools | Check that you don't use them.
---|---

* * *
### References

[Top]

* * *
### History

Version: **1** [Jan 2003] | Document created
---|---
[Top]

* * *

_Copyright 2003, Dassault Systmes. All rights reserved._
