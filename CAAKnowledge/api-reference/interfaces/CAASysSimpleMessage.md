---
title: "CAASysSimpleMessage"
type: "interface"
module: "CAASystem"
base: "CATBBMessage"
method_count: 4
visibility: "local"
verified: true
---

# CAASysSimpleMessage

**基类**: CATBBMessage  
**模块**: CAASystem  
**可见性**: local  
**方法数**: 4

> - Implement CATIStreamMsg   (here in the implementation class )

## 方法列表

### UnstreamData
```cpp
HRESULT UnstreamData(void  *iBuffer, uint32  iLen);
```

### StreamData
```cpp
HRESULT StreamData(void **oBuffer, uint32 *oLen);
```

### FreeStreamData
```cpp
HRESULT FreeStreamData(void  *iBuffer, uint32  iLen);
```

### SetMessageSpecifications
```cpp
HRESULT SetMessageSpecifications();
```

## 依赖

- `CATBBMessage.h`

