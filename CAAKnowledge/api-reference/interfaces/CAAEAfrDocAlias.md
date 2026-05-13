---
title: "CAAEAfrDocAlias"
type: "LocalClass"
module: "CAAApplicationFrame"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAAApplicationFrame.edu/CAAAfrSampleDocument.m/LocalInterfaces/CAAEAfrDocAlias.h"
---

# CAAEAfrDocAlias

> Abstract: Class which implements the CATIDocAlias interface for the CAASample document. It's a data extension of a late type (CAASample) which is the Document identifier that is shown is the File->New dialog box. It returns the document suffix. This suffix is also used as late type to implement other interfaces for the document (CATInit, CATIEditor, CATIDocumentEdit). Therefore, this document is represented by two components: the first one whose late type is CAASample (the document name) the second one whose late type is CAADoc (the suffix) Illustrates Implementation of CATIDocAlias on a document. Inheritance: CATBaseUnknown (System Framework). Main Method: GiveDocSuffix System Framework

**基类**: CATBaseUnknown | **模块**: CAAApplicationFrame | **方法数**: 1

## 依赖

- `CATBaseUnknown.h`

## 公共方法

### GiveDocSuffix

```cpp
CATUnicodeString GiveDocSuffix() ;
```


---

**源文件**: `CAAApplicationFrame.edu/CAAAfrSampleDocument.m/LocalInterfaces/CAAEAfrDocAlias.h`
