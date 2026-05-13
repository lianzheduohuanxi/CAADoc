---
title: "CAAMaiDumpToolPathCommand"
type: "PublicInterface"
module: "CAAManufacturingItf"
base: "CATStateCommand"
method_count: 4
source_file: "CAAManufacturingItf.edu/PublicInterfaces/CAAMaiDumpToolPathCommand.h"
---

# CAAMaiDumpToolPathCommand

> Implementation as a command Usage: Launch CATIA V5 Inside one of the Manufacturing Workbench (Prismatic Machining Programmer, for example) Select an operation with a tool path A report "DumpToolPath.txt" is created in temporary directory (by default, C:\Temp for NT, /tmp for UNIX) Inheritance: CATStateCommand (System Framework) Main Method: DumpToolPath (method called when an operation is selected)

**基类**: CATStateCommand | **模块**: CAAManufacturingItf | **方法数**: 4

## 依赖

- `CATStateCommand.h`
- `CAAMaiDumpTPEnv.h`
- `stdio.h`

## 静态方法

### CAAMaiWriteString

```cpp
static void CAAMaiWriteString(int , const CATUnicodeString&) ;
```

| 参数 | 类型 |
|------|------|
|  | `int` |
| CATUnicodeString& | `const` |


## 公共方法

### BuildGraph

```cpp
void BuildGraph() ;
```


### DumpToolPath

```cpp
CATBoolean DumpToolPath(void *) ;
```

| 参数 | 类型 |
|------|------|
| * | `void` |


### Valuate

```cpp
void Valuate(const CATBaseUnknown_var&) ;
```

| 参数 | 类型 |
|------|------|
| CATBaseUnknown_var& | `const` |


---

**源文件**: `CAAManufacturingItf.edu/PublicInterfaces/CAAMaiDumpToolPathCommand.h`
