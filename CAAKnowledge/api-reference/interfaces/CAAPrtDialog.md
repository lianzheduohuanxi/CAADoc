---
title: "CAAPrtDialog"
type: "LocalClass"
module: "CAAPrint"
base: "CATDlgDocument"
method_count: 3
source_file: "CAAPrint.edu/CAAPrtApplication.m/LocalInterfaces/CAAPrtDialog.h"
---

# CAAPrtDialog

> Main window class. The window is composed of a menu bar and a 2D viewer. The menu bar contains only two menus: File with the items: Open... Print... Capture... Album... Printer Manager... Exit Printable objects with the items: Display a test image Print a test image Print a label The class creates the viewer and the menu bar in an Init method and subscribes to the menu items. File menu: The callbacks associated with the Print, Capture, Album, Printer Manager items only instantiate a dialog command provided by the Print framework. Only reading the image file is managed by the class itself, in the DisplayImage method. Printable objects mneu: Most of the code dealing with this menu is in another module: CAPrtPrintableObjects.m. Inheritance: CATDlgDocument (Dialog Framework) CATDlgWindow (Dialog Framework) CATDialog (Dialog Framework) CATCommand (System Framework) CATEventSubscriber (System Framework) CATBaseUnknown (System Framework) Main Method: Init: creates of the window contents DisplayImage: reads the input TIFF file and displays the image

**基类**: CATDlgDocument | **模块**: CAAPrint | **方法数**: 3

## 依赖

- `CATDlgDocument.h`

## 公共方法

### Clean

```cpp
void Clean() ;
```


### DisplayImage

```cpp
void DisplayImage(const char *iPath) ;
```

| 参数 | 类型 |
|------|------|
| *iPath | `const char` |


### Init

```cpp
void Init() ;
```


---

**源文件**: `CAAPrint.edu/CAAPrtApplication.m/LocalInterfaces/CAAPrtDialog.h`
