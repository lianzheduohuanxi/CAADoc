---
```vbscript
title: "CAAKniParamPerComponents.CATScript"
category: "use-case"
module: "CAAScdKniUseCases"
tags: ["CATIA", "CAAKniParamPerComponents", "CAAKniClash", "CAAScdKniUseCases"]
source_file: "Doc/online/CAAScdKniUseCases/CAAKniParamPerComponentsSource.htm"
converted: "2026-05-11T17:31:51.989309"
```

---
tags: ["CATIA", "CAAKniParamPerComponents", "CAAKniClash", "CAAScdKniUseCases"]
source_file: "Doc/online/CAAScdKniUseCases/CAAKniParamPerComponentsSource.htm"
converted: "2026-05-11T17:31:51.989309"
    Option Explicit
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2001

```

```

```vbscript
    Dim Language as String
    Language="VBScript"
```

```vbscript
```vbscript
```vbscript
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
```

```

```

```vbscript
    Sub CATMain()

```

```vbscript
```vbscript
```vbscript
     ' Set the CATIA popup file alerts to False
     ' It prevents to stop the macro at each alert during its execution
     CATIA.DisplayFileAlerts = False
     ' Retrieve your active document - CATIA is your application
     ' You get the active document by using the ActiveDocument property
     ' on your application object
        ' -----------------------------------------------------------
        ' Optional: allows to find the sample wherever it's installed
        dim sDocPath As String
        sDocPath=CATIA.SystemService.Environ("CATDocView")
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
          Err.Raise 9999,,"No Doc Path Defined"
        End If
        ' -----------------------------------------------------------
        ' Open the Part document
        Dim sFilePath
        sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```

```

```

    		"online\CAAScdKniUseCases\samples\CAAKniClash.CATProduct")
```vbscript
Dim sFilePath
```vbscript
```vbscript
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
        Dim oDoc As Document
        set oDoc = CATIA.Documents.Open(sFilePath)

     Dim oActiveDoc As Document
     Set oActiveDoc = CATIA.ActiveDocument

     Dim i As Integer
     Dim j As Integer
```

```

```

```vbscript
```vbscript
```vbscript
     ' Check whether the document is a CATPart
     ' InStr is a standard VB function
     If (InStr(oActiveDoc.Name,".CATProduct")) <> 0  Then

        Dim oParams As Parameters
        Set oParams = oActiveDoc.Product.Parameters
```

```

```

```vbscript
Dim oParams As Parameters
```vbscript
Set oParams = oActiveDoc.Product.Parameters
```

        msgbox oParams.Count
```

```vbscript
```vbscript
```vbscript
        ' Search for the parameters having Product1 as their
        ' "grand-parent"
        ' Note that the parent of parameters created right below
        ' a root product is the Parameters feature.
        For i = 1 to oParams.Count
         if oParams.item(i).Parent.Parent.name = "Product1" then
```

```

```

```vbscript
```vbscript
```vbscript
' a root product is the Parameters feature.
For i = 1 to oParams.Count
```

```

```

if oParams.item(i).Parent.Parent.name = "Product1" then
          msgbox oParams.item(i).name
         end if
```vbscript
        Next
```

```vbscript
```vbscript
```vbscript
        ' Searches for the parameters right below the p2.1 component
        Dim oProductList As Products
        Set oProductList = oActiveDoc.Product.Products
        For j = 1 to oProductList.Count
           if  oProductList.Item(j).Name = "p2.1" then
           Dim oProd As Product
           Set oProd = oProductList.item(j)
           'Msgbox oProductList.Item(j).Name
           For i = 1 to oProd.Parameters.Count
```

```

```

```vbscript
Set oProd = oProductList.item(j)
```vbscript
'Msgbox oProductList.Item(j).Name
```

```

For i = 1 to oProd.Parameters.Count
              Msgbox oProd.Parameters.item(i).name
              Msgbox oProd.Parameters.item(i).Parent.Parent.name
```vbscript
            Next
```vbscript
```vbscript
           end if
        Next

```

```

```

```vbscript
end if
```vbscript
Next
```

     Else
        MsgBox "The active document must be a CATProduct"
```vbscript
    End If

```

```

```vbscript
    End Sub

```
