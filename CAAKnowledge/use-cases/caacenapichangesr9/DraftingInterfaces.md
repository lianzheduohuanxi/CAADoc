---
title: "DraftingInterfaces Modifications"
category: "use-case"
module: "CAACenAPIChangesR9"
version: "V5R9"
tags: ["CATIDrwDimValue", "CATIDftArrow", "CATIGenerSpec", "CATIDrwDimDimension", "CATIDrwSubText", "CATIDrwAnnotationFactory", "CATIDftGenGeom", "CATIDrwAreaFill"]
source_file: "Doc/online/CAACenAPIChangesR9/DraftingInterfaces.md"
converted: "2026-05-11T17:33:52.880439"
---

CAA C++ API Modifications|  DraftingInterfaces  |   
---|---|---  
  
* * *

**Entity|  SP| Modification| To Do** | DraftingInterfaces/Protected/CATIDftArrow.h/CATIDftArrow/GetSymbolType| GA| MHBDM|   
---|---|---|---  
DraftingInterfaces/Protected/CATIDftArrow.h/CATIDftArrow/SetSymbolType| GA| MHBDM|   
DraftingInterfaces/Protected/CATIDftArrow.h/CATIDftArrow/GetNbPoint| GA| MHBDM|   
DraftingInterfaces/Protected/CATIDftArrow.h/CATIDftArrow/RemovePoint| GA| MHBDM|   
DraftingInterfaces/Protected/CATIDftArrow.h/CATIDftArrow/ModifyPoint| GA| MHBDM|   
DraftingInterfaces/Protected/CATIDftArrow.h/CATIDftArrow/GetPoints| GA| MHBDM|   
DraftingInterfaces/Protected/CATIDftArrow.h/CATIDftArrow/GetPoint| GA| MHBDM|   
DraftingInterfaces/Protected/CATIDftArrow.h/CATIDftArrow/SetTarget| GA| MHBDM|   
DraftingInterfaces/Protected/CATIDftArrow.h/CATIDftArrow/GetTarget| GA| MHBDM|   
DraftingInterfaces/Protected/CATIDftGenGeom.h/CATIDftGenGeom/SetUnderlyingGeometry| GA| INDM| Check that you don't use it  
DraftingInterfaces/Protected/CATIDftGenGeom.h/CATIDftGenGeom/SetGeometryOfOrigin| GA| INDM| Check that you don't use it  
DraftingInterfaces/Protected/CATIDftGenGeom.h/CATIDftGenGeom/SetBody| GA| INDM| Check that you don't use it  
DraftingInterfaces/Protected/CATIDftGenGeom.h/CATIDftGenGeom/SetProduct| GA| INDM| Check that you don't use it  
DraftingInterfaces/Protected/CATIDftGenGeom.h/CATIDftGenGeom/SetTransformation| GA| INDM| Check that you don't use it  
DraftingInterfaces/Protected/CATIDrwAnnotationFactory.h/CATIDrwAnnotationFactory/CreateDrwAreaFill| GA| MHBDM|   
DraftingInterfaces/Protected/CATIDrwAreaFill.h/CATIDrwAreaFill/AddContour| GA| MHBDM|   
DraftingInterfaces/Protected/CATIDrwDimDimension.h/CATIDrwDimDimension/MoveDimensionLine| GA| MHBDM|   
DraftingInterfaces/Protected/CATIDrwDimDimension.h/CATIDrwDimDimension/Move| GA| MRTHC|   
DraftingInterfaces/Protected/CATIDrwDimDimension.h/CATIDrwDimDimension/MoveValue| GA| MHBDM|   
DraftingInterfaces/Protected/CATIDrwSubText.h/CATIDrwSubText/GetText| GA| INDM| Check that you don't use it  
DraftingInterfaces/Protected/CATIGenerSpec.h/CATIGenerSpec/AddClipping| GA| MRTHC|   
DraftingInterfaces/Protected/CATIGenerSpec.h/CATIGenerSpec/AddSection| GA| MHBDM|   
DraftingInterfaces/Protected/CATIGenerSpec.h/CATIGenerSpec/AddBreakOut| GA| MRTHC|   
DraftingInterfaces/Protected/CATIGenerSpec.h/CATIGenerSpec/AddOperator| GA| INDM| Check that you don't use it  
DraftingInterfaces/Protected/CATIDrwDimValue.h/CATIDrwDimValue/GetOffsets| GA| MRTHC|   
DraftingInterfaces/Protected/CATIDrwDimValue.h/CATIDrwDimValue/SetOffsets| GA| MRTHC| 
