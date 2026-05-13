---
```vbscript
title: "Creating an Open Body"
category: tech-article article"
module: "CAAGsiTechArticles"
tags: ["CATIPrtPart", "CAAGsiNozzle", "CATIPrtManagement_var", "CATIPrtContainer", "CATIMechanicalRootFactory", "CAAGSMInterfaces", "CAAGsiUserTools", "CATIContainer_var", "CATIA", "CATIGSMFactory", "CATIGSMTool", "CATIPrtPart_var", "CATIDescendants_var", "CATInit_var", "CATIBasicTool_var", "CATISpecObject_var", "CATIDescendants", "CAAGsiToolkit", "CATIBasicTool", "CATIPrtManagement"]
source_file: "Doc/online/CAAGsiTechArticles/CAAGsiCreateGSMTool.htmmd"
converted: "2026-05-11T17:31:50.660543"
```

---
# Shape Design & Styling

|
## Generative Shape Design

|
### Creating an Open Body

_How to create a GSMTool in a Part document_
---|---|---
Technical Article

* * *
### Abstract

This article discusses the Open Body The class CAAGsiUserTools Objec explains how to create an open body feature that is bound to imbed Shape Design Features.

  * **What is an Open Body**
  * **The CAAGsiUserTools Object - Creating an OpenBody**
    * What Does CAAGsiUserTools Do
    * Where to Find the CAAGsiUserTools Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What is an Open Body

An "Open Body" is a mechanical modeler object required as father for any GSD feature to be insert in a part document.

An "Open Body" is a mechanical modeler object required as father for any GSD feature to be insert in a part document.
This article is intended to help you make your first steps in programming with CATIA Shape Design [1]. Its main intent is to practically describe the creation of the open body

Before creating this open body, you will have to navigate through the feature model of CATIA V5 to find the objects that will enable you to create this open body (also called a GSMTool object) under the part feature.

[Top]
### The CAAGsiUserTools Object - Creating an OpenBody

Before creating this open body, you will have to navigate through the feature model of CATIA V5 to find the objects that will enable you to create this open body (also called a GSMTool object) under the part feature.
CAAGsiUserTools is a usefull class in CAAGsiToolkit.m module of the CAAGSMInterfaces.edu framework that illustrates GSMInterfaces framework object standard use.

CAAGsiUserTools is a toolkit object that encapsulate three aspects of CAA development in Wireframe and Shape Design

  * Creating an OpenBody
  * Inserting a Wireframe and Shape Design feature in an OpenBody
  * Creating Wireframe and shape Design feature using GSMInterface framework Interfaces

Two first aspects are general behaviors to re-use to instanciate any GSD features of GSMInterfaces in CATIA V5 frame.

The first aspect is presented in this article

[Top]
#### What Does CAAGsiUserTools Do

The first aspect is presented in this article
The goal of CAAGsiUserTools Object is to show how to create an open body feature, which is the first common step before creating shape design features in a part document. We enrich the sample code CAAGsiUserTools.cpp(.h) and illustrates some backbone concepts thats are shared by all Mechanical Applications.

CAAGsiUserTools is used in CAAGsiNozzle sample

[Top]Top]
#### Where to Find the CAAGsiUserTools Code

CAAGsiUserTools is used in CAAGsiNozzle sample
The CAAGsiUserTools Object is made of a single class named CAAGsiUserTools located in the CAAGsiToolkit.m module of the CAAGSMInterfaces.edu framework:

Windows | `InstallRootDirectory/CAAGSMInterfaces.edu/CAAGsiToolkit.m/`

The CAAGsiUserTools Object is made of a single class named CAAGsiUserTools located in the CAAGsiToolkit.m module of the CAAGSMInterfaces.edu framework:
Windows | `InstallRootDirectory/CAAGSMInterfaces.edu/CAAGsiToolkit.m/`
Unix | `InstallRootDirectory/CAAGSMInterfaces.edu/CAAGsiToolkit.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
There are six logical steps illustrated in CAAGsiUserTools for creating an Open Body :

  1. Prolog
  2. Retrieving the Part Container Feature
  3. Retrieving the Current Tool
  4. Locating the Tool Under The Part Feature
  5. Creating a GSMTool Feature Instance
  6. Setting the Created Tool as Current

We will now first comment the Part document creation and intialization in the method `CAAGsiUserTools::Init` in the prolog, and then each of these steps by looking at the code of the method `CAAGsiUserTools::CreateGSMTool`.

[Top]
#### Prolog

We first have created a Part document handled using the `_pDoc` smart pointer. We have stored the `_pFact` pointer in the _CAAGsiUserTools_ class in the method `Init` that has to be called before doing anything with a _CAAGsiUserTools_ object.

We first have created a Part document handled using the `_pDoc` smart pointer. We have stored the `_pFact` pointer in the _CAAGsiUserTools_ class in the method `Init` that has to be called before doing anything with a _CAAGsiUserTools_ object.
    HRESULT CAAGsiUserTools::Init(char *& iSessionName)

    {
We first have created a Part document handled using the `_pDoc` smart pointer. We have stored the `_pFact` pointer in the _CAAGsiUserTools_ class in the method `Init` that has to be called before doing anything with a _CAAGsiUserTools_ object.
HRESULT CAAGsiUserTools::Init(char *& iSessionName)
      HRESULT rc = S_OK;

      ...  // Create the CATPart document
HRESULT CAAGsiUserTools::Init(char *& iSessionName)
HRESULT rc = S_OK;
      CATInit_var spInit = **_pDoc** ;
      spInit->Init(TRUE);

      CATIPrtContainer * piPartContainer = (CATIPrtContainer*) spInit->**GetRootContainer**("CATIPrtContainer");

      ... // Process piPartContainer == NULLL
CATInit_var spInit = **_pDoc** ;
spInit->Init(TRUE);
CATIPrtContainer * piPartContainer = (CATIPrtContainer*) spInit->**GetRootContainer**("CATIPrtContainer");
```vbscript
      rc = piPartContainer -> QueryInterface(IID_CATIGSMFactory, (void**)&**_pFact**);

```

      ... // Process rc == E_xxx
    }

---

Once the Part document is created, it must be initialized thanks to the `Init` method of the _CATInit_ interface. This method creates the document's root container. Then, the root container is retrieved as a pointer to the _CATIPrtContainer_ interface using the `GetRootContainer` method of the the _CATInit_ interface. This root container implements also the _CATIGSMFactory_ interface. A pointer to _CATIGSMFactory_ is retrieved from on root container and stored as a data member to be used later.

[Top]
#### Retrieving the Part Container Feature

We need a _CATIPrtPart_ interface pointer onto the Part Container feature to be able to get the current Tool Feature.

We need a _CATIPrtPart_ interface pointer onto the Part Container feature to be able to get the current Tool Feature.
    CATIGSMTool_var CAAGsiUserTools::**CreateGSMTool**(const CATUnicodeString &iName,
                                                   int                    iSetAsCurrent,
                                                   int                    iTopLevel)

    {
CATIGSMTool_var CAAGsiUserTools::**CreateGSMTool**(const CATUnicodeString &iName,
int                    iSetAsCurrent,
int                    iTopLevel)
      CATIContainer_var    spCont     = **_pFact** ;
      CATIPrtContainer_var spPartCont = spCont;
      CATIPrtPart_var      spPart     = **spPartCont - > GetPart(#)**;

    ...

---

We first get a smart pointer to _CATIPrtContainer_ from the stored pointer `_pFact`, then we get the Part **root** feature from the Part container as a smart pointer to the _CATIPrtPart_ interface.

[Top]
#### Retrieving the Current Tool

Now that we have retrieved the Part feature, we can retrieve the current tool, that can be a MechanicalTool or a GSMTool.

![](../CAAIcons/images/warning.gif)A GSMTool can be created only under another GSMTool or directly under the part **root** feature, but not under a MechanicalTool.

      ...
      CATIGSMTool_var spTool = NULL_var;
CATIGSMTool_var spTool = NULL_var;
```vbscript
      if ( NULL_var != spPart )

```

      {
CATIGSMTool_var spTool = NULL_var;
if ( NULL_var != spPart )
        CATIBasicTool_var spCurrentTool = spPart->**GetCurrentTool**(#);

        ...

---

CATIBasicTool_var spCurrentTool = spPart->**GetCurrentTool**(#);
The _CATIPrtPart_ interface enables us to retrieve the current tool (One always exists.) Then, we try to get a _CATIGSMTool_ smart pointer from the `spCurrentTool` _CATIBasicTool_ smart pointer.

At this stage, we have to check that the tool retrieved is not the open body dedicated to store external references (Multi-model links) If it is the case, we set `spTool` to `NULL_var` which means that we need to create another GSMTool feature for our need.

[Top]
#### Locating the Tool Under the Part Feature

![](../CAAIcons/images/key.gif)We show here how to get the position of a feature in the descendants' list of the part feature, using the _CATIDescendants_ interface.

        ...
        int Position = 0;
        CATISpecObject_var spCurrentFeat = spPart->**GetCurrentFeature**(#);
        CATISpecObject_var **spParentForGSMTool** = spPart;

```vbscript
        if (spCurrentFeat != spCurrentTool && 0 == iTopLevel)

```

        {
CATISpecObject_var spCurrentFeat = spPart->**GetCurrentFeature**(#);
CATISpecObject_var **spParentForGSMTool** = spPart;
if (spCurrentFeat != spCurrentTool && 0 == iTopLevel)
          spParentForGSMTool  = spCurrentTool;
          CATISpecObject_var spExternalRef = spPart->**GetBodyForExternalReferences**(#);
```vbscript
          if (NULL_var != spExternalRef && spCurrentTool == spExternalRef)

```

          {
spParentForGSMTool  = spCurrentTool;
CATISpecObject_var spExternalRef = spPart->**GetBodyForExternalReferences**(#);
if (NULL_var != spExternalRef && spCurrentTool == spExternalRef)
            spParentForGSMTool = spPart;

          }
CATISpecObject_var spExternalRef = spPart->**GetBodyForExternalReferences**(#);
if (NULL_var != spExternalRef && spCurrentTool == spExternalRef)
spParentForGSMTool = spPart;
          else

          {
spParentForGSMTool = spPart;
else
            CATIDescendants_var spRoot = spCurrentTool;
```vbscript
            Position = spRoot -> **GetPosition**( spCurrentFeat);

```

          }
        }
        ...

---

We use a again the _CATIPrtPart_ interface to get the current feature. This feature can be a Tool or a mechanical feature. A GSMTool has to be created with a parent, and the parent candidate must be the part itself or another GSMTool.

`spParentForGSMTool` is initialized to the part feature and the retrieved `Position` is 0.

We use a again the _CATIPrtPart_ interface to get the current feature. This feature can be a Tool or a mechanical feature. A GSMTool has to be created with a parent, and the parent candidate must be the part itself or another GSMTool.
In case of a current feature that is different from the current tool and if `iTopLevel` equals 0, then we will compute the position of the current tool in order to create the new one just after the current feature in the procedural view and under the current tool. In order to get the position of the current feature with respect to the current tool, we use the _CATIDescendants_ implementation of the current tool `spRoot`.

Note: In retrieving the require tool it is needed to check that the body is not a body used for "ExternalReferences" generated in assembly context when selecting geometry in a different part as of the current one.

[Top]
#### Creating a GSMTool Feature Instance

We can now create a new GSMTool feature instance by giving its name, parent reference and position under its parent.

    ...
        if (NULL_var != spParentForGSMTool)
        {
          **CATIMechanicalRootFactory** _var spMechRoot = spCont;
          spTool = spMechRoot -> **CreateGSMTool(iName,spParentForGSMTool,Position)** ;
        }
    ...

---

We get the _CATIMechanicalRootFactory_ interface from the `spCont` smart pointer. The GSMTool is created by giving the smart pointer of its parent, that is, either the part feature or a GSMTol instance, and the position of the new tool under its parent. 0 will create the Tool directly under `spParentForGSMTool`.

[Top]
#### Setting the Created Tool as Current

![](../CAAIcons/images/information.gif)Now that we have created this new tool, we have to set it as the current tool, if we want to automatically create skin and wireframe features under this open body.

    ...
        if (NULL_var != spTool && 0 != iSetAsCurrent)
        {
          **CATIPrtManagement** _var spPartManage = spPart;
```vbscript
if (NULL_var != spTool && 0 != iSetAsCurrent)
```vbscript
          if (NULL_var != spPartManage)
```

            spPartManage->**SetCurrentFeature**(spTool);
```

        }
      }
```vbscript
if (NULL_var != spPartManage)
spPartManage->**SetCurrentFeature**(spTool);
      return spTool;

```

---

We check that we want to set the spTool smart pointer as the current tool by testing `iSetAsCurrent`. To set a tool as current we have to retrieve the _CATIPrtManagement_ interface on the part feature, and call the `SetCurrentFeature` method with `spTool` as argument.

[Top]

* * *
### In Short

This article has demonstrated the way to create an open body in a part document. We illustrate how some management interfaces on the part feature can be used like _CATIPrtPart_ , _CATIPrtManagement_ , _CATIMechanicalRootFactory_. We also illustrate the way to get the feature position in the descendant list of its parent using _CATIDescendants_.

[Top]

* * *
### References

[1] | [About Generative Shape Design Features](CAAGsiShapeDesignFeature.md)
---|---
[2] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
[3] | [CAAGsiNozzle Use case](../CAAGsiUseCases/CAAGsiNozzleSample.md)
[Top]

* * *
### History

Version: **1** [Apr 2000] | Document created
---|---
Version: **2** [June 2003] | Document set as a technical article
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
