---
title: "CAAEMaiMacroAccess"
type: "PublicInterface"
module: "CAAManufacturingItf"
base: ""
method_count: 2
source_file: "CAAManufacturingItf.edu/PublicInterfaces/CAAEMaiMacroAccess.h"
---

# CAAEMaiMacroAccess

**基类**: 无 | **模块**: CAAManufacturingItf | **方法数**: 2

## 依赖

- `CAAMaiMacroEnv.h`
- `CATIMfgActivityMacroMotion.h`
- `CATIMfgActivity.h`

## 公共方法

### GetMacroDatas

```cpp
HRESULT GetMacroDatas() ;
```

This method is a sample  of CAA macro Interfaces use.


### ReadElementaryMotionDatas

```cpp
HRESULT ReadElementaryMotionDatas(const int &iTypeMacro, CATIMfgActivityMacroMotion_var& MacroMotion) ;
```

This method is a sample  of CAA macro Interfaces use on each kind of macro elementary motion.

| 参数 | 类型 |
|------|------|
| &iTypeMacro | `const int` |
| MacroMotion | `CATIMfgActivityMacroMotion_var&` |


---

**源文件**: `CAAManufacturingItf.edu/PublicInterfaces/CAAEMaiMacroAccess.h`
