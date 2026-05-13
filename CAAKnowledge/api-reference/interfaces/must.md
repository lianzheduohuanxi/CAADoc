---
title: "must"
type: "LocalClass"
module: "CAASystem"
base: "CATBBMessage"
method_count: 4
source_file: "CAASystem.edu/CAASysBBMessage.m/LocalInterfaces/CAASysSimpleMessage.h"
---

# must

> Message class for backbone. This Message is without data A backbone message is a message which may be sent to another application through the backbone bus All backbone messages class must   : Declare that it is a component (CATDeclareClass/CATImplementClass) wich OM derives from the CATBBMessage component C++ Derive from CATBBMessage Implement CATIStreamMsg   (here in the implementation class ) > They must follow correct rules to stream their data Implement by Code Extension CATICreateInstance System Framework

**基类**: CATBBMessage | **模块**: CAASystem | **方法数**: 4

## 依赖

- `CATBBMessage.h`

## 虚方法

### UnstreamData

```cpp
virtual HRESULT UnstreamData(void *iBuffer, uint32 iLen) ;
```

CATIStreamMsg Interface

| 参数 | 类型 |
|------|------|
| *iBuffer | `void` |
| iLen | `uint32` |


### StreamData

```cpp
virtual HRESULT StreamData(void **oBuffer, uint32 *oLen) ;
```

| 参数 | 类型 |
|------|------|
| **oBuffer | `void` |
| *oLen | `uint32` |


### FreeStreamData

```cpp
virtual HRESULT FreeStreamData(void *iBuffer, uint32 iLen) ;
```

| 参数 | 类型 |
|------|------|
| *iBuffer | `void` |
| iLen | `uint32` |


### SetMessageSpecifications

```cpp
virtual HRESULT SetMessageSpecifications() ;
```


---

**源文件**: `CAASystem.edu/CAASysBBMessage.m/LocalInterfaces/CAASysSimpleMessage.h`
