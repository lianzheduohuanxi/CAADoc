---
title: "CAAIAfrMRUManagement"
type: "interface"
module: "CAAApplicationFrame"
base: "CATBaseUnknown"
method_count: 3
verified: true
---

# CAAIAfrMRUManagement

**基类**: CATBaseUnknown  
**模块**: CAAApplicationFrame  
**方法数**: 3

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

