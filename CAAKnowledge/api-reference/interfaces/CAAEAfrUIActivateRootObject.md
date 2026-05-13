---
title: "CAAEAfrUIActivateRootObject"
type: "LocalClass"
module: "CAAApplicationFrame"
base: "CATExtIUIActivate"
method_count: 0
source_file: "CAAApplicationFrame.edu/CAAAfrSampleDocument.m/LocalInterfaces/CAAEAfrUIActivateRootObject.h"
---

# CAAEAfrUIActivateRootObject

> Data extension of the root object of the document. It implements the CATIUIActivate interface in order to associate a workshop with the document. It derives from the CATExtIUIActivate adapter which provides most of the implementation. Illustrates: implementation of the CATIUIActivate interface to associate a workshop with a document. Usage: Launch CATIA V5, File/New. Choose the Geometry document. The Geometry workshop is loaded. Inheritance: CATExtIUIActivate ( ApplicationFrame Framework ) CATBaseUnknown    (System Framework). Main Method: GetWorkshop : returns the workshop name GetDefaultCommand : returns the name of the default command.

**基类**: CATExtIUIActivate | **模块**: CAAApplicationFrame | **方法数**: 0

## 依赖

- `CATExtIUIActivate.h`
- `CATString.h`

---

**源文件**: `CAAApplicationFrame.edu/CAAAfrSampleDocument.m/LocalInterfaces/CAAEAfrUIActivateRootObject.h`
