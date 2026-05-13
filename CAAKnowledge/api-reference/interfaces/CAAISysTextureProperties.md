---
title: "CAAISysTextureProperties"
type: "PublicInterface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAASystem.edu/PublicInterfaces/CAAISysTextureProperties.h"
---

# CAAISysTextureProperties

> Interface to manage texture property . Usage: In the edit properties Inheritance: CATBaseUnknown (System Framework). Main Methods: GetMetal SetMetal GetRough SetRough

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

## 纯虚方法 (接口契约)

### GetMetal

```cpp
virtual HRESULT GetMetal(int & oIsMetal) = 0 ;
```

Texture properties are: A metal property ---------------- 0 : the object is not metallic 1 : the object is metallic

| 参数 | 类型 |
|------|------|
| oIsMetal | `int &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetMetal

```cpp
virtual HRESULT SetMetal(const int iIsMetal) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iIsMetal | `const int` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetRough

```cpp
virtual HRESULT GetRough(int & oIsMetal) = 0 ;
```

A Roughness property -------------------- 0 : The object is smooth 1 : The object is rough

| 参数 | 类型 |
|------|------|
| oIsMetal | `int &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetRough

```cpp
virtual HRESULT SetRough(const int iIsMetal) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iIsMetal | `const int` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAASystem.edu/PublicInterfaces/CAAISysTextureProperties.h`
