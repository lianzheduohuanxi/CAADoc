---
title: "CAAEMaiUserToolDatabaseCustomization"
type: "LocalClass"
module: "CAAManufacturingItf"
base: "CATBaseUnknown"
method_count: 19
source_file: "CAAManufacturingItf.edu/CAAMaiUserToolDatabaseCustomization.m/LocalInterfaces/CAAEMaiUserToolDatabaseCustomization.h"
---

# CAAEMaiUserToolDatabaseCustomization

**基类**: CATBaseUnknown | **模块**: CAAManufacturingItf | **方法数**: 19

## 依赖

- `CATBaseUnknown.h`
- `CATListOfInt.h`
- `CATListOfDouble.h`
- `CATListOfCATUnicodeString.h`
- `CATUnicodeString.h`
- `CATIDocId.h`
- `CATIMfgResourceQuery.h`
- `CATBaseUnknown.h`

## 虚方法

### InitConnection

```cpp
virtual HRESULT InitConnection() ;
```

This method allows to make connection to the database


### ResetConnection

```cpp
virtual HRESULT ResetConnection() ;
```

This method allows to reset connection to the database


### GetNamesToDisplay

```cpp
virtual HRESULT GetNamesToDisplay(CATListOfCATUnicodeString &oListNames) ;
```

This method allows to define the names that will be displayed in the Tool Selection panel combo "Look in"

| 参数 | 类型 |
|------|------|
| &oListNames | `CATListOfCATUnicodeString` |


### Initialize

```cpp
virtual HRESULT Initialize(const CATUnicodeString &iName, const CATUnicodeString &iType) ;
```

This method allows to initialize the database query

| 参数 | 类型 |
|------|------|
| &iName | `const CATUnicodeString` |
| &iType | `const CATUnicodeString` |


### AddSubComponentTypeConstraint

```cpp
virtual HRESULT AddSubComponentTypeConstraint(CATIMfgResourceQuery::MfgResourceQueryType iResourceType, const CATUnicodeString &iFamily) ;
```

| 参数 | 类型 |
|------|------|
| iResourceType | `CATIMfgResourceQuery::MfgResourceQueryType` |
| &iFamily | `const CATUnicodeString` |


### AddNameLikeConstraint

```cpp
virtual HRESULT AddNameLikeConstraint(const CATUnicodeString &iValue, CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent) ;
```

This method allows to add a constraint on the name of the tool to search A like condition will be defined (ex: search tool where name like %ID%)

| 参数 | 类型 |
|------|------|
| &iValue | `const CATUnicodeString` |
| iResourceType=CATIMfgResourceQuery::MfgCurrent | `CATIMfgResourceQuery::MfgResourceQueryType` |


### AddDiameterBetweenConstraint

```cpp
virtual HRESULT AddDiameterBetweenConstraint(const double &iMinValue, const double &iMaxValue, const CATUnicodeString &iUnit, CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent) ;
```

This method allows to add a constraint on the nominal diameter of the tool to search. A between condition will be defined (ex: search tool where nominal diameter between 10.0mm and 15.0mm)

| 参数 | 类型 |
|------|------|
| &iMinValue | `const double` |
| &iMaxValue | `const double` |
| &iUnit | `const CATUnicodeString` |
| iResourceType=CATIMfgResourceQuery::MfgCurrent | `CATIMfgResourceQuery::MfgResourceQueryType` |


### AddConstraint

```cpp
virtual HRESULT AddConstraint(const CATUnicodeString &iAttribute, const int &iOperator, const int &iValue, CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent) ;
```

This method allows to add a constraint on the integer type parameters on the tool to search. Legal values for iOperator: 0:Equal 1:Not Equal 2:Less 3:Greater 4:Less or Equal 5:Greater Or Equal 6:Not Less 7:Not Greater (ex: search tool where number of flutes = 5)

| 参数 | 类型 |
|------|------|
| &iAttribute | `const CATUnicodeString` |
| &iOperator | `const int` |
| &iValue | `const int` |
| iResourceType=CATIMfgResourceQuery::MfgCurrent | `CATIMfgResourceQuery::MfgResourceQueryType` |


### AddConstraint

```cpp
virtual HRESULT AddConstraint(const CATUnicodeString &iAttribute, const int &iOperator, const double &iValue, const CATUnicodeString &iUnit, CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent) ;
```

This method allows to add a constraint on the integer type parameters on the tool to search. Legal values for iOperator: 0:Equal 1:Not Equal 2:Less 3:Greater 4:Less or Equal 5:Greater Or Equal 6:Not Less 7:Not Greater (ex: search tool where number of flutes = 5)

| 参数 | 类型 |
|------|------|
| &iAttribute | `const CATUnicodeString` |
| &iOperator | `const int` |
| &iValue | `const double` |
| &iUnit | `const CATUnicodeString` |
| iResourceType=CATIMfgResourceQuery::MfgCurrent | `CATIMfgResourceQuery::MfgResourceQueryType` |


### AddConstraint

```cpp
virtual HRESULT AddConstraint(const CATUnicodeString &iAttribute, const int &iOperator, const CATUnicodeString &iValue, CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent) ;
```

This method allows to add a constraint on the integer type parameters on the tool to search. Legal values for iOperator: 0:Equal 1:Not Equal 2:Less 3:Greater 4:Less or Equal 5:Greater Or Equal 6:Not Less 7:Not Greater (ex: search tool where number of flutes = 5)

| 参数 | 类型 |
|------|------|
| &iAttribute | `const CATUnicodeString` |
| &iOperator | `const int` |
| &iValue | `const CATUnicodeString` |
| iResourceType=CATIMfgResourceQuery::MfgCurrent | `CATIMfgResourceQuery::MfgResourceQueryType` |


### AddConstraints

```cpp
virtual HRESULT AddConstraints(const CATUnicodeString &iAttribute, const CATUnicodeString &iUnit, const int &iTypeValue, const CATListOfInt &iOperators, const CATListOfInt &iIntValues, const CATListOfDouble &iDblValues, const CATListOfCATUnicodeString &iStrValues, const CATListOfInt &iLogLinks, CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent) ;
```

This method allows to add several constraints on the tool to search. Defines several constraints for query on a specific attribute. (ex: search tool where nominal diameter == 10.0mm or nominal diameter == 15.00mm)

| 参数 | 类型 |
|------|------|
| &iAttribute | `const CATUnicodeString` |
| &iUnit | `const CATUnicodeString` |
| &iTypeValue | `const int` |
| &iOperators | `const CATListOfInt` |
| &iIntValues | `const CATListOfInt` |
| &iDblValues | `const CATListOfDouble` |
| &iStrValues | `const CATListOfCATUnicodeString` |
| &iLogLinks | `const CATListOfInt` |
| iResourceType=CATIMfgResourceQuery::MfgCurrent | `CATIMfgResourceQuery::MfgResourceQueryType` |


### Execute

```cpp
virtual HRESULT Execute() ;
```

This method allows to execute the query in database


### GetResultSize

```cpp
virtual HRESULT GetResultSize(int &NbElem, CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent) ;
```

This method allows to read the number of tools matching the query

| 参数 | 类型 |
|------|------|
| &NbElem | `int` |
| iResourceType=CATIMfgResourceQuery::MfgCurrent | `CATIMfgResourceQuery::MfgResourceQueryType` |


### GetDescription

```cpp
virtual HRESULT GetDescription(const int &iElem, CATListOfCATUnicodeString &oAttributes, CATListOfInt &oTypeValues, CATListOfInt &oNbValues, CATListOfInt &oIntValues, CATListOfDouble &DblValues, CATListOfCATUnicodeString &StrValues, CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent) ;
```

This method allows to read the description of a given record in database

| 参数 | 类型 |
|------|------|
| &iElem | `const int` |
| &oAttributes | `CATListOfCATUnicodeString` |
| &oTypeValues | `CATListOfInt` |
| &oNbValues | `CATListOfInt` |
| &oIntValues | `CATListOfInt` |
| &DblValues | `CATListOfDouble` |
| &StrValues | `CATListOfCATUnicodeString` |
| iResourceType=CATIMfgResourceQuery::MfgCurrent | `CATIMfgResourceQuery::MfgResourceQueryType` |


### GetComponentNameAndIndex

```cpp
virtual HRESULT GetComponentNameAndIndex(const int &iNumElem, CATUnicodeString &oCompName, int &oCompNumElem, CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent) ;
```

| 参数 | 类型 |
|------|------|
| &iNumElem | `const int` |
| &oCompName | `CATUnicodeString` |
| &oCompNumElem | `int` |
| iResourceType=CATIMfgResourceQuery::MfgCurrent | `CATIMfgResourceQuery::MfgResourceQueryType` |


### GetRepresentation

```cpp
virtual HRESULT GetRepresentation(const int &iElem, CATUnicodeString &oPathName, CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent) ;
```

This method allows to read the representaion of a given tool in database

| 参数 | 类型 |
|------|------|
| &iElem | `const int` |
| &oPathName | `CATUnicodeString` |
| iResourceType=CATIMfgResourceQuery::MfgCurrent | `CATIMfgResourceQuery::MfgResourceQueryType` |


### GetRepresentation

```cpp
virtual HRESULT GetRepresentation(const int &iElem, CATIDocId *&oDocId, CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent) ;
```

This method allows to read the representaion of a given tool in database

| 参数 | 类型 |
|------|------|
| &iElem | `const int` |
| *&oDocId | `CATIDocId` |
| iResourceType=CATIMfgResourceQuery::MfgCurrent | `CATIMfgResourceQuery::MfgResourceQueryType` |


### GetCorrectors

```cpp
virtual HRESULT GetCorrectors(const int &iElem, CATListOfCATUnicodeString &oListPoints, CATListOfInt &oListNumber, CATListOfInt &oListLengthNumber, CATListOfInt &oListRadiusNumber, CATListOfDouble &oListDiameter, CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent) ;
```

| 参数 | 类型 |
|------|------|
| &iElem | `const int` |
| &oListPoints | `CATListOfCATUnicodeString` |
| &oListNumber | `CATListOfInt` |
| &oListLengthNumber | `CATListOfInt` |
| &oListRadiusNumber | `CATListOfInt` |
| &oListDiameter | `CATListOfDouble` |
| iResourceType=CATIMfgResourceQuery::MfgCurrent | `CATIMfgResourceQuery::MfgResourceQueryType` |


### InstantiateResourceInDocument

```cpp
virtual HRESULT InstantiateResourceInDocument(const int &iElem, CATBaseUnknown_var &hBUResources, CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent, CATDocument *piDoc = NULL) ;
```

| 参数 | 类型 |
|------|------|
| &iElem | `const int` |
| &hBUResources | `CATBaseUnknown_var` |
| iResourceType=CATIMfgResourceQuery::MfgCurrent | `CATIMfgResourceQuery::MfgResourceQueryType` |
| NULL | `CATDocument *piDoc =` |


---

**源文件**: `CAAManufacturingItf.edu/CAAMaiUserToolDatabaseCustomization.m/LocalInterfaces/CAAEMaiUserToolDatabaseCustomization.h`
