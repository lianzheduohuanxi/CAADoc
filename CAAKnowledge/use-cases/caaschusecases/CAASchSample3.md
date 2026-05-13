---
title: "Untitled"
category: "use-case"
module: "CAASchUseCases"
tags: ["CATInit", "CAADocStyleSheets", "CAASchPlatformModeler", "CAASchAppSample3", "CAASchAppBaseEnv", "CAASchApp", "CATISchRoute", "CAASCHEDU_SamplePID", "CAADocUseCases", "CAASchAppUtilities", "CAASchSample1", "CATISchAppObjectFactory", "CAASchAppSample2", "CAASchAppBase", "CAASchEduIn", "CATISchSession", "CATISchBaseFactory", "CAASchAppSample3Main", "CAAESchAppObjectFactory", "CAADocRunSample"]
source_file: "Doc/online/CAASchUseCases/CAASchSample3.htmmd"
converted: "2026-05-11T11:27:02.665786"
---

---

---

### What You Will Learn With This Use Case

This use case is intended to help you understand how to use the CAA Schematic
Platform Interfaces to create string class objects, or routes.

[Top]

### The CAASchAppSample2 Use Case

CAASchAppSample3 is a use case of the CAASchPlatformModeler.edu framework
that illustrates CAASchPlatformModeler framework capabilities. The use case
demonstrates the creation of a route for a sample Schematics application, CAASCHEDU_SamplePID.

[Top]

#### What Does CAASchAppSample3 Do

The sample demonstrates how to create a route two different ways; by points,
and from primitives.

[Top]

#### How to Launch CAASchAppSample3

To launch CAASchAppSample3, you will need to set up the build time
environment, then compile CAASchAppSample3 along with its prerequisites, set up
the run time environment, and then execute the sample. This is fully described
in the referenced article [1]. When launching the use
case, you must pass the following arguments:

  
- **CAASchEduIn.CATProduct** - the entire pathname, name and extension
    (.CATProduct) of the input drawing. Normally, it should be stored in the
    CNext/resources/graphic directory.
  
- **CAASchEduOut3.CATProduct** - the entire pathname, name and extension
    (.CATProduct) under which the new document is to be stored

[Top]

#### Where to Find the CAASchAppSample3 Code

CAASchAppSample3 code is located in the CAASchAppSample3.m use case module of
the CAASchPlatformModeler.edu framework:

where `InstallRootDirectory` is the root directory of your CAA V5
installation. It is made of a two unique source files named
CAASchAppSample3Main.cpp and CAASchAppSample3.cpp.

Additional prerequisite code is located in the CAASchAppUtilities.m and
CAASchAppBase.m modules of the same framework.

[Top]

### Step-by-Step

These are the logical steps in CAASchAppSample2:

  
- Prolog
  
- Initializing the Environment
  
- Creating the Application Route Object
  
- Creating a Route from Points
  
- Creating a Route from Primitives

[Top]

#### Prolog

In this use case, we open an input drawing containing one main sheet and one
detail sheet. The main sheet contains one component instantiated from a
reference object. The detail sheet contains three views. The use case will
create a new .CATProduct drawing for the sample application.

[Top]

#### Initializing the Environment

The CAASchAppSample2 code is derived from the CAASchAppBaseEnv base class.
The base class contains functionality common to the other CAASchApp samples.
Initializing the environment involves the following methods:

These methods perform the following functions:

  
- Creating a session, namely "Session DSA CAASchAppBaseEnv
    CATProduct".
  
- Obtaining the *CATISchSession* interface from the session.
  
- Obtaining the *CATISchBaseFactory* interface from the session
  
- Obtaining the applications *CATISchAppObjectFactory* interface
    pointer.
  
- Loading the input document.
  
- Initializing the document using the *CATInit* interface.
  
- Obtaining the pointer to the component reference.

[Top]

#### Creating the Application Route Object

According to the rules for the Schematics Modeler, if you want to create a
route, you must first use your application object factory to create the route
(feature) object. The sample uses the *CATISchAppObjectFactory* interface
method `AppCreateRoute` to create the route object instance. The
application route reference is already residing in the input model, and `AppCreateRoute`
retrieves it and creates the application route instance from it.

The method `AppCreateRoute` is implemented in the file **CAAESchAppObjectFactory.cpp**.
See the the section [Creating an
Application Reference Object](CAASchSample1.md) in CAASchSample1 for more information.

[Top]

#### Creating a Route from Points

After the route feature object is created, the Schematics base factory
interface *CATISchBaseFactory* method `CreateSchRouteByPoints`
is used to create the Route.

[Top]

#### Creating a Route from Primitives

Another way to create a route is using primitives. This technique involves
first creating a Graphical representation for the route, and then using the
Schematics base factory interface *CATISchBaseFactory* method `CreateSchRouteByPrim.`

[Top]

---

### In Short

This use case has demonstrated how to create a string class object, route,
using two different methods. Specifically, it has illustrated:

  
- Obtaining the necessary Sch Interfaces
  
- Creating the application route feature using the Application Object
    Factory
  
- Creating a Schematics route object from a point definition
  
- Creating a Schematics route object from a two graphical representation
    primitives

[Top]

---

### References

---

### History

---

*Copyright  2000, Dassault Systmes. All rights reserved.*

```cpp
CAASchAppSample2::InitEnvironment
CreateCATProductEnv::CreateCATProductEnv
```

```cpp
CATISchSession* piSchSession = NULL;
    if ( SUCCEEDED( pSession-&gt;QueryInterface (IID_CATISchSession,(void**)&amp;piSchSession)))
    {
      piSchSession-&gt;GetSchObjInterface(SCHEDUApplication_Name,
        IID_CATISchAppObjectFactory, (void**)&amp;_piSchAppObjFact);

      piSchSession-&gt;Release(#); piSchSession = NULL;
    } 
    else
    {
      cout &lt;&lt; &quot;Cannot get schematic session&quot; &lt;&lt; endl;
      return E_FAIL;
    }

    //-------------------------------------------------------------------------
    //  Create two application route instances
    //-------------------------------------------------------------------------
    if (NULL != _piSchAppObjFact)
    {
      if (SUCCEEDED(_piSchAppObjFact-&gt;AppCreateRoute (SCHEDUClass_String,
           &amp;_piUKAppRoute1)))
      {
        cout &lt;&lt; &quot;CAASchAppSample3::DoSample: First application route found&quot; &lt;&lt; endl;
      }
      else
      {
        cout &lt;&lt; &quot;Route: &quot;
             &lt;&lt; &quot;Fail to find application object&quot;
             &lt;&lt; endl;
        return E_FAIL;
      }
```

```cpp
if (SUCCEEDED(_piSchAppObjFact-&gt;AppCreateRoute (SCHEDUClass_String,
           &amp;_piUKAppRoute2)))
      {
        cout &lt;&lt; &quot;CAASchAppSample3::DoSample: Second application route found&quot; &lt;&lt; endl;
      }
      else
      {
        cout &lt;&lt; &quot;Route: &quot;
             &lt;&lt; &quot;Fail to find application object&quot;
             &lt;&lt; endl;
        return E_FAIL;
      } 
    }
    else
    {
      cout &lt;&lt; &quot;Cannot get Schematic Application Object Factory&quot; &lt;&lt; endl;
      return E_FAIL;
    }
```

```cpp
CATISchRoute   *_piSchRoute1;
    if ( _piUKAppRoute1 )
    {
      double LDbPts[4] = {50.0, 50.0, 500.0, 50.0};
      int iSize = 4;
      RC = _piBaseFact-&gt;CreateSchRouteByPoints (_piUKAppRoute1, 
                        LDbPts, iSize, &amp;_piSchRoute1);
      if (SUCCEEDED(RC) &amp;&amp; _piSchRoute1)
      {
        RC = _piSchRoute1-&gt;QueryInterface (IID_CATISpecObject, 
             (void **) &amp;_piSpecSchRoute1);
        if (SUCCEEDED(RC) &amp;&amp; _piSpecSchRoute1)
        {
          _piSpecSchRoute1-&gt;SetName (&quot;App_RouteInstance&quot;);
          cout &lt;&lt; &quot;App_RouteInstance created&quot; &lt;&lt;endl;
        }
      }
    }
```

```vbscript
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
       RC = _piGRRFact-&gt;CreateGRRRoute (iLDbLinePath, iSizeOfPath, &amp;_piSchGRRRoute1);
       if (!SUCCEEDED(RC) || !_piSchGRRRoute1)
       {
          cout &lt;&lt; &quot;CreateRouteTest: &quot;
               &lt;&lt; &quot;Cannot create route graphical representation&quot;
               &lt;&lt; endl;
          return 0;
       } 
       iLDbLinePath[0] = 400.0;
       iLDbLinePath[1] = 400.0;
       iLDbLinePath[2] = 900.0;
       iLDbLinePath[3] = 400.0;
       RC = _piGRRFact-&gt;CreateGRRRoute (iLDbLinePath, iSizeOfPath, &amp;_piSchGRRRoute2);
       if (!SUCCEEDED(RC) || !_piSchGRRRoute2)
       {
          cout &lt;&lt; &quot;CreateRouteTest: &quot;
               &lt;&lt; &quot;Cannot create route graphical representation&quot;
               &lt;&lt; endl;
          return 0;
       }
       cout &lt;&lt; &quot;CreateRouteTest: GRRRoutes created&quot; &lt;&lt; endl;
    }

    CATSchListServices SchList;
    if (SUCCEEDED(SchList.CreateCATIUnknownList (&amp;_piLUK)))
    {
       if (_piLUK)
       {
          if (SUCCEEDED (_piSchGRRRoute1-&gt;QueryInterface (IID_IUnknown, 
              (void **) &amp;_piUK)) )
          {
             _piLUK-&gt;Add(0,_piUK);
             CAASchAppDeleteBaseUnknown (_piUK);
          }
          if (SUCCEEDED (_piSchGRRRoute2-&gt;QueryInterface (IID_IUnknown, 
              (void **) &amp;_piUK)) )
          {
             _piLUK-&gt;Add(1,_piUK);
             CAASchAppDeleteBaseUnknown (_piUK);
          }
       } 
    }

    //-------------------------------------------------------------------------
    //  Create schematic route by primitives
    //-------------------------------------------------------------------------
    RC = _piBaseFact-&gt;CreateSchRouteByPrim (_piUKAppRoute2, _piLUK, &amp;_piSchRoute2);               
    if (SUCCEEDED(RC) &amp;&amp; _piSchRoute2)
    {
      RC = _piSchRoute2-&gt;QueryInterface (IID_CATISpecObject, 
           (void **) &amp;_piSpecSchRoute2);
      if (SUCCEEDED(RC) &amp;&amp; _piSpecSchRoute2)
      {
        _piSpecSchRoute2-&gt;SetName (&quot;App_RouteInstance2&quot;);
        cout &lt;&lt; &quot;App_RouteInstance2 created&quot; &lt;&lt;endl;
      }
    }
```