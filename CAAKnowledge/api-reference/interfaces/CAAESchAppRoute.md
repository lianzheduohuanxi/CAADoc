---
title: "CAAESchAppRoute"
type: "LocalClass"
module: "CAASchPlatformModeler"
base: "CATBaseUnknown"
method_count: 8
source_file: "CAASchPlatformModeler.edu/CAASchAppBase.m/LocalInterfaces/CAAESchAppRoute.h"
---

# CAAESchAppRoute

**基类**: CATBaseUnknown | **模块**: CAASchPlatformModeler | **方法数**: 8

## 依赖

- `CATBaseUnknown.h`
- `CATBooleanDef.h`

## 虚方法

### AppCreateLocalReference

```cpp
virtual HRESULT AppCreateLocalReference(CATDocument *iDocumentToPutCopyIn, CATISchAppRoute **oSchAppRoute) ;
```

| 参数 | 类型 |
|------|------|
| *iDocumentToPutCopyIn | `CATDocument` |
| **oSchAppRoute | `CATISchAppRoute` |


## 公共方法

### AppBreak

```cpp
HRESULT AppBreak(IUnknown **oNewAppRoute) ;
```

| 参数 | 类型 |
|------|------|
| **oNewAppRoute | `IUnknown` |


### AppPostBreakProcess

```cpp
HRESULT AppPostBreakProcess(CATISchRoute *iOldAppRoute, CATISchRoute *iNewAppRoute) ;
```

| 参数 | 类型 |
|------|------|
| *iOldAppRoute | `CATISchRoute` |
| *iNewAppRoute | `CATISchRoute` |


### AppPostConcatenateProcess

```cpp
HRESULT AppPostConcatenateProcess(CATISchRoute *iSchRoute2) ;
```

| 参数 | 类型 |
|------|------|
| *iSchRoute2 | `CATISchRoute` |


### AppOKToModifyPoints

```cpp
HRESULT AppOKToModifyPoints(boolean *oBYes) ;
```

| 参数 | 类型 |
|------|------|
| *oBYes | `boolean` |


### AppOKToBreak

```cpp
HRESULT AppOKToBreak(boolean *oBYes) ;
```

| 参数 | 类型 |
|------|------|
| *oBYes | `boolean` |


### AppOKToConcatenate

```cpp
HRESULT AppOKToConcatenate(boolean *oBYes) ;
```

| 参数 | 类型 |
|------|------|
| *oBYes | `boolean` |


### AppOKToBranch

```cpp
HRESULT AppOKToBranch(const char* iBranchClassType, boolean *oBYes) ;
```

| 参数 | 类型 |
|------|------|
| iBranchClassType | `const char*` |
| *oBYes | `boolean` |


---

**源文件**: `CAASchPlatformModeler.edu/CAASchAppBase.m/LocalInterfaces/CAAESchAppRoute.h`
