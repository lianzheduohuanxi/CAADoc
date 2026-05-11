---
title: "Creating Preprocessing Data from Publications"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAAniPreproOnPublish", "CAAScrBase", "CAAInfLauchMacro", "CAAAniPreprocessingFeatures", "CAAScdInfUseCases", "CAAAniTocAnalysisDocument", "CATISamImportDefine", "CAAAniPreproOnPublishSource", "CAAScdAniTechArticles", "CAAScdAniUseCases", "CATIA", "CAAScrJavaScript"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreproPublish.htm"
converted: "2026-05-11T11:06:32.304204"
---

## Analysis Modeler
		
		
## []Creating Preprocessing Data from Publications
		
	

---

	
		![](../CAAScrBase/images/atarget.gif)
		|[]This macro shows you how to create an 
		Analysis document for a generative structural analysis. With this scenario, 
		you will cover all the steps of a generative analysis application.
		

It creates an Analysis document, imports a Part document provided with 
		the sample. An Analysis Case is created as for static linear analysis. Some 
		preprocessing data are defined by using the publication defined on the part. 
		Then, the computation is launched. An image (for Von Misses stresses) is 
		created and displayed. A parameter that measure the maximum value of this 
		stress is created and value is printed. At last, image data is exported 
		and the image is deactivated.
		

		![](images/PreproOnPublish.jpg)
		

 
		
	
	
		![](../CAAScrBase/images/ainfo.gif)
		|[]CAAAniPreproOnPublish is launched in CATIA 
		[[1]]. No open document is needed.
		

[CAAAniPreproOnPublish.catvbs] 
		is located in the CAAScdAniUseCases module.
		[Execute macro] (Windows 
		only).
		

 
		
	
	
		![](../CAAScrBase/images/ascenari.gif)
		|[]CAAAniPreproOnPublish includes the following 
		steps:
		

			
- [Prolog]
			
- [Importing the Part Document and Extracting 
			the Publication]
			
- [Creating an Analysis Case for Static Analysis]
			
- [Defining the Boundaries]
			
- [Defining the Load]
			
- [Defining a Sensor ]
			
- [Computing the Case and Printing the Sensor Value]
			
- [Creating an Image]
			
- [Exporting Data from the Image]
			
- [Deactivating the Image]
			
- [Epilog]
		
		
#### []Prolog
		
			
				
```
...
```

				
```
' ----------------------------------------------------------- 

' Optional: allows to find the sample wherever it's installed

 sDocPath=CATIA.SystemService.Environ("CATDocView")

 If
(Not CATIA.FileSystem.FolderExists(sDocPath)) 
Then

 Err.Raise 9999,,"No Doc Path Defined"

 End If

' -----------------------------------------------------------
```

				
```
' Get the collection of documents in session

 Set 
documents1 = CATIA.Documents

' ----------------------------------------------------------- 

' Get the collection of documents in session
 

' Create the CATAnalysis Document 

 
Set 
TheAnalysisDocument = documents1.
Add
("Analysis") 
 

' if WB name already is "GPSCfg", not to use StartWorkbench
 
 WBName = CATIA.GetWorkbenchId 
if 
(WBName <> "GPSCfg") 
Then
 
 CATIA.
StartWorkbench
("GPSCfg")
 
 
End If

 ...
```

				
			
		
		

Create the Analysis document. The use of StartWorkbench  will customize 
		the analysis document as a generative one. it mean's that meshparts and 
		properties will be automatically created as in the Generative workbench.
		
#### []Importing the Part Document and Extracting the 
		Publications
		

In order to import the document you have to give the path of this document, 
		the late type which implements CATISamImportDefine and an array of CATVariant 
		if you want to customize the import.
		
			
				
```
...

'_____________________________________________________________________________________
 

' Start to scan the existing structure of analysis document: Retrieve the AnalysisManager
 
 
Set 
analysisManager1 = TheAnalysisDocument.Analysis
```

				
```
Dim arrayOfVariantOfShort1(0)
 analysisManager1.
ImportDefineFile
 (sDocPath & sSep & "online" & sSep & "CAAScdAniUseCases" & sSep & "samples" & sSep & "AnalysisMechfeat.CATPart"),
```

				
```
"CATAnalysisImport", arrayOfVariantOfShort1
```

				
```
' _____________________________________________________________________________________
 

' Reframe All.
 
 
Set 
specsAndGeomWindow1 = CATIA.ActiveWindow 
 
Set 
viewer3D1 = specsAndGeomWindow1.ActiveViewer 
 viewer3D1.
Reframe
 

' _____________________________________________________________________________________
 

' Scan the analysis document: Retrieve the Pointed documents to extract the reference for preprocessing
 
 
Set 
analysisLinkedDocuments1 = analysisManager1.LinkedDocuments 
 CATIA.SystemService.Print analysisLinkedDocuments1.Name 
 
If 
(analysisLinkedDocuments1.Count <> 1 )
 Then
 
 Err.Raise 9999,,"NbDoc Li NE 1" 
 
End If
 

' _____________________________________________________________________________________
 

' Retrieve the CATPart Document and associated publications for preprocessing.
 
 
Set 
TheDoc = analysisLinkedDocuments1.Item(1) 
 CATIA.SystemService.Print TheDoc.FullName 
 
Set 
product1 = TheDoc.Product 
 
Set 
publications1 = product1.
Publications
 
 
Set 
publication1 = publications1.Item("Bottomface") 
 
Set 
publication2 = publications1.Item("Sliding1") 
 
Set 
publication3 = publications1.Item("Sliding2") 
 
Set 
publication4 = publications1.Item("ResizeBody")
...
```

				
			
		
		

The part document is fetched in the documentation installation path, 
		this path has already been stored in the `sDocPath` variable. 
		In the collection of documents analysisLinkedDocuments1 , two documents 
		can be retrieved: the Analysis one and the Part document. The extraction 
		of pre defined geometrical arena is done by using the Publication interface. 
		Each publication is identified by a logical name. This is equivalent as 
		the selection of a Publication element inside the interactive applications.
		

[[Top]]
		
#### []Creating an Analysis Case for Static Analysis
		
			
				
```
...

' _____________________________________________________________________________________
 

' Create a Static Case in the current analysis model.
 
 
Set 
analysisModels1 = analysisManager1.AnalysisModels 
 
Set 
analysisModel1 = analysisModels1.Item(1) 
 
Set 
analysisCases1 = analysisModel1.AnalysisCases
 
 
Set 
analysisCase1 = analysisCases1.
Add
()
 
Set 
analysisSets1 = analysisCase1.AnalysisSets
 
Set 
analysisSet1 = analysisSets1.
Add
("RestraintSet", catAnalysisSetIn)
 
Set 
analysisSet2 = analysisSets1.
Add
("LoadSet", catAnalysisSetIn)
 
Set 
analysisSet3 = analysisCase1.
AddSolution
("StaticSet")
 ...
```

				
			
		
		

According to the general
		[
		Analysis Document] structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **document**, 
		we find the **Analysis manager Object**, the **Analysis models** and 
		the **Analysis cases Objects**. From both last object (Analysis Model 
		and Analysis case), you can get access to **Analysis Sets** and **Analysis 
		entities** that defines the pre-processing actions. This step create a 
		new case and create two input sets (Restraint Set and Load Set) and a solution 
		set (StaticSet).
		

[[Top]]
		
#### []Defining the Boundaries
		
			
				
```
...

' To work with the collection of entities that defines the Boundary condition.

' _____________________________________________________________________________________
 
 
Set 
analysisEntities1 = analysisSet1.AnalysisEntities
 
 
Set 
analysisEntity1 = analysisEntities1.Add("SAMClamp")
 
 analysisEntity1.
AddSupportFromPublication
 product1, publication1 

' _____________________________________________________________________________________
 

' Create Slider boundary.

 
Set 
analysisEntity2 = analysisEntities1.Add("SAMSurfaceSlider")
 
 analysisEntity2.
AddSupportFromPublication
 product1, publication2
 
 analysisEntity2.
AddSupportFromPublication
 product1, publication3
...
```

				
			
		
		

From the restraint set defined on the analysis case, we retrieve the 
		collection of  analysis entities. We add to this collection a fix (clamp) 
		boundary condition and apply it on the geometry extracted from the Part 
		document. Then, same is done for the sliding conditions.
		

[[Top]]
		
#### []Defining the Load
		
			
				
```
...

' _____________________________________________________________________________________
 

' Create Pressure.

 
Set 
analysisEntities2 = analysisSet2.AnalysisEntities 
 
Set 
analysisEntity3 = analysisEntities2.Add("SAMPressure")
 analysisEntity3.
AddSupportFromPublication
 product1, publication4 
 analysisEntity3.
SetValue
 "SAMPressureMag","", 0, 0, 0, 500.
...
```

				
			
		
		

The load is defined as the boundaries. For more information about the 
		physical type included inside analysis entities and the way to valuate them, 
		refer to the reference [[2]]
		

[[Top]]
		
#### []Defining a Sensor
		
			
				
```
...

' _____________________________________________________________________________________
 

' Define a global sensor measuring the maximum value of VonMises criterion.
 
 
Set 
dimension1 = 
analysisManager1.Parameters.CreateDimension
("Maximum value of VonMises criterion", "PRESSURE", 0.000000)
 
Set 
formula1 = analysisManager1.
Relations.CreateFormula
("Maximum value of VonMises criterion","",dimension1,
 "misesmax(`Finite Element Model.1\Static Case Solution.1` ) ")
...
```

				
			
		
		

[[Top]]
		
#### []Computing the Case and Printing the Sensor Value
		
			
				
```
...

' Launch the computation of the Case
 
 MyCase.Compute ...
 

' Extract the computed value of the sensor

 CATIA.SystemService.Print " Mises Max Computed " & dimension1.ValueAsString
...
```

				
			
		
		

This method will launch the mesher, generate the finite element model 
		for preprocessing and launch the solver to generate the finite element results.
		

[[Top]]
		
#### []Creating an Image
		
			
				
```
...

' _____________________________________________________________________________________
 

' Create corresponding image.

 
Set 
analysisImages1 = analysisSet3.
AnalysisImages
 
 
Set 
analysisImage1 = analysisImages1.
Add
("StressVonMises_Iso_Smooth", False, False, True)
 
' _____________________________________________________________________________________
 
'

 Reframe All.
 
 viewer3D1.
Reframe

...
```

				
			
		
		

The image is created based on the solution of the case. For this use 
		the AnalysisImages collection and create the image according to it's name. 
		Then, reframe will update the display.
		

[[Top]]
		
#### []Exporting Data from the Image
		
			
				
```
...

' _____________________________________________________________________________________
 

' Export data from the created image.

 
Set 
fileSystem1 = CATIA.FileSystem 
 
Set 
folder1 = fileSystem1.
GetFolder
(outputPath)
 analysisImage1.
ExportData
 folder1, "VonMises", "txt"
 
' _____________________________________________________________________________________
 
'

 

...
```

				
			
		
		

The image is exported in the specified file. This file is defined by 
		folder, export data filename and filetype.
		
#### []Deactivating the Image
		
			
				
```
...

' _____________________________________________________________________________________
 

' Deactivate and Update the created image.

 analysisImage1.
SetActivationStatus
 false
 analysisImage1.
Update

 
' _____________________________________________________________________________________
 
'

 

...
```

				
			
		
		

The image is deactivated.
		
#### []Epilog
		
			
				
```
...
```

				End Sub
				
```
...
```

				
			
		
		

To run the macro interactively CATDocView and ADL_ODT_SLASH 
		environment variables must be defined.
	

![](../CAAScrBase/images/aendtask.gif)

[[Top]]

---

#### []In Short

This use case has shown how to produce in VB a complete analysis document with 
a generative way.

[[Top]]

---

#### []References

	
		|[1]
		|[Replaying 
		a macro]
	
	
		|[2]
		[
		The Physical Types for Structural Analysis]
	
	
		|[[Top]]
	

---

*Copyright 2001, Dassault Systmes. All rights reserved.*