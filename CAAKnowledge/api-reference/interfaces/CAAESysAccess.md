---
title: "CAAESysAccess"
type: "LocalClass"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysAccess.h"
---

# CAAESysAccess

> Data extension implementing the CAAISysAccess interface which associates a container with its objects in the CAAGeometry document. Every container's object implements this interface to know its container. Inheritance: CATBaseUnknown (System Framework) Main Method: SetContainer: Sets the container GetContainer: Retrieves the container

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`

## 虚方法

### SetContainer

```cpp
virtual HRESULT SetContainer(CATBaseUnknown * iContainer) ;
```

Sets the container

| 参数 | 类型 |
|------|------|
| iContainer | `CATBaseUnknown *` |


### GetContainer

```cpp
virtual HRESULT GetContainer(CATBaseUnknown ** oContainer) ;
```

Retrieves the container

| 参数 | 类型 |
|------|------|
| oContainer | `CATBaseUnknown **` |


---

**源文件**: `CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysAccess.h`
