---
```vbscript
title: "Managing Geometry with User Machining Features"
category: use-case case"
module: "CAASmiUseCases"
tags: ["CAASmiUserOperationGeometryPanel", "CATISmgNcGeometryManager", "CAAManufacturing", "CATIMfgViewAccess_var", "CATISmgNcGeometryParameter", "CAASmgOperation", "CATISmgFactory", "CATIMfgGeometryActivity", "CAASmiUserOperationGeomUI", "CATIMfgViewAccess", "CAASmiUserOperationGeometrySelCom", "CAASmiUserMachFeatureCatalog", "CATIEdit", "CATIMfgActivity", "CAASmgMachiningFeature", "CAAESmiUserOperationGeometryEditor", "CATISpecObject_var", "CATISmgNcGeometryManager_var", "CAASmgGuide", "CAASurfaceMachiningItf"]
source_file: "Doc/online/CAASmiUseCases/CAASmiUserOperationWithUserMF.htmmd"
converted: "2026-05-11T17:31:51.281341"
```

---
# Machining

|
## 3 Axis Surface Machining

|
### Managing Geometry with User Machining Features

_Customize the geometry tab page of a surface machining operation with user machining features_
---|---|---
Use Case

* * *
### Abstract

This article discusses the CAASmiUserOperationWithUserMF use case. It explains how to customize the default geometry tab page of a surface machining operation to be able to select geometry through an user machining feature's geometry attribute. This paper accompanies the first scenario of _Surface Machining Operation Sample_ [1].

  * **What You Will Learn With This Use Case**
  * **The CAASmiUserOperationWithUserMF Use Case**
    * What Does CAASmiUserOperationWithUserMF Do
    * How to Launch CAASmiUserOperationWithUserMF
    * Where to Find the CAASmiUserOperationWithUserMF Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

This use case is intended to help you to manage geometry of a surface machining operation with a machining feature geometry attribute.

More specifically, the CAASmiUserOperationWithUserMF Use Case shows how to:

  * Overload the geometry tab page of a surface machining operation.
  * Create a new machining feature.
  * Connect a machining feature with a surface machining operation.
  * Manage geometry selection of surface machining geometry attributes.

[Top]
### The CAASmiUserOperationWithUserMF Use Case

CAASmiUserOperationWithUserMF is a use case of the CAASurfaceMachiningItf.edu framework that illustrates Surface Machining capabilities. It is a part of the sample described in the technical article [1].

[Top]
#### What Does CAASmiUserOperationWithUserMF Do

CAASmiUserOperationWithUserMF is a use case of the CAASurfaceMachiningItf.edu framework that illustrates Surface Machining capabilities. It is a part of the sample described in the technical article [1].
This use case customizes the default geometry tab page of **CAASmgOperation**.

CAASmgOperation**** is associated with a new machining feature: **CAASmgMachiningFeature**.

CAASmgMachiningFeature has a geometry attribute : **CAASmgGuide**. This parameter can support manufacturing geometries or nc geometry features.

The geometry management is done by several functionalities:

 Description of functionalities illustrated:

  * _Select a curve_ : select an edge with the edge selection toolbar.
  * _Select a set of curves_ : select a NC Geometry Feature of edges.
  * _Remove all_ : remove selection.
  * _Add a empty set_ : create an empty NC Geometry Feature of edges.
  * _Export curves in a new set_ : create an NC Geometry Feature with the edges previously selected.

[Top]
#### How to Launch CAASmiUserOperationWithUserMF

This use case is a part of _Surface Machining Operation Sample_ [1]. You should build all the modules of this sample at a time to be able to launch it [2].

This use case is a part of _Surface Machining Operation Sample_ [1]. You should build all the modules of this sample at a time to be able to launch it [2].
Don't forget to edit the interface dictionary located in:

Windows | `InstallRootDirectory/CAASurfaceMachiningItf.edu/CNext/code/dictionary/`

Don't forget to edit the interface dictionary located in:
Windows | `InstallRootDirectory/CAASurfaceMachiningItf.edu/CNext/code/dictionary/`
Unix | `InstallRootDirectory/CAASurfaceMachiningItf.edu/CNext/code/dictionary/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed, and uncomment the appropriate lines by removing the '#' character.

[Top]
#### Where to Find the CAASmiUserOperationWithUserMF Code

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed, and uncomment the appropriate lines by removing the '#' character.
This use case is made of source files located in the CAASmiUserOperationGeomUI.m module of the CAASurfaceMachiningItf.edu framework :

Windows | `InstallRootDirectory/CAASurfaceMachiningItf.edu/CAASmiUserOperationGeomUI.m`

This use case is made of source files located in the CAASmiUserOperationGeomUI.m module of the CAASurfaceMachiningItf.edu framework :
Windows | `InstallRootDirectory/CAASurfaceMachiningItf.edu/CAASmiUserOperationGeomUI.m`
Unix | `InstallRootDirectory/CAASurfaceMachiningItf.edu/CAASmiUserOperationGeomUI.m`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

CAASmiUserOperationWithUserMF is divided into the following steps:

  * Implementing CATIMfgGeometryActivity:
    * Declaring CATIMfgGeometryActivity Implementation
    * Coding GetMainPanelEditor
    * Creating a New Machining Feature CAASmgMachiningFeature
  * Creating the geometry dialog frame:
    * Geometry Management: Coding SelectCurve
    * Geometry Management: Coding SelectZone
    * Geometry Management: Coding RemoveAll
    * Geometry Management: Coding NewZone
    * Geometry Management: Coding Export

We now comment each of those sections by looking at the code.

[Top]
#### Declaring CATIMfgGeometryActivity Implementation

To overload the geometry tab page, we should create an extension class that will implement _CATIMfgGeometryActivity_ :

      ...
      // Tie the implementation to its interface
      #include "TIE_CATIMfgGeometryActivity.h"
      TIE_CATIMfgGeometryActivity( CAAESmiUserOperationGeometryEditor);
      ...

---

[Top]
#### Coding GetMainPanelEditor

In _GetMainPanelEditor,_ we create a new **CAASmgMachiningFeature** and we associate it with **CAASmgOperation**. Then we call the geometry dialog frame described below.

      ...
      // Associates a machining feature
In _GetMainPanelEditor,_ we create a new **CAASmgMachiningFeature** and we associate it with **CAASmgOperation**. Then we call the geometry dialog frame described below.
      CATIMfgActivity * pActivity = NULL;
      oRC = QueryInterface(IID_CATIMfgActivity, (void**) &pActivity);
```vbscript
```vbscript
      if (SUCCEEDED(oRC))

```

```

      {
CATIMfgActivity * pActivity = NULL;
oRC = QueryInterface(IID_CATIMfgActivity, (void**) &pActivity);
```vbscript
```vbscript
if (SUCCEEDED(oRC))
        spMachFeature = pActivity->GetFeature(#);
        if (NULL_var == spMachFeature)

```

```

        {
          // Create a user machining feature
spMachFeature = pActivity->GetFeature(#);
```vbscript
```vbscript
if (NULL_var == spMachFeature)
          oRC = CreateCAAMachiningFeature(spMachFeature);
          if (SUCCEEDED(oRC))

```

```

          {
            // Link the machining feature to the activity
oRC = CreateCAAMachiningFeature(spMachFeature);
```vbscript
if (SUCCEEDED(oRC))
```

            pActivity->SetFeature(spMachFeature);

          }
        }
pActivity->SetFeature(spMachFeature);
        pActivity->Release(#);
        pActivity = NULL;

      }

      // Creates the frame
pActivity->Release(#);
pActivity = NULL;
```vbscript
      oFrame = new CAASmiUserOperationGeometryPanel(iFather,spMachFeature);

```

      ...

---

[Top]
#### Creating a New Machining Feature CAASmgMachiningFeature

The _CreateCAAMachiningFeature_ method is used to create **CAASmgMachiningFeature**.

At first, we retrieve the startup of **CAASmgMachiningFeature** from the catalog generated by CAASmiUserMachFeatureCatalog.m module.

      ...
      // Loads catalog
At first, we retrieve the startup of **CAASmgMachiningFeature** from the catalog generated by CAASmiUserMachFeatureCatalog.m module.
      CATUnicodeString CatalogFeature ("CAAUserMachiningFeatures.CATfct");
      CATUnicodeString ClientID ("CAAManufacturing");
      CATUnicodeString NewSUFeatType("CAASmgMachiningFeature");
      CATOsmSUHandler novelSUHandler(NewSUFeatType, ClientID, CatalogFeature);

      CATISpecObject_var spInstance = NULL_var;
      oRC = novelSUHandler.Instanciate(spInstance, spFeatCont, "");
```vbscript
```vbscript
      if (FAILED(oRC)) return oRC;

```

```

      ...

---

Then, we instanciate **CAASmgMachiningFeature** and we add the **CAASmgGuide** attribute with the _AddNcGeometryParameter_ method of _CATISmgNcGeometryManager_. This method adds a geometry attribute which support standard geometries or nc geometry features.

      ...
      // Creates the machining feature (associated in Catalog)
Then, we instanciate **CAASmgMachiningFeature** and we add the **CAASmgGuide** attribute with the _AddNcGeometryParameter_ method of _CATISmgNcGeometryManager_. This method adds a geometry attribute which support standard geometries or nc geometry features.
```vbscript
      if (SUCCEEDED(oRC))

```

      {
        oFeature = spInstance;

        // Adds a geometric parameter "CAASmgGuide"
```vbscript
if (SUCCEEDED(oRC))
oFeature = spInstance;
        CATISmgNcGeometryManager_var spSmgManager = oFeature;
        if (spSmgManager != NULL_var)
```vbscript
          oRC = spSmgManager->AddNcGeometryParameter("CAASmgGuide",SmgEdgeType);
```

```

      }
      ...

---

Finally, we add our feature in the Manufacturing Container.

      ...
      // Adds the feature in the MfgView
Finally, we add our feature in the Manufacturing Container.
      SEQUENCE(CATBaseUnknown_ptr) ListOfMfgView;
      spFeatCont->ListMembersHere(CATIMfgViewAccess::ClassName(#), ListOfMfgView);

      int NbMfgView = ListOfMfgView.length(#);
      if(NbMfgView)

      {
spFeatCont->ListMembersHere(CATIMfgViewAccess::ClassName(#), ListOfMfgView);
int NbMfgView = ListOfMfgView.length(#);
if(NbMfgView)
        CATBaseUnknown * pBaseView = ListOfMfgView[NbMfgView - 1];
```vbscript
        if (pBaseView)

```

        {
```vbscript
if(NbMfgView)
CATBaseUnknown * pBaseView = ListOfMfgView[NbMfgView - 1];
if (pBaseView)
          CATIMfgViewAccess_var spMfgView = pBaseView;
          if (spMfgView != NULL_var)
          spMfgView->AddFeature(oFeature);
          pBaseView->Release(#);
```

        }
      }
      ...

---

[Top]
#### Geometry Management: Coding SelectCurve

In _CAASmiUserOperationGeometryPanel_ class, _SelectCurve_ is called whenever the user clicks on "_Select a curve_ " button. It calls the _CAASmiUserOperationGeometrySelCom_ command that manages the selection of standard geometries (edge or curve).

      ...
      // Sends Selection command
      new CAASmiUserOperationGeometrySelCom (this,_spGuide);
      ...

---

[Top]
#### Geometry Management: Coding SelectZone

In _CAASmiUserOperationGeometryPanel_ class, _SelectZone_ is called whenever the user clicks on "_Select a set of curves_ " button. It activates the standard dialog editor of NC Geometry Features management via the _CATIEdit_ interface.

      ...
In _CAASmiUserOperationGeometryPanel_ class, _SelectZone_ is called whenever the user clicks on "_Select a set of curves_ " button. It activates the standard dialog editor of NC Geometry Features management via the _CATIEdit_ interface.
      CATIEdit * pEdit = NULL;
      HRESULT RC = _spGuide->QueryInterface(IID_CATIEdit, (void**) &pEdit);
```vbscript
      if (SUCCEEDED(RC))

```

      {
        // For zone management
CATIEdit * pEdit = NULL;
HRESULT RC = _spGuide->QueryInterface(IID_CATIEdit, (void**) &pEdit);
if (SUCCEEDED(RC))
        pEdit->**Activate**(NULL);
        pEdit->Release(#);
        pEdit = NULL;

      }
      ...

---

[Top]
#### Geometry Management: Coding RemoveAll

In _CAASmiUserOperationGeometryPanel_ class, _RemoveAll_ is called whenever the user clicks on "_Remove all_ " button. It uses the _RemoveAll_ method of _CATISmgNcGeometryParameter_ interface.

     ...
In _CAASmiUserOperationGeometryPanel_ class, _RemoveAll_ is called whenever the user clicks on "_Remove all_ " button. It uses the _RemoveAll_ method of _CATISmgNcGeometryParameter_ interface.
      CATISmgNcGeometryParameter * pSmgParameter = NULL;
      HRESULT RC = _spGuide->QueryInterface(IID_CATISmgNcGeometryParameter, (void**) &pSmgParameter);
```vbscript
      if (SUCCEEDED(RC))

```

      {
CATISmgNcGeometryParameter * pSmgParameter = NULL;
HRESULT RC = _spGuide->QueryInterface(IID_CATISmgNcGeometryParameter, (void**) &pSmgParameter);
if (SUCCEEDED(RC))
        pSmgParameter->**RemoveAll**(#);
        pSmgParameter->Release(#);
        pSmgParameter = NULL;

      }
      ...

---

[Top]
#### Geometry Management: Coding NewZone

In _CAASmiUserOperationGeometryPanel_ class, _NewZone_ is called whenever the user clicks on "_Add a empty set_ " button. A Nc Geometry Feature is created by the _CreateNcGeometryFeature_ method of _CATISmgFactory_. The Nc Geometry Feature is added with _Add_ method of _CATISmgNcGeometryParameter_.

      ...
      // Creates a empty zone
In _CAASmiUserOperationGeometryPanel_ class, _NewZone_ is called whenever the user clicks on "_Add a empty set_ " button. A Nc Geometry Feature is created by the _CreateNcGeometryFeature_ method of _CATISmgFactory_. The Nc Geometry Feature is added with _Add_ method of _CATISmgNcGeometryParameter_.
      CATISmgFactory * pSmgFactory = NULL;
      HRESULT RC = spFeatCont->QueryInterface(IID_CATISmgFactory, (void**)&pSmgFactory);
```vbscript
      if (SUCCEEDED(RC))

```

      {
CATISmgFactory * pSmgFactory = NULL;
HRESULT RC = spFeatCont->QueryInterface(IID_CATISmgFactory, (void**)&pSmgFactory);
if (SUCCEEDED(RC))
        pSmgFactory->**CreateNcGeometryFeature**(SmgEdgeType,spNcFeature);
        pSmgFactory->Release(#);
      pSmgFactory = NULL;

      }

      // Adds it in the guide parameter
pSmgFactory->Release(#);
pSmgFactory = NULL;
```vbscript
      if (!!_spGuide && !!spNcFeature)

```

      {
```vbscript
if (!!_spGuide && !!spNcFeature)
        CATISmgNcGeometryParameter * pSmgParameter = NULL;
        RC = _spGuide->QueryInterface(IID_CATISmgNcGeometryParameter, (void**) &pSmgParameter);
```vbscript
        if (SUCCEEDED(RC))
```

```

        {
CATISmgNcGeometryParameter * pSmgParameter = NULL;
RC = _spGuide->QueryInterface(IID_CATISmgNcGeometryParameter, (void**) &pSmgParameter);
```vbscript
if (SUCCEEDED(RC))
```

          pSmgParameter->**Add**(spNcFeature);
          pSmgParameter->Release(#);
          pSmgParameter = NULL;

        }
      }
      ...

---

[Top]
#### Geometry Management: Coding Export

In _CAASmiUserOperationGeometryPanel_ class, _Export_ is called whenever the user clicks on "_Export curves in a new set_ " button. It uses the _Export_ method of _CATISmgNcGeometryParameter_ interface.

      ...
In _CAASmiUserOperationGeometryPanel_ class, _Export_ is called whenever the user clicks on "_Export curves in a new set_ " button. It uses the _Export_ method of _CATISmgNcGeometryParameter_ interface.
      CATISmgNcGeometryParameter * pSmgParameter = NULL;
      HRESULT RC = _spGuide->QueryInterface(IID_CATISmgNcGeometryParameter, (void**) &pSmgParameter);
```vbscript
      if (SUCCEEDED(RC))

```

      {
CATISmgNcGeometryParameter * pSmgParameter = NULL;
HRESULT RC = _spGuide->QueryInterface(IID_CATISmgNcGeometryParameter, (void**) &pSmgParameter);
if (SUCCEEDED(RC))
        pSmgParameter->**Export**(#);
        pSmgParameter->Release(#);
        pSmgParameter = NULL;

      }
      ...

---

[Top]

* * *
### In Short

This use case has demonstrated how to manage surface machining operation geometry interactive with a geometry attribute of an user machining feature.

  * It first shows how to implement the _CATIMfgGeometryActivity_ interface to overload default geometry tab page.
  * Then, it shows how to create its own machining feature with a surface machining geometry attribute.
  * Finally, it describes geometry management illustrating the use of _CATISmgNcGeometryParameter_ , _CATISmgNcGeometryManager_ and _CATISmgFactory_ interfaces.

We will see now how to compute the tool path of our operation [3].

[Top]

* * *
### References

[1] | [Surface Machining Operation Sample Overview](../CAASmiTechArticles/CAASmiOperationSampleOverview.md)
---|---
[2] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
[3] | [Computing a Tool Path with User Machining Features](CAASmiUserOperationWithUserMFToolPath.md)
[Top]

* * *
### History

Version: **1** [Mar 2002] | Document created
---|---
[Top]

* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
