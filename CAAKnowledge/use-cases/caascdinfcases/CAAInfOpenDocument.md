---
```vbscript
title: "Opening an Existing CATIA Document"
category: "use-case"
module: "CAAScdInfUseCases"
tags: ["CAAScdInfUseCases", "CAAInfReadDocument", "CAAInfOpenDocument", "CAAInfCloseDocument", "CATIA", "CAAInfSaveDocument"]
source_file: "Doc/online/CAAScdInfUseCases/CAAInfOpenDocument.htm"
converted: "2026-05-11T17:31:52.383001"
```

---
## Infrastructure

 |
 ## Opening an Existing CATIA Document

 * * *

  This macro shows you how to open an existing CATIA document. It details the programming equivalent of the `File -> Open` command.
 ---|---
This macro shows you how to open an existing CATIA document. It details the programming equivalent of the `File -> Open` command.
  CAAInfOpenDocument is launched in CATIA [1]. An existing document called "CAAInfReadDocument.CATPart" must be found in the CATDocView. [CAAInfOpenDocument.CATScript](CAAInfOpenDocumentSource.md) is located in the CAAScdInfUseCases module. [Execute macro](macros/CAAInfOpenDocument.CATScript) (Windows only).
  CAAInfOpenDocument includes two steps:
     1. Retrieving the CATDocView Environment Variable and Checking its Valuation
     2. Opening an existing CATIA document

 **Retrieving the CATDocView Environment Variable and Checking its Valuation** |
CAAInfOpenDocument is launched in CATIA [1]. An existing document called "CAAInfReadDocument.CATPart" must be found in the CATDocView. [CAAInfOpenDocument.CATScript](CAAInfOpenDocumentSource.md) is located in the CAAScdInfUseCases module. [Execute macro](macros/CAAInfOpenDocument.CATScript) (Windows only).
CAAInfOpenDocument includes two steps:
1. Retrieving the CATDocView Environment Variable and Checking its Valuation
2. Opening an existing CATIA document
```vbscript
```vbscript
     ' Optional: allows to find the sample wherever it's installed

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

 #### Opening an Existing CATIA Document

 |

     ...
```vbscript
         Dim iPartDoc As Document
```vbscript
         Set iPartDoc = CATIA.Documents.**Open**(sDocPath & _
```

```

            "\online\CAAScdInfUseCases\samples\CAAInfReadDocument.CATPart")
       ...

 ---

 An existing CATIA document is opened using the `Open` method of the _Documents_ collection (_Documents_ object). The only argument to this method must contain the entire storage path and name specifying where the document is to be found. This single statement opens the document stored in the file and adds it to the end of the collection of documents. It also creates and displays a new window for the document. Both document and window are activated. Note that if any changes to the opened document occur, the document should be saved at the end of the session. See the CAAInfSaveDocument [2] sample for an illustration of how to save an opened document. In any case, the opened document should also be closed at the end of the session. See the CAAInfCloseDocument [3] sample for an illustration of how to close an opened document.

 [Top]

 * * *
 #### In Short

 This use case has shown how to open an existing CATIA document during an interactive session.

 [Top]

 * * *
 #### References

 [1] | [Replaying a Macro](CAAInfLauchMacro.md)
 ---|---
 [2] | [Saving an Existing CATIA Document](CAAInfSaveDocument.md)
 [3] | [Closing a CATIA Document](CAAInfCloseDocument.md)
 [Top]

 * * *

 _Copyright 2001, Dassault Systmes. All rights reserved._
