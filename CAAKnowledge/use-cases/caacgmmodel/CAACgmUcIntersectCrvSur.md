---
title: "Intersecting a Curve and a Surface"
category: "use case"
module: "CAACgmModel"
tags: ["CAAGMModelInterfaces", "CATICGMIntersectionCrvSur", "CAAGMModelGeometryCreation", "CAAGMModelIntersectionOpe"]
source_file: "Doc/online/CAACgmModel/CAACgmUcIntersectCrvSur.htm"
converted: "2026-05-11T17:33:48.452515"
---
# Intersecting a Curve and a Surface  
  
---  
Use Case  
## Abstract

A curve and a surface can be intersected by using the CATICGMIntersectionCrvSur operator. The result is a set of geometrical objects (points, curves or a combination of these objects) that you have to scan.
    * Operator to be Used
    * Use Case Description
    * References  
---  
## Operator to be Used

Use CATICGMIntersectionCrvSur. This operator is created by using the CATCGMCreateIntersection global function. 
## Use Case Description

The CAAGMModelIntersectionOpe.m module in CAAGMModelInterfaces.edu illustrates how to intersect a curve and a surface. This use case constructs its input data and requires the CAAGMModelGeometryCreation.m module. You have to specify this module in your Imakefile.mk file.  If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md).

With the input data below:

Fig.1 Intersection:  Input data are a curve and a surface ![Intersect Curve and Surface](images/CGM_intersect_crvSur_0.png) 
---|---  
  
and the code below:
    
    CATICGMIntersectionCrvSur * pPtCrvSur =:: CATCGMCreateIntersection(
    		piGeomFactory,
    		pConfig,
    		piNurbsCurve, 
    		piTabulatedCyl1); 
    ...
    CATLONG32 nbOfPoints = pPtCrvSur->GetNumberOfPoints();
    cout   << "NumberOfPoints "   << nbOfPoints   << endl;
    CATPointOnSurface * Pt1= NULL;
    if(nbOfPoints)
        {
    	while(pPtCrvSur->NextPoint())
     	{
    	     // Retrieve the resulting points 
                 // 4 points are expected 
                 Pt1 = pPtCrvSur->GetPointOnSurface();
    	     CATMathPoint p;
    	     ...
    	     Pt1->GetMathPoint(p);
    	     cout   << "X="   << p.GetX()   << endl;
    	     cout   << "Y="   << p.GetY()   << endl;
                 cout   << "Z="   << p.GetZ()   << endl;
    	     ...
    	} 
    				
          
    ---  
    
    
    
    
    returns 
    
    
    NumberOfPoints 4
    X=20
    Y=0
    Z=0
    X=27.4154
    Y=13.7707
    Z=0
    X=32.7227
    Y=12.7463
    Z=0
    X=42.7015
    Y=10.7434
    Z=0

on the standard output.  Fig.2 Intersection:  Output data are four points ![Intersect Curve and Surface](images/CGM_intersect_crvSur_2.png)  
---  
## References

[1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)  
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)  
[4] |  [How to Use Geometric Operators](CAACgmUcGMModelOpeOverw.md)  
## History

Version: **1** [Feb 2014] | Document created  
---|---
