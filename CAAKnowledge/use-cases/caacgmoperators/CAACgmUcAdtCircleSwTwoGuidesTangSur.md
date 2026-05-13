---
title: "Creating a Circle Sweep with Two Guides and a Tangency Surface"
category: "use case"
module: "CAACgmOperators"
tags: "["CAAGMOperatorsInterfaces", "CAADoc", "CAAGMOperatorsCircleSweepTwoEdgesTangSur", "CAAGMModelGemBrowser", "CAAAdtCircleSweepTwoEdgesTangSur", "CATICGMFrFTopologicalSweep", "CATIA", "CATICGMTopPrism"]"
source_file: "Doc/online/CAACgmOperators/CAACgmUcAdtCircleSwTwoGuidesTangSur.htm"
converted: "2026-05-11T17:33:48.833466"
---
tags: ["CAAGMOperatorsInterfaces", "CAADoc", "CAAGMOperatorsCircleSweepTwoEdgesTangSur", "CAAGMModelGemBrowser", "CAAAdtCircleSweepTwoEdgesTangSur", "CATICGMFrFTopologicalSweep", "CATIA", "CATICGMTopPrism"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcAdtCircleSwTwoGuidesTangSur.htmmd"
converted: "2026-05-11T17:33:48.833466"
Creating a Circle Sweep with Two Guides and a Tangency Surface

---
converted: "2026-05-11T17:33:48.833466"
Creating a Circle Sweep with Two Guides and a Tangency Surface
Use Case
Abstract The CATICGMFrFTopologicalSweep operator enables you to create sweeps. This use case explains how to create a circle sweep with two guides and a tangency surface.

    * What You Will Learn With This Use Case
    * The CAAGMOperatorsCircleSweepTwoEdgesTangSur Use Case
      * What Does CAAGMOperatorsCircleSweepTwoEdgesTangSur Do?
      * How to Launch CAAGMOperatorsCircleSweepTwoEdgesTangSur
      * Where to Find the CAAGMOperatorsCircleSweepTwoEdgesTangSur Code
    * Step-by-Step
    * In Short
    * References
---
What You Will Learn With This Use Case In this use case, you learn how to use the CATICGMFrFTopologicalSweep operator to create circle sweeps with two guides and a tangency surface. ![Swept Surface Definition Dialog Box](images/CAACgmAdttwoedgestangsurresult.gif) | CATICGMFrFTopologicalSweep is to be used according to the general scheme of topological operators. If need be, you can take a look at "Overview of the Topological Operators" [1] for more information.
---|---
What You Will Learn With This Use Case In this use case, you learn how to use the CATICGMFrFTopologicalSweep operator to create circle sweeps with two guides and a tangency surface. ![Swept Surface Definition Dialog Box](images/CAACgmAdttwoedgestangsurresult.gif) | CATICGMFrFTopologicalSweep is to be used according to the general scheme of topological operators. If need be, you can take a look at "Overview of the Topological Operators" [1] for more information.
The CAAGMOperatorsCircleSweepTwoEdgesTangSur Use Case CAAGMOperatorsCircleSweepTwoEdgesTangSur is a use case of the CAAGMOperatorsInterfaces.edu framework that illustrates the GMOperatorsInterfaces framework capabilities. ![Circle Sweep](images/CAACgmAdttwoedgestangsur.gif) | The circle sweep which is created by this use case looks something like this:

What You Will Learn With This Use Case In this use case, you learn how to use the CATICGMFrFTopologicalSweep operator to create circle sweeps with two guides and a tangency surface. ![Swept Surface Definition Dialog Box](images/CAACgmAdttwoedgestangsurresult.gif) | CATICGMFrFTopologicalSweep is to be used according to the general scheme of topological operators. If need be, you can take a look at "Overview of the Topological Operators" [1] for more information.
The CAAGMOperatorsCircleSweepTwoEdgesTangSur Use Case CAAGMOperatorsCircleSweepTwoEdgesTangSur is a use case of the CAAGMOperatorsInterfaces.edu framework that illustrates the GMOperatorsInterfaces framework capabilities. ![Circle Sweep](images/CAACgmAdttwoedgestangsur.gif) | The circle sweep which is created by this use case looks something like this:
What Does CAAGMOperatorsCircleSweepTwoEdgesTangSur Do ? The use case:

    * Creates the curves and tangency surface to be used as input data.
    * Creates a CATICGMFrFTopologicalSweep operator instance.
    * Runs the CATICGMFrFTopologicalSweep and retrieve the resulting body.
**Note** : This article only focuses on the operations related to the CATICGMFrFTopologicalSweep operator. Refer to "Overview of the Topological Operators" [1] for more information on the operations which are not detailed in the article. How to Launch CAAGMOperatorsCircleSweepTwoEdgesTangSur To launch CAAGMOperatorsCircleSweepTwoEdgesTangSur, you will need to set up the build time environment, then compile CAAGMOperatorsCircleSweepTwoEdgesTangSur.m, set up the run time environment, and then execute the use case [2]. If you simply type CAAGMOperatorsCircleSweepTwoEdgesTangSur with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example: CAAGMOperatorsCircleSweepTwoEdgesTangSur `e/sweep.NCGM` This NCGM file can be displayed using the CAAGMModelGemBrowser use case. Where to Find the CAAGMOperatorsCircleSweepTwoEdgesTangSur Code The CAAGMOperatorsCircleSweepTwoEdgesTangSur use case is made of a main named CAAAdtCircleSweepTwoEdgesTangSur.cpp located in the CAAGMOperatorsCircleSweepTwoEdgesTangSur.m module of the CAAGMOperatorsInterfaces.edu framework: `InstallRootFolder/CAADoc/CAAGMOperatorsInterfaces.edu/CAAGMOperatorsCircleSweepTwoEdgesTangSur.m/` where `InstallRootFolder` [2] is the folder where the API CD-ROM is installed. Step-by-Step The use case is divided into the following main steps:
    * Creating the two guides and the tangency surface
    * Creating a CATICGMFrFTopologicalSweep operator instance
    * Setting the parameters
    * Running the operator and retrieving the resulting body (common to all operators - not discussed below).
Creating the Two Guides and the Tangency Surface The curves to be used as guides are CATSpline that are simply created from the geometry factory. See [3] for information on how to create a spline. The tangency surface is created by extruding one of the spline (CATICGMTopPrism operator). Creating a CATICGMFrFTopologicalSweep Operator Instance The CATICGMFrFTopologicalSweep operator is created by the CATCGMCreateFrFTopologicalCircleSweep global function. The two guides are passed in the form of a list as the third argument of the function. IMPORTANT: referring to the interactive dialog, the first guide appended in the list below is the "Limit curve" (pGuideGeom2) - the second guide appended is the "Limit curve with tangency" (pGuideGeom1 in the code below). The "Limit curve with tangency" must result from a projection on the tangency surface even if the curve is geometrically lying on the tangency surface.

    CATLISTP(CATGeometry) guides ;
    CATGeometry * pGuideGeom2 = (CATGeometry*)pWireBody2 ;
    CATGeometry * pGuideGeom1 = (CATGeometry*)pBodyProj ;

    guides.Append(pGuideGeom2);
    guides.Append(pGuideGeom1);

    // (a) - Create the sweep operator
    //
guides.Append(pGuideGeom2);
guides.Append(pGuideGeom1);
    CATICGMFrFTopologicalSweep * pSweepOpe = CATCGMCreateFrFTopologicalCircleSweep(piGeomFactory,

            &topdata, &guides);

Setting the Parameters The SetLimitGuideSlopeCondition method enables you to:
    * Specify the guide which is on the tangency surface. You just have to give the rank of this guide in the guide list (1 is the first guide appended).
    * Specify the tangency surface (arg 2)
    * A composite law. Only a NULL argument can be passed for this CATIA Version.

    //       2 - Specify the slope.
    //           When the angle is 0, the sweep to be generated is tangent to
    //           the reference element. The rank specified is
    //           the rank of the guide which is a projection on the surface
    //           in the CATLISTP(CATGeometry) list of guides.
    //
    CATGeometry * referenceElement = (CATGeometry *)pPBody;
    int rank = 2;
    pSweepOpe->SetLimitGuideSlopeCondition(rank, referenceElement,pCompLaw );

In Short This use case is an example of how to create a circle sweep with two guides and a tangency surface. References [1] |  [Overview of the Topological Operators](CAACgmUcTopOverview.md)

[2] |  [Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
[3] |  [Using the Basic Topological Operators](CAACgmUcTopSpline.md)
History Version: **1** [Aug 2002] | Document created
---|---
