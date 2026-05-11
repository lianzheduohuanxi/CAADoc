---
title: "GeometricObjects Modifications"
category: "use-case"
module: "CAACenAPIChangesR7"
version: "V5R7"
tags: ["CATICGMObject"]
source_file: "Doc/online/CAACenAPIChangesR7/GeometricObjects.htm"
converted: "2026-05-11T17:33:52.070018"
---

CAA API Modifications|  GeometricObjects  |   
---|---|---  
  
* * *

**Entity|  Modification| To Do** | GeometricObjects/Protected/CATICGMObject.h/CATICGMObject/Completed| MHBDM| Addition of a default argument -> BT compatible (recompile)  
---|---|---  
GeometricObjects/Protected/CATICGMObject.h/CATICGMObject/GetUseCount| MHBDM| Addition of a default argument -> BT compatible (recompile)  
GeometricObjects/Protected/CATICGMObject.h/CATICGMObject/GetContainer| MHBDM| Addition of a default argument -> BT compatible (recompile)  
GeometricObjects/Protected/CATPCurve.h/CATPCurve/Create3DCurve| INDM| This method is not implemented... Check that you don't use it  
GeometricObjects/Protected/CATSetOfCrvParams.h| LHC| This header is not useful to any other L1 header, and does not bring any valuable functionality to CAA  
GeometricObjects/Protected/CATSetOfCrvParams.h/CATSetOfCrvParams/Allocate| INDM| This header is not useful to any other L1 header, and does not bring any valuable functionality to CAA (see above)
