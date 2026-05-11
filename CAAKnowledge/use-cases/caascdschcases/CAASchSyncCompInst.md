---
title: "Synchronizing component instances with the catalog reference"
category: "general"
module: "CAAScdSchUseCases"
tags: ["CAASchSyncCompInst", "CATIASchComponent", "CAASCH_SyncCompInst", "CAAScdSchUseCases", "CATIA", "CATIASchUpdateInstances"]
source_file: "Doc\online\CAAScdSchUseCases\CAASchSyncCompInst.htm"
converted: "2026-05-11T17:31:51.502797"
---

## Schematics Platform Modeler

| 

## Synchronizing component instances with the catalog reference  
  
---|---  
  
* * *

![](../CAAScrBase/images/atarget.gif) | This macro shows you how to update component instances after the changes in the corresponding catalog reference. The update of the component instances in the document is done through the corresponding local reference component.As a result of the update, both the local reference and all the component instances are synchronized with the corresponding reference component in the catalog. This macro opens the CAASCH_SyncCompInst.CATProduct document.  
---|---  
![](../CAAScrBase/images/ainfo.gif) | CAASchSyncCompInst is launched in CATIA [1]. No open document is needed.[CAASchSyncCompInst.CATScript ](CAASchSyncCompInstSource.htm)is located in the CAAScdSchUseCases module. [Execute macro](macros/CAASchSyncCompInst.CATScript) (Windows only).  
![](../CAAScrBase/images/ascenari.gif) | CAASchSyncCompInst includes the following steps:

  1. Prolog
  2. Update component instances



#### Prolog

The macro first loads CAASCH_SyncCompInst.CATProduct. |     ' Open the schematic document  
    Dim sFilePath  
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _  
            "online\CAAScdSchUseCases\samples\CAASCH_SyncCompInst.CATProduct")  
  
    Dim objSchDoc As Document  
    Set objSchDoc = CATIA.Documents.Open(sFilePath)   
---  
  
Next, the macro acquires the schematic root object from the document. The schematic root is the top node of the object instance tree in a schematic document.

    ' Find the top node of the schematic object tree - schematic root.  
    Dim objPrdRoot As Product  
    Dim objSchRoot As SchematicRoot  
    If ( Not ( objSchDoc Is Nothing ) ) Then  
      Set objPrdRoot = objSchDoc.Product   
      If ( Not ( objPrdRoot Is Nothing ) ) Then  
        Set objSchRoot = objPrdRoot.GetTechnologicalObject("SchematicRoot")  
      End If  
    End If  
---  
  
Then, the SchUpdateInstances interface is requested on the schematic root. This interface provides a method for updating component instances.

    ' Get SchUpdateInstances interface on the schematic root.   
    Dim objUpdateInstancesAs SchUpdateInstances  
  
    If ( Not ( objSchRoot Is Nothing ) ) Then  
       Set objUpdateInstances = objSchRoot.GetInterface ("CATIASchUpdateInstances",objSchRoot)   
    End If  
---  
  
The SchematicRoot interface provides the GetRefComponents method to find a list of all the Schematic eference components in the model. The macro takes the first one in the list and specifically requests for the SchComponent interface.

    ' Find a list of reference component in the model  
    Dim objLCompRefsAs SchListOfObjects  
    Dim objCompRefAs SchComponent  
    If ( Not ( objSchRoot Is Nothing ) ) Then  
       Set objLCompRefs = objSchRoot.GetRefComponents  
  
       ' Get the first reference component    
       If ( Not ( objLCompRefs Is Nothing ) )Then  
          Set objCompRef = objLCompRefs.Item (1,"CATIASchComponent")  
       End If  
    End If    
---  
  
#### Update component instances

The macro calls UpdateAllInstancesFromReference method of SchUpdateInstance interface to update all the component instances for the specified reference component.

    ' Synchronize component instances of the first reference component   
    If ( Not ( objCompRef Is Nothing ) And _  
         Not ( objUpdateInstances Is Nothing ) )Then  
  
       objUpdateInstances.UpdateAllInstancesFromReference objCompRef  
  
    End If '--- If ( Not ( objCompRef Is Nothing )  
---  
  
[Top]

* * *

#### In Short

This use case shows how to update component instances after the changes in the corresponding catalog reference. A message logging the status of the critical steps is displayed at the end of the use case.

![](images/CAASchSyncCompInst_01.jpg)

[Top]

* * *

#### References

[1] | [ Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.htm)  
---|---  
|   
[Top]  
  
* * *

_Copyright 2007, Dassault Systmes. All rights reserved._
