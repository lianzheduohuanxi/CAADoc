---
title: "Running Light Query"
category: "use case"
module: "CAADkoUseCases"
tags: ["CATIVpmLightQueryManager", "CAAVPMDesktopObjects", "CATIVpmPredicate_var", "CATIVpmQuery_var", "CAADkoLightQuery", "CATIVpmPathExpression_var", "CATIVpmLightQueryManager_var", "CATIVpmFactoryManager_var"]
source_file: "Doc\online\CAADkoUseCases\CAADkoLightQuery.htm"
converted: "2026-05-11T17:33:45.996993"
---

Lifecycle Applications |  EBOM Part & Assembly Detailing |  Running Light Query _Running Light Query_  
---|---|---  
Use Case  
  
* * *

Abstract This article shows how to run a Light Query to get data on objects and delete all the memory used to run that query.

  * **What You Will Learn With This Use Case**
  * **The CAADkoLightQuery Use Case**
    * What Does CAADkoLightQuery Do
    * How to Launch CAADkoLightQuery
    * Where to Find the CAADkoLightQuery Code
  * **Step-by-Step**
  * **In Short**
  * **References**

  
---  
  
* * *

What You Will Learn With This Use Case This use case is intended to show you how to run a Light Query. To get information on the objects found in the memory of the session or in the database, a query has to be run. The information is then used to execute business processes: make some checks, print some reports, modify the objects. The query gets the objects matching a predicate, and all the attributes of those objects are accessible. The objects are loaded in memory.  
The first problem with that traditional query is that it is time consuming: all the attribute values are read from the database even though just a few of them will be used, and loading the objects in memory takes time. The second problem is that once the objects are in memory, they can't be removed from the session's server memory. After a while, depending on the number of objects, the memory gets full. To remedy those problems, the Light Query has been implemented. Light Query is using a small structure to hold the attribute values, structure that is deleted once the query is done. The objects are not loaded in memory. The improvements are found on the time spent to execute the query and on the memory spent to execute the process. Inside the Light Query, only the attributes values asked for in input are retrieved. [Top] The CAADkoLightQuery Use Case CAADkoLightQuery is a use case of the CAAVPMDesktopObjects.edu framework that illustrates VPMDesktopObjects, VPMInterfaces and VPMPersistency framework capabilities. [Top] What Does CAADkoLightQuery Do CAADkoLightQuery is a stand-alone executable that runs a Light Query to get a list of Part Instances and print some information about those Part Instances. CATIVpmLightQueryManager is used to run the Light Query and get the Part Instances.

  1. In this use case, we set up the Light Query to get the Part Instances matching a filter. We define if the query is case sensitive or not, if it has to be run in database and memory or database only. We select the list of attributes that we want to get. We define the attribute used to sort the results. 
  2. On the results, we print the Part Number and the UUID (unique identifier) of each Part Instance. 

[Top] How to Launch CAADkoLightQuery To launch CAADkoLightQuery, you will need to set up the build time environment, then compile CAADkoLightQuery along with its prerequisites, set up the run time environment, and then execute the use case [1]. [Top] Where to Find the CAADkoLightQuery Code The CAADkoLightQuery use case is made of a single file located in the CAADkoLightQuery.m module of the CAAVPMDesktopObjects.edu framework: Windows | `InstallRootDirectory\CAAVPMDesktopObjects.edu\CAADkoLightQuery.m\`  
---|---  
Unix | `InstallRootDirectory/CAAVPMDesktopObjects.edu/CAADkoLightQuery.m/`  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed. [Top] Step-by-Step There are five logical steps in CAADkoLightQuery:

  1. Get the Light Query Manager
  2. Define the Light Query parameter
  3. Run the Light Query
  4. Use the results to print some information
  5. Delete the Light Query result structure

[Top] Get the Light Query Manager The Light Query Manager is an extension of the Factory Manager, it is retrieved by a simple Query Interface from the latter.  
The code is therefore : 
    
    
       CATIVpmFactoryManager_var theManager = NULL_var;
       RC = Session->GetVPMObjectFactory( theManager );
       CATIVpmLightQueryManager_var LightQueryManager( theManager );
            
  
---  
[Top] Define the Light Query parameter The first part is to define the entity on which the query will be run, and the predicate to apply for this query. This is not new to Light Query and is done the same way, with the same API than before. Here we define the query on the VPMItemInstance entity with a predicate on the V_ID attribute of the Part Master. 
    
    
       CATIVpmPathExpression_var PathExpr = CreatePathExpression( "VPMItemInstance", "V_PV.V_master.V_ID" );
       CORBAAny cvalue;
       CATUnicodeString SearchValue = NameBase + "%";
       cvalue << SearchValue;
       CATIVpmPredicate_var WhereClause = ::IsLike( PathExpr, cvalue );
       CATIVpmQuery_var Query = CreateQuery( "VPMItemInstance", NULL_var, WhereClause );
            
  
---  
The query is defined to be case sensitive. 
    
    
       Query->SetCaseSensitive();
            
  
---  
The Light Query can be run in database only or in database and memory. The next parameter sets the run in database and memory. 
    
    
       QueryType TypeOfQuery = DatabaseAndMemory;
            
  
---  
We define the list of attributes for which we want to get the values in the result. This is the Select Clause of the query. The attributes that can be used in the Select Clause are defined in the metadata file defining the entity. For the lock information, two additional string attributes can be used: LOCKUSER and LOCKSTATUS. For the site ownership information, the additional binary attribute OWNERSITE can be used.  
If the entity on which the query is run is linked to another entity by a direct relationship attribute (not multi-valuated, not inverse), then the attributes of that linked entity can also be used in the Select Clause. Here, we put some attributes of the Part Version entity, the Part Master entity, the parent PRC, the parent AR and the parent ItemInstance. 
    
    
       // We define the Select Clause. This is the list of attributes for which we want the values on the parts matching the Where Clause, result of the query.
       CATListOfCATUnicodeString SelectClause;
    
       // We can get some attributes on the instance
       SelectClause.Append( "VPMItemInstance::V_instance_ID" );
       SelectClause.Append( "VPMItemInstance::V_user" );
       SelectClause.Append( "VPMItemInstance::C_created" );
       SelectClause.Append( "VPMItemInstance::V_organization" );
       SelectClause.Append( "VPMItemInstance::V_discipline" );
       SelectClause.Append( "VPMItemInstance::V_level" );
       SelectClause.Append( "VPMItemInstance::V_status" );
       SelectClause.Append( "VPMItemInstance::V_volume_x1" );
       SelectClause.Append( "VPMItemInstance::V_PV" );
       SelectClause.Append( "VPMItemInstance::LOCKUSER" );
       SelectClause.Append( "VPMItemInstance::OWNERSITE" );
    
       // We can get some attributes on the Part Version
       SelectClause.Append( "VPMItemInstance::V_PV.C_created" );
       SelectClause.Append( "VPMItemInstance::V_PV.V_user" );
       SelectClause.Append( "VPMItemInstance::V_PV.V_version" );
       SelectClause.Append( "VPMItemInstance::V_PV.V_status" );
       SelectClause.Append( "VPMItemInstance::V_PV.V_master" );
       SelectClause.Append( "VPMItemInstance::V_PV.LOCKUSER" );
       SelectClause.Append( "VPMItemInstance::V_PV.OWNERSITE" );
    
       // We can get some attributes on the Part Master
       SelectClause.Append( "VPMItemInstance::V_PV.V_master.V_ID" );
       SelectClause.Append( "VPMItemInstance::V_PV.V_master.C_created" );
       SelectClause.Append( "VPMItemInstance::V_PV.V_master.V_user" );
       SelectClause.Append( "VPMItemInstance::V_PV.V_master.V_name" );
       SelectClause.Append( "VPMItemInstance::V_PV.V_master.V512_IsConfigured" );
    
       // We can get some attributes on the Parent PRC
       SelectClause.Append( "VPMItemInstance::V_parent_PRC.V_ID" );
    
       // We can get some attributes on the Parent AR, if there is one
       SelectClause.Append( "VPMItemInstance::V_AR.V_instance_ID" );
    
       // We can get some attributes on the Parent II, if there is one
       SelectClause.Append( "VPMItemInstance::V_parent_II.V_instance_ID" );
       SelectClause.Append( "VPMItemInstance::V_parent_II.V_discipline" );
            
  
---  
Finally, we choose the attribute used to sort the results. This attribute can be undefined (empty), so that no sort is applied on the results. If the attribute is defined, it must be one of the attributes of the Select Clause. It can be an attribute of type string, integer, date or real. Any attempt to sort the results on another type of attribute will result in a failure.  
Here we sort the results according to the values of the V_level integer attribute on the VPMItemInstance entity. 
    
    
       CATUnicodeString SortAttr( "VPMItemInstance::V_level" );
            
  
---  
[Top] Run the Light Query This step is easy, it just consists in calling the RunLightQuery method to execute the query.  

    
    
       RC = LightQueryManager->RunLightQuery( Query, SelectClause, SortAttr, TypeOfQuery, oQueryResult );
            
  
---  
[Top] Use the results to print some information First the Part Number attribute (the attribute V_ID on the PartMaster entity) values are read for each Part Instance in the result. Getting the values is done with the method getAllValuesForAttributes. 
    
    
          CATUnicodeString PartNumberAttributeName( "VPMItemInstance::V_PV.V_master.V_ID" );
          _SEQUENCE_CORBAAny PartNumberValues;
          CATListOfInt IsSet;
          RC = oQueryResult->getAllValuesForAttribute( PartNumberAttributeName, PartNumberValues, IsSet );
            
  
---  
The values are put in a sequence of CORBAAny objects. The method fills a list of integers, IsSet, that have the value 1 if the attribute is set (has a defined value) or 0 if the attribute is unset (the attribute does not have a value). If the IsSet flag is set to 0, then the value found in the CORBAAny is meaningless.  
Once we have the values, we print them out: 
    
    
          int nbValues = PartNumberValues.length();
          for( int i=1; i<=nbValues; i++ )
          {
             CATUnicodeString PartNumber;
             PartNumberValues[i-1] >> PartNumber;
    
             TRACE << "Part at index " << i << " has a Part Number ";
             if ( IsSet[i] == 1 )
             {
                TRACE << "with value : " << PartNumber << endl;
             }
             else
             {
                TRACE << "unset" << endl;
             }
          }
            
  
---  
After that, we get the unique identifiers (UUID) of each Part Instance. This is done by calling the static method getUUIDs on the interface ENOVLightQueryToFullObjectsServices. 
    
    
          CATListOfInt Indexes;
          CATLISTV(_SEQUENCE_octet) UUIDs;
          RC = ENOVLightQueryToFullObjectsServices::getUUIDs( Indexes, UUIDs, oQueryResult );
          int nbUUIDs = UUIDs.Size();
          for( i=1; i <= nbUUIDs; i++ )
          {
             TRACE << "Part at index " << i << " has the UUID : " << GetHexaValue( UUIDs[i] ) << endl;
          }
            
  
---  
[Top] Delete the Light Query result structure It is very important at the end to delete the structure used by the Light Query to retrieve the data. No object has been loaded in memory during the Light Query, but all the attribute values and object identifiers are stored in that structure. Deleting the structure will ensure that the server memory at the end of the Light Query is the same as the memory at the start of the Light Query. 
    
    
          delete oQueryResult; oQueryResult = NULL;
            
  
---  
[Top]

* * *

In Short Running Light Query on the server consists in getting the Light Query Manager, defining the parameters of the Light Query, running the Light Query, reading the results of the Light Query and deleting the result structure to clean all the memory used by the Light Query. [Top]

* * *

References [1] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.htm)  
---|---  
[Top]  
  
* * *

History Version: **1** [Sep 2013] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2013, Dassault Systmes. All rights reserved._
