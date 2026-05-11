---
title: "CAACafTexturePropertyPageEdt"
type: "interface"
module: "CAACATIAApplicationFrm"
base: "CATEditor"
method_count: 4
visibility: "local"
verified: true
---

# CAACafTexturePropertyPageEdt

**基类**: CATEditor  
**模块**: CAACATIAApplicationFrm  
**可见性**: local  
**方法数**: 4

> System framework

## 方法列表

### GetEditorTitle
```cpp
CATUnicodeString GetEditorTitle();
```

### SetEditorSize
```cpp
void SetEditorSize(int & oSize);
```

### BuildEditor
```cpp
void BuildEditor(CATEditorPage * iEditor);
```

### CloseWindowFromEditor
```cpp
void CloseWindowFromEditor();
```

## 依赖

- `CATEditor.h`
- `CATLISTV_CATBaseUnknown.h`

