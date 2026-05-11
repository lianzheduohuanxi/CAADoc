---
```vbscript
title: "ENOVInterfaces Framework Modifications in V5R15"
category: "use-case"
module: "CAACenAPIChangesR15"
version: "V5R15"
tags: ["CATIAVPMProductSpecification_var", "CATIAVPMProductSpecification", "CATIAVPMProductSpecification2"]
source_file: "Doc/online/CAACenAPIChangesR15/ENOVInterfaces.htm"
converted: "2026-05-11T17:33:51.091455"
```

---
# CAA C++ API Modifications

|
##  ENOVInterfaces Framework Modifications in V5R15

* * *

**Entity|  SP| Modification| To Do** | ENOVInterfaces/Public/ENOVIConfigProductSpec.h/ENOVIConfigProductSpec/DeleteProductSpecification
**Prototype:**`virtual HRESULT DeleteProductSpecification(const CATIAVPMProductSpecification_var& iPS)=0;`| GA| [MHBDM ](CAACenAPIChangeDetail.htm#Abstract)| Signature has been changed to use a CATIAVPMProductSpecification2, CATIAVPMProductSpecification is not a CAA class.
---|---|---|---
