---
title: "CAAKniFilterRightBelowRoot.CATScript"
category: "use-case"
module: "CAAScdKniUseCases"
tags: "["CAAKniFilterRightBelowRoot", "CATIA", "CAAKniClash", "CAAScdKniUseCases"]"
source_file: "Doc/online/CAAScdKniUseCases/CAAKniFilterRightBelowRootSource.htm"
converted: "2026-05-11T17:31:51.981824"
---
tags: ["CAAKniFilterRightBelowRoot", "CATIA", "CAAKniClash", "CAAScdKniUseCases"]
source_file: "Doc/online/CAAScdKniUseCases/CAAKniFilterRightBelowRootSource.htmmd"
converted: "2026-05-11T17:31:51.981824"
    Option Explicit
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2001

```

```

```vbscript
```vbscript
    Dim Language as String
    Language="VBScript"
```
```

```vbscript
```vbscript
```cpp
    ' ***********************************************************************
    '   Purpose:      Given a CATProduct document,
    '                 this macro filters the parameters right below the root
    '                 product.
    '                 Note: You cannot retrieve the list of parameters
    '                 right below the root product by using the
    '                 Product.Parameters attribute of the active document
    '                 because if you do this, you retrieve all the
    '                 parameters of the CATProduct document (parameters
    '                 right below the root product as well as parameters
    '                 below components.
    '                 The trick is to determine whether a parameter which belongs
    '                 to the activedocument.Product.Parameters list belongs to
    '                 one of the sub-component parameter list.
    '
    '   Assumptions:  This macro is intended to be run on
    '                 any CATProduct with CATProduct documents as components
    '
    '
    '   Author:       Carole ROULLE , Pierre Grignon
    '   Languages:    VBScript
    '   Locales:      English (United States)
    '   CATIA Level:  V5R6
    ' ***********************************************************************
```

```

```

```vbscript
```cpp
    Sub CATMain(#)

```

```

```vbscript
```vbscript
```vbscript
        ' -----------------------------------------------------------
        ' Optional: allows to find the sample wherever it's installed
        dim sDocPath As String
```cpp
        sDocPath=CATIA.SystemService.Environ("CATDocView")
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
          Err.Raise 9999,,"No Doc Path Defined"
        End If
```
        ' -----------------------------------------------------------
        ' Open the Part document
```cpp
        Dim sFilePath
        sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```
```

```

```

    		"online/CAAScdKniUseCases/samples/CAAKniClash.CATProduct")
```vbscript
```vbscript
Dim sFilePath
```vbscript
```
```vbscript
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
        Dim oDoc As Document
        set oDoc = CATIA.Documents.Open(sFilePath)
```
```

```

```

```vbscript
```vbscript
```vbscript
```cpp
     ' Set the CATIA popup file alerts to False
     ' It prevents to stop the macro at each alert during its execution
```
```cpp
     CATIA.DisplayFileAlerts = False
     ' Retrieve your active document - CATIA is your application
```
     ' You get the active document by using the ActiveDocument property
     ' on your application object
```cpp
     Dim oActiveDoc As Document
     Set oActiveDoc = CATIA.ActiveDocument

     Dim i,j,k As Integer
     Dim BelongToComp As Integer
     ' Check whether the document is a CATProduct
```
     If (InStr(oActiveDoc.Name,".CATProduct")) <> 0  Then
        ' Scan the complete list of parameters
```vbscript
        Dim oProductList As Products
        Set oProductList = oActiveDoc.Product.Products
        Dim S1 As String
        For i = 1 to oActiveDoc.Product.Parameters.Count
```
        S1 =  oActiveDoc.Product.Parameters.Item(i).Name
        ' Use the BelongToComp flag to set the parameter status
        ' Initial value = 0 (does not belong to a sub-component)
```

```

        BelongToComp = 0
```vbscript
```vbscript
           ' Scan each parameter list of a sub-component
           For j = 1 to oProductList.Count
              For k = 1 to oProductList.Item(j).Parameters.Count
              ' If the document parameter is the same as the sub-component
              ' parameter - Sets the flag to 1
              if  S1 = oProductList.Item(j).Parameters.Item(k).name then
```

```

              BelongToComp = 1
              end if
```

```vbscript
if  S1 = oProductList.Item(j).Parameters.Item(k).name then
BelongToComp = 1
end if
```vbscript
```vbscript
              next
           Next
```

```

```

```vbscript
```vbscript
```vbscript
            ' if the flag is set to 0 - the document parameter
            ' does not belong to ant sub-component
            ' Conclusion: it is right below the root
            if BelongToComp = 0 then
```

```

```

```vbscript
```vbscript
```vbscript
' does not belong to ant sub-component
' Conclusion: it is right below the root
if BelongToComp = 0 then
```

```

            msgbox S1
           end if
```vbscript
        Next
```

     Else
```cpp
        MsgBox "The active document must be a CATProduct"
```vbscript
```
    End If

```

```

```vbscript
```vbscript
    End Sub

```
```
