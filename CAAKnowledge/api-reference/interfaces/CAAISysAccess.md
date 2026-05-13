---
title: "CAAISysAccess"
type: "PublicInterface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAASystem.edu/PublicInterfaces/CAAISysAccess.h"
---

# CAAISysAccess

> Interface which associates a container with its objects the CAAGeometry document. Every container's object implements this interface to know its container. Inheritance: CATBaseUnknown (System Framework) Main Methods: SetContainer: Sets the container GetContainer: Retrieve the container

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

## 纯虚方法 (接口契约)

### SetContainer

```cpp
virtual HRESULT SetContainer(CATBaseUnknown * iContainer) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iContainer | `CATBaseUnknown *` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetContainer

```cpp
virtual HRESULT GetContainer(CATBaseUnknown ** oContainer) = 0 ;
```

| 参数 | 类型 |
|------|------|
| oContainer | `CATBaseUnknown **` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAASystem.edu/PublicInterfaces/CAAISysAccess.h`
