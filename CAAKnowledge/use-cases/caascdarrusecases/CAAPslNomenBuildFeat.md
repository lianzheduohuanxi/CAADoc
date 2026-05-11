---
title: "Untitled"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScrJavaScript", "CAAPslNomenBuildFeat", "CATIArrWorkbench"]
source_file: "Doc/online/CAAScdArrUseCases/CAAPslNomenBuildFeat.htm"
converted: "2026-05-11T11:27:02.686085"
---

---

 
 
     

#### Create the Feat Document
     
     

#### Get Nomenclature data from new document, 
     ArrWorkbench, Save the Feat Document. 
     
     

#### Epilog
     

Thus we saw how to read a CATProduct document, retrieve the interface  
     we are interested in and generate a report on these objects
     
     
   
 
 
 

 ![](../CAAScrBase/images/aendtask.gif)
 

[Top]

---

 
 

#### In Short
 

Thus we saw how to read a CATProduct document, retrieve the interface we are 
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
   Dim objCATIAV5Document0 As Document
   Dim objCATIAV5FeatDocument As Document
   Dim objCATIAV5ArrWorkbench0 As Workbench
   Set objCATIAV5Document0 = CATIA.ActiveDocument
   '//---------- Get Arrworkbench from current document
   Set objCATIAV5ArrWorkbench0 = objCATIAV5Document0.GetWorkbench  ( &quot;ArrWorkbench&quot; ) 
   '//---------- Create a new .feat document 
   Set objCATIAV5FeatDocument = objCATIAV5ArrWorkbench0.CreateFeatDocument (&quot;CATfct&quot;)
...
```

```vbscript
...
   Dim objCATIAV5ArrWorkbench1 As Workbench
   Dim objCATIAV5ArrNomTree1 As ArrNomenclatureTree
   Dim objCATIAV5ArrNomTopNode As ArrNomenclatures
   '//---------- Get Arrworkbench from the new &quot;.feat&quot; document
   Set objCATIAV5ArrWorkbench1 = objCATIAV5FeatDocument.GetWorkbench  ( &quot;ArrWorkbench&quot; ) 
   '//---------- Add a nomenclature hierachy tree to the .feat document 
   Set objCATIAV5ArrNomTree1 = objCATIAV5ArrWorkbench1.AddNomenclatureTree
   '//---------- Access the root of the tree
   Set objCATIAV5ArrNomTopNode = objCATIAV5ArrNomTree1.BaseNomenclatures
   '//----------  Create nomenclature
   Set objCATIAV5oArrNom = objCATIAV5ArrNomTopNode.AddUserNomenclature
            (strFeatIntSysName, strFeatIconName, strFeatNLSName, strFeatSuperTypeName)
   '---------- Save the .feat document
   strOutputFileName = strCATIAV5FeatOutputFileName + &quot;.CATfct&quot;
   '---------- Use the workbench save, so as to remove LifeCycleObject also
   objCATIAV5ArrWorkbench1.SaveFeatDocument strOutputFileName, objCATIAV5FeatDocument
 ...
```

```vbscript
...
End Sub
```