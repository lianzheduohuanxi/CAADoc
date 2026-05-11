---
title: "CAAIAniAeroImport"
type: "interface"
module: "CAAAnalysisInterfaces"
base: "CATBaseUnknown"
method_count: 3
verified: true
---

# CAAIAniAeroImport

**基类**: CATBaseUnknown  
**模块**: CAAAnalysisInterfaces  
**方法数**: 3

## 方法列表

### Import
```cpp
HRESULT Import(CATDocument * ipAnalysisDoc);
```

### ImportFif
```cpp
HRESULT ImportFif(CATIMSHMeshPart * MeshPart,CATIMSHMesh * ipMesh);
```

### TranslateToFieldModel
```cpp
HRESULT TranslateToFieldModel(CATISpecObject* iFeatToTranslate, 
                                          CATISamAnalysisModel* iFEMModel, 
                                          CATAnalysisExplicitListUsr& iOldExplObjects, 
                                          CATAnalysisExplicitListUsr& oNewExplObjects);
```

