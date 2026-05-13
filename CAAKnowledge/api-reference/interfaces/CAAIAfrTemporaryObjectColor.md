---
title: "CAAIAfrTemporaryObjectColor"
type: "PublicInterface"
module: "CAAApplicationFrame"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAApplicationFrame.edu/PublicInterfaces/CAAIAfrTemporaryObjectColor.h"
---

# CAAIAfrTemporaryObjectColor

**基类**: CATBaseUnknown | **模块**: CAAApplicationFrame | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CAAAfrCustCommandHdrModel.h`

## 纯虚方法 (接口契约)

### GetCurrentColor

```cpp
virtual HRESULT GetCurrentColor(int & oRed, int & oGreen, int & oBlue) const = 0 ;
```

Returns the current color associated with the UI active object

| 参数 | 类型 |
|------|------|
| oRed | `int &` |
| oGreen | `int &` |
| oBlue | `int &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetCurrentColor

```cpp
virtual HRESULT SetCurrentColor(int & oRed, int & oGreen, int & oBlue) = 0 ;
```

| 参数 | 类型 |
|------|------|
| oRed | `int &` |
| oGreen | `int &` |
| oBlue | `int &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAApplicationFrame.edu/PublicInterfaces/CAAIAfrTemporaryObjectColor.h`
