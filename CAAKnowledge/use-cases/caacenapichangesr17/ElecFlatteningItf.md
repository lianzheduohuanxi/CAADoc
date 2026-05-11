---
title: "ElecFlatteningItf Framework Modifications in V5R17"
category: "use-case"
module: "CAACenAPIChangesR17"
version: "V5R17"
tags: ["CATIEhfFlatteningParameters"]
source_file: "Doc/online/CAACenAPIChangesR17/ElecFlatteningItf.md"
converted: "2026-05-11T17:33:51.329760"
---

| 
# CAA C++ API Modifications

| 
##  ElecFlatteningItf Framework Modifications in V5R17 

  
* * *

**Entity|  SP| Modification| To Do** | ElecFlatteningItf/Public/CATIEhfFlatteningParameters.h/CATIEhfFlatteningParameters/GetPlane  
**Prototype:**`virtual HRESULT GetPlane(CATMathPlane* iopActivePlane)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Signature changed from a pointer into a reference.  
---|---|---|---
