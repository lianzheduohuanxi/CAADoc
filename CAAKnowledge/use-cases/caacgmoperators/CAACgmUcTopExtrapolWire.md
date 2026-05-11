---
title: "Extrapolating a Wire"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CATICGMExtrapolateBody", "CATICGMWireExtrapolationOp", "CAATopTangExtrapol", "CAAGMOperatorsTangExtrapol"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopExtrapolWire.md"
converted: "2026-05-11T17:33:49.169875"
---

    
    
    
    
    
    
    
    	
    		
    		Extrapolating a Wire
    		
    	  
    ---  
    
    	
    		Use Case
    	  
    
    
    
    
    	
    		
    		Abstract
    		CATICGMExtrapolateBody can be used to extrapolate a wire in tangency 
    		and CATICGMWireExtrapolationOp to extrapolate a wire in curvature.
    		
    			
            * Operator to be Used
    
    			
            * Use Case Description
    
    			
            * References
    
    		
    		
    	  
    ---  
    
    
    
    Operator to be Used
    To extrapolate a wire in tangency, use the CATICGMExtrapolateBody operator in GMOperatorsInterfaces. This operator has to be created by the CATCGMCreateExtrapolateBody global function. 
    To extrapolate a wire in curvature, use CATICGMWireExtrapolationOp. This 
    operator has to be created by the CATCGMCreateWireExtrapolationOp global function.
    Use Case Description
    The CAAGMOperatorsTangExtrapol.m module in CAAGMOperatorsInterfaces.edu 
    illustrates how to extrapolate a wire. The wire to be extrapolated is a spline 
    which is created in CAATopTangExtrapol.cpp by using the CATCGMCreateTopSpline function.
    If you are not already 
    familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md).
    
      Fig.1 The spline to be extrapolated
      
        
    	![Extrapol Wire](images/CGM_extrapolWire_0.png)
        
    ---  
    
    
    Tangency Extrapolation
    With the code below:
    
        
            
           
    
    CATICGMExtrapolateBody * extrapolOpe0 =::CATCGMCreateExtrapolateBody(piGeomFactory,
            &amptopdata;,
            piSplineBody,NULL,0);
         if (NULL==extrapolOpe0)
        {
            ::CATCloseCGMContainer(piGeomFactory);
            return (1);
        }
        extrapolOpe0->SetLimitToExtrapolate(cellToExtrapolate, 20.0);
        extrapolOpe0->Run();
        CATBody * pBody0 = extrapolOpe0->GetResult();  
  
---  
you get this result: Fig.1 The extrapolated spline (tangency extrapolation) ![tangency extrapolation](images/CGM_extrapolWire_1.png)  
---  
Curvature Extrapolation With the code below:
    
    CATICGMWireExtrapolationOp * extrapolOpe1 =::CATCGMCreateWireExtrapolationOp(piGeomFactory,
            &amptopdata;,piSplineBody);
        if (NULL==extrapolOpe1)
        {
            ::CATCloseCGMContainer(piGeomFactory);
            return (1);
        }
        extrapolOpe1->SetExtrapolation(V2, 20.0);
        extrapolOpe1->Run();
        CATBody * pBody1 = extrapolOpe1->GetResult();
          
  
---  
you get this result: Fig.2 The extrapolated spline (curvature extrapolation) ![curvature extrapolation](images/CGM_extrapolWire_2.png)  
---  
References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)  
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)  
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.md)  
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.md)  
History Version: **1** [Feb 2014] | Document created  
---|---
