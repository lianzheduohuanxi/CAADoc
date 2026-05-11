---
title: "ElecDeviceItf Framework Modifications in V5R14"
category: "general"
module: "CAACenAPIChangesR14"
tags: ["CATIElbCavity", "CATIProduct", "CATILinkableObject", "CATIElbSingleConnectorReference"]
source_file: "Doc\online\CAACenAPIChangesR14\ElecDeviceItf.htm"
converted: "2026-05-11T17:33:50.897403"
---

CAA C++ API Modifications|  ElecDeviceItf Framework Modifications in V5R14 |   
---|---|---  
  
* * *

**Entity|  SP| Modification| To Do** | ElecDeviceItf/Public/CATIElbSingleConnectorReference.h/CATIElbSingleConnectorReference/AddCavity  
**Prototype:**`virtual HRESULT AddCavity(const CATUnicodeString &iId;_Number,const int &iNumber;,CATIProduct* iGeoDefinition,CATILinkableObject* iRepresentation,const CATUnicodeString &iJointType;,CATListValCATBaseUnknown_var*iJointReferences,CATIElbCavity*& oCavity)= 0;`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)| Correction of a wrong 'nodoc' tag. Documentation was clear: this method must not be used.  
---|---|---|---
