---
title: "CAAIV5V6ExtMmrCCDataExtension"
type: "PublicInterface"
module: "CAAV5V6MechanicalModeler"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAAV5V6MechanicalModeler.edu/PublicInterfaces/CAAIV5V6ExtMmrCCDataExtension.h"
---

# CAAIV5V6ExtMmrCCDataExtension

**基类**: CATBaseUnknown | **模块**: CAAV5V6MechanicalModeler | **方法数**: 4

## 依赖

- `CAAV5V6ExtMmrCCDataExtension.h`
- `CATBaseUnknown.h`

## 纯虚方法 (接口契约)

### SetGeomFeature

```cpp
virtual HRESULT SetGeomFeature(CATBaseUnknown * ipGeomFeature) = 0 ;
```

| 参数 | 类型 |
|------|------|
| ipGeomFeature | `CATBaseUnknown *` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetGeomFeature

```cpp
virtual HRESULT GetGeomFeature(CATBaseUnknown*& opGeomFeature) = 0 ;
```

| 参数 | 类型 |
|------|------|
| opGeomFeature | `CATBaseUnknown*&` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### AggregateParam

```cpp
virtual HRESULT AggregateParam(CATICkeParm_var ispParmToAggregate) = 0 ;
```

| 参数 | 类型 |
|------|------|
| ispParmToAggregate | `CATICkeParm_var` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetValuatedParam

```cpp
virtual HRESULT GetValuatedParam(CATICkeParm_var& iospValuatedParm) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iospValuatedParm | `CATICkeParm_var&` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAV5V6MechanicalModeler.edu/PublicInterfaces/CAAIV5V6ExtMmrCCDataExtension.h`
