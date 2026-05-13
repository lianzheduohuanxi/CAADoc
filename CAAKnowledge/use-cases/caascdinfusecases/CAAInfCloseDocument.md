---
title: "Untitled"
category: "use-case"
module: "CAAScdInfUseCases"
tags: ["CAAScrBase", "CATIA", "CAAInfOpenDocument", "CAAScrJavaScript", "CAAInfCloseDocumentSource", "CAAInfCloseDocument", "CAAInfReadDocument", "CAAScdInfUseCases", "CAAInfLauchMacro"]
source_file: "Doc/online/CAAScdInfUseCases/CAAInfCloseDocument.htmmd"
converted: "2026-05-11T11:27:02.695648"
---

---

      

Define the `sDocPath` variable to retrieve the
      CATDocView environment variable value which holds the documentation path
      where the Part document used below is stored. Also, check that this
      variable is valuated.
      

[Top]
      

#### Closing the Active CATIA Document
      
      

An existing CATIA document is opened using the `Open` method
      of the *Documents* collection (*Documents* object). See the
      CAAInfOpenDocument [2] sample for a description
      of how to open a CATIA document. Because the `Open` method also
      activates the opened document, you can use the `Close` method
      of the `ActiveDocument` property of the CATIA application in
      order to close it: the document is thus removed from the *Documents*
      collection and all the windows that contain it are also closed and removed
      from the *Windows* collection.
      

[Top]
    
  

      

A second way of closing an existing CATIA document is to execute the `Close`
      method directly on the object variable already assigned to handle the
      document: the document is thus removed from the *Documents*
      collection and all the windows that contain it are also closed and removed
      from the *Windows* collection.
      

[Top]
    
  

      

Finally, the third way of closing a CATIA document is to execute the `Close`
      method on the name of the document which is itself retrieved using the *Documents*
      collection's `Item` method: the document is thus removed from
      the *Documents* collection and all the windows that contain it are
      also closed and removed from the *Windows* collection.
      

[Top]
    
  

---

#### In Short

This use case has shown the three ways of closing an existing CATIA document
during an interactive session:

  
- Using the `ActiveDocument` property of the CATIA application
  
- Using the variable assigned to handle the document 
  
- Using the name of the document retrieved from the *Documents*
    collection by the `Item` method

[Top]

---

#### References

---

*Copyright  2001, Dassault Systmes. All rights reserved.*

```vbscript
'Optional: allows to find the sample wherever it's installed

```vbscript
      Dim sDocPath As String
      sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)

      If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
          Err.Raise 9999,,&quot;No Doc Path Defined&quot;
      End If
```
```

```vbscript
...
```

```vbscript
'Open the document. 
```vbscript
     Dim iPartDoc As Document
     Set iPartDoc = CATIA.Documents.Open(sDocPath &amp; _
       &quot;/online/CAAScdInfUseCases/samples/CAAInfReadDocument.CATPart&quot;)
```

    'Close the active document which is the document just opened.
```vbscript
     CATIA.ActiveDocument.Close(#)

```

  ...
```

```vbscript
...
```

```vbscript
'Open the same document again.
```vbscript
     Set iPartDoc = CATIA.Documents.Open(sDocPath &amp; _
       &quot;/online/CAAScdInfUseCases/samples/CAAInfReadDocument.CATPart&quot;)
```

    'Close the document using the variable defined for it.
     iPartDoc.Close(#)

  ...
```

```vbscript
...
```

```vbscript
'Open the same document a third time.
```vbscript
      Set iPartDoc = CATIA.Documents.Open(sDocPath &amp; _
        &quot;/online/CAAScdInfUseCases/samples/CAAInfReadDocument.CATPart&quot;)
```

     'Close the document by specifying its name.
```vbscript
      CATIA.Documents.Item(&quot;CAAInfReadDocument.CATPart&quot;).Close(#)
  ...
```
```