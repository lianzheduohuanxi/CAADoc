---
title: "Creating a Circle Sweep with One Guide and a Tangency Surface"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CAADoc", "CATICGMTopMultiResult", "CATICGMTopSweepWireSkinCircle", "CAAGMModelGemBrowser", "CAAGMOperatorsCircleSweepTangSurRadius", "CATICGMTopPrism"]
source_file: "Doc\online\CAACgmOperators\CAACgmUcAdtCircleSwTangSurRadius.htm"
converted: "2026-05-11T17:33:48.799462"
---

Creating a Circle Sweep with One Guide and a Tangency Surface  
---  
Use Case  
Abstract The CATICGMTopSweepWireSkinCircle operator enables you to create sweeps. This use case explains how to create a circle sweep with one guide and a tangency surface.
    * What You Will Learn With This Use Case
    * The CAAGMOperatorsCircleSweepTangSurRadius Use Case
      * What Does CAAGMOperatorsCircleSweepTangSurRadius Do?
      * How to Launch CAAGMOperatorsCircleSweepTangSurRadius
      * Where to Find the CAAGMOperatorsCircleSweepTangSurRadius Code
    * Step-by-Step
    * In Short
    * References  
---  
What You Will Learn With This Use Case In this use case, you learn how to use the CATICGMTopSweepWireSkinCircle operator to create circle sweeps with one guide and a tangency surface. A radius law is to be specified. ![Swept Surface Definition Dialog Box](images/CAACgmAdtcirclesweeponegtangsur.gif) | CATICGMTopSweepWireSkinCircle is a CATICGMTopMultiResult operator. To scan the results, you must use the BeginningResult() and NextResult() methods provided by the CATICGMTopMultiResult operator.  
---|---  
The CAAGMOperatorsCircleSweepTangSurRadius Use Case CAAGMOperatorsCircleSweepTangSurRadius is a use case of the CAAGMOperatorsInterfaces.edu framework that illustrates the GMOperatorsInterfaces framework capabilities. ![Circle Sweep](images/CAACgmAdttangsurresult.gif) | The circle sweep which is created by this use case looks something like this. The tangency surface is not displayed.  
---|---  
What Does CAAGMOperatorsCircleSweepTangSurRadius Do ? The use case:
    * Creates the guide and the tangency surface.
    * Creates a CATICGMTopMultiResult operator instance.
    * Runs the CATICGMTopMultiResult and retrieve one of the resulting bodies.
**Note** : This article only focuses on the operations related to the CATICGMTopMultiResult and CATICGMTopSweepWireSkinCircle operators. Refer to "Overview of the Topological Operators" [1] for more information on the operations which are not detailed in the article. How to Launch CAAGMOperatorsCircleSweepTangSurRadius To launch CAAGMOperatorsCircleSweepTangSurRadius, you will need to set up the build time environment, then compile CAAGMOperatorsCircleSweepTangSurRadius.m, set up the run time environment, and then execute the use case [2]. If you simply type CAAGMOperatorsCircleSweepTangSurRadius with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example: `CAAGMOperatorsCircleSweepTangSurRadius e:\sweep.NCGM` This NCGM file can be displayed using the CAAGMModelGemBrowser use case. Where to Find the CAAGMOperatorsCircleSweepTangSurRadius Code The CAAGMOperatorsCircleSweepTangSurRadius use case is made of a main named CAAGMOperatorsCircleSweepTangSurRadius.cpp located in the CAAGMOperatorsCircleSweepTangSurRadius.m module of the CAAGMOperatorsInterfaces.edu framework: `InstallRootFolder\CAADoc\CAAGMOperatorsInterfaces.edu\CAAGMOperatorsCircleSweepTangSurRadius.m\` where `InstallRootFolder` [2] is the folder where the API CD-ROM is installed. Step-by-Step The use case is divided into the following main steps:
    * Creating the Guide and the Tangency Surface
    * Creating a CATICGMTopSweepWireSkinCircle Operator Instance
    * Running the Operator and Retrieving the Resulting Body.
Creating the Guide and the Tangency Surface The curve to be used as the guide is a CATSpline that is simply created from the geometry factory. See [3] for information on how to create a spline. The tangency surface is created by extruding a spline (CATICGMTopPrism operator). Creating a CATICGMTopSweepWireSkinCircle Operator Instance The CATICGMTopSweepWireSkinCircle operator is created by the CATCGMCreateTopSweepWireSkinCircleVariable global function (arg 3: tangency surface, arg 4: the guide, arg 5: the spine, arg 6: the radius law).
    
    CATLaw * radiusLaw = ((CATLaw*)(piGeomFactory -> CreateConstantLaw(0.0, 1.0, 10.0)));
        
    // (b) - Create the CATICGMTopSweepWireSkinCircle operator
    //
    CATICGMTopMultiResult * pWireSkinCircleOpe =
            CATCGMCreateTopSweepWireSkinCircleVariable(piGeomFactory, &topdata, 
            pPBody, pWireBody2,
            pWireBody2, radiusLaw);
    ...

Running the Operator and Retrieving the Resulting Body CATICGMTopSweepWireSkinCircle is a CATICGMTopMultiResult operator. For all the operators deriving from CATICGMTopMultiResult, you access the results by using the BeginningResult(), NextResult() and GetResult() methods provided by the operators.
    
    // (d) - Retrieve the second body
    //
    pWireSkinCircleOpe->BeginningResult();
    int nbBodies = pWireSkinCircleOpe->GetNumberOfResults();
    for (int iBody = 1 ; iBody <= nbBodies ; iBody ++)
      {
        pWireSkinCircleOpe->NextResult();
        if (iBody == 2)
            {
                CATBody * pCurBody = pWireSkinCircleOpe->GetResult();
            }
        }  
    ...

In Short This use case is an example of how to create a circle sweep with one guide and a tangency surface by using the CATICGMTopSweepWireSkinCircle operator. References [1] | [Overview of the Topological Operators](CAACgmUcTopOverview.htm)  
---|---  
[2] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.htm)  
[3] | [Using the Basic Topological Operators](CAACgmUcTopSpline.htm)  
History Version: **1** [Aug 2002] | Document created  
---|---
