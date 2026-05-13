---
title: "CAAXMLMultiFileStream"
type: "LocalClass"
module: "CAAXMLParser"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAAXMLParser.edu/CAAXMLCustomStream.m/LocalInterfaces/CAAXMLMultiFileStream.h"
---

# CAAXMLMultiFileStream

**基类**: CATBaseUnknown | **模块**: CAAXMLParser | **方法数**: 1

## 依赖

- `CATListOfCATUnicodeString.h`
- `CATBaseUnknown.h`

## 虚方法

### Read

```cpp
virtual HRESULT Read(unsigned char* ioByteArray, unsigned int iByteArrayCapacity, unsigned int& oSizeRead) ;
```

Implement the CATIXMLInputStream interface.

| 参数 | 类型 |
|------|------|
| ioByteArray | `unsigned char*` |
| iByteArrayCapacity | `unsigned int` |
| oSizeRead | `unsigned int&` |


---

**源文件**: `CAAXMLParser.edu/CAAXMLCustomStream.m/LocalInterfaces/CAAXMLMultiFileStream.h`
