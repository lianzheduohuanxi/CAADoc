---
title: "DrawingDocument Object"
category: "use-case"
module: "CAAScdDriTechArticles"
tags: ["CATIA"]
source_file: "Doc/online/CAAScdDriTechArticles/CAADriObjDrawingDocument.md"
converted: "2026-05-11T17:31:51.117216"
---
# DrawingDocument Object

| See Also | UseCases | Properties | Methods  
---|---|---|---  
  
 

[![](../CAAScrAutomationImages/images/applicat.gif)](../CAAScdInfTechArticles/CAAInfObjApplication.md)  
![](../CAAScrAutomationImages/images/parchild.gif)[![](../CAAScrAutomationImages/images/docs.gif)](../CAAScdInfTechArticles/CAAInfObjDocument.md)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/doc.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parderiv.gif)![](../CAAScrAutomationImages/images/draftdoc.gif)[![Application Object Diagram](../CAAScrAutomationImages/images/uparrow.gif)](../CAAScdInfTechArticles/CAAInfTocApplication.md)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/drroot.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchild.gif)[![](../CAAScrAutomationImages/images/drsheets.gif)](CAADriObjDrawingSheets.md)  
---  
  
Represents a Drawing document. The **DrawingDocument** object is part of the Documents collection that contains all the documents currently open in the CATIA application.
## Using the DrawingDocument Object

The following properties for returning a DrawingDocument object are described in this section:

  * **Documents** property
  * **ActiveDocument** property

### Documents Property

Use **Documents**(_index_), where index is the document name or index number in the Documents collection, to return a single **DrawingDocument** object. The following example activates the second document in the collection.
    
    
```vbscript
    CATIA.Documents(2).Activate

```

The index number denotes the order in which the documents were opened or created. `Documents(1)` is the second document created, and `Documents(Documents.Count)` is the last one created. Activating a document doesn't change its index number. All documents are included in the index count, even if they're hidden.

Use the **ActiveDocument** property to retrieve the active document: 
    
    
```vbscript
    Dim Doc As Document
    Set Doc = CATIA.ActiveDocuments

```

* * *

_Copyright 1999-2013, Dassault Syst èmes. All rights reserved._

```