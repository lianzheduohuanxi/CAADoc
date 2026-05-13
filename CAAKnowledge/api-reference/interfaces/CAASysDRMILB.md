---
title: "CAASysDRMILB"
type: "LocalClass"
module: "CAAxPDMInterfaces"
base: "CATBaseUnknown"
method_count: 9
source_file: "CAAxPDMInterfaces.edu/CAAxPDMDRMILB.m/LocalInterfaces/CAASysDRMILB.h"
---

# CAASysDRMILB

> Data extension of the CATSysDRMDocument component and implementing the CATIUExitDRMILockBytes, CATIUExitDRMDocument and CATIUExitDRMAuthorization

**基类**: CATBaseUnknown | **模块**: CAAxPDMInterfaces | **方法数**: 9

## 依赖

- `CATBaseUnknown.h`
- `CATIUExitDRMILockBytes.h`
- `CATILockBytes.h`

## 公共方法

### ReadAt

```cpp
HRESULT ReadAt(ULARGE_INTEGER iOffset, void *iBuff, ULONG iLengthToRead, ULONG *oLengthRead) ;
```

| 参数 | 类型 |
|------|------|
| iOffset | `ULARGE_INTEGER` |
| *iBuff | `void` |
| iLengthToRead | `ULONG` |
| *oLengthRead | `ULONG` |


### WriteAt

```cpp
HRESULT WriteAt(ULARGE_INTEGER iOffset, const void *iDataSource, ULONG iLengthToWrite, ULONG *LengthWritten) ;
```

| 参数 | 类型 |
|------|------|
| iOffset | `ULARGE_INTEGER` |
| *iDataSource | `const void` |
| iLengthToWrite | `ULONG` |
| *LengthWritten | `ULONG` |


### Flush

```cpp
HRESULT Flush() ;
```


### SetSize

```cpp
HRESULT SetSize(ULARGE_INTEGER iLength) ;
```

| 参数 | 类型 |
|------|------|
| iLength | `ULARGE_INTEGER` |


### LockRegion

```cpp
HRESULT LockRegion(ULARGE_INTEGER iOffset, ULARGE_INTEGER iLegnth, DWORD dwLockType) ;
```

| 参数 | 类型 |
|------|------|
| iOffset | `ULARGE_INTEGER` |
| iLegnth | `ULARGE_INTEGER` |
| dwLockType | `DWORD` |


### UnlockRegion

```cpp
HRESULT UnlockRegion(ULARGE_INTEGER iOffset, ULARGE_INTEGER iLength, DWORD dwLockType) ;
```

| 参数 | 类型 |
|------|------|
| iOffset | `ULARGE_INTEGER` |
| iLength | `ULARGE_INTEGER` |
| dwLockType | `DWORD` |


### Stat

```cpp
HRESULT Stat(STATSTG FAR *oStat, DWORD iStatFlag) ;
```

| 参数 | 类型 |
|------|------|
| *oStat | `STATSTG FAR` |
| iStatFlag | `DWORD` |


### OpenOnILockBytes

```cpp
HRESULT OpenOnILockBytes(CATILockBytes *iILB) ;
```

CATIUExitDRMILockBytes

| 参数 | 类型 |
|------|------|
| *iILB | `CATILockBytes` |


### Close

```cpp
HRESULT Close() ;
```


---

**源文件**: `CAAxPDMInterfaces.edu/CAAxPDMDRMILB.m/LocalInterfaces/CAASysDRMILB.h`
