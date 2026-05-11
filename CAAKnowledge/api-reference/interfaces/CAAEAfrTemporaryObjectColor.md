---
title: "CAAEAfrTemporaryObjectColor"
type: "interface"
module: "CAAApplicationFrame"
base: "CATBaseUnknown"
method_count: 2
visibility: "local"
verified: true
---

# CAAEAfrTemporaryObjectColor

**基类**: CATBaseUnknown  
**模块**: CAAApplicationFrame  
**可见性**: local  
**方法数**: 2

> header into: a toolbar, the menu bar or a contextual menu.

## 方法列表

### GetCurrentColor
```cpp
HRESULT GetCurrentColor(int & oRed, int & oGreen, int & oBlue) const;
```

### SetCurrentColor
```cpp
HRESULT SetCurrentColor(int & oRed, int & oGreen, int & oBlue);
```

## 依赖

- `CATBaseUnknown.h`

