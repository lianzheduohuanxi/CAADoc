---
```vbscript
title: "LiteralFeatures Modifications"
category: "use-case"
module: "CAACenAPIChangesR7"
version: "V5R7"
tags: ["CATIParmPublisher", "CAALifServices", "CATIParmPublisherNew"]
source_file: "Doc/online/CAACenAPIChangesR7/LiteralFeatures.htm"
converted: "2026-05-11T17:33:52.117776"
```

---
tags: ["CATIParmPublisher", "CAALifServices", "CATIParmPublisherNew"]
source_file: "Doc/online/CAACenAPIChangesR7/LiteralFeatures.htm"
converted: "2026-05-11T17:33:52.117776"
CAA API Modifications|  LiteralFeatures  |

* * *

**Entity|  Modification| To Do** | LiteralFeatures/Protected/CATCkeEvalContext.h/CATCkeEvalContext/Relation| INDM| Check that you don't use it. Not useful for the CAA programmer. The relation can be retrieved either by its parameters or by the relation set.
---|---|---
LiteralFeatures/Protected/CATCkeEvalContext.h/CATCkeEvalContext/Container| INDM| Check that you don't use it. The container must be retrieved by a none knowledgeware API (from the document, for instance). See CAALifServices use case.
LiteralFeatures/Protected/CATIParmPublisherNew.h| LHC| Use CATIParmPublisher instead.
