---
```vbscript
title: "Describing State Dialog Commands Using UML"
category: "use-case"
module: "CAADegTechArticles"
tags: []
source_file: "Doc/online/CAADegTechArticles/CAADegUMLDescription.htm"
converted: "2026-05-11T17:33:49.888146"
```

---
tags: []
source_file: "Doc/online/CAADegTechArticles/CAADegUMLDescription.htm"
converted: "2026-05-11T17:33:49.888146"
3D PLM Enterprise Architecture |  User Interface - Commands |  Describing State Dialog Commands Using UML _The tools that UML provides to design you state dialog commands_  

converted: "2026-05-11T17:33:49.888146"
3D PLM Enterprise Architecture |  User Interface - Commands |  Describing State Dialog Commands Using UML _The tools that UML provides to design you state dialog commands_
Technical Article  

* * *

Abstract State dialog commands can be easily designed using state machines, and described using statechart diagrams expressed using the Unified Modeling Language (UML) as a dialog description tool. This article introduces the sate machines and the graphical formalism of the UML. 
    * **State Machines**
    * **Statechart Diagrams**
      * Example of the Line Command
      * Graphical Notation Standard
      * Simple and Composite States
    * **Dialog Agents**
      * Dialog Agents and Input-Driven Transitions
      * Dialog Agents Enable Straightforward Statechart Diagrams
      * Dialog Agents and Conditions
    * **An Artificial Interlocutor**
      * Interacting with the Line Command
      * One-Shot Input
      * Repeated Input
    * **In Short**
    * **References**  
---  

* * *

State Machines A _state machine_ reacts to events applied to it by external objects, according to the Unified Modeling Language (UML) semantics [1]. Dialog state commands are modeled as state machines. A state machine describes an object's behavior as a graph made of _states_ linked between them using incoming and outgoing _transitions_. A transition is usually triggered thanks to an _event_ , and usually checks that a _guard condition_ evaluates to true before executing the _action_ associated with the state. The transition _source state_ becomes _inactive_ and the transition _target state_ becomes _active_. The _initial state_ and the _final state_ are _pseudo states_ between which the state machine states range. A state machine is divided into _steps_ , and the fundamental assumption is that events are processed in sequence. Each event stimulates a _run-to-completion_ step. This simplifies transitions in a state machine, since any incoming event is processed only after the state machine has reached a stable _state configuration_. Transitions can be triggered not only by events, but also by conditions, or both. They can be also automatically triggered, or  automatically triggered with respect to a guard condition. A state can be decomposed into substates, and is there called a _composite state_. Two refinement ways are possible: sequential substates, that is substates that are linked with transitions in sequence, one being active at a given instant, and concurrent substates that are mutually exclusive substates that are active at the same time. Each substate can be in turn refined. Transitions can be assembled in clusters of transitions named _compound_ transitions, or _complex_ transitions by UML notation. [Top] Statechart Diagrams A statechart diagram is intended to graphically represent a state machine. [Top] Example of the Line Command UML provides a means to describe and graphically represent state machines using statechart diagrams, that prove useful when designing dialog state commands. Let's take the example of the Line command [2]. The Line command, as any state dialog command, could be described as a state machine and represented using the UML notation [3] as shown in Fig. 1. ![GettingStartedStateChart.gif \(9621 bytes\)](images/GettingStartedStateChart.gif)  
---  
State Machines A _state machine_ reacts to events applied to it by external objects, according to the Unified Modeling Language (UML) semantics [1]. Dialog state commands are modeled as state machines. A state machine describes an object's behavior as a graph made of _states_ linked between them using incoming and outgoing _transitions_. A transition is usually triggered thanks to an _event_ , and usually checks that a _guard condition_ evaluates to true before executing the _action_ associated with the state. The transition _source state_ becomes _inactive_ and the transition _target state_ becomes _active_. The _initial state_ and the _final state_ are _pseudo states_ between which the state machine states range. A state machine is divided into _steps_ , and the fundamental assumption is that events are processed in sequence. Each event stimulates a _run-to-completion_ step. This simplifies transitions in a state machine, since any incoming event is processed only after the state machine has reached a stable _state configuration_. Transitions can be triggered not only by events, but also by conditions, or both. They can be also automatically triggered, or  automatically triggered with respect to a guard condition. A state can be decomposed into substates, and is there called a _composite state_. Two refinement ways are possible: sequential substates, that is substates that are linked with transitions in sequence, one being active at a given instant, and concurrent substates that are mutually exclusive substates that are active at the same time. Each substate can be in turn refined. Transitions can be assembled in clusters of transitions named _compound_ transitions, or _complex_ transitions by UML notation. [Top] Statechart Diagrams A statechart diagram is intended to graphically represent a state machine. [Top] Example of the Line Command UML provides a means to describe and graphically represent state machines using statechart diagrams, that prove useful when designing dialog state commands. Let's take the example of the Line command [2]. The Line command, as any state dialog command, could be described as a state machine and represented using the UML notation [3] as shown in Fig. 1. ![GettingStartedStateChart.gif \(9621 bytes\)](images/GettingStartedStateChart.gif)
_Fig. 1: The Line Command Statechart Diagram_  
The state machine progresses from the initial state to the final state. The dialog flow starts with the initial state, which is a pseudo state that has no incoming transition. The command is never in the initial state that automatically skips to the first state. This first state is dedicated to the start point input and is shown as a state vertex using a round corner box that displays the state name. A prompt linked to the first state can invite the end user to indicate this start point. The transition between the first state and the second state is triggered as soon as the end user indicates a valid point. This happens when the expected event is detected (the mouse left key is pressed), and when the guard condition is satisfied. The transition action, that is create a temporary point, is executed. A prompt linked to the second state can then invite the end user to indicate the end point. The transition to the final state is triggered as soon as the end user indicates a valid point. This creates the line. The final state is reached, and the command completes. [Top] Graphical Notation Standard We use the UML notation [3] _State vertices_ | Round corner boxes showing the state name 

State Machines A _state machine_ reacts to events applied to it by external objects, according to the Unified Modeling Language (UML) semantics [1]. Dialog state commands are modeled as state machines. A state machine describes an object's behavior as a graph made of _states_ linked between them using incoming and outgoing _transitions_. A transition is usually triggered thanks to an _event_ , and usually checks that a _guard condition_ evaluates to true before executing the _action_ associated with the state. The transition _source state_ becomes _inactive_ and the transition _target state_ becomes _active_. The _initial state_ and the _final state_ are _pseudo states_ between which the state machine states range. A state machine is divided into _steps_ , and the fundamental assumption is that events are processed in sequence. Each event stimulates a _run-to-completion_ step. This simplifies transitions in a state machine, since any incoming event is processed only after the state machine has reached a stable _state configuration_. Transitions can be triggered not only by events, but also by conditions, or both. They can be also automatically triggered, or  automatically triggered with respect to a guard condition. A state can be decomposed into substates, and is there called a _composite state_. Two refinement ways are possible: sequential substates, that is substates that are linked with transitions in sequence, one being active at a given instant, and concurrent substates that are mutually exclusive substates that are active at the same time. Each substate can be in turn refined. Transitions can be assembled in clusters of transitions named _compound_ transitions, or _complex_ transitions by UML notation. [Top] Statechart Diagrams A statechart diagram is intended to graphically represent a state machine. [Top] Example of the Line Command UML provides a means to describe and graphically represent state machines using statechart diagrams, that prove useful when designing dialog state commands. Let's take the example of the Line command [2]. The Line command, as any state dialog command, could be described as a state machine and represented using the UML notation [3] as shown in Fig. 1. ![GettingStartedStateChart.gif \(9621 bytes\)](images/GettingStartedStateChart.gif)
_Fig. 1: The Line Command Statechart Diagram_
The state machine progresses from the initial state to the final state. The dialog flow starts with the initial state, which is a pseudo state that has no incoming transition. The command is never in the initial state that automatically skips to the first state. This first state is dedicated to the start point input and is shown as a state vertex using a round corner box that displays the state name. A prompt linked to the first state can invite the end user to indicate this start point. The transition between the first state and the second state is triggered as soon as the end user indicates a valid point. This happens when the expected event is detected (the mouse left key is pressed), and when the guard condition is satisfied. The transition action, that is create a temporary point, is executed. A prompt linked to the second state can then invite the end user to indicate the end point. The transition to the final state is triggered as soon as the end user indicates a valid point. This creates the line. The final state is reached, and the command completes. [Top] Graphical Notation Standard We use the UML notation [3] _State vertices_ | Round corner boxes showing the state name
_Transitions_ | Arrows between state vertices 
_Initial state_ | A small solid filled circle 
_Final state_ | A circle surrounding a small solid filled circle 
_Events_ | Text | left-mouse-down  
_Guard conditions_ | Text between square brackets | [point indicated && point valid]  
_Actions_ | Text beginning with a slash | / create line  

[Top] Simple and Composite States Command input can be a bit more complex than the one of the Line command shown above. A composite input can be necessary when an applicative task requires at least two input without taking care of the order in which they are provided by the user. This is a common situation as illustrated by a Sphere creation dialog: 
    * "_A sphere is created when the user has provided a center**and** a radius_".
_Events_ | Text | left-mouse-down
_Guard conditions_ | Text between square brackets | [point indicated && point valid]
_Actions_ | Text beginning with a slash | / create line
With simple states, the statechart diagram could be as shown in Fig. 2. ![SphereSimpleStatechart.gif \(6419 bytes\)](images/SphereSimpleStatechart.gif)  

---  
_Actions_ | Text beginning with a slash | / create line
With simple states, the statechart diagram could be as shown in Fig. 2. ![SphereSimpleStatechart.gif \(6419 bytes\)](images/SphereSimpleStatechart.gif)
_Fig. 2: The Sphere Command Statechart Diagram with Simple States_  
But composite input can be also described thanks to concurrent composite states. A composite state is the result of a state decomposed into substates. It is said to be concurrent if the decomposition results in substates that are all active, or non-concurrent if one only is active. Each substate can in turn be refined into its own substates. Using a concurrent composite state, the sphere dialog statechart diagram is simplified, as shown in Fig. 3. It is made of a single concurrent composite state between the initiaml and the final states, that includes two concurrent substates. These two substates are active when the state machine transitions from the initial state to the concurrent composite state. Each substate is shown as a  nested statechart diagram, including its own initial state, and its own final state. Both final states must have been reached to trigger the transition that creates the sphere. ![SphereCompositeState.gif \(4147 bytes\)](images/SphereCompositeState.gif)  

---  
With simple states, the statechart diagram could be as shown in Fig. 2. ![SphereSimpleStatechart.gif \(6419 bytes\)](images/SphereSimpleStatechart.gif)
_Fig. 2: The Sphere Command Statechart Diagram with Simple States_
But composite input can be also described thanks to concurrent composite states. A composite state is the result of a state decomposed into substates. It is said to be concurrent if the decomposition results in substates that are all active, or non-concurrent if one only is active. Each substate can in turn be refined into its own substates. Using a concurrent composite state, the sphere dialog statechart diagram is simplified, as shown in Fig. 3. It is made of a single concurrent composite state between the initiaml and the final states, that includes two concurrent substates. These two substates are active when the state machine transitions from the initial state to the concurrent composite state. Each substate is shown as a  nested statechart diagram, including its own initial state, and its own final state. Both final states must have been reached to trigger the transition that creates the sphere. ![SphereCompositeState.gif \(4147 bytes\)](images/SphereCompositeState.gif)
_Fig. 3: The Sphere Command Statechart Diagram with a Concurrent Composite State_  

[Top] Dialog Agents A _dialog agent_ translates a user interaction into a user input. This translation is managed by a state machine that is encapsulated by the dialog agent. As an example, the indication agent interprets a left button mouse click as a 2D-coordinate input. ![DialogAgentStateMachine.gif \(2555 bytes\)](images/DialogAgentStateMachine.gif) The dialog agent hides the details of how a user interaction, here a mouse click in a 2D viewer, is translated as a user input, that is 2D coordinates. The keypoint is that dialog agents strenghtens the MVC model by shifting from an _event-driven_ dialog to an _input-driven_ dialog: using a indication agent allows a dialog command to read 2D coordinates without taking care of how the end user provides them, for example by keying numeric values or by clicking the left button of the mouse in a 2D viewer. [Top] Dialog Agents and Input-Driven Transitions The new representation highlights event encapsulation by using _input-driven_ transitions instead of _event-driven_ transitions. An _input-driven_ transition is a kind of condition-driven transition which requires a user input. The condition has a validation responsibility toward the end user input: the input may be constrained. For example, the position should be within the drawing sheet ([position within sheet?]), or elsewhere ([position?]). ![DialogAgentStateMachine2.gif \(3900 bytes\)](images/DialogAgentStateMachine2.gif) [Top] Dialog Agents Enable Straightforward Statechart Diagrams Using dialog agents simplifies further the Sphere dialog: ![DialogAgentStateMachine3.gif \(5186 bytes\)](images/DialogAgentStateMachine3.gif) [Top] Dialog Agents and Conditions Statechart diagrams representing state dialog commands are often input-driven. This characteristic impacts the test of conditions: 
    * In a traditional state machine, condition-driven transitions are tested as soon as a state becomes active.
    * In a statechart of a state dialog command, the input-driven transitions are tested only after an end user input. This makes sense because a condition may become true only if new input has been provided.
Some dialogs contain ambiguous conditions. In this case the transition order is crucial: the first transition which matches the user interaction wins while the others are not even warned. [Top] An Artificial Interlocutor A state dialog command embodies a part of the developer's know-how to interact with the end user like an alter-ego. This section shows how this interactivity takes place.

* * *

Interacting with the Line Command From the user's point of view, the Line dialog follows a step by step scenario: ![LineCmdStatechart.gif \(9222 bytes\)](images/LineCmdStatechart.gif) In the case of the Line command, the dialog agent to acquire points is recycled after the first transition to be reused in the second transition as if it were a new one. [Top] One-Shot Input Once a valid input has been provided, the agent becomes inactive (this is shown by the checkmark): the user is no more prompted to provide an input. **Graphical Representation:** ![depg0a10.gif \(907 bytes\)](images/depg0a10.gif) The _checkmark_ symbolizes a valid input. The one-shot input behavior doesn't make a difference in the Line command dialog but it is not the case with the Sphere command dialog: ![SphereStatechart.gif \(5599 bytes\)](images/SphereStatechart.gif) [Top] Repeated Input A _repeater_ agent is not deactivated by a user input as opposed to a _one-shot_ agent (default mode). If we set the radius agent as a repeater in the Sphere dialog, the user will be able to modify the radius as long as the center is not provided. **Graphical Representation** : ![depg0aa2.gif \(917 bytes\)](images/depg0aa2.gif) The repeat mark symbolizes a repeater agent. The repeated input behavior for the radius input of the Sphere command dialog enables the end user to modify the radius value after it was input, as long as the center is not input. ![SphereStatechartRepeat.gif \(5735 bytes\)](images/SphereStatechartRepeat.gif) [Top]

* * *

In Short A state dialog command is modeled as a state machine and can be graphically represented using a statechart diagram expressed using the Unified Modeling Language (UML). Dialog agents are specific encapsulated state machines that simplifies the dialog by replacing several states and event-driven transitions by a composite state and a simple input-driven transition. Dialog agents can be valued in one shot, or proposed again for input value modification. They can also be recycled. [Top]

* * *

References [1] | Unified Modeling Language - UML Semantics version 1.1  
---|---  
[2] | [Getting Started with State Dialog Commands](CAADegGettingStarted.md)  
[3] | Unified Modeling Language - UML Notation Guide version 1.1  
[Top]  

* * *

History Version: **1** [Jan 2000] | Document created  
---|---  
[Top]  

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
