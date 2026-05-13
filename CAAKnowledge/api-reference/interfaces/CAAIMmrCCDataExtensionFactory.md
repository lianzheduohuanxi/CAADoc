---
title: "CAAIMmrCCDataExtensionFactory"
type: "PublicInterface"
module: "CAAMechanicalModeler"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAAMechanicalModeler.edu/PublicInterfaces/CAAIMmrCCDataExtensionFactory.h"
---

# CAAIMmrCCDataExtensionFactory

**基类**: CATBaseUnknown | **模块**: CAAMechanicalModeler | **方法数**: 1

## 依赖

- `CAAMmrCCDataExtension.h`
- `CATBaseUnknown.h`

## 纯虚方法 (接口契约)

### CreateMmrCCDataExtension

```cpp
virtual HRESULT CreateMmrCCDataExtension(const CATBaseUnknown *iBaseFeature, CAAIMmrCCDataExtension **ioMmrCCDataExtension) = 0 ;
```

| 参数 | 类型 |
|------|------|
| *iBaseFeature | `const CATBaseUnknown` |
| **ioMmrCCDataExtension | `CAAIMmrCCDataExtension` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAAMechanicalModeler.edu/PublicInterfaces/CAAIMmrCCDataExtensionFactory.h`
