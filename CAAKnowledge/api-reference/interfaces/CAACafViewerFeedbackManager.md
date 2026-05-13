---
title: "CAACafViewerFeedbackManager"
type: "LocalClass"
module: "CAACATIAApplicationFrm"
base: "CATBaseUnknown"
method_count: 3
source_file: "CAACATIAApplicationFrm.edu/CAACafViewerFeedback.m/LocalInterfaces/CAACafViewerFeedbackManager.h"
---

# CAACafViewerFeedbackManager

> This class manages a visual feedback in the current viewer.

**基类**: CATBaseUnknown | **模块**: CAACATIAApplicationFrm | **方法数**: 3

## 依赖

- `CATBaseUnknown.h`
- `CATEventSubscriber.h`

## 静态方法

### GetManager

```cpp
static void GetManager(CAACafViewerFeedbackManager ** opManager) ;
```

This class has only one instance during the session

| 参数 | 类型 |
|------|------|
| opManager | `CAACafViewerFeedbackManager **` |


## 公共方法

### SetViewerFeedbackOn

```cpp
void SetViewerFeedbackOn() ;
```


### SetViewerFeedbackOff

```cpp
void SetViewerFeedbackOff() ;
```


---

**源文件**: `CAACATIAApplicationFrm.edu/CAACafViewerFeedback.m/LocalInterfaces/CAACafViewerFeedbackManager.h`
