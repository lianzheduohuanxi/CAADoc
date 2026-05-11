---
title: "CAAXMLMultiFileStream"
type: "interface"
module: "CAAXMLParser"
base: "CATBaseUnknown"
method_count: 1
visibility: "local"
verified: true
---

# CAAXMLMultiFileStream

**基类**: CATBaseUnknown  
**模块**: CAAXMLParser  
**可见性**: local  
**方法数**: 1

> System framework

## 方法列表

### Read
```cpp
HRESULT Read(unsigned char* ioByteArray,
			unsigned int iByteArrayCapacity,
			unsigned int& oSizeRead);
```

## 依赖

- `CATListOfCATUnicodeString.h`
- `CATBaseUnknown.h`

