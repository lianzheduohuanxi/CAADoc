---
title: "CAAE5iUEDocumentName"
type: "LocalClass"
module: "CAAProductStructureE5i"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAProductStructureE5i.edu/CAAE5iUEDocumentName.m/LocalInterfaces/CAAE5iUEDocumentName.h"
---

# CAAE5iUEDocumentName

**基类**: CATBaseUnknown | **模块**: CAAProductStructureE5i | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`

## 公共方法

### ComputeDocumentName

```cpp
HRESULT ComputeDocumentName(CATUnicodeString &iDocumentDomain, CATUnicodeString &iDocumentV_ID, CATUnicodeString &iDocumentV_version, CATUnicodeString &iDocumentV_extension, CATUnicodeString &iPartV_ID, CATUnicodeString &iPartV_version, CATUnicodeString &oDocumentName) ;
```

| 参数 | 类型 |
|------|------|
| &iDocumentDomain | `CATUnicodeString` |
| &iDocumentV_ID | `CATUnicodeString` |
| &iDocumentV_version | `CATUnicodeString` |
| &iDocumentV_extension | `CATUnicodeString` |
| &iPartV_ID | `CATUnicodeString` |
| &iPartV_version | `CATUnicodeString` |
| &oDocumentName | `CATUnicodeString` |


### ComputeDocumentName

```cpp
HRESULT ComputeDocumentName(CATDocument *iDocument, CATUnicodeString & oDocumentName) ;
```

| 参数 | 类型 |
|------|------|
| *iDocument | `CATDocument` |
| oDocumentName | `CATUnicodeString &` |


---

**源文件**: `CAAProductStructureE5i.edu/CAAE5iUEDocumentName.m/LocalInterfaces/CAAE5iUEDocumentName.h`
