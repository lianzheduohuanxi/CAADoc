---
title: "GMOperatorsInterfaces Framework Modifications in V5R21"
category: "use-case"
module: "CAACenAPIChangesR21"
version: "V5R21"
tags: ["CATICGMTopSplineOperator"]
source_file: "Doc/online/CAACenAPIChangesR21/GMOperatorsInterfaces.md"
converted: "2026-05-11T17:33:51.679765"
---
# CAA C++ API Modifications  
  
| 
##  GMOperatorsInterfaces Framework Modifications in V5R21 

  
* * *

**Entity|  SP| Modification| To Do** | GMOperatorsInterfaces/Public/CATICGMTopSplineOperator.h/CATICGMTopSplineOperator/GetImposedCurvatureVectors  
**Prototype:**`virtual CATLONG32 GetImposedCurvatureVectors(const CATMathVector*oCurvatures,const CATLONG32*oImposition)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Out argument is now passed as a reference. Previous signature didn't work.  
---|---|---|---  
GMOperatorsInterfaces/Public/CATICGMTopSplineOperator.h/CATICGMTopSplineOperator/GetComputedCurvatureVectors  
**Prototype:**`virtual CATLONG32 GetComputedCurvatureVectors(const CATMathVector*oCurvatures)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Out argument is now passed as a reference. Previous signature didn't work.
