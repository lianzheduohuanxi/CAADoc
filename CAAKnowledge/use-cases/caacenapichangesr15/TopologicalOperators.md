---
title: "TopologicalOperators Framework Modifications in V5R15"
category: "use-case"
module: "CAACenAPIChangesR15"
version: "V5R15"
tags: []
source_file: "Doc/online/CAACenAPIChangesR15/TopologicalOperators.htm"
converted: "2026-05-11T17:33:51.157823"
---

| 
# CAA C++ API Modifications

| 
##  TopologicalOperators Framework Modifications in V5R15 

  
* * *

**Entity|  SP| Modification| To Do** | TopologicalOperators/Public/CATHybOperator.h/CATHybOperator/GetDistance  
**Prototype:**`virtual double GetDistance(CATDomain* iDomOfResultBody);`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)| Correction of an exposition Error. This method must not be used. Check that you don't use it  
---|---|---|---  
TopologicalOperators/Public/CATHybProject.h/CATHybProject/GetSimplificationMode  
**Prototype:**`CATBoolean GetSimplificationMode()const;`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)| Correction of an exposition Error. This method must not be used. Check that you don't use it
