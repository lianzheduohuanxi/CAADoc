---
title: "Managing Indication"
category: "use case"
module: "CAADegUseCases"
tags: ["CAACreateCircleCmd", "CAADegCreateCircleCmd", "CAADialogEngine", "CAAGeometry", "CATIndicationAgent", "CAADegGeoCommands"]
source_file: "Doc\online\CAADegUseCases\CAADegSampleIndication.htm"
converted: "2026-05-11T17:33:49.684430"
---

3D PLM Enterprise Architecture |  User Interface - Commands |  Managing Indication _Retrieving a 3D point from a mouse click_  
---|---|---  
Use Case  
  
* * *

Abstract This article shows how to retrieve a point in the 3D space from an end user mouse click on the screen in a state dialog command. 
    * **What You Will Learn With This Use Case**
    * **The Circle Command Use Case**
      * What Does the Circle Command Do
      * How to Launch the Circle Command
      * Where to Find the Circle Command Code
    * **Step-by-Step**
    * **In Short**
    * **References**  
---  
  
* * *

What You Will Learn With This Use Case This use case is intended to show how to retrieve, in a state dialog command, a 3D point using its coordinates in the 3D space from a mouse click on the screen. This 3D point can be used afterwards as input for any object creation, modification, or analysis in the document, such as creating the center of a circle in this example. [Top] The Circle Command Use Case CAADegCreateCircleCmd creates a circle in the 3D space. We will focus on the circle center creation. [Top] What Does the Circle Command Do The Circle command is a state dialog command that creates a circle in the 3D space according to the following UML statechart diagram [1]. ![CAACreateCircleStatechart.jpg \(21192 bytes\)](images/CAACreateCircleStatechart.jpg) The dialog is as follows: ![CAACreateCircle1.jpg \(19537 bytes\)](images/CAACreateCircle1.jpg) | Select an existing plane that will be used as the circle plane. The active state becomes GetPlane.  
---|---  
![CAACreateCircle2.jpg \(19058 bytes\)](images/CAACreateCircle2.jpg) | The viewpoint changes to make the selected plane and the screen plane coincide. The active state is GetCircle.  
![CAACreateCircle3.jpg \(19295 bytes\)](images/CAACreateCircle3.jpg) | Click to indicate a point for the circle center. The active state becomes GetRadius. This image is captured just after the click. The indicated point is shown beside the plane. The mouse has not yet moved.  
![CAACreateCircle4.jpg \(20301 bytes\)](images/CAACreateCircle4.jpg) | Move the mouse from this center. A temporary circle is drawn and increases or decreases to follow the mouse moves. The active state remains GetRadius. The self transition loops onto this state.  
![CAACreateCircle5.jpg \(20578 bytes\)](images/CAACreateCircle5.jpg) | When the wished circle is obtained, click a point on this circle to actually create the circle. The command is now complete.  
Indicating a point means clicking on the screen at the desired location with the left mouse key. The command retrieves from this click a geometric point with coordinates expressed in the absolute axis system. This is made possible by assigning an indication agent [2] to the state that asks for indication. This indication agent is valued by the mouse click with a point computed from the pixel coordinates of the point clicked on the screen. This point is the projection of the clicked point in the screen plane onto a specific plane associated with the indication point and therefore named the projection plane [2]. The Circle command uses this means to create the circle center and to determine the circle radius. The step by step describes the circle center creation. [Top] How to Launch the Circle Command See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.htm)" use case for a detailed description of how this use case should be launched.  Then, in the window where you run the mkrun command, do not type the module name on the command line, but type CNEXT instead. When the application is ready, do the following: 
    * Select File->New
    * In the New box, select CAAGeometry and click OK
    * Select Insert->Point
    * Create three points
    * Select Insert->Plane
    * Successively click the three points to create a plane
    * Select Insert->Circle
    * Click to create the circle center
    * Click to create the circle.
[Top] Where to Find the Circle Command Code The Circle command is made of a single class named _CAADegCreateCircleCmd_ located in the CAADegGeoCommands.m module of the CAADialogEngine.edu framework: Windows | `InstallRootDirectory\CAADialogEngine.edu\CAADegGeoCommands.m\`  
---|---  
Unix | `InstallRootDirectory/CAADialogEngine.edu/CAADegGeoCommands.m/`  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed. [Top] Step-by-Step To create the circle center, there are seven steps: # | Step | Where  
---|---|---  
1 | Declare the indication agent | Header file  
2 | Instantiate the indication agent | `BuildGraph` method [3]  
3 | Set the indication agent projection plane | Transition action method `SetPlane`  
4 | Assign the indication agent to the GetCenter state | `BuildGraph` method  
5 | Create a transition from the GetCenter state triggered by the indication agent valuation | `BuildGraph` method  
6 | Retrieve the indication agent value and convert this value into a 3D point | Transition action method `CreateCircleCenter`  
7 | Release the indication agent | Destructor or `Cancel` method  
[Top] Declaring the Indication Agent and its Projection Plane The state command class derives from CATStateCommand.
    
    class CAADegCreateCircleCmd : public CATStateCommand
    {
      ...
      private :
        CATIndicationAgent * _daIndicCircleCenter;
        CATMathPlane         _ProjPlane;
        CATMathPoint         _CircleCenter;
        ...  
  
---  
A pointer to the indication agent, its projection plane, and the temporary point to keep the circle center are declared as private data members. [Top] Instantiating the Indication Agent The indication agent is instantiated in the command `BuildGraph` method.
    
    void CAACreateCircleCmd::BuildGraph()
    {
      ...
      _daIndicCircleCenter = **new** **CATIndicationAgent**("GetCircleCenter");
      ...  
  
---  
The character string GetCircleCenter defined as the argument of the CATIndicationAgent constructor is the indication agent identifier. This identifier can be used to assign undo/redo prompts replacing the Undo and Redo items in the Edit menu. [Top] Setting the Selected Plane as the Indication Agent Projection Plane The `SetPlane` method is the action method associated with the transition that retrieves the selected plane and use it to change the viewpoint. It is the appropriate place to assign this plane as the indication agent projection plane, since the plane selected is not kept as a data member.
    
    CATBoolean CAACreateCircleCmd::SetPlane(void *iDummy)
    {
      ... _// Retrieve the origin and axes of the selected document plane_
      CATMathPoint     PlaneOrigin;        
      CATMathDirection U, V;
      modelplane->GetOrigin(PlaneOrigin);
      modelplane->GetPlane(U,V);
              
      _// Set these retrieved origin and axes to the _ProjPlane_
      _ProjPlane.**SetOrigin**(PlaneOrigin);
      _ProjPlane.**SetDirections**(U,V);
    
      _// Set _ProjPlane as the indiation agent projection plane_
      _daIndicCircleCenter->**SetMathPlane**(_ProjPlane);
      ...  
  
---  
The plane selected in the document is retrieved in `modelplane`. Its origin and directions are retrieved using the methods of this object, and are set to `_ProjPlane` using the `SetOrigin` and `SetDirections` methods of the CATMathPlane class. Then `_ProjPlane` is set as the indication agent projection plane. [Top] Assigning the Indication Agent to the GetCenter State Still in the `BuildGraph` method, the GetCenter state is created, and the indication agent is added to this state. This makes it possible to value the indication agent when this state becomes the active one.
    
    ...
      CATDialogState *stGetCircleCenter = **AddDialogState**("stGetCircleCenterId");
      stGetCircleCenter->**AddDialogAgent**(_daIndicCircleCenter);
      ...  
  
---  
The `AddDialogState` method creates a new dialog state and adds it to the states managed by the dialog command. The `AddDialogAgent` method adds the indication agent to the state. [Top] Creating a Transition between the GetCenter and GetRadius States The transition between these two states is created in the `BuildGraph` method. This transition is triggered when the indication agent is valued, that is when the end user clicks a point. The guard condition is checked, and if it returns True, the action is performed.
    
    ...
      CATDialogTransition *pSecondTransition = **AddTransition**
      (
        stGetCircleCenter,
        stGetRadius,
        AndCondition(
          IsOutputSetCondition(_daIndicCircleCenter),
          Condition((ConditionMethod) & CAACreateCircleCmd::CheckCircleCenter)),			  
        Action((ActionMethod) & CAACreateCircleCmd::CreateCircleCenter)
      );
    ...  
  
---  
The `AddTransition` method creates a transition and adds it to the transitions managed by the dialog command. Pointers to the transition's source and target states are the first and second arguments respectively. The transition trigger is defined in the guard condition as the first condition to be checked using the `IsOutputSetCondition` method applied to the indication agent. A second condition that is useless for this use case purpose uses the `CheckCircleCenter` method. Because we use `AndCondition` to create the guard condition, both condition methods must return True to fire the transition. In this case, the `CreateCircleCenter` action method is executed. [Top] Retrieving the Indicated Point and Converting it to a 3D Point When the end user has clicked to indicate a point, the transition between the GetCenter and GetRadius states is triggered, and if the guard condition returns True, the following action method executes.
    
    CATBoolean CAACreateCircleCmd::CreateCircleCenter(void * iData)
    {
      _// Get the indicated point from the indication agent_
      CATMathPoint2D point2D = _daIndicCircleCenter->**GetValue**();
      _// Convert this point to a 3D point for the circle center_
      _ProjPlane.**EvalPoint**(point2D.GetX(), point2D.GetY(), _CircleCenter);
      _// Retrieve the circle center coordinates_
      float x = (float) _CircleCenter.GetX(); 
      float y = (float) _CircleCenter.GetY();
      float z = (float) _CircleCenter.GetZ();
      ...  
  
---  
The indication agent is valued by the end user click. Its value is a 2D point located on the indication agent projection plane, obtained by the projection of the point corresponding to the mouse location on the screen when the click happens along a line passing through the viewpoint eye and the point clicked onto the projection plane. The indication agent `GetValue` method retrieves this 2D point whose coordinates are expressed according to the projection plane axis system. Then the CATMathPlane `EvalPoint` method creates a 3D point from these coordinates. Then you can use the 3D point as you wish, for example retrieve its coordinates expressed with respect of the 3D global axis system. [Top] Releasing the Indication Agent A pointer to the indication agent was created in the command `BuildGraph` method as a data member to be accessed and used in different methods. It should be released when it becomes useless. This can be done in the command destructor, as shown here. This could also be done in the `Cancel` method called just before the destructor.
    
    CAACreateCircleCmd::~CAACreateCircleCmd()
    {
      ...
      if (NULL != _daIndicCircleCenter) _daIndicCircleCenter->**RequestDelayedDestruction**();
      daIndicCircleCenter = NULL ;
      ...  
  
---  
[Top]

* * *

In Short This use case shows the objects involved in an end user indication: the state dialog command, the statechart and its implementation in the `BuildGraph` method, the states, the indication dialog agent and its projection plane, the transition along with its composite condition and action, and the way to retrieve a usable 3D point from the pixel clicked on the screen by the end user. [Top]

* * *

References [1] | [Describing State Dialog Commands Using UML](../CAADegTechArticles/CAADegUMLDescription.htm)  
---|---  
[2] | [Managing Indication](../CAADegTechArticles/CAADegGraph.htm#510000)  
[3] | [Implementing the Statechart Diagram](../CAADegTechArticles/CAADegGraph.htm)  
[Top]  
  
* * *

History Version: **1** [Jan 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
