---
title: "Changes to ENOVIA LCA Metadata in V5R13 Compared with V5R12"
category: "use-case"
module: "CAACenQuickRefs"
tags: []
source_file: "Doc/online/CAACenQuickRefs/CAACenMetaExpR13vsR12.md"
converted: "2026-05-11T17:33:46.738859"
---

CAA V5 Encyclopedia |  Changes to ENOVIA LCA Metadata in V5R13 Compared with V5R12  
---|---  
  
* * *

Type | Owner | CAA | Message | Domain | Domain Inheritance | Object | Type | Object Inheritance | Attribute | Type | Inherited | Alias | Short Role | Role  
---|---|---|---|---|---|---|---|---|---|---|---|---|---|---  
3 | 3 | 0 | New attribute | CONFIG |   | CFGABLE_OBJECT | Class |   | V_project | Simple of String |   | V_project | The product name |    
3 | 3 | 0 | New attribute | CONFIG |   | EFF_MOD | Class |   | V_project | Simple of String |   | V_project | The modification name |    
3 | 3 | 0 | New attribute | CONFIG |   | SPECIFICATION | Class |   | V_project | Simple of String |   | V_project | The specification name |    
3 | 3 | 0 | New attribute | CONFIG |   | CATEGORYSPEC | Class |   | V_project | Simple of String |   | V_project | The category description |    
3 | 3 | 0 | New attribute | CONFIG |   | CATLNK | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | CONFIG |   | CFGABLE | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | CONFIG |   | SPECLNK | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | CONFIG |   | EXPLNK | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | CONFIG |   | EXPRESSIONSPEC | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | CONFIG |   | INCLNK | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | CONFIG |   | INCLUSIONSPEC | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | CONFIG |   | PROGRAMLNK | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | CONFIG |   | PROGRAM | Class |   | V_project | Simple of String |   | V_project | The program name |    
3 | 3 | 0 | New attribute | CONFIG |   | MILESTONE | Class |   | V_project | Simple of String |   | V_project | The milestone name |    
3 | 3 | 0 | New attribute | CONFIG |   | MILESTONEVALUE | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | CONFIG |   | CFHANDLER | Class |   | V_project | Simple of String |   | V_project | The configuration handler name |    
3 | 3 | 0 | New attribute | CONFIG |   | BSF | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | CONFIG |   | MODHistory | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | CONFIG |   | MOD_GROUP | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | CONFIG |   | COMPSPECS | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | CONFIG |   | COMPLNK | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | CONFIG |   | PRODUCTTYPE | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | VPMProductClass | Class |   | V_project | Simple of String |   | V_project | The ProductClass owner organization |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | VPMProductRootClass | Class |   | V_project | Simple of String |   | V_project | The product owner organization |    
3 | 3 | 1 | New attribute | PRODUCT | TEMPLAT | VPMProductRootClass | Class |   | V513_VAR | List of Oid |   | V513_VAR | The list of children assembly relation objects that are physically under the current part version |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | VPMProductSpecification | Class |   | V_project | Simple of String |   | V_project | The product specification creation owner organization |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | VPMProductComponent | Class |   | V_project | Simple of String |   | V_project | The product component owner organization |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | VPMProductFunction | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | VPMItemInstance | Class |   | V_project | Simple of String |   | V_project | The item instance owner organization |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | VPMSubstituteRelation | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | VPMTransformRelation | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | VPMTechRelation | Class | VPMTPHistoricalConnexion | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | VPMTechInstance | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | VPMTechInterface | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | VPMPartMaster | Class |   | V_project | Simple of String |   | V_project | The part master owner organization |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | VPMPartFamily | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | VPMPartVersion | Class |   | V_project | Simple of String |   | V_project | The part version owner organization |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | VPMPartVersion | Class |   | V513_OwningPRC | Simple of Oid |   | V513_OwningPRC | The list of children assembly relation objects that are physically under the current part version |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | VPMAssemblyRelation | Class |   | V_project | Simple of String |   | V_project | The assembly relation owner organization |    
3 | 3 | 1 | New attribute | PRODUCT | TEMPLAT | VPMAssemblyRelation | Class |   | V513_VPV | Simple of Oid |   | V513_VPV | The child part version |    
3 | 3 | 1 | New attribute | PRODUCT | TEMPLAT | VPMAssemblyRelation | Class |   | V513_VPRC | Simple of Oid |   | V513_VPRC | The child PRC |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | VPMAlternateRelation | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | VPMVolumeProperty | Class | VPMTPProperty | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | VPMSpacemapProperty | Class | VPMTPProperty | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | VPMEvolution | Class | VPMTPDependence | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | VPMReplace | Class | VPMTPDependence | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | VPMContext | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | VPMZone | Class |   | V_project | Simple of String |   | V_project | The zone owner organization |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | V508GenericComp | Class | VPMProductComponent | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | V508PCoDependence | Class | VPMTPDependence | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | V509PrdConnection | Class | VPMTPHistoricalConnexion | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | PRODUCT | TEMPLAT | V509Branch | Class | V506Branch | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | TEMPLAT |   | VPMTPProperty | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | TEMPLAT |   | VPMTPRelation | Class | VPMTPProperty | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | TEMPLAT |   | VPMTPIntProperty | Class | VPMTPProperty | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | TEMPLAT |   | VPMTPRealProperty | Class | VPMTPProperty | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | TEMPLAT |   | VPMTPStringProperty | Class | VPMTPProperty | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | TEMPLAT |   | VPMTPBinaryProperty | Class | VPMTPProperty | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | TEMPLAT |   | VPMTPDocument | Class | VPMTPRelation | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | TEMPLAT |   | VPMTPDocumentation | Class | VPMTPDocument | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | TEMPLAT |   | VPMTPRepresentation | Class | VPMTPDocument | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | TEMPLAT |   | VPMTPConnexion | Class | VPMTPRelation | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | TEMPLAT |   | VPMTPHistoricalConnexion | Class | VPMTPConnexion | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | TEMPLAT |   | VPMTPDependence | Class | VPMTPHistoricalConnexion | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | TEMPLAT |   | VPMTPFolderMaster | Class |   | V_project | Simple of String |   | V_project | The folder master organization |    
3 | 3 | 0 | New attribute | TEMPLAT |   | VPMTPFolderFamily | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | TEMPLAT |   | VPMTPFolderVersion | Class |   | V_project | Simple of String |   | V_project | The folder version owner organization |    
3 | 3 | 0 | New attribute | TEMPLAT |   | VPMTPDocumentMaster | Class |   | V_project | Simple of String |   | V_project | The document master owner organization |    
3 | 3 | 0 | New attribute | TEMPLAT |   | VPMTPDocumentFamily | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | TEMPLAT |   | VPMTPDocumentVersion | Class |   | V_project | Simple of String |   | V_project |   |    
3 | 3 | 0 | New attribute | TEMPLAT |   | V506Branch | Class | VPMTPRelation | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | TEMPLAT |   | V508_GenCont | Class | VPMTPRelation | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 1 | New attribute | DOCDIR | TEMPLAT | VPMDocumentRevision | Class | VPMTPDocumentVersion | V513_IsAutoLocked | Simple of Boolean |   | V513_IsAutoLocked | Flag to determine whether document has been locked by system | When a document is checked-out, it is automatically locked by system. This case this attribute is set to TRUE. If it is locked by user manually, it is set to FALSE. This flag should not be modified manually.  
3 | 3 | 1 | New attribute | DOCDIR | TEMPLAT | VPMDocumentRevision | Class | VPMTPDocumentVersion | V513_IsArchived | Simple of Boolean |   | V513_IsArchived | Flag to determine whether document has been archived to another vault. | This flag should not be modified manually.  
3 | 3 | 0 | New attribute | DOCDIR | TEMPLAT | VPMDocumentRevision | Class | VPMTPDocumentVersion | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 1 | New attribute | DOCDIR | TEMPLAT | VPMDocumentIteration | Class |   | V_project | Simple of String |   | V_project | The iteration project | The iteration project should not be modified after creation.  
3 | 3 | 0 | New attribute | DOCDIR | TEMPLAT | VPMTOCMaster | Class | VPMTPFolderMaster | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | DOCDIR | TEMPLAT | VPMTOCVersion | Class | VPMTPFolderVersion | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | ACTION |   | AFLAction | Class |   | V_project | Simple of String |   | V_project | The user who created the action |    
3 | 3 | 0 | New attribute | ACTION |   | AFLPSAction | Class | AFLAction | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | ACTION |   | AFLLink | Class |   | V_project | Simple of String |   | V_project | The link name |    
3 | 3 | 0 | New attribute | ACTION |   | V506AFLSessEff | Class | AFLPSAction | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | ACTION |   | AFLPSObject | Class | AFLAffected_Object | V_project | Simple of String |   | V_project | The priority of the affected object |    
3 | 3 | 0 | New attribute | ACTION |   | AFLOrientedLink | Class | AFLLink | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | ACTION |   | AFLSymetricLink | Class | AFLLink | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | ACTION |   | AFLCancelLink | Class | AFLOrientedLink | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | ACTION |   | AFLSupersedeLink | Class | AFLOrientedLink | V_project | Simple of String | Inherited | V_project |   |    
2 | 2 | 1 | New object | ACTION |   | AFLProjectTask | Class | AFLAction |   |   |   | AFLProjectTask |   |    
3 | 2 | 1 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V_projectCalendar | Simple of String |   | V_projectCalendar |   |    
3 | 2 | 1 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V_scheduleFrom | Simple of String |   | V_scheduleFrom |   |    
3 | 2 | 1 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V_statusDate | Simple of Timestamp |   | V_statusDate |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V_name | Simple of String | Inherited | V_name |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V_description | Simple of String | Inherited | V_description |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V_abstract | Simple of String | Inherited | V_abstract |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V_creator | Simple of String | Inherited | V_creator |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V_user | Simple of String | Inherited | V_user |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V_organization | Simple of String | Inherited | V_organization |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V_project | Simple of String | Inherited | V_project |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V_priority | Simple of String | Inherited | V_priority |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V_status | Simple of String | Inherited | V_status |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V506_graph | Simple of URL | Inherited | V506_graph |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V_start_date | Simple of Timestamp | Inherited | V_start_date |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V_end_date | Simple of Timestamp | Inherited | V_end_date |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V_actual_start_date | Simple of Timestamp | Inherited | V_actual_start_date |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V_actual_end_date | Simple of Timestamp | Inherited | V_actual_end_date |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V_duration | Simple of Integer | Inherited | V_duration |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V_durationUnit | Simple of String | Inherited | V_durationUnit |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V_progress | Simple of String | Inherited | V_progress |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V_workingTimeUnit | Simple of String | Inherited | V_workingTimeUnit |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V_workingTime | Simple of Integer | Inherited | V_workingTime |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V_del_date | Simple of Timestamp | Inherited | V_del_date |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V506_del_int | Simple of Integer | Inherited | V506_del_int |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | V_lastmodif_user | Simple of String | Inherited | V_lastmodif_user |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | C_created | Simple of Timestamp | Inherited | C_created |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | C_modified | Simple of Timestamp | Inherited | C_modified |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | C508_isCompleted | Simple of Boolean | Inherited | C508_isCompleted |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | C_datas | Set of Oid | Inherited | C_datas |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | C_histories | Set of Oid | Inherited | C_histories |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | C_objects | Set of Oid | Inherited | C_objects |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | C_attachements | Set of Oid | Inherited | C_attachements |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | C506_resps | Set of Oid | Inherited | C506_resps |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | C_Linked1 | Inverse of AFLLink.C_action1 (Set) | Inherited | C_Linked1 |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTask | Class | AFLAction | C_Linked2 | Inverse of AFLLink.C_action2 (Set) | Inherited | C_Linked2 |   |    
2 | 2 | 1 | New object | ACTION |   | AFLProjectTaskLink | Class | AFLLink |   |   |   | AFLProjectTaskLink |   |    
3 | 2 | 1 | New object | ACTION |   | AFLProjectTaskLink | Class | AFLLink | V_relationType | Simple of String |   | V_relationType |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTaskLink | Class | AFLLink | V_lagTime | Simple of Integer |   | V_lagTime |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTaskLink | Class | AFLLink | C_name | Simple of String | Inherited | C_name |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTaskLink | Class | AFLLink | V_level | Simple of Integer | Inherited | V_level |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTaskLink | Class | AFLLink | V_user | Simple of String | Inherited | V_user |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTaskLink | Class | AFLLink | V_organization | Simple of String | Inherited | V_organization |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTaskLink | Class | AFLLink | V_project | Simple of String | Inherited | V_project |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTaskLink | Class | AFLLink | C_created | Simple of Timestamp | Inherited | C_created |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTaskLink | Class | AFLLink | C_modified | Simple of Timestamp | Inherited | C_modified |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTaskLink | Class | AFLLink | C_action1 | Simple of Oid | Inherited | C_action1 |   |    
3 | 2 | 0 | New object | ACTION |   | AFLProjectTaskLink | Class | AFLLink | C_action2 | Simple of Oid | Inherited | C_action2 |   |    
3 | 3 | 0 | New attribute | APLAFL | ACTION | AFLBaseAction | Class | AFLPSAction | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | APLAFL | ACTION | AFLBaseObject | Class | AFLPSObject | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | APLAFL | ACTION | Action_Design | Class | AFLBaseAction | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | APLAFL | ACTION | Action_Deliverable | Class | AFLBaseAction | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | APLAFL | ACTION | Action_Manufacturing | Class | AFLBaseAction | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | APLAFL | ACTION | Action_Maintenance | Class | AFLBaseAction | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | APLAFL | ACTION | Action_Documentation | Class | AFLBaseAction | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | APLAFL | ACTION | Action_SignOff | Class | AFLBaseAction | V_project | Simple of String | Inherited | V_project |   |    
2 | 2 | 1 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction |   |   |   | Action_ImpactAnalysis |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | C_products | Set of Oid | Inherited | C_products |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | V_name | Simple of String | Inherited | V_name |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | V_description | Simple of String | Inherited | V_description |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | V_abstract | Simple of String | Inherited | V_abstract |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | V_creator | Simple of String | Inherited | V_creator |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | V_user | Simple of String | Inherited | V_user |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | V_organization | Simple of String | Inherited | V_organization |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | V_project | Simple of String | Inherited | V_project |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | V_priority | Simple of String | Inherited | V_priority |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | V_status | Simple of String | Inherited | V_status |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | V506_graph | Simple of URL | Inherited | V506_graph |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | V_start_date | Simple of Timestamp | Inherited | V_start_date |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | V_end_date | Simple of Timestamp | Inherited | V_end_date |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | V_actual_start_date | Simple of Timestamp | Inherited | V_actual_start_date |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | V_actual_end_date | Simple of Timestamp | Inherited | V_actual_end_date |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | V_duration | Simple of Integer | Inherited | V_duration |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | V_durationUnit | Simple of String | Inherited | V_durationUnit |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | V_progress | Simple of String | Inherited | V_progress |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | V_workingTimeUnit | Simple of String | Inherited | V_workingTimeUnit |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | V_workingTime | Simple of Integer | Inherited | V_workingTime |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | V_del_date | Simple of Timestamp | Inherited | V_del_date |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | V506_del_int | Simple of Integer | Inherited | V506_del_int |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | V_lastmodif_user | Simple of String | Inherited | V_lastmodif_user |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | C_created | Simple of Timestamp | Inherited | C_created |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | C_modified | Simple of Timestamp | Inherited | C_modified |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | C508_isCompleted | Simple of Boolean | Inherited | C508_isCompleted |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | C_datas | Set of Oid | Inherited | C_datas |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | C_histories | Set of Oid | Inherited | C_histories |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | C_objects | Set of Oid | Inherited | C_objects |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | C_attachements | Set of Oid | Inherited | C_attachements |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | C506_resps | Set of Oid | Inherited | C506_resps |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | C_Linked1 | Inverse of AFLLink.C_action1 (Set) | Inherited | C_Linked1 |   |    
3 | 2 | 0 | New object | APLAFL | ACTION | Action_ImpactAnalysis | Class | AFLBaseAction | C_Linked2 | Inverse of AFLLink.C_action2 (Set) | Inherited | C_Linked2 |   |    
3 | 3 | 0 | New attribute | APLAFL | ACTION | Action_PenetrationRequest | Class | AFLBaseAction | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | APLAFL | ACTION | Action_DSG_custo | Class | Action_Design | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | APLAFL | ACTION | Associated_Object | Class | AFLBaseObject | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | APLAFL | ACTION | Output_Associated_Object | Class | AFLBaseObject | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | APLAFL | ACTION | Input_Associated_Object | Class | AFLBaseObject | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | APLAFL | ACTION | AFLParent | Class | AFLOrientedLink | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | APLAFL | ACTION | AFLPeer | Class | AFLSymetricLink | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | APLAFL | ACTION | V506MBOMLink | Class | AFLSymetricLink | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | APLAFL | ACTION | ActionForDataX | Class | AFLBaseAction | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | APLAFL | ACTION | Action_Export | Class | ActionForDataX | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | APLAFL | ACTION | Action_Import | Class | ActionForDataX | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | APLECO | ACTION | CHANGEMANAGEMENT | Class | AFLPSAction | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | APLECO | ACTION | ECR | Class | CHANGEMANAGEMENT | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | APLECO | ACTION | ECO | Class | CHANGEMANAGEMENT | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | APLECO | ACTION | DELIVERABLE_LINK | Class | AFLOrientedLink | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | APLECO | ACTION | V506ec_corequ | Class | AFLSymetricLink | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | APLECO | ACTION | V506ec_prerequ | Class | AFLOrientedLink | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | APLECO | ACTION | V506eco_link | Class | AFLOrientedLink | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 1 | New attribute | VPMWFL | ACTION | WFProcess | Class | AFLAction | C_startMode | Simple of String |   | C_startMode | The process start mode | The process start mode value may be MANUAL or AUTO.  
3 | 3 | 0 | New attribute | VPMWFL | ACTION | WFProcess | Class | AFLAction | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | VPMWFL | ACTION | WFActivity | Class | AFLAction | C_isVisited | Simple of Boolean |   | C_isVisited | The working lifecycle name | The working lifecycle name refines the built in lifecycle of the activity.  
3 | 3 | 0 | New attribute | VPMWFL | ACTION | WFActivity | Class | AFLAction | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | VPMWFL | ACTION | WFRegularActivity | Class | WFActivity | C_isVisited | Simple of Boolean | Inherited | C_isVisited |   |    
3 | 3 | 0 | New attribute | VPMWFL | ACTION | WFRegularActivity | Class | WFActivity | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | VPMWFL | ACTION | WFManualActivity | Class | WFRegularActivity | C_isVisited | Simple of Boolean | Inherited | C_isVisited |   |    
3 | 3 | 0 | New attribute | VPMWFL | ACTION | WFManualActivity | Class | WFRegularActivity | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | VPMWFL | ACTION | WFApplicationActivity | Class | WFRegularActivity | C_isVisited | Simple of Boolean | Inherited | C_isVisited |   |    
3 | 3 | 0 | New attribute | VPMWFL | ACTION | WFApplicationActivity | Class | WFRegularActivity | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | VPMWFL | ACTION | WFSubflowActivity | Class | WFRegularActivity | C_isVisited | Simple of Boolean | Inherited | C_isVisited |   |    
3 | 3 | 0 | New attribute | VPMWFL | ACTION | WFSubflowActivity | Class | WFRegularActivity | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | VPMWFL | ACTION | WFLoopActivity | Class | WFRegularActivity | C_isVisited | Simple of Boolean | Inherited | C_isVisited |   |    
3 | 3 | 0 | New attribute | VPMWFL | ACTION | WFLoopActivity | Class | WFRegularActivity | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | VPMWFL | ACTION | WFInlineBlockActivity | Class | WFRegularActivity | C_isVisited | Simple of Boolean | Inherited | C_isVisited |   |    
3 | 3 | 0 | New attribute | VPMWFL | ACTION | WFInlineBlockActivity | Class | WFRegularActivity | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | VPMWFL | ACTION | WFRouteActivity | Class | WFActivity | C_isVisited | Simple of Boolean | Inherited | C_isVisited |   |    
3 | 3 | 0 | New attribute | VPMWFL | ACTION | WFRouteActivity | Class | WFActivity | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | VPMWFL | ACTION | WFRelevantData | Class | AFLAffected_Object | V_project | Simple of String |   | V_project | The relevant data current status | The relevant data current status can be Checked or Unchecked.  
3 | 3 | 0 | New inverse attribute | VPMWFL | ACTION | WFParameterBindings | Class |   | C_appliActivityDef | Inverse of WFD_ApplicationActivity.C_appliParamBindings (Simple) |   | C_appliActivityDef |   |    
3 | 3 | 0 | New attribute | VPMWFL | ACTION | WFApprovalActivity | Class | WFManualActivity | V_isSecured | Simple of Boolean |   | V_isSecured | The default value for the reason code |    
3 | 3 | 0 | New attribute | VPMWFL | ACTION | WFApprovalActivity | Class | WFManualActivity | C_isVisited | Simple of Boolean | Inherited | C_isVisited |   |    
3 | 3 | 0 | New attribute | VPMWFL | ACTION | WFApprovalActivity | Class | WFManualActivity | V_project | Simple of String | Inherited | V_project |   |    
3 | 3 | 0 | New attribute | VPMWFL | ACTION | WFMultipleActivity | Class | WFInlineBlockActivity | C_isVisited | Simple of Boolean | Inherited | C_isVisited |   |    
3 | 3 | 0 | New attribute | VPMWFL | ACTION | WFMultipleActivity | Class | WFInlineBlockActivity | V_project | Simple of String | Inherited | V_project |   |    
2 | 2 | 1 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity |   |   |   | WFProceduralSubflow |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_execMode | Simple of String | Inherited | V_execMode |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_generatorId | Simple of String | Inherited | V_generatorId |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_instantiateOnce | Simple of Boolean | Inherited | V_instantiateOnce |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_subProcess | Simple of Oid | Inherited | C_subProcess |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_multiplicity | Simple of String | Inherited | V_multiplicity |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_cost | Simple of String | Inherited | V_cost |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_waitingTime | Simple of Integer | Inherited | V_waitingTime |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_startMode | Simple of String | Inherited | C_startMode |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_finishMode | Simple of String | Inherited | C_finishMode |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_performer | Simple of Oid | Inherited | C_performer |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_id | Simple of String | Inherited | V_id |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_icon | Simple of String | Inherited | C_icon |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_expectedCFT | Simple of Integer | Inherited | C_expectedCFT |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_receivedCFT | Simple of Integer | Inherited | C_receivedCFT |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_CFTSourceNames | Set of String | Inherited | C_CFTSourceNames |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_expectedInputs | Set of String | Inherited | C_expectedInputs |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_expectedOutputs | Set of String | Inherited | C_expectedOutputs |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_inputs | Set of Oid | Inherited | C_inputs |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_outputs | Set of Oid | Inherited | C_outputs |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_TransRestriction | Simple of Oid | Inherited | C_TransRestriction |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_documentation | Simple of String | Inherited | V_documentation |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_entryCondition | Simple of String | Inherited | V_entryCondition |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_exitCondition | Simple of String | Inherited | V_exitCondition |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_exitCode | Simple of Integer | Inherited | V_exitCode |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_isEarly | Simple of Boolean | Inherited | C_isEarly |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_workingStatus | Simple of String | Inherited | V_workingStatus |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_workingLCycleName | Simple of String | Inherited | V_workingLCycleName |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_isVisited | Simple of Boolean | Inherited | C_isVisited |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_inTransitions | Set of Oid | Inherited | C_inTransitions |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_outTransitions | Set of Oid | Inherited | C_outTransitions |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_name | Simple of String | Inherited | V_name |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_description | Simple of String | Inherited | V_description |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_abstract | Simple of String | Inherited | V_abstract |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_creator | Simple of String | Inherited | V_creator |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_user | Simple of String | Inherited | V_user |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_organization | Simple of String | Inherited | V_organization |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_project | Simple of String | Inherited | V_project |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_priority | Simple of String | Inherited | V_priority |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_status | Simple of String | Inherited | V_status |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V506_graph | Simple of URL | Inherited | V506_graph |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_start_date | Simple of Timestamp | Inherited | V_start_date |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_end_date | Simple of Timestamp | Inherited | V_end_date |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_actual_start_date | Simple of Timestamp | Inherited | V_actual_start_date |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_actual_end_date | Simple of Timestamp | Inherited | V_actual_end_date |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_duration | Simple of Integer | Inherited | V_duration |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_durationUnit | Simple of String | Inherited | V_durationUnit |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_progress | Simple of String | Inherited | V_progress |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_workingTimeUnit | Simple of String | Inherited | V_workingTimeUnit |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_workingTime | Simple of Integer | Inherited | V_workingTime |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_del_date | Simple of Timestamp | Inherited | V_del_date |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V506_del_int | Simple of Integer | Inherited | V506_del_int |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | V_lastmodif_user | Simple of String | Inherited | V_lastmodif_user |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_created | Simple of Timestamp | Inherited | C_created |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_modified | Simple of Timestamp | Inherited | C_modified |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C508_isCompleted | Simple of Boolean | Inherited | C508_isCompleted |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_datas | Set of Oid | Inherited | C_datas |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_histories | Set of Oid | Inherited | C_histories |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_objects | Set of Oid | Inherited | C_objects |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_attachements | Set of Oid | Inherited | C_attachements |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C506_resps | Set of Oid | Inherited | C506_resps |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_process | Inverse of WFProcess.C_activities (Simple) | Inherited | C_process |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_Linked1 | Inverse of AFLLink.C_action1 (Set) | Inherited | C_Linked1 |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFProceduralSubflow | Class | WFSubflowActivity | C_Linked2 | Inverse of AFLLink.C_action2 (Set) | Inherited | C_Linked2 |   |    
2 | 2 | 1 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow |   |   |   | WFApprovalSubflow |   |    
3 | 2 | 1 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_mode | Simple of String |   | V_mode | The approval mode | The approval mode used for multiple users (Dynamic) approval. Its value may be Any, Majority, or Unanimous  
3 | 2 | 1 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_response | Simple of String |   | V_response | The approval response given by the user |    
3 | 2 | 1 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_allowedResps | Set of String |   | V_allowedResps | The authorized values for the approval responses |    
3 | 2 | 1 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_defaultResponse | Simple of String |   | V_defaultResponse | The default value for the approval response |    
3 | 2 | 1 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_soughtResponse | Simple of String |   | V_soughtResponse | The response sought for the approval activity |    
3 | 2 | 1 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_reasonCode | Simple of String |   | V_reasonCode | The reason code |    
3 | 2 | 1 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_allowedRCodes | Set of String |   | V_allowedRCodes | The authorized values for the reason code |    
3 | 2 | 1 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_defaultRCode | Simple of String |   | V_defaultRCode | The default value for the reason code |    
3 | 2 | 1 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_approvalCriteria | Simple of String |   | V_approvalCriteria | The criteria for the approval |    
3 | 2 | 1 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_performerType | Simple of String |   | V_performerType | The performer type to be considered for the approval activity |    
3 | 2 | 1 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_specificNumber | Simple of Integer |   | V_specificNumber | The performer type to be considered for the approval activity |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_isSecured | Simple of Boolean |   | V_isSecured | Specifies whether the user should authenticate for his response |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_execMode | Simple of String | Inherited | V_execMode |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_generatorId | Simple of String | Inherited | V_generatorId |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_instantiateOnce | Simple of Boolean | Inherited | V_instantiateOnce |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_subProcess | Simple of Oid | Inherited | C_subProcess |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_multiplicity | Simple of String | Inherited | V_multiplicity |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_cost | Simple of String | Inherited | V_cost |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_waitingTime | Simple of Integer | Inherited | V_waitingTime |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_startMode | Simple of String | Inherited | C_startMode |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_finishMode | Simple of String | Inherited | C_finishMode |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_performer | Simple of Oid | Inherited | C_performer |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_id | Simple of String | Inherited | V_id |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_icon | Simple of String | Inherited | C_icon |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_expectedCFT | Simple of Integer | Inherited | C_expectedCFT |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_receivedCFT | Simple of Integer | Inherited | C_receivedCFT |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_CFTSourceNames | Set of String | Inherited | C_CFTSourceNames |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_expectedInputs | Set of String | Inherited | C_expectedInputs |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_expectedOutputs | Set of String | Inherited | C_expectedOutputs |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_inputs | Set of Oid | Inherited | C_inputs |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_outputs | Set of Oid | Inherited | C_outputs |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_TransRestriction | Simple of Oid | Inherited | C_TransRestriction |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_documentation | Simple of String | Inherited | V_documentation |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_entryCondition | Simple of String | Inherited | V_entryCondition |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_exitCondition | Simple of String | Inherited | V_exitCondition |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_exitCode | Simple of Integer | Inherited | V_exitCode |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_isEarly | Simple of Boolean | Inherited | C_isEarly |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_workingStatus | Simple of String | Inherited | V_workingStatus |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_workingLCycleName | Simple of String | Inherited | V_workingLCycleName |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_isVisited | Simple of Boolean | Inherited | C_isVisited |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_inTransitions | Set of Oid | Inherited | C_inTransitions |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_outTransitions | Set of Oid | Inherited | C_outTransitions |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_name | Simple of String | Inherited | V_name |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_description | Simple of String | Inherited | V_description |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_abstract | Simple of String | Inherited | V_abstract |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_creator | Simple of String | Inherited | V_creator |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_user | Simple of String | Inherited | V_user |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_organization | Simple of String | Inherited | V_organization |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_project | Simple of String | Inherited | V_project |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_priority | Simple of String | Inherited | V_priority |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_status | Simple of String | Inherited | V_status |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V506_graph | Simple of URL | Inherited | V506_graph |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_start_date | Simple of Timestamp | Inherited | V_start_date |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_end_date | Simple of Timestamp | Inherited | V_end_date |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_actual_start_date | Simple of Timestamp | Inherited | V_actual_start_date |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_actual_end_date | Simple of Timestamp | Inherited | V_actual_end_date |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_duration | Simple of Integer | Inherited | V_duration |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_durationUnit | Simple of String | Inherited | V_durationUnit |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_progress | Simple of String | Inherited | V_progress |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_workingTimeUnit | Simple of String | Inherited | V_workingTimeUnit |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_workingTime | Simple of Integer | Inherited | V_workingTime |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_del_date | Simple of Timestamp | Inherited | V_del_date |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V506_del_int | Simple of Integer | Inherited | V506_del_int |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | V_lastmodif_user | Simple of String | Inherited | V_lastmodif_user |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_created | Simple of Timestamp | Inherited | C_created |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_modified | Simple of Timestamp | Inherited | C_modified |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C508_isCompleted | Simple of Boolean | Inherited | C508_isCompleted |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_datas | Set of Oid | Inherited | C_datas |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_histories | Set of Oid | Inherited | C_histories |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_objects | Set of Oid | Inherited | C_objects |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_attachements | Set of Oid | Inherited | C_attachements |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C506_resps | Set of Oid | Inherited | C506_resps |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_process | Inverse of WFProcess.C_activities (Simple) | Inherited | C_process |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_Linked1 | Inverse of AFLLink.C_action1 (Set) | Inherited | C_Linked1 |   |    
3 | 2 | 0 | New object | VPMWFL | ACTION | WFApprovalSubflow | Class | WFProceduralSubflow | C_Linked2 | Inverse of AFLLink.C_action2 (Set) | Inherited | C_Linked2 |   |    
[Top]

* * *

History Version: **1** [Nov 2003] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 1994-2003, Dassault Systmes. All rights reserved._
