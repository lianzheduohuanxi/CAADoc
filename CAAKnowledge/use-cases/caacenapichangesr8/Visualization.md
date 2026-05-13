---
```vbscript
title: "Visualization Modifications"
category: "use-case"
module: "CAACenAPIChangesR8"
version: "V5R8"
tags: ["CATInfoDeviceEvent"]
source_file: "Doc/online/CAACenAPIChangesR8/Visualization.htmmd"
converted: "2026-05-11T17:33:52.717886"
```

---
tags: ["CATInfoDeviceEvent"]
source_file: "Doc/online/CAACenAPIChangesR8/Visualization.htmmd"
converted: "2026-05-11T17:33:52.717886"
CAA C++ API Modifications|  Visualization  |

* * *

**Entity|  SP| Modification| To Do** | Visualization/Protected/CAT2DRep.h/CAT2DRep/OkToDraw| GA| INDM| Check that you don't use it
---|---|---|---
Visualization/Protected/CATSO.h/CATSO/AddElement| GA| MRTHC|
Visualization/Protected/CAT2DViewpoint.h/CAT2DViewpoint/GetTranslationBounds| GA| INDM| Check that you don't use it
Visualization/Protected/CAT3DArcEllipseRep.h/CAT3DArcEllipseRep/BuildArcEllipse| GA| MHBDM|
Visualization/Protected/CAT3DMarkerGP.h/CAT3DMarkerGP/CAT3DMarkerGP| GA| MHBDM|
Visualization/Protected/CAT3DViewpoint.h/CAT3DViewpoint/GetTarget| GA| INDM| Check that you don't use it
Visualization/Protected/CATGraphicPathElement.h/CATGraphicPathElement/CATGraphicPathElement| GA| MHBDM|
Visualization/Protected/CATViewer.h/CATViewer/Pick| GA| MHBDM|
Visualization/Protected/CATDeviceBox.h| GA| FHBD| Now Use CATVRManager
Visualization/Protected/CATDeviceEventDispatcher.h| GA| FHBD| Now Use CATVRManager,CATVRDispatcherOnIdle,CATVRDispatcher
Visualization/Protected/CATDeviceField.h| GA| FHBD| Now Use CATVRDeviceEvent
Visualization/Protected/CATDeviceGenericField.h| GA| FHBD| Now Use CATVRDeviceEvent
Visualization/Protected/CATInfoDeviceEvent.h| GA| FHBD| Now Use CATVRDeviceEvent
Visualization/Protected/CATVRDeviceEvent.h/CATVRDeviceEvent/NextEvent| GA| INDM| Check that you don't use it
Visualization/Protected/CATVRDeviceEvent.h/CATVRDeviceEvent/PreviousEvent| GA| INDM| Check that you don't use it
Visualization/Protected/CATVRDeviceEvent.h/CATVRDeviceEvent/TailEvent| GA| INDM| Check that you don't use it
Visualization/Protected/CATVRDeviceEvent.h/CATVRDeviceEvent/GetName| GA| MHBDM|
Visualization/Protected/CATVRDeviceEvent.h/CATVRDeviceEvent/GetNumber| GA| INDM| Check that you don't use it
Visualization/Protected/CATVRDeviceEvent.h/CATVRDeviceEvent/CATVRDeviceEvent| GA| INDM| Check that you don't use it
Visualization/Protected/CATVRDeviceEvent.h/CATVRDeviceEvent/GetPriority| GA| MHBDM|
Visualization/Protected/CATVRDeviceEvent.h/CATVRDeviceEvent/GetDeviceBox| GA| MHBDM|
Visualization/Protected/CATVRNotification.h/CATVRNotification/GetCATVRDeviceEvent| GA| MHBDM|
