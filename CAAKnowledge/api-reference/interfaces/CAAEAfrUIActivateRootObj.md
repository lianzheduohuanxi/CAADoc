---
title: "CAAEAfrUIActivateRootObj"
type: "LocalClass"
module: "CAAApplicationFrame"
base: "CATExtIUIActivate"
method_count: 2
source_file: "CAAApplicationFrame.edu/CAAAfrGeoDocument.m/LocalInterfaces/CAAEAfrUIActivateRootObj.h"
---

# CAAEAfrUIActivateRootObj

> Data extension of the root object of the document. It implements the CATIUIActivate interface in order to associate a workshop with the document. It derives from the CATExtIUIActivate adapter which provides most of the implementation. Illustrates: implementation of the CATIUIActivate interface to associate a workshop with a document. Usage: Launch CATIA V5, File/New. Choose the CAAGeometry document. The CAAGeometryWks workshop is loaded. Inheritance: CATExtIUIActivate ( ApplicationFrame Framework ) CATBaseUnknown    (System Framework). Main Method: GetWorkshop       : returns the workshop name GetDefaultCommand : returns the name of the default command.

**基类**: CATExtIUIActivate | **模块**: CAAApplicationFrame | **方法数**: 2

## 依赖

- `CATExtIUIActivate.h`
- `CATString.h`

## 虚方法

### GetWorkshop

```cpp
virtual CATString & GetWorkshop() ;
```

GetWorkshop ------------ Returns the workshop identifier. This identifier is the name of class which implements CATIWorkshop


### GetDefaultCommand

```cpp
virtual CATString & GetDefaultCommand() ;
```

GetDefaultCommand ------------------ Returns the command header identifier of the default command. The default command is the one that is made active whenever the object which implements CATIUIActivate becomes UIActive.


---

**源文件**: `CAAApplicationFrame.edu/CAAAfrGeoDocument.m/LocalInterfaces/CAAEAfrUIActivateRootObj.h`
