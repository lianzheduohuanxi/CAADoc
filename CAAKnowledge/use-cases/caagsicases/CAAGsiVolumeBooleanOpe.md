---
title: "Inserting Boolean Operations on Volume Features"
category: "use-case case"
module: "CAAGsiUseCases"
tags: "["CAAGSMInterfaces", "CATIPrtBooleanFactory", "CATIPrtContainer", "CAAGsiStartVolumeForBoolean", "CAAGsiVolumeOpe", "CATIPrtPart_var", "CATInit", "CATISpecObject_var", "CATIPrtBooleanFactory_var", "CAAGsiStartForBoolean", "CAAGsiVolumeFormFeatures", "CAAGsiObjectUpdate", "CAAGsiVolumeBooleanOpe"]"
source_file: "Doc/online/CAAGsiUseCases/CAAGsiVolumeBooleanOpe.htm"
converted: "2026-05-11T17:31:50.644673"
---
# Shape Design & Styling

|
## Generative Shape Design

|
### Inserting Boolean Operations on Volume Features

_Using the Part Design Boolean factory, add, remove , intersect operations on volume features_
---|---|---
Use Case

* * *
### Abstract

This article discusses the CAAGsiVolumeBooleanOpe use case. This use case explains how to boolean operation on volume.

  * **What You Will Learn With This Use Case**
  * **The CAAGsiVolumeBooleanOpe Use Case**
    * What Does CAAGsiVolumeBooleanOpe Do
    * How to Launch CAAGsiVolumeBooleanOpe
    * Where to Find the CAAGsiVolumeBooleanOpe Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will You Learn With This Use Case

This use case learns how to use Part Design Boolean factory to create boolean operations between volumes
Note : Creations of volume and use of boolean operations on volumes  are licensed by GSO Product

>   * Add , Remove , Intersect, Union trim are the supported operation on volumes
>

[Top]
### The CAAGsiVolumeBooleanOpe Use Case

CAAGsiVolumeBooleanOpe is a use case of the CAAGSMInterfaces.edu framework that illustrates boolean operations on volumes using Part Design

![](images/CAAGsiVolumeBooleanOpe.jpg)

CAAGsiVolumeBooleanOpe is a use case of the CAAGSMInterfaces.edu framework that illustrates boolean operations on volumes using Part Design
Boolean operation on volume are propose in the CATIPrtBooleanFactory, use also for boolean operations on solid features, a context has to be initalize in the creation methods
Note : The sample uses a C++ "#define" to be valuated to 4 for volume named BOOLEAN_OPE_ON_VOLUME

[Top]
#### What Does CAAGsiVolumeBooleanOpe Do

CAAGsiVolumeOpe creates different operations on volumes using  CATIPrtBooleanFactory

[Top]
#### How to Launch CAAGsiVolumeBooleanOpe

CAAGsiVolumeOpe creates different operations on volumes using  CATIPrtBooleanFactory
To launch CAAGsiVolumeBooleanOpe, you will need to set up the build time environment, then compile CAAGsiVolumeBooleanOpe along with its prerequisites, and set up the run time environment, and then execute the use case [1].

Launch the use case as follows:

  * With Windows

        e:>CAAGsiVolumeBooleanOpe InstallDir/CAAGSMInterfaces.edu/Data.d/CAAGsiStartVolumeForBoolean.CATPart CAAGsiStartVolumeForBoolean.CATPart outputDirectory/CAAGsiVolumeBooleanOpe.CATPart

---
  * With UNIX

        $ CAAGsiVolumeBooleanOpe InstallDir/CAAGSMInterfaces.edu/Data.d/CAAGsiStartVolumeForBoolean.CATPart CAAGsiStartVolumeForBoolean.CATPart outputDirectory/CAAGsiVolumeBooleanOpe.CATPart

---

where:

`inputDirectory` | The directory into which `CAAGsiStartForBoolean.CATPart is found `
---|---
`outputDirectory` | The directory into which `CAAGsiVolumeBooleanOpe.CATPart is saved`
`CAAGsiVolumeBooleanOpe.CATPart` | The file that contains the part created with the datum surface t

[Top]
#### Where to Find the CAAGsiVolumeBooleanOpe Code

The CAAGsiVolumeBooleanOpe use case is made of main program located in the CAAGsiVolumeBooleanOpe.m module of the CAAGSMInterfaces.edu framework:

Windows | `InstallRootDirectory/CAAGSMInterfaces.edu/CAAGsiVolumeBooleanOpe.m/`

The CAAGsiVolumeBooleanOpe use case is made of main program located in the CAAGsiVolumeBooleanOpe.m module of the CAAGSMInterfaces.edu framework:
Windows | `InstallRootDirectory/CAAGSMInterfaces.edu/CAAGsiVolumeBooleanOpe.m/`
Unix | `InstallRootDirectory/CAAGSMInterfaces.edu/CAAGsiVolumeBooleanOpe.m/`

The input CAAGsiStartForBoolean.CATPart is proposed in Data.d directory of CAAGSMInterfaces.edu

Windows | `InstallRootDirectory/CAAGSMInterfaces.edu/Data.d/CAAGsiStartForBoolean.CATPart `

The input CAAGsiStartForBoolean.CATPart is proposed in Data.d directory of CAAGSMInterfaces.edu
Windows | `InstallRootDirectory/CAAGSMInterfaces.edu/Data.d/CAAGsiStartForBoolean.CATPart `
Unix | `InstallRootDirectory/CAAGSMInterfaces.edu/Data.d/CAAGsiStartForBoolean.CATPart`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
There are five logical step in CAAGsiVolumeBooleanOpe:

  1. Prolog
  2. Create add operation on volume
  3. Create remove operation on volume
  4. Create intersect operation on volume
  5. Save and close session

We will now comment each of those sections by looking at the code of the main method of file CAAGsiVolumeBooleanOpe.

[Top]

* * *
#### Prolog

CAAGsiVolumeBooleanOpe sample first creates a session and opens the input CATPart.

Note: The important feature of the following sequence of code consists in the required call to the GetPart(#) method of the CATPrtContainer interfaces. This method allow to load in session the different containers of the part

    ....
    // creates a session
Note: The important feature of the following sequence of code consists in the required call to the GetPart(#) method of the CATPrtContainer interfaces. This method allow to load in session the different containers of the part
    char *pSessionName = "SampleSession";
    CATSession *pSession = NULL;
    rc = Create_Session(pSessionName, pSession);
```vbscript
    if (NULL == pSession ) {
```

       cout << "(CAAGsiVolumeBooleanOpe) ERROR: Create_Session" << endl ;
       TestCaseError = 1 ;

    }

    // loads the document and initializes it
cout << "(CAAGsiVolumeBooleanOpe) ERROR: Create_Session" << endl ;
TestCaseError = 1 ;
    cout << "The input document " << InputName << " is opened" << endl ;
    CATDocument *pDoc = NULL;
```cpp
    rc =CATDocumentServices::OpenDocument(InputName, pDoc) ;

    if (NULL == pDoc ) {
```

       cout << "(CAAGsiVolumeBooleanOpe) ERROR CATDocumentServices::OpenDocument" << endl ;
       TestCaseError = 2 ;

    }

    // Part Container
cout << "(CAAGsiVolumeBooleanOpe) ERROR CATDocumentServices::OpenDocument" << endl ;
TestCaseError = 2 ;
    CATIPrtContainer *piPartContainer = NULL ;
    CATIPrtPart_var spPrtPart;

```vbscript
    if ( NULL != pDoc ) {

```

       // queries on the document to get the root container
CATIPrtContainer *piPartContainer = NULL ;
CATIPrtPart_var spPrtPart;
if ( NULL != pDoc ) {
       CATInit *pDocAsInit = NULL;
       pDoc->QueryInterface(IID_CATInit, (void**)&pDocAsInit) ;
```vbscript
       if ( NULL != pDocAsInit ) {

```

        // Extracts from document a reference to its part in hPartAsRequest
CATInit *pDocAsInit = NULL;
pDoc->QueryInterface(IID_CATInit, (void**)&pDocAsInit) ;
if ( NULL != pDocAsInit ) {
       piPartContainer =
          (CATIPrtContainer*)pDocAsInit->GetRootContainer("CATIPrtContainer");
       pDocAsInit->Release(#); pDocAsInit = NULL ;

       if( NULL != piPartContainer ) {
          CATISpecObject_var spPart = piPartContainer->GetPart(#) ;
          spPrtPart = spPart ;

       }
    }
    ...

---

Then in the initialization phase the wire frame and shape design and Part Design factory are retrieved. .

    ....
Then in the initialization phase the wire frame and shape design and Part Design factory are retrieved. .
    CATIPrtBooleanFactory_var spBoolPrtFact;
```vbscript
    if ( NULL !=piPartContainer ) {

```

    // Retrieve the boolean part  Factory Interface
CATIPrtBooleanFactory_var spBoolPrtFact;
if ( NULL !=piPartContainer ) {
      CATIPrtBooleanFactory * _pBoolPrtFact =NULL;
      rc = piPartContainer -> QueryInterface(IID_CATIPrtBooleanFactory ,(void**)&_pBoolPrtFact);
```vbscript
      if (SUCCEEDED(rc) ) {
```

         spBoolPrtFact = _pBoolPrtFact;
```vbscript
         if (_pBoolPrtFact) _pBoolPrtFact -> Release(#); _pBoolPrtFact = NULL;

```

      }
    }
    ....

---

[Top]
#### Create add operation on volume

Create add operation using CreateAdd method of CATIPrtBooleanFactory

Note: Insert in procedural view is done at creation under the current geometrical feature set

    ...
    #define BOOLEAN_OPE_ON_VOLUME  4
    ...
    // Add
    // ----------------------------------------------------------------------------
    cout << "(CAAGsiVolumeFormFeatures) Add " << endl;
    CATISpecObject_var spSpecExtr1 = ...
    CATISpecObject_var spSpecExtr2 = ...

    CATISpecObject_var spSpecAdd = spBoolPrtFact -> CreateAdd ( spSpecExtr1,spSpecExtr2 ,BOOLEAN_OPE_ON_VOLUME) ;
    CAAGsiObjectUpdate(spSpecAdd) ;

    ...

---

[Top]
#### Create remove operation on volume

Create remove operation using CreateRemove method of CATIPrtBooleanFactory

Note: Insert in procedural view is done at creation under the current geometrical feature set

    ...
    #define BOOLEAN_OPE_ON_VOLUME  4
    ...
    // Remove
    // ----------------------------------------------------------------------------
    cout << "(CAAGsiVolumeFormFeatures) Remove " << endl;
    CATISpecObject_var spSpecExtr3 = ...

    CATISpecObject_var spSpecRemove = spBoolPrtFact -> CreateRemove ( spSpecAdd,spSpecExtr3 ,BOOLEAN_OPE_ON_VOLUME ) ;
    CAAGsiObjectUpdate(spSpecRemove) ;

---

[Top]
#### Create intersect operation on volume

Create intersect operation using CreateIntersect method of CATIPrtBooleanFactory

    ...
    #define BOOLEAN_OPE_ON_VOLUME  4
    ...
    // Intersection
    // ----------------------------------------------------------------------------
    cout << "(CAAGsiVolumeFormFeatures) Intersection " << endl;
    CATISpecObject_var spSpecExtr4 = ...
    CATISpecObject_var spSpecExtr5 = ...

    CATISpecObject_var spSpecInt = spBoolPrtFact -> CreateIntersect ( spSpecExtr4,spSpecExtr5 ,BOOLEAN_OPE_ON_VOLUME ) ;
    CAAGsiObjectUpdate(spSpecInt) ;

---

[Top]
#### Save and close session

Save part and close the session

    ...
    // save
Save part and close the session
    if (NULL != OutputName )      {
```vbscript
```cpp
        rc = CATDocumentServices::SaveAs  (*pDoc, OutputName );
        if (SUCCEEDED(rc))   {
```

```

                cout << "(CAAGsiVolumeBooleanOpe) Document saved " << endl;

         }
```vbscript
if (NULL != OutputName )      {
```vbscript
```cpp
rc = CATDocumentServices::SaveAs  (*pDoc, OutputName );
if (SUCCEEDED(rc))   {
```

```

cout << "(CAAGsiVolumeBooleanOpe) Document saved " << endl;
         else {
                cout << "ERROR in saving document" << endl ;
```

         }
    }
    // Closes the document
else {
cout << "ERROR in saving document" << endl ;
    CATDocumentServices::Remove(*pDoc);

    // Ends session and drops document
    Delete_Session("SampleSession");
    ...

---

[Top]

* * *
### In Short

This use case has demonstrated the way to perform boolean operation on volume thanks to part design boolean factory. resulting feature add, remove , intersect and Union-Trin are inserted in GS or OGS When then are inserted in OGS the boolean operation are 'absorbant' features

We illustrate feature in this use case boolean operation that do not have BRep feature as input . Operations that required BRep feature in input (Ex: Union-Trim) the use of boolean operation interface is similar as presented in the sample.

Note : The BRep features are retrieved in interactive commands through in selecting of sub-element and using Mechanical Modeler agent (Ex:CATFeatureImportAgent)

Union-Trim

Note : The BRep features are retrieved in interactive commands through in selecting of sub-element and using Mechanical Modeler agent CATFeatureImportAgent

[Top]

* * *
### References

[1] |  [ Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] |  [ About Generative Shape Design Features](../CAAGsiTechArticles/CAAGsiShapeDesignFeature.md)
[3] |  [ Inserting a Shape Design Feature in the procedural view ](../CAAGsiTechArticles/CAAGsiInsertInProceduralView.md)
[4] | [ Updating a shape Design feature ](../CAAGsiTechArticles/CAAGsiUpdateShapeDesign.md)
[Top]

* * *
### History

Version: **1** [May 2004] | Document created
---|---
[Top]

* * *

_Copyright 2004, Dassault Systmes. All rights reserved._
