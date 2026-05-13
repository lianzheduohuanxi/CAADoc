---
title: "CAAIV5V6ExtMmrMultiMeasure"
type: "PublicInterface"
module: "CAAV5V6MechanicalModeler"
base: "CATBaseUnknown"
method_count: 5
source_file: "CAAV5V6MechanicalModeler.edu/PublicInterfaces/CAAIV5V6ExtMmrMultiMeasure.h"
---

# CAAIV5V6ExtMmrMultiMeasure

**基类**: CATBaseUnknown | **模块**: CAAV5V6MechanicalModeler | **方法数**: 5

## 依赖

- `CAAV5V6ExtMmrMultiMeasure.h`
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
virtual HRESULT GetGeomFeature(CATBaseUnknown *& oGeomFeature) = 0 ;
```

| 参数 | 类型 |
|------|------|
| oGeomFeature | `CATBaseUnknown *&` |

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

**源文件**: `CAAV5V6MechanicalModeler.edu/PublicInterfaces/CAAIV5V6ExtMmrMultiMeasure.h`
