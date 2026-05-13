---
title: "CAAEAfrTemporaryObjectColor"
type: "LocalClass"
module: "CAAApplicationFrame"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAApplicationFrame.edu/CAAAfrCustCommandHdrModel.m/LocalInterfaces/CAAEAfrTemporaryObjectColor.h"
---

# CAAEAfrTemporaryObjectColor

> It is mainly an implementation  of the CATIAfrCommandHeaderRep interface on the CAAAfrComboColorHeader command header. This interface enables you to define the dialog object associated with the starter which represents the command header into: a toolbar, the menu bar or a contextual menu. This class is also an implementation  of the CAAIAfrComboColorHeader interface on the same component. This interface "exports" the current r,g,b color composant.

**基类**: CATBaseUnknown | **模块**: CAAApplicationFrame | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`

## 虚方法

### GetCurrentColor

```cpp
virtual HRESULT GetCurrentColor(int & oRed, int & oGreen, int & oBlue) const ;
```

CAAIAfrTemporaryObjectColor

| 参数 | 类型 |
|------|------|
| oRed | `int &` |
| oGreen | `int &` |
| oBlue | `int &` |


### SetCurrentColor

```cpp
virtual HRESULT SetCurrentColor(int & oRed, int & oGreen, int & oBlue) ;
```

| 参数 | 类型 |
|------|------|
| oRed | `int &` |
| oGreen | `int &` |
| oBlue | `int &` |


---

**源文件**: `CAAApplicationFrame.edu/CAAAfrCustCommandHdrModel.m/LocalInterfaces/CAAEAfrTemporaryObjectColor.h`
