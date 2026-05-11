---
```vbscript
title: "Inserting a Shape Design Feature in the Procedural View"
category: "technical article"
module: "CAAGsiTechArticles"
tags: ["CATIPrtPart", "CAAGsiNozzle", "CATIGSMProceduralView_var", "CATIGSMInsertInProceduralView", "CAAGSMInterfaces", "CAAGsiUserTools", "CATIContainer_var", "CATIA", "CATIGSMTool", "CATIPrtPart_var", "CATIDescendants_var", "CATIBasicTool_var", "CATISpecObject_var", "CATISpecObject", "CATIDescendants", "CAAGsiToolkit", "CATIBasicTool", "CATIGSMTool_var", "CATIPrtContainer_var"]
source_file: "Doc/online/CAAGsiTechArticles/CAAGsiInsertInProceduralView.htm"
converted: "2026-05-11T17:31:50.666036"
```

---
# Shape Design & Styling

|
## Generative Shape Design

|
### Inserting a Shape Design Feature in the Procedural View

_Insert GSD feature in the procedural view: attach it to an Open Body in the graph_
---|---|---
Technical Article

* * *
### Abstract

This article discusses the CAAGsiUserTools Object. This use case explains how to insert a feature in an open body.

  * **What means inserting in the procedural view**
  * **The CAAGsiUserTools Object - Inserting Wireframe and ShapeDesign Feature in procedural view**
    * What Does CAAGsiUserTools Do
    * Where to Find the CAAGsiUserTools Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What means inserting in the procedural view

The procedural view is the representation of the associative feature creation in the CATIA V5 frame.

The procedural view is the representation of the associative feature creation in the CATIA V5 frame.
Once the feature is created , its representation is generated (build, update) and it is visualized in CATIA in the 3D window and in graph

This article is intended to help you make your first steps in programming with CATIA Shape Design [1]. Its main intent is to show you how to insert a feature in procedural view.

[Top]
### The CAAGsiUserTools Object - Inserting Wireframe and Shape Design Feature in the procedural view

This article is intended to help you make your first steps in programming with CATIA Shape Design [1]. Its main intent is to show you how to insert a feature in procedural view.
CAAGsiUserTools is a usefull class in CAAGsiToolkit.m module of the CAAGSMInterfaces.edu framework that illustrates GSMInterfaces framework object standard use.

CAAGsiUserTools is a toolkit object that encapsulate three aspects of CAA development in Wireframe and Shape Design

  * Creating an OpenBody
  * Inserting a Wireframe and Shape Design feature in an OpenBody
  * Creating Wireframe and shape Design feature using GSMInterface framework Interfaces

Two first aspects are general behaviors to re-use to instanciate any GSD features of GSMInterfaces in CATIA V5 frame.

The second aspect is presented in this article

[Top]
#### What Does CAAGsiUserTools Do

The goal of CAAGsiUserTools Object is to show how to insert a feature in an open body feature, which is a basic task when you create shape design features in a part document. CAAGsiUserTools illustrates some backbone concepts that are shared by all mechanical applications.

[Top][Top]
#### Where to Find the CAAGsiUserTools Code

The goal of CAAGsiUserTools Object is to show how to insert a feature in an open body feature, which is a basic task when you create shape design features in a part document. CAAGsiUserTools illustrates some backbone concepts that are shared by all mechanical applications.
The CAAGsiUserTools Object is made of a single class named CAAGsiUserTools located in the CAAGsiToolkit.m module of the CAAGSMInterfaces.edu framework:

Windows | `InstallRootDirectory\CAAGSMInterfaces.edu\CAAGsiToolkit.m\`

The CAAGsiUserTools Object is made of a single class named CAAGsiUserTools located in the CAAGsiToolkit.m module of the CAAGSMInterfaces.edu framework:
Windows | `InstallRootDirectory\CAAGSMInterfaces.edu\CAAGsiToolkit.m\`
Unix | `InstallRootDirectory/CAAGSMInterfaces.edu/CAAGsiToolkit.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
There are two logical steps in CAAGsiUserTools:

Since release V5R12

  1. Use of CATIGSMInsertInProceduralView interface

Before release CATIA V5R12

  1. Retrieving the Open Body from the Part Feature
  2. Aggregating the Feature to This Open Body

[Top]
#### Use of CATIGSMInsertInProceduralView interface

    **HRESULT
    CAAGsiUserTools::InsertInProceduralView**(const CATISpecObject_var& ispObjectToAppend,
                                            const CATISpecObject_var& ispInputParent)
    {

        // V5R12 AND FOLLOWING VERSIONS: Tool to Insert into the procedural view
        //   ----------------------------------------------------------------------------

        HRESULT rc = E_FAIL;
        CATIGSMProceduralView_var curobj = ispObjectToAppend;
        if (NULL_var != curobj ) {
```vbscript
```vbscript
            rc = curobj->InsertInProceduralView(ispInputParent);

```

```

        }
HRESULT rc = E_FAIL;
CATIGSMProceduralView_var curobj = ispObjectToAppend;
if (NULL_var != curobj ) {
```vbscript
rc = curobj->InsertInProceduralView(ispInputParent);
```

        return rc ;

    }

---

The interface is implemented for all GSD feature and it allows to directly insert the current feature in the procedural view
It encapsulates the previous proposed methodology to insert a feature in an Open Body
If the input father feature is not set (NULL_var) then the current feature is used as reference for inserting.
Note: If object is already inserted, nothing is done.

Some additionnal arguments can be setted (which values are default defined)

  * bSetAsCurrent (TRUE by default) TRUE means that the object after insert becomes current
  * BeforeFeature (NULL_var by default), only to be used for inserting in a partbody, allow to specify where insert the feature in a PartBody

![](../CAAIcons/images/warning.gif)The interface is much more straight forward for inserting GSD feature and it is recommended to use it since V5R12.
#### Retrieving the Open Body from the Part Feature

    **HRESULT
     CAAGsiUserTools::InsertInProceduralView**(const CATISpecObject_var &ispObjectToAppend,
CAAGsiUserTools::InsertInProceduralView**(const CATISpecObject_var &ispObjectToAppend,
                                             const CATISpecObject_var &ispInputParent)

    {
CAAGsiUserTools::InsertInProceduralView**(const CATISpecObject_var &ispObjectToAppend,
const CATISpecObject_var &ispInputParent)
      CATIGSMTool_var spTool = ispInputParent;

      if (NULL_var == spTool)
```vbscript
```vbscript
        spTool = **GetCurrentGSMTool**("",1);

```

```

      ...

---

spTool = **GetCurrentGSMTool**("",1);
We first get a _CATIGSMTool_ smart pointer from the `ispInputParent` smart pointer. If the given _CATISpecObject_ Smart Pointer `ispInputParent` equals NULL_var then we call the `GetCurrentGSMTool` method to retrieve a GMTool. If we call `InsertInProceduralView` with a null `ispInputParent` then we will retrieve the GSMTool automatically.

We have stored the _pFact pointer in the CAAGsiUserTools class in the method `Init` that has to be called before doing anything, we call the `GetCurrentGSMTool()` method to retrieve a Current GSMTool or create one and set it current. This enable the user to directly call `InsertInProceduralView()` without calling `CreateGSMTool()` before.

![](../CAAIcons/images/warning.gif)The main drawback of this, is that we will make a lot of unuseful calls to retrieve the Part, the current Tool and finally insert a feature in the GSMTool.

    **CATIGSMTool_var
      CAAGsiUserTools::GetCurrentGSMTool**(const CATUnicodeString &iName,
CAAGsiUserTools::GetCurrentGSMTool**(const CATUnicodeString &iName,
                                         int iSetAsCurrent)

    {
CAAGsiUserTools::GetCurrentGSMTool**(const CATUnicodeString &iName,
int iSetAsCurrent)
      CATIContainer_var    spCont      = _pFact;
      CATIPrtContainer_var spPartCont  = spCont;
      CATIPrtPart_var      spPart      = spPartCont -> GetPart();

      CATIGSMTool_var spTool = NULL_var;
```vbscript
      if (NULL_var != spPart)

```

      {
CATIPrtPart_var      spPart      = spPartCont -> GetPart();
CATIGSMTool_var spTool = NULL_var;
if (NULL_var != spPart)
        CATIBasicTool_var spCurrentTool = spPart->**GetCurrentTool**();
        spTool = spCurrentTool;
```vbscript
        if (NULL_var != spTool)

```

        {
CATIBasicTool_var spCurrentTool = spPart->**GetCurrentTool**();
spTool = spCurrentTool;
if (NULL_var != spTool)
          CATISpecObject_var spExternalRef = spPart->**GetBodyForExternalReferences**();
          if (NULL_var != spExternalRef && spTool == spExternalRef)
                 spTool = NULL_var;

        }
CATISpecObject_var spExternalRef = spPart->**GetBodyForExternalReferences**();
if (NULL_var != spExternalRef && spTool == spExternalRef)
spTool = NULL_var;
```vbscript
        if (**NULL_var == spTool**)

```

        {
```vbscript
if (NULL_var != spExternalRef && spTool == spExternalRef)
spTool = NULL_var;
if (**NULL_var == spTool**)
```vbscript
          spTool = **CreateGSMTool**(iName);
```

```

        }
      }
```vbscript
if (**NULL_var == spTool**)
```vbscript
spTool = **CreateGSMTool**(iName);
```

      return spTool;
```

    }

---

return spTool;
The smart pointer `spPart` to the _CATIPrtPart_ interface enables us to retrieve the active Tool (One always one.) Then, we try to get a _CATIGSMTool_ smart pointer on the `spCurrentTool` _CATIBasicTool_ smart pointer, if `spCurrentTool` is a GSMTool then `spTool` is not null.

At this stage, we have to check that the tool retrieved is not the open body dedicated to store external references (Multi-model links). If it is the case, we set `spTool` to NULL_var which means that we need to create another GSMTool feature for our need. We finally call the `CreateGSMTool` method [3]. We will create this open body with the default argument (iSetAsCurrent = 1 and iTopLevel = 0). This open body will appear after the current open body in procedural view.

![](../CAAIcons/images/information.gif)In some case, we will insert two features at a time in the procedural view: a feature and an open body.

[Top]
#### Aggregating the Feature to This Open Body

Now that we have retrieved (or created) an open body, we can aggregate the shape design feature inside it.

    **HRESULT CAAGsiUserTools::InsertInProceduralView()**
      {
      ...
      if ( NULL_var != ispObjectToAppend && NULL_var != spTool)
      {
        **CATIDescendants** _var spParent = spTool;
```vbscript
if ( NULL_var != ispObjectToAppend && NULL_var != spTool)
```vbscript
        if ( NULL_var != spParent)
```

          spParent->**Append ( ispObjectToAppend )** ;
        else
          return E_FAIL;
```

      }
```vbscript
if ( NULL_var != spParent)
spParent->**Append ( ispObjectToAppend )** ;
else
return E_FAIL;
      else
        return E_FAIL;
      return S_OK;

```

---

return E_FAIL;
return S_OK;
We get a _CATIDescendants_ interface smart pointer from the `spTool` smart pointer, in order to aggregate the _ispObjectToAppend_ in the GSMTool.

![](../CAAIcons/images/information.gif)A shape design feature is created without any parent, but in order to see them in 3D and to manipulate them in the CATIA V5 applications, we have to aggregate them in open bodies.

We call the `Append` method of spParent in order to add to its descendant the `ispObjectToAppend` feature.

[Top]

* * *
### In Short

This use case has demonstrated the way to insert a shape design feature in procedural view. We illustrate the way we can automatically insert an open body in the procedural view if no active open body exists. We also show how to aggregate a feature in an open body using _CATIDescendants_ interface.

[Top]

* * *
### References

[1] | [About Generative Shape Design Features](CAAGsiShapeDesignFeature.md)
---|---
[2] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
[3] | [Creating an Open Body](CAAGsiCreateGSMTool.md)
[4] | [CAAGsiNozzle Use case](../CAAGsiUseCases/CAAGsiNozzleSample.md)
[Top]

* * *
### History

Version: **1** [Apr 2000] | Document created
---|---
Version: **2** [Apr 2003] | Documentset as Technical Article
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
