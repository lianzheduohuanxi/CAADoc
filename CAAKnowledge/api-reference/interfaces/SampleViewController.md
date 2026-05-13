---
title: "SampleViewController"
type: "LocalClass"
module: "CAACATIAApplicationFrm"
base: "CATExtIDlgTableViewController"
method_count: 32
source_file: "CAACATIAApplicationFrm.edu/CAACafDlgView.m/LocalInterfaces/SampleViewController.h"
---

# SampleViewController

**基类**: CATExtIDlgTableViewController | **模块**: CAACATIAApplicationFrm | **方法数**: 32

## 依赖

- `CATExtIDlgTableViewController.h`
- `CATString.h`
- `CATBaseUnknown.h`
- `CATListOfSampleCell.h`
- `CATLISTV_CATBaseUnknown.h`
- `CATIDlgTableViewModel.h`
- `CATBoolean.h`

## 虚方法

### IsSelected

```cpp
virtual HRESULT IsSelected(CATBaseUnknown_var iNode, CATBoolean & oResult) ;
```

| 参数 | 类型 |
|------|------|
| iNode | `CATBaseUnknown_var` |
| oResult | `CATBoolean &` |


### IsSelected

```cpp
virtual HRESULT IsSelected(CATBaseUnknown_var iNode, const CATString& iColID, CATBoolean & oResult) ;
```

| 参数 | 类型 |
|------|------|
| iNode | `CATBaseUnknown_var` |
| iColID | `const CATString&` |
| oResult | `CATBoolean &` |


### IsPreSelected

```cpp
virtual HRESULT IsPreSelected(CATBaseUnknown_var iNode, const CATString& iColID, CATBoolean & oResult) ;
```

| 参数 | 类型 |
|------|------|
| iNode | `CATBaseUnknown_var` |
| iColID | `const CATString&` |
| oResult | `CATBoolean &` |


### HasSelection

```cpp
virtual HRESULT HasSelection(const CATString& iColumn, CATBoolean & oHasSelection) ;
```

| 参数 | 类型 |
|------|------|
| iColumn | `const CATString&` |
| oHasSelection | `CATBoolean &` |


### OnSelect

```cpp
virtual HRESULT OnSelect(CATBaseUnknown_var iNode, const CATString& iColID) ;
```

| 参数 | 类型 |
|------|------|
| iNode | `CATBaseUnknown_var` |
| iColID | `const CATString&` |


### OnMoveOver

```cpp
virtual HRESULT OnMoveOver(CATBaseUnknown_var iNode, const CATString& iColID) ;
```

| 参数 | 类型 |
|------|------|
| iNode | `CATBaseUnknown_var` |
| iColID | `const CATString&` |


### OnActivate

```cpp
virtual HRESULT OnActivate(CATBaseUnknown_var iItem) ;
```

| 参数 | 类型 |
|------|------|
| iItem | `CATBaseUnknown_var` |


### OnContext

```cpp
virtual HRESULT OnContext(CATBaseUnknown_var iNode) ;
```

| 参数 | 类型 |
|------|------|
| iNode | `CATBaseUnknown_var` |


### OnCellContext

```cpp
virtual HRESULT OnCellContext(CATBaseUnknown_var iNode, const CATString& iColID) ;
```

| 参数 | 类型 |
|------|------|
| iNode | `CATBaseUnknown_var` |
| iColID | `const CATString&` |


### OnRowHeaderContext

```cpp
virtual HRESULT OnRowHeaderContext(CATBaseUnknown_var iItem) ;
```

| 参数 | 类型 |
|------|------|
| iItem | `CATBaseUnknown_var` |


### OnColumnHeaderContext

```cpp
virtual HRESULT OnColumnHeaderContext(const CATString& iColID) ;
```

| 参数 | 类型 |
|------|------|
| iColID | `const CATString&` |


### OnSampleContextualDependant

```cpp
virtual void OnSampleContextualDependant(CATCallbackEvent , void *, CATNotification * evt, CATSubscriberData data, CATCallback) ;
```

| 参数 | 类型 |
|------|------|
|  | `CATCallbackEvent` |
| * | `void` |
| evt | `CATNotification *` |
| data | `CATSubscriberData` |
|  | `CATCallback` |


### ACellIsSelectedInTheColumn

```cpp
virtual int ACellIsSelectedInTheColumn(const CATString& iColID) ;
```

| 参数 | 类型 |
|------|------|
| iColID | `const CATString&` |


### ACellIsSelectedInTheLine

```cpp
virtual int ACellIsSelectedInTheLine(CATBaseUnknown_var iItem) ;
```

| 参数 | 类型 |
|------|------|
| iItem | `CATBaseUnknown_var` |


### ACellIsSelectedInTheLine

```cpp
virtual int ACellIsSelectedInTheLine(const int iRow) ;
```

| 参数 | 类型 |
|------|------|
| iRow | `const int` |


### OnSelectContextualMenu

```cpp
virtual void OnSelectContextualMenu(CATCallbackEvent , void *, CATNotification *, CATSubscriberData data, CATCallback) ;
```

| 参数 | 类型 |
|------|------|
|  | `CATCallbackEvent` |
| * | `void` |
| * | `CATNotification` |
| data | `CATSubscriberData` |
|  | `CATCallback` |


### OnSelectContextualMenu

```cpp
virtual void OnSelectContextualMenu(CATCommand *, CATNotification *, CATCommandClientData) ;
```

| 参数 | 类型 |
|------|------|
| * | `CATCommand` |
| * | `CATNotification` |
|  | `CATCommandClientData` |


## 公共方法

### SetModel

```cpp
void SetModel(CATIDlgTableViewModel_var iModel) ;
```

| 参数 | 类型 |
|------|------|
| iModel | `CATIDlgTableViewModel_var` |


### ClearSelection

```cpp
void ClearSelection(int iNotify= 1) ;
```

| 参数 | 类型 |
|------|------|
| 1 | `int iNotify=` |


### RemoveFromSelection

```cpp
void RemoveFromSelection(const SampleCell &pCell) ;
```

| 参数 | 类型 |
|------|------|
| &pCell | `const SampleCell` |


### AddToSelection

```cpp
void AddToSelection(const SampleCell &pCell, int iNotify= 1) ;
```

| 参数 | 类型 |
|------|------|
| &pCell | `const SampleCell` |
| 1 | `int iNotify=` |


### IsInSelection

```cpp
int IsInSelection(const SampleCell &pCell) ;
```

| 参数 | 类型 |
|------|------|
| &pCell | `const SampleCell` |


### SelectionCount

```cpp
int SelectionCount() ;
```


### UnregisterItemSelectedEvent

```cpp
void UnregisterItemSelectedEvent(CATEventSubscriber *iSubscriber, CATCallback iUpdateCallback) ;
```

| 参数 | 类型 |
|------|------|
| *iSubscriber | `CATEventSubscriber` |
| iUpdateCallback | `CATCallback` |


### HighlightColumn

```cpp
void HighlightColumn(const CATString& iColID) ;
```

| 参数 | 类型 |
|------|------|
| iColID | `const CATString&` |


### LineSelection

```cpp
void LineSelection(CATBaseUnknown_var iItem, const CATBoolean &AddLine) ;
```

| 参数 | 类型 |
|------|------|
| iItem | `CATBaseUnknown_var` |
| &AddLine | `const CATBoolean` |


### OnScrollStart

```cpp
void OnScrollStart() ;
```


### OnScroll

```cpp
void OnScroll() ;
```


### OnScrollStop

```cpp
void OnScrollStop() ;
```


### Synchronize

```cpp
void Synchronize(SampleListEditor *another, SampleViewController * anotherController, CATBoolean iHide=FALSE) ;
```

| 参数 | 类型 |
|------|------|
| *another | `SampleListEditor` |
| anotherController | `SampleViewController *` |
| iHide=FALSE | `CATBoolean` |


### UpdateHighlight

```cpp
void UpdateHighlight(CATBaseUnknown_var iItem) ;
```

| 参数 | 类型 |
|------|------|
| iItem | `CATBaseUnknown_var` |


### UpdateHighlight

```cpp
void UpdateHighlight(int iLine) ;
```

| 参数 | 类型 |
|------|------|
| iLine | `int` |


---

**源文件**: `CAACATIAApplicationFrm.edu/CAACafDlgView.m/LocalInterfaces/SampleViewController.h`
