---
title: "Untitled"
category: "use-case"
module: "CAAScdKniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAKniClash", "CAAKniParamPerComponents", "CAAScdKniUseCases"]
source_file: "Doc/online/CAAScdKniUseCases/CAAKniParamPerComponentsSource.htmmd"
converted: "2026-05-11T11:27:02.708429"
---

Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2001
```vbscript
Dim Language as String
Language="VBScript"
```

' ***********************************************************************
'   Purpose:      This macro filters the parameters created in a CATProduct 
'                 document
'                 1 - It displays the parameters right below 
'                     the root product
'                 2 - It displays the parameters belonging to a component 
'
'   Assumptions:  This macro is intended to be run on the 
'                 CAAKniClash.CATPoduct document.
'                 However, you can run this macro on any CATProduct document       
'                 which has a rule base.
'
'
'   Author:       Carole ROULLE, Pierre Grignon
'   Languages:    VBScript
'   Locales:      English (United States)
'   CATIA Level:  V5R6  
'   revision V5R13
' ***********************************************************************

```vbscript
Sub CATMain(#)

 ' Set the CATIA popup file alerts to False
 ' It prevents to stop the macro at each alert during its execution
```
```vbscript
 CATIA.DisplayFileAlerts = False

```

 ' Retrieve your active document - CATIA is your application 
 ' You get the active document by using the ActiveDocument property
 ' on your application object

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
		"online/CAAScdKniUseCases/samples/CAAKniClash.CATProduct")
```
```vbscript
    Dim oDoc As Document
    set oDoc = CATIA.Documents.Open(sFilePath)

 Dim oActiveDoc As Document 
 Set oActiveDoc = CATIA.ActiveDocument 
 
 Dim i As Integer
 Dim j As Integer
 ' Check whether the document is a CATPart
```
 ' InStr is a standard VB function
 If (InStr(oActiveDoc.Name,".CATProduct")) <> 0  Then 

```vbscript
    Dim oParams As Parameters
    Set oParams = oActiveDoc.Product.Parameters
    msgbox oParams.Count
```
    
    ' Search for the parameters having Product1 as their 
    ' "grand-parent"
    ' Note that the parent of parameters created right below
    ' a root product is the Parameters feature.
    For i = 1 to oParams.Count
     if oParams.item(i).Parent.Parent.name = "Product1" then 
      msgbox oParams.item(i).name
     end if
    Next 

    ' Searches for the parameters right below the p2.1 component
```vbscript
    Dim oProductList As Products
    Set oProductList = oActiveDoc.Product.Products
    For j = 1 to oProductList.Count
```
       if  oProductList.Item(j).Name = "p2.1" then
```vbscript
       Dim oProd As Product
       Set oProd = oProductList.item(j)
       'Msgbox oProductList.Item(j).Name
```
       For i = 1 to oProd.Parameters.Count
          Msgbox oProd.Parameters.item(i).name
          Msgbox oProd.Parameters.item(i).Parent.Parent.name 
        Next  
       end if
    Next       

 Else 
```vbscript
    MsgBox "The active document must be a CATProduct"
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
'   Purpose:      This macro filters the parameters created in a CATProduct 
'                 document
'                 1 - It displays the parameters right below 
'                     the root product
'                 2 - It displays the parameters belonging to a component 
'
'   Assumptions:  This macro is intended to be run on the 
'                 CAAKniClash.CATPoduct document.
'                 However, you can run this macro on any CATProduct document       
'                 which has a rule base.
'
'
'   Author:       Carole ROULLE, Pierre Grignon
'   Languages:    VBScript
'   Locales:      English (United States)
'   CATIA Level:  V5R6  
'   revision V5R13
' ***********************************************************************

```vbscript
Sub CATMain(#)

 ' Set the CATIA popup file alerts to False
 ' It prevents to stop the macro at each alert during its execution
```
```vbscript
 CATIA.DisplayFileAlerts = False

```

 ' Retrieve your active document - CATIA is your application 
 ' You get the active document by using the ActiveDocument property
 ' on your application object

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
		"online/CAAScdKniUseCases/samples/CAAKniClash.CATProduct")
```
```vbscript
    Dim oDoc As Document
    set oDoc = CATIA.Documents.Open(sFilePath)

 Dim oActiveDoc As Document 
 Set oActiveDoc = CATIA.ActiveDocument 
 
 Dim i As Integer
 Dim j As Integer
 ' Check whether the document is a CATPart
```
 ' InStr is a standard VB function
 If (InStr(oActiveDoc.Name,".CATProduct")) &lt;&gt; 0  Then 

```vbscript
    Dim oParams As Parameters
    Set oParams = oActiveDoc.Product.Parameters
    msgbox oParams.Count
```
    
    ' Search for the parameters having Product1 as their 
    ' "grand-parent"
    ' Note that the parent of parameters created right below
    ' a root product is the Parameters feature.
    For i = 1 to oParams.Count
     if oParams.item(i).Parent.Parent.name = "Product1" then 
      msgbox oParams.item(i).name
     end if
    Next 

    ' Searches for the parameters right below the p2.1 component
```vbscript
    Dim oProductList As Products
    Set oProductList = oActiveDoc.Product.Products
    For j = 1 to oProductList.Count
```
       if  oProductList.Item(j).Name = "p2.1" then
```vbscript
       Dim oProd As Product
       Set oProd = oProductList.item(j)
       'Msgbox oProductList.Item(j).Name
```
       For i = 1 to oProd.Parameters.Count
          Msgbox oProd.Parameters.item(i).name
          Msgbox oProd.Parameters.item(i).Parent.Parent.name 
        Next  
       end if
    Next       

 Else 
```vbscript
    MsgBox "The active document must be a CATProduct"
End If
```

```vbscript
End Sub
```
```