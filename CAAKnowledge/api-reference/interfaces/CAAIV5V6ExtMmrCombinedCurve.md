---
title: "CAAIV5V6ExtMmrCombinedCurve"
type: "PublicInterface"
module: "CAAV5V6MechanicalModeler"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAAV5V6MechanicalModeler.edu/PublicInterfaces/CAAIV5V6ExtMmrCombinedCurve.h"
---

# CAAIV5V6ExtMmrCombinedCurve

**基类**: CATBaseUnknown | **模块**: CAAV5V6MechanicalModeler | **方法数**: 4

## 依赖

- `CAAV5V6ExtMmrCombinedCurve.h`
- `CATBaseUnknown.h`

## 纯虚方法 (接口契约)

### SetCurve

```cpp
virtual HRESULT SetCurve(int iNum, CATBaseUnknown *ipCurve) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iNum | `int` |
| *ipCurve | `CATBaseUnknown` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetCurve

```cpp
virtual HRESULT GetCurve(int iNum, CATBaseUnknown *&opCurve) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iNum | `int` |
| *&opCurve | `CATBaseUnknown` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetDirection

```cpp
virtual HRESULT SetDirection(int iNum, CATBaseUnknown *ipDirection) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iNum | `int` |
| *ipDirection | `CATBaseUnknown` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetDirection

```cpp
virtual HRESULT GetDirection(int iNum, CATBaseUnknown *&opDirection) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iNum | `int` |
| *&opDirection | `CATBaseUnknown` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAV5V6MechanicalModeler.edu/PublicInterfaces/CAAIV5V6ExtMmrCombinedCurve.h`
