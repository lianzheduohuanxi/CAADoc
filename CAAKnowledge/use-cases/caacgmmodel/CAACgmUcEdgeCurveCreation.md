---
title: "Creating or Computing an Edge Curve"
category: "use-case case"
module: "CAACgmModel"
tags: "["CATICGMComputeEdgeCurve", "CATICGMObject", "CAAGMModelInterfaces", "CAAGMModelTetra", "CATICGMEdgeCurveComputation", "CAAGMModelEdgeCurveComputation"]"
source_file: "Doc/online/CAACgmModel/CAACgmUcEdgeCurveCreation.htm"
converted: "2026-05-11T17:33:48.198981"
---
# Creating or Computing an Edge Curve

---
Use Case
### Abstract

The edge curve (CATEdgeCurve) is the object which aggregates the curves or sub-curves making up the geometry of an edge. It is intended to define the limits of the edge though the POECs (PointsOnEdgeCurve) as well as the curve which supports the topology.  It is highly recommended to create an edge curve by using the CATICGMEdgeCurveComputation operator because this operator computes a mapping between the parameters on either curve. If the sub-curves making up an edge curve are identical (same parameterization, same limits and confusion), you can use the CATGeoFactory::CreateSimCurve method, but only in this case. Not using CATICGMEdgeCurveComputation may lead to unpredictable results when the sub-curves are not identical.
    * Operator to be Used to Compute an Edge Curve
    * Use Case Description
    * About the Edge Curve Maximum Gap
    * References
---
## Operator to be Used to Create an Edge Curve

The CATICGMComputeEdgeCurve is to be used and should be preferred to any other API.
## Use Case Description

The CATICGMComputeEdgeCurve is to be used and should be preferred to any other API.
The CAAGMModelEdgeCurveComputation.m module in CAAGMModelInterfaces.edu illustrates how to compute an edge curve. This use case creates its own input data. You can refer to [ Using Topological Objects](CAACgmUcTobTetra.md) for more information on how to create geometry and topological objects without using operators. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md).

The code which is used in the CAAGMModelEdgeCurveComputation.m use case is basically the same as CAAGMModelTetra.m except that only a shell is created. It is intended to focus on the edge curve computation. The shell is made up of two triangular faces. There are five edges. Only the edge curves under the shell bounding edges are CATSimCurve. The edge curve under the edge which is shared between the two faces must not be created as a CATSimCurve, it has to be created with the CATICGMEdgeCurveComputation operator. In the code below, piPLinexy20 and piPLineyz01 do not have the same limits and there is a small gap between the two sub-curves. Any gap is allowed between sub-curves but it is recommended to have a gap between sub-curves smaller than 0.1mm. The MPG_1 rule of the data checker is infringed if the gap is greater than 0.1mm. The code below:

    ...
The CAAGMModelEdgeCurveComputation.m module in CAAGMModelInterfaces.edu illustrates how to compute an edge curve. This use case creates its own input data. You can refer to [ Using Topological Objects](CAACgmUcTobTetra.md) for more information on how to create geometry and topological objects without using operators. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md).
The code which is used in the CAAGMModelEdgeCurveComputation.m use case is basically the same as CAAGMModelTetra.m except that only a shell is created. It is intended to focus on the edge curve computation. The shell is made up of two triangular faces. There are five edges. Only the edge curves under the shell bounding edges are CATSimCurve. The edge curve under the edge which is shared between the two faces must not be created as a CATSimCurve, it has to be created with the CATICGMEdgeCurveComputation operator. In the code below, piPLinexy20 and piPLineyz01 do not have the same limits and there is a small gap between the two sub-curves. Any gap is allowed between sub-curves but it is recommended to have a gap between sub-curves smaller than 0.1mm. The MPG_1 rule of the data checker is infringed if the gap is greater than 0.1mm. The code below:
    piPlanexy->GetParam(CATMathPoint(0.0,     0,     0.05),Pxy0);
    piPlanexy->GetParam(CATMathPoint(10.01,   0.03,  0.0) ,Pxy1);
    piPlanexy->GetParam(CATMathPoint(0,       10.04, 0.05) ,Pxy2);

    ...
    // Edge curve 5 (shared by two faces: two sub-curves)-> Compute the edge curve
piPlanexy->GetParam(CATMathPoint(0.0,     0,     0.05),Pxy0);
piPlanexy->GetParam(CATMathPoint(10.01,   0.03,  0.0) ,Pxy1);
piPlanexy->GetParam(CATMathPoint(0,       10.04, 0.05) ,Pxy2);
    CATICGMEdgeCurveComputation * pEdgeComputationOpe20=::CATCGMCreateEdgeCurveComputation(piGeomFactory,pConfig,
    piPLinexy20,piPLineyz01);
    pEdgeComputationOpe20->SetMaxGap(0.11);
    pEdgeComputationOpe20->Run(#);
    CATEdgeCurve * piSimCurve20= pEdgeComputationOpe20->GetEdgeCurve(#);

generates this result if the Data Checker is not activated. The max gap is around 0.101mm: Fig.1 Edge Curve Computation ![ddd](images/CGM_computeEdgeCurve_0.png)

---

generates this result if the Data Checker is not activated. The max gap is around 0.101mm: Fig.1 Edge Curve Computation ![ddd](images/CGM_computeEdgeCurve_0.png)
```vbscript
If you run the use case with the Data Checker activated, you get something like this on the standard output and no shell is created:

```

    CGM_CHECK_RULE:MPG_1:KO
    MPG_1: MacroPoint: CATMacroPoint_26
    MPG_1:   RefPoint: CATPointOnEdgeCurve_17
    MPG_1:     [0, 10.04, 0]
    MPG_1:   CurrPoint: CATPointOnEdgeCurve_20
    MPG_1:     [0, 10.02, 0.0990000000000002]
    MPG_1: GeometricalTol(0.1) : Gap3D = 0.101

    ** CATCGMCheckRule::Check Object( MPG_1 ; CATMacroPoint_26  )
    ********************************************************************************
MPG_1:   CurrPoint: CATPointOnEdgeCurve_20
MPG_1:     [0, 10.02, 0.0990000000000002]
MPG_1: GeometricalTol(0.1) : Gap3D = 0.101
    CGMCleaner on Body Completion CHECK #14

    CGM Rule : MPG_1
    On CGM Objects : (factory : 1) :
    CATMacroPoint 26
    From Feature : Unknown Feature
    Short msg : Macro Point has a too big gap between its internal points.
    Extended msg : none.

    ********************************************************************************

## About the Edge Curve Maximum Gap

    * The CATGeoFactory::CreateSimCurve method does not prevent you from creating an edge curve with unsuitable sub-curves (non identical sub-curves). It is up to the application to make sure that the input parameters are correct: parameterization, limits, confusion.
    * The CATICGMEdgeCurveComputation generates an ABEND if the maximum gap between sub-curves is greater than the one specified in SetMaxGap. If SetMaxGap is not used, the authorized max gap is around 1 mm. However, the CATICGMObject::Completed method generates an Abend, when the Data Checker is run (the MPG_1 rule must be activated) and when the max gap is greater than 0.1mm.
## References

[1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] |  [Scanning an Edge Curve](CAACgmUcTobEdgeCurve.md)
## History

Version: **1** [Jan 2012] | Document created
---|---
