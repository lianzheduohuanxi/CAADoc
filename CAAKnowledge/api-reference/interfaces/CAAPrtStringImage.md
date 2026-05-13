---
title: "CAAPrtStringImage"
type: "LocalClass"
module: "CAAPrint"
base: "CATPrintImage"
method_count: 2
source_file: "CAAPrint.edu/CAAPrtPrintableObjects.m/LocalInterfaces/CAAPrtStringImage.h"
---

# CAAPrtStringImage

> Class representing an image which draws a string surrounded by a frame composed of zigzag folded lines. Inheritance: CATPrintImage (Print Framework) CATBaseUnknown (System Framework) Main Methods: Decode: displays the image using a given generator and speficied parameters.

**基类**: CATPrintImage | **模块**: CAAPrint | **方法数**: 2

## 依赖

- `CATPrintImage.h`
- `CATUnicodeString.h`

## 公共方法

### GetSize

```cpp
int GetSize(float &oWidth, float &oHeight) ;
```

| 参数 | 类型 |
|------|------|
| &oWidth | `float` |
| &oHeight | `float` |


### Decode

```cpp
int Decode(CATPrintGenerator *iGenerator, const CATPrintParameters &iParameters) ;
```

| 参数 | 类型 |
|------|------|
| *iGenerator | `CATPrintGenerator` |
| &iParameters | `const CATPrintParameters` |


---

**源文件**: `CAAPrint.edu/CAAPrtPrintableObjects.m/LocalInterfaces/CAAPrtStringImage.h`
