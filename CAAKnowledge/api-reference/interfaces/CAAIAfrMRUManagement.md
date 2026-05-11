---
title: "CAAIAfrMRUManagement"
type: "interface"
module: "CAAApplicationFrame"
base: "CATBaseUnknown"
method_count: 3
visibility: "public"
verified: true
---

# CAAIAfrMRUManagement

**基类**: CATBaseUnknown  
**模块**: CAAApplicationFrame  
**可见性**: public  
**方法数**: 3

> Local Framework

## 方法列表

### AddElement
```cpp
HRESULT AddElement(CATUnicodeString &iNewElement);
```

### GetElementList
```cpp
HRESULT GetElementList(CATListOfCATUnicodeString &ElementList) const;
```

### SelectElement
```cpp
HRESULT SelectElement(int iPosition);
```

## 依赖

- `CATBaseUnknown.h`
- `CATListOfCATUnicodeString.h`
- `CAAAfrCustCommandHdrModel.h`

