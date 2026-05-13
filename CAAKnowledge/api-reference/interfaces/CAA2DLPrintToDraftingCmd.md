---
title: "CAA2DLPrintToDraftingCmd"
type: "LocalClass"
module: "CAADrafting2DLInterfaces"
base: "CATCommand"
method_count: 1
source_file: "CAADrafting2DLInterfaces.edu/CAA2DLPrintToDrafting.m/LocalInterfaces/CAA2DLPrintToDraftingCmd.h"
---

# CAA2DLPrintToDraftingCmd

> Interactive command This command launches a batch to create a Drawing from 2DLayout and print the active sheet of the drawing

**基类**: CATCommand | **模块**: CAADrafting2DLInterfaces | **方法数**: 1

## 依赖

- `CATCommand.h`

## 虚方法

### Activate

```cpp
virtual CATStatusChangeRC Activate(CATCommand* FromClient, CATNotification* EvtDat) ;
```

| 参数 | 类型 |
|------|------|
| FromClient | `CATCommand*` |
| EvtDat | `CATNotification*` |


---

**源文件**: `CAADrafting2DLInterfaces.edu/CAA2DLPrintToDrafting.m/LocalInterfaces/CAA2DLPrintToDraftingCmd.h`
