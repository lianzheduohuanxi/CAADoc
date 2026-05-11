---
```vbscript
title: "Moved C++ Authorized APIs in CAA V5R14 GA"
category: "use-case"
module: "CAACenQuickRefs"
tags: []
source_file: "Doc/online/CAACenQuickRefs/CAACenV5R14GAMovedCPPAPI.htm"
converted: "2026-05-11T17:33:47.155397"
```

---
tags: []
source_file: "Doc/online/CAACenQuickRefs/CAACenV5R14GAMovedCPPAPI.htm"
converted: "2026-05-11T17:33:47.155397"
CAA V5 Encyclopedia |  Moved C++ Authorized APIs in CAA V5R14 GA

* * *

The following Authorized APIs are moved from VPMInterfaces to ENOVInterfaces in V5R14. Modules using the moved Authorized APIs should have the module **GUIDENOVInterfaces.m** added to, and possibly replacing **GUIDVPMInterfaces.m** , to their `LINK_WITH `statement of their Imakefile.mk file and possibly add the **ENOVInterfaces** framework as a prerequisite in the IdentityCard of their frameworks.

  * ENOVInterfaces framework
    * Class  CATListOfVPMIWflActivity
    * Class  CATListOfVPMIWflApplication
    * Class  CATListOfVPMIWflData
    * Class  CATListOfVPMIWflParticipant
    * Class  CATListOfVPMIWflProcess
    * Class  CATListOfVPMIWflRegularActivity
    * Class  CATListOfVPMIWflTransition
    * Global Function  GetWflApplicationHandler
    * Global Function  GetWflCreationMgr
    * Interface  VPMIWflActivity
    * Interface  VPMIWflActivityListener
    * Interface  VPMIWflApplication
    * Interface  VPMIWflApplicationHandler
    * Interface  VPMIWflCmdRequest
    * Interface  VPMIWflCreation
    * Interface  VPMIWflData
    * Interface  VPMIWflDataListener
    * Interface  VPMIWflParticipant
    * Interface  VPMIWflProcess
    * Interface  VPMIWflProcessListener
    * Interface  VPMIWflQuery
    * Interface  VPMIWflRegularActivity
    * Interface  VPMIWflTransition
    * Interface  VPMIWflUserExit

[Top]

* * *

History Version: **1** [Jul 2004] | Document created
---|---
[Top]

* * *

_Copyright 1994-2004, Dassault Systmes. All rights reserved._
