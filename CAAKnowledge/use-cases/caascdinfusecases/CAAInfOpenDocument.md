---
title: "Untitled"
category: "use-case"
module: "CAAScdInfUseCases"
tags: ["CAAScrBase", "CATIA", "CAAInfOpenDocument", "CAAScrJavaScript", "CAAInfCloseDocument", "CAAInfReadDocument", "CAAScdInfUseCases", "CAAInfOpenDocumentSource", "CAAInfLauchMacro", "CAAInfSaveDocument"]
source_file: "Doc/online/CAAScdInfUseCases/CAAInfOpenDocument.htm"
converted: "2026-05-11T11:27:02.700964"
---

---

      

Define the `sDocPath` variable to retrieve the
      CATDocView environment variable value which holds the documentation path
      where the Part document used below is stored. Also, check that this
      variable is valuated.
      

[Top]
      

#### Opening an Existing CATIA Document
      
      

An existing CATIA document is opened using the `Open` method
      of the *Documents* collection (*Documents* object). The only
      argument to this method must contain the entire storage path and name
      specifying where the document is to be found. This single statement opens
      the document stored in the file and adds it to the end of the collection
      of documents. It also creates and displays a new window for the document.
      Both document and window are activated. Note that if any changes to the
      opened document occur, the document should be saved at the end of the
      session. See the CAAInfSaveDocument [2] sample
      for an illustration of how to save an opened document. In any case, the
      opened document should also be closed at the end of the session. See the
      CAAInfCloseDocument [3] sample for an
      illustration of how to close an opened document.
      

[Top]
    
  

---

#### In Short

This use case has shown how to open an existing CATIA document during an
interactive session.

[Top]

---

#### References

---

*Copyright  2001, Dassault Systmes. All rights reserved.*



```vbscript
' Optional: allows to find the sample wherever it's installed
     Dim sDocPath As String
     sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)

     If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
        Err.Raise 9999,,&quot;No Doc Path Defined&quot;
     End If
```

```vbscript
...
    Dim iPartDoc As Document
    Set iPartDoc = CATIA.Documents.Open(sDocPath &amp; _
       &quot;\online\CAAScdInfUseCases\samples\CAAInfReadDocument.CATPart&quot;)
  ...
```