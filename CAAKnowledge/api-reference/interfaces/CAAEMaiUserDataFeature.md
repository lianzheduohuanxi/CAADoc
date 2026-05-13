---
title: "CAAEMaiUserDataFeature"
type: "PublicInterface"
module: "CAAManufacturingItf"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAManufacturingItf.edu/PublicInterfaces/CAAEMaiUserDataFeature.h"
---

# CAAEMaiUserDataFeature

**基类**: CATBaseUnknown | **模块**: CAAManufacturingItf | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CATDlgInclude.h`

## 公共方法

### GetEditor

```cpp
HRESULT GetEditor(CATDialog *iFather, CATDlgFrame* &oEditor) ;
```

Implementation of the CATIMfgUserDataFeature interface methods

| 参数 | 类型 |
|------|------|
| *iFather | `CATDialog` |
| &oEditor | `CATDlgFrame*` |


### GetNLSDescription

```cpp
HRESULT GetNLSDescription(CATUnicodeString &oNLSDescription) ;
```

| 参数 | 类型 |
|------|------|
| &oNLSDescription | `CATUnicodeString` |


---

**源文件**: `CAAManufacturingItf.edu/PublicInterfaces/CAAEMaiUserDataFeature.h`
