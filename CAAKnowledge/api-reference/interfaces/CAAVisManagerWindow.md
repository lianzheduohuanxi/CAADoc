---
title: "CAAVisManagerWindow"
type: "LocalClass"
module: "CAAVisualization"
base: "CATDlgDialog"
method_count: 4
source_file: "CAAVisualization.edu/CAAVisManagerAppli.m/LocalInterfaces/CAAVisManagerWindow.h"
---

# CAAVisManagerWindow

> MDI Window . Events send by it: WINDOW_ACTIVATED    (from uncurrent window to current window) WINDOW_DEACTIVATED  (from current window to uncurrent window) WINDOW_CREATED WINDOW_DELETED VIEWER_SELECTED    (MouseButton1 Down on a Viewer) (sender is viewer) VIEWER_ACTIVATED   (The CurrentViewer has been changed) (sender is viewer) VIEWPOINT_CHANGED  (The main viewpoint of the currentViewer has been changed) (sender is window) Dialog Framework

**基类**: CATDlgDialog | **模块**: CAAVisualization | **方法数**: 4

## 依赖

- `CATDlgDialog.h`
- `CATString.h`

## 虚方法

### DuplicateWindow

```cpp
virtual CAAVisManagerWindow * DuplicateWindow() ;
```

Duplicator, Not Yet implemented


### GetEditor

```cpp
virtual CAAVisManagerEditor * GetEditor() ;
```


### Build

```cpp
virtual void Build() ;
```


### DeleteWindow

```cpp
virtual void DeleteWindow() ;
```

Methods called by the application


---

**源文件**: `CAAVisualization.edu/CAAVisManagerAppli.m/LocalInterfaces/CAAVisManagerWindow.h`
