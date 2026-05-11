---
title: "Untitled"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CATIAArrSystemLineProduct", "CAAScrBase", "CATIA", "CAAScrJavaScript", "CATIArrBendableString", "CATIArrSystemLineProduct", "CATIAArrBendableString", "CAAPslTubingExtract"]
source_file: "Doc/online/CAAScdArrUseCases/CAAPslTubingExtract.htm"
converted: "2026-05-11T11:27:02.679919"
---

---

 
 
     

Once the Product has been loaded, the macro is designed to read the 
     relevant objects from the model.
     

#### Obtain the ArrBendableString Object
     

The ArrSystemLineProduct object is a collection object that manages 
     ArrBendableString object's.
     
     

#### Start to get the bending data information form 
     ArrBendableString object
     
     

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
  a) Open the Input Document with Tubing or Piping runs and bendables
  b) Highlight the LineID (Place the line id in CSO)
  c) Run the macro.	
  ...
```

```vbscript
... 
   Set objCATIAV5Document0 = CATIA.ActiveDocument

   '//---------- Get Arrworkbench from current document
   Set objCATIAV5ArrWorkbench0 = objCATIAV5Document0.GetWorkbench(&quot;ArrWorkbench&quot;) 

   '//---------- Get current selection
   Set objCATIAV5Selection = objCATIAV5Document0.Selection
   Dim objSysLineProduct As ArrSystemLineProduct
   Dim objBendableString As ArrBendableString

   ' Find from the selection list, objects that conform to the CATIAArrSystemLineProduct interface.
   Set objSysLineProduct = objCATIAV5Selection.FindObject(&quot;CATIAArrSystemLineProduct&quot;)

   ' Get the count of subproducts, actual subproduct (methods of CATIArrSystemLineProduct interface)
   Dim intNumOfSubProducts As integer
   intNumOfSubProducts = objSysLineProduct.GetSubProductsCount(&quot;CATIAArrBendableString&quot;) 
   For intSubProdIndex =1 to intNumOfSubProducts
     Set objBendableString = objSysLineProduct.GetSubItem(intSubProdIndex)
...
```

```vbscript
... 
  ' Get Instance Name of the ArrBendableString object 
  objBendableString.InstanceName 
  ' Get number of Segments 
  int NumOfSegments = objBendableString.GetNumOfSegments 
  ' Loop through the segments and get bending data of each segment 
  Dim dblSegmentData(14) As Double 
  objBendableString.GetSegmentData intForLooping, dblSegmentData 
  ' The data can be interpreted as follows  
  dblStrXCoord        = dblSegmentData(0)
  dblStrYCoord        = dblSegmentData(1)
  dblStrZCoord        = dblSegmentData(2)

  dblEndXCoord        = dblSegmentData(3)
  dblEndYCoord        = dblSegmentData(4)
  dblEndZCoord        = dblSegmentData(5)

  '//Valid only if Radius &gt; 0
  dblBendNodeXCoord   = dblSegmentData(6)
  dblBendNodeYCoord   = dblSegmentData(7)
  dblBendNodeZCoord   = dblSegmentData(8)

  '//Valid only if Radius &gt; 0
  dblBendRadius       = dblSegmentData(9)
  dblBendAngle        = dblSegmentData(10)

  dblRotationAngle    = dblSegmentData(11)
  dblSlopeAngle       = dblSegmentData(12)

  dblLinearSegLen     = dblSegmentData(13)
  '//Arc Len valid only if Radius &gt; 0
  dblArcLen           = dblSegmentData(14) 
  ' Store this data for every segment, update the corresponding template and save the data as an excel document 
...
```

```vbscript
...
End Sub
```