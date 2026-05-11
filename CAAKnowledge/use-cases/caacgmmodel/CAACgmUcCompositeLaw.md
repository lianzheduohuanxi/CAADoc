---
title: "Creating a Composite Law"
category: "use case"
module: "CAACgmModel"
tags: ["CAAGMModelInterfaces", "CAAGMModelMakeLaws"]
source_file: "Doc/online/CAACgmModel/CAACgmUcCompositeLaw.htm"
converted: "2026-05-11T17:33:48.173955"
---
# Creating a Composite Law  
  
---  
Use Case  
## Abstract

A composite law is made up of a set of C2 continuous laws but the connection between the pieces of the composite law is not necessarily continuous. Sub-laws can be of any type, they can be polynomial or user functions. Composite laws are used in various operations such as sweeps or variable fillets.
    * The API to be Used
    * Use Case Description
    * References  
---  
## The API to be Used

Use CATGeoFactory::CreateCompositeLaw in the GeometricObjects framework.
## Use Case Description

The CAAGMModelMakeLaws.m module in CAAGMModelInterfaces.edu illustrates how to manipulate mathematical functions and polynomials (CATMathFunctionX and CATMathPolynomX) as well as laws.

This use case constructs its input data. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md).
### Case 1: Linear functions

To define a composite law from two pieces 

    * f1(x) = 1 + 2x applied in the [ 0 , 0.5 ] range 
    * and f2(x) = 1.25 + 1.5x applied in the [ 0.5 , 2 ] range

you must:

define the two functions f1 and f2
    
    CATMathFunctionX *ListOfFunctions1[2] = { NULL, NULL };
    double array1[2] = {1,2};      // first law coefficients 1, 2
    CATMathPolynomX P1(1,array1);
    ListOfFunctions1[0]=&P1;
    double array2[2] = {2,1.5};    // second law coefficients
    CATMathPolynomX P2(1,array2);
    ListOfFunctions1[1]=&P2;
    ...
    
          
    ---  
    
    
    
    
    then create the composite laws
    
    
    
        
            
           
    
    CATCompositeLaw * compLaw1 = piGeomFactory->CreateCompositeLaw (2,LimitParameters1,
    		(const CATMathFunctionX**)ListOfFunctions1);
    	...
    
          
    ---  
    
    
    
    
    
    The CATCompositeLaw::Eval service computes the result for a given value. 
    
    
    
    ### Case 2: User Functions
    
    
    
    
    You can define a user function as a piece of a composite law. 
    
    
    
    
    To define a user function, you must create an object deriving from 
    CATMathFunctionX, and implement the services below:
    
    
    
    	
            * a constructor
    
    	
            * a destructor
    
    	
            * an eval method (here it depends on a trigonometric function but it could 
          	be any mathematical function)
    
    	
            * the Duplicate and DeepDuplicate methods.
    
    
    
    
    Using a user function in a composite law does not change the way you create 
    the composite law.
    
    
    
    
    ## References
    
    
    
    	
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
    	  
    
    	
    
    
    ## History
    
    
    
    	
    		Version: **1** [Feb 2014]
    		| Document created
    	  
    
    
    
    
    
    
    
    
    
