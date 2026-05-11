---
title: "Untitled"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAAScrBase", "CAASchNetwork_02", "CATIA", "CAAScrJavaScript", "CAASCH_Network01", "CAAScdSchUseCases", "CAASchPlatformModeler", "CAAScdInfUseCases", "CAAInfLauchMacro", "CAASchNetwork", "CAASCHEDUApp", "CAASchNetworkSource", "CAASchNetwork_01", "CAASchAppBase", "CATIAProduct", "CAADoc", "CAASchAppUtilities", "CATIASchNetworkAnalysis"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchNetwork.htm"
converted: "2026-05-11T11:27:02.645122"
---

---

 
 
     

Next, the macro acquires the schematic root object from the document. 
     The schematic root is the top node of the object instance tree in a 
     schematic document.
     
     

#### Create a list of network objects 
     using the SchBaseFactory interface
     

The macro calls the GetSchBaseFactory method to get a handle of the 
     SchBaseFactory interface.
     

This macro provides a private Find2ComponentInst function which searches 
     for 2 component instances in the model based on a specific naming 
     convention. Those instances which have the word "network" as parts of their 
     instance names will be included. For each instance returned by 
     Find2ComponentInst, the graphical image of the instance is also returned. 
     Notice that two global variables: objLCntbl_**g** and objLGRR_**g **
     are used to stored these results in Find2ComponentInst. They are available 
     to the main subroutine to be used in calling the CreateNetwork method.
     
     

#### Query the member of the list of network 
     objects
     

Each network object in the list contains the following information.
     

       
- The input object itself.
       
- A list of Schematic component instances that are directly or 
       indirectly connected to the input object. This list of connected 
       component instances can be retrieved using the ListNetworkObjects method.
       
- The listing procedure is recursive, and it will stop when the 
       connected object is a Schematic route. This Schematic route (known as the 
       "extremity") will be stored in a separate list. This list of "extremity" 
       objects can be retrieved using the ListExtremityObjects method.
     
     

The macro first find out the number of network objects in the output 
     list. Then, for each member in the output list it does the following.
     

       
- Call the ListNetworkObjects method to get a list of connected 
       Schematic component.
       
- Call the ListExtremityObjects method to get a list of extremity 
       objects (the Schematic route objects).
       
- For each member in those lists, the macro obtain a Product interface 
       handle to report their instance names.
     
     
     
   
 
 

[Top]

---

 
 

#### In Short
 

This use case shows how to create a Schematic network object. Furthermore, 
 it illustrates how to get information from the network object. A message 
 logging the status of the critical steps is displayed at the end of the use 
 case. 
 

![](images/CAASchNetwork_02.jpg)
 

[Top]

---

 
 

#### References
 
 

---

 
 

*Copyright  2001, Dassault Systmes. All rights reserved.*