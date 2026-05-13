---
title: "CAAISmiUserMachFeature"
type: "ProtectedInterface"
module: "CAASurfaceMachiningItf"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAASurfaceMachiningItf.edu/ProtectedInterfaces/CAAISmiUserMachFeature.h"
---

# CAAISmiUserMachFeature

**基类**: CATBaseUnknown | **模块**: CAASurfaceMachiningItf | **方法数**: 1

## 依赖

- `CAASmiUserMachFeatureEnv.h`
- `CATBaseUnknown.h`
- `CATListOfCATGeometries.h`

## 纯虚方法 (接口契约)

### GetGuideParameter

```cpp
virtual HRESULT GetGuideParameter(CATBaseUnknown_var &oParameter) = 0 ;
```

Gets parameter of the guide of our Machining Feature.

| 参数 | 类型 |
|------|------|
| &oParameter | `CATBaseUnknown_var` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAASurfaceMachiningItf.edu/ProtectedInterfaces/CAAISmiUserMachFeature.h`
