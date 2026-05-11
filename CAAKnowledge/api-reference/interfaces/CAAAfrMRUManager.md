---
title: "CAAAfrMRUManager"
type: "interface"
module: "CAAApplicationFrame"
base: "CATBaseUnknown"
method_count: 3
visibility: "local"
verified: true
---

# CAAAfrMRUManager

**基类**: CATBaseUnknown  
**模块**: CAAApplicationFrame  
**可见性**: local  
**方法数**: 3

> COPYRIGHT DASSAULT SYSTEMES 2000

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
- `CATCallbackManager.h`
- `CATIniCleanerSettingCtrl.h`

