---
title: "Changes to ENOVIA LCA Metadata in V5R15 Compared with V5R14"
category: "use-case"
module: "CAACenQuickRefs"
tags: "[]"
source_file: "Doc/online/CAACenQuickRefs/CAACenMetaExpR15vsR14.htm"
converted: "2026-05-11T17:33:46.992768"
---
tags: []
source_file: "Doc/online/CAACenQuickRefs/CAACenMetaExpR15vsR14.htmmd"
converted: "2026-05-11T17:33:46.992768"
CAA V5 Encyclopedia |  Changes to ENOVIA LCA Metadata in V5R15 Compared with V5R14

* * *

CAA V5 Encyclopedia |  Changes to ENOVIA LCA Metadata in V5R15 Compared with V5R14
Type | Owner | CAA | Message | Domain | Domain Inheritance | Object | Type | Object Inheritance | Attribute | Type | Inherited | Alias | Short role | Role

2 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction |  |  |  | Action_Simulation |  |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_execute | Simple of String |  | V_execute | The executable to run to perform the analysis or simulation |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_applName | Simple of String |  | V_applName | The analysis or simulation software name |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_applVersion | Simple of String |  | V_applVersion | The analysis or simulation software name |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_executeOnServer | Simple of Boolean |  | V_executeOnServer | Indicator of client versus server execution |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_isSynchronous | Simple of Boolean |  | V_isSynchronous | Indicator of synchronous or asynchronous execution |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_execution_date | Simple of Timestamp |  | V_execution_date | Date of last analysis execution |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | C_products | Injective of Oid | Inherited | C_products | References to the products which modifications are to be tracked by the action |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_name | Simple of String | Inherited | V_name | The action name | It may be customized through a user exit
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_description | Simple of String | Inherited | V_description | The action short description |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_taskDocumentation | Simple of String | Inherited | V_taskDocumentation | The document ID of a document describing the work to be performed on the action |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_abstract | Simple of String | Inherited | V_abstract | The action abstract |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_creator | Simple of String | Inherited | V_creator | The user who created the action |
3 | 2 | 0 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_user | Simple of String | Inherited | V_user | The user who created the action |
3 | 2 | 0 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_organization | Simple of String | Inherited | V_organization | The user who created the action |
3 | 2 | 0 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_project | Simple of String | Inherited | V_project | The user who created the action |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_priority | Simple of String | Inherited | V_priority | The action priority |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_status | Simple of String | Inherited | V_status | The action current status |
3 | 2 | 0 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V506_graph | Simple of URL | Inherited | V506_graph | The action current status |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_start_date | Simple of Timestamp | Inherited | V_start_date | The action planned start date |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_end_date | Simple of Timestamp | Inherited | V_end_date | The action planned end date |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_actual_start_date | Simple of Timestamp | Inherited | V_actual_start_date | The action actual start date |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_actual_end_date | Simple of Timestamp | Inherited | V_actual_end_date | The action actual end date |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_duration | Simple of Integer | Inherited | V_duration | The action duration |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_durationTime | Simple of Real | Inherited | V_durationTime | The expected duration time |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_durationUnit | Simple of String | Inherited | V_durationUnit | The action duration unit |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_progress | Simple of String | Inherited | V_progress | The action progress |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_workTime | Simple of Real | Inherited | V_expectedTime | The action actual working time |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_workingTimeUnit | Simple of String | Inherited | V_elapsedTimeUnit | The action unit for working time |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_workingTime | Simple of Integer | Inherited | V_elapsedTime | The action actual working time |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_del_date | Simple of Timestamp | Inherited | V_del_date | The action delinquency date |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V506_del_int | Simple of Integer | Inherited | V506_del_int | The action delinquency interval |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_delIntervalTime | Simple of Real | Inherited | V_delIntervalTime | The action delinquency interval time |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_lastmodif_user | Simple of String | Inherited | V_lastmodif_user | The user who made the last modification |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | V_mfg_project | Simple of String | Inherited | V_mfg_project | Manufacturing Project Name |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | C_created | Simple of Timestamp | Inherited | C_created | The creation date of the Action |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | C_modified | Simple of Timestamp | Inherited | C_modified | The action modification date |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | C508_isCompleted | Simple of Boolean | Inherited | C508_isCompleted | A flag to specify whether the action is completed |
3 | 2 | 0 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | C_datas | Injective of Oid | Inherited | C_datas | A flag to specify whether the action is completed |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | C_histories | Injective of Oid | Inherited | C_histories | References to all action histories |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | C_objects | Injective of Oid | Inherited | C_objects | References to all action affected objects |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | C_attachements | Injective of Oid | Inherited | C_attachements | References to all action attachments |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | C506_resps | Injective of Oid | Inherited | C506_resps | References to all action responsibilities |
3 | 2 | 1 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | C_categories | Injective of Oid | Inherited | C_categories | References to affected object categories for classification |
3 | 2 | 0 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | C_Linked1 | Inverse of AFLLink.C_action1 (Set) | Inherited | C_Linked1 |  |
3 | 2 | 0 | New object | APLAFL | ACTION | Action_Simulation | Class | AFLBaseAction | C_Linked2 | Inverse of AFLLink.C_action2 (Set) | Inherited | C_Linked2 |  |
2 | 2 | 1 | New object | APLAFL | ACTION | Internal_Associated_Object | Class | AFLBaseObject |  |  |  | Internal_Associated_Object |  |
3 | 2 | 1 | New object | APLAFL | ACTION | Internal_Associated_Object | Class | AFLBaseObject | V_status | Simple of String | Inherited | V_status | The current status of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | Internal_Associated_Object | Class | AFLBaseObject | V506_graph | Simple of URL | Inherited | V506_graph | The current status of the affected object |
3 | 2 | 1 | New object | APLAFL | ACTION | Internal_Associated_Object | Class | AFLBaseObject | V_priority | Simple of String | Inherited | V_priority | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | Internal_Associated_Object | Class | AFLBaseObject | V_user | Simple of String | Inherited | V_user | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | Internal_Associated_Object | Class | AFLBaseObject | V_organization | Simple of String | Inherited | V_organization | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | Internal_Associated_Object | Class | AFLBaseObject | V_project | Simple of String | Inherited | V_project | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | Internal_Associated_Object | Class | AFLBaseObject | V_source | Simple of String | Inherited | V_source | The priority of the affected object |
3 | 2 | 1 | New object | APLAFL | ACTION | Internal_Associated_Object | Class | AFLBaseObject | C_object_id | Simple of URL | Inherited | C_object_id | The reference to the real object |
3 | 2 | 1 | New object | APLAFL | ACTION | Internal_Associated_Object | Class | AFLBaseObject | V_name | Simple of String | Inherited | V_name | Typically the name of the real object |
3 | 2 | 1 | New object | APLAFL | ACTION | Internal_Associated_Object | Class | AFLBaseObject | V_type | Simple of String | Inherited | V_type | The real object type |
3 | 2 | 1 | New object | APLAFL | ACTION | Internal_Associated_Object | Class | AFLBaseObject | V_value | Simple of String | Inherited | V_value | A value for a non-object type affected data |
3 | 2 | 1 | New object | APLAFL | ACTION | Internal_Associated_Object | Class | AFLBaseObject | V_object_description | Simple of String | Inherited | V_object_description | The real object short description |
3 | 2 | 1 | New object | APLAFL | ACTION | Internal_Associated_Object | Class | AFLBaseObject | C_created | Simple of Timestamp | Inherited | C_created | The real object creation date |
3 | 2 | 1 | New object | APLAFL | ACTION | Internal_Associated_Object | Class | AFLBaseObject | C_modified | Simple of Timestamp | Inherited | C_modified | The real object modification date |
```vbscript
3 | 2 | 1 | New object | APLAFL | ACTION | Internal_Associated_Object | Class | AFLBaseObject | C506_objects | Set of Oid | Inherited | C506_objects | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | Internal_Associated_Object | Class | AFLBaseObject | C_changeType | Simple of String | Inherited | C_changeType | References to other affected objects |
```
3 | 2 | 0 | New object | APLAFL | ACTION | Internal_Associated_Object | Class | AFLBaseObject | C_changeAction | Simple of String | Inherited | C_changeAction | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | Internal_Associated_Object | Class | AFLBaseObject | C_manuallyAdded | Simple of Boolean | Inherited | C_manuallyAdded | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | Internal_Associated_Object | Class | AFLBaseObject | C_actuallyChanged | Simple of Boolean | Inherited | C_actuallyChanged | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | Internal_Associated_Object | Class | AFLBaseObject | C_related_action | Inverse of AFLAction.C_objects (Simple) | Inherited | C_related_action |  |
3 | 2 | 0 | New object | APLAFL | ACTION | Internal_Associated_Object | Class | AFLBaseObject | C506_inv_objects | Inverse of AFLAffected_Object.C506_objects (Set) | Inherited | C506_inv_objects |  |
2 | 2 | 1 | New object | APLAFL | ACTION | Validated_Associated_Object | Class | AFLBaseObject |  |  |  | Validated_Associated_Object |  |
3 | 2 | 1 | New object | APLAFL | ACTION | Validated_Associated_Object | Class | AFLBaseObject | V_status | Simple of String | Inherited | V_status | The current status of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | Validated_Associated_Object | Class | AFLBaseObject | V506_graph | Simple of URL | Inherited | V506_graph | The current status of the affected object |
3 | 2 | 1 | New object | APLAFL | ACTION | Validated_Associated_Object | Class | AFLBaseObject | V_priority | Simple of String | Inherited | V_priority | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | Validated_Associated_Object | Class | AFLBaseObject | V_user | Simple of String | Inherited | V_user | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | Validated_Associated_Object | Class | AFLBaseObject | V_organization | Simple of String | Inherited | V_organization | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | Validated_Associated_Object | Class | AFLBaseObject | V_project | Simple of String | Inherited | V_project | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | Validated_Associated_Object | Class | AFLBaseObject | V_source | Simple of String | Inherited | V_source | The priority of the affected object |
3 | 2 | 1 | New object | APLAFL | ACTION | Validated_Associated_Object | Class | AFLBaseObject | C_object_id | Simple of URL | Inherited | C_object_id | The reference to the real object |
3 | 2 | 1 | New object | APLAFL | ACTION | Validated_Associated_Object | Class | AFLBaseObject | V_name | Simple of String | Inherited | V_name | Typically the name of the real object |
3 | 2 | 1 | New object | APLAFL | ACTION | Validated_Associated_Object | Class | AFLBaseObject | V_type | Simple of String | Inherited | V_type | The real object type |
3 | 2 | 1 | New object | APLAFL | ACTION | Validated_Associated_Object | Class | AFLBaseObject | V_value | Simple of String | Inherited | V_value | A value for a non-object type affected data |
3 | 2 | 1 | New object | APLAFL | ACTION | Validated_Associated_Object | Class | AFLBaseObject | V_object_description | Simple of String | Inherited | V_object_description | The real object short description |
3 | 2 | 1 | New object | APLAFL | ACTION | Validated_Associated_Object | Class | AFLBaseObject | C_created | Simple of Timestamp | Inherited | C_created | The real object creation date |
3 | 2 | 1 | New object | APLAFL | ACTION | Validated_Associated_Object | Class | AFLBaseObject | C_modified | Simple of Timestamp | Inherited | C_modified | The real object modification date |
```vbscript
3 | 2 | 1 | New object | APLAFL | ACTION | Validated_Associated_Object | Class | AFLBaseObject | C506_objects | Set of Oid | Inherited | C506_objects | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | Validated_Associated_Object | Class | AFLBaseObject | C_changeType | Simple of String | Inherited | C_changeType | References to other affected objects |
```
3 | 2 | 0 | New object | APLAFL | ACTION | Validated_Associated_Object | Class | AFLBaseObject | C_changeAction | Simple of String | Inherited | C_changeAction | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | Validated_Associated_Object | Class | AFLBaseObject | C_manuallyAdded | Simple of Boolean | Inherited | C_manuallyAdded | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | Validated_Associated_Object | Class | AFLBaseObject | C_actuallyChanged | Simple of Boolean | Inherited | C_actuallyChanged | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | Validated_Associated_Object | Class | AFLBaseObject | C_related_action | Inverse of AFLAction.C_objects (Simple) | Inherited | C_related_action |  |
3 | 2 | 0 | New object | APLAFL | ACTION | Validated_Associated_Object | Class | AFLBaseObject | C506_inv_objects | Inverse of AFLAffected_Object.C506_objects (Set) | Inherited | C506_inv_objects |  |
2 | 2 | 1 | New object | APLAFL | ACTION | Specification_Associated_Object | Class | AFLBaseObject |  |  |  | Specification_Associated_Object |  |
3 | 2 | 1 | New object | APLAFL | ACTION | Specification_Associated_Object | Class | AFLBaseObject | V_status | Simple of String | Inherited | V_status | The current status of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | Specification_Associated_Object | Class | AFLBaseObject | V506_graph | Simple of URL | Inherited | V506_graph | The current status of the affected object |
3 | 2 | 1 | New object | APLAFL | ACTION | Specification_Associated_Object | Class | AFLBaseObject | V_priority | Simple of String | Inherited | V_priority | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | Specification_Associated_Object | Class | AFLBaseObject | V_user | Simple of String | Inherited | V_user | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | Specification_Associated_Object | Class | AFLBaseObject | V_organization | Simple of String | Inherited | V_organization | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | Specification_Associated_Object | Class | AFLBaseObject | V_project | Simple of String | Inherited | V_project | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | Specification_Associated_Object | Class | AFLBaseObject | V_source | Simple of String | Inherited | V_source | The priority of the affected object |
3 | 2 | 1 | New object | APLAFL | ACTION | Specification_Associated_Object | Class | AFLBaseObject | C_object_id | Simple of URL | Inherited | C_object_id | The reference to the real object |
3 | 2 | 1 | New object | APLAFL | ACTION | Specification_Associated_Object | Class | AFLBaseObject | V_name | Simple of String | Inherited | V_name | Typically the name of the real object |
3 | 2 | 1 | New object | APLAFL | ACTION | Specification_Associated_Object | Class | AFLBaseObject | V_type | Simple of String | Inherited | V_type | The real object type |
3 | 2 | 1 | New object | APLAFL | ACTION | Specification_Associated_Object | Class | AFLBaseObject | V_value | Simple of String | Inherited | V_value | A value for a non-object type affected data |
3 | 2 | 1 | New object | APLAFL | ACTION | Specification_Associated_Object | Class | AFLBaseObject | V_object_description | Simple of String | Inherited | V_object_description | The real object short description |
3 | 2 | 1 | New object | APLAFL | ACTION | Specification_Associated_Object | Class | AFLBaseObject | C_created | Simple of Timestamp | Inherited | C_created | The real object creation date |
3 | 2 | 1 | New object | APLAFL | ACTION | Specification_Associated_Object | Class | AFLBaseObject | C_modified | Simple of Timestamp | Inherited | C_modified | The real object modification date |
```vbscript
3 | 2 | 1 | New object | APLAFL | ACTION | Specification_Associated_Object | Class | AFLBaseObject | C506_objects | Set of Oid | Inherited | C506_objects | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | Specification_Associated_Object | Class | AFLBaseObject | C_changeType | Simple of String | Inherited | C_changeType | References to other affected objects |
```
3 | 2 | 0 | New object | APLAFL | ACTION | Specification_Associated_Object | Class | AFLBaseObject | C_changeAction | Simple of String | Inherited | C_changeAction | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | Specification_Associated_Object | Class | AFLBaseObject | C_manuallyAdded | Simple of Boolean | Inherited | C_manuallyAdded | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | Specification_Associated_Object | Class | AFLBaseObject | C_actuallyChanged | Simple of Boolean | Inherited | C_actuallyChanged | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | Specification_Associated_Object | Class | AFLBaseObject | C_related_action | Inverse of AFLAction.C_objects (Simple) | Inherited | C_related_action |  |
3 | 2 | 0 | New object | APLAFL | ACTION | Specification_Associated_Object | Class | AFLBaseObject | C506_inv_objects | Inverse of AFLAffected_Object.C506_objects (Set) | Inherited | C506_inv_objects |  |
2 | 2 | 1 | New object | APLAFL | ACTION | Context_Associated_Object | Class | AFLBaseObject |  |  |  | Context_Associated_Object |  |
3 | 2 | 1 | New object | APLAFL | ACTION | Context_Associated_Object | Class | AFLBaseObject | V_status | Simple of String | Inherited | V_status | The current status of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | Context_Associated_Object | Class | AFLBaseObject | V506_graph | Simple of URL | Inherited | V506_graph | The current status of the affected object |
3 | 2 | 1 | New object | APLAFL | ACTION | Context_Associated_Object | Class | AFLBaseObject | V_priority | Simple of String | Inherited | V_priority | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | Context_Associated_Object | Class | AFLBaseObject | V_user | Simple of String | Inherited | V_user | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | Context_Associated_Object | Class | AFLBaseObject | V_organization | Simple of String | Inherited | V_organization | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | Context_Associated_Object | Class | AFLBaseObject | V_project | Simple of String | Inherited | V_project | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | Context_Associated_Object | Class | AFLBaseObject | V_source | Simple of String | Inherited | V_source | The priority of the affected object |
3 | 2 | 1 | New object | APLAFL | ACTION | Context_Associated_Object | Class | AFLBaseObject | C_object_id | Simple of URL | Inherited | C_object_id | The reference to the real object |
3 | 2 | 1 | New object | APLAFL | ACTION | Context_Associated_Object | Class | AFLBaseObject | V_name | Simple of String | Inherited | V_name | Typically the name of the real object |
3 | 2 | 1 | New object | APLAFL | ACTION | Context_Associated_Object | Class | AFLBaseObject | V_type | Simple of String | Inherited | V_type | The real object type |
3 | 2 | 1 | New object | APLAFL | ACTION | Context_Associated_Object | Class | AFLBaseObject | V_value | Simple of String | Inherited | V_value | A value for a non-object type affected data |
3 | 2 | 1 | New object | APLAFL | ACTION | Context_Associated_Object | Class | AFLBaseObject | V_object_description | Simple of String | Inherited | V_object_description | The real object short description |
3 | 2 | 1 | New object | APLAFL | ACTION | Context_Associated_Object | Class | AFLBaseObject | C_created | Simple of Timestamp | Inherited | C_created | The real object creation date |
3 | 2 | 1 | New object | APLAFL | ACTION | Context_Associated_Object | Class | AFLBaseObject | C_modified | Simple of Timestamp | Inherited | C_modified | The real object modification date |
```vbscript
3 | 2 | 1 | New object | APLAFL | ACTION | Context_Associated_Object | Class | AFLBaseObject | C506_objects | Set of Oid | Inherited | C506_objects | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | Context_Associated_Object | Class | AFLBaseObject | C_changeType | Simple of String | Inherited | C_changeType | References to other affected objects |
```
3 | 2 | 0 | New object | APLAFL | ACTION | Context_Associated_Object | Class | AFLBaseObject | C_changeAction | Simple of String | Inherited | C_changeAction | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | Context_Associated_Object | Class | AFLBaseObject | C_manuallyAdded | Simple of Boolean | Inherited | C_manuallyAdded | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | Context_Associated_Object | Class | AFLBaseObject | C_actuallyChanged | Simple of Boolean | Inherited | C_actuallyChanged | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | Context_Associated_Object | Class | AFLBaseObject | C_related_action | Inverse of AFLAction.C_objects (Simple) | Inherited | C_related_action |  |
3 | 2 | 0 | New object | APLAFL | ACTION | Context_Associated_Object | Class | AFLBaseObject | C506_inv_objects | Inverse of AFLAffected_Object.C506_objects (Set) | Inherited | C506_inv_objects |  |
2 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Clash | Class | AFLBaseObject |  |  |  | AFLAffected_Clash |  |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Clash | Class | AFLBaseObject | V_status | Simple of String | Inherited | V_status | The current status of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Clash | Class | AFLBaseObject | V506_graph | Simple of URL | Inherited | V506_graph | The current status of the affected object |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Clash | Class | AFLBaseObject | V_priority | Simple of String | Inherited | V_priority | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Clash | Class | AFLBaseObject | V_user | Simple of String | Inherited | V_user | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Clash | Class | AFLBaseObject | V_organization | Simple of String | Inherited | V_organization | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Clash | Class | AFLBaseObject | V_project | Simple of String | Inherited | V_project | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Clash | Class | AFLBaseObject | V_source | Simple of String | Inherited | V_source | The priority of the affected object |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Clash | Class | AFLBaseObject | C_object_id | Simple of URL | Inherited | C_object_id | The reference to the real object |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Clash | Class | AFLBaseObject | V_name | Simple of String | Inherited | V_name | Typically the name of the real object |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Clash | Class | AFLBaseObject | V_type | Simple of String | Inherited | V_type | The real object type |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Clash | Class | AFLBaseObject | V_value | Simple of String | Inherited | V_value | A value for a non-object type affected data |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Clash | Class | AFLBaseObject | V_object_description | Simple of String | Inherited | V_object_description | The real object short description |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Clash | Class | AFLBaseObject | C_created | Simple of Timestamp | Inherited | C_created | The real object creation date |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Clash | Class | AFLBaseObject | C_modified | Simple of Timestamp | Inherited | C_modified | The real object modification date |
```vbscript
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Clash | Class | AFLBaseObject | C506_objects | Set of Oid | Inherited | C506_objects | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Clash | Class | AFLBaseObject | C_changeType | Simple of String | Inherited | C_changeType | References to other affected objects |
```
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Clash | Class | AFLBaseObject | C_changeAction | Simple of String | Inherited | C_changeAction | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Clash | Class | AFLBaseObject | C_manuallyAdded | Simple of Boolean | Inherited | C_manuallyAdded | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Clash | Class | AFLBaseObject | C_actuallyChanged | Simple of Boolean | Inherited | C_actuallyChanged | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Clash | Class | AFLBaseObject | C_related_action | Inverse of AFLAction.C_objects (Simple) | Inherited | C_related_action |  |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Clash | Class | AFLBaseObject | C506_inv_objects | Inverse of AFLAffected_Object.C506_objects (Set) | Inherited | C506_inv_objects |  |
2 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_PenetrationObject | Class | AFLBaseObject |  |  |  | AFLAffected_PenetrationObject |  |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_PenetrationObject | Class | AFLBaseObject | RelPath | Simple of String |  | RelPath |  |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_PenetrationObject | Class | AFLBaseObject | DisciplineCode | Simple of String |  | DisciplineCode |  |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_PenetrationObject | Class | AFLBaseObject | V_status | Simple of String | Inherited | V_status | The current status of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_PenetrationObject | Class | AFLBaseObject | V506_graph | Simple of URL | Inherited | V506_graph | The current status of the affected object |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_PenetrationObject | Class | AFLBaseObject | V_priority | Simple of String | Inherited | V_priority | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_PenetrationObject | Class | AFLBaseObject | V_user | Simple of String | Inherited | V_user | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_PenetrationObject | Class | AFLBaseObject | V_organization | Simple of String | Inherited | V_organization | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_PenetrationObject | Class | AFLBaseObject | V_project | Simple of String | Inherited | V_project | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_PenetrationObject | Class | AFLBaseObject | V_source | Simple of String | Inherited | V_source | The priority of the affected object |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_PenetrationObject | Class | AFLBaseObject | C_object_id | Simple of URL | Inherited | C_object_id | The reference to the real object |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_PenetrationObject | Class | AFLBaseObject | V_name | Simple of String | Inherited | V_name | Typically the name of the real object |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_PenetrationObject | Class | AFLBaseObject | V_type | Simple of String | Inherited | V_type | The real object type |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_PenetrationObject | Class | AFLBaseObject | V_value | Simple of String | Inherited | V_value | A value for a non-object type affected data |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_PenetrationObject | Class | AFLBaseObject | V_object_description | Simple of String | Inherited | V_object_description | The real object short description |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_PenetrationObject | Class | AFLBaseObject | C_created | Simple of Timestamp | Inherited | C_created | The real object creation date |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_PenetrationObject | Class | AFLBaseObject | C_modified | Simple of Timestamp | Inherited | C_modified | The real object modification date |
```vbscript
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_PenetrationObject | Class | AFLBaseObject | C506_objects | Set of Oid | Inherited | C506_objects | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_PenetrationObject | Class | AFLBaseObject | C_changeType | Simple of String | Inherited | C_changeType | References to other affected objects |
```
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_PenetrationObject | Class | AFLBaseObject | C_changeAction | Simple of String | Inherited | C_changeAction | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_PenetrationObject | Class | AFLBaseObject | C_manuallyAdded | Simple of Boolean | Inherited | C_manuallyAdded | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_PenetrationObject | Class | AFLBaseObject | C_actuallyChanged | Simple of Boolean | Inherited | C_actuallyChanged | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_PenetrationObject | Class | AFLBaseObject | C_related_action | Inverse of AFLAction.C_objects (Simple) | Inherited | C_related_action |  |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_PenetrationObject | Class | AFLBaseObject | C506_inv_objects | Inverse of AFLAffected_Object.C506_objects (Set) | Inherited | C506_inv_objects |  |
2 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Penetrating | Class | AFLAffected_PenetrationObject |  |  |  | AFLAffected_Penetrating |  |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrating | Class | AFLAffected_PenetrationObject | RelPath | Simple of String | Inherited | RelPath |  |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrating | Class | AFLAffected_PenetrationObject | DisciplineCode | Simple of String | Inherited | DisciplineCode |  |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Penetrating | Class | AFLAffected_PenetrationObject | V_status | Simple of String | Inherited | V_status | The current status of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrating | Class | AFLAffected_PenetrationObject | V506_graph | Simple of URL | Inherited | V506_graph | The current status of the affected object |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Penetrating | Class | AFLAffected_PenetrationObject | V_priority | Simple of String | Inherited | V_priority | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrating | Class | AFLAffected_PenetrationObject | V_user | Simple of String | Inherited | V_user | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrating | Class | AFLAffected_PenetrationObject | V_organization | Simple of String | Inherited | V_organization | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrating | Class | AFLAffected_PenetrationObject | V_project | Simple of String | Inherited | V_project | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrating | Class | AFLAffected_PenetrationObject | V_source | Simple of String | Inherited | V_source | The priority of the affected object |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Penetrating | Class | AFLAffected_PenetrationObject | C_object_id | Simple of URL | Inherited | C_object_id | The reference to the real object |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Penetrating | Class | AFLAffected_PenetrationObject | V_name | Simple of String | Inherited | V_name | Typically the name of the real object |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Penetrating | Class | AFLAffected_PenetrationObject | V_type | Simple of String | Inherited | V_type | The real object type |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Penetrating | Class | AFLAffected_PenetrationObject | V_value | Simple of String | Inherited | V_value | A value for a non-object type affected data |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Penetrating | Class | AFLAffected_PenetrationObject | V_object_description | Simple of String | Inherited | V_object_description | The real object short description |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Penetrating | Class | AFLAffected_PenetrationObject | C_created | Simple of Timestamp | Inherited | C_created | The real object creation date |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Penetrating | Class | AFLAffected_PenetrationObject | C_modified | Simple of Timestamp | Inherited | C_modified | The real object modification date |
```vbscript
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Penetrating | Class | AFLAffected_PenetrationObject | C506_objects | Set of Oid | Inherited | C506_objects | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrating | Class | AFLAffected_PenetrationObject | C_changeType | Simple of String | Inherited | C_changeType | References to other affected objects |
```
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrating | Class | AFLAffected_PenetrationObject | C_changeAction | Simple of String | Inherited | C_changeAction | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrating | Class | AFLAffected_PenetrationObject | C_manuallyAdded | Simple of Boolean | Inherited | C_manuallyAdded | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrating | Class | AFLAffected_PenetrationObject | C_actuallyChanged | Simple of Boolean | Inherited | C_actuallyChanged | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrating | Class | AFLAffected_PenetrationObject | C_related_action | Inverse of AFLAction.C_objects (Simple) | Inherited | C_related_action |  |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrating | Class | AFLAffected_PenetrationObject | C506_inv_objects | Inverse of AFLAffected_Object.C506_objects (Set) | Inherited | C506_inv_objects |  |
2 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Penetrated | Class | AFLAffected_PenetrationObject |  |  |  | AFLAffected_Penetrated |  |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrated | Class | AFLAffected_PenetrationObject | RelPath | Simple of String | Inherited | RelPath |  |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrated | Class | AFLAffected_PenetrationObject | DisciplineCode | Simple of String | Inherited | DisciplineCode |  |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Penetrated | Class | AFLAffected_PenetrationObject | V_status | Simple of String | Inherited | V_status | The current status of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrated | Class | AFLAffected_PenetrationObject | V506_graph | Simple of URL | Inherited | V506_graph | The current status of the affected object |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Penetrated | Class | AFLAffected_PenetrationObject | V_priority | Simple of String | Inherited | V_priority | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrated | Class | AFLAffected_PenetrationObject | V_user | Simple of String | Inherited | V_user | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrated | Class | AFLAffected_PenetrationObject | V_organization | Simple of String | Inherited | V_organization | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrated | Class | AFLAffected_PenetrationObject | V_project | Simple of String | Inherited | V_project | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrated | Class | AFLAffected_PenetrationObject | V_source | Simple of String | Inherited | V_source | The priority of the affected object |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Penetrated | Class | AFLAffected_PenetrationObject | C_object_id | Simple of URL | Inherited | C_object_id | The reference to the real object |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Penetrated | Class | AFLAffected_PenetrationObject | V_name | Simple of String | Inherited | V_name | Typically the name of the real object |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Penetrated | Class | AFLAffected_PenetrationObject | V_type | Simple of String | Inherited | V_type | The real object type |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Penetrated | Class | AFLAffected_PenetrationObject | V_value | Simple of String | Inherited | V_value | A value for a non-object type affected data |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Penetrated | Class | AFLAffected_PenetrationObject | V_object_description | Simple of String | Inherited | V_object_description | The real object short description |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Penetrated | Class | AFLAffected_PenetrationObject | C_created | Simple of Timestamp | Inherited | C_created | The real object creation date |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Penetrated | Class | AFLAffected_PenetrationObject | C_modified | Simple of Timestamp | Inherited | C_modified | The real object modification date |
```vbscript
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_Penetrated | Class | AFLAffected_PenetrationObject | C506_objects | Set of Oid | Inherited | C506_objects | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrated | Class | AFLAffected_PenetrationObject | C_changeType | Simple of String | Inherited | C_changeType | References to other affected objects |
```
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrated | Class | AFLAffected_PenetrationObject | C_changeAction | Simple of String | Inherited | C_changeAction | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrated | Class | AFLAffected_PenetrationObject | C_manuallyAdded | Simple of Boolean | Inherited | C_manuallyAdded | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrated | Class | AFLAffected_PenetrationObject | C_actuallyChanged | Simple of Boolean | Inherited | C_actuallyChanged | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrated | Class | AFLAffected_PenetrationObject | C_related_action | Inverse of AFLAction.C_objects (Simple) | Inherited | C_related_action |  |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_Penetrated | Class | AFLAffected_PenetrationObject | C506_inv_objects | Inverse of AFLAffected_Object.C506_objects (Set) | Inherited | C506_inv_objects |  |
2 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_CutoutSketch | Class | AFLAffected_PenetrationObject |  |  |  | AFLAffected_CutoutSketch |  |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_CutoutSketch | Class | AFLAffected_PenetrationObject | RelPath | Simple of String | Inherited | RelPath |  |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_CutoutSketch | Class | AFLAffected_PenetrationObject | DisciplineCode | Simple of String | Inherited | DisciplineCode |  |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_CutoutSketch | Class | AFLAffected_PenetrationObject | V_status | Simple of String | Inherited | V_status | The current status of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_CutoutSketch | Class | AFLAffected_PenetrationObject | V506_graph | Simple of URL | Inherited | V506_graph | The current status of the affected object |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_CutoutSketch | Class | AFLAffected_PenetrationObject | V_priority | Simple of String | Inherited | V_priority | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_CutoutSketch | Class | AFLAffected_PenetrationObject | V_user | Simple of String | Inherited | V_user | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_CutoutSketch | Class | AFLAffected_PenetrationObject | V_organization | Simple of String | Inherited | V_organization | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_CutoutSketch | Class | AFLAffected_PenetrationObject | V_project | Simple of String | Inherited | V_project | The priority of the affected object |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_CutoutSketch | Class | AFLAffected_PenetrationObject | V_source | Simple of String | Inherited | V_source | The priority of the affected object |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_CutoutSketch | Class | AFLAffected_PenetrationObject | C_object_id | Simple of URL | Inherited | C_object_id | The reference to the real object |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_CutoutSketch | Class | AFLAffected_PenetrationObject | V_name | Simple of String | Inherited | V_name | Typically the name of the real object |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_CutoutSketch | Class | AFLAffected_PenetrationObject | V_type | Simple of String | Inherited | V_type | The real object type |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_CutoutSketch | Class | AFLAffected_PenetrationObject | V_value | Simple of String | Inherited | V_value | A value for a non-object type affected data |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_CutoutSketch | Class | AFLAffected_PenetrationObject | V_object_description | Simple of String | Inherited | V_object_description | The real object short description |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_CutoutSketch | Class | AFLAffected_PenetrationObject | C_created | Simple of Timestamp | Inherited | C_created | The real object creation date |
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_CutoutSketch | Class | AFLAffected_PenetrationObject | C_modified | Simple of Timestamp | Inherited | C_modified | The real object modification date |
```vbscript
3 | 2 | 1 | New object | APLAFL | ACTION | AFLAffected_CutoutSketch | Class | AFLAffected_PenetrationObject | C506_objects | Set of Oid | Inherited | C506_objects | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_CutoutSketch | Class | AFLAffected_PenetrationObject | C_changeType | Simple of String | Inherited | C_changeType | References to other affected objects |
```
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_CutoutSketch | Class | AFLAffected_PenetrationObject | C_changeAction | Simple of String | Inherited | C_changeAction | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_CutoutSketch | Class | AFLAffected_PenetrationObject | C_manuallyAdded | Simple of Boolean | Inherited | C_manuallyAdded | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_CutoutSketch | Class | AFLAffected_PenetrationObject | C_actuallyChanged | Simple of Boolean | Inherited | C_actuallyChanged | References to other affected objects |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_CutoutSketch | Class | AFLAffected_PenetrationObject | C_related_action | Inverse of AFLAction.C_objects (Simple) | Inherited | C_related_action |  |
3 | 2 | 0 | New object | APLAFL | ACTION | AFLAffected_CutoutSketch | Class | AFLAffected_PenetrationObject | C506_inv_objects | Inverse of AFLAffected_Object.C506_objects (Set) | Inherited | C506_inv_objects |  |
2 | 2 | 1 | New object | ACTION |  | AFLCategory | Class |  |  |  |  | AFLCategory |  |
3 | 2 | 1 | New object | ACTION |  | AFLCategory | Class |  | V_type | Simple of String |  | V_type | An affected object type |
```vbscript
3 | 2 | 1 | New object | ACTION |  | AFLCategory | Class |  | C_associations | Set of Oid |  | C_associations | References to category associations |
3 | 2 | 0 | New object | ACTION |  | AFLCategory | Class |  | C_related_action | Inverse of AFLAction.C_categories (Simple) |  | C_related_action | References to category associations |
```
2 | 2 | 1 | New object | ACTION |  | AFLCategoryAssociation | Class |  |  |  |  | AFLCategoryAssociation |  |
3 | 2 | 1 | New object | ACTION |  | AFLCategoryAssociation | Class |  | C_folder_id | Simple of URL |  | C_folder_id | The reference to a folder |
3 | 2 | 1 | New object | ACTION |  | AFLCategoryAssociation | Class |  | V_description | Simple of String |  | V_description | A description of the category association |
3 | 2 | 0 | New object | ACTION |  | AFLCategoryAssociation | Class |  | C_related_category | Inverse of AFLCategory.C_associations (Simple) |  | C_related_category | A description of the category association |
2 | 2 | 1 | New object | ACTION |  | AFLRootCategoryAssociation | Class | AFLCategoryAssociation |  |  |  | AFLRootCategoryAssociation |  |
3 | 2 | 1 | New object | ACTION |  | AFLRootCategoryAssociation | Class | AFLCategoryAssociation | C_folder_id | Simple of URL | Inherited | C_folder_id | The reference to a folder |
3 | 2 | 1 | New object | ACTION |  | AFLRootCategoryAssociation | Class | AFLCategoryAssociation | V_description | Simple of String | Inherited | V_description | A description of the category association |
3 | 2 | 0 | New object | ACTION |  | AFLRootCategoryAssociation | Class | AFLCategoryAssociation | C_related_category | Inverse of AFLCategory.C_associations (Simple) | Inherited | C_related_category |  |

[Top]

* * *

History Version: **1** [Mar 2005] | Document created
---|---
[Top]

* * *

_Copyright 1994-2005, Dassault Systmes. All rights reserved._
