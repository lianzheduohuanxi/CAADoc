---
title: "Computing the Minimum Distance between Geometries"
category: "use case"
module: "CAACgmModel"
tags: ["CAAGMModelDistanceMinOpe", "CATICGMDistanceMinPtSur", "CAAGMModelInterfaces", "CATICGMDistanceMinCrvCrv", "CATICGMDistanceMinPtCrv"]
source_file: "Doc/online/CAACgmModel/CAACgmUcGMModelDistanceMin.md"
converted: "2026-05-11T17:33:48.298158"
---
# Computing the Minimum Distance between Geometries  
  
---  
Use Case  
## Abstract

The minimum distance between a point and a surface as well as the point matching this minimum distance can be computed.
    * Operator to be Used
    * Use Case Description
    * References  
---  
## Operator to be Used

To compute the minimum distance between: 
    * a cartesian point and a surface, use the CATICGMDistanceMinPtSur operator. This operator is created by the CATCGMCreateDistanceMin global function which is defined in the CATCGMCreateDistanceMinPtSur.h header of the GMModelInterfaces framework. 
    * a cartesian point and a curve, use the CATICGMDistanceMinPtCrv operator. This operator is created by the CATCGMCreateDistanceMin global function which is defined in the CATCGMCreateDistanceMinPtCrv.h header of the GMModelInterfaces framework. 
    * two curves, use the CATICGMDistanceMinCrvCrv operator. This operator is created by the CATCGMCreateDistanceMin global function which is defined in the CATCGMCreateDistanceMinCrvCrv.h header of the GMModelInterfaces framework. 
## Use Case Description

The CAAGMModelDistanceMinOpe.m module in CAAGMModelInterfaces.edu illustrates how to compute the minimum distance between two geometries. This use case creates its own input data. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md).
### Case 1: Minimum Distance between a Cartesian Point and a Surface

With the input data below:

Fig.1 Minimum Distance between a  Point and a Surface : Input Data ![Projection Point on Surface: Input](images/CGM_projection_ptSur_1.png)  
---  
  
and the code below:
    
    CATICGMDistanceMinPtSur * pDistMinPtSurOpe =::CATCGMCreateDistanceMin(piGeomFactory,
    		pConfig,
    		piCartP1, 
    		piNurbsSurface, TRUE); 
    ...
    // d - retrieves the distance, resulting point and CATSurParam
    //         
    double dist1 = pDistMinPtSurOpe->GetDistance();
    cout << "distance point - surface " << dist1 << endl;
    CATPointOnSurface * pPtOnSur = pDistMinPtSurOpe->GetPointOnSurface() ;
    ...
      
  
---  
generates this message on the standard output: 
    
    distance point - surface 21.5346
    

A projection point is created on the surface. The minimum distance is 21.535mm

Fig.2 Minimum Distance between Point and Surface : Projection Point ![Projection Point on Surface: Ouput](images/CGM_projection_ptSur_2.png)  
---  
## Case 2 : Minimum Distance between a Point and a Curve

With the input data below:

Fig.1 Distance Minimum between a Point and a Curve : Input Data ![ Distance Minimum between a Point and a 
	Curve : Input Data](images/CGM_distancemin_ptcrv_0.png)  
---  
  
and the code below:
    
    CATICGMDistanceMinPtCrv * pDistMinPtCrvOpe =::CATCGMCreateDistanceMin(piGeomFactory,
    		pConfig,
    		piCartP1, 
    		pNurbsCurve, ADVANCED); 
    ...
    pDistMinPtCrvOpe->Run();
    //     d - retrieves the distance, resulting point and CATSurParam
    //         
    double dist2= pDistMinPtCrvOpe->GetDistance();
    cout << "distance point - curve "<< dist2 << endl;
    CATPointOnCurve * ptOnCrv = pDistMinPtCrvOpe->GetPointOnCurve() ;	  
  
---  
generates this message on the standard output: 
    
    distance point - curve 32.0743
    

A projection point is created on the curve. The minimum distance is 32.0743mm

Fig.2 Distance Minimum between a  Point and Curve : Output Data ![Projection Point on Surface: Ouput](images/CGM_distancemin_ptcrv_1.png)  
---  
### Case 3 : Minimum Distance between Two Curves

With the input data below:

Fig.3 Distance Minimum between Two Curves : Input Data ![Distance Minimum between Two Curves: Input Data](images/CGM_distancemin_crvcrv_0.png)  
---  
  
and the code below:
    
    CATICGMDistanceMinCrvCrv * pDistMinCrvCrvOpe =::CATCGMCreateDistanceMin(piGeomFactory,
    		pConfig,
    		pLine, 
    		pNurbsCurve); 
    ...
    pDistMinCrvCrvOpe->Run();
    //     c - retrieves the distance min between both curves
    //         zero is expected as one end of the line is located on the curve
    double dist3= pDistMinCrvCrvOpe->GetDistance();
    cout << "distance curve - curve "<< dist3 << endl;  
  
---  
generates this message on the standard output: 
    
    distance curve - curve 0
    
## References

[1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)  
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)  
[4] |  [How to Use Geometric Operators](CAACgmUcGMModelOpeOverw.md)  
## History

Version: **1** [Dec 2011] | Document created  
---|---
