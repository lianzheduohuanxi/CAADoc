---
title: "Using the Smoothing Options when Creating a Sweep"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CAADoc", "CAAAdtSweepSmoothingCode", "CATICGMObject", "CAAGemBrowser", "CATICGMFrFTopologicalSweep", "CAAGMOperatorsSweepSmoothing", "CATIA"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcAdtSweepSmoothing.htm"
converted: "2026-05-11T17:33:48.857282"
---

Using the Smoothing Options when Creating a Sweep  
---  
Use Case  
Abstract The CATICGMFrFTopologicalSweep operator enables you to create sweeps. This use case explains how to create a circle sweep with two guides and a tangency surface.
    * What You Will Learn With This Use Case
    * The CAAGMOperatorsSweepSmoothing Use Case
      * What Does CAAGMOperatorsSweepSmoothing Do?
      * How to Launch CAAGMOperatorsSweepSmoothing
      * Where to Find the CAAGMOperatorsSweepSmoothing Code
    * Step-by-Step
    * In Short
    * References  
---  
What You Will Learn With This Use Case In this use case, you learn how to use the "Smooth Sweeping" option of the CATICGMFrFTopologicalSweep operator. You create a segment sweep with a guide curve and a reference surface, specify the input data as indicated below and improve the sweep surface quality by acting on the "Smooth sweeping" parameters. CATICGMFrFTopologicalSweep is to be used according to the general scheme of topological operators. If need be, you can take a look at "Overview of the Topological Operators" [1] for more information. 
---|---  
The CAAGMOperatorsSweepSmoothing Use Case Reminder In a CATIA session, the "Smooth Sweeping" option can be used in two cases:
    1. Whenever a sweep cannot be generated because the specified input data are invalid (guide not continuous in tangency or not planar).
    2. Whenever the generated sweep does not provide the user with the expected quality. The user may wish to reduce the number of edges on the created surface or at least improve the tangency conditions along the edges.
There are two parameters to be adjusted in order to perform a sweep that does not complete with the standard options or to achieve a sweep of better quality: The "Angular Correction" Option This parameter is related to the angular tolerance of the moving frame (plane that moves perpendicularly along the guide curve). When the "Angular Correction" option is activated, the sweep algorithm tries to modify the angle between the moving frame and the guide curve to complete the sweep operation or produce a surface of better quality. The "Deviation From Guide" Option This parameter defines the gap authorized between the guide curve and the sweep itself. With the default option, there is no gap. When this option is activated, the sweep algorithm tries to generate a surface that does not stick necessarily to the guide curve but is of better quality or enables the completion of the sweep operation. When the resulting sweep is smooth enough, some edges can be cleaned. For more information, see the CATIA/Shape/Generative Shape Design/User Tasks/Creating Surfaces/Creating Swept Surfaces interactive documentation. The Improvements to Be Expected By adjusting the parameters above, you can reduce the tangency constraints along the edges and reduce the number of patches for the Nurbs surfaces underlying the sweep faces. What Does CAAGMOperatorsSweepSmoothing Do? The use case:
    * Retrieves the input data (guide curve and reference surface) from the TolerantSweepInit.ncgm[*] file.
    * Creates a CATICGMFrFTopologicalSweep  operator instance.
    * Specifies the sweep parameters (angle and length laws, smoothing options).
    * Runs the CATICGMFrFTopologicalSweep  and retrieve the resulting body.
How to Launch CAAGMOperatorsSweepSmoothing To launch CAAGMOperatorsSweepSmoothing, you will need to set up the build time environment, then compile CAAGMOperatorsSweepSmoothing.m, set up the run time environment, and then execute the use case [2].  To launch this use case you must type the command below, this commands saves the result in the outfile.NCGM file: `CAAGMOperatorsSweepSmoothing .../tolerantSweepInit.ncgm `outfile.NCGM This NCGM file can be displayed using the CAAGemBrowser use case. Where to Find the CAAGMOperatorsSweepSmoothing Code The CAAGMOperatorsSweepSmoothing code use case is made of a main named CAAAdtSweepSmoothingCode.cpp located in the CAAGMOperatorsSweepSmoothing.m code module of the CAAGMOperatorsInterfaces.edu framework: `InstallRootFolder\CAADoc\CAAGMOperatorsInterfaces.edu\CAAGMOperatorsSweepSmoothing.m\` where `InstallRootFolder` [2] is the folder where the API CD-ROM is installed. Step-by-Step The use case is divided into the following main steps:
    * Retrieving the Input Data
    * Creating a CATICGMFrFTopologicalSweep Operator Instance
    * Setting the Smooth Options
    * Running the operator and retrieving the resulting body (common to all operators - not discussed below).
Retrieving the Input Data The guide curve as well as the reference surface are retrieved from the input file by using the CATICGMObject::GetPersistentTag method. Creating a CATICGMFrFTopologicalSweep Operator Instance The CATICGMFrFTopologicalSweep operator is created by the CATCGMCreateFrFTopologicalSegmentSweep global function. The guide is passed in the form of a list as the third argument of the function.
    
    // (a) - Define the list of guides (a single guide list in this case)
    //
    
    CATLISTP(CATGeometry) guides= NULL;
    CATGeometry * guideGeom = (CATGeometry*)piInputBody ; 
    guides.Append(guideGeom);
    
    // (b) - Create the sweep operator
    //
    
    CATICGMFrFTopologicalSweep  * sweepOpe =::CATCGMCreateFrFTopologicalSegmentSweep(piGeomFactory, 
    &topdata, &guides);

Setting the Smooth Options The "smooth sweeping" options are specified by using the combination of services below: Service(s) | Correspond(s) to  
---|---  
SetSmoothOption(1) + SetSmoothAngleThreshold(_RadianAngleTol_) | "Angular correction" check box activated.  
SetCleanGuidesOption(1, ..., ..., ...); | "Deviation from Guide" check box activated.  
No SetSmoothOption or SetSmoothOption(0) | "Angular correction" check box deactivated.  
No SetCleanGuidesOption or SetCleanGuidesOption (0) | "Deviation from Guide" check box deactivated.  
Four set of data are specified. The result is analyzed by using the "Apply Dress-Up" capability of the "Free Style" workbench. "Apply Dress-Up" allows you to display the number of patches for each face of the generated sweep as well as the isoparametric curves (dotted lines). The "Connect Checker" is used to check the tangency condition along edges. Specification 1 Deviation from Guide: 0.03 mm  
Angular correction: not activated  
---  
**Code**
    
    sweepOpe -> SetSmoothOption (**0**);
    double iCleanMaxDeformation=**0.03** ;
    sweepOpe -> SetCleanGuidesOption(**1** ,
                 &iCleanMaxDeformation,NULL, NULL);

**Comments** The tangency conditions along the two edges are not satisfactory (maximum angle between edges: 5.921deg) Face 1: 2 knots along U - 2 along V  
Face 2: 3 knots along U - 2 along V  
Face 3: 2 knots along U - 2 along V 
Specification 2 Deviation from Guide: 0.03 mm  
Angular correction: 0.5deg  
**Code**
    
    sweepOpe -> SetSmoothOption (1);
    double AngleTol = 0.5 ;// in degrees
    double RadianAngleTol = AngleTol*CATDegreeToRadian;
    sweepOpe -> SetSmoothAngleThreshold(RadianAngleTol);
    double iCleanMaxDeformation=0.03;
    sweepOpe -> SetCleanGuidesOption(1,
                 &iCleanMaxDeformation, NULL, NULL);

**Comments** The tangency conditions along the two edges are satisfactory (Max is 0deg). Face 1: 3 knots along U - 2 along V  
Face 2: 4 knots along U - 2 along V  
Face 3: 3 knots along U - 2 along V 
Specification 3 Deviation from Guide: 1mm  
Angular correction: 2deg  
**Code**
    
    sweepOpe -> SetSmoothOption (1);
    double AngleTol = 2 ;// in degrees
    double RadianAngleTol = AngleTol*CATDegreeToRadian;
    sweepOpe -> SetSmoothAngleThreshold(RadianAngleTol);
    double iCleanMaxDeformation=1;
    sweepOpe -> SetCleanGuidesOption(1,
                 &iCleanMaxDeformation, NULL, NULL);

**Comments** The tangency conditions along the two edges are satisfactory (Max is 0deg) Face 1: 2 knots along U - 2 along V  
Face 2: 3 knots along U - 2 along V  
Face 3: 2 knots along U - 2 along V 
Specification 4 No smooth option specified - a throw is issued - the sweep cannot be generated.  
In Short This use case is an example of how to the smooth options to achieve a better quality of the segment sweep.  References [*] | Delivered in CAAGMOperatorsInterfaces.edu/FunctionTests/InputData  
---|---  
[1] | [Overview of the Topological Operators](CAACgmUcTopOverview.md)  
[2] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
[3] | [Using the Basic Topological Operators](CAACgmUcTopSpline.md)  
History Version: **1** [Aug 2002] | Document created  
---|---  
Version: **2** [Jan 2008] | Document Modified
