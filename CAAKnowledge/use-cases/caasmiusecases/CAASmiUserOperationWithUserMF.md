---
title: "Untitled"
category: "use-case"
module: "CAASmiUseCases"
tags: ["CATISmgNcGeometryParameter", "CAASmiTechArticles", "CAASmiUserOperationWithUserMF", "CATISmgNcGeometryManager_var", "CAADocStyleSheets", "CAASurfaceMachiningItf", "CAASmiUserOperationGeometrySelCom", "CATIMfgActivity", "CATIMfgGeometryActivity", "CAASmgGuide", "CAASmiOperationSampleOverview", "CATISmgFactory", "CAASmiOperationWithuserMFPanel", "CAASmiUserOperationGeomUI", "CATISmgNcGeometryManager", "CAASmiUserOperationWithUserMFToolPath", "CAADocRunSample", "CATIMfgViewAccess", "CAAManufacturing", "CAADocUseCases"]
source_file: "Doc/online/CAASmiUseCases/CAASmiUserOperationWithUserMF.htm"
converted: "2026-05-11T11:06:32.975965"
---

# Machining
 
 
## 3 Axis Surface Machining
 
 
### []Managing Geometry with User Machining Features
 *Customize the geometry tab page of a surface machining operation with
 user machining features*
 
 
 |Use Case
 

---

 
 
### Abstract
 

This article discusses the CAASmiUserOperationWithUserMF use case. It
 explains how to customize the default geometry tab page of a surface
 machining operation to be able to select geometry through an user
 machining feature's geometry attribute.
 

This paper accompanies the first scenario of *Surface Machining
 Operation Sample* [[1]].
 

 
- [**What You Will Learn With This Use Case**]
 
- [**The CAASmiUserOperationWithUserMF Use
 Case**]
 

 
- [What Does CAASmiUserOperationWithUserMF Do]
 
- [How to Launch CAASmiUserOperationWithUserMF]
 
- [Where to Find the CAASmiUserOperationWithUserMF
 Code]
 
 
- [**Step-by-Step**]
 
- **[In Short]**
 
- **[References]**
 
 
 

---

### []What You Will Learn With This Use Case

This use case is intended to help you to manage geometry of a surface
machining operation with a machining feature geometry attribute.

More specifically, the CAASmiUserOperationWithUserMF Use Case shows how to:

 
- Overload the geometry tab page of a surface machining operation.
 
- Create a new machining feature.
 
- Connect a machining feature with a surface machining operation.
 
- Manage geometry selection of surface machining geometry attributes.

[[Top]]

### []The CAASmiUserOperationWithUserMF Use Case

CAASmiUserOperationWithUserMF is a use case of the CAASurfaceMachiningItf.edu
framework that illustrates Surface Machining capabilities. It is a part of the
sample described in the technical article [[1]].

[[Top]]

#### []What Does CAASmiUserOperationWithUserMF Do

This use case customizes the default geometry tab page of **CAASmgOperation**.

CAASmgOperation** **is associated with a new machining feature: **CAASmgMachiningFeature**.

CAASmgMachiningFeature has a geometry attribute : **CAASmgGuide**. This
parameter can support manufacturing geometries or nc geometry features.

The geometry management is done by several functionalities:

 
 |![](images/CAASmiOperationWithuserMFPanel.jpg)
 |Description of functionalities illustrated:
 

 
- *Select a curve* : select an edge with the edge selection
 toolbar.
 
- *Select a set of curves* : select a NC Geometry Feature of
 edges.
 
- *Remove all* : remove selection.
 
- *Add a empty set* : create an empty NC Geometry Feature of
 edges.
 
- *Export curves in a new set* : create an NC Geometry Feature
 with the edges previously selected.
 
 
 

[[Top]]

#### []How to Launch CAASmiUserOperationWithUserMF

This use case is a part of *Surface Machining Operation Sample* [[1]].
You should build all the modules of this sample at a time to be able to launch
it [[2]].

Don't forget to edit the interface dictionary located in:

 
 |Windows
 |`InstallRootDirectory\CAASurfaceMachiningItf.edu\CNext\code\dictionary\`
 
 
 |Unix
 |`InstallRootDirectory/CAASurfaceMachiningItf.edu/CNext/code/dictionary/`
 

where `InstallRootDirectory` is the directory where the CAA CD-ROM
is installed, and uncomment the appropriate lines by removing the '#' character.

[[Top]]

#### []Where to Find the CAASmiUserOperationWithUserMF Code

This use case is made of source files located in the
CAASmiUserOperationGeomUI.m module of the CAASurfaceMachiningItf.edu framework :

 
 |Windows
 |`InstallRootDirectory\CAASurfaceMachiningItf.edu\CAASmiUserOperationGeomUI.m`
 
 
 |Unix
 |`InstallRootDirectory/CAASurfaceMachiningItf.edu/CAASmiUserOperationGeomUI.m`
 

where `InstallRootDirectory` is the directory where the CAA CD-ROM
is installed.

[[Top]]

### []Step-by-Step

CAASmiUserOperationWithUserMF is divided into the following steps:

 
- Implementing CATIMfgGeometryActivity:
 

 
- [Declaring CATIMfgGeometryActivity Implementation]
 
- [Coding GetMainPanelEditor]
 
- [Creating a New Machining Feature
 CAASmgMachiningFeature]
 
 
 
- Creating the geometry dialog frame:
 

 
- [Geometry Management: Coding SelectCurve]
 
- [Geometry Management: Coding SelectZone]
 
- [Geometry Management: Coding RemoveAll]
 
- [Geometry Management: Coding NewZone]
 
- [Geometry Management: Coding Export]
 
 

We now comment each of those sections by looking at the code.

[[Top]]

#### []Declaring CATIMfgGeometryActivity Implementation

To overload the geometry tab page, we should create an extension class that
will implement *CATIMfgGeometryActivity*:

 
 
```
...
 // Tie the implementation to its interface
 #include "TIE_CATIMfgGeometryActivity.h"
 TIE_CATIMfgGeometryActivity( CAAESmiUserOperationGeometryEditor);
 ...
```

 
 

[[Top]]

#### []Coding GetMainPanelEditor

In *GetMainPanelEditor, *we create a new **CAASmgMachiningFeature**
and we associate it with **CAASmgOperation**. Then we call the geometry
dialog frame described below.

 
 
```
...
 // Associates a machining feature
 CATIMfgActivity * pActivity = NULL;
 oRC = QueryInterface(IID_CATIMfgActivity, (void**) &pActivity);
 if (SUCCEEDED(oRC))
 {
 spMachFeature = pActivity->GetFeature(); 
 if (NULL_var == spMachFeature)
 {
 // Create a user machining feature
 oRC = CreateCAAMachiningFeature(spMachFeature);
 if (SUCCEEDED(oRC))
 {
 // Link the machining feature to the activity
 pActivity->SetFeature(spMachFeature);
 }
 }
 pActivity->Release();
 pActivity = NULL;
 }

 // Creates the frame
 oFrame = new CAASmiUserOperationGeometryPanel(iFather,spMachFeature);
 ...
```

 
 

[[Top]]

#### []Creating a New Machining Feature CAASmgMachiningFeature

The *CreateCAAMachiningFeature* method is used to create **CAASmgMachiningFeature**.

At first, we retrieve the startup of **CAASmgMachiningFeature** from the
catalog generated by CAASmiUserMachFeatureCatalog.m module.

 
 
```
...
 // Loads catalog	 
 CATUnicodeString CatalogFeature ("CAAUserMachiningFeatures.CATfct");	
 CATUnicodeString ClientID ("CAAManufacturing");
 CATUnicodeString NewSUFeatType("CAASmgMachiningFeature");
 CATOsmSUHandler novelSUHandler(NewSUFeatType, ClientID, CatalogFeature);

 CATISpecObject_var spInstance = NULL_var;
 oRC = novelSUHandler.Instanciate(spInstance, spFeatCont, "");
 if (FAILED(oRC)) return oRC;
 ...
```

 
 

Then, we instanciate **CAASmgMachiningFeature** and we add the **CAASmgGuide**
attribute with the *AddNcGeometryParameter* method of *CATISmgNcGeometryManager*.
This method adds a geometry attribute which support standard geometries or nc
geometry features.

 
 
```
...
 // Creates the machining feature (associated in Catalog)	 
 if (SUCCEEDED(oRC))
 {
 oFeature = spInstance;

 // Adds a geometric parameter "CAASmgGuide"
 CATISmgNcGeometryManager_var spSmgManager = oFeature;
 if (spSmgManager != NULL_var)
 oRC = spSmgManager->AddNcGeometryParameter("CAASmgGuide",SmgEdgeType);
 }
 ...
```

 
 

Finally, we add our feature in the Manufacturing Container.

 
 
```
...	
 // Adds the feature in the MfgView
 SEQUENCE(CATBaseUnknown_ptr) ListOfMfgView;
 spFeatCont->ListMembersHere(CATIMfgViewAccess::ClassName(), ListOfMfgView);

 int NbMfgView = ListOfMfgView.length();
 if(NbMfgView)
 {
 CATBaseUnknown * pBaseView = ListOfMfgView[NbMfgView - 1];
 if (pBaseView)
 {
 CATIMfgViewAccess_var spMfgView = pBaseView;
 if (spMfgView != NULL_var)
 spMfgView->AddFeature(oFeature);
 pBaseView->Release();
 }
 }
 ...
```

 
 

[[Top]]

#### []Geometry Management: Coding SelectCurve

In *CAASmiUserOperationGeometryPanel* class, *SelectCurve* is
called whenever the user clicks on "*Select a curve*" button. It
calls the *CAASmiUserOperationGeometrySelCom* command that manages the
selection of standard geometries (edge or curve).

 
 
```
...
 // Sends Selection command
 new CAASmiUserOperationGeometrySelCom (this,_spGuide);
 ...
```

 
 

[[Top]]

#### []Geometry Management: Coding SelectZone

In *CAASmiUserOperationGeometryPanel* class, *SelectZone* is called
whenever the user clicks on "*Select a set of curves*" button. It
activates the standard dialog editor of NC Geometry Features management via the *CATIEdit*
interface.

 
 ****
```
...
 CATIEdit * pEdit = NULL;
 HRESULT RC = _spGuide->QueryInterface(IID_CATIEdit, (void**) &pEdit);
 if (SUCCEEDED(RC))
 {
 // For zone management
 pEdit->
Activate
(NULL);
 pEdit->Release();
 pEdit = NULL;
 }
 ...
```

 
 

[[Top]]

#### []Geometry Management: Coding RemoveAll

In *CAASmiUserOperationGeometryPanel* class, *RemoveAll* is called
whenever the user clicks on "*Remove all*" button. It uses the *RemoveAll*
method of *CATISmgNcGeometryParameter* interface.

 
 ****
```
...
 CATISmgNcGeometryParameter * pSmgParameter = NULL;
 HRESULT RC = _spGuide->QueryInterface(IID_CATISmgNcGeometryParameter, (void**) &pSmgParameter);
 if (SUCCEEDED(RC))
 {
 pSmgParameter->
RemoveAll
();
 pSmgParameter->Release();
 pSmgParameter = NULL;
 }
 ...
```

 
 

[[Top]]

#### []Geometry Management: Coding NewZone

In *CAASmiUserOperationGeometryPanel* class, *NewZone* is called
whenever the user clicks on "*Add a empty set*" button. A Nc
Geometry Feature is created by the *CreateNcGeometryFeature* method of *CATISmgFactory*.
The Nc Geometry Feature is added with *Add* method of *CATISmgNcGeometryParameter*.

 
 ********
```
...
 // Creates a empty zone
 CATISmgFactory * pSmgFactory = NULL;
 HRESULT RC = spFeatCont->QueryInterface(IID_CATISmgFactory, (void**)&pSmgFactory);
 if (SUCCEEDED(RC))
 {
 pSmgFactory->
CreateNcGeometryFeature
(SmgEdgeType,spNcFeature);
 pSmgFactory->Release();
 pSmgFactory = NULL;
 }

 // Adds it in the guide parameter
 if (!!_spGuide && !!spNcFeature)
 {
 CATISmgNcGeometryParameter * pSmgParameter = NULL;
 RC = _spGuide->QueryInterface(IID_CATISmgNcGeometryParameter, (void**) &pSmgParameter);
 if (SUCCEEDED(RC))
 {
 pSmgParameter->
Add
(spNcFeature);
 pSmgParameter->Release();
 pSmgParameter = NULL;
 }
 }
 ...
```

 
 

[[Top]]

#### []Geometry Management: Coding Export

In *CAASmiUserOperationGeometryPanel* class, *Export* is called
whenever the user clicks on "*Export curves in a new set*"
button. It uses the *Export* method of *CATISmgNcGeometryParameter*
interface.

 
 ****
```
...
 CATISmgNcGeometryParameter * pSmgParameter = NULL;
 HRESULT RC = _spGuide->QueryInterface(IID_CATISmgNcGeometryParameter, (void**) &pSmgParameter);
 if (SUCCEEDED(RC))
 {
 pSmgParameter->
Export
();
 pSmgParameter->Release();
 pSmgParameter = NULL;
 }
 ...
```

 
 

[[Top]]

---

### []In Short

This use case has demonstrated how to manage surface machining operation
geometry interactive with a geometry attribute of an user machining feature.

 
- It first shows how to implement the *CATIMfgGeometryActivity*
 interface to overload default geometry tab page.
 
- Then, it shows how to create its own machining feature with a surface
 machining geometry attribute.
 
- Finally, it describes geometry management illustrating the use of *CATISmgNcGeometryParameter*,
 *CATISmgNcGeometryManager* and *CATISmgFactory* interfaces.

We will see now how to compute the tool path of our operation [[3]].

[[Top]]

---

### []References

 
 |[1]
 |[Surface
 Machining Operation Sample Overview]
 
 
 |[2]
 |[Building
 and Launching a CAA V5 Use Case]
 
 
 |[3]
 |[Computing a Tool
 Path with User Machining Features]
 
 
 |[[Top]]
 

---

### []History

 
 |Version: **1** [Mar 2002]
 |Document created
 
 
 |[[Top]]
 

---

*Copyright 2002, Dassault Systmes. All rights reserved.*