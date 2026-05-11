---
title: "DrawingSheets Collection"
category: "general"
module: "CAAScdDriTechArticles"
tags: []
source_file: "Doc\online\CAAScdDriTechArticles\CAADriObjDrawingSheets.htm"
converted: "2026-05-11T17:31:51.123204"
---

# DrawingSheets Collection

 

See Also | UseCases | Properties | Methods  
---|---|---|---  
  
 

[![](../CAAScrAutomationImages/images/draftdoc.gif)](CAADriObjDrawingDocument.htm)  
![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/drsheets.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchild.gif)[![](../CAAScrAutomationImages/images/drsheet.gif)](CAADriObjDrawingSheet.htm)  
---  
  
A collection of all the [DrawingSheet](CAADriObjDrawingSheet.htm) objects that are currently open in a [DrawingDocument](CAADriObjDrawingDocument.htm) object.

## Using the DrawingSheets Collection

Use the Add method to create a new, empty drawing sheet and add it to the collection. The following example adds a new, empty drawing sheet to the active drawing document.
    
    
    DrawingSheets.Add

Use the AddDetail method to add a detail drawing sheet and add it to the collection. The following example adds a new, empty drawing sheet to the active drawing document.
    
    
    DrawingSheets.AddDetail

Use the Item method to retrieve a drawing sheet from the collection.
    
    
    DrawingSheets.Item(index)

where index is the drawing sheet name or index number in the DrawingSheets collection. 

For more information about using a single DrawingSheet object, see the [DrawingSheet](CAADriObjDrawingSheet.htm) object.

* * *

_Copyright 1999-2013, Dassault Syst èmes. All rights reserved._
