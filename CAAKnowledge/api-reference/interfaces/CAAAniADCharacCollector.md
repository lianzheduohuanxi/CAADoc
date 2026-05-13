---
title: "CAAAniADCharacCollector"
type: "LocalClass"
module: "CAAAnalysisInterfaces"
base: "CATECharacCollector"
method_count: 8
source_file: "CAAAnalysisInterfaces.edu/CAAAniAeroDTransition.m/LocalInterfaces/CAAAniADCharacCollector.h"
---

# CAAAniADCharacCollector

**基类**: CATECharacCollector | **模块**: CAAAnalysisInterfaces | **方法数**: 8

## 依赖

- `CATECharacCollector.h`
- `CATAnalysisExplicitModel.h`
- `CATAnalysisExplicitTypes.h`
- `CATAnalysisCharacCollector.h`
- `CATSamCharacVersion.h`
- `CATAnalysisExplicitSet.h`
- `CATSamDimension.h`

## 公共方法

### GetAvailablePhysicalTypes

```cpp
HRESULT GetAvailablePhysicalTypes(int & oNumber, const CATSamPhysicalType* & oPhysicalTypes, const CATString* & oUnits) ;
```

| 参数 | 类型 |
|------|------|
| oNumber | `int &` |
| oPhysicalTypes | `const CATSamPhysicalType* &` |
| oUnits | `const CATString* &` |


### GetAvailableVersions

```cpp
HRESULT GetAvailableVersions(const CATSamPhysicalType iPhysicalType, int & oNumber, const CATSamCharacVersion* & oVersions) ;
```

| 参数 | 类型 |
|------|------|
| iPhysicalType | `const CATSamPhysicalType` |
| oNumber | `int &` |
| oVersions | `const CATSamCharacVersion* &` |


### GetAvailablePositions

```cpp
HRESULT GetAvailablePositions(const CATSamPhysicalType iPhysicalType, const CATSamCharacVersion & iVersion, int & oNumber, const CATString* & oPositions) ;
```

| 参数 | 类型 |
|------|------|
| iPhysicalType | `const CATSamPhysicalType` |
| iVersion | `const CATSamCharacVersion &` |
| oNumber | `int &` |
| oPositions | `const CATString* &` |


### GetNumberOfOccurrences

```cpp
HRESULT GetNumberOfOccurrences(int & oNumberOfOccurrences) ;
```

| 参数 | 类型 |
|------|------|
| oNumberOfOccurrences | `int &` |


### GetCurrentOccurrence

```cpp
HRESULT GetCurrentOccurrence(int & oOccurrenceNumber) ;
```

| 参数 | 类型 |
|------|------|
| oOccurrenceNumber | `int &` |


### SetCurrentOccurrence

```cpp
HRESULT SetCurrentOccurrence(const int iOccurrenceNumber) ;
```

| 参数 | 类型 |
|------|------|
| iOccurrenceNumber | `const int` |


### GetCharacCollector

```cpp
HRESULT GetCharacCollector(const CATSamPhysicalType iPhysicalType, const CATSamCharacVersion & iVersion, const CATString & iPosition, const char* const iEntityFlags, const CATAnalysisCharacCollector* & oCharacCollector, const CATBoolean iCollectValues = TRUE, const CATSamPhysicalType iEntiyPhysicalTypeToCollect = CATSamPhysicalTypeNone) ;
```

| 参数 | 类型 |
|------|------|
| iPhysicalType | `const CATSamPhysicalType` |
| iVersion | `const CATSamCharacVersion &` |
| iPosition | `const CATString &` |
| iEntityFlags | `const char* const` |
| oCharacCollector | `const CATAnalysisCharacCollector* &` |
| TRUE | `const CATBoolean iCollectValues =` |
| CATSamPhysicalTypeNone | `const CATSamPhysicalType iEntiyPhysicalTypeToCollect =` |


### Update

```cpp
HRESULT Update(CATBoolean iFullUpdate = TRUE) ;
```

| 参数 | 类型 |
|------|------|
| TRUE | `CATBoolean iFullUpdate =` |


---

**源文件**: `CAAAnalysisInterfaces.edu/CAAAniAeroDTransition.m/LocalInterfaces/CAAAniADCharacCollector.h`
