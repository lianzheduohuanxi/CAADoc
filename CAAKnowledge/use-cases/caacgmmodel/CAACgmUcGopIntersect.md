---
title: "Intersecting a Curve with a Surface"
category: "use case"
module: "CAACgmModel"
tags: ["CAAGopIntersect", "CATICGMIntersectionCrvSur", "CAAGMModelGemBrowser", "CAAGMModelInterfaces", "CAAGMModelIntersect"]
source_file: "Doc/online/CAACgmModel/CAACgmUcGopIntersect.md"
converted: "2026-05-11T17:33:48.435496"
---
# Intersecting a Curve with a Surface  
  
---  
Use Case  
## Abstract

The CAAGMModelIntersect use case illustrates how to intersect a curve with a surface by using the _CATICGMIntersectionCrvSur_ operator.
    * What You Will Learn With This Use Case
    * The CAAGMModelIntersect Use Case
      * What Does CAAGMModelIntersect Do
      * How to Launch CAAGMModelIntersect
      * Where to Find the CAAGMModelIntersect Code
    * Step-by-Step
    * In Short
    * References  
---  
## What You Will Learn With This Use Case

This use case [1] is intended to help you to use the CATICGMIntersectionCrvSur operator. See [2] for an overview of this type of operators.
## The CAAGMModelIntersect Use Case

CAAGMModelIntersect is a use case of the CAAGMModelInterfaces.edu framework.
### What Does CAAGMModelIntersect Do

This use case creates the input data to be passed to the CATICGMIntersectionCrvSur operator (a line and a cylinder). The result can be optionally saved into an NCGM container and displayed using the CAAGMModelGemBrowser use case [3].

Fig. 1: The Geometry of the CAAGMModelIntersect Use Case ![Use Case Data](images/CAACgmGopIntersect1.gif) | This use case illustrates the global scheme of the geometric operators and takes the curve-surface intersection operator as example. The curve is a line, and the surface a cylinder. The operator being independent of the type of curve or surface, any kind of curve or surface can be used in the same way.  
---|---  
### How to Launch CAAGMModelIntersect 

To launch CAAGMModelIntersect, you will need to set up the build time environment, then compile CAAGMModelIntersect.m along with its prerequisites, set up the run time environment, and then execute the use case [4].

If you simply type CAAGMModelIntersect with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example:

CAAGMModelIntersect `e/Intersection.NCGM`

This NCGM file can be displayed using the CAAGMModelGemBrowser use case [3].
### Where to Find the CAAGMModelIntersect Code

The CAAGMModelIntersect use case is made of a main named CAAGopIntersect.cpp located in the CAAGMModelIntersect .m module of the CAAGMModelInterfaces.edu framework:

`InstallRootDirectory\CAAGMModelInterfaces.edu\CAAGMModelIntersect.m\`

where `InstallRootFolder` [4] is the folder where the API CD-ROM is installed.
## Step-by-Step

The initial step which consists in creating the geometry factory as well as the last step which consists in writing the model and closing the factory are described in . The coding steps dedicated to the CATICGMIntersectionCrvSur operator are explained below:

    1. Creating the Geometry Factory [1].
    2. Creating the Line and Cylinder to Intersect.
    3. Using the BASIC Mode [2] 
       * Creating the operator.
       * Getting the results by using the iterators.
       * Deleting the operator.
    4. Using the ADVANCED Mode [2] 
       * Creating the operator.
       * Running.
       * Getting the results.
       * Modifying input parameters.
       * Running again.
       * Deleting the operator.
    5. Writing the Model and Closing the Factory [1].
### Creating the Line and Cylinder to Intersect
    
    // ------------ line passing thru (0,0,0), of direction (1.,1.,0)
    CATLine * piLine = piGeomFactory->**CreateLine**(CATMathO,     // (0,0,0) math point
                                                 CATMathVector(1.,1.,0.) );
    if (NULL==piLine) 
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }
    //
    // ------------ cylinder
    double radius = 10.;
    double axisStart = -50.;
    double axisEnd = 50.;
    double angleStart = 0.;
    double angleEnd = CAT2PI;
    CATCylinder* piCylinder = piGeomFactory->**CreateCylinder**(CATMathOIJK, // canonical axis system
                                                            radius,
                                                            axisStart,
                                                            axisEnd,
                                                            angleStart,
                                                            angleEnd);
    if (NULL==piCylinder) 
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }

The geometry is created by the `CATGeoFactory` with the `CreateLine` and `CreateCylinder` methods.
### Using the BASIC Mode

In this mode, you must use the operator only once with the input parameters. The results are retrieved with a point iterator which

    * Retrieves the number of solution points: `GetNumberOfPoints`.
    * Skips to the next point: `NextPoint`.
    * Creates the current geometric point: `GetCartesianPoint`.
    
    //  creation and run
    CATICGMIntersectionCrvSur* pIntOp = **::CATCGMCreateIntersection**(
                           piGeomFactory,   // geometric factory 
                           piLine,          // geometric line
                           piCylinder,      // geometric cylinder
                           **BASIC**);          // the mode (default value)
    //
    // get the results
    if (NULL == pIntOp) return (3);
    long nbPoints = pIntOp->**GetNumberOfPoints**();
    
    cout << "Basic case: Number of intersection points: "<< nbPoints 
         << endl;
    if (0 != nbPoints) 
    {
      // iterator on the resulting points
      pIntOp->**BeginningPoint**();	         // initialization
      while(TRUE== (pIntOp->**NextPoint**()) )   // loop on the resulting points
      {
        // create the geometric point
        CATCartesianPoint* piPoint=pIntOp->**GetCartesianPoint**(); 
        double x,y,z;
        if (NULL != piPoint)
        {
          piPoint->GetCoord(x,y,z);
          cout << " X= "<< x << " Y= "<< y << " Z= "<< z <<endl;
          // remove the point if you do not want to keep it
          piGeomFactory->**Remove**(piPoint); 
        }                          
      }
    }
    // delete the operator
    **pIntOp- >Release(); 
    pIntOp = NULL;**
### Using the ADVANCED Mode

This mode can be used, in case of the curve - surface intersection:

    * To set advanced parameters: the limits on the geometry to take into account for this operation.
    * To run again the operator on a different curve. This mode can be useful where performing intersections between a surface and a bunch of curves.
    
    CATTICGMIntersectionCrvSur* pIntOp = **::CATCGMCreateIntersection**(
                                    piGeomFactory,    // geometric factory
                                    piLine,           // geometric line
                                    piCylinder,       // geometric cylinder
                                    **ADVANCED**);        // MODE
    if (NULL==pIntOp) return (3);
    
    // set  limits. These limits were previously defined or computed
    pIntOp->**SetLimits**(crvLimits);
    
    // run
    pIntOp->**Run**();
    
    // get the results
    // ... same way as in BASIC mode ..., but not same result! 
    // as the curve limits are more restrictive, only one solution is found
    
    // set another line and new limits
    
    pIntOp->**SetCurve**(piNewLine);     // piNewLine was previously created
    pIntOp->SetLimits(newCrvLimits); // newCrvLimits was previously defined
    
    // run again 
    pIntOp->**Run**();
    
    // get the results
    nbPoints = pIntOp->GetNumberOfPoints();
    cout << " Number of intersection points: "<< nbPoints << endl;
    long nbCurves= pIntOp->GetNumberOfCurves();
    cout << "Number of intersection curves: "<< nbCurves << endl;
    
    // delete
    **pIntOp- >Release();  
    pIntOp=NULL;**

**Notes** :

    1. If you only ask for the number of solutions, without getting the corresponding geometric objects, these objects are not created in the geometric factory. So you will not see them at the visualization of the NCGM document. In the use case, the `NewLine` curve is lying on the cylinder. There is a curve solution, that is not created, because the `GetPCurve` method is not called.
    2. The limits are defined by two CATCrvParam. These CATCrvParam are directly computed by calling the `CATCurve::GetParam` method on two cartesian points. This is only possible, first because these points belong to the curve, and second because the line is a canonical entity. In other cases, you must use `CATProjectionPtCrv` to retrieve the `CATCrvParam` corresponding to a `CATPoint` on a given curve.
    
    CATCrvParam  startParam, endParam;
    
    // piLine is the line of origin CATMathO and of direction (1.,1.,0.)
    // The use of GetParam is only possible because the points belong to the line
    // and piLine is canonical.
    // In other cases use a CATProjectionPtCrv operator
    piLine->GetParam(CATMathO,startParam);
    
    // another point on the line  
    piLine->GetParam(CATMathPoint(35.,35.,0.),endParam);
    
    // the limits
    CATCrvLimits crvLimits(startParam,endParam);
## In Short

    * CATICGMIntersectionCrvSur is a geometric operator which follows the same scheme as all geometric operators: it is a transient object and its execution does not modify the input operands. It must be operated within a single container.
    * CATICGMIntersectionCrvSur can be used in BASIC and ADVANCED modes. The ADVANCED mode allows you to specify new parameters (new limits or a new curve to be intersected) and re-run the operator with these parameters.
## References

[1] | [An Introduction to Geometric Modeler Use Cases](CAACgmUcGMModelUseCaseOverw.md)  
---|---  
[2] | [How to Use Geometric Operators](CAACgmUcGMModelOpeOverw.md)  
[3] | [Browsing the Geometric Container](CAACgmUcGemBrowser.md)  
[4] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
## History

Version: **1** [Jan 2007] | Document created  
---|---
