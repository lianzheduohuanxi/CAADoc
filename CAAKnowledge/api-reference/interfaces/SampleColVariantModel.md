---
title: "SampleColVariantModel"
type: "LocalClass"
module: "CAACATIAApplicationFrm"
base: "CATExtIDlgTableViewColumnModel"
method_count: 13
source_file: "CAACATIAApplicationFrm.edu/CAACafDlgView.m/LocalInterfaces/SampleColVariantModel.h"
---

# SampleColVariantModel

**基类**: CATExtIDlgTableViewColumnModel | **模块**: CAACATIAApplicationFrm | **方法数**: 13

## 依赖

- `CATExtIDlgTableViewColumnModel.h`
- `SampleViewController.h`
- `CATListOfCATString.h`
- `CATListOfCATUnicodeString.h`
- `CATListOfInt.h`

## 公共方法

### SetController

```cpp
void SetController(SampleViewController* iControl) ;
```

| 参数 | 类型 |
|------|------|
| iControl | `SampleViewController*` |


### SetOrderedColumns

```cpp
HRESULT SetOrderedColumns(const CATListOfCATString &iColumns) ;
```

| 参数 | 类型 |
|------|------|
| &iColumns | `const CATListOfCATString` |


### GetOrderedColumns

```cpp
HRESULT GetOrderedColumns(CATListOfCATString &oColumns) ;
```

| 参数 | 类型 |
|------|------|
| &oColumns | `CATListOfCATString` |


### GetLabel

```cpp
HRESULT GetLabel(const CATString & iColumn, CATUnicodeString & oLabel) ;
```

| 参数 | 类型 |
|------|------|
| iColumn | `const CATString &` |
| oLabel | `CATUnicodeString &` |


### GetStyle

```cpp
HRESULT GetStyle(const CATString & iColumn, CATDlgTableStyle & oStyle) ;
```

| 参数 | 类型 |
|------|------|
| iColumn | `const CATString &` |
| oStyle | `CATDlgTableStyle &` |


### GetWidth

```cpp
HRESULT GetWidth(const CATString &iColumn, int & oWidth) ;
```

| 参数 | 类型 |
|------|------|
| &iColumn | `const CATString` |
| oWidth | `int &` |


### SetWidth

```cpp
HRESULT SetWidth(const CATString &iColumn, int iWidth) ;
```

| 参数 | 类型 |
|------|------|
| &iColumn | `const CATString` |
| iWidth | `int` |


### SetSortDefinition

```cpp
void SetSortDefinition(const CATString &iColumn, int iReverse= 0) ;
```

| 参数 | 类型 |
|------|------|
| &iColumn | `const CATString` |
| 0 | `int iReverse=` |


### GetSortDefinition

```cpp
void GetSortDefinition(CATString &oColumn, int &oReverse) ;
```

| 参数 | 类型 |
|------|------|
| &oColumn | `CATString` |
| &oReverse | `int` |


### SetVisibility

```cpp
HRESULT SetVisibility(const CATString & iColumn, CATDlgTableStyle iStyle) ;
```

| 参数 | 类型 |
|------|------|
| iColumn | `const CATString &` |
| iStyle | `CATDlgTableStyle` |


### GetBackgroundColor

```cpp
HRESULT GetBackgroundColor(CATDlgTableStyle iStyle, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha) ;
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
HRESULT GetTextColor(CATDlgTableStyle iStyle, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha) ;
```

| 参数 | 类型 |
|------|------|
| iStyle | `CATDlgTableStyle` |
| ioRed | `unsigned int &` |
| ioGreen | `unsigned int &` |
| ioBlue | `unsigned int &` |
| ioAlpha | `unsigned int &` |


### DefineTheColumns

```cpp
void DefineTheColumns(int iNbCols) ;
```

| 参数 | 类型 |
|------|------|
| iNbCols | `int` |


---

**源文件**: `CAACATIAApplicationFrm.edu/CAACafDlgView.m/LocalInterfaces/SampleColVariantModel.h`
