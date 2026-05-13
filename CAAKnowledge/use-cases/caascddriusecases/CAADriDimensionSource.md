---
title: "Untitled"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAAScrBase", "CATIA", "CAADriDimension"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriDimensionSource.htmmd"
converted: "2026-05-11T11:27:02.756876"
---

```vbscript
Dim Language as String
Language="VBScript"
```

'---------------------------------------------------------------------------
'COPYRIGHT DASSAULT SYSTEMES 2002

' ****************************************************************************
'
' Purpose:       To analyze a subset of dimensions pointed by text leaders
'                in the active drafting document.
'                That macro checks all dimensions pointed by text leader elements.
'                If dimensions have a wrong display (tolerances or wrong frame)
'                text leader object is highlighted.
'
' Assumptions:   A Drafting document should be active
'
' Author: 
' Languages:     VBScript
' Version:       V5R10
' Locales:       English 
' CATIA Level: V5R10 
'
' ****************************************************************************

'---------------------------------------------------------------------------

```cpp
Sub CATMain(#)

    ' Set the CATIA popup file alerts to False
    ' It prevents to stop the macro at each alert during its execution
```
```cpp
    CATIA.DisplayFileAlerts = False

    ' Optional: allows to find the sample wherever it's installed
```
    dim sDocPath As String 
```cpp
    sDocPath=CATIA.SystemService.Environ("CATDocView")
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```

'---------------------------------------------------------------------------
'1/ Read active CATDrawing Document
'---------------------------------------------------------------------------
```cpp
Dim DrwDoc As DrawingDocument
Set DrwDoc = CATIA.ActiveDocument

' Get Selection Object and clear it
```
```vbscript
Dim DrwSelect As Selection
Set DrwSelect = DrwDoc.Selection

' Variables declaration
```
```cpp
Dim ElemDispatch As CATBaseDispatch
Dim NomObj As String
Dim numsheet As Long
Dim numview As Long
Dim numtxt As Long
Dim numleader As Long

```

'---------------------------------------------------------------------------
'2/ Scan all the sheet of the current drawing (Included detail sheet)
'---------------------------------------------------------------------------
```vbscript
Dim DrwSheets As DrawingSheets
Set DrwSheets = DrwDoc.Sheets
Dim CurrentSheet As DrawingSheet

'Read the current sheet to restore it at the end of the macro
```
```vbscript
Dim SheetToRestore As DrawingSheet
Set SheetToRestore = DrwSheets.ActiveSheet

For numsheet = 1 To DrwSheets.Count
```

```vbscript
   Set CurrentSheet = DrwSheets.Item(numsheet)
   
```
   
   ' Active Currentsheet
   CurrentSheet.Activate
   
   ' Clear the selection
   DrwSelect.Clear
   
```vbscript
   Dim DrwViews As DrawingViews
   Set DrwViews = CurrentSheet.Views
   
   'Read the current view to restore it at the end of the macro
```
```vbscript
   Dim ViewToRestore As DrawingView
   Set ViewToRestore = DrwViews.ActiveView

```

'---------------------------------------------------------------------------
'3/ Scan all the view of the current sheet
'---------------------------------------------------------------------------
```vbscript
   Dim CurrentView As DrawingView
   
   For numview = 1 To DrwViews.Count
```
   
```vbscript
      Set CurrentView = DrwViews.Item(numview)
      
```
      
      'Active the current view
      CurrentView.Activate

'---------------------------------------------------------------------------
'4/ Scan all the texts of the current view
'---------------------------------------------------------------------------

```vbscript
      Dim Texts As DrawingTexts
      Set Texts = CurrentView.Texts
         
      For numtxt = 1 To Texts.Count
```
         
```vbscript
         Dim CurrentText As DrawingText
         Set CurrentText = Texts.Item(numtxt)
            
```
            
'---------------------------------------------------------------------------
'5/ Scan all the leaders of the current text
'---------------------------------------------------------------------------
               
```vbscript
         Dim Leaders As DrawingLeaders
         Set Leaders = CurrentText.Leaders
 
         For numleader = 1 To Leaders.Count
```
```vbscript
            Dim CurrentLeader As DrawingLeader
            Set CurrentLeader = Leaders.Item(numleader)
                    
            ' Manage error on HeadTarget method when
```
            ' no element is pointed by the text leader.
```vbscript
            On Error Resume Next
            ' Get object pointed on the leader
```
```vbscript
            Set ElemDispatch = Nothing
            Set ElemDispatch = CurrentLeader.HeadTarget
            NomObj = TypeName(ElemDispatch)
```
                       
'------------------------------------------------------------------------------
'6/ Check tolerances and the frame type of the dimension pointed by text leader
'------------------------------------------------------------------------------

            ' A dimension is pointed by text leader
            If NomObj = "DrawingDimension" Then
                            
               ' Get the dimension object
```vbscript
               Dim PointedDim As DrawingDimension
               Set PointedDim = ElemDispatch
                   
               ' Read dimension tolerances
```
```vbscript
               Dim oTolType As Long
               Dim oDisplayMode As Long
               Dim oTolName As String
               Dim oUpTolS As String
               Dim oLowTolS As String
               Dim oUpTolD As Double
               Dim oLowTolD As Double
               PointedDim.GetTolerances oTolType, oTolName, oUpTolS, oLowTolS, oUpTolD, oLowTolD, oDisplayMode
```
    
               ' Read dimension frame type
```vbscript
               Dim TypeFrame As CatDimFrame
               TypeFrame = PointedDim.ValueFrame
```
               
'---------------------------------------------------------------------------
'7/ Change the visualization of the text leader linked to that dimension
'---------------------------------------------------------------------------
            
               ' If dimension does not respect the criteria text leader object is highlighted
               If oTolType <> 0 Or TypeFrame <> catFraRectangle Then
                  DrwSelect.Add CurrentText
                  DrwSelect.VisProperties.SetRealColor 255, 0, 0, 0
                  DrwSelect.VisProperties.SetRealWidth 6, 1
               End If
             
            End If
         Next

      Next

    'Restore the view
    ViewToRestore.Activate

   Next

 Next 

'Restore the Drawing Document sheet
SheetToRestore.Activate
   
```vbscript
End Sub

```vbscript
```
```vbscript
Dim Language as String
Language=&quot;VBScript&quot;
```

'---------------------------------------------------------------------------
'COPYRIGHT DASSAULT SYSTEMES 2002

' ****************************************************************************
'
' Purpose:       To analyze a subset of dimensions pointed by text leaders
'                in the active drafting document.
'                That macro checks all dimensions pointed by text leader elements.
'                If dimensions have a wrong display (tolerances or wrong frame)
'                text leader object is highlighted.
'
' Assumptions:   A Drafting document should be active
'
' Author: 
' Languages:     VBScript
' Version:       V5R10
' Locales:       English 
' CATIA Level: V5R10 
'
' ****************************************************************************

'---------------------------------------------------------------------------

```cpp
Sub CATMain(#)

    ' Set the CATIA popup file alerts to False
    ' It prevents to stop the macro at each alert during its execution
```
```cpp
    CATIA.DisplayFileAlerts = False

    ' Optional: allows to find the sample wherever it's installed
```
    dim sDocPath As String 
```cpp
    sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
```

'---------------------------------------------------------------------------
'1/ Read active CATDrawing Document
'---------------------------------------------------------------------------
```cpp
Dim DrwDoc As DrawingDocument
Set DrwDoc = CATIA.ActiveDocument

' Get Selection Object and clear it
```
```vbscript
Dim DrwSelect As Selection
Set DrwSelect = DrwDoc.Selection

' Variables declaration
```
```cpp
Dim ElemDispatch As CATBaseDispatch
Dim NomObj As String
Dim numsheet As Long
Dim numview As Long
Dim numtxt As Long
Dim numleader As Long

```

'---------------------------------------------------------------------------
'2/ Scan all the sheet of the current drawing (Included detail sheet)
'---------------------------------------------------------------------------
```vbscript
Dim DrwSheets As DrawingSheets
Set DrwSheets = DrwDoc.Sheets
Dim CurrentSheet As DrawingSheet

'Read the current sheet to restore it at the end of the macro
```
```vbscript
Dim SheetToRestore As DrawingSheet
Set SheetToRestore = DrwSheets.ActiveSheet

For numsheet = 1 To DrwSheets.Count
```

```vbscript
   Set CurrentSheet = DrwSheets.Item(numsheet)
   
```
   
   ' Active Currentsheet
   CurrentSheet.Activate
   
   ' Clear the selection
   DrwSelect.Clear
   
```vbscript
   Dim DrwViews As DrawingViews
   Set DrwViews = CurrentSheet.Views
   
   'Read the current view to restore it at the end of the macro
```
```vbscript
   Dim ViewToRestore As DrawingView
   Set ViewToRestore = DrwViews.ActiveView

```

'---------------------------------------------------------------------------
'3/ Scan all the view of the current sheet
'---------------------------------------------------------------------------
```vbscript
   Dim CurrentView As DrawingView
   
   For numview = 1 To DrwViews.Count
```
   
```vbscript
      Set CurrentView = DrwViews.Item(numview)
      
```
      
      'Active the current view
      CurrentView.Activate

'---------------------------------------------------------------------------
'4/ Scan all the texts of the current view
'---------------------------------------------------------------------------

```vbscript
      Dim Texts As DrawingTexts
      Set Texts = CurrentView.Texts
         
      For numtxt = 1 To Texts.Count
```
         
```vbscript
         Dim CurrentText As DrawingText
         Set CurrentText = Texts.Item(numtxt)
            
```
            
'---------------------------------------------------------------------------
'5/ Scan all the leaders of the current text
'---------------------------------------------------------------------------
               
```vbscript
         Dim Leaders As DrawingLeaders
         Set Leaders = CurrentText.Leaders
 
         For numleader = 1 To Leaders.Count
```
```vbscript
            Dim CurrentLeader As DrawingLeader
            Set CurrentLeader = Leaders.Item(numleader)
                    
            ' Manage error on HeadTarget method when
```
            ' no element is pointed by the text leader.
```vbscript
            On Error Resume Next
            ' Get object pointed on the leader
```
```vbscript
            Set ElemDispatch = Nothing
            Set ElemDispatch = CurrentLeader.HeadTarget
            NomObj = TypeName(ElemDispatch)
```
                       
'------------------------------------------------------------------------------
'6/ Check tolerances and the frame type of the dimension pointed by text leader
'------------------------------------------------------------------------------

            ' A dimension is pointed by text leader
            If NomObj = &quot;DrawingDimension&quot; Then
                            
               ' Get the dimension object
```vbscript
               Dim PointedDim As DrawingDimension
               Set PointedDim = ElemDispatch
                   
               ' Read dimension tolerances
```
```vbscript
               Dim oTolType As Long
               Dim oDisplayMode As Long
               Dim oTolName As String
               Dim oUpTolS As String
               Dim oLowTolS As String
               Dim oUpTolD As Double
               Dim oLowTolD As Double
               PointedDim.GetTolerances oTolType, oTolName, oUpTolS, oLowTolS, oUpTolD, oLowTolD, oDisplayMode
```
    
               ' Read dimension frame type
```vbscript
               Dim TypeFrame As CatDimFrame
               TypeFrame = PointedDim.ValueFrame
```
               
'---------------------------------------------------------------------------
'7/ Change the visualization of the text leader linked to that dimension
'---------------------------------------------------------------------------
            
               ' If dimension does not respect the criteria text leader object is highlighted
               If oTolType &lt;&gt; 0 Or TypeFrame &lt;&gt; catFraRectangle Then
                  DrwSelect.Add CurrentText
                  DrwSelect.VisProperties.SetRealColor 255, 0, 0, 0
                  DrwSelect.VisProperties.SetRealWidth 6, 1
               End If
             
            End If
         Next

      Next

    'Restore the view
    ViewToRestore.Activate

   Next

 Next 

'Restore the Drawing Document sheet
SheetToRestore.Activate
   
```vbscript
End Sub
```
```