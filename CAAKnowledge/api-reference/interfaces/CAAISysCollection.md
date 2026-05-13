---
title: "CAAISysCollection"
type: "PublicInterface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 5
source_file: "CAASystem.edu/PublicInterfaces/CAAISysCollection.h"
---

# CAAISysCollection

> Interface which enables to manages the list of objects of the container in the CAAGeometry Document. Inheritance: CATBaseUnknown (System Framework) Main Method: GetNumberOfObjects GetObject AddObject RemoveObject

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 5

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

## 纯虚方法 (接口契约)

### GetNumberOfObjects

```cpp
virtual HRESULT GetNumberOfObjects(int * oCount) = 0 ;
```

| 参数 | 类型 |
|------|------|
| oCount | `int *` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetObject

```cpp
virtual HRESULT GetObject(int iRank, CATBaseUnknown ** oObject) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iRank | `int` |
| oObject | `CATBaseUnknown **` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### AddObject

```cpp
virtual HRESULT AddObject(CATBaseUnknown * iObject) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iObject | `CATBaseUnknown *` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### RemoveObject

```cpp
virtual HRESULT RemoveObject(CATBaseUnknown * iObject) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iObject | `CATBaseUnknown *` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### Empty

```cpp
virtual HRESULT Empty() = 0 ;
```

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAASystem.edu/PublicInterfaces/CAAISysCollection.h`
