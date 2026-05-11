---
title: "Untitled"
category: "use-case"
module: "CAAScdInfUseCases"
tags: ["CAAScrBase", "CAAInfLauchMacro", "CAAInfCloseDocument", "CAAScdInfUseCases", "CAAInfCloseDocumentSource", "CAAInfReadDocument", "CAAInfOpenDocument", "CATIA", "CAAScrJavaScript"]
source_file: "Doc/online/CAAScdInfUseCases/CAAInfCloseDocument.htm"
converted: "2026-05-11T11:06:32.784642"
---

## Infrastructure
 
 
## []Closing a CATIA Document
 
 

---

 
 |![](../CAAScrBase/images/atarget.gif)
 

[]This macro shows you how to close an existing CATIA
 document that is currently in the session. It details the programming
 equivalent of the `File -> Close` command.
 

 
 
 
 
 |![](../CAAScrBase/images/ainfo.gif)
 

[]CAAInfCloseDocument is launched in CATIA [[1]].
 An existing document called "CAAInfReadDocument.CATPart" must be
 found in the CATDocView.
 

[CAAInfCloseDocument.CATScript
 ]is located in the CAAScdInfUseCases module. [Execute
 macro] (Windows only).
 

 
 
 
 
 |![](../CAAScrBase/images/ascenari.gif)
 

[]CAAInfCloseDocument includes four steps:
 

 
- [Retrieving the CATDocView Environment Variable
 and Checking its Valuation]
 
- [Closing the Active CATIA Document]
 
- [Closing the CATIA Document Specified by an
 Object Variable]
 
- [Closing the CATIA Document Specified by its
 Name]
 
 
#### []Retrieving the CATDocView Environment
 Variable and Checking its Valuation
 
 
 
```
'Optional: allows to find the sample wherever it's installed

 
Dim
 sDocPath 
As
 String
 sDocPath=CATIA.SystemService.Environ("CATDocView")

 
If
 (
Not
 CATIA.FileSystem.FolderExists(sDocPath))
 Then

 Err.Raise 9999,,"No Doc Path Defined"
 
End If
```

 
 
 

Define the `sDocPath` variable to retrieve the
 CATDocView environment variable value which holds the documentation path
 where the Part document used below is stored. Also, check that this
 variable is valuated.
 

[[Top]]
 
#### []Closing the Active CATIA Document
 
 
 
```
...
```

 ********
```
'Open the document.
 
 
Dim
 iPartDoc 
As
 Document
 
Set
 iPartDoc = CATIA.Documents.
Open
(sDocPath & _
 "\online\CAAScdInfUseCases\samples\CAAInfReadDocument.CATPart")

 
'Close the active document which is the document just opened.

 
CATIA.ActiveDocument.Close()

 ...
```

 
 
 
 

An existing CATIA document is opened using the `Open` method
 of the *Documents* collection (*Documents* object). See the
 CAAInfOpenDocument [[2]] sample for a description
 of how to open a CATIA document. Because the `Open` method also
 activates the opened document, you can use the `Close` method
 of the `ActiveDocument` property of the CATIA application in
 order to close it: the document is thus removed from the *Documents*
 collection and all the windows that contain it are also closed and removed
 from the *Windows* collection.
 

[[Top]]
 
 

 
 
#### []Closing the CATIA Document Specified by an
 Object Variable
 
 
 
```
...
```

 ********
```
'Open the same document again.

 
Set
 iPartDoc = CATIA.Documents.
Open
(sDocPath & _
 "\online\CAAScdInfUseCases\samples\CAAInfReadDocument.CATPart")

 
'Close the document using the variable defined for it.

 
iPartDoc.Close()

 ...
```

 
 
 
 

A second way of closing an existing CATIA document is to execute the `Close`
 method directly on the object variable already assigned to handle the
 document: the document is thus removed from the *Documents*
 collection and all the windows that contain it are also closed and removed
 from the *Windows* collection.
 

[[Top]]
 
 

 
 
#### []Closing the CATIA Document Specified by its
 Name
 
 
 
```
...
```

 ********
```
'Open the same document a third time.

 
Set
 iPartDoc = CATIA.Documents.
Open
(sDocPath & _
 "\online\CAAScdInfUseCases\samples\CAAInfReadDocument.CATPart")

 
'Close the document by specifying its name.

 
CATIA.Documents.Item("CAAInfReadDocument.CATPart").Close()

 ...
```

 
 
 
 

Finally, the third way of closing a CATIA document is to execute the `Close`
 method on the name of the document which is itself retrieved using the *Documents*
 collection's `Item` method: the document is thus removed from
 the *Documents* collection and all the windows that contain it are
 also closed and removed from the *Windows* collection.
 

[[Top]]
 
 

---

#### []In Short

This use case has shown the three ways of closing an existing CATIA document
during an interactive session:

 
- Using the `ActiveDocument` property of the CATIA application
 
- Using the variable assigned to handle the document 
 
- Using the name of the document retrieved from the *Documents*
 collection by the `Item` method

[[Top]]

---

#### []References

 
 |[1]
 |[Replaying a Macro]
 
 
 |[2]
 |[Opening an Existing CATIA Document]
 
 
 |[[Top]]

---

*Copyright 2001, Dassault Systmes. All rights reserved.*