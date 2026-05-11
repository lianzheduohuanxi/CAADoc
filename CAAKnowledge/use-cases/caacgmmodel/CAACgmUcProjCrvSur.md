---
```vbscript
title: "Projecting a Curve onto a Surface"
category: "use case"
module: "CAACgmModel"
tags: ["CATICGMProjectionCrvSur", "CAAGMModelInterfaces", "CAAGMModelProjectionOpe"]
source_file: "Doc/online/CAACgmModel/CAACgmUcProjCrvSur.htm"
converted: "2026-05-11T17:33:48.489649"
```

---
tags: ["CATICGMProjectionCrvSur", "CAAGMModelInterfaces", "CAAGMModelProjectionOpe"]
source_file: "Doc/online/CAACgmModel/CAACgmUcProjCrvSur.htm"
converted: "2026-05-11T17:33:48.489649"
Projecting a Curve onto a Surface  

---  
converted: "2026-05-11T17:33:48.489649"
Projecting a Curve onto a Surface
Use Case  
Abstract A curve can be projected onto a surface by using the CATICGMProjectionCrvSur operator. The result is a set of geometrical objects (curves and/or points) that you have to scan.

    * Operator to be Used
    * Use Case Description
    * References  
---  
Abstract A curve can be projected onto a surface by using the CATICGMProjectionCrvSur operator. The result is a set of geometrical objects (curves and/or points) that you have to scan.
Operator to be Used Use CATICGMProjectionCrvSur. This operator is created by using the `CATCGMCreateProjection` global function. Use Case Description The CAAGMModelProjectionOpe.m module in CAAGMModelInterfaces.edu illustrates how to project a curve onto a surface. This use case constructs its input data. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). With the input data below: Fig.1 Project a Curve onto a Surface:  Input data ![Porject a Curve onto a Surface](images/CGM_proj_crvSur_0.png)   

---  
Operator to be Used Use CATICGMProjectionCrvSur. This operator is created by using the `CATCGMCreateProjection` global function. Use Case Description The CAAGMModelProjectionOpe.m module in CAAGMModelInterfaces.edu illustrates how to project a curve onto a surface. This use case constructs its input data. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). With the input data below: Fig.1 Project a Curve onto a Surface:  Input data ![Porject a Curve onto a Surface](images/CGM_proj_crvSur_0.png)
and the code below:

    CATICGMProjectionCrvSur * pCrvSurOpe =:: CATCGMCreateProjection(piGeomFactory,
    		pConfig,
    		piNurbsCurve, &crvLim1;,
    		piNurbsSurface, &surLim1;);

    ...
    // c - Check the results
pConfig,
piNurbsCurve, &crvLim1;,
piNurbsSurface, &surLim1;);
    if (!pCrvSurOpe->GetNumberOfPoints() && !pCrvSurOpe->GetNumberOfCurves())

       {
piNurbsSurface, &surLim1;);
if (!pCrvSurOpe->GetNumberOfPoints() && !pCrvSurOpe->GetNumberOfCurves())
           cout << "Projection of curve onto surface has failed"  << endl; 

    		::CATCloseCGMContainer(piGeomFactory);
```vbscript
if (!pCrvSurOpe->GetNumberOfPoints() && !pCrvSurOpe->GetNumberOfCurves())
cout << "Projection of curve onto surface has failed"  << endl;
    		return (1);
```

       }
    // d - Scan the resulting curve
cout << "Projection of curve onto surface has failed"  << endl;
return (1);
    while (pCrvSurOpe->NextCurve())

       {
return (1);
while (pCrvSurOpe->NextCurve())
           pPcurve = pCrvSurOpe->GetPCurve();
           maxDist   = pCrvSurOpe->GetDistance();

           ...

    ---  

    you retrieve this curve .

      Fig.2 Curve Projected on Surface 

    	![Curve Projected on Surface](images/CGM_proj_crvSur_1.png) 

    ---  

    References

    		[1]
    		| 
    		[
    		Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)

    		[2]
    		| 
    		[About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)

    		[3]
    		| 
    		[How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)

    		[4]
    		| 
    		[How to Use Geometric Operators](CAACgmUcGMModelOpeOverw.md)

    History

    		Version: **1** [Feb 2014]
    		| Document created
