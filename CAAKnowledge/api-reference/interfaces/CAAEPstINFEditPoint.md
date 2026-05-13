---
title: "CAAEPstINFEditPoint"
type: "LocalClass"
module: "CAAProductStructure"
base: "CATExtIEdit"
method_count: 1
source_file: "CAAProductStructure.edu/CAAPstINFCommands.m/LocalInterfaces/CAAEPstINFEditPoint.h"
---

# CAAEPstINFEditPoint

> Data extension of the CAAPstINFPoint component, implementing the CATIEdit interface to enable the edition of the points. This class derives from the CATExtIEdit adapter. Illustrates programming the edition of an object by implementing the CATIEdit interface of the ApplicationFrame framework. The CATIEdit interface has 2 methods: Activate and GetPanelItem. Only Activate needs to be redefined. Its aim is to return a command that edits the object. Inheritance: CATExtIEdit (ApplicationFrame Framework) CATBaseUnknown (System Framework) Main Method: Activate: Returns a CATCommand to edit the selected point.

**基类**: CATExtIEdit | **模块**: CAAProductStructure | **方法数**: 1

## 依赖

- `CATExtIEdit.h`

## 虚方法

### Activate

```cpp
virtual CATCommand * Activate(CATPathElement *ipPath) ;
```

Activate -------- Returns a CATCommand to edit the selected point. iPath is the path from the root object to the selected object

| 参数 | 类型 |
|------|------|
| *ipPath | `CATPathElement` |


---

**源文件**: `CAAProductStructure.edu/CAAPstINFCommands.m/LocalInterfaces/CAAEPstINFEditPoint.h`
