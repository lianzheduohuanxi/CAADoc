---
```vbscript
title: "Retrieving Data of an Element of a V4 Document"
category: use-case case"
module: "CAAV4iUseCases"
tags: ["CAADoc", "CAACATIAV4Interfaces", "CAAV4iV4DataAccess", "CAAV4iEduV4DataAccess", "CATIAV4Interfaces"]
source_file: "Doc/online/CAAV4iUseCases/CAAV4iDataAccessUseCase.htmmd"
converted: "2026-05-11T17:33:45.752658"
```

---
# 3D PLM PPR Hub Open Gateway

|
## V4 Access

|
### Retrieving Data of an Element of a V4 Document

_Get the information contained in a model_
---|---|---
Use Case

* * *
### Abstract

This article shows how to retrieves data of a V4 element.

  * **What You Will Learn With This Use Case**
  * **The CAAV4iEduV4DataAccess Use Case**
    * What Does CAAV4iV4DataAccess Do
    * How to Launch CAAV4iEduV4DataAccess
    * Where to Find the CAAV4iEduV4DataAccess Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

This use case is intended to show you how to retrieve data of an element of a model.

[Top]
### The CAAV4iEduV4DataAccess Use Case

CAAV4iEduV4DataAccess is a use case of the CAACATIAV4Interfaces.edu framework that illustrates CATIAV4Interfaces framework capabilities.

[Top]
#### What Does CAAV4iEduV4DataAccess Do

CAAV4iEduV4DataAccess is a use case of the CAACATIAV4Interfaces.edu framework that illustrates CATIAV4Interfaces framework capabilities.
CAAV4iEduV4DataAccess begins by opening the _.model_ document.
Then, it scans the model using functions of CATIAV4Interfaces to get the element to be analyzed [1]. These elements are objects of the class CATV4iV4Element.
In this particular case, it retrieves the first element of the first set of the workspace MASTER.
Finally, data of the element are retrieved : the identificator, the primary and secondary types, the number of the layer of the element and some graphical information about the element.
The elements are removed.

[Top]
#### How to Launch CAAV4iEduV4DataAccess

The elements are removed.
To launch CAAV4iEduV4DataAccess , you will need to set up the build time environment, then compile CAAV4iEduV4DataAccess along with its prerequisites, set up the run time environment, and then execute the use case [2].
CAAV4iEduV4DataAccess takes two parameters.

mkrun -c **CAAV4iEduV4DataAccess** InputModel  OutputFile

Where:

  InputModel : the full path of the model
  OutputFile : the full path of the output text file.

You can use the model `CUBE.model` located in `CAADoc/``CAA``CATIAV4Interfaces``.edu/CNext/resources/graphic`

  * Windows : `InstallRootDirectory/CAADoc/CAA``CATIAV4Interfaces``.edu/CNext/resources/graphic`
  * Unix : `InstallRootDirectory/CAADoc/CAA``CATIAV4Interfaces``.edu/CNext/resources/graphic`

[Top]
#### Where to Find the CAAV4iEduV4DataAccess Code

The CAAV4iEduV4DataAccess use case is made of a single file located in the CAAV4iEduV4DataAccess.m module of the CAACATIAV4Interfaces.edu framework:
The CAAV4iEduV4DataAccess use case is made of a single file located in the CAAV4iEduV4DataAccess.m module of the CAACATIAV4Interfaces.edu framework:
  Windows | `InstallRootDirectory/`CAACATIAV4Interfaces`.edu/`CAAV4iEduV4DataAccess`.m/`

The CAAV4iEduV4DataAccess use case is made of a single file located in the CAAV4iEduV4DataAccess.m module of the CAACATIAV4Interfaces.edu framework:
Windows | `InstallRootDirectory/`CAACATIAV4Interfaces`.edu/`CAAV4iEduV4DataAccess`.m/`
Unix | `InstallRootDirectory/`CAACATIAV4Interfaces`.edu/`CAAV4iEduV4DataAccess`.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

There are 3 logical steps in CAAV4iEduV4DataAccess :

There are 3 logical steps in CAAV4iEduV4DataAccess :
  1. Opening the model
  2. Scaning the model
  3. Retrieving the data

[Top]
#### Opening the model

    ...
      char* pathname = argv[1];
      CATDocument * doc=NULL;
      CATUnicodeString filename( pathname );
      CATDocumentServices::OpenDocument( filename, doc, readOnlyFlag );

    ...

---

CATDocumentServices::OpenDocument( filename, doc, readOnlyFlag );
To access to the data of the model, a CATDocument is needed.
The path of the model passed in argument is converted to a CATString and is used to open the model in "read only" mode.
__

[Top]
#### Scaning the model

    ...
      CATV4iV4Element* masterElem=NULL;
      CATV4iV4Element* setElem=NULL;
      CATV4iV4Element* element=NULL;
      int end =0;
```vbscript
      if (! CATV4iGetMaster(doc, masterElem, ier) )

```

      {
CATV4iV4Element* setElem=NULL;
CATV4iV4Element* element=NULL;
int end =0;
if (! CATV4iGetMaster(doc, masterElem, ier) )
```vbscript
```vbscript
        if (! CATV4iGisset(masterElem, setElem, end, ier) )

```

```

        {
int end =0;
if (! CATV4iGetMaster(doc, masterElem, ier) )
```vbscript
```vbscript
if (! CATV4iGisset(masterElem, setElem, end, ier) )
          if (! CATV4iGisels(setElem, NULL, element, end, ier) )

```

```

          {
    ...

---

CATV4iGetMaster is a functions that retrieves the first workspace of the model : the MASTER. If _doc_ is not a V4 document, the function fails.
CATV4iGisset retrieves the first set of the workspace _masterElem_.
CATV4iGisels retrieves the first element of the set _setElem_.

[Top]
#### Retrieving the data

    ...
              CATString identificator=element->GetId(#);
    ...
CATString identificator=element->GetId(#);
              int itp, its;
              element->GetType(itp, its);

    ...
CATString identificator=element->GetId(#);
int itp, its;
element->GetType(itp, its);
              int layer =-1;
```vbscript
              result = CATV4iGirlay(element, layer, ier);

```

    ...
element->GetType(itp, its);
int layer =-1;
result = CATV4iGirlay(element, layer, ier);
              int oShow=-1, oPick=-1, oCol=-1, oBlink=-1, oThick=-1, oLine=-1;
```vbscript
              result = CATV4iGirvis( element, oShow, oPick, oCol, oBlink, oThick, oLine, ier);

```

    ...

---

result = CATV4iGirvis( element, oShow, oPick, oCol, oBlink, oThick, oLine, ier);
```vbscript
If _element_ has been correctly created by CATV4iGisels, the data can be retrieved.
```

_element- >Id(#)_ retrieves the identificator of the _element_ ,
_element- >GetType(...)_ retrieves the primary and the secondary types of _element_
_...CATV4iGirlay(..._ retrieves the number of the layer
_...CATV4iGirvis(..._ retrieves graphical data about the element : show, pickable, color, blink, steady, thickness, line type.

[Top]

* * *
### In Short

This use case provides a way to retrieves information of  elements of a model.

_[_Top]

* * *
### References

[1] | [Scanning the model](CAAV4iScanUseCase.md)
---|---
[2] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
[Top]

* * *
### History

Version: **1** [Jul 2003] | Document created
---|---
[Top]

* * *

_Copyright 1994-2003, Dassault Systmes. All rights reserved._
