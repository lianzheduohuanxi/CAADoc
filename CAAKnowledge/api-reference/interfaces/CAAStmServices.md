---
title: "CAAStmServices"
type: "PublicInterface"
module: "CAAAerospaceSheetMetal"
base: ""
method_count: 8
source_file: "CAAAerospaceSheetMetal.edu/PublicInterfaces/CAAStmServices.h"
---

# CAAStmServices

**基类**: 无 | **模块**: CAAAerospaceSheetMetal | **方法数**: 8

## 依赖

- `CAAStmExportedBy.h`
- `CAAStmInputData.h`
- `CATDocument.h`
- `CATISpecObject.h`
- `CATListPtrCATISpecObject.h`
- `CATTopDefine.h`
- `CATUnicodeString.h`
- `CATListOfCATUnicodeString.h`

## 公共方法

### ReadInputFile

```cpp
HRESULT ReadInputFile(const CATUnicodeString & iFilePath, CATListOfCATUnicodeString & oLines) ;
```

| 参数 | 类型 |
|------|------|
| iFilePath | `const CATUnicodeString &` |
| oLines | `CATListOfCATUnicodeString &` |


### AnalyseWebInputData

```cpp
HRESULT AnalyseWebInputData(const CATUnicodeString & iInputDataFilePath, CAAStmInputData & ioCAAInputFlg) ;
```

| 参数 | 类型 |
|------|------|
| iInputDataFilePath | `const CATUnicodeString &` |
| ioCAAInputFlg | `CAAStmInputData &` |


### AnalyseSurfacicFlangeInputData

```cpp
HRESULT AnalyseSurfacicFlangeInputData(const CATUnicodeString & iInputDataFilePath, CAAStmInputData & ioCAAInputFlg) ;
```

| 参数 | 类型 |
|------|------|
| iInputDataFilePath | `const CATUnicodeString &` |
| ioCAAInputFlg | `CAAStmInputData &` |


### AnalyseJoggleInputData

```cpp
HRESULT AnalyseJoggleInputData(const CATUnicodeString & iInputDataFilePath, CAAStmInputData & ioCAAInputJoggle) ;
```

| 参数 | 类型 |
|------|------|
| iInputDataFilePath | `const CATUnicodeString &` |
| ioCAAInputJoggle | `CAAStmInputData &` |


### FindWeb

```cpp
HRESULT FindWeb(const CATISpecObject_var & ispPrtPartSpec, CATISpecObject ** opiWebSpec) ;
```

| 参数 | 类型 |
|------|------|
| ispPrtPartSpec | `const CATISpecObject_var &` |
| opiWebSpec | `CATISpecObject **` |


### FindFeatureInSpecTree

```cpp
HRESULT FindFeatureInSpecTree(const CATISpecObject_var & ispPrtPartSpec, const CATUnicodeString & iSpecName, CATISpecObject ** opiSpec) ;
```

| 参数 | 类型 |
|------|------|
| ispPrtPartSpec | `const CATISpecObject_var &` |
| iSpecName | `const CATUnicodeString &` |
| opiSpec | `CATISpecObject **` |


### Update

```cpp
HRESULT Update(CATISpecObject * ipiSpec) ;
```

| 参数 | 类型 |
|------|------|
| ipiSpec | `CATISpecObject *` |


### Display

```cpp
HRESULT Display(CATISpecObject * ipiSpec) ;
```

| 参数 | 类型 |
|------|------|
| ipiSpec | `CATISpecObject *` |


---

**源文件**: `CAAAerospaceSheetMetal.edu/PublicInterfaces/CAAStmServices.h`
