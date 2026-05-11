---
title: "CAAEOmbExportTypeData"
type: "interface"
module: "CAAObjectModelerBase"
base: "CATBaseUnknown"
method_count: 2
visibility: "local"
verified: true
---

# CAAEOmbExportTypeData

**基类**: CATBaseUnknown  
**模块**: CAAObjectModelerBase  
**可见性**: local  
**方法数**: 2

> ===========================================================================

## 方法列表

### ExportData
```cpp
HRESULT ExportData(CATDocument      * ipDoc,
                                 CATUnicodeString   iPath);
```

### ExportData
```cpp
HRESULT ExportData(CATUnicodeString iToExportPath,
                                 CATUnicodeString iExportedPath);
```

## 依赖

- `CATBaseUnknown.h`
- `CATUnicodeString.h`

