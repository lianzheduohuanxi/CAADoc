---
```vbscript
title: "Testing the Position of a Point inside a Face or a Volume "
category: "use case"
module: "CAACgmModel"
tags: ["CATICGMPositionPtFaceOperator", "CAAGMModelPositionOpe", "CAAGMModelInterfaces", "CATICGMPositionPtVolOperator"]
source_file: "Doc/online/CAACgmModel/CAACgmUcPtPosition.htmmd"
converted: "2026-05-11T17:33:48.514152"
```

---
Testing the Position of a Point inside a Face or a Volume

    ---

    		Use Case

    		Abstract
    		You can test whether a point is inside or on the boundary of a face
    		or a volume by
    		using the CATICGMPositionPtFaceOperator and CATICGMPositionPtVolOperator operators.

            * Operator to be Used

            * Use Case Description

            * References

    ---

    Operator to be Used
    Use CATICGMPositionPtFaceOperator  and CATICGMPositionPtVolOperator. These operators
    are created by using the CATCGMCreatePositionPtFaceOperator and CATCGMCreatePositionPtVolOperator
    global functions.

    Use Case Description
    The CAAGMModelPositionOpe.m module in CAAGMModelInterfaces.edu
    illustrates how to test the inclusion of a point inside a volume or a face. This use case
    constructs its input data. If you are not already
    familiar with geometric modeler use cases, go to

    [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md).
The CAAGMModelPositionOpe.m module in CAAGMModelInterfaces.edu
illustrates how to test the inclusion of a point inside a volume or a face. This use case
constructs its input data. If you are not already
familiar with geometric modeler use cases, go to
    With the input data below:

      Fig.1 Point Inclusion:  Input
    	data

    	The point pointOnFace (in blue) relies on the bottom face ( x=4.008, y=4.996, z=0.996), the
    	point pOUT (in yellow) is located at 5., 5., 5.

    	![Point Inclusion](images/CGM_point_inclusion_0.png)

    ---

    the code below:

    CATICGMPositionPtVolOperator * pPositionPtVolOpe1 =::CATCGMCreatePositionPtVolOperator(piGeomFactory, &topdata;,
CATICGMPositionPtVolOperator * pPositionPtVolOpe1 =::CATCGMCreatePositionPtVolOperator(piGeomFactory, &topdata;,
    		pOUT, pVolume);

    ...
CATICGMPositionPtVolOperator * pPositionPtVolOpe1 =::CATCGMCreatePositionPtVolOperator(piGeomFactory, &topdata;,
pOUT, pVolume);
    CATLocation loc1 = pPositionPtVolOpe1->GetLocationResult(#);
    	if (loc1==CATLocationOuter)
    		cout << "math point(5., 5.,5.) is outside" << endl;
    	else

    ...

---
returns

    "math point(5., 5.,5.) is outside"

returns
on the standard output. The code below (pointOnFace relies on a bordering face):

    CATICGMPositionPtVolOperator * pPositionPtVolOpe2 =::CATCGMCreatePositionPtVolOperator(piGeomFactory, &topdata;,
    		pointOnFace, pVolume);

    ...
on the standard output. The code below (pointOnFace relies on a bordering face):
CATICGMPositionPtVolOperator * pPositionPtVolOpe2 =::CATCGMCreatePositionPtVolOperator(piGeomFactory, &topdata;,
pointOnFace, pVolume);
    CATLocation loc2 = pPositionPtVolOpe2->GetLocationResult(#);
```vbscript
    	if (loc2==CATLocationFull)

```

    	{
pointOnFace, pVolume);
CATLocation loc2 = pPositionPtVolOpe2->GetLocationResult(#);
if (loc2==CATLocationFull)
    		cout << "math point with coordinates " << endl;
    		cout << pointOnFace.GetX(#) << " " << pointOnFace.GetY(#) << " " << pointOnFace.GetZ(#) << endl;
            cout << "is on the volume border " << endl;

    	}
    	...

---
returns

returns
    math point with coordinates
    4.00772 4.99616 0.996126
    is on the volume border

The code below:

    CATICGMPositionPtFaceOperator *pPositionPtFaceOpe =::CATCGMCreatePositionPtFaceOperator(piGeomFactory, pConfig,
    		surParam, theFaceOnWhichICreateAPoint);

    ...
The code below:
CATICGMPositionPtFaceOperator *pPositionPtFaceOpe =::CATCGMCreatePositionPtFaceOperator(piGeomFactory, pConfig,
surParam, theFaceOnWhichICreateAPoint);
```vbscript
    if ( (pPositionPtFaceOpe->GetOneResult(#) )==CATLocationInner)

```

    	{
CATICGMPositionPtFaceOperator *pPositionPtFaceOpe =::CATCGMCreatePositionPtFaceOperator(piGeomFactory, pConfig,
surParam, theFaceOnWhichICreateAPoint);
if ( (pPositionPtFaceOpe->GetOneResult(#) )==CATLocationInner)
    		cout << "math point with coordinates " << endl;
    		cout << pointOnFace.GetX(#)  << " " << pointOnFace.GetY(#) << " " << pointOnFace.GetZ(#) << endl;
    		cout <<  "is INSIDE (not on the boundary of) the face  " <<  theFaceOnWhichICreateAPoint->GetPersistentTag(#) << endl;

    	}
    ...

---
returns

returns
    math point with coordinates
    4.00772 4.99616 0.996126
    is INSIDE (not on the boundary of) the face  53

References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)

[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)
[4] |  [How to Use Geometric Operators](CAACgmUcGMModelOpeOverw.md)
History Version: **1** [Feb 2014] | Document created
---|---
