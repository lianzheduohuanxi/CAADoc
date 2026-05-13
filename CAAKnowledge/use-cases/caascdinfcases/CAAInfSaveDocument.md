---
title: "Saving an Existing CATIA Document"
category: "use-case"
module: "CAAScdInfUseCases"
tags: "["CAAInfSaveAsDocument", "CAAScdInfUseCases", "CAAInfReadDocument", "CAAInfOpenDocument", "CAAInfCloseDocument", "CATIA", "CAAInfSaveDocument"]"
source_file: "Doc/online/CAAScdInfUseCases/CAAInfSaveDocument.htm"
converted: "2026-05-11T17:31:52.395470"
---
|
 ## Infrastructure

 |
 ## Saving an Existing CATIA Document

 * * *

  This macro shows you how to save an existing CATIA document that is currently in the session. In order to save a new CATIA document, see the CAAInfSaveAsDocument [1] sample for a detailed description. This sample details the programming equivalent of the `File -> Save` command.
 ---|---
This macro shows you how to save an existing CATIA document that is currently in the session. In order to save a new CATIA document, see the CAAInfSaveAsDocument [1] sample for a detailed description. This sample details the programming equivalent of the `File -> Save` command.
  CAAInfSaveDocument is launched in CATIA [2]. An existing document called "CAAInfReadDocument.CATPart" must be found in the CATDocView. [CAAInfSaveDocument.CATScript ](CAAInfSaveDocumentSource.md)is located in the CAAScdInfUseCases module. [Execute macro](macros/CAAInfSaveDocument.CATScript) (Windows only).
  CAAInfSaveDocument includes four steps:
     1. Retrieving the CATDocView Environment Variable and Checking its Valuation
     2. Saving the Active CATIA Document
     3. Saving the CATIA Document Specified by an Object Variable
     4. Saving the CATIA Document Specified by its Name

 #### Retrieving the CATDocView Environment Variable and Checking its Valuation

 |
3. Saving the CATIA Document Specified by an Object Variable
4. Saving the CATIA Document Specified by its Name
```vbscript
```vbscript
     'Optional: allows to find the sample wherever it's installed

```

```

```vbscript
```vbscript
           Dim sDocPath  As String
```vbscript
```
```vbscript
```cpp
           sDocPath=CATIA.SystemService.Environ("CATDocView")

           If (Not CATIA.FileSystem.FolderExists(sDocPath))  Then
              Err.Raise 9999,,"No Doc Path Defined"
           End If
```

```

```

```

```vbscript
```vbscript
Err.Raise 9999,,"No Doc Path Defined"
```
```

End If
 Define the `sDocPath` variable to retrieve the CATDocView environment variable value which holds the documentation path where the Part document used below is stored. Also, check that this variable is valuated. [Top]

 #### Saving the Active CATIA Document

 |

     ...
```vbscript
```vbscript
```vbscript
         'Open the document and add it as the last item of the collection of documents.
         'Create and display a new window for the document.
         'Activate the document and its window.
```

```

```

```vbscript
```vbscript
          Dim iPartDoc As Document
```vbscript
```
```cpp
          Set iPartDoc = CATIA.Documents.**Open**(sDocPath & _
```
```

```

            "/online/CAAScdInfUseCases/samples/CAAInfReadDocument.CATPart")
```vbscript
```vbscript
Dim iPartDoc As Document
```vbscript
```
```vbscript
```cpp
Set iPartDoc = CATIA.Documents.**Open**(sDocPath & _
         'The document just opened is the active document.
```
         'Save the active document and then close it.
```

```

```

```cpp
          **CATIA.ActiveDocument.Save(#)**
          **CATIA.ActiveDocument.Close(#)**

     ...
```

 ---

 An existing CATIA document is opened using the `Open` method of the _Documents_ collection (_Documents_ object). See the CAAInfOpenDocument [3] sample for a description of how to open a CATIA document. Because the `Open` method also activates the opened document, you can use the `Save` method of the `ActiveDocument` property of the CATIA application in order to save it: the document is saved in the same storage location and under the same name. Note that before exiting the session, the document should also be closed. See the CAAInfCloseDocument [4] sample for a description of how to close a document.

 [Top]

 |
 #### Save the CATIA Document Specified by an Object Variable

 |

     ...
```vbscript
     'Open the same document again.
```

```vbscript
```cpp
          Set iPartDoc = CATIA.Documents.**Open**(sDocPath & _
```
```

            "/online/CAAScdInfUseCases/samples/CAAInfReadDocument.CATPart")
```vbscript
```vbscript
```vbscript
'Open the same document again.
```cpp
Set iPartDoc = CATIA.Documents.**Open**(sDocPath & _
         'Save the document just opened using the variable name defined for it.
```
         'Then, close the document in the same way.
```

```

```

          **iPartDoc.Save(#)
          iPartDoc.Close(#)**

       ...

 ---

 The same document is opened a second time. Another way of saving an existing CATIA document is to execute the `Save` method directly on the variable already assigned to handle the document: the document is saved in the same storage location and under the same name. Note that before exiting the session, the document should also be closed.

 [Top]

 |
 #### Save the CATIA Document Specified by its Name

 |

     ...
```vbscript
     'Open the same document a third time.
```

```vbscript
```cpp
          Set iPartDoc = CATIA.Documents.**Open**(sDocPath & _
```
```

            "/online/CAAScdInfUseCases/samples/CAAInfReadDocument.CATPart")
```vbscript
```vbscript
```vbscript
'Open the same document a third time.
```cpp
Set iPartDoc = CATIA.Documents.**Open**(sDocPath & _
         'Save the document by specifying its name and then close it in the same way.
```
```

```

```

```cpp
          **CATIA.Documents.Item( "CAAInfReadDocument.CATPart").Save(#)
```vbscript
```
```vbscript
```cpp
          CATIA.Documents.Item("CAAInfReadDocument.CATPart").Close(#)**

```
```

```

       ...

 ---

 The same document is opened one last time. The third way of saving a CATIA document is by executing the `Save` method on the document that has been retrieved from the _Documents_ collection by specifying its name to the argument of the `Item` method: the document is saved in the same storage location and under the same name. Note that before exiting the session, the document should also be closed.

 [Top]

 * * *
 #### In Short

 This use case has shown the three ways of saving an existing CATIA document during an interactive session:

     * Using the `ActiveDocument` property of the CATIA application
     * Using the variable assigned to handle the document
     * Using the name of the document retrieved from the _Documents_ collection by the `Item` method

 In all three cases, the document is saved under the same storage path and name.

 [Top]

 * * *
 #### References

 [1] | [Saving a New CATIA Document](CAAInfSaveAsDocument.md)
 ---|---
 [2] | [Replaying a Macro](CAAInfLauchMacro.md)
 [3] | [Opening an Existing CATIA Document](CAAInfOpenDocument.md)
 [4] | [Closing a CATIA Document](CAAInfCloseDocument.md)
 [Top]

 * * *

 _Copyright 2001, Dassault Systmes. All rights reserved._
