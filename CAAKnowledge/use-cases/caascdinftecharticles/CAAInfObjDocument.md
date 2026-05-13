---
```vbscript
title: "Documents Object"
category: tech-article
module: "CAAScdInfTechArticles"
tags: ["CATIA"]
source_file: "Doc/online/CAAScdInfTechArticles/CAAInfObjDocument.htmmd"
converted: "2026-05-11T17:31:52.427065"
```

---
# Documents Object

source_file: "Doc/online/CAAScdInfTechArticles/CAAInfObjDocument.htmmd"
converted: "2026-05-11T17:31:52.427065"
 See Also | Use Cases | Properties | Methods

 [![](../CAAScrAutomationImages/images/applicat.gif)](CAAInfObjApplication.md)
![](../CAAScrAutomationImages/images/parchild.gif)[![](../CAAScrAutomationImages/images/docs.gif)](CAAInfObjDocument.md)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/doc.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/select.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/cameras.gif)
 ---

 _**A Collection of Document objects.**_

 The **Document** is the object which stores your application data on disk. A document is either created empty using the **File- >New** command or using the **Add** method of the **Documents** collection, or opened from a file using the **File- >Open** command or using the **Open** method of the **Documents** collection. CATIA provides access to eight document types: the **PartDocument** , the **ProductDocument** , the **DrawingDocument** , the **AnalysisDocument** , the **ProcessDocument** , the **FunctionalDocument** , the **MaterialDocument** and the **CatalogDocument**. The **Document** abstract object gathers the properties and methods common to all actual document types. When a document is created or opened, it is automatically set as the active document and displayed in a **window** which automatically becomes the active window. A document aggregates the current object or set of objects in the **Selection** object, and **Cameras** , a **camera** collection.

 [Top]

 * * *

 _Copyright 1994-2004, Dassault Systmes. All rights reserved._
