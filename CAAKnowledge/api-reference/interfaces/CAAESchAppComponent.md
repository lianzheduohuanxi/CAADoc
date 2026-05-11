---
title: "CAAESchAppComponent"
type: "interface"
module: "CAASchPlatformModeler"
base: "CATBaseUnknown"
method_count: 22
visibility: "local"
verified: true
---

# CAAESchAppComponent

**基类**: CATBaseUnknown  
**模块**: CAASchPlatformModeler  
**可见性**: local  
**方法数**: 22

## 方法列表

### AppCreateComponentInst
```cpp
HRESULT AppCreateComponentInst(IUnknown **oNewAppCompInst);
```

### AppCreateLocalReference
```cpp
HRESULT AppCreateLocalReference(CATDocument *iDocToCopyTo,
    IUnknown **oNewAppCompRef);
```

### AppListGRRNames
```cpp
HRESULT AppListGRRNames(CATICStringList **oLGRRNames);
```

### AppGetDefaultGRRName
```cpp
HRESULT AppGetDefaultGRRName(char **oGRRDefaultName);
```

### AppListGRRNames2
```cpp
HRESULT AppListGRRNames2(CATListOfCATUnicodeString &oLGRRNames);
```

### AppGetDefaultGRRName2
```cpp
HRESULT AppGetDefaultGRRName2(CATUnicodeString &oGRRDefaultName);
```

### AppPostPlaceProcess
```cpp
HRESULT AppPostPlaceProcess(CATISchComponent *iNewCompInst, 
    CATISchAppConnectable *iCntblConnectedTo);
```

### AppPostSlideProcess
```cpp
HRESULT AppPostSlideProcess(void);
```

### AppPostFlipConnectedProcess
```cpp
HRESULT AppPostFlipConnectedProcess(void);
```

### AppPostFlipOnLineProcess
```cpp
HRESULT AppPostFlipOnLineProcess(void);
```

### AppPostFlipHorizontalProcess
```cpp
HRESULT AppPostFlipHorizontalProcess(void);
```

### AppPostFlipVerticalProcess
```cpp
HRESULT AppPostFlipVerticalProcess(void);
```

### AppPostUninsertProcess
```cpp
HRESULT AppPostUninsertProcess(CATISchRoute *iOldAppRoute1,
    CATISchRoute *iOldAppRoute2, CATISchRoute *iNewAppRoute);
```

### AppPostSwitchGraphicProcess
```cpp
HRESULT AppPostSwitchGraphicProcess(CATISchGRR *iGRR);
```

### AppOKToPlaceInSpace
```cpp
HRESULT AppOKToPlaceInSpace(boolean *oBYes);
```

### AppOKToSlide
```cpp
HRESULT AppOKToSlide(boolean *oBYes);
```

### AppOKToFlipConnected
```cpp
HRESULT AppOKToFlipConnected(boolean *oBYes);
```

### AppOKToFlipOnLine
```cpp
HRESULT AppOKToFlipOnLine(boolean *oBYes);
```

### AppOKToFlipVertical
```cpp
HRESULT AppOKToFlipVertical(boolean *oBYes);
```

### AppOKToFlipHorizontal
```cpp
HRESULT AppOKToFlipHorizontal(boolean *oBYes);
```

### AppOKToUninsert
```cpp
HRESULT AppOKToUninsert(boolean *oBYes);
```

### AppOKToScale
```cpp
HRESULT AppOKToScale(boolean *oBYes);
```

## 依赖

- `CATBaseUnknown.h`
- `CATBooleanDef.h`
- `CATUnicodeString.h`
- `CATListOfCATUnicodeString.h`

