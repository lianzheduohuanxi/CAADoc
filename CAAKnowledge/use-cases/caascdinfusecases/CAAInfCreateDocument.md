---
title: "Untitled"
category: "use-case"
module: "CAAScdInfUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScrJavaScript", "CAAInfSaveAsDocument", "CAAScdInfUseCases", "CAAInfCloseDocument", "CAAInfLauchMacro", "CAAInfCreateDocument", "CAAInfCreateDocumentSource"]
source_file: "Doc/online/CAAScdInfUseCases/CAAInfCreateDocument.htmmd"
converted: "2026-05-11T11:27:02.687842"
---

---

      

A new CATIA document is created using the `Add` method of
      the *Documents* collection (*Documents* object). The type of
      document to be created must be specified to the `Add` method.
      This type can be a part, an assembly, or a drawing. You would then use `Part`,
      `Product`, or `Drawing` type respectively as the
      argument to the `Add` method. In this case, a `Part`
      document is created. The new document is added to the end of the
      collection of documents. A new window for the document is also created and
      displayed. Both document and window are activated. Note that the existence
      of the new document is limited to the CATIA session. To be persistent, the
      document must be saved. See the CAAInfSaveAsDocument [2]
      sample for an illustration of how to save the new document. Note also that
      the newly created document should also be closed at the end of the
      session. See the CAAInfCloseDocument [3] sample
      for an illustration of how to close the new document. 
      

[Top]
    
  

---

#### In Short

This use case has shown how to create a new CATIA document during an
interactive session.

[Top]

---

#### References

---

*Copyright  2001, Dassault Systmes. All rights reserved.*

```vbscript
...
    'Create a new part document.
    'Add the new document to the end of the collection of documents.
    'Create and display a new window for the new document.
    'Activate the new document and the window.
```cpp
     Dim oNewPartDoc As Document
     Set oNewPartDoc = CATIA.Documents.Add(&quot;Part&quot;)
  ...
```
```