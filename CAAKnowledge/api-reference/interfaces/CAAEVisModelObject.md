---
title: "CAAEVisModelObject"
type: "LocalClass"
module: "CAAVisualization"
base: "CATBaseUnknown"
method_count: 6
source_file: "CAAVisualization.edu/CAAVisManagerImpl.m/LocalInterfaces/CAAEVisModelObject.h"
---

# CAAEVisModelObject

> Data extension of the CAAVisModelObject component, implementing the CAAIVisModelObject interface.

**基类**: CATBaseUnknown | **模块**: CAAVisualization | **方法数**: 6

## 依赖

- `CATBaseUnknown.h`
- `list.h`
- `CATMathPointf.h`

## 虚方法

### GetType

```cpp
virtual HRESULT GetType(char ** oType) ;
```

Get the type of object

| 参数 | 类型 |
|------|------|
| oType | `char **` |


### SetType

```cpp
virtual HRESULT SetType(const char * iType) ;
```

| 参数 | 类型 |
|------|------|
| iType | `const char *` |


## 公共方法

### AddChild

```cpp
HRESULT AddChild(CATBaseUnknown *iObject) ;
```

--------------------------------------------------------------- +++  Methods of the CAAIVisModelObject interface ++++++++++++++ --------------------------------------------------------------- Adds an object to the current model

| 参数 | 类型 |
|------|------|
| *iObject | `CATBaseUnknown` |


### RemChild

```cpp
HRESULT RemChild(CATBaseUnknown *iObject) ;
```

Remove an object to the current model

| 参数 | 类型 |
|------|------|
| *iObject | `CATBaseUnknown` |


### AddParent

```cpp
HRESULT AddParent(CATBaseUnknown *iObject) ;
```

Add a parent to the current object

| 参数 | 类型 |
|------|------|
| *iObject | `CATBaseUnknown` |


### RemParent

```cpp
HRESULT RemParent(CATBaseUnknown *iObject) ;
```

Remove a parent from the current object.

| 参数 | 类型 |
|------|------|
| *iObject | `CATBaseUnknown` |


---

**源文件**: `CAAVisualization.edu/CAAVisManagerImpl.m/LocalInterfaces/CAAEVisModelObject.h`
