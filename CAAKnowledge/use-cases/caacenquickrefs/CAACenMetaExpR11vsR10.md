---
title: "Changes to ENOVIA LCA Metadata in V5R11 Compared with V5R10"
category: "use-case"
module: "CAACenQuickRefs"
tags: []
source_file: "Doc/online/CAACenQuickRefs/CAACenMetaExpR11vsR10.md"
converted: "2026-05-11T17:33:46.563961"
---

CAA V5 Encyclopedia |  Changes to ENOVIA LCA Metadata in V5R11 Compared with V5R10  
---|---  
  
* * *

Status | Domain | Domain Inheritance | Object | Type | Object Inheritance | Attribute | Type  
---|---|---|---|---|---|---|---  
New attribute | CONFIG |   | MOD_GROUP | Class |   | C511_XEFF_LIST | Oid/Set  
Domain inheritance change | GRAPH | from <TEMPLAT> to <> |   |   |   |   |    
Object inheritance change | GRAPH |   | GIMaster | Class | from <VPMTPObjectMaster> to <> |   |    
Object inheritance change | GRAPH |   | GIFamily | Class | from <VPMTPObjectFamily> to <> |   |    
Object inheritance change | GRAPH |   | GIVersion | Class | from <VPMTPObjectVersion> to <> |   |    
Object inheritance change | PRODUCT | TEMPLAT | VPMProductClass | Class | from <VPMTPObjectID> to <> |   |    
Object inheritance change | PRODUCT | TEMPLAT | VPMProductRootClass | Class | from <VPMTPObjectID> to <> |   |    
Object inheritance change | PRODUCT | TEMPLAT | VPMProductSpecification | Class | from <VPMTPObject> to <> |   |    
Object inheritance change | PRODUCT | TEMPLAT | VPMProductComponent | Class | from <VPMTPObjectID> to <> |   |    
Object inheritance change | PRODUCT | TEMPLAT | VPMProductFunction | Class | from <VPMTPObjectID> to <> |   |    
Object inheritance change | PRODUCT | TEMPLAT | VPMItemInstance | Class | from <VPMTPObject> to <> |   |    
New attribute | PRODUCT | TEMPLAT | VPMItemInstance | Class |   | C511_ExpandString | String/Simple  
New attribute | PRODUCT | TEMPLAT | VPMItemInstance | Class |   | V511_Substitutes | Oid/Simple  
New attribute | PRODUCT | TEMPLAT | VPMItemInstance | Class |   | V511_PlanningCode | String/Simple  
New attribute | PRODUCT | TEMPLAT | VPMItemInstance | Class |   | V511_unit | String/Simple  
Object inheritance change | PRODUCT | TEMPLAT | VPMSubstituteRelation | Class | from <VPMTPObjectBase> to <> |   |    
Object inheritance change | PRODUCT | TEMPLAT | VPMTransformRelation | Class | from <VPMTPObjectBase> to <> |   |    
New attribute | PRODUCT | TEMPLAT | VPMTechRelation | Class | VPMTPHistoricalConnexion | C511_LoadingStrategy | Integer/Simple  
Object inheritance change | PRODUCT | TEMPLAT | VPMTechInstance | Class | from <VPMTPObject> to <> |   |    
Object inheritance change | PRODUCT | TEMPLAT | VPMTechInterface | Class | from <VPMTPObjectID> to <> |   |    
Object inheritance change | PRODUCT | TEMPLAT | VPMPartMaster | Class | from <VPMTPObjectMaster> to <> |   |    
New attribute | PRODUCT | TEMPLAT | VPMPartMaster | Class |   | V511_Magnitude | String/Simple  
New attribute | PRODUCT | TEMPLAT | VPMPartMaster | Class |   | V511_PartType | Integer/Simple  
New attribute | PRODUCT | TEMPLAT | VPMPartMaster | Class |   | V511_ControlledBy | Integer/Simple  
New attribute | PRODUCT | TEMPLAT | VPMPartMaster | Class |   | V511_AssemblyType | Integer/Simple  
Object inheritance change | PRODUCT | TEMPLAT | VPMPartFamily | Class | from <VPMTPObjectFamily> to <> |   |    
Object inheritance change | PRODUCT | TEMPLAT | VPMPartVersion | Class | from <VPMTPObjectVersion> to <> |   |    
New attribute | PRODUCT | TEMPLAT | VPMPartVersion | Class |   | V511_ApplicDate_MS | String/Simple  
Object inheritance change | PRODUCT | TEMPLAT | VPMAssemblyRelation | Class | from <VPMTPObject> to <> |   |    
New attribute | PRODUCT | TEMPLAT | VPMAssemblyRelation | Class |   | V_quantity | Real/Simple  
New attribute | PRODUCT | TEMPLAT | VPMAssemblyRelation | Class |   | C511_IsSubstitute | Boolean/Simple  
New attribute | PRODUCT | TEMPLAT | VPMAssemblyRelation | Class |   | V511_PlanningCode | String/Simple  
New attribute | PRODUCT | TEMPLAT | VPMAssemblyRelation | Class |   | V511_unit | String/Simple  
Object inheritance change | PRODUCT | TEMPLAT | VPMAlternateRelation | Class | from <VPMTPObjectBase> to <> |   |    
New attribute | PRODUCT | TEMPLAT | VPMEvolution | Class | VPMTPDependence | C511_LoadingStrategy | Integer/Simple  
New attribute | PRODUCT | TEMPLAT | VPMReplace | Class | VPMTPDependence | C511_LoadingStrategy | Integer/Simple  
Object inheritance change | PRODUCT | TEMPLAT | VPMContext | Class | from <VPMTPObjectID> to <> |   |    
New attribute | PRODUCT | TEMPLAT | VPMContext | Class |   | V511_PRC_ID | String/Simple  
Object inheritance change | PRODUCT | TEMPLAT | VPMZone | Class | from <VPMTPObjectID> to <> |   |    
Object inheritance change | PRODUCT | TEMPLAT | V508Implementation | Extension | from <V506TPExtension> to <> |   |    
Deleted attribute | PRODUCT | TEMPLAT | V508Implementation | Class | V506TPExtension | C506ExtensionOf | Oid / Simple  
Deleted attribute | PRODUCT | TEMPLAT | V508Implementation | Class | V506TPExtension | V_exposed | Binary / Simple  
Deleted attribute | PRODUCT | TEMPLAT | V508Implementation | Class | V506TPExtension | V_user | String / Simple  
Deleted attribute | PRODUCT | TEMPLAT | V508Implementation | Class | V506TPExtension | V_organization | String / Simple  
Deleted attribute | PRODUCT | TEMPLAT | V508Implementation | Class | V506TPExtension | V_histo_id | URL / Simple  
Deleted attribute | PRODUCT | TEMPLAT | V508Implementation | Class | V506TPExtension | V_previous | Oid / Simple  
Deleted attribute | PRODUCT | TEMPLAT | V508Implementation | Class | V506TPExtension | V508_AppDomaine | String / Simple  
Deleted attribute | PRODUCT | TEMPLAT | V508Implementation | Class | V506TPExtension | V508_AppType | String / Simple  
Deleted attribute | PRODUCT | TEMPLAT | V508Implementation | Class | V506TPExtension | C_properties | URL / List  
Deleted attribute | PRODUCT | TEMPLAT | V508Implementation | Class | V506TPExtension | V_aggregated | Oid / List  
Deleted attribute | PRODUCT | TEMPLAT | V508Implementation | Class | V506TPExtension | C_timestamp | Binary / Simple  
Deleted attribute | PRODUCT | TEMPLAT | V508Implementation | Class | V506TPExtension | C_created | Timestamp / Simple  
Deleted attribute | PRODUCT | TEMPLAT | V508Implementation | Class | V506TPExtension | C_modified | Timestamp / Simple  
Deleted attribute | PRODUCT | TEMPLAT | V508Implementation | Class | V506TPExtension | V_externalID | String / Simple  
New attribute | PRODUCT | TEMPLAT | V508PCoDependence | Class | VPMTPDependence | C511_LoadingStrategy | Integer/Simple  
New attribute | PRODUCT | TEMPLAT | V509PrdConnection | Class | VPMTPHistoricalConnexion | C511_LoadingStrategy | Integer/Simple  
New attribute | PRODUCT | TEMPLAT | V509Branch | Class | V506Branch | C511_LoadingStrategy | Integer/Simple  
Deleted object | PRODUCT | TEMPLAT | VPMItem | Class | VPMTPObjectID |   |    
Deleted object | PRODUCT | TEMPLAT | VPMRelationItem | Class | VPMTPObjectID |   |    
Deleted object | PRODUCT | TEMPLAT | VPMMPRecipeParameter | Class | VPMTPObjectBase |   |    
Deleted object | PRODUCT | TEMPLAT | VPMMPRecipeType | Class | VPMTPObjectID |   |    
Deleted object | PRODUCT | TEMPLAT | VPMMPRecipeInstance | Class | VPMMPSequenced |   |    
Deleted object | PRODUCT | TEMPLAT | VPMMPActivity | Class | VPMTPObjectID |   |    
Deleted object | PRODUCT | TEMPLAT | VPMMPGamme | Class | VPMMPActivity |   |    
Deleted object | PRODUCT | TEMPLAT | VPMMPSequenced | Class | VPMMPActivity |   |    
Deleted object | PRODUCT | TEMPLAT | VPMMPOperationGestion | Class | VPMMPSequenced |   |    
Deleted object | PRODUCT | TEMPLAT | VPMMPOperationTechnique | Class | VPMMPSequenced |   |    
Deleted object | PRODUCT | TEMPLAT | VPMMPWorkstation | Class | VPMTPObjectID |   |    
Deleted object | PRODUCT | TEMPLAT | VPMClash | Class | VPMTPHistoricalConnexion |   |    
Object inheritance change | TEMPLAT |   | VPMTPProperty | Class | from <VPMTPObject> to <> |   |    
New attribute | TEMPLAT |   | VPMTPRelation | Class | VPMTPProperty | C511_LoadingStrategy | Integer/Simple  
New attribute | TEMPLAT |   | VPMTPDocument | Class | VPMTPRelation | C511_LoadingStrategy | Integer/Simple  
New attribute | TEMPLAT |   | VPMTPDocumentation | Class | VPMTPDocument | C511_LoadingStrategy | Integer/Simple  
New attribute | TEMPLAT |   | VPMTPRepresentation | Class | VPMTPDocument | C511_LoadingStrategy | Integer/Simple  
New attribute | TEMPLAT |   | VPMTPConnexion | Class | VPMTPRelation | C511_LoadingStrategy | Integer/Simple  
New attribute | TEMPLAT |   | VPMTPHistoricalConnexion | Class | VPMTPConnexion | C511_LoadingStrategy | Integer/Simple  
New attribute | TEMPLAT |   | VPMTPDependence | Class | VPMTPHistoricalConnexion | C511_LoadingStrategy | Integer/Simple  
Object inheritance change | TEMPLAT |   | VPMTPFolderMaster | Class | from <VPMTPObjectMaster> to <> |   |    
Object inheritance change | TEMPLAT |   | VPMTPFolderFamily | Class | from <VPMTPObjectFamily> to <> |   |    
Object inheritance change | TEMPLAT |   | VPMTPFolderVersion | Class | from <VPMTPObjectVersion> to <> |   |    
Object inheritance change | TEMPLAT |   | VPMTPDocumentMaster | Class | from <VPMTPObjectMaster> to <> |   |    
New attribute | TEMPLAT |   | VPMTPDocumentMaster | Class |   | V511_NumExtLinks | Integer/Simple  
Object inheritance change | TEMPLAT |   | VPMTPDocumentFamily | Class | from <VPMTPObjectFamily> to <> |   |    
Object inheritance change | TEMPLAT |   | VPMTPDocumentVersion | Class | from <VPMTPObjectVersion> to <> |   |    
New attribute | TEMPLAT |   | V506Branch | Class | VPMTPRelation | C511_LoadingStrategy | Integer/Simple  
New attribute | TEMPLAT |   | V508_GenCont | Class | VPMTPRelation | C511_LoadingStrategy | Integer/Simple  
New object | TEMPLAT |   | V511PPRExternalRef | Class |   |   |    
Deleted object | TEMPLAT |   | VPMTPObjectBase | Class |   |   |    
Deleted object | TEMPLAT |   | VPMTPObject | Class | VPMTPObjectBase |   |    
Deleted object | TEMPLAT |   | VPMTPObjectID | Class | VPMTPObject |   |    
Deleted object | TEMPLAT |   | VPMTPObjectMaster | Class | VPMTPObjectID |   |    
Deleted object | TEMPLAT |   | VPMTPObjectFamily | Class | VPMTPObjectID |   |    
Deleted object | TEMPLAT |   | VPMTPObjectVersion | Class | VPMTPObject |   |    
Deleted object | TEMPLAT |   | V506TPExtension | Class | VPMTPObject |   |    
New attribute | ACTION |   | V506AFLResp | Class |   | V_userId | String/Simple  
New attribute | ACTION |   | V506AFLResp | Class |   | V_roleId | String/Simple  
New object | ACTION |   | AFLCalendar | Class |   |   |    
New object | ACTION |   | AFLCalendarEvent | Class |   |   |    
New attribute | APLECO | ACTION | CMAFFECTED_OBJECT | Class | AFLAffected_Object | ChangeType | String/Simple  
New attribute | APLECO | ACTION | CMAFFECTED_OBJECT | Class | AFLAffected_Object | ChangeAction | String/Simple  
New attribute | APLECO | ACTION | CMAFFECTED_OBJECT | Class | AFLAffected_Object | ManuallyAdded | Boolean/Simple  
New attribute | APLECO | ACTION | CMAFFECTED_OBJECT | Class | AFLAffected_Object | ActuallyChanged | Boolean/Simple  
New attribute | APLECO | ACTION | CMAFFECTED_OBJECT | Class | AFLAffected_Object | InternalRelations | URL/Set  
New object | APLECO | ACTION | CMAFF_PROD | Class | CMAFFECTED_OBJECT |   |    
New attribute | APLECO | ACTION | V506CHANGETEAM | Class | V506AFLResp | V_userId | String/Simple  
New attribute | APLECO | ACTION | V506CHANGETEAM | Class | V506AFLResp | V_roleId | String/Simple  
New attribute | APLECO | ACTION | V506REVIEWTEAM | Class | V506CHANGETEAM | V_userId | String/Simple  
New attribute | APLECO | ACTION | V506REVIEWTEAM | Class | V506CHANGETEAM | V_roleId | String/Simple  
New attribute | VPMWFL | ACTION | WFActivity | Class | AFLAction | V_workingStatus | String/Simple  
New attribute | VPMWFL | ACTION | WFActivity | Class | AFLAction | V_workingLCycleName | String/Simple  
New attribute | VPMWFL | ACTION | WFActivity | Class | AFLAction | C_inTransitions | Oid/Set  
New attribute | VPMWFL | ACTION | WFActivity | Class | AFLAction | C_outTransitions | Oid/Set  
Deleted attribute | VPMWFL | ACTION | WFActivity | Class | AFLAction | V_performanceStatus | String / Simple  
New attribute | VPMWFL | ACTION | WFRegularActivity | Class | WFActivity | V_workingStatus | String/Simple  
New attribute | VPMWFL | ACTION | WFRegularActivity | Class | WFActivity | V_workingLCycleName | String/Simple  
New attribute | VPMWFL | ACTION | WFRegularActivity | Class | WFActivity | C_inTransitions | Oid/Set  
New attribute | VPMWFL | ACTION | WFRegularActivity | Class | WFActivity | C_outTransitions | Oid/Set  
Deleted attribute | VPMWFL | ACTION | WFRegularActivity | Class | WFActivity | V_performanceStatus | String / Simple  
New attribute | VPMWFL | ACTION | WFManualActivity | Class | WFRegularActivity | V_workingStatus | String/Simple  
New attribute | VPMWFL | ACTION | WFManualActivity | Class | WFRegularActivity | V_workingLCycleName | String/Simple  
New attribute | VPMWFL | ACTION | WFManualActivity | Class | WFRegularActivity | C_inTransitions | Oid/Set  
New attribute | VPMWFL | ACTION | WFManualActivity | Class | WFRegularActivity | C_outTransitions | Oid/Set  
Deleted attribute | VPMWFL | ACTION | WFManualActivity | Class | WFRegularActivity | V_performanceStatus | String / Simple  
New attribute | VPMWFL | ACTION | WFApplicationActivity | Class | WFRegularActivity | V_workingStatus | String/Simple  
New attribute | VPMWFL | ACTION | WFApplicationActivity | Class | WFRegularActivity | V_workingLCycleName | String/Simple  
New attribute | VPMWFL | ACTION | WFApplicationActivity | Class | WFRegularActivity | C_inTransitions | Oid/Set  
New attribute | VPMWFL | ACTION | WFApplicationActivity | Class | WFRegularActivity | C_outTransitions | Oid/Set  
Deleted attribute | VPMWFL | ACTION | WFApplicationActivity | Class | WFRegularActivity | V_performanceStatus | String / Simple  
New attribute | VPMWFL | ACTION | WFSubflowActivity | Class | WFRegularActivity | V_workingStatus | String/Simple  
New attribute | VPMWFL | ACTION | WFSubflowActivity | Class | WFRegularActivity | V_workingLCycleName | String/Simple  
New attribute | VPMWFL | ACTION | WFSubflowActivity | Class | WFRegularActivity | C_inTransitions | Oid/Set  
New attribute | VPMWFL | ACTION | WFSubflowActivity | Class | WFRegularActivity | C_outTransitions | Oid/Set  
Deleted attribute | VPMWFL | ACTION | WFSubflowActivity | Class | WFRegularActivity | V_performanceStatus | String / Simple  
New attribute | VPMWFL | ACTION | WFLoopActivity | Class | WFRegularActivity | V_workingStatus | String/Simple  
New attribute | VPMWFL | ACTION | WFLoopActivity | Class | WFRegularActivity | V_workingLCycleName | String/Simple  
New attribute | VPMWFL | ACTION | WFLoopActivity | Class | WFRegularActivity | C_inTransitions | Oid/Set  
New attribute | VPMWFL | ACTION | WFLoopActivity | Class | WFRegularActivity | C_outTransitions | Oid/Set  
Deleted attribute | VPMWFL | ACTION | WFLoopActivity | Class | WFRegularActivity | V_performanceStatus | String / Simple  
New attribute | VPMWFL | ACTION | WFInlineBlockActivity | Class | WFRegularActivity | V_workingStatus | String/Simple  
New attribute | VPMWFL | ACTION | WFInlineBlockActivity | Class | WFRegularActivity | V_workingLCycleName | String/Simple  
New attribute | VPMWFL | ACTION | WFInlineBlockActivity | Class | WFRegularActivity | C_inTransitions | Oid/Set  
New attribute | VPMWFL | ACTION | WFInlineBlockActivity | Class | WFRegularActivity | C_outTransitions | Oid/Set  
Deleted attribute | VPMWFL | ACTION | WFInlineBlockActivity | Class | WFRegularActivity | V_performanceStatus | String / Simple  
New attribute | VPMWFL | ACTION | WFRouteActivity | Class | WFActivity | V_workingStatus | String/Simple  
New attribute | VPMWFL | ACTION | WFRouteActivity | Class | WFActivity | V_workingLCycleName | String/Simple  
New attribute | VPMWFL | ACTION | WFRouteActivity | Class | WFActivity | C_inTransitions | Oid/Set  
New attribute | VPMWFL | ACTION | WFRouteActivity | Class | WFActivity | C_outTransitions | Oid/Set  
Deleted attribute | VPMWFL | ACTION | WFRouteActivity | Class | WFActivity | V_performanceStatus | String / Simple  
New attribute | VPMWFL | ACTION | WFRelevantData | Class | AFLAffected_Object | V_allowedValues | String/Set  
New attribute | VPMWFL | ACTION | WFRelevantData | Class | AFLAffected_Object | V506_graph | URL/Simple  
Deleted attribute | VPMWFL | ACTION | WFRelevantData | Class | AFLAffected_Object | V_graph | URL / Simple  
New attribute | VPMWFL | ACTION | WFParticipant | Class | V506AFLResp | V_userId | String/Simple  
New attribute | VPMWFL | ACTION | WFParticipant | Class | V506AFLResp | V_roleId | String/Simple  
New attribute | VPMWFL | ACTION | WFApprovalActivity | Class | WFManualActivity | V_reasonCode | String/Simple  
New attribute | VPMWFL | ACTION | WFApprovalActivity | Class | WFManualActivity | V_allowedRCodes | String/Set  
New attribute | VPMWFL | ACTION | WFApprovalActivity | Class | WFManualActivity | V_defaultRCode | String/Simple  
New attribute | VPMWFL | ACTION | WFApprovalActivity | Class | WFManualActivity | V_workingStatus | String/Simple  
New attribute | VPMWFL | ACTION | WFApprovalActivity | Class | WFManualActivity | V_workingLCycleName | String/Simple  
New attribute | VPMWFL | ACTION | WFApprovalActivity | Class | WFManualActivity | C_inTransitions | Oid/Set  
New attribute | VPMWFL | ACTION | WFApprovalActivity | Class | WFManualActivity | C_outTransitions | Oid/Set  
Deleted attribute | VPMWFL | ACTION | WFApprovalActivity | Class | WFManualActivity | V_performanceStatus | String / Simple  
Deleted object | VPMWFL | ACTION | WFTransition | Class | AFLOrientedLink |   |    
Deleted object | VPMWFL | ACTION | WFInlineBlock | Class | WFTransRestriction |   |    
Object inheritance change | DOCDIR | TEMPLAT | VPMDocumentIteration | Class | from <VPMTPObject> to <> |   |    
[Top]

* * *

History Version: **1** [Jul 2003] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 1994-2003, Dassault Systmes. All rights reserved._
