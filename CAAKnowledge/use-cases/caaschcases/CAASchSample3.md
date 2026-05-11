---
title: "Creating Features in an Applicative Container"
category: "use case"
module: "CAASchUseCases"
tags: ["CAASchEduIn", "CAASchAppSample2", "CATISchAppObjectFactory", "CAASchAppSample3Main", "CAASchAppSample3", "CAASchSample1", "CATISchSession", "CAASCHEDU_SamplePID", "CAASchApp", "CATISchRoute", "CAASchEduOut3", "CATISchBaseFactory", "CAASchPlatformModeler", "CAASchAppUtilities", "CATInit", "CAAESchAppObjectFactory", "CAASchAppBase", "CAASchAppBaseEnv", "CAASchAppDeleteBaseUnknown"]
source_file: "Doc\online\CAASchUseCases\CAASchSample3.htm"
converted: "2026-05-11T17:31:51.529141"
---

# Equipment & Systems

| 

## Schematics Platform Modeler

| 

### Creating Schematic Application Components

_Working with Schematic Components_  
---|---|---  
Use Case  
  
* * *

### Abstract

This article discusses the CAASchAppSample3 use case.

  * **What You Will Learn With This Use Case**
  * **The CAASchAppSample3 Use Case**
    * What Does CAASchAppSample3 Do
    * How to Launch CAASchAppSample3
    * Where to Find the CAASchAppSample3 Code
  * **Step-by-Step**
  * **In Short**
  * **References**

  
---  
  
* * *

### What You Will Learn With This Use Case

This use case is intended to help you understand how to use the CAA Schematic Platform Interfaces to create string class objects, or routes.

[Top]

### The CAASchAppSample2 Use Case

CAASchAppSample3 is a use case of the CAASchPlatformModeler.edu framework that illustrates CAASchPlatformModeler framework capabilities. The use case demonstrates the creation of a route for a sample Schematics application, _CAASCHEDU_SamplePID_.

[Top]

#### What Does CAASchAppSample3 Do

The sample demonstrates how to create a route two different ways; by points, and from primitives.

[Top]

#### How to Launch CAASchAppSample3

To launch CAASchAppSample3, you will need to set up the build time environment, then compile CAASchAppSample3 along with its prerequisites, set up the run time environment, and then execute the sample. This is fully described in the referenced article [1]. When launching the use case, you must pass the following arguments:

  * **CAASchEduIn.CATProduct** \- the entire pathname, name and extension (.CATProduct) of the input drawing. Normally, it should be stored in the CNext/resources/graphic directory.
  * **CAASchEduOut3.CATProduct** \- the entire pathname, name and extension (.CATProduct) under which the new document is to be stored



[Top]

#### Where to Find the CAASchAppSample3 Code

CAASchAppSample3 code is located in the CAASchAppSample3.m use case module of the CAASchPlatformModeler.edu framework:

Windows | `InstallRootDirectory\CAASchPlatformModeler.edu\CAASchAppSample3.m`  
---|---  
Unix | `InstallRootDirectory/CAASchPlatformModeler.edu/CAASchAppSample3.m`  
  
where `InstallRootDirectory` is the root directory of your CAA V5 installation. It is made of a two unique source files named CAASchAppSample3Main.cpp and CAASchAppSample3.cpp.

Additional prerequisite code is located in the CAASchAppUtilities.m and CAASchAppBase.m modules of the same framework.

[Top]

### Step-by-Step

These are the logical steps in CAASchAppSample2:

  1. Prolog
  2. Initializing the Environment
  3. Creating the Application Route Object
  4. Creating a Route from Points
  5. Creating a Route from Primitives



[Top]

#### Prolog

In this use case, we open an input drawing containing one main sheet and one detail sheet. The main sheet contains one component instantiated from a reference object. The detail sheet contains three views. The use case will create a new .CATProduct drawing for the sample application.

[Top]

#### Initializing the Environment

The CAASchAppSample2 code is derived from the CAASchAppBaseEnv base class. The base class contains functionality common to the other CAASchApp samples. Initializing the environment involves the following methods:
    
    
    CAASchAppSample2::InitEnvironment
    CreateCATProductEnv::CreateCATProductEnv  
  
---  
  
These methods perform the following functions:

  * Creating a session, namely "Session DSA CAASchAppBaseEnv CATProduct".
  * Obtaining the _CATISchSession_ interface from the session.
  * Obtaining the _CATISchBaseFactory_ interface from the session
  * Obtaining the applications _CATISchAppObjectFactory_ interface pointer.
  * Loading the input document.
  * Initializing the document using the _CATInit_ interface.
  * Obtaining the pointer to the component reference.



[Top]

#### Creating the Application Route Object

According to the rules for the Schematics Modeler, if you want to create a route, you must first use your application object factory to create the route (feature) object. The sample uses the _CATISchAppObjectFactory_ interface method `AppCreateRoute` to create the route object instance. The application route reference is already residing in the input model, and `AppCreateRoute` retrieves it and creates the application route instance from it.
    
    
        CATISchSession* piSchSession = NULL;
        if ( SUCCEEDED( pSession->QueryInterface (IID_CATISchSession,(void**)&piSchSession)))
        {
          piSchSession->GetSchObjInterface(SCHEDUApplication_Name,
            IID_CATISchAppObjectFactory, (void**)&_piSchAppObjFact);
    
          piSchSession->Release(); piSchSession = NULL;
        } 
        else
        {
          cout << "Cannot get schematic session" << endl;
          return E_FAIL;
        }
    
        //-------------------------------------------------------------------------
        //  Create two application route instances
        //-------------------------------------------------------------------------
        if (NULL != _piSchAppObjFact)
        {
          if (SUCCEEDED(_piSchAppObjFact->AppCreateRoute (SCHEDUClass_String,
               &_piUKAppRoute1)))
          {
            cout << "CAASchAppSample3::DoSample: First application route found" << endl;
          }
          else
          {
            cout << "Route: "
                 << "Fail to find application object"
                 << endl;
            return E_FAIL;
          } 
    
    
          if (SUCCEEDED(_piSchAppObjFact->AppCreateRoute (SCHEDUClass_String,
               &_piUKAppRoute2)))
          {
            cout << "CAASchAppSample3::DoSample: Second application route found" << endl;
          }
          else
          {
            cout << "Route: "
                 << "Fail to find application object"
                 << endl;
            return E_FAIL;
          } 
        }
        else
        {
          cout << "Cannot get Schematic Application Object Factory" << endl;
          return E_FAIL;
        }   
  
---  
  
The method `AppCreateRoute` is implemented in the file **CAAESchAppObjectFactory.cpp**. See the the section [Creating an Application Reference Object](CAASchSample1.htm#AppReferenceObject) in CAASchSample1 for more information.

[Top]

#### Creating a Route from Points

After the route feature object is created, the Schematics base factory interface _CATISchBaseFactory_ method `CreateSchRouteByPoints` is used to create the Route.
    
    
        CATISchRoute   *_piSchRoute1;
        if ( _piUKAppRoute1 )
        {
          double LDbPts[4] = {50.0, 50.0, 500.0, 50.0};
          int iSize = 4;
          RC = _piBaseFact->CreateSchRouteByPoints (_piUKAppRoute1, 
                            LDbPts, iSize, &_piSchRoute1);
          if (SUCCEEDED(RC) && _piSchRoute1)
          {
            RC = _piSchRoute1->QueryInterface (IID_CATISpecObject, 
                 (void **) &_piSpecSchRoute1);
            if (SUCCEEDED(RC) && _piSpecSchRoute1)
            {
              _piSpecSchRoute1->SetName ("App_RouteInstance");
              cout << "App_RouteInstance created" <<endl;
            }
          }
        }  
  
---  
  
[Top]

#### Creating a Route from Primitives

Another way to create a route is using primitives. This technique involves first creating a Graphical representation for the route, and then using the Schematics base factory interface _CATISchBaseFactory_ method `CreateSchRouteByPrim.`
    
    
    //-------------------------------------------------------------------------
        //  Create 2 graphical representations (GRRRoute)
        //-------------------------------------------------------------------------
        if ( _piUKAppRoute2 )
        {
           double iLDbLinePath[4];
           int iSizeOfPath = 4;
           iLDbLinePath[0] = 400.0;
           iLDbLinePath[1] = 120.0;
           iLDbLinePath[2] = 400.0;
           iLDbLinePath[3] = 700.0;
           RC = _piGRRFact->CreateGRRRoute (iLDbLinePath, iSizeOfPath, &_piSchGRRRoute1);
           if (!SUCCEEDED(RC) || !_piSchGRRRoute1)
           {
              cout << "CreateRouteTest: "
                   << "Cannot create route graphical representation"
                   << endl;
              return 0;
           } 
           iLDbLinePath[0] = 400.0;
           iLDbLinePath[1] = 400.0;
           iLDbLinePath[2] = 900.0;
           iLDbLinePath[3] = 400.0;
           RC = _piGRRFact->CreateGRRRoute (iLDbLinePath, iSizeOfPath, &_piSchGRRRoute2);
           if (!SUCCEEDED(RC) || !_piSchGRRRoute2)
           {
              cout << "CreateRouteTest: "
                   << "Cannot create route graphical representation"
                   << endl;
              return 0;
           }
           cout << "CreateRouteTest: GRRRoutes created" << endl;
        }
    
        CATSchListServices SchList;
        if (SUCCEEDED(SchList.CreateCATIUnknownList (&_piLUK)))
        {
           if (_piLUK)
           {
              if (SUCCEEDED (_piSchGRRRoute1->QueryInterface (IID_IUnknown, 
                  (void **) &_piUK)) )
              {
                 _piLUK->Add(0,_piUK);
                 CAASchAppDeleteBaseUnknown (_piUK);
              }
              if (SUCCEEDED (_piSchGRRRoute2->QueryInterface (IID_IUnknown, 
                  (void **) &_piUK)) )
              {
                 _piLUK->Add(1,_piUK);
                 CAASchAppDeleteBaseUnknown (_piUK);
              }
           } 
        }
    
        //-------------------------------------------------------------------------
        //  Create schematic route by primitives
        //-------------------------------------------------------------------------
        RC = _piBaseFact->CreateSchRouteByPrim (_piUKAppRoute2, _piLUK, &_piSchRoute2);               
        if (SUCCEEDED(RC) && _piSchRoute2)
        {
          RC = _piSchRoute2->QueryInterface (IID_CATISpecObject, 
               (void **) &_piSpecSchRoute2);
          if (SUCCEEDED(RC) && _piSpecSchRoute2)
          {
            _piSpecSchRoute2->SetName ("App_RouteInstance2");
            cout << "App_RouteInstance2 created" <<endl;
          }
        }
      
  
---  
  
[Top]

* * *

### In Short

This use case has demonstrated how to create a string class object, route, using two different methods. Specifically, it has illustrated:

  * Obtaining the necessary Sch Interfaces
  * Creating the application route feature using the Application Object Factory
  * Creating a Schematics route object from a point definition
  * Creating a Schematics route object from a two graphical representation primitives



[Top]

* * *

### References

[1] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.htm)  
---|---  
  
* * *

### History

Version: **1** [April 2001] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
