---
title: "CAAEAfrInit"
type: "LocalClass"
module: "CAAApplicationFrame"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAApplicationFrame.edu/CAAAfrSampleDocument.m/LocalInterfaces/CAAEAfrInit.h"
---

# CAAEAfrInit

> Class which implements the CATInit interface of a new document type (CAASample) It is a data extension of a late type (CAADoc) which is the document suffix. Usage: Launch CATIA V5, File/New In the Dialog Box the new document type appears. Inheritance: CATBaseUnknown (System Framework) Main Method: Init GetRootContainer

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

**源文件**: `CAAApplicationFrame.edu/CAAAfrSampleDocument.m/LocalInterfaces/CAAEAfrInit.h`
