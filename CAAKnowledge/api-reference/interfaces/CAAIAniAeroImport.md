---
title: "CAAIAniAeroImport"
type: "LocalClass"
module: "CAAAnalysisInterfaces"
base: "CATBaseUnknown"
method_count: 3
source_file: "CAAAnalysisInterfaces.edu/CAAAniAeroDTransition.m/LocalInterfaces/CAAIAniAeroImport.h"
---

# CAAIAniAeroImport

**基类**: CATBaseUnknown | **模块**: CAAAnalysisInterfaces | **方法数**: 3

## 依赖

- `CATBaseUnknown.h`

## 纯虚方法 (接口契约)

### Import

```cpp
virtual HRESULT Import(CATDocument * ipAnalysisDoc) = 0 ;
```

| 参数 | 类型 |
|------|------|
| ipAnalysisDoc | `CATDocument *` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### ImportFif

```cpp
virtual HRESULT ImportFif(CATIMSHMeshPart * MeshPart, CATIMSHMesh * ipMesh) = 0 ;
```

| 参数 | 类型 |
|------|------|
| MeshPart | `CATIMSHMeshPart *` |
| ipMesh | `CATIMSHMesh *` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### TranslateToFieldModel

```cpp
virtual HRESULT TranslateToFieldModel(CATISpecObject* iFeatToTranslate, CATISamAnalysisModel* iFEMModel, CATAnalysisExplicitListUsr& iOldExplObjects, CATAnalysisExplicitListUsr& oNewExplObjects) = 0 ;
```

Create the field model objects

| 参数 | 类型 |
|------|------|
| iFeatToTranslate | `CATISpecObject*` |
| iFEMModel | `CATISamAnalysisModel*` |
| iOldExplObjects | `CATAnalysisExplicitListUsr&` |
| oNewExplObjects | `CATAnalysisExplicitListUsr&` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAAnalysisInterfaces.edu/CAAAniAeroDTransition.m/LocalInterfaces/CAAIAniAeroImport.h`
