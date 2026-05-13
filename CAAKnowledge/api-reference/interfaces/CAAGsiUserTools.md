---
title: "CAAGsiUserTools"
type: "PublicInterface"
module: "CAAGSMInterfaces"
base: ""
method_count: 11
source_file: "CAAGSMInterfaces.edu/PublicInterfaces/CAAGsiUserTools.h"
---

# CAAGsiUserTools

**基类**: 无 | **模块**: CAAGSMInterfaces | **方法数**: 11

## 依赖

- `CATLISTV_CATISpecObject.h`
- `CATUnicodeString.h`
- `CATBoolean.h`
- `CAAGsiToolkit.h`

## 公共方法

### Init

```cpp
HRESULT Init(char *& ipSessionName) ;
```

| 参数 | 类型 |
|------|------|
| ipSessionName | `char *&` |


### InitSession

```cpp
HRESULT InitSession(char *& ipSessionName) ;
```

| 参数 | 类型 |
|------|------|
| ipSessionName | `char *&` |


### New

```cpp
HRESULT New() ;
```


### Open

```cpp
HRESULT Open(char *& ipDocName) ;
```

| 参数 | 类型 |
|------|------|
| ipDocName | `char *&` |


### Save

```cpp
HRESULT Save(char *& ipDocName) ;
```

| 参数 | 类型 |
|------|------|
| ipDocName | `char *&` |


### Close

```cpp
HRESULT Close(char *& ipSessionName) ;
```

| 参数 | 类型 |
|------|------|
| ipSessionName | `char *&` |


### InsertInProceduralView

```cpp
HRESULT InsertInProceduralView(const CATISpecObject_var& ispObjectToAppend, const CATISpecObject_var& ispInputParent=NULL_var) ;
```

| 参数 | 类型 |
|------|------|
| ispObjectToAppend | `const CATISpecObject_var&` |
| ispInputParent=NULL_var | `const CATISpecObject_var&` |


### ObjectUpdate

```cpp
HRESULT ObjectUpdate(const CATISpecObject_var & ispSpec) ;
```

| 参数 | 类型 |
|------|------|
| ispSpec | `const CATISpecObject_var &` |


### CreateLength

```cpp
HRESULT CreateLength(const char* ipNameParam, const double iValue, CATISpecObject_var &ospCkeParam) ;
```

| 参数 | 类型 |
|------|------|
| ipNameParam | `const char*` |
| iValue | `const double` |
| &ospCkeParam | `CATISpecObject_var` |


### CreateAngle

```cpp
HRESULT CreateAngle(const char* ipNameParam, const double iValue, CATISpecObject_var &ospCkeParam) ;
```

| 参数 | 类型 |
|------|------|
| ipNameParam | `const char*` |
| iValue | `const double` |
| &ospCkeParam | `CATISpecObject_var` |


### CreateReal

```cpp
HRESULT CreateReal(const char* ipNameParam, const double iValue, CATISpecObject_var &ospCkeParam) ;
```

| 参数 | 类型 |
|------|------|
| ipNameParam | `const char*` |
| iValue | `const double` |
| &ospCkeParam | `CATISpecObject_var` |


---

**源文件**: `CAAGSMInterfaces.edu/PublicInterfaces/CAAGsiUserTools.h`
