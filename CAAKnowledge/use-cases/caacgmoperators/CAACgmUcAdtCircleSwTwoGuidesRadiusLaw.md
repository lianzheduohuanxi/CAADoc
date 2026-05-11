---
```vbscript
title: "Creating a Circle Sweep with Two Guides and a Radius Law"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CAADoc", "CAAGMOperatorsCircleSweepTwoGuidesRadius", "CAAGMModelGemBrowser", "CATICGMFrFTopologicalSweep", "CAAAdtCircleSweepTwoGuidesRadius"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcAdtCircleSwTwoGuidesRadiusLaw.htm"
converted: "2026-05-11T17:33:48.822965"
```

---
tags: ["CAAGMOperatorsInterfaces", "CAADoc", "CAAGMOperatorsCircleSweepTwoGuidesRadius", "CAAGMModelGemBrowser", "CATICGMFrFTopologicalSweep", "CAAAdtCircleSweepTwoGuidesRadius"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcAdtCircleSwTwoGuidesRadiusLaw.htm"
converted: "2026-05-11T17:33:48.822965"
Creating a Circle Sweep with Two Guides and a Radius Law

---
converted: "2026-05-11T17:33:48.822965"
Creating a Circle Sweep with Two Guides and a Radius Law
Use Case
Abstract The CATICGMFrFTopologicalSweep operator enables you to create sweeps. This use case explains how to create a circle sweep with three guides.

    * What You Will Learn With This Use Case
    * The CAAGMOperatorsCircleSweepTwoGuidesRadius Use Case
      * What Does CAAGMOperatorsCircleSweepTwoGuidesRadius Do?
      * How to Launch CAAGMOperatorsCircleSweepTwoGuidesRadius
      * Where to Find the CAAGMOperatorsCircleSweepTwoGuidesRadius Code
    * Step-by-Step
    * In Short
    * References
---
What You Will Learn With This Use Case In this use case, you learn how to use the CATICGMFrFTopologicalSweep operator to create circle sweeps with three guides. ![Swept Surface Definition Dialog Box](images/CAACgmAdtcirclesweep2guidesradiuslaw.gif) | CATICGMFrFTopologicalSweep is to be used according to the general scheme of topological operators. If need be, you can take a look at "Overview of the Topological Operators" [1] for more information.
---|---
What You Will Learn With This Use Case In this use case, you learn how to use the CATICGMFrFTopologicalSweep operator to create circle sweeps with three guides. ![Swept Surface Definition Dialog Box](images/CAACgmAdtcirclesweep2guidesradiuslaw.gif) | CATICGMFrFTopologicalSweep is to be used according to the general scheme of topological operators. If need be, you can take a look at "Overview of the Topological Operators" [1] for more information.
The CAAGMOperatorsCircleSweepTwoGuidesRadius Use Case CAAGMOperatorsCircleSweepTwoGuidesRadius is a use case of the CAAGMOperatorsInterfaces.edu framework that illustrates the GMOperatorsInterfaces framework capabilities. ![Circle Sweep](images/CAACgmAdtcirclesweepradiuslawresult.gif) | The circle sweep which is created by this use case looks something like this:

What You Will Learn With This Use Case In this use case, you learn how to use the CATICGMFrFTopologicalSweep operator to create circle sweeps with three guides. ![Swept Surface Definition Dialog Box](images/CAACgmAdtcirclesweep2guidesradiuslaw.gif) | CATICGMFrFTopologicalSweep is to be used according to the general scheme of topological operators. If need be, you can take a look at "Overview of the Topological Operators" [1] for more information.
The CAAGMOperatorsCircleSweepTwoGuidesRadius Use Case CAAGMOperatorsCircleSweepTwoGuidesRadius is a use case of the CAAGMOperatorsInterfaces.edu framework that illustrates the GMOperatorsInterfaces framework capabilities. ![Circle Sweep](images/CAACgmAdtcirclesweepradiuslawresult.gif) | The circle sweep which is created by this use case looks something like this:
What Does CAAGMOperatorsCircleSweepTwoGuidesRadius Do? The use case:

    * Creates the curves and radius law to be used as input data.
    * Creates a CATICGMFrFTopologicalSweep operator instance.
    * Runs the CATICGMFrFTopologicalSweep and retrieve the resulting body.
**Note** : This article only focuses on the operations related to the CATICGMFrFTopologicalSweep operator. Refer to "Overview of the Topological Operators" [1] for more information on the operations which are not detailed in the article. How to Launch CAAGMOperatorsCircleSweepTwoGuidesRadius To launch CAAGMOperatorsCircleSweepTwoGuidesRadius, you will need to set up the build time environment, then compile CAAGMOperatorsCircleSweepTwoGuidesRadius.m, set up the run time environment, and then execute the use case [2]. If you simply type CAAGMOperatorsCircleSweepTwoGuidesRadius with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example: `CAAGMOperatorsCircleSweepTwoGuidesRadius e/sweep.NCGM` This NCGM file can be displayed using the CAAGMModelGemBrowser use case. Where to Find the CAAGMOperatorsCircleSweepTwoGuidesRadius Code The CAAGMOperatorsCircleSweepTwoGuidesRadius use case is made of a main named CAAAdtCircleSweepTwoGuidesRadius.cpp located in the CAAGMOperatorsCircleSweepTwoGuidesRadius.m module of the CAAGMOperatorsInterfaces.edu framework: `InstallRootFolder\CAADoc\CAAGMOperatorsInterfaces.edu\CAAGMOperatorsCircleSweepTwoGuidesRadius.m\` where `InstallRootFolder` [2] is the folder where the API CD-ROM is installed. Step-by-Step The use case is divided into the following main steps:
    * Creating the Two Guides
    * Creating a CATICGMFrFTopologicalSweep Operator Instance
    * Setting the Radius Law
    * Running the operator and retrieving the resulting body (common to all operators - not discussed below).
Creating the Two Guides The curves to be used as guides are CATSpline that are simply created from the geometry factory. See [3] for information on how to create a spline. Creating a CATICGMFrFTopologicalSweep Operator Instance The CATICGMFrFTopologicalSweep operator is created by the CATCGMCreateFrFTopologicalCircleSweep global function. The two guides are passed in the form of a list as the third argument of the function.

Creating the Two Guides The curves to be used as guides are CATSpline that are simply created from the geometry factory. See [3] for information on how to create a spline. Creating a CATICGMFrFTopologicalSweep Operator Instance The CATICGMFrFTopologicalSweep operator is created by the CATCGMCreateFrFTopologicalCircleSweep global function. The two guides are passed in the form of a list as the third argument of the function.
    CATLISTP(CATGeometry) guides0;
    CATGeometry * guideGeom1 = (CATGeometry*)pWireBody1 ;
    CATGeometry * guideGeom2 = (CATGeometry*)pWireBody2 ;
    guides0.Append(guideGeom1);
    guides0.Append(guideGeom2);

    // (a) - Create the sweep operator
    //
guides0.Append(guideGeom1);
guides0.Append(guideGeom2);
    CATICGMFrFTopologicalSweep * pSweepOpe = CATCGMCreateFrFTopologicalCircleSweep(piGeomFactory,

            &topdata, &guides0);

Setting the Radius Law The radius law is created from the geometry factory.

    // (b) - Create the radius law
    //
Setting the Radius Law The radius law is created from the geometry factory.
    CATLaw * radiusLaw = ((CATLaw*)(piGeomFactory -> CreateConstantLaw(0.0, 1.0, 10.0)));
    pSweepOpe->SetRadiusLaw(radiusLaw);

In Short This use case is an example of how to create a circle sweep with two guides and a radius law. References [1] | [Overview of the Topological Operators](CAACgmUcTopOverview.md)

[2] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
[3] | [Using the Basic Topological Operators](CAACgmUcTopSpline.md)
History Version: **1** [Aug 2002] | Document created
---|---
