---
title: "New C++ Authorized APIs in CAA V5R20 GA"
category: "use-case"
module: "CAACenQuickRefs"
tags: "["CATI2DLayoutClipping", "CATIEcvPercentFill", "CATIPDMUELoadProcess", "CATIPrintableDrafting", "CATISamImageAttributes", "CATICfgEffVal", "CATIMfgMultiAxisCurveMachining", "CATIMfgPPMachine", "CATICGMOperator", "CATIElbDeviceInstance", "CATIBRepAccess_var", "CATICGMVirtual", "CATISysFileAccessStatisticsSettingAtt", "CATITPSDimVisu", "CATISamImageFilters", "CATIAApplicationFrame", "CATIntersectionHVertexType", "CATIAV4Interfaces", "CATIA", "CATISamImageAxisSystem"]"
source_file: "Doc/online/CAACenQuickRefs/CAACenV5R20GANewCPPAPI.htm"
converted: "2026-05-11T17:33:47.475080"
---
tags: ["CATI2DLayoutClipping", "CATIEcvPercentFill", "CATIPDMUELoadProcess", "CATIPrintableDrafting", "CATISamImageAttributes", "CATICfgEffVal", "CATIMfgMultiAxisCurveMachining", "CATIMfgPPMachine", "CATICGMOperator", "CATIElbDeviceInstance", "CATIBRepAccess_var", "CATICGMVirtual", "CATISysFileAccessStatisticsSettingAtt", "CATITPSDimVisu", "CATISamImageFilters", "CATIAApplicationFrame", "CATIntersectionHVertexType", "CATIAV4Interfaces", "CATIA", "CATISamImageAxisSystem"]
source_file: "Doc/online/CAACenQuickRefs/CAACenV5R20GANewCPPAPI.htmmd"
converted: "2026-05-11T17:33:47.475080"
CAA V5 Encyclopedia |  New C++ Authorized APIs in CAA V5R20 GA

* * *

The following are the new CAA V5R20 GA C++ Authorized APIs, compared with CAA V5R19 at GA level.

  * ABQConstants
    * Enumeration LocalAxisSystemTypeEnum
  * ApplicationFrame
```cpp
    * Global Function CATAfrIsUndoRedoLocked
  * CATAnalysisVisuInterfaces
```
    * Enumeration CATSamAxisSystemType
    * Enumeration CATSamColorType
    * Enumeration CATSamComparisonOperator
    * Enumeration CATSamComplexPart
    * Enumeration CATSamCoordinateSystem
    * Enumeration CATSamFilterDomain
    * Enumeration CATSamSymbolType
    * Interface CATISamImageAttributes
    * Interface CATISamImageAxisSystem
    * Interface CATISamImageFilters
  * CATCommonLayoutInterfaces
    * Class CATEEcvPercentFillAdapter
    * Class CATEcwLightNwkArcForPercentFill
    * Class CATEcwLightNwkCableForPercentFill
    * Class CATEcwLightNwkNodeForPercentFill
    * Interface CATIEcvPercentFill
  * CATIAApplicationFrame
    * Class CATCafSearchInformationAdapter
```cpp
    * Global Function CATCafSetApplyFilterMode
    * Interface CATISearchInformation
```
  * CATIAV4Interfaces
    * Class CATListPtrCATV4iV4Attributes
    * Class CATV4iV4Attribute
    * Enumeration AttributeFormat
```cpp
    * Global Function CATV4iGetCombinedTub
    * Global Function CATV4iGetElbowTubeData
    * Global Function CATV4iGetModelComment
    * Global Function CATV4iGetTubConnectors
    * Global Function CATV4iGetTubGeoData
    * Global Function CATV4iGetTubLineName
    * Global Function CATV4iGetTubLineOD
    * Global Function CATV4iGetTubType
    * Global Function CATV4iGetV4Attributes
    * Global Function CATV4iGislnk
    * Global Function CATV4iPibroc
    * Global Function CATV4iPibrte
  * CATPDMBase
```
```cpp
    * Global Function SaveToPDM
  * CATPDMBaseInterfaces
```
    * Interface CATIPDMUELoadProcess
  * CATPlantShipInterfaces
    * Macro or #define Validation_RootObject
  * CATTPSInterfaces
    * Interface CATITPSDimVisu
  * DMAPSInterfaces
    * Enumeration CATSPPListDisplayOrder
    * Interface CATINavigateObjectPPR
  * Drafting2DLInterfaces
    * Enumeration CAT2DLClippingProfileMode
    * Interface CATI2DLayoutClipping
  * ENOVInterfaces
    * Interface ENOVIIntrospecNeededUE
  * ElecDeviceItf
    * Interface CATIElbDeviceInstance
    * Interface CATIElbSupport
  * GeometricObjects
    * Macro or #define CATBoneChamferType
    * Macro or #define CATCGMImplAttributeWithoutCreate
    * Macro or #define CATCellManifoldGroupType
    * Macro or #define CATCellManifoldType
    * Macro or #define CATContextualManifoldGroupType
    * Macro or #define CATDistanceHVertexType
    * Macro or #define CATHEdgeType
    * Macro or #define CATHGeometryType
    * Macro or #define CATHVertexType
    * Macro or #define CATHierarchicalManifoldGroupType
    * Macro or #define CATIntersectionHVertexType
    * Macro or #define CATManifoldGroupType
    * Macro or #define CATRatioHVertexType
    * Macro or #define CATSubdivGridSurfaceType
    * Interface CATICGMOperator
  * GeometricOperators
```cpp
    * Global Function CATCreateDistanceMinLim
  * ManufacturingInterfaces
```
    * Interface CATIMfgPPMachine
  * Mathematics
```cpp
    * Global Function CATCreateSoftwareConfiguration
    * Class CATCGMVirtualItf
```
    * Class CATICGMVirtual
    * Class CATLISTP(CATCGMVirtualItf)
    * Enumeration CATCanonicalPlane
```cpp
    * Global Function CATCreateSoftwareConfiguration
    * Global Function CATSign
  * MecModInterfaces
```
    * Class CATLISTV(CATIBRepAccess_var)
    * Interface CATIMmiInternalCopyWithLinkEdition
  * MechanicalModeler
    * Class CATMmrImportComparator
  * ObjectModelerNavigator
    * Enumeration CATNavigNodeState
  * PSNInteroperability
```cpp
    * Global Function CATAddCBToCurrentEditor
    * Global Function CATLoadFromVPM
  * PrintBase
```
    * Interface CATIPrintableDrafting
  * SurfaceMachiningInterfaces
    * Interface CATIMfgMultiAxisCurveMachining
  * System
    * Macro or #define CATMaxPathSize
    * Interface CATISysFileAccessStatisticsSettingAtt
    * Typedef CATSafeArray
  * TopologicalOperators
```cpp
    * Global Function CATCreateTopDevelop
  * VPMInterfaces
```
    * Macro or #define EFFVALSIZE
    * Interface CATICfgEffVal

[Top]

* * *

History Version: **1** [Oct 2009] | Document created
---|---
[Top]

* * *

_Copyright © 1999-2009, Dassault Systèmes. All rights reserved._
```cpp
Special Notices [CAA V5 CATIA](../CAADocQuickRefs/CAADocSpecialNoticesCATIA.md) | [CAA V5 DELMIA](../CAADocQuickRefs/CAADocSpecialNoticesDELMIA.md) | [CAA V5 ENOVIA](../CAADocQuickRefs/CAADocSpecialNoticesENOVIA.md)

```