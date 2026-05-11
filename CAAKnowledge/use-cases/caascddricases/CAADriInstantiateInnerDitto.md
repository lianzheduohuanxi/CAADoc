---
title: "Instantiating a Ditto in a Drawing View"
category: "general"
module: "CAAScdDriUseCases"
tags: ["CAADriInstantiateInnerDitto", "CAADriInstantiateDittoSource", "CATIA", "CAADriUseCases", "CAAScdDriUseCases"]
source_file: "Doc\online\CAAScdDriUseCases\CAADriInstantiateInnerDitto.htm"
converted: "2026-05-11T17:31:51.080302"
---

## Interactive Drafting

| 

## Instantiating a Ditto in a Drawing View  
  
---|---  
  
* * *

![](../CAAScrBase/images/atarget.gif) | This macro shows you how to instantiate a ditto into a view from a detail view of the current drawing document, offers to user to define the ditto location and defines the ditto's modifiable text value. This macro open the drawing document containing the view an the detail view.   
---|---  
![](../CAAScrBase/images/ainfo.gif) |  CAADriInstantiateInnerDitto is launched in CATIA [1]. No open document is needed. [CAADriInstantiateInnerDitto](CAADriInstantiateInnerDittoSource.htm) is located in the CAADriUseCases module.  [Execute macro](macros/CAADriInstantiateInnerDitto.CATScript) (Windows only).  
![](../CAAScrBase/images/ascenari.gif) | CAADriInstantiateInnerDitto includes seven steps: 

  1. Prolog
  2. Opening the Drawing Document
  3. Retrieving and Defining the View
  4. Retrieving and Defining the Detail View
  5. Defining the Ditto's Location
  6. Instantiating the Ditto
  7. Retrieving the Ditto's Modifiable Text



#### Prolog

| 
    
    
      ...
        ' Set the CATIA popup file alerts to False
        ' It prevents to stop the macro at each alert during its execution
        CATIA.DisplayFileAlerts = False
      ...  
  
---  
  
The CATIA prompts are disabled thanks to the `DisplayFileAlerts` property of the _Application_ object set to `False`.

#### Opening the Drawing Document
    
    
      ...
        ' Open the drawing document
        Dim oDrawing As DrawingDocument
        Set oDrawing = CATIA.Documents.Open(sDocPath & _
                 "\online\CAAScdDriUseCases\samples\CAADriInstantiateDittoSource.CATDrawing")    
      ...  
  
---  
  
A drawing document is opened, its window is reframed according to the size of the sheet.

#### Retrieving and Defining the View
    
    
      ...
        ' Retrieve the sheets collection of the drawing document
        Dim oSheets As DrawingSheets
        Set oSheets = oDrawing.Sheets
        
        ' Retrieve the sheet where the detail view will be instantiated
        Dim oSheet As DrawingSheet
        Set oSheet = oSheets.Item("Sheet.1")
        
        ' Retrieve the view where the detail view will be instantiated
        Dim oView As DrawingView
        Set oView = oSheet.Views.Item("View.3")
        oView.Activate
      ...  
  
---  
  
The sheets collection is retrieved from the `oDrawing` object using the `Sheets` method.  
The sheet object is retrieved from the collection using the `Item` method from its name.  
The views collection is retrieved from the `oSheet` object using the `Views` method.  
The view object is retrieved from the collection using the `Item` method from its name.  
The view is activated.

#### Retrieving and Defining the Detail View
    
    
      ...
        ' Retrieve the detail sheet containing the detail view to be instantiated
        Dim oDetailSheet As DrawingSheet
        Set oDetailSheet = oSheets.Item("Sheet.2 (Detail)")
        
        ' Retrieve the detail view to be instantiated
        Dim oDetailView As DrawingView
        Set oDetailView = oDetailSheet.Views.Item("DrwDetail.1")
      ...  
  
---  
  
The detail sheet object is retrieved from the collection using the `Item` method from its name.  
The detail view object is retrieved from the collection using the `Item` method from its name.

#### Defining the Ditto's Location
    
    
      ...
        ' Indicate the ditto location
        Dim ReturnStatus As String
        Dim iDittoCoordinates(1)
        Dim oDraw
        Set oDraw = oDrawing
        ReturnStatus = oDraw.Indicate2D("Indicate the ditto location", iDittoCoordinates)
      ...  
  
---  
  
The ditto's location is retrieved using the `Indicate2D` method which allow user to retrieve the `x` and `y` coordinates when clicking the mouse. Coordinates are stored  in an array `iDittoCoordinates`. An unspecified object `oDraw` is used to prevent a signature's method restriction usage.

![](images/img014.gif)

#### Instantiating the Ditto
    
    
      ...
        ' Retrieve the drawing components collection of the target drawing view
        Dim o2DComponents As DrawingComponents
        Set o2DComponents = oView.Components
        
        ' Create the ditto
        Dim o2DComponent As DrawingComponent
        Set o2DComponent = o2DComponents.Add(oDetailView, iDittoCoordinates(0), iDittoCoordinates(1))
      ...  
  
---  
  
The components collection is retrieved from the `oView` object using the `Components` method.  
The component object is created in the collection using the `Add` method from the `oDetailView` view.

![](images/img015.gif)

#### Retrieving the Ditto's Modifiable Text
    
    
      ...
        ' Retrieve the modifiable text of the ditto
        Dim oText As DrawingText
        Set oText = o2DComponent.GetModifiableObject(1)
        
        ' Modify the modifiable text value
        Dim ReturnValue As String
        ReturnValue = InputBox("Enter a value", "", "New Value For Text")
        oText.Text = ReturnValue
      ...  
  
---  
  
The text object is retrieved from the `o2DComponent` object using the `GetModifiableObject` method.  
The text of the text object is returned using the `InputBox` procedure. Enter 10 and click OK.

![](images/img016.gif)

![](images/img017.gif)  
  
![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *

#### In Short

This use case has shown how to instantiate a drawing detail view as a ditto in a view using the _Add_ method of the _Components_ object.

[Top]

* * *

#### References

[1] | [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.htm)  
---|---  
[2] | _[DrawingDocument](../CAAScdDriTechArticles/CAADriObjDrawingDocument.htm)_ , _[DrawingSheet](../CAAScdDriTechArticles/CAADriObjDrawingSheet.htm),_ [_DrawingSheets_](../CAAScdDriTechArticles/CAADriObjDrawingSheets.htm) _,_[_DrawingView_](../CAAScdDriTechArticles/CAADriObjDrawingView.htm)  
[Top]  
  
* * *

_Copyright 2003, Dassault Systmes. All rights reserved._
