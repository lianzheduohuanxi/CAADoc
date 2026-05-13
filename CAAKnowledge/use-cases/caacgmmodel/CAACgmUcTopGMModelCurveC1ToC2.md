---
```vbscript
title: "Breaking a C1 Curve into C2 Pieces"
category: "use case"
module: "CAACgmModel"
tags: ["CAAGMModelConvertCurveToC2", "CAAGMModelInterfaces", "CATICGMNurbsCurveTools", "CATIA", "CATICGMMathNurbsCurveTools"]
source_file: "Doc/online/CAACgmModel/CAACgmUcTopGMModelCurveC1ToC2.htmmd"
converted: "2026-05-11T17:33:48.589667"
```

---
tags: ["CAAGMModelConvertCurveToC2", "CAAGMModelInterfaces", "CATICGMNurbsCurveTools", "CATIA", "CATICGMMathNurbsCurveTools"]
source_file: "Doc/online/CAACgmModel/CAACgmUcTopGMModelCurveC1ToC2.htmmd"
converted: "2026-05-11T17:33:48.589667"
Breaking a C1 Curve into C2 Pieces

---
converted: "2026-05-11T17:33:48.589667"
Breaking a C1 Curve into C2 Pieces
Use Case
Abstract The geometric modeler is designed to operate on C2 curves and surfaces. Non-C2 curves and surfaces are to be broken into C2 pieces. Any curve which is suspected of being non-C2 can be analyzed by using the CATICGMNurbsCurveTools::Check method. If a curve is detected as being non-C2, it has to be split into C2 pieces by using the CATICGMMathNurbsCurveTools operator. From the C2 pieces, you can compute the parameters of a single Nurbs. These parameters can be used to create a single Nurbs (non-C2) in an other modeler.

    * Operator to be Used
    * Use Case Description
    * References
---
Abstract The geometric modeler is designed to operate on C2 curves and surfaces. Non-C2 curves and surfaces are to be broken into C2 pieces. Any curve which is suspected of being non-C2 can be analyzed by using the CATICGMNurbsCurveTools::Check method. If a curve is detected as being non-C2, it has to be split into C2 pieces by using the CATICGMMathNurbsCurveTools operator. From the C2 pieces, you can compute the parameters of a single Nurbs. These parameters can be used to create a single Nurbs (non-C2) in an other modeler.
Operator to be Used To check whether a curve is C2, use the `Check` method of CATICGMNurbsCurveTools operator. This operator is created by the CATCGMCreateNurbsCurveTools global function. To break a non-C2 curve into C2 pieces, use the `ConvertToC2NurbsCurves` method of the CATICGMMathNurbsCurveTools operator. Use Case Description The CAAGMModelConvertCurveToC2.m module in CAAGMModelInterfaces.edu illustrates how to break a non-C2 curve into C2 pieces. This use case is to be run with the RationalNurbsCurveC1.ncgm file which is delivered in the FunctionTests/InputData folder. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). With the input data below: Fig.1 Break a C1 Curve into C2 Pieces: Input Curve  ![Break a C1 Curve into C2](images/CGM_curve_C1toC2_1.png)

---
and the code below:

    // Checks the input curve continuity
Operator to be Used To check whether a curve is C2, use the `Check` method of CATICGMNurbsCurveTools operator. This operator is created by the CATCGMCreateNurbsCurveTools global function. To break a non-C2 curve into C2 pieces, use the `ConvertToC2NurbsCurves` method of the CATICGMMathNurbsCurveTools operator. Use Case Description The CAAGMModelConvertCurveToC2.m module in CAAGMModelInterfaces.edu illustrates how to break a non-C2 curve into C2 pieces. This use case is to be run with the RationalNurbsCurveC1.ncgm file which is delivered in the FunctionTests/InputData folder. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). With the input data below: Fig.1 Break a C1 Curve into C2 Pieces: Input Curve  ![Break a C1 Curve into C2](images/CGM_curve_C1toC2_1.png)
and the code below:
    CATICGMNurbsCurveTools  * pNurbsTool3D  =::CATCGMCreateNurbsCurveTools(piGeomFactory, pConfig, pC1Nurbs);

    ...
and the code below:
CATICGMNurbsCurveTools  * pNurbsTool3D  =::CATCGMCreateNurbsCurveTools(piGeomFactory, pConfig, pC1Nurbs);
    CATNurbsToolsInfo infoContinuity = pNurbsTool3D->Check(#);
```vbscript
    if (infoContinuity != Info_InternalContinuity)

```

        {
CATICGMNurbsCurveTools  * pNurbsTool3D  =::CATCGMCreateNurbsCurveTools(piGeomFactory, pConfig, pC1Nurbs);
CATNurbsToolsInfo infoContinuity = pNurbsTool3D->Check(#);
if (infoContinuity != Info_InternalContinuity)
    		cout << "The curve is C2 discontinuous" << endl;

         // Retrieves the parameters to be passed to the
CATNurbsToolsInfo infoContinuity = pNurbsTool3D->Check(#);
if (infoContinuity != Info_InternalContinuity)
cout << "The curve is C2 discontinuous" << endl;
         const CATKnotVector * inputKV = pC1Nurbs->GetKnotVector(#);  // the knot vector
         CATLONG32  NbCp  =  inputKV->GetNumberOfControlPoints(#);

         ...
cout << "The curve is C2 discontinuous" << endl;
const CATKnotVector * inputKV = pC1Nurbs->GetKnotVector(#);  // the knot vector
CATLONG32  NbCp  =  inputKV->GetNumberOfControlPoints(#);
         CATICGMMathNurbsCurveTools  * pMathNurbsTool3D  =::CATCGMCreateMathNurbsCurveTools( *inputKV,
                pNurbs->IsRational(#),
    			ctlPts,
    			CATMathNurbsFull3D,
    			aWeights);

         ...
         // Creates the C2 curves pieces
ctlPts,
CATMathNurbsFull3D,
aWeights);
         CATLISTP(CATCurve) listOfC2Curves;
         pMathNurbsTool3D->ConvertToC2NurbsCurves(piGeomFactory,listOfC2Curves);

         ...
         }

    ---

    three pieces are created. Assembling these three pieces and analyzing the
three pieces are created. Assembling these three pieces and analyzing the
    wire with the CATIA GSD "Curve Smooth" capability  gives this result:

      Fig.2 Point on a Wire: Result

    	![Break a C1 Curve into C2: Result](images/CGM_curve_C1toC2_0.png)

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
