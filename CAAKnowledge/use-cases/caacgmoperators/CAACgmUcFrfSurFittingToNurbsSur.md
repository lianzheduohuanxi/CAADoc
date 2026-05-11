---
```vbscript
title: "Converting Surfaces into NURBS"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsSurFittingToNurbsSur", "CAAGMOperatorsInterfaces", "CAADoc", "CATICGMSurFittingToNurbsSur", "CATICGMObject", "CAAGMModelGemBrowser", "CAASurFittingToNurbsSur", "CATIA", "CAAGMOperatorInterfaces"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcFrfSurFittingToNurbsSur.htm"
converted: "2026-05-11T17:33:48.947040"
```

---
tags: ["CAAGMOperatorsSurFittingToNurbsSur", "CAAGMOperatorsInterfaces", "CAADoc", "CATICGMSurFittingToNurbsSur", "CATICGMObject", "CAAGMModelGemBrowser", "CAASurFittingToNurbsSur", "CATIA", "CAAGMOperatorInterfaces"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcFrfSurFittingToNurbsSur.htm"
converted: "2026-05-11T17:33:48.947040"
Converting Surfaces into NURBS

---
converted: "2026-05-11T17:33:48.947040"
Converting Surfaces into NURBS
Use Case
Abstract You can convert surfaces into NURBS by using the CATICGMSurFittingToNurbsSur operator. These operator allows you to specify the characteristics of the resulting NURBS as well as a maximum deviation you would like to obtain with respect to the initial surface.

    * What You Will Learn With This Use Case
    * The CATICGMSurFittingToNurbsSur Operator
    * The CAAGMOperatorsSurFittingToNurbsSur Use Case
      * What Does CAAGMOperatorsSurFittingToNurbsSur Do
      * How to Launch CAAGMOperatorsSurFittingToNurbsSur
      * Where to Find the CAAGMOperatorsSurFittingToNurbsSur Code
    * Step-by-Step
    * In Short
    * References
---
What You Will Learn With This Use Case This use case is intended to help you use the free form operators. It particularly illustrates how to convert a curve/surface into a NURBS curve/surface. The CATICGMSurFittingToNurbsSur Operator The CATICGMSurFittingToNurbsSur operator is to be used according to the general scheme of operators:
    1. Creation of an operator instance from a global function. Two modes BASIC or ADVANCED are proposed.
    2. If the ADVANCED mode is chosen, tuning of the parameters by using the Setxxx methods then run of the operator.
    3. Retrieve the created NURBS by using the GetNurbsxxx method.

**Note** : In ADVANCED mode, you cannot use the same operator to convert several surfaces. You must replay the sequence below:
What You Will Learn With This Use Case This use case is intended to help you use the free form operators. It particularly illustrates how to convert a curve/surface into a NURBS curve/surface. The CATICGMSurFittingToNurbsSur Operator The CATICGMSurFittingToNurbsSur operator is to be used according to the general scheme of operators:
1. Creation of an operator instance from a global function. Two modes BASIC or ADVANCED are proposed.
2. If the ADVANCED mode is chosen, tuning of the parameters by using the Setxxx methods then run of the operator.
3. Retrieve the created NURBS by using the GetNurbsxxx method.
    1. Operator creation.
    2. Set of parameters.
    3. Run.
    4. GetNurbsSurface.
    5. Operator deletion.
As many times as you need. The CAAGMOperatorsSurFittingToNurbsSur Use Case CAAGMOperatorsSurFittingToNurbsSur is a use case of the CAAGMOperatorsInterfaces.edu framework that illustrates the GMOperatorsInterfaces framework capabilities. What Does CAAGMOperatorsSurFittingToNurbsSur Do This use case
    1. Creates a revolution surface to be converted into a NURBS surface.
    2. Creates a first CATICGMSurFittingToNurbsSur operator to be used to convert the initial surface into a rational surface. No constraints are specified.
    3. Creates a second CATICGMSurFittingToNurbsSur operator and set a constraint on the minimum length of an arc.
How to Launch CAAGMOperatorsSurFittingToNurbsSur To launch CAAGMOperatorsSurFittingToNurbsSur, you will need to set up the build time environment, then compile CAAGMOperatorsSurFittingToNurbsSur.m along with its prerequisites, set up the run time environment, and then execute the use case [4]. If you simply type CAAGMOperatorsSurFittingToNurbsSur with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example: `CAAGMOperatorsSurFittingToNurbsSur e/NurbsSur.NCGM` This NCGM file can be displayed using the CAAGMModelGemBrowser use case. Where to Find the CAAGMOperatorsSurFittingToNurbsSur Code The CAAGMOperatorsSurFittingToNurbsSur use case is made of a main named CAASurFittingToNurbsSur.cpp located in the CAAGMOperatorsSurFittingToNurbsSur.m module of the CAAGMOperatorInterfaces.edu framework: `InstallRootFolder\CAADoc\CAAGMOperatorInterfaces.edu\CAAGMOperatorsSurFittingToNurbsSur.m\` where `InstallRootFolder` [4] is the folder where the API CD-ROM is installed. Step-by-Step CAAGMOperatorsSurFittingToNurbsSur.cpp is divided into five logical steps:
    1. Creating the Geometry Factory
    2. Creating the Surface to Be Converted into NURBS
    3. Converting the Created Surface into a NURBS without Specifying Any Constraints
    4. Converting the Created Surface into a NURBS and Specifying a Constraint on the Minimum Length of an Arc
    5. Writing the Model and Closing the Container
Creating the Geometry Factory The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject (and the curves and surfaces in particular) [1]. This creation is done by the global function `::CATCreateCGMContainer`. Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.

    CATGeoFactory* piGeomFactory = **::CATCreateCGMContainer**() ;
```vbscript
    if (NULL==piGeomFactory) return (1);

```

Creating the Surface to Be Converted into a NURBS The surface to be converted is a revolution surface created from a spline curve. Both the spline and the revolution surface are geometric objects created from the geometry factory. Converting the Created Surface into a NURBS without Specifying any Constraints This first operator is intended to create an operator instance with the following parameters:
    1. A 0.001 maximum deviation. It is important to note that this value is the CATIA resolution and it would not be meaningful to specify a maximum deviation less than this resolution.
    2. The rational factor is 1 - meaning that resulting curve is to be rational (different weights can be assigned to control points.

    CATICGMSurFittingToNurbsSur * pSurFitting1 =

    		::CATCGMCreateSurFittingToNurbsSur(piGeomFactory,
1. A 0.001 maximum deviation. It is important to note that this value is the CATIA resolution and it would not be meaningful to specify a maximum deviation less than this resolution.
2. The rational factor is 1 - meaning that resulting curve is to be rational (different weights can be assigned to control points.
CATICGMSurFittingToNurbsSur * pSurFitting1 =
    		pConfig,
    		piSurface,
    		surLimits,
    		0.001,
    		1,
    		ADVANCED);

At this stage, you have just created an instance of operator, if you want to get the converted NURBS, you must Run the operator and retrieve the resulting NURBS by using the GetNurbsSurface operator.

    pSurFitting1->Run();
    CATNurbsSurface * pNurbsSurf1 = pSurFitting1->GetNurbsSurface();

The transformation of the surface into NURBS is exact. To check this, you can use the IsExactTransformation method or retrieve the maximum deviation (0 is returned in the present use case).

    // (g) --- Determine whether the transformation is exact
    // "Transformation exact" expected as the surface
    // has been specified rational
    //
    IsExact = pSurFitting1->IsExactTransformation();
```vbscript
    if (IsExact == 0) cout << "Transformation not exact" << endl;
```

    else {cout << "Exact transformation" << endl;}

    // (h) --- Display the maximum deviation on the standard output
    //
IsExact = pSurFitting1->IsExactTransformation();
```vbscript
if (IsExact == 0) cout << "Transformation not exact" << endl;
```

else {cout << "Exact transformation" << endl;}
    maxDeviat = pSurFitting1->GetMaxDeviation();
    cout << "Maximum deviation of surface 1 " <<  maxDeviat << endl;

Modify the rationality factor by replacing 1 with 0 in the argument 4 of the CATCreateSurFittingToNurbsSur operator. Recompile and rerun, the curve cannot be converted exactly because actually, you have set a constraint on the control point weights (1 everywhere). Converting the Created Surface into a NURBS and Specifying a Constraint on the Minimum Length of an Arc This second operator is intended to create an operator instance with the same parameters as the first operator. Prior to running the operator, the minimum length of an arc is set to 32. The resulting transformation is not exact and a maximum deformation around 0.09 is achieved. The operator tries first to comply the parameters specified by using the Setxxx methods. Writing the Model and Closing the Factory To save the model in a file, the `::CATSaveCGMContainer` global function is used. Notice that in the use case, the save is conditioned by an input parameter representing the file inside which the model must be saved. The use case ends with the closure of the geometry factory, done by the ` ::CATCloseCGMContainer` global function.

    if(1==toStore)

     {
    #ifdef _WINDOWS_SOURCE
Modify the rationality factor by replacing 1 with 0 in the argument 4 of the CATCreateSurFittingToNurbsSur operator. Recompile and rerun, the curve cannot be converted exactly because actually, you have set a constraint on the control point weights (1 everywhere). Converting the Created Surface into a NURBS and Specifying a Constraint on the Minimum Length of an Arc This second operator is intended to create an operator instance with the same parameters as the first operator. Prior to running the operator, the minimum length of an arc is set to 32. The resulting transformation is not exact and a maximum deformation around 0.09 is achieved. The operator tries first to comply the parameters specified by using the Setxxx methods. Writing the Model and Closing the Factory To save the model in a file, the `::CATSaveCGMContainer` global function is used. Notice that in the use case, the save is conditioned by an input parameter representing the file inside which the model must be saved. The use case ends with the closure of the geometry factory, done by the ` ::CATCloseCGMContainer` global function.
if(1==toStore)
       ofstream filetowrite(pfileName, ios::binary ) ;

    #else
```vbscript
if(1==toStore)
ofstream filetowrite(pfileName, ios::binary ) ;
       ofstream filetowrite(pfileName,ios::out,filebuf::openprot) ;
```

    #endif

       **::CATSaveCGMContainer**(piGeomFactory,filetowrite);
       filetowrite.close();
     }

     //
     // Closes the container
     //
     **::CATCloseCGMContainer**(piGeomFactory);

In Short The CATICGMSurFittingToNurbsSur operators allows you to convert a surface into a NURBS surface. Apart from the usual parameters, this operator requires you specify the maximum deviation you would like to obtain from the initial surface as well as the rationality. Constraints on the resulting surface can be specified by using Setxxx methods. References [1] |  [ About NURBS](../CAACgmModel/CAACgmTaGobAboutNurbs.md)
---|---
[2] |  [ The Objects of CATIA Geometric Modeler](../CAACgmModel/CAACgmTaGobGeoObjects.md)
[3] |  [ The Curves of CATIA Geometric Modeler](../CAACgmModel/CAACgmTaGobCurves.md)
[4] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
History Version: **1** [Feb 2000] | Document created
---|---
