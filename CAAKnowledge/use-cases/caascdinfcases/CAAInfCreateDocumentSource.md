---
```vbscript
title: "CAAInfCreateDocument.CATScript"
category: "use-case"
module: "CAAScdInfUseCases"
tags: ["CATIA", "CAAInfCreateDocument"]
source_file: "Doc/online/CAAScdInfUseCases/CAAInfCreateDocumentSource.htmmd"
converted: "2026-05-11T17:31:52.356061"
```

---
tags: ["CATIA", "CAAInfCreateDocument"]
source_file: "Doc/online/CAAScdInfUseCases/CAAInfCreateDocumentSource.htmmd"
converted: "2026-05-11T17:31:52.356061"
    Option Explicit

```vbscript
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2001
    ' *****************************************************************************
    '   Purpose:       Create a New Document.
    '   Assumtions:   None
    '   Author:
    '   Languages:   VBScript
    '   Locales:        English
    '   CATIA Level:  V5R7
    ' *****************************************************************************

```

```

```

```vbscript
```vbscript
    Sub CATMain(#)

```

```

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
```vbscript
        Dim oNewPartDoc As Document
```vbscript
```
```vbscript
```vbscript
        Set oNewPartDoc = CATIA.Documents.Add("Part")

```
```

```

```

```vbscript
```vbscript
    End Sub

```
```
