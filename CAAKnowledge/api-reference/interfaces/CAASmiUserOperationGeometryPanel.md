---
title: "CAASmiUserOperationGeometryPanel"
type: "ProtectedInterface"
module: "CAASurfaceMachiningItf"
base: "CATDlgFrame"
method_count: 6
source_file: "CAASurfaceMachiningItf.edu/ProtectedInterfaces/CAASmiUserOperationGeometryPanel.h"
---

# CAASmiUserOperationGeometryPanel

**基类**: CATDlgFrame | **模块**: CAASurfaceMachiningItf | **方法数**: 6

## 依赖

- `CAASmiUserOperationGeomUIEnv.h`
- `CATDlgFrame.h`

## 公共方法

### SelectCurve

```cpp
void SelectCurve(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| *iPublisher | `CATCommand` |
| *iNotification | `CATNotification` |
| iUsefulData | `CATCommandClientData` |


### SelectZone

```cpp
void SelectZone(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| *iPublisher | `CATCommand` |
| *iNotification | `CATNotification` |
| iUsefulData | `CATCommandClientData` |


### RemoveAll

```cpp
void RemoveAll(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| *iPublisher | `CATCommand` |
| *iNotification | `CATNotification` |
| iUsefulData | `CATCommandClientData` |


### NewZone

```cpp
void NewZone(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| *iPublisher | `CATCommand` |
| *iNotification | `CATNotification` |
| iUsefulData | `CATCommandClientData` |


### Export

```cpp
void Export(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| *iPublisher | `CATCommand` |
| *iNotification | `CATNotification` |
| iUsefulData | `CATCommandClientData` |


### UpdateButtons

```cpp
void UpdateButtons(CATCallbackEvent iEvent, void *iFrom, CATNotification *iNotification, CATSubscriberData iClientData, CATCallback iCallBack) ;
```

| 参数 | 类型 |
|------|------|
| iEvent | `CATCallbackEvent` |
| *iFrom | `void` |
| *iNotification | `CATNotification` |
| iClientData | `CATSubscriberData` |
| iCallBack | `CATCallback` |


---

**源文件**: `CAASurfaceMachiningItf.edu/ProtectedInterfaces/CAASmiUserOperationGeometryPanel.h`
