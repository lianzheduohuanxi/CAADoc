---
title: "Using the Basic Topological Operators"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CATICGMContainer", "CAADoc", "CATICGMTopPointOperator", "CAATopSpline", "CATICGMObject", "CATICGMTopSplineOperator", "CAAGMModelGemBrowser", "CAATGMOperatorsInterfaces", "CATICGMTopLineOperator", "CAAGMOperatorsSpline", "CATICGMSplineBody", "CATICGMLengthFromBodyOnWire"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopSpline.htm"
converted: "2026-05-11T17:33:49.328293"
---

Using Basic Topological Operators (Point, Line, Spline)  
---  
Use Case  
Abstract Basic topological operators are transient objects for the creation of basic topological bodies such as point, line or spline bodies. These operators are based on the same scheme, which is described. The use of each provided basic topological operator is presented in the `CAATopSpline.cpp` sample:
    * What You Will Learn With This Use Case
    * Basic Topological Operators
    * How to Use a Basic Topological Operator
    * The CAAGMOperatorsSpline Use Case
      * What Does CAAGMOperatorsSpline Do
      * How to Launch CAAGMOperatorsSpline
      * Where to Find the CAAGMOperatorsSpline Code
    * Step-by-Step
    * In Short
    * References  
---  
What You Will Learn With This Use Case This use case is intended to help you use the basic topological operators classes and presents an example of use for each provided basic topological operator: creation of a point body, a spline body, a line body, and length computation. Basic Topological Operators Using basic topological operators is an easy way to create point, line, or spline bodies, that is to say: bodies only containing one vertex, or one wire whose geometry is a line or a spline. These operators are called with parameters such as coordinates (to define a point), vectors (to define tangents), or other basic bodies. They work inside one geometric container: the input and output objects must belong to the same geometric container. Basic topological operators create:
    * Point body: `CATICGMTopPointOperator`.
    * Line body: `CATICGMTopLineOperator`.
    * Spline body: `CATICGMTopSplineOperator`.
An additional operator, the `CATICGMLengthFromBodyOnWire` operator, analyzes the length between two point bodies. How to Use a Basic Topological Operator There are two ways to create basic bodies.
    1. One way is to use the corresponding basic topological operator, based on the general scheme of the GM operators, that: 
       * Creates the operator with a global function: `::CATCGMCreateTopxxxOperator` (where `xxx` stands for the type of the created geometry of the body). The created operator is transient (that is to say, it is not streamed when streaming the geometric factory).
       * Possibly sets parameters.
       * Runs the operation.
       * Retrieves the resulting body.
       * Deletes the operator.
    2. The other way is to call the global function `::CATCGMCreateTopxxx`: it directly returns the created body. But in this case, you cannot tune parameters. You can only retrieve the created body: the tangents to the spline are not available for example.
The length analysis can be only used with the first way, except that there is no creation global function. In this case, the constructor is directly used. The CAAGMOperatorsSpline Use Case CAAGMOperatorsSpline is a use case of the CAAGMOperatorsInterfaces.edu framework that illustrates GMOperatorsInterfaces framework capabilities. What Does CAAGMOperatorsSpline Do Fig. 1: The created objects of the CAAGMOperatorsSpline use case ![CAAGMOperatorsSpline Use Case Created Objects](images/CAACgmTopSpline1.gif) | This use case details the two ways of creation of basic bodies. 
    * `SplineBody` is directly created with a global function.
    * `SplineBody2` is created by an operator. Tangency constraints are imposed on the extremities. The operator also returns the tangents to all the passing points, that are used to create lines.
Moreover, the use case shows an example of the curve length computation.  
---|---  
How to Launch CAAGMOperatorsSpline To launch CAAGMOperatorsSpline, you will need to set up the build time environment, then compile CAAGMOperatorsSpline.m along with its prerequisites, set up the run time environment, and then execute the use case [1]. If you simply type CAAGMOperatorsSpline with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example: `CAAGMOperatorsSpline e/SplineCreation.NCGM` This NCGM file can be displayed using the CAAGMModelGemBrowser use case. Where to Find the CAATopSpline Code The CAAGMOperatorsSpline use case is made of a main named CAATopSpline.cpp located in the CAAGMOperatorsSpline.m module of the CAAGMOperatorsInterfaces.edu framework: `InstallRootFolder\CAADoc\CAATGMOperatorsInterfaces.edu\CAAGMOperatorsSpline.m\` where `InstallRootFolder` [1] is the folder where the API CD-ROM is installed. Step-by-Step There are six steps in CAATopSpline.cpp:
    1. Creating the Geometry Factory
    2. Directly Creating Point Bodies and a Spline Body (first way)
    3. Using a Basic Topological Operator to Create Another Spline Body (second way.) This includes: 
       * Creating the operator.
       * Running it.
       * Getting the results, then using them to create the line bodies representing the tangents to the passing points.
       * Deleting the operator.
    4. Computing the Length
    5. Removing the Unused Bodies
    6. Writing the Model And Closing the Container
Creating the Geometry Factory The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject. This creation is done by the global function `::CATCreateCGMContainer`. Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.
    
    CATGeoFactory* piGeomFactory = **::CATCreateCGMContainer**() ;
    if (NULL==piGeomFactory) return (1);

Directly Creating Point Bodies and a Spline Body To operate in this way, you only have to call the global function `::CATCGMCreateTopPoint` or `::CATCGMCreateTopSpline`. In case of the spline body creation, the created body is retrieved, but you cannot have access to the tangent or curvature at the passing points. To have them, you must use the operator, as in the next section. The non detailed steps created or loaded the geometric factory (`piGeomFactory`).
    
    //
    // 2-Direct creation of point bodies 
    //
    const int nbpts = 4;
    CATBody ** aPoints = new CATBody * [nbpts];
    
    // defines an open configuration for the operator
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    // defines the data of the operator: configuration + journal
    CATTopData topdata(pConfig,NULL);
    
    aPoints[0] = **::CATCGMCreateTopPointXYZ**(piGeomFactory,&topdata,10., 15., 0.);
    aPoints[1] = ::CATCGMCreateTopPointXYZ(piGeomFactory,&topdata,20., 20., 0.5);
    aPoints[2] = ::CATCGMCreateTopPointXYZ(piGeomFactory,&topdata,30., 18., 0.);
    aPoints[3] = ::CATCGMCreateTopPointXYZ(piGeomFactory,&topdata,40., 15., 0.5);
    
    //
    // 3-Direct creation of a spline body without any tangent 
    // or curvature imposition.
    //
    CATBody * piSplineBody = **::CATCGMCreateTopSpline**(piGeomFactory,
                                                     &topdata,
                                                     nbpts,
                                                     aPoints);
    

The operator configuration is the level of software you want to use to run this operator. By default, define an open configuration as in this use case to run with the current level. Moreover here, the pointer to the journal is set to `NULL` in the operator data. So that the journal is not filled. Using a Basic Topological Operator to Create Another Spline Body To operate in this mode, the sample proceeds with the following steps that:
    1. Create the operator with the appropriate global function (`CATCGMCreateTopSplineOperator`). Here, tangents to the start and end points are imposed.
    2. Execute the operation: `Run` method.
    3. Get the results: 
       * The created body.
       * The computed tangents at all the passing points. These vectors are used to create line bodies (`CATCGMCreateTopLineFromDirection`).
    4. Remove the operator instance from the memory. Notice that you also must release the software configuration, because it is no more used.
    
    //
    // 4-Use now a CATICGMSplineBody Operator.
    //
    CATMathVector aTangent[nbpts];
    long          aImposition[nbpts];
    
    // imposition of the direction of the tangent at the start point.
    aImposition[0]=1;
    aTangent[0].SetCoord(1.,0.,0.);
    
    // no imposition for the intermediate points:
    // the corresponding aTangent values need not to be given
    aImposition[1]=0;
    aImposition[2]=0;
    
    // imposition of the tangent at the ending point.
    aImposition[3]=2;
    aTangent[3].SetCoord(5.,5.,0.);
    
    // a- creation
    CATICGMTopSplineOperator *pSplineOp = 
    **::CATCGMCreateTopSplineOperator**(piGeomFactory,
                                            &topdata,
                                            nbpts,
                                            aPoints,
                                            aTangent,
                                            NULL,   // no curvature imposition
                                            aImposition);
    
    if (NULL==pSplineOp)                    // in case of problem
    {
      CATCloseCGMContainer(piGeomFactory);  // close the factory and return
      return(2);                             
    }
    // b- run the operator
    pSplineOp->**Run**();
    
    // c- get the result
    CATBody * piSplineBody2 = pSplineOp->**GetResult**();
    
    // also get the computed tangents .
    const CATMathVector *  pComputedTangents=NULL; 
    pSplineOp->**GetComputedTangents**(pComputedTangents);
    
    // Create topological lines representing the tangents
    CATBody * aTgtBody[nbpts];
    for (int i=0;i <nbpts; i++)
    {
      double length = pComputedTangents[i].Norm();
      aTgtBody[i] = **::CATCGMCreateTopLineFromDirection**(piGeomFactory,
                                                    &topdata,
                                                    aPoints[i],
                                                    pComputedTangents[i],
                                                    length);
    }
    
    // d- delete the operator
    **pSplineOp- >Release();
    pSplineOp=NULL;
    **// Releases the configuration**pConfig- >Release();**

Computing the Length The `CATICGMLengthFromBodyOnWire` operator is constructed by using the CATCGMCreateLengthFromBodyOnWire global function. Then, it is run and the length is retrieved. Finally, it is released. The `l1` and `l2` computed lengths are different, even though they are computed between the same points, because the lengths are computed on the splines, that are different.
    
    //
    // 5- length computation
    //
    // between two points on the first spline
    // between two points on the first spline
    CATICGMLengthFromBodyOnWire* pLengthOp= 
    CATCGMCreateLengthFromBodyOnWire(piGeomFactory,
    &topdata,
    aPoints[1], 
    aPoints[2],
    piSplineBody );
    double l1=0.;
    if (NULL != pLengthOp)
    {
    l1=pLengthOp->GetDistance();
    
    pLengthOp->Release();
    pLengthOp = NULL;
    }
    
    // between the same points on the second spline
    pLengthOp =CATCGMCreateLengthFromBodyOnWire(piGeomFactory,
    &topdata,
    aPoints[1], 
    aPoints[2],
    piSplineBody2 ); 
    
    // P2 will contain the 3D mathematical coordinates of the second point
    CATMathPoint P2;
    double l2=0.;
    if (NULL != pLengthOp)
    {
    l2=pLengthOp->GetDistance(NULL, // the coordinates of the first point are not asked
    &P2); // the coordinates of the second point
    pLengthOp->Release();
    pLengthOp = NULL;
    }
    cout << "length 1 = " << l1 <<" , length2  "<< l2 << endl;

Removing the Unused Bodies The point bodies have only been constructed to be used in the definition of the spline. Depending on your application, you may not need them afterwards. If you want to remove them from the geometric factory, use the `CATICGMContainer::Remove` method. If not, they will be automatically saved when streaming the factory. **Note** : Although geometric objects are handled by the mean of interfaces, such as `CATCartesianPoint`, `CATLine`, or `CATBody`, the pointers on these objects must not be released. In fact, they are released at the closure of the factory (the `CATCloseCGMContainer` global function).
    
    //
    // 6- Delete the unused point bodies and the array
    //
    
    for (i=0;i <nbpts; i++)
    {
      piGeomFactory->**Remove**(aPoints[i],CATICGMContainer::RemoveDependancies);
    }
    
    delete [] aPoints;
    aPoints = NULL;

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

In Short
    * The basic topological operators are transient objects used to create basic topological objects. They work inside one container.
    * They are base on the general scheme of the GM operators: creation, optionally set of advanced options, run, read of the results, deletion
    * Basic bodies can also be directly created by a global function.
References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
History Version: **1** [Feb 2000] | Document created  
---|---
