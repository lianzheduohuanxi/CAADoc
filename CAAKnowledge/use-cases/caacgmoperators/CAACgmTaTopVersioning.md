---
```vbscript
title: "Understanding the Versioning of the Topological Operators"
category: "use-case"
module: "CAACgmOperators"
tags: []
source_file: "Doc/online/CAACgmOperators/CAACgmTaTopVersioning.htmmd"
converted: "2026-05-11T17:33:48.710152"
```

---
tags: []
source_file: "Doc/online/CAACgmOperators/CAACgmTaTopVersioning.htmmd"
converted: "2026-05-11T17:33:48.710152"
Understanding the Versioning of the Topological Operators

---
converted: "2026-05-11T17:33:48.710152"
Understanding the Versioning of the Topological Operators
Technical Article
Abstract The topological operators create new bodies from input bodies, depending on an internal algorithm. For maintenance or enhancement reasons, this internal algorithm may change, so that the results could not be exactly the same after the code modification. The operator versioning is a way to always replay an operator with the same level of software. This can be needed by applications that store the specifications of their operations, such as the feature applications. To put this mechanism in place, existing interfaces are modified, and the migration process is explained.

    * Principle
      * The CATSoftwareConfiguration Class
      * The CATTopData Class
    * Migration
      * TopologicalOperators
      * BasicTopologicalOpe
      * AdvancedTopologicalOpe
      * Case of the Journal
    * In Short
    * References
---
Principle If an application stores the way to build an object, and gives the mean to replay this definition, it expects that the replay always gives the same result. Up to now, for maintenance or enhancement reasons, the software modifications could lead to slightly different results. To avoid this situation, the current software configuration of an operator is accessible, and an operator can be replayed with a given software configuration: we call that the operator versioning. The CATSoftwareConfiguration Class The class that manages the operator versioning is the _CATSoftwareConfiguration_ class of the Mathematics framework. This class:
    * Creates an open configuration for the current software level.
    * Creates a closed configuration. (That can be read from a previously streamed configuration with a specific method. See also the Part documentation.)
    * Streams an existing configuration.
    * Tests whether a configuration is supported by the current software.
To create an open configuration (a configuration for the current software level), use the default constructor. Notice that you must use the `new` operator.

    // Defines an open configuration for the operator
To create an open configuration (a configuration for the current software level), use the default constructor. Notice that you must use the `new` operator.
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration(#);

```vbscript
If you use feature applications, please refer to their documentation to see how to retrieve the configuration associated with a given feature. The configuration must be released after use in the following way:

```

    // Releases the configuration after the deletion of the operators
CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration(#);
If you use feature applications, please refer to their documentation to see how to retrieve the configuration associated with a given feature. The configuration must be released after use in the following way:
    pConfig->**Release**(#);

The CATTopData Class Once created, the configuration instance is given to the topological operator to inform it of the level of software it must use during its run. The software configuration is not given directly to the operator, but by the mean of the class _CATTopData_ that contains:

    * A pointer to the configuration, that must be not `NULL`.
    * A pointer to the journal [1] of the operator. This pointer can be `NULL` : in this case, the journal is not filled.
pConfig->**Release**(#);
The CATTopData Class Once created, the configuration instance is given to the topological operator to inform it of the level of software it must use during its run. The software configuration is not given directly to the operator, but by the mean of the class _CATTopData_ that contains:
We give here an example for creating a `CATTopSkin` operator, that is fully commented in _Overview of the topological operators_ [2].

    // defines the data of the operator: configuration + journal
We give here an example for creating a `CATTopSkin` operator, that is fully commented in _Overview of the topological operators_ [2].
    CATTopData topdata(pConfig,NULL);

    // now creates the operator
We give here an example for creating a `CATTopSkin` operator, that is fully commented in _Overview of the topological operators_ [2].
CATTopData topdata(pConfig,NULL);
    CATTopSkin * pSkinOp = **::CATCreateTopSkin** (piGeomFactory,// the pointer to the factory for the creation of the result

                                               **& topdata**,     // the topological data
CATTopData topdata(pConfig,NULL);
CATTopSkin * pSkinOp = **::CATCreateTopSkin** (piGeomFactory,// the pointer to the factory for the creation of the result
                                               piPlane,
                                               nbPCurves,
                                               aPCurves,
                                               aLimits,
                                               aOrientations);

All the operators are based on the same frame: the pointer to the factory for the creation of the resulting body is the first argument, the not `NULL` pointer to the topological data containing the configuration and the journal is the second argument. Migration As now an operator must know the configuration software on which it must run, this argument becomes mandatory. The following table indicates the correspondence between the old signature and the new signature for the operators of the TopologicalOperators, AdvancedTopologicalOpe, BasicTopologicalOpe frameworks. Be careful that migration can also affect the class of the operator. Topological Operators Deprecated Signature | New Signature

    **CATHybOperator*
All the operators are based on the same frame: the pointer to the factory for the creation of the resulting body is the first argument, the not `NULL` pointer to the topological data containing the configuration and the journal is the second argument. Migration As now an operator must know the configuration software on which it must run, this argument becomes mandatory. The following table indicates the correspondence between the old signature and the new signature for the operators of the TopologicalOperators, AdvancedTopologicalOpe, BasicTopologicalOpe frameworks. Be careful that migration can also affect the class of the operator. Topological Operators Deprecated Signature | New Signature
    CreateHybSkinAssembly**(CATGeoFactory* iFactory,
                          ListPOfCATBody* iBodiesToAssemble,
                          CATCGMJournalList* iJournal)

    **CATHybOperator*
CreateHybSkinAssembly**(CATGeoFactory* iFactory,
ListPOfCATBody* iBodiesToAssemble,
CATCGMJournalList* iJournal)
    CreateHybWireAssembly**(CATGeoFactory* iFactory,
                          ListPOfCATBody* iBodiesToAssemble,
                          CATCGMJournalList* iJournal)

|

    **CATHybAssemble*
CATCGMJournalList* iJournal)
    CATCreateTopAssemble**(CATGeoFactory* iFactory,
                         CATTopData* iData,
                         ListPOfCATBody* iBodiesToAssemble)

    **CATHybOperator*
CATCreateTopAssemble**(CATGeoFactory* iFactory,
CATTopData* iData,
ListPOfCATBody* iBodiesToAssemble)
    CreateHybIntersect**(CATGeoFactory* iFactory,
                       CATBody* iBody1ToIntersect,
                       CATBody* iBody2ToIntersect,
                       CATCGMJournalList* iReport)

|

    **CATHybIntersect*
CATCGMJournalList* iReport)
    CATCreateTopIntersect**(CATGeoFactory* iFactory,
                          CATTopData* iData,
                          CATBody* iBody1ToIntersect,
                          CATBody* iBody2ToIntersect)

    **CATHybOperator*
CATTopData* iData,
CATBody* iBody1ToIntersect,
CATBody* iBody2ToIntersect)
    CreateHybProject**(CATGeoFactory* iFactory,
                     CATBody* iBodyToProject,
                     CATBody* iBodySupport,
                     const CATMathDirection* iDirection,
                     CATCGMJournalList* iJournal)

|

    **CATHybProject*
CATCGMJournalList* iJournal)
    CATCreateTopProject**(CATGeoFactory* iFactory,
                        CATTopData* iData,
                        CATBody* iBodyToProject,
                        CATBody* iBodySupport,
                        CATMathDirection* iDirection)

    **CATHybOperator*
CATBody* iBodyToProject,
CATBody* iBodySupport,
CATMathDirection* iDirection)
    CreateHybSplit**(CATGeoFactory* iFactory,
                   CATBody* iBodyToSplit,
                   short iSideToKeep,
                   CATBody* iSplittingBody,
                   CATBody* iCuttingBody,
                   CATCGMJournalList* iJournal)

|

    **CATHybSplit*
CATCGMJournalList* iJournal)
    CATCreateTopSplit**(CATGeoFactory* iFactory,
                      CATTopData* iData,
                      CATBody* iBodyToSplit,
                      short iSideToKeep,
                      CATBody* iSplittingBody,
                      CATBody* iCuttingBody)

    **CATHybOperator*
short iSideToKeep,
CATBody* iSplittingBody,
CATBody* iCuttingBody)
    CreateHybTrim**(CATGeoFactory* iFactory,
                  CATBody* iFirstBodyToCut,
                  short iFirstSideToKeep,
                  CATBody* iSecondBodyToCut,
                  short iSecondSideToKeep,
                  CATBody* iCuttingBody,
                  CATCGMJournalList* iJournal)

|

    **CATHybTrim*
CATCGMJournalList* iJournal)
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

CATBody *iBody2,
CATSkillValue iMode=BASIC)
    CATDistanceMinBodyBody * **CATCreateDistanceMinTopo**(CATGeoFactory *iFactory,
                     CATTopData *iData,
                     CATBody *iBody1,
                     CATBody *iBody2,
                     CATSkillValue iMode=BASIC)

    CATDynBoolean*

    **CATDynCreateBoolean**(CATGeoFactory* iFactory,
CATBody *iBody2,
CATSkillValue iMode=BASIC)
CATDynBoolean*
                        CATDynBooleanType iOperation,
                        CATBody* iPart,
                        CATBody* iTool,
                        CATCGMJournalList* iJournal)

|

CATBody* iTool,
CATCGMJournalList* iJournal)
    CATDynBoolean*

    **CATCreateDynBoolean**(CATGeoFactory* iFactory,
CATDynBoolean*
                        CATTopData* iData,
                        CATDynBooleanType iOperation,
                        CATBody* iPart,
                        CATBody* iTool)

    CATDynChamfer*

    **CATDynCreateChamfer**(CATGeoFactory* Container,
CATBody* iPart,
CATBody* iTool)
CATDynChamfer*
                        CATBody* iPart,
                        CATCGMJournalList* iJournal)

|

CATBody* iPart,
CATCGMJournalList* iJournal)
    CATDynChamfer*

    **CATCreateDynChamfer**(CATGeoFactory* Container,
CATDynChamfer*
                        CATTopData* iData,
                        CATBody* iPart)

    CATDynDraft*

    **CATDynCreateDraft**(CATGeoFactory* iContainer,
CATTopData* iData,
CATBody* iPart)
CATDynDraft*
                      CATBody* iPart,
                      const CATDynDraftType iType,
                      CATCGMJournalList* iJournal)

|

const CATDynDraftType iType,
CATCGMJournalList* iJournal)
    CATDynDraft*

    **CATCreateDynDraft**(CATGeoFactory* iContainer,
CATDynDraft*
                      CATTopData* iData,
                      CATBody* iPart,
                      const CATDynDraftType iType)

    CATDynFillet*

    **CATDynCreateFillet**(CATGeoFactory* iContainer,
CATBody* iPart,
const CATDynDraftType iType)
CATDynFillet*
                      CATBody* iPart,
                      CATCGMJournalList* iJournal)

|

CATBody* iPart,
CATCGMJournalList* iJournal)
    CATDynFillet*

    **CATCreateDynFillet**(CATGeoFactory* iContainer,
CATDynFillet*
                       CATTopData* iData,
                       CATBody* iPart)

    CATDynShell*

    **CATDynCreateShell**(CATGeoFactory* iForResultingBody,
CATTopData* iData,
CATBody* iPart)
CATDynShell*
                      CATBody* iBody,
                      CATLength iInternal,
                      CATLength iExternal,
                      CATCGMJournalList* iJournal)

|

CATLength iExternal,
CATCGMJournalList* iJournal)
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

CATDynSplitType iSplitType,
CATCGMJournalList* iJournal)
    CATDynSplit*

    **CATCreateDynSplit**(CATGeoFactory* iFactory,
CATDynSplit*
                      CATTopData* iData,
                      CATBody* iBody,
                      CATDynSplitType iSplitType)

    **CATThick::CATThick**(CATBody* iBody,
CATTopData* iData,
CATBody* iBody,
CATDynSplitType iSplitType)
               CATCGMJournalList* iJournal)

|

    **CATDynThickness*
CATCGMJournalList* iJournal)
    CATCreateDynThickness**(CATGeoFactory* iContainer,
                          CATTopData* iTopData,
                          CATBody* iPart)

    CATDynTransformation*

    **CATDynCreateTransformation**(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iPart)
CATDynTransformation*
                               CATBody* iBodytoTransform,
                               CATCGMJournalList* iJournal)

|

CATBody* iBodytoTransform,
CATCGMJournalList* iJournal)
    CATDynTransformation*

    **CATCreateDynTransformation**(CATGeoFactory* iFactory,
CATDynTransformation*
                               CATTopData* iData,
                               CATBody* iBodytoTransform)

  |

CATTopData* iData,
CATBody* iBodytoTransform)
    CATSkinExtrapol*

    **CATCreateSkinExtrapol**(CATGeoFactory* iFactory,
CATSkinExtrapol*
                          CATTopData* iTopData,
                          CATBody * iSkin)

    **CATSkinOperator::CATSkinOperator**(
CATTopData* iTopData,
CATBody * iSkin)
          CATGeoFactory* iFactory,
          CATTopData* iData,
          CATSurface* iSurface)

|

CATTopData* iData,
CATSurface* iSurface)
    CATTopSkin* **CATCreateTopSkin**(CATGeoFactory* iFactory,
                     CATTopData* iData,
                     CATSurface* iSurface,
                     const CATSurLimits* iLims)

    **CATSkinOperator::CATSkinOperator**(
CATTopData* iData,
CATSurface* iSurface,
const CATSurLimits* iLims)
          CATGeoFactory* iFactory,
          int iNbPcurves,
          CATPCurve** iPcurves,
          CATCrvLimits* iLimits,
          short* iOrientations,
          CATBody* iTargetBody=NULL,
          CATBodyFreezeMode iBodyfreezemode,
          CATCGMJournalList* iJournal)

|

CATBodyFreezeMode iBodyfreezemode,
CATCGMJournalList* iJournal)
    CATTopSkin*

    **CATCreateTopSkin**(CATGeoFactory* iFactory,
CATTopSkin*
                     CATTopData* iData,
                     CATSurface* iSurface,
                     int iNbPcurves,
                     CATPCurve** iPcurves,
                     CATCrvLimits* iLimits,
                     short* iOrientations)

    **CATSolidCuboid::CATSolidCuboid**(
CATPCurve** iPcurves,
CATCrvLimits* iLimits,
short* iOrientations)
          CATGeoFactory* iFactory,
          const CATMathPoint& iPt1,
          const CATMathPoint& iPt2,
          const CATMathPoint& iPt3,
          const CATMathPoint& iPt4,
          CATCGMJournalList *iJournal)

|

    **CATSolidCuboid*
CATCGMJournalList *iJournal)
    CATCreateSolidCuboid**(CATGeoFactory* iFactory,
                         CATTopData* iData,
                         const CATMathPoint& iPt1,
                         const CATMathPoint& iPt2,
                         const CATMathPoint& iPt3,
                         const CATMathPoint& iPt4)

    **CATSolidCylinder::CATSolidCylinder**(
const CATMathPoint& iPt2,
const CATMathPoint& iPt3,
const CATMathPoint& iPt4)
          CATGeoFactory* iFactory,
          const CATMathPoint& iFirstPointOnAxis,
          const CATMathPoint& iSecondPointOnAxis,
          const CATMathPoint& iPointOnSurface,
          CATCGMJournalList* iJournal)

|

    **CATSolidCylinder*
CATCGMJournalList* iJournal)
    CATCreateSolidCylinder**(CATGeoFactory* iFactory,
                           CATTopData* iData,
                           const CATMathPoint& iFirstPointOnAxis,
                           const CATMathPoint& iSecondPointOnAxis,
                           const CATMathPoint& iPointOnSurface)

    **CATSolidCylinder::CATSolidCylinder**(
const CATMathPoint& iFirstPointOnAxis,
const CATMathPoint& iSecondPointOnAxis,
const CATMathPoint& iPointOnSurface)
          CATGeoFactory* iFactory,
          const CATMathPoint& iFirstPointOnAxis,
          const CATMathPoint& iSecondPointOnAxis,
          double iRadius,
          CATCGMJournalList* iJournal)

|

    **CATSolidCylinder*
CATCGMJournalList* iJournal)
    CATCreateSolidCylinder**(CATGeoFactory* iFactory,
                           CATTopData* iData,
                           const CATMathPoint& iFirstPointOnAxis,
                           const CATMathPoint& iSecondPointOnAxis,
                           double iRadius)

    **CATSolidPyramid::
const CATMathPoint& iFirstPointOnAxis,
const CATMathPoint& iSecondPointOnAxis,
double iRadius)
          CATSolidPyramid**(CATGeoFactory* iFactory,
          const CATMathPoint& iPt1,
          const CATMathPoint& iPt2,
          const CATMathPoint& iPt3,
          const CATMathPoint& iTop,
          CATCGMJournalList* iJournal)

|

    **CATSolidPyramid*
CATCGMJournalList* iJournal)
    CATCreateSolidPyramid**(CATGeoFactory* iFactory,
                          CATTopData* iData,
                          const CATMathPoint& iPt1,
                          const CATMathPoint& iPt2,
                          const CATMathPoint& iPt3,
                          const CATMathPoint& iTop)

    **CATSolidPyramid::CATSolidPyramid**(
const CATMathPoint& iPt2,
const CATMathPoint& iPt3,
const CATMathPoint& iTop)
          CATGeoFactory* iFactory,
          CATFace* iBase,
          const CATMathPoint& iTop,
          CATCGMJournalList *iJournal)

|

    **CATSolidPyramid*
CATCGMJournalList *iJournal)
    CATCreateSolidPyramid**(CATGeoFactory* iFactory,
                          CATTopData* iData,
                          CATFace* iBase,
                          const CATMathPoint& iTop)

    **CATSolidSphere::CATSolidSphere**(
CATTopData* iData,
CATFace* iBase,
const CATMathPoint& iTop)
          CATGeoFactory* iFactory,
          const CATMathPoint& iCenter,
          double iRadius,
          CATCGMJournalList* iJournal)

|

    **CATSolidSphere*
CATCGMJournalList* iJournal)
    CATCreateSolidSphere**(CATGeoFactory* iFactory,
                         CATTopData* iData,
                         const CATMathPoint& iCenter,
                         double iRadius)

    **CATSolidTorus::CATSolidTorus**(
CATTopData* iData,
const CATMathPoint& iCenter,
double iRadius)
          CATGeoFactory* iFactory,
          const CATMathAxis& iAxis,
          const CATMathPoint& iMajor,
          const CATMathPoint& iMinor,
          CATCGMJournalList *iJournal)

|

    **CATSolidTorus*
CATCGMJournalList *iJournal)
    CATCreateSolidTorus**(CATGeoFactory* iFactory,
                        CATTopData* iData,
                        const CATMathAxis& iAxis,
                        const CATMathPoint& iMajor,
                        const CATMathPoint& iMinor)

    **CATThick::CATThick**(
const CATMathAxis& iAxis,
const CATMathPoint& iMajor,
const CATMathPoint& iMinor)
          CATBody* iBody,
          CATCGMJournalList* iJournal)

|

    **CATDynThickness*
CATCGMJournalList* iJournal)
    CATCreateDynThickness**(CATGeoFactory* iFactory,
                          CATTopData* iTopData,
                          CATBody* iPart)

    CATTopCorner*

    **CreateTopOpCorner**(CATGeoFactory* iFactory,
CATTopData* iTopData,
CATBody* iPart)
CATTopCorner*
                      CATBody * iCurve1,
                      CATBody * iCurve2,
                      CATBody * iSupport,
                      double iRadius,
                      CATCGMJournalList* iJournalList)

|

double iRadius,
CATCGMJournalList* iJournalList)
    CATTopCorner*

    **CATCreateTopCorner**(CATGeoFactory* iFactory,
CATTopCorner*
                       CATTopData* iTopData,
                       CATBody* iCurve1,
                       CATBody* iCurve2,
                       CATBody* iSupport,
                       double iRadius)

    CATTopDevelop*

    **CreateTopOpDevelop**(CATGeoFactory* iFactory,
CATBody* iSupport,
double iRadius)
CATTopDevelop*
                       CATBody* iWire,
                       CATBody* iWireSupport,
                       CATBody* iTargetSupport,
                       CATSurTo2DGlobalMapping* iMappingIn,
                       CATSurTo2DGlobalMapping* iMappingOut,
                       CATCGMJournalList *iReport)

|

CATSurTo2DGlobalMapping* iMappingOut,
CATCGMJournalList *iReport)
    CATTopDevelop*

    **CATCreateTopDevelop**(CATGeoFactory* iFactory,
CATTopDevelop*
                        CATTopData* iData,
                        CATBody* iWire,
                        CATBody* iWireSupport,
                        CATBody* iTargetSupport,
                        CATSurTo2DGlobalMapping* iMappingIn,
                        CATSurTo2DGlobalMapping* iMappingOut)

    CATTopParallel*

    **CreateTopOpAllParallel**(CATGeoFactory* iFactory,
CATSurTo2DGlobalMapping* iMappingIn,
CATSurTo2DGlobalMapping* iMappingOut)
CATTopParallel*
                           CATBody* iCurve,
                           CATBody* iSupport,
                           CATDistanceTool* iDistance,
                           CATCGMJournalList* iJournal,
                           CATLaw** iMappingLaws)

|

CATCGMJournalList* iJournal,
CATLaw** iMappingLaws)
    CATTopParallel*

    **CATCreateTopParallel**(CATGeoFactory* iFactory,
CATTopParallel*
                         CATTopData* iData,
                         CATBody* iCurve,
                         CATBody* iSupport,
                         CATDistanceTool* iDistance)

    CATTopPrism*

    **CATTopCreatePrism**(CATGeoFactory* iFactory,
CATBody* iSupport,
CATDistanceTool* iDistance)
CATTopPrism*
                      CATBody* iProfileBody,
                      CATMathDirection* iDirection,
                      CATLength iStartOffset,
                      CATLength iEndOffset,
                      CATCGMJournalList* iJournal)

|

CATLength iEndOffset,
CATCGMJournalList* iJournal)
    CATTopPrism*

    **CATCreateTopPrism**(CATGeoFactory* iFactory,
CATTopPrism*
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

CATAngle iEndAngle,
CATCGMJournalList* iJournal)
    CATTopRevol* **CATCreateTopRevol**(CATGeoFactory* iFactory,
                      CATTopData* iData,
                      CATBody* iProfile,
                      CATMathAxis* iAxis,
                      CATAngle iStartAngle,
                      CATAngle iEndAngle)

  |

CATAngle iStartAngle,
CATAngle iEndAngle)
    CATTopSimplify* **CATCreateTopSimplify**(CATGeoFactory* iFactory,
                         CATTopData* iData,
                        CATBody* iBodyToSimplify)

    **CATVertexOperator::CATVertexOperator**(
CATTopSimplify* **CATCreateTopSimplify**(CATGeoFactory* iFactory,
CATTopData* iData,
CATBody* iBodyToSimplify)
          CATGeoFactory* iFactory,
          CATPoint* iPoint,
          CATBody* iTargetBody=NULL,
          CATBodyFreezeMode iBodyfreezemode,
          CATCGMJournalList* iJournal)

|

    **CATTopVertex*
CATCGMJournalList* iJournal)
    CATCreateTopVertex**(CATGeoFactory* iFactory,
                       CATTopData* iData,
                       CATPoint* iPoint)

    **CATWireOperator::CATWireOperator**(
CATCreateTopVertex**(CATGeoFactory* iFactory,
CATTopData* iData,
CATPoint* iPoint)
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
CATCGMJournalList *iJournal)
    CATCreateTopWire**(CATGeoFactory* iFactory,
                     CATTopData* iData,
                     int iNbCurves,
                     CATCurve** iCurves,
                     CATCrvLimits* iLimits,
                     short* iOrientations)

AdvancedTopologicalOpe Deprecated Signature | New Signature

short* iOrientations)
AdvancedTopologicalOpe Deprecated Signature | New Signature
    CATThickenOp*

    **CATCreateThickenOp**(CATGeoFactory* iFactory,
AdvancedTopologicalOpe Deprecated Signature | New Signature
CATThickenOp*
                       CATBody* iBody,
                       double iOffset1,
                       double iOffset2,
                       CATCGMJournalList* iJournal)

|

double iOffset2,
CATCGMJournalList* iJournal)
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

CATSkillValue iMode,
CATCGMJournalList* iJournal);
    CATTopologicalBlend*

    **CATCreateTopologicalBlend**(CATGeoFactory* iFactory,
CATTopologicalBlend*
                              CATTopData* iTopData,
                              const CATBody* iWire1,
                              const CATBody* iWire2,
                              const CATBody* iSupport1,
                              const CATBody* iSupport2)

    CATTopologicalBlend*

    **CreateTopologicalBlend**(CATGeoFactory* iFactory,
const CATBody* iSupport1,
const CATBody* iSupport2)
CATTopologicalBlend*
                           const CATBody* iWire1,
                           const CATBody* iWire2,
                           CATSkillValue iMode,
                           CATCGMJournalList* iJournal)

|

CATSkillValue iMode,
CATCGMJournalList* iJournal)
    CATTopologicalBlend*

    **CATCreateTopologicalBlend**(CATGeoFactory* iFactory,
CATTopologicalBlend*
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

CATCGMJournalList* iJournal,
CATSkillValue iMode)
    CATTopologicalBlendCurve*

    **CATCreateTopologicalBlendCurve**(CATGeoFactory* iFactory,
CATTopologicalBlendCurve*
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

CATSkillValue iMode,
CATCGMJournalList *iJournal)
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

CATSkillValue iMode,
CATCGMJournalList* iJournal)
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

CATSkillValue iMode,
CATCGMJournalList* iReport)
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

CATSkillValue iMode,
CATCGMJournalList* iJournal)
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

CATSkillValue iMode,
CATCGMJournalList* iJournal)
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

CATBody* iProfile,
CATCGMJournalList* iJournal)
    CATTopSweep*

    **CATCreateTopSweep**(CATGeoFactory* iGeoFactory,
CATTopSweep*
                      CATTopData* iData,
                      CATBody* iCenterBody,
                      CATGeometry* iCenterSupport,
                      CATBody* iSpineBody,
                      CATBody* iProfile)

BasicTopologicalOpe Deprecated Signature | New Signature

CATBody* iProfile)
BasicTopologicalOpe Deprecated Signature | New Signature
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

long iTrigoOrientation,
CATCGMJournalList* iJournal)
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

CATBody* iProfile,
CATCGMJournalList* iJournal)
    CATTopLineOperator*
    CATCreateTopLineOperatorNormalToShell(
                              CATGeoFactory* iFactory,
                              CATTopData* iTopData,
                              CATBody* iOriginPoint,
                              CATBody* iShellOfPoint,
                              double iLength)

    CATTopLineOperator*

    **CATCreateTopLineOperatorAngledTangentToWire**(
CATBody* iShellOfPoint,
double iLength)
CATTopLineOperator*
                      CATGeoFactory* iFactory,
                      CATBody* iOriginPoint,
                      CATBody* iCurve,
                      CATBody* iShellOfCurve,
                      double iLength,
                      CATAngle iAngle,
                      CATCGMJournalList* iJournal)

|

CATAngle iAngle,
CATCGMJournalList* iJournal)
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
double iLength,
CATAngle iAngle)
CATTopLineOperator*
                      CATGeoFactory* iFactory,
                      CATBody* iOriginPoint,
                      CATBody* iCurve,
                      double iLength,
                      CATCGMJournalList* iJournal)

|

double iLength,
CATCGMJournalList* iJournal)
    CATTopLineOperator*
    CATCreateTopLineOperatorTangentToWire(
                              CATGeoFactory* iFactory,
                              CATTopData* iTopData,
                              CATBody* iOriginPoint,
                              CATBody* iCurve,
                              double iLength)

    CATTopLineOperator*

    **CATCreateTopLineOperatorFromDirection**(
CATBody* iCurve,
double iLength)
CATTopLineOperator*
                      CATGeoFactory* iFactory,
                      CATBody* iOriginPoint,
                      const CATMathVector& iDirection,
                      double iLength,
                      CATCGMJournalList* iJournal)

|

double iLength,
CATCGMJournalList* iJournal)
    CATTopLineOperator*
    CATCreateTopLineOperatorFromDirection(
                              CATGeoFactory* iFactory,
                              CATTopData* iTopData,
                              CATBody* iOriginPoint,
                              const CATMathVector& iDirection,
                              double iLength)

    CATTopLineOperator*

    **CATCreateTopLineOperatorFromPoints**(
const CATMathVector& iDirection,
double iLength)
CATTopLineOperator*
                      CATGeoFactory* iFactory,
                      CATBody* iOriginPoint,
                      CATBody* iSecondPoint,
                      CATCGMJournalList* iJournal)

|

CATBody* iSecondPoint,
CATCGMJournalList* iJournal)
    CATTopLineOperator*
    CATCreateTopLineOperatorFromPoints(
                              CATGeoFactory* iFactory,
                              CATTopData* iTopData,
                              CATBody* iOriginPoint,
                              CATBody* iSecondPoint)

    CATTopPointOperator*

    **CATCreateTopPointOperator**(CATGeoFactory * iFactory,
CATBody* iOriginPoint,
CATBody* iSecondPoint)
CATTopPointOperator*
                              CATCGMJournalList* iJournal)

|

CATCGMJournalList* iJournal)
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

const long* iImposition,
CATCGMJournalList* iJournal)
    CATTopSplineOperator*
    CATCreateTopSplineOperator(CATGeoFactory* iFactory,
                               CATTopData* iTopData,
                               long iNbpts,
                               CATBody** iListOfPoints,
                               const CATMathVector* iTangents,
                               const CATMathVector* iCurvatures,
                               const long* iImposition)

```vbscript
Case of the Journal If you directly create a CATCGMJournalList, you must now give the software configuration that must be use. Deprecated Signature | New Signature

```

const long* iImposition)
Case of the Journal If you directly create a CATCGMJournalList, you must now give the software configuration that must be use. Deprecated Signature | New Signature
    CATCGMJournalList::CATCGMJournalList
           (CATCGMJournalList* ioList)

|

CATCGMJournalList::CATCGMJournalList
(CATCGMJournalList* ioList)
    CATCGMJournalList::CATCGMJournalList
          (CATSoftwareConfiguration* iConfig,
           CATCGMJournalList* ioList)

In Short

    * The versioning allows an operator to be replayed with a special software configuration. The software configuration is given to the operator by the mean of a CATTopData instance.
    * This enhancement leads to interface modifications, and the correspondence of the deprecated and new methods is given.
CATCGMJournalList* ioList)
In Short
References [1] | [Understanding the CGM Journal](CAACgmTaTopJournal.md)

[2] | [Overview of the Topological Operators](CAACgmUcTopOverview.md)
History Version: **1** [Oct 2000] | Document created
---|---
