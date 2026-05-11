---
title: "Creating Fillets"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CAADoc", "CAATopVariableFillets", "CAATopConstantFillets", "CATICGMObject", "CAAGMModelGemBrowser", "CATICGMDynFillet", "CAATopRollingEdges", "CAATopFilletsMain", "CAAGMOperatorsAllFillets"]
source_file: "Doc\online\CAACgmOperators\CAACgmUcTopAllFillets.htm"
converted: "2026-05-11T17:33:49.071438"
---

Fillets  
---  
Use Case  
Abstract This use case explains how to create constant fillets, variable fillets and fillets with rolling edges.
    * What You Will Learn With This Use Case
    * The CAAGMOperatorsAllFillets Use Case
      * What Does CAAGMOperatorsAllFillets Do?
      * How to Launch CAAGMOperatorsAllFillets
      * Where to Find the CAAGMOperatorsAllFillets Code
    * Step-by-Step
    * In Short
    * References  
---  
What You Will Learn With This Use Case This use case is intended to help you use fillets in geometric modeler applications. The CAAGMOperatorsAllFillets Use Case CAAGMOperatorsAllFillets is a use case of the CAAGMOperatorsInterfaces.edu framework that illustrates GMOperatorsInterfaces framework capabilities. What Does CAAGMOperatorsAllFillets Do? CAAGMOperatorsAllFillets creates two solid cuboids, performs a Boolean union of the cubes, then creates fillets on the resulting solid. ![Constant Radius Fillet](images/CAACgmTopfilletconstant.gif) | The CAATopConstantFillets function which is defined in the CAATopConstantFillets.cpp file creates a constant fillet along the edges common to both cubes.  
---|---  
![Constant Radius Fillet](images/CAACgmToprollingedges.gif) | The CAATopRollingEdges function which is defined in the CAATopRollingEdges.cpp file creates a fillet along the common edges and for specified rolling edges.  
![Variable Radius Fillet](images/CAACgmTopvariableradius.gif) | The CAATopVariableFillets function which is defined in the CAATopVariableFillets.cpp file creates a variable radius fillet on one edge of the solid.  
How to Launch CAAGMOperatorsAllFillets To launch CAAGMOperatorsAllFillets, you will need to set up the build time environment, then compile CAAGMOperatorsAllFillets.m along with its prerequisites, set up the run time environment, and then execute the use case [1]. If you simply type CAAGMOperatorsAllFillets with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example: `CAAGMOperatorsAllFillets e:\Fillets.NCGM` This NCGM file can be displayed using the CAAGMModelGemBrowser use case. Where to Find the CAAGMOperatorsAllFillets Code The CAAGMOperatorsAllFillets use case is made of a main named CAATopFilletsMain.cpp located in the CAAGMOperatorsAllFillets.m module of the CAAGMOperatorsInterfaces.edu framework: `InstallRootFolder\CAADoc\CAAGMOperatorsInterfaces.edu\CAAGMOperatorsAllFillets.m\` where `InstallRootFolder` [1] is the folder where the API CD-ROM is installed. Step-by-Step There are seven steps in CAATopFilletsMain.cpp:
    1. Creating the Geometry Factory
    2. Creating the Solid Cuboids
    3. Performing a Boolean Union on the Cuboids
    4. Creating a Constant Radius Fillet around the Edges Common to Both Cubes
    5. Creating a Constant Radius Fillet by Specifying Rolling Edges
    6. Creating a Variable Radius Fillet
    7. Writing the Model and Closing the Container
Creating the Geometry Factory The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject. This creation is done by the global function `::CATCreateCGMContainer`. Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.
    
    CATGeoFactory* piGeomFactory = **::CATCreateCGMContainer**() ;
    if (NULL==piGeomFactory) return (1);

Creating the Solid Cuboids See [2] which illustrates how to create a solid cuboid. Performing a Boolean Union on the Cuboids See also [2]. Creating a Constant Radius Fillet around the Edges Common to Both Cubes To create a constant radius fillet, you must:
    1. Define your CATDynFilletRadius. 
           
           double * ratio= NULL;
           CATDynFilletRadius * pRadius = new CATDynFilletRadius(3.,    // radius value
                       NULL,  
                       ratio,  
                       NULL);

The arguments two, three and four of the constructor are only to be specified when the fillet to be created is of variable radius. The cells to be filleted with a constant radius are specified in the CATDynEdgeFilletRibbon constructor.
    2. Define the CATDynEdgeFilletRibbon object whereby you specify what cells are to be filleted. If you create a constant radius fillet, the list to be passed as the second argument of the CATDynEdgeFilletRibbon is a single item list. 
           
           CATLISTP(CATDynFilletRadius) listRadius;		
           listRadius.Append(pRadius);		
           CATDynEdgeFilletRibbon * pRibbon = new CATDynEdgeFilletRibbon(listEdges, listRadius);

    3. If need be, set the parameters of the CATDynFilletRibbon. 
           
           pRibbon ->SetSegmentationMode(CATDynTrim);

    4. Create the CATICGMDynFillet operator by using the CATCGMCreateDynFillet operator. 
           
           CATICGMDynFillet * pFilletOp1 = CATCGMCreateDynFillet(iFactory,iTopData,iBody);

    5. Append the CATDynEdgeFilletRibbon to the operator instance. 
           
           pFilletOp1 ->Append(pRibbon);

Creating a Constant Radius Fillet by Specifying Rolling Edges To create a variable radius fillet, you must:
    1. Proceed as you would do for a constant radius fillet.
    2. In the CATDynEdgeFilletRibbon constructor, specify the list of rolling edges as well as the fillet behavior (CATDynRolling). 
           
           CATDynEdgeFilletRibbon * pRibbon = new CATDynEdgeFilletRibbon(listEdges, listRadius,
                       CATBody::CATEdgePropagAuto,
                       listRollingEdges,   // the rolling edges
                       CATDynRolling);

Creating a Variable Radius Fillet To create a variable radius fillet, you must:
    1. Define the CATDynFilletRadius necessary to define the fillet shape. You must specify: 
       * The radius value (in mm).
       * The pointer to the cell on which the fillet is to be applied.
       * The pointer to the ratio of the edge length which defines the point where the radius is defined.
       * And the pointer to the tangency angle at the point where the radius is specified. Note that either a NULL pointer or a NULL angle are supported so far. If a NULL pointer is passed, the radius law is not constrained and the resulting fillet looks something like a "linear" one. If a NULL value is passed for the extremities, the resulting fillet looks something like a "cubic" one.
    
    double * ratio0= new double(0.0);
    CATDynFilletRadius * pRadius0 = new CATDynFilletRadius(4.,  // radius value
                listCells[2],  
                ratio0,  
                NULL);  // "free" tangency at this extremity
    ...
    double * ratio1= new double(0.25);
    CATDynFilletRadius * pRadius1 = new CATDynFilletRadius(0.2,  // radius value
                listCells[2],  
                ratio1,  
                NULL);  // "free" tangency for this location

The second and third arguments of the constructor must be specified when the fillet to be created is of variable radius.
    2. Define the CATDynEdgeFilletRibbon object whereby you specify the list of radii to be applied along the edge to be filleted. The list of edges to be filleted is to be set to NULL. 
           
           CATLISTP(CATDynFilletRadius) listRadius;		
           listRadius.Append(pRadius0);
           listRadius.Append(pRadius1);
           listRadius.Append(pRadius2);
           listRadius.Append(pRadius3);
                    
           // Create the CATDynEdgeFilletRibbon
           //
           CATDynEdgeFilletRibbon * pRibbon = new CATDynEdgeFilletRibbon(NULL, listRadius);

    3. If need be, set the parameters of the CATDynFilletRibbon.
           
           pRibbon ->SetSegmentationMode(CATDynTrim);

    4. Create the CATICGMDynFillet operator by using the CATCGMCreateDynFillet operator.
           
           CATICGMDynFillet * pFilletOp1 = CATCGMCreateDynFillet(iFactory,iTopData,iBody);

    5. Append the CATDynEdgeFilletRibbon to the operator instance.
           
           pFilletOp1 ->Append(pRibbon);

Writing the Model and Closing the Container To save the model in a file, the `::CATSaveCGMContainer` global function is used. Notice that in the use case, the save is conditioned by an input parameter representing the file inside which the model must be saved. The use case ends with the closure of the geometry factory, done by the ` ::CATCloseCGMContainer` global function.
    
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

In Short To create fillets, you must specify a list of radii as well as a list of edges to be filleted. For a constant radius, the list of radii contains a single item that you can apply to one or more edges. When creating a variable fillet, you must specify the list of radii. The edge to be filleted is then specified in the radius definition. References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.htm)  
---|---  
[2] | [Overview of the Topological Operators](CAACgmUcTopOverview.htm)  
History Version: **1** [Mar 2002] | Document created  
---|---
