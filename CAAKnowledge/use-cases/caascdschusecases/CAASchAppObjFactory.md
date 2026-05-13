---
title: "Untitled"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CATIA", "CAASchPlatformModeler", "CAASchAppObjFactory", "CAAScrBase", "CAASCHEDUFuncString", "CATIASchComponent2", "CAAScdInfUseCases", "CAASchAppObjFactory_02", "CAASCHEDU_SamplePID", "CAASCHEDUApp", "CAASchAppObjFactory_01", "CAAInfLauchMacro", "CAASchAppUtilities", "CATIASchGRR", "CAASCHEDUCompressFunc", "CAASchAppBase", "CAAScrJavaScript", "CAAScdSchUseCases", "CAASCHEDUConnector", "CATIASchCompatible"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchAppObjFactory.htmmd"
converted: "2026-05-11T11:27:02.642129"
---

---

 
 
     

Next, the macro acquires the schematic root object from the document. 
     The schematic root is the top node of the object instance tree in a 
     schematic document.
     
     

From this schematic root object the following factory objects can be 
     obtained.
     

       
- Application object factory (in this case the application is 
       "CAASCHEDU_SamplePID") creates application objects independent of the 
       Schematic platform.
       
- Schematic base object factory. This factory creates the schematic 
       extensions and associates them to application objects.
       
- Schematic temporary list factory. This factory creates various kinds 
       of lists that are not persistent. They are only available in the current 
       session and are not saved in the model.
     
     
     

#### Creating a schematic reference 
     component
     

The macro calls the AppCreateCompRef method to create an application 
     reference object. In this use case, the "CAASCHEDU_SamplePID" sample 
     application implements this method to create the appropriate object that 
     suits its needs. The schematic platform is totally transparent to how the 
     application does this. 
     
     

A graphical representation (a symbol) is needed to define a schematic 
     reference component. The macro searches the model to find an appropriate 
     one by calling the method GetComponentSymbol. An appropriate symbol is the 
     one that has not been associated to any schematic component.
     
     

Next, after successfully obtaining the application object and the 
     graphical representation, the marco calls the CreateSchComponent method to 
     create and to associate a schematic component extension to the application 
     object. This method is implemented by the Schematic Platform.
     

Note that, a temporary list of object is created to contain the graphic 
     representation. This list is input (the second argument) to the function 
     CreateSchComponent.
     
     

#### Add two connectors to the reference 
     component
     

To add connectors to the reference component just created, we need a 
     different interface ("CATIASchCompConnector") on the reference component 
     class. Given a different interface handle (on the same reference component) 
     objAppCompRef, we can obtain the necessary interface handle by using the 
     GetInterface method. This method is implemented on the schematic root 
     object class.
     

The following data needs to be defined when creating a connector.
     

       
- The x-y coordinates of the connector position with respect to the 
       axis of the symbol.
       
- The x-y coordinates of the connector alignment vector with respect to 
       the axis of the symbol.
     
     
     

#### Place an instance of the schematic 
     reference component in the current document
     

To create an instance in a specific document, we need to use the 
     PlaceInSpace method of the interface CATIASchComponent2. We can obtain this 
     interface from the schematic reference object through the GetInterface 
     method.
     

We also need to specify the positioning matrix for the graphical 
     representation of the component instance. This matrix consists of six real 
     numbers (double). The first four numbers defines the axes (x-axis and 
     y-axis) and the last two numbers defines the x-y position of the symbol 
     instance.
     
     

#### Create a schematic route instance
     

To create a schematic route instance we need to specify the x-y 
     coordinates of all the points defining the segments of the route path (a 
     polyline). In this use case, the macro will find a position that matches 
     one of the connector position in the schematic component instance we have 
     just created in previous step, and will use that to define the first point 
     of the route. 
     

Given a schematic component instance, we can obtain the 
     CATIASchCompatible interface from it. This interface can be used to check 
     whether this component instance can be connected to a specific type of 
     schematic route. In this use case, the type of the route to be created is 
     one that includes a "CAASCHEDUConnector" at each of its two ends.
     

IsTargetOKForRoute is called for the checking. It returns a flag 
     bCompatible and if this flag is TRUE, then the route we are going to create 
     is compatible with the component instance and can be connected to it. It 
     also returns a list of compatible connectors of the component instance that 
     can be used in the next call GetBestCntrForRoute. This call returns a 
     handle on a connector (of the component instance). The x-y coordinates of 
     the position of this connector defines the first route points.
     
     

The macro calls the AppCreateRoute method to create an application route 
     instance. In this use case, the P&ID application implements this method to 
     create the appropriate object that suits its needs. The schematic platform 
     is totally transparent to how the application does this. 
     

Method CreateSchRouteByPoints is called to create and to associate a 
     schematic route instance to the application object. Note that an array of 
     doubles specifying the x-y coordinates of the route points is input to the 
     method. The first two doubles in the array is an output of the previous 
     call.
     
     

#### Connect the route instance to the component 
     instance
     

The newly created route instance is connected to the component instance 
     via their connectors.
     
     
   
 
 

[Top]

---

 
 

#### In Short
 

This use case shows how to build a schematic component reference with 
 connectors. In addition, it shows how to create an instance of the reference. A 
 message logging the status of the critical steps is displayed at the end of the 
 use case. 
 

 ![](images/CAASchAppObjFactory_02.jpg)
 

[Top]

---

 
 

#### References
 
 

---

 
 

*Copyright  2001, Dassault Systmes. All rights reserved.*