---
title: "CAAPeoDelegateInstanciation"
type: "interface"
module: "CAAOptimizationInterfaces"
base: "CATBaseUnknown"
method_count: 2
visibility: "local"
verified: true
---

# CAAPeoDelegateInstanciation

**基类**: CATBaseUnknown  
**模块**: CAAOptimizationInterfaces  
**可见性**: local  
**方法数**: 2

> forwards

## 方法列表

### Instanciate
```cpp
HRESULT Instanciate(const CATIInstance_var& iOwner,
		const CATUnicodeString& iKey,
		const CATUnicodeString& typeName,
		CATIInstance_var& oInstanciated,
		const CATInstanciationContext *iContext);
```

### CreateInstance
```cpp
HRESULT __stdcall CreateInstance(void **oPPV);
```

## 依赖

- `CATBaseUnknown.h`

