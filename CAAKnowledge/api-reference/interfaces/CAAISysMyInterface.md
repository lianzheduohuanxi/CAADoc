---
title: "CAAISysMyInterface"
type: "PublicInterface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAASystem.edu/PublicInterfaces/CAAISysMyInterface.h"
---

# CAAISysMyInterface

> Interface which prints the content of a CAASysComponent object. Inheritance: CATBaseUnknown (System Framework)

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 1

## 依赖

- `CATBaseUnknown.h`
- `CAASysComponentInt.h`

## 纯虚方法 (接口契约)

### Print

```cpp
virtual HRESULT Print() const = 0 ;
```

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAASystem.edu/PublicInterfaces/CAAISysMyInterface.h`
