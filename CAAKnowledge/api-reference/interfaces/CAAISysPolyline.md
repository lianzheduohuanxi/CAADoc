---
title: "CAAISysPolyline"
type: "PublicInterface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAASystem.edu/PublicInterfaces/CAAISysPolyline.h"
---

# CAAISysPolyline

> Interface which characterizes a Polyline object. Inheritance: CATBaseUnknown (System Framework) Main Method: GetListPoint/SetListPoint GetCloseStatus/SetCloseStatus System Framework

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

## 纯虚方法 (接口契约)

### SetListPoint

```cpp
virtual HRESULT SetListPoint(const int iPointCount, CATMathPoint * iList) = 0 ;
```

iList contains at least 3 points else error. This list is duplicated in the polyline data.

| 参数 | 类型 |
|------|------|
| iPointCount | `const int` |
| iList | `CATMathPoint *` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetListPoint

```cpp
virtual HRESULT GetListPoint(int * oPointCount, CATMathPoint ** oList) = 0 ;
```

| 参数 | 类型 |
|------|------|
| oPointCount | `int *` |
| oList | `CATMathPoint **` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetCloseStatus

```cpp
virtual HRESULT SetCloseStatus(const int iIsClosed) = 0 ;
```

1 - Closed : It's a polygone 0 - Open   : It's a polyline

| 参数 | 类型 |
|------|------|
| iIsClosed | `const int` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetCloseStatus

```cpp
virtual HRESULT GetCloseStatus(int * oIsClosed) = 0 ;
```

| 参数 | 类型 |
|------|------|
| oIsClosed | `int *` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAASystem.edu/PublicInterfaces/CAAISysPolyline.h`
