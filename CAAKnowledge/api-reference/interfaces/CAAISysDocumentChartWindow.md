---
title: "CAAISysDocumentChartWindow"
type: "PublicInterface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAASystem.edu/PublicInterfaces/CAAISysDocumentChartWindow.h"
---

# CAAISysDocumentChartWindow

> Interface which allows to create a chart window for document.

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 1

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

## 纯虚方法 (接口契约)

### CreateHistogramWindow

```cpp
virtual HRESULT CreateHistogramWindow() = 0 ;
```

CreateHistogramWindow --------------------- Create a window which contains a new representation of the Document.

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAASystem.edu/PublicInterfaces/CAAISysDocumentChartWindow.h`
