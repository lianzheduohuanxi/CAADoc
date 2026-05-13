---
title: "CAAAfrComboRep"
type: "LocalClass"
module: "CAAApplicationFrame"
base: "CATAfrCommandHeaderRep"
method_count: 1
source_file: "CAAApplicationFrame.edu/CAAAfrCustomizedCommandHeader.m/LocalInterfaces/CAAAfrComboRep.h"
---

# CAAAfrComboRep

> This class is the representation ( a CATCommand ) of the CAAAfrComboColorHeader in the tool bar. The current color is kept by the UIActive object of the CAAGeometry document.

**基类**: CATAfrCommandHeaderRep | **模块**: CAAApplicationFrame | **方法数**: 1

## 依赖

- `CATAfrCommandHeaderRep.h`

## 公共方法

### Build

```cpp
HRESULT Build() ;
```

Build ----- This method  creates the CATDlgCombo instance and calls SetCurrentColor to set the current selected color


---

**源文件**: `CAAApplicationFrame.edu/CAAAfrCustomizedCommandHeader.m/LocalInterfaces/CAAAfrComboRep.h`
