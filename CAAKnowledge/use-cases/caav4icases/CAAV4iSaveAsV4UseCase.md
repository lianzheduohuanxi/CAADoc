---
title: "Creating V4 Data from a V5 Geometrical Element"
category: "use-case case"
module: "CAAV4iUseCases"
tags: "["CAAGobSurfV4DataSaver", "CAACATIAV4Interfaces", "CAASurfV4DataSaver", "CATIForeignCurve_var", "CAAV4iEduSaveAsV4", "CATIForeignSurface_var", "CATIA", "CATIV4DataSaver"]"
source_file: "Doc/online/CAAV4iUseCases/CAAV4iSaveAsV4UseCase.htm"
converted: "2026-05-11T17:33:45.786384"
---
# 3D PLM PPR Hub Open Gateway

|
## V4 Access

|
### Creating V4 Data from a V5 Geometrical Element

Adapt the behavior of saving a CATPart as a V4 Model
---|---|---
Use Case

* * *
### Abstract

This article shows how to create V4 data from a V5 geometrical element.

  * **What You Will Learn With This Use Case**
  * **The CAAV4iEduSaveAsV4 Use Case**
    * What Does CAAV4iEduSaveAsV4
    * How to Launch CAAV4iEduSaveAsV4
    * Where to Find the CAAV4iEduSaveAsV4 Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

This use case is intended to show you how to create V4 data from a V5 geometrical element.

[Top]
### The CAAV4iEduSaveAsV4 Use Case

CAAV4iEduSaveAsV4 is a use case of the CAACATIAV4Interfaces.edu framework that illustrates V5ToV4Geo framework capabilities.

[Top]
#### What Does CAAV4iEduSaveAsV4 Do

CAAV4iEduSaveAsV4 is a frame, which implements the CATIV4DataSaver interface. This interface is used by CATIA V5, when a CATPart is saved as a V4 model. Actually the implementation is restricted to spline curves and nets.

[Top]
#### How to Launch CAAV4iEduSaveAsV4

CAAV4iEduSaveAsV4 is a frame, which implements the CATIV4DataSaver interface. This interface is used by CATIA V5, when a CATPart is saved as a V4 model. Actually the implementation is restricted to spline curves and nets.
__  First of all, complete the object methods in order to compute the V4 data from the foreign V5 data. Read your V5 data and set the matching V4 data in accordance with the V4 CATGEO format. Tell the process that you want to compute yourself the V4 data. If you want to let the system do, the generic process will be applied and a nurbs element will be computed by approximation. If you wish no computation, the V4 element will be omitted if it is not linked to a topology.
__  Then set up the build time environment, compile CAAV4iEduSaveAsV4 with its prerequisites, set up the run time environment to take into account the use case dictionary, and execute the use case [1].
__

[Top]
#### Where to Find the CAAV4iEduSaveAsV4 Code

__
The CAAV4iEduSaveAsV4 use case is made of two files located in the CAAV4iEduSaveAsV4.m module of the CAACATIAV4Interfaces.edu framework:
  Windows | `InstallRootDirectory/`CAACATIAV4Interfaces`.edu/`CAAV4iEduSaveAsV4`.m/`

The CAAV4iEduSaveAsV4 use case is made of two files located in the CAAV4iEduSaveAsV4.m module of the CAACATIAV4Interfaces.edu framework:
Windows | `InstallRootDirectory/`CAACATIAV4Interfaces`.edu/`CAAV4iEduSaveAsV4`.m/`
Unix | `InstallRootDirectory/`CAACATIAV4Interfaces`.edu/`CAAV4iEduSaveAsV4`.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

There are 4 logical steps in CAAV4iEduSaveAsV4 :

  1. Read the V5 data of the foreign geometry
  2. Make a V4 data block
  3. Change the SaveAsModel behaviour
  4. If necessary, make a V4 spline constraint data

[Top]
#### Read the V5 data of the foreign geometry

      HRESULT CAASurfV4DataSaver::GetData(int & oV4Type, double * & oV4Block)
      {
      ...
      CATIForeignSurface_var forSurf = this;
      ...

---

To access the data of the foreign geometry, read your own V5 geometry implementation. For a curve, replace CATIForeignSurface_var by CATIForeignCurve_var.
__

[Top]
#### Make a V4 data block

        ...
        oV4Type = V4CATGEOType;
        oV4Block = new double[V4Length];
```vbscript
        for (int i=0; i<V4Length; i++)

```

        {
oV4Type = V4CATGEOType;
oV4Block = new double[V4Length];
for (int i=0; i<V4Length; i++)
          oV4Block[i] = ...;

        }
        ...

---

To create the V4 data of the foreign geometry, refer to the V4 CATGEO documentation.

[Top]
#### Change the SaveAsModel behaviour

      HRESULT CAAGobSurfV4DataSaver::GetUserIntent(int & oIntent)
      {
HRESULT CAAGobSurfV4DataSaver::GetUserIntent(int & oIntent)
        HRESULT rc = S_OK;
        oIntent = ...;
        return rc;

      }

---

oIntent is set to

  * 0 : forget this V5 geometry in all the computation, do not fill the GetData method.
  * 1 : do the generic process, do not fill the GetData method.
  * 2 : let the customer do as here before.

[Top]
#### Make a V4 spline constraint data block

        ...
        oV4Type = V4SplineType;
        oV4BlockLength = V4SplineConstraintLength;
        oV4SplineConstraintBlock = new double[V4SplineConstraintLength];
```vbscript
        for (int i=0; i<V4SplineConstraintLength; i++)

```

        {
oV4Type = V4SplineType;
oV4BlockLength = V4SplineConstraintLength;
oV4SplineConstraintBlock = new double[V4SplineConstraintLength];
for (int i=0; i<V4SplineConstraintLength; i++)
          oV4SplineConstraintBlock[i] = ...;

        }
        ...

---

To create the V4 data of the foreign geometry, refer to the V4 CATGEO documentation.

To create the V4 spline data of the foreign geometry, refer to the CATV4iV4Element documentation. If there is no V4 spline data, set the outputs to 0 for the integers and to NULL for the pointer.

[Top]

* * *
### In Short

This use case provides a way to retrieves information of  elements of a model.

_[_Top]

* * *
### References

[1] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[Top]

* * *
### History

Version: **1** [Jul 2003] | Document created
---|---
[Top]

* * *

_Copyright 1994-2003, Dassault Systmes. All rights reserved._
