---
title: "CAASysDRMDocument"
type: "LocalClass"
module: "CAAxPDMInterfaces"
base: "CATBaseUnknown"
method_count: 12
source_file: "CAAxPDMInterfaces.edu/CAAxPDMDRMILB.m/LocalInterfaces/CAASysDRMDocument.h"
---

# CAASysDRMDocument

> Data extension of the CATSysDRMDocument component and implementing CATIUExitDRMDocument and CATIUExitDRMAuthorization

**基类**: CATBaseUnknown | **模块**: CAAxPDMInterfaces | **方法数**: 12

## 依赖

- `CATBaseUnknown.h`
- `CATILockBytes.h`

## 公共方法

### DRMCreateContext

```cpp
HRESULT DRMCreateContext(const CATUC2Bytes * iDocumentID) ;
```

| 参数 | 类型 |
|------|------|
| iDocumentID | `const CATUC2Bytes *` |


### DRMCloseContext

```cpp
HRESULT DRMCloseContext() ;
```


### DRMExportEnveloppe

```cpp
HRESULT DRMExportEnveloppe(void *&oDRMEnvelope, size_t &oDRMEnvelopeSize) ;
```

| 参数 | 类型 |
|------|------|
| *&oDRMEnvelope | `void` |
| &oDRMEnvelopeSize | `size_t` |


### DRMFreeEnveloppe

```cpp
HRESULT DRMFreeEnveloppe(void *oDRMEnvelope) ;
```

| 参数 | 类型 |
|------|------|
| *oDRMEnvelope | `void` |


### DRMImportEnveloppe

```cpp
HRESULT DRMImportEnveloppe(const void *iDRMEnvelope, size_t iDRMEnvelopeSize) ;
```

| 参数 | 类型 |
|------|------|
| *iDRMEnvelope | `const void` |
| iDRMEnvelopeSize | `size_t` |


### DRMGetLibUID

```cpp
HRESULT DRMGetLibUID(GUID &oUID) ;
```

| 参数 | 类型 |
|------|------|
| &oUID | `GUID` |


### DRMInitAuthorization

```cpp
HRESULT DRMInitAuthorization(const CATUC2Bytes * iDocumentID) ;
```

| 参数 | 类型 |
|------|------|
| iDocumentID | `const CATUC2Bytes *` |


### DRMReleaseAuthorization

```cpp
HRESULT DRMReleaseAuthorization(const CATUC2Bytes * iDocumentID) ;
```

| 参数 | 类型 |
|------|------|
| iDocumentID | `const CATUC2Bytes *` |


### IsGranted

```cpp
HRESULT IsGranted(DWORD iRightToCheck) ;
```

| 参数 | 类型 |
|------|------|
| iRightToCheck | `DWORD` |


### DRMExportAuthorization

```cpp
HRESULT DRMExportAuthorization(void *&oDRMAuthorization, size_t &oDRMAuthorizationSize) ;
```

| 参数 | 类型 |
|------|------|
| *&oDRMAuthorization | `void` |
| &oDRMAuthorizationSize | `size_t` |


### DRMFreeAuthorization

```cpp
HRESULT DRMFreeAuthorization(void *iDRMAuthorization) ;
```

| 参数 | 类型 |
|------|------|
| *iDRMAuthorization | `void` |


### DRMImportAuthorization

```cpp
HRESULT DRMImportAuthorization(const void *iDRMAuthorization, size_t iDRMAuthorizationSize) ;
```

| 参数 | 类型 |
|------|------|
| *iDRMAuthorization | `const void` |
| iDRMAuthorizationSize | `size_t` |


---

**源文件**: `CAAxPDMInterfaces.edu/CAAxPDMDRMILB.m/LocalInterfaces/CAASysDRMDocument.h`
