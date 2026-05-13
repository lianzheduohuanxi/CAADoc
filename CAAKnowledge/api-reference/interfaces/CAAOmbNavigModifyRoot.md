---
title: "CAAOmbNavigModifyRoot"
type: "LocalClass"
module: "CAAObjectModelerBase"
base: "CATNodeExtension"
method_count: 1
source_file: "CAAObjectModelerBase.edu/CAAOmbGeoNavigate.m/LocalInterfaces/CAAOmbNavigModifyRoot.h"
---

# CAAOmbNavigModifyRoot

> This is an implementation of the CATINavigModify interface. Execute the Use Case: To execute this Use Case, you must be in a CATIA V5 session.  Create a new document of type "CAAGeometry".  Create geometric elements in the document. Select the root node "CAASysGeomRootObj":  a tree is displayed containing the names of all of the elements existing in the document. CATINavigModify::UpdateElem allows the modification of tree nodes by changing node colors using CATIGraphNode::SetColor and by adding icons to nodes using CATIGraphNode::SetPixelImage. ******************************************************************************

**基类**: CATNodeExtension | **模块**: CAAObjectModelerBase | **方法数**: 1

## 依赖

- `CATNodeExtension.h`

## 公共方法

### UpdateElem

```cpp
void UpdateElem(CATNavigInstance * iInstance) ;
```

| 参数 | 类型 |
|------|------|
| iInstance | `CATNavigInstance *` |


---

**源文件**: `CAAObjectModelerBase.edu/CAAOmbGeoNavigate.m/LocalInterfaces/CAAOmbNavigModifyRoot.h`
