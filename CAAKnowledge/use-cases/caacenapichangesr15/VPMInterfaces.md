---
title: "VPMInterfaces Framework Modifications in V5R15"
category: "use-case"
module: "CAACenAPIChangesR15"
version: "V5R15"
tags: ["CATIConfigurableObject_var", "CATICfgUEValidateEff", "CATICfgBasicEffectivity_var"]
source_file: "Doc/online/CAACenAPIChangesR15/VPMInterfaces.htm"
converted: "2026-05-11T17:33:51.169792"
---
# CAA C++ API Modifications  
  
| 
##  VPMInterfaces Framework Modifications in V5R15 

  
* * *

**Entity|  SP| Modification| To Do** | VPMInterfaces/Public/CATICfgUEValidateEff.h/CATICfgUEValidateEff/ValidateEffectivity  
**Prototype:**`virtual HRESULT ValidateEffectivity(const CATListOfCATILinkableObject& iObjects,const CATICfgBasicEffectivity_var& iObject,const CATUnicodeString& iDomain,const CATUnicodeString& iModName,const CATIConfigurableObject_var iCV)= 0;`| GA| [NPVM](CAACenAPIChangeDetail.htm#Abstract)| Implement it when entity is implemented or inherited  
---|---|---|---
