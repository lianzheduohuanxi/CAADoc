---
```vbscript
title: "DrawingPageSetup Object"
category: "use-case"
module: "CAAScdDriTechArticles"
tags: ["CATIA"]
source_file: "Doc/online/CAAScdDriTechArticles/CAADriObjDrawingPageSetup.htm"
converted: "2026-05-11T17:31:51.118717"
```

---
# DrawingPageSetup Object

See Also | UseCases | Properties | Methods  
---|---|---|---  

[![](../CAAScrAutomationImages/images/drsheets.gif)](CAADriObjDrawingSheets.md)  
![](../CAAScrAutomationImages/images/parchild.gif)[![](../CAAScrAutomationImages/images/drsheet.gif)](CAADriObjDrawingSheet.md)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/drpgset.gif)  
---  

Represents the page setup of a drawing sheet object of a drawing document. The page setup is the object that stores data which defines how the drawing sheet will be actually printed on paper. This data includes namely the paper size, the orientation, the bottom, top, right, and left margins, the zoom factor, the banner, the printing quality, the choice of the orientation, the ability to either select the appropriate printer format to fit the sheet format or to zoom the sheet in or out to fit the printer format.

The **DrawingPageSetup** object inherits most of its properties from the **PageSetup** object.
## Using the DrawingPageSetup Object

Represents the page setup of a drawing sheet object of a drawing document. The page setup is the object that stores data which defines how the drawing sheet will be actually printed on paper. This data includes namely the paper size, the orientation, the bottom, top, right, and left margins, the zoom factor, the banner, the printing quality, the choice of the orientation, the ability to either select the appropriate printer format to fit the sheet format or to zoom the sheet in or out to fit the printer format.
The **DrawingPageSetup** object inherits most of its properties from the **PageSetup** object.
Use the **FitToPrinterFormat** method to to zoom the sheet in or out to fit the printer format.

```vbscript
    CATIA.Documents(2).ActiveSheet.DrawingPageSetup.FitToPrinterFormat

```

Use the **ChooseBestOrientation** method to activate if it is deactivated, or to deactivate if is activated, the ability to choose the best orientation to fit the printer format.

```vbscript
    CATIA.Documents(2).ActiveSheet.DrawingPageSetup.ChooseBestOrientation

```

* * *

_Copyright 1999-2013, Dassault Syst èmes. All rights reserved._
