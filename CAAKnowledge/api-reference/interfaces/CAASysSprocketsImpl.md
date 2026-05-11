---
title: "CAASysSprocketsImpl"
type: "interface"
module: "CAASystem"
base: "CATBaseCollection"
method_count: 6
visibility: "local"
verified: true
---

# CAASysSprocketsImpl

**基类**: CATBaseCollection  
**模块**: CAASystem  
**可见性**: local  
**方法数**: 6

## 方法列表

### get_Name
```cpp
HRESULT __stdcall get_Name(CATBSTR & oNameBSTR);
```

### get__NewEnum
```cpp
HRESULT __stdcall get__NewEnum(IUnknown *& oEnumerator);
```

### get_Count
```cpp
HRESULT __stdcall get_Count(CATLONG & oCount);
```

### Item
```cpp
HRESULT __stdcall Item(const CATVariant & iIndex, 
      CAAIASysSprocket *& oSprocket);
```

### AddAll
```cpp
HRESULT __stdcall AddAll(const CATSafeArrayVariant & iSprocketArray);
```

### ToArray
```cpp
HRESULT __stdcall ToArray(CATSafeArrayVariant & ioArray);
```

## 依赖

- `CATBaseCollection.h`
- `CATVariant.h`
- `CATSafeArray.h`
- `CATListOfCAAIASysSprocket.h`

