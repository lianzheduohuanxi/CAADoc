---
title: "CAAMfgTPEUserCommandHeaders"
type: "interface"
module: "CAAToolPathEditorItf"
base: "CATBaseUnknown"
method_count: 2
visibility: "protected"
verified: true
---

# CAAMfgTPEUserCommandHeaders

**基类**: CATBaseUnknown  
**模块**: CAAToolPathEditorItf  
**可见性**: protected  
**方法数**: 2

## 方法列表

### GetHeaders
```cpp
HRESULT GetHeaders(CATListValCATString &ioHeadersList);
```

### IsHeadersAvailable
```cpp
HRESULT IsHeadersAvailable(CATListValCATString& ioHeadersList , CATCSO* iCSO);
```

## 依赖

- `CAAMfgTPEUserCommandHeadersEnv.h`
- `CATBaseUnknown.h`
- `CATBoolean.h`
- `CATBooleanDef.h`
- `CATListOfCATString.h`

