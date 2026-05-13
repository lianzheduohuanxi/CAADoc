---
title: "CAAESchAppComponent"
type: "LocalClass"
module: "CAASchPlatformModeler"
base: "CATBaseUnknown"
method_count: 22
source_file: "CAASchPlatformModeler.edu/CAASchAppBase.m/LocalInterfaces/CAAESchAppComponent.h"
---

# CAAESchAppComponent

**基类**: CATBaseUnknown | **模块**: CAASchPlatformModeler | **方法数**: 22

## 依赖

- `CATBaseUnknown.h`
- `CATBooleanDef.h`
- `CATUnicodeString.h`
- `CATListOfCATUnicodeString.h`

## 虚方法

### AppCreateComponentInst

```cpp
virtual HRESULT AppCreateComponentInst(IUnknown **oNewAppCompInst) ;
```

| 参数 | 类型 |
|------|------|
| **oNewAppCompInst | `IUnknown` |


### AppCreateLocalReference

```cpp
virtual HRESULT AppCreateLocalReference(CATDocument *iDocToCopyTo, IUnknown **oNewAppCompRef) ;
```

| 参数 | 类型 |
|------|------|
| *iDocToCopyTo | `CATDocument` |
| **oNewAppCompRef | `IUnknown` |


### AppListGRRNames

```cpp
virtual HRESULT AppListGRRNames(CATICStringList **oLGRRNames) ;
```

| 参数 | 类型 |
|------|------|
| **oLGRRNames | `CATICStringList` |


### AppGetDefaultGRRName

```cpp
virtual HRESULT AppGetDefaultGRRName(char **oGRRDefaultName) ;
```

| 参数 | 类型 |
|------|------|
| **oGRRDefaultName | `char` |


### AppListGRRNames2

```cpp
virtual HRESULT AppListGRRNames2(CATListOfCATUnicodeString &oLGRRNames) ;
```

| 参数 | 类型 |
|------|------|
| &oLGRRNames | `CATListOfCATUnicodeString` |


### AppGetDefaultGRRName2

```cpp
virtual HRESULT AppGetDefaultGRRName2(CATUnicodeString &oGRRDefaultName) ;
```

| 参数 | 类型 |
|------|------|
| &oGRRDefaultName | `CATUnicodeString` |


### AppPostPlaceProcess

```cpp
virtual HRESULT AppPostPlaceProcess(CATISchComponent *iNewCompInst, CATISchAppConnectable *iCntblConnectedTo) ;
```

| 参数 | 类型 |
|------|------|
| *iNewCompInst | `CATISchComponent` |
| *iCntblConnectedTo | `CATISchAppConnectable` |


### AppPostSlideProcess

```cpp
virtual HRESULT AppPostSlideProcess() ;
```


### AppPostFlipConnectedProcess

```cpp
virtual HRESULT AppPostFlipConnectedProcess() ;
```


### AppPostFlipOnLineProcess

```cpp
virtual HRESULT AppPostFlipOnLineProcess() ;
```


### AppPostFlipHorizontalProcess

```cpp
virtual HRESULT AppPostFlipHorizontalProcess() ;
```


### AppPostFlipVerticalProcess

```cpp
virtual HRESULT AppPostFlipVerticalProcess() ;
```


### AppPostUninsertProcess

```cpp
virtual HRESULT AppPostUninsertProcess(CATISchRoute *iOldAppRoute1, CATISchRoute *iOldAppRoute2, CATISchRoute *iNewAppRoute) ;
```

| 参数 | 类型 |
|------|------|
| *iOldAppRoute1 | `CATISchRoute` |
| *iOldAppRoute2 | `CATISchRoute` |
| *iNewAppRoute | `CATISchRoute` |


### AppPostSwitchGraphicProcess

```cpp
virtual HRESULT AppPostSwitchGraphicProcess(CATISchGRR *iGRR) ;
```

| 参数 | 类型 |
|------|------|
| *iGRR | `CATISchGRR` |


### AppOKToPlaceInSpace

```cpp
virtual HRESULT AppOKToPlaceInSpace(boolean *oBYes) ;
```

| 参数 | 类型 |
|------|------|
| *oBYes | `boolean` |


### AppOKToSlide

```cpp
virtual HRESULT AppOKToSlide(boolean *oBYes) ;
```

| 参数 | 类型 |
|------|------|
| *oBYes | `boolean` |


### AppOKToFlipConnected

```cpp
virtual HRESULT AppOKToFlipConnected(boolean *oBYes) ;
```

| 参数 | 类型 |
|------|------|
| *oBYes | `boolean` |


### AppOKToFlipOnLine

```cpp
virtual HRESULT AppOKToFlipOnLine(boolean *oBYes) ;
```

| 参数 | 类型 |
|------|------|
| *oBYes | `boolean` |


### AppOKToFlipVertical

```cpp
virtual HRESULT AppOKToFlipVertical(boolean *oBYes) ;
```

| 参数 | 类型 |
|------|------|
| *oBYes | `boolean` |


### AppOKToFlipHorizontal

```cpp
virtual HRESULT AppOKToFlipHorizontal(boolean *oBYes) ;
```

| 参数 | 类型 |
|------|------|
| *oBYes | `boolean` |


### AppOKToUninsert

```cpp
virtual HRESULT AppOKToUninsert(boolean *oBYes) ;
```

| 参数 | 类型 |
|------|------|
| *oBYes | `boolean` |


### AppOKToScale

```cpp
virtual HRESULT AppOKToScale(boolean *oBYes) ;
```

| 参数 | 类型 |
|------|------|
| *oBYes | `boolean` |


---

**源文件**: `CAASchPlatformModeler.edu/CAASchAppBase.m/LocalInterfaces/CAAESchAppComponent.h`
