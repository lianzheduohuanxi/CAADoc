---
title: "CAAxPDMDRMRightEditionFrame"
type: "LocalClass"
module: "CAAxPDMInterfaces"
base: "CATDlgFrame"
method_count: 9
source_file: "CAAxPDMInterfaces.edu/CAAxPDMDRMILB.m/LocalInterfaces/CAAxPDMDRMRightEditionFrame.h"
---

# CAAxPDMDRMRightEditionFrame

**基类**: CATDlgFrame | **模块**: CAAxPDMInterfaces | **方法数**: 9

## 依赖

- `CATDlgFrame.h`
- `CATListOfCATString.h`

## 公共方法

### BuildPanel

```cpp
void BuildPanel() ;
```


### Init

```cpp
HRESULT Init(const void *iDRMAuthorization, size_t iDRMAuthorizationSize) ;
```

| 参数 | 类型 |
|------|------|
| *iDRMAuthorization | `const void` |
| iDRMAuthorizationSize | `size_t` |


### InitWithDefault

```cpp
HRESULT InitWithDefault() ;
```


### RefreshDisplay

```cpp
HRESULT RefreshDisplay(CATUnicodeString * DRMUser, DWORD* DRMRight, int DRMUserNb) ;
```

| 参数 | 类型 |
|------|------|
| DRMUser | `CATUnicodeString *` |
| DRMRight | `DWORD*` |
| DRMUserNb | `int` |


### GetAuthorization

```cpp
HRESULT GetAuthorization(CATUnicodeString *&DRMUser, DWORD *&DRMRight, int& DRMUserNb) ;
```

| 参数 | 类型 |
|------|------|
| *&DRMUser | `CATUnicodeString` |
| *&DRMRight | `DWORD` |
| DRMUserNb | `int&` |


### GetAuthorizations

```cpp
HRESULT GetAuthorizations(void *& iDRMAuthorization, size_t& iDRMAuthorizationSize) ;
```

| 参数 | 类型 |
|------|------|
| iDRMAuthorization | `void *&` |
| iDRMAuthorizationSize | `size_t&` |


### ValidateToDefault

```cpp
HRESULT ValidateToDefault() ;
```


### Refresh

```cpp
void Refresh() ;
```


### Validate

```cpp
void Validate() ;
```


---

**源文件**: `CAAxPDMInterfaces.edu/CAAxPDMDRMILB.m/LocalInterfaces/CAAxPDMDRMRightEditionFrame.h`
