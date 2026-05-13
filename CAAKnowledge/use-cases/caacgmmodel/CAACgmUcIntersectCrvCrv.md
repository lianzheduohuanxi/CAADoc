---
title: "Intersecting Curves"
category: "use-case case"
module: "CAACgmModel"
tags: "["CATICGMIntersectionCrvCrv", "CAAGMModelGeometryCreation", "CAAGMModelInterfaces", "CAAGMModelIntersectionOpe"]"
source_file: "Doc/online/CAACgmModel/CAACgmUcIntersectCrvCrv.htm"
converted: "2026-05-11T17:33:48.444003"
---
# Intersecting  Curves

---
Use Case
## Abstract

Curves can be intersected by using the CATICGMIntersectionCrvCrv operator. The result is a set of geometrical objects (points, curves or a combination of these objects) that you have to scan.
    * Operator to be Used
    * Use Case Description
    * References
---
## Operator to be Used

Use CATICGMIntersectionCrvCrv. This operator is created by using the CATCGMCreateIntersection global function.
## Use Case Description

Use CATICGMIntersectionCrvCrv. This operator is created by using the CATCGMCreateIntersection global function.
The CAAGMModelIntersectionOpe.m module in CAAGMModelInterfaces.edu illustrates how to intersect curves. This use case constructs its input data and requires the CAAGMModelGeometryCreation.m module. You have to specify this module in your Imakefile.mk file.  If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md).

With the input data below:

Fig.1 Intersection of Curves:  Input data  ![Curve Intersection](images/CGM_intersect_crvCrv_0.png)

---

With the input data below:
Fig.1 Intersection of Curves:  Input data  ![Curve Intersection](images/CGM_intersect_crvCrv_0.png)
the code below:

    CATICGMIntersectionCrvCrv * pPtCrvCrv =:: CATCGMCreateIntersection(
    		piGeomFactory,
    		pConfig,
    		piNurbsCurve,
    		piNurbsCurve1);

    ...

    //       c - Scan the resulting points
piNurbsCurve,
piNurbsCurve1);
    CATLONG32 nbOfPoints1 = pPtCrvCrv->GetNumberOfPoints(#);
    cout   << "NumberOfPoints "   << nbOfPoints1   << endl;
    CATCartesianPoint * pCartP = NULL;
    if(nbOfPoints1)

    	{
CATLONG32 nbOfPoints1 = pPtCrvCrv->GetNumberOfPoints(#);
cout   << "NumberOfPoints "   << nbOfPoints1   << endl;
CATCartesianPoint * pCartP = NULL;
if(nbOfPoints1)
```vbscript
    		while(pPtCrvCrv->NextPoint(#))

```

    		{
    			// Retrieves the resulting points
    			// 3 points are expected
```vbscript
while(pPtCrvCrv->NextPoint(#))
```vbscript
```vbscript
    			pCartP = pPtCrvCrv->GetCartesianPoint(#);
    			if (pCartP)
```

```

```

    			{
pCartP = pPtCrvCrv->GetCartesianPoint(#);
```vbscript
if (pCartP)
```

    				cout   << "X="   << pCartP->GetX(#)   << endl;
    				cout   << "Y="   << pCartP->GetY(#)   << endl;
    				cout   << "Z="   << pCartP->GetZ(#)   << endl;

    			}
    		}
    	}

    ---

    returns

returns
    NumberOfPoints 3
    X=34.9987
    Y=9.86305
    Z=0
    X=26.2534
    Y=12.9795
    Z=0
    X=100
    Y=20
    Z=0

on the standard output.  Fig.2 Curve Intersection:  Output data are three points ![Intersecting Curves](images/CGM_intersect_crvCrv_1.png)

---
## References

[1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)
[4] |  [How to Use Geometric Operators](CAACgmUcGMModelOpeOverw.md)
## History

Version: **1** [Feb 2014] | Document created
---|---
