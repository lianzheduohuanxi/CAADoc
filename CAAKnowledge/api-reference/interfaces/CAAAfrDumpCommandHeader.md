---
title: "CAAAfrDumpCommandHeader"
type: "LocalClass"
module: "CAAApplicationFrame"
base: "CATCommandHeader"
method_count: 0
source_file: "CAAApplicationFrame.edu/CAAAfrGeometryWshop.m/LocalInterfaces/CAAAfrDumpCommandHeader.h"
---

# CAAAfrDumpCommandHeader

> Command header of the Dump command. It is customized in order to manage the command availability: the command is available when the document contains objects other than the UIActive object. The header subscribes to the notification sent by the document container to be informed when objects are created. Illustrates: customizing a command header subscribing to notifications Usually, you use the macro #include <CATCommandHeader.h> MacDeclareHeader(MyHeaderClassName) ; to define a command header. But it cannot be customized. In order to customize a command header, you must create a new class derived from CATCommandHeader. Inheritance: CATCommandHeader (ApplicationFrame Framework) CATEventSubscriber  (System Framework) CATBaseUnknown (System Framework) Main Method: constructor Subscribes to the container's notification AnalyseFilledCB AnalyseEmptyCB callbacks. Change the command availability.

**基类**: CATCommandHeader | **模块**: CAAApplicationFrame | **方法数**: 0

## 依赖

- `CATCommandHeader.h`

---

**源文件**: `CAAApplicationFrame.edu/CAAAfrGeometryWshop.m/LocalInterfaces/CAAAfrDumpCommandHeader.h`
