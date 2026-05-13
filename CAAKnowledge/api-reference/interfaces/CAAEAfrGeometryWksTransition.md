---
title: "CAAEAfrGeometryWksTransition"
type: "LocalClass"
module: "CAAApplicationFrame"
base: "CATExtIWorkbenchTransition"
method_count: 1
source_file: "CAAApplicationFrame.edu/CAAAfrGeometryWksTransition.m/LocalInterfaces/CAAEAfrGeometryWksTransition.h"
---

# CAAEAfrGeometryWksTransition

> Extension of the CAAAfrGeometryWks workshop which enables to manage the transitions to this workshop. This is useful when the user selects the workshop from the start menu. This class implements the CATIWorkbenchTransition interface and is a data extension of a late type, whose name is composed of: workshopName + "_trans". It derives from the CATExtIWorkbenchTransition adapter. It gives the document type associated with the workshop, so that a document of this type can be activated or created when the workshop is selected. Illustrates: Managing workshop transitions. Inheritance: CATExtIWorkbenchTransition   (ApplicationFrame Framework) CATBaseUnknown (System Framework) ApplicationFrame Framework

**基类**: CATExtIWorkbenchTransition | **模块**: CAAApplicationFrame | **方法数**: 1

## 依赖

- `CATExtIWorkbenchTransition.h`

## 公共方法

### DoTransition

```cpp
int DoTransition(const CATString & ifromWS, const CATString & ifromWB, const CATString & itoWS, const CATString & itoWB) ;
```

| 参数 | 类型 |
|------|------|
| ifromWS | `const CATString &` |
| ifromWB | `const CATString &` |
| itoWS | `const CATString &` |
| itoWB | `const CATString &` |


---

**源文件**: `CAAApplicationFrame.edu/CAAAfrGeometryWksTransition.m/LocalInterfaces/CAAEAfrGeometryWksTransition.h`
