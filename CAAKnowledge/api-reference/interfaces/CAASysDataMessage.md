---
title: "CAASysDataMessage"
type: "interface"
module: "CAASystem"
base: "CATBBMessage"
method_count: 6
visibility: "local"
verified: true
---

# CAASysDataMessage

**基类**: CATBBMessage  
**模块**: CAASystem  
**可见性**: local  
**方法数**: 6

> - Implement CATIStreamMsg   (here in the implementation class )

## 方法列表

### StreamData
```cpp
HRESULT StreamData(void **oBuffer, uint32 *oLen);
```

### UnstreamData
```cpp
HRESULT UnstreamData(void  *iBuffer, uint32  iLen);
```

### FreeStreamData
```cpp
HRESULT FreeStreamData(void  *iBuffer, uint32  iLen);
```

### SetMessageSpecifications
```cpp
HRESULT SetMessageSpecifications();
```

### SetData
```cpp
HRESULT SetData(const float iRadiusOfCircle      , 
                              const int   iNbOfCircle   ,
                              char      * iColorOfCircle   ,
                              float     * iSagOfCircle);
```

### GetData
```cpp
HRESULT GetData(float   & oRadiusOfCircle     , 
                           int     & oNbOfCircle     ,
                           char   ** oColorOfCircle   ,
                           float  ** oSagOfCircle);
```

## 依赖

- `CATBBMessage.h`

