---
title: "CAAGobAttributeManagement"
type: "ProtectedInterface"
module: "CAAGeometricObjects"
base: "CATCGMStreamAttribute"
method_count: 4
source_file: "CAAGeometricObjects.edu/ProtectedInterfaces/CAAGobAttributeManagement.h"
---

# CAAGobAttributeManagement

**基类**: CATCGMStreamAttribute | **模块**: CAAGeometricObjects | **方法数**: 4

## 依赖

- `CAAGobAttribute.h`
- `CATCGMStreamAttribute.h`

## 公共方法

### Stream

```cpp
void Stream(CATCGMStream &) const ;
```

| 参数 | 类型 |
|------|------|
| & | `CATCGMStream` |


### UnStream

```cpp
void UnStream(CATCGMStream &) ;
```

| 参数 | 类型 |
|------|------|
| & | `CATCGMStream` |


### SetValue

```cpp
void SetValue(CATLONG32 val) ;
```

| 参数 | 类型 |
|------|------|
| val | `CATLONG32` |


### GetValue

```cpp
void GetValue(CATLONG32 & val) ;
```

| 参数 | 类型 |
|------|------|
| val | `CATLONG32 &` |


---

**源文件**: `CAAGeometricObjects.edu/ProtectedInterfaces/CAAGobAttributeManagement.h`
