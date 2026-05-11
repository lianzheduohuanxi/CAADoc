---
title: "Transforming a Schematic Network Object"
category: "general"
module: "CAAScdSchUseCases"
tags: ["CAADoc", "CAAScdSchUseCases", "CATIA", "CAASchAppBase", "CAASCHEDUApp", "CAASchPlatformModeler", "CATIASchMovable", "CAASCH_Network01", "CAASchNetworkTransf", "CAASchAppUtilities"]
source_file: "Doc\online\CAAScdSchUseCases\CAASchNetworkTransf.htm"
converted: "2026-05-11T17:31:51.417508"
---

## Schematics Platform Modeler

| 

## Transforming a Schematic Network Object  
  
---|---  
  
* * *

![](../CAAScrBase/images/atarget.gif) | This macro shows you how to transform a schematic network object.Given a list of independent objects that are connected to other objects, this macros shows how to transform the members accounting for the connectivity. This macro opens the CAASCH_Network01.CATProduct document. ![](images/CAASchNetworkTransf_01.jpg) Through special naming convention (i.e. the word "_network_scale" embedded in the instance name), the macro knows to include the following Schematic component instances in the input list.

  1. V-082_network_scale_instance.

  
---|---  
![](../CAAScrBase/images/ainfo.gif) | CAASchNetworkTransf is launched in CATIA [1]. No open document is needed.Special environment must be available to successfully run this macro:

  * Prerequisites:



>   1. RADE must be installed.
>   2. CAASchPlatformModeler.edu must exist in CAADoc folder.
> 


  * Setup:



>   1. Build CAASchAppBase.m and CAASchAppUtilities.m, located in CAASchPlatformModeler.edu (RADE is required). 
>   2. Copy generated DLLs, CAASchAppBase.dll and CAASchAppUtilities.m, respectively, to the run-time environment folder "intel_a\code\bin."
>   3. Copy CAASCHEDUApp.CATfct, located CAASchPlatformModeler.edu\CNext\resources\graphic, to the run-time environment folder "intel_a\resources\graphic."
>   4. Copy CAASchPlatformModeler.edu\CNext\code\dictionary\CAASchPlatformModeler.edu.dico to the run-time environment folder "intel_a\code\dictionary."
> 


[CAASchNetworkTransf.CATScript ](CAASchNetworkTransfSource.htm) is located in the CAAScdSchUseCases module. [Execute macro](macros/CAASchNetworkTransf.CATScript) (Windows only).  
![](../CAAScrBase/images/ascenari.gif) | CAASchNetworkTransf includes the following steps:

  1. Prolog
  2. Translating a Schematic component that is connected to other objects
  3. Scaling a Schematic component that is connected to other objects



#### Prolog

The macro first loads CAASCH_Network01.CATProduct. |     ...  
    ' -------------------------------------------------------------------------    
    ' Open the schematic document   
    Dim sFilePath  
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _  
            "online\CAAScdSchUseCases\samples\CAASCH_Network01.CATProduct")  
  
    Dim objSchDoc As Document  
    Set objSchDoc = CATIA.Documents.Open(sFilePath)  
    ...  
---  
  
Next, the macro acquires the schematic root object from the document. The schematic root is the top node of the object instance tree in a schematic document.

    ...  
    ' Find the top node of the schematic object tree - schematic root.  
    Dim objPrdRoot As Product  
    Dim objSchRoot As SchematicRoot  
    If ( Not ( objSchDoc Is Nothing ) ) Then  
      Set objPrdRoot = objSchDoc.Product   
      If ( Not ( objPrdRoot Is Nothing ) ) Then  
        Set objSchRoot = objPrdRoot.GetTechnologicalObject("SchematicRoot")  
      End If  
    End If  
    ...  
---  
  
#### Translating a Schematic component that is connected to other objects

This macro provides a private FindNetworkComponent subroutine which searches for specific component instances in the model based on a specific naming convention. Those instances which have the word "_network_scale" as parts of their instance names will be included. FindNetworkComponent populates the two global lists objLCntbl_**g** and objLGRRl_**g** that are used as input in calling the CreateNetwork method.

    ...  
             '-----------------------------------------------------------------  
             ' The following "Sub" will populate objLCntbl_g and objLGRR_g and  
             ' objLSelected_g  
             '-----------------------------------------------------------------  
             FindNetworkComponentInst objSchRoot  
  
             Set objLNetWork = objSchBaseFact.CreateNetwork (objLCntbl_g, _  
               objLGRR_g)  
    ...  
---  
  
A network object member in the output list: objLNetwork implements the SchMovable interface. This interface provides the Translate method to move all the members in the network accounting for the connectivity.

    ...  
       intNbNet = objLNetWork.Count  
    ...  
       If ( intNbNet > 0 ) Then    
          Set objSchNet = objLNetWork.Item (1,"CATIASchMovable")  
  
          If ( Not ( objSchNet Is Nothing ) ) Then  
             '-----------------------------------------------------------------  
             '  Translate the first network by (50.0, 0.0)  
             '-----------------------------------------------------------------  
             objSchNet.Translate Db2Vector  
    ...  
---  
  
#### Scaling a Schematic component that is connected to other objects

The SchMovable interface provides the ScaledSelectedObjects method to scale a component that is part of the network. This method also requires a list of "selected" component as input. "Selected" components are those that are found explicitly by FindNetworkComponentInst (through naming convention in this use case) and **not** those that are inferred from the network analysis done by the CreateNetwork method.

    ...  
             '-----------------------------------------------------------------  
             '  Scale a component (the one with "_Scale" in its name) that is in  
             '  the network. Objects directly connected to this component will  
             '  be adjusted according until a route is reached. The latter will  
             '  be "reshaped".  
             '  objLSelected_g is set in FindNetworkComponentInst  
             '-----------------------------------------------------------------  
             Dim intSelected As Integer  
             intSelected = objLSelected_g.Count  
             If ( intSelected > 0 ) Then    
                objSchNet.ScaleSelectedObjects objLSelected_g, DbScaleFactor  
    ...  
---  
  
[Top]

* * *

#### In Short

This use case shows how to transform a Schematic network object. A message logging the status of the critical steps is displayed at the end of the use case.

![](images/CAASchNetworkTransf_02.jpg)

[Top]

* * *

#### References

[1] | [ Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.htm)  
---|---  
|   
[Top]  
  
* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
