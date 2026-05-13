---
title: "CAAEOmbExportTypeData"
type: "LocalClass"
module: "CAAObjectModelerBase"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAObjectModelerBase.edu/CAAOmbExportType.m/LocalInterfaces/CAAEOmbExportTypeData.h"
---

# CAAEOmbExportTypeData

> Implement interface ObjectModelerBase.CATIExportTypeManager for object CATProduct to OmbExportType

**基类**: CATBaseUnknown | **模块**: CAAObjectModelerBase | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CATUnicodeString.h`

## 虚方法

### ExportData

```cpp
virtual HRESULT ExportData(CATDocument * ipDoc, CATUnicodeString iPath) ;
```

CATIExportTypeManager Methods

| 参数 | 类型 |
|------|------|
| ipDoc | `CATDocument *` |
| iPath | `CATUnicodeString` |


### ExportData

```cpp
virtual HRESULT ExportData(CATUnicodeString iToExportPath, CATUnicodeString iExportedPath) ;
```

CATIExportTypeManager Methods

| 参数 | 类型 |
|------|------|
| iToExportPath | `CATUnicodeString` |
| iExportedPath | `CATUnicodeString` |


---

**源文件**: `CAAObjectModelerBase.edu/CAAOmbExportType.m/LocalInterfaces/CAAEOmbExportTypeData.h`
