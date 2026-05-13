---
title: "CAAESchAppCompCompat"
type: "LocalClass"
module: "CAASchPlatformModeler"
base: "CATBaseUnknown"
method_count: 3
source_file: "CAASchPlatformModeler.edu/CAASchAppBase.m/LocalInterfaces/CAAESchAppCompCompat.h"
---

# CAAESchAppCompCompat

**基类**: CATBaseUnknown | **模块**: CAASchPlatformModeler | **方法数**: 3

## 依赖

- `CATBaseUnknown.h`
- `CATBooleanDef.h`

## 虚方法

### AppIsTargetOKForRoute

```cpp
virtual HRESULT AppIsTargetOKForRoute(const char *iRouteCntrClassType, CATIUnknownList **oLOKCntrs, boolean *oBYes) ;
```

| 参数 | 类型 |
|------|------|
| *iRouteCntrClassType | `const char` |
| **oLOKCntrs | `CATIUnknownList` |
| *oBYes | `boolean` |


### AppIsTargetOKForPlace

```cpp
virtual HRESULT AppIsTargetOKForPlace(CATIUnknownList *iLCompSourceCntrs, CATIUnknownList **oLTargetCntrs, boolean *oBYes) ;
```

| 参数 | 类型 |
|------|------|
| *iLCompSourceCntrs | `CATIUnknownList` |
| **oLTargetCntrs | `CATIUnknownList` |
| *oBYes | `boolean` |


### AppIsTargetOKForInsert

```cpp
virtual HRESULT AppIsTargetOKForInsert(CATIUnknownList *iLCompSourceCntrs, CATIUnknownList **oLSourceCntrs, boolean *oBYes) ;
```

| 参数 | 类型 |
|------|------|
| *iLCompSourceCntrs | `CATIUnknownList` |
| **oLSourceCntrs | `CATIUnknownList` |
| *oBYes | `boolean` |


---

**源文件**: `CAASchPlatformModeler.edu/CAASchAppBase.m/LocalInterfaces/CAAESchAppCompCompat.h`
