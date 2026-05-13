---
title: "CAASysSprocketsImpl"
type: "LocalClass"
module: "CAASystem"
base: "CATBaseCollection"
method_count: 7
source_file: "CAASystem.edu/CAASysAutomationImpl.m/LocalInterfaces/CAASysSprocketsImpl.h"
---

# CAASysSprocketsImpl

**基类**: CATBaseCollection | **模块**: CAASystem | **方法数**: 7

## 依赖

- `CATBaseCollection.h`
- `CATVariant.h`
- `CATSafeArray.h`
- `CATListOfCAAIASysSprocket.h`

## 虚方法

### get_Name

```cpp
virtual HRESULT __stdcall get_Name(CATBSTR & oNameBSTR) ;
```

Partial implementation of the CATIACollection interface

| 参数 | 类型 |
|------|------|
| oNameBSTR | `CATBSTR &` |


### get__NewEnum

```cpp
virtual HRESULT __stdcall get__NewEnum(IUnknown *& oEnumerator) ;
```

| 参数 | 类型 |
|------|------|
| oEnumerator | `IUnknown *&` |


### get_Count

```cpp
virtual HRESULT __stdcall get_Count(CATLONG & oCount) ;
```

| 参数 | 类型 |
|------|------|
| oCount | `CATLONG &` |


### Item

```cpp
virtual HRESULT __stdcall Item(const CATVariant & iIndex, CAAIASysSprocket *& oSprocket) ;
```

Implementation of the CAAIASysSprockets interface

| 参数 | 类型 |
|------|------|
| iIndex | `const CATVariant &` |
| oSprocket | `CAAIASysSprocket *&` |


### AddAll

```cpp
virtual HRESULT __stdcall AddAll(const CATSafeArrayVariant & iSprocketArray) ;
```

| 参数 | 类型 |
|------|------|
| iSprocketArray | `const CATSafeArrayVariant &` |


### ToArray

```cpp
virtual HRESULT __stdcall ToArray(CATSafeArrayVariant & ioArray) ;
```

| 参数 | 类型 |
|------|------|
| ioArray | `CATSafeArrayVariant &` |


## 静态方法

### CreateSprockets

```cpp
static HRESULT __stdcall CreateSprockets(CAAIASysSprockets*& oCAAIASysSprockets) ;
```

| 参数 | 类型 |
|------|------|
| oCAAIASysSprockets | `CAAIASysSprockets*&` |


---

**源文件**: `CAASystem.edu/CAASysAutomationImpl.m/LocalInterfaces/CAASysSprocketsImpl.h`
