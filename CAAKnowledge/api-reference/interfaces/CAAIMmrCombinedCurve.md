---
title: "CAAIMmrCombinedCurve"
type: "PublicInterface"
module: "CAAMechanicalModeler"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAAMechanicalModeler.edu/PublicInterfaces/CAAIMmrCombinedCurve.h"
---

# CAAIMmrCombinedCurve

**基类**: CATBaseUnknown | **模块**: CAAMechanicalModeler | **方法数**: 4

## 依赖

- `CAAMmrCombinedCurve.h`
- `CATBaseUnknown.h`

## 纯虚方法 (接口契约)

### SetCurve

```cpp
virtual HRESULT SetCurve(int iNum, CATISpecObject *ipCurve) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iNum | `int` |
| *ipCurve | `CATISpecObject` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetCurve

```cpp
virtual HRESULT GetCurve(int iNum, CATISpecObject **opCurve) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iNum | `int` |
| **opCurve | `CATISpecObject` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetDirection

```cpp
virtual HRESULT SetDirection(int iNum, CATISpecObject *ipDirection) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iNum | `int` |
| *ipDirection | `CATISpecObject` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetDirection

```cpp
virtual HRESULT GetDirection(int iNum, CATISpecObject **opDirection) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iNum | `int` |
| **opDirection | `CATISpecObject` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAMechanicalModeler.edu/PublicInterfaces/CAAIMmrCombinedCurve.h`
