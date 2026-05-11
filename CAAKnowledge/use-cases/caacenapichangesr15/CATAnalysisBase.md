---
```vbscript
title: "CATAnalysisBase Framework Modifications in V5R15"
category: "use-case"
module: "CAACenAPIChangesR15"
version: "V5R15"
tags: ["CATICharacCollector", "CATISPMProcess", "CATISamGroup", "CATISPMProcessAccess"]
source_file: "Doc/online/CAACenAPIChangesR15/CATAnalysisBase.htm"
converted: "2026-05-11T17:33:51.043914"
```

---
# CAA C++ API Modifications

| 
##  CATAnalysisBase Framework Modifications in V5R15 

* * *

**Entity|  SP| Modification| To Do** | CATAnalysisBase/Public/CATAnalysisCollectorArchiver.h/CATAnalysisCollectorArchiver/CATAnalysisCollectorArchiver  
**Prototype:**`CATAnalysisCollectorArchiver();`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Argument has been added.See reference documentation.  
---|---|---|---  
CATAnalysisBase/Public/CATAnalysisCollectorArchiver.h/CATAnalysisCollectorArchiver/UnStream  
**Prototype:**`HRESULT UnStream(const CATAnalysisCharacCollector* oCollector);`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Arguments have been added.See reference documentation.  
CATAnalysisBase/Public/CATAnalysisCollectorArchiver.h/CATAnalysisCollectorArchiver/UnStream
CATAnalysisBase/Public/CATAnalysisCollectorArchiver.h/CATAnalysisCollectorArchiver/IsUnStreamable  

**Prototype:**`CATBoolean IsUnStreamable(int iEntityFlagsSize)const;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Argument has been added. See reference documentation.  
CATAnalysisBase/Public/CATAnalysisCollectorArchiver.h/CATAnalysisCollectorArchiver/UnStream
CATAnalysisBase/Public/CATAnalysisCollectorArchiver.h/CATAnalysisCollectorArchiver/IsUnStreamable
CATAnalysisBase/Public/CATAnalysisExplicitRulesData.h/CATAnalysisExplicitRulesData/ReadRulesCatalog  

**Prototype:**`HRESULT ReadRulesCatalog(CATListOfCATUnicodeString &iBuffer;,const CATUnicodeString iStorageName =;`| GA| [MHBDM ](CAACenAPIChangeDetail.htm#Abstract)| Method has been removed but had never been implemented. It was so useless.  
CATAnalysisBase/Public/CATAnalysisCollectorArchiver.h/CATAnalysisCollectorArchiver/IsUnStreamable
CATAnalysisBase/Public/CATAnalysisExplicitRulesData.h/CATAnalysisExplicitRulesData/ReadRulesCatalog
CATAnalysisBase/Public/CATICharacCollector.h| GA| [FHBD ](CAACenAPIChangeDetail.htm#Abstract)| Moved into CATAnalysisInterfaces. May required IdentityCard & Imakefiles upgrades.  
CATAnalysisBase/Public/CATISPMProcess.h| GA| [FHBD ](CAACenAPIChangeDetail.htm#Abstract)| Moved into CATAnalysisVisuInterfaces. May required IdentityCard & Imakefiles upgrades.  
CATAnalysisBase/Public/CATISPMProcessAccess.h| GA| [FHBD ](CAACenAPIChangeDetail.htm#Abstract)| Moved into CATAnalysisVisuInterfaces. May required IdentityCard & Imakefiles upgrades.  
CATAnalysisBase/Public/CATISamGroup.h| GA| [FHBD ](CAACenAPIChangeDetail.htm#Abstract)| Moved into CATAnalysisInterfaces. May required IdentityCard & Imakefiles upgrades.  
CATAnalysisBase/Public/CATSamGroupTypes.h| GA| [FHBD ](CAACenAPIChangeDetail.htm#Abstract)| Moved into CATAnalysisInterfaces. May required IdentityCard & Imakefiles upgrades.  
CATAnalysisBase/Public/CATSamDimension.h/CATSamDimension/Fill  

**Prototype:**`void Fill(int iNbPositions,const int* const iPositionsNumber,int iNbLaminates,const int* const iLaminatesNumber,int iNbSMI,const int* const iSMI,const int* const iNbRepeats,const int* const iRepeatsNumber,const CATSamAggregationMode* const iAggregationMode,CATSamValue iValueType,CATSamMathType iMathType,int iMathDimension);`| GA| [MRTHC](CAACenAPIChangeDetail.htm#Abstract)| Return value has been changed from void to HRESULT: no impact.  
CATAnalysisBase/Public/CATISPMProcessAccess.h| GA| [FHBD ](CAACenAPIChangeDetail.htm#Abstract)| Moved into CATAnalysisVisuInterfaces. May required IdentityCard & Imakefiles upgrades.
CATAnalysisBase/Public/CATISamGroup.h| GA| [FHBD ](CAACenAPIChangeDetail.htm#Abstract)| Moved into CATAnalysisInterfaces. May required IdentityCard & Imakefiles upgrades.
CATAnalysisBase/Public/CATSamGroupTypes.h| GA| [FHBD ](CAACenAPIChangeDetail.htm#Abstract)| Moved into CATAnalysisInterfaces. May required IdentityCard & Imakefiles upgrades.
CATAnalysisBase/Public/CATSamDimension.h/CATSamDimension/Fill
CATAnalysisBase/Public/CATSamDimension.h/CATSamDimension/SetUnitaryValueSize  

**Prototype:**`void SetUnitaryValueSize(int iUnitaryValueSize);`| GA| [MRTHC](CAACenAPIChangeDetail.htm#Abstract)| Return value has been changed from void to HRESULT: no impact.
