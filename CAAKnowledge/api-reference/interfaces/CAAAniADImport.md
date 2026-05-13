---
title: "CAAAniADImport"
type: "LocalClass"
module: "CAAAnalysisInterfaces"
base: "CATBaseUnknown"
method_count: 5
source_file: "CAAAnalysisInterfaces.edu/CAAAniAeroDTransition.m/LocalInterfaces/CAAAniADImport.h"
---

# CAAAniADImport

**基类**: CATBaseUnknown | **模块**: CAAAnalysisInterfaces | **方法数**: 5

## 依赖

- `CATBaseUnknown.h`
- `CATString.h`
- `CATDocument.h`
- `CATAnalysisExplicitTypes.h`

## 公共方法

### Import

```cpp
HRESULT Import(CATDocument * idocument) ;
```

| 参数 | 类型 |
|------|------|
| idocument | `CATDocument *` |


### ImportFif

```cpp
HRESULT ImportFif(CATIMSHMeshPart * ipMeshPart, CATIMSHMesh * ipMesh) ;
```

| 参数 | 类型 |
|------|------|
| ipMeshPart | `CATIMSHMeshPart *` |
| ipMesh | `CATIMSHMesh *` |


### TranslateToFieldModel

```cpp
HRESULT TranslateToFieldModel(CATISpecObject* iFeatToTranslate, CATISamAnalysisModel* ipFEMModel, CATAnalysisExplicitListUsr& iOldExplObjects, CATAnalysisExplicitListUsr& oNewExplObjects) ;
```

| 参数 | 类型 |
|------|------|
| iFeatToTranslate | `CATISpecObject*` |
| ipFEMModel | `CATISamAnalysisModel*` |
| iOldExplObjects | `CATAnalysisExplicitListUsr&` |
| oNewExplObjects | `CATAnalysisExplicitListUsr&` |


### OnRenameCB

```cpp
void OnRenameCB(CATCallbackEvent , void* , CATNotification *notif, CATSubscriberData , CATCallback) ;
```

| 参数 | 类型 |
|------|------|
|  | `CATCallbackEvent` |
|  | `void*` |
| *notif | `CATNotification` |
|  | `CATSubscriberData` |
|  | `CATCallback` |


### OnRenameCB2

```cpp
void OnRenameCB2(CATCallbackEvent , void* , CATNotification *notif, CATSubscriberData , CATCallback) ;
```

| 参数 | 类型 |
|------|------|
|  | `CATCallbackEvent` |
|  | `void*` |
| *notif | `CATNotification` |
|  | `CATSubscriberData` |
|  | `CATCallback` |


---

**源文件**: `CAAAnalysisInterfaces.edu/CAAAniAeroDTransition.m/LocalInterfaces/CAAAniADImport.h`
