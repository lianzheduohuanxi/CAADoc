---
```vbscript
title: "Creating a Circle Sweep with Three Guides"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CAAGMOperatorsCircleSweepThreeGuidesUse", "CAAAdtCircleSweepThreeGuides", "CAADoc", "CAAGMOperatorsCircleSweepThreeGuideswith", "CAAGMOperatorsCircleSweepThreeGuidesis", "CAAGMModelGemBrowser", "CAAGMOperatorsCircleSweepThreeGuidesCode", "CAAGMOperatorsCircleSweepThreeGuides", "CATICGMFrFTopologicalSweep", "CAAGMOperatorsCircleSweepThreeGuidesDo"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcAdtCircleSwThreeGuides.htm"
converted: "2026-05-11T17:33:48.810459"
```

---
tags: ["CAAGMOperatorsInterfaces", "CAAGMOperatorsCircleSweepThreeGuidesUse", "CAAAdtCircleSweepThreeGuides", "CAADoc", "CAAGMOperatorsCircleSweepThreeGuideswith", "CAAGMOperatorsCircleSweepThreeGuidesis", "CAAGMModelGemBrowser", "CAAGMOperatorsCircleSweepThreeGuidesCode", "CAAGMOperatorsCircleSweepThreeGuides", "CATICGMFrFTopologicalSweep", "CAAGMOperatorsCircleSweepThreeGuidesDo"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcAdtCircleSwThreeGuides.htm"
converted: "2026-05-11T17:33:48.810459"
Creating a Circle Sweep with Three Guides  

---  
converted: "2026-05-11T17:33:48.810459"
Creating a Circle Sweep with Three Guides
Use Case  
Abstract The CATICGMFrFTopologicalSweep operator enables you to create sweeps. This use case explains how to create a circle sweep with three guides.

    * What You Will Learn With This Use Case
    * The CAAGMOperatorsCircleSweepThreeGuides Use Case
      * What Does CAAGMOperatorsCircleSweepThreeGuidesDo?
      * How to Launch CAAGMOperatorsCircleSweepThreeGuides
      * Where to Find the CAAGMOperatorsCircleSweepThreeGuidesCode
    * Step-by-Step
    * In Short
    * References  
---  
What You Will Learn With This Use Case In this use case, you learn how to use the CATICGMFrFTopologicalSweep operator to create circle sweeps with three guides. ![Swept Surface definition Dialog Box](images/CAACgmAdtcirclesweep3guides.gif) | CATICGMFrFTopologicalSweep is to be used according to the general scheme of topological operators. If need be, you can take a look at "Overview of the Topological Operators" [1] for more information.  
---|---  
What You Will Learn With This Use Case In this use case, you learn how to use the CATICGMFrFTopologicalSweep operator to create circle sweeps with three guides. ![Swept Surface definition Dialog Box](images/CAACgmAdtcirclesweep3guides.gif) | CATICGMFrFTopologicalSweep is to be used according to the general scheme of topological operators. If need be, you can take a look at "Overview of the Topological Operators" [1] for more information.
The CAAGMOperatorsCircleSweepThreeGuidesUse Case CAAGMOperatorsCircleSweepThreeGuidesis a use case of the CAAGMOperatorsInterfaces.edu framework that illustrates the GMOperatorsInterfaces framework capabilities. ![Circle Sweep](images/CAACgmAdtcirclesweep3guidesresult.gif) | The circle sweep which is created by this use case looks something like this:  

What You Will Learn With This Use Case In this use case, you learn how to use the CATICGMFrFTopologicalSweep operator to create circle sweeps with three guides. ![Swept Surface definition Dialog Box](images/CAACgmAdtcirclesweep3guides.gif) | CATICGMFrFTopologicalSweep is to be used according to the general scheme of topological operators. If need be, you can take a look at "Overview of the Topological Operators" [1] for more information.
The CAAGMOperatorsCircleSweepThreeGuidesUse Case CAAGMOperatorsCircleSweepThreeGuidesis a use case of the CAAGMOperatorsInterfaces.edu framework that illustrates the GMOperatorsInterfaces framework capabilities. ![Circle Sweep](images/CAACgmAdtcirclesweep3guidesresult.gif) | The circle sweep which is created by this use case looks something like this:
What Does CAAGMOperatorsCircleSweepThreeGuidesDo ? The use case:

    * Creates the curves making up the wires to be used as guides.
    * Creates a CATICGMFrFTopologicalSweep operator instance.
    * Runs the CATICGMFrFTopologicalSweep and retrieve the resulting body.
**Note** : This article only focuses on the operations related to the CATICGMFrFTopologicalSweep operator. Refer to "Overview of the Topological Operators" [1] for more information on the operations which are not detailed in the article. How to Launch CAAGMOperatorsCircleSweepThreeGuides  To launch CAAGMOperatorsCircleSweepThreeGuides, you will need to set up the build time environment, then compile CAAGMOperatorsCircleSweepThreeGuides.m, set up the run time environment, and then execute the use case [2]. If you simply type CAAGMOperatorsCircleSweepThreeGuideswith no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example: `CAAGMOperatorsCircleSweepThreeGuides e/sweep.NCGM` This NCGM file can be displayed using the CAAGMModelGemBrowser use case. Where to Find the CAAGMOperatorsCircleSweepThreeGuidesCode The CAAGMOperatorsCircleSweepThreeGuides use case is made of a main named CAAAdtCircleSweepThreeGuides.cpp located in the CAAGMOperatorsCircleSweepThreeGuides.m module of the CAAGMOperatorsInterfaces.edu framework: `InstallRootFolder\CAADoc\CAAGMOperatorsInterfaces.edu\CAAGMOperatorsCircleSweepThreeGuides.m\` where `InstallRootFolder` [2] is the folder where the API CD-ROM is installed. Step-by-Step The use case is divided into the following main steps:
    * Creating the Three Guides
    * Creating a CATICGMFrFTopologicalSweep Operator Instance
    * Running the operator and retrieving the resulting body (common to all operators - not discussed below).
Creating the Three Guides The curves to be used in the wire are CATSpline that are simply created from the geometry factory. See [3] for information on how to create a spline. Creating a CATICGMFrFTopologicalSweep Operator Instance The CATICGMFrFTopologicalSweep operator is created by the CATCGMCreateFrFTopologicalCircleSweep global function. The three guides are passed in the form of a list as the third argument of the function.

Creating the Three Guides The curves to be used in the wire are CATSpline that are simply created from the geometry factory. See [3] for information on how to create a spline. Creating a CATICGMFrFTopologicalSweep Operator Instance The CATICGMFrFTopologicalSweep operator is created by the CATCGMCreateFrFTopologicalCircleSweep global function. The three guides are passed in the form of a list as the third argument of the function.
    CATLISTP(CATGeometry) guides0;
    CATGeometry * guideGeom1 = (CATGeometry*)pWireBody1 ;
    CATGeometry * guideGeom2 = (CATGeometry*)pWireBody2 ;
    CATGeometry * guideGeom3 = (CATGeometry*)pWireBody3 ;
    guides0.Append(guideGeom1);
    guides0.Append(guideGeom3);
    guides0.Append(guideGeom2);

    // (a) - Creation of the sweep operator
    //
guides0.Append(guideGeom3);
guides0.Append(guideGeom2);
    CATICGMFrFTopologicalSweep * pSweepOpe = CATCGMCreateFrFTopologicalCircleSweep(piGeomFactory, 

            &topdata, &guides0);

In Short The CATICGMFrFTopologicalSweep operator allows you to create sweeps. This use case is an example of how to create a circle sweep with three guides. References [1] | [Overview of the Topological Operators](CAACgmUcTopOverview.md)  
---|---  
[2] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
[3] | [Using the Basic Topological Operators](CAACgmUcTopSpline.md)  
History Version: **1** [Aug 2002] | Document created  
---|---
