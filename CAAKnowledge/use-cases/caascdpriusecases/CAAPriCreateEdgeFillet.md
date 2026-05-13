---
title: "Untitled"
category: "use-case"
module: "CAAScdPriUseCases"
tags: ["CAAScrBase", "CAAPriCreateEdgeFillet", "CATIA", "CAAScrJavaScript", "CAAScdInfUseCases", "CAAScdPriUseCases", "CAAInfLauchMacro", "CAAPriCreateEdgeFilletSource", "CAAPriUseCases"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriCreateEdgeFillet.htmmd"
converted: "2026-05-11T11:27:02.721619"
---

---

      

oPad is retrieved by its name "Pad.1" in the PartBody tree.

#### Retrieving All the Vertical Edges of the Rectangular Pad
      
      
      

The elements to be filleted are edges. Here these
      elements are REdge features

      defined by their symbolic addresses.

#### Creating a first EdgeFillet with the selected edges

      

The AddNewEdgeFilletWithConstantRadius method from the ShapeFactory
      allows you to create a constant

      EdgeFillet with the propagation mode (1 for second argument) and a 5 mm
      radius.

      Update the part to compute the result of the EdgeFillet.
      

![](images/PartWithVerticalFillets.jpg)

      Figure 2: Rectangular pad with its vertical filleted edges.

#### Retrieving the Top and Bottom Faces of the Rectangular
Pad
      

Retrieve the Rsur features representing the top and bottom faces of the pad
to use
them to create another EdgeFillet.

#### Creating a Second EdgeFillet with the Selected Faces
      
      
      

 All the limiting edges of  the selected faces will be used to create the second EdgeFillet.
    
  
  
    
    
      

![image](../../assets/images/aendtask.gif)
    
  

[Top]

---

#### In Short

This use case has shown how to create EdgeFillets retrieving REdge or RSur
features from a pad.

[Top]

---

#### References

[Top]

---

*Copyright &#169; 2001, Dassault Syst&#232;mes. All rights reserved.*

```vbscript
...
```

```vbscript
...
```

```vbscript
...
```

```vbscript
...
```

```vbscript
...
```

```vbscript
...
```

```vbscript
...
```

```vbscript
...
```