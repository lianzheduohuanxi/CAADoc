---
title: "Untitled"
category: "use-case"
module: "CAAScdInfUseCases"
tags: ["CAAScrBase", "CATIA", "CAAInfOpenDocument", "CAAScrJavaScript", "CAAInfSaveAsDocument", "CAAInfReadDocument", "CAAInfSaveDocumentSource", "CAAScdInfUseCases", "CAAInfCloseDocument", "CAAInfLauchMacro", "CAAInfSaveDocument"]
source_file: "Doc/online/CAAScdInfUseCases/CAAInfSaveDocument.htm"
converted: "2026-05-11T11:27:02.696903"
---

---

      

Define the `sDocPath` variable to retrieve the
      CATDocView environment variable value which holds the documentation path
      where the Part document used below is stored. Also, check that this
      variable is valuated.
      

[Top]
      

#### Saving the Active CATIA Document
      
      

An existing CATIA document is opened using the `Open` method
      of the *Documents* collection (*Documents* object). See the
      CAAInfOpenDocument [3] sample for a description
      of how to open a CATIA document. Because the `Open` method also
      activates the opened document, you can use the `Save` method of
      the `ActiveDocument` property of the CATIA application in order
      to save it: the document is saved in the same storage location and under
      the same name. Note that before exiting the session, the document should
      also be closed. See the CAAInfCloseDocument [4]
      sample for a description of how to close a document.
      

[Top]
    
  

      

The same document is opened a second time. Another way of saving an
      existing CATIA document is to execute the `Save` method
      directly on the variable already assigned to handle the document: the
      document is saved in the same storage location and under the same name.
      Note that before exiting the session, the document should also be
      closed. 
      

[Top]
    
  

      

The same document is opened one last time. The third way of saving a
      CATIA document is by executing the `Save` method on the
      document that has been retrieved from the *Documents* collection by
      specifying its name to the argument of the `Item` method: the
      document is saved in the same storage location and under the same name.
      Note that before exiting the session, the document should also be
      closed. 
      

[Top]
    
  

---

#### In Short

This use case has shown the three ways of saving an existing CATIA document
during an interactive session:

  
- Using the `ActiveDocument` property of the CATIA application
  
- Using the variable assigned to handle the document 
  
- Using the name of the document retrieved from the *Documents*
    collection by the `Item` method

In all three cases, the document is saved under the same storage path and
name.

[Top]

---

#### References

---

*Copyright  2001, Dassault Systmes. All rights reserved.*



```vbscript
'Optional: allows to find the sample wherever it's installed

      Dim sDocPath  As String
      sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)

      If (Not CATIA.FileSystem.FolderExists(sDocPath))  Then
         Err.Raise 9999,,&quot;No Doc Path Defined&quot;
      End If
```

```vbscript
...
    'Open the document and add it as the last item of the collection of documents.
    'Create and display a new window for the document.
    'Activate the document and its window.
     Dim iPartDoc As Document
     Set iPartDoc = CATIA.Documents.Open(sDocPath &amp; _
       &quot;\online\CAAScdInfUseCases\samples\CAAInfReadDocument.CATPart&quot;)

    'The document just opened is the active document.
    'Save the active document and then close it.
     CATIA.ActiveDocument.Save()
     CATIA.ActiveDocument.Close()
```

```vbscript
...
```

```vbscript
...
```

```vbscript
'Open the same document again.
     Set iPartDoc = CATIA.Documents.Open(sDocPath &amp; _
       &quot;\online\CAAScdInfUseCases\samples\CAAInfReadDocument.CATPart&quot;)

    'Save the document just opened using the variable name defined for it. 
    'Then, close the document in the same way.
     iPartDoc.Save()
     iPartDoc.Close()

  ...
```

```vbscript
...
```

```vbscript
'Open the same document a third time.
     Set iPartDoc = CATIA.Documents.Open(sDocPath &amp; _
       &quot;\online\CAAScdInfUseCases\samples\CAAInfReadDocument.CATPart&quot;)

    'Save the document by specifying its name and then close it in the same way.
     CATIA.Documents.Item(&quot;CAAInfReadDocument.CATPart&quot;).Save()
     CATIA.Documents.Item(&quot;CAAInfReadDocument.CATPart&quot;).Close()

  ...
```