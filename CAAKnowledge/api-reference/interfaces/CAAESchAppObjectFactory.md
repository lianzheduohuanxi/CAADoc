---
title: "CAAESchAppObjectFactory"
type: "LocalClass"
module: "CAASchPlatformModeler"
base: "CATEASchAppObjectFactory2"
method_count: 2
source_file: "CAASchPlatformModeler.edu/CAASchAppBase.m/LocalInterfaces/CAAESchAppObjectFactory.h"
---

# CAAESchAppObjectFactory

**基类**: CATEASchAppObjectFactory2 | **模块**: CAASchPlatformModeler | **方法数**: 2

## 依赖

- `CATEASchAppObjectFactory2.h`

## 虚方法

### AppCreateCompRef

```cpp
virtual HRESULT AppCreateCompRef(const char *iAppCompClassType, const CATDocument *iDoc, IUnknown **oAppComp) ;
```

| 参数 | 类型 |
|------|------|
| *iAppCompClassType | `const char` |
| *iDoc | `const CATDocument` |
| **oAppComp | `IUnknown` |


### AppCreateRoute2

```cpp
virtual HRESULT AppCreateRoute2(const char *iAppRouteClassType, const CATDocument *iDoc, const CATUnicodeString *iLogLineID, IUnknown **oAppRoute) ;
```

| 参数 | 类型 |
|------|------|
| *iAppRouteClassType | `const char` |
| *iDoc | `const CATDocument` |
| *iLogLineID | `const CATUnicodeString` |
| **oAppRoute | `IUnknown` |


---

**源文件**: `CAASchPlatformModeler.edu/CAASchAppBase.m/LocalInterfaces/CAAESchAppObjectFactory.h`
