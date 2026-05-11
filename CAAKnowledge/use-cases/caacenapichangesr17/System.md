---
```vbscript
title: "System Framework Modifications in V5R17"
category: "use-case"
module: "CAACenAPIChangesR17"
version: "V5R17"
tags: ["CATIUExitCryptedILockBytes"]
source_file: "Doc/online/CAACenAPIChangesR17/System.htm"
converted: "2026-05-11T17:33:51.378408"
```

---
# CAA C++ API Modifications  

| 
##  System Framework Modifications in V5R17 

* * *

**Entity|  SP| Modification| To Do** | System/Public/CATIUExitCryptedILockBytes.h/CATIUExitCryptedILockBytes/Open  
**Prototype:**`virtual HRESULT Open(const CATUC2Bytes* iPath,DWORD iMode,CATSysOpenMode iOpenMode,CATSysSharing iSharingMode,CATSysCreateMode iOpenFlag,CATSysCloseMode iCloseFlag= CATSys_Close)=0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| This method had bene renamed into OpenW to avoid confusion with the other Open method. Depending on the platform compiler, the same source code could call one or the other.  
---|---|---|---  
System/Public/CATIUExitCryptedILockBytes.h/CATIUExitCryptedILockBytes/OpenW  
**Prototype:**`virtual HRESULT OpenW(const CATUC2Bytes* iPath,DWORD iMode,CATSysOpenMode iOpenMode,CATSysSharing iSharingMode,CATSysCreateMode iOpenFlag,CATSysCloseMode iCloseFlag= CATSys_Close)=0;`| GA| [NPVM](CAACenAPIChangeDetail.htm#Abstract)| Consequence of the preceeding. Just rename the Open method of your implementation into OpenW.
