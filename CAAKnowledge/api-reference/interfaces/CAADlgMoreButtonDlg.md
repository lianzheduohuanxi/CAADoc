---
title: "CAADlgMoreButtonDlg"
type: "interface"
module: "CAADialog"
base: "CATDlgDialog"
method_count: 5
visibility: "local"
verified: true
---

# CAADlgMoreButtonDlg

**基类**: CATDlgDialog  
**模块**: CAADialog  
**可见性**: local  
**方法数**: 5

> Dialog framework

## 方法列表

### CloseWindow
```cpp
void CloseWindow(CATCommand * iSendingCommand, 
                                CATNotification * iSentNotification, 
                                CATCommandClientData iUsefulData);
```

### OnPushButtonMorePushBActivateNotification
```cpp
void OnPushButtonMorePushBActivateNotification(CATCommand * iSendingCommand, 
                                                              CATNotification *  iSentNotification, 
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
- `CATUnicodeString.h`
- `CATBoolean.h`

