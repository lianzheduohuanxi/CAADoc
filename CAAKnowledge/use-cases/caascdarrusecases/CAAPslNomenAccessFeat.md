---
title: "Untitled"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CAAScrBase", "CATIAArrNomenclatureTrees", "CATIA", "CAAScrJavaScript", "CATIArrNomenclatureTrees", "CAAPslNomenAccessFeat", "CATIArrNomenclatures", "CATIArrNomenclature"]
source_file: "Doc/online/CAAScdArrUseCases/CAAPslNomenAccessFeat.htm"
converted: "2026-05-11T11:27:02.686987"
---

---

 
 
     

Once the Product has been loaded, the macro is designed to read the 
     relevant objects from the model.
     

#### Obtain the ArrNomenclatures object
     
     

#### Start to get the information about ArrNomenclature 
     object from ArrNomenclatures object recursively
     
     

#### Epilog
     

Thus we saw how to read a CATProduct document, retrieve the objects we 
     are interested in and get more information about the objects
     
     
   
 
 
 

 ![](../CAAScrBase/images/aendtask.gif)
 

[Top]

---

 
 

#### In Short
 

Thus we saw how to read a CATProduct document, retrieve the objects we are 
 interested in and get more information about the objects
 

[Top]

---

 
 

#### References
 
 

---

 
 

*Copyright  2000, Dassault Systmes. All rights reserved.*

 

```vbscript
...
  a) Open the Input Document
  b) Run the macro
  ...
```

```vbscript
...
   '//---------- Get Arrworkbench from current document
   Dim objDocument0 As Object
   Set objDocument0 = CATIA.ActiveDocument  
   Dim objArrWorkbench1 As Workbench
   Set objArrWorkbench1 = objDocument0.GetWorkbench  ( &quot;ArrWorkbench&quot; )
   '//---------- Get ArrNomenclatureTree from ArrWorkbench
   Dim objArrNomTree1 As ArrNomenclatureTree
   Set objArrNomTree1 = objArrWorkbench1.ArrNomenclatureTree
```

```vbscript
...
   Dim intK
   Dim objKArrNom As ArrNomenclature
   Dim strIntSysClassName
   Dim strNLSInstanceName
   Dim strIconName
  '// -------- Recursively loop Through each Nomenclature and do the following
   Set objKArrNom = objArrNomTopNode.Item(intK)
   strIntSysClassName = objKArrNom.IntSysClassName
   strNLSInstanceName = objKArrNom.NLSInstanceName
   strIconName = objKArrNom.IconName
   '// ArrNomenclature can contain various subtypes
   Dim objArrSubTypes As ArrNomenclatures
   Set objArrSubTypes = iobjArrNomen.SubTypes
   intNBOfNom = objArrSubtypes.Count
   Dim objJArrNom As ArrNomenclature
   For intJ=1 to intNBOfNom  
   Set objJArrNom = objArrSubTypes.Item(intJ) 
   strNLSInstanceName = objJArrNom.NLSInstanceName
   strIntSysClassName = objJArrNom.IntSysClassName
   strIconName = objJArrNom.IconName
   ' Call recursive function again on objJArrNom
  ...
```

```vbscript
...
End Sub
```