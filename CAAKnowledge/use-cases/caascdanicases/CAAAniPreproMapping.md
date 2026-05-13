---
```vbscript
title: "Mapping Loads"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATISamImportDefine", "CAAScdAniUseCases", "CAAAniPreproOnPublish", "CATIA", "CAAAniPreproMapping"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreproMapping.htmmd"
converted: "2026-05-11T17:31:51.809905"
```

---
## Analysis Modeler

|
## Mapping Loads

* * *

 This macro shows you how to create an Analysis document for a generative structural analysis. With this scenario, you will cover all the steps of a generative analysis application. It creates an Analysis document, imports a Part document provided with the sample. An Analysis Case is created as for static linear analysis. Some pre-processing data are defined by using the publication defined on the part. This example will focus on the usage of mapping surface forces. For this we will use the Design table object. Then, the computation is launched. A parameter that measures the maximum value of this stress is created and its value is printed. ![](images/PreproWithMapping.jpg)
---|---
This macro shows you how to create an Analysis document for a generative structural analysis. With this scenario, you will cover all the steps of a generative analysis application. It creates an Analysis document, imports a Part document provided with the sample. An Analysis Case is created as for static linear analysis. Some pre-processing data are defined by using the publication defined on the part. This example will focus on the usage of mapping surface forces. For this we will use the Design table object. Then, the computation is launched. A parameter that measures the maximum value of this stress is created and its value is printed. ![](images/PreproWithMapping.jpg)
 CAAAniPreproOnPublish is launched in CATIA [1]. No open document is needed. [CAAAniPreproMapping.catvbs](CAAAniPreproMappingSource.md) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniPreproMapping.catvbs) (Windows only).
 CAAAniPreproOnPublish includes the following steps:

  1. Prolog
  2. Importing the Part Document and Extracting the Publication
  3. Creating an Analysis Case for Static Analysis
  4. Defining the Boundaries
  5. Defining the Load
  6. Computing the Case
  7. Defining a Sensor and Printing it's Value
  8. Epilog

#### Prolog

|

    ...

```vbscript
    ' -----------------------------------------------------------
```

```vbscript
```vbscript
```vbscript
' -----------------------------------------------------------
    ' Optional: allows to find the sample wherever it's installed

```vbscript
      sDocPath=CATIA.SystemService.Environ("CATDocView")
      sSep=CATIA.SystemService.Environ("ADL_ODT_SLASH")

```
```

```

```

```vbscript
```vbscript
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```
```

```vbscript
```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
```vbscript
```
```vbscript
        End If
    ' -----------------------------------------------------------

```

```

```

```vbscript
End If
```vbscript
```vbscript
' -----------------------------------------------------------
    ' Get the collection of documents in session
```

```

```

```vbscript
```vbscript
        Set documents1 = CATIA.Documents
```
```

```vbscript
```vbscript
```vbscript
    ' -----------------------------------------------------------
    ' Get the collection of documents in session
    ' Create the CATAnalysis Document
```vbscript
       Set TheAnalysisDocument = documents1.Add("Analysis")
    ' if WB name already is "GPSCfg", not to use StartWorkbench
```
```

```

```vbscript
       WBName = CATIA.GetWorkbenchId
       if (WBName <> "GPSCfg") Then
```
```vbscript
```vbscript
```vbscript
          CATIA.StartWorkbench("GPSCfg")
       End If
```
```

```

```

     ...

---

Create the Analysis document. The use of StartWorkbench  will customize the Analysis document as a generative one. This means that meshparts and properties will be automatically created as in the Generative workbench.
#### Importing the Part Document and Extracting the Publications

In order to import the document you have to give the path of this document, the late type which implements CATISamImportDefine and an array of CATVariant if you want to customize the import.

    ...
In order to import the document you have to give the path of this document, the late type which implements CATISamImportDefine and an array of CATVariant if you want to customize the import.
```vbscript
```vbscript
    '_____________________________________________________________________________________
    ' Start to scan the existing structure of analysis document: Retrieve the AnalysisManager

```

```

```vbscript
```vbscript
```vbscript
       Set analysisManager1 = TheAnalysisDocument.Analysis

```
```

```

```vbscript
```vbscript
       Dim arrayOfVariantOfShort1(0)
       analysisManager1.ImportDefineFile (sDocPath & sSep & "online" & sSep & "CAAScdAniUseCases" & sSep & "samples" & sSep & "SimpleCrank.CATPart"),
```

```

    				      "CATAnalysisImport", arrayOfVariantOfShort1
```vbscript
    ' _____________________________________________________________________________________
```

```vbscript
```vbscript
```vbscript
' _____________________________________________________________________________________
    ' Reframe All.
```

```

```

```vbscript
```vbscript
       Set specsAndGeomWindow1 = CATIA.ActiveWindow
```vbscript
```
```vbscript
       Set viewer3D1 = specsAndGeomWindow1.ActiveViewer
```
```

       viewer3D1.Reframe
```

```vbscript
```vbscript
```vbscript
    ' _____________________________________________________________________________________
    ' Scan the analysis document: Retrieve the Pointed documents to extract the reference for pre-processing
```vbscript
       Set analysisLinkedDocuments1 = analysisManager1.LinkedDocuments
       CATIA.SystemService.Print analysisLinkedDocuments1.Name
       If (analysisLinkedDocuments1.Count <> 1 ) Then
```
```vbscript
          Err.Raise 9999,,"NbDoc Li NE 1"
       End If
```
    ' _____________________________________________________________________________________
    ' Retrieve the CATPart Document and associated publications for pre-processing.
```vbscript
       Set TheDoc = analysisLinkedDocuments1.Item(1)
       CATIA.SystemService.Print TheDoc.FullName
       Set product1 = TheDoc.Product
       Set publications1 = product1.Publications
       Set publication1 = publications1.Item("ClampFace")
       Set publication2 = publications1.Item("MappingFace")
```
```

```

```

    ...

---

The Part document is fetched in the documentation installation path, this path has already been stored in the `sDocPath` variable. In the collection of documents analysisLinkedDocuments1, two documents can be retrieved: the Analysis document and the Part document. The extraction of pre-defined geometrical arena is done by using the Publication interface. Each publication is identified by a logical name. This is equivalent as the selection of a Publication element inside the interactive applications.

[Top]
#### Creating an Analysis Case for Static Analysis

    ...
```vbscript
```vbscript
```vbscript
    ' _____________________________________________________________________________________
    ' Create a Static Case in the current analysis model.
```

```

```

```vbscript
```vbscript
       Set analysisModels1 = analysisManager1.AnalysisModels
```vbscript
```
```vbscript
```vbscript
       Set analysisModel1 = analysisModels1.Item(1)
       Set analysisCases1 = analysisModel1.AnalysisCases

       Set analysisCase1 = analysisCases1.Add(#)
       Set analysisSets1 = analysisCase1.AnalysisSets
       Set analysisSet1 = analysisSets1.Add("RestraintSet", catAnalysisSetIn)
       Set analysisSet2 = analysisSets1.Add("LoadSet", catAnalysisSetIn)
       Set analysisSet3 = analysisCase1.AddSolution("StaticSet")
```
```

```

```

      ...

---

```vbscript
According to the general [ Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **document** , we find the **Analysis manager Object** , the **Analysis models** and the **Analysis cases Objects**. From both last object (Analysis Model and Analysis case), you can get access to **Analysis Sets** and **Analysis entities** that defines the pre-processing actions. This step create a new case and create two input sets (Restraint Set and Load Set) and a solution set (StaticSet).

```

[Top]
#### Defining the Boundaries

      ...
```vbscript
    ' To work with the collection of entities that defines the Boundary condition.
```

```vbscript
```vbscript
    ' _____________________________________________________________________________________
```

```

```vbscript
```vbscript
       Set analysisEntities1 = analysisSet1.AnalysisEntities
```vbscript
```
```vbscript
       Set analysisEntity1 = analysisEntities1.Add("SAMClamp")
```
```

       analysisEntity1.AddSupportFromPublication product1, publication1
```

    ...

---

From the restraint set defined on the analysis case, we retrieve the collection of  analysis entities. We add to this collection a fix (clamp) boundary condition and apply it on the geometry extracted from the Part document. Then, same is done for the sliding conditions.

[Top]
#### Defining the Loads

    ...
```vbscript
```vbscript
```vbscript
    ' _____________________________________________________________________________________
    ' Create Surfacic Force and apply to the publication called MappingFace

```

```

```

```vbscript
```vbscript
       Set analysisEntities2 = analysisSet2.AnalysisEntities
```vbscript
```
```vbscript
```vbscript
       Set analysisEntity3 = analysisEntities2.Add("SAMSurfacicForce")

```
```

```

```

```vbscript
```vbscript
Set analysisEntities2 = analysisSet2.AnalysisEntities
```vbscript
```
```vbscript
Set analysisEntity3 = analysisEntities2.Add("SAMSurfacicForce")
```
```

       analysisEntity3.AddSupportFromPublication product1, publication2

```

```vbscript
```vbscript
       Set basicComponents1 = analysisEntity3.BasicComponents
```vbscript
```
```vbscript
    ' No Local Axis is defined
```vbscript
       Set basicComponent1 = basicComponents1.GetItem("SAMSurfacicForceAxis.1")
```
```

```

       basicComponent1.SetValue "", 0, 0, 0, 1
```vbscript
```vbscript
    ' Valuate the vector.
```vbscript
       Set basicComponent2 = basicComponents1.GetItem("SAMSurfacicForceVector.1")
```
```

```

       basicComponent2.SetValue "Values", 1, 1, 1, 0.000000
       basicComponent2.SetValue "Values", 2, 1, 1, -1000000.000000
       basicComponent2.SetValue "Values", 3, 1, 1, 0.000000
```

```vbscript
```vbscript
```vbscript
    ' Create a Design Table for the mapping file and valuate the basic component
```vbscript
       Set basicComponent3 = basicComponents1.GetItem("SAMDTPtrSurfForce")
       Set designTable1 = analysisManager1.Relations.CreateDesignTable("", "", False, sDocPath & sSep  & "online" &
```
```

```

```

```vbscript
```vbscript
```vbscript
' Create a Design Table for the mapping file and valuate the basic component
```vbscript
Set basicComponent3 = basicComponents1.GetItem("SAMDTPtrSurfForce")
Set designTable1 = analysisManager1.Relations.CreateDesignTable("", "", False, sDocPath & sSep  & "online" &
```
```

```

                                     sSep & "CAAScdAniUseCases" & sSep & "samples" & sSep  & "MappingForCrank.txt")
       basicComponent3.SetValue "", 0, 0, 0, designTable1

```

    ...

---

The load is defined as the boundaries. For the mapping file, we will use the DesignTable object. This object is created with the collection of Relations. This collection is available on the **AnalysisManager** object by using analysisManager1.Relations method.

```vbscript
```vbscript
For more information about the physical types included inside analysis entities and the way to valuate them, refer to the reference [2]

```

```

[Top]
#### Computing the Case

    ...
```vbscript
    ' Launch the computation of the Case
```

       MyCase.Compute
    ...

---

This method will launch the mesher, generate the finite element model for pre-processing and launch the solver to generate the finite element results.

[Top]
#### Defining a Sensor and Printing it's Value

    ...
```vbscript
```vbscript
```vbscript
    ' _____________________________________________________________________________________
    ' Define a global sensor measuring the maximum value of VonMises criterion.
```

```

```

```vbscript
```vbscript
       Set dimension1 = analysisManager1.Parameters.CreateDimension("Maximum value of VonMises criterion", "PRESSURE", 0.000000)
```vbscript
```
```vbscript
       Set formula1 = analysisManager1.Relations.CreateFormula("Maximum value of VonMises criterion","",dimension1,
```
```

```

                                                     "misesmax(`Finite Element Model.1/Static Case Solution.1` ) ")
```vbscript
```vbscript
```vbscript
' Define a global sensor measuring the maximum value of VonMises criterion.
```vbscript
Set dimension1 = analysisManager1.Parameters.CreateDimension("Maximum value of VonMises criterion", "PRESSURE", 0.000000)
Set formula1 = analysisManager1.Relations.CreateFormula("Maximum value of VonMises criterion","",dimension1,
    ' Extract the computed value of the sensor
```
```vbscript
       CATIA.SystemService.Print " Mises Max Computed " & dimension1. ValueAsString
```
```

```

```

    ...

---
#### Epilog

    ...

```vbscript
```vbscript
End Sub

```
```

    ...

---

To run the macro interactively CATDocView and ADL_ODT_SLASH environment variables must be defined.

![image](../../assets/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to produce in VB a complete analysis document with a generative way.

[Top]

* * *
#### References

[1] | [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[2] |  [ The Physical Types for Structural Analysis](../use-cases/caascdaniusecases/CAAAniPreprocessingFeatures.md)
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
