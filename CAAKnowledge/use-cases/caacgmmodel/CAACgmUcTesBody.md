---
title: "Using a Tessellation Operator"
category: "use case"
module: "CAACgmModel"
tags: ["CAAGMOperatorsInterfaces", "CATICGMCellTessellator", "CAATesBody", "CAAGMOperatorsTesBody", "CATICGMBodyTessellator", "CATICGMObject", "CAAGMModelGemBrowser", "CATICGMTopSkin", "CATIA"]
source_file: "Doc/online/CAACgmModel/CAACgmUcTesBody.md"
converted: "2026-05-11T17:33:48.537640"
---

Using a Tessellation Operator  
---  
Use Case  
Abstract This article discusses the CAAGMOperatorsTesBody use case. This tutorial explains how to use the a Tessellation operator.
    * What You Will Learn With This Use Case
    * Tessellation Parameters
    * How to Use a Tessellation Operator
    * The CAAGMOperatorsTesBody Use Case
      * What Does CAAGMOperatorsTesBody Do
      * How to Launch CAAGMOperatorsTesBody
      * Where to Find the CAAGMOperatorsTesBody Code
    * Step-by-Step
    * In Short
    * References  
---  
What You Will Learn With This Use Case This use case is intended to help you use the tessellation classes. The article first recalls the parameters that are used to tune the tessellation process, then explains how to use a tessellation operator to tessellate an object. Tessellation Parameters The tessellation computes a geometric discretization from geometric curves [3], surfaces [4], or topological bodies, edges, or faces [1,2]. The results of their tessellation can then be used by applications which need to work with discretized data, such as visualization, mesh, or numerical control applications. Fig. 1: The Tessellation of a Quarter of Hemisphere ![Quarter of Hemisphere Tessellation](images/CAACgmTesTessellation0.gif) | The surfaces, faces, and the skin of the topological bodies are paved with triangles. The curves and topological edges are discretized with linear segments called bars. The extremities of the bars are called points. Fig 1. shows an example of triangles generation on a quarter of hemisphere.  
---|---  
Three parameters tune the tessellation result.

_Sag_
    Defines the maximum distance between a bar and the object to tessellate
_Step_
    Defines the maximum length of a bar.
_Angle_
    Defines the maximum angle between the normals at each bar end.
By default, _Step_ is infinite (in this case, it is not taken into account), and _Angle_ is set to _Pi/2_. Fig. 2: The Parameters of a Tessellation Operator ![Tessellation Operator Parameters](images/CAACgmTesTessellation1.gif) |  The _Sag_ parameter takes the curvature of the objects into account. A lower sag creates bars that are "nearer" the object to tessellate. The _Step_ acts on the length of the generated bars. A higher step generates longer bars. Now, imagine a semicircle whose radius is less than the _Sag_ value and than the _Step/Pi_. If the tessellation only takes into account these two prameters, it would ignore this object. The _Angle_ parameter allows you to catch the semicircle: the tessellation operator will create a new point as soon as the angle between the tangent at the extremities of the bars is more than _Angle_. In the figure _Angle_ is set to _Pi/2_.  
---|---  
**Note** : The parameter values are indicative values that can be sometimes locally overhang. Moreover, for a triangle discretization, the criteria are checked for the bars, not for all the points of the triangle interior. How to Use a Tessellation Operator The tessellation of an object is made by the use of specific operators. There is an operator per type of object to tessellate:
    * `CATICGMBodyTessellator` to tessellate a topological body.
    * `CATICGMCellTessellator` to tessellate one or several topological edges or faces.
They are built on the same scheme, which is the general scheme of a CGM operator. To use it:
    * Create the operator instance.
    * Optionally, add new curves, surfaces, cells to tessellate.
    * Run the operator.
    * Retrieve the results.
    * Delete the operator instance.
The results for curves and topological edges are given by the means of an array of computed points. The results for surfaces, topological faces and bodies are given as isolated triangles, strips of triangles, fans of triangles, the last two being provided for minimizing the memory size. Exceptionally, polygons are returned. In other words, the tessellation process outputs as few triangles as possible. In peculiar, if you tessellate a cube, no isolated triangles are output. Fig. 3: The Various Result Formats ![Various Result Formats](images/CAACgmTesTessellation2.gif) |  An isolated triangle is defined by its three points (V1,V2,V3). A fan of triangles is a list of triangles, such that the first point of the list with any two consecutive points define a triangle. A strip of triangles is a list of points, such that any three consecutive points define a triangle.  
---|---  
The algorithm tries, as far as possible, to return the triangles as strips or fans. But it happens that it returns them as isolated triangles, although it could find strips or fans. In some rare cases, polygons can be returned if the algorithm failed to tessellate them. Fig. 4: The Polygon Case ![Polygon Case](images/CAACgmTesTessellationEx.gif) | In case of some perturbed surface, the tessellation can lead to a rare configuration as in Fig 4. The polygon (V40, V41, V42, V43) represents a 3D twisted area, and fails to be expressed in terms of triangles.  
---|---  
As many tessellation objects can be generated, the results of a tessellation operator are retrieved by the mean of iterators, one iterator per object type: generated object | `Iterator name`  
---|---  
points | `CATCGMTessPointIter`  
triangles | `CATCGMTessTrianIter`  
strips | `CATCGMTessStripeIter`  
fans | `CATCGMTessFanIter`  
polygons | `CATCGMTessPolyIter`  
These iterators are all built on the same scheme. To use them:
    * Ask for the number of objects that the operator has computed.
    * Initialize the iterator.
    * Increment the iterator.
    * Retrieve one object.
The CAAGMOperatorsTesBody Use Case CAAGMOperatorsTesBody is a use case of the CAAGMOperatorsInterfaces.edu framework that illustrates the tessellation capabilities. What Does CAAGMOperatorsTesBody Do This use case creates a body representing a quarter of hemisphere. Then it defines a tessellation operator, runs it, and uses the results to create lines representing the generated bars. Finally, it clears the environment. How to Launch CAAGMOperatorsTesBody To launch CAAGMOperatorsTesBody, you will need to set up the build time environment, then compile CAAGMOperatorsTesBody.m along with its prerequisites, set up the run time environment, and then execute the use case [5]. If you simply type CAAGMOperatorsTesBody with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example: `CAAGMOperatorsTesBody e/Tessellation.NCGM` This NCGM file can be displayed using the CAAGMModelGemBrowser use case [6]. Where to Find the CAAGMOperatorsTesBody Code The CAAGMOperatorsTesBody use case is made of a main named CAATesBody.cpp located in the CAAGMOperatorsTesBody.m module of the CAAGMOperatorsInterfaces.edu framework: `InstallRootDirectory\CAAGMOperatorsInterfaces.edu\CAAGMOperatorsTesBody.m\` where `InstallRootFolder` [5] is the folder where the API CD-ROM is installed. Step-by-Step There are five logical sections in CAAGMOperatorsTesBody:
    1. Creating the Geometry Factory
    2. Creating the Topological Body representing a topological sphere
    3. Tessellating the Body
    4. Using the Iterators to Retrieve the Results
    5. Writing the Model And Closings the Container
Creating the Geometry Factory The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject. This creation is done by the global function `::CATCreateCGMContainer`. Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.
    
    CATGeoFactory* piGeomFactory = **::CATCreateCGMContainer**() ;
    if (NULL==piGeomFactory) return (1);

Creating the Topological Body The body is created on the boundary of a geometric sphere (limited to a quarter of hemisphere).
    
    // Creates the geometric sphere ...
     CATSphere * piSphere=piGeomFactory->**CreateSphere**
         (CATMathAxis(CATMathPoint(20,0,0)),10,0,CATPIBY2,0,CATPIBY2);
     if (NULL==piSphere)
     {
       ::CATCloseCGMContainer(piGeomFactory);
       return (1);
     }
    	
     //
     // ... and the body
     //
     CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration(); // defines an open configuration
     // creates the data of the operator : configuration + journal
     CATTopData topdata(pConfig,NULL);                                        
     CATSurLimits limits;
     piSphere->GetLimits(limits);                                         // retrieves the sphere limits
     // now creates the operator
     CATICGMTopSkin *pSkinOper = **::CATCGMCreateTopSkin** (piGeomFactory,&topdata,piSphere,&limits); 
     
     if (NULL==pSkinOper)
     {
       ::CATCloseCGMContainer(piGeomFactory);
       return (1);
     }
     pSkinOper->**Run**();
     CATBody * piBody=pSkinOper->**GetResult**();
     if (NULL==piBody)
     {
       ::CATCloseCGMContainer(piGeomFactory);
       return (1);
     }
    pSkinOper->**Release**();
    pSkinOper = NULL;
    // Releases the configuration
    pConfig->**Release**();

The geometry is created by the `CreateSphere` method of `CATGeoFactory`. The body is created by the topological operator `CATICGMTopSkin`. To use the operator:
    * Defines the configuration, that is to say the level of software you want to use to run the operator. By default, define an open configuration as in this use case to run with the current level. Moreover here, the pointer to the journal is set to `NULL` in the operator data. So that the journal is not filled.
    * Create it.
    * Run it.
    * Get the resulting body.
    * Delete it. Then, the configuration is released after use.
Tessellating the Body In this use case `piBody` is the pointer to the body to tessellate.
    
    //
     // create the operator
     double sag   = 0.2;
     CATICGMBodyTessellator * pTessellator =:: **CATCGMCreateBodyTessellator**(piBody,sag);
     if (NULL!=pTessellator)
     {
     pTessellator -> **Run**();
    	
     //
     // Get the results
     //
     CATBoolean isPlanar=FALSE;
     CATCGMTessPointIter *    pVertices  = NULL;
     CATCGMTessStripeIter *   pStrips    = NULL;
     CATCGMTessFanIter *      pFans      = NULL;
     CATCGMessPolyIter *     pPolygons  = NULL;
     CATCGMTessTrianIter *    pTriangles = NULL;
    	
     // Retrieve all the body faces. 
     //
     CATLISTP(CATCell) faces;
     piBody->GetAllCells( faces,2); // faces are cells of dimension 2
     int numberOfFaces = faces.Size();
    
     // Scan  the result for one face
     for (int i=1 ; i<=numberOfFaces ; i++)
     { 
       // 
       // for each face, retrieve the tessellation results.
       //
       CATFace * piFace = (CATFace*) faces[i];	
       pTessellator -> **GetFace**(piFace,
                               isPlanar,
                               &pVertices,
                               &pStrips,
                               &pFans,
                               &pPolygons,
                               &pTriangles);
        // use the results (see Using the Iterators to Retrieve the Results)
        //  ...... //
     }
     //
     // delete the operator
     **pTessellator- >Release();
     pTessellator = NULL**;
    }

The operator `pTesselator` is created with the body to tessellate and the requested sag value. Then, call the `Run` method on the operator . The results are retrieved by dedicated iterators, allocated by the `GetFace` method. These iterators are deleted at the operator deletion. Using the Iterators to Retrieve the Results Now, the following section explains how to use these iterators. Results can be retrieved in one shot: in this case, the arrays, such as `aCoord` and `aNuPts` must be allocated and deallocated by the caller. The use case shows how to use the retrieved tessellation results in order to create geometric lines, but only the strips case is detailed here.
    * First, all the coordinates of the points are retrieved in the `aCoord` array, that was already allocated.
    * Then, the strips are read, using the `CATTessStripeIter` iterator: 
      * Retrieve the number of points of each strip: their sum is the size of the array `aNuPts` to allocate.
      * This array is filled in by the indexes of the points defining the strips: you access directly the point coordinates using these indexes.
    * At least, the arrays are deallocated.
    
    float  (* aCoord)[3]= NULL;
    int * aNuPts        = NULL;
    CATLine * piLn      = NULL;
    //
    // Points (in one shot)
    //
    if(NULL != pVertices)
    {
       long nbp=pVertices->**GetNbPoint**();
       **aCoord** = new float[nbp][3];
       pVertices->**GetPointXyzAll**(aCoord); // all the coordinates in one shot
    } 
    //
    // strips (one by one) 
    //
    if(NULL != pStrips)
    {
      // size of the maximum allocation: use the iterator
      long nbs=0;
      while (0==(pStrips->**IsExhausted**()))       // last strip?
      {
        nbs=CATMax(nbs,pStrips->**GetStriNbPts**()); // the result of the current strip
        pStrips->**GoToNext**();                     // next strip
      }
    
      //
      // allocation
      //
      **aNuPts** =new int[nbs];
      //
      // from the beginning again to retrieve the results
      //
      pStrips->Reset();                          //initialize the strip iterator
      while (0==(pStrips->IsExhausted()))        // last one?
      { 
        nbs=pStrips->GetStriNbPts();
        pStrips->**GetStriNuPts**(aNuPts);
        // create some interior lines of the strip from the results
        for (int j=0;j<nbs-1;j++)
        {
        piLn= piGeomFactory->CreateLine(
          CATMathPoint(aCoord[aNuPts[j]][0],
                       aCoord[aNuPts[j]][1],
                       aCoord[aNuPts[j]][2]),
          CATMathPoint(aCoord[aNuPts[j+1]][0],
                       aCoord[aNuPts[j+1]][1],
                       aCoord[aNuPts[j+1]][2]) );
      }
      // ..... //
      pStrips->GoToNext();                      // next one
    }
    **delete [] aNuPts;
    aNuPts = NULL;**
    } 
    **if (NULL!=aCoord) delete [] aCoord;
    aCoord = NULL;** 

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

In Short
    * The tessellation operators compute a discretized geometry from geometric (curve, surface) or topological (body, face, vertex) objects according to a sag, a step and an angle parameter.
    * They follow the general scheme of a CGM operator. Results are presented by means of iterators.
References [1] | [Topology Concepts](CAACgmTaTobTopoConcepts.md)  
---|---  
[2] | [The CGM Topological Model](CAACgmTaTobTopoModel.md)  
[3] | [The Curves of CATIA Geometric Modeler](CAACgmTaGobCurves.md)  
[4] | [The Surfaces of CATIA Geometric Modeler](CAACgmTaGobSurfaces.md)  
[5] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
[6] | [Browsing the Geometric Container](CAACgmUcGemBrowser.md)  
History Version: **1** [dec 2006] | Document created  
---|---
