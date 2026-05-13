---
title: "CAAECafGeoDocument"
type: "LocalClass"
module: "CAACATIAApplicationFrm"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAACATIAApplicationFrm.edu/CAACafGeoDocument.m/LocalInterfaces/CAAECafGeoDocument.h"
---

# CAAECafGeoDocument

> Class which implements a new document type (CAAGeometry) It is a data extension of a late type (CAAGeomety) representing the document type. In this document, the document identifier equals the document suffix (CAAGeometry). So all these interfaces are implemented by a data extension of the same late type (CAAGeometry). Illustrates: implementation of the following interfaces to create a new document CATIDocAlias CATIEditor CATIDocumentEdit CATInit CATIDocAlias and CATIEditor are implemented in CAAApplicationFrame.edu Usage: Launch CATIA V5, File/New In the Dialog Box the new document type appears. Inheritance: CATBaseUnknown (System Framework) Main Method: CreateDefaultWindow GetActiveObject Activate Deactivate MemoryDraw

**基类**: CATBaseUnknown | **模块**: CAACATIAApplicationFrm | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CATPathElement.h`

## 公共方法

### Activate

```cpp
void Activate() ;
```


### Deactivate

```cpp
void Deactivate() ;
```


---

**源文件**: `CAACATIAApplicationFrm.edu/CAACafGeoDocument.m/LocalInterfaces/CAAECafGeoDocument.h`
