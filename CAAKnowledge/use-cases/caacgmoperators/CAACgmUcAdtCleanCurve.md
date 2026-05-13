---
```vbscript
title: "Achieving a Given Continuity along a Wire"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CAADoc", "CATICGMTopCleanCrvOperator", "CAAGMModelGemBrowser", "CATICGMTopWire", "CAAGMOperatorsCleanCrv", "CAAAdtCleanCrv"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcAdtCleanCurve.htmmd"
converted: "2026-05-11T17:33:48.844279"
```

---
tags: ["CAAGMOperatorsInterfaces", "CAADoc", "CATICGMTopCleanCrvOperator", "CAAGMModelGemBrowser", "CATICGMTopWire", "CAAGMOperatorsCleanCrv", "CAAAdtCleanCrv"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcAdtCleanCurve.htmmd"
converted: "2026-05-11T17:33:48.844279"
Achieving a Given Continuity along a Wire

---
converted: "2026-05-11T17:33:48.844279"
Achieving a Given Continuity along a Wire
Use Case
Abstract CATICGMTopCleanCrvOperator enables you to correct or improve the (dis)continuities along a wire. It can be run in two modes: either by giving the priority to continuity or by giving the priority to deformation. In neither mode, the points where the curve segments join are displaced. This is an important feature: the operator only modifies the curve around the vertices. An interesting capability of this operator stands in the cell reduction: the vertices where the curvature continuity is achieved can be removed from your topology that way reducing the number of cells.

    * What You Will Learn With This Use Case
    * The CAAGMOperatorsCleanCrv Use Case
      * What Does CAAGMOperatorsCleanCrv Do?
      * How to Launch CAAGMOperatorsCleanCrv
      * Where to Find the CAAGMOperatorsCleanCrv Code
    * Step-by-Step
    * In Short
    * References
---
What You Will Learn With This Use Case In this use case, you learn how to use the CATICGMTopCleanCrvOperator operator to modify a wire in order to get a better continuity at the points where the curve segments are joined. CATICGMTopCleanCrvOperator is to be used according to the general scheme of topological operators. If need be, you can take a look at "Overview of the Topological Operators" [1] for more information. The CAAGMOperatorsCleanCrv Use Case CAAGMOperatorsCleanCrv is a use case of the CAAGMOperatorsInterfaces.edu framework that illustrates the GMOperatorsInterfaces framework capabilities. What Does CAAGMOperatorsCleanCrv Do The use case:
    * Creates the curves making up the wire.
    * Creates a wire by using the CATICGMTopWire operator.
    * Creates a CATICGMTopCleanCrvOperator operator instance.
    * Sets the parameters prior to running the operator. Three set of parameters are tested:
What You Will Learn With This Use Case In this use case, you learn how to use the CATICGMTopCleanCrvOperator operator to modify a wire in order to get a better continuity at the points where the curve segments are joined. CATICGMTopCleanCrvOperator is to be used according to the general scheme of topological operators. If need be, you can take a look at "Overview of the Topological Operators" [1] for more information. The CAAGMOperatorsCleanCrv Use Case CAAGMOperatorsCleanCrv is a use case of the CAAGMOperatorsInterfaces.edu framework that illustrates the GMOperatorsInterfaces framework capabilities. What Does CAAGMOperatorsCleanCrv Do The use case:
      1. No angle specified for the tangency criteria
Targeted continuity: curvature continuity.
      2. Angle specified for the tangency criteria: 32 deg
Targeted continuity: curvature continuity
Cell reduction requested.
      3. Angle specified for the tangency criteria: 32 deg
Targeted continuity: curvature continuity
Cell reduction requested
Criteria to be met on priority is deformation
Maximum deformation of 0.2 specified.

    * Runs the CATICGMTopCleanCrvOperator and retrieve the resulting body.
**Note** : This article only focuses on the operations related to the CATICGMTopCleanCrvOperator operator. Refer to "Overview of the Topological Operators" [3] for more information on the operations which are not detailed in the article. How to Launch CAAGMOperatorsCleanCrv To launch CAAGMOperatorsCleanCrv, you will need to set up the build time environment, then compile CAAGMOperatorsCleanCrv .m, set up the run time environment, and then execute the use case [2]. If you simply type CAAGMOperatorsCleanCrv with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example:  CAAGMOperatorsCleanCrv `e/G2Wire.NCGM` This NCGM file can be displayed using the CAAGMModelGemBrowser use case. Where to Find the CAAGMOperatorsCleanCrv Code The CAAGMOperatorsCleanCrv use case is made of a main named CAAAdtCleanCrv.cpp located in the CAAGMOperatorsCleanCrv .m module of the CAAGMOperatorsInterfaces.edu framework: `InstallRootFolder/CAADoc/CAAGMOperatorsInterfaces.edu/CAAGMOperatorsCleanCrv.m/` where `InstallRootFolder` [2] is the folder where the API CD-ROM is installed. Step-by-Step The use case is divided into the following main steps:
    * Creating the Curves Making up the Wire
    * Creating the Wire to Be Corrected
    * Creating a CATICGMTopCleanCrvOperator Operator Instance
    * Setting the parameters
    * Running the operator and retrieving the resulting body (common to all operators - not discussed below).
Creating the Curves Making up the Wire The curves to be used in the wire are CATLine that are simply created from the geometry factory.

Creating the Curves Making up the Wire The curves to be used in the wire are CATLine that are simply created from the geometry factory.
    CATMathPoint P0(0,0,0);
    CATMathPoint P1(10,7.5,0);
    CATMathPoint P2(20,15,-2);
    CATMathPoint P3(45,20,-5);
    CATMathPoint P4(77,23,-7);

    CATLine * piLine0 = piGeomFactory->CreateLine(P0,P1);
    CATLine * piLine1 = piGeomFactory->CreateLine(P1,P2);
    CATLine * piLine2 = piGeomFactory->CreateLine(P2,P3);
    CATLine * piLine3 = piGeomFactory->CreateLine(P3,P4);

Creating the Wire to Be Corrected You must follow the general scheme of all the topological operators:

    * Create an operator instance.
    * Run it.
    * Retrieve the resulting body.

Creating the Wire to Be Corrected You must follow the general scheme of all the topological operators:
    CATICGMTopWire * pWire0 = ::CATCGMCreateTopWire(piGeomFactory,

            &topdata,
CATICGMTopWire * pWire0 = ::CATCGMCreateTopWire(piGeomFactory,
            nbcurve0,
            ListOfCurves0,
            curLimits0,
            wireOrientations0);

    ...
nbcurve0,
ListOfCurves0,
curLimits0,
wireOrientations0);
    pWire0->Run(#);
    CATBody * pWireBody0 = pWire0->GetResult(#);

Creating a CATICGMTopCleanCrvOperator Operator Instance The CATICGMTopCleanCrvOperator operator is created by the CATCGMCreateTopCleanCrvOperator global function. The wire body is passed as the third argument of the function.

    CATICGMTopCleanCrvOperator * pCleanCrvOpe0 = NULL;
    CATBody * piCleanBody = NULL;

    // 4.1 - Create the operator
    //
CATICGMTopCleanCrvOperator * pCleanCrvOpe0 = NULL;
CATBody * piCleanBody = NULL;
```vbscript
    pCleanCrvOpe0 =::CATCGMCreateTopCleanCrvOperator(piGeomFactory,

```

            &topdata,
            pWireBody0);  // the wire to be corrected

pCleanCrvOpe0 =::CATCGMCreateTopCleanCrvOperator(piGeomFactory,
pWireBody0);  // the wire to be corrected
Setting the parameters Three set of parameters are tested. For each set, the G2 continuity is requested.
    1. **Case a** : No angle specified for the tangency criteria, by default this angle is set to 0.5 deg. The G2 requirement is not achieved.

           pCleanCrvOpe0->SetContinuityLevel(CATFrFCurvatureCont) ; // G2 requested

The resulting body and the input body are the same: ![Input and Resulting Bodies](images/CAACgmAdtcleancrv1.gif)
    2. **Case b** : The angle specified for the tangency criteria is 32 deg - the cell reduction is requested. In other words, the simplification of the topology is requested whenever a vertex becomes G2 continuous.

           pCleanCrvOpe0->SetContinuityLevel(CATFrFCurvatureCont) ; /* Target: G2 */
           pCleanCrvOpe0->SetCellReduction(TRUE) ; // Cell reduction requested
           CATAngle tanAngle = 32;
           pCleanCrvOpe0->SetTangencyAngle(tanAngle); // Tangency criteria specified

The resulting body only has two vertices.

![Resulting Body](images/CAACgmAdtcleancrv2.gif) The model displayed in the figure above is obtained by applying the "Porcupine" capability of the Generative Shape Design product on the resulting curve. Red lines represent the curvature along the resulting wire while the green curve represents the curvature envelope.
CATAngle tanAngle = 32;
pCleanCrvOpe0->SetTangencyAngle(tanAngle); // Tangency criteria specified
The resulting body only has two vertices.
The second derivative is always null at the vertex location, in other words there is an inflexion at each vertex. In order to achieve G2 continuity at all price, the curve may exhibit an undesirable bulge around a vertex Keep in mind that the resulting curve is not C2 but G2 continuous.
    3. **Case c** : The angle specified for the tangency criteria is 32 deg - The cell reduction requested - The criteria to be met on priority is deformation. Setting the priority criteria to the deformation does not imply that the maximum has to be specified. By default this deformation is set to 0.001 - In this sample, a value of 0.2 is specified:

           pCleanCrvOpe0->SetContinuityLevel(CATFrFCurvatureCont) ; /* Target: G2 */
           pCleanCrvOpe0->SetCellReduction(TRUE) ;  // Cell reduction requested
           CATAngle tanAngle = 32;
           pCleanCrvOpe0->SetTangencyAngle(tanAngle);  // Tangency criteria specified

The resulting curve is corrected and the cell reduction is also achieved.

![Resulting Curve](images/CAACgmAdtcleancrv3.gif)
CATAngle tanAngle = 32;
pCleanCrvOpe0->SetTangencyAngle(tanAngle);  // Tangency criteria specified
The resulting curve is corrected and the cell reduction is also achieved.
But after a "Porcupine" operation, the resulting body exhibits some abrupt changes in the second derivative. The resulting curve exhibits local irregularities. Using the CATICGMTopCleanCrvOperator operator requires a fine tuning of the parameters. Being G2 at all price does not mean that the quality of the resulting curve suits your application needs. The operator is best fit to work with a slight or moderate tangency angle threshold, that way you may reduce not all the vertices but obtain a better quality on the reduced portion.
In Short The CATICGMTopCleanCrvOperator operator attempts to achieve a given geometric continuity along a wire. The cell reduction is a process whereby the topology is simplified whenever the G2 continuity is achieved at a vertex. CATICGMTopCleanCrvOperator is not really a smoothing operator, depending on the parameters specified, the resulting curve may exhibit bulges at inflexions. References [1] |  [Overview of the Topological Operators](CAACgmUcTopOverview.md)

[2] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
But after a "Porcupine" operation, the resulting body exhibits some abrupt changes in the second derivative. The resulting curve exhibits local irregularities. Using the CATICGMTopCleanCrvOperator operator requires a fine tuning of the parameters. Being G2 at all price does not mean that the quality of the resulting curve suits your application needs. The operator is best fit to work with a slight or moderate tangency angle threshold, that way you may reduce not all the vertices but obtain a better quality on the reduced portion.
In Short The CATICGMTopCleanCrvOperator operator attempts to achieve a given geometric continuity along a wire. The cell reduction is a process whereby the topology is simplified whenever the G2 continuity is achieved at a vertex. CATICGMTopCleanCrvOperator is not really a smoothing operator, depending on the parameters specified, the resulting curve may exhibit bulges at inflexions. References [1] |  [Overview of the Topological Operators](CAACgmUcTopOverview.md)
History Version: **1** [Feb 2002] | Document created
