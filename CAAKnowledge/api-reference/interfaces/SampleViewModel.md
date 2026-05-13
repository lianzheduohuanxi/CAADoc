---
title: "SampleViewModel"
type: "LocalClass"
module: "CAACATIAApplicationFrm"
base: "CATExtIDlgTableViewModel"
method_count: 18
source_file: "CAACATIAApplicationFrm.edu/CAACafDlgView.m/LocalInterfaces/SampleViewModel.h"
---

# SampleViewModel

**基类**: CATExtIDlgTableViewModel | **模块**: CAACATIAApplicationFrm | **方法数**: 18

## 依赖

- `CATExtIDlgTableViewModel.h`
- `CATIDlgTableViewModel.h`
- `SampleRow.h`

## 虚方法

### GetUpdateEvent

```cpp
virtual HRESULT GetUpdateEvent(CATCallbackEvent * oUpdateEvent) ;
```

CATIDlgTableViewModel implementation

| 参数 | 类型 |
|------|------|
| oUpdateEvent | `CATCallbackEvent *` |


### GetEventPublisher

```cpp
virtual HRESULT GetEventPublisher(CATBaseUnknown ** oTableModelEventPublisher) ;
```

| 参数 | 类型 |
|------|------|
| oTableModelEventPublisher | `CATBaseUnknown **` |


### GetLabel

```cpp
virtual HRESULT GetLabel(CATBaseUnknown_var & iLine, const CATString & iColumnID, CATUnicodeString & oLabel) ;
```

| 参数 | 类型 |
|------|------|
| iLine | `CATBaseUnknown_var &` |
| iColumnID | `const CATString &` |
| oLabel | `CATUnicodeString &` |


### SetLabel

```cpp
virtual HRESULT SetLabel(CATBaseUnknown_var & iLine, const CATString &iColumnID, const CATUnicodeString& iLabel) ;
```

| 参数 | 类型 |
|------|------|
| iLine | `CATBaseUnknown_var &` |
| &iColumnID | `const CATString` |
| iLabel | `const CATUnicodeString&` |


### IsEditable

```cpp
virtual HRESULT IsEditable(CATBaseUnknown_var & iLine, const CATString& iColumnID, CATBoolean & oEditable) ;
```

| 参数 | 类型 |
|------|------|
| iLine | `CATBaseUnknown_var &` |
| iColumnID | `const CATString&` |
| oEditable | `CATBoolean &` |


### GetIcon

```cpp
virtual HRESULT GetIcon(CATBaseUnknown_var iLine, const CATString &iColumnID, CATUnicodeString & oIcon) ;
```

virtual HRESULT IsEditable(CATBaseUnknown_var & iLine, const CATString& iColumnID, CATBoolean & oEditable);

| 参数 | 类型 |
|------|------|
| iLine | `CATBaseUnknown_var` |
| &iColumnID | `const CATString` |
| oIcon | `CATUnicodeString &` |


### GetStyle

```cpp
virtual HRESULT GetStyle(CATBaseUnknown_var iLine, const CATString &iColumnID, CATDlgTableStyle & oStyle) ;
```

| 参数 | 类型 |
|------|------|
| iLine | `CATBaseUnknown_var` |
| &iColumnID | `const CATString` |
| oStyle | `CATDlgTableStyle &` |


### GetLineCount

```cpp
virtual HRESULT GetLineCount(int & oLineCount) ;
```

| 参数 | 类型 |
|------|------|
| oLineCount | `int &` |


### GetLines

```cpp
virtual HRESULT GetLines(int iStart, int iCount, CATListOfCATBaseUnknown_var & oLines) ;
```

| 参数 | 类型 |
|------|------|
| iStart | `int` |
| iCount | `int` |
| oLines | `CATListOfCATBaseUnknown_var &` |


### GetBackgroundColor

```cpp
virtual HRESULT GetBackgroundColor(CATDlgTableStyle iStyle, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha) ;
```

| 参数 | 类型 |
|------|------|
| iStyle | `CATDlgTableStyle` |
| ioRed | `unsigned int &` |
| ioGreen | `unsigned int &` |
| ioBlue | `unsigned int &` |
| ioAlpha | `unsigned int &` |


### GetTextColor

```cpp
virtual HRESULT GetTextColor(CATDlgTableStyle iStyle, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha) ;
```

| 参数 | 类型 |
|------|------|
| iStyle | `CATDlgTableStyle` |
| ioRed | `unsigned int &` |
| ioGreen | `unsigned int &` |
| ioBlue | `unsigned int &` |
| ioAlpha | `unsigned int &` |


### GetBorderColor

```cpp
virtual HRESULT GetBorderColor(CATDlgTableStyle iStyle, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha) ;
```

| 参数 | 类型 |
|------|------|
| iStyle | `CATDlgTableStyle` |
| ioRed | `unsigned int &` |
| ioGreen | `unsigned int &` |
| ioBlue | `unsigned int &` |
| ioAlpha | `unsigned int &` |


### GetTextColor

```cpp
virtual HRESULT GetTextColor(CATBaseUnknown_var iLine, const CATString &iColumnID, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha) ;
```

| 参数 | 类型 |
|------|------|
| iLine | `CATBaseUnknown_var` |
| &iColumnID | `const CATString` |
| ioRed | `unsigned int &` |
| ioGreen | `unsigned int &` |
| ioBlue | `unsigned int &` |
| ioAlpha | `unsigned int &` |


### GetBackgroundColor

```cpp
virtual HRESULT GetBackgroundColor(CATBaseUnknown_var iLine, const CATString &iColumnID, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha) ;
```

| 参数 | 类型 |
|------|------|
| iLine | `CATBaseUnknown_var` |
| &iColumnID | `const CATString` |
| ioRed | `unsigned int &` |
| ioGreen | `unsigned int &` |
| ioBlue | `unsigned int &` |
| ioAlpha | `unsigned int &` |


### Sort

```cpp
virtual void Sort(const CATString &iColumn, int iReverse) ;
```

| 参数 | 类型 |
|------|------|
| &iColumn | `const CATString` |
| iReverse | `int` |


### HighlightColumn

```cpp
virtual void HighlightColumn(const CATString &iColumnID) ;
```

| 参数 | 类型 |
|------|------|
| &iColumnID | `const CATString` |


## 静态方法

### GetRowId

```cpp
static int GetRowId(CATBaseUnknown_var iItem) ;
```

Utilitaire

| 参数 | 类型 |
|------|------|
| iItem | `CATBaseUnknown_var` |


## 公共方法

### FillTheColumns

```cpp
void FillTheColumns(int iNbRows) ;
```

| 参数 | 类型 |
|------|------|
| iNbRows | `int` |


---

**源文件**: `CAACATIAApplicationFrm.edu/CAACafDlgView.m/LocalInterfaces/SampleViewModel.h`
