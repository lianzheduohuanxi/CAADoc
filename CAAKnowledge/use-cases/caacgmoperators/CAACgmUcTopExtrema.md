---
```vbscript
title: "Extrema of a Solid"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CATICGMTopBodyExtremum", "CAAGMOperatorsBodyExtremum"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopExtrema.htm"
converted: "2026-05-11T17:33:49.178885"
```

---
tags: ["CAAGMOperatorsInterfaces", "CATICGMTopBodyExtremum", "CAAGMOperatorsBodyExtremum"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopExtrema.htm"
converted: "2026-05-11T17:33:49.178885"
Extrema of a Solid  

---  
converted: "2026-05-11T17:33:49.178885"
Extrema of a Solid
Use Case  
Abstract Given a point located in a solid, the extrema are the point(s) which are the furthest or the closest from this input point in a given direction. 

    * Operator to be Used
    * Use Case Description
    * References  
---  
Abstract Given a point located in a solid, the extrema are the point(s) which are the furthest or the closest from this input point in a given direction.
Operator to be Used To compute the extrema of a solid, use the CATICGMTopBodyExtremum operator in GMOperatorsInterfaces. This operator has to be created by the CATCGMCreateDirBodyExtremum global function. Use Case Description The CAAGMOperatorsBodyExtremum.m module in CAAGMOperatorsInterfaces.edu illustrates how to compute the extrema of a solid. This use case creates the data to be passed to the operator. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). With the input data below: Fig.1 Extrema Computation : Input Data ![Extrema Input](images/CGM_extrema_0.png)  

---  
Operator to be Used To compute the extrema of a solid, use the CATICGMTopBodyExtremum operator in GMOperatorsInterfaces. This operator has to be created by the CATCGMCreateDirBodyExtremum global function. Use Case Description The CAAGMOperatorsBodyExtremum.m module in CAAGMOperatorsInterfaces.edu illustrates how to compute the extrema of a solid. This use case creates the data to be passed to the operator. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). With the input data below: Fig.1 Extrema Computation : Input Data ![Extrema Input](images/CGM_extrema_0.png)
and the code below:

    CATMathPoint Origin(0,0,0);
    CATMathVector VAxeX(1,0,0);
    CATMathVector VAxeY(0,1,0);
    CATMathVector VAxeZ(0,0,1);

    CATBody* pBodyXMin = NULL;

    ...

    // a - Compute the minimum along X
    //
CATBody* pBodyXMin = NULL;
    CATICGMTopBodyExtremum  *pOpXMin  =  CATCGMCreateDirBodyExtremum(piGeomFactory,    

        &topdata;,piBody,CATMinimum,VAxeX,Origin)  ;              
CATICGMTopBodyExtremum  *pOpXMin  =  CATCGMCreateDirBodyExtremum(piGeomFactory,
      if  (pOpXMin)  

      {  
CATICGMTopBodyExtremum  *pOpXMin  =  CATCGMCreateDirBodyExtremum(piGeomFactory,
if  (pOpXMin)
        pOpXMin->Run();  
        pBodyXMin =  pOpXMin->GetResult();  
        pOpXMin->Release();  
        pOpXMin  =  NULL;  

      }  
    ...
    // f - Compute the maximum along Z
    //
pOpXMin  =  NULL;
    CATICGMTopBodyExtremum  *pOpZMax  =  CATCGMCreateDirBodyExtremum(piGeomFactory,    

        &topdata;,piBody,CATMaximum,VAxeZ,Origin)  ;              
CATICGMTopBodyExtremum  *pOpZMax  =  CATCGMCreateDirBodyExtremum(piGeomFactory,
    if  (pOpZMax)  

      {  
CATICGMTopBodyExtremum  *pOpZMax  =  CATCGMCreateDirBodyExtremum(piGeomFactory,
if  (pOpZMax)
        pOpZMax->Run();  
        pBodyZMax =  pOpZMax->GetResult();   
        pOpZMax->Release();  
        pOpZMax  =  NULL;  

      }  

    ---  

    you get this result:

      Fig.2 Extrema Computation: Result

        ![Extrema Result](images/CGM_extrema_1.png)

    ---  

     Four extrema are returned as edges and two extrema (along Z) as faces.

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
    		[Understanding Boolean Operators](CAACgmTaTopBoolean.md)

    		[5]
    		| 
    		[Overview of Topological Operators](CAACgmUcTopOverview.md)

    History

    		Version: **1** [Sept 2011]
    		| Document created
