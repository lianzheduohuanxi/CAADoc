---
title: "Connecting Wires"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CAAGMOperatorsConnectCurve", "CATICGMTopSimilarCurve"]
source_file: "Doc\online\CAACgmOperators\CAACgmUcTopConnectCurve.htm"
converted: "2026-05-11T17:33:49.117320"
---

Connecting Wires  
---  
Use Case  
Abstract Wires can be connected. The shape of the connecting piece can be computed from a reference curve. The reference curve as well as the created connecting curve have similar mathematical descriptions.
    * Operator to be Used
    * Use Case Description
    * References  
---  
   
Operator to be Used The CATICGMTopSimilarCurve operator is to be used.Use Case Description The CAAGMOperatorsConnectCurve.m module in CAAGMOperatorsInterfaces.edu illustrates how to connect two wires by specifying a base curve. This use case requires the Connect-Curve-Sample.NCGM file as input data. This file is delivered in the FunctionTests/InputData folder of CAAGMOperatorsInterfaces.edu framework.  If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.htm).With the input data below (wires to be connected in pink, base curve in dark blue, end points in green): Fig.1 Connect Curve : Input Data ![Connect Curve: Input data](images/CGM_connect_curve_0.png)  
---  
and the code below:
    
    CATICGMTopSimilarCurve * pSimilarCurve = CATCGMCreateTopSimilarCurve(piGeomFactory, 
    		&topdata;, 
    		piBodyBaseCurve, // the base curve
    		piBodyCurve1,    // the first wire
    		piBodyCurve2);   // the second wire
    ...
    pSimilarCurve->SetStartPoint(piBodyV1,piBodyCurve1); // specifies the start point
    pSimilarCurve->SetEndPoint(piBodyV2,piBodyCurve2);   // specifies the end point
    pSimilarCurve->Run();
    CATBody * pSimilCurvBody = pSimilarCurve->GetResult();
          
    ---  
    
    
    you get this result (connect curve in light blue):
    
      Fig.2 Connect Curve :  Result
      
        
    	![Connect Curve: Result](images/CGM_connect_curve_1.png)
    	 | 
    	 
           
    ---|---  
    
     
    
    References
    
    	
    		[1]
    		| 
    		[
    		Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.htm)
    	  
    ---|---  
    
    	
    		[2]
    		| 
    		[About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.htm)
    	  
    
    	
    		[3]
    		| 
    		[How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.htm)
    	  
    
    	
    		[4]
    		| 
    		[Understanding Boolean Operators](CAACgmTaTopBoolean.htm)
    	  
    
    
    
    		[5]
    		| 
    		[Overview of Topological Operators](CAACgmUcTopOverview.htm)
    	  
    
    	
    
    History
    
    	
    		Version: **1** [Oct 2011]
    		| Document created
    	  
    ---|---  
    
    
    
    
    
    
    
    
    
