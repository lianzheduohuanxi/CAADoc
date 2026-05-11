---
title: "CAAIAfrTemporaryObjectColor"
type: "interface"
module: "CAAApplicationFrame"
base: "CATBaseUnknown"
method_count: 2
visibility: "public"
verified: true
---

# CAAIAfrTemporaryObjectColor

**基类**: CATBaseUnknown  
**模块**: CAAApplicationFrame  
**可见性**: public  
**方法数**: 2

> Local Framework

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
- `CAAAfrCustCommandHdrModel.h`

