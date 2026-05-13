---
title: "Untitled"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CAAAniPreproOnVirtualSource", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAAniPreproOnVirtual", "CAAScdAniTechArticles", "CAAAniPreprocessingFeatures", "CATISamImportDefine", "CAAInfLauchMacro"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPreproOnVirtual.htmmd"
converted: "2026-05-11T11:27:02.574330"
---

---

      

Create the Analysis document. The use of StartWorkbench will customize
      the analysis document as a generative one. it mean's that a 3D meshpart
      and an isotropic property will be automatically created as in the
      Generative workbench.
      

#### Importing the Part Document
      

In order to import the document you have to give the path of this 
      document, the late type which implements CATISamImportDefine and an array 
      of CATVariant if you want to customize the import.
      
      

The Part document is fetched in the documentation installation path,
      this path has already been stored in the `sDocPath` variable.
      In the collection of documents analysisLinkedDocuments1, two documents can
      be retrieved: the Analysis document and the Part document. The extraction
      of pre-defined geometrical arena is done by using the Publication
      interface. Each publication is identified by a logical name. This is
      equivalent as the selection of a Publication element inside the
      interactive applications.
      

[Top]
      

#### Creating an Analysis Case for Frequency
      Analysis
      

According to the general [Analysis
      Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to
      navigate or retrieve the required objects. First, from the **document**,
      we find the **Analysis manager Object**, the **Analysis models** and
      the **Analysis cases Objects**. From both last object (Analysis Model
      and Analysis case), you can get access to **Analysis Sets** and **Analysis
      entities** that defines the preprocessing actions.
      

Inserting a new* *Frequency Case* *allows you to create
      objects sets for the new environmental specifications, and to implicitly
      require a normal modes solution procedure** **for the computation of
      the system vibration frequencies and normal modes for a given
      non-structural mass distribution under given restraints
      
      

 
      

[Top]
      

#### Creating Virtual Parts inside the Property Set
      

**Virtual Parts** are structures created without a geometric
      support. They represent bodies for which no geometry model is available,
      but which play a role in the structural analysis of single part or
      assembly systems. Virtual Parts are used to transmit action at a distance.
      Therefore they can be thought of as rigid bodies, except for the case
      where a lumped flexibility is explicitly introduced by the means of a
      spring element. For each hole we, will create a Rigid virtual part in
      order to fix the global structure.
      
      

[Top]
      

#### Defining Boundaries
      
      

From the restraint set defined on the analysis case, we retrieve the
      collection of analysis entities. We add to this collection a fix (clamp)
      boundary condition and apply it on the virtual part. For this we have to
      create a reference on the analysis feature and use the
      AddSupportFromReference method. Then, same is done for the 3 other
      virtual parts.
      

[Top]
      

#### Defining Non Structural Masses
      

Distributed Masses are used to model purely inertial (non-structural)
      system characteristics such as additional equipment. They represent scalar
      point mass fields equivalent to a total mass concentrated at a given
      point, distributed on a virtual part or on a geometric selection. We apply
      this mass of the top surface.
      
      

Note that to valuate the parameters, you can SetValue
      method and to read them again, you can use the GetValue
      that will return the value stored in the document.
      

[Top]
      

#### Computing the Case
      
      

This method will launch the mesher, generate the finite element model
      for preprocessing and launch the solver to generate the finite element
      results.
      

[Top]
      

#### Epilog
      
    
  

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to produce in VB a complete analysis document
with a generative way.

[Top]

---

#### References

---

*Copyright  2001, Dassault Systmes. All rights reserved.*

```cpp
...
' ----------------------------------------------------------- 
' Get the collection of documents in session 
' Create the CATAnalysis Document 
```vbscript
   Set TheAnalysisDocument = documents1.Add(&quot;Analysis&quot;) 
   
' if WB name already is &quot;GPSCfg&quot;, not to use StartWorkbench 
```
```cpp
   WBName = CATIA.GetWorkbenchId 
   if (WBName &lt;&gt; &quot;GPSCfg&quot;) Then 
```
```cpp
      CATIA.StartWorkbench(&quot;GPSCfg&quot;)
   End If
```
 ...
```

```vbscript
...
'_____________________________________________________________________________________ 
' Start to scan the existing structure of analysis document: Retrieve the AnalysisManager 
```vbscript
   Set analysisManager1 = TheAnalysisDocument.Analysis
```
```

```vbscript
```cpp
Dim arrayOfVariantOfShort1(0)
   analysisManager1.ImportDefineFile (sDocPath &amp; &quot;/online/CAAScdAniUseCases/samples/AnalysisMechfeat.CATPart&quot;),
```
```

```cpp
&quot;CATAnalysisImport&quot;, arrayOfVariantOfShort1 
' _____________________________________________________________________________________ 
' Reframe All. 
```cpp
   Set specsAndGeomWindow1 = CATIA.ActiveWindow 
   Set viewer3D1 = specsAndGeomWindow1.ActiveViewer 
   viewer3D1.Reframe 
```
' _____________________________________________________________________________________ 
' Scan the analysis document: Retrieve the Pointed documents to extract the reference for preprocessing 
```cpp
   Set analysisLinkedDocuments1 = analysisManager1.LinkedDocuments 
   CATIA.SystemService.Print analysisLinkedDocuments1.Name 
   If (analysisLinkedDocuments1.Count &lt;&gt; 1 ) Then 
```
```vbscript
      Err.Raise 9999,,&quot;NbDoc Li NE 1&quot; 
   End If 
```
' _____________________________________________________________________________________ 
' Retrieve the CATPart Document and associated publications for preprocessing. 
```cpp
   Set TheDoc = analysisLinkedDocuments1.Item(1) 
   CATIA.SystemService.Print TheDoc.FullName 
   Set product1 = TheDoc.Product 
   Set publications1 = product1.Publications 
...
```
```

```vbscript
...
' _____________________________________________________________________________________ 
' Create a Case for frequency computation in the current analysis model. 
```vbscript
   Set analysisModels1 = analysisManager1.AnalysisModels
   Set analysisModel1 = analysisModels1.Item(1)

   Set analysisCases1 = analysisModel1.AnalysisCases
   Set analysisCase1 = analysisCases1.Add(#)
   Set analysisSets1 = analysisCase1.AnalysisSets

   Set analysisSet1 = analysisSets1.Add(&quot;RestraintSet&quot;, catAnalysisSetIn)
   Set analysisSet2 = analysisSets1.Add(&quot;MassSet&quot;, catAnalysisSetIn)
   Set analysisSet3 = analysisCase1.AddSolution(&quot;FrequencySet&quot;)
   Set analysisSet6 = analysisSets1.Add(&quot;SensorSet&quot;,catAnalysisSetOut)
  ...
```
```

```vbscript
...
```vbscript
Set analysisSet4 = analysisSets2.ItemByType(&quot;PropertySet&quot;)

Set analysisEntities1 = analysisSet4.AnalysisEntities
Set analysisEntity1 = analysisEntities1.Add(&quot;SAMVirPartRigid&quot;)
Set publication1 = publications1.Item(&quot;SmallHole&quot;)
analysisEntity1.AddSupportFromPublication product1, publication1
```

...
```

```vbscript
...
' _____________________________________________________________________________________
' Clamp the Rigid Virtal Parts

```vbscript
   Set analysisEntities2 = analysisSet1.AnalysisEntities
   Set analysisEntity5 = analysisEntities2.Add(&quot;SAMClamp&quot;)
   Set reference1 = analysisManager1.CreateReferenceFromObject(analysisEntity4)
   analysisEntity5.AddSupportFromReference reference1, reference1
```
...
```

```vbscript
...
' _____________________________________________________________________________________
' Distribute some Masses on top of the Part

```vbscript
   Set analysisEntities3 = analysisSet2.AnalysisEntities
   Set analysisEntity9 = analysisEntities3.Add(&quot;SAMDistributedMass&quot;)
   Set publication5 = publications1.Item(&quot;TopFace&quot;)
   analysisEntity9.AddSupportFromPublication product1, publication5
```

```vbscript
   Set basicComponents1 = analysisEntity9.BasicComponents
   Set basicComponent1 = basicComponents1.GetItem(&quot;SAMMassMag&quot;)
   basicComponent1.SetValue &quot;&quot;, 0, 0, 0, 25.000000
```

' _____________________________________________________________________________________
' Read the Value of the Mass
```cpp
  CATIA.SystemService.Print &quot; Mass Applied of the Part: &quot; &amp; basicComponent1.GetValue (&quot;&quot;,0,0,0)

```

...
```

```vbscript
...
' Launch the computation of the Case 
   MyCase.Compute ...
...
```

```vbscript
...
```vbscript
 End Sub
```
```