---
```vbscript
title: "Reading Migration Report of a Model"
category: "use case"
module: "CAAV4iUseCases"
tags: ["CATIAV4Interfaces", "CAACATIAV4Interfaces", "CAAV4iMigrationReportExtraction"]
source_file: "Doc/online/CAAV4iUseCases/CAAV4iMigrationReportUseCase.htm"
converted: "2026-05-11T17:33:45.775884"
```

---
# 3D PLM PPR Hub Open Gateway

|
## V4 Access

|
### Reading Migration Report of a Model

_Working with the elements of model_
---|---|---
Use Case

* * *
### Abstract

This article shows how to read Migration Report

  * **What You Will Learn With This Use Case**
  * **o The CAAV4iMigrationReportExtraction Use Case**
    * What Does CAAV4iMigrationReportExtraction Do
    * How to Launch CAAV4iMigrationReportExtraction
    * Where to Find the CAAV4iMigrationReportExtraction Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

This use case is intended to show you how to read Migration Report of a model.

[Top]
### The CAAV4iMigrationReportExtraction Use Case

CAAV4iMigrationReportExtraction is a use case of the CAACATIAV4Interfaces.edu framework that illustrates CATIAV4Interfaces framework capabilities.

[Top]
#### What Does CAAV4iMigrationReportExtraction Do

CAAV4iMigrationReportExtraction is a use case of the CAACATIAV4Interfaces.edu framework that illustrates CATIAV4Interfaces framework capabilities.
The CAAV4iMigrationReportExtraction reads the Migration report file in ReadReportFile().
Then it creates a session and open the .CATPart (in OpenDocument(pfileNamePart, pDoc)) provided in input.
From this pDoc we get the entities of the part with GetListOfBodies() and stored in bodyList object
Now migrated object decoding is done and gets the Type.
If Type == 1, we retrieve the V4 model’s corresponding V5 object from RetrieveObject() and print its name
```vbscript
If Type == 2, it’s an attribute of the previous found V5 object and print attributes value.
```

The output looks like :

    attributcxr1.model   0000000000000000    OK

    *MASTER   0000000000000000    OK

    *SET1   0000000000000000    OK

    *LN1   0000000012226890    OK
           0000000012226890   Att.:  discret 1  Val.: value discret 1
           0000000012226890   Att.:  discret 2  Val.: bbbb discret 2
           0000000012226890   Att.:  numeric 1  Val.: 10
           0000000012226890   Att.:  numeric 2  Val.: -1.#QNAN
           0000000012226890   Att.:  numeric 3  Val.: 30
           0000000012226890   Att.:  alpha 1  Val.: TEXT1
           0000000012226890   Att.:  alpha 2  Val.:
           0000000012226890   Att.:  binaire 1  Val.:
           0000000012226890   Att.:  binaire 2  Val.:

    *LN2   000000001222A370    OK
0000000012226890   Att.:  alpha 2  Val.:
0000000012226890   Att.:  binaire 1  Val.:
0000000012226890   Att.:  binaire 2  Val.:
           000000001222A370   Att.:  discret 2  Val.: bbbb discret 1
           000000001222A370   Att.:  numeric 2  Val.: 20
           000000001222A370   Att.:  alpha 2  Val.: TEXT2
           000000001222A370   Att.:  binaire 2  Val.:

    *LN3   0000000012229A10    OK
000000001222A370   Att.:  numeric 2  Val.: 20
000000001222A370   Att.:  alpha 2  Val.: TEXT2
000000001222A370   Att.:  binaire 2  Val.:
           0000000012229A10   Att.:  numeric 3  Val.: 100

    *LN4   0000000012309F70    OK

Close the report,release the buffer,remove the pDoc and finally delete the session. if the reading failed, code returns an error with rc = 1.
#### How to Launch CAAV4iMigrationReportExtraction

Close the report,release the buffer,remove the pDoc and finally delete the session. if the reading failed, code returns an error with rc = 1.
To launch CAAV4iMigrationReportExtraction, you will need to set up the build time environment, then compile CAAV4iMigrationReportExtraction along with its prerequisites, set up the run time environment, and then execute the use case [1].
CAAV4iMigrationReportExtraction takes two parameters.

mkrun -c CAAV4iMigrationReportExtraction PathReport PathPart

Where:

  PathReport: is the complete path of the report file
  PathPart : is the complete path of the CATPart file.

You can use the model attribut.CATPart located in CAACATIAV4Interfaces.edu/InputData

  * Windows : `InstallRootDirectory\CAA``CATIAV4Interfaces``.edu\InputData`
  * Unix : `InstallRootDirectory/CAA``CATIAV4Interfaces``.edu/InputData`

[Top]
#### Where to Find the CAAV4iMigrationReportExtraction Code

The CAAV4iMigrationReportExtraction use case is made of a single file located in the CAAV4iMigrationReportExtraction.m module of the CAACATIAV4Interfaces.edu framework:
The CAAV4iMigrationReportExtraction use case is made of a single file located in the CAAV4iMigrationReportExtraction.m module of the CAACATIAV4Interfaces.edu framework:
  Windows | `InstallRootDirectory\CAACATIAV4Interfaces.edu\`CAAV4iMigrationReportExtraction`.m\`

The CAAV4iMigrationReportExtraction use case is made of a single file located in the CAAV4iMigrationReportExtraction.m module of the CAACATIAV4Interfaces.edu framework:
Windows | `InstallRootDirectory\CAACATIAV4Interfaces.edu\`CAAV4iMigrationReportExtraction`.m\`
Unix | `InstallRootDirectory/CAACATIAV4Interfaces.edu/`CAAV4iMigrationReportExtraction`.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
There are 4 logical steps in CAAV4iMigrationReportExtraction :

  1. Opening the report file
  2. Opening the model
  3. Get the entities of the part
  4. Migrated object decoding
  5. Retrieving the object and its attribute

[Top]
#### Opening the report file

    ...
       const char *pfileNameReport =  iArgv[1];
       CATUnicodeString Name(pfileNameReport);
       int errread= ::ReadReportFile(Name, Buffer, LgBuffer, FileDesc, ier );

    ...

---

[Top]
#### Opening the model

    ...

      // The second argument of CAAV4iMigrationReportExtraction is complete path of the CATPart file.

      const char *pfileNamePart =  iArgv[2];
      // open the v5 document
const char *pfileNamePart =  iArgv[2];
      CATDocument *pDoc = NULL;
      HRESULT hr = CATDocumentServices::OpenDocument( pfileNamePart, pDoc) ;

    ...

---

[Top]
#### Get the entities of the part

    ...
      CATListValCATBaseUnknown_var bodyList;
     int errlst = GetListOfBodies(pDoc,bodyList );
    ...

---

[Top]
#### Migrated object decoding

    ...
    PathReport: Reportfile is present in
PathReport: Reportfile is present in
    CAACATIAV4Interfaces.edu\CNext\resources\graphic\MigrationReportExtraction\report.txt

    Report Structure:

      //                   Element 1
     //                                  ATT 1 : Value
      //                                  ATT 2 : Value
      //                                  ....
      //                   Element 2
           --------------------------------------------------------
    Report snippet :

    attributcxr1.model | OK
       *MASTER         | OK
          *SET1        | OK
             *LN1      | OK
                       | discret 1        : value discret 1
                       | discret 2        : bbbb discret 2
                       | numeric 1        : 10 …

    --------------------------------------------------------

    int erdec = ::DecodeLine (Line, Start, End, Type, Label, Value);

    DecodeLine () function to read element and attribute from report file.
      // decode a line
      //                   oType = 1 -> element;          : Label | Value
      //                   oType = 2 -> attribute;               :       | Label : Value
      // for each type=>  Label and Value are returned
    ...

---

[Top]
#### Retrieving the object and its attribute

```vbscript
If above calculated Type from DecodeLine () equals to 1, it retrieve v4 element’s corresponding V5 object.

```

    ...
            // retrieving migrated object, using modified label
            // ( because wsp name is repeated in migrated object name)
            // ex V4 Name: *SOL1
            // ex V5 Name: PartBody ( *SOL1 - wsp *MASTER -  )

              CATUnicodeString Name =  "( " + Label; // Label = *SOL1, *LN1, etc..
              int err = ::RetrieveObject(bodyList, Name, pObj);

    …

    …
    If Type from DecodeLine () equals to 2
            // it’s an attribute of the previous found object
            // Attribute: Label, Value
    …

    Output of above Retrieving the object and its attribute is below

    ----------------------------------------------------------------------------------------------------------------------------
    attributcxr1.model   0000000000000000    OK

    *MASTER   0000000000000000    OK

    *SET1   0000000000000000    OK

    *LN1   0000000012226890    OK
           0000000012226890   Att.:  discret 1  Val.: value discret 1
           0000000012226890   Att.:  discret 2  Val.: bbbb discret 2
           0000000012226890   Att.:  numeric 1  Val.: 10

    ----------------------------------------------------------------------------------------------------------------------------

---
### Close the report file and delete buffer

    ...

       // close the report file and delete buffer
       int errclose = ::CloseReportFile(Buffer,FileDesc,ier);
    ...

---
### Release the loaded document

    ...
           CATDocumentServices::Remove (*pDoc);
    ...

---
### Delete the session

    ...

    hrs = ::Delete_Session(pSessionName);
    ...

---

[Top]

* * *
### In Short

These sample show a way to read Migration Report of a model.

_[_Top]

* * *
### References

[1] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[Top]

* * *
### History

Version: **1** [Jan 2014] | Document created
---|---
[Top]

* * *

_Copyright 1994-2003, Dassault Systmes. All rights reserved._
