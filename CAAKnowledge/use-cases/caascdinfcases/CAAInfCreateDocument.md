---
```vbscript
title: "Creating a New CATIA Document"
category: "use-case"
module: "CAAScdInfUseCases"
tags: ["CAAScdInfUseCases", "CAAInfSaveAsDocument", "CAAInfCloseDocument", "CAAInfCreateDocument", "CATIA"]
source_file: "Doc/online/CAAScdInfUseCases/CAAInfCreateDocument.htm"
converted: "2026-05-11T17:31:52.355066"
```

---
|
## Infrastructure

|
## Creating a New CATIA Document

* * *

  This macro shows you how to create a new CATIA document. It details the programming equivalent to the `File -> New` command.
---|---
This macro shows you how to create a new CATIA document. It details the programming equivalent to the `File -> New` command.
  CAAInfCreateDocument is launched in CATIA [1]. No opened document is needed. [CAAInfCreateDocument.CATScript](CAAInfCreateDocumentSource.md) is located in the CAAScdInfUseCases module. [Execute macro](macros/CAAInfCreateDocument.CATScript) (Windows only).
  CAAInfCreateDocument includes one step:

  1. Creating a new CATIA Document

#### Creating a New CATIA Document

|

      ...
```vbscript
```vbscript
```vbscript
        'Create a new part document.
        'Add the new document to the end of the collection of documents.
        'Create and display a new window for the new document.
        'Activate the new document and the window.
```

```

```

```vbscript
         Dim oNewPartDoc As Document
```vbscript
         Set oNewPartDoc = CATIA.Documents.**Add**("Part")
```

```

      ...

---

A new CATIA document is created using the `Add` method of the _Documents_ collection (_Documents_ object). The type of document to be created must be specified to the `Add` method. This type can be a part, an assembly, or a drawing. You would then use `Part`, `Product`, or `Drawing` type respectively as the argument to the `Add` method. In this case, a `Part` document is created. The new document is added to the end of the collection of documents. A new window for the document is also created and displayed. Both document and window are activated. Note that the existence of the new document is limited to the CATIA session. To be persistent, the document must be saved. See the CAAInfSaveAsDocument [2] sample for an illustration of how to save the new document. Note also that the newly created document should also be closed at the end of the session. See the CAAInfCloseDocument [3] sample for an illustration of how to close the new document.

[Top]

* * *
#### In Short

This use case has shown how to create a new CATIA document during an interactive session.

[Top]

* * *
#### References

[1] | [Replaying a Macro](CAAInfLauchMacro.md)
---|---
[2] | [Saving a New CATIA Document](CAAInfSaveAsDocument.md)
[3] | [Closing a CATIA Document](CAAInfCloseDocument.md)
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
