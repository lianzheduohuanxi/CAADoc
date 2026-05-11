---
```vbscript
title: "Closing a CATIA Document"
category: "use-case"
module: "CAAScdInfUseCases"
tags: ["CAAScdInfUseCases", "CAAInfReadDocument", "CAAInfOpenDocument", "CAAInfCloseDocument", "CATIA"]
source_file: "Doc/online/CAAScdInfUseCases/CAAInfCloseDocument.htm"
converted: "2026-05-11T17:31:52.350580"
```

---
## Infrastructure

|
## Closing a CATIA Document

* * *

  This macro shows you how to close an existing CATIA document that is currently in the session. It details the programming equivalent of the `File -> Close` command.
---|---
This macro shows you how to close an existing CATIA document that is currently in the session. It details the programming equivalent of the `File -> Close` command.
  CAAInfCloseDocument is launched in CATIA [1]. An existing document called "CAAInfReadDocument.CATPart" must be found in the CATDocView. [CAAInfCloseDocument.CATScript ](CAAInfCloseDocumentSource.md)is located in the CAAScdInfUseCases module. [Execute macro](macros/CAAInfCloseDocument.CATScript) (Windows only).
  CAAInfCloseDocument includes four steps:

  1. Retrieving the CATDocView Environment Variable and Checking its Valuation
  2. Closing the Active CATIA Document
  3. Closing the CATIA Document Specified by an Object Variable
  4. Closing the CATIA Document Specified by its Name

#### Retrieving the CATDocView Environment Variable and Checking its Valuation

|

```vbscript
```vbscript
    'Optional: allows to find the sample wherever it's installed

```

```

```vbscript
          Dim sDocPath As String
```vbscript
```vbscript
          sDocPath=CATIA.SystemService.Environ("CATDocView")

          If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
              Err.Raise 9999,,"No Doc Path Defined"
          End If

```

```

```

```vbscript
Err.Raise 9999,,"No Doc Path Defined"
```

End If
Define the `sDocPath` variable to retrieve the CATDocView environment variable value which holds the documentation path where the Part document used below is stored. Also, check that this variable is valuated. [Top]

#### Closing the Active CATIA Document

|

      ...

```vbscript
        'Open the document.
```

```vbscript
         Dim iPartDoc As Document
```vbscript
         Set iPartDoc = CATIA.Documents.**Open**(sDocPath & _
```

```

           "\online\CAAScdInfUseCases\samples\CAAInfReadDocument.CATPart")
```vbscript
```vbscript
```vbscript
'Open the document.
Dim iPartDoc As Document
Set iPartDoc = CATIA.Documents.**Open**(sDocPath & _
        'Close the active document which is the document just opened.
```

```

```

         **CATIA.ActiveDocument.Close()**

      ...

---

An existing CATIA document is opened using the `Open` method of the _Documents_ collection (_Documents_ object). See the CAAInfOpenDocument [2] sample for a description of how to open a CATIA document. Because the `Open` method also activates the opened document, you can use the `Close` method of the `ActiveDocument` property of the CATIA application in order to close it: the document is thus removed from the _Documents_ collection and all the windows that contain it are also closed and removed from the _Windows_ collection.

[Top]

|
#### Closing the CATIA Document Specified by an Object Variable

|

      ...

```vbscript
        'Open the same document again.
```

```vbscript
         Set iPartDoc = CATIA.Documents.**Open**(sDocPath & _
```

           "\online\CAAScdInfUseCases\samples\CAAInfReadDocument.CATPart")
```vbscript
```vbscript
```vbscript
'Open the same document again.
Set iPartDoc = CATIA.Documents.**Open**(sDocPath & _
        'Close the document using the variable defined for it.
```

```

```

         **iPartDoc.Close()**

      ...

---

A second way of closing an existing CATIA document is to execute the `Close` method directly on the object variable already assigned to handle the document: the document is thus removed from the _Documents_ collection and all the windows that contain it are also closed and removed from the _Windows_ collection.

[Top]

|
#### Closing the CATIA Document Specified by its Name

|

      ...

```vbscript
         'Open the same document a third time.
```

```vbscript
          Set iPartDoc = CATIA.Documents.**Open**(sDocPath & _
```

            "\online\CAAScdInfUseCases\samples\CAAInfReadDocument.CATPart")
```vbscript
```vbscript
```vbscript
'Open the same document a third time.
Set iPartDoc = CATIA.Documents.**Open**(sDocPath & _
         'Close the document by specifying its name.
```

```

```

          **CATIA.Documents.Item( "CAAInfReadDocument.CATPart").Close()**
      ...

---

Finally, the third way of closing a CATIA document is to execute the `Close` method on the name of the document which is itself retrieved using the _Documents_ collection's `Item` method: the document is thus removed from the _Documents_ collection and all the windows that contain it are also closed and removed from the _Windows_ collection.

[Top]

* * *
#### In Short

This use case has shown the three ways of closing an existing CATIA document during an interactive session:

  * Using the `ActiveDocument` property of the CATIA application
  * Using the variable assigned to handle the document
  * Using the name of the document retrieved from the _Documents_ collection by the `Item` method

[Top]

* * *
#### References

[1] | [Replaying a Macro](CAAInfLauchMacro.md)
---|---
[2] | [Opening an Existing CATIA Document](CAAInfOpenDocument.md)
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
