---
title: "CATxPDMInterfaces Framework Modifications in V5R18"
category: "use-case"
module: "CAACenAPIChangesR18"
version: "V5R18"
tags: ["CATIxPDMProductItem"]
source_file: "Doc/online/CAACenAPIChangesR18/CATxPDMInterfaces.htm"
converted: "2026-05-11T17:33:51.453533"
---

| 
# CAA C++ API Modifications

| 
##  CATxPDMInterfaces Framework Modifications in V5R18 

  
* * *

**Entity|  SP| Modification| To Do** | CATxPDMInterfaces/Public/CATIxPDMProductItem.h/CATIxPDMProductItem/ChangeNameWithSessionImpacts  
**Prototype:**`virtual HRESULT ChangeNameWithSessionImpacts(const CATBaseUnknown_var &iInstanceOrPublicationToRename;,const CATUnicodeString &iNewName;)= 0;`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)| Exposition error, removed in R17SP1, this method should not be used.  
---|---|---|---
