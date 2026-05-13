---
```vbscript
title: "Intersecting Surfaces"
category: use-case case"
module: "CAACgmModel"
tags: ["CAAGMModelInterfaces", "CAAGMModelGeometryCreation", "CATICGMIntersectionSurSur", "CAAGMModelIntersectionOpe"]
source_file: "Doc/online/CAACgmModel/CAACgmUcIntersectSurSur.htmmd"
converted: "2026-05-11T17:33:48.461523"
```

---
# Intersecting Surfaces

---
Use Case
## Abstract

Surfaces can be intersected by using the CATICGMIntersectionSurSur operator. The result is a set of geometrical objects (points, curves, surfaces or a combination of these objects) that you have to scan.
    * Operator to be Used
    * Use Case Description
    * References
---
## Operator to be Used

Use CATICGMIntersectionSurSur. This operator is created by using the CATCGMCreateIntersection global function.
## Use Case Description

Use CATICGMIntersectionSurSur. This operator is created by using the CATCGMCreateIntersection global function.
The CAAGMModelIntersectionOpe.m module in CAAGMModelInterfaces.edu illustrates how to intersect surfaces. This use case constructs its input data and requires the CAAGMModelGeometryCreation.m module. You have to specify this module in your Imakefile.mk file.  If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md).

With the input data below:

Fig.1 Intersecting Surfaces:  Input data are two overlapping tabulated surfaces ![Surface Intersection](images/CGM_intersect_sursur_0.png)

---

With the input data below:
Fig.1 Intersecting Surfaces:  Input data are two overlapping tabulated surfaces ![Surface Intersection](images/CGM_intersect_sursur_0.png)
and the code below:

    CATICGMIntersectionSurSur * pPtSurSur =:: CATCGMCreateIntersection(
    		piGeomFactory,
    		pConfig,
    		piTabulatedCyl1,
    		piTabulatedCyl2);

    ...
piGeomFactory,
pConfig,
piTabulatedCyl1,
piTabulatedCyl2);
    CATLONG32 nbOfSurfaces = pPtSurSur->GetNumberOfSurfaces(#);
    cout   << "NumberOfSurfaces "   << nbOfSurfaces   << endl;
    if(nbOfSurfaces)

    	{
CATLONG32 nbOfSurfaces = pPtSurSur->GetNumberOfSurfaces(#);
cout   << "NumberOfSurfaces "   << nbOfSurfaces   << endl;
if(nbOfSurfaces)
    		pPtSurSur->BeginningSurface(#);
    		while(pPtSurSur->NextSurface(#))

    		{
    			// Retrieve the CATPCurve in confusion on piNurbsSurface
    			// 4 Pcurves are expected as the second surface is immerged within the first one
pPtSurSur->BeginningSurface(#);
while(pPtSurSur->NextSurface(#))
```vbscript
    			CATLISTP(CATPCurve) listPCurve;
```vbscript
    			listPCurve = pPtSurSur->GetSurfaceBoundaries(piTabulatedCyl2);
    			for (int i=1; i<=listPCurve.Size(#); i++ )

```

```

    			{
```vbscript
CATLISTP(CATPCurve) listPCurve;
```vbscript
```vbscript
listPCurve = pPtSurSur->GetSurfaceBoundaries(piTabulatedCyl2);
for (int i=1; i<=listPCurve.Size(#); i++ )
```

```

    				pCurve = listPCurve[i];
    				cout   << " Confusion found "   << endl;
```

    			}
    		}
    	}

    ---

    returns

returns
    NumberOfSurfaces 1
     Confusion found
     Confusion found
     Confusion found
     Confusion found

on the standard output. The CATPCurve geometries in confusion are the borders of the smaller tabulated cylinder.
The code below:

    CATLONG32 nbOfCurves0 = pPtSurSur->GetNumberOfCurves(#);
    cout   << "NumberOfCurves "   << nbOfCurves0   << endl;

    ...

---
cout   << "NumberOfCurves "   << nbOfCurves0   << endl;
results in:

    NumberOfCurves 0

on the standard output.

## References

[1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)
[4] |  [How to Use Geometric Operators](CAACgmUcGMModelOpeOverw.md)
## History

Version: **1** [Feb 2014] | Document created
---|---
