---
title: "CAAIMmrCCDataExtension"
type: "PublicInterface"
module: "CAAMechanicalModeler"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAAMechanicalModeler.edu/PublicInterfaces/CAAIMmrCCDataExtension.h"
---

# CAAIMmrCCDataExtension

**基类**: CATBaseUnknown | **模块**: CAAMechanicalModeler | **方法数**: 4

## 依赖

- `CAAMmrCCDataExtension.h`
- `CATBaseUnknown.h`

## 纯虚方法 (接口契约)

### SetGeomFeature

```cpp
virtual HRESULT SetGeomFeature(const CATBaseUnknown * ipGeomFeature) = 0 ;
```

| 参数 | 类型 |
|------|------|
| ipGeomFeature | `const CATBaseUnknown *` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetGeomFeature

```cpp
virtual HRESULT GetGeomFeature(CATISpecObject** ioGeomFeature) = 0 ;
```

| 参数 | 类型 |
|------|------|
| ioGeomFeature | `CATISpecObject**` |

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

**源文件**: `CAAMechanicalModeler.edu/PublicInterfaces/CAAIMmrCCDataExtension.h`
