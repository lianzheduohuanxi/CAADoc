---
title: "Projecting a Point onto a Curve"
category: "use case"
module: "CAACgmModel"
tags: ["CATICGMProjectionPtCrv", "CAAGMModelInterfaces", "CAAGMModelProjectionOpe"]
source_file: "Doc/online/CAACgmModel/CAACgmUcProjPtCrv.htm"
converted: "2026-05-11T17:33:48.498129"
---

    
    
    
    
    
    
    
    	
    		
    		Projecting a Point onto a Curve
    		
    	  
    ---  
    
    	
    		Use Case
    	  
    
    
    
    
    	
    		
    		Abstract
    		A geometrical point can be projected onto a curve by using the CATICGMProjectionPtCrv operator. 
    		The result is a set of geometrical objects that you have to scan.
    		
    			
            * Operator to be Used
    
    			
            * Use Case Description
    
    			
            * References
    
    		
    		
    	  
    ---  
    
    
    
    Operator to be Used
    Use CATICGMProjectionPtCrv. This operator is created by using the CATCGMCreateProjection global function.
    
    Use Case Description
    The CAAGMModelProjectionOpe.m module in CAAGMModelInterfaces.edu 
    illustrates how to project a Cartesian point onto a curve. This use case 
    constructs its input data. If you are not already 
    familiar with geometric modeler use cases, go to
    [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md).
    With the input data below:
    
      Fig.1 Project a Point onto a Curve:  Input 
    	data
      
        
    	![Project a Point onto Surface](images/CGM_proj_ptCrv_0.png) 
         
    ---  
    
    
    and the code below:
    
        
            
           
    
    CATICGMProjectionPtCrv * pPtCrvOpe =:: CATCGMCreateProjection(piGeomFactory,
    		pConfig,
    		piCartP1, 
    		piNurbsCurve); 
    //     c - Retrieve the resulting points
    ...      
    if (pPtCrvOpe->GetNumberOfPoints()   >  0) 
      {
         pPtCrvOpe->BeginningPoint();
    	while ( pPtCrvOpe->NextPoint() )
    	    {
    		distancePtCrv = pPtCrvOpe->GetDistance();
    		pProjectedPtOnCrv = pPtCrvOpe->GetPointOnCurve() ;
    		pProjectedCartPoint = pPtCrvOpe->GetCartesianPoint() ;
    		pProjectedCrvParam = pPtCrvOpe->GetParam() ;
    	     }
    ...
    		
          
    ---  
    
    
    you retrieve three resulting points .
    
      Fig.2 Points Projected on Curve 
      
        
    	![Points Projected On Curve](images/CGM_proj_ptCrv_1.png) 
             
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
    	  
    
    
    
    
    
    
    
    
    
