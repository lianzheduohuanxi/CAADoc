---
title: "Scanning an Edge Curve"
category: "use case"
module: "CAACgmModel"
tags: ["CAATopEdgeCurve", "CATICGMContainer", "CAADoc", "CAAGMModelScanEdgeCurve", "CATICGMObject", "CAAGMModelInterfaces", "CAACGMModelScanEdgeCurve", "CATIntCurve", "CAAScanEdgeCurve"]
source_file: "Doc/online/CAACgmModel/CAACgmUcTobEdgeCurve.md"
converted: "2026-05-11T17:33:48.549132"
---

Scanning an Edge Curve  
---  
Use Case  
Abstract Between the topology and the geometry, there are intermediate objects that are used by the geometric modeler to group objects with similar function. Such objects are created to join various pieces of geometry before covering them by topology. Given two faces with a common edge, the edge curve is the object which is built from the two Pcurves defining the common side. The CATEdge topological object is then created from this edge curve. In short, this is the way an edge (a topological object) is constructed from the geometry. In this use case, no edge and no topology is created, this is the opposite which is done. From the topology (an edge), the underlying geometry is retrieved and analyzed.
    * What You Will Learn With This Use Case
    * The CAAGMModelScanEdgeCurve Use Case
      * What Does CAAGMModelScanEdgeCurve Do?
      * How to Launch CAAGMModelScanEdgeCurve
      * Where to Find the CAAGMModelScanEdgeCurve Code
    * Step-by-Step
    * References  
---  
What You Will Learn With This Use Case This use case is intended to make you understand how an edge curve is constructed and how to use the _CATEdgeCurveIterator_ operator to scan an edge curve. About the Edge Curve ? An edge curve is an aggregation of several curves. The curves aggregated are the curves which define the boundaries of the adjacent faces. They can be of various type: CATPNurbs, CATLine or even CATEdgeCurve. Among the aggregated curves, there is one which is used as a reference to determine the orientation of the edge curve and if needed re-parameterize the other curve, this is the "ref curve". EDGE CURVE ORIENTATION / “REF CURVE” ORIENTATION = 1 The "ref curve" is:
    1. Either the first canonical curve (HasMathCurve returns non NULL).
    2. Or the first curve which is neither a CATPCurve nor a CATEdgeCurve.
    3. Or the first curve.
There are three kinds of edge curve:
    1. The CATIntCurve which results from the intersection of surfaces. CAA developers are not allowed to create directly such edge curves.
    2. The CATSimCurve which is created from curves which have a linear parameterization.
    3. The CATMergedCurve type which is created for curves which do not have a linear parameterization. By default, some operators create a CATMergedCurve even if the underlying curves have a linear parameterization. This is to adjust to any case of input geometry.
To manipulate an edge curve, you must:
    1. Retrieve the edge curve from the corresponding edge by using CATEdge::GetCurve.
    2. If need be, retrieve the “ref curve” from an edge curve by using CATEdgeCurve::GetRefCurve. 
    3. Retrieve the CATCurve making up the edge curve by using the CATEdgeCurveIterator operator.

The CAACGMModelScanEdgeCurve Use Case CAACGMModelScanEdgeCurve is a use case of the CAAGMModelInterfaces.edu framework that illustrates how to use the CATEdgeCurveIterator which is delivered in GeometricObjects.  What Does CAACGMModelScanEdgeCurve Do? The CAACGMModelScanEdgeCurve use case:
    * Loads the container and retrieves the edge to be scanned.
    * Retrieves the edge curve from to edge to be analyzed and scans this edge curve.
    * Writes the model and closes the factory. Note that, in this use case the output model is the same as the input model.
How to Launch CAACGMModelScanEdgeCurve  To launch CAACGMModelScanEdgeCurve, you will need to set up the build time environment, then compile CAACGMModelScanEdgeCurve .m along with its prerequisites, set up the run time environment, and then execute the use case [1]. CAACGMModelScanEdgeCurve `e:/edgeCurve1.NCGM" e:/output file.NCGM` where `edgeCurve1.NCGM` is an input file delivered in the CAAGMModelInterfaces.edu/FunctionTests/InputData file. Where to Find the CAACGMModelScanEdgeCurve Code The CAACGMModelScanEdgeCurve use case is made of a main named CAAScanEdgeCurve.cpp located in the CAACGMModelScanEdgeCurve .m module of the CAAGMModelInterfaces.edu framework: `InstallRootFolder\CAADoc\CAAGMModelInterfaces.edu\CAACGMModelScanEdgeCurve.m\` where `InstallRootFolder` [1] is the folder where the API CD-ROM is installed. Step-by-Step There are three main steps in CAATopEdgeCurve.cpp: 
    1. Loading the Container and Retrieving the Edge to Be Scanned
    2. Analyzing the Edge Contents
    3. Writing the Model and Closing the Factory
Loading the Container and Retrieving the Edge to Be Scanned The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject (and the curves and surfaces in particular). In this use case, the factory is defined by reading a NCGM file that was previously stored,  the global function `::CATLoadCGMContainer` must be used to retrieve the factory. The edge is retrieved by using the CATICGMContainer::FindObjectFromTag method. 1857 is the edge tag.
    
    CATGeoFactory* piGeomFactory = CATLoadCGMContainer(filetoread);
    ...
    CATICGMObject * piCGMObj1 = piGeomFactory->FindObjectFromTag( 1857 );

Here is the input model. The edge to be analyzed is highlighted. ![Edge Curve](images/CAACgmTobedgecurve.gif) Analyzing the Edge Contents There are three steps:
    1. Retrieve the edge curve.
    2. Retrieve the "ref curve" from the edge curve.
    3. Scan the edge curve.
    
    ...
    // (a) - retrieve the edge curve from the edge
    CATEdgeCurve * pEdgeCurve = piEdge->GetCurve(&OriECrvVsEdge);
    //
    // (b) - retrieve the "ref curve"
    //
    CATCurve * RefCurve = pEdgeCurve->GetRefCurve();
    ...
    //
    // (c) - scans the edge curve
    //       In this particular case, the scanned edge curve embeddes
    //       two edge curves. 
    //               !----------- Simcurve 393 
    //               !                    !--------- PLine 385
    //               !                    !--------- PLine 386
    //               !----------- Intcurve 1843
    //               !                    !--------- PLine 1841
    //               !                    !--------- PLine 1842
    //       SetLeafScan(1) returns the four PLines. 
    //                                               385
    //                                               386
    //                                              1841
    //                                              1842
    //       SetLeafScan(0) returns all the curves (the edge curve itself + sub edge curves + Pcurves).
    //                                              1858
    //                                               393
    //                                               385
    //                                               386
    //                                              1843
    //                                              1841
    //                                              1842
    ...
    CATEdgeCurveIterator Iterator(pEdgeCurve);   // create the iterator
    Iterator.SetLeafScan(0);                     
    Iterator.SetRepetitions(0);
    ...

The edge curve which is scanned is itself made up of two edge curves. If you need to retrieve only the underlying CATCurves and not the possible edge curves which are making up the initial edge curve, you can specify the 1 option in SetLeafScan, otherwise you get all the objects at all levels under the edge curve. Writing the Model and Closing the Factory To save the model in a file, the `::CATSaveCGMContainer` global function is used. Notice that in the use case, the save is conditioned by an input parameter representing the file inside which the model must be saved. The use case ends with the closure of the geometry factory, done by the ` ::CATCloseCGMContainer` global function.
    
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
    // Close the container
    //
    **::CATCloseCGMContainer**(piGeomFactory);

References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
History Version: **1** [Jan 2009] | Document created  
---|---
