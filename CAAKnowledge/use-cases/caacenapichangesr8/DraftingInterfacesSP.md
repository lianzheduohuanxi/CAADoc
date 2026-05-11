---
title: "DraftingInterfaces Modifications"
category: "use-case"
module: "CAACenAPIChangesR8"
version: "V5R8"
tags: ["CATIDftArrow", "CATIView", "CATIGenerSpec", "CATIDrwDimDimension", "CATIDrwSubText", "CATIDrwAnnotationFactory", "CATIDftGenGeom", "CATIDrwAreaFill"]
source_file: "Doc/online/CAACenAPIChangesR8/DraftingInterfacesSP.htm"
converted: "2026-05-11T17:33:52.507721"
---

CAA C++ API Modifications|  DraftingInterfaces  |   
---|---|---  
  
* * *

**Entity|  SP| Modification| To Do** | DraftingInterfaces/Protected/CATIDftGenGeom.h/CATIDftGenGeom/SetUnderlyingGeometry| 1| INDM| Check that you don't use it  
---|---|---|---  
DraftingInterfaces/Protected/CATIDftGenGeom.h/CATIDftGenGeom/SetGeometryOfOrigin| 1| INDM| Check that you don't use it  
DraftingInterfaces/Protected/CATIDftGenGeom.h/CATIDftGenGeom/SetBody| 1| INDM| Check that you don't use it  
DraftingInterfaces/Protected/CATIDftGenGeom.h/CATIDftGenGeom/SetProduct| 1| INDM| Check that you don't use it  
DraftingInterfaces/Protected/CATIDftGenGeom.h/CATIDftGenGeom/SetTransformation| 1| INDM| Check that you don't use it  
DraftingInterfaces/Protected/CATIDrwDimDimension.h/CATIDrwDimDimension/MoveDimensionLine| 1| MHBDM|   
DraftingInterfaces/Protected/CATIDrwDimDimension.h/CATIDrwDimDimension/MoveValue| 1| MHBDM|   
DraftingInterfaces/Protected/CATIDrwAnnotationFactory.h/CATIDrwAnnotationFactory/CreateDrwAreaFill| 1| MHBDM|   
DraftingInterfaces/Protected/CATIDrwAreaFill.h/CATIDrwAreaFill/AddContour| 1| MHBDM|   
DraftingInterfaces/Protected/CATIGenerSpec.h/CATIGenerSpec/AddClipping| 1| MRTHC|   
DraftingInterfaces/Protected/CATIGenerSpec.h/CATIGenerSpec/AddSection| 1| MRTHC|   
DraftingInterfaces/Protected/CATIGenerSpec.h/CATIGenerSpec/AddBreakOut| 1| MRTHC|   
DraftingInterfaces/Protected/CATIGenerSpec.h/CATIGenerSpec/AddOperator| 2| INDM| Check that you don't use it  
DraftingInterfaces/Protected/CATIDftArrow.h/CATIDftArrow/GetSymbolType| 2| MHBDM|   
DraftingInterfaces/Protected/CATIDftArrow.h/CATIDftArrow/SetSymbolType| 2| MHBDM|   
DraftingInterfaces/Protected/CATIDftArrow.h/CATIDftArrow/GetNbPoint| 2| MHBDM|   
DraftingInterfaces/Protected/CATIDftArrow.h/CATIDftArrow/RemovePoint| 2| MHBDM|   
DraftingInterfaces/Protected/CATIDftArrow.h/CATIDftArrow/ModifyPoint| 2| MHBDM|   
DraftingInterfaces/Protected/CATIDftArrow.h/CATIDftArrow/GetPoints| 2| MHBDM|   
DraftingInterfaces/Protected/CATIDftArrow.h/CATIDftArrow/GetPoint| 2| MHBDM|   
DraftingInterfaces/Protected/CATIDftArrow.h/CATIDftArrow/SetTarget| 2| MHBDM|   
DraftingInterfaces/Protected/CATIDftArrow.h/CATIDftArrow/GetTarget| 2| MHBDM|   
DraftingInterfaces/Protected/CATIDrwSubText.h/CATIDrwSubText/GetText| 2| INDM| Check that you don't use it  
DraftingInterfaces/Protected/CATIView.h/CATIView/GetOleSiteList| 2| INDM| Check that you don't use it
