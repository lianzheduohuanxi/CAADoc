---
```vbscript
title: "Building a Schematic Reference Component"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAADoc", "CAASchPlatformModeler", "CAASchAppObjFactory", "CATIASchCompConnector", "CAASCHEDUCompressFunc", "CAAScdSchUseCases", "CAASCHEDU_SamplePID", "CAASCHEDUFuncString", "CATIA", "CAASchAppBase", "CAASCHEDUApp", "CAASCHEDUConnector", "CATIASchGRR", "CATIASchCompatible", "CAASCH_Detail01", "CATIASchComponent2", "CAASchAppUtilities"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchAppObjFactory.htmmd"
converted: "2026-05-11T17:31:51.312764"
```

---
## Schematics Platform Modeler

|
## Building a Schematic Reference Component

* * *

 This macro shows you how to build a schematic reference component. Instances of this reference component can then be placed in design documents.This macro opens the document CAASCH_Detail01.CATProduct that contains three component symbols. One of the symbols will be used as the graphical representation of the reference component to be built. Two connectors will also be added to the reference component.  To illustrate the usage of this reference component, an instance of this reference will be placed in the design document and a schematic route will be created connected to the connector in the component instance, which is inherited from the reference.
---|---
 CAASchAppObjFactory is launched in CATIA [1]. No open document is needed.Special environment must be available to successfully run this macro:

  * Prerequisites:

>   1. RADE must be installed.
>   2. CAASchPlatformModeler.edu must exist in CAADoc folder.
>

  * Setup:

>   1. Build CAASchAppBase.m and CAASchAppUtilities.m, located in CAASchPlatformModeler.edu (RADE is required).
>   2. Copy generated DLLs, CAASchAppBase.dll and CAASchAppUtilities.m, respectively, to the run-time environment folder "intel_a/code/bin."
>   3. Copy CAASCHEDUApp.CATfct, located CAASchPlatformModeler.edu/CNext/resources/graphic, to the run-time environment folder "intel_a/resources/graphic."
>   4. Copy CAASchPlatformModeler.edu/CNext/code/dictionary/CAASchPlatformModeler.edu.dico to the run-time environment folder "intel_a/code/dictionary."
>

[CAASchAppObjFactory.CATScript](CAASchAppObjFactorySource.md) is located in the CAAScdSchUseCases module. [Execute macro](macros/CAASchAppObjFactory.CATScript) (Windows only).
 CAASchAppObjFactory includes the following steps:

CAASchAppObjFactory includes the following steps:
  1. Prolog
  2. Create a schematic reference component
  3. Add two connectors to the reference component
  4. Place an instance of the reference component
  5. Create a schematic route instance
  6. Connect the route instance to the component instance

#### Prolog

5. Create a schematic route instance
6. Connect the route instance to the component instance
The macro first loads CAASCH_Detail01.CATProduct that contains 3 schematic component symbols. ![](images/CAASchAppObjFactory_01.jpg) |     ...
```vbscript
```vbscript
    ' Open the schematic document

```

```

```vbscript
```vbscript
    Dim sFilePath
```vbscript
```
```vbscript
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```
```

```

            "online/CAAScdSchUseCases/samples/CAASCH_Detail01.CATProduct")

```vbscript
```vbscript
Dim sFilePath
```vbscript
```
```vbscript
```vbscript
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
    Dim objSchDoc As Document
    Set objSchDoc = CATIA.Documents.Open(sFilePath)
```
```

```

```

    ...

---

Next, the macro acquires the schematic root object from the document. The schematic root is the top node of the object instance tree in a schematic document.

    ...
Next, the macro acquires the schematic root object from the document. The schematic root is the top node of the object instance tree in a schematic document.
```vbscript
```vbscript
    ' Find the top node of the schematic object tree - schematic root.

```

```

```vbscript
```vbscript
    Dim objPrdRoot As Product
```vbscript
```
```vbscript
```vbscript
    Dim objSchRoot As SchematicRoot
    If ( Not ( objSchDoc Is Nothing ) ) Then
```
```vbscript
      Set objPrdRoot = objSchDoc.Product
      If ( Not ( objPrdRoot Is Nothing ) ) Then
```
```vbscript
        Set objSchRoot = objPrdRoot.GetTechnologicalObject("SchematicRoot")
      End If
```
    End If
```

```

```

    ...

---

From this schematic root object the following factory objects can be obtained.

From this schematic root object the following factory objects can be obtained.
  1. Application object factory (in this case the application is "CAASCHEDU_SamplePID") creates application objects independent of the Schematic platform.
  2. Schematic base object factory. This factory creates the schematic extensions and associates them to application objects.
  3. Schematic temporary list factory. This factory creates various kinds of lists that are not persistent. They are only available in the current session and are not saved in the model.

    ...
```vbscript
```vbscript
    Dim objAppObjFact As SchAppObjectFactory
```vbscript
```
```vbscript
```vbscript
    Dim objSchBaseFact As SchBaseFactory
    Dim objSchTempListFact As SchTempListFactory

```
```

```

```

```vbscript
    If ( Not ( objSchRoot Is Nothing ) ) Then
```

```vbscript
```vbscript
```vbscript
       '-----------------------------------------------------------------------
       ' Get all the necessary factories.
       '-----------------------------------------------------------------------
```vbscript
       Set objAppObjFact = objSchRoot.GetApplObjFactFromVirtualType ("CAASCHEDU_SamplePID")
       Set objSchBaseFact = objSchRoot.GetSchBaseFactory
       Set objSchTempListFact = objSchRoot.GetTemporaryListFactory
```
```

```

```

    ...

---
#### Creating a schematic reference component

The macro calls the AppCreateCompRef method to create an application reference object. In this use case, the "CAASCHEDU_SamplePID" sample application implements this method to create the appropriate object that suits its needs. The schematic platform is totally transparent to how the application does this.

    ...
```vbscript
```vbscript
```vbscript
         '---------------------------------------------------------------------
         ' Ask application to create a component reference
         '---------------------------------------------------------------------
```

```

```

```vbscript
```vbscript
```vbscript
'---------------------------------------------------------------------
' Ask application to create a component reference
'---------------------------------------------------------------------
```

```

         objAppObjFact.AppCreateCompRef "CAASCHEDUCompressFunc", _
           objAppCompRef
```

    ...
---

objAppObjFact.AppCreateCompRef "CAASCHEDUCompressFunc", _
objAppCompRef
A graphical representation (a symbol) is needed to define a schematic reference component. The macro searches the model to find an appropriate one by calling the method GetComponentSymbol. An appropriate symbol is the one that has not been associated to any schematic component.

    ...
```vbscript
```vbscript
```vbscript
           '---------------------------------------------------------------------
           ' Find a unassociated component symbol in the document
           '---------------------------------------------------------------------
```

```

```

```vbscript
```vbscript
           Set objSchSymbol = GetComponentSymbol (objSchRoot)
```
```

    ...

---

Next, after successfully obtaining the application object and the graphical representation, the marco calls the CreateSchComponent method to create and to associate a schematic component extension to the application object. This method is implemented by the Schematic Platform.

Note that, a temporary list of object is created to contain the graphic representation. This list is input (the second argument) to the function CreateSchComponent.

    ...
```vbscript
           If ( Not ( objSchSymbol Is Nothing ) ) Then
```

```vbscript
```vbscript
              Set objSchListGRR = objSchTempListFact.CreateListOfObjects
```vbscript
```
              If ( Not ( objSchListGRR Is Nothing ) ) Then
```

                 objSchListGRR.Append objSchSymbol
```vbscript
                 Set objSchCompRef = objSchBaseFact.CreateSchComponent ( _
                   objAppCompRef, objSchListGRR)
```
```

    ...

---
#### Add two connectors to the reference component

To add connectors to the reference component just created, we need a different interface ("CATIASchCompConnector") on the reference component class. Given a different interface handle (on the same reference component) objAppCompRef, we can obtain the necessary interface handle by using the GetInterface method. This method is implemented on the schematic root object class.

To add connectors to the reference component just created, we need a different interface ("CATIASchCompConnector") on the reference component class. Given a different interface handle (on the same reference component) objAppCompRef, we can obtain the necessary interface handle by using the GetInterface method. This method is implemented on the schematic root object class.
The following data needs to be defined when creating a connector.

  1. The x-y coordinates of the connector position with respect to the axis of the symbol.
  2. The x-y coordinates of the connector alignment vector with respect to the axis of the symbol.

    ...
```vbscript
```vbscript
```vbscript
           '---------------------------------------------------------------------
           ' Add two connectors to the reference component
           '---------------------------------------------------------------------
```

```

```

```vbscript
```vbscript
           Dim objSchCntr As SchCompConnector
```vbscript
```
```vbscript
```vbscript
           Dim objSchAppCntr As SchAppConnector
           Dim objSchCntrLoc As SchCntrLocation

           Set objSchCntr = objSchRoot.GetInterface ("CATIASchCompConnector", _
```
```

```

             objSchCompRef)

```

```vbscript
```vbscript
           If ( Not ( objSchCntr Is Nothing ) ) Then

```vbscript
              Dim iCntr As Integer
```
```

```vbscript
```vbscript
```vbscript
              Dim db2CntrPos (2) As CATSafeArrayVariant
              Dim db2CntrVec (2) As CATSafeArrayVariant

```
```

```

```

```vbscript
              For iCntr = 1 To 2
```vbscript
```vbscript
                Set objSchCntrLoc = Nothing
```
```

```

```vbscript
```vbscript
```vbscript
                '-------------------------------------------------------------
                ' connector position and alignment vector are in coordinates
                ' relative the origin of the reference component graphical
                ' representation (the detail axis).
                '-------------------------------------------------------------
                If ( iCntr = 1 ) Then
```

```

```

```vbscript
```vbscript
```vbscript
' representation (the detail axis).
'-------------------------------------------------------------
If ( iCntr = 1 ) Then
```

                   db2CntrPos(0) = 30.0
                   db2CntrPos(1) = 10.0
                   db2CntrVec(0) = 1.0
                   db2CntrVec(1) = 0.0
```

                Else
                   db2CntrPos(0) = -30.0
```vbscript
                   db2CntrPos(1) = 10.0
                   db2CntrVec(0) = -1.0
                   db2CntrVec(1) = 0.0
```vbscript
                End If

```

```

```

```vbscript
db2CntrVec(1) = 0.0
```vbscript
End If
```

                objSchCntr.AddConnector "Piping_Connector", objSchSymbol, _
                  Db2CntrPos, objSchAppCntr

```

    ...

---
#### Place an instance of the schematic reference component in the current document

To create an instance in a specific document, we need to use the PlaceInSpace method of the interface CATIASchComponent2. We can obtain this interface from the schematic reference object through the GetInterface method.

We also need to specify the positioning matrix for the graphical representation of the component instance. This matrix consists of six real numbers (double). The first four numbers defines the axes (x-axis and y-axis) and the last two numbers defines the x-y position of the symbol instance.

    ...
```vbscript
```vbscript
```vbscript
           '-------------------------------------------------------------------
           ' Place an instance of reference just created in an empty space in
           ' the design document
           ' Note that the target document is an input to PlaceInSpace
           '-------------------------------------------------------------------
           '-------------------------------------------------------------------
           ' Component instance (to be created below) orientation matrix.
           ' x-axis = (1.0,0.0)
           ' y-axis = (0.0,1.0)
           ' origin = (100.0,100.0)
           '-------------------------------------------------------------------
```

```

```

```vbscript
```vbscript
           Dim db6Matrix(6) As CATSafeArrayVariant
```vbscript
```
           db6Matrix(0)=1.0
           db6Matrix(1)=0.0
           db6Matrix(2)=0.0
           db6Matrix(3)=1.0
           db6Matrix(4)=100.0
           db6Matrix(5)=100.0

```vbscript
           Set objSchComp2Ref = objSchRoot.GetInterface ( _
```
```

```

             "CATIASchComponent2",objAppCompRef)

```vbscript
```vbscript
           If ( Not ( objSchComp2Ref Is Nothing ) ) Then

```

```

```vbscript
If ( Not ( objSchComp2Ref Is Nothing ) ) Then
              objSchComp2Ref.PlaceInSpace objSchSymbol,db6Matrix, _
                objSchDoc,objSchCompInst
```

    ...

---
#### Create a schematic route instance

To create a schematic route instance we need to specify the x-y coordinates of all the points defining the segments of the route path (a polyline). In this use case, the macro will find a position that matches one of the connector position in the schematic component instance we have just created in previous step, and will use that to define the first point of the route.

To create a schematic route instance we need to specify the x-y coordinates of all the points defining the segments of the route path (a polyline). In this use case, the macro will find a position that matches one of the connector position in the schematic component instance we have just created in previous step, and will use that to define the first point of the route.
Given a schematic component instance, we can obtain the CATIASchCompatible interface from it. This interface can be used to check whether this component instance can be connected to a specific type of schematic route. In this use case, the type of the route to be created is one that includes a "CAASCHEDUConnector" at each of its two ends.

IsTargetOKForRoute is called for the checking. It returns a flag bCompatible and if this flag is TRUE, then the route we are going to create is compatible with the component instance and can be connected to it. It also returns a list of compatible connectors of the component instance that can be used in the next call GetBestCntrForRoute. This call returns a handle on a connector (of the component instance). The x-y coordinates of the position of this connector defines the first route points.

    ...
```vbscript
```vbscript
            Set objSchCompCompat = objSchRoot.GetInterface ( _
```
```

             "CATIASchCompatible",objSchCompInst)

```vbscript
            If ( Not ( objSchCompCompat Is Nothing ) And _
```vbscript
                 Not ( objSchGRRCompInst Is Nothing ) ) Then

```

```

```vbscript
If ( Not ( objSchCompCompat Is Nothing ) And _
```

Not ( objSchGRRCompInst Is Nothing ) ) Then
               objSchCompCompat.IsTargetOKForRoute "CAASCHEDUConnector", _
                  objSchGRRCompInst, objLCntrs, bCompatible

```vbscript
```vbscript
```vbscript
               '---------------------------------------------------------------
               '  IsTargetOKRoute returns a list of compatible connectors
               '  on the target component if the component is compatible to
               '  be connected to the start point of the route.
               '---------------------------------------------------------------
```

```

```

```vbscript
```vbscript
               Dim objSchGRRInst As SchGRR
```vbscript
```
```vbscript
```vbscript
               Dim objAppCntrCompBest As SchAppConnector
               Dim objLDbOut As SchListOfDoubles
               Dim db2SelectPt(2) As CATSafeArrayVariant

```
```

```

```

```vbscript
```vbscript
Dim objLDbOut As SchListOfDoubles
```vbscript
```
```vbscript
Dim db2SelectPt(2) As CATSafeArrayVariant
               db2SelectPt(0) = 130.0
```
               db2SelectPt(1) = 110.0

```

```

```vbscript
```vbscript
               Set objSchGRRInst = objSchRoot.GetInterface ( _
```
```

                 "CATIASchGRR",objSchGRRCompInst)

```vbscript
               If ( Not ( objLCntrs Is Nothing ) And  _
```vbscript
                    Not ( objSchGRRInst Is Nothing ) And bCompatible ) Then
```

```

```vbscript
```vbscript
```vbscript
                  '------------------------------------------------------------
                  '  GetBestCntrForRoute returns a connector from
                  '  the output list that is closest
                  '  to a user selection point.
                  '------------------------------------------------------------
```

```

```

```vbscript
```vbscript
```vbscript
'  the output list that is closest
'  to a user selection point.
'------------------------------------------------------------
```

```

                  objSchCompCompat.GetBestCntrForRoute db2SelectPt, _
                    objSchGRRInst, objLCntrs, objLDbOut, objAppCntrCompBest
```

    ...

---

The macro calls the AppCreateRoute method to create an application route instance. In this use case, the P&ID application implements this method to create the appropriate object that suits its needs. The schematic platform is totally transparent to how the application does this.

Method CreateSchRouteByPoints is called to create and to associate a schematic route instance to the application object. Note that an array of doubles specifying the x-y coordinates of the route points is input to the method. The first two doubles in the array is an output of the previous call.

    ...
The macro calls the AppCreateRoute method to create an application route instance. In this use case, the P&ID application implements this method to create the appropriate object that suits its needs. The schematic platform is totally transparent to how the application does this.
Method CreateSchRouteByPoints is called to create and to associate a schematic route instance to the application object. Note that an array of doubles specifying the x-y coordinates of the route points is input to the method. The first two doubles in the array is an output of the previous call.
                  dbPtArray(0) = 0.0
```vbscript
                  dbPtArray(1) = 0.0

```

                  IntNbCoord = objLDbOut.Count

```vbscript
                  If (IntNbCoord > 1) Then
```vbscript
                    dbPtArray(0) = objLDbOut.Item(1)
                    dbPtArray(1) = objLDbOut.Item(2)
```

```

    ...
```vbscript
If (IntNbCoord > 1) Then
```

dbPtArray(0) = objLDbOut.Item(1)
```vbscript
dbPtArray(1) = objLDbOut.Item(2)
```

                  objAppObjFact.AppCreateRoute "CAASCHEDUFuncString", _
                    objAppRouteRef, strLogLineID

```vbscript
                  If ( Not ( objAppCompRef Is Nothing ) ) Then
                    strMessage = strMessage &  _
```

                      "application reference route created" & vbCr

strMessage = strMessage &  _
                    objSchBaseFact.CreateSchRouteByPoints objAppRouteRef, _
                      dbPtArray, objSchRoute

    ...
---
#### Connect the route instance to the component instance

The newly created route instance is connected to the component instance via their connectors.

    ...
```vbscript
```vbscript
```vbscript
                         '-----------------------------------------------------
                         ' Connect "Connector A" to "Connector B"
                         '-----------------------------------------------------
```

```

```

```vbscript
```vbscript
                         Set objAppConnection = objAppCntrCompBest.AppConnect _
                           (objAppCntrRouteBest)
```
```

    ...

---

[Top]

* * *
#### In Short

This use case shows how to build a schematic component reference with connectors. In addition, it shows how to create an instance of the reference. A message logging the status of the critical steps is displayed at the end of the use case.

![](images/CAASchAppObjFactory_02.jpg)

[Top]

* * *
#### References

[1] | [ Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
