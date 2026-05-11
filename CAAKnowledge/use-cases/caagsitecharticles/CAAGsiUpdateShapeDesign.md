---
```vbscript
title: "Updating Shape Design Features"
category: "technical article"
module: "CAAGsiTechArticles"
tags: ["CAAGSMInterfaces", "CATIPrtPart", "CAAGsiNozzle", "CATIGSMTool", "CAAAGsiService", "CAAGsiService", "CAAGsiServices", "CATIAV5", "CAAGsiObjectUpdate", "CATISpecObject_var"]
source_file: "Doc/online/CAAGsiTechArticles/CAAGsiUpdateShapeDesign.htm"
converted: "2026-05-11T17:31:50.677519"
```

---
# Shape Design& Styling

| 
## Generative Shape Design

| 
### Updating Shape Design Features

_Update and check linearity for Shape Design features_  
---|---|---  
Technical Article  

* * *
### Abstract

This article discusses the CAAGsiObjectUpdate service.

  * **What is new in the update of Shape Design feature**
    * The CAAGsiObjectUpdate service of CAAAGsiService.h header - Update Shape Design features
    * Where to Find the CAAGsiServices Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---  

* * *
### What is new in the update of Shape Design features 

Shape Design features can now be inserted in Body, OGS and GS.  
Body and OGS are new set of features in which shape design features can be inserted   
They proposed enhanced mechanisms for feature (Absorbed main input, Current feature for Shapes ) that required additional actions at update for feature in Body and OGS context (GS is the former "Ooen Body") 

### The CAAGsiObjectUpdate Service of CAAGsiService,h header - Update Shape Design features 

Shape Design features can now be inserted in Body, OGS and GS.
Body and OGS are new set of features in which shape design features can be inserted
They proposed enhanced mechanisms for feature (Absorbed main input, Current feature for Shapes ) that required additional actions at update for feature in Body and OGS context (GS is the former "Ooen Body")
CAAGsiServices encapsulates generic sequences of code.   
CAAGsiObjectUpdate is an update method available for Shape Design features, Part Design features to be used when features are inserted in Body, OGS and GS 

[Top]
#### Where to Find the CAAGsiServices Code

CAAGsiObjectUpdate is an update method available for Shape Design features, Part Design features to be used when features are inserted in Body, OGS and GS
The CAAGsiServices header export a list of self-contain tools , is located in PublicInterfaces of CAAGSMInterfaces.edu and is implements in the CAAGsiServices.m module of the CAAGSMInterfaces.edu framework:

Windows | `InstallRootDirectory\CAAGSMInterfaces.edu\CAAGsiServices.m\`  

The CAAGsiServices header export a list of self-contain tools , is located in PublicInterfaces of CAAGSMInterfaces.edu and is implements in the CAAGsiServices.m module of the CAAGSMInterfaces.edu framework:
Windows | `InstallRootDirectory\CAAGSMInterfaces.edu\CAAGsiServices.m\`
Unix | `InstallRootDirectory/CAAGSMInterfaces.edu/CAAGsiServices.m/`  

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
CAAGsiServices , CAAGsiObjectUpdate Step by Step 

  1. Use standard Mechanical Modeler Update on feature 
  2. Check insert location set and manage linearity if needed 

[Top]

* * *
#### Use standard Mechanical Modeler Update on feature

Mechanical Modeler update standard mechanism 

    // Update 
    // ---------------------------------------------------------------------------
Mechanical Modeler update standard mechanism
    ExportedByCAAGsiServices HRESULT 
    CAAGsiObjectUpdate(const CATISpecObject_var & ispSpec)

    {
       ... 
ExportedByCAAGsiServices HRESULT
CAAGsiObjectUpdate(const CATISpecObject_var & ispSpec)
       HRESULT rc = S_OK ; 
       CATTry { 
        iStat = ispSpec -> Update();

        ...
        }
       // This block is specific for Update Errors
CATTry {
iStat = ispSpec -> Update();
       CATCatch(CATMfErrUpdate,error) {
           cerr << " Update Error: " << (error-> GetDiagnostic()).ConvertToChar() << endl; 
           return E_FAIL; 

       } 
       // This block treats every other exception
```vbscript
CATCatch(CATMfErrUpdate,error) {
cerr << " Update Error: " << (error-> GetDiagnostic()).ConvertToChar() << endl;
return E_FAIL;
       CATCatch(CATError,error) {
           cerr << " Error: " << (error->GetMessageText()).ConvertToChar() << endl; 
           return E_FAIL; 
```

       }
```vbscript
CATCatch(CATError,error) {
cerr << " Error: " << (error->GetMessageText()).ConvertToChar() << endl;
return E_FAIL;
       CATEndTry;
       return rc ; 
```

    }

---  
#### Check insert location set and manage linearity if needed 

To be done after feature update 

    ...
    // check Linearity / useful for absorbent feature inserted in OGS 
To be done after feature update
    CATISpecObject_var spFather = ispSpec->GetFather();
    if ( NULL_var != spFather )

    {
CATISpecObject_var spFather = ispSpec->GetFather();
if ( NULL_var != spFather )
       spFather -> Release();
       CATIGSMTool *piGSMToolFather = NULL;
       rc =spFather->QueryInterface ( IID_CATIGSMTool, (void**)&piGSMToolFather);
       if ( SUCCEEDED(rc) ) { 
         int IsAnAbsorbantSet = -1 ;
         piGSMToolFather->GetType(IsAnbsorbantSet) ;
         if ( 1 == IsAnAbsorbantSet ) {
            CATBaseUnknown_var spUnkwnSpec = ispSpec;
            rc = CATMmrLinearBodyServices::Insert(spUnkwnSpec) ; 

        } 
piGSMToolFather->GetType(IsAnbsorbantSet) ;
if ( 1 == IsAnAbsorbantSet ) {
CATBaseUnknown_var spUnkwnSpec = ispSpec;
rc = CATMmrLinearBodyServices::Insert(spUnkwnSpec) ;
       piGSMToolFather->Release() ; piGSMToolFather=NULL; 

    }
    ... 

---  

Most of the case, it is recommended in applicative code to call afterwards SetCurrentFeature method of CATIPrtPart Interface on the just updated object : in CATIAV5 interactive function : Object just created or just edited are set as current (Body and OGS) 

* * *
### In Short

This service demonstrated how to implement absorbent mechanism at feature update for shape design and part design features inserted in Body and/or OGS 

[Top]
### References

[1] | [About Generative Shape Design Features](CAAGsiShapeDesignFeature.md)  
---|---  
[2] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)  
[3] | [Creating an Open Body](CAAGsiCreateGSMTool.md)  
[4] | [CAAGsiNozzle Use case](../CAAGsiUseCases/CAAGsiNozzleSample.md)  
[Top]  

* * *
### History

Version: **1** [May 2004] | Document created  
---|---  
[Top]  

* * *

_Copyright 2004, Dassault Systmes. All rights reserved._
