---
title: "Untitled"
category: "use-case"
module: "CAAScdInfUseCases"
tags: ["CAAScrBase", "CAAInfWriteDocument3", "CATIA", "CAAScrJavaScript", "CAAInfSaveAsDocumentSource", "CAAInfSaveAsDocument", "CAAInfReadDocument", "CAAScdInfUseCases", "CAAInfCloseDocument", "CAAInfWriteDocument1", "CAAInfCreateDocument", "CAAInfWriteDocument2", "CAAInfLauchMacro", "CAAInfSaveDocument"]
source_file: "Doc/online/CAAScdInfUseCases/CAAInfSaveAsDocument.htm"
converted: "2026-05-11T11:27:02.698963"
---

---

      

Define the `sDocPath` variable to retrieve the
      CATDocView environment variable value which holds the documentation path
      where the Part document used below is stored. Also, check that this
      variable is valuated.
      

[Top]
      

#### Retrieving the CATTEMP Environment Variable and
      Checking its Valuation
      
      

Define a variable to use for the current CATTEMP in order
      to define the document storage path of saved document. Also, verify that
      this variable has been valuated.
      

Define the `sTmpPath` variable to retrieve the
      CATTEMP environment variable value to define the path where the Part
      document used below will saved. Also, check that this variable is
      valuated.
      

[Top]
      

#### Saving the Active CATIA Document
      
      

An existing CATIA document is created using the `Add` method
      of the *Documents* collection (*Documents* object). See the
      CAAInfCreateDocument [3] sample for a
      description of how to create a new CATIA document. Because the `Add`
      method also activates the new document, you can execute the `SaveAs`
      method on the `ActiveDocument` property of the CATIA
      application in order to save it: the document is thus saved in the storage
      path name and location specified in the argument of the `SaveAs`
      method. If a document with the same name already exists, a prompt will
      request that you specify whether or not you want that document to be
      overwritten with this one. Note that before exiting the session, the
      document should also be closed. See the CAAInfCloseDocument [4]
      sample for a description of how to close a document.
      

[Top]
    
  

      

A second way of saving a new CATIA document is to use execute the `SaveAs`
      method directly on the variable already assigned to handle the document:
      the document is thus saved in the storage path name and location specified
      in the argument of the `SaveAs` method. If a document with the
      same name already exists, a prompt will request that you specify whether
      or not you want that document to be overwritten with this one. Note that
      before exiting the session, the document should also be closed.
      

[Top]
    
  

      

Finally, the third way of saving a new CATIA document is by executing
      the `SaveAs` method on an existing document that has been
      retrieved from the *Documents* collection by specifying its name to
      the argument of the `Item` method: a new document identical to
      the existing one is then saved under the storage path name and location
      specified in the argument of the `SaveAs` method. If a document
      with the same name already exists, a prompt will request that you specify
      whether or not you want that document to be overwritten with this one.
      Note that before exiting the session, the document should also be closed.
      

[Top]
    
  

---

#### In Short

This use case has shown the three ways of saving a new CATIA document during
an interactive session:

  
- Using the `ActiveDocument` property of the CATIA application
  
- Using the variable assigned to handle the document
  
- Using the name of an existing document retrieved from the document
    collection by the `Item` method

In all three cases, it is necessary to specify the path name and location
where the new document will be stored.

[Top]

---

#### References

---

*Copyright  2001, Dassault Systmes. All rights reserved.*



```vbscript
' Optional: allows to find the sample wherever it may be installed

    Dim sDocPath  As String
    DocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
            Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
```

```vbscript
' Optional: allows to specify where document should be saved

    Dim sTmpPath  As String
    sTmpPath=CATIA.SystemService.Environ(&quot;CATTemp&quot;)
    If (Not CATIA.FileSystem.FolderExists(sTmpPath)) Then
        Err.Raise 9999,,&quot;No Tmp Path Defined&quot;
    End If
```

```vbscript
...
    'Create a new part document.
    'Add the new document to the end of the collection of documents.
    'Create and display a new window for the new document.
    'Activate the new document and the window.
     Dim oFirstNewPartDoc As Document
     Set oFirstNewPartDoc = CATIA.Documents.Add(&quot;Part&quot;)

    'The document just created is the active one.
    'Save the new document.
     CATIA.ActiveDocument.SaveAs(sTmpPath &amp; _
       &quot;\CAAInfWriteDocument1.CATPart&quot;)
 ...
```

```vbscript
...
   'Create a second new part document.
     Dim oSecondNewPartDoc As Document
     Set oSecondNewPartDoc = CATIA.Documents.Add(&quot;Part&quot;)

    'Save the new document using the variable name defined for it.
     oSecondNewPartDoc.SaveAs(sTmpPath &amp; _
       &quot;\CAAInfWriteDocument2.CATPart&quot;)
  ...
```

```vbscript
...
     'Open an existing document.
      Dim iThirdPartDoc As Document
      Set iThirdPartDoc = CATIA.Documents.Open(sDocPath &amp; _
        &quot;\online\CAAScdInfUseCases\samples\CAAInfReadDocument.CATPart&quot;)

     'Save the new document by specifying its name.
      CATIA.Documents.Item(&quot;CAAInfReadDocument.CATPart&quot;).SaveAs(sTmpPath &amp; _
        &quot;\CAAInfWriteDocument3.CATPart&quot;)

  ...
```