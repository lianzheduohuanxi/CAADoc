---
title: "CAAEOmmFactory"
type: "LocalClass"
module: "CAAOLE4MecMod"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAAOLE4MecMod.edu/CAAOmmImpl.m/LocalInterfaces/CAAEOmmFactory.h"
---

# CAAEOmmFactory

**基类**: CATBaseUnknown | **模块**: CAAOLE4MecMod | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`
- `CATBSTR.h`
- `CATIAApplication.h`
- `CAAIAOmmVerticalLine.h`

## 公共方法

### get_Application

```cpp
HRESULT get_Application(CATIAApplication *& opiApplicationOnCATIA) ;
```

CATIABase interface methods Returns CATIA as an application

| 参数 | 类型 |
|------|------|
| opiApplicationOnCATIA | `CATIAApplication *&` |


### get_Name

```cpp
HRESULT get_Name(CATBSTR & oName) ;
```

Returns the entity name

| 参数 | 类型 |
|------|------|
| oName | `CATBSTR &` |


### put_Name

```cpp
HRESULT put_Name(const CATBSTR & iName) ;
```

Sets the entity name

| 参数 | 类型 |
|------|------|
| iName | `const CATBSTR &` |


### GetItem

```cpp
HRESULT GetItem(const CATBSTR & iName, CATBaseDispatch *& opiBaseOnChildObject) ;
```

Gives an child exposed object when this object is considered as a container

| 参数 | 类型 |
|------|------|
| iName | `const CATBSTR &` |
| opiBaseOnChildObject | `CATBaseDispatch *&` |


---

**源文件**: `CAAOLE4MecMod.edu/CAAOmmImpl.m/LocalInterfaces/CAAEOmmFactory.h`
