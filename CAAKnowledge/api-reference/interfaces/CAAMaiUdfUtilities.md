---
title: "CAAMaiUdfUtilities"
type: "PublicInterface"
module: "CAAManufacturingItf"
base: ""
method_count: 1
source_file: "CAAManufacturingItf.edu/PublicInterfaces/CAAMaiUdfUtilities.h"
---

# CAAMaiUdfUtilities

**基类**: 无 | **模块**: CAAManufacturingItf | **方法数**: 1

## 依赖

- `CAAMaiUdfEnv.h`
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

**源文件**: `CAAManufacturingItf.edu/PublicInterfaces/CAAMaiUdfUtilities.h`
