---
title: "Untitled"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CAAScrBase", "CATIAArrBOMReport", "CATIA", "CAAArrPipingBOMReport", "CATIAV5ArrWorkbench", "CATIAArrWorkbench", "CAAScrJavaScript"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrPipingBOMReport.htm"
converted: "2026-05-11T11:06:32.752383"
---

## Arrangement
 
 
## []CATIAV5ArrWorkbench, CATIAArrBOMReport Interfaces Use 
 Case
 
 
 
 

---

 
 
 
 ![](../CAAScrBase/images/atarget.gif)
 |This example shows how to extract a report of Arrangement 
 objects within a document. Help is taken of a macro. This macro has a 
 reference to CATIAArrBOMReport, CATIAV5ArrWorkbench Interfaces (referred to 
 as ArrBOMReport, Workbench in the reference Visual Basic document).

This 
 macro opens an existing Product document and retrieves the 
 CATIAArrWorkbench selection. Then it finds the interface CATIAArrBOMReport. 
 It then generates the BOM report and saves the report.
 
 
 ![](../CAAScrBase/images/ainfo.gif)
 |CATArrPipingBOMReport is launched after CATIA is up and the 
 reference document is opened.

CATArrPipingBOMReport.CATScript is located 
 in the runtime directory Operating System (say intel_a)\code\command
 
 
 ![](../CAAScrBase/images/ascenari.gif)
 |CAAArrPipingBOMReport includes the following steps:

 
- [Prolog] 
 
- [Declare the macro variables]
 
- [Obtain the CATIAArrBOMReport Interface]
 
- [Epilog] 
 
 
#### []Prolog
 
 
 
```
...
 a) Open the Input Document with Arrangement objects.
 b) Run the macro.
 ...
```

 
 
 
 

Once the Product has been loaded, the macro is designed to read the 
 relevant objects from the model.
 

 
#### []Declare the Macro Variables
 
 
 
```
...
 Dim objCATIAV5Document As Document
 Dim objCATIAV5ArrWorkbench As Workbench
 Dim objCATIAV5ArrBOMReport As ArrBOMReport
...
```

 
 
 
 
#### []Obtain the CATIAArrBOMReport Interface
 
 
 
```
...
 Set objCATIAV5Document = CATIA.ActiveDocument

 
'//---------- Get ArrWorkbench from current document

 Set objCATIAV5ArrWorkbench = objCATIAV5Document.GetWorkbench("ArrWorkbench")

 '//---------- Get CATIAArrBOMReport from ArrWorkbench

 Set objCATIAV5ArrBOMReport = objCATIAV5ArrWorkbench.FindInterface ("CATIAArrBOMReport",objCATIAV5Document)
 
 '//---------- Generate the report

 objCATIAV5ArrBOMReport.GenerateBOMReport objCATIAV5Document, strGReportOutputPath

 ' Store this reported data.

 ...
```

 
 
 
 
#### []Epilog
 

Thus we saw how to read a CATProduct document, retrieve the interface  
 we are interested in and generate a report on these objects
 
 
 
```
...
 End Sub
```

 
 
 
 
 
 
 |[[Top]]
 
 
 
 

 ![](../CAAScrBase/images/aendtask.gif)
 

[[Top]]

---

 
 
#### In Short
 

Thus we saw how to read a Product document, retrieve the interface we are 
 interested in and generate a report on these objects.
 

[[Top]]

---

 
 
#### References
 
 
 |[1]
 |Replaying a macro
 
 
 |[[Top]]
 
 
 

---

 
 

*Copyright 2000, Dassault Systmes. All rights reserved.*