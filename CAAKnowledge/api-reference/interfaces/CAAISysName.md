---
title: "CAAISysName"
type: "PublicInterface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAASystem.edu/PublicInterfaces/CAAISysName.h"
---

# CAAISysName

> Interface which manages the name of the CAAGeometry's object. Inheritance: CATBaseUnknown (System Framework) Main Methods: SetName: Sets the name of the component Getname: Retrieves the name of the component

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

## 纯虚方法 (接口契约)

### SetName

```cpp
virtual HRESULT SetName(const CATUnicodeString & iName) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iName | `const CATUnicodeString &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetName

```cpp
virtual HRESULT GetName(CATUnicodeString & ioName) = 0 ;
```

| 参数 | 类型 |
|------|------|
| ioName | `CATUnicodeString &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAASystem.edu/PublicInterfaces/CAAISysName.h`
