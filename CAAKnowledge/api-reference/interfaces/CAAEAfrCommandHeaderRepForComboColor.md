---
title: "CAAEAfrCommandHeaderRepForComboColor"
type: "LocalClass"
module: "CAAApplicationFrame"
base: "CATBaseUnknown"
method_count: 3
source_file: "CAAApplicationFrame.edu/CAAAfrCustomizedCommandHeader.m/LocalInterfaces/CAAEAfrCommandHeaderRepForComboColor.h"
---

# CAAEAfrCommandHeaderRepForComboColor

> It is an implementation  of the CATIAfrCommandHeaderRep interface on the CAAAfrComboColorHeader command header. This interface enables you to define the dialog object associated with the starter which represents the command header into a toolbar.

**基类**: CATBaseUnknown | **模块**: CAAApplicationFrame | **方法数**: 3

## 依赖

- `CATBaseUnknown.h`

## 虚方法

### CreateToolbarRep

```cpp
virtual HRESULT CreateToolbarRep(const CATDialog * iParent, CATAfrCommandHeaderRep ** oHdrRep) ;
```

CATIAfrCommandHeaderRep

| 参数 | 类型 |
|------|------|
| iParent | `const CATDialog *` |
| oHdrRep | `CATAfrCommandHeaderRep **` |


### CreateMenuRep

```cpp
virtual HRESULT CreateMenuRep(const CATDialog * iParent, CATAfrCommandHeaderRep ** oHdrRep) ;
```

| 参数 | 类型 |
|------|------|
| iParent | `const CATDialog *` |
| oHdrRep | `CATAfrCommandHeaderRep **` |


### CreateCtxMenuRep

```cpp
virtual HRESULT CreateCtxMenuRep(const CATDialog * iParent, CATAfrCommandHeaderRep ** oHdrRep) ;
```

| 参数 | 类型 |
|------|------|
| iParent | `const CATDialog *` |
| oHdrRep | `CATAfrCommandHeaderRep **` |


---

**源文件**: `CAAApplicationFrame.edu/CAAAfrCustomizedCommandHeader.m/LocalInterfaces/CAAEAfrCommandHeaderRepForComboColor.h`
