---
title: "SketcherInterfaces Framework Modifications in V5R21"
category: "use-case"
module: "CAACenAPIChangesR21"
tags: "["CATIPspValidation"]"
source_file: "Doc/online/CAACenAPIChangesR21/CATPlantShipInterfaces.htm"
converted: "2026-05-11T17:33:51.667069"
---
# CAA C++ API Modifications

|
##  CATPlantShipInterfaces Framework Modifications in V5R21

* * *

**Entity|  SP| Modification| To Do** | CATPlantShipInterfaces/Public/CATEAPspValidation.h/CATEAPspValidation/GetContextObjectViolation
**Prototype:**`virtual HRESULT GetContextObjectViolation(const intamp; iViolationIndex,CATPspViolationProduct** oProduct,CATListPV** oViolation)`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)| CAA Exposition Error: Method Was using non exposed resources, so were not usable and has been removed.
---|---|---|---
CATPlantShipInterfaces/Public/CATIPspValidation.h/CATIPspValidation/GetContextObjectViolation
**Prototype:**`virtual HRESULT GetContextObjectViolation(const intamp; iViolationIndex,CATPspViolationProduct** oProduct,CATListPV** oViolation)`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)| CAA Exposition Error: Method Was using non exposed resources, so were not usable and has been removed.
