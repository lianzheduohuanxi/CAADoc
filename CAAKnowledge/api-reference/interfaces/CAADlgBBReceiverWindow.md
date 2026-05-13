---
title: "CAADlgBBReceiverWindow"
type: "LocalClass"
module: "CAADialog"
base: "CATDlgDocument"
method_count: 1
source_file: "CAADialog.edu/CAADlgBBReceiver.m/LocalInterfaces/CAADlgBBReceiverWindow.h"
---

# CAADlgBBReceiverWindow

> Initialize the backbone bus: Declare a communication with the backbone bus Create a component CAADlgBBEditorMessageHandler which can handle message received from a sender application if no problem with the backbone commnunication : Retrieve the Message's Manager to set a callback when this manager sends a notification when the CAADlgBBEditorMessageHandler has handled a message. Create a CATDlgEditor with will contain the text sent by the sender application

**基类**: CATDlgDocument | **模块**: CAADialog | **方法数**: 1

## 依赖

- `CATDlgDocument.h`
- `CATEventSubscriber.h`

## 公共方法

### Build

```cpp
void Build() ;
```


---

**源文件**: `CAADialog.edu/CAADlgBBReceiver.m/LocalInterfaces/CAADlgBBReceiverWindow.h`
