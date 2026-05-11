---
```vbscript
title: "Creating Volume Form Features"
category: "use case"
module: "CAAGsiUseCases"
tags: ["CATIGSMProceduralView_var", "CATICkeParm_var", "CATIPrtBooleanFactory", "CATIPrtContainer", "CATIGSMSweepUnspec_var", "CAAGsiVolumeFormFeature", "CAAGSMInterfaces", "CAAGsiVolumeFormFeatures", "CATIMf3DBehavior2", "CATIGSMFactory", "CATIPrtFactory", "CATIGSMProceduralView", "CATIGSMExtrude_var", "CATIPrtFactory_var", "CATIPrtPart_var", "CAAGsiObjectUpdate", "CAAGsiStartVolume", "CATISpecObject_var", "CATIGSMLoft_var", "CATInit"]
source_file: "Doc/online/CAAGsiUseCases/CAAGsiVolumeFormFeatures.htm"
converted: "2026-05-11T17:31:50.653046"
```

---
# Shape Design & Styling

| 
## Generative Shape Design

| 
### Creating Volume Form Features

_Using the Shape Design and the Part Design factories, create volume form features_  
---|---|---  
Use Case  

* * *
### Abstract

This article discusses the CAAGsiVolumeFormFeatures use case. This use case explains how to create volume shape features. 

  * **What You Will Learn With This Use Case**
  * **The CAAGsiVolumeFormFeatures Use Case**
    * What Does CAAGsiVolumeFormFeatures Do
    * How to Launch CAAGsiVolumeFormFeatures
    * Where to Find the CAAGsiVolumeFormFeatures Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---  

* * *
### What You Will You Learn With This Use Case

This use case shows how to use shape design and part design factories to create volumes. The volume features can be created in Shape Design factory or in Part Design factory.  
**Note** : Creations of volumes feature are licensed by the GSO Product.

>   * Shape Design Extrude, Revolve, MultiSections volumes, Sweep volumes.
>   * Part Design Closed Volumes, Thick volumes, Draft, Draft Angle, Draft ReflectLine, Sew Volumes, and Shell.
> 

### The CAAGsiVolumeFormFeatures Use Case

CAAGsiVolumeFormFeatures is a use case of the CAAGSMInterfaces.edu framework that illustrates creation of volumes using Shape Design and Part Design   
(Extrude, Revol, Thick, Close, Multi-Sections Volume, and Sweep). 

![](images/CAAGsiVolumeForms.jpg)
#### What Does CAAGsiVolumeFormFeatures Do

(Extrude, Revol, Thick, Close, Multi-Sections Volume, and Sweep).
The goal of CAAGsiVolumeFormFeatures is to illustrate how to create volume either using shape design factory or part design factory.   
Volume features are surfacic features they answer to the TRUE to the IsAShape() method of CATMf3DBehavior, and also answer TRUE to the IsAVolume() method of CATIMf3DBehavior2   
Volume features can only be inserted in the procedural view in Geometrical Set (GS) or Ordered Geometrical Set (OGS) 

Volume created using shape design factory (CATIGSMFactory) 

>   * Volume created from shape design factory are extension on the corresponding surface feature , the creation method are teh same the CAA user just have to use the SetContext methods of the corresponding interface feature to specify the type surfacic or volume result. 
>   * Volume case: The Input has to be a closed  wire(Ex: Profile to extrude)  or a surface (Ex: Shape to extrude  . eitherwise a error is returned when volume is  updated 
>   * Once created the volume have to be insert in the procedural view using the CATIGSMProceduralView Interfaces, if the current tool is a body, automatically an OGS will be create in the Body to insert the volume underneath 
> 

Volume created using part design factory (CATIPrtFactory or CATIPrtBooleanFactory) 

>   * Part Design factories  propose dedicated methods to create volume feature (ex: CreateVolumicCloseSurface.), 
>   * Part design factory volumes methods automatically insert resulting feature in the procedural view at creation , the feature just have then to be updated ,if the current tool is a body, automatically an OGS will be create in the Body to insert the volume underneath. The CAAGsiObjectUpdate service can be used 
> 

[Top]
#### How to Launch CAAGsiVolumeFormFeatures

To launch CAAGsiVolumeFormFeatures, you will need to set up the build time environment, then compile CAAGsiVolumeFormFeatures along with its prerequisites, and set up the run time environment, and then execute the use case [1].

Launch the use case as follows: 

  * With Windows 

        e/CAAGsiVolumeFormFeatures InstallDir\CAAGSMInterfaces.edu\Data.d\CAAGsiStartVolume.CATPart outputDirectory\CAAGsiVolumeFormFeatures.CATPart  

---  
  * With UNIX 

        \CAAGsiVolumeFormFeatures InstallDir\CAAGSMInterfaces.edu\Data.d\CAAGsiStartVolume.CATPart outputDirectory/CAAGsiVolumeFormFeatures.CATPart  

---  

where:

`inputDirectory` | The directory into which `CAAGsiStartVolume.CATPart is found `  
---|---  
`outputDirectory` | The directory into which `CAAGsiVolumeFormFeatures.CATPart is saved`  
`CAAGsiVolumeFormFeatures.CATPart` | The file that contains the part created with the datum surface t  

[Top]
#### Where to Find the CAAGsiVolumeFormFeatures Code

The CAAGsiVolumeFormFeatures use case is made of main program located in the CAAGsiVolumeFormFeatures.m module of the CAAGSMInterfaces.edu framework:

The CAAGsiVolumeFormFeatures use case is made of main program located in the CAAGsiVolumeFormFeatures.m module of the CAAGSMInterfaces.edu framework:
Windows | ` InstallRootDirectory\CAAGSMInterfaces.edu\CAAGsiVolumeFormFeatures.m\`  

The CAAGsiVolumeFormFeatures use case is made of main program located in the CAAGsiVolumeFormFeatures.m module of the CAAGSMInterfaces.edu framework:
Windows | ` InstallRootDirectory\CAAGSMInterfaces.edu\CAAGsiVolumeFormFeatures.m\`
Unix | ` InstallRootDirectory/CAAGSMInterfaces.edu/CAAGsiVolumeFormFeatures.m/`  

The input CAAGsiStartVolume.CATPart is proposed in Data.d directory of CAAGSMInterfaces.edu 

Windows | ` InstallRootDirectory\CAAGSMInterfaces.edu\Data.d\CAAGsiStartVolume.CATPart `  

The input CAAGsiStartVolume.CATPart is proposed in Data.d directory of CAAGSMInterfaces.edu
Windows | ` InstallRootDirectory\CAAGSMInterfaces.edu\Data.d\CAAGsiStartVolume.CATPart `
Unix | ` InstallRootDirectory/CAAGSMInterfaces.edu/Data.d/CAAGsiStartVolume.CATPart`  

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
There are eight logical step in CAAGsiVolumeFormFeatures: 

  1. Prolog
  2. Create extrude volume feature
  3. Create revol volume feature
  4. Create a mutli-section volume
  5. Create a volume sweep feature
  6. Create a volume close featureume
  7. Create a volume thick feature
  8. Save and close session

We will now comment each of those sections by looking at the code of the main method of file CAAGsiVolumeFormFeatures.

[Top]
#### Prolog

We will now comment each of those sections by looking at the code of the main method of file CAAGsiVolumeFormFeatures.
CAAGsiVolumeFormFeatures sample first creates a session and opens the input CATPart. 

Note: The important feature of the following sequence of code consists in the required call to the GetPart() method of the CATPrtContainer interfaces. This method allow to load in session the different containers of the part 

    ....
    // creates a session
Note: The important feature of the following sequence of code consists in the required call to the GetPart() method of the CATPrtContainer interfaces. This method allow to load in session the different containers of the part
    char *pSessionName = "SampleSession";
    CATSession *pSession = NULL; 
    rc = Create_Session(pSessionName, pSession); 
    if (NULL == pSession ) {
       cout << "(CAAGsiVolumeFormFeatures) ERROR: Create_Session" << endl  ;
       TestCaseError = 1 ;

    }

    // loads the document and initializes it
cout << "(CAAGsiVolumeFormFeatures) ERROR: Create_Session" << endl  ;
TestCaseError = 1 ;
    cout << "The input document " << InputName << " is opened" << endl ;
    CATDocument *pDoc = NULL; 
    rc =CATDocumentServices::OpenDocument(InputName, pDoc) ;

    if (NULL == pDoc ) {
       cout << "(CAAGsiVolumeFormFeatures) ERROR CATDocumentServices::OpenDocument" << endl  ;
       TestCaseError = 2 ;

    }

    // Part Container 
cout << "(CAAGsiVolumeFormFeatures) ERROR CATDocumentServices::OpenDocument" << endl  ;
TestCaseError = 2 ;
    CATIPrtContainer *piPartContainer = NULL ; 
    CATIPrtPart_var spPrtPart; 

    if ( NULL != pDoc ) { 

       // queries on the document to get the root container
CATIPrtContainer *piPartContainer = NULL ;
CATIPrtPart_var spPrtPart;
if ( NULL != pDoc ) {
       CATInit *pDocAsInit = NULL; 
       pDoc->QueryInterface(IID_CATInit, (void**)&pDocAsInit) ; 
       if ( NULL != pDocAsInit ) {

        // Extracts from document a reference to its part in hPartAsRequest
CATInit *pDocAsInit = NULL;
pDoc->QueryInterface(IID_CATInit, (void**)&pDocAsInit) ;
if ( NULL != pDocAsInit ) {
       piPartContainer = 
          (CATIPrtContainer*)pDocAsInit->GetRootContainer("CATIPrtContainer");
       pDocAsInit->Release(); pDocAsInit = NULL ;

       if( NULL != piPartContainer ) {
          CATISpecObject_var spPart = piPartContainer->GetPart() ; 
          spPrtPart = spPart ;

       } 
    } 
    ...

---  

Then in the initilization phasis the wireframe and shape design and Part Design factory are retrieved. . 

    ....
    // Retrieve the Generative Shape Design Factory Interface 
Then in the initilization phasis the wireframe and shape design and Part Design factory are retrieved. .
    CATIPrtFactory_var spPrtFact; 
    CATIGSMFactory_var spGsmFact; 
    if ( NULL !=piPartContainer ) { 
       CATIGSMFactory * _pFact =NULL; 
       rc = piPartContainer -> QueryInterface(IID_CATIGSMFactory ,(void**)&_pFact);
       if (SUCCEEDED(rc) ) {
         spGsmFact = _pFact;
         if (_pFact) _pFact -> Release(); _pFact = NULL; 

      }

      // Retrieve the Part Design factory Interface 
spGsmFact = _pFact;
if (_pFact) _pFact -> Release(); _pFact = NULL;
       CATIPrtFactory * _pPrtFact =NULL;
       rc = piPartContainer -> QueryInterface(IID_CATIPrtFactory ,(void**)&_pPrtFact); 
       if (SUCCEEDED(rc) ) { 
            spPrtFact = _pPrtFact;
           if (_pPrtFact) _pPrtFact ->Release(); _pPrtFact = NULL;

         } 
       }
    } ....

---  

[Top]
#### Create extrude volume feature 

Create extrude volume using CreateExtrude method of CATIGSMFactory

    ....
    #include "CATGSMContextDef.h"
    ....
    // Create Volume Extrude
    CATISpecObject_var SpecSkethToExtrude = ...;
CATISpecObject_var SpecSkethToExtrude = ...;
    CATISpecObject_var SpecPlaneRef1 = ...;

    CATICkeParm_var spCkeLgStart ;
    spCkeLgStart = spCkeFact -> CreateLength( "Start" ,0.0/1000.);
    if (NULL_var == spCkeLgStart) {
         cout << "ERROR in creating Cke length paramater" << endl;

    }
CATICkeParm_var spCkeLgStart ;
spCkeLgStart = spCkeFact -> CreateLength( "Start" ,0.0/1000.);
if (NULL_var == spCkeLgStart) {
cout << "ERROR in creating Cke length paramater" << endl;
    CATICkeParm_var spCkeLgEnd ;
    spCkeLgEnd = spCkeFact -> CreateLength( "End" ,100.0/1000.);
    if (NULL_var == spCkeLgEnd) {
       cout << " ERROR in creating Cke length paramater" << endl;

    }
CATICkeParm_var spCkeLgEnd ;
spCkeLgEnd = spCkeFact -> CreateLength( "End" ,100.0/1000.);
if (NULL_var == spCkeLgEnd) {
cout << " ERROR in creating Cke length paramater" << endl;
    DirRef =spGsmFact -> CreateDirection ( SpecPlaneRef1);

    // Create Extrude
cout << " ERROR in creating Cke length paramater" << endl;
DirRef =spGsmFact -> CreateDirection ( SpecPlaneRef1);
    CATIGSMExtrude_var spExtrude1 = spGsmFact -> CreateExtrude ( SpecSkethToExtrude , DirRef , spCkeLgStart,spCkeLgEnd, TRUE) ;

    //Initialize volume Context
    spExtrude1 -> SetContext(CATGSMVolumeCtxt) ;

    // Insert in procedural view and Update
spExtrude1 -> SetContext(CATGSMVolumeCtxt) ;
    CATISpecObject_var spSpecExtr1 = spExtrude1 ;
    if (NULL_var != spSpecExtr1) {
       CATIGSMProceduralView_var ispProcView = spSpecExtr1;
       if (NULL_var != ispProcView ) {
          rc = ispProcView ->InsertInProceduralView();

       }
    }
CATIGSMProceduralView_var ispProcView = spSpecExtr1;
if (NULL_var != ispProcView ) {
rc = ispProcView ->InsertInProceduralView();
    CAAGsiObjectUpdate(spSpecExtr1) ;

    ...

---  

[Top]
#### Create revolve volume feature 

Create revolve volume using CreateRevol method of CATIGSMFactory

    ....
    #include "CATGSMContextDef.h"
    ....
    // Create Volume revolve
    CATISpecObject_var SpecSkethToRevol = ...;
CATISpecObject_var SpecSkethToRevol = ...;
    CATISpecObject_var SpecLineRef1 = ...;

    CATICkeParm_var spCkeAngStart ;
    spCkeAngStart = spCkeFact -> CreateLength( "Ang1" ,(180.0/180.0)*CATPI);
    if (NULL_var == spCkeAngStart) {
           cout << "ERROR in creating Cke angle paramater"

    << endl ;
    }
```vbscript
spCkeAngStart = spCkeFact -> CreateLength( "Ang1" ,(180.0/180.0)*CATPI);
if (NULL_var == spCkeAngStart) {
cout << "ERROR in creating Cke angle paramater"
    CATICkeParm_var spCkeAngEnd;
    spCkeAngEnd = spCkeFact -> CreateLength( "Ang2" ,(180.0/180.)*CATPI);
    if (NULL_var == spCkeAngEnd) {
           cout << "ERROR in creating Cke angle paramater"
```

    << endl ;
    }

```vbscript
if (NULL_var == spCkeAngEnd) {
cout << "ERROR in creating Cke angle paramater"
    CATIGSMRevol_var spRevol1 =
           spGsmFact -> CreateRevol (SpecSkethToRevol, SpecLineRef1 , spCkeAngStart, spCkeAngEnd , FALSE);

```

    //Initialize volume Context
CATIGSMRevol_var spRevol1 =
spGsmFact -> CreateRevol (SpecSkethToRevol, SpecLineRef1 , spCkeAngStart, spCkeAngEnd , FALSE);
    spRevol1 -> SetContext(CATGSMVolumeCtxt) ;

    // Insert in procedural view and Update
spRevol1 -> SetContext(CATGSMVolumeCtxt) ;
    CATISpecObject_var spSpecRevol1 = spRevol1 ;
    if (NULL_var != spSpecRevol1 ) {
       CATIGSMProceduralView_var ispProcView = spSpecRevol1 ;
       if (NULL_var != ispProcView ) {
          rc = ispProcView ->InsertInProceduralView();

        }
    }
CATIGSMProceduralView_var ispProcView = spSpecRevol1 ;
if (NULL_var != ispProcView ) {
rc = ispProcView ->InsertInProceduralView();
    CAAGsiObjectUpdate(spSpecRevol1 ) ;

    ...

---  

[Top]
#### Create multi-sections volume feature 

Create multi-sections volume using CreateLoft method of CATIGSMFactory

    ....
    #include "CATGSMContextDef.h"
    ....
    // Create Multi Section volume
    CATISpecObject_var SpecSection;
    SpecSection = ... ;spListSections.Append(SpecSection);
    SpecSection = ... ;spListSections.Append(SpecSection);
    SpecSection = ... ;spListSections.Append(SpecSection);
    SpecSection = ... ;spListSections.Append(SpecSection);

    CATListValCATISpecObject_var	spListGuides;
    CATISpecObject_var SpecGuide;
    SpecGuide = ... ;spListGuides.Append(SpecGuide);
    SpecGuide = ... ;spListGuides.Append(SpecGuide);
    SpecGuide = ... ;spListGuides.Append(SpecGuide);
    SpecGuide = ... ;spListGuides.Append(SpecGuide);

    CATIGSMLoft_var spLoft1 =
    spGsmFact -> CreateLoft (spListSections,spListGuides);

    //Initialize volume Context
CATIGSMLoft_var spLoft1 =
spGsmFact -> CreateLoft (spListSections,spListGuides);
    spLoft1 -> SetContext(CATGSMVolumeCtxt) ;

    // Insert in procedural view and Update
spLoft1 -> SetContext(CATGSMVolumeCtxt) ;
    CATISpecObject_var spSpecLoft1 = spLoft1 ;
    if (NULL_var != spSpecLoft1 ) {
       CATIGSMProceduralView_var ispProcView = spSpecLoft1 ;
       if (NULL_var != ispProcView ) {
          rc = ispProcView ->InsertInProceduralView();

       }
    }
CATIGSMProceduralView_var ispProcView = spSpecLoft1 ;
if (NULL_var != ispProcView ) {
rc = ispProcView ->InsertInProceduralView();
    CAAGsiObjectUpdate(spSpecLoft1 ) ;

    ...

---  

[Top]
#### Create volume sweep feature 

Create volume sweep using CreateSweep method of CATIGSMFactory

    ....
    #include "CATGSMContextDef.h"
    ....
    // Create Multi Section volume
    CATISpecObject_var SpecProfile = ...
    CATISpecObject_var SpecGuideSw = ...
    CATISpecObject_var SpecSpine = ....

    CATIGSMSweepUnspec_var spExplSweep1 =
    spGsmFact -> CreateExplicitSweep(SpecGuideSw,SpecProfile,SpecSpine,NULL_var , NULL_var );

    //Initialize volume Context
CATIGSMSweepUnspec_var spExplSweep1 =
spGsmFact -> CreateExplicitSweep(SpecGuideSw,SpecProfile,SpecSpine,NULL_var , NULL_var );
    spExplSweep1 -> SetContext(CATGSMVolumeCtxt) ;

    // Insert in procedural view and Update
spExplSweep1 -> SetContext(CATGSMVolumeCtxt) ;
    CATISpecObject_var spSpecSweep1 = spExplSweep1 ;
    if (NULL_var != spSpecSweep1 ) {
     CATIGSMProceduralView_var ispProcView = spSpecSweep1 ;
     if (NULL_var != ispProcView ) {
     rc = ispProcView ->InsertInProceduralView();

     }
    }
CATIGSMProceduralView_var ispProcView = spSpecSweep1 ;
if (NULL_var != ispProcView ) {
rc = ispProcView ->InsertInProceduralView();
    CAAGsiObjectUpdate(spSpecSweep1 ) ;

    ...

---  

[Top]
#### Create volume thick feature 

Create volume thick using CreateVolumicOffset method of CATIPrtFactory

Note: Insert in procedural view is done at creation under the current geometrical feature set 

    // Create and Insert in procedural view volume Thick
Note: Insert in procedural view is done at creation under the current geometrical feature set
    CATISpecObject_var SpecShape = ...
    CATPrtOffsetSens iIsensOffset = NormalSide;
    CATISpecObject_var spThick =
    spPrtFact -> CreateVolumicOffset (SpecShape, iIsensOffset,0.00, 10.00);

    // Update
CATPrtOffsetSens iIsensOffset = NormalSide;
CATISpecObject_var spThick =
spPrtFact -> CreateVolumicOffset (SpecShape, iIsensOffset,0.00, 10.00);
    CAAGsiObjectUpdate(spThick) ;

    ...

---  

[Top]
#### Create volume close feature 

Create volume close using CreateVolumicCloseSurface method of CATIPrtFactory

Note: Insert in procedural view is done at creation under the current geometrical feature set 

    // Create and Insert in procedural view volume close
Note: Insert in procedural view is done at creation under the current geometrical feature set
    CATISpecObject_var SpecShapeToClose = ...
    CATISpecObject_var spClose =
    spPrtFact -> CreateVolumicCloseSurface (SpecShapeToClose);

    // Update
CATISpecObject_var SpecShapeToClose = ...
CATISpecObject_var spClose =
spPrtFact -> CreateVolumicCloseSurface (SpecShapeToClose);
    CAAGsiObjectUpdate(spClose) ;

    ...

---  

[Top]
#### Save and close session 

Save part and close the session 

    ...
    // save
Save part and close the session
    if (NULL != OutputName ) {
       rc = CATDocumentServices::SaveAs (*pDoc, OutputName );
       if (SUCCEEDED(rc)) {
        cout << " (CAAGsiVolumeFormFeature) Document saved " << endl;

       }
```vbscript
if (NULL != OutputName ) {
rc = CATDocumentServices::SaveAs (*pDoc, OutputName );
if (SUCCEEDED(rc)) {
cout << " (CAAGsiVolumeFormFeature) Document saved " << endl;
       else {
          cout << " ERROR in saving document" << endl;
```

       }
    }
    // Closes the document
else {
cout << " ERROR in saving document" << endl;
    CATDocumentServices::Remove(*pDoc);

    // Ends session and drops document	
    Delete_Session("SampleSession");
    ...

---  

[Top]

* * *
### In Short

This use case has demonstrated the way to create a volume features thanks to shape design and part design. 

We illustrate feature in this use case volume feature that do not have BRep feature as input . Creation of features that required BRep as input (Ex: Shell, volume sew ,Draft,.. -mainly in Part Design feature - ) the creation and access to parameters is similar as presented in the sample . 

This use case has demonstrated the way to create a volume features thanks to shape design and part design.
We illustrate feature in this use case volume feature that do not have BRep feature as input . Creation of features that required BRep as input (Ex: Shell, volume sew ,Draft,.. -mainly in Part Design feature - ) the creation and access to parameters is similar as presented in the sample .
Note : The BRep features are retrieved in interactive commands through in selecting of sub-element and using Mechanical Modeler agent CATFeatureImportAgent 

[Top]

* * *
### References

[1] |  [ Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] |  [ About Generative Shape Design Features](../CAAGsiTechArticles/CAAGsiShapeDesignFeature.md)  
[3] |  [ Inserting a Shape Design Feature in the procedural view](../CAAGsiTechArticles/CAAGsiInsertInProceduralView.md)  
[4] | [ Updating a shape Design feature ](../CAAGsiTechArticles/CAAGsiUpdateShapeDesign.md)  
[Top]  

* * *
### History

Version: **1** [May 2004] | Document created  
---|---  
[Top]  

* * *

_Copyright 2004, Dassault Systmes. All rights reserved._
