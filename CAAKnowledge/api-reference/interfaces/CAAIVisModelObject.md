---
title: "CAAIVisModelObject"
type: "ProtectedInterface"
module: "CAAVisualization"
base: "CATBaseUnknown"
method_count: 6
source_file: "CAAVisualization.edu/ProtectedInterfaces/CAAIVisModelObject.h"
---

# CAAIVisModelObject

> Interface to manage objects handled by the CAAVisManager sample. Usage This interface is used to give ownership relations to objects that are handled in this sample. This interface defines a parent and child relationship. Thus using this interface allows you to define a ownership tree for any modeling structure. For example, objects that implement this interface are able to be made up of others objects or to be hold by other objects. Every object that wants to be part of the ownership tree of the user model has to implements the CAAIVisModelObject interface.

**基类**: CATBaseUnknown | **模块**: CAAVisualization | **方法数**: 6

## 依赖

- `CATBaseUnknown.h`
- `list.h`
- `CAAVisManagerInt.h`

## 纯虚方法 (接口契约)

### GetType

```cpp
virtual HRESULT GetType(char ** oType) = 0 ;
```

| 参数 | 类型 |
|------|------|
| oType | `char **` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetType

```cpp
virtual HRESULT SetType(const char * iType) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iType | `const char *` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### AddChild

```cpp
virtual HRESULT AddChild(CATBaseUnknown *iObject) = 0 ;
```

| 参数 | 类型 |
|------|------|
| *iObject | `CATBaseUnknown` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### RemChild

```cpp
virtual HRESULT RemChild(CATBaseUnknown *iObject) = 0 ;
```

| 参数 | 类型 |
|------|------|
| *iObject | `CATBaseUnknown` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### AddParent

```cpp
virtual HRESULT AddParent(CATBaseUnknown *iObject) = 0 ;
```

| 参数 | 类型 |
|------|------|
| *iObject | `CATBaseUnknown` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### RemParent

```cpp
virtual HRESULT RemParent(CATBaseUnknown *iObject) = 0 ;
```

| 参数 | 类型 |
|------|------|
| *iObject | `CATBaseUnknown` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAVisualization.edu/ProtectedInterfaces/CAAIVisModelObject.h`
