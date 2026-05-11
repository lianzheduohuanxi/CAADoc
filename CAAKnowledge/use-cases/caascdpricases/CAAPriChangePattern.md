---
title: "Changing the Pattern Parameters"
category: "general"
module: "CAAScdPriUseCases"
tags: ["CATIA", "CAAPriChangePattern", "CAAPriPatternDescription"]
source_file: "Doc\online\CAAScdPriUseCases\CAAPriChangePattern.htm"
converted: "2026-05-11T17:31:51.211500"
---

## Part Design

| 

## Changing the Pattern Parameters  
  
---|---  
  
* * *

![](../CAAScrBase/images/atarget.gif) | This macro shows you how to change the description of a pattern to the unequal spacing angular mode.  
This macro allows you to define:

  * A new instances number.
  * The unequal spacing angular mode.
  * The angular values between instances.

It modifies the _ CircPattern_ object from its methods and properties, and update the part.  
---|---  
![](../CAAScrBase/images/ainfo.gif) | 

  * Open the [CAAPriChangePattern.CATPart](samples/CAAPriChangePattern.CATPart) document.
  * Reference in the application the catscript file:  [CAAPriChangePattern.htm](CAAPriChangePatternSource.htm).
  * Run the macro.
  * Select CircPattern.1 in the specification tree or in the the geometry.

  
![](../CAAScrBase/images/ascenari.gif) | CAAPriPatternDescription includes the following steps:

  1. Prolog
  2. Looking for the Circular Pattern Object in the Selection
  3. Applying the Circular Pattern Description



#### Prolog

Load the CAAPriPatternDescription.CATPart that contains two circular patterns. ![](images/CAAPriChangePattern01.gif) ![](images/CAAPriChangePattern03.gif) Run the macro. | 
    
    
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
  
---  
  
Once the macro has been started, the `oPartDocument `and ` oPart `variables are declared to receive the instance of the part document and the part.

#### Looking for the Circular Pattern Object in the Selection
    
    
    ...
    ' ------------
    ' Get the selection
    ' ------------
    Set oSelection = oPartDocument.Selection
    ' ------------
    ' Set the selection type
    ' ------------
    InputObjectType(0) = "CircPattern"
    ' ------------
    ' Get the status
    ' ------------
    oStatus = oSelection.SelectElement2 ( InputObjectType, "Select a circular pattern", True )
    ' ------------
    ' Get the object in the selection
    ' ------------
    Set oCircularPattern = oSelection.Item(1).Value...  
  
---  
  
`oSelection `variable is declared to receive the instance of the part document selection, the string containing selection type name is defined in an array `InputObjectType`, the `SelectElement2` method is used to retrieve the selection:

  * If the document selection is empty or contains an object other than a circular pattern, a message is displayed in the left bottom corner of the application, `Select a circular pattern`.
  * If the selection contains a circular pattern, no message is displayed.



Take care, this allows you to select one object only in both cases!

`oCircularPattern `variable is declared to receive the instance of the circular pattern from the selection collection.

#### Applying the Circular Pattern Description
    
    
    ...
    ' ------------
    ' Set the circular pattern instance number
    ' ------------
    oCircularPattern.AngularRepartition.InstancesCount.Value = 6
    ...  
  
---  
  
The circular pattern number of instances is set to 6.
    
    
    ...
    ' ------------
    ' Set the circular pattern instance as Unequal Angular Spacing mode
    ' ------------
    oCircularPattern.CircularPatternParameters = catUnequalAngularSpacing
    oCircularPattern.SetUnequalStep 6
    ...  
  
---  
  
The circular pattern parameter is set to Unequal Angular Spacing.
    
    
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
  
---  
  
For each circular pattern instances the angular spacing is modified.
    
    
    ...
    ' ------------
    ' Update the part
    ' ------------
    oPart.Update 
    ...  
  
---  
  
The part document is updated, the circular pattern is modified.

![](images/CAAPriChangePattern02.gif)  
  
![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *

#### In Short

This use case has shown how to modify specifications of an existing circular pattern.

[Top]

* * *

#### References

[1] | [Replaying a macro](../CAAScdInfUseCases/CAAInfLauchMacro.htm)  
---|---  
|   
[Top]  
  
* * *

_Copyright 2004, Dassault Systmes. All rights reserved._
