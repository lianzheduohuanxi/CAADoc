---
title: "CAADlgBBEditorMessage"
type: "interface"
module: "CAADialog"
base: "CATBBMessage"
method_count: 6
visibility: "local"
verified: true
---

# CAADlgBBEditorMessage

**基类**: CATBBMessage  
**模块**: CAADialog  
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

### GetData
```cpp
HRESULT GetData(char ** oText);
```

### SetData
```cpp
HRESULT SetData(const char *iText);
```

## 依赖

- `CATBBMessage.h`

