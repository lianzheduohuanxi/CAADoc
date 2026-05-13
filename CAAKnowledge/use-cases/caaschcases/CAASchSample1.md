---
title: "Creating Features in an Applicative Container"
category: "use-case case"
module: "CAASchUseCases"
tags: "["CAASchEduIn", "CAASchAppSample1", "CAASCHEDUApp", "CATISchAppObjectFactory", "CATISchSession", "CATIContainer_var", "CAASCHEDU_SamplePID", "CAASchAppBaseServices", "CAASchApp", "CATISchCompFlow", "CAASchEduOut1", "CATIExtendable_var", "CATISchBaseFactory", "CAASchAppSample1Main", "CAASchPlatformModeler", "CATISpecObject_var", "CAASchAppUtilities", "CATISpecObject", "CATISchAppConnectable", "CATISchComponent"]"
source_file: "Doc/online/CAASchUseCases/CAASchSample1.htm"
converted: "2026-05-11T17:31:51.513274"
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

This article discusses the CAASchAppSample1 use case.

  * **What You Will Learn With This Use Case**
  * **The CAASchAppSample1 Use Case**
    * What Does CAASchAppSample1 Do
    * How to Launch CAASchAppSample1
    * Where to Find the CAASchAppSample1 Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

This use case is intended to help you understand how to use the CAA Schematic Platform Interfaces to create Schematic components.

[Top]
### The CAASchAppSample1 Use Case

CAASchAppSample1 is a use case of the CAASchPlatformModeler.edu framework that illustrates CAASchPlatformModeler framework capabilities. The use case demonstrates the creation of a component for a sample Schematics application, CAASCHEDU_SamplePID.

[Top]
#### What Does CAASchAppSample1 Do

CAASchAppSample1 is a use case of the CAASchPlatformModeler.edu framework that illustrates CAASchPlatformModeler framework capabilities. The use case demonstrates the creation of a component for a sample Schematics application, CAASCHEDU_SamplePID.
The sample will create a component (feature reference) with two connectors and an internal flow. An Instance of the component is then created on the main sheet of the output drawing.

The sample uses a Schematic Extension Container to obtain the Schematics Base Factory and Application factory interfaces. It then makes a component reference object, adds connectors and internal flow to it, and instantiates (places) it on the main sheet of the drawing. The sample uses the Catalog, CAASCHEDUApp.CATfct. Here is an image of the contents of this catalog:

Fig.1: CAASCHEDUApp.CATfct Catalog Contents ![](images/CAASchCATFct.gif)

---

[Top]
#### How to Launch CAASchAppSample1

To launch CAASchAppSample1, you will need to set up the build time environment, then compile CAASchAppSample1 along with its prerequisites, set up the run time environment, and then execute the sample. This is fully described in the referenced article [1]. When launching the use case, you must pass the following arguments:

  * **CAASchEduIn.CATProduct** /- the entire pathname, name and extension (.CATProduct) of the input drawing. Normally, it should be stored in the CNext/resources/graphic file directory.
  * **CAASchEduOut1.CATProduct** /- the entire pathname, name and extension (.CATProduct) under which the new document is to be stored.

[Top]
#### Where to Find the CAASchAppSample1 Code

CAASchAppSample1 code is located in the CAASchAppSample1.m use case module of the CAASchPlatformModeler.edu framework:

Windows | `InstallRootDirectory/CAASchPlatformModeler.edu/CAASchAppSample1.m`

CAASchAppSample1 code is located in the CAASchAppSample1.m use case module of the CAASchPlatformModeler.edu framework:
Windows | `InstallRootDirectory/CAASchPlatformModeler.edu/CAASchAppSample1.m`
Unix | `InstallRootDirectory/CAASchPlatformModeler.edu/CAASchAppSample1.m`

where `InstallRootDirectory` is the root directory of your CAA V5 installation. It is made of a two unique source files named CAASchAppSample1Main.cpp and CAASchAppSample1.cpp.

Additional prerequisite code is located in the CAASchAppUtilities.m and CAASchAppBase.m modules of the same framework.

[Top]
### Step-by-Step

Additional prerequisite code is located in the CAASchAppUtilities.m and CAASchAppBase.m modules of the same framework.
There are eight logical steps in CAASchAppSample1:

  1. Prolog
  2. Initializing the Environment
  3. Creating an Application Reference Object
  4. Determining the Graphical Representation for the Reference Object
  5. Creating a Component Reference Object
  6. Adding Connectors to Component Reference Object
  7. Adding an Internal Flow to the Component Reference Object
  8. Placing an Instance of the Component on the Main Sheet

[Top]
#### Prolog

In this use case, we open an input drawing containing one main sheet and one detail sheet. The detail sheet contains three views. The use case will create a new .CATProduct drawing for the sample application.

[Top]
#### Initializing the Environment

The CAASchAppSample1 code is derived from the CAASchAppBaseEnv base class. The base class contains functionality common to the other CAASchApp samples. Initializing the environment involves the following methods:

    CAASchAppSample1::InitEnvironment
    CAASchAppSample1::GetDraftingObjects
    CreateCATProductEnv::CreateCATProductEnv

---

CAASchAppSample1::GetDraftingObjects
CreateCATProductEnv::CreateCATProductEnv
These methods perform the following functions:

  * Creating a session, namely "Session DSA CAASchAppBaseEnv CATProduct".
  * Obtaining the _CATISchSession_ interface from the session.
  * Obtaining the _CATISchBaseFactory_ interface from the session
  * Obtaining the applications _CATISchAppObjectFactory_ interface pointer.
  * Loading the input document.
  * Initializing the document using the _CATInit_ interface Init.
  * Retrieving the pointer to the root container object.
  * Obtaining the pointer to the detail sheet, etc.

[Top]
#### Creating an Application Reference Object

According to the rules of the Schematics Platform, a reference component is required before a component can be created and placed. The reference component is created by the _CATISchBaseFactory_ interface method CreateSchComponent. This method builds the component reference object from the application reference and a list of graphical representations. It is the responsibility of the Schematics application, in this case CAASCHEDU_SamplePID, to retrieve the application reference object.

As one of the requirements of a schematics application, the application must implement the _CATISchAppObjectFactory_ interface. This is the interface used by the application to create the application reference using the method AppCreateCompRef. In this use case, the application reference is already residing in the input document and AppCreateCompRef is used to retrieve it.

Notice the _CATISchAppObjectFactory_ interface pointer is obtained from the _CATISchSession_ interface which is tied to the session.

    CATISchSession* piSchSession = NULL;
```cpp
    if ( SUCCEEDED( pSession->QueryInterface (IID_CATISchSession,(void**)&piSchSession) ) )

```

    {
CATISchSession* piSchSession = NULL;
if ( SUCCEEDED( pSession->QueryInterface (IID_CATISchSession,(void**)&piSchSession) ) )
      HRESULT rc = piSchSession->GetSchObjInterface(SCHEDUApplication_Name,
                                                    IID_CATISchAppObjectFactory,
                                                    (void**)&_piSchAppObjFact);
      piSchSession->Release(#); piSchSession = NULL;

    }

---

_CAASCHEDU_SamplePID_ implements the _CATISchAppObjectFactory_ in the files **CAAESchAppObjectFactory.cpp** using methods in **CAASchAppBaseServices.cpp**. The important piece of code to know is listed below:

    //---------------------------------------------------------------------------
    //  Find an application object in a container by a specific class type
    //---------------------------------------------------------------------------
    CATISpecObject_var CAASchAppBaseServices::FindAppObjByClass (
       const CATUnicodeString &iUClass, const CATIContainer_var &iCont)

    {
CATISpecObject_var CAASchAppBaseServices::FindAppObjByClass (
const CATUnicodeString &iUClass, const CATIContainer_var &iCont)
       HRESULT RC = S_OK;
       CATISpecObject_var spObjFound = NULL_var;
       CATUnicodeString ClassType;
       int MatchPos;
       CATISchAppConnectable *piSchAppCntbl = NULL;
       CATIExtendable_var spApplExtble = NULL_var;

       SEQUENCE (CATBaseUnknown_ptr) L0Obj = iCont->
```cpp
          ListMembers(CATISpecObject::ClassName(#));

```

       int SizeOfL0Obj = L0Obj.length(#);
       CATISpecObject *piSpec;
```vbscript
       for (int iObj=0; iObj<SizeOfL0Obj; iObj++)

```

       {
int SizeOfL0Obj = L0Obj.length(#);
CATISpecObject *piSpec;
for (int iObj=0; iObj<SizeOfL0Obj; iObj++)
```vbscript
```cpp
         piSpec = (CATISpecObject *) L0Obj[iObj];
         if (NULL != piSpec)

```

```

         {
```vbscript
for (int iObj=0; iObj<SizeOfL0Obj; iObj++)
```vbscript
```cpp
piSpec = (CATISpecObject *) L0Obj[iObj];
if (NULL != piSpec)
            if (!spObjFound)
```

```

```

            {
piSpec = (CATISpecObject *) L0Obj[iObj];
```vbscript
```vbscript
if (NULL != piSpec)
if (!spObjFound)
              ClassType = piSpec->GetType(#);
```

              printf ("Class Type -- %s/n", ClassType.ConvertToChar(#));
```vbscript
              MatchPos = ClassType.SearchSubString(iUClass);
              if (MatchPos >= 0)

```

```

              {
ClassType = piSpec->GetType(#);
```vbscript
printf ("Class Type -- %s/n", ClassType.ConvertToChar(#));
```vbscript
MatchPos = ClassType.SearchSubString(iUClass);
if (MatchPos >= 0)
```

                printf ("Match found /n");
```

                spObjFound = piSpec;

              }
            }
printf ("Match found /n");
spObjFound = piSpec;
            piSpec->Release(#);
            piSpec = NULL;

         }
       }
piSpec->Release(#);
piSpec = NULL;
       return spObjFound;

    }

---

[Top]
#### Determining the Graphical Representation for the Reference Object

```vbscript
If a component is to be visualized, it needs Graphical Representation (GRR). A component may have more than one GRR, but can only display one GRR for a given instance. For this sample, the Component Reference Object to be created will have only one GRR. The GRR is the geometry shown in the first view on the detail sheet.

```

```cpp
If a component is to be visualized, it needs Graphical Representation (GRR). A component may have more than one GRR, but can only display one GRR for a given instance. For this sample, the Component Reference Object to be created will have only one GRR. The GRR is the geometry shown in the first view on the detail sheet.
        CATSchListServices SchList;
```cpp
        rc = SchList.CreateCATIUnknownList(&_piLUK);

        if ( SUCCEEDED(rc) )
```

```

        {
CATSchListServices SchList;
rc = SchList.CreateCATIUnknownList(&_piLUK);
```vbscript
```vbscript
if ( SUCCEEDED(rc) )
           if (_piLUK)

```

```

           {
```vbscript
if ( SUCCEEDED(rc) )
```vbscript
```vbscript
if (_piLUK)
              if (SUCCEEDED (_spDetailSpec->QueryInterface (IID_IUnknown,(void **) &_piUK)) )
```

```

```

              {
```vbscript
if (_piLUK)
```vbscript
if (SUCCEEDED (_spDetailSpec->QueryInterface (IID_IUnknown,(void **) &_piUK)) )
```

                 _piLUK->Add(0,_piUK);  // This list will only have 1 graphical representation
```

              }
           }
        }

---

[Top]
#### Creating a Component Reference Object

According to the rules of the Schematics Platform, a component reference object is required before a component can be created and placed. The reference component is created by the _CATISchBaseFactory_ interface method CreateSchComponent. This method builds the component reference object from the application reference and a list of graphical representations.

        //-------------------------------------------------------------------------
        //  Create schematic object
        //-------------------------------------------------------------------------
        rc = _piBaseFact->CreateSchComponent (_piUKAppRef, _piLUK, &_piSchComp);
```vbscript
```vbscript
rc = _piBaseFact->CreateSchComponent (_piUKAppRef, _piLUK, &_piSchComp);
        if (SUCCEEDED(rc) )

```

```

        {
rc = _piBaseFact->CreateSchComponent (_piUKAppRef, _piLUK, &_piSchComp);
```vbscript
```vbscript
if (SUCCEEDED(rc) )
          if ( _piSchComp)

```

```

          {
rc = _piBaseFact->CreateSchComponent (_piUKAppRef, _piLUK, &_piSchComp);
```vbscript
```cpp
if (SUCCEEDED(rc) )
if ( _piSchComp)
            rc = _piSchComp->QueryInterface (IID_CATISpecObject,(void **) &_piSpecSchComp);
            if (SUCCEEDED(rc))

```

```

            {
```vbscript
if ( _piSchComp)
```vbscript
```cpp
rc = _piSchComp->QueryInterface (IID_CATISpecObject,(void **) &_piSpecSchComp);
if (SUCCEEDED(rc))
```

```

              _piSpecSchComp->SetName (SCHEDUPart_TestRef1);  // Name it.
```

            }
          }
        }

---

[Top]
#### Adding Connectors to Component Reference Object

A component such as a valve can have connectors. Some components may have multiple connectors. This sample adds two connectors to the Component Reference Object. In order to do this, the code must use the _CATISchCompConnector_ interface method AddConnector. Once the connector is created, it must be aligned, ( i.e. horizontally, vertically, etc.) See the code for more detail.

        rc = piCompCtr->AddConnector (SCHEDUClass_Connector, piGrr, ctr1Loc, &piAppCtr1);
```vbscript
```vbscript
        if ( !SUCCEEDED(rc) || !piAppCtr1 )

```

```

        {
rc = piCompCtr->AddConnector (SCHEDUClass_Connector, piGrr, ctr1Loc, &piAppCtr1);
```vbscript
if ( !SUCCEEDED(rc) || !piAppCtr1 )
```

           cout << "CreateComponent: "

                << "Add Connector 1 Failed"
                << endl;
```vbscript
if ( !SUCCEEDED(rc) || !piAppCtr1 )
cout << "CreateComponent: "
           return E_FAIL;
```

        }
cout << "CreateComponent: "
return E_FAIL;
        rc = piAppCtr1->QueryInterface (IID_CATISchCntrLocation,(void **) &piCtrLoc);
```vbscript
```vbscript
        if (SUCCEEDED (rc) && piCtrLoc )

```

```

        {
return E_FAIL;
rc = piAppCtr1->QueryInterface (IID_CATISchCntrLocation,(void **) &piCtrLoc);
```vbscript
if (SUCCEEDED (rc) && piCtrLoc )
```

          piCtrLoc->SetAlignVector(NULL, vector1);
          CAASchAppDeleteBaseUnknown(piCtrLoc);

        }

---

[Top]
#### Adding an Internal Flow to the Component Reference Object

A component may have an internal flow. An internal flow represents a flow between pairs of connectors of a component. The sample creates an internal flow between the two connectors added to the component. To do this, the _CATISchCompFlow_ interface must be obtained from the component reference object.

The sample uses the  AddInternalFlow method of the _CATISchCompFlow_ __ interface, which takes two arguments. The first argument represents a list of connector pairs, in this case only one connector pair. The second argument is a pointer to the internal flow created.

A component may have an internal flow. An internal flow represents a flow between pairs of connectors of a component. The sample creates an internal flow between the two connectors added to the component. To do this, the _CATISchCompFlow_ interface must be obtained from the component reference object.
The sample uses the  AddInternalFlow method of the _CATISchCompFlow_ __ interface, which takes two arguments. The first argument represents a list of connector pairs, in this case only one connector pair. The second argument is a pointer to the internal flow created.
        rc = _piSchComp->QueryInterface (IID_CATISchCompFlow, (void **) &piCompFlow);
```vbscript
```vbscript
        if ( !SUCCEEDED(rc) || !piCompFlow )

```

```

        {
rc = _piSchComp->QueryInterface (IID_CATISchCompFlow, (void **) &piCompFlow);
```vbscript
if ( !SUCCEEDED(rc) || !piCompFlow )
```

           cout << "CreateComponent: "

                << "QI Failed for IID_CATISchCompFlow"
                << endl;
```vbscript
if ( !SUCCEEDED(rc) || !piCompFlow )
cout << "CreateComponent: "
           return E_FAIL;
```

        }
cout << "CreateComponent: "
return E_FAIL;
        CATSchListServices aList;
        aList.CreateCATIUnknownList(&pLICtrs); // Create a list of unknowns

        rc = piAppCtr1->QueryInterface (IID_IUnknown, (void **) &piUnknown);
```vbscript
```vbscript
        if (SUCCEEDED(rc) && piUnknown)

```

```

        {
aList.CreateCATIUnknownList(&pLICtrs); // Create a list of unknowns
rc = piAppCtr1->QueryInterface (IID_IUnknown, (void **) &piUnknown);
```vbscript
```vbscript
if (SUCCEEDED(rc) && piUnknown)
          rc = pLICtrs->Add(0,piUnknown);
```

          CAASchAppDeleteBaseUnknown(piUnknown);

```

        }
```vbscript
if (SUCCEEDED(rc) && piUnknown)
```vbscript
rc = pLICtrs->Add(0,piUnknown);
CAASchAppDeleteBaseUnknown(piUnknown);
```vbscript
        rc = piAppCtr2->QueryInterface (IID_IUnknown, (void **) &piUnknown);
        if (SUCCEEDED(rc) && piUnknown)
```

```

```

        {
```vbscript
CAASchAppDeleteBaseUnknown(piUnknown);
```vbscript
```vbscript
rc = piAppCtr2->QueryInterface (IID_IUnknown, (void **) &piUnknown);
if (SUCCEEDED(rc) && piUnknown)
          rc = pLICtrs->Add(1,piUnknown);
```

          CAASchAppDeleteBaseUnknown(piUnknown);
```

```

        }

rc = pLICtrs->Add(1,piUnknown);
```vbscript
CAASchAppDeleteBaseUnknown(piUnknown);
```vbscript
        rc = piCompFlow->AddInternalFlow(pLICtrs, &piInternalFlow1);
        if ( !SUCCEEDED(rc) || !piInternalFlow1 )

```

```

        {
rc = piCompFlow->AddInternalFlow(pLICtrs, &piInternalFlow1);
```vbscript
if ( !SUCCEEDED(rc) || !piInternalFlow1 )
```

           cout << "CreateComponent: "

                << "AddInternalFlow failed"
                << endl;
```vbscript
if ( !SUCCEEDED(rc) || !piInternalFlow1 )
cout << "CreateComponent: "
           return E_FAIL;
```

        }

---

[Top]
#### Placing an Instance of the Component on the Main Sheet

The component reference can now be instantiated on the main sheet of the drawing. This is done with the _CATISchComponent_ interface. The PlaceInSpace __ method is used to do this.

        double aDb6Axis[6] = {1.0,0.0,0.0,1.0,50.0,100.0};
        rc = _piSchComp->PlaceInSpace (NULL, aDb6Axis, &piSchComp);
```vbscript
```vbscript
        if (SUCCEEDED (rc))

```

```

        {

---

Note the aDb6Axis array contains the vector (1.0,0.0) representing the X axis, the vector (0.0,1.0) representing the Y axis, and the location (50.0,100). This vectors determines the orientation and location of the component on the sheet.

[Top]

* * *
### In Short

This use case has demonstrated how to create a component reference object and instantiate it on the main sheet of the drawing for a sample Schematics application. Specifically, it has illustrated:

  * Obtaining the necessary Sch Interfaces
  * Using the Application Object Factory to create an Application Reference Object
  * Associating a Graphical Representation to a component reference
  * Using the Schematics Base Object Factory to create a component reference
  * Adding connectors and internal flow to a component reference
  * Placing a component

[Top]

* * *
### References

[1] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---

* * *
### History

Version: **1** [April 2001] | Document created
---|---
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
