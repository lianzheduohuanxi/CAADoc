---
title: "CAASysSymetricProvider"
type: "ProtectedInterface"
module: "CAAxPDMInterfaces"
base: ""
method_count: 3
source_file: "CAAxPDMInterfaces.edu/ProtectedInterfaces/CAASysDRMCtrl.h"
---

# CAASysSymetricProvider

**基类**: 无 | **模块**: CAAxPDMInterfaces | **方法数**: 3

## 依赖

- `CATWTypes.h`

## 公共方法

### InitProvider

```cpp
HRESULT InitProvider(Mode mode, Direction dir, unsigned char * key, size_t KeyLen) ;
```

| 参数 | 类型 |
|------|------|
| mode | `Mode` |
| dir | `Direction` |
| key | `unsigned char *` |
| KeyLen | `size_t` |


### Encrypt

```cpp
HRESULT Encrypt(void *iPT, size_t iPTLen, void *ioCT, size_t &oCTLen) ;
```

| 参数 | 类型 |
|------|------|
| *iPT | `void` |
| iPTLen | `size_t` |
| *ioCT | `void` |
| &oCTLen | `size_t` |


### Decrypt

```cpp
HRESULT Decrypt(void *iCT, size_t iCTLen, void *ioPT, size_t &oPTLen) ;
```

| 参数 | 类型 |
|------|------|
| *iCT | `void` |
| iCTLen | `size_t` |
| *ioPT | `void` |
| &oPTLen | `size_t` |


---

**源文件**: `CAAxPDMInterfaces.edu/ProtectedInterfaces/CAASysDRMCtrl.h`
