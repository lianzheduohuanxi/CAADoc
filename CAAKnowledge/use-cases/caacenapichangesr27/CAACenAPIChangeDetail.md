---
title: "Detail Of C++ API Changes"
category: "api-changes"
module: "CAACenAPIChangesR27"
version: "V5R27"
tags: ["CAA2Usage", "CAA2Level", "CATIMciMultiCADSettingAtt"]
source_file: "Doc/online/CAACenAPIChangesR27/CAACenAPIChangeDetail.htm"
converted: "2026-05-11T17:33:51.873433"
---

|  |  Detail Of V5-6R2017 C++ API Changes _What changes in the API compared with CAA V5-6R2016_  
---|---|---  
Technical Article  
  
* * *

Abstract This article presents by frameworks the detail of CAA C++ resources modified in V5-6R2017 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities. Possibly impacting modifications are highlighted in red.  
| Classification | Meaning  
---|---  
LHC | @CAA2Level Has Changed: a L1 file is no more L1.  
UHC | @CAA2Usage Has Changed: usage has changed for a more restricted usage. For example a class tagged as derivable is not derivable anymore.  
CHBD | Class Has Been Deleted  
FHBD | File Has Been Deleted  
ADVHC | Argument Default Value Has Changed  
MHBDM | Method Has Been Deleted or Modified  
MRTHC | Method Returned Type Has Changed  
NPVM | New Pure Virtual Method. A new pure virtual method has been added on a derivable class or on an interface to be implemented without an adapter.   
INDM | Method is no more documented. It does not break your code in any way but means that you are not supposed to use it anymore. Check that you don't use it or look for replacement information.    
MINMV | Method is no more virtual. If occurs on a U1 class, may require modifications in Imakefile.mk of client code. If occurs on a U2 class, see details on the documentation of the concerned resource modification.  
   
  
* * *

Framework | Header | Class | Method | Signature | Modification | To Do  
---|---|---|---|---|---|---  
CATMultiCADInterfaces | CATIMciMultiCADSettingAtt.h | CATIMciMultiCADSettingAtt | GetIdeasComponentName| virtual HRESULT GetIdeasComponentName(CATUnicodeString amp; oIdeasComponentName)= 0 | MHBDM | The corresponding settings do not exist anymore, so the API have been modified accordingly.  
GetIdeasComponentNameInfo| virtual HRESULT GetIdeasComponentNameInfo(CATSettingInfo* oInfo)= 0  
GetIdeasComponentType| virtual HRESULT GetIdeasComponentType(int amp; oIdeasComponentType)= 0  
GetIdeasComponentTypeInfo| virtual HRESULT GetIdeasComponentTypeInfo(CATSettingInfo* oInfo)= 0  
GetIdeasLibraryName| virtual HRESULT GetIdeasLibraryName(CATUnicodeString amp; oIdeasLibraryName)= 0  
GetIdeasLibraryNameInfo| virtual HRESULT GetIdeasLibraryNameInfo(CATSettingInfo* oInfo)= 0  
GetIdeasPartNumber| virtual HRESULT GetIdeasPartNumber(CATUnicodeString amp; oIdeasPartNumber)= 0  
GetIdeasPartNumberInfo| virtual HRESULT GetIdeasPartNumberInfo(CATSettingInfo* oInfo)= 0  
GetIdeasProjectName| virtual HRESULT GetIdeasProjectName(CATUnicodeString amp; oIdeasProjectName)= 0  
GetIdeasProjectNameInfo| virtual HRESULT GetIdeasProjectNameInfo(CATSettingInfo* oInfo)= 0  
GetIdeasRevNumber| virtual HRESULT GetIdeasRevNumber(CATUnicodeString amp; oIdeasRevNumber)= 0  
GetIdeasRevNumberInfo| virtual HRESULT GetIdeasRevNumberInfo(CATSettingInfo* oInfo)= 0  
GetIdeasTessParam| virtual HRESULT GetIdeasTessParam(float amp; oParam)= 0  
GetIdeasTessParamInfo| virtual HRESULT GetIdeasTessParamInfo(CATSettingInfo* oInfo)= 0  
GetIdi3dAnnotationMode| virtual HRESULT GetIdi3dAnnotationMode(int amp; oMode)= 0  
GetIdi3dAnnotationModeInfo| virtual HRESULT GetIdi3dAnnotationModeInfo(CATSettingInfo* oInfo)= 0  
SetIdeasComponentName| virtual HRESULT SetIdeasComponentName(const CATUnicodeString amp; iIdeasComponentName)= 0  
SetIdeasComponentNameLock| virtual HRESULT SetIdeasComponentNameLock(unsigned char iLock)= 0  
SetIdeasComponentType| virtual HRESULT SetIdeasComponentType(const int amp; iIdeasComponentType)= 0  
SetIdeasComponentTypeLock| virtual HRESULT SetIdeasComponentTypeLock(unsigned char iLock)= 0  
SetIdeasLibraryName| virtual HRESULT SetIdeasLibraryName(const CATUnicodeString amp; iIdeasLibraryName)= 0  
SetIdeasLibraryNameLock| virtual HRESULT SetIdeasLibraryNameLock(unsigned char iLock)= 0  
SetIdeasPartNumber| virtual HRESULT SetIdeasPartNumber(const CATUnicodeString amp; iIdeasPartNumber)= 0  
SetIdeasPartNumberLock| virtual HRESULT SetIdeasPartNumberLock(unsigned char iLock)= 0  
SetIdeasProjectName| virtual HRESULT SetIdeasProjectName(const CATUnicodeString amp; iIdeasProjectName)= 0  
SetIdeasProjectNameLock| virtual HRESULT SetIdeasProjectNameLock(unsigned char iLock)= 0  
SetIdeasRevNumber| virtual HRESULT SetIdeasRevNumber(const CATUnicodeString amp; iIdeasRevNumber)= 0  
SetIdeasRevNumberLock| virtual HRESULT SetIdeasRevNumberLock(unsigned char iLock)= 0  
SetIdeasTessParam| virtual HRESULT SetIdeasTessParam(const float amp; iParam)= 0  
SetIdeasTessParamLock| virtual HRESULT SetIdeasTessParamLock(unsigned char iLock)= 0  
SetIdi3dAnnotationMode| virtual HRESULT SetIdi3dAnnotationMode(const int amp; iMode)= 0  
SetIdi3dAnnotationModeLock| virtual HRESULT SetIdi3dAnnotationModeLock(unsigned char iLock)= 0  
System | CATUnicodeString.h | CATUnicodeString | BuildFromNum | int BuildFromNum(unsigned int iIntegerValue,const char*iCFormat=quot;%dquot;) | MHBDM | Default format is now unsigned int, in sync with expected type. Should not impact Apps : it corrects latent errors when strings are initialized with big numbers.  
References

* * *

History Version: **1** [Sep 2015] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2015, Dassault Systmes. All rights reserved._
