---
title: "CAAPrtPrintableString"
type: "LocalClass"
module: "CAAPrint"
base: "CATBaseUnknown"
method_count: 0
source_file: "CAAPrint.edu/CAAPrtPrintableObjects.m/LocalInterfaces/CAAPrtPrintableString.h"
---

# CAAPrtPrintableString

> Printable object whose image is composed of a frame surrounding a string specified as an argument of the object's constructor. The print dialog needs a printable object as an argument of its constructor, that is to say an object which implements the CATIPrintable interface. The only method of this interface is CreatePrintableImage which returns the image to print. The image could have implementes the CATIPrintable interface itself as it is done in the "test image" sample in the same module. But the current solution is useful when an existing component needs to become printable. In this case, the component implements the CATIPrintable interface in its implementation or in a data extension. For example, if CATUnicodeString had been a component (CATUnicodeString does not derive from CATBaseUnknown), CATIPrintable could have been implemented in a data extension. Inheritance: CATBaseUnknown (System Framework) Main Method: CreatePrintableImage: returns the image representing the string given as an  argument of the constructor.

**基类**: CATBaseUnknown | **模块**: CAAPrint | **方法数**: 0

## 依赖

- `CATBaseUnknown.h`
- `CATUnicodeString.h`

---

**源文件**: `CAAPrint.edu/CAAPrtPrintableObjects.m/LocalInterfaces/CAAPrtPrintableString.h`
