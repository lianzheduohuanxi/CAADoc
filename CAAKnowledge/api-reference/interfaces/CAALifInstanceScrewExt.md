---
title: "CAALifInstanceScrewExt"
type: "interface"
module: "CAALiteralFeatures"
base: "CATKweInstanceAdapter"
method_count: 3
visibility: "local"
verified: true
---

# CAALifInstanceScrewExt

**基类**: CATKweInstanceAdapter  
**模块**: CAALiteralFeatures  
**可见性**: local  
**方法数**: 3

## 方法列表

### TypeInternal
```cpp
CATIType* TypeInternal() const;
```

### SetValueInternal
```cpp
HRESULT SetValueInternal(const CATUnicodeString& iKey, const CATIValue_var& iValue);
```

### GetValueInternal
```cpp
CATIValue* GetValueInternal(const CATUnicodeString& iKey);
```

## 依赖

- `CATKweInstanceAdapter.h`

