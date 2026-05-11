---
title: "Untitled"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CATIA", "CAASchPlatformModeler", "CATIASchCompGraphic", "CAAScrBase", "CAASCHEDUFuncString", "CAAScdInfUseCases", "CAASCHEDUApp", "CATIASchGRRComp", "CAAInfLauchMacro", "CAASchAppUtilities", "CATIASchGRR", "CAASCH_RouteBetween2Equip", "CAASchRouteBetween2Equip_01", "CAASchAppBase", "CAAScrJavaScript", "CAAScdSchUseCases", "CAASCHEDUConnector", "CATIASchCompatible", "CAASchRouteBetween2EquipSource", "CAASchRouteBetween2Equip_02"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchRouteBetween2Equip.htm"
converted: "2026-05-11T11:27:02.624110"
---

---

 
 
     

Next, the macro acquires the schematic root object from the document. 
     The schematic root is the top node of the object instance tree in a 
     schematic document.
     
     

#### Find the two Schematic 
     component instances to route between
     

This macro provides the internal Find2ComponentInst subroutine to find 
     the Schematic component instance to start the route with and the Schematic 
     component instance to end the route with.
     

Find2ComponentInst uses the GetComponents method to obtain a list of all 
     the Schematic component instances in the document.
     
     

Then it searches for two components that match the name requirement. 
     Notice that when looping through each member in the component instance 
     list, the macro uses the method GetInterface to get two specific interface 
     on the same member object.
     

       
- SchCompatible - to be use latter in the route.
       
- Product - for the Name method. The macro uses this method to obtain 
       the name of the current instance so that it can match it with "_Routeto" 
       and "_Routetrom"
     
     
     

If a match is found, the interface SchCompatible interface handle will 
     be stored in a local variable: objCompCompatFrom or objCompCompatTo. The 
     macro also uses the internal GetComponentImage function to find the 
     graphical image of the current instance. The function returns a 
     SchCompGraphic handle which will be store in the local variable: 
     objSchCompGraph.
     

The loop exists when intNbFound is two.
     
     

The local varaibles are stored in two global lists which are accessible 
     to the main subroutine.
     

       
- objLCompat_g - for the list of SchCompat handles of the "RouteFrom" 
       and the "RouteTo" component instances.
       
- objLGRRComp_g - for the list of GRRComp handles for the corresponding 
       members in the objLCompat_g list.
     
     
     

#### Create a 
     Schematic Route connecting to the two Schematic Component instances
     

This macro provides the internal RouteLineBetween2Component subroutine 
     to create the Schematic route. Two global lists populated in previous steps 
     are accessible to this subroutine. They are the objLCompat_g and the 
     objLGRRComp_g lists. Each member is that list is used for calling the 
     following methods.
     

       
- IsTargetOKForRoute - checks whether the component instance is 
       compatible with the type of Schematic route to make a connection. In type 
       is specified by the connector type at the end of the route. In this case, 
       it the "CAASCHEDUConnector".
       
- GetBestCntrForRoute - returns the x-y coordinates of the position of 
       a connector that the route can connect to. The position is used as the 
       start or the end point of the Schematic route. This position is based on 
       an input point. The position of the connector closest to the input point 
       will be returned.
     
     
     

The beginning and the ending route points of the Schematic routes are 
     the connector positions from above. The macro uses the AppCreateRoute to 
     create an application specific route object, this is an input to the next 
     method to be called. Next, the method CreateSchRouteByPoints is used to 
     create the Schematic Route.
     
     

The macro provides the internal FindConnectorAtPosition function to 
     return an interface handle on the connectors at each ends of the newly 
     created Schematic route. 
     
     

Finally, the macro uses the AppConnect method to connect the newly 
     created route instance to the two existing component instances through 
     their connectors.
     
     
   
 
 

[Top]

---

 
 

#### In Short
 

This use case shows how to create a Schematic route between two Schematic 
 component instances. A message logging the status of the critical steps is 
 displayed at the end of the use case.
 

 ![](images/CAASchRouteBetween2Equip_02.jpg)
 

[Top]

---

 
 

#### References
 
 

---

 
 

*Copyright  2001, Dassault Systmes. All rights reserved.*