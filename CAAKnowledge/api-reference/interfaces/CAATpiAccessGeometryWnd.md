---
title: "CAATpiAccessGeometryWnd"
type: "LocalClass"
module: "CAATPSInterfaces"
base: "CATDlgDialog"
method_count: 2
source_file: "CAATPSInterfaces.edu/CAATpiAccessGeometry.m/LocalInterfaces/CAATpiAccessGeometryWnd.h"
---

# CAATpiAccessGeometryWnd

**基类**: CATDlgDialog | **模块**: CAATPSInterfaces | **方法数**: 2

## 依赖

- `CATDlgDialog.h`
- `CATBoolean.h`
- `CATListOfCATUnicodeString.h`

## 公共方法

### SetCompositionList

```cpp
HRESULT SetCompositionList(CATListValCATUnicodeString &iCompositionList) ;
```

| 参数 | 类型 |
|------|------|
| &iCompositionList | `CATListValCATUnicodeString` |


### GetRequiredDisplay

```cpp
HRESULT GetRequiredDisplay(CATBoolean * oDisplay3DGrid, CATBoolean * oDisplayTTRSRep) ;
```

| 参数 | 类型 |
|------|------|
| oDisplay3DGrid | `CATBoolean *` |
| oDisplayTTRSRep | `CATBoolean *` |


---

**源文件**: `CAATPSInterfaces.edu/CAATpiAccessGeometry.m/LocalInterfaces/CAATpiAccessGeometryWnd.h`
