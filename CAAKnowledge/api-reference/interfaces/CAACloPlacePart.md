---
title: "CAACloPlacePart"
type: "LocalClass"
module: "CAACommonLayoutItf"
base: "CAAPspBaseEnvProtected"
method_count: 12
source_file: "CAACommonLayoutItf.edu/CAACloPlacePart.m/LocalInterfaces/CAACloPlacePart.h"
---

# CAACloPlacePart

**基类**: CAAPspBaseEnvProtected | **模块**: CAACommonLayoutItf | **方法数**: 12

## 依赖

- `CAAPspBaseEnvProtected.h`
- `CATError.h`
- `CATUnicodeString.h`

## 公共方法

### GetPartConnector

```cpp
HRESULT GetPartConnector(const IUnknown *ipiPartUnk, const int &iConnectorNumber, IUnknown *&opiPartConnector) ;
```

Get a part connector.

| 参数 | 类型 |
|------|------|
| *ipiPartUnk | `const IUnknown` |
| &iConnectorNumber | `const int` |
| *&opiPartConnector | `IUnknown` |


### GetPartConnectorData

```cpp
HRESULT GetPartConnectorData(const IUnknown *ipiPartUnk, const int &iConnectorNumber, IUnknown *ipiRelAxisUnk, CATMathPoint &oCtrPosition, CATMathDirection &oCtrAlign, CATMathDirection &oCtrUp) ;
```

Get location data for a part connector.

| 参数 | 类型 |
|------|------|
| *ipiPartUnk | `const IUnknown` |
| &iConnectorNumber | `const int` |
| *ipiRelAxisUnk | `IUnknown` |
| &oCtrPosition | `CATMathPoint` |
| &oCtrAlign | `CATMathDirection` |
| &oCtrUp | `CATMathDirection` |


### GetConnectedPart

```cpp
HRESULT GetConnectedPart(const IUnknown *ipiPartUnk, const int &iConnectorNumber, IUnknown *&opiConnectedCtr, IUnknown *&opiConnectedPart) ;
```

Get part connected to a part ctr.

| 参数 | 类型 |
|------|------|
| *ipiPartUnk | `const IUnknown` |
| &iConnectorNumber | `const int` |
| *&opiConnectedCtr | `IUnknown` |
| *&opiConnectedPart | `IUnknown` |


### TestConnectedPart

```cpp
HRESULT TestConnectedPart(const IUnknown *ipiPartUnk, const int &iConnectorNumber, const IUnknown *ipiConnectedPart, const int &iConnectedConnectorNumber) ;
```

Test location data for a part connector.

| 参数 | 类型 |
|------|------|
| *ipiPartUnk | `const IUnknown` |
| &iConnectorNumber | `const int` |
| *ipiConnectedPart | `const IUnknown` |
| &iConnectedConnectorNumber | `const int` |


### TestPartConnectorData

```cpp
HRESULT TestPartConnectorData(const IUnknown *ipiPartUnk, const int &iConnectorNumber, IUnknown *ipiRelAxisUnk, const CATMathPoint &iCtrPosition, const CATMathDirection &iCtrAlign, const CATMathDirection &iCtrUp) ;
```

Test location data for a part connector.

| 参数 | 类型 |
|------|------|
| *ipiPartUnk | `const IUnknown` |
| &iConnectorNumber | `const int` |
| *ipiRelAxisUnk | `IUnknown` |
| &iCtrPosition | `const CATMathPoint` |
| &iCtrAlign | `const CATMathDirection` |
| &iCtrUp | `const CATMathDirection` |


### PlacePartInSpace

```cpp
HRESULT PlacePartInSpace() ;
```

Place a part in space.


### RouteStringPartInSpace

```cpp
HRESULT RouteStringPartInSpace() ;
```

Route a string part in space.


### PlacePartOnRunSegment

```cpp
HRESULT PlacePartOnRunSegment() ;
```

Place a part on a run segment.


### PlacePartOnRunNode

```cpp
HRESULT PlacePartOnRunNode() ;
```

Place a part on a run node.


### PlacePartOnPartConnector

```cpp
HRESULT PlacePartOnPartConnector() ;
```

Place a part on a part conntector.


### PlacePartOnPartConnectorAndReconnectRun

```cpp
HRESULT PlacePartOnPartConnectorAndReconnectRun() ;
```

Place part on part connector and reconnect run to the placed part.


### DoSample

```cpp
HRESULT DoSample(const CATUnicodeString &iuFileToBeLoaded) ;
```

Input: iuFileToBeLoaded - path of document name to be loaded (CATProduct containing geometry, objects ...

| 参数 | 类型 |
|------|------|
| &iuFileToBeLoaded | `const CATUnicodeString` |


---

**源文件**: `CAACommonLayoutItf.edu/CAACloPlacePart.m/LocalInterfaces/CAACloPlacePart.h`
