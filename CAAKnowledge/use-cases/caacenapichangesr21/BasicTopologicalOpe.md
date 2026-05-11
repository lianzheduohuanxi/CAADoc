---
title: "BasicTopologicalOpe Framework Modifications in V5R21"
category: "use-case"
module: "CAACenAPIChangesR21"
version: "V5R21"
tags: []
source_file: "Doc/online/CAACenAPIChangesR21/BasicTopologicalOpe.htm"
converted: "2026-05-11T17:33:51.643117"
---
# CAA C++ API Modifications  
  
| 
##  BasicTopologicalOpe Framework Modifications in V5R21 

  
* * *

**Entity|  SP| Modification| To Do** | GMOperatorsInterfaces/Public/CATTopSplineOperator.h/CATTopSplineOperator/GetComputedCurvatureVector  
**Prototype:**`virtual CATLONG32 GetComputedCurvatureVectors(const CATMathVector* oCurvatures)=0`| GA| MHBDM| Out argument type changed from * to *&. Didn't work. Should have no impact.** | GMOperatorsInterfaces/Public/CATTopSplineOperator.h/CATTopSplineOperator/GetImposedCurvatureVector  
**Prototype:**`virtual CATLONG32 GetImposedCurvatureVectors(const CATMathVector* oCurvatures,const CATLONG32* oImposition)=0`| GA| MHBDM| Out argument type changed from * to *&. Didn't work. Should have no impact.**
