---
title: "Projecting a Point onto  a Surface"
category: "use case"
module: "CAACgmModel"
tags: "["CAAGMModelInterfaces", "CATICGMProjectionPtSur", "CAAGMModelProjectionOpe"]"
source_file: "Doc/online/CAACgmModel/CAACgmUcProjPtSur.htm"
converted: "2026-05-11T17:33:48.506138"
---
Projecting a Point onto a Surface

    ---

    		Use Case

    		Abstract
    		A geometrical point can be projected onto a surface by using the CATICGMProjectionPtSur operator.
    		The result is a set of geometrical objects that you have to scan.

            * Operator to be Used

            * Use Case Description

            * References

    ---

    Operator to be Used
Operator to be Used
    Use CATICGMProjectionPtSur. This operator is created by using the CATCGMCreateProjection global function.

    Use Case Description
    The CAAGMModelProjectionOpe.m module in CAAGMModelInterfaces.edu
    illustrates how to project a Cartesian point onto a surface. This use case
    constructs its input data. If you are not already
    familiar with geometric modeler use cases, go to

    [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md).
The CAAGMModelProjectionOpe.m module in CAAGMModelInterfaces.edu
illustrates how to project a Cartesian point onto a surface. This use case
constructs its input data. If you are not already
familiar with geometric modeler use cases, go to
    With the input data below:

      Fig.1 Project a Point onto a Surface:  Input
    	data

    	![Project a Point onto a Surface](images/CGM_proj_ptSur_0.png)

    ---

    and the code below:

    // -------------------------------------------------------------------------
    // 2 - Projection of a point onto a surface CATICGMProjectionPtSur
    // -------------------------------------------------------------------------
    ...
    CATICGMProjectionPtSur * pPtSurOpe =:: CATCGMCreateProjection(
    		piGeomFactory,
    		pConfig,
    		piCartP1,
    		piNurbsSurface, &Dir, ADVANCED);

    ...
piGeomFactory,
pConfig,
piCartP1,
piNurbsSurface, &Dir, ADVANCED);
    pPtSurOpe->UseLimits( &SurLimits );
    pPtSurOpe->Run(#);

    //     d - Retrieve the resulting points
    //         Five resulting points are expected
pPtSurOpe->UseLimits( &SurLimits );
pPtSurOpe->Run(#);
    cout << "Number of resulting points " << pPtSurOpe->GetNumberOfPoints(#) << endl;
```vbscript
    if (pPtSurOpe->GetNumberOfPoints(#)   >  0)

```

    {
cout << "Number of resulting points " << pPtSurOpe->GetNumberOfPoints(#) << endl;
if (pPtSurOpe->GetNumberOfPoints(#)   >  0)
       pPtSurOpe->BeginningPoint(#);
```vbscript
       while ( pPtSurOpe->NextPoint(#) )

```

    	{
    ...

    ---

    you retrieve five resulting points (some of them cannot be distinguished as
    they are quite close to others).

      Fig.2 Projected Points

    	![Projected Points](images/CGM_proj_ptSur_1.png)

    ---

    References

    		[1]
    		|
    		[
    		Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)

    		[2]
    		|
    		[About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)

    		[3]
    		|
    		[How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)

    		[4]
    		|
    		[How to Use Geometric Operators](CAACgmUcGMModelOpeOverw.md)

    History

    		Version: **1** [Feb 2014]
    		| Document created
