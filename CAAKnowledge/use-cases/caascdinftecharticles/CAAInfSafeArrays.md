---
title: "About CATSafeArrayVariant"
category: "use-case"
module: "CAAScdInfTechArticles"
tags: ["CATIA"]
source_file: "Doc/online/CAAScdInfTechArticles/CAAInfSafeArrays.md"
converted: "2026-05-11T17:31:52.433114"
---
## Infrastructure
 
 | 
 ## About CATSafeArrayVariant  
   
   
 * * *
 
 Many methods which return a value do not return a single value, but an array of values. For example, the **GetOrigin** property of the **Viewpoint3D** object returns a 3D point as an array of three coordinates. This array is returned as an output argument.
 
 Such arguments are visible in the VB/VBA object browser as a **variant** but the reference documentation lists them as **CATSafeArrayVariant**.
 
 You can retrieve in the **MyVPOrigin** variable the origin of the 3D viewpoint of the active viewer in the active window as follows:
     
     ReDim MyVPOrigin(2)
```vbscript
     CATIA.ActiveWindow.ActiveViewer.Viewpoint3D.GetOrigin MyVPOrigin
 
```

 You should directly use the ReDim statement to assign a size to the array while declaring it as a variable size array, and then call the GetOrigin method. Assigning a size of 2 allocates an array containing three values.
 
 To access each coordinate, you need to go deeper:
 
     * The x coordinate is in **MyVPOrigin(0)**
     * The y coordinate is in **MyVPOrigin(1)**
     * The z coordinate is in **MyVPOrigin(2)**
 
 Contrary to collections, a CATSafeArrayVariant's index begins at 0. To set a new triplet of values, you can write:
     
     MyVPOrigin = Array(150, 200, 50)
```vbscript
     CATIA.ActiveWindow.ActiveViewer.Viewpoint3D.PutOrigin MyVPOrigin
 
```

 or
     
```vbscript
     CATIA.ActiveWindow.ActiveViewer.Viewpoint3D.PutOrigin Array(150, 200, 50)
 
```

 But to modify the y coordinate only, write:
     
     MyVPOrigin(1) = 200
 
```vbscript
 CATIA.ActiveWindow.ActiveViewer.Viewpoint3D.PutOrigin MyVPOrigin 
 
```

 When you don't know the size of an array, use the UBound function. It returns the rank of the highest element in the array. For example the following example returns 2 in Highestrank:
     
     Highestrank = Ubound(MyVPOrigin)
 
 [Top]
 
 * * *
 
 _Copyright 1994-2004, Dassault Systmes. All rights reserved._

```