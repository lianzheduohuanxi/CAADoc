---
```vbscript
title: "Running Light Expand"
category: "use case"
module: "CAADkoUseCases"
tags: ["CATIVpmLightExpandObject", "CAAVPMDesktopObjects", "CAADkoLightExpand"]
source_file: "Doc/online/CAADkoUseCases/CAADkoLightExpand.htm"
converted: "2026-05-11T17:33:45.981463"
```

---
tags: ["CATIVpmLightExpandObject", "CAAVPMDesktopObjects", "CAADkoLightExpand"]
source_file: "Doc/online/CAADkoUseCases/CAADkoLightExpand.htm"
converted: "2026-05-11T17:33:45.981463"
Lifecycle Applications |  EBOM Part & Assembly Detailing |  Running Light Expand _Running Light Expand_

converted: "2026-05-11T17:33:45.981463"
Lifecycle Applications |  EBOM Part & Assembly Detailing |  Running Light Expand _Running Light Expand_
Use Case

* * *

Abstract This article shows how to run a Light Expand to get data on objects and delete all the memory used to run that expand.

  * **What You Will Learn With This Use Case**
  * **The CAADkoLightExpand Use Case**
    * What Does CAADkoLightExpand Do
    * How to Launch CAADkoLightExpand
    * Where to Find the CAADkoLightExpand Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *

What You Will Learn With This Use Case This use case is intended to show you how to run a Light Expand. An expand is a particular case of query. In the simplest case, a root Product Root Class is expanded to find the structure of Part Instances and Product Instances. Expand consists in finding the instances that are attached under the root PRC, ordering them thanks to their children/parent relationships, and finding the documents attached to those parts. Expand is using Query to find those instances. Expand has the same problems as Query: it is slow, loads in memory all objects found matching the input predicate, using memory that can't be cleaned after the process, and reads all attributes of the objects even if only few of them are useful.
What You Will Learn With This Use Case This use case is intended to show you how to run a Light Expand. An expand is a particular case of query. In the simplest case, a root Product Root Class is expanded to find the structure of Part Instances and Product Instances. Expand consists in finding the instances that are attached under the root PRC, ordering them thanks to their children/parent relationships, and finding the documents attached to those parts. Expand is using Query to find those instances. Expand has the same problems as Query: it is slow, loads in memory all objects found matching the input predicate, using memory that can't be cleaned after the process, and reads all attributes of the objects even if only few of them are useful.
After having implemented Light Query to solve those issues, Light Expand has been implemented to take advantage of the improvements provided by Light Query. In particular, the result structure of Light Expand has to be deleted at the end in order to free the memory used by the Light Expand, memory that can be reused further. [Top] The CAADkoLightExpand Use Case CAADkoLightExpand is a use case of the CAAVPMDesktopObjects.edu framework that illustrates VPMDesktopObjects, VPMInterfaces and VPMPersistency framework capabilities. [Top] What Does CAADkoLightExpand Do CAADkoLightExpand is a stand-alone executable that runs a Light Expand to get the product structure made of parts under a root PRC. The interface ENOVILightExpandable is used to run the Light Expand and get the ordered structure. Each object in the result list is accessed via the interface CATIVpmLightExpandObject.

  1. In this use case, we set up the Light Expand to get the instances attached under the root PRC. This example focuses on the structure of parts under a PRC. It is possible to expand different kinds of objects and get different kinds of object types in the results.
  2. On the results, we print the type, name, out of sync status, lock information of each object.

[Top] How to Launch CAADkoLightExpand To launch CAADkoLightExpand, you will need to set up the build time environment, then compile CAADkoLightExpand along with its prerequisites, set up the run time environment, and then execute the use case [1]. [Top] Where to Find the CAADkoLightExpand Code The CAADkoLightExpand use case is made of a single file located in the CAADkoLightExpand.m module of the CAAVPMDesktopObjects.edu framework: Windows | `InstallRootDirectory\CAAVPMDesktopObjects.edu\CAADkoLightExpand.m\`
---|---
1. In this use case, we set up the Light Expand to get the instances attached under the root PRC. This example focuses on the structure of parts under a PRC. It is possible to expand different kinds of objects and get different kinds of object types in the results.
2. On the results, we print the type, name, out of sync status, lock information of each object.
Unix | `InstallRootDirectory/CAAVPMDesktopObjects.edu/CAADkoLightExpand.m/`
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed. [Top] Step-by-Step There are five logical steps in CAADkoLightExpand:

  1. Get the root object to expand
  2. Define the Light Expand parameter
  3. Run the Light Expand
  4. Use the results to print some information
  5. Delete the Light Expand result structure

[Top] Get the root object to expand The object to expand must be loaded in memory in order to access its ENOVILightExpandable interface. In order to do this, in this use case we have used Light Query to get the identifier of the PRC we want to expand. See the Light Query use case for more information on how to do that. Then we load this PRC in memory by using the following code.
3. Run the Light Expand
4. Use the results to print some information
5. Delete the Light Expand result structure
Be careful when using the following API (ENOVLightQueryToFullObjectsServices::getFactoryObjects) as this call will load all light objects in input in memory. Doing so negates all the improvements brought by Light Query, and loads the objects in memory one by one which is very bad for performances.

          CATListOfInt Indexes;
          CATLISTV(CATBaseUnknown_var) FactoryObjects;
```vbscript
```vbscript
          RC = ENOVLightQueryToFullObjectsServices::getFactoryObjects( Indexes, FactoryObjects, oQueryResult );

```

```

---
```vbscript
CATLISTV(CATBaseUnknown_var) FactoryObjects;
```vbscript
RC = ENOVLightQueryToFullObjectsServices::getFactoryObjects( Indexes, FactoryObjects, oQueryResult );
```

Once we have the object in memory, we can use Query Interface to get the ENOVILightExpandable interface:

          ENOVILightExpandable_var LightPRC( FactoryObjects[1] );

```

---
[Top] Define the Light Expand parameter We want to get Generic Components and Instances (Part and Product) under the root PRC.

          int Type = LEX_GenericComponent;

---
We want to expand the tree completely, without stopping at a predefined level. We expand the tree until there is no children parts to be found.

          int ExpandLevel = LEX_MODE_ALL;

---
Light Expand is defining a list of attributes on the instances to be able to do its job. We don't want any additonal attributes. So we define a list and leave it empty.

          CATListOfCATUnicodeString SelectClause;

---
We want to get all kinds of attached document, if any.

          DocumentCriteria DocCriteria = LEX_Document;

---
[Top] Run the Light Expand This step is easy, it just consists in calling the getLightTree method to execute the expand.

```vbscript
          RC = LightPRC->getLightTree( ExpandLevel, SelectClause, ExpandResult, Type, DocCriteria );

```

---
[Top] Use the results to print some information For each object in the result structure, we get the type of the object, its name, its out of sync status, its lock status, the number of attached documents and we print everything.

          int nb = ExpandResult->Size();
          TRACE << "There are " << nb << " parts and GCo in the result of the expand" << endl;
          for( int i=1; i<=nb; i++ )

          {
int nb = ExpandResult->Size();
TRACE << "There are " << nb << " parts and GCo in the result of the expand" << endl;
for( int i=1; i<=nb; i++ )
             CATIVpmLightExpandObject * LEXObj = (*ExpandResult)[i];
```vbscript
             if ( LEXObj != NULL )

```

             {
                // Get the level
CATIVpmLightExpandObject * LEXObj = (*ExpandResult)[i];
if ( LEXObj != NULL )
                int level = 0;
                LEXObj->getLevel( level );

                // Get the name of the object
int level = 0;
LEXObj->getLevel( level );
                CATUnicodeString Name;
                LEXObj->getName( Name );

                // Get the synchronization status
CATUnicodeString Name;
LEXObj->getName( Name );
                vpmOutOfSync SyncStatus = LEX_Unknown;
                LEXObj->getUpToDate( SyncStatus );

                // Get the type of the object
vpmOutOfSync SyncStatus = LEX_Unknown;
LEXObj->getUpToDate( SyncStatus );
                vpmTypeNames BasicType = LEX_UnknownType;
                LEXObj->getBasicType( BasicType );

                // Get the lock owner on the instance
vpmTypeNames BasicType = LEX_UnknownType;
LEXObj->getBasicType( BasicType );
                CATUnicodeString LockOwner;
                LEXObj->getLockInfo( LockOwner );

                // Get the attached documents
                // the pointer 'Documents' will be deleted when the global expand results will be deleted.
CATUnicodeString LockOwner;
LEXObj->getLockInfo( LockOwner );
                CATListPtrCATIVpmLightExpandObject * Documents = NULL;
                LEXObj->getDocuments( Documents, DocCriteria );
                int nbDocs = 0;
                if ( Documents != NULL )
```vbscript
```vbscript
                   nbDocs = Documents->Size();

```

```

                TRACE << "Object at index : " << i << " is a ";
                if ( BasicType == LEX_PartInstance )
                   TRACE << "Part Instance";
                else if ( BasicType == LEX_ProductInstance )
                   TRACE << "Product Instance";
                else if ( BasicType == LEX_TempoItemInstance )
                   TRACE << "Tempo Instance";
                else if ( BasicType == LEX_GCoGenericComponent )
                   TRACE << "Generic Component";
                TRACE << " at level " << level << ", named : " << Name << ",";
                if (( BasicType == LEX_PartInstance ) || ( BasicType == LEX_ProductInstance ) || ( BasicType == LEX_TempoItemInstance ))

                {
else if ( BasicType == LEX_GCoGenericComponent )
TRACE << "Generic Component";
TRACE << " at level " << level << ", named : " << Name << ",";
if (( BasicType == LEX_PartInstance ) || ( BasicType == LEX_ProductInstance ) || ( BasicType == LEX_TempoItemInstance ))
```vbscript
                   if ( LockOwner.GetLengthInChar() > 0 )
```

                      TRACE << " locked by " << LockOwner << ",";
                   if ( SyncStatus == LEX_UpToDate )
                      TRACE << " up to date,";
                   else if ( SyncStatus == LEX_Version )
                      TRACE << " out of sync by version,";
                   else if ( SyncStatus == LEX_Reference )
                      TRACE << " out of sync by reference,";
                   else if ( SyncStatus == LEX_Quantity )
                      TRACE << " out of sync by quantity,";
                   else if ( SyncStatus == LEX_Position )
                      TRACE << " out of sync by position,";

                }
else if ( SyncStatus == LEX_Quantity )
TRACE << " out of sync by quantity,";
else if ( SyncStatus == LEX_Position )
TRACE << " out of sync by position,";
                TRACE << " with " << nbDocs << " documents." << endl;

             }
          }

---
[Top] Delete the Light Expand result structure It is very important at the end to delete the structure used by the Light Expand to retrieve the data. No object has been loaded in memory during the Light Expand, but all the attribute values and object identifiers are stored in that structure. Deleting the structure will ensure that the server memory at the end of the Light Expand is the same as the memory at the start of the Light Expand.
A macro is available to delete the list of objects and all objects in that list.

          CATLIST_APPLY_DELETE_LIGHTEXPAND( ExpandResult );

---
[Top]

* * *

In Short Running Light Expand on the server consists in getting the root object to expand, defining the parameters of the Light Expand, running the Light Expand, reading the results of the Light Expand and deleting the result structure to clean all the memory used by the Light Expand. [Top]

* * *

References [1] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[Top]

* * *

History Version: **1** [Sep 2013] | Document created
---|---
[Top]

* * *

_Copyright 2013, Dassault Systmes. All rights reserved._
