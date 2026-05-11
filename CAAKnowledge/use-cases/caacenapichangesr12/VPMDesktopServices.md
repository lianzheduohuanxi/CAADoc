---
```vbscript
title: "VPMDesktopServices Modifications"
category: "use-case"
module: "CAACenAPIChangesR12"
version: "V5R12"
tags: []
source_file: "Doc/online/CAACenAPIChangesR12/VPMDesktopServices.htm"
converted: "2026-05-11T17:33:50.621304"
```

---
tags: []
source_file: "Doc/online/CAACenAPIChangesR12/VPMDesktopServices.htm"
converted: "2026-05-11T17:33:50.621304"
CAA C++ API Modifications|  VPMDesktopServices  |   

* * *

**Entity|  SP| Modification| To Do** | VPMDesktopServices/Public/VPMIQAttribute.h/VPMIQAttribute/GetObject| GA| MRTHC| For performance purpose, return value has been changed to a reference on a const object. Code that used to modify the returned value must now create a copy.  
---|---|---|---  
VPMDesktopServices/Public/VPMIQAttribute.h/VPMIQAttribute/GetName| GA| MRTHC| idem  
VPMDesktopServices/Public/VPMIQAttribute.h/VPMIQAttribute/GetAlias| GA| MRTHC| idem  
VPMDesktopServices/Public/VPMIQAttribute.h/VPMIQAttribute/GetFamily| GA| MRTHC| idem  
VPMDesktopServices/Public/VPMIQAttribute.h/VPMIQAttribute/GetFormat| GA| MRTHC| idem  
VPMDesktopServices/Public/VPMIQAttribute.h/VPMIQAttribute/GetDefaultValue| GA| MRTHC| idem  
VPMDesktopServices/Public/VPMIQAttribute.h/VPMIQAttribute/GetListOfValues| GA| MRTHC| idem  
VPMDesktopServices/Public/VPMIQAttribute.h/VPMIQAttribute/GetAuthorizedValues| GA| MRTHC| idem  
VPMDesktopServices/Public/VPMIQAttribute.h/VPMIQAttribute/GetHelpValues| GA| MRTHC| idem
