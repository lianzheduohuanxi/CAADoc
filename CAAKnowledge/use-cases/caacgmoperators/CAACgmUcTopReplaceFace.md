---
title: "Modifying the Geometry of a Face"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CAAGMOperatorsFaceReplaceSurface", "CATICGMTopFaceReplaceSurface"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopReplaceFace.md"
converted: "2026-05-11T17:33:49.298443"
---

Modifying the Geometry of a Face  
---  
Use Case  
Abstract The geometry of a face, that is the surface underlying a CATFace can be replaced. The operator manages to extrapolate the adjacent faces up to the replacing surface in order to build a new solid. 
    * Operator to be Used
    * Use Case Description
    * References  
---  
   
Operator to be Used The CATICGMTopFaceReplaceSurface operator is to be used.Use Case Description The CAAGMOperatorsFaceReplaceSurface.m module in CAAGMOperatorsInterfaces.edu illustrates how to replace the geometry of a face by a new surface. This use case requires the ReplaceFace.NCGM file as input data. This file is delivered in the FunctionTests/InputData folder of CAAGMOperatorsInterfaces.edu framework.  If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md).With the input data below: Fig.1 Modify the Geometry of a Face : Input Data ![Modify the Geometry of a Face: Input Data](images/CGM_replace_face_0.png)  
---  
and the code below:
    
    CATICGMTopFaceReplaceSurface * pOp = ::CATCGMCreateFaceReplaceSurfaceOperator(piGeomFactory, &topdata;, piInputBody);
    ...
    CATSurLimits limits;
    piNewSurf->GetLimits(limits);
    pOp->ReplaceWith(piOldFace, piNewSurf, limits, CATOrientationNegative);
    
    pOp->Run();
    
    CATBody * piResultBody = pOp->GetResult();
    pOp->Release();
    pOp = NULL;
    
          
    ---  
    
    
    you get this result :
    
      Fig.2 Modify the Geometry of a Face :  Result
      
        
    	![Modify the Geometry of a Face: Result 1](images/CGM_replace_face_1.png)
    	 | 
    	![Modify the Geometry of a Face: Result 2](images/CGM_replace_face_2.png)
           
    
     
    
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
    
    	
    		Version: **1** [Oct 2011]
    		| Document created
    	  
    
    
    
    
    
    
    
    
    
