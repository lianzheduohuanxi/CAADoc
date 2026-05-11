---
title: "Untitled"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAAScrBase", "CAADriObjDrawingSheets", "CATIA", "CAADriDimension", "CAAScrJavaScript", "CAADriUseCases", "CAAScdDriTechArticles", "CAAScdInfUseCases", "CAADriObjDrawingView", "CAADriObjDrawingSheet", "CAADriObjDrawingDocument", "CAAInfLauchMacro", "CAADriDimensionSource"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriDimension.htm"
converted: "2026-05-11T11:27:02.742748"
---

---

      

The CATIA prompts are disabled thanks to the `DisplayFileAlerts`
      property of the *Application* object set to `False`.
      

#### Reading current Drawing Document of the CATIA
      Session
      
      

#### ![](images/img012.jpg)
       
      

Here is the Drawing document. 
      

#### Scanning all the Sheets
      
      

The Sheets collection is retrieved from the `DrwDoc` object
      using the `Sheets` method.

      
      

#### **Scanning all the Views of the current Sheet**
      
      

The Views collection is retrieved from Sheet object using the Views
      method.
      

#### **Scanning all the Texts of the current View**
      
      

the Texts collection is retrieved from View object using the Texts
      method.
      

#### **Scanning all Leaders  and check if a
      Dimension is pointed by leader**
      
      The Leaders collection is retrieved from Text object using the Leaders
      method. HeadTarget method returns a CATBaseDispath object.
      

If no element is pointed by the leader  the method returns fail.
      

#### Reading Tolerances and Frame of the Dimension
      
      

TypeName method returns the name of the pointed element.

      .
      

#### Highlighting text to show the wrong Dimension
      
      

Text appearance is changed by using VisProperties capabilities of
      Select object.
      

![](images/img013.jpg)
      

#### Restore Current Sheet and Current Views of the
      Drawing document
      
      

By this way the Drawing document keep his state before macro
      processing.
      

      End of the macro.
    
  

![](../CAAScrBase/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to get dimension pointed by a Text leader.

[Top]

---

#### References

---

*Copyright  2002, Dassault Systmes. All rights reserved.*



```vbscript
...
    ' Set the CATIA popup file alerts to False
    ' It prevents to stop the macro at each alert during its execution
    CATIA.DisplayFileAlerts = False
  ...
```

```vbscript
...
' Get the drawing document
    Set DrwDoc= CATIA.ActiveDocument
  ...
```

```vbscript
...
    ' Retrieve the drawing document's sheets collection
    Set DrwSheet = DrwDoc.Sheets

    ' Retrieve the active sheet to restore it at the end of the macro
    Set SheetToRestore = oDrwSheets.ActiveSheet

    ' Scan all the sheet of the Drawing document
    For numsheet = 1 To DrwSheets.Count

      Set CurrentSheet = DrwSheets.Item(numsheet)
      ' Active Currentsheet
      CurrentSheet.Activate
  ...
```

```vbscript
...
'get the Views' collection 
   Set DrwViews = CurrentSheet.Views

   'Read the current view to restore it at the end of the macro
   Set ViewToRestore = DrwViews.ActiveView
```

```vbscript
'Scan all the view of the current Sheet
   
   For numview = 1 To DrwViews.Count
   
      Set CurrentView = DrwViews.Item(numview)
      
      'Active the current view
      CurrentView.Activate
  ...
```

```vbscript
...
'Get the Texts' collection 
   Set DrwTexts = CurrentView.Texts
```

```vbscript
'Scan all the Texts of the current View
   
   For numtxt = 1 To DrwTexts.Count
   
      Set CurrentText = DrwTexts.Item(numtxt)
   ...
```

```vbscript
...
'Get the Leaders' collection 
   Set DrwLeaders = CurrentText.Leaders

   'Scan all the Leader of the current Text
   
   For numlead = 1 To DrwLeaders.Count
   
     Set CurrentLeader = DrwLeaders.Item(numlead)
```

```vbscript
' Manage error on HeadTarget method when
     ' no element is pointed by the text leader.
     On Error Resume Next
     ' Get object pointed on the leader
     Set ElemDispatch = Nothing
     Set ElemDispatch = CurrentLeader.HeadTarget
     NomObj = TypeName(ElemDispatch)
  ...
```

```vbscript
...
   ' A dimension is pointed by text leader
     If NomObj = &quot;DrawingDimension&quot; Then
                            
       ' Get the dimension object
       Dim PointedDim As DrawingDimension
       Set PointedDim = ElemDispatch
                   
       ' Read dimension tolerances
       PointedDim.GetTolerances oTolType, oTolName, oUpTolS, oLowTolS, oUpTolD, oLowTolD, oDisplayMode
    
       ' Read dimension frame type
       TypeFrame = PointedDim.ValueFrame
  ...
```

```vbscript
...
'&nbsp; If dimension does not respect the criteria text leader object is highlighted

   If oTolType &lt;&gt; 0 Or TypeFrame &lt;&gt; catFraRectangle Then
     DrwSelect.Add CurrentText
     DrwSelect.VisProperties.SetRealColor 255, 0, 0, 0
     DrwSelect.VisProperties.SetRealWidth 6, 1
   End If
...
```

```vbscript
...
   'Restore the view
    ViewToRestore.Activate

    Next

  Next 

 'Restore the Drawing Document sheet
 SheetToRestore.Activate
  ...
```