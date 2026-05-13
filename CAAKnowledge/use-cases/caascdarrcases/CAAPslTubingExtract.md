---
title: "CATIArrBendableString, CATIAArrSystemLineProduct Interfaces Use Case
 "
```vbscript
title: "CATIArrBendableString, CATIAArrSystemLineProduct Interfaces Use Case
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CAAPslTubingExtract", "CATIAArrBendableString", "CATIArrSystemLineProduct", "CATIA", "CATIArrBendableString", "CATIAArrSystemLineProduct"]
source_file: "Doc/online/CAAScdArrUseCases/CAAPslTubingExtract.htmmd"
converted: "2026-05-11T17:31:51.583562"
```

---
## Arrangement

|
## CATIArrBendableString, CATIAArrSystemLineProduct Interfaces Use Case

* * *

 This example shows how to extract Bendable Data from BendableString objects (Pipe with bends, Tube with bends). Help is taken of a macro. This macro has a reference to CATIArrBendableString, CATIAArrSystemLineProduct  Interfaces (referred to as ArrBendableString and as ArrSystemLineProduct in reference Visual Basic document).This macro opens an existing Product document and retrieves the CATIAArrSystemLineProduct selection. Then it obtains the subproducts of this selection, which adhere to CATIAArrBendableString. It then gets the bending details of the ArrBendableString object.
---|---
This example shows how to extract Bendable Data from BendableString objects (Pipe with bends, Tube with bends). Help is taken of a macro. This macro has a reference to CATIArrBendableString, CATIAArrSystemLineProduct  Interfaces (referred to as ArrBendableString and as ArrSystemLineProduct in reference Visual Basic document).This macro opens an existing Product document and retrieves the CATIAArrSystemLineProduct selection. Then it obtains the subproducts of this selection, which adhere to CATIAArrBendableString. It then gets the bending details of the ArrBendableString object.
 PslTubingExtract is launched after CATIA is up and the reference document is opened.PslTubingExtract.CATScript is located in the runtime directory Operating System (say intel_a)/code/command
 CAAPslTubingExtract includes the following steps:

  1. Prolog
  2. Obtain the ArrBendableString Object
  3. Start to get the bending data information from ArrBendableString object
  4. Epilog

#### Prolog

|

      ...
      a) Open the Input Document with Tubing or Piping runs and bendables
      b) Highlight the LineID (Place the line id in CSO)
      c) Run the macro.

      ...

---

Once the Product has been loaded, the macro is designed to read the relevant objects from the model.
#### Obtain the ArrBendableString Object

The ArrSystemLineProduct object is a collection object that manages ArrBendableString object's.

    ...
```vbscript
```vbscript
       Set objCATIAV5Document0 = CATIA.ActiveDocument
```
```

```vbscript
```vbscript
```vbscript
       '//---------- Get Arrworkbench from current document
```vbscript
       Set objCATIAV5ArrWorkbench0 = objCATIAV5Document0.GetWorkbench("ArrWorkbench")
       '//---------- Get current selection
```
```vbscript
       Set objCATIAV5Selection = objCATIAV5Document0.Selection
       Dim objSysLineProduct As ArrSystemLineProduct
       Dim objBendableString As ArrBendableString
       ' Find from the selection list, objects that conform to the CATIAArrSystemLineProduct interface.
```
```vbscript
       Set objSysLineProduct = objCATIAV5Selection.FindObject("CATIAArrSystemLineProduct")
       ' Get the count of subproducts, actual subproduct (methods of CATIArrSystemLineProduct interface)
```
```vbscript
       Dim intNumOfSubProducts As integer
       intNumOfSubProducts = objSysLineProduct.GetSubProductsCount("CATIAArrBendableString")
```
       For intSubProdIndex =1 to intNumOfSubProducts
```vbscript
         Set objBendableString = objSysLineProduct.GetSubItem(intSubProdIndex)
```
```

```

```

    ...

---
#### Start to get the bending data information form ArrBendableString object

    ...
```vbscript
```vbscript
      ' Get Instance Name of the ArrBendableString object
```

      objBendableString.InstanceName
```vbscript
      ' Get number of Segments
```

      int NumOfSegments = objBendableString.GetNumOfSegments
```vbscript
      ' Loop through the segments and get bending data of each segment
```

```

```vbscript
```vbscript
      Dim dblSegmentData(14) As Double
      objBendableString.GetSegmentData intForLooping, dblSegmentData
```
```

```vbscript
```vbscript
```vbscript
      ' The data can be interpreted as follows
      dblStrXCoord        = dblSegmentData(0)
      dblStrYCoord        = dblSegmentData(1)
      dblStrZCoord        = dblSegmentData(2)
```

```

```

      dblEndXCoord        = dblSegmentData(3)
```vbscript
```vbscript
      dblEndYCoord        = dblSegmentData(4)
      dblEndZCoord        = dblSegmentData(5)

```

```

```vbscript
```vbscript
```vbscript
      '//Valid only if Radius > 0
      dblBendNodeXCoord   = dblSegmentData(6)
      dblBendNodeYCoord   = dblSegmentData(7)
      dblBendNodeZCoord   = dblSegmentData(8)
      '//Valid only if Radius > 0
      dblBendRadius       = dblSegmentData(9)
      dblBendAngle        = dblSegmentData(10)
```

```

```

dblBendRadius       = dblSegmentData(9)
```vbscript
```vbscript
dblBendAngle        = dblSegmentData(10)
      dblRotationAngle    = dblSegmentData(11)
      dblSlopeAngle       = dblSegmentData(12)

      dblLinearSegLen     = dblSegmentData(13)

```

```

```vbscript
```vbscript
```vbscript
      '//Arc Len valid only if Radius > 0
      dblArcLen           = dblSegmentData(14)
      ' Store this data for every segment, update the corresponding template and save the data as an excel document
```

```

```

    ...

---
#### Epilog

Thus we saw how to read a CATProduct document, retrieve the objects we are interested in and get more information about the objects

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

Thus we saw how to read a CATProduct document, retrieve the objects we are interested in and get more information about the objects

[Top]

* * *
#### References

[1] | Replaying a macro
---|---
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
