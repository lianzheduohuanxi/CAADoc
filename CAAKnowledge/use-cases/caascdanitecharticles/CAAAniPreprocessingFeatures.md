---
title: "The Physical Types for Structural Analysis"
category: "general"
module: "CAAScdAniTechArticles"
tags: ["CATIAConstraints"]
source_file: "Doc\online\CAAScdAniTechArticles\CAAAniPreprocessingFeatures.htm"
converted: "2026-05-11T17:31:51.963872"
---

# Analysis Solution

| 

## Analysis Modeler

| 

### The Physical Types for Structural Analysis

_All the physical types you can use_  
---|---|---  
Technical Article  
  
* * *

### Abstract

This article describes the physical types that are defined for structural Analysis applications. At first, we explain the basic principles of analysis entities. Then, we classify the preprocessing features of the analysis specification tree, and for each we indicate the command that generate it in our application, the type of the analysis entity and the basic components included for defining the physics. This includes the arguments definition for their valuation. This list is useful for C++ programming and Visual Basic Macro generation. You will find in this chapter the following sections:

  * **About entities**
  * **AnalysisConnectionDesign**
  * **AnalysisMaterial**
  * **AnalysisProperty**
  * **AnalysisRestraint**
  * **AnalysisLoad**
  * **AnalysisMass**
  * **AnalysisSensor**
  * **Specified Group**
  * **Free Group**
  * **References**

  
---  
  
* * *

### About Entities

The basic automation type for all the preprocessing data objects is AnalysisEntity. Their parameters are Basic component. An analysis entity is created by using the Add method of the collection. This collection is given by the appropriate set (ex: load set for creating loading condition). The basic component is retrieved using the Item method of the collection. To valuate attributes with units, if you need to be independent of the current user settings, you can valuate the parameters with strings including the current unit system. This is essential if you need to generate macros what will not depend on a user settings. For this, see next example:
    
    
    ...
    ' To valuate by forcing the unit system:
    basicComponent2.SetValue "", 1, 1, 1, "5000.0lbf_ft"
    
    ' To take into account the current unit system: 
    basicComponent2.SetValue "", 1, 1, 1, 5000.0
    ...  
  
---  
  
 Remember that the basic components are mainly created automatically when the entity itself is created. For this the Add method makes non sense, as in the following example:
    
    
    ' To Create an analysis entity:
    Dim analysisEntities As AnalysisEntities
    Dim ThisAnalysisEntity As AnalysisEntity
    Set ThisAnalysisEntity = analysisEntities.Add("Analysis Entity Type")
    
    ' To retrieve the parameter "Param": First Retrieve the collection on the Entity
    Dim BasicComponents1 As BasicComponents
    Set BasicComponents1 = ThisAnalysisEntity.BasicComponents
    
    Dim BasicComponent1 As BasicComponent
    Set BasicComponent1 = BasicComponents1.Item("Param")
    ...  
  
---  
  
Note that the basic components concept can be used also on an analysis set. In this case, use also the "BasicComponents" collection returned by the set.

To valuate a support on an analysis entity and for some Basic components, the following methods may be used:

  * To use a Brep element or a mechanical feature


    
    
    ' To valuate a support from a mechanical feature or a Brep element: The product object will manage
    ' the instance of the Part Document.
    ' Retrieve the Part from this document
    Dim part1 As Part
    Set part1 = PartDocument.Part
    
    Dim product1 As Product
    Set product1 = PartDocument.Product
    
    ' Retrieve the References for Brep's
    Dim referenceBound As Reference
    Set referenceBound = part1.CreateReferenceFromName("Selection_RSur:(Face:(Brp:(GSMxxx))") // **Brep Case**
    
    ' Retrieve the References for Mechanical Features
    Dim bodies1 As Bodies
    Set bodies1 = part1.Bodies
    Dim body1 As Body
    Set body1 = bodies1.Item("PartBody")
    Dim shapes1 As Shapes 
    Set shapes1 = body1.ShapeS
    Dim split1 As Split 
    Set split1 = shapes1.Item("Split.1")
    Dim reference1 As Reference
    Set reference1 = part1.CreateReferenceFromObject(split1)               // Create the reference thanks to the part
    
    ThisAnalysisEntity.AddSupportFromProduct product1, reference1 
    
    ...  
  
---  
  
  * To use a publication


    
    
    ' To valuate a support from a publication: From the product feature (in a product or part document)
    
    Dim product1 As Product
    Set product1 = TheProductDoc.Product
    Dim publications1 As Publications
    Set publications1 = product1.Publications    // Extract the collection of publications.
    Dim publication1 As Publication
    Set publication1 = publications1.Item("ClampFace")
    
    ThisAnalysisEntity.AddSupportFromPublication product1, publication1 // product1 is the publisher object.
    ...  
  
---  
  
  * To use an assembly constraints


    
    
    ' To valuate a support from an assembly constraints:
    Dim product1 As Product
    Set product1 = TheProductDoc.Product
    Dim constraints1 As Constraints
    Set constraints1 = product1.Connections("CATIAConstraints")// Extract the collection of constraints.
    Dim constraint1 As Constraint
    Set constraint1 = constraints1.Item("Surface contact.2")
    
    ThisAnalysisEntity.AddSupportFromConstraint product1, constraint1 
    ...  
  
---  
  
  * To use another Analysis feature


    
    
    ' To valuate a support from another analysis feature: 
    ' Consider analysisSets2 is the Collection of AnalysisSet returned by AnalysisModel
    
    Dim analysisSet4  As AnalysisSet 
    Set analysisSet4 = analysisSets2.ItemByType("PropertySet") // Extract the property set 
    Dim analysisEntities1 As AnalysisEntities
    Set analysisEntities1 = analysisSet4.AnalysisEntities
    Dim analysisEntity1 As AnalysisEntity
    Set analysisEntity1= analysisEntities1.Item("MyRigidVirPart")  // Extract the entity to consider as a support 
    
    Set reference2 = analysisManager1.CreateReferenceFromObject(analysisEntity1) // Create the Reference Object
    ThisAnalysisEntity.AddSupportFromReference reference2, reference2
    ...  
  
---  
  
[Top]

#### AnalysisConnectionDesign

This section presents all the preprocessing features derived from AnalysisConnectionDesign.

Analysis Entity Name | Parameter Name | Value Type | Line Column Layer Number  
---|---|---|---  
![](images/I_ConnDesignGene.jpg) SAMGenericConnDesign |   |   |    
  | SAMConnectionDesigner1.1 | SAMMultiGeomPtr | [ 0 , 1 , 1 ]  
  | SAMConnectionDesigner2.1 | SAMMultiGeomPtr | [ 0 , 1 , 1 ]  
  | PointForGeneConn | SAMSlavePointPtr | [ 1 , 1 , 1 ]  
![](images/I_ConnDesignPoint.jpg) SAMPointConnDesign |   |   |    
  | SAMConnectionDesigner1.1 | SAMMultiGeomPtr | [ 0 , 1 , 1 ]  
  | SAMConnectionDesigner2.1 | SAMMultiGeomPtr | [ 0 , 1 , 1 ]  
  | PointsPtr | SAMMultiGeomPtr | [ 0 , 1 , 1 ]  
![](images/I_ConnDesignPointWOP.jpg) SAMPointConnDesignWOP |   |   |    
  | SAMConnectionDesigner1.1 | SAMMultiGeomPtr | [ 0 , 1 , 1 ]  
  | SAMConnectionDesigner2.1 | SAMMultiGeomPtr | [ 0 , 1 , 1 ]  
  | PointsPtr.1 | SAMMultiGeomPtr | [ 0 , 1 , 1 ]  
![](images/I_ConnDesignLine.jpg) SAMLineConnDesign |   |   |    
  | SAMConnectionDesigner1.1 | SAMMultiGeomPtr | [ 0 , 1 , 1 ]  
  | SAMConnectionDesigner2.1 | SAMMultiGeomPtr | [ 0 , 1 , 1 ]  
  | LinesPtr | SAMMultiGeomPtr | [ 0 , 1 , 1 ]  
![](images/I_ConnDesignLineWOP.jpg) SAMLineConnDesignWOP |   |   |    
  | SAMConnectionDesigner1.1 | SAMMultiGeomPtr | [ 0 , 1 , 1 ]  
  | SAMConnectionDesigner2.1 | SAMMultiGeomPtr | [ 0 , 1 , 1 ]  
  | LinesPtr.1 | SAMMultiGeomPtr | [ 0 , 1 , 1 ]  
  
[Top]

#### AnalysisMaterial

This section presents all the preprocessing features derived from AnalysisMaterial.

Analysis Entity Name | Parameter Name | Value Type | Line Column Layer Number  
---|---|---|---  
![](images/I_Sphere.jpg) SAMIsotropicMaterial |   |   |    
  | SAMYoungModulus | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMPoissonRatio | Real | [ 1 , 1 , 1 ]  
  | SAMDensity | DENSITY | [ 1 , 1 , 1 ]  
  | SAMThermalExpansion | INVERSE_TEMRTRE | [ 1 , 1 , 1 ]  
  | SAMShearModulus | PRESSURE | [ 1 , 1 , 1 ]  
![](images/I_Sphere.jpg) SAMOrthotropicMaterial |   |   |    
  | SAMYoungModulus_11 | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMYoungModulus_22 | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMPoissonRatio_12 | Real | [ 1 , 1 , 1 ]  
  | SAMShearModulus_12 | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMShearModulus_1Z | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMShearModulus_2Z | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMDensity | DENSITY | [ 1 , 1 , 1 ]  
  | SAMThermalExpansion_X | INVERSE_TEMRTRE | [ 1 , 1 , 1 ]  
  | SAMThermalExpansion_Y | INVERSE_TEMRTRE | [ 1 , 1 , 1 ]  
  | SAMTensileStressLimit_X | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMTensileStressLimit_Y | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMCompressiveStressLimit_X | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMCompressiveStressLimit_Y | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMTensileStrainLimit_X | Real | [ 1 , 1 , 1 ]  
  | SAMTensileStrainLimit_Y | Real | [ 1 , 1 , 1 ]  
  | SAMCompressiveStrainLimit_X | Real | [ 1 , 1 , 1 ]  
  | SAMCompressiveStrainLimit_Y | Real | [ 1 , 1 , 1 ]  
  | SAMShearStressLimit_12 | PRESSURE | [ 1 , 1 , 1 ]  
![](images/I_Sphere.jpg) SAMFiberMaterial |   |   |    
  | SAMYoungModulus_11 | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMYoungModulus_22 | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMPoissonRatio_12 | Real | [ 1 , 1 , 1 ]  
  | SAMShearModulus_12 | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMShearModulus_2Z | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMDensity | DENSITY | [ 1 , 1 , 1 ]  
  | SAMThermalExpansion_X | INVERSE_TEMRTRE | [ 1 , 1 , 1 ]  
  | SAMThermalExpansion_Y | INVERSE_TEMRTRE | [ 1 , 1 , 1 ]  
  | SAMTensileStressLimit_X | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMTensileStressLimit_Y | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMCompressiveStressLimit_X | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMCompressiveStressLimit_Y | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMShearStressLimit_12 | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMShearStressLimit_23 | PRESSURE | [ 1 , 1 , 1 ]  
![](images/I_Sphere.jpg) SAMHoneyCombMaterial |   |   |    
  | SAMYoungModulus_33 | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMShearModulus_1Z | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMShearModulus_2Z | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMDensity | DENSITY | [ 1 , 1 , 1 ]  
  | SAMThermalExpansion_33 | INVERSE_TEMRTRE | [ 1 , 1 , 1 ]  
  | SAMShearStressLimit_13 | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMShearStressLimit_23 | PRESSURE | [ 1 , 1 , 1 ]  
![](images/I_Sphere.jpg) SAMOrthotropic3DMaterial |   |   |    
  | SAMYoungModulus_11 | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMYoungModulus_22 | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMYoungModulus_33 | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMPoissonRatio_12 | Real | [ 1 , 1 , 1 ]  
  | SAMPoissonRatio_13 | Real | [ 1 , 1 , 1 ]  
  | SAMPoissonRatio_23 | Real | [ 1 , 1 , 1 ]  
  | SAMShearModulus_12 | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMShearModulus_13 | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMShearModulus_23 | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMDensity | DENSITY | [ 1 , 1 , 1 ]  
  | SAMThermalExpansion_X | INVERSE_TEMRTRE | [ 1 , 1 , 1 ]  
  | SAMThermalExpansion_Y | INVERSE_TEMRTRE | [ 1 , 1 , 1 ]  
  | SAMThermalExpansion_Z | INVERSE_TEMRTRE | [ 1 , 1 , 1 ]  
  | SAMTensileStressLimit_X | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMTensileStressLimit_Y | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMCompressiveStressLimit_X | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMCompressiveStressLimit_Y | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMShearStressLimit_12 | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMShearStressLimit_13 | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMShearStressLimit_23 | PRESSURE | [ 1 , 1 , 1 ]  
![](images/I_Sphere.jpg) SAMAnisotropicMaterial |   |   |    
  | SAMShearModulus_11 | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMShearModulus_12 | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMShearModulus_1Z | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMShearModulus_22 | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMShearModulus_2Z | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMShearModulus_33 | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMDensity | DENSITY | [ 1 , 1 , 1 ]  
  | SAMThermalExpansion_X | INVERSE_TEMRTRE | [ 1 , 1 , 1 ]  
  | SAMThermalExpansion_Y | INVERSE_TEMRTRE | [ 1 , 1 , 1 ]  
  | SAMThermalExpansion_Z | INVERSE_TEMRTRE | [ 1 , 1 , 1 ]  
  | SAMTensileStressLimit | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMCompressiveStressLimit | PRESSURE | [ 1 , 1 , 1 ]  
  | SAMShearStressLimit | PRESSURE | [ 1 , 1 , 1 ]  
  
[Top]

#### AnalysisProperty

This section presents all the preprocessing features derived from AnalysisProperty.

Analysis Entity Name | Parameter Name | Value Type | Line Column Layer Number  
---|---|---|---  
![](images/I_Prop1D.jpg) SAMBeam |   |   |    
  | SAMAnalysisMaterialPtr.1 | SAMSingleEntityPtr | [ 1 , 1 , 1 ]  
  | CustoBeamBC | SAMListManager | [ 1 , 1 , 1 ]  
  | PointForBeamAxis | SAMSlavePointPtr | [ 1 , 1 , 1 ]  
Optional   | SAMVariableBeamFactors | SAMBindComponent | [ 1 , 1 , 1 ]  
  |   | SAMScalingFactorStart | Real [ 1 , 1 , 1 ]  
  |   | SAMScalingFactorEnd | Real [ 1 , 1 , 1 ]  
![](images/I_MshTr3.jpg) SAMShell |   |   |    
  | SAMAnalysisMaterialPtr.1 | SAMSingleEntityPtr | [ 1 , 1 , 1 ]  
  | SAMThickness | LENGTH | [ 1 , 1 , 1 ]  
![](images/I_MshTet.jpg) SAM3DSolid |   |   |    
  | SAMAnalysisMaterialPtr.1 | SAMSingleEntityPtr | [ 1 , 1 , 1 ]  
SAMConnection |   |   |    
![](images/I_SliderConnection.jpg) SAMFaceFaceSlider |   |   |    
![](images/I_ContactConnection.jpg) SAMFaceFaceContact |   |   |    
  | SAMContactClearance | LENGTH | [ 0 , 1 , 1 ]  
![](images/I_FastenedConnection.jpg) SAMFaceFaceFastened |   |   |    
![](images/I_RigidConnection.jpg) SAMDistantRigid |   |   |    
Optional   | SAMDOFDistantConn | SAMBindComponent | [ 1 , 1 , 1 ]  
  |   | SAMConnAxisSytemDOF.1 | SAMAxisSystem [ 1 , 1 , 1 ]  
  |   | SAMConnDOF.1 | SAMDOFBoolean [ 6 , 1 , 1 ]  
![](images/I_SmoothConnection.jpg) SAMDistantSmooth |   |   |    
Optional   | SAMDOFDistantConn | SAMBindComponent | [ 1 , 1 , 1 ]  
  |   | SAMConnAxisSytemDOF.1 | SAMAxisSystem [ 1 , 1 , 1 ]  
  |   | SAMConnDOF.1 | SAMDOFBoolean [ 6 , 1 , 1 ]  
SAMVirtualPart |   |   |    
![](images/I_SmoothVirtualPart.jpg) SAMVirPartSmooth |   |   |    
  | SAMSmoSlavePoint | SAMSingleGeomPtr | [ 1 , 1 , 1 ]  
![](images/I_ContactVirtualPart.jpg) SAMVirPartContact |   |   |    
  | SAMConSlavePoint | SAMSingleGeomPtr | [ 1 , 1 , 1 ]  
  | SAMVPartContClr | LENGTH | [ 1 , 1 , 1 ]  
![](images/I_RigidVirtualPart.jpg) SAMVirPartRigid |   |   |    
  | SAMRigSlavePoint | SAMSingleGeomPtr | [ 1 , 1 , 1 ]  
![](images/I_RigidSpringVirtualPart.jpg) SAMVirPartRigidSpring |   |   |    
  | SAMRigSprSlavePoint | SAMSingleGeomPtr | [ 1 , 1 , 1 ]  
  | SAMRigStifAxis | SAMAxisSystem | [ 1 , 1 , 1 ]  
  | SAMRigStifTranslation | TSTIFNES | [ 3 , 1 , 1 ]  
  | SAMRigStifRotation | RSTIFNES | [ 3 , 1 , 1 ]  
![](images/I_SmoothSpringVirtualPart.jpg) SAMVirPartSmoothSpring |   |   |    
  | SAMSmoSprSlavePoint | SAMSingleGeomPtr | [ 1 , 1 , 1 ]  
  | SAMSmoStifAxis | SAMAxisSystem | [ 1 , 1 , 1 ]  
  | SAMSmoStifTranslation | TSTIFNES | [ 3 , 1 , 1 ]  
  | SAMSmoStifRotation | RSTIFNES | [ 3 , 1 , 1 ]  
![](images/I_FittingConnection.jpg) SAMPressureFitting |   |   |    
  | SAMPresFittingOverlap | LENGTH | [ 1 , 1 , 1 ]  
![](images/I_TighteningConnection.jpg) SAMBoltTightening |   |   |    
  | SAMBoltTighteningForce | FORCE | [ 1 , 1 , 1 ]  
  | SAMBoltTighOrientation | Enumere | [ 1 , 1 , 1 ]  
![](images/I_VirtualBoltTighConnection.jpg) SAMVirtBoltTightening |   |   |    
  | SAMVirtBoltTighteningForce | FORCE | [ 1 , 1 , 1 ]  
![](images/I_SamVirtualSpringBoltTighConnect.jpg) SAMVirtSpringBoltTigh |   |   |    
  | SAMVirtSpringBoltTighForce | FORCE | [ 1 , 1 , 1 ]  
  | SAMVirtSpringBoltTighStifTrans | TSTIFNES | [ 3 , 1 , 1 ]  
  | SAMVirtSpringBoltTighStifRot | RSTIFNES | [ 3 , 1 , 1 ]  
![](images/I_SamSpotWeldingConnection.jpg) SAMSpotWeldingConnect |   |   |    
  | SAMCustoWeld | SAMListManager | [ 1 , 1 , 1 ]  
![](images/I_MshTr3.jpg) SAMShellLocal |   |   |    
  | SAMAnalysisMaterialPtr.1 | SAMSingleEntityPtr | [ 1 , 1 , 1 ]  
  | SAMThickness | LENGTH | [ 1 , 1 , 1 ]  
![](images/I_PeriodicConnection.jpg) SAMPeriodicConnection |   |   |    
![](images/I_SamSeamWeldConnection.jpg) SAMSeamWeldConnect |   |   |    
  | SAMCustoSeamWeld | SAMListManager | [ 1 , 1 , 1 ]  
![](images/I_GenericConnection.jpg) SAMGenericDistant |   |   |    
  | SAMCustoStartComb | SAMListManager | [ 1 , 1 , 1 ]  
  | SAMCustoMiddleComb | SAMListManager | [ 1 , 1 , 1 ]  
  | SAMCustoEndComb | SAMListManager | [ 1 , 1 , 1 ]  
  | SAMAnalysisMaterialPtr | SAMSingleEntityPtr | [ 1 , 1 , 1 ]  
![](images/I_FastenedSpringConnection.jpg) SAMFaceFaceFastenedSpring |   |   |    
  | AxisSystem | SAMAxisSystem | [ 1 , 1 , 1 ]  
  | StifTranslation | TSTIFNES | [ 3 , 1 , 1 ]  
  | StifRotation | RSTIFNES | [ 3 , 1 , 1 ]  
![](images/I_Prop1D.jpg) SAMBeamLocal |   |   |    
  | SAMAnalysisMaterialPtr.1 | SAMSingleEntityPtr | [ 1 , 1 , 1 ]  
  | CustoBeamBC.1 | SAMListManager | [ 1 , 1 , 1 ]  
  | PointForBeamAxis.1 | SAMSlavePointPtr | [ 1 , 1 , 1 ]  
Optional   | SAMVariableBeamFactors | SAMBindComponent | [ 1 , 1 , 1 ]  
  |   | SAMScalingFactorStart | Real [ 1 , 1 , 1 ]  
  |   | SAMScalingFactorEnd | Real [ 1 , 1 , 1 ]  
  
[Top]

#### AnalysisRestraint

This section presents all the preprocessing features derived from AnalysisRestraint.

Analysis Entity Name | Parameter Name | Value Type | Line Column Layer Number  
---|---|---|---  
![](images/I_Clamp.jpg) SAMClamp |   |   |    
  | SAMClampDOF | SAMDOFBinary | [ 1 , 1 , 1 ]  
![](images/I_Analysis_Pivot.jpg) SAMPivot |   |   |    
  | SAMPivotAxis | SAMAxisSystem | [ 1 , 1 , 1 ]  
  | SAMPivotDirection | Real | [ 3 , 1 , 1 ]  
  | SAMPivotDOF | SAMDOFBinary | [ 1 , 1 , 1 ]  
![](images/I_Analysis_Slider_Pivot.jpg) SAMSlidingPivot |   |   |    
  | SAMSlidingPivotAxis | SAMAxisSystem | [ 1 , 1 , 1 ]  
  | SAMSlidingPivotDirection | Real | [ 3 , 1 , 1 ]  
  | SAMSlidingPivotDOF | SAMDOFBinary | [ 1 , 1 , 1 ]  
![](images/I_Analysis_Surface_Slider.jpg) SAMSurfaceSlider |   |   |    
  | SAMSurfaceSliderDOF | SAMDOFBinary | [ 1 , 1 , 1 ]  
![](images/I_Analysis_Slider.jpg) SAMSlider |   |   |    
  | SAMSliderAxis | SAMAxisSystem | [ 1 , 1 , 1 ]  
  | SAMSliderDirection | Real | [ 3 , 1 , 1 ]  
  | SAMSliderDOF | SAMDOFBinary | [ 1 , 1 , 1 ]  
![](images/I_Rigid.jpg) SAMPinned |   |   |    
  | SAMPinnedDOF | SAMDOFBinary | [ 1 , 1 , 1 ]  
![](images/I_Analysis_Ball_Join.jpg) SAMBallJoin |   |   |    
  | SAMBallJoinDOF | SAMDOFBinary | [ 1 , 1 , 1 ]  
![](images/I_Analysis_Restraint.jpg) SAMRestraint |   |   |    
  | SAMRestrainAxis | SAMAxisSystem | [ 1 , 1 , 1 ]  
  | SAMRestrainDOF | SAMDOFBasicComponent | [ 6 , 1 , 1 ]  
![](images/I_IsostaticRestraint.jpg) SAMRestIsostatic |   |   |    
  
[Top]

#### AnalysisLoad

This section presents all the preprocessing features derived from AnalysisLoad.

Analysis Entity Name | Parameter Name | Value Type | Line Column Layer Number  
---|---|---|---  
![](images/I_Pressure.jpg) SAMPressure |   |   |    
  | SAMPressureMag | PRESSURE | [ 1 , 1 , 1 ]  
Optional   | SAMDTPtrPressure | SAMSingleEntityPtr | [ 1 , 1 , 1 ]  
![](images/I_LineicForce.jpg) SAMLineicForce |   |   |    
  | SAMLineicForceAxis | SAMGUIAxisSystem | [ 1 , 1 , 1 ]  
  | SAMLineicForceVector | TSTIFNES | [ 3 , 1 , 1 ]  
Optional   | SAMDTPtrLinForce | SAMSingleEntityPtr | [ 1 , 1 , 1 ]  
![](images/I_SurfacicForce.jpg) SAMSurfacicForce |   |   |    
  | SAMSurfacicForceAxis | SAMAxisSystem | [ 1 , 1 , 1 ]  
  | SAMSurfacicForceVector | PRESSURE | [ 3 , 1 , 1 ]  
Optional   | SAMDTPtrSurfForce | SAMSingleEntityPtr | [ 1 , 1 , 1 ]  
![](images/I_VolumicForce.jpg) SAMVolumicForce |   |   |    
  | SAMVolumicForceAxis | SAMAxisSystem | [ 1 , 1 , 1 ]  
  | SAMVolumicForceVector | VOLFORCE | [ 3 , 1 , 1 ]  
Optionnal   | SAMDTPtrVolForce | SAMSingleEntityPtr | [ 1 , 1 , 1 ]  
![](images/I_Traction.jpg) SAMDistributedForce |   |   |    
  | SAMForceAxis | SAMAxisSystem | [ 1 , 1 , 1 ]  
  | SAMForceVector | FORCE | [ 3 , 1 , 1 ]  
  | SAMDistForcePoint | SAMSingleGeomPtr | [ 1 , 1 , 1 ]  
![](images/I_Moment.jpg) SAMMoment |   |   |    
  | SAMMomentAxis | SAMAxisSystem | [ 1 , 1 , 1 ]  
  | SAMMomentVector | MOMENT | [ 3 , 1 , 1 ]  
![](images/I_RotationForce.jpg) SAMRotationForce |   |   |    
  | SAMRotForceGeomPtr | SAMSingleGeomPtr | [ 1 , 1 , 1 ]  
  | SAMRotVelocity | ANGULARSPINDLESPEED | [ 1 , 1 , 1 ]  
  | SAMRotAcceleration | ANGACCELRTN | [ 1 , 1 , 1 ]  
![](images/I_Gravity.jpg) SAMTransAcceleration |   |   |    
  | SAMTransAccelAxis | SAMAxisSystem | [ 1 , 1 , 1 ]  
  | SAMTransAccelVector | ACCELRTN | [ 3 , 1 , 1 ]  
![](images/I_Rigid.jpg) SAMEnforcedDisp |   |   |    
  | SAMEnfDispEntityPtr | SAMSingleEntityPtr | [ 1 , 1 , 1 ]  
  | SAMEnfDispTransX | LENGTH | [ 1 , 1 , 1 ]  
  | SAMEnfDispTransY | LENGTH | [ 1 , 1 , 1 ]  
  | SAMEnfDispTransZ | LENGTH | [ 1 , 1 , 1 ]  
  | SAMEnfDispRotX | ANGLE | [ 1 , 1 , 1 ]  
  | SAMEnfDispRotY | ANGLE | [ 1 , 1 , 1 ]  
  | SAMEnfDispRotZ | ANGLE | [ 1 , 1 , 1 ]  
![](images/I_Bearing.jpg) SAMBearingLoad |   |   |    
  | SAMBearForceAxis | SAMAxisSystem | [ 1 , 1 , 1 ]  
  | SAMBearForceVector | FORCE | [ 3 , 1 , 1 ]  
  | SAMBearAngle | ANGLE | [ 1 , 1 , 1 ]  
  | SAMBearOrientation | Enumere | [ 1 , 1 , 1 ]  
  | SAMBearProfile | BasicComponent | [ 1 , 1 , 1 ]  
  |   | SAMBearProfileType | Enumere [ 1 , 1 , 1 ]  
  |   | SAMBearProfileLaw.1 | SAMSingleEntityPtr [ 1 , 1 , 1 ]  
![](images/I_TemperatureField.jpg) SAMTemperatureField |   |   |    
  | SAMTemperatureMag | TEMPRTRE | [ 1 , 1 , 1 ]  
Optional   | SAMDTPtrTemperatureField | SAMSingleEntityPtr | [ 1 , 1 , 1 ]  
![](images/I_ImportedForce.jpg) SAMImportedForce |   |   |    
  | AxisSystem | SAMAxisSystem | [ 1 , 1 , 1 ]  
  | SAMDTPtrImportedForceDesignTable | SAMSingleEntityPtr | [ 1 , 1 , 1 ]  
![](images/I_ImportedMoment.jpg) SAMImportedMoment |   |   |    
  | AxisSystem | SAMAxisSystem | [ 1 , 1 , 1 ]  
  | SAMDTPtrImportedMomentDesignTable | SAMSingleEntityPtr | [ 1 , 1 , 1 ]  
![](images/I_ForceDensity.jpg) SAMForceDensity |   |   |    
  | SAMForceDensityAxis | SAMAxisSystem | [ 1 , 1 , 1 ]  
  | SAMForceDensityVector | FORCE | [ 3 , 1 , 1 ]  
  
[Top]

#### AnalysisMass

This section presents all the preprocessing features derived from AnalysisMass.

Analysis Entity Name | Parameter Name | Value Type | Line Column Layer Number  
---|---|---|---  
![](images/I_Mass.jpg) SAMDistributedMass |   |   |    
  | SAMMassMag | MASS | [ 1 , 1 , 1 ]  
![](images/I_LineicMass.jpg) SAMLineicMass |   |   |    
  | SAMLineicMassMag | LINEMASS | [ 1 , 1 , 1 ]  
![](images/I_SurfacicMass.jpg) SAMSurfacicMass |   |   |    
  | SAMSurfacicMassMag | SURFACICMASS | [ 1 , 1 , 1 ]  
![](images/I_InertiaMass.jpg) SAMInertiaMass |   |   |    
  | SAMInertiaMassAxis | SAMAxisSystem | [ 1 , 1 , 1 ]  
  | SAMInertiaMassMass | MASS | [ 1 , 1 , 1 ]  
  | SAMInertiaMassVector | INERTIAMOMENT | [ 3 , 1 , 1 ]  
  
[Top]

#### AnalysisSensor

This section presents all the preprocessing features derived from AnalysisSensor.

Analysis Entity Name | Parameter Name | Value Type | Line Column Layer Number  
---|---|---|---  
![](images/I_AnalysisMeasure.jpg) SAMGlobalSensor |   |   |    
  | SAMOccSolutionFilter | SAMOccurrencesFilter | [ 1 , 1 , 1 ]  
![](images/I_AnalysisMeasure.jpg) SAMImageSensor |   |   |    
  | SAMOccSolutionFilter | SAMOccurrencesFilter | [ 1 , 1 , 1 ]  
  | SAMImagePointer.1 | BasicComponent | [ 1 , 1 , 1 ]  
  | PostProType | Enumere | [ 1 , 1 , 1 ]  
  | Parameters | Enumere | [ 1 , 1 , 1 ]  
  
[Top]

#### SAMSpecifiedGroup

This section presents all the preprocessing features derived from SAMSpecifiedGroup. They are dedicated to finite element grouping based on geometry definition.

Analysis Entity Name | Parameter Name | Value Type | Line Column Layer Number  
---|---|---|---  
![](images/I_GroupVertexSp.jpg) SAMVertexGroup |   |   |    
![](images/I_GroupEdgeSp.jpg) SAMEdgeGroup |   |   |    
![](images/I_GroupSurfaceSp.jpg) SAMSurfaceGroup |   |   |    
![](images/I_GroupBodySp.jpg) SAMBodyGroup |   |   |    
  
[Top]

#### SAMFreeGroup

This section presents all the preprocessing features derived from SAMFreeGroup. They are dedicated to pure finite element grouping.

Analysis Entity Name | Parameter Name | Value Type | Line Column Layer Number  
---|---|---|---  
![](images/I_GroupBoxSp.jpg) SAMBoxFEGroup |   |   |    
  | SAMBoxFE | LENGTH | [ 3 , 4 , 1 ]  
  | Extremum | BasicComponent | [ 1 , 1 , 1 ]  
![](images/I_GroupSphereSp2.jpg) SAMSphereFEGroup |   |   |    
  | SAMSphereFE | BasicComponent | [ 4 , 1 , 1 ]  
  | Extremum | BasicComponent | [ 1 , 1 , 1 ]  
  
[Top]

* * *

### History

Version: **1** [Mar 2001] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
