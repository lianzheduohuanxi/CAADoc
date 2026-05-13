---
title: "CAAISysLine"
type: "PublicInterface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAASystem.edu/PublicInterfaces/CAAISysLine.h"
---

# CAAISysLine

> Interface which characterizes a line object. Inheritance: CATBaseUnknown (System Framework) Main Method: SetStartPoint/GetStartPoint SetEndPoint/GetEndPoint

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

## 纯虚方法 (接口契约)

### SetStartPoint

```cpp
virtual HRESULT SetStartPoint(const CATMathPoint & iStartPoint) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iStartPoint | `const CATMathPoint &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetEndPoint

```cpp
virtual HRESULT SetEndPoint(const CATMathPoint & iEndPoint) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iEndPoint | `const CATMathPoint &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetStartPoint

```cpp
virtual HRESULT GetStartPoint(CATMathPoint & oStartPoint) const = 0 ;
```

| 参数 | 类型 |
|------|------|
| oStartPoint | `CATMathPoint &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetEndPoint

```cpp
virtual HRESULT GetEndPoint(CATMathPoint & oEndPoint) const = 0 ;
```

| 参数 | 类型 |
|------|------|
| oEndPoint | `CATMathPoint &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAASystem.edu/PublicInterfaces/CAAISysLine.h`
