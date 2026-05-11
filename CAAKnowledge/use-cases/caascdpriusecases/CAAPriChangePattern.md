---
title: "Untitled"
category: "use-case"
module: "CAAScdPriUseCases"
tags: ["CAAScrBase", "CAAPriPatternDescription", "CATIA", "CAAScrJavaScript", "CAAPriChangePattern02", "CAAPriChangePatternSource", "CAAScdInfUseCases", "CAAPriChangePattern03", "CAAPriChangePattern01", "CAAPriChangePattern", "CAAInfLauchMacro", "CAAlink"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriChangePattern.htm"
converted: "2026-05-11T11:27:02.720499"
---

---

    

Once the macro has been started, the `oPartDocument `and `
    oPart `variables are declared to receive the instance of the part 
    document and the part.
    

#### Looking for the Circular Pattern Object in the Selection
    
    

`oSelection `variable is declared to receive the instance of 
    the part document selection, the string containing selection type name is 
    defined in an array `InputObjectType`, the `SelectElement2` 
    method is used to retrieve the selection:
    

      
- If the document selection is empty or contains an object other than a 
      circular pattern, a message is displayed in the left bottom corner of the 
      application, `Select a circular pattern`.
      
- If the selection contains a circular pattern, no message is displayed.
    
    

Take care, this allows you to select one object only in both cases!
    

`oCircularPattern `variable is declared to receive the 
    instance of the circular pattern from the selection collection.
    

#### Applying the Circular Pattern Description
    
    

The circular pattern number of instances is set to 6.
    
    

The circular pattern parameter is set to Unequal Angular Spacing.
    
    

For each circular pattern instances the angular spacing is modified.
    
    

The part document is updated, the circular pattern is modified.
    

![](images/CAAPriChangePattern02.gif)
  

![](../CAAScrBase/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to modify specifications of an existing circular 
pattern.

[Top]

---

#### References

---

*Copyright  2004, Dassault Systmes. All rights reserved.*



```vbscript
...
' ------------
' Get the part document
' ------------
Set oPartDocument = CATIA.ActiveDocument
' ------------
' Get the part
' ------------
Set oPart = oPartDocument.Part
   ...
```

```vbscript
...
' ------------
' Get the selection
' ------------
Set oSelection = oPartDocument.Selection
' ------------
' Set the selection type
' ------------
InputObjectType(0) = &quot;CircPattern&quot;
' ------------
' Get the status
' ------------
oStatus = oSelection.SelectElement2 ( InputObjectType, &quot;Select a circular pattern&quot;, True )
' ------------
' Get the object in the selection
' ------------
Set oCircularPattern = oSelection.Item(1).Value...
```

```vbscript
...
' ------------
' Set the circular pattern instance number
' ------------
oCircularPattern.AngularRepartition.InstancesCount.Value = 6
...
```

```vbscript
...
' ------------
' Set the circular pattern instance as Unequal Angular Spacing mode
' ------------
oCircularPattern.CircularPatternParameters = catUnequalAngularSpacing
oCircularPattern.SetUnequalStep 6
...
```

```vbscript
...
' ------------
' Set the circular pattern Unequal Angular Spacing
' ------------
oCircularPattern.SetInstanceAngularSpacing 2, 30.000000
oCircularPattern.SetInstanceAngularSpacing 3, 75.000000
oCircularPattern.SetInstanceAngularSpacing 4, 75.000000
oCircularPattern.SetInstanceAngularSpacing 5, 30.000000
oCircularPattern.SetInstanceAngularSpacing 6, 75.000000
...
```

```vbscript
...
' ------------
' Update the part
' ------------
oPart.Update 
...
```