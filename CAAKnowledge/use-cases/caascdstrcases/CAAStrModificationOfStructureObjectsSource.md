---
title: "CAAStrModificationOfStructureObjects.CATScript"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CATIA", "CAAStrModificationOfStructureObjects"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrModificationOfStructureObjectsSource.htm"
converted: "2026-05-11T17:31:50.903114"
---

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

    
```vbscript
    Sub CATMain()
    
```vbscript
        Dim doc As Document
    
        Dim StrWorkbench As StrWorkbench
        Dim strFactory As StrObjectFactory
    
        Set doc = CATIA.ActiveDocument
        Dim rootProduct As Product
        Set rootProduct = doc.Product
    	dim strMembers as StrMembers
    
        Set strWorkbench = doc.GetWorkbench("StrWorkbench")
        Set strMembers = rootProduct.GetTechnologicalObject("StructureMembers")
```vbscript
    	'============================================================
    	' looking for a member
    	'============================================================
```

    
```

    	dim member as StrMember
    	set member = strMembers.Item("Column_3")
```vbscript
    	'============================================================
    	' rotate a member
    	'============================================================
```

    
    	member.Rotate(45.0)
```vbscript
    	'============================================================
    	' anchor point modification
    	'============================================================
```

    
    	member.CurrentAnchorPointName = "catStrTopCenter"
```vbscript
    	'============================================================
    	' looking for a plate
    	'============================================================
    
    	dim strPlates as StrPlates
```

```vbscript
        Set strPlates = rootProduct.GetTechnologicalObject("StructurePlates")
    
```

    	dim plate as StrPlates
    	set plate = strPlates.Item("PlateType_11")
```vbscript
    	'============================================================
    	' inverse material orientation
    	'============================================================
```

    
    	plate.ReverseDirection
```vbscript
    	'============================================================
    	' thickness modification
    	'============================================================
```

    
    	plate.StandardThickness = 0.020
```vbscript
    	'============================================================
    	' update
    	'============================================================
```

    
    	rootProduct.Update
    	
```vbscript
    End Sub
    
```

    
    
    

```