---
title: "CAAEMaiUserToolDatabaseCustomization"
type: "interface"
module: "CAAManufacturingItf"
base: "CATBaseUnknown"
method_count: 19
visibility: "local"
verified: true
---

# CAAEMaiUserToolDatabaseCustomization

**基类**: CATBaseUnknown  
**模块**: CAAManufacturingItf  
**可见性**: local  
**方法数**: 19

> Motherinterface of CATIMfgResourceQueryUserDatabase

## 方法列表

### InitConnection
```cpp
HRESULT InitConnection();
```

### ResetConnection
```cpp
HRESULT ResetConnection();
```

### GetNamesToDisplay
```cpp
HRESULT GetNamesToDisplay(CATListOfCATUnicodeString &oListNames);
```

### Initialize
```cpp
HRESULT Initialize(const CATUnicodeString &iName, 
								              const CATUnicodeString &iType);
```

### AddSubComponentTypeConstraint
```cpp
HRESULT AddSubComponentTypeConstraint(CATIMfgResourceQuery::MfgResourceQueryType  iResourceType,
                                                  const CATUnicodeString                     &iFamily);
```

### AddNameLikeConstraint
```cpp
HRESULT AddNameLikeConstraint(const CATUnicodeString   &iValue,
                                          CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent);
```

### AddDiameterBetweenConstraint
```cpp
HRESULT AddDiameterBetweenConstraint(const double             &iMinValue,
												                        const double             &iMaxValue,
										                            const CATUnicodeString   &iUnit,
                                                CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent);
```

### AddConstraint
```cpp
HRESULT AddConstraint(const CATUnicodeString   &iAttribute, 
								                 const int                &iOperator,
								                 const int                &iValue,
                                 CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent);
```

### AddConstraint
```cpp
HRESULT AddConstraint(const CATUnicodeString   &iAttribute, 
								                 const int                &iOperator,
								                 const double             &iValue,
								                 const CATUnicodeString   &iUnit,
                                 CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent);
```

### AddConstraint
```cpp
HRESULT AddConstraint(const CATUnicodeString   &iAttribute, 
								                  const int                &iOperator,
								                  const CATUnicodeString   &iValue,
                                  CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent);
```

### AddConstraints
```cpp
HRESULT AddConstraints(const CATUnicodeString            &iAttribute, 
									                const CATUnicodeString            &iUnit,
								                  const int                         &iTypeValue,
                                  const CATListOfInt                &iOperators,
                                  const CATListOfInt                &iIntValues,
                                  const CATListOfDouble             &iDblValues,
                                  const CATListOfCATUnicodeString   &iStrValues,
                                  const CATListOfInt                &iLogLinks,
                                  CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent);
```

### Execute
```cpp
HRESULT Execute();
```

### GetResultSize
```cpp
HRESULT GetResultSize(int &NbElem,
                                CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent);
```

### GetDescription
```cpp
HRESULT GetDescription(const int                  &iElem, 
					 			                  CATListOfCATUnicodeString  &oAttributes, 
                                  CATListOfInt               &oTypeValues, 
                                  CATListOfInt               &oNbValues,
                                  CATListOfInt               &oIntValues,
                                  CATListOfDouble            &DblValues, 
                                  CATListOfCATUnicodeString  &StrValues,
                                  CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent);
```

### GetComponentNameAndIndex
```cpp
HRESULT GetComponentNameAndIndex(const int        &iNumElem,
                                            CATUnicodeString &oCompName,
                                            int              &oCompNumElem,
                                            CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent);
```

### GetRepresentation
```cpp
HRESULT GetRepresentation(const int         &iElem,
  								                    CATUnicodeString  &oPathName,
                                      CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent);
```

### GetRepresentation
```cpp
HRESULT GetRepresentation(const int         &iElem,
  								                    CATIDocId         *&oDocId,
																			CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent);
```

### GetCorrectors
```cpp
HRESULT GetCorrectors(const int                 &iElem,
                                  CATListOfCATUnicodeString &oListPoints,
                                  CATListOfInt              &oListNumber,
                                  CATListOfInt              &oListLengthNumber,
                                  CATListOfInt              &oListRadiusNumber,
                                  CATListOfDouble           &oListDiameter,
                                  CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent);
```

### InstantiateResourceInDocument
```cpp
HRESULT InstantiateResourceInDocument(const int          &iElem,
                                                  CATBaseUnknown_var &hBUResources,
                                                  CATIMfgResourceQuery::MfgResourceQueryType iResourceType=CATIMfgResourceQuery::MfgCurrent,
                                                  CATDocument *piDoc = NULL);
```

## 依赖

- `CATBaseUnknown.h`
- `CATListOfInt.h`
- `CATListOfDouble.h`
- `CATListOfCATUnicodeString.h`
- `CATUnicodeString.h`
- `CATIDocId.h`
- `CATIMfgResourceQuery.h`
- `CATBaseUnknown.h`

