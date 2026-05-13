---
title: "CAAESysTextureProperties"
type: "LocalClass"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysTextureProperties.h"
---

# CAAESysTextureProperties

> Data extension implementing the CAAITextureProperties interface. Inheritance: CATBaseUnknown (System Framework)

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`

## 虚方法

### GetMetal

```cpp
virtual HRESULT GetMetal(int & oIsMetal) ;
```

Texture properties are: A metal property ---------------- 0 : the object is not metallic 1 : the object is metallic

| 参数 | 类型 |
|------|------|
| oIsMetal | `int &` |


### SetMetal

```cpp
virtual HRESULT SetMetal(const int iIsMetal) ;
```

| 参数 | 类型 |
|------|------|
| iIsMetal | `const int` |


### GetRough

```cpp
virtual HRESULT GetRough(int & oIsRough) ;
```

A Roughness property -------------------- 0 : The object is smooth 1 : The object is rough

| 参数 | 类型 |
|------|------|
| oIsRough | `int &` |


### SetRough

```cpp
virtual HRESULT SetRough(const int iIsRough) ;
```

| 参数 | 类型 |
|------|------|
| iIsRough | `const int` |


---

**源文件**: `CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysTextureProperties.h`
