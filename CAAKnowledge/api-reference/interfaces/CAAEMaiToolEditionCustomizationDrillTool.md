---
title: "CAAEMaiToolEditionCustomizationDrillTool"
type: "interface"
module: "CAAManufacturingItf"
base: "CATBaseUnknown"
method_count: 5
visibility: "local"
verified: true
---

# CAAEMaiToolEditionCustomizationDrillTool

**基类**: CATBaseUnknown  
**模块**: CAAManufacturingItf  
**可见性**: local  
**方法数**: 5

> Dialog Framework

## 方法列表

### GetPanelEditor
```cpp
CATDlgFrame* GetPanelEditor(CATDialog    *iParent, CATDlgStyle  iStyle=CATDlgFraNoFrame,
											 const CATBoolean iEditMode=TRUE);
```

### GetMorePanelEditor
```cpp
CATDlgFrame* GetMorePanelEditor(CATDialog    *iParent, CATDlgStyle iStyle=CATDlgFraNoFrame,
											 const CATBoolean iEditMode=TRUE);
```

### GetActivityEditor
```cpp
CATDlgFrame* GetActivityEditor(CATDialog    *iParent, CATDlgStyle  iStyle=CATDlgFraNoFrame,
											 const CATBoolean iEditMode=FALSE, const CATISpecObject_var &ihSpecAct=NULL_var);
```

### GetGraphicEditor
```cpp
CATDlgFrame* GetGraphicEditor(CATDialog    *iParent, CATDlgStyle   iStyle=CATDlgFraNoFrame,
											 const CATBoolean iEditMode=FALSE);
```

### GenerateJPEGImageFromGraphicEditor
```cpp
void GenerateJPEGImageFromGraphicEditor(CATDialog             *iParent,
													 const CATUnicodeString &iImagePathName="");
```

## 依赖

- `CATDlgInclude.h`
- `CATBooleanDef.h`
- `CATListOfCATUnicodeString.h`
- `CATISpecObject.h`

