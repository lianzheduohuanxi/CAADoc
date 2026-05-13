---
title: "Detail Of C++ API Changes"
category: "api-changes"
module: "CAACenAPIChangesR26"
tags: "["CAA2Usage", "CATIDftDatumFeature", "CAA2Level"]"
source_file: "Doc/online/CAACenAPIChangesR26/CAACenAPIChangeDetail.htm"
converted: "2026-05-11T17:33:51.846182"
---
|  |  Detail Of V5-6R2016 C++ API Changes _What changes in the API compared with CAA V5-6R2015_
---|---|---
Technical Article

* * *

Abstract This article presents by frameworks the detail of CAA C++ resources modified in V5-6R2016 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities. Possibly impacting modifications are highlighted in red.
| Classification | Meaning
---|---
Abstract This article presents by frameworks the detail of CAA C++ resources modified in V5-6R2016 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities. Possibly impacting modifications are highlighted in red.
LHC | @CAA2Level Has Changed: a L1 file is no more L1.
UHC | @CAA2Usage Has Changed: usage has changed for a more restricted usage. For example a class tagged as derivable is not derivable anymore.
CHBD | Class Has Been Deleted
FHBD | File Has Been Deleted
ADVHC | Argument Default Value Has Changed
MHBDM | Method Has Been Deleted or Modified
MRTHC | Method Returned Type Has Changed
NPVM | New Pure Virtual Method. A new pure virtual method has been added on a derivable class or on an interface to be implemented without an adapter.
INDM | Method is no more documented. It does not break your code in any way but means that you are not supposed to use it anymore. Check that you don't use it or look for replacement informations.
MINMV | Method is no more virtual. If occurs on a U1 class, may require modifications in Imakefile.mk of client code. If occurs on a U2 class, see details on the documentation of the concerned resource modification.

* * *

MINMV | Method is no more virtual. If occurs on a U1 class, may require modifications in Imakefile.mk of client code. If occurs on a U2 class, see details on the documentation of the concerned resource modification.
Framework | Header | Class | Method | Signature | Modification | To Do

DraftingInterfaces | CATIDftDatumFeature.h | CATIDftDatumFeature | GetText | virtual HRESULT SetText(const wchar_t*iText)= 0 | INDM | Use the signature with a CATUnicodeString.
SetText | virtual HRESULT SetText(const wchar_t*iText)= 0 | INDM | Use the signature with a CATUnicodeString.
```cpp
Mathematics | CATMathCircle2D.h | CATMathCircle2D | Set | HRESULT Set(const CATMathPoint2D& iLimit,const CATMathPoint2D& iMiddle,const CATMathPoint2D& iOtherLimit) | INDM | Use the signature that allows to specify a CATTolerance.
CATMathCircle.h | CATMathCircle | GetParam | int GetParam(const CATMathPoint& iPoint,double*oParam,const double iTol,const double iStartParam,const double iEndParam)const | INDM | Use the signature that allows to specify a CATTolerance.
```
Intersect | int Intersect(const CATMathLine& iLine,double iStartParamOnLine,double iEndParamOnLine,double iStartParamOnThisCircle,double iEndParamOnThisCircle,double iTol,double ioParamOnLine[2],double ioParamOnThisCircle[2])const | INDM | Use the signature that allows to specify a CATTolerance.
References

* * *

Intersect | int Intersect(const CATMathLine& iLine,double iStartParamOnLine,double iEndParamOnLine,double iStartParamOnThisCircle,double iEndParamOnThisCircle,double iTol,double ioParamOnLine[2],double ioParamOnThisCircle[2])const | INDM | Use the signature that allows to specify a CATTolerance.
References
History Version: **1** [Sep 2015] | Document created

[Top]

* * *

_Copyright 2015, Dassault Systmes. All rights reserved._
