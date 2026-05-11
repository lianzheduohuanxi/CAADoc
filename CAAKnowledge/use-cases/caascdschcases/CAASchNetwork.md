---
title: "Creating a Schematic Network Object"
category: "general"
module: "CAAScdSchUseCases"
tags: ["CAADoc", "CATIAProduct", "CATIASchNetworkAnalysis", "CAAScdSchUseCases", "CATIA", "CAASchAppBase", "CAASCHEDUApp", "CAASchNetwork", "CAASchPlatformModeler", "CAASCH_Network01", "CAASchAppUtilities"]
source_file: "Doc\online\CAAScdSchUseCases\CAASchNetwork.htm"
converted: "2026-05-11T17:31:51.405039"
---

## Schematics Platform Modeler

| 

## Creating a Schematic Network Object  
  
---|---  
  
* * *

![](../CAAScrBase/images/atarget.gif) | This macro shows you how to create a schematic network object.Given a list of independent objects, this macros shows how to create a Schematic network for each member in the list. The network will include the member itself and all the objects that are connected to it. This macro opens the CAASCH_Network01.CATProduct document. ![](images/CAASchNetwork_01.jpg) Through special naming convention (i.e. the word "network" embedded in the instance name), the macro knows to include the following Schematic component instances in the input list.

  1. V-082_network_scale_instance.
  2. V_084_network instance (the control valve in the screen shot).

  
---|---  
![](../CAAScrBase/images/ainfo.gif) | CAASchNetwork is launched in CATIA [1]. No open document is needed.Special environment must be available to successfully run this macro:

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


[ CAASchNetwork.CATScript ](CAASchNetworkSource.htm)is located in the CAAScdSchUseCases module. [Execute macro](macros/CAASchNetwork.CATScript) (Windows only).  
![](../CAAScrBase/images/ascenari.gif) | CAASchNetwork includes the following steps:

  1. Prolog
  2. Create a list of network objects using the SchBaseFactory interface
  3. Query the member of the list of network objects



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
  
#### Create a list of network objects using the SchBaseFactory interface

The macro calls the GetSchBaseFactory method to get a handle of the SchBaseFactory interface.

This macro provides a private Find2ComponentInst function which searches for 2 component instances in the model based on a specific naming convention. Those instances which have the word "network" as parts of their instance names will be included. For each instance returned by Find2ComponentInst, the graphical image of the instance is also returned. Notice that two global variables: objLCntbl_**g** and objLGRR_**g** are used to stored these results in Find2ComponentInst. They are available to the main subroutine to be used in calling the CreateNetwork method.

    ...  
       '-----------------------------------------------------------------------  
       ' Get all the necessary factories.  
       '-----------------------------------------------------------------------  
       Set objSchBaseFact = objSchRoot.GetSchBaseFactory   
       Set objSchTempListFact = objSchRoot.GetTemporaryListFactory  
  
       If ( Not ( objSchBaseFact Is Nothing )  And _  
            Not ( objSchTempListFact Is Nothing ) ) Then  
          Set objLCntbl_g = objSchTempListFact.CreateListOfObjects  
          Set objLGRR_g = objSchTempListFact.CreateListOfObjects  
  
          If ( Not ( objLCntbl_g Is Nothing )  And _  
               Not ( objLGRR_g Is Nothing ) ) Then  
  
             '-----------------------------------------------------------------  
             ' The following "Sub" will populate objLCntbl_g and objLGRR_g  
             '-----------------------------------------------------------------  
             Find2ComponentInst objSchRoot  
  
             Set objLNetWork = objSchBaseFact.CreateNetwork (objLCntbl_g, _  
               objLGRR_g)  
    ...  
---  
  
#### Query the member of the list of network objects

Each network object in the list contains the following information.

  1. The input object itself.
  2. A list of Schematic component instances that are directly or indirectly connected to the input object. This list of connected component instances can be retrieved using the ListNetworkObjects method.
  3. The listing procedure is recursive, and it will stop when the connected object is a Schematic route. This Schematic route (known as the "extremity") will be stored in a separate list. This list of "extremity" objects can be retrieved using the ListExtremityObjects method.



The macro first find out the number of network objects in the output list. Then, for each member in the output list it does the following.

  1. Call the ListNetworkObjects method to get a list of connected Schematic component.
  2. Call the ListExtremityObjects method to get a list of extremity objects (the Schematic route objects).
  3. For each member in those lists, the macro obtain a Product interface handle to report their instance names.

    ...  
    If (  Not ( objLNetWork Is Nothing ) ) Then  
  
       Dim intNbNet As Integer  
       Dim intNetIndex As Integer  
       Dim intNbMember As Integer  
       Dim intMemIndex As Integer  
       Dim objSchNet As SchNetworkAnalysis  
       Dim objLNetMember As SchListOfObjects  
       Dim objMemPrd As Product  
       Dim strName As String  
  
       intNbNet = objLNetWork.Count  
    ...  
  
       '-----------------------------------------------------------------------  
       ' Query the network members  
       '-----------------------------------------------------------------------  
       For intNetIndex = 1 To intNbNet   
  
         intNbMember = 0  
         Set objLNetMember = Nothing  
  
         Set objSchNet = objLNetWork.Item (intNetIndex,"CATIASchNetworkAnalysis")  
  
         '---------------------------------------------------------------------  
         '  Get the members of the list of connectables.  
         '---------------------------------------------------------------------  
         If ( Not ( objSchNet Is Nothing ) ) Then  
  
            Set objLNetMember = objSchNet.ListNetworkObjects  
  
         End If    
  
         If ( Not ( objLNetMember Is Nothing ) ) Then  
  
            intNbMember = objLNetMember.Count  
  
    ...  
  
            For intMemIndex = 1 To intNbMember  
  
              Set objMemPrd = objLNetMember.Item (intMemIndex,"CATIAProduct")  
    ...  
  
            Next '--- For intMemIndex  
  
         End If '--- If ( Not ( objLNetMember Is Nothing ) ...  
  
  
         '---------------------------------------------------------------------  
         '  Get the members of the list of extremities (routes).  
         '---------------------------------------------------------------------  
         If ( Not ( objSchNet Is Nothing ) ) Then  
  
            Set objLNetMember = objSchNet.ListExtremityObjects  
  
         End If    
  
         If ( Not ( objLNetMember Is Nothing ) ) Then  
  
            intNbMember = objLNetMember.Count  
    ...  
  
            For intMemIndex = 1 To intNbMember  
  
              Set objMemPrd = objLNetMember.Item (intMemIndex,"CATIAProduct")  
              strName = ""  
    ...  
  
            Next '--- For intMemIndex  
  
         End If '--- If ( Not ( objLNetMember Is Nothing ) ...  
  
       Next '--- For intNetIndex  
    End If '--- If ( Not ( objLNetWork Is Nothing ) ...  
---  
  
[Top]

* * *

#### In Short

This use case shows how to create a Schematic network object. Furthermore, it illustrates how to get information from the network object. A message logging the status of the critical steps is displayed at the end of the use case. 

![](images/CAASchNetwork_02.jpg)

[Top]

* * *

#### References

[1] | [ Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.htm)  
---|---  
|   
[Top]  
  
* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
