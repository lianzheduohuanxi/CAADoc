---
title: "CAAISysColorProperties"
type: "PublicInterface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAASystem.edu/PublicInterfaces/CAAISysColorProperties.h"
---

# CAAISysColorProperties

> Interface to modify the color . Inheritance: CATBaseUnknown (System Framework). Main Methods: GetColor SetColor

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

## 纯虚方法 (接口契约)

### GetColor

```cpp
virtual HRESULT GetColor(int & oRed, int & oGreen, int & oBlue) = 0 ;
```

| 参数 | 类型 |
|------|------|
| oRed | `int &` |
| oGreen | `int &` |
| oBlue | `int &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetColor

```cpp
virtual HRESULT SetColor(const int iRed, const int iGreen, const int iBlue) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iRed | `const int` |
| iGreen | `const int` |
| iBlue | `const int` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAASystem.edu/PublicInterfaces/CAAISysColorProperties.h`
