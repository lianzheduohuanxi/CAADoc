---
title: "Untitled"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CATIAV5ArrWorkbench", "CATIAArrBOMReport", "CAAScrBase", "CATIA", "CAAScrJavaScript", "CATIAArrWorkbench", "CAAArrPipingBOMReport"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrPipingBOMReport.htmmd"
converted: "2026-05-11T11:27:02.681913"
---

---

 
 
     

Once the Product has been loaded, the macro is designed to read the 
     relevant objects from the model.
     

     

#### Declare the Macro Variables
     
     

#### Obtain the CATIAArrBOMReport Interface
     
     

#### Epilog
     

Thus we saw how to read a CATProduct document, retrieve the interface  
     we are interested in and generate a report on these objects
     
     
   
   
     [Top]
   
 
 
 

 ![image](../../assets/images/aendtask.gif)
 

[Top]

---

 
 

#### In Short
 

Thus we saw how to read a Product document, retrieve the interface we are 
 interested in and generate a report on these objects.
 

[Top]

---

 
 

#### References
 
 

---

 
 

*Copyright  2000, Dassault Systmes. All rights reserved.*
 
 
 

 

```vbscript
...
  a) Open the Input Document with Arrangement objects.
  b) Run the macro.
  ...
```

```vbscript
...
```cpp
   Dim objCATIAV5Document As Document
   Dim objCATIAV5ArrWorkbench As Workbench
   Dim objCATIAV5ArrBOMReport As ArrBOMReport
...
```
```

```vbscript
...
```cpp
   Set objCATIAV5Document = CATIA.ActiveDocument

   '//---------- Get ArrWorkbench from current document
```
```cpp
   Set objCATIAV5ArrWorkbench = objCATIAV5Document.GetWorkbench(&quot;ArrWorkbench&quot;)
   '//---------- Get CATIAArrBOMReport from ArrWorkbench
```
```cpp
   Set objCATIAV5ArrBOMReport = objCATIAV5ArrWorkbench.FindInterface (&quot;CATIAArrBOMReport&quot;,objCATIAV5Document)
   '//---------- Generate the report
```
   objCATIAV5ArrBOMReport.GenerateBOMReport objCATIAV5Document, strGReportOutputPath
   ' Store this reported data.
  ...
```

```vbscript
...
```vbscript
 End Sub
```
```