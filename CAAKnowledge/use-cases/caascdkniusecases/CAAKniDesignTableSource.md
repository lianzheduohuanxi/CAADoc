---
title: "Untitled"
category: "use-case"
module: "CAAScdKniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdKniUseCases", "CAAKniDesignTable"]
source_file: "Doc/online/CAAScdKniUseCases/CAAKniDesignTableSource.htmmd"
converted: "2026-05-11T11:27:02.711281"
---

Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2001
```vbscript
Dim Language as String
Language="VBScript"
```

' ***********************************************************************
'   Purpose:      This macro:
'                 1 - Checks whether the active document is a CATPart
'                 2 - Checks whether the xls file containing the design table 
'                     exists
'                 3 - Creates a design table from an existing Excel file
'                 4 - Creates two associations 
'                 5 - Applies a new configuration to the document
'                 6 - Add a new row to the design table          
'
'   Assumptions:  This macro only operates on Windows NT  
'                 This macro is intended to be run on the 
'                 KwrMacro0.CATPart document.
'                 This macro uses as an input data the KwrMacTable.xls file
'                 You must replace the value of the sFolderPath variable with the path
'                 of the file where this Excel table has been downloaded.
'   
'
'
'   Author:       Carole ROULLE , Pierre Grignon
'   Languages:    VBScript
'   Locales:      English (United States)
'   CATIA Level:  V5R6
'   Revision : V5R13
' ***********************************************************************

```vbscript
Sub CATMain(#)

```

    ' ----------------------------------------------------------- 
    ' Optional: allows to find the sample wherever it's installed
    dim sDocPath As String 
```vbscript
    sDocPath=CATIA.SystemService.Environ("CATDocView")
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```
    ' ----------------------------------------------------------- 

    ' Open the Part document 
```vbscript
    Dim sFilePath
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
		"online/CAAScdKniUseCases/samples/KwrMacro0.CATPart")
```
```vbscript
    Dim oDoc As Document
    set oDoc = CATIA.Documents.Open(sFilePath)
 ' Set the CATIA popup file alerts to False
 ' It prevents to stop the macro at each alert during its execution
```
```vbscript
 CATIA.DisplayFileAlerts = False

```

 ' Retrieve your active document - CATIA is your application 
 ' You get the active document by using the ActiveDocument property
 ' on your application object
```vbscript
 Dim oActiveDoc As Document 
 Set oActiveDoc = CATIA.ActiveDocument 
  
```
  
' Check whether the document is a CATPart
' InStr is a standard VB function
If (InStr(oActiveDoc.Name,".CATPart")) <> 0  Then 

```vbscript
    ' Set the file system object containing the folder
    Dim oFileSys As FileSystem
    Set oFileSys = CATIA.FileSystem 

    ' Define the design table path
```
```vbscript
    Dim sFolderPath As String
    sFolderPath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
    "online/CAAScdKniUseCases/samples/KwrMacTable.xls")
```
 
    ' Test whether the design table file exists
    ' if it does not exist a message box is displayed
    ' if it exists the design table is created in the document
    if (oFileSys.FileExists(sFolderPath) = False) then 
```vbscript
        MsgBox sFolderPath & " doesn't exist" 
    else
```
        ' Retrieve the collection object which contains
        ' all the document relations.
        ' The statements below are only valid when the active
        ' document is a CATPart
```vbscript
        Dim oRelations As Relations
        Set oRelations = oActiveDoc.Part.Relations

```

        ' Just to be clean before creating relations
        ' Scan the collection of relations and remove the relations
        ' with name "DesignTable.1" 
```vbscript
        Dim i As Integer 
        For i = 1 To oRelations.Count
```
          if oRelations.Item(i).Name  = "DesignTable.1" then
          oRelations.Remove oRelations.Item(i).Name 
          end if
        Next

       ' Create the "DesignTable.1" design table
       ' by using the Relations.CreateDesignTable method 
       ' Argument 1: Design table name
       ' Argument 2: Comment (empty here below)
       ' Argument 3: Allows you to specify whether you want to copy the
```vbscript
       '             design table data in the document or not. Set this argument
       '             to True whenever you work on a platform (NT/Unix)
```
       '             and intend to reuse your document on another platform
       '             (Unix/NT). Otherwise, set this argument to False
       ' Argument 4: design table path
```vbscript
       Dim oDesignTable As DesignTable
       Set oDesignTable = oRelations.CreateDesignTable("DesignTable.1","",_
                                                    False,_
```
                                                   sFolderPath) 

       ' Retrieve the collection object which contains
       ' all the part bodies
```vbscript
       Dim oBodies As Bodies
       Set oBodies = oActiveDoc.Part.Bodies

```

       ' Scan the Bodies collection to determine 
       ' whether a PartBody feature exists
       ' if the PartBody exists - creates two associations
```vbscript
       Dim j As Integer
       For j = 1 to oBodies.Count
```
          if oBodies.Item(j).Name  = "PartBody" then 
             ' Retrieve the "PartBody" item from the Bodies collection
```vbscript
             Dim oPartBody As AnyObject
             Set oPartBody = CATIA.ActiveDocument.Part.Bodies.Item("PartBody") 

             ' Check there is at least one shape in the Part 
```
```vbscript
             Dim oShapes As Shapes
             Set oShapes = oPartBody.Shapes
             if (oShapes.Count <> 0) then  
```
               ' Retrieve the Pad.1 object
```vbscript
               Dim Pad2 As AnyObject
               Set Pad2 = oPartBody.Shapes.Item("Pad.1")
               ' Creates two associations
```
               oDesignTable.AddAssociation Pad2.FirstLimit.Dimension, "A"
               oDesignTable.AddAssociation Pad2.SecondLimit.Dimension, "B"
               ' Apply the third configuration of the design table 
               ' to your document 
               oDesignTable.Configuration = 3
             else 
               msgbox "no shapes"
             end if

            ' Add a new row
            ' A new row is added to the design table each time the
            ' macro is replayed on the document
            ' A limit of 10 rows is specified
            msgbox oDesignTable.ConfigurationsNb
            If (oDesignTable.ConfigurationsNb < 10) Then
              oDesignTable.AddNewRow(#)
            else 
              msgbox "configuration number = 10"
            end if

          else
            msgbox "A PartBody feature is required"
          end if 

       Exit For
       Next

      ' Update the document
```vbscript
      CATIA.ActiveDocument.Part.Update 

    End If
```
else 
```vbscript
    MsgBox "The active document must be a CATPart"
End If
```

```vbscript
End Sub

```

```vbscript
Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2001
```vbscript
Dim Language as String
Language="VBScript"
```

' ***********************************************************************
'   Purpose:      This macro:
'                 1 - Checks whether the active document is a CATPart
'                 2 - Checks whether the xls file containing the design table 
'                     exists
'                 3 - Creates a design table from an existing Excel file
'                 4 - Creates two associations 
'                 5 - Applies a new configuration to the document
'                 6 - Add a new row to the design table          
'
'   Assumptions:  This macro only operates on Windows NT  
'                 This macro is intended to be run on the 
'                 KwrMacro0.CATPart document.
'                 This macro uses as an input data the KwrMacTable.xls file
'                 You must replace the value of the sFolderPath variable with the path
'                 of the file where this Excel table has been downloaded.
'   
'
'
'   Author:       Carole ROULLE , Pierre Grignon
'   Languages:    VBScript
'   Locales:      English (United States)
'   CATIA Level:  V5R6
'   Revision : V5R13
' ***********************************************************************

```vbscript
Sub CATMain(#)

```

    ' ----------------------------------------------------------- 
    ' Optional: allows to find the sample wherever it's installed
    dim sDocPath As String 
```vbscript
    sDocPath=CATIA.SystemService.Environ("CATDocView")
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```
    ' ----------------------------------------------------------- 

    ' Open the Part document 
```vbscript
    Dim sFilePath
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
		"online/CAAScdKniUseCases/samples/KwrMacro0.CATPart")
```
```vbscript
    Dim oDoc As Document
    set oDoc = CATIA.Documents.Open(sFilePath)
 ' Set the CATIA popup file alerts to False
 ' It prevents to stop the macro at each alert during its execution
```
```vbscript
 CATIA.DisplayFileAlerts = False

```

 ' Retrieve your active document - CATIA is your application 
 ' You get the active document by using the ActiveDocument property
 ' on your application object
```vbscript
 Dim oActiveDoc As Document 
 Set oActiveDoc = CATIA.ActiveDocument 
  
```
  
' Check whether the document is a CATPart
' InStr is a standard VB function
If (InStr(oActiveDoc.Name,".CATPart")) &lt;&gt; 0  Then 

```vbscript
    ' Set the file system object containing the folder
    Dim oFileSys As FileSystem
    Set oFileSys = CATIA.FileSystem 

    ' Define the design table path
```
```vbscript
    Dim sFolderPath As String
    sFolderPath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
    "online/CAAScdKniUseCases/samples/KwrMacTable.xls")
```
 
    ' Test whether the design table file exists
    ' if it does not exist a message box is displayed
    ' if it exists the design table is created in the document
    if (oFileSys.FileExists(sFolderPath) = False) then 
```vbscript
        MsgBox sFolderPath & " doesn't exist" 
    else
```
        ' Retrieve the collection object which contains
        ' all the document relations.
        ' The statements below are only valid when the active
        ' document is a CATPart
```vbscript
        Dim oRelations As Relations
        Set oRelations = oActiveDoc.Part.Relations

```

        ' Just to be clean before creating relations
        ' Scan the collection of relations and remove the relations
        ' with name "DesignTable.1" 
```vbscript
        Dim i As Integer 
        For i = 1 To oRelations.Count
```
          if oRelations.Item(i).Name  = "DesignTable.1" then
          oRelations.Remove oRelations.Item(i).Name 
          end if
        Next

       ' Create the "DesignTable.1" design table
       ' by using the Relations.CreateDesignTable method 
       ' Argument 1: Design table name
       ' Argument 2: Comment (empty here below)
       ' Argument 3: Allows you to specify whether you want to copy the
```vbscript
       '             design table data in the document or not. Set this argument
       '             to True whenever you work on a platform (NT/Unix)
```
       '             and intend to reuse your document on another platform
       '             (Unix/NT). Otherwise, set this argument to False
       ' Argument 4: design table path
```vbscript
       Dim oDesignTable As DesignTable
       Set oDesignTable = oRelations.CreateDesignTable("DesignTable.1","",_
                                                    False,_
```
                                                   sFolderPath) 

       ' Retrieve the collection object which contains
       ' all the part bodies
```vbscript
       Dim oBodies As Bodies
       Set oBodies = oActiveDoc.Part.Bodies

```

       ' Scan the Bodies collection to determine 
       ' whether a PartBody feature exists
       ' if the PartBody exists - creates two associations
```vbscript
       Dim j As Integer
       For j = 1 to oBodies.Count
```
          if oBodies.Item(j).Name  = "PartBody" then 
             ' Retrieve the "PartBody" item from the Bodies collection
```vbscript
             Dim oPartBody As AnyObject
             Set oPartBody = CATIA.ActiveDocument.Part.Bodies.Item("PartBody") 

             ' Check there is at least one shape in the Part 
```
```vbscript
             Dim oShapes As Shapes
             Set oShapes = oPartBody.Shapes
             if (oShapes.Count &lt;&gt; 0) then  
```
               ' Retrieve the Pad.1 object
```vbscript
               Dim Pad2 As AnyObject
               Set Pad2 = oPartBody.Shapes.Item("Pad.1")
               ' Creates two associations
```
               oDesignTable.AddAssociation Pad2.FirstLimit.Dimension, "A"
               oDesignTable.AddAssociation Pad2.SecondLimit.Dimension, "B"
               ' Apply the third configuration of the design table 
               ' to your document 
               oDesignTable.Configuration = 3
             else 
               msgbox "no shapes"
             end if

            ' Add a new row
            ' A new row is added to the design table each time the
            ' macro is replayed on the document
            ' A limit of 10 rows is specified
            msgbox oDesignTable.ConfigurationsNb
            If (oDesignTable.ConfigurationsNb &lt; 10) Then
              oDesignTable.AddNewRow(#)
            else 
              msgbox "configuration number = 10"
            end if

          else
            msgbox "A PartBody feature is required"
          end if 

       Exit For
       Next

      ' Update the document
```vbscript
      CATIA.ActiveDocument.Part.Update 

    End If
```
else 
```vbscript
    MsgBox "The active document must be a CATPart"
End If
```

```vbscript
End Sub
```
```