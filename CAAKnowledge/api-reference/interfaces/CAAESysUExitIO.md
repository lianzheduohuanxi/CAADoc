---
title: "CAAESysUExitIO"
type: "LocalClass"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 3
source_file: "CAASystem.edu/CAASysUExitIO.m/LocalInterfaces/CAAESysUExitIO.h"
---

# CAAESysUExitIO

> Data extension of the CATUExitIO component and implementing the CATIUExitIO interface. The component CATUExitIO is defined in the System FW.

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 3

## 依赖

- `CATBaseUnknown.h`
- `CATIUExitIO.h`
- `CATBoolean.h`

## 虚方法

### OnOpen

```cpp
virtual HRESULT OnOpen(const CATUnicodeString *iFileName, CATAccessRight iMode, HRESULT *oGranted, CATFileSystemError *oError) ;
```

Enables to perform some operations on the file to open This method is called when a file is physically open

| 参数 | 类型 |
|------|------|
| *iFileName | `const CATUnicodeString` |
| iMode | `CATAccessRight` |
| *oGranted | `HRESULT` |
| *oError | `CATFileSystemError` |


### CreationMask

```cpp
virtual HRESULT CreationMask(const CATUnicodeString *iFileName, DWORD *oMode, CATFileSystemError *oError) ;
```

This method is not implemented

| 参数 | 类型 |
|------|------|
| *iFileName | `const CATUnicodeString` |
| *oMode | `DWORD` |
| *oError | `CATFileSystemError` |


### OnClose

```cpp
virtual HRESULT OnClose(const CATUnicodeString *iFileName, CATFileSystemError *oError) ;
```

Enables to perform some operations on the file to close This method is called when a file is physically close

| 参数 | 类型 |
|------|------|
| *iFileName | `const CATUnicodeString` |
| *oError | `CATFileSystemError` |


---

**源文件**: `CAASystem.edu/CAASysUExitIO.m/LocalInterfaces/CAAESysUExitIO.h`
