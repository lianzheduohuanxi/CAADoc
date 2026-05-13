---
```vbscript
title: "GeometricObjects Framework Modifications in V5R15"
category: use-case
module: "CAACenAPIChangesR15"
version: "V5R15"
tags: []
source_file: "Doc/online/CAACenAPIChangesR15/GeometricObjects.htmmd"
converted: "2026-05-11T17:33:51.096941"
```

---
# CAA C++ API Modifications

|
##  GeometricObjects Framework Modifications in V5R15

* * *

**Entity|  SP| Modification| To Do** | GeometricObjects/Public/CATCylinder.h/CATCylinder/GetCylinderParam
**Prototype:**`virtual void GetCylinderParam(double & iUnitU,double & iMinParam,double & iStartParam,double & iEndParam)= 0;`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)| Correction of an exposition error. Must not be used. Check that you don't use it
---|---|---|---
GeometricObjects/Public/CATCylinder.h/CATCylinder/SetCylinderParam
**Prototype:**`virtual void SetCylinderParam(double iUnitU,double iMinParam,double iStartParam,double iEndParam)= 0;`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)| Correction of an exposition error. Must not be used. Check that you don't use it
