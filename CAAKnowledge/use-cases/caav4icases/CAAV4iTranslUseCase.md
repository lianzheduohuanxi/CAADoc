---
title: "Creating a V5 Geometrical Element from V4 Data"
category: "use case"
module: "CAAV4iUseCases"
tags: ["CAACATIAV4Interfaces", "CAAV4iEduTranslV4ToV5", "CAADataTranslator", "CATIV4DataTranslator", "CATIAV4Interfaces", "CATIA"]
source_file: "Doc/online/CAAV4iUseCases/CAAV4iTranslUseCase.htm"
converted: "2026-05-11T17:33:45.807427"
---
# 3D PLM PPR Hub Open Gateway

| 
## V4 Access

| 
### Creating a V5 Geometrical Element from V4 Data

Adapt the behavior of V4 data migration  
---|---|---  
Use Case  
  
* * *
### Abstract

This article shows how to migrate V5 geometrical element from a V4 data . 

  * **What You Will Learn With This Use Case**
  * **The CAAV4iEduTranslV4ToV5 Use Case**  
    * What Does CAAV4iEduTranslV4ToV5
    * How to Launch CAAV4iEduTranslV4ToV5
    * Where to Find the CAAV4iEduTranslV4ToV5 Code
  * **Step-by-Step**
  * **In Short**
  * **References**

  
---  
  
* * *
### What You Will Learn With This Use Case

This use case is intended to show you how to migrate V5 geometrical element from a V4 data. 

[Top] 
### The CAAV4iEduTranslV4ToV5 Use Case

CAAV4iEduTranslV4ToV5 is a use case of the CAACATIAV4Interfaces.edu framework that illustrates CATIAV4Interfaces framework capabilities. 

[Top] 
#### What Does CAAV4iEduTranslV4ToV5 Do

CAAV4iEduTranslV4ToV5 is a frame, which implements the CATIV4DataTranslator interface. This interface is used by CATIA V5, when elements from a V4 model are pasted into a CATPart. Currently the implementation is restricted to spline curves and nets. 

[Top] 
#### How to Launch CAAV4iEduTranslV4ToV5

__  First of all, complete the object methods in order to migrate V5 geometrical element from a V4 data. Read your V4 data and set the matching V5 data in accordance with the V4 CATGEO type as SPLINE or NET. Tell the process that you want to compute yourself the V5 data. If you want to let the system do, the generic process will be applied and curve or a surface will be computed. If you wish no computation, the V4 element will not be migrated.  
__  Then set up the build time environment, compile CAAV4iEduTranslV4ToV5 with its prerequisites, set up the run time environment to take into account the use case dictionary, and execute the use case [1].  
__ 

[Top] 
#### Where to Find the CAAV4iEduTranslV4ToV5 Code

The CAAV4iEduTranslV4ToV5 use case is made of one file located in the CAAV4iEduTranslV4ToV5.m module of the CAACATIAV4Interfaces.edu framework:  
  Windows | `InstallRootDirectory\`CAACATIAV4Interfaces`.edu\`CAAV4iEduTranslV4ToV5`.m\`  
---|---  
Unix | `InstallRootDirectory/`CAACATIAV4Interfaces`.edu/`CAAV4iEduTranslV4ToV5`.m/`  
  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.  
 

[Top] 
### Step-by-Step

There is possible to manage your intent in CAAV4iEduTranslV4ToV5 : 

  1. Change the V4 to V5 Paste behaviour

[Top] 
#### Change the V4 to V5 Paste behaviour
    
    
      HRESULT CAADataTranslator::GetUserIntent(CATV4iV4Element * V4Elem, int & oIntent)
      {
        HRESULT rc = S_OK;
        ...
        oIntent = ...;
        return rc;
      }
      
  
---  
  
oIntent is set to 

  * 0 : do the generic process, do not use the customer method. 
  * 1 : let the customer do as here before. 

[Top] 

* * *
### In Short

This use case provides a way to decide if an element will be pasted or not. 

_[_Top] 

* * *
### References

[1] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[Top]  
  
* * *
### History

Version: **1** [Dec 2003] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 1994-2003, Dassault Systmes. All rights reserved._
