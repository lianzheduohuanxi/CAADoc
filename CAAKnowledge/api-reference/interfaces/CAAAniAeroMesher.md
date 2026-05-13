---
title: "CAAAniAeroMesher"
type: "LocalClass"
module: "CAAAnalysisInterfaces"
base: "CATMSHExtIMesher"
method_count: 3
source_file: "CAAAnalysisInterfaces.edu/CAAAniAeroDTransition.m/LocalInterfaces/CAAAniAeroMesher.h"
---

# CAAAniAeroMesher

**基类**: CATMSHExtIMesher | **模块**: CAAAnalysisInterfaces | **方法数**: 3

## 依赖

- `CATMSHExtIMesher.h`

## 公共方法

### IsATypeOf

```cpp
int IsATypeOf(CATIMSHMeshPart * iMeshPart, const CATUnicodeString &iType) ;
```

| 参数 | 类型 |
|------|------|
| iMeshPart | `CATIMSHMeshPart *` |
| &iType | `const CATUnicodeString` |


### CheckSupport

```cpp
HRESULT CheckSupport(CATIMSHMeshPart * iMeshPart, int &oNbParents, CATIMSHMeshPart ** &oParentMeshParts) ;
```

| 参数 | 类型 |
|------|------|
| iMeshPart | `CATIMSHMeshPart *` |
| &oNbParents | `int` |
| &oParentMeshParts | `CATIMSHMeshPart **` |


### Mesh

```cpp
HRESULT Mesh(CATIMSHMeshPart * iMeshPart) ;
```

| 参数 | 类型 |
|------|------|
| iMeshPart | `CATIMSHMeshPart *` |


---

**源文件**: `CAAAnalysisInterfaces.edu/CAAAniAeroDTransition.m/LocalInterfaces/CAAAniAeroMesher.h`
