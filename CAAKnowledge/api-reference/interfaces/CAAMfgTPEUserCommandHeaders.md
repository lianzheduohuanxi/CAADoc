---
title: "CAAMfgTPEUserCommandHeaders"
type: "ProtectedInterface"
module: "CAAToolPathEditorItf"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAToolPathEditorItf.edu/ProtectedInterfaces/CAAMfgTPEUserCommandHeaders.h"
---

# CAAMfgTPEUserCommandHeaders

**基类**: CATBaseUnknown | **模块**: CAAToolPathEditorItf | **方法数**: 2

## 依赖

- `CAAMfgTPEUserCommandHeadersEnv.h`
- `CATBaseUnknown.h`
- `CATBoolean.h`
- `CATBooleanDef.h`
- `CATListOfCATString.h`

## 虚方法

### GetHeaders

```cpp
virtual HRESULT GetHeaders(CATListValCATString &ioHeadersList) ;
```

| 参数 | 类型 |
|------|------|
| &ioHeadersList | `CATListValCATString` |


### IsHeadersAvailable

```cpp
virtual HRESULT IsHeadersAvailable(CATListValCATString& ioHeadersList, CATCSO* iCSO) ;
```

| 参数 | 类型 |
|------|------|
| ioHeadersList | `CATListValCATString&` |
| iCSO | `CATCSO*` |


---

**源文件**: `CAAToolPathEditorItf.edu/ProtectedInterfaces/CAAMfgTPEUserCommandHeaders.h`
