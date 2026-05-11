---
title: "Converting Curves into NURBS"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CAADoc", "CAACrvFittingToNurbsCrv", "CAAGMOperatorsCrvFittingToNurbsCrv", "CATICGMCrvFittingToNurbsCrv", "CATICGMObject", "CAAGMModelGemBrowser", "CATIA"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcFrfCrvFittingToNurbsCrv.md"
converted: "2026-05-11T17:33:48.934549"
---

Converting Curves into NURBS  
---  
Use Case  
Abstract You can convert curves into NURBS by using the CATICGMCrvFittingToNurbsCrv operator. This operator allows you to specify the characteristics of the resulting NURBS as well as a maximum deviation you would like to obtain with respect to the initial curve. This maximum deviation may not be achieved.
    * What You Will Learn With This Use Case
    * The CATICGMCrvFittingToNurbsCrv  Operator
    * The CAAGMOperatorsCrvFittingToNurbsCrv Use Case
      * What Does CAAGMOperatorsCrvFittingToNurbsCrv Do
      * How to Launch CAAGMOperatorsCrvFittingToNurbsCrv
      * Where to Find the CAAGMOperatorsCrvFittingToNurbsCrv Code
    * Step-by-Step
    * In Short
    * References  
---  
What You Will Learn With This Use Case This use case is intended to help you use the free form operators. It particularly illustrates how to convert a curve into a NURBS. The CATICGMCrvFittingToNurbsCrv  Operator The CATICGMCrvFittingToNurbsCrv  operator is to be used according to the general scheme of operators:
    1. Creation of an operator instance from a global function. Two modes BASIC or ADVANCED are proposed.
    2. If the ADVANCED mode is chosen, tuning of the parameters by using the Setxxx methods then run of the operator.
    3. Retrieve the created NURBS by using the GetPNurbs method.
**Note** : In ADVANCED mode, you cannot use the same operator to convert several curves. You must replay the sequence below:
    1. Operator creation.
    2. Set of parameters.
    3. Run.
    4. GetPNurbs.
    5. Operator deletion.
As many times as you need. The CAAGMOperatorsCrvFittingToNurbsCrv Use Case CAAGMOperatorsCrvFittingToNurbsCrv is a use case of the CAAGMOperatorsInterfaces.edu framework that illustrates the GMOperatorsInterfaces framework capabilities. What Does CAAGMOperatorsCrvFittingToNurbsCrv __ Do This use case:
    1. Creates a PSpline to be converted into a Nurbs.
    2. Creates a CATICGMCrvFittingToNurbsCrv operator to be used to convert the initial curve into a rational curve _._ A constraint __ is __ set on the minimum length of an arc.
    3. Retrieves the created Nurbs.
How to Launch CAAGMOperatorsCrvFittingToNurbsCrv To launch CAAGMOperatorsCrvFittingToNurbsCrv, you will need to set up the build time environment, then compile CAAGMOperatorsCrvFittingToNurbsCrv.m along with its prerequisites, set up the run time environment, and then execute the use case [4]. If you simply type CAAGMOperatorsCrvFittingToNurbsCrv with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example: `CAAGMOperatorsCrvFittingToNurbsCrv e/NurbsSur.NCGM` This NCGM file can be displayed using the CAAGMModelGemBrowser use case. Where to Find the CAAGMOperatorsCrvFittingToNurbsCrv Code The CAAGMOperatorsCrvFittingToNurbsCrv use case is made of a main named CAACrvFittingToNurbsCrv.cpp located in the CAAGMOperatorsCrvFittingToNurbsCrv.m module of the CAAGMOperatorsInterfaces.edu framework: `InstallRootFolder\CAADoc\CAAGMOperatorsInterfaces.edu\CAAGMOperatorsCrvFittingToNurbsCrv.m\` where `InstallRootFolder` [4] is the folder where the API CD-ROM is installed. Step-by-Step CAAGMOperatorsCrvFittingToNurbsCrv .cpp is divided into four logical steps:
    1. Creating the Geometry Factory
    2. Creating the Curve to Be Converted into a NURBS
    3. Converting the Created Curve into a NURBS and Specifying a Constraint on the Minimum Length of an Arc
    4. Writing the Model and Closing the Container
Creating the Geometry Factory The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject (and the curves and surfaces in particular) [1]. This creation is done by the global function `::CATCreateCGMContainer`. Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.
    
    CATGeoFactory* piGeomFactory = **::CATCreateCGMContainer**() ;
    if (NULL==piGeomFactory) return (1);

Creating the Curve to Be Converted into a NURBS The curve to be converted is a PSpline. Its underlying geometry is a sphere. All the geometric objects are created from the geometry factory. Converting the Created Curve into a NURBS and Specifying a Constraint on the Minimum Length of an Arc This first operator is intended to create an operator instance with the following parameters:
    1. A 0.001 maximum deviation. It is important to note that this value is the modeler resolution and it would not be meaningful to specify a maximum deviation less than this resolution.
    2. The rational factor is 1 - meaning that resulting curve is to be rational.
    
    CATICGMCrvFittingToNurbsCrv  * pCrvFitting1 = ::CATCGMCreateCrvFittingToNurbsCrv(piGeomFactory,
                      pConfig,
    		piCurve,
    		crvLimits,
    		maxdeviation,
    		1,
    		ADVANCED) ;

At this stage, you have just created an instance of operator. Prior to running the operator, the minimum length of an arc is set to 14.
    
    //  (d) --- Specifies the minimal length of an arc on the output curve
    //          Should be properly specified with respect to the input curve
    //          length - otherwise the execution results in an abend
    //
    pCrvFitting1->SetInternalMinLength(14);

If you want to get the converted NURBS, you must Run the operator and retrieve the resulting NURBS by using the GetPNurbs method. To convert a CATPCurve into a CATNurbsCurve, you can use the Set3DCurveCreation method (before applying the Run method), then use the GetNurbsCurve method instead of GetPNurbs.
    
    pCrvFitting1->Run();
    CATPNurbs * piPNurbs1 = pCrvFitting1->GetPNurbs();

The transformation of the curve into NURBS is not exact. To check this, you can use the IsExactTransformation method or retrieve the maximum deviation (0.899 is returned in the present use case).
    
    cout << "Maximum deviation is " << pCrvFitting1->GetMaxDeviation() << endl;

Writing the Model and Closing the Factory To save the model in a file, the `::CATSaveCGMContainer` global function is used. Notice that in the use case, the save is conditioned by an input parameter representing the file inside which the model must be saved. The use case ends with the closure of the geometry factory, done by the ` ::CATCloseCGMContainer` global function.
    
    if(1==toStore)
     {
    #ifdef _WINDOWS_SOURCE
       ofstream filetowrite(pfileName, ios::binary ) ;
    #else
       ofstream filetowrite(pfileName,ios::out,filebuf::openprot) ;
    #endif
    
       **::CATSaveCGMContainer**(piGeomFactory,filetowrite);
       filetowrite.close();
     }	
    
     //
     // Closes the container
     //	
     **::CATCloseCGMContainer**(piGeomFactory);

In Short The CATICGMCrvFittingToNurbsCrv operator allows you to convert a curve into a NURBS. Apart from the usual parameters, this operator requires you specify the maximum deviation you would like to obtain from the initial curve as well as the rationality. Constraints on the resulting curve can be specified by using Setxxx methods. References [1] |  [ About NURBS](../CAACgmModel/CAACgmTaGobAboutNurbs.md)  
---|---  
[2] |  [ The Objects of CATIA Geometric Modeler](../CAACgmModel/CAACgmTaGobGeoObjects.md)  
[3] |  [ The Curves of CATIA Geometric Modeler](../CAACgmModel/CAACgmTaGobCurves.md)  
[4] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
[5] | [Converting Surfaces into NURBS](CAACgmUcFrfSurFittingToNurbsSur.md)  
History Version: **1** [Feb 2000] | Document created  
---|---
