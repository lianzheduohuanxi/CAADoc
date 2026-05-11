---
```vbscript
title: "Dimensions Checking"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CATIA", "CAADriUseCases", "CAADriDimension"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriDimension.htm"
converted: "2026-05-11T17:31:51.055354"
```

---
| 
## Interactive Drafting

| 
## Dimensions Checking  

* * *

  This macro shows you how to find dimensions pointed by text leader in Drawing document. This macro works on current drawing document.  
---|---  
This macro shows you how to find dimensions pointed by text leader in Drawing document. This macro works on current drawing document.
  CAADriDimension has to be launch in CATIA [1]. Open CAADriDimension.CATDrawing document below sample directory. [CAADriDimension.CATScript](CAADriDimensionSource.md) is located in the CAADriUseCases module.  [Execute macro](macros/CAADriDimension.CATScript) (Windows only).    
  CAADriDimension includes nine steps:

  1. Prolog
  2. Reading current Drawing Document of the CATIA Session 
  3. Scanning all the Sheets
  4. Scanning all the Views of the current Sheet
  5. Scanning all texts of the current View
  6. Scanning all Leaders  and check if a Dimension is pointed by leader
  7. Reading Tolerances and Frame of the Dimension
  8. Highlighting Text to show wrong Dimension
  9. Restore current Sheet and current Views

#### Prolog

| 

      ...
        ' Set the CATIA popup file alerts to False
```vbscript
' Set the CATIA popup file alerts to False
        ' It prevents to stop the macro at each alert during its execution
```

```vbscript
        CATIA.DisplayFileAlerts = False
```

      ...  

---  

The CATIA prompts are disabled thanks to the `DisplayFileAlerts` property of the _Application_ object set to `False`.
#### Reading current Drawing Document of the CATIA Session

      ...
The CATIA prompts are disabled thanks to the `DisplayFileAlerts` property of the _Application_ object set to `False`.
    ' Get the drawing document

```vbscript
        Set DrwDoc= CATIA.ActiveDocument
```

      ...  

---  
#### ![](images/img012.jpg)

Here is the Drawing document. 
#### Scanning all the Sheets

    ...
Here is the Drawing document.
        ' Retrieve the drawing document's sheets collection

```vbscript
        Set DrwSheet = DrwDoc.Sheets
```

```vbscript
        ' Retrieve the active sheet to restore it at the end of the macro
        Set SheetToRestore = oDrwSheets.ActiveSheet
        ' Scan all the sheet of the Drawing document
        For numsheet = 1 To DrwSheets.Count

          Set CurrentSheet = DrwSheets.Item(numsheet)
          ' Active Currentsheet
```

```vbscript
Set CurrentSheet = DrwSheets.Item(numsheet)
' Active Currentsheet
          CurrentSheet.Activate
```

      ...  

---  

The Sheets collection is retrieved from the `DrwDoc` object using the `Sheets` method.  

#### **Scanning all the Views of the current Sheet**

    ...
    'get the Views' collection 
```vbscript
       Set DrwViews = CurrentSheet.Views
       'Read the current view to restore it at the end of the macro
       Set ViewToRestore = DrwViews.ActiveView

```

```vbscript
'Read the current view to restore it at the end of the macro
Set ViewToRestore = DrwViews.ActiveView
       'Scan all the view of the current Sheet

```

```vbscript
       For numview = 1 To DrwViews.Count

          Set CurrentView = DrwViews.Item(numview)
          'Active the current view
          CurrentView.Activate
```

      ...  

---  

The Views collection is retrieved from Sheet object using the Views method.
#### **Scanning all the Texts of the current View**

    ...
The Views collection is retrieved from Sheet object using the Views method.
    'Get the Texts' collection 

```vbscript
       Set DrwTexts = CurrentView.Texts

```

       'Scan all the Texts of the current View

```vbscript
       For numtxt = 1 To DrwTexts.Count

          Set CurrentText = DrwTexts.Item(numtxt)
```

       ...  

---  

the Texts collection is retrieved from View object using the Texts method.
#### **Scanning all Leaders   and check if a Dimension is pointed by leader**

    ...
the Texts collection is retrieved from View object using the Texts method.
    'Get the Leaders' collection 

```vbscript
       Set DrwLeaders = CurrentText.Leaders
       'Scan all the Leader of the current Text

```

```vbscript
       For numlead = 1 To DrwLeaders.Count

         Set CurrentLeader = DrwLeaders.Item(numlead)

```

```vbscript
Set CurrentLeader = DrwLeaders.Item(numlead)
         ' Manage error on HeadTarget method when
         ' no element is pointed by the text leader.
         On Error Resume Next
         ' Get object pointed on the leader
```

```vbscript
         Set ElemDispatch = Nothing
         Set ElemDispatch = CurrentLeader.HeadTarget
         NomObj = TypeName(ElemDispatch)
```

      ...  

---  
The Leaders collection is retrieved from Text object using the Leaders method. HeadTarget method returns a CATBaseDispath object. 

If no element is pointed by the leader  the method returns fail.
#### Reading Tolerances and Frame of the Dimension

      ...
```vbscript
       ' A dimension is pointed by text leader
         If NomObj = "DrawingDimension" Then
           ' Get the dimension object
```

```vbscript
           Dim PointedDim As DrawingDimension
           Set PointedDim = ElemDispatch
           ' Read dimension tolerances
           PointedDim.GetTolerances oTolType, oTolName, oUpTolS, oLowTolS, oUpTolD, oLowTolD, oDisplayMode
           ' Read dimension frame type
           TypeFrame = PointedDim.ValueFrame
```

      ...  

---  

TypeName method returns the name of the pointed element.  
.
#### Highlighting text to show the wrong Dimension

    ...
    '  If dimension does not respect the criteria text leader object is highlighted

```vbscript
'  If dimension does not respect the criteria text leader object is highlighted
       If oTolType <> 0 Or TypeFrame <> catFraRectangle Then
         DrwSelect.Add CurrentText
         DrwSelect.VisProperties.SetRealColor 255, 0, 0, 0
         DrwSelect.VisProperties.SetRealWidth 6, 1
       End If
```

    **...**  

---  

Text appearance is changed by using VisProperties capabilities of Select object.

![](images/img013.jpg)
#### Restore Current Sheet and Current Views of the Drawing document

      ...
       'Restore the view
```vbscript
'Restore the view
        ViewToRestore.Activate

        Next

```

```vbscript
      Next 
     'Restore the Drawing Document sheet
     SheetToRestore.Activate
```

      ...  

---  

By this way the Drawing document keep his state before macro processing.

End of the macro.  

![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to get dimension pointed by a Text leader.

[Top]

* * *
#### References

[1] | [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)  
---|---  
[2] | _[Drawing Document](../CAAScdDriTechArticles/CAADriObjDrawingDocument.md)_ , _[DrawingSheet](../CAAScdDriTechArticles/CAADriObjDrawingSheet.md),_ [_DrawingSheets_](../CAAScdDriTechArticles/CAADriObjDrawingSheets.md) _,_[_DrawingView_](../CAAScdDriTechArticles/CAADriObjDrawingView.md) _,_  
[Top]

* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
