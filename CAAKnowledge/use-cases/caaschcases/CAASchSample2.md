---
```vbscript
title: "Creating Features in an Applicative Container"
category: "use case"
module: "CAASchUseCases"
tags: ["CAASchAppSample2", "CATISchAppObjectFactory", "CAASchAppSample1", "CATISchSession", "CAASCHEDU_SamplePID", "CATISchGRRComp", "CAASchApp", "CAASchEduOut2", "CAASchEduIn2", "CATISchBaseFactory", "CAASchAppSample2Main", "CAASchPlatformModeler", "CATISchCompGraphic", "CATIView", "CAASchAppUtilities", "CATISpecObject", "CATISchComponent", "CATInit", "CAASchAppBase", "CAASchAppBaseEnv"]
source_file: "Doc/online/CAASchUseCases/CAASchSample2.htm"
converted: "2026-05-11T17:31:51.518765"
```

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

This article discusses the CAASchAppSample2 use case.

  * **What You Will Learn With This Use Case**
  * **The CAASchAppSample2 Use Case**
    * What Does CAASchAppSample2 Do
    * How to Launch CAASchAppSample2
    * Where to Find the CAASchAppSample2 Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

This use case is intended to help you understand how to use the CAA Schematic Platform Interfaces to manipulate Graphical Representations (GRRS) of Schematic components.

[Top]
### The CAASchAppSample2 Use Case

CAASchAppSample2 is a use case of the CAASchPlatformModeler.edu framework that illustrates CAASchPlatformModeler framework capabilities. The use case demonstrates the creation of a component for a sample Schematics application, **CAASCHEDU_SamplePID**.

[Top]
#### What Does CAASchAppSample2 Do

The sample demonstrates the use of multiple Graphical Representations (GRRs) of a component and the ability to swap these representations among the instances of the component.

[Top]
#### How to Launch CAASchAppSample2

To launch CAASchAppSample2, you will need to set up the build time environment, then compile CAASchAppSample2 along with its prerequisites, set up the run time environment, and then execute the sample. This is fully described in the referenced article [1]. When launching the use case, you must pass the following arguments:

  * **CAASchEduIn2.CATProduct** \- the entire pathname, name and extension (.CATProduct) of the input drawing. Normally, it should be stored in the CNext/resources/graphic file directory.
  * **CAASchEduOut2.CATProduct** \- the entire pathname, name and extension (.CATProduct) under which the new document is to be stored

[Top]
#### Where to Find the CAASchAppSample2 Code

CAASchAppSample2 code is located in the CAASchAppSample2.m use case module of the CAASchPlatformModeler.edu framework:

CAASchAppSample2 code is located in the CAASchAppSample2.m use case module of the CAASchPlatformModeler.edu framework:
Windows | `InstallRootDirectory\CAASchPlatformModeler.edu\CAASchAppSample2.m`

CAASchAppSample2 code is located in the CAASchAppSample2.m use case module of the CAASchPlatformModeler.edu framework:
Windows | `InstallRootDirectory\CAASchPlatformModeler.edu\CAASchAppSample2.m`
Unix | `InstallRootDirectory/CAASchPlatformModeler.edu/CAASchAppSample2.m`

where `InstallRootDirectory` is the root directory of your CAA V5 installation. It is made of a two unique source files named CAASchAppSample2Main.cpp and CAASchAppSample2.cpp.

Additional prerequisite code is located in the CAASchAppUtilities.m and CAASchAppBase.m modules of the same framework.

[Top]
### Step-by-Step

Additional prerequisite code is located in the CAASchAppUtilities.m and CAASchAppBase.m modules of the same framework.
These are the logical steps in CAASchAppSample2:

  1. Prolog
  2. Initializing the Environment
  3. Obtaining the List of GRRs for the Component Reference Object
  4. Adding additional GRRs to the Component Reference Object
  5. Placing another Instance of the Component on the Main Sheet
  6. Activating a Second Occurrence of the Instance using a Different GRR
  7. Swapping GRRs

[Top]
#### Prolog

In this use case, we open an input drawing containing one main sheet and one detail sheet. The main sheet contains one component instantiated from a reference object. The detail sheet contains three views. The use case will create a new .CATProduct drawing for the sample application.

[Top]
#### Initializing the Environment

The CAASchAppSample2 code is derived from the CAASchAppBaseEnv base class. The base class contains functionality common to the other CAASchApp samples. Initializing the environment involves the following methods:

The CAASchAppSample2 code is derived from the CAASchAppBaseEnv base class. The base class contains functionality common to the other CAASchApp samples. Initializing the environment involves the following methods:
    CAASchAppSample2::InitEnvironment
    CAASchAppSample2::GetAppReference
    CreateCATProductEnv::CreateCATProductEnv

---

CAASchAppSample2::GetAppReference
CreateCATProductEnv::CreateCATProductEnv
These methods perform the following functions:

  * Creating a session, namely "Session DSA CAASchAppBaseEnv CATProduct".
  * Obtaining the _CATISchSession_ interface from the session.
  * Obtaining the _CATISchBaseFactory_ interface from the session
  * Obtaining the applications _CATISchAppObjectFactory_ interface pointer.
  * Loading the input document.
  * Initializing the document using the _CATInit_ interface.
  * Obtaining the pointer to the component reference.

[Top]
#### Obtaining the List of GRRs for the Component Reference Object

In order to add to the list of GRRs for the component reference, we first obtain the current list of GRRs. We dont want to add a duplicate GRR to our component reference. To obtain the list of GRRs, the code uses the _CATISchCompGraphic_ interface method ListGraphicalRepresentations. From this method we obtain a list of GRR, each of which we can query for the _CATIView_ interface pointer.

Since the drawing was created by CAASchAppSample1, we know there is only one GRR in the list.

        //-------------------------------------------------------------------------
        //  Using the reference object, find CATISchCompGraphic interface.
        //-------------------------------------------------------------------------
        HRESULT rc = _spAppRef->QueryInterface (IID_CATISchCompGraphic,(void **) &piCompGraphic);
HRESULT rc = _spAppRef->QueryInterface (IID_CATISchCompGraphic,(void **) &piCompGraphic);
```vbscript
        if (!SUCCEEDED(rc))

```

        {
HRESULT rc = _spAppRef->QueryInterface (IID_CATISchCompGraphic,(void **) &piCompGraphic);
if (!SUCCEEDED(rc))
           cout << "cannot get CATISchCompGraphic interface " << endl;
           return 0;

        }

        //-------------------------------------------------------------------------
        //  Use the CATISchCompGraphic's method, ListGraphicalRepresentations, to
        //  find the current graphical representations for the object.
        //
        //  Since this object was created in sample1, we know it will only have
        //  one GRR.  Use this to find the detail sheet and view of the GRR.
        //-------------------------------------------------------------------------
        int NbGRR = 0;
int NbGRR = 0;
```vbscript
        if (SUCCEEDED (piCompGraphic->ListGraphicalRepresentations (&pLIGRRs)))

```

        {
int NbGRR = 0;
if (SUCCEEDED (piCompGraphic->ListGraphicalRepresentations (&pLIGRRs)))
           unsigned int uSize = 0;
```vbscript
           if (SUCCEEDED (pLIGRRs->Count(&uSize)))

```

           {
```vbscript
if (SUCCEEDED (piCompGraphic->ListGraphicalRepresentations (&pLIGRRs)))
unsigned int uSize = 0;
if (SUCCEEDED (pLIGRRs->Count(&uSize)))
              cout << "Size of GRR List = " << uSize << endl;
              NbGRR = uSize;
              if (uSize)
```

              {
cout << "Size of GRR List = " << uSize << endl;
NbGRR = uSize;
if (uSize)
                 IUnknown *piUK = NULL;
```vbscript
                 if (SUCCEEDED (pLIGRRs->Item(0,&piUK)))

```

                 {
```vbscript
if (uSize)
IUnknown *piUK = NULL;
if (SUCCEEDED (pLIGRRs->Item(0,&piUK)))
```vbscript
                    if ( SUCCEEDED (piUK->QueryInterface (IID_CATIView,(void **) &piViewGRR1)))
```

```

                    {
IUnknown *piUK = NULL;
if (SUCCEEDED (pLIGRRs->Item(0,&piUK)))
```vbscript
```vbscript
if ( SUCCEEDED (piUK->QueryInterface (IID_CATIView,(void **) &piViewGRR1)))
                       spDtlSheet = piViewGRR1->GetSheet();
                       if (!!spDtlSheet)

```

```

                       {
```vbscript
if ( SUCCEEDED (piUK->QueryInterface (IID_CATIView,(void **) &piViewGRR1)))
```vbscript
```vbscript
spDtlSheet = piViewGRR1->GetSheet();
if (!!spDtlSheet)
```

```

                          cout << "Got detail sheet containing the GRR detail "
```

                               << endl;
                       }
                    }
cout << "Got detail sheet containing the GRR detail "
                    rc = piUK->QueryInterface (IID_CATISchGRRComp,(void **) &piGRRComp1);
```vbscript
                    CAASchAppDeleteBaseUnknown (piUK);

```

                 }
              }
           }
        }

---

[Top]
#### Adding Additional GRRs to the Component Reference Object

To add a GRR to a component reference we use the the _CATISchCompGraphic_ interface method `AddGraphicalRepresentation`. This method has one argument which is of type CATISchGRRComp*. The code loops through all the view in the detail sheet. When it finds a view, it checks to see if it matches the view of the original GRR. If not, it adds the GRR to the component. Since the _CATISchGRRComp_ interface is tied to the view object, we can obtain the CATISchGRRComp* for each view.

To add a GRR to a component reference we use the the _CATISchCompGraphic_ interface method `AddGraphicalRepresentation`. This method has one argument which is of type CATISchGRRComp*. The code loops through all the view in the detail sheet. When it finds a view, it checks to see if it matches the view of the original GRR. If not, it adds the GRR to the component. Since the _CATISchGRRComp_ interface is tied to the view object, we can obtain the CATISchGRRComp* for each view.
```vbscript
    	for (int iView = 3; iView <= SizeOfLView; iView++)

```

            {
To add a GRR to a component reference we use the the _CATISchCompGraphic_ interface method `AddGraphicalRepresentation`. This method has one argument which is of type CATISchGRRComp*. The code loops through all the view in the detail sheet. When it finds a view, it checks to see if it matches the view of the original GRR. If not, it adds the GRR to the component. Since the _CATISchGRRComp_ interface is tied to the view object, we can obtain the CATISchGRRComp* for each view.
for (int iView = 3; iView <= SizeOfLView; iView++)
```vbscript
```vbscript
              if (LView[iView] != spSpecView)

```

```

              {
```vbscript
for (int iView = 3; iView <= SizeOfLView; iView++)
```vbscript
```vbscript
if (LView[iView] != spSpecView)
                if (SUCCEEDED ( (LView[iView])->QueryInterface (IID_CATISchGRRComp,(void **) &piGRRComp)))
```

```

```

                {
```vbscript
if (LView[iView] != spSpecView)
```vbscript
```vbscript
if (SUCCEEDED ( (LView[iView])->QueryInterface (IID_CATISchGRRComp,(void **) &piGRRComp)))
                  if (SUCCEEDED (piCompGraphic->AddGraphicalRepresentation (piGRRComp)))
```

```

```

                  {
```vbscript
if (SUCCEEDED ( (LView[iView])->QueryInterface (IID_CATISchGRRComp,(void **) &piGRRComp)))
```vbscript
if (SUCCEEDED (piCompGraphic->AddGraphicalRepresentation (piGRRComp)))
```

                    cout << "successfully added GRR at position " << iView << endl;
                    NbGRR ++;
                    if ( NbGRR == 2 ) piGRRComp2 = piGRRComp;
```vbscript
                    if ( NbGRR == 3 ) piGRRComp3 = piGRRComp;
```

```

                  }
                }
              }
    	}

---

[Top]
#### Placing Another Instance of the Component on the Main Sheet

Placing an instance of the component reference is done using the PlaceInSpace method of the CATISchComponent interface. The coding is similar to that of CAASchAppSample1.

Placing an instance of the component reference is done using the PlaceInSpace method of the CATISchComponent interface. The coding is similar to that of CAASchAppSample1.
```vbscript
        if ( SUCCEEDED(_spAppRef->QueryInterface (IID_CATISchComponent,(void **) &piComponent)) )

```

        {
Placing an instance of the component reference is done using the PlaceInSpace method of the CATISchComponent interface. The coding is similar to that of CAASchAppSample1.
if ( SUCCEEDED(_spAppRef->QueryInterface (IID_CATISchComponent,(void **) &piComponent)) )
          double aDb6Axis[6] = {1.0,0.0, 0.0,1.0, 50.0,200.0};

          rc = piComponent->PlaceInSpace (NULL, aDb6Axis, &piSchComp);
```vbscript
```vbscript
          if (SUCCEEDED (rc))

```

```

          {

rc = piComponent->PlaceInSpace (NULL, aDb6Axis, &piSchComp);
```vbscript
if (SUCCEEDED (rc))
```

            CATISpecObject *piSchCompInst = NULL;
```vbscript
            if (SUCCEEDED (piSchComp->QueryInterface (IID_CATISpecObject,(void **) &piSchCompInst)))

```

            {
CATISpecObject *piSchCompInst = NULL;
if (SUCCEEDED (piSchComp->QueryInterface (IID_CATISpecObject,(void **) &piSchCompInst)))
              piSchCompInst->SetName (SCHEDUPart_TestInst2);  // Name the instance
              CAASchAppDeleteBaseUnknown (piSchCompInst);

            }

---

[Top]
#### Activating a Second Occurrenc of the Instance using a Different GRR

A component may have more than one occurrence shown on the drawing. This is not the same as instantiating the component reference another time. Rather, it is useful for allowing the representation of a component to be shown in different locations on a drawing with the same or a different GRR. Our component reference object now has three GRRs. The code below shows the activating of another occurrence of our component at a new location and using the second GRR. This is done using the _CATISchCompGraphic_ interface `Activate` method from our placed component.

A component may have more than one occurrence shown on the drawing. This is not the same as instantiating the component reference another time. Rather, it is useful for allowing the representation of a component to be shown in different locations on a drawing with the same or a different GRR. Our component reference object now has three GRRs. The code below shows the activating of another occurrence of our component at a new location and using the second GRR. This is done using the _CATISchCompGraphic_ interface `Activate` method from our placed component.
            double Db2Loc[2] = {220.0,200.0};
            char *pGRRName = NULL;
```vbscript
            if ( SUCCEEDED (piGRRComp2->QueryInterface(IID_CATISchGRR,(void**)&piSchGRR) ) )

```

            {
double Db2Loc[2] = {220.0,200.0};
char *pGRRName = NULL;
if ( SUCCEEDED (piGRRComp2->QueryInterface(IID_CATISchGRR,(void**)&piSchGRR) ) )
```vbscript
```vbscript
              if ( SUCCEEDED (piSchGRR->GetGRRName(&pGRRName)) )

```

```

              {
char *pGRRName = NULL;
if ( SUCCEEDED (piGRRComp2->QueryInterface(IID_CATISchGRR,(void**)&piSchGRR) ) )
```vbscript
```vbscript
if ( SUCCEEDED (piSchGRR->GetGRRName(&pGRRName)) )
                rc = piSchComp->QueryInterface (IID_CATISchCompGraphic,(void **) &piCompGraphic);
                if ( SUCCEEDED(rc) )

```

```

                {
```vbscript
if ( SUCCEEDED (piSchGRR->GetGRRName(&pGRRName)) )
```vbscript
```vbscript
rc = piSchComp->QueryInterface (IID_CATISchCompGraphic,(void **) &piCompGraphic);
if ( SUCCEEDED(rc) )
                  rc = piCompGraphic->Activate(pGRRName,Db2Loc,&piNewGRRComp);
```

```

```

                }

---

[Top]
#### Swap GRRs

The _CATISchCompGraphic_ interface also has methods to allow switching of the GRRs for a given occurrence or all occurrences of an object. The sample shows using the `SwitchAll` method to change all the occurrences of our new placed component to the second GRR.

The _CATISchCompGraphic_ interface also has methods to allow switching of the GRRs for a given occurrence or all occurrences of an object. The sample shows using the `SwitchAll` method to change all the occurrences of our new placed component to the second GRR.
```vbscript
       if ( SUCCEEDED(piCompGraphic->SwitchAll(pGRRName)) )

```

       {
The _CATISchCompGraphic_ interface also has methods to allow switching of the GRRs for a given occurrence or all occurrences of an object. The sample shows using the `SwitchAll` method to change all the occurrences of our new placed component to the second GRR.
if ( SUCCEEDED(piCompGraphic->SwitchAll(pGRRName)) )
         cout << "Successfully switched all images" << endl;

       }
```vbscript
if ( SUCCEEDED(piCompGraphic->SwitchAll(pGRRName)) )
cout << "Successfully switched all images" << endl;
       else cout << "Failed to switch all images" << endl;

```

---

[Top]

* * *
### In Short

This use case has demonstrated how to get a component reference object from a drawing, manipulate it's GRRs, instantiate and activate more than one occurrence. Specifically, it has illustrated:

  * Obtaining the necessary Sch Interfaces
  * Listing the Graphical Representations of a component reference
  * Adding additional Graphical Representations to a component reference
  * Activating additional occurrences of a component instance
  * Swapping GRRs of a component instance

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
