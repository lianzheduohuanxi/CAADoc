---
title: "Creating a Schematic Document"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CATIA", "CAASchCreateSchDocument2", "CAAScdSchUseCases"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchCreateSchDocument2.htm"
converted: "2026-05-11T17:31:51.345185"
---
## Schematics Platform Modeler

| 
## Creating a Schematic Document  
  
  
* * *

 This macro shows you how to create a new schematic document. Schematic documents for DS provided Schematic applications are all of the same kind. They are all special CATProduct document. Instead of having typical 3D viewers, these Schematic documents have 2D viewers embedded in them. Therefore, when using the standard way of creating a new document, an additional step is required to initialize this new document the "Schematic way". This macro illustrates this important step.  
---|---  
 CAASchCreateSchDocument2 is launched in CATIA [1]. No open document is needed. [ CAASchCreateSchDocument2.CATScript ](CAASchCreateSchDocument2Source.md)is located in the CAAScdSchUseCases module. [Execute macro](macros/CAASchCreateSchDocument2.CATScript) (Windows only).  
 CAASchCreateSchDocument2 includes the following steps:

  1. Prolog
  2. Initialize the new Schematic document the "schematic way"
  3. Get the current CNEXT session
  4. Create a new schematic document
  5. Set the drawing standard

#### Prolog

The macro first creates a new document.. |     ...  
```vbscript
    '--------------------------------------------------------------------------  
    ' Create a CATProduct document  
    '--------------------------------------------------------------------------  
```

```vbscript
    Dim objSchDoc As Document  
    Set objSchDoc = CATIA.Documents.Add ("CATProduct")  
    ...  
```

```

---  
#### Initialize the new Schematic document the "schematic way"

    ...  
```vbscript
         '---------------------------------------------------------------------  
         ' Regular CATProduct is a 3D document and is associated with a 3D  
         ' editor and a 3D viewer. On the other hand a schematic document  
         ' is a special CATProduct document that is associated with a special  
         ' 2D viewer and 2D editor. Therefore, we need to trigger the  
         ' documentation initialization (which has already been done in    
         ' CATDocuments.Add) again after associating schematic    
         ' behavior to the document,   
         ' by saving the document and re-opening it again.  
         '---------------------------------------------------------------------  
```

         objSchDoc.SaveAs strDocName  
  
         objSchDoc.Close  
  
```vbscript
         Set objSchDoc = CATIA.Documents.Open (strDocName)  
    ...  
```

```

---  
#### Set the drawing standard of the drafting viewer in the schematic document

A schematic document has a drafting viewer embedded in it. The drawing standard of that drafting viewer can be set by calling the SetDrawingStandard method. This macro also illustrates how to use the GetDrawingStandard method to retrieve the drawing standard of a schematic document.

    ...  
```vbscript
         '---------------------------------------------------------------------  
         ' Set the drawing standard if needed   
         '---------------------------------------------------------------------  
```

```vbscript
         If ( Not ( objSchRoot Is Nothing ) ) Then  
            objSchRoot.SetDrawingStandard catISO  
            strMessage = strMessage & "drawing standard set to catISO" & vbCr  
```vbscript
            Dim std As CatDrawingStandard  
            std = objSchRoot.GetDrawingStandard  
            strMessage = strMessage & "drawing standard = " & std & vbCr  
         End If  
    ...  
```

```

---  
  
[Top]

* * *
#### In Short

This use case shows how to create a schematic document. A message logging the status of the critical steps is displayed at the end of the use case. 

![](images/CAASchCreateSchDocument2.jpg)

[Top]

* * *
#### References

[1] | [ Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)  
---|---  
[Top]  
  
* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
