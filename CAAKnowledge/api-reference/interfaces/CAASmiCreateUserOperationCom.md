---
title: "CAASmiCreateUserOperationCom"
type: "ProtectedInterface"
module: "CAASurfaceMachiningItf"
base: "CATStateCommand"
method_count: 5
source_file: "CAASurfaceMachiningItf.edu/ProtectedInterfaces/CAASmiCreateUserOperationCom.h"
---

# CAASmiCreateUserOperationCom

**基类**: CATStateCommand | **模块**: CAASurfaceMachiningItf | **方法数**: 5

## 依赖

- `CAASmiUserOperationCmdEnv.h`
- `CATStateCommand.h`
- `CATBoolean.h`

## 虚方法

### BuildGraph

```cpp
virtual void BuildGraph() ;
```

Builds the command statechart.


## 公共方法

### CreateActivity

```cpp
CATBoolean CreateActivity(void *) ;
```

| 参数 | 类型 |
|------|------|
| * | `void` |


### SetLinksAndDataOnActivity

```cpp
HRESULT SetLinksAndDataOnActivity() ;
```

To Initialize the activity


### InitTool

```cpp
HRESULT InitTool() ;
```


### SetCompatibleToolingFromDocument

```cpp
HRESULT SetCompatibleToolingFromDocument(const CATListOfCATUnicodeString &iToolTypeList, CATBaseUnknown_var& oTool) ;
```

| 参数 | 类型 |
|------|------|
| &iToolTypeList | `const CATListOfCATUnicodeString` |
| oTool | `CATBaseUnknown_var&` |


---

**源文件**: `CAASurfaceMachiningItf.edu/ProtectedInterfaces/CAASmiCreateUserOperationCom.h`
