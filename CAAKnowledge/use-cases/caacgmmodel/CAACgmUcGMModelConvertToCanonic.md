---
title: "Extracting the Canonical Representation of a Curve"
category: "use case"
module: "CAACgmModel"
tags: ["CAAGMModelInterfaces", "CATICGMConvertCurveToCanonic", "CAAGMModelConvertToCanonic"]
source_file: "Doc/online/CAACgmModel/CAACgmUcGMModelConvertToCanonic.htm"
converted: "2026-05-11T17:33:48.288651"
---
# Extracting the Canonical Representation of a Curve  
  
---  
Use Case  
## Abstract

Given a curve representing a line or a circle but not defined as a line or a circle, you can extract the canonical definition of the curve or circle.
    * Operator to be Used
    * Use Case Description
    * References  
---  
## Operator to be Used

Use the CATICGMConvertCurveToCanonic operator in GMModelInterfaces. This operator is created by the CATCGMCreateConvertCurveToCanonic global function. 
## Use Case Description

The CAAGMModelConvertToCanonic.m module in CAAGMModelInterfaces.edu illustrates how to extract the canonical definition of a line which is basically created as a spline. This use case creates its own input data: a spline curve. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md).

With the code below:
    
    const double Scale = 100.;
    const CATLONG32 NbPoints = 10;
    CATMathSetOfPointsND Points(3,NbPoints);
    double eps = 0.01*piGeomFactory->GetResolution();
    Points.Reset();
    for (CATLONG32 k=0; k < NbPoints; k++)
       {
    	  double lambda =double(k)/double(NbPoints);
    	  double p[3];
    	  p[0] =Scale*lambda;
    	  p[1] =Scale*lambda;
    	  p[2] =eps*sin(2.2*lambda);
    	   Points.AddPoint(p);
    	}
    CATSplineCurve * pSpline1 =piGeomFactory->CreateSplineCurve(&Points;, 0, 1, 2, 0);
    ...
    	  
  
---  
  
a spline is created. This spline passes through the points which are all aligned:

    * [0,   0,  ε]
    * [10, 10, ε]
    * [20, 20, ε]
    * [..., ...,  ε]
    * [90, 90, ε]
The code below creates a curve whose type is CATLineType 
    
    CATICGMConvertCurveToCanonic * pCrvToCanonicOpe1 = NULL;
    pCrvToCanonicOpe1 =::CATCGMCreateConvertCurveToCanonic(piGeomFactory,pConfig,pSpline1,Lim1);
    ...
    pCrvToCanonicOpe1->Run();
    CATCurve * pCrv1 = pCrvToCanonicOpe1->GetResult(oCrvLim1);
    if (pCrv1==NULL ||!pCrv1->IsATypeOf(CATLineType))
    	{
    	...
    	}
    		  
  
---  
  
Replacing the coordinates of Points[3] with {40,40,0.05} makes impossible the extraction of the canonical line definition as the new point is not aligned with the others. 
## References

[1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)  
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)  
[4] |  [How to Use Geometric Operators](CAACgmUcGMModelOpeOverw.md)  
## History

Version: **1** [Dec 2011] | Document created  
---|---
