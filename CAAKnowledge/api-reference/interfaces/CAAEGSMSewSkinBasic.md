---
title: "CAAEGSMSewSkinBasic"
type: "LocalClass"
module: "CAAGSMInterfaces"
base: "CATBaseUnknown"
method_count: 7
source_file: "CAAGSMInterfaces.edu/CAAGsiFeaturesSplModel.m/LocalInterfaces/CAAEGSMSewSkinBasic.h"
---

# CAAEGSMSewSkinBasic

**基类**: CATBaseUnknown | **模块**: CAAGSMInterfaces | **方法数**: 7

## 依赖

- `CATBaseUnknown.h`
- `CATGSMOrientation.h`
- `CATGSMContextDef.h`

## 公共方法

### SetSurfaceToSew

```cpp
HRESULT SetSurfaceToSew(CATISpecObject_var ispSurfaceToSew) ;
```

| 参数 | 类型 |
|------|------|
| ispSurfaceToSew | `CATISpecObject_var` |


### GetSurfaceToSew

```cpp
HRESULT GetSurfaceToSew(CATISpecObject_var & ospSurfaceToSew) ;
```

| 参数 | 类型 |
|------|------|
| ospSurfaceToSew | `CATISpecObject_var &` |


### SetSurfaceSupport

```cpp
HRESULT SetSurfaceSupport(CATISpecObject_var ispSupport) ;
```

| 参数 | 类型 |
|------|------|
| ispSupport | `CATISpecObject_var` |


### GetSurfaceSupport

```cpp
HRESULT GetSurfaceSupport(CATISpecObject_var & ospSupport) ;
```

| 参数 | 类型 |
|------|------|
| ospSupport | `CATISpecObject_var &` |


### SetOrientation

```cpp
HRESULT SetOrientation(CATGSMOrientation iOrientation) ;
```

| 参数 | 类型 |
|------|------|
| iOrientation | `CATGSMOrientation` |


### GetOrientation

```cpp
HRESULT GetOrientation(CATGSMOrientation & oOrientation) ;
```

| 参数 | 类型 |
|------|------|
| oOrientation | `CATGSMOrientation &` |


### InvertOrientation

```cpp
HRESULT InvertOrientation() ;
```


---

**源文件**: `CAAGSMInterfaces.edu/CAAGsiFeaturesSplModel.m/LocalInterfaces/CAAEGSMSewSkinBasic.h`
