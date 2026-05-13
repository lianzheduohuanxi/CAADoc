---
title: "CAAUEUnixNtMapping"
type: "LocalClass"
module: "CAAPSNInteroperability"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAPSNInteroperability.edu/CAAPsnUEUnixNtMapping.m/LocalInterfaces/CAAUEUnixNtMapping.h"
---

# CAAUEUnixNtMapping

**基类**: CATBaseUnknown | **模块**: CAAPSNInteroperability | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CATUnicodeString.h`

## 公共方法

### UnixPathToNTPath

```cpp
HRESULT UnixPathToNTPath(CATUnicodeString iUnixPath, CATUnicodeString& oNTPath) ;
```

| 参数 | 类型 |
|------|------|
| iUnixPath | `CATUnicodeString` |
| oNTPath | `CATUnicodeString&` |


### NtPathToUnix

```cpp
HRESULT NtPathToUnix(CATUnicodeString iNTPath, CATUnicodeString& oUnixPath) ;
```

| 参数 | 类型 |
|------|------|
| iNTPath | `CATUnicodeString` |
| oUnixPath | `CATUnicodeString&` |


---

**源文件**: `CAAPSNInteroperability.edu/CAAPsnUEUnixNtMapping.m/LocalInterfaces/CAAUEUnixNtMapping.h`
