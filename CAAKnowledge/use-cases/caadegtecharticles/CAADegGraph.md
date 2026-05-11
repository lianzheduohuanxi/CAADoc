---
title: "Implementing the Command Statechart Diagram"
category: "general"
module: "CAADegTechArticles"
tags: ["CAACreatePolylineCmd", "CAAILine", "CATI2DPoint", "CAACommandCmd", "CAACreateCircleCmd", "CATI3DCamera", "CATI2DControlPoint", "CATIAxle", "CAAIPoint", "CAACreateLineCmd", "CATIndication", "CATICamera", "CATIndicationAgent"]
source_file: "Doc\online\CAADegTechArticles\CAADegGraph.htm"
converted: "2026-05-11T17:33:49.838586"
---

3D PLM Enterprise Architecture |  User Interface - Commands |  Implementing the Command Statechart Diagram _From the statechart diagram to the BuildGraph method_  
---|---|---  
Technical Article  
  
* * *

Abstract This article shows how to code the command class `BuildGraph` method that contains the command statechart implementation. 
    * **Implementing the Statechart Diagram**
    * **Creating States**
      * Creating Simple States
      * Creating Composite States
      * Deleting States
    * **Creating Dialog Agents**
      * Managing Indication
      * Managing Selection
      * Creating an Acquisition Filter to an Indication or a Path Element Dialog Agent
      * Setting a Dialog Agent as Repeatable
      * Modifying a Dialog Agent's Behavior
      * Plugging a Dialog Agent to a State
      * Concatenating Several Dialog Agents
      * Using a Dialog Agent in a Condition or Action Method
    * **Creating Transitions**
      * Creating Simple Transitions
      * Creating Transitions with the Same Source State
      * Creating Transitions with the Same Target State
      * Creating Self-Transitions
    * **Creating Guard Conditions**
      * Creating Conditions with Unconstrained Data Input
      * Creating Conditions Constraining Data Input
      * Creating Composite Conditions
      * Creating a State Exit Condition
    * **Creating Actions**
      * Creating an Action and Adding it to a Transition
      * Creating Composite Actions
      * Creating State Entry/Exit Actions
      * Storing the Created Object in the CSO
    * **Troubleshooting**
    * **In Short**
    * **References**  
---  
  
* * *

Implementing the Statechart Diagram The statechart diagram is implemented using the `BuildGraph` method. States, transitions, guard conditions, actions, and dialog agents are created in this method, and states, guard conditions and action methods are declared as transition parameters, or as state parameters.
    
    void CAACommandCmd::BuildGraph()
    {
      // Create states
      // Create dialog agents, set their behaviors, and plug them to the states
      // Create transitions between states and declare your guard conditions and actions
    }  
  
---  
[Top] Creating States States are instances of the _CATDialogState_ class. Creating Simple States
    * The initial state, as a pseudo state, is never explicitly created. It automatically activates the first state of the statechart diagram to which it is linked with a triggerless transition. This first state is created thanks to the `GetInitialState` method of the _CATStateCommand_ class. 
          
          CATDialogState * stFirstState = GetInitialState("stFirstStateId");   
  
---  
    * Additional states are created using the `AddDialogState` of the _CATStateCommand_ class. 
          
          CATDialogState * stSecondState = AddDialogState("stSecondStateId");  
  
---  
    * The final state, as a pseudo state, is also never explicitly created. It is reffered to as the `NULL` state in the `AddTransition` method that creates the transition to complete the state dialog command. 
          
          CATDialogTransition * pLastTransition = AddTransition(stEndState, **NULL** , ...  
  
---  
    * The Cancel state is a flavor of the final state. Like the final state, it ends the command, but in addition, it requests the [command undo](CAADegUndoRedo.htm) when the command completes. It is created using the `GetCancelState` method. 
          
          CATDialogState * stCancelState = GetCancelState();  
  
---  
The parameter passed as the argument of the methods `GetInitialState` and `AddDialogState` is the state identifier. This identifier is used in the state dialog command resource file to declare prompts to display when the state is the active one. [Top] Creating Composite States Composite states are created like simple states. 
    * Non-concurrent composite states are in fact made of a series of subsequent simple states
    * Concurrent composite states are modeled as simple states with dialog agents matching composite input.
[Top] Deleting States The states created using the `GetInitiaState`, `AddDialogState`, and `GetCancelState` methods of the _CATStateCommand_ class are automatically deleted. Never explicitly delete them. On the opposite, the states created using the _CATDialogState_ constructor must be explicitly deleted in your state dialog command destructor. [Top] Creating Dialog Agents A _dialog agent_ translates a user interaction into a user input. It is created to match a given end user interaction and is valued when the end user performs this interaction. It is associated with one or possibly several states, and its valuation is always required to check the conditions of the transition from this or these states. From the state machine viewpoint, the event that triggers the transition and enters the guard condition check process is the dialog agent valuation. An end user interaction is always defined, for the dialog agent, using a notification whose type reflects the interaction, and a notifier, that is, the object that sends the notification. Basically, the dialog agent is valued when both notification and notifier match the dialog agent's required ones. For specific dialog agents, the notification should also be decoded, for example to find what is under the mouse, and the decoding result should be checked before the dialog agent is valued. The end user interactions with which a state dialog command can be interested are made either by the following notifiers: a 2D or a 3D viewer, or a dialog box. The corresponding notifications are those of the viewer protocol [1], or those that the dialog box can send, depending on which controls it is made of. Specific interactions are indication (left click in the viewer background), selection (left click on an object representation), and dialog box input. They are retrieved thanks to specific dialog agents named acquisition agents. An acquisition agent is a specific dialog agent dedicated to get something "under the mouse" in addition to the notification. Acquisition agents are valued as dialog agents, but in addition, what is under the mouse must match what's expected by the acquisition agent. Acquisition agents fall into the following categories: 
    * Indication agent: dedicated to indication, that is to retrieve a 2D point from a left click
    * Path element agent: dedicated to selection, that is to retrieve the path element of the object under the mouse.
Any dialog agent has a behavior that you can customize. For example, you can activate it or not, or enable it for undo or not. You can also apply a filter or a combination of filters to a dialog agent, or concatenate several dialog agents to refine the condition that triggers the transition. In addition, other interactions such as double click on an object representation, right click, move with the left button pressed, can also be retrieved by customizing the dialog agent behavior. Note that: 
    * Dialog agents should be created as data members of the state dialog command class
    * They are created in the `BuildGraph` method, along with the state(s) they are dedicated to, and the transition(s) in which they are used
    * Their destruction must be requested in the command destructor using the `RequestDelayedDestruction` method.
[Top] Managing Indication Indication retrieves the coordinates of a 2D point that doesn't exist in the document, but that is indicated by an end user left click in a 2D or a 3D viewer. An indication agent is an instance of the CATIndicationAgent class. Creating an Indication Agent An indication agent is instantiated as follows.
    
    _daIndicationAgent = new CATIndicationAgent("2DIndicationAgentId");  
  
---  
Enabling a 3D Point Indication on a 2D Screen An indication agent that is dedicated to a command running with a 2D viewer directly retrieves the 2D point coordinates from the screen plane, expressed with respect to the document absolute axis system. With a 3D viewer, the click on the screen is undetermined. If you do not provide a projection plane, the default is a plane parallel to the screen. You can supply a plane, attached to the dialog agent, on which the point clicked on the screen plane will be projected according to the sight direction of the current viewpoint. ![3DIndicationAgent.gif \(7508 bytes\)](images/3DIndicationAgent.gif) Pay attention to this plane: it should not be perpendicular to the near or far planes, that is to the screen plane, in order to get a point. To create a plane, create the plane axis system origin, and the two plane axes, then set the origin and the axes as those of the plane, and set the plane as the indication agent plane using the `SetMathPlane` method.
    
    CATMathPoint origin(0,0,0);  // Create projection plane origin and axes
    CATMathDirection u(1,0,0);
    CATMathDirection v(0,1,0);
    
    CATMathPlane Plane;
    Plane.SetOrigin(origin);     // Set them to the projection plane
    Plane.SetDirections(u, v);
    
    _daIndicationAgent->**SetMathPlane**(Plane); // Assigns the plane to the dialog agent  
  
---  
If you want to make sure that the plane is not perpendicular to the screen plane, you can, for example, check that the vector normal to the plane is not perpendicular to the sight direction of the viewpoint. This can be done as follows.
    
    ...
    CATCATBoolean isPlaneNormal = FALSE;
    
    CATFrmLayout * pCurrentLayout = CATFrmLayout::GetCurrentLayout();
    if ( NULL != pCurrentLayout )
    {
      CATFrmWindow * pCurrentWindow = pCurrentLayout->GetCurrentWindow();
      if ( NULL != pCurrentWindow )
      {
        CATICamera * piICamera = NULL;
        piICamera = pCurrentWindow->GetCurrentCamera();
        
        if (NULL != piICamera) 
        {
          CATI3DCamera * pi3DCamera = NULL;
          HRESULT rc = piICamera->QueryInterface(IID_CATI3DCamera,(void **)& pi3DCamera);
    
          if ( SUCCEEDED(rc) )
          {
            CATMathVector Normal;
            Plane.GetNormal(Normal);
            CATMathDirection Sight = pi3DCamera->GetDirection();
            isPlaneNormal = Sight.IsNormal(Normal);
    
            pi3DCamera->Release(); 
            pi3DCamera=NULL;
          }
          piICamera->Release();
          piICamera= NULL ;
        }
      }
    }
    if (FALSE == isPlaneNormal) ...  
  
---  
Enabling for Multi-indication You may allow the end user to indicate a set of points instead of one. This is done by setting the behavior of the indication dialog agent to `CATDlgEngMultiAcquisition` by means of the `SetBehavior` method:
    
    _daMultiIndicationAgent = new CATIndicationAgent("MultipleAgentId");
    _daMultiIndicationAgent->SetBehavior(CATDlgEngMultiAcquisition);  
  
---  
Retrieving the Indicated Point The point indicated by the end user is retrieved directly as a _CATMathPoint2D_ instance in case of a 2D viewer, and should be transformed as a _CATMathPoint_ with a 3D viewer. 
    * With a 2D viewer 
          
          ...
          CATMathPoint2D IndPoint = _daIndicationAgent->GetValue();
          
          double X = IndPoint.GetX();
          double Y = IndPoint.GetY();
          // OR
          double X, Y;
          IndPoint.GetCoord(X, Y);
          ...  
  
---  
    * With a 3D viewer 
          
          ...
          CATMathPoint2D IndPoint2D = _daIndicationAgent->GetValue();
          CATMathPoint IndPoint3D;
          Plane.EvalPoint(IndPoint2D.GetX(),IndPoint2D.GetY(), IndPoint3D);
          
          double X = IndPoint3D.GetX();
          double Y = IndPoint3D.GetY();
          double Z = IndPoint3D.GetZ();
          // OR
          double, X, Y, Z;
          IndPoint3D.GetCoord(X, Y, Z);
          ...  
  
---  
If you do not have define an explicit plane, you retrieve the default plane, with the `GetMathPlane` method.
    
    ...
    CATMathPlane Plane = _daIndicationAgent->**GetMathPlane**();
    Plane.EvalPoint(IndPoint2D.GetX(),IndPoint2D.GetY(), IndPoint3D);
    ...  
  
---  
[Top] Managing Selection Selection enables the object-action paradigm, as well as the action-object paradigm: **Object-action** : The Select command and the commands that can take their input from the CSO enable the object-action paradigm. Using the Select command, the end user can select an object, that is, make this object active, and then click a command to work on this object. The command takes this object as input. ![Selection1.jpg \(44094 bytes\)](images/Selection1.jpg) | Using the Select command, provided as an arrow button in the user interface and shown here as the current command with its focused icon, the end user selects the top face of the pad. This face is put into the CSO, and its contour is highlighted. No predicate is done about what could be the next current command.    
---|---  
![Selection2.jpg \(53162 bytes\)](images/Selection2.jpg) | The end user clicks the Thickness command. The selected face is taken as input to be the face to thicken. If the clicked command cannot take a face as input, the selected face is ignored by the command, and is deselected, that is  removed from the CSO.  
**Action-object** : Each command that requires an end user input enables the action-object paradigm. The command can be selected first, and if no object is active, or if no active object matches the expected one(s), the active objects are deselected and the command waits for the end user to select an appropriate object, and takes this object as input. ![Selection3.jpg \(52480 bytes\)](images/Selection3.jpg) | The thickness command is clicked, but no face is selected. The command includes a selection step that lets the end user select the face to thicken.  
---|---  
![Selection4.jpg \(53021 bytes\)](images/Selection4.jpg) | The end user selects a face, and the command applies to this face.  
To detect that the end user has selected a representation in a viewer that stands for an object that matches what your state dialog command expects in the current state, and to retrieve this object, use an instance of the _CATPathElementAgent_ class. The path element dialog agent is a generic dialog agent that interprets a user selection, that is a left click on an object's representation in a viewer, as a document's object input, such as the selection of the rear left wheel instance of a car, and of all the objects above it in the document specification tree structure. It retrieves a path element, instance of the _CATPathElement_ class, that is an object that contains an ordered list of pointers starting from the root object of the active document to the selected object. Using the path element; you can navigate to find objects that are above the selected one in the document specification tree structure. [Top] Creating a CATPathElement Instance You can create an instance of a _CATPathElement_ class by simply providing its identifier, as follows:
    
    _SelectionAgent = new CATPathElementAgent("MySelectionAgentId");  
  
---  
If you do nothing else, your path element dialog agent will be valued with any object selected. [Top] Enabling for Selection You can decide which feedback to give to the end user when the object is selected, take your input from the CSO if the object your command expects is already selected, define the object(s) the command expects, and retrieve the selected object, or the path element that contains it. 
    * **Enabling a given object to be selected (Type Query)** : To value your path element dialog agent when the end user selects a given type of object, use the `AddElementType` method to set an interface this object implements. The following example shows how to value a path element dialog agent when the end user selects objects implementing the _CAAIPoint_ interface. 
          
          _daSelectionAgent->AddElementType(CAAIPoint::ClassId());  
  
---  
When a dialog agent is intended for such objects implementing the _CAAIPoint_ interface, it automatically sets the  cursor as ![NoEntry.gif \(864 bytes\)](images/NoEntry.gif) when the end user moves or locates the mouse above the representation of an object that doesn't implement this interface. The `AddElementType` method can be used as many times as you want the dialog agent to be valued with  objects implementing different interfaces. For example, if you want to value it with points or with lines, write:
          
          _daSelectionAgent->AddElementType(CAAIPoint::ClassId());
          _daSelectionAgent->AddElementType(CAAILine::ClassId());  
  
---  
The order in which the interfaces are declared using the `AddElementType` method is not taken into account. You can also set an ordered list of the interfaces among which the object selected should match at least one, and use the `SetOrderedTypeList` method to pass this ordered list to the dialog agent. Interface support is then sequentially checked using the list order.
          
          CATListOfCATString Types;
          Types.Append(CAAIPoint::ClassId());
          Types.Append(CAAILine::ClassId());
          _daSelectionAgent->SetOrderedTypeList(Types);  
  
---  
In this case, the _CAAIPoint_ is queried first against the selected object, and if the query fails, then the _CAAILine_ interface is queried.
    * **Input from the CSO** : You can ask a path element dialog agent to retrieve its input from the CSO if it contains appropriate elements. This is done by defining it as a CSO client with the `AddCSOClient` method: 
          
          AddCSOClient(_daSelectionAgent);  
  
---  
The valuation of all the dialog agents set as CSO clients is done when the command starts, whatever the state to which the dialog agent is plugged. When this is done, the CSO is emptied. If at least one object in the CSO is not expected by a dialog agent, none of them is valued, and the CSO is emptied.
    * **Feedback** : You can ask a path element dialog agent to highlight the object it is valued with by calling the `SetBehavior` method in the `BuildGraph` method with the appropriate parameter. 
          
          _daSelectionAgent->SetBehavior(CATDlgEngWithPSOHSO);  
  
---  
This puts the object in the PSO and in the HSO. You can use `CATDlgEngWithPSO` or `CATDlgEngWithHSO` to put the object in the PSO or in the HSO respectively. The default is `CATDlgEngWithoutSO` that does not highlight the object. Nothing happens if the selected object does not match the requested type.
[Top] Enabling for Multiselection You may allow the end user to select a set of elements instead of one. Multiselection is possible using a trap, or using the Search command, either run from the Edit menu or from the Power Input field. To enable a path element dialog agent for multiselection, set its behavior to `CATDlgEngMultiAcquisition` by means of the `SetBehavior` method:
    
    _daMultiSelectionAgent = new CATPathElementAgent("MultipleAgentId");
    _daMultiSelectionAgent->SetBehavior(CATDlgEngMultiAcquisition);  
  
---  
[Top] Creating an Acquisition Filter to an Indication or a Path Element Dialog Agent To filter the possible values of an indication or a path element dialog agent, you can create an acquisition filter. It encapsulates a constraint you set on the selected object to value the dialog agent. Typical constraints include: 
    * Topological constraints, such as check if a point belongs to a given plane
    * Interval constraints, such as check if a number is between 0 and 100
    * Lexical constraints, such as check if a date is a "MM/DD/YY" string.
When a dialog agent has such a filter, it applies the filter to check if the end user input is valid. It automatically sets the  cursor as ![NoEntry.gif \(864 bytes\)](images/NoEntry.gif) when the end user moves or locates the mouse above the representation of an object that doesn't match the filter.  Use acquisition filters to provide single-data constraints, such as `0<=N<=100`, and conditions to provide multiple-data constraints, such as `[point1<>point2 ?]`. Using filters simplifies conditions (all single-data constraints are provided as filters) and improves performance (conditions are checked only when each data has been checked). Use a condition method or a filter can seem equivalent, but there is a point to consider. Suppose your dialog agent has the pre-highlight behavior. With the condition method the wrong selected element will be first pre-highlighted and then the condition method will reject it. To re-pre-select an other element a re-initialization will be done, but the wrong element will be always pre-highlighted. With the filter the element will be pre-highlighted only if it is really selectable.  A filter can be created using the `Filter` method of the _CATStateCommand_ class:
    
    CATAcquisitionFilter * CATStateCommand::Filter
                            (FilterMethod iMethod, void * data);  
  
---  
Adding an acquisition filter to an acquisition agent is done by means of the `SetFilter` method:
    
    void CATAcquisitionAgent::SetFilter(CATAcquisitionFilter * iFilter)  
  
---  
Composite filters can be built by combining filters using the `AndFilter`, `OrFilter` and `NotFilter` methods.
    
    CATAcquisitionFilter * CATDialogAgent::AndFilter(CATAcquisitionFilter * iFilter1,
                                                     CATAcquisitionFilter * iFilter2)
    
    CATAcquisitionFilter * CATDialogAgent::OrFilter (CATAcquisitionFilter * iFilter1,
                                                     CATAcquisitionFilter * iFilter2)
    
    CATAcquisitionFilter * CATDialogAgent::NotFilter(CATAcquisitionFilter * iFilter)  
  
---  
Filters created using these methods are automatically deleted, and thus should not be explicitly deleted in the destructor  For example, assume you want to trigger a transition as soon as the end user selects a point in a 2D viewer. This is easy if all the points implement a point type interface, such as _CATI2DPoint_. In this case, you should create a single dialog agent, as follows:
    
    _PointAgent = new CATPathElementAgent("PointAgent");
    _PointAgent->AddElementType(IID_CATI2DPoint);
    SourceState->AddDialogAgent(_PointAgent);
    ...
    AddTransition(SourceState, TargetState, IsOutputSetCondition(_PointAgent), ...);  
  
---  
But assume in addition that some other points, such as spline control points, exist in the document, and that these control points implement their own interface _CATI2DControlPoint_ in addition to _CATI2DPoint_. To filter control point selection, you can create a filter to apply to the previous dialog agent. This dialog agent will be valued only with points and not with control points.  To set this filter to the dialog agent, first instantiate the filter thanks to the `Filter` method,**** and use the ` SetFilter` method. New statements are shown in bold:
    
    _PointAgent = new CATPathElementAgent("PointAgent");
    _PointAgent->AddElementType(IID_CATI2DPoint);
    
    **CATAcquisitionFilter * pFilterForPointCtrl = Filter((FilterMethod) & MyCmd::TestCtrlPoint,(void*)NULL);
    										   ****_PointAgent- >SetFilter(pFilterForPointCtrl);
    **
    SourceState->AddDialogAgent(_PointAgent);
    ...
    AddTransition(SourceState, TargetState, IsOutputSetCondition(_PointAgent), ...);  
  
---  
`TestCtrlPoint` is a Filter method of the _MyCmd_ state command. 
    
    CATBoolean MyCmd::TestCtrlPoint ( CATDialogAgent * iAgent, void * iUsefulData)
    {
      CATBoolean ret = FALSE;
      if ( NULL != iAgent )
      {
         CATBaseUnknown * pSelectedElt= ((CATPathElementAgent *)iAgent)->GetElementValue();
         if ( NULL != pSelectedElt )
         {
            CATI2DControlPoint * pI2DControlPoint = NULL;
            HRESULT rc = pSelectedElt->QueryInterface(IID_CATI2DControlPoint,
                                           (void **) & pI2DControlPoint );
            if SUCCEEDED(rc)
            {
               ret = TRUE;
               pI2DControlPoint ->Release();
               pI2DControlPoint = NULL ;
            }
          }
        }
      }
      return ret;
    }  
  
---  
To retrieve the value to check, you can use the `GetValue` , `GetListOfValues` and `GetElementValue` methods of the _CATPathElementAgent_ class. Attention, the `GetElementValue` method does not Addref the returned value.  [Top] Setting a Dialog Agent as Repeatable A dialog agent set as repeatable is useful for states with self-transitions, that is transitions that loops on the same state, when: 
    * You request from the end user an array input: in this case, the dialog agent should be valued to trigger the transition
    * You want to hook a rubber band at the mouse cursor: in this case, the dialog agent should be just prevalued to trigger the transition.
You can set a dialog agent set as repeatable using the behavior parameter `CATDlgEngRepeat`. [Top] Modifying a Dialog Agent's Behavior All dialog agents share a common behavior made of: 
    1. The behavior mode
    2. The notifier set
    3. The notification pattern.
It defines when a dialog agent accepts a notification and how it behaves afterwards. [Top] Behavior Mode It can set either using the optional second parameter of the dialog agent constructor, or by calling the `SetBehavior` method:
    
    void CATDialogAgent::SetBehavior(CATDlgEngBehavior iBehavior);  
  
---  
The behavior mode is made of behavioral facets that can be each set to a given value. These behavioral facets can apply to all dialog agents, or to acquisition dialog agents only. The behavior mode is described as a concatenation of the following parameters described below (defaults appear in bold) Dialog Agents | Behavioral Facet | Behavior Parameters | Description  
---|---|---|---  
Any dialog agent | Activating | **CATDlgEngActive** | Is notified about user interactions  
CATDlgEngInactive | Isn't notified about user interactions  
Repeating | **CATDlgEngOneShot** | Doesn't remain active after it is valued  
CATDlgEngRepeat | Remains active and reusable after it is valued  
Receiving notifications | **CATDlgEngReceiveAllNotifications** | Receives all the notifications received by the command it belongs to  
CATDlgEngReceiveFromLinkedViews | Receives only notifications sent by objects of which it is the father  
Visualizing | **CATDlgEngWithoutVisualization** | Has no particular visualization attribute  
CATDlgEngWithVisualization | Is put into the ISO when it is activated  
CATDlgEngWithXORVisualization | Is put into the furtive ISO when it is activated  
Undoing | **CATDlgEngWithUndoStep** | Agent's valuation can be undone, and an undo step is registered  
CATDlgEngWithUndo | Agent's valuation can be undone, but no undo step is registered  
CATDlgEngWithoutUndo | Agent's valuation can't be undone  
Any state command | Repeating | **CATDlgEngOneShot** | Stops when it reaches the NULL state  
CATDlgEngRepeat | Resumes when it reaches the NULL state  
Undoing | **CATDlgEngWithAutoUndo** | Can have Undo steps depending on its agents' behaviors  
CATDlgEngWithoutAutoUndo | Can't have Undo steps  
Undoing | CATDlgEngWithoutUndoStart | No Undo step is automatically added at the beginning of the command  
Undoing | CATDlgEngNoTransaction | The Undo/Redo stack is emptied and remains empty as long as the command is active  
Initializing | **CATDlgEngWithAgentInitialization** | Reinitializes its agents if it resumes after reaching the NULL state of after Undo or Redo  
CATDlgEngWithoutAgentInitialization | Does not reinitialize its agents  
Activating agents | **CATDlgEngAgentActivationWhenEnteringState** | Activates its agents each time a state they belong to is entered  
CATDlgEngAgentActivationWhenChangingState | Activates its agents only if the state has changed  
Acquisition dialog agent | Prevaluating | **CATDlgEngIgnoreOnPrevaluate** | Requests that the transition triggers when an object is selected only  
CATDlgEngAcceptOnPrevaluate | Requests that the transition triggers as soon as an object is located under the mouse without being selected  
Valuating from CSO | **CATDlgEngNotValuedFromCSO** | Is not valued from the CSO  
CATDlgEngValuedFromCSO | Is valued from the CSO at the beginning of the command  
Valuating | **CATDlgEngSimpleValuation** | Values the agent with object selection, that is, mouse left button simple click on an object (CATActivate notification)  
CATDlgEngWithPrevaluation | Values the agent with object preselection, that is, object under the mouse without being selected, in addition to object selection (CATActivate, CATPreactivate, CATMove, and CATEndPreactivate notifications)  
CATDlgEngWithManipulation | Values the agent with object manipulation, that is, object selected and dragged (CATBeginManipulate, CATManipulate, CATEndManipulate notifications)  
CATDlgEngWithEdit | Values the agent with object edition, that is, mouse left button double click on an object (CATEdit notification)  
CATDlgEngWithContext | Values the agent with a mouse right click, on an object (CATContext and CATEndContext notifications)  
CATDlgEngWithDrag | Manages notifications during Drag and Drop  
Highlighting | **CATDlgEngWithoutSO** | Doesn't highlight neither the object under the mouse nor the selected object  
CATDlgEngWithPSOHSO | Highlights both the object under the mouse and the selected object. Requests that valuing be CATDlgEngWithPrevaluation  
CATDlgEngWithPSO | Highlights the object under the mouse. Requests that valuing be CATDlgEngWithPrevaluation  
CATDlgEngWithHSO | Highlights the selected object  
Highlighting | **CATDlgEngOldHSOManager** | Selected element remains highlighted until the end of the command  
CATDlgEngNewHSOManager | Selected elements do not remain highlighted when the agent is removed  
Multi-selecting | **CATDlgEngMonoAcquisition** | Accepts one object indication or selection only  
CATDlgEngMultiAcquisition | Accepts indication or multi-selection. Multi-selection is possible using a trap, or using the Search command, either run from the Edit menu or from the Power Input field   
CATDlgEngMultiAcquisitionSelModes | Accepts indication or multi-selection, with the help of an user interface. Triggered as soon as a selection is performed. Multi-selection is possible using a trap, or using the Search command, either run from the Edit menu or from the Power Input field   
CATDlgEngMultiAcquisitionCtrl | Accepts indication or multi-selection, with the help of an user interface. Triggered as soon as the user validates the selection. Multi-selection is possible using a trap, or using the Search command, either run from the Edit menu or from the Power Input field   
CATDlgEngMultiAcquisitionUserCtrl | Accepts indication or multi-selection, with the help of a user interface. Triggered as soon as a selection is performed unless the end user decides to toggle the multi-acquisition control mode.   Multi-selection is possible using a trap, or using the Search command, either run from the Edit menu or from the Power Input field   
"through" selecting | **CATDlgEngWithoutDeepSel** | One selection only. Accepts no "through" selection, only the element "in front"  
CATDlgEngWithDeepSel | Multi-selection. Accepts "through" selection  
CATDlgEngWithDeepFirstSel | One selection only. Accepts "through" selection  
leaf selecting | CATDlgEngNoSubPath | Accepts leaf selections only  
Agent set | Dispatching | **CATDlgEngDispatchUntilAccept** | Dispatches notifications to the agents until one accepts it  
CATDlgEngDispatchToAllAgents | Dispatches notifications to all the agents  
The behavior mode is a concatenation of the behavior parameters using the | character. For example, you can change the default behavior mode of a dialog agent for repeatability and undo as follows:
    
    MyDialogAgent->SetBehavior(CATDlgEngRepeat | CATDlgEngWithUndo);  
  
---  
The behavior mode is a concatenation of the behavior parameters using the | character. For example, you can change the default behavior mode of a dialog agent for repeatability and undo as follows:
    
    MyDialogAgent->SetBehavior(CATDlgEngRepeat | CATDlgEngWithUndo);  
  
---  
[Top] Notifier Set When a dialog agent is created, its _notifier set_ is the set of all the notifiers, that is, all viewers and dialog boxes that can send notifications conveyed to the dialog agent through the command thanks to the Send/receive communication protocol. But you can define explicitly the notifier set by calling the `AddNotifier` method, as many times as required.
    
    void CATDialogAgent::AddNotifier(CATCommand * iNotifier);  
  
---  
    * The first call actually empties the notifier set and fills it with the notifier passed as parameter
    * Each following call adds the notifier passed as a parameter to the notifier set.
Use the `RemoveNotifier` method to remove a given notifier from the notifier set. [Top] Notification Pattern The _notification pattern_ describes when the dialog agent accepts the user intent. It's a set of {Accept if n comes from N} rules, where n is a notification and N a notifier. These rules are defined by calling the `AcceptOnNotify` method.
    
    void CATDialogAgent::AcceptOnNotify
            (CATCommand * iNotifier, CATCommand * iNotification);  
  
---  
    * Set `iNotifier` to `NULL` if the notification is notifier (viewer or dialog box) independent
    * Set `iNotification` to `NULL` to receive all the sent notifications, whatever their kind.
Use the `IgnoreOnNotify` method to remove a rule from the notification pattern. [Top] Plugging a Dialog Agent to a State Once the dialog agent is created and well defined with the appropriate behavior, you can plug it to the dialog state you intend it for. This is done using the `AddDialogAgent` method of the _CATDialogState_ class.
    
    stStartState->AddDialogAgent(_daIndicationAgent);  
  
---  
A dialog agent is usually associated with one state only, but you can also associate it with several states if you recycle it between two usages. Refer to Recycling a Dialog Agent. If you use it several times for the same state in a self-transition, you can set it as repeatable. Refer to Setting a Dialog Agent as Repeatable. On the other hand, several dialog agents can be associated with a single state. Refer to Concatenating Several Dialog Agents. [Top] Concatenating Several Dialog Agents You can concatenate several dialog agents plugged to the same state to filter the end user input. To understand how you can use dialog agent concatenation, remember that if several dialog agents are plugged to the same state: 
    * The end user interaction values only one of them before the transition is triggered
    * The dialog agents are scanned for setting their values in the order they are declared to the state using the `AddDialogAgent` method.
For example, assume you want to trigger a transition as soon as the end user right clicks. This is easy to do using a dialog agent valued with a `CATContext` notification sent by the right click.
    
    _daAgent = new CATDialogAgent("RightClickAgentId");
    _daAgent->AcceptOnNotify(NULL, "CATContext");
    SourceState->AddDialogAgent(_daAgent);
    ...
    AddTransition(SourceState, TargetState, IsOutputSetCondition(_daAgent), ...);  
  
---  
But if you want that the transition is triggered only when the end user right clicks in the background, you can concatenate two dialog agents. The first one declared, a _CATPathElementAgent_ instance, captures all right clicks on any object. To do this, set its behavior to `CATDlgEngWithContext`. The second one, as above, is valued with right clicks, but since it is plugged to the state as the second one, the right clicks on objects will not value it. Only the second dialog agent fires the transition.
    
    _peAgent = new CATPathElementAgent("RightClickOnObjectId");
    _peAgent->SetBehavior(CATDlgEngWithContext|CATDlgEngRepeat);
    _daAgent = new CATDialogAgent("RightClick");
    _daAgent->AcceptOnNotify(NULL, "CATContext");
    SourceState->AddDialogAgent(_peAgent);
    SourceState->AddDialogAgent(_daAgent);
    ...
    AddTransition(SourceState, TargetState, IsOutputSetCondition(_daAgent), ...);  
  
---  
[Top] Using a Dialog Agent in a Condition or Action Method You can use a dialog agent in a condition or action method to: 
    * Retrieve the selected object
    * Retrieve the selected path element
    * Retrieved the multiselected path elements
    * Retrieve the end user interaction
    * Recycle the dialog agent to use it again as a brand new one.
Retrieving the Selected Object To retrieve the object selected, use the `GetElementValue` method, as follows:
    
    CATBaseUnknown * SelectedObject = _SelectionAgent->GetElementValue();  
  
---  
This is generally done in the appropriate action method, or possibly in a condition method. Retrieving the Selected Path Element You may want also to retrieve the path element which contains the selected object by using the `GetValue` method.
    
    CATPathElement * SelectedPath = _SelectionAgent->GetValue();  
  
---  
    * If you have not specified any interface or class, the returned path element contains all the elements from the root element to the selected element. For example, if the user selects the rear left wheel, the returned path is: Car/RearAxle/RearLeftWheel
    * Otherwise, with a type query, if the selected element is a child of the required element, the returned model path is a subpath, that is a path that begins with the root element and truncated with the first element matching the interface or class name specified using the `AddElementType` method. For example, if a CATIAxle is required and the user selects the rear left wheel, the returned subpath is: Car/RearAxle
[Top] Retrieving the Multiselected Path Elements You may want also to retrieve the path elements which contains the multiselected objects by using the `GetListOfValue`s method, as a pointer to a CATSO instance that contains the list of path elements.
    
    CATSO * SelectedPaths = _SelectionAgent->GetListOfValues();  
  
---  
With a type query, the returned path list contains only the matching object paths. Each object path may be truncated if the selected object is a child of the required one. For example, if a CATIAxle is required and the user selects the rear left wheel and the front axle, the returned list is: 
    * Car/RearAxle (subpath for the rear left wheel).
    * Car/FrontAxle (path for the front axle).
[Top] Retrieving whether a Dialog Agent Is Valued You can query a dialog agent to know whether it is valued by calling the `IsOutputSet` method.
    
    CATBoolean CATDialogAgent::IsOutputSet()  
  
---  
[Top] Recycling a Dialog Agent Recycling allows a dialog agent to be reused once it has been input. This feature is useful in the following situations: 
    * **Array input** : One acquisition variable is enough to input an array: a self-transition is used to store each data input in an array's element before recycling by means of the `InitializeAcquisition` method. For example, for a _CATIndicationAgent_ : 
          
          CATMathPoint2D point2D = _daIndication->GetValue();
          ...
          _daIndication->InitializeAcquisition();  
  
---  
If the dialog agent is recycled using the `InitializeAcquisition` method, you can use it again as if it were never used, that is, using the `IsOutputSetCondition` method. Another way of providing array input with a single dialog agent is to set it as repeatable using the `CATDlgEngRepeat` behavior parameter, and to use the `IsLastModifiedAgentCondition` method instead of the `IsOutputSetCondition` method.
    * **Multiple use** : This situation arises when there are multiple occurrences of the same data type in a dialog. We may design a LineBuilder which benefits from recycling. Any state that use the same dialog agent must recycle it, usually in one of their action methods, using the `InitializeAcquisition` method.
[Top] Creating Transitions A transition is a relationship between a _source state_ and a _target state_. The transition's source state being the active state, the transition is triggered when an event activates it. The guard condition is evaluated, and if it evaluates to TRUE, the transition fires. This executes the action associated with the transition and the transition's target state becomes the active state. You can create simple transitions, transitions with the same source state, transitions with the same target state and self-transitions. Transitions are created using the `AddTransition` method of the _CATStateCommand_ class. [Top] Creating Simple Transitions A simple transition that connects `SourceState` to `TargetState` is created using the `AddTransition` method as follows:
    
    AddTransition(SourceState, TargetState, ...);  
  
---  
`AddTransition` has other arguments used to associate the transition with the guard condition evaluated when the transition is triggered, and actions to perform when the transition fires. See Creating Guard Conditions and Creating Actions respectively. [Top] Creating Transitions with the Same Source State Several transitions may originate from the same source state. When creating such transitions, the transition creation order is important if they, or some of them, share the same condition. To prevent from condition overlapping, which could lead to freeze the flow of control, the transition creation order is taken into account. As soon as one of the dialog agents assigned to the state is valued, the first transition found in the transition creation order whose condition evaluates to True fires. On the opposite, if the guard condition evaluates to False, the transition doesn't fire, and the condition of the following transition is evaluated, and so on until a transition fires, or the last transition is reached. For example, a command that creates a polyline can declare two transitions originating from the same state with the same trigger: a point indication. The first transition creates a line of the polyline, the second draws a rubber band to visualize the line that could be created at the current mouse location.
    
    ...
    _daIndicationP = new CATIndicationAgent("IndicationPNId");
    _daIndicationP->SetBehavior(CATDlgEngAcceptOnPrevaluate | 
                                CATDlgEngWithPrevaluation);
    ...
    AddTransition(stRepeatState,
                  stRepeatState,
                  AndCondition(IsOutputSetCondition(_daIndicationP),
                     Condition((ConditionMethod) & CAACreatePolylineCmd::CheckPointByIndic)),
                  Action((ActionMethod) & CAACreatePolylineCmd::CreateLineByIndic,));
       
    AddTransition(stRepeatState,
                  stRepeatState,
                  IsLastModifiedAgentCondition(_daIndicationP),
                  Action((ActionMethod) & CAACreatePolylineCmd::RubberLine));
    ...  
  
---  
Both transitions share the same trigger, that is the CATIndication agent valuation or prevaluation, according to the dialog agent behavior. As soon as the dialog agent is valued or prevalued, that is if the end user left clicks or moves the mouse, the first transition is triggered. Its guard condition evaluates. As a composite condition, the first condition evaluates to TRUE if the dialog agent is valued, that is, if the end user has left clicked. If this is the case, and if the other condition evaluates to TRUE, the transition fires to create the line. Otherwise, the second transition is triggered, its guard condition evaluates, and if it evaluates to TRUE, the transition fires to update the rubber band. Note that the target states are also identical, making these transitions self-transitions. To enable for the dialog agent reuse, it must be recycled in both action methods. [Top] Creating Transition with the Same Target State Several transitions may target the same state. If in addition they share the same guard conditions and actions, you may end up with a bulky code like this if you create separate transitions:
    
    AddTransition(**state1** , target, IsOutputSetCondition(_daAgent),
                  Action(ActionMethod) &MyDialogCommand::action));
    AddTransition(**state2** , target, IsOutputSetCondition(_daAgent),
                  Action(ActionMethod) &MyDialogCommand::action));
    AddTransition(**state3** , target, IsOutputSetCondition(_daAgent),
                  Action(ActionMethod) &MyDialogCommand::action));  
  
---  
Using the `AddInitialState` method to define a transition avoids repeating the transition guard conditions and actions.
    
    CATDialogTransition * **JoinTransition** =
             AddTransition(**state1** , target,
                           IsOutputSetCondition(_daAgent)
                           Action(ActionMethod) &MyDialogCommand::action));
    **JoinTransition- >AddInitialState(state2);
    JoinTransition->AddInitialState(state3);**  
  
---  
[Top] Creating Self-Transitions A self-transition loops on the same state. This can be useful to enable the same kind of input several times, or to visualize using a rubber band the object that could be created with respect to the current mouse location. To create a self-transition, the `AddTransition` method should just set the same state as its source state and as its target state.
    
    AddTransition(stRepeatState, stRepeatState,
                  Condition(...),
                  Action(...));  
  
---  
To make it possible to get out of the loop, another transition from the same source state to another target state should exist. Self-transitions are also useful to visualize the object that could be created at the current mouse location if the end user requested to create it. Below are two examples. ![RubberBanding1.gif \(2520 bytes\)](images/RubberBanding1.gif) | The circle is not yet created. The circle center is already created, and the end user moves the mouse. A circle that corresponds to the current mouse location is drawn. It corresponds to the circle that would be created if the end user clicked the mouse at that location. This is made possible thanks to a self-transition looping on a state that expects the circle radius input by means of an indication.  
---|---  
![RubberBanding3.gif \(2868 bytes\)](images/RubberBanding3.gif) | The state dedicated to get the circle radius has an incoming transition that comes from a previous state that is not detailed here. As long as the end user moves the mouse, the viewer sends a preactivation notification that values a dialog agent and fires the self-transition whose action creates a temporary circle that corresponds to the current mouse location. As soon as the end user indicates a point, the transition that creates the circle fires, the circle is created and the final state is reached.  
The code to write to create the self-transition for the circle in the `BuildGraph` method is the following.
    
    _daIndicRadius = new CATIndicationAgent("GetRadiusPoint");
    _daIndicRadius->SetBehavior(CATDlgEngWithPrevaluation |
                                CATDlgEngAcceptOnPrevaluate |
                                CATDlgEngWithUndo);
    ...
    AddTransition(stGetRadius, stGetRadius,
                  IsLastModifiedAgentCondition(_daIndicRadius),
                  Action((ActionMethod) & CAACreateCircleCmd::UpdateCircle));  
  
---  
The indication dialog agent should feature a behavior that makes it react on preactivation notifications: 
    * `CATDlgEngWithPrevaluation` enables the dialog agent to be valued from such a notification
    * `CATDlgEngAcceptOnPrevaluate` triggers the transition when the dialog agent is prevalued with such a notification, the default being that a selection should occur to trigger a transition.
The transition is triggered as soon as the dialog agent is prevalued. Dialog agent prevaluation takes place when a preactivation notification is received. This is the case with an indication dialog agent as long as the mouse moves without clicking the left button. The `IsLastModifiedAgentCondition` method detects dialog agent prevaluation. Otherwise, using the `IsOutputSetCondition` method, the transition would be triggered only when the agent would be valued, that is once the end user would have clicked. The temporary circle displayed is not stored in the document, but added to the ISO (Interactive Set of Objects). It is created from a previous action, and updated according to the mouse move using the `UpdateCircle` method.
    
    CATBoolean CAACreateCircleCmd::UpdateCircle(void * iData)
    {
      //        Get current point  
      CATMathPoint2D point2D = _daIndicRadius->GetValue();
      CATMathPoint Mouse;
      _ProjPlane.EvalPoint(point2D.GetX(),point2D.GetY(),Mouse);
      //        Compute the radius 
      _Radius = (float) _CircleCenter.DistanceTo(Mouse);
      //        Modify the temporary circle
      _TemporaryCircle->SetRadius(_Radius);
      //        Update ISO
      _ISO->UpdateElement(_TemporaryCircle);
      //        Recycle the dialog agent
      _daIndicRadius->InitializeAcquisition();
    
      return TRUE;
    }  
  
---  
The `UpdateElement` method updates the ISO with the modified temporary circle, and the dialog agent is recycled before the method returns. The "Get Point" state becomes active again, and the dialog agent can be reused thanks to the  `InitializeAcquisition` method. Note that if the dialog agent were set as repeatable using the `CATDlgEngRepeat` behavior parameter, it would be useless to recycle it. Here is another case with a polyline example. ![RubberBanding2.gif \(2160 bytes\)](images/RubberBanding2.gif) | The polyline is being built. Five line segments are created, and the end user moves the mouse to create the sixth one. The dashed line segment visualizes what would be this line segment if the end user clicked at the current mouse location. This is made possible thanks two self-transitions looping on a state. The first transition expects a point indication to create a line segment, the second one expects a point indication prevaluation to create the rubber band.  
---|---  
![RubberBanding4.gif \(3988 bytes\)](images/RubberBanding4.gif) | The state dedicated to get a point of the polyline has an incoming transition that comes from a previous state that is not detailed here. As long as the end user moves the mouse, the viewer sends a preactivation notification that values a dialog agent and fires the self-transition whose action creates a temporary line that corresponds to the current mouse location. As soon as the end user indicates a point, another self-transition fires and the line segment is created. Due to the self-transition, the state remains active to enable another line segment creation. The final state is reached as soon as the end user right clicks.  
Creating Guard Conditions The guard condition is a CATBoolean expression that is evaluated as soon as the transition is triggered, and if it evaluates True, the transition fires and the associated action is executed. A guard condition is declared as the third parameter of the `AddTransition` method. A composite condition can be created by combining elementary conditions. In addition, an exit condition can be set onto the state. It is evaluated before the guard conditions, and if it evaluates False, the guard condition is not evaluated. [Top] Creating Conditions with Unconstrained Data Input An _unconstrained data input_ is either: 
    * A dataless input, that is an input without associated value
    * A data input without any constraint on the value provided by the end user.
To create such a condition, use the `IsOutputSetCondition` method to build a _CATStateCondition_ instance and provide the returned instance as the third argument of the `AddTransition` method:
    
    AddTransition(iSourceState, iTargetSstate,
    **IsOutputSetCondition(** _daAgent**)** , ...);  
  
---  
As soon as the dialog agent is valued, the condition is checked, and since there is no constraint on this value, the condition is evaluates True and the transition fires. The same agent can be reused in self-transitions if it is set as repeatable using the `CATDlgEngRepeat` behavior parameter, for example to trigger the transition when it is prevalued. In these cases, use the `IsLastModifiedAgentCondition` method instead of the `IsOutputSetCondition` method.
    
    AddTransition(iSourceState, iTargetSstate,
    **IsLastModifiedAgentCondition(** _daAgent**)** , ...);  
  
---  
[Top] Creating Conditions Constraining Data Input To constrain data input, you need to retrieve the input value and check it according to the constraints you want to apply to this data. You can do this either in a condition method, or using a condition class. Creating a condition class allows the condition to be reused in other commands. Another way of constraining data input is to create filters. Filters are set to dialog agents. When a dialog agent is assigned a filter, it is valued when the filter evaluates True. This means that the transition is not triggered as long as the filter evaluates False, and thus that the guard condition is not evaluated. This improves performance. In addition, the end user receives a feedback using the cursor featuring the no entry shape ![NoEntry.gif \(864 bytes\)](images/NoEntry.gif) when attempting to indicate or select an undesired object. Refer to Creating an Acquisition Filter to an Indication or a Path Element Dialog Agent for more information. Creating a Condition Method The easiest way to define a data constraint is to encapsulate it in a method of state dialog command. Such a condition method has a single argument and must return a CATBoolean.
    
    CATBoolean ConditionMethod(void * iUsefulData);  
  
---  
The argument can be passed as the second argument of the `Condition` method, or using the  `SetData` method
    
    AddTransition(...
                  **Condition**((ConditionMethod) &CAACreateLineCmd::CheckEndPoint,**CAAIPoint * PointToCheck)** ,
                  ...);
    // OR
    _MyCondition->**SetData(CAAIPoint * PointToCheck)** ;  
  
---  
For example, assume that a command creating a line in the 3D space needs to check that the end point input by the end user is not coincident with the start point. This can be checked in the `CheckEndPoint` method of the _CAACreateLineCmd_ class, standing for the Line command.
    
    CATBoolean CAACreateLineCmd::CheckEndPoint(void * iDummy)
    {
      CATBoolean ret = TRUE;
      CATMathPoint2D point2D = _daIndicationAgent->GetValue();
      CATMathPoint EndPoint;
      _ProjPlane.EvalPoint(point2D.GetX(),point2D.GetY(), EndPoint);
    
      if ( EndPoint.DistanceTo(StartPoint) < EPSILON ) 
      { 
        ret = FALSE;
        _daIndicationAgent->InitializeAcquisition();
      }
      return ret;
    }  
  
---  
The input point is retrieved from the indication dialog agent, and transformed as a 3D point. Refer to Managing Indication for more details about how to get a 3D point from an end user indication. Then the distance between the start and end points is compared to the tolerance that defines coincident points, and the method returns `TRUE` or `FALSE` according to the test result. Note that if points are found as coincident, the dialog indication agent is recycled using the `InitializeAcquisition` method. It can be reused in the transition source state that remains active to enable the end user to indicate another point, because the condition is not met and the method returned False. Then, the `CATStateCondition` instance is built from this method by means of the `Condition` method. This instance is then provided to the `AddTransition` method, concatened to the indication agent valuation check using the `AndCondition` method to create a composite condition:
    
    AddTransition(state2, NULL,
                  **AndCondition**(
                     IsOutputSetCondition(_daIndicationAgent**),**
                     **Condition((ConditionMethod) &CAACreateLineCmd::CheckEndPoint)**),
                  ...);  
  
---  
Creating a Condition Class When a condition is intended to be reusable, you can encapsulate it in a _CATStateCondition_ subclass. The condition test is implemented by overloading the `GetStatus` method. For example, the _NoCoincidence_ class is created to check that the two points input to the Line command do not coincide. The NoCoincidence class header file is:
    
    class **NoCoincidence** : public CATStateCondition
    {
      public:
        NoCoincidence(CATMathPoint StartPoint, CATIndicationAgent * daIndicationAgent);
        virtual ~NoCoincidence();
        virtual CATBoolean **GetStatus**();
      private:
        CATMathPoint         _StartPoint;
        CATIndicationAgent * _daIndicationAgent;
    }  
  
---  
Let's have a look at the _NoCoincidence_ constructor and `GetStatus` method.
    
    ...
    NoCoincidence::NoCoincidence(CATMathPoint         StartPoint,
                                 CATIndicationAgent * daIndicationAgent)
                 : _StartPoint(StartPoint), _daIndicationAgent(daIndicationAgent)
    {}
        
    CATBoolean NoCoincidence::**GetStatus**()
    {
      CATBoolean ret = TRUE;
      CATMathPoint2D point2D = _daIndicationAgent->GetValue();
      CATMathPoint EndPoint;
      _ProjPlane.EvalPoint(point2D.GetX(),point2D.GetY(), EndPoint);
    
      if ( EndPoint.DistanceTo(StartPoint) < EPSILON ) 
      { 
        ret = FALSE;
        _daIndicationAgent->InitializeAcquisition();
      }
      return ret;
    }  
  
---  
Notice that condition parameters are provided by means of the constructor. They are stored in private data members in order to be used by the `GetStatus` method that retrieves the end point as a 3D point from the indicated 2D point, checks the coincidence with the start point, and returns accordingly. To use this condition class in the `BuildGraph` method of your state dialog commands, you simply need to instantiate it, and pass the pointer to that class to the `Condition` method that will call the `GetStatus` method.
    
    ...
    **_CoincidenceCondition** = new NoCoincidence(_StartPoint,
                                              _daIndicationAgent);
    ...
    AddTransition(state2, NULL,
                  AndCondition(
                     IsOutputSetCondition(_daIndicationAgent),
                     **_CoincidenceCondition**)),
                  ...);
    ...  
  
---  
Note that `_CoincidenceCondition` must be a data member of your state dialog command class, and must be deleted in the destructor. [Top] Creating Composite Conditions When CATBoolean expressions, such as `[condition1 AND condition2?]`, are needed, you must write them as _composite conditions_. A composite condition is built by combining conditions using the AND, OR, and NOT operators supplied through the following methods:
    
    CATStateCondition * **AndCondition**(CATStateCondition * iCondition1,
                                     CATStateCondition * iCondition2);
    
    CATStateCondition * **OrCondition** (CATStateCondition * iCondition1,
                                     CATStateCondition * iCondition2);
    
    CATStateCondition * **NotCondition**(CATStateCondition * iCondition);  
  
---  
For example, when creating a line with two points, if you want to check that the end user has indicated a point, and that this point is not identical to the previously selected point, the condition could be expressed as follows: `[EndPoint input AND (StartPoint<>EndPoint)?]` This is implemented in this way:
    
    AddTransition(state2, NULL,
                  **AndCondition**(
                     IsOutputSetCondition(EndPoint), // condition1: EndPoint input?
                     Condition((ConditionMethod)     // condition2: StartPoint<> EndPoint?
                               &CAACreateLineCmd::CheckEndPoint)),
                  ...);  
  
---  
You can combine these methods to match your specific needs. [Top] Creating a State Exit Condition A state exit condition is assigned to the state, and is evaluated: 
    * When entering the state from a non self transition
    * Whenever a state dialog agent is valued
    * When entering the state from a self transition if the dialog agent were valued in the transition action
This evaluation is done prior to the guard conditions. If it evaluates False, the guard conditions are not evaluated, and the transition doesn't fire. To create a state exit condition, you can either instantiate classes you have derived from the _CATStateCondition_ class or use the `Condition` method, as described in Creating Conditions with Unconstrained Data Input and in Creating Conditions Constraining Data Input. You can also combine conditions to create a composite condition, as described in Creating Composite Conditions,  you'll assign to the state. Use the `SetLeaveCondition` method to assign the created condition to the state.
    
    _State->SetLeaveCondition(_ExitCondition);  
  
---  
[Top] Creating Actions The action associated with the transition is executed when the transition fires. This action can be represented by a method of the state dialog command class, or, if the action is intended to be reused by other commands, by a class derivinf from the _CATDiaAction_ class. An action is declared as the fourth parameter of the `AddTransition` method. A composite action can be created by combining elementary actions. A state can also feature enter and leave actions that are automatically executed when the state is respectively entered and left. [Top] Creating an Action and Adding It to a Transition You can create an action either using a method of the state dialog command or using a class. Creating an Action Method The easiest way to add an action to a transition is to implement it as a method of your state dialog command. Such an action method has a sigle argument and must return a CATBoolean.
    
    CATBoolean ActionMethod(void * iUsefulData);  
  
---  
The argument can be passed as the fourth argument of the `Action` method, or using the  `SetData` method. The second and third arguments are dedicated to undo/redo. Refer to [Managing Undo/Redo](CAADegUndoRedo.htm).
    
    AddTransition(...
                  **Action(**(ActionMethod) &CAACreateLineCmd::CreateLine,
                         (ActionMethod) &CAACreateLineCmd::UndoCreateLine,
                         (ActionMethod) &CAACreateLineCmd::RedoCreateLine,**CAAIPoint * EndPoint)**);
    // OR
    _MyAction->**SetData(CAAIPoint * EndPoint)** ;  
  
---  
For example, an action method that creates a line could be.
    
    CATBoolean CAACreateLineCmd::CreateLine(void * iDummy)
    {
      // action task is implemented there
      return TRUE;
    }  
  
---  
Then you may add this action to a transition by providing it as an argument of the `Action` method which returns a _CATDiaAction_ instance and provide the returned instance as the fourth argument of the `AddTransition` method:
    
    AddTransition(_state1, NULL,
                  IsOutputSetCondition(_point2),
                  **Action((ActionMethod) &CAACreateLineCmd::CreateLine)**);  
  
---  
Creating an Action Class When an action is reusable, such as a line creation that can be used in a command that creates line and in a command that creates polylines, it is advised to encapsulate it in class that derives from _CATDiaAction_. An action class must at least override the inherited `Execute` method in order to implement the action task. It may also provide an `Undo` method (see Input Undo/Redo.) For example, the _CreateLine_ class is created to create a line. The _CreateLine_ class header file is:
    
    class CreateLine: public CATDiaAction
    {
      public:
        CreateLine(CATMathPoint StartPoint, CATIndicationAgent * daIndicationAgent);
        virtual ~CreateLine();
        virtual CATBoolean Execute();
      private:
        CATMathPoint         _StartPoint;
        CATIndicationAgent * _daIndicationAgent;
    }  
  
---  
Let's have a look at the _CreateLine_ constructor and `Execute` method.
    
    CreateLine::CreateLine(CATMathPoint         StartPoint,
                           CATIndicationAgent * daIndicationAgent):
              _StartPoint(StartPoint), _daIndicationAgent(daIndicationAgent)
    {}
    
    CATBoolean CreateLine::Execute()
    {
      // Creates a line between StartPoint and EndPoint
      return TRUE;
    }  
  
---  
Notice that action parameters are provided by means of its constructor. They are stored in private data members in order to be used by the `Execute` method. To use this action class in the `BuildGraph` method of your state dialog commands, you simply need to instantiate it, and pass the pointer to that class to the `Action` method that will call the `Execute` method.
    
    ...
    **_CreateLineAction** = new CreateLine(_StartPoint,
                                       _daIndicationAgent);
    AddTransition(_state2, NULL,
                  AndCondition(
                    IsOutputSetCondition(_daIndicationAgent),
                    CoincidenceCondition)),
                  **_CreateLineAction**);
    ...  
  
---  
Note that `_CreateLineAction` must be a data member of your state dialog command class, and must be deleted in the destructor. [Top] Creating Composite Actions A composite action is built by combining actions using the AND and  OR operators supplied through the following methods: 
    * `AndAction`: `iAction1` is executed first, then `iAction2` is executed 
          
          CATDiaAction * AndAction(CATDiaAction * iAction1,
                                   CATDiaAction * iAction2);  
  
---  
    * `OrAction`: `iAction1` is executed first, and then `iAction2` is executed if `iAction1` was successful, that is if the executed method returned `TRUE`
          
          CATDiaAction * OrAction (CATDiaAction * iAction1,
                                   CATDiaAction * iAction2);  
  
---  
For example, the following expression: `/action1, action2` is implemented in this way:
    
    AddTransition(state1, state2,
                  ... ,
                  AndAction(action1, action2);  
  
---  
where `action1` and `action2` are pointers to _CATDiaAction_ instances. [Top] Creating State Entry/Exit Actions Entry/Exit actions are useful when you need to execute an action either: 
    * When a transition enters a state: 
          
          CATDialogState::SetEnterAction(CATDiaAction * iAction);  
  
---  
    * When a transition exits a state: 
          
          CATDialogState::SetLeaveAction(CATDiaAction * iAction);  
  
---  
Entry/Exit actions are not executed by a self-transition. [Top] Storing the Created Object in the CSO If your state dialog command creates a new object in the document, you should store this object in the Current Set of Objects to enable for the object-action paradigm. The next command will then be able to take this object as input without end user action. Storing the resulting object in the CSO is done in three steps in the appropriate method: 
    1. Retrieve the current editor
    2. Retrieve the CSO from the current editor
    3. Add the element to the CSO
The following code shows how to add the `_CreatedObject` to the CSO:
    
    ...
    CATFrmEditor * pEditor = GetEditor();
    CATCSO * pCso;
    if (pEditor && ((pCso = pEditor->GetCSO()) != NULL)
                     pCso->AddElement(_CreatedObject);
    ...  
  
---  
[Top]

* * *

Troubleshooting A Self-transition Loops with no Means to Get out of the Loop ![symptom.gif \(111 bytes\)](../CAAIcons/images/symptom.gif) | A self-transition loops on the same state, and whatever the end user does, there is no means to get out of the loop.  
---|---  
![diagnos.gif \(130 bytes\)](../CAAIcons/images/diagnos.gif) | The state on which the self-transition loops has no dialog agent plugged, or the dialog agent is already valued, is not set as repeatable, and is not recycled.  
![solution.gif \(218 bytes\)](../CAAIcons/images/solution.gif) | Either assign a dialog agent to the state, or recycle the existing one in the action method.  
[Top]

* * *

In Short A dialog state command is a dialog command designed as a state machine, each state enabling end user input, that allows the end user to pass from state to state using transitions between these states triggered when requested events happen and when requested guard conditions are satisfied, and that execute the declared actions. It is modeled using a class deriving from the _CATStateCommand_ class. The statechart diagram is implemented using the `BuildGraph` method. [Top]

* * *

References [1] | [Conveying End User Intent from Mouse to Controller](../CAAVisTechArticles/CAAVisViewerProtocol.htm)  
---|---  
[Top]  
  
* * *

History Version: **1** [Jan 2000] | Document created  
---|---  
Version: **2** [Sep 2002] | Behavior mode updated  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
