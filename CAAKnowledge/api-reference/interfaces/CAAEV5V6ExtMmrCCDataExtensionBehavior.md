---
title: "CAAEV5V6ExtMmrCCDataExtensionBehavior"
type: "LocalClass"
module: "CAAV5V6MechanicalModeler"
base: "CATIFmFeatureBehaviorCustomization"
method_count: 9
source_file: "CAAV5V6MechanicalModeler.edu/CAAV5V6ExtMmrCCDataExtension.m/LocalInterfaces/CAAEV5V6ExtMmrCCDataExtensionBehavior.h"
---

# CAAEV5V6ExtMmrCCDataExtensionBehavior

**基类**: CATIFmFeatureBehaviorCustomization | **模块**: CAAV5V6MechanicalModeler | **方法数**: 9

## 依赖

- `CATIFmFeatureBehaviorCustomization.h`

## 虚方法

### CanBeRemoved

```cpp
virtual HRESULT CanBeRemoved(CATBoolean & oDeletable) const ;
```

| 参数 | 类型 |
|------|------|
| oDeletable | `CATBoolean &` |


### BeforeRemove

```cpp
virtual HRESULT BeforeRemove() ;
```


### Build

```cpp
virtual HRESULT Build() ;
```


### CcpRegisterAdditionalObjectsForCopy

```cpp
virtual HRESULT CcpRegisterAdditionalObjectsForCopy(const CATListValCATBaseUnknown_var & iInitialSetOfObjects, CATListValCATBaseUnknown_var & oObjectToAddToBoundary) const ;
```

| 参数 | 类型 |
|------|------|
| iInitialSetOfObjects | `const CATListValCATBaseUnknown_var &` |
| oObjectToAddToBoundary | `CATListValCATBaseUnknown_var &` |


### CcpUpdate

```cpp
virtual HRESULT CcpUpdate(const CATFmCCPContext & iContext) ;
```

| 参数 | 类型 |
|------|------|
| iContext | `const CATFmCCPContext &` |


### CcpUpdate

```cpp
virtual HRESULT CcpUpdate(CATFmCCPContext & iContext) ;
```

| 参数 | 类型 |
|------|------|
| iContext | `CATFmCCPContext &` |


### CcpPaste

```cpp
virtual HRESULT CcpPaste(const CATFmCCPContext & iContext) ;
```

| 参数 | 类型 |
|------|------|
| iContext | `const CATFmCCPContext &` |


### CcpPaste

```cpp
virtual HRESULT CcpPaste(CATFmCCPContext & iContext) ;
```

| 参数 | 类型 |
|------|------|
| iContext | `CATFmCCPContext &` |


### CcpRegisterAdditionalObjectsForRemove

```cpp
virtual HRESULT CcpRegisterAdditionalObjectsForRemove(const CATListValCATBaseUnknown_var & iInitialSetOfObjects, CATListValCATBaseUnknown_var & oObjectToAddToBoundary) const ;
```

| 参数 | 类型 |
|------|------|
| iInitialSetOfObjects | `const CATListValCATBaseUnknown_var &` |
| oObjectToAddToBoundary | `CATListValCATBaseUnknown_var &` |


---

**源文件**: `CAAV5V6MechanicalModeler.edu/CAAV5V6ExtMmrCCDataExtension.m/LocalInterfaces/CAAEV5V6ExtMmrCCDataExtensionBehavior.h`
