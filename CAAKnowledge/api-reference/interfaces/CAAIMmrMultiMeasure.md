---
title: "CAAIMmrMultiMeasure"
type: "ProtectedInterface"
module: "CAAMechanicalModeler"
base: "CATBaseUnknown"
method_count: 5
source_file: "CAAMechanicalModeler.edu/ProtectedInterfaces/CAAIMmrMultiMeasure.h"
---

# CAAIMmrMultiMeasure

**基类**: CATBaseUnknown | **模块**: CAAMechanicalModeler | **方法数**: 5

## 依赖

- `CAAMmrMultiMeasureAndMeasureSet.h`
- `CATBaseUnknown.h`

## 纯虚方法 (接口契约)

### SetInputGeomFeature

```cpp
virtual HRESULT SetInputGeomFeature(CATBaseUnknown * ipGeomFeature) = 0 ;
```

| 参数 | 类型 |
|------|------|
| ipGeomFeature | `CATBaseUnknown *` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetGeomFeature

```cpp
virtual HRESULT GetGeomFeature(CATISpecObject** ioGeomFeature) = 0 ;
```

| 参数 | 类型 |
|------|------|
| ioGeomFeature | `CATISpecObject**` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetLengthParameter

```cpp
virtual HRESULT GetLengthParameter(CATICkeParm_var &oLengthParm) = 0 ;
```

| 参数 | 类型 |
|------|------|
| &oLengthParm | `CATICkeParm_var` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetWetAreaParameter

```cpp
virtual HRESULT GetWetAreaParameter(CATICkeParm_var &oWetAreaParm) = 0 ;
```

| 参数 | 类型 |
|------|------|
| &oWetAreaParm | `CATICkeParm_var` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetVolumeParameter

```cpp
virtual HRESULT GetVolumeParameter(CATICkeParm_var &oVolumeParm) = 0 ;
```

| 参数 | 类型 |
|------|------|
| &oVolumeParm | `CATICkeParm_var` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAMechanicalModeler.edu/ProtectedInterfaces/CAAIMmrMultiMeasure.h`
