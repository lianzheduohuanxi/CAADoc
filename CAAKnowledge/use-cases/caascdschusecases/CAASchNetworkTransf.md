---
title: "Untitled"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAAScrBase", "CATIASchMovable", "CATIA", "CAAScrJavaScript", "CAASCH_Network01", "CAASchNetworkTransfSource", "CAAScdSchUseCases", "CAASchNetworkTransf_02", "CAASchPlatformModeler", "CAASchNetworkTransf_01", "CAAScdInfUseCases", "CAAInfLauchMacro", "CAASCHEDUApp", "CAASchAppBase", "CAADoc", "CAASchAppUtilities", "CAASchNetworkTransf"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchNetworkTransf.htm"
converted: "2026-05-11T11:27:02.651660"
---

---

 
 
     

Next, the macro acquires the schematic root object from the document. 
     The schematic root is the top node of the object instance tree in a 
     schematic document.
     
     

#### Translating a Schematic component 
     that is connected to other objects
     

This macro provides a private FindNetworkComponent subroutine which 
     searches for specific component instances in the model based on a specific 
     naming convention. Those instances which have the word "_network_scale" as 
     parts of their instance names will be included. FindNetworkComponent 
     populates the two global lists objLCntbl_**g** and objLGRRl_**g **
     that are used as input in calling the CreateNetwork method.
     
     

A network object member in the output list: objLNetwork implements the 
     SchMovable interface. This interface provides the Translate method to move 
     all the members in the network accounting for the connectivity.
     
     

#### Scaling a Schematic component that is 
     connected to other objects
     

The SchMovable interface provides the ScaledSelectedObjects method to 
     scale a component that is part of the network. This method also requires a 
     list of "selected" component as input. "Selected" components are those that 
     are found explicitly by FindNetworkComponentInst (through naming convention 
     in this use case) and **not** those that are inferred from the network 
     analysis done by the CreateNetwork method.
     
     
   
 
 

[Top]

---

 
 

#### In Short
 

This use case shows how to transform a Schematic network object. A message 
 logging the status of the critical steps is displayed at the end of the use 
 case.
 

 ![](images/CAASchNetworkTransf_02.jpg)
 

[Top]

---

 
 

#### References
 
 

---

 
 

*Copyright  2001, Dassault Systmes. All rights reserved.*