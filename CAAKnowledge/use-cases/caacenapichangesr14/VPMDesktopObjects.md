---
```vbscript
title: "VPMDesktopObjects Framework Modifications in CXR14"
category: "use-case"
module: "CAACenAPIChangesR14"
version: "V5R14"
tags: ["CATIVpmFactoryObject_var"]
source_file: "Doc/online/CAACenAPIChangesR14/VPMDesktopObjects.htm"
converted: "2026-05-11T17:33:50.993057"
```

---
tags: ["CATIVpmFactoryObject_var"]
source_file: "Doc/online/CAACenAPIChangesR14/VPMDesktopObjects.htm"
converted: "2026-05-11T17:33:50.993057"
CAA C++ API Modifications|  VPMDesktopObjects |

* * *

**Entity|  SP| Modification| To Do** | VPMDesktopObjects/Public/ENOVCustoCommandUtils.h/ENOVCustoCommandUtils/~ENOVCustoCommandUtils
**Prototype:**`virtual ~ENOVCustoCommandUtils();`| GA| [MINMV](CAACenAPIChangeDetail.htm#Abstract)| May require a modification of Imakefile.mk.
---|---|---|---
VPMDesktopObjects/Public/ENOVCustoCommandUtils.h/ENOVCustoCommandUtils/setResult
**Prototype:** all signatures.| GA| [MINMV](CAACenAPIChangeDetail.htm#Abstract)| May require a modification of Imakefile.mk.
VPMDesktopObjects/Public/ENOVCustoCommandUtils.h/ENOVCustoCommandUtils/setResult
VPMDesktopObjects/Public/ENOVCustoCommandUtils.h/ENOVCustoCommandUtils/GetIntParameter

**Prototype:**`virtual HRESULT GetIntParameter(CATUnicodeString outName,int &outVal;);`| GA| [MINMV](CAACenAPIChangeDetail.htm#Abstract)| May require a modification of Imakefile.mk
VPMDesktopObjects/Public/ENOVCustoCommandUtils.h/ENOVCustoCommandUtils/setResult
VPMDesktopObjects/Public/ENOVCustoCommandUtils.h/ENOVCustoCommandUtils/GetIntParameter
VPMDesktopObjects/Public/ENOVCustoCommandUtils.h/ENOVCustoCommandUtils/GetDoubleParameter

**Prototype:**`virtual HRESULT GetDoubleParameter(CATUnicodeString outName,double &outVal;);`| GA| [MINMV](CAACenAPIChangeDetail.htm#Abstract)| May require a modification of Imakefilakefile.mk.
VPMDesktopObjects/Public/ENOVCustoCommandUtils.h/ENOVCustoCommandUtils/GetIntParameter
VPMDesktopObjects/Public/ENOVCustoCommandUtils.h/ENOVCustoCommandUtils/GetDoubleParameter
VPMDesktopObjects/Public/ENOVCustoCommandUtils.h/ENOVCustoCommandUtils/GetBooleanParameter

**Prototype:**`virtual HRESULT GetBooleanParameter(CATUnicodeString outName,boolean &outVal;);`| GA| [MINMV](CAACenAPIChangeDetail.htm#Abstract)| May require a modification of Imakefilakefile.mk.
VPMDesktopObjects/Public/ENOVCustoCommandUtils.h/ENOVCustoCommandUtils/GetDoubleParameter
VPMDesktopObjects/Public/ENOVCustoCommandUtils.h/ENOVCustoCommandUtils/GetBooleanParameter
VPMDesktopObjects/Public/ENOVCustoCommandUtils.h/ENOVCustoCommandUtils/GetStringParameter

**Prototype:**`virtual HRESULT GetStringParameter(const CATUnicodeString& outName,CATUnicodeString& outVal);`| GA| [MINMV](CAACenAPIChangeDetail.htm#Abstract)| May require a modification of Imakefilakefile.mk.
VPMDesktopObjects/Public/ENOVCustoCommandUtils.h/ENOVCustoCommandUtils/GetBooleanParameter
VPMDesktopObjects/Public/ENOVCustoCommandUtils.h/ENOVCustoCommandUtils/GetStringParameter
VPMDesktopObjects/Public/ENOVCustoCommandUtils.h/ENOVCustoCommandUtils/GetObjParameter

**Prototype:**`virtual HRESULT GetObjParameter(CATUnicodeString outName,CATIVpmFactoryObject_var &oFactObj;);`| GA| [MINMV](CAACenAPIChangeDetail.htm#Abstract)| May require a modification of Imakefilakefile.mk.
VPMDesktopObjects/Public/ENOVCustoCommandUtils.h/ENOVCustoCommandUtils/GetStringParameter
VPMDesktopObjects/Public/ENOVCustoCommandUtils.h/ENOVCustoCommandUtils/GetObjParameter
VPMDesktopObjects/Public/ENOVCustoCommandUtils.h/ENOVCustoCommandUtils/GetObjListParameter

**Prototype:**`virtual HRESULT GetObjListParameter(CATUnicodeString inName,CATLISTV_CATIVpmFactoryObject_var_ &oFactObjList;);`| GA| [MINMV](CAACenAPIChangeDetail.htm#Abstract)| May require a modification of Imakefilakefile.mk.
