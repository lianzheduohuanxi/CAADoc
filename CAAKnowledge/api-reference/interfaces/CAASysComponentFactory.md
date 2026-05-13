---
title: "CAASysComponentFactory"
type: "LocalClass"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAASystem.edu/CAASysComponentImpl.m/LocalInterfaces/CAASysComponentFactory.h"
---

# CAASysComponentFactory

> By implementing IClassFactory interface, this class allows you to create the component CAASysComponent. See the CAASysComponentCreateCLSID module which contains a sample to use this fonctionality.

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`

## 虚方法

### CreateInstance

```cpp
virtual HRESULT __stdcall CreateInstance(IUnknown * iUnkOuter, const IID &iIid, void ** oObject) ;
```

| 参数 | 类型 |
|------|------|
| iUnkOuter | `IUnknown *` |
| &iIid | `const IID` |
| oObject | `void **` |


### LockServer

```cpp
virtual HRESULT __stdcall LockServer(int iLock) ;
```

| 参数 | 类型 |
|------|------|
| iLock | `int` |


---

**源文件**: `CAASystem.edu/CAASysComponentImpl.m/LocalInterfaces/CAASysComponentFactory.h`
