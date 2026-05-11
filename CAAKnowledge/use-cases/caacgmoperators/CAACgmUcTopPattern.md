---
title: "Creating a Pattern"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsPattern", "CAAGMOperatorsInterfaces", "CATICGMTopPattern", "CATICGMSolidCylinder"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopPattern.md"
converted: "2026-05-11T17:33:49.266941"
---

Creating a Pattern  
---  
Use Case  
Abstract A pattern is a set of operations repeated by applying a transformation in the same body. 
    * Operator to be Used
    * Use Case Description
    * References  
---  
Operator to be Used To create a pattern, use the CATICGMTopPattern operator in GMOperatorsInterfaces. This operator has to be created by the CATCGMCreateTopPattern global function. Use Case Description The CAAGMOperatorsPattern.m module in CAAGMOperatorsInterfaces.edu illustrates how to create a pattern. This use case is to be run with the PatternTest.NCGM input file which is delivered in CAAGMOperatorsInterfaces.edu/FunctionTests/InputData. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). Case 1: Pattern Creation from a List of Faces With the input data below: Fig.1 Pattern Operation: Input Data ![Pattern Support](images/CGM_pattern_0.png) 
---|---  
and the code below:
    
    CATLISTP(CATMathTransformation) translationList;
    int nbOccurrences = 9;
    // Translation distance
    double distToNext = 40.0;
     
    for (int i = 1; i <=nbOccurrences; i++)
    	{			
    		CATMathTransformation *pTrans =
    			new CATMathTransformation(CATMathVector(i * distToNext, 0, 0));
    		translationList.Append(pTrans);
    	}
    // 
    // Create a plane representing the pattern plane (performance)
    // 
    CATMathPlane patternMathPlane(CATMathPoint(0, 0, 10), CATMathVector(0, 0, 1));
    CATPlane* pPatternPlane =iFactory->CreatePlane(patternMathPlane);
    // 
    // Create the pattern operator
    // 
    CATICGMTopPattern *pPatternOp =
    		CATCGMCreateTopPattern(iFactory, iTopData, iBody, pPatternPlane, iFaces, &translationList;);
    // 
    // Identify the pattern type (performance)
    //
    pPatternOp->SetRectPattern(nbOccurrences , translationList[1], 1, NULL);
    
    // 
    // Run the pattern operator and get the result
    // 
    pPatternOp->Run();
    oResultBody = pPatternOp->GetResult();
    ...
    	  
  
---  
you get this result: Fig.2 Result of Pattern Operation from a Set of Faces  ![Pattern Result - Set of faces](images/CGM_pattern_2.png) 
---|---  
Case 2: Pattern Creation from a Body to be Replicated  The body to be patterned is a solid cylinder. With the same input body as above and the code below:
    
    // Create the body to be patterned
    CATICGMSolidCylinder* pCylinderOp =
    		CATCGMCreateSolidCylinder(iFactory, iTopData, firstPointOnAxis, secondPointOnAxis, cylRadius);
    ...
    pCylinderOp->Run();
    CATBody *piCylindricalTool = pCylinderOp->GetResult();
    ...
    // Create a list of transformations for a 2D pattern
    CATLISTP(CATMathTransformation) translationList;
    int nbOccurrencesX = 10;
    int nbOccurrencesY = 3;
    double distToNextX = 40.0;
    double distToNextY = 30.0;
     
    for (int i = 1; i <= nbOccurrencesX; i++)
     {			
     	for (int j = 1; j <=nbOccurrencesY; j++)
    		{
    			CATMathTransformation * pTrans =
    				new CATMathTransformation(CATMathVector(i * distToNextX, -j * distToNextY, 0));
    			translationList.Append( pTrans );
    		}
     }
     
    // Create a plane representing the pattern plane (performance)
    CATMathPlane patternMathPlane(CATMathPoint(0, 0, 10), CATMathVector(0, 0, 1));
    CATPlane* pPatternPlane =iFactory->CreatePlane(patternMathPlane);
     
    // Create the pattern operator
    CATICGMTopPattern *pPatternOp =
    		CATCGMCreateTopPattern(iFactory, iTopData, CATBoolRemoval, iBody, pPatternPlane, 
    		    piCylindricalTool, &translationList;);
    
    // Identify the pattern type (performance)
    CATMathTransformation translation1X(CATMathVector(distToNextX, 0, 0));
    CATMathTransformation translation1Y(CATMathVector(0, -distToNextY, 0));
    pPatternOp->SetRectPattern(nbOccurrencesX, &translation1X;, nbOccurrencesY, &translation1Y;);
    pPatternOp->Run();
    pPatternOp->GetResult();
    	  
  
---  
you get this result: Fig.3 Result of Pattern Operation from a Body to be Replicated ![Pattern Result - Tool](images/CGM_pattern_4.png) 
---|---  
References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)  
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)  
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.md)  
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.md)  
History Version: **1** [Sept 2011] | Document created  
---|---
