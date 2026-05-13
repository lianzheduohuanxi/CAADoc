---
title: "CATPDMBase Framework Modifications in V5R19"
category: "use-case"
module: "CAACenAPIChangesR23"
tags: "["CATIDomain", "CATIDocId"]"
source_file: "Doc/online/CAACenAPIChangesR23/CATPDMBase.htm"
converted: "2026-05-11T17:33:51.776615"
---
# CAA C++ API Modifications

|
##  CATPDMBase Framework Modifications in V5-6R2013

* * *

**Entity|  SP| Modification| To Do** | CATPDMBase/Public/CATIDomain.h| GA| [FHBD ](CAACenAPIChangeDetail.htm#Abstract)| Interface was not implemented, so was useless and has been removed.
---|---|---|---
CATPDMBase/Public/CATPDMServices.h/CATPDMServices/LoadNomadSession
**Prototype:**`LoadNomadSession(CATUnicodeString, CATLISTP(CATIDocId), CATLISTP(CATDocument));`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| The product providing the corresponding capability has been withdrawn, so methods have been removed.
CATPDMBase/Public/CATPDMServices.h/CATPDMServices/LoadNomadSession
CATPDMBase/Public/CATPDMServices.h/CATPDMServices/NomadDocumentProperties

**Prototype:**`NomadDocumentProperties(CATUnicodeString, CATLISTP(CATDocument), CATListOfCATBoolean, CATListOfCATUnicodeString);`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)
CATPDMBase/Public/CATPDMServices.h/CATPDMServices/LoadNomadSession
CATPDMBase/Public/CATPDMServices.h/CATPDMServices/NomadDocumentProperties
CATPDMBase/Public/CATPDMServices.h/CATPDMServices/ReplaceDocument

**Prototype:**`ReplaceDocument(CATDocument*);`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)
CATPDMBase/Public/CATPDMServices.h/CATPDMServices/NomadDocumentProperties
CATPDMBase/Public/CATPDMServices.h/CATPDMServices/ReplaceDocument
CATPDMBase/Public/CATPDMServices.h/CATPDMServices/ReplicateDocument

**Prototype:**`ReplicateDocument(CATUnicodeString, CATDocument*);`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)
