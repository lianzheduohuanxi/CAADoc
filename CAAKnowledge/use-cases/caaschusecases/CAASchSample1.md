---
title: "Untitled"
category: "use-case"
module: "CAASchUseCases"
tags: ["CATInit", "CAADocStyleSheets", "CAASchPlatformModeler", "CAASchCATFct", "CAASchAppBaseEnv", "CAASchApp", "CAASchEduOut1", "CAASCHEDU_SamplePID", "CAASCHEDUApp", "CATISchAppConnectable", "CAASchAppSample1Main", "CAADocUseCases", "CATISchCompConnector", "CATISpecObject_var", "CAASchAppUtilities", "CATIContainer_var", "CATISpecObject", "CATISchComponent", "CATISchCompFlow", "CATISchAppObjectFactory"]
source_file: "Doc/online/CAASchUseCases/CAASchSample1.htmmd"
converted: "2026-05-11T11:27:02.669894"
---

---

---

### What You Will Learn With This Use Case

This use case is intended to help you understand how to use the CAA Schematic
Platform Interfaces to create Schematic components.

[Top]

### The CAASchAppSample1 Use Case

CAASchAppSample1 is a use case of the CAASchPlatformModeler.edu framework
that illustrates CAASchPlatformModeler framework capabilities. The use case
demonstrates the creation of a component for a sample Schematics application,
CAASCHEDU_SamplePID.

[Top]

#### What Does CAASchAppSample1 Do

The sample will create a component (feature reference) with two connectors
and an internal flow. An Instance of the component is then created on the main
sheet of the output drawing.

The sample uses a Schematic Extension Container to obtain the Schematics Base
Factory and Application factory interfaces. It then makes a component reference
object, adds connectors and internal flow to it, and instantiates (places) it on
the main sheet of the drawing. The sample uses the Catalog, CAASCHEDUApp.CATfct.
Here is an image of the contents of this catalog:

[Top]

#### How to Launch CAASchAppSample1

To launch CAASchAppSample1, you will need to set up the build time
environment, then compile CAASchAppSample1 along with its prerequisites, set up
the run time environment, and then execute the sample. This is fully described
in the referenced article [1]. When launching the use
case, you must pass the following arguments:

  
- **CAASchEduIn.CATProduct** - the entire pathname, name and extension
    (.CATProduct) of the input drawing. Normally, it should be stored in the
    CNext/resources/graphic file directory.
  
- **CAASchEduOut1.CATProduct** - the entire pathname, name and extension
    (.CATProduct) under which the new document is to be stored.

[Top]

#### Where to Find the CAASchAppSample1 Code

CAASchAppSample1 code is located in the CAASchAppSample1.m use case module of
the CAASchPlatformModeler.edu framework:

where `InstallRootDirectory` is the root directory of your CAA V5
installation. It is made of a two unique source files named
CAASchAppSample1Main.cpp and CAASchAppSample1.cpp.

Additional prerequisite code is located in the CAASchAppUtilities.m and
CAASchAppBase.m modules of the same framework.

[Top]

### Step-by-Step

There are eight logical steps in CAASchAppSample1:

  
- Prolog
  
- Initializing the Environment
  
- Creating an Application Reference Object
  
- Determining the Graphical Representation for the
    Reference Object
  
- Creating a Component Reference Object
  
- Adding Connectors to Component Reference
    Object
  
- Adding an Internal Flow to the Component
    Reference Object
  
- Placing an Instance of the Component on the Main Sheet

[Top]

#### Prolog

In this use case, we open an input drawing containing one main sheet and one
detail sheet. The detail sheet contains three views. The use case will create a
new .CATProduct drawing for the sample application.

[Top]

#### Initializing the Environment

The CAASchAppSample1 code is derived from the CAASchAppBaseEnv base class.
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
  
- Initializing the document using the *CATInit* interface Init.
  
- Retrieving the pointer to the root container object.
  
- Obtaining the pointer to the detail sheet, etc.

[Top]

#### Creating an Application Reference Object

According to the rules of the Schematics Platform, a reference component is
required before a component can be created and placed. The reference component
is created by the * CATISchBaseFactory* interface method CreateSchComponent. This
method builds the component reference object from the application reference and
a list of graphical representations. It is the responsibility of the Schematics
application, in this case CAASCHEDU_SamplePID, to retrieve the application
reference object.

As one of the requirements of a schematics application, the application must
implement the *CATISchAppObjectFactory* interface. This is the interface
used by the application to create the application reference using the method AppCreateCompRef.
In this use case, the application reference is already residing in the input
document and AppCreateCompRef is used
to retrieve it.

Notice the *CATISchAppObjectFactory* interface pointer is obtained from
the *CATISchSession* interface which is tied to the session.

CAASCHEDU_SamplePID implements the *CATISchAppObjectFactory* in
the files **CAAESchAppObjectFactory.cpp**  using methods in **CAASchAppBaseServices.cpp**. The
important piece of code to know is listed below:

[Top]

#### Determining the Graphical Representation for
the Reference Object

If a component is to be visualized, it needs Graphical Representation (GRR).
A component may have more than one GRR, but can only display one GRR for a given
instance. For this sample, the Component Reference Object to be created will
have only one GRR. The GRR is the geometry shown in the first view on the detail
sheet.

[Top]

#### Creating a Component Reference Object

According to the rules of the Schematics Platform, a component reference
object is required before a component can be created and placed. The reference
component is created by the * CATISchBaseFactory* interface method CreateSchComponent. This method builds the component reference object from the
application reference and a list of graphical representations.

[Top]

#### Adding Connectors to Component Reference
Object

A component such as a valve can have connectors. Some components may have
multiple connectors. This sample adds two connectors to the Component Reference
Object. In order to do this, the code must use the *CATISchCompConnector*
interface method AddConnector. Once the connector is created, it must be
aligned, ( i.e. horizontally, vertically, etc.) See the code for more detail.

[Top]

#### Adding an Internal Flow to the Component
Reference Object

A component may have an internal flow. An internal flow represents a flow
between pairs of connectors of a component. The sample creates an internal flow
between the two connectors added to the component. To do this, the *CATISchCompFlow*
interface must be obtained from the component reference object.

The sample uses the  AddInternalFlow method of the
*CATISchCompFlow* * *interface,
which takes two arguments. The first argument represents a list of connector
pairs, in this case only one connector pair. The second argument is a
pointer to the internal flow created.

[Top]

#### Placing an Instance of the Component on the Main Sheet

The component reference can now be instantiated on the main sheet of the
drawing. This is done with the *CATISchComponent* interface. The PlaceInSpace *
*method is used to do this.

Note the aDb6Axis array contains the vector (1.0,0.0) representing the X
axis, the vector (0.0,1.0) representing the Y axis, and the location (50.0,100).
This vectors determines the orientation and location of the component on the
sheet.

[Top]

---

### In Short

This use case has demonstrated how to create a component reference object and
instantiate it on the main sheet of the drawing for a sample Schematics
application. Specifically, it has illustrated:

  
- Obtaining the necessary Sch Interfaces
  
- Using the Application Object Factory to create an Application Reference
    Object
  
- Associating a Graphical Representation to a component reference
  
- Using the Schematics Base Object Factory to create a component reference
  
- Adding connectors and internal flow to a component reference
  
- Placing a component

[Top]

---

### References

---

### History

---

*Copyright  2000, Dassault Systmes. All rights reserved.*

```vbscript
CAASchAppSample1::InitEnvironment
CAASchAppSample1::GetDraftingObjects
CreateCATProductEnv::CreateCATProductEnv
```

```vbscript
CATISchSession* piSchSession = NULL;
if ( SUCCEEDED( pSession-&gt;QueryInterface (IID_CATISchSession,(void**)&amp;piSchSession) ) )
{
  HRESULT rc = piSchSession-&gt;GetSchObjInterface(SCHEDUApplication_Name,
                                                IID_CATISchAppObjectFactory,
                                                (void**)&amp;_piSchAppObjFact);
  piSchSession-&gt;Release(#); piSchSession = NULL;
}
```

```vbscript
//---------------------------------------------------------------------------
//  Find an application object in a container by a specific class type
//---------------------------------------------------------------------------
CATISpecObject_var CAASchAppBaseServices::FindAppObjByClass (
   const CATUnicodeString &amp;iUClass, const CATIContainer_var &amp;iCont)
{
   HRESULT RC = S_OK;
   CATISpecObject_var spObjFound = NULL_var;
   CATUnicodeString ClassType;
   int MatchPos;
   CATISchAppConnectable *piSchAppCntbl = NULL;
   CATIExtendable_var spApplExtble = NULL_var;

   SEQUENCE (CATBaseUnknown_ptr) L0Obj = iCont-&gt;
      ListMembers(CATISpecObject::ClassName(#));
      
   int SizeOfL0Obj = L0Obj.length(#);
   CATISpecObject *piSpec;
   for (int iObj=0; iObj&lt;SizeOfL0Obj; iObj++)
   {
     piSpec = (CATISpecObject *) L0Obj[iObj];
     if (NULL != piSpec)   
     { 
        if (!spObjFound)
        {
          ClassType = piSpec-&gt;GetType(#);
          printf (&quot;Class Type -- %s/n&quot;, ClassType.ConvertToChar(#));
          MatchPos = ClassType.SearchSubString(iUClass);
          if (MatchPos &gt;= 0)
          { 
            printf (&quot;Match found /n&quot;);
            spObjFound = piSpec;
          }
        }
        piSpec-&gt;Release(#);
        piSpec = NULL;
     }
   }
   return spObjFound;
}
```

```vbscript
CATSchListServices SchList;
    rc = SchList.CreateCATIUnknownList(&amp;_piLUK);

    if ( SUCCEEDED(rc) )
    {
       if (_piLUK)
       {
          if (SUCCEEDED (_spDetailSpec-&gt;QueryInterface (IID_IUnknown,(void **) &amp;_piUK)) )
          {
             _piLUK-&gt;Add(0,_piUK);  // This list will only have 1 graphical representation
          }
       } 
    }
```

```vbscript
//-------------------------------------------------------------------------
    //  Create schematic object
    //-------------------------------------------------------------------------
    rc = _piBaseFact-&gt;CreateSchComponent (_piUKAppRef, _piLUK, &amp;_piSchComp);               
    if (SUCCEEDED(rc) ) 
    {
      if ( _piSchComp)
      {
        rc = _piSchComp-&gt;QueryInterface (IID_CATISpecObject,(void **) &amp;_piSpecSchComp);
        if (SUCCEEDED(rc))
        {
          _piSpecSchComp-&gt;SetName (SCHEDUPart_TestRef1);  // Name it.
        }
      }
    }
```

```vbscript
rc = piCompCtr-&gt;AddConnector (SCHEDUClass_Connector, piGrr, ctr1Loc, &amp;piAppCtr1);
    if ( !SUCCEEDED(rc) || !piAppCtr1 ) 
    {
       cout &lt;&lt; &quot;CreateComponent: &quot;
            &lt;&lt; &quot;Add Connector 1 Failed&quot;
            &lt;&lt; endl;
       return E_FAIL;
    }
    rc = piAppCtr1-&gt;QueryInterface (IID_CATISchCntrLocation,(void **) &amp;piCtrLoc);
    if (SUCCEEDED (rc) &amp;&amp; piCtrLoc )
    {
      piCtrLoc-&gt;SetAlignVector(NULL, vector1);
      CAASchAppDeleteBaseUnknown(piCtrLoc);
    }
```

```vbscript
rc = _piSchComp-&gt;QueryInterface (IID_CATISchCompFlow, (void **) &amp;piCompFlow);
    if ( !SUCCEEDED(rc) || !piCompFlow ) 
    {
       cout &lt;&lt; &quot;CreateComponent: &quot;
            &lt;&lt; &quot;QI Failed for IID_CATISchCompFlow&quot;
            &lt;&lt; endl;
       return E_FAIL;
    }
    CATSchListServices aList;
    aList.CreateCATIUnknownList(&amp;pLICtrs); // Create a list of unknowns

    rc = piAppCtr1-&gt;QueryInterface (IID_IUnknown, (void **) &amp;piUnknown);
    if (SUCCEEDED(rc) &amp;&amp; piUnknown)
    {
      rc = pLICtrs-&gt;Add(0,piUnknown);
      CAASchAppDeleteBaseUnknown(piUnknown);
    }
    rc = piAppCtr2-&gt;QueryInterface (IID_IUnknown, (void **) &amp;piUnknown);
    if (SUCCEEDED(rc) &amp;&amp; piUnknown)
    {
      rc = pLICtrs-&gt;Add(1,piUnknown);
      CAASchAppDeleteBaseUnknown(piUnknown);
    }

    rc = piCompFlow-&gt;AddInternalFlow(pLICtrs, &amp;piInternalFlow1);
    if ( !SUCCEEDED(rc) || !piInternalFlow1 ) 
    {
       cout &lt;&lt; &quot;CreateComponent: &quot;
            &lt;&lt; &quot;AddInternalFlow failed&quot;
            &lt;&lt; endl;
       return E_FAIL;
    }
```

```vbscript
double aDb6Axis[6] = {1.0,0.0,0.0,1.0,50.0,100.0};
    rc = _piSchComp-&gt;PlaceInSpace (NULL, aDb6Axis, &amp;piSchComp);
    if (SUCCEEDED (rc))
    {
```