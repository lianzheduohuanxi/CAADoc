---
title: "DrawingSheet Object"
category: "tech-article"
module: "CAAScdDriTechArticles"
tags: "["CATIA"]"
source_file: "Doc/online/CAAScdDriTechArticles/CAADriObjDrawingSheet.htm"
converted: "2026-05-11T17:31:51.121705"
---
# DrawingSheet Object

See Also | UseCases | Properties | Methods
---|---|---|---

[![](../CAAScrAutomationImages/images/drsheets.gif)](CAADriObjDrawingSheets.md)
![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/drsheet.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchild.gif)[![](../CAAScrAutomationImages/images/drviews.gif)](CAADriObjDrawingViews.md)
---

Represents a drawing sheet object of a drawing document. All the **DrawingSheet** objects of the **DrawingDocument** are contained in the **DrawingSheets** collection. The **DrawingSheet** object contains in turn a collection of **DrawingView** objects that contains all the views of the sheet.

A drawing sheet has a page setup that defines the sheet attributes, such as its size, margins, orientation, and so forth. This page setup can be retrieved thanks to the **DrawingPageSetup** read only property.
## Using the DrawingSheet Object

Represents a drawing sheet object of a drawing document. All the **DrawingSheet** objects of the **DrawingDocument** are contained in the **DrawingSheets** collection. The **DrawingSheet** object contains in turn a collection of **DrawingView** objects that contains all the views of the sheet.
A drawing sheet has a page setup that defines the sheet attributes, such as its size, margins, orientation, and so forth. This page setup can be retrieved thanks to the **DrawingPageSetup** read only property.
Use the **Views** property to return the **Views** collection.

```vbscript
```vbscript
    Dim ViewCollection As Object
```vbscript
```
```vbscript
```cpp
    Set ViewCollection = CATIA.Documents(2).ActiveSheet.Views

```
```

```

```

```vbscript
```vbscript
Dim ViewCollection As Object
```vbscript
```
```cpp
Set ViewCollection = CATIA.Documents(2).ActiveSheet.Views
```
```

```

Use the **DrawingPageSetup** property to retrieve the sheet setup attributes.

```vbscript
```vbscript
    Dim SheetSetup As Object
```vbscript
```
```vbscript
```cpp
    Set SheetSetup = CATIA.Documents(2).ActiveSheet.DrawingPageSetup

```
```

```

```

* * *

_Copyright 1999-2013, Dassault Syst èmes. All rights reserved._
