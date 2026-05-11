---
```vbscript
title: "Getting Started with Automation"
category: "use-case"
module: "CAAScdInfUseCases"
tags: ["CAAScdInfUseCases", "CATIA", "CAAInfGettingStarted", "CATIASketch3"]
source_file: "Doc/online/CAAScdInfUseCases/CAAInfGettingStarted.htm"
converted: "2026-05-11T17:31:52.374517"
```

---
| 
## Infrastructure

| 
## Getting Started with Automation  

* * *

This article will show you how to use a scripting language to access CAA V5 automation objects to capture your own know-how and to increase your productivity. You can customize V5 applications to automate repetitive tasks, and to make it fit your own process.

This article will show you how to use a scripting language to access CAA V5 automation objects to capture your own know-how and to increase your productivity. You can customize V5 applications to automate repetitive tasks, and to make it fit your own process.
The products that make up the CATIA and DELMIA applications share the same object model which can be accessed, as well as their own objects, by scripts written in Visual Basic with Windows, and scripts written in Basic Script for UNIX.

You can write your scripts from scratch, but you can also use the journalling facility from the **Macros ...  ** command in the **Tools** menu that records end-user scenarios in scripts you can then use as is or modify. 

 Recording macros is not available in all workbenches.  

You can write your scripts from scratch, but you can also use the journalling facility from the **Macros ...  ** command in the **Tools** menu that records end-user scenarios in scripts you can then use as is or modify.
Recording macros is not available in all workbenches.
We put here a simple script **example** , to show what is scripting, which are the different things to do to script, present briefly the scripting environment and dialog window, and what is journaling. This example is divided into the following parts:

  * 1-Recording the Scenario, where we'll record the creation of a cylindric pad.
  * 2-Understanding the recorded macro, where we'll explain the content of the resulting recorded macro
  * 3-Modifying the Generated Macro, where we'll modify the generated macro to create five similar pads
  * 4-Replaying the Modified Macro

You will then find information about the scripting languages and environments, and some keys for you if you are not familiar with writing macros in [Invoking CATIA from a Scripting Language](../CAAScdInfTechArticles/CAAInfInvoking.md).
## 1-Recording the Scenario

You will then find information about the scripting languages and environments, and some keys for you if you are not familiar with writing macros in [Invoking CATIA from a Scripting Language](../CAAScdInfTechArticles/CAAInfInvoking.md).
  This scenario creates a circle in a sketch, and uses this sketch to create a cylindric pad.  

You will then find information about the scripting languages and environments, and some keys for you if you are not familiar with writing macros in [Invoking CATIA from a Scripting Language](../CAAScdInfTechArticles/CAAInfInvoking.md).
This scenario creates a circle in a sketch, and uses this sketch to create a cylindric pad.
  The recorded macro is stored in a file, and not in the document.  

  1. Select the **Tools- >Macro->Start Recording ... ** command to display the Record Macro dialog box:

> ![](images/CAAInfRecord2.jpg) A default macro library is provided. Macro libraries are places where a macro can be stored, they can be folders, VBA project or Documents.  Depending in the library, you can select different recording languages. Select CATScript to have a result similar to what you will find below. 

  | 

  1. Click **Start** in the **Record Macro** dialog box to start recording the macro. The **Stop Recording** dialog box appears.

 ![](images/CAAInfRecord3.jpg)  
  | 

  1. In the **File** menu, click on **New,** or click on the
![](images/I_NewP2.gif) icon, and double-click Part to create a new part. A new part is created and a window for this part is opened. 

  | 

  1. Select the xy plane in the specification tree, and select the sketcher icon
![](images/I_SketcherP2.gif) to create a sketch. 

  | 

  1. In the sketcher toolbar, select the circle icon
![](images/I_CircleCtrRadP2.gif) and click twice to successively  indicate the center of the circle and a current point on the circle. 

  | 

  1. Click on the sketcher exit icon ![](images/I_CloseP2.gif)

  | 

  1. Select the pad icon ![](images/I_PadP2.gif) to create a pad on the sketch.

  | 

  1. In the Pad Definition dialog box, choose a length of 20 mm and click OK. The pad is created.

  | 

  1. The pad creation is now complete.

  | 

  1. Click **Stop Recording** in the **Stop Recording** dialog box, or select the **Tools- >Macro->Stop Recording** command. Your macro is now stored in the file you have selected.

![](images/CAAInfRecord3.jpg)    
![](images/aendtask.gif)  
##   
1. Click **Stop Recording** in the **Stop Recording** dialog box, or select the **Tools- >Macro->Stop Recording** command. Your macro is now stored in the file you have selected.
2-Understanding the recorded macro

We detail below, line by line, what has been recorded, following the interactive steps. How to access the macro generated source is explained in the next step (Modifying the Generated Macro):

  1. Starting to record a macro creates the macro file and generates the first instruction stating the scripting language used and the macro entry point, the _CATMain_ sub: 

> > 
>>     Language="VBSCRIPT"
>>     
>>     Sub CATMain()

  1. Click on the**New** item of the **File** menu**,** or click on the ![](images/I_NewP2.gif) icon**,** and double-click Part to create a new part generates the following instructions: 

> Dim documents1 As Documents
>          Set documents1 = CATIA.Documents
>          
>          Dim partDocument1 As Document
>          Set partDocument1 = documents1.Add("Part")
>          

A new document with the Part type is created. To do this, such a document is added to the _Documents_ collection of the `CATIA` application. 

  2. Select the xy plane and click on the sketcher icon ![](images/I_SketcherP2.gif) to create a sketch: 

> Dim part1 As Part
>          Set part1 = partDocument1.Part
>          
>          Dim bodies1 As Bodies
>          Set bodies1 = part1.Bodies
>          
>          Dim body1 As Body
>          Set body1 = bodies1.Item("PartBody")
>          
>          Dim sketches1 As Sketches
>          Set sketches1 = body1.Sketches
>          
>          Dim originElements1 As OriginElements
>          Set originElements1 = part1.OriginElements
>          
>          Dim reference1 As AnyObject
>          Set reference1 = originElements1.PlaneXY
>          
>          Dim sketch1 As Sketch
>          Set sketch1 = sketches1.Add(reference1)
>          
>          Dim arrayOfVariantOfDouble1(8)
>          arrayOfVariantOfDouble1(0) = 0.000000
>          arrayOfVariantOfDouble1(1) = 0.000000
>          arrayOfVariantOfDouble1(2) = 0.000000
>          arrayOfVariantOfDouble1(3) = 1.000000
>          arrayOfVariantOfDouble1(4) = 0.000000
>          arrayOfVariantOfDouble1(5) = 0.000000
>          arrayOfVariantOfDouble1(6) = 0.000000
>          arrayOfVariantOfDouble1(7) = 1.000000
>          arrayOfVariantOfDouble1(8) = 0.000000
>          sketch1.SetAbsoluteAxisData arrayOfVariantOfDouble1
>          
>          Dim factory2D1 As Factory2D
>          Set factory2D1 = sketch1.OpenEdition()

A _Sketch_ object named `Sketch1` is added to the _Sketches_ collection using the `reference1` _Reference_ corresponding to the XY plane as a support. Using a reference allows to create a sketch either on an element, as here the XY plane, or on a solid planar face that is not directly accessible as a VB object. 

The `SetAbsoluteAxisData` method is used to define the orientation of the sketch axis, that can be on either side and can rotate inside of the support plane. A _Factory2D_ object is created by opening the sketch editor against the created sketch. This _Factory2D_ object features methods to create 2D objects.

> > 
>>     Dim geometricElements1 As GeometricElements
>>     Set geometricElements1 = sketch1.GeometricElements
>>     
>>     Dim axis2D1 As GeometricElement
>>     Set axis2D1 = geometricElements1.Item("AbsoluteAxis")
>>     
>>     Dim line2D1 As AnyObject
>>     Set line2D1 = axis2D1.GetItem("HDirection")
>>     
>>     line2D1.ReportName = 1
>>     
>>     Dim line2D2 As AnyObject
>>     Set line2D2 = axis2D1.GetItem("VDirection")
>>     
>>     line2D2.ReportName = 2

When the sketch is created, an axis, that is the aggregation of a center point, and horizontal line and vertical line (directions), is created. 

When the sketch is created, an axis, that is the aggregation of a center point, and horizontal line and vertical line (directions), is created.
The axis is retrieved in the _GeometricElements_ collection of the _Sketch_ object, the directions are retrieved as objects aggregated by the axis. The two lines are here assigned an identifier using their `ReportName` property that will be used by the 3D modeling services to retrieve those elements inside of the sketch. They have no end-user meaning.

  1. In the sketcher toolbar, select the circle icon ![](images/I_CircleCtrRadP2.gif) and click twice to indicate successively the center of the circle and a current point on the circle 

> > 
>>     Dim circle2D1 As Circle2D
>>     Set circle2D1 = factory2D1.CreateClosedCircle(0.000000, 0.000000, 10.000000)
>>         
>>     Dim point2D1 As AnyObject
>>     Set point2D1 = axis2D1.GetItem("Origin")
>>         
>>     circle2D1.CenterPoint = point2D1
>>         
>>     circle2D1.ReportName = 3
>>         
> 
> The `CreateCloseCircle` method of the _Factory2D_ object is used to create the circle. It is first created as centered at the point (0,0) with a radius of 10 mm. It is then constraint on the axis center point using the `CenterPoint` property. 

  1. Click on the sketcher exit icon ![](images/I_CloseP2.gif)

1. Click on the sketcher exit icon ![](images/I_CloseP2.gif)
         CATIASketch3.CloseEdition
             part1.Update 

The sketch editor is closed and the part udapted.

  2. Select the pad icon ![](images/I_PadP2.gif) to create a pad, and in the Pad Definition dialog box, choose a length of 10 mm and click OK. The pad is created. 

```vbscript
         Dim shapeFactory1 As Factory
             Set shapeFactory1 = part1.ShapeFactory

             Dim pad1 As Pad
             Set pad1 = shapeFactory1.AddNewPad(sketch1, 20.000000)

```

```vbscript
Dim pad1 As Pad
Set pad1 = shapeFactory1.AddNewPad(sketch1, 20.000000)
             part1.Update  

The `AddNewPad` method of the _ShapeFactory_ object is used to create the pad. It is created using the sketch and the length of 20mm. The part is updated.  

  3. Click **Stop Recording** in the **Stop Recording** dialog box, or point to **Stop Recording** in the Macro item of the Tools menu.

This closes the macro recording sequence and saves the macro in the selected file.

This is all what you performed interactively in the previous chapter.

```

## 3-Modifying the Generated Macro

 This task explains how to modify the generated macro to make it loop on the creation of five identical cylindric pads.  
---|---  

  1. Select the **Tools- >Macro->Macros... command **to display the **Macros** dialog box.

![](images/CAAInfEdit1.jpg)    
  | 

  1. Select the name of the macro you have just created and click on **Edit** to display the **Macro Editor** window.

![](images/CAAInfEdit2.jpg)    

 You can choose your own text editor to edit the macro by  setting the **CATMacroEditor** environment variable prior to launching CATIA with the name of the editor program:

You can choose your own text editor to edit the macro by  setting the **CATMacroEditor** environment variable prior to launching CATIA with the name of the editor program:
        set CATMacroEditor=NOTEPAD

or using **Control Panel/System/Environment** on Windows, or:

       export CATMacroEditor=vi

On Unix. This editor must be accessible through the **PATH** environment variable. Consult your administrator for more information on how to proceed.      

  | 

export CATMacroEditor=vi
On Unix. This editor must be accessible through the **PATH** environment variable. Consult your administrator for more information on how to proceed.
  1. The instructions written using the bold typeface are those you need to add or modify while the others already exist in the macro: 

         Language="VBSCRIPT"

         **'My macro creates five cylinders**

         Sub CATMain()

         **...**
```vbscript
         Dim refer1 As AnyObject
         Set refer1 = originElements1.PlaneXY

```

         **x = 0**

```vbscript
         Dim arrayOfVariantOfDouble1(8)
         arrayOfVariantOfDouble1(0) = 0.000000
```

         ...
```vbscript
Dim arrayOfVariantOfDouble1(8)
arrayOfVariantOfDouble1(0) = 0.000000
         arrayOfVariantOfDouble1(8) = 0.000000

```

         **For I = 1 To 5**

```vbscript
           Dim sketch1 As Sketch
           Set sketch1 = sketches1.Add(refer1)
```

           **...**
```vbscript
           Dim circle2D1 As Circle2D
           Set circle2D1 =                   _
              factory2D1.CreateClosedCircle( _
```

                                   **x** ,        _
                                   0.000000, _
0.000000, _
                                   10.000000)

           circle2D1.ReportName = 3

           **...**
0.000000, _
10.000000)
circle2D1.ReportName = 3
           part1.Update 

           **x = x + 25
circle2D1.ReportName = 3
part1.Update
         Next** End Sub  

You simply need to initialize a variable, here x, to allow for the sketch position in the plane to vary, and create a loop beginning with the `For` keyword and ending with the **`Next`** keyword. The `For` keyword specifies the counter variable `I` which will take all values between 1 and 5 inclusively. Move the array declaration and valuation outside of the loop:  those values do not change. Change the first parameter of the `CreateCloseCircle` method to `x`. Increment the value of the `x` variable to move the next center of 25mm from the previous one. 

  | 

  1. Save the macro using the **File- >Save** command of the Macro Editor and exit the editor using the **File- >Exit** command.

The source of the modified macro, [CAAInfGettingStarted.CATScript](CAAInfGettingStartedSource.md), is available in the CAAScdInfUseCases module. [Execute macro](macros/CAAInfGettingStarted.CATScript) (windows only).  ![](images/aendtask.gif)  
## 4-Running the Macro

The source of the modified macro, [CAAInfGettingStarted.CATScript](CAAInfGettingStartedSource.md), is available in the CAAScdInfUseCases module. [Execute macro](macros/CAAInfGettingStarted.CATScript) (windows only).  ![](images/aendtask.gif)
  This task explains how to run the modified macro.  

The source of the modified macro, [CAAInfGettingStarted.CATScript](CAAInfGettingStartedSource.md), is available in the CAAScdInfUseCases module. [Execute macro](macros/CAAInfGettingStarted.CATScript) (windows only).  ![](images/aendtask.gif)
This task explains how to run the modified macro.
  After exiting the Macro Editor, you're back in the Macros window: ![](images/CAAInfEdit1.jpg) Your macro should be the current one. You just have to click **Run** to run this macro. Here is the result.![](images/CAAInfReplay2.jpg)    

![](images/aendtask.gif)  

* * *
#### In Short

This use case has shown how to record a macro, modify it and then launch its execution.

[Top]

* * *
#### References

[1] | [Adding a Macro as a Command in a Toolbar](CAAInfAddingMacroInToolbar.md)  
---|---  
[Top]
