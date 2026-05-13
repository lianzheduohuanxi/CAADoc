---
title: "Untitled"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAAScrBase", "CAADriObjDrawingSheets", "CATIA", "CAADriUseCases", "CAAScrJavaScript", "CAAScdDriTechArticles", "CAAScdInfUseCases", "CAADriObjDrawingView", "CAADriDrawingtable", "CAADriObjDrawingDocument", "CAADriObjDrawingSheet", "CAADriDrawingTable", "CAAInfLauchMacro", "CAADriDrawingTableSource"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriDrawingTable.htmmd"
converted: "2026-05-11T11:27:02.761079"
---

---

      

The CATIA prompts are disabled thanks to the `DisplayFileAlerts`
      property of the *Application* object set to `False`.
      

#### Creating and Specifying a New Drawing Document
      
      

A new drawing document is created and its standard is set to ISO.
      

#### Retrieving and Defining the Sheet
      
      

The sheets collection is retrieved from the `oDrwDocument`
      object using the `Sheets` method.

      The sheet object is retrieved from the `oDrwSheets` collection
      using the `ActiveSheet` method.

      The `oDrwSheet` properties set are A4 format, landscape
      orientation and 1:1 scale.
      

#### Retrieving and Defining the View
      
      

The view object is retrieved from the `oDrwSheet` object
      using the `ActiveView` method.
      

#### Creating the Drawing Table
      
      

The tables collection is retrieved from the `oDrwView`
      object using the `Tables` method.

      The table object is created from the `oDrwTables` collection
      using the `Add` method:
      

        
- At 107mm from the sheet origin along x.
        
- At 60 mm from the sheet origin along y.
        
- With 9 rows and a row size of 5mm.
        
- With 9 columns and a column size of 20mm.
        
- Named `"Title Block" `
      
      

![](images/img007.gif)
      

#### Defining the Drawing Table Update
      
      

The `CatTableComputeOFF` enumerate allows you to modify the
      drawing table without update visualization.
      

#### Modifying the Drawing Table
      
      

The table's cells are merged using the `MergeCells` method.

      Row and column sizes are modified using the `SetRowSize` and `SetColumnSize`
      methods.

      The `CatTableComputeON` enumerate allows you to update drawing
      table visualization.
      

![](images/img008.gif)
      **
        

`oDrwTable.MergeCells 1, 1, 2, 2` instruction is executed,
        cells (1,1), (1,2), (2,1), (2,2) are merged.
      
      

![](images/img009.gif)
      **
        

At the end of merging operation.
      
      

![](images/img010.gif)
      **
        

`oDrwTable.SetRowSize 1, 20` instruction is executed, the
        first row is resized.
      
      

![](images/img011.gif)
      **
        

End of the macro.
      
    
  

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create a Drawing Table sheets using the *Add*
method of the *DrawingTables* collection.

[Top]

---

#### References

---

*Copyright  2002, Dassault Systmes. All rights reserved.*

```vbscript
...
```vbscript
    ' Set the CATIA popup file alerts to False
    ' It prevents to stop the macro at each alert during its execution
```
```vbscript
    CATIA.DisplayFileAlerts = False
  ...
```
```

```vbscript
...
    ' Create a new drawing document
```vbscript
    Set oDrwDocument = CATIA.Documents.Add(&quot;Drawing&quot;)

    ' Set the drawing document standard
    oDrwDocument.Standard = catISO
```
  ...
```

```vbscript
...
    ' Retrieve the drawing document's sheets collection
```vbscript
    Set oDrwSheets = oDrwDocument.Sheets

    ' Retrieve the active sheet
```
```vbscript
    Set oDrwSheet = oDrwSheets.ActiveSheet

    ' Set the sheet properties
    oDrwSheet.PaperSize = catPaperA4
```
    oDrwSheet.Orientation = catPaperLandscape
    oDrwSheet.Scale2 = 1
  ...
```

```vbscript
...
    ' Retrieve the active view of the sheet
```vbscript
    Set oDrwView = oDrwSheet.Views.ActiveView
  ...
```
```

```vbscript
...
    ' Retrieve the view's tables collection
```vbscript
    Set oDrwTables = oDrwView.Tables
    
    ' Create a new drawing table
```
```vbscript
    Set oDrwTable = oDrwTables.Add(107, 70, 9, 9, 5, 20)
```
```

```vbscript
```vbscript
' Set the drawing table's name
    oDrwTable.Name = &quot;Title Block&quot;
```
  ...
```

```vbscript
...
    ' Do not update drawing table modifications
    oDrwTable.ComputeMode = CatTableComputeOFF
  ...
```

```vbscript
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

```vbscript
    ' Set the drawing table's row sizes
    oDrwTable.SetRowSize 1, 20
```
    oDrwTable.SetRowSize 2, 4
    oDrwTable.SetRowSize 3, 5
    oDrwTable.SetRowSize 4, 7
    oDrwTable.SetRowSize 5, 5
    oDrwTable.SetRowSize 6, 7
    oDrwTable.SetRowSize 7, 2
    oDrwTable.SetRowSize 8, 3
    oDrwTable.SetRowSize 9, 7

```vbscript
    ' Set the drawing table's column sizes
    oDrwTable.SetColumnSize 1, 45
```
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
```