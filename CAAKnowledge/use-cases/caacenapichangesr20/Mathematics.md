---
```vbscript
title: "Mathematics Framework Modifications in V5R20"
category: "use-case"
module: "CAACenAPIChangesR20"
version: "V5R20"
tags: []
source_file: "Doc/online/CAACenAPIChangesR20/Mathematics.htm"
converted: "2026-05-11T17:33:51.636633"
```

---
# CAA C++ API Modifications

|
##  Mathematics Framework Modifications in V5R20

* * *

**Entity|  SP| Modification| To Do** | Mathematics/Public/CATMathStream.h/CATMathStream/CATMathStream
**Prototype:**`CATMathStream(CATStream& iDirectStreaming,size_t iSizeStream,CATMathStreamImpl* ipImpl = NULL); and CATMathStream(CATMathStream& iDirectStreaming, const CATCGMStreamType iAccess, const CATBoolean iEnableByAdress=FALSE, CATMathStreamImpl * ipImpl=NULL)`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)| Useless methods removed from exposition. Check that you don't use them.
---|---|---|---
Mathematics/Public/CATMathStream.h/CATMathStream/GetImpl
**Prototype:**`inline void* GetImpl();`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)| Useless method removed from exposition. Check that you don't use it.
Mathematics/Public/CATCGMStream.h/CATCGMStream/CATCGMStream
**Prototype:**`CATCGMStream(CATStream iDirectStreaming,const CATCGMStreamType iAcces,const CATBoolean iEnableByAddress = FALSE,CATCGMStreamImpl* ipImpl = NULL) and CATCGMStream(CATStream iDirectStreaming,size_t iSizeStream,CATCGMStreamImpl* ipImpl = NULL)`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)| Useless methods removed from exposition. Check that you don't use them.
