---
title: "CAAMfgProcessTableNewColumn"
type: "LocalClass"
module: "CAAManufacturingItf"
base: "CATIMfgTabularViewColumn"
method_count: 5
source_file: "CAAManufacturingItf.edu/CAAMaiProcessTableNewColumn.m/LocalInterfaces/CAAMfgProcessTableNewColumn.h"
---

# CAAMfgProcessTableNewColumn

**基类**: CATIMfgTabularViewColumn | **模块**: CAAManufacturingItf | **方法数**: 5

## 依赖

- `CATIMfgTabularViewColumn.h`
- `CATString.h`
- `CATUnicodeString.h`
- `CATListOfCATString.h`
- `CATListOfCATUnicodeString.h`

## 公共方法

### GetListColumnId

```cpp
HRESULT GetListColumnId(CATListOfCATString& oListColumnId) ;
```

| 参数 | 类型 |
|------|------|
| oListColumnId | `CATListOfCATString&` |


### GetListTitleColumn

```cpp
HRESULT GetListTitleColumn(CATListOfCATUnicodeString& oListTitle) ;
```

| 参数 | 类型 |
|------|------|
| oListTitle | `CATListOfCATUnicodeString&` |


### GetParamCke

```cpp
HRESULT GetParamCke(const CATBaseUnknown_var& ispBUActivity, const CATString& iColumnId, CATBaseUnknown_var& ospBUCkeParm, int& MultiMod) ;
```

| 参数 | 类型 |
|------|------|
| ispBUActivity | `const CATBaseUnknown_var&` |
| iColumnId | `const CATString&` |
| ospBUCkeParm | `CATBaseUnknown_var&` |
| MultiMod | `int&` |


### GetValue

```cpp
HRESULT GetValue(const CATBaseUnknown_var& ispBUActivity, const CATString& iColumnId, CATUnicodeString& ostrValue) ;
```

| 参数 | 类型 |
|------|------|
| ispBUActivity | `const CATBaseUnknown_var&` |
| iColumnId | `const CATString&` |
| ostrValue | `CATUnicodeString&` |


### ResetCache

```cpp
HRESULT ResetCache(const int iCacheID) ;
```

| 参数 | 类型 |
|------|------|
| iCacheID | `const int` |


---

**源文件**: `CAAManufacturingItf.edu/CAAMaiProcessTableNewColumn.m/LocalInterfaces/CAAMfgProcessTableNewColumn.h`
