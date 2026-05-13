---
```vbscript
title: "ENOVaultClientCPP Framework Modifications in V5R16"
category: use-case
module: "CAACenAPIChangesR16"
version: "V5R16"
tags: []
source_file: "Doc/online/CAACenAPIChangesR16/ENOVaultClientCPP.htmmd"
converted: "2026-05-11T17:33:51.209179"
```

---
|
# CAA C++ API Modifications

|
##  ENOVaultClientCPP Framework Modifications in V5R16

* * *

**Entity|  SP| Modification| To Do** | ENOVaultClientCPP/Public/ENOVIVaultError.h/ENOVIVaultError/getCode
**Prototype:**`void getCode(CATLONG32 & code);`| GA| [MHBDM ](CAACenAPIChangeDetail.htm#Abstract)| Argument code is now formally a HRESULT which should have been the case and has no impact on existing applications.
---|---|---|---
