---
title: "The Versioning of the Topological Operators"
category: "use-case"
module: "CAATopTechArticles"
tags: []
source_file: "Doc/online/CAATopTechArticles/TopoVersioning.htm"
converted: "2026-05-11T17:31:50.815757"
---
# Geometric Modeler

| 
## Topology

| 
### The Versioning of the Topological Operators

_Migration principles_  
---|---|---  
Technical Article  
  
* * *
### Abstract

The topological operators create new bodies from input bodies, depending on an internal algorithm. For maintenance or enhancement reasons, this internal algorithm may change, so that the results could not be exactly the same after the code modification. The operator versioning is a way to always replay an operator with the same level of software. This can be needed by applications that store the specifications of their operations, such as the feature applications. To put this mechanism in place, existing interfaces are modified, and the migration process is explained. 

  * **Principle**
    * The CATSoftwareConfiguration Class
    * The CATTopData Class
  * **Migration**
    * TopologicalOperators
    * BasicTopologicalOpe
    * AdvancedTopologicalOpe
    * Case of the Journal
  * **In Short**
  * **References**

  
---  
  
* * *
### Principle

If an application stores the way to build an object, and gives the mean to replay this definition, it expects that the replay always gives the same result. Up to now, for maintenance or enhancement reasons, the software modifications could lead to slightly different results. To avoid this situation, the current software configuration of an operator is accessible, and an operator can be replayed with a given software configuration: we call that the operator versioning.

[Top]
#### The CATSoftwareConfiguration Class

The class that manages the operator versioning is the _CATSoftwareConfiguration_ class of the Mathematics framework. This class 

  * Creates an open configuration for the current software level
  * Creates a closed configuration (that can be read from a previously streamed configuration with a specific method. See also the Part documentation.)
  * Streams an existing configuration
  * Tests whether a configuration is supported by the current software.

To create an open configuration (a configuration for the current software level), use the default constructor. Notice that you must use the `new` operator. 
    
    
    _//_ _Defines an open configuration for the operator_
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();  
  
---  
  
If you use feature applications, please refer to their documentation to see how to retrieve the configuration associated with a given feature.

The configuration must be released after use in the following way:
    
    
    _//_ _Releases the configuration after the deletion of the operators_
    pConfig->**Release**();  
  
---  
  
[Top]
#### The CATTopData Class

Once created, the configuration instance is given to the topological operator to inform it of the level of software it must use during its run. The software configuration is not given directly to the operator, but by the mean of the class _CATTopData_ that contains: 

  * A pointer to the configuration, that must be not `NULL`
  * A pointer to the journal [1] of the operator. This pointer can be `NULL` : in this case, the journal is not filled.

We give here an example for creating a `CATTopSkin` operator, that is fully commented in _Overview of the topological operators_ [2]. 
    
    
    _// defines the data of the operator: configuration + journal_
    CATTopData topdata(pConfig,NULL);
    _// now creates the operator_
    CATTopSkin * pSkinOp = **::CATCreateTopSkin** (piGeomFactory,_// the pointer to the factory for the creation of the result_
                                               **& topdata**,_// the topological data_
                                               piPlane,
                                               nbPCurves, 
                                               aPCurves,
                                               aLimits,
                                               aOrientations);  
  
---  
  
All the operators are based on the same frame: the pointer to the factory for the creation of the resulting body is the first argument, the not `NULL` pointer to the topological data containing the configuration and the journal is the second argument. 

[Top]
### Migration

As now an operator must know the configuration software on which it must run, this argument becomes mandatory. The following table indicates the correspondence between the old signature and the new signature for the operators of the TopologicalOperators, AdvancedTopologicalOpe, BasicTopologicalOpe frameworks. Be careful that migration can also affect the class of the operator.

[Top]
#### Topological Operators

Deprecated Signature | New Signature  
---|---  
      
    
    **CATHybOperator*
    CreateHybSkinAssembly**(CATGeoFactory* iFactory,
                          ListPOfCATBody* iBodiesToAssemble,
                          CATCGMJournalList* iJournal)
    
    **CATHybOperator*
    CreateHybWireAssembly**(CATGeoFactory* iFactory,
                          ListPOfCATBody* iBodiesToAssemble,
                          CATCGMJournalList* iJournal)

| 
    
    
    **CATHybAssemble*
    CATCreateTopAssemble**(CATGeoFactory* iFactory,
                         CATTopData* iData,
                         ListPOfCATBody* iBodiesToAssemble)  
      
    
    **CATHybOperator*
    CreateHybIntersect**(CATGeoFactory* iFactory,
                       CATBody* iBody1ToIntersect,
                       CATBody* iBody2ToIntersect,
                       CATCGMJournalList* iReport)

| 
    
    
    **CATHybIntersect*
    CATCreateTopIntersect**(CATGeoFactory* iFactory,
                          CATTopData* iData,
                          CATBody* iBody1ToIntersect,
                          CATBody* iBody2ToIntersect)  
      
    
    **CATHybOperator*
    CreateHybProject**(CATGeoFactory* iFactory,
                     CATBody* iBodyToProject,
                     CATBody* iBodySupport,
                     const CATMathDirection* iDirection,
                     CATCGMJournalList* iJournal)

| 
    
    
    **CATHybProject*
    CATCreateTopProject**(CATGeoFactory* iFactory,
                        CATTopData* iData,
                        CATBody* iBodyToProject,
                        CATBody* iBodySupport,
                        CATMathDirection* iDirection)  
      
    
    **CATHybOperator*
    CreateHybSplit**(CATGeoFactory* iFactory,
                   CATBody* iBodyToSplit,
                   short iSideToKeep,
                   CATBody* iSplittingBody,
                   CATBody* iCuttingBody,
                   CATCGMJournalList* iJournal)

| 
    
    
    **CATHybSplit*
    CATCreateTopSplit**(CATGeoFactory* iFactory,
                      CATTopData* iData,
                      CATBody* iBodyToSplit,
                      short iSideToKeep,
                      CATBody* iSplittingBody,
                      CATBody* iCuttingBody)  
      
    
    **CATHybOperator*
    CreateHybTrim**(CATGeoFactory* iFactory,
                  CATBody* iFirstBodyToCut,
                  short iFirstSideToKeep,
                  CATBody* iSecondBodyToCut,
                  short iSecondSideToKeep,
                  CATBody* iCuttingBody,
                  CATCGMJournalList* iJournal)

| 
    
    
    **CATHybTrim*
    CATCreateTopTrim**(CATGeoFactory* iFactory,
                     CATTopData* iData,
                     CATBody* iFirstBodyToCut,
                     short iFirstSideToKeep,
                     CATBody* iSecondBodyToCut,
                     short iSecondSideToKeep,
                     CATBody* iCuttingBody)  
      
    
    CATDistanceMinBodyBody * **CreateDistanceMinTopo**(CATGeoFactory *iFactory,
                          CATBody *iBody1,
                          CATBody *iBody2,
                          CATSkillValue iMode=BASIC)

| 
    
    
    CATDistanceMinBodyBody * **CATCreateDistanceMinTopo**(CATGeoFactory *iFactory,
                     CATTopData *iData,
                     CATBody *iBody1,
                     CATBody *iBody2,
                     CATSkillValue iMode=BASIC)  
      
    
    CATDynBoolean*
    **CATDynCreateBoolean**(CATGeoFactory* iFactory,
                        CATDynBooleanType iOperation,
                        CATBody* iPart,
                        CATBody* iTool,
                        CATCGMJournalList* iJournal)

| 
    
    
    CATDynBoolean*
    **CATCreateDynBoolean**(CATGeoFactory* iFactory,
                        CATTopData* iData,
                        CATDynBooleanType iOperation,
                        CATBody* iPart,
                        CATBody* iTool)  
      
    
    CATDynChamfer*
    **CATDynCreateChamfer**(CATGeoFactory* Container,
                        CATBody* iPart,
                        CATCGMJournalList* iJournal)

| 
    
    
    CATDynChamfer*
    **CATCreateDynChamfer**(CATGeoFactory* Container,
                        CATTopData* iData,
                        CATBody* iPart)  
      
    
    CATDynDraft*
    **CATDynCreateDraft**(CATGeoFactory* iContainer,
                      CATBody* iPart,
                      const CATDynDraftType iType,
                      CATCGMJournalList* iJournal)

| 
    
    
    CATDynDraft*
    **CATCreateDynDraft**(CATGeoFactory* iContainer,
                      CATTopData* iData,
                      CATBody* iPart,
                      const CATDynDraftType iType)  
      
    
    CATDynFillet*
    **CATDynCreateFillet**(CATGeoFactory* iContainer,
                      CATBody* iPart,
                      CATCGMJournalList* iJournal)

| 
    
    
    CATDynFillet*
    **CATCreateDynFillet**(CATGeoFactory* iContainer,
                       CATTopData* iData,
                       CATBody* iPart)  
      
    
    CATDynShell*
    **CATDynCreateShell**(CATGeoFactory* iForResultingBody,
                      CATBody* iBody,
                      CATLength iInternal,
                      CATLength iExternal,
                      CATCGMJournalList* iJournal)

| 
    
    
    CATDynShell* **CATCreateDynShell**(CATGeoFactory * iFactory,
                      CATTopData * iTopData,
                      CATBody * iBody,
                      CATLength iInternal,
                      CATLength iExternal)  
      
    
    CATDynSplit* **CATDynCreateSplit**(CATGeoFactory* iFactory,
                      CATBody* iBody,
                      CATDynSplitType iSplitType,
                      CATCGMJournalList* iJournal)

| 
    
    
    CATDynSplit*
    **CATCreateDynSplit**(CATGeoFactory* iFactory,
                      CATTopData* iData,
                      CATBody* iBody,
                      CATDynSplitType iSplitType)  
      
    
    **CATThick::CATThick**(CATBody* iBody,
               CATCGMJournalList* iJournal)

| 
    
    
    **CATDynThickness*
    CATCreateDynThickness**(CATGeoFactory* iContainer,
                          CATTopData* iTopData,
                          CATBody* iPart)  
      
    
    CATDynTransformation*
    **CATDynCreateTransformation**(CATGeoFactory* iFactory,
                               CATBody* iBodytoTransform,
                               CATCGMJournalList* iJournal)

| 
    
    
    CATDynTransformation*
    **CATCreateDynTransformation**(CATGeoFactory* iFactory,
                               CATTopData* iData,
                               CATBody* iBodytoTransform)  
  
  | 
    
    
    CATSkinExtrapol*
    **CATCreateSkinExtrapol**(CATGeoFactory* iFactory,
                          CATTopData* iTopData,
                          CATBody * iSkin)  
      
    
    **CATSkinOperator::CATSkinOperator**(
          CATGeoFactory* iFactory,
          CATTopData* iData,
          CATSurface* iSurface)

| 
    
    
    CATTopSkin* **CATCreateTopSkin**(CATGeoFactory* iFactory,
                     CATTopData* iData,
                     CATSurface* iSurface,
                     const CATSurLimits* iLims)  
      
    
    **CATSkinOperator::CATSkinOperator**(
          CATGeoFactory* iFactory,
          int iNbPcurves,
          CATPCurve** iPcurves,
          CATCrvLimits* iLimits,
          short* iOrientations,
          CATBody* iTargetBody=NULL,
          CATBodyFreezeMode iBodyfreezemode,
          CATCGMJournalList* iJournal)

| 
    
    
    CATTopSkin*
    **CATCreateTopSkin**(CATGeoFactory* iFactory,
                     CATTopData* iData,
                     CATSurface* iSurface,
                     int iNbPcurves,
                     CATPCurve** iPcurves,
                     CATCrvLimits* iLimits,
                     short* iOrientations)  
      
    
    **CATSolidCuboid::CATSolidCuboid**(
          CATGeoFactory* iFactory,
          const CATMathPoint& iPt1,
          const CATMathPoint& iPt2,
          const CATMathPoint& iPt3,
          const CATMathPoint& iPt4,
          CATCGMJournalList *iJournal)

| 
    
    
    **CATSolidCuboid*
    CATCreateSolidCuboid**(CATGeoFactory* iFactory,
                         CATTopData* iData,
                         const CATMathPoint& iPt1,
                         const CATMathPoint& iPt2,
                         const CATMathPoint& iPt3,
                         const CATMathPoint& iPt4)  
      
    
    **CATSolidCylinder::CATSolidCylinder**(
          CATGeoFactory* iFactory,
          const CATMathPoint& iFirstPointOnAxis,
          const CATMathPoint& iSecondPointOnAxis,
          const CATMathPoint& iPointOnSurface,
          CATCGMJournalList* iJournal)

| 
    
    
    **CATSolidCylinder*
    CATCreateSolidCylinder**(CATGeoFactory* iFactory,
                           CATTopData* iData,
                           const CATMathPoint& iFirstPointOnAxis,
                           const CATMathPoint& iSecondPointOnAxis,
                           const CATMathPoint& iPointOnSurface)  
      
    
    **CATSolidCylinder::CATSolidCylinder**(
          CATGeoFactory* iFactory,
          const CATMathPoint& iFirstPointOnAxis,
          const CATMathPoint& iSecondPointOnAxis,
          double iRadius,
          CATCGMJournalList* iJournal)

| 
    
    
    **CATSolidCylinder*
    CATCreateSolidCylinder**(CATGeoFactory* iFactory,
                           CATTopData* iData,
                           const CATMathPoint& iFirstPointOnAxis,
                           const CATMathPoint& iSecondPointOnAxis,
                           double iRadius)  
      
    
    **CATSolidPyramid::
          CATSolidPyramid**(CATGeoFactory* iFactory,
          const CATMathPoint& iPt1,
          const CATMathPoint& iPt2,
          const CATMathPoint& iPt3,
          const CATMathPoint& iTop,
          CATCGMJournalList* iJournal)

| 
    
    
    **CATSolidPyramid*
    CATCreateSolidPyramid**(CATGeoFactory* iFactory,
                          CATTopData* iData,
                          const CATMathPoint& iPt1,
                          const CATMathPoint& iPt2,
                          const CATMathPoint& iPt3,
                          const CATMathPoint& iTop)  
      
    
    **CATSolidPyramid::CATSolidPyramid**(
          CATGeoFactory* iFactory,
          CATFace* iBase,
          const CATMathPoint& iTop,
          CATCGMJournalList *iJournal)

| 
    
    
    **CATSolidPyramid*
    CATCreateSolidPyramid**(CATGeoFactory* iFactory,
                          CATTopData* iData,
                          CATFace* iBase,
                          const CATMathPoint& iTop)  
      
    
    **CATSolidSphere::CATSolidSphere**(
          CATGeoFactory* iFactory,
          const CATMathPoint& iCenter,
          double iRadius,
          CATCGMJournalList* iJournal)

| 
    
    
    **CATSolidSphere*
    CATCreateSolidSphere**(CATGeoFactory* iFactory,
                         CATTopData* iData,
                         const CATMathPoint& iCenter,
                         double iRadius)  
      
    
    **CATSolidTorus::CATSolidTorus**(
          CATGeoFactory* iFactory,
          const CATMathAxis& iAxis,
          const CATMathPoint& iMajor,
          const CATMathPoint& iMinor,
          CATCGMJournalList *iJournal)

| 
    
    
    **CATSolidTorus*
    CATCreateSolidTorus**(CATGeoFactory* iFactory,
                        CATTopData* iData,
                        const CATMathAxis& iAxis,
                        const CATMathPoint& iMajor,
                        const CATMathPoint& iMinor)  
      
    
    **CATThick::CATThick**(
          CATBody* iBody,
          CATCGMJournalList* iJournal)

| 
    
    
    **CATDynThickness*
    CATCreateDynThickness**(CATGeoFactory* iFactory,
                          CATTopData* iTopData,
                          CATBody* iPart)  
      
    
    CATTopCorner*
    **CreateTopOpCorner**(CATGeoFactory* iFactory,
                      CATBody * iCurve1,
                      CATBody * iCurve2,
                      CATBody * iSupport,
                      double iRadius,
                      CATCGMJournalList* iJournalList)

| 
    
    
    CATTopCorner*
    **CATCreateTopCorner**(CATGeoFactory* iFactory,
                       CATTopData* iTopData,
                       CATBody* iCurve1,
                       CATBody* iCurve2,
                       CATBody* iSupport,
                       double iRadius)  
      
    
    CATTopDevelop*
    **CreateTopOpDevelop**(CATGeoFactory* iFactory,
                       CATBody* iWire,
                       CATBody* iWireSupport,
                       CATBody* iTargetSupport,
                       CATSurTo2DGlobalMapping* iMappingIn,
                       CATSurTo2DGlobalMapping* iMappingOut,
                       CATCGMJournalList *iReport)

| 
    
    
    CATTopDevelop*
    **CATCreateTopDevelop**(CATGeoFactory* iFactory,
                        CATTopData* iData,
                        CATBody* iWire,
                        CATBody* iWireSupport,
                        CATBody* iTargetSupport,
                        CATSurTo2DGlobalMapping* iMappingIn,
                        CATSurTo2DGlobalMapping* iMappingOut)  
      
    
    CATTopParallel*
    **CreateTopOpAllParallel**(CATGeoFactory* iFactory,
                           CATBody* iCurve,
                           CATBody* iSupport,
                           CATDistanceTool* iDistance,
                           CATCGMJournalList* iJournal,
                           CATLaw** iMappingLaws)

| 
    
    
    CATTopParallel*
    **CATCreateTopParallel**(CATGeoFactory* iFactory,
                         CATTopData* iData,
                         CATBody* iCurve,
                         CATBody* iSupport,
                         CATDistanceTool* iDistance)  
      
    
    CATTopPrism*
    **CATTopCreatePrism**(CATGeoFactory* iFactory,
                      CATBody* iProfileBody,
                      CATMathDirection* iDirection,
                      CATLength iStartOffset,
                      CATLength iEndOffset,
                      CATCGMJournalList* iJournal)

| 
    
    
    CATTopPrism*
    **CATCreateTopPrism**(CATGeoFactory* iFactory,
                      CATTopData* iData,
                      CATBody* iProfileBody,
                      CATMathDirection* iDirection,
                      CATLength iStartOffset,
                      CATLength iEndOffset)  
      
    
    CATTopRevol* **CATTopCreateRevol**(CATGeoFactory* iFactory,
                      CATBody* iProfile,
                      CATMathAxis* iAxis,
                      CATAngle iStartAngle,
                      CATAngle iEndAngle,
                      CATCGMJournalList* iJournal)

| 
    
    
    CATTopRevol* **CATCreateTopRevol**(CATGeoFactory* iFactory,
                      CATTopData* iData,
                      CATBody* iProfile,
                      CATMathAxis* iAxis,
                      CATAngle iStartAngle,
                      CATAngle iEndAngle)  
  
  | 
    
    
    CATTopSimplify* **CATCreateTopSimplify**(CATGeoFactory* iFactory,
                         CATTopData* iData,
                        CATBody* iBodyToSimplify)  
      
    
    **CATVertexOperator::CATVertexOperator**(
          CATGeoFactory* iFactory,
          CATPoint* iPoint,
          CATBody* iTargetBody=NULL,
          CATBodyFreezeMode iBodyfreezemode,
          CATCGMJournalList* iJournal)

| 
    
    
    **CATTopVertex*
    CATCreateTopVertex**(CATGeoFactory* iFactory,
                       CATTopData* iData,
                       CATPoint* iPoint)  
      
    
    **CATWireOperator::CATWireOperator**(
          CATGeoFactory* iFactory,
          int iNbCurves,
          CATCurve** iCurves,
          CATCrvLimits* iLimits,
          short* iOrientations,
          CATBody* iTargetBody=NULL,
          CATBodyFreezeMode iBodyfreezemode,
          CATCGMJournalList *iJournal)

| 
    
    
    **CATTopWire*
    CATCreateTopWire**(CATGeoFactory* iFactory,
                     CATTopData* iData,
                     int iNbCurves,
                     CATCurve** iCurves,
                     CATCrvLimits* iLimits,
                     short* iOrientations)  
  
[Top]
#### AdvancedTopologicalOpe

Deprecated Signature | New Signature  
---|---  
      
    
    CATThickenOp*
    **CATCreateThickenOp**(CATGeoFactory* iFactory,
                       CATBody* iBody,
                       double iOffset1,
                       double iOffset2,
                       CATCGMJournalList* iJournal)

| 
    
    
    CATThickenOp*
    CATCreateThickenOp(CATGeoFactory* iFactory,
                       CATTopData* iTopData,
                       CATBody* iBody,
                       double iOffset1,
                       double iOffset2)  
      
    
    CATTopologicalBlend* **CreateTopologicalBlend**(CATGeoFactory* iFactory,
                           const CATBody* iWire1,
                           const CATBody* iWire2,
                           const CATBody* iSupport1,
                           const CATBody* iSupport2,
                           CATSkillValue iMode,
                           CATCGMJournalList* iJournal);

| 
    
    
    CATTopologicalBlend*
    **CATCreateTopologicalBlend**(CATGeoFactory* iFactory,
                              CATTopData* iTopData,
                              const CATBody* iWire1,
                              const CATBody* iWire2,
                              const CATBody* iSupport1,
                              const CATBody* iSupport2)  
      
    
    CATTopologicalBlend*
    **CreateTopologicalBlend**(CATGeoFactory* iFactory,
                           const CATBody* iWire1,
                           const CATBody* iWire2,
                           CATSkillValue iMode,
                           CATCGMJournalList* iJournal)

| 
    
    
    CATTopologicalBlend*
    **CATCreateTopologicalBlend**(CATGeoFactory* iFactory,
                              CATTopData* iTopData,
                              const CATBody* iWire,
                              const CATBody* iSupport )  
      
    
    CATTopologicalBlendCurve* **CreateTopologicalBlendCurve**(CATGeoFactory* iFactory,
                                CATBody* iWire1,
                                CATBody* iWireParam1,
                                CATBody* iWire2,
                                CATBody* iWireParam2,
                                CATBody* iTargetBody,
                                CATBodyFreezeMode iMode,
                                CATCGMJournalList* iJournal,
                                CATSkillValue iMode)

| 
    
    
    CATTopologicalBlendCurve*
    **CATCreateTopologicalBlendCurve**(CATGeoFactory* iFactory,
                                   CATTopData* iData,
                                   CATBody* iWire1,
                                   CATBody* iWireParam1,
                                   CATBody* iWire2,
                                   CATBody* iWireParam2)  
      
    
    CATTopologicalFill* **CreateTopologicalFill**(CATGeoFactory* iFactory,
                          const long iNumberOfWires,
                          const CATBody** iArrayOfWires,
                          CATSkillValue iMode,
                          CATCGMJournalList *iJournal)

| 
    
    
    CATTopologicalFill* **CATCreateTopologicalFill**(CATGeoFactory* iFactory,
                             CATTopData* iTopData,
                             const long iNumberOfWires,
                             const CATBody** iArrayOfWires,
                             CATSkillValue iMode)  
      
    
    CATTopologicalFill* **CreateTopologicalFill**(CATGeoFactory* iFactory,
                          const long iNumberOfWires,
                          const CATBody** iBodyWires,
                          const CATBody** iBodySupports,
                          CATSkillValue iMode,
                          CATCGMJournalList* iJournal)

| 
    
    
    CATTopologicalFill* **CATCreateTopologicalFill**(CATGeoFactory* iFactory,
                             CATTopData* iTopData,
                             const long iNumberOfWires,
                             const CATBody** iBodyWires,
                             const CATBody** iBodySupports,
                             CATSkillValue iMode)  
      
    
    CATTopologicalFilletBlend* **CreateTopologicalFilletBlend**(CATGeoFactory* iFactory,
                                 const CATBody* iBodySupport1,
                                 const CATBody* iBodySupport2,
                                 long iOrientation1,
                                 long iOrientation2,
                                 double iRadius,
                                 const CATDomain* iDomainSupport1,
                                 const CATDomain* iDomainSupport2,
                                 CATSkillValue iMode,
                                 CATCGMJournalList* iReport)

| 
    
    
    CATTopologicalFilletBlend* **CATCreateTopologicalFilletBlend**(CATGeoFactory* iFactory,
                                    CATTopData* iTopData,
                                    const CATBody* iBodySupport1,
                                    const CATBody* iBodySupport2,
                                    long iOrientation1,
                                    long iOrientation2,
                                    double iRadius,
                                    const CATDomain* iDomainSupport1,
                                    const CATDomain* iDomainSupport2)  
      
    
    CATTopologicalMatch* **CreateTopologicalMatch**(CATGeoFactory* iFactory,
                           CATBody** iWire1,
                           CATBody** iWire2,
                           long iNbWires,
                           CATBody* iSupport1,
                           CATBody** iSupport2,
                           CATSkillValue iMode,
                           CATCGMJournalList* iJournal)

| 
    
    
    CATTopologicalMatch* **CATCreateTopologicalMatch**(CATGeoFactory* iFactory,
                              CATTopData* iTopData,
                              CATBody** iWire1,
                              CATBody** iWire2,
                              long iNbWires,
                              CATBody* iSupport1,
                              CATBody** iSupport2,
                              CATSkillValue iMode)  
      
    
    CATTopologicalMatch* **CreateTopologicalMatchBoth**(CATGeoFactory* iFactory,
                               CATBody* iWire1,
                               CATBody* iWire2,
                               CATBody* iSupport1,
                               CATBody* iSupport2,
                               CATSkillValue iMode,
                               CATCGMJournalList* iJournal)

| 
    
    
    CATTopologicalMatch* **CATCreateTopologicalMatchBoth**(CATGeoFactory* iFactory,
                                  CATTopData* iTopData,
                                  CATBody* iWire1,
                                  CATBody* iWire2,
                                  CATBody* iSupport1,
                                  CATBody* iSupport2,
                                  CATSkillValue iMode)  
      
    
    CATTopSweep* **CATTopCreateSweep**(CATGeoFactory* iGeoFactory,
                      CATBody* iCenterBody,
                      CATGeometry* iCenterSupport,
                      CATBody* iSpineBody,
                      CATBody* iProfile,
                      CATCGMJournalList* iJournal)

| 
    
    
    CATTopSweep*
    **CATCreateTopSweep**(CATGeoFactory* iGeoFactory,
                      CATTopData* iData,
                      CATBody* iCenterBody,
                      CATGeometry* iCenterSupport,
                      CATBody* iSpineBody,
                      CATBody* iProfile)  
  
[Top]
#### BasicTopologicalOpe

Deprecated Signature | New Signature  
---|---  
      
    
    CATTopHelixOperator* **CATCreateTopHelixOperator**(CATGeoFactory* iFactory,
                              CATBody* iHelixAxis,
                              long iHelixAxisOrientation,
                              CATBody* iHelixOrigin,
                              CATAngle iStartAngle,
                              CATAngle iEndAngle,
                              CATLength iPitch,
                              long iTrigoOrientation,
                              CATCGMJournalList* iJournal)

| 
    
    
    CATTopHelixOperator*
    CATCreateTopHelixOperator(CATGeoFactory* iFactory,
                              CATTopData* iTopData,
                              CATBody* iHelixAxis,
                              long iHelixAxisOrientation,
                              CATBody* iHelixOrigin,
                              CATAngle iStartAngle,
                              CATAngle iEndAngle,
                              CATLength iPitch,
                              long iTrigoOrientation)  
      
    
    CATTopSweep* **CATTopCreateSweep**(CATGeoFactory* iFactory,
                      CATBody* iCenterBody,
                      CATGeometry* iCenterSupport,
                      CATBody* iSpineBody,
                      CATBody* iProfile,
                      CATCGMJournalList* iJournal)

| 
    
    
    CATTopLineOperator*
    CATCreateTopLineOperatorNormalToShell(
                              CATGeoFactory* iFactory,
                              CATTopData* iTopData,
                              CATBody* iOriginPoint,
                              CATBody* iShellOfPoint,
                              double iLength)  
      
    
    CATTopLineOperator*
    **CATCreateTopLineOperatorAngledTangentToWire**(
                      CATGeoFactory* iFactory,
                      CATBody* iOriginPoint,
                      CATBody* iCurve,
                      CATBody* iShellOfCurve,
                      double iLength,
                      CATAngle iAngle,
                      CATCGMJournalList* iJournal)

| 
    
    
    CATTopLineOperator*
    CATCreateTopLineOperatorAngledTangentToWire(
                              CATGeoFactory* iFactory,
                              CATTopData* iTopData,
                              CATBody* iOriginPoint,
                              CATBody* iCurve,
                              CATBody* iShellOfCurve,
                              double iLength,
                              CATAngle iAngle)  
      
    
    CATTopLineOperator*
    **CATCreateTopLineOperatorTangentToWire**(
                      CATGeoFactory* iFactory,
                      CATBody* iOriginPoint,
                      CATBody* iCurve,
                      double iLength,
                      CATCGMJournalList* iJournal)

| 
    
    
    CATTopLineOperator*
    CATCreateTopLineOperatorTangentToWire(
                              CATGeoFactory* iFactory,
                              CATTopData* iTopData,
                              CATBody* iOriginPoint,
                              CATBody* iCurve,
                              double iLength)  
      
    
    CATTopLineOperator*
    **CATCreateTopLineOperatorFromDirection**(
                      CATGeoFactory* iFactory,
                      CATBody* iOriginPoint,
                      const CATMathVector& iDirection,
                      double iLength,
                      CATCGMJournalList* iJournal)

| 
    
    
    CATTopLineOperator*
    CATCreateTopLineOperatorFromDirection(
                              CATGeoFactory* iFactory,
                              CATTopData* iTopData,
                              CATBody* iOriginPoint,
                              const CATMathVector& iDirection,
                              double iLength)  
      
    
    CATTopLineOperator*
    **CATCreateTopLineOperatorFromPoints**(
                      CATGeoFactory* iFactory,
                      CATBody* iOriginPoint,
                      CATBody* iSecondPoint,
                      CATCGMJournalList* iJournal)

| 
    
    
    CATTopLineOperator*
    CATCreateTopLineOperatorFromPoints(
                              CATGeoFactory* iFactory,
                              CATTopData* iTopData,
                              CATBody* iOriginPoint,
                              CATBody* iSecondPoint)  
      
    
    CATTopPointOperator*
    **CATCreateTopPointOperator**(CATGeoFactory * iFactory,
                              CATCGMJournalList* iJournal)

| 
    
    
    CATTopPointOperator*
    CATCreateTopPointOperator(CATGeoFactory* iFactory,
                              CATTopData* iTopData)  
      
    
    CATTopSplineOperator* **CATCreateTopSplineOperator**(CATGeoFactory* iFactory,
                               long iNbpts,
                               CATBody** iListOfPoints,
                               const CATMathVector* iTangents,
                               const CATMathVector* iCurvatures,
                               const long* iImposition,
                               CATCGMJournalList* iJournal)

| 
    
    
    CATTopSplineOperator*
    CATCreateTopSplineOperator(CATGeoFactory* iFactory,
                               CATTopData* iTopData,
                               long iNbpts,
                               CATBody** iListOfPoints,
                               const CATMathVector* iTangents,
                               const CATMathVector* iCurvatures,
                               const long* iImposition)  
  
[Top]
#### Case of the Journal

If you directly create a CATCGMJournalList, you must now give the software configuration that must be use.

Deprecated Signature | New Signature  
---|---  
      
    
    CATCGMJournalList::CATCGMJournalList
           (CATCGMJournalList* ioList)

| 
    
    
    CATCGMJournalList::CATCGMJournalList
          (CATSoftwareConfiguration* iConfig,
           CATCGMJournalList* ioList)  
  
[Top]

* * *
### In Short

  * The versioning allows an operator to be replayed with a special software configuration. The software configuration is given to the operator by the mean of a CATTopData instance.
  * This enhancement leads to interface modifications, and the correspondence of the deprecated and new methods is given.

[Top]

* * *
### References

[1] | [The CGM Journal](TopoJournal.md)  
---|---  
[2] | [Overview of the Topological Operators](../CAATopUseCases/CAATopOverview.md)  
[Top]  
  
* * *
### History

Version: **1** [Oct 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
