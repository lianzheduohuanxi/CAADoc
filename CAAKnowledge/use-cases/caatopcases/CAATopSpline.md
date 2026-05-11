---
title: "Basic Topological Operators"
category: "use case"
module: "CAATopUseCases"
tags: ["CAAATopSpline", "CAAGemBrowser", "CATICGMObject", "CAATopSpline", "CAABopSpine", "CAATopologicalOperators", "CATICGMContainer"]
source_file: "Doc/online/CAATopUseCases/CAATopSpline.md"
converted: "2026-05-11T17:31:50.766842"
---
# Geometric Modeler

| 
## Topology

| 
### Basic Topological Operators

_How to create vertex bodies or simple wire bodies_  
---|---|---  
Use Case  
  
* * *
### Abstract

Basic topological operators are transient objects for the creation of basic topological bodies such as point, line or spline bodies. These operators are based on the same scheme, which is described. The use of each provided basic topological operator is presented in the `CAABopSpine.cpp` sample. 

  * **What You Will Learn With This Use Case**
  * **The Basic Topological Operators**
  * **How to Use a Basic Topological Operator**
  * **The CAAATopSpline Use Case**
    * What Does CAATopSpline Do
    * How to Launch CAATopSpline
    * Where to Find the CAATopSpline Code
  * **Step-by-Step**
  * **In Short**
  * **References**

  
---  
  
* * *
### What You Will Learn With This Use Case

This use case is intended to help you use the basic topological operators classes and presents an example of use for each provided basic topological operator: creation of a point body, a spline body, a line body, and length computation.

[Top]
### The Basic Topological Operators

Using basic topological operators is an easy way to create point, line, or spline bodies, that is to say: bodies only containing one vertex, or one wire whose geometry is a line or a spline.

These operators are called with parameters such as coordinates (to define a point), vectors (to define tangents), or other basic bodies. They work inside one geometric container: the input and output objects must belong to the same geometric container.

The basic topological operators create: 

  * Point body: `CATTopPointOperator`
  * Line body: `CATTopLineOperator`
  * Spline body: `CATTopSplineOperator.`

An additional operator, the `CATLengthFromBodyOnWire` operator, analyzes the length between two point bodies.

[Top]
### How to Use a Basic Topological Operator

There are two ways to create basic bodies. 

  * One way is to use the corresponding basic topological operator, based on the general scheme of the CGM operators, that: 
    * Creates the operator with a global function: `::CATCreateTopxxxOperator` (where `xxx` stands for the type of the created geometry of the body). The created operator is transient (that is to say, it is not streamed when streaming the geometric factory).
    * Possibly sets parameters
    * Runs the operation
    * Retrieves the resulting body
    * Deletes the operator.
  * The other way is to call the global function `::CATCreateTopxxx`: it directly returns the created body. But in this case, you cannot tune parameters. You can only retrieve the created body: the tangents to the spline are not available for example .

The length analysis can be only used with the first way, except that there is no creation global function. In this case, the constructor is directly used.

[Top]
### The CAATopSpline Use Case

CAATopSpline is a use case of the CAATopologicalOperators.edu framework that illustrates TopologicalOperators framework capabilities.

[Top]
#### What Does CAATopSpline Do

Fig. 1: The created objects of the CAATopSpline use case ![Spline1.gif \(29988 bytes\)](images/Spline1.gif) | This use case details the two ways of creation of basic bodies. 

  * `SplineBody` is directly created with a global function
  * `SplineBody2` is created by an operator. Tangency constraints are imposed on the extremities. The operator also returns the tangents to all the passing points, that are used to create lines.

Moreover, the use case shows an example of the curve length computation.  
---|---  
  
[Top]
#### How to Launch CAATopSpline

To launch CAATopSpline, you will need to set up the build time environment, then compile CAATopSpline.m along with its prerequisites, set up the run time environment, and then execute the use case [1].

If you simply type CAATopSpline with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example:

With Windows `CAATopSpline e/SplineCreation.NCGM`

With UNIX `CAATopSpline /u/SplineCreation.NCGM`

This NCGM file can be displayed using the CAAGemBrowser use case.

[Top]
#### Where to Find the CAATopSpline Code

The CAATopSpline use case is made of a main named CAATopSpline.cpp located in the CAATopSpline.m module of the CAATopologicalOperators.edu framework:

Windows | `InstallRootDirectory\CAATopologicalOperators.edu\CAATopSpline.m\`  
---|---  
Unix | `InstallRootDirectory/CAATopologicalOperators.edu/CAATopSpline.m/`  
  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

There are six steps in CAATopSpline.cpp: 

  1. Creating the Geometry Factory
  2. Directly Creating Point Bodies and a Spline Body (first way)
  3. Using a Basic Topological Operator to Create Another Spline Body (second way.) This includes: 
     * Creating the operator
     * Running it
     * Getting the results, then using them to create the line bodies representing the tangents to the passing points
     * Deleting the operator.
  4. Computing the Length
  5. Removing the Unused Bodies
  6. Writing the Model And Closing the Container

[Top]
#### Creating the Geometry Factory

The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject. This creation is done by the global function `::CATCreateCGMContainer`. Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.
    
    
    CATGeoFactory* piGeomFactory = **::CATCreateCGMContainer**() ;
    if (NULL==piGeomFactory) return (1);  
  
---  
  
[Top]
#### Directly Creating Point Bodies and a Spline Body

To operate in this way, you only have to call the global function `::CATCreateTopPoint` or `::CATCreateTopSpline`.

In case of the spline body creation, the created body is retrieved, but you cannot have access to the tangent or curvature at the passing points. To have them, you must use the operator, as in the next section.

The non detailed steps created or loaded the geometric factory (`piGeomFactory`).
    
    
    _//
    // 2-Direct creation of point bodies 
    //_
    const int nbpts = 4;
    CATBody ** aPoints = new CATBody * [nbpts];
    
    _// defines an open configuration for the operator_
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    _// defines the data of the operator: configuration + journal_
    CATTopData topdata(pConfig,NULL);
    
    aPoints[0] = **::CATCreateTopPointXYZ**(piGeomFactory,&topdata,10., 15., 0.);
    aPoints[1] = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,20., 20., 0.5);
    aPoints[2] = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,30., 18., 0.);
    aPoints[3] = ::CATCreateTopPointXYZ(piGeomFactory,&topdata,40., 15., 0.5);
    
    _//
    // 3-Direct creation of a spline body without any tangent 
    // or curvature imposition.
    /_ /
    CATBody * piSplineBody = **::CATCreateTopSpline**(piGeomFactory,
                                                  &topdata,
                                                  nbpts,
                                                  aPoints);
      
  
---  
  
The operator configuration is the level of software you want to use to run this operator. By default, define an open configuration as in this use case to run with the current level. Moreover here, the pointer to the journal is set to `NULL` in the operator data. So that the journal is not filled.

[Top]
#### Using a Basic Topological Operator to Create Another Spline Body

To operate in this mode, the sample proceeds with the following steps that: 

  1. Create the operator with the appropriate global function (`CATCreateTopSplineOperator`). Here, tangents to the start and end points are imposed
  2. Execute the operation: `Run` method
  3. Get the results: 
     * The created body
     * The computed tangents at all the passing points. These vectors are used to create line bodies (`CATCreateTopLineFromDirection`)
  4. Remove the operator instance from the memory. Notice that you also must release the software configuration, because it is no more used.

    
    
    _//
    // 4-Use now aCATTopSplineBody Operator.
    //_
    CATMathVector aTangent[nbpts];
    long          aImposition[nbpts];
    
    _// imposition of the direction of the tangent at the start point._
    aImposition[0]=1;
    aTangent[0].SetCoord(1.,0.,0.);
    
    _// no imposition for the intermediate points:
    // the corresponding aTangent values need not to be given_
    aImposition[1]=0;
    aImposition[2]=0;
    
    _// imposition of the tangent at the ending point._
    aImposition[3]=2;
    aTangent[3].SetCoord(5.,5.,0.);
    
    _// a- creation_
    CATTopSplineOperator *pSplineOp = 
    **::CATCreateTopSplineOperator**(piGeomFactory,
                                         &topdata,
                                         nbpts,
                                         aPoints,
                                         aTangent,
                                         NULL,   _// no curvature imposition_ 
                                         aImposition);
    
    if (NULL==pSplineOp)  _// in case of problem_
    {
      CATCloseCGMContainer(piGeomFactory);  _// close the factory_ _and return_
      return(2);                             
    }_// b- run the operator_
    pSplineOp->**Run**();
    
    _// c- get the result_
    CATBody * piSplineBody2 = pSplineOp->**GetResult**();
    
    _// also get the computed tangents ._
    const CATMathVector *  pComputedTangents=NULL; 
    pSplineOp->**GetComputedTangents**(pComputedTangents);
    
    _//Create topological lines representing the tangents_
    CATBody * aTgtBody[nbpts];
    for (int i=0;i <nbpts; i++)
    {
      double length = pComputedTangents[i].Norm();
      aTgtBody[i] = **::CATCreateTopLineFromDirection**(piGeomFactory,
                                                    &topdata,
                                                    aPoints[i],
                                                    pComputedTangents[i],
                                                    length);
    }
    
    _// d- delete the operator_
    **delete pSplineOp;
    pSplineOp=NULL;**_// Releases the configuration_**pConfig- >Release();**  
  
---  
  
 

[Top]
#### Computing the Length

The `CATLengthFromBodyOnWire` operator is directly constructed. Then, it is run and the length is retrieved. Finally, it is deleted.

The `l1` and `l2` computed lengths are different, even though they are computed between the same points, because the lengths are computed on the splines, that are different.
    
    
    _//
    // 5- length computation
    //
    // between two points on the first spline_
    CATLengthFromBodyOnWire* pLengthOp= 
    		new **CATLengthFromBodyOnWire**(piGeomFactory,
                                                aPoints[1],
                                                aPoints[2],
                                                piSplineBody );
    double l1=0.;
    if (NULL != pLengthOp)
    {
     l1=pLengthOp->**GetDistance**();
     **delete pLengthOp;
     pLengthOp = NULL;**
    }
    
    _// between the same points on the second spline_
    pLengthOp =new CATLengthFromBodyOnWire(piGeomFactory,
                                           aPoints[1], 
    				       aPoints[2],
    				       piSplineBody2 );	
    
    _// P2 will contain the 3D mathematical coordinates of the second point_ 
    CATMathPoint P2;
    double l2=0.;
    if (NULL != pLengthOp)
    {
     l2=pLengthOp->GetDistance(NULL, _// the coordinates of the first point are not asked_
    			   &P2); _// the coordinates of the second point_
     delete pLengthOp;
     pLengthOp = NULL;
    }
    cout << "length 1 = " << l1 <<" , length2  "<< l2 << endl;  
  
---  
  
[Top]
#### Removing the Unused Bodies

The point bodies have only been constructed to be used in the definition of the spline. Depending on your application, you may not need them afterwards. If you want to remove them from the geometric factory, use the `CATICGMContainer::Remove` method. If not, they will be automatically saved when streaming the factory.

**Note** : Although geometric objects are handled by the mean of interfaces, such as `CATCartesianPoint`, `CATLine`, or `CATBody`, the pointers on these objects must not be released. In fact, they are released at the closure of the factory (the `CATCloseCGMContainer` global function).
    
    
    _//
    // 6- Delete the unused point bodies and the array
    //_
    
    for (i=0;i <nbpts; i++)
    {
      piGeomFactory->**Remove**(aPoints[i],CATICGMContainer::RemoveDependancies);
    }
    
    delete [] aPoints;
    aPoints = NULL;  
  
---  
  
[Top]
#### Writing the Model and Closing the Factory

To save the model in a file, the `::CATSaveCGMContainer` global function is used. Notice that in the use case, the save is conditioned by an input parameter representing the file inside which the model must be saved.

The use case ends with the closure of the geometry factory, done by the `::CATCloseCGMContainer` global function.
    
    
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
    
     _//
     // Closes the container
     //_	
     **::CATCloseCGMContainer**(piGeomFactory);  
  
---  
  
[Top]

* * *
### In Short

  * The basic topological operators are transient objects used to create basic topological objects. They work inside one container
  * They are base on the general scheme of the CGM operators: creation, optionally set of advanced options, run, read of the results, deletion
  * Basic bodies can also be directly created by a global function.

[Top]

* * *
### References

[1] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[Top]  
  
* * *
### History

Version: **1** [Feb 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
