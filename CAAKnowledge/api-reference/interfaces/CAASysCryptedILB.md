---
title: "CAASysCryptedILB"
type: "LocalClass"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 18
source_file: "CAASystem.edu/CAASysCryptedILB.m/LocalInterfaces/CAASysCryptedILB.h"
---

# CAASysCryptedILB

> Data extension of the CATUExitCryptedILockBytes component and implementing the CATIUExitCryptedILockBytes interface. The component CATUExitCryptedILockBytes is defined in the System FW.

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 18

## 依赖

- `CATBaseUnknown.h`
- `CATIUExitCryptedILockBytes.h`

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


### Open

```cpp
HRESULT Open(const CATUnicodeString * iPath, DWORD iMode, CATSysOpenMode iOpenMode, CATSysSharing iSharingMode, CATSysCreateMode iOpenFlag, CATSysCloseMode iCloseFlag) ;
```

| 参数 | 类型 |
|------|------|
| iPath | `const CATUnicodeString *` |
| iMode | `DWORD` |
| iOpenMode | `CATSysOpenMode` |
| iSharingMode | `CATSysSharing` |
| iOpenFlag | `CATSysCreateMode` |
| iCloseFlag | `CATSysCloseMode` |


### OpenW

```cpp
HRESULT OpenW(const CATUC2Bytes * iPath, DWORD iMode, CATSysOpenMode iOpenMode, CATSysSharing iSharingMode, CATSysCreateMode iOpenFlag, CATSysCloseMode iCloseFlag) ;
```

| 参数 | 类型 |
|------|------|
| iPath | `const CATUC2Bytes *` |
| iMode | `DWORD` |
| iOpenMode | `CATSysOpenMode` |
| iSharingMode | `CATSysSharing` |
| iOpenFlag | `CATSysCreateMode` |
| iCloseFlag | `CATSysCloseMode` |


### Close

```cpp
HRESULT Close() ;
```


### Read

```cpp
HRESULT Read(void *iBuff, ULONG iLengthToRead, ULONG *oLengthRead) ;
```

| 参数 | 类型 |
|------|------|
| *iBuff | `void` |
| iLengthToRead | `ULONG` |
| *oLengthRead | `ULONG` |


### Write

```cpp
HRESULT Write(const void *iDataSource, ULONG iLengthToWrite, ULONG *LengthWritten) ;
```

| 参数 | 类型 |
|------|------|
| *iDataSource | `const void` |
| iLengthToWrite | `ULONG` |
| *LengthWritten | `ULONG` |


### ReadLine

```cpp
HRESULT ReadLine(char * ioLine, ULONG iNb, int &oEof) ;
```

| 参数 | 类型 |
|------|------|
| ioLine | `char *` |
| iNb | `ULONG` |
| &oEof | `int` |


### WriteLine

```cpp
HRESULT WriteLine(const char * iBuff) ;
```

| 参数 | 类型 |
|------|------|
| iBuff | `const char *` |


### ReadLineW

```cpp
HRESULT ReadLineW(CATUnicodeString *ioLine, ULONG iNb, int &oEof) ;
```

| 参数 | 类型 |
|------|------|
| *ioLine | `CATUnicodeString` |
| iNb | `ULONG` |
| &oEof | `int` |


### ReadLineWchar

```cpp
HRESULT ReadLineWchar(CATUC2Bytes *ioLine, ULONG iNb, int &oEof) ;
```

| 参数 | 类型 |
|------|------|
| *ioLine | `CATUC2Bytes` |
| iNb | `ULONG` |
| &oEof | `int` |


### WriteLineW

```cpp
HRESULT WriteLineW(const CATUnicodeString * iBuff) ;
```

| 参数 | 类型 |
|------|------|
| iBuff | `const CATUnicodeString *` |


### WriteLineWchar

```cpp
HRESULT WriteLineWchar(const CATUC2Bytes* iBuff) ;
```

| 参数 | 类型 |
|------|------|
| iBuff | `const CATUC2Bytes*` |


---

**源文件**: `CAASystem.edu/CAASysCryptedILB.m/LocalInterfaces/CAASysCryptedILB.h`
