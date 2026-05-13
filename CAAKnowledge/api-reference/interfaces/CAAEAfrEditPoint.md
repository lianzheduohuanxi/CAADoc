---
title: "CAAEAfrEditPoint"
type: "LocalClass"
module: "CAAApplicationFrame"
base: "CATExtIEdit"
method_count: 1
source_file: "CAAApplicationFrame.edu/CAAAfrGeoEdition.m/LocalInterfaces/CAAEAfrEditPoint.h"
---

# CAAEAfrEditPoint

> Data extension of the CAASysPoint component, implementing the CATIEdit interface to enable the edition of the points. This class derives from the CATExtIEdit adapter. Illustrates: programming the edition of an object by implementing the CATIEdit interface. The CATIEdit interface has 2 methods: Activate and GetPanelItem. Only Activate needs to be redefined. Its aim is to return a command be edits the object. Inheritance: CATExtIEdit ( ApplicationFrame Framework) CATBaseUnknown (System Framework). Main Method: Activate: Returns a CATCommand to edit the selected point. ApplicationFrame Framework

**基类**: CATExtIEdit | **模块**: CAAApplicationFrame | **方法数**: 1

## 依赖

- `CATExtIEdit.h`

## 虚方法

### Activate

```cpp
virtual CATCommand * Activate(CATPathElement * iPath) ;
```

Activate -------- Returns a CATCommand to edit the selected point. iPath is the path from the root object to the selected object

| 参数 | 类型 |
|------|------|
| iPath | `CATPathElement *` |


---

**源文件**: `CAAApplicationFrame.edu/CAAAfrGeoEdition.m/LocalInterfaces/CAAEAfrEditPoint.h`
