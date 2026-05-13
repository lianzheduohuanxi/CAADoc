---
title: "CAAIVisTextModel"
type: "PublicInterface"
module: "CAAVisualization"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAAVisualization.edu/PublicInterfaces/CAAIVisTextModel.h"
---

# CAAIVisTextModel

**基类**: CATBaseUnknown | **模块**: CAAVisualization | **方法数**: 1

## 依赖

- `CATBaseUnknown.h`
- `CAAVisModelForRep.h`

## 纯虚方法 (接口契约)

### SetGraphicRepresentation

```cpp
virtual HRESULT SetGraphicRepresentation(CATRep * iRep) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iRep | `CATRep *` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAVisualization.edu/PublicInterfaces/CAAIVisTextModel.h`
