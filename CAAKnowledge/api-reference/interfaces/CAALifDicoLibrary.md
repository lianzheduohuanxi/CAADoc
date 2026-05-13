---
title: "CAALifDicoLibrary"
type: "ProtectedInterface"
module: "CAALiteralFeatures"
base: "CATBaseUnknown"
method_count: 0
source_file: "CAALiteralFeatures.edu/ProtectedInterfaces/CAALifDicoLibrary.h"
---

# CAALifDicoLibrary

> The LiteralFeatures framework allows you to create user functions. Example: Hypothenuse = SQRT(X*X + Y*Y) This user function can be used within a relation. If "Hypothenuse" has been added to the "Formulas" dictionary, the end-user can create a formula using this user function Example: Formula1: Hypothenuse(A,B)*10 To create a user function, you must: 1 -  Declare that you add a function with a given signature to the dictionary (CAALifDicoLibrary.cpp). To do this, you have to create an implementation of CATIAddLibrary. The only method to implement is CATIAddLibrary::Add No matter you create one or more user functions, only one library is required. 2 -  Provide an evaluator (CAALifEval.cpp) 3 -  Provide an implementation of CATICreateInstance (System) in an extension of the code which describes the user function (CAALifDicoLibrary) - This implemenattaion is provided in CAALifCreateExt.cpp Usage: new CAALifDicoLibrary() Add(). Inheritance: Inherits from CATBaseUnknown. Return Codes: None

**基类**: CATBaseUnknown | **模块**: CAALiteralFeatures | **方法数**: 0

## 依赖

- `CATBaseUnknown.h`

---

**源文件**: `CAALiteralFeatures.edu/ProtectedInterfaces/CAALifDicoLibrary.h`
