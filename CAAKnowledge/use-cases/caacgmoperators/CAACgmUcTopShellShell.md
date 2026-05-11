---
title: "Corner"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CATICGMHybIntersect", "CAAGMOperatorsIntersectShellShell"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopShellShell.htm"
converted: "2026-05-11T17:33:49.305940"
---

    
    
    
    
    
    
    
    	
    		
    		Intersecting Shells
    		
    	  
    ---  
    
    	
    		Use Case
    	  
    
    
    
    
    	
    		
    		Abstract
    		CATICGMHybIntersect can be used to compute the wire resulting from 
    		the intersection of two shells.
    		
    			
            * Operator to be Used
    
    			
            * Use Case Description
    
    			
            * References
    
    		
    		
    	  
    ---  
    
    
    
    Operator to be Used
    To intersect two shells, use the CATICGMHybIntersect operator in GMOperatorsInterfaces. 
    This operator has to be created by the CATCGMCreateTopIntersect global function.Use Case Description
    The CAAGMOperatorsIntersectShellShell.m module in CAAGMOperatorsInterfaces.edu 
    illustrates how to retrieve the wire resulting from the intersection of two 
    shells. This use case is to be run with 
    the intersectShellShell.NCGM input file which is delivered in 
    CAAGMOperatorsInterfaces.edu/FunctionTests/InputData. If you are not already 
    familiar with geometric modeler use cases, go to
    [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md).
    The input data are the plane in blue and the surface in yellow.
    
      Fig.1 Intersecting Shells
      
        
    	![Intersecting Shells](images/CGM_intersect_shellshell.png)
        
    ---  
    
    
    With the code below:
    
        
            
           
    
    CATICGMHybIntersect *pIntersectOpe = NULL;
    CATBody *CurrentBody = NULL;
    	
    pIntersectOpe = CATCGMCreateTopIntersect(piGeomFactory, &topdata, pBody1, pBody2);
    if(pIntersectOpe )
       {
          pIntersectOpe -> Run();
          CurrentBody = pIntersectOpe -> GetResult ();	
          pIntersectOpe-&gtRelease;(); pIntersectOpe=NULL;
       }
      
  
---  
the resulting object is the wire in purple. References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)  
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)  
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.md)  
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.md)  
History Version: **1** [Feb 2014] | Document created  
---|---
