---
title: "CAAAniImportDefine"
type: "LocalClass"
module: "CAAAnalysisInterfaces"
base: "CATESamImportDefineAdaptor"
method_count: 3
source_file: "CAAAnalysisInterfaces.edu/CAAAniAeroDTransition.m/LocalInterfaces/CAAAniImportDefine.h"
---

# CAAAniImportDefine

**基类**: CATESamImportDefineAdaptor | **模块**: CAAAnalysisInterfaces | **方法数**: 3

## 依赖

- `CATESamImportDefineAdaptor.h`
- `CATError.h`

## 公共方法

### GetFileTypes

```cpp
HRESULT GetFileTypes(CATListValCATString& oTypes) ;
```

CATISamImportDefine interface

| 参数 | 类型 |
|------|------|
| oTypes | `CATListValCATString&` |


### GetCommentForType

```cpp
HRESULT GetCommentForType(const CATString iType, CATUnicodeString& oComment) ;
```

| 参数 | 类型 |
|------|------|
| iType | `const CATString` |
| oComment | `CATUnicodeString&` |


### Import

```cpp
HRESULT Import(CATDocument * iImportedDoc, CATDocument * iAnalysisDoc) ;
```

| 参数 | 类型 |
|------|------|
| iImportedDoc | `CATDocument *` |
| iAnalysisDoc | `CATDocument *` |


---

**源文件**: `CAAAnalysisInterfaces.edu/CAAAniAeroDTransition.m/LocalInterfaces/CAAAniImportDefine.h`
