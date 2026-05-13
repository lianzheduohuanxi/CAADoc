---
```vbscript
title: "Breaking a C1 Surface into C2 Pieces"
category: "use case"
module: "CAACgmModel"
tags: ["CAAGMModelInterfaces", "CATICGMMathNurbsSurfaceTools", "CAAGMModelConvertSurfaceToC2", "CATICGMNurbsSurfaceTools"]
source_file: "Doc/online/CAACgmModel/CAACgmUcTopGMModelSurfaceC1ToC2.htmmd"
converted: "2026-05-11T17:33:48.605582"
```

---
Breaking a C1 Surface into C2 Pieces

    ---

    		Use Case

    		Abstract
    		The geometric modeler is designed to operate on C2 curves and surfaces.
    		Non-C2 curves and surfaces are to be broken into C2 pieces.	Any surface which is suspected of being non-C2
    		can be analyzed by using the CATICGMNurbsSurfaceTools::Check method. If
    		a
    		surface is detected as being non-C2,
    		it has to be split into C2 pieces by using the CATICGMMathNurbsSurfaceTools operator.
            From the C2 pieces, you can compute the parameters of a single Nurbs.
            These parameters can be used to create a single Nurbs (non-C2) in an other modeler.

            * Operator to be Used

            * Use Case Description

            * References

    ---

    Operator to be Used
    To check whether a surface is C2, use the Check method of CATICGMNurbsSurfaceTools operator.
    This operator is created by the CATCGMCreateNurbsSurfaceTools global function.
    To break a non-C2 surface into C2 pieces, use the ConvertToC2NurbsSurfaces method of the CATICGMMathNurbsSurfaceTools operator.

    Use Case Description
    The CAAGMModelConvertSurfaceToC2.m module in CAAGMModelInterfaces.edu
    illustrates how to break a non-C2 surface into C2 pieces. This use case
    is to be run with the
    C1NurbsSurface.ncgm file which is delivered in the FunctionTests/InputData
    folder. If you are not already
    familiar with geometric modeler use cases, go to

    [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md).
is to be run with the
C1NurbsSurface.ncgm file which is delivered in the FunctionTests/InputData
folder. If you are not already
familiar with geometric modeler use cases, go to
    With the input data below:

      Fig.1 Break a C1 Surface into C2 Pieces: Input
    	Surface

    	![Break a C1 Surface into C2 Pieces: Input](images/CGM_surface_C1toC2_0.png)

    ---

    and the code below:

    CATICGMNurbsSurfaceTools  * pNurbsTool3D  =::CATCGMCreateNurbsSurfaceTools(piGeomFactory, pConfig, pC1Nurbs);
    ...
    // Retrieve the surface degree
CATICGMNurbsSurfaceTools  * pNurbsTool3D  =::CATCGMCreateNurbsSurfaceTools(piGeomFactory, pConfig, pC1Nurbs);
    int degU = 0;
    int degV = 0;
    pNurbsTool3D->GetDegrees (degU,degV);
    cout << "surface degree along U (3 expected) " << degU << endl;
    cout << "surface degree along V (3 expected) "<< degV << endl;

    ...
    // Retrieve the knot number
    ...
    // Checks the input curve continuity
cout << "surface degree along V (3 expected) "<< degV << endl;
    CATNurbsToolsInfo infoContinuity = pNurbsTool3D->Check(#);
    cout << "Check the surface continuity " << endl;
```vbscript
    if (infoContinuity == Info_InternalContinuity)

```

    	{
    	 ...
    // Create the CATICGMMathNurbsSurfaceTools operator
cout << "Check the surface continuity " << endl;
if (infoContinuity == Info_InternalContinuity)
    CATICGMMathNurbsSurfaceTools  * pMathNurbsTool3D  =::CATCGMCreateMathNurbsSurfaceTools( *inputKVU, *inputKVV,
    			pC1Nurbs->IsRational(#), Vertices, aWeights);

    ...
CATICGMMathNurbsSurfaceTools  * pMathNurbsTool3D  =::CATCGMCreateMathNurbsSurfaceTools( *inputKVU, *inputKVV,
pC1Nurbs->IsRational(#), Vertices, aWeights);
    int NbRefU, NbRefV=0;
    CATLISTP(CATSurface) listOfC2Surfaces;

    // Create the C2 surfaces
pC1Nurbs->IsRational(#), Vertices, aWeights);
int NbRefU, NbRefV=0;
CATLISTP(CATSurface) listOfC2Surfaces;
    cout << listOfC2Surfaces.Size(#) << " C2 surfaces are generated" << endl;

    ...

    ---

    nine pieces are created.

      Fig.2 Break a C1 Surface into C2 Pieces: Result

    	![Break a C1 Surface into C2 Pieces: Result](images/CGM_surface_C1toC2_1.png)

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

    		Version: **1** [Dec 2011]
    		| Document created
