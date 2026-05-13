---
title: "CAAVisBaseDocument"
type: "LocalClass"
module: "CAAVisualization"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAVisualization.edu/CAAVisBasics.m/LocalInterfaces/CAAVisBaseDocument.h"
---

# CAAVisBaseDocument

> Document base class. Each document of our application inherits from CAAVisBaseDocument. The documents are created by the application (CAAVisBaseApplication). Each document has an associated view (CAAVisBaseView) to graphically display its data. The main role of the document is to manage our model, which is a tree of CATRep objects, stored as a CAT3DBagRep * _pRootContainer data member. Inheritance: CAAVisBaseDocument CATBaseUnknown (System Framework) Main Method: CreateDocView : Creates the document view (CAAVisBaseView). DeleteDocView : Deletes the document view. CreateModel   : Creates the model, which is in fact a graphical representation, that will be visualized in the view. DeleteModel   : Deallocates resources used for the model. AddRepToViewer: Adds our graphical representation to the viewer. This method allows our model to be represented in the view.

**基类**: CATBaseUnknown | **模块**: CAAVisualization | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`

## 虚方法

### GetView

```cpp
virtual CAAVisBaseView * GetView() ;
```

Gets the view associated to the document. There is only one view per document.


### InsertModel

```cpp
virtual void InsertModel(const char *iCGRFileName) ;
```

Inserts a graphical representation read from a CGR file into the model.

| 参数 | 类型 |
|------|------|
| *iCGRFileName | `const char` |


---

**源文件**: `CAAVisualization.edu/CAAVisBasics.m/LocalInterfaces/CAAVisBaseDocument.h`
