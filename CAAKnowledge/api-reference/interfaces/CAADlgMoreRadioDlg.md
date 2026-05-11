---
title: "CAADlgMoreRadioDlg"
type: "interface"
module: "CAADialog"
base: "CATDlgDialog"
method_count: 7
visibility: "local"
verified: true
---

# CAADlgMoreRadioDlg

**基类**: CATDlgDialog  
**模块**: CAADialog  
**可见性**: local  
**方法数**: 7

> COPYRIGHT Dassault Systemes 2001

## 方法列表

### CloseWindow
```cpp
void CloseWindow(CATCommand * iSendingCommand, 
                                CATNotification * iSentNotification, 
                                CATCommandClientData iUsefulData);
```

### OnRadioButtonDBRadBModifyNotification
```cpp
void OnRadioButtonDBRadBModifyNotification(CATCommand * iSendingCommand, 
                                                          CATNotification * iSentNotification, 
                                                          CATCommandClientData iUsefulData);
```

### OnRadioButtonDARadBModifyNotification
```cpp
void OnRadioButtonDARadBModifyNotification(CATCommand * iSendingCommand, 
                                                          CATNotification * iSentNotification, 
                                                          CATCommandClientData iUsefulData);
```

### OnRadioButtonNDRadBModifyNotification
```cpp
void OnRadioButtonNDRadBModifyNotification(CATCommand * iSendingCommand, 
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

