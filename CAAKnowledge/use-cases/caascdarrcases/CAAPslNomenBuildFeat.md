---
title: "CATIArrWorkbench Interfaces Use Case"
category: "use-case"
module: "CAAScdArrUseCases"
tags: "["CATIA", "CATIArrWorkbench", "CAAPslNomenBuildFeat"]"
source_file: "Doc/online/CAAScdArrUseCases/CAAPslNomenBuildFeat.htm"
converted: "2026-05-11T17:31:51.580064"
---
## Arrangement

|
## CATIArrWorkbench Interfaces Use Case

* * *

 This example shows how to create a .feat file, read the file, create Nomenclatures and other data and save the file. Help is taken of a macro. This macro has a reference to CATIArrWorkbench Interface (referred to as Workbench in the reference Visual Basic document).
---|---
This example shows how to create a .feat file, read the file, create Nomenclatures and other data and save the file. Help is taken of a macro. This macro has a reference to CATIArrWorkbench Interface (referred to as Workbench in the reference Visual Basic document).
 PslNomenBuildFeat is launched after CATIA is up and the reference document is opened. PslNomenBuildFeat.CATScript is located in the runtime directory Operating System (say intel_a)/code/command
 CAAPslNomenBuildFeat includes the following steps:

  1. Prolog
  2. Create the Feat Document
  3. Get Nomenclature data from new document, ArrWorkbench, Save the Feat Document
  4. Epilog

#### Prolog

|

      ...
      a) Open the Input Document with Arrangement objects.
      b) Run the macro.
      ...

---
#### Create the Feat Document

    ...
```vbscript
```cpp
       Dim objCATIAV5Document0 As Document
```vbscript
```
```vbscript
```cpp
       Dim objCATIAV5FeatDocument As Document
       Dim objCATIAV5ArrWorkbench0 As Workbench
       Set objCATIAV5Document0 = CATIA.ActiveDocument
```
```

```

```

```vbscript
```vbscript
```vbscript
       '//---------- Get Arrworkbench from current document
```cpp
       Set objCATIAV5ArrWorkbench0 = objCATIAV5Document0.GetWorkbench  ( "ArrWorkbench" )
       '//---------- Create a new .feat document
```
```cpp
       Set objCATIAV5FeatDocument = objCATIAV5ArrWorkbench0.CreateFeatDocument ("CATfct")
```
```

```

```

    ...

---
#### Get Nomenclature data from new document, ArrWorkbench, Save the Feat Document.

    ...
```vbscript
```cpp
       Dim objCATIAV5ArrWorkbench1 As Workbench
```vbscript
```
```vbscript
```cpp
       Dim objCATIAV5ArrNomTree1 As ArrNomenclatureTree
       Dim objCATIAV5ArrNomTopNode As ArrNomenclatures
```
```

```

```

```vbscript
```vbscript
```vbscript
       '//---------- Get Arrworkbench from the new ".feat" document
```cpp
       Set objCATIAV5ArrWorkbench1 = objCATIAV5FeatDocument.GetWorkbench  ( "ArrWorkbench" )
       '//---------- Add a nomenclature hierachy tree to the .feat document
```
```cpp
       Set objCATIAV5ArrNomTree1 = objCATIAV5ArrWorkbench1.AddNomenclatureTree
       '//---------- Access the root of the tree
```
```cpp
       Set objCATIAV5ArrNomTopNode = objCATIAV5ArrNomTree1.BaseNomenclatures
       '//----------  Create nomenclature
```
```cpp
       Set objCATIAV5oArrNom = objCATIAV5ArrNomTopNode.AddUserNomenclature
```
```

```

                (strFeatIntSysName, strFeatIconName, strFeatNLSName, strFeatSuperTypeName)
```vbscript
       '---------- Save the .feat document
```

       strOutputFileName = strCATIAV5FeatOutputFileName + ".CATfct"
```vbscript
       '---------- Use the workbench save, so as to remove LifeCycleObject also
```

```

```vbscript
```vbscript
'---------- Save the .feat document
```

strOutputFileName = strCATIAV5FeatOutputFileName + ".CATfct"
```vbscript
'---------- Use the workbench save, so as to remove LifeCycleObject also
```

       objCATIAV5ArrWorkbench1.SaveFeatDocument strOutputFileName, objCATIAV5FeatDocument
```

     ...

---
#### Epilog

Thus we saw how to read a CATProduct document, retrieve the interface  we are interested in and generate a report on these objects

    ...
```vbscript
```vbscript
    End Sub

```
```

---

![image](../../assets/images/aendtask.gif)

[Top]

* * *
#### In Short

Thus we saw how to read a CATProduct document, retrieve the interface we are interested in and generate a report on these objects.

[Top]

* * *
#### References

[1] | Replaying a macro
---|---
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
