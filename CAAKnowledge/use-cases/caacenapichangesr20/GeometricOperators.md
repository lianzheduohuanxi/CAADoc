---
```vbscript
title: "GeometricOperators Framework Modifications in V5R20"
category: use-case
module: "CAACenAPIChangesR20"
version: "V5R20"
tags: []
source_file: "Doc/online/CAACenAPIChangesR20/GeometricOperators.htmmd"
converted: "2026-05-11T17:33:51.630150"
```

---
# CAA C++ API Modifications

|
##  GeometricOperators Framework Modifications in V5R20

* * *

**Entity|  SP| Modification| To Do** | GeometricOperators/Public/CATDistanceMinCrvCrv.h/CATDistanceMinCrvCrv/SetLimits
**Prototype:**`virtual void SetLimits(CATCrvLimits iCrvLim1,CATCrvLimits iCrvLim2)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| CATCrvLimits arguments are now references on const objects for performance purpose. Very probably no impact in customer code. Copy to local object if modification is required.
---|---|---|---
GeometricOperators/Public/CATDistanceMinPtSur.h/CATDistanceMinPtSur/SetLimits
**Prototype:**`virtual void SetLimits(CATSurLimits iLimits)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| CATSurLimits argument is now references on const objects for performance purpose. Very probably no impact in customer code. Copy to local object if modification is required.
GeometricOperators/Public/CATDistanceMinPtSur.h/CATDistanceMinPtSur/SetLimits
GeometricOperators/Public/CATDistanceMinPtSur.h/CATDistanceMinPtSur/SetPointAndInit

**Prototype:**`virtual void SetPointAndInit(CATMathPoint & iNewPointToOperate,CATSurParam iSolutionInit)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| CATSurParam argument is now references on const objects for performance purpose. Very probably no impact in customer code. Copy to local object if modification is required.
GeometricOperators/Public/CATDistanceMinPtSur.h/CATDistanceMinPtSur/SetLimits
GeometricOperators/Public/CATDistanceMinPtSur.h/CATDistanceMinPtSur/SetPointAndInit
GeometricOperators/Public/CATProjectionPtCrv.h/CATProjectionPtCrv/SetLimits

**Prototype:**`virtual void SetLimits(const CATCrvLimits iLimits)=0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| CATCrvLimits argument is now references on const objects for performance purpose. Very probably no impact in customer code. Copy to local object if modification is required.
