---
```vbscript
title: "ElecHarnessItf Framework Modifications in V5R17"
category: "use-case"
module: "CAACenAPIChangesR17"
version: "V5R17"
tags: ["CATIEhiFLEX"]
source_file: "Doc/online/CAACenAPIChangesR17/ElecHarnessItf.htm"
converted: "2026-05-11T17:33:51.337240"
```

---
# CAA C++ API Modifications  

| 
##  ElecHarnessItf Framework Modifications in V5R17 

* * *

**Entity|  SP| Modification| To Do** | ElecHarnessItf/Public/CATIEhiFLEX.h/CATIEhiFLEX/GetFLEXEquivalentModulus  
**Prototype:**`virtual HRESULT GetFLEXEquivalentModulus(CATListValCATBaseUnknown_var* ipListOfWireWireGroup,CATListValCATBaseUnknown_var* ipOrderedListOfProtectionReference,CATListValCATBaseUnknown_var* ipInternalSpliceReferenceList,CATEhiProfileType iProfile,double iProfileLength1,double iProfileLength2,int iBundleSegmentFlexibility,double & oYoungModulusEquivalent,double & oEquivalentRatioToBend,double & oEquivalentRatioToTwist)=0;`| GA| [NPVM](CAACenAPIChangeDetail.htm#Abstract)| Implement it when entity is implemented or inherited  
---|---|---|---
