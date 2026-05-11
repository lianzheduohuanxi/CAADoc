---
title: "Creating a Schematic Route between two Schematic Equipments"
category: "general"
module: "CAAScdSchUseCases"
tags: ["CAASCH_RouteBetween2Equip", "CAADoc", "CAASchRouteBetween2Equip", "CATIAProduct", "CAAScdSchUseCases", "CATIASchGRRComp", "CATIA", "CAASchAppBase", "CAASCHEDUApp", "CAASCHEDUConnector", "CATIASchGRR", "CAASCHEDUFuncString", "CATIASchCompatible", "CAASchPlatformModeler", "CATIASchCompGraphic", "CAASchAppUtilities"]
source_file: "Doc\online\CAAScdSchUseCases\CAASchRouteBetween2Equip.htm"
converted: "2026-05-11T17:31:51.486843"
---

## Schematics Platform Modeler

| 

## Creating a Schematic Route between two Schematic Equipments  
  
---|---  
  
* * *

![](../CAAScrBase/images/atarget.gif) | This macro shows you how to create a Schematic route between two Schematic component instances. The ends of the route are then connected to a connector to each of the component instance. Through special naming convention, the macro knows how to identity the two component instances to use for routing. The Schematic component instances with the word "_RouteFrom" or the word "_RouteTo" embedded in their instance names will be used. ![](images/CAASchRouteBetween2Equip_01.jpg)  
---|---  
![](../CAAScrBase/images/ainfo.gif) | CAASchRouteBetween2Equip is launched in CATIA [1]. No open document is needed.Special environment must be available to successfully run this macro:

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


[ CAASchRouteBetween2Equip.CATScript ](CAASchRouteBetween2EquipSource.htm)is located in the CAAScdSchUseCases module. [Execute macro](macros/CAASchRouteBetween2Equip.CATScript) (Windows only).  
![](../CAAScrBase/images/ascenari.gif) | CAASchRouteBetween2Equip includes the following steps:

  1. Prolog
  2. Find the two Schematic component instances to route between.
  3. Create a Schematic Route connecting to the two Schematic Component instances.



#### Prolog

The macro first loads the CAASCH_RouteBetween2Equip.CATProduct document. |     ...  
    ' Open the schematic document   
    Dim sFilePath  
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _  
            "online\CAAScdSchUseCases\samples\CAASCH_RouteBetween2Equip.CATProduct")  
  
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
  
#### Find the two Schematic component instances to route between

This macro provides the internal Find2ComponentInst subroutine to find the Schematic component instance to start the route with and the Schematic component instance to end the route with.

Find2ComponentInst uses the GetComponents method to obtain a list of all the Schematic component instances in the document.

    ...  
' -----------------------------------------------------------------------------  
' | Find 2 components and their images. The user need to designate specific  
' | specific component instances by naming them specially.  
' | From - component : should have "_Routefrom" embedded in the name  
' | To - component : should have "_Routeto" embedded in the name  
' |  
' | Input: objSchRootArg:  the root of the document.  
' | Returns: objLCompat_g: a list of component instance objects  
' |          objLGRRComp_g: a list of component instance image objects  
' -----------------------------------------------------------------------------  
Private Sub Find2ComponentInst (objSchRootArg As SchematicRoot)  
  
    ...  
      Set objLCompInst = objSchRootArg.GetComponents  
    ...  
---  
  
Then it searches for two components that match the name requirement. Notice that when looping through each member in the component instance list, the macro uses the method GetInterface to get two specific interface on the same member object.

  1. SchCompatible - to be use latter in the route.
  2. Product - for the Name method. The macro uses this method to obtain the name of the current instance so that it can match it with "_Routeto" and "_Routetrom"

    ...  
      For intIndex = 1 To intNbComp  
  
        strInstName = ""  
        intFound = 0  
  
        Set objCompCompat = objLCompInst.Item (intIndex,"CATIASchCompatible")  
  
        If ( Not ( objCompCompat Is Nothing ) ) Then  
  
           Set objPrd = objSchRootArg.GetInterface ( _  
             "CATIAProduct", objCompCompat)  
  
           If ( Not ( objPrd Is Nothing ) ) Then  
              strInstName = objPrd.Name  
              intFound  = Instr (1, strInstName, strTgtFrom, 1)   
              If ( intFound < 1 ) Then  
                 intFound  = Instr (1, strInstName, strTgtTo, 1)   
                 intStoreIndex = 2  
              Else  
                 intStoreIndex = 1  
              End If     
           End If    
    ...  
---  
  
If a match is found, the interface SchCompatible interface handle will be stored in a local variable: objCompCompatFrom or objCompCompatTo. The macro also uses the internal GetComponentImage function to find the graphical image of the current instance. The function returns a SchCompGraphic handle which will be store in the local variable: objSchCompGraph.

The loop exists when intNbFound is two.

    ...  
           If ( intFound > 0 ) Then  
  
             Dim ObjSchCompGraph As SchCompGraphic  
             Set objSchCompGraph = objSchRootArg.GetInterface ( _  
               "CATIASchCompGraphic",objCompCompat)  
             Set objGRRComp = GetComponentImage (objSchCompGraph)  
  
             If ( ( Not objGRRComp Is Nothing ) ) Then  
                If ( intStoreIndex = 1 ) Then  
                  Set objCompCompatFrom = objCompCompat  
                  Set objGRRCompFrom = objGRRComp  
                Else  
                  Set objCompCompatTo = objCompCompat  
                  Set objGRRCompTo = objGRRComp  
                End If    
                intNbFound  = intNbFound + 1  
             End If    
           End If  
  
           If ( intNbFound > 1 ) Then  Exit For             
  
        End If '--- If ( Not ( objCompCompat Is Nothing ) ...  
  
      Next  
---  
  
The local varaibles are stored in two global lists which are accessible to the main subroutine.

  1. objLCompat_g - for the list of SchCompat handles of the "RouteFrom" and the "RouteTo" component instances.
  2. objLGRRComp_g - for the list of GRRComp handles for the corresponding members in the objLCompat_g list.

      If ( Not ( objCompCompatFrom Is Nothing ) And _  
           Not ( objGRRCompFrom Is Nothing ) ) Then  
  
         objLCompat_g.Append objCompCompatFrom  
         objLGRRComp_g.Append objGRRCompFrom  
  
      End If   
  
      If ( Not ( objCompCompatTo Is Nothing ) And _  
           Not ( objGRRCompTo Is Nothing ) ) Then  
  
         objLCompat_g.Append objCompCompatTo  
         objLGRRComp_g.Append objGRRCompTo  
  
      End If   
    ...  
---  
  
#### Create a Schematic Route connecting to the two Schematic Component instances

This macro provides the internal RouteLineBetween2Component subroutine to create the Schematic route. Two global lists populated in previous steps are accessible to this subroutine. They are the objLCompat_g and the objLGRRComp_g lists. Each member is that list is used for calling the following methods.

  1. IsTargetOKForRoute - checks whether the component instance is compatible with the type of Schematic route to make a connection. In type is specified by the connector type at the end of the route. In this case, it the "CAASCHEDUConnector".
  2. GetBestCntrForRoute - returns the x-y coordinates of the position of a connector that the route can connect to. The position is used as the start or the end point of the Schematic route. This position is based on an input point. The position of the connector closest to the input point will be returned.

    ...  
   For intIndex = 1 To 2  
  
      Set objCompCompat = objLCompat_g.Item (intIndex,"CATIASchCompatible")  
      Set objGRRComp = objLGRRComp_g.Item (intIndex,"CATIASchGRRComp")  
  
    ...  
  
      If ( Not ( objGRRComp Is Nothing ) And _  
           Not ( objCompCompat Is Nothing ) ) Then  
  
         '---------------------------------------------------------------------  
         '  IsTargetOKRoute returns a list of compatible connectors  
         '  on the target component is the component is compatible to  
         '  to connected to the start point of the route.  
         '---------------------------------------------------------------------  
         objCompCompat.IsTargetOKForRoute "CAASCHEDUConnector", _  
           objGRRComp, objLCntrs, bCompatible  
  
         Set objSchGRR = objSchRootArg.GetInterface ("CATIASchGRR",objGRRComp)   
  
         If ( Not ( objLCntrs Is Nothing ) And  _  
              Not ( objSchGRR Is Nothing ) And bCompatible ) Then  
  
            If ( intIndex = 1 ) Then  
               db2SelectPt(0) = 62.0  
               db2SelectPt(1) = 62.0  
            Else   
               db2SelectPt(0) = 170.0  
               db2SelectPt(1) = 100.0  
            End If    
  
            '------------------------------------------------------------------  
            '  GetBestCntrForRoute returns a connector from  
            '  the output list that is closest    
            '  to a user selection point.  
            '------------------------------------------------------------------  
            objCompCompat.GetBestCntrForRoute db2SelectPt, _  
              objSchGRR, objLCntrs, objLDbOut, objAppCntrBest  
     
            IntNbCoord = objLDbOut.Count  
            If (IntNbCoord > 1) Then  
              db2CntrPt(0) = objLDbOut.Item(1)  
              db2CntrPt(1) = objLDbOut.Item(2)  
  
              If ( intIndex = 1 ) Then  
                 db2CntrPt1(0) =  db2CntrPt(0)  
                 db2CntrPt1(1) =  db2CntrPt(1)  
                 Set objAppCntrCompBest1 = objAppCntrBest  
  
    ...  
              Else  
                 db2CntrPt2(0) =  db2CntrPt(0)  
                 db2CntrPt2(1) =  db2CntrPt(1)  
    ...  
                 Set objAppCntrCompBest2 = objAppCntrBest  
              End If    
            End If '--- If (IntNbCoord > 1) Then  
  
         End If '--- If ( Not ( objLCntrs Is Nothing ) And  _  
      End If '--- If ( Not ( objGRRComp Is Nothing ) ...  
   Next '--- For intIndex  
---  
  
The beginning and the ending route points of the Schematic routes are the connector positions from above. The macro uses the AppCreateRoute to create an application specific route object, this is an input to the next method to be called. Next, the method CreateSchRouteByPoints is used to create the Schematic Route.

    ...  
   dbPtArray(0) = db2CntrPt1(0)  
   dbPtArray(1) = db2CntrPt1(1)  
  
   dbPtArray(2) = (db2CntrPt1(0) + db2CntrPt2(0)) * 0.5  
   dbPtArray(3) = db2CntrPt1(1)  
  
   dbPtArray(4) = dbPtArray(2)  
   dbPtArray(5) = db2CntrPt2(1)  
  
   dbPtArray(6) = db2CntrPt2(0)  
   dbPtArray(7) = db2CntrPt2(1)  
  
   '---------------------------------------------------------------------------  
   ' Ask application to create a route reference  
   '---------------------------------------------------------------------------  
   strLogLineID = "U1-P101-2in-CS150R-FG"  
  
   objAppObjFact.AppCreateRoute "CAASCHEDUFuncString", _  
     objAppRouteRef, strLogLineID        
  
   If ( Not ( objAppRouteRef Is Nothing ) ) Then  
   ...  
  
     objSchBaseFact.CreateSchRouteByPoints objAppRouteRef, _  
       dbPtArray, objSchRoute    
  
    ...  
---  
  
The macro provides the internal FindConnectorAtPosition function to return an interface handle on the connectors at each ends of the newly created Schematic route. 

    ...  
       '-----------------------------------------------------------------------  
       ' Find the connector of the route matching the    
       ' component connector position at each end  
       '-----------------------------------------------------------------------  
  
       Set objAppCntrRouteBest1 = FindConnectorAtPosition ( _  
         db2CntrPt1(0), db2CntrPt1(1), objRouteCntbl, objSchRootArg)  
  
       Set objAppCntrRouteBest2 = FindConnectorAtPosition ( _  
         db2CntrPt2(0), db2CntrPt2(1), objRouteCntbl, objSchRootArg)  
    ...  
---  
  
Finally, the macro uses the AppConnect method to connect the newly created route instance to the two existing component instances through their connectors.

    ...  
          Set objAppConnection = objAppCntrCompBest1.AppConnect _  
            (objAppCntrRouteBest1)  
    ...  
---  
  
[Top]

* * *

#### In Short

This use case shows how to create a Schematic route between two Schematic component instances. A message logging the status of the critical steps is displayed at the end of the use case.

![](images/CAASchRouteBetween2Equip_02.jpg)

[Top]

* * *

#### References

[1] | [ Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.htm)  
---|---  
|   
[Top]  
  
* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
