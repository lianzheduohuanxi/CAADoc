---
title: "CAAESysName"
type: "LocalClass"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysName.h"
---

# CAAESysName

> Data extension implementing the CAAISysName interface

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CATUnicodeString.h`

## 虚方法

### SetName

```cpp
virtual HRESULT SetName(const CATUnicodeString & iName) ;
```

Sets the name

| 参数 | 类型 |
|------|------|
| iName | `const CATUnicodeString &` |


### GetName

```cpp
virtual HRESULT GetName(CATUnicodeString & ioName) ;
```

Retrieves the name

| 参数 | 类型 |
|------|------|
| ioName | `CATUnicodeString &` |


---

**源文件**: `CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysName.h`
