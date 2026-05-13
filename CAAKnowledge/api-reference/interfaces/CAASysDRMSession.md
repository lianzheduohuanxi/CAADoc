---
title: "CAASysDRMSession"
type: "LocalClass"
module: "CAAxPDMInterfaces"
base: "CATBaseUnknown"
method_count: 8
source_file: "CAAxPDMInterfaces.edu/CAAxPDMDRMILB.m/LocalInterfaces/CAASysDRMSession.h"
---

# CAASysDRMSession

**基类**: CATBaseUnknown | **模块**: CAAxPDMInterfaces | **方法数**: 8

## 依赖

- `CATBaseUnknown.h`
- `CATUnicodeString.h`

## 虚方法

### DRMInitSession

```cpp
virtual HRESULT DRMInitSession() ;
```


### DRMGetPolicy

```cpp
virtual HRESULT DRMGetPolicy(DWORD iPolicy) ;
```

| 参数 | 类型 |
|------|------|
| iPolicy | `DWORD` |


### DRMCloseSession

```cpp
virtual HRESULT DRMCloseSession() ;
```


### DRMGetProviderName

```cpp
virtual HRESULT DRMGetProviderName(CATUnicodeString &oName) ;
```

| 参数 | 类型 |
|------|------|
| &oName | `CATUnicodeString` |


### BuildAboutFrame

```cpp
virtual HRESULT BuildAboutFrame(CATDlgFrame *iParentFrame) ;
```

| 参数 | 类型 |
|------|------|
| *iParentFrame | `CATDlgFrame` |


### BuildEditRightFrame

```cpp
virtual HRESULT BuildEditRightFrame(CATDlgFrame *iParentFrame, const void *iDRMAuthorization, size_t iDRMAuthorizationSize, CATDlgFrame **oCreatedFrame) ;
```

| 参数 | 类型 |
|------|------|
| *iParentFrame | `CATDlgFrame` |
| *iDRMAuthorization | `const void` |
| iDRMAuthorizationSize | `size_t` |
| **oCreatedFrame | `CATDlgFrame` |


## 公共方法

### FillAdditionalInformationFrame

```cpp
HRESULT FillAdditionalInformationFrame(CATDlgFrame *iParentFrame, CATBaseUnknown *iCurrentDoc) ;
```

| 参数 | 类型 |
|------|------|
| *iParentFrame | `CATDlgFrame` |
| *iCurrentDoc | `CATBaseUnknown` |


### IsAbletoShow

```cpp
HRESULT IsAbletoShow(int iFrameDescriptor, CATBoolean& iIsAble) ;
```

| 参数 | 类型 |
|------|------|
| iFrameDescriptor | `int` |
| iIsAble | `CATBoolean&` |


---

**源文件**: `CAAxPDMInterfaces.edu/CAAxPDMDRMILB.m/LocalInterfaces/CAASysDRMSession.h`
