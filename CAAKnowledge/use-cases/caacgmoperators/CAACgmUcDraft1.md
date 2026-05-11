---
title: "Basic Draft"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CAAGMOperatorsDraftCreation", "CATICGMDynDraft", "CAATopDraft", "CAATopDraftLimitingElement"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcDraft1.md"
converted: "2026-05-11T17:33:48.896806"
---

Basic Draft  
---  
Use Case  
Abstract A basic draft is created by specifying a face to be drafted, an angle, a neutral element and a pulling direction.  All the operation parameters are gathered in a CATDynDraftDomain which is added to the CATICGMDynDraft operator prior to running it.   

    * Operator to be Used
    * Use Case Description
    * References  
---  
Operator to be Used To create a basic draft, use the CATICGMDynDraft operator in GMOperatorsInterfaces. This operator has to be created using the CATCGMCreateDynDraft global function.  Use Case Description The CAAGMOperatorsDraftCreation.m module in CAAGMOperatorsInterfaces.edu framework illustrates how to create drafts. This use case must be executed with two arguments, the input file DraftTest.NCGM which is delivered in the FunctionTests/InputData folder of the CAAGMOperatorsInterfaces.edu framework and the NCGM file to store the result. This use case is divided into three parts. The part which is dedicated to the creation of a basic draft is in the CreateDraft.cpp code file, more precisely in the CAATopDraft function. This part of the use case creates its own input data. The input file which is required by the global use case execution is related to the creation of advanced drafts.  If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). Case 1: No Limiting Element (CAATopDraft Function) Fig.1 Basic Draft: Input data (face to be drafted in dark green, neutral face in yellow, pulling direction is normal to the neutral face ) ![Basic Draft: Input File](images/CGM_basic_draft_0.png)  
---  
With the code below:
    
    // (a) Compute a normal (this is an example)
    CATMathVector  Vector;
    const  CATSurLimits*  pBox2D  =  pNeutralFace->Get2DBoundingBox();  
    CATSurParam  Param  (0.5,  0.5,  *pBox2D);  
    pNeutralFace->EvalNormal(Param,  Vector);  
    CATMathDirection  PullingDirection  =  Vector; 
    
    // (b)Create the CATICGMDynDraft operator
    CATICGMDynDraft* pDraftOpe = CATCGMCreateDynDraft (piGeomFactory, &topdata;, pBody, CATDynAutoJoint);
    
    // (c) Create the CATDynDraftAngle, the object which defines
    // which faces are to be drafted with which angle
    CATAngle angle = 10.0;
    CATDynDraftAngle * pdraftAngle    =  new  CATDynDraftAngle(listOfFacesToDraft,angle); 
    CATLISTP(CATDynDraftAngle) facesAndAngles;
    facesAndAngles.Append(pdraftAngle);
    
    // (d) Create the CATDynDraftRibbon and CATDynDraftDomain to define a set of parameters:
    // neutral face and pulling direction.
    CATDynDraftRibbon * pdraftRibbon  =  new  CATDynDraftRibbon(facesAndAngles ); 
    CATLISTP(CATDynDraftRibbon) ribbons;
    ribbons.Append(pdraftRibbon);
    CATDynDraftDomain * pdraftDomain  =  new  CATDynDraftDomain(PullingDirection,  
        CATDynDraftDomainNeutral, 
        pNeutralFace, 
        ribbons);  
    pDraftOpe->Add(pdraftDomain);
    
    // (e) Run the operator
    pDraftOpe->Run();
    
    // (f) Get the result   
    CATBody * pWireBody = pDraftOpe->GetResult();
    ...
      
  
---  
you get this result: Fig.2 Basic Draft:  Result  ![Basic Draft: Result](images/CGM_basic_draft_1.png)  
---  
case 2: Limiting Element (CAATopDraftLimitingElement Function) Specifying a plane as limiting element:
    
    ...  
    pDraftOpe->Add(pdraftDomain);
    pDraftOpe->AddLimiting(piLimitingBody); // limiting element
    // (e) Run the operator
    pDraftOpe->Run();
    
    // (f) Get the result   
    CATBody * pWireBody = pDraftOpe->GetResult();
    ...
      
  
---  
restricts the draft creation. The draft is generated only up to the limiting element. Fig.3 Basic Draft with Limiting Element(in Blue)  ![Basic Draft With Limiting Element](images/CGM_basic_draft_2.png)  
---  
References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)  
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)  
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.md)  
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.md)  
History Version: **1** [Sept 2011] | Document created  
---|---
