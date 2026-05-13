---
title: "CAAStrModificationOfStructureObjects.CATScript"
category: "use-case"
module: "CAAScdStrUseCases"
tags: "["CATIA", "CAAStrModificationOfStructureObjects"]"
source_file: "Doc/online/CAAScdStrUseCases/CAAStrModificationOfStructureObjectsSource.htm"
converted: "2026-05-11T17:31:50.903114"
---
```vbscript
```vbscript
```vbscript
    '// COPYRIGHT DASSAULT SYSTEMES 2000
    '//============================================================================
    '//
    '// Language="VBSCRIPT"
    '// Sample of macro of using structural vb objects
    '//
    '//============================================================================
    '//
    '// Alain DEBUISSON			le 07/11/2000		creation
    '//
    '//============================================================================
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
        Dim doc As Document

        Dim StrWorkbench As StrWorkbench
```
```

```vbscript
```vbscript
```cpp
        Dim strFactory As StrObjectFactory

        Set doc = CATIA.ActiveDocument
        Dim rootProduct As Product
        Set rootProduct = doc.Product
    	dim strMembers as StrMembers
```

```vbscript
        Set strWorkbench = doc.GetWorkbench("StrWorkbench")
        Set strMembers = rootProduct.GetTechnologicalObject("StructureMembers")
```
```

```

```

```vbscript
```vbscript
```vbscript
    	'============================================================
    	' looking for a member
    	'============================================================
```

```

```

    	dim member as StrMember
```vbscript
dim member as StrMember
```vbscript
    	set member = strMembers.Item("Column_3")
```

```

```vbscript
```vbscript
```vbscript
    	'============================================================
    	' rotate a member
    	'============================================================
```

```

```

```vbscript
```vbscript
```vbscript
' rotate a member
'============================================================
```

```

    	member.Rotate(45.0)
```

```vbscript
```vbscript
```vbscript
    	'============================================================
    	' anchor point modification
    	'============================================================
```

```

```

```vbscript
```vbscript
```vbscript
' anchor point modification
'============================================================
    	member.CurrentAnchorPointName = "catStrTopCenter"
```

```

```

```vbscript
```vbscript
```vbscript
    	'============================================================
    	' looking for a plate
    	'============================================================

    	dim strPlates as StrPlates
```

```

```

```vbscript
```vbscript
```vbscript
        Set strPlates = rootProduct.GetTechnologicalObject("StructurePlates")

```
```

```

```vbscript
```vbscript
Set strPlates = rootProduct.GetTechnologicalObject("StructurePlates")
```vbscript
```
```vbscript
    	dim plate as StrPlates
    	set plate = strPlates.Item("PlateType_11")
```

```

```

```vbscript
```vbscript
```vbscript
    	'============================================================
    	' inverse material orientation
    	'============================================================
```

```

```

```vbscript
```vbscript
```vbscript
' inverse material orientation
'============================================================
```

```

    	plate.ReverseDirection
```

```vbscript
```vbscript
```vbscript
    	'============================================================
    	' thickness modification
    	'============================================================
```

```

```

```vbscript
```vbscript
```vbscript
' thickness modification
'============================================================
    	plate.StandardThickness = 0.020
```

```

```

```vbscript
```vbscript
```vbscript
    	'============================================================
    	' update
    	'============================================================
```

```

```

```vbscript
```vbscript
```vbscript
' update
'============================================================
```

```

    	rootProduct.Update

```

```vbscript
```vbscript
    End Sub

```
```
