---
title: "CAAIAfrMRUManagement"
type: "PublicInterface"
module: "CAAApplicationFrame"
base: "CATBaseUnknown"
method_count: 3
source_file: "CAAApplicationFrame.edu/PublicInterfaces/CAAIAfrMRUManagement.h"
---

# CAAIAfrMRUManagement

**基类**: CATBaseUnknown | **模块**: CAAApplicationFrame | **方法数**: 3

## 依赖

- `CATBaseUnknown.h`
- `CATListOfCATUnicodeString.h`
- `CAAAfrCustCommandHdrModel.h`

## 纯虚方法 (接口契约)

### AddElement

```cpp
virtual HRESULT AddElement(CATUnicodeString &iNewElement) = 0 ;
```

Adds a new item

| 参数 | 类型 |
|------|------|
| &iNewElement | `CATUnicodeString` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetElementList

```cpp
virtual HRESULT GetElementList(CATListOfCATUnicodeString &ElementList) const = 0 ;
```

Retrieves the list of items

| 参数 | 类型 |
|------|------|
| &ElementList | `CATListOfCATUnicodeString` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SelectElement

```cpp
virtual HRESULT SelectElement(int iPosition) = 0 ;
```

Selects an element of the list

| 参数 | 类型 |
|------|------|
| iPosition | `int` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAApplicationFrame.edu/PublicInterfaces/CAAIAfrMRUManagement.h`
