---
```vbscript
title: "DrawingViews Collection"
category: "use-case"
module: "CAAScdDriTechArticles"
tags: []
source_file: "Doc/online/CAAScdDriTechArticles/CAADriObjDrawingViews.htm"
converted: "2026-05-11T17:31:51.129194"
```

---
# DrawingViews Collection

See Also | UseCases | Properties | Methods
---|---|---|---

[![](../CAAScrAutomationImages/images/drsheet.gif)](CAADriObjDrawingSheet.md)
![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/drviews.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/dractview.gif)[![](../CAAScrAutomationImages/images/drview.gif)](CAADriObjDrawingView.md)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchild.gif)[![](../CAAScrAutomationImages/images/drview.gif)](CAADriObjDrawingView.md)
---

A collection of all the [DrawingView](CAADriObjDrawingView.md) objects that are in a [DrawingSheet](CAADriObjDrawingSheet.md) object.
## Using the DrawingViews Collection

Use the Add method to create a new, empty drawing view and add it to the collection. The following example adds a new, empty drawing view to the active drawing sheet.

Use the Add method to create a new, empty drawing view and add it to the collection. The following example adds a new, empty drawing view to the active drawing sheet.
    DrawingViews.Add

Use the Item method to retrieve a drawing view from the collection.

    DrawingViews.Item(index)

where index is the drawing view name or index number in the DrawingViews collection.

The active view can be retrieved thanks to the ActiveView property.

```vbscript
```vbscript
For more information about using a single DrawingView object, see the [DrawingView](CAADriObjDrawingView.md) object.

```

```

* * *

_Copyright 1999-2013, Dassault Syst èmes. All rights reserved._
