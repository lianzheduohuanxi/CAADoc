---
title: "CAADlgFrameReplaceDlg"
type: "interface"
module: "CAADialog"
base: "CATDlgDialog"
method_count: 6
visibility: "local"
verified: true
---

# CAADlgFrameReplaceDlg

**基类**: CATDlgDialog  
**模块**: CAADialog  
**可见性**: local  
**方法数**: 6

> System framework

## 方法列表

### OnComboSelectNotification
```cpp
void OnComboSelectNotification(CATCommand * iSendingCommand, 
                                CATNotification * iSentNotification, 
                                CATCommandClientData iUsefulData);
```

### CloseWindowOK
```cpp
void CloseWindowOK(CATCommand * iSendingCommand, 
                                CATNotification * iSentNotification, 
                                CATCommandClientData iUsefulData);
```

### CloseWindow
```cpp
void CloseWindow(CATCommand * iSendingCommand, 
                                CATNotification * iSentNotification, 
                                CATCommandClientData iUsefulData);
```

### Activate
```cpp
CATStatusChangeRC Activate(CATCommand * iFromClient,
                            CATNotification * iEvtDat);
```

### Desactivate
```cpp
CATStatusChangeRC Desactivate(CATCommand * iFromClient,
                            CATNotification * iEvtDat);
```

### Cancel
```cpp
CATStatusChangeRC Cancel(CATCommand * iFromClient,
                            CATNotification * iEvtDat);
```

## 依赖

- `CATDlgDialog.h`

