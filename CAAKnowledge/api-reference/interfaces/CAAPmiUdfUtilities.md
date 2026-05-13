---
title: "CAAPmiUdfUtilities"
type: "ProtectedInterface"
module: "CAAPrismaticMachiningItf"
base: ""
method_count: 1
source_file: "CAAPrismaticMachiningItf.edu/ProtectedInterfaces/CAAPmiUdfUtilities.h"
---

# CAAPmiUdfUtilities

**基类**: 无 | **模块**: CAAPrismaticMachiningItf | **方法数**: 1

## 依赖

- `CAAPmiUdfEnv.h`
- `CATBaseUnknown.h`

## 静态方法

### GetUdfGeometry

```cpp
static HRESULT GetUdfGeometry(CATBaseUnknown * iUdf, CATUnicodeString iGeometryName, CATBaseUnknown_var &oGeometry) ;
```

GetUdfGeometry: Generic method to get a User Feature geometry from its role name

| 参数 | 类型 |
|------|------|
| iUdf | `CATBaseUnknown *` |
| iGeometryName | `CATUnicodeString` |
| &oGeometry | `CATBaseUnknown_var` |


---

**源文件**: `CAAPrismaticMachiningItf.edu/ProtectedInterfaces/CAAPmiUdfUtilities.h`
