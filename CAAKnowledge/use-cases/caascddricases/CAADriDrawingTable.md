---
title: "Creating a Drawing Table"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CATIA", "CAADriDrawingtable", "CAADriDrawingTable", "CAADriUseCases"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriDrawingTable.md"
converted: "2026-05-11T17:31:51.064833"
---

| 
## Interactive Drafting

| 
## Creating a Drawing Table  
  
  
* * *

  This macro shows you how to create a drawing table in Drawing document. This macro creates a new drawing document. In the active view of the document we create a drawing table and specify merged cells, row sizes then column size.  
---|---  
  CAADriDrawingTable is launched in CATIA [1]. No open document is needed. [CAADriDrawingTable.CATScript](CAADriDrawingTableSource.md) is located in the CAADriUseCases module.  [Execute macro](macros/CAADriDrawingTable.CATScript) (Windows only).    
  CAADriDrawingtable includes five steps:

  1. Prolog
  2. Creating and Specifying a New Drawing Document
  3. Retrieving and Defining the Sheet
  4. Retrieving and Defining the View
  5. Creating the Drawing Table
  6. Defining the Drawing Table Update
  7. Modifying the Drawing Table

#### Prolog

| 
    
    
      ...
        ' Set the CATIA popup file alerts to False
        ' It prevents to stop the macro at each alert during its execution
```vbscript
        CATIA.DisplayFileAlerts = False
      ...  
  
```

```

---  
  
The CATIA prompts are disabled thanks to the `DisplayFileAlerts` property of the _Application_ object set to `False`.
#### Creating and Specifying a New Drawing Document
    
    
      ...
        ' Create a new drawing document
```vbscript
        Set oDrwDocument = CATIA.Documents.Add("Drawing")
        ' Set the drawing document standard
        oDrwDocument.Standard = catISO
      ...  
  
```

```

---  
  
A new drawing document is created and its standard is set to ISO.
#### Retrieving and Defining the Sheet
    
    
    ...
        ' Retrieve the drawing document's sheets collection
```vbscript
        Set oDrwSheets = oDrwDocument.Sheets
```vbscript
        ' Retrieve the active sheet
        Set oDrwSheet = oDrwSheets.ActiveSheet
        ' Set the sheet properties
```

        oDrwSheet.PaperSize = catPaperA4
        oDrwSheet.Orientation = catPaperLandscape
        oDrwSheet.Scale2 = 1
      ...  
  
```

```

---  
  
The sheets collection is retrieved from the `oDrwDocument` object using the `Sheets` method.  
The sheet object is retrieved from the `oDrwSheets` collection using the `ActiveSheet` method.  
The `oDrwSheet` properties set are A4 format, landscape orientation and 1:1 scale.
#### Retrieving and Defining the View
    
    
    ...
        ' Retrieve the active view of the sheet
```vbscript
        Set oDrwView = oDrwSheet.Views.ActiveView
      ...  
  
```

```

---  
  
The view object is retrieved from the `oDrwSheet` object using the `ActiveView` method.
#### Creating the Drawing Table
    
    
      ...
        ' Retrieve the view's tables collection
```vbscript
        Set oDrwTables = oDrwView.Tables
        ' Create a new drawing table
        Set oDrwTable = oDrwTables.Add(107, 70, 9, 9, 5, 20)
    
```

        ' Set the drawing table's name
        oDrwTable.Name = "Title Block"
      ...  
  
```

---  
  
The tables collection is retrieved from the `oDrwView` object using the `Tables` method.  
The table object is created from the `oDrwTables` collection using the `Add` method:

  * At 107mm from the sheet origin along x.
  * At 60 mm from the sheet origin along y.
  * With 9 rows and a row size of 5mm.
  * With 9 columns and a column size of 20mm.
  * Named `"Title Block" `

![](images/img007.gif)
#### Defining the Drawing Table Update
    
    
      ...
        ' Do not update drawing table modifications
        oDrwTable.ComputeMode = CatTableComputeOFF
      ...  
  
---  
  
The `CatTableComputeOFF` enumerate allows you to modify the drawing table without update visualization.
#### Modifying the Drawing Table
    
    
      ...
        ' Merge drawing table's cells
        oDrwTable.MergeCells 1, 1, 2, 2
        oDrwTable.MergeCells 1, 3, 1, 7
        oDrwTable.MergeCells 2, 3, 2, 7
        oDrwTable.MergeCells 4, 3, 1, 7
        oDrwTable.MergeCells 5, 4, 1, 5
        oDrwTable.MergeCells 6, 3, 2, 1
        oDrwTable.MergeCells 6, 4, 2, 5
        oDrwTable.MergeCells 6, 9, 2, 1
        oDrwTable.MergeCells 7, 1, 2, 1
        oDrwTable.MergeCells 7, 2, 2, 1
        oDrwTable.MergeCells 8, 3, 2, 1
        oDrwTable.MergeCells 8, 4, 2, 1
        oDrwTable.MergeCells 8, 5, 2, 1
        oDrwTable.MergeCells 8, 6, 2, 1
        oDrwTable.MergeCells 8, 7, 2, 1
        oDrwTable.MergeCells 8, 8, 2, 1
        oDrwTable.MergeCells 8, 9, 2, 1
        ' Set the drawing table's row sizes
        oDrwTable.SetRowSize 1, 20
        oDrwTable.SetRowSize 2, 4
        oDrwTable.SetRowSize 3, 5
        oDrwTable.SetRowSize 4, 7
        oDrwTable.SetRowSize 5, 5
        oDrwTable.SetRowSize 6, 7
        oDrwTable.SetRowSize 7, 2
        oDrwTable.SetRowSize 8, 3
        oDrwTable.SetRowSize 9, 7
        ' Set the drawing table's column sizes
        oDrwTable.SetColumnSize 1, 45
        oDrwTable.SetColumnSize 2, 20
        oDrwTable.SetColumnSize 3, 15
        oDrwTable.SetColumnSize 4, 15
        oDrwTable.SetColumnSize 5, 27
        oDrwTable.SetColumnSize 6, 18
        oDrwTable.SetColumnSize 7, 20
        oDrwTable.SetColumnSize 8, 15
        oDrwTable.SetColumnSize 9, 15
        ' Update drawing table modifications
        oDrwTable.ComputeMode = CatTableComputeON
      ...  
  
---  
  
The table's cells are merged using the `MergeCells` method.  
Row and column sizes are modified using the `SetRowSize` and `SetColumnSize` methods.  
The `CatTableComputeON` enumerate allows you to update drawing table visualization.

![](images/img008.gif)

> `oDrwTable.MergeCells 1, 1, 2, 2` instruction is executed, cells (1,1), (1,2), (2,1), (2,2) are merged.

![](images/img009.gif)

> At the end of merging operation.

![](images/img010.gif)

> `oDrwTable.SetRowSize 1, 20` instruction is executed, the first row is resized.

![](images/img011.gif)

> End of the macro.  
  
![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create a Drawing Table sheets using the _Add_ method of the _DrawingTables_ collection.

[Top]

* * *
#### References

[1] | [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)  
---|---  
[2] | _[DrawingDocument](../CAAScdDriTechArticles/CAADriObjDrawingDocument.md)_ , _[DrawingSheet](../CAAScdDriTechArticles/CAADriObjDrawingSheet.md),_ [_DrawingSheets_](../CAAScdDriTechArticles/CAADriObjDrawingSheets.md) _,_[_DrawingView_](../CAAScdDriTechArticles/CAADriObjDrawingView.md)  
[Top]

* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
