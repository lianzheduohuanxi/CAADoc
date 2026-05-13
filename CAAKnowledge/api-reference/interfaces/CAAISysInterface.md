---
title: "CAAISysInterface"
type: "PublicInterface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAASystem.edu/PublicInterfaces/CAAISysInterface.h"
---

# CAAISysInterface

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 1

## 依赖

- `CATBaseUnknown.h`
- `CAASysInterface.h`

## 纯虚方法 (接口契约)

### ToString

```cpp
virtual HRESULT ToString() = 0 ;
```

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAASystem.edu/PublicInterfaces/CAAISysInterface.h`
