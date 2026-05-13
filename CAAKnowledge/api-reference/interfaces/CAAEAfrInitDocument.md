---
title: "CAAEAfrInitDocument"
type: "LocalClass"
module: "CAAApplicationFrame"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAApplicationFrame.edu/CAAAfrGeoDocument.m/LocalInterfaces/CAAEAfrInitDocument.h"
---

# CAAEAfrInitDocument

> Data extension of the CAAGeom Late Type. Usage: Launch CATIA V5, File/New In the Dialog Box the new document type appears. Inheritance: CATBaseUnknown (System Framework) Main Method: Init GetRootContainer

**基类**: CATBaseUnknown | **模块**: CAAApplicationFrame | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CATBoolean.h`

## 虚方法

### GetRootContainer

```cpp
virtual CATBaseUnknown * GetRootContainer(const CATIdent interfaceID) ;
```

| 参数 | 类型 |
|------|------|
| interfaceID | `const CATIdent` |


## 公共方法

### Init

```cpp
void Init(CATBoolean iDestroyExistingData) ;
```

| 参数 | 类型 |
|------|------|
| iDestroyExistingData | `CATBoolean` |


---

**源文件**: `CAAApplicationFrame.edu/CAAAfrGeoDocument.m/LocalInterfaces/CAAEAfrInitDocument.h`
