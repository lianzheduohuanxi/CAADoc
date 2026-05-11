---
title: "How to Use the Topological Journal"
category: "use case"
module: "CAATopUseCases"
tags: ["CAAErrorTopStif7", "CAATopJournal", "CAAErrorTopStif6", "CAAErrorTopStif2", "CAAErrorTopStif5", "CAATopOperator", "CATICGMObject", "CAATopOverview", "CATIntersectionCrvCrv", "CAAErrorTopStif3", "CAAErrorTopStifx", "CAATopStifferner", "CAATopologicalOperators", "CATICGMContainer", "CAAGemBrowser", "CAATopStiffener", "CAAErrorTopStif1", "CAATopStiffner", "CAATeopJournal"]
source_file: "Doc/online/CAATopUseCases/CAATopJournal.md"
converted: "2026-05-11T17:31:50.719384"
---
# Geometric Modeler

| 
## Topology

| 
### How to Use the Topological Journal

_Reading data and creating the journal of a sequence of topological operations_  
---|---|---  
Use Case  
  
* * *
### Abstract

The journal describes the topological modifications brought to the input bodies to get the resulting body during a topological operation. The journal is filled under request by the topological operators. The use case proposes a way to define a topological operator by chaining a sequence of topological operators. In this sequence, data necessary to operations are read in the journal of previous operations. The journal of the global operation is filled. 

  * **What You Will Learn With This Use Case**
  * **The Principle**
  * **The CAATopJournal Use Case**
    * What Does CAATopJournal Do
    * How to Launch CAATopJournal
    * Where to Find the CATopJournal Code
  * **Step-by-Step**
  * **In Short**
  * **References**

  
---  
  
* * *
### What You Will Learn With This Use Case

In this use case, you learn how to create a new topological operator (`CAATopStiffner`) by chaining several CGM topological operators. In the sequence, 

  * The journal of the CGM operators is read to recover data needed to the operations
  * The journal corresponding to the global operation is created.

Meanwhile, the use of the some topological operators is detailed such as: 

  * The creation of a thin cylinder body
  * The creation of a skin body
  * The creation of a prism with "until" limits
  * The filleting of non connected edges in a single operation.

See "Overview of the Topological Operators" [3] to have the general scheme of the topological operators and other use examples.

[Top]
### The Principle

A topological operator operates on topological objects to create new topological objects. Most of the time, these topological objects are bodies (a body is a set of connected (or not) volumes, faces, edges and vertices [1]). A topological operator does never modify the input bodies: the resulting body is a new one, but it can share cells with the input bodies, if these cells are not touched by the operation. This is called the smart concept [2]. On request, the operator can describe the way to go from the initial objects to the resulting body. This information is then put by each operator into a topological journal.

The topological journal [4] records the creation, modification and deletion of the faces, free edges and free vertices of topological objects. A free edge is an edge bounding at most one face, and a free vertex is a vertex bounding at most one edge. In fact, it is sufficient to follow the modifications of these cells to know how the whole body is modified. The journal is attached to any topological or geometric operator that operates on topological objects.

This journal is transient. You have to create it before its use and delete it when you have finished.

As said, each topological operator is able to write the journal corresponding to its operation. So that the journal of the new operator is the concatenation of the journals of each called CGM operator, as demonstrated in the use case.

[Top]
### The CAATopJournal Use Case

CAATopJournal is a use case of the CAATopologicalOperators.edu framework that illustrates TopologicalOperators framework capabilities.

[Top]
#### What Does CAATopJournal Do

The use case defines a new topological operator `CAATopStiffener`, that follows the general scheme of the topological operators: 

  * Create
  * Run
  * Get the result
  * Delete.

This operator defines a stiffener between two thin cylinder bodies ("wings") as displayed on Fig.1.

Fig. 1: The Resulting Body ![](images/CAATopJournal1.gif) 

  * A rectangular `SkinBody` is extruded along the `z` direction to create a prism until `FirstCylinderBody` and `SecondCylinderBody` are reached
  * From the journal of this operation, the large lateral faces of the prim are retrieved. On these faces, holes could be created, that are only sketched here by circles to lighten the presentation
  * From the journal, the edges of the intersection between these faces and `FirstCylinderBody` are also retrieved
  * These edges are filleted in a single operation
  * The journal corresponding to this sequence of operations is filled.

  
  
[Top]
#### How to Launch CAATopJournal

To launch CAATopJournal, you will need to set up the build time environment, then compile CAATopJournal.m and CAATopOperator.m along with its prerequisites, set up the run time environment, and then execute the use case [5].

If you simply type CAATopJournal with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example:

With Windows `CAATopJournal e/ExJournal.NCGM`

With UNIX `CAATopJournal /u/ExJournal.NCGM`

This NCGM file can be displayed using the CAAGemBrowser use case.

 

[Top]
#### Where to Find the CAATeopJournal Code

The CAATopJournal use case is made of a main named CAATopJournal.cpp located in the CAATopJournal.m module of the CAATopologicalOperators.edu framework:

Windows | `InstallRootDirectory\CAATopologicalOperators.edu\CAATopJournal.m\`  
---|---  
Unix | `InstallRootDirectory/CAATopologicalOperators.edu/CAATopJournal.m/`  
  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

This main uses the new operator class CAATopStiffener, which header is located in the ProtectedInterfaces directory of the CAATopologicalOperators.edu framework, and which source is located in the CAATopOperator.m module of the CAATopologicalOperators.edu framework:

Windows | `InstallRootDirectory\CAATopologicalOperators.edu\CAATopOperator.m\`  
---|---  
Unix | `InstallRootDirectory/CAATopologicalOperators.edu/CAATopOperator.m/`  
  
[Top]
### Step-by-Step

The CAATopStiffener header declares the new class, the corresponding code implements it and CAATopJournal.cpp is a main to run the new operator.

The use case is divided into the following steps:

  * CAATopStiffener: a New Class
    * Testing the Inputs
    * Creating a Prism (`CATTopPrism`) With "Until"Limits
    * Searching For the Long Side of the Profile
    * Searching Inside the Journal For the Bottom Face of the Prism
    * Creating a Circle on the Underlying Surface of the Face
    * Searching Inside the Journal For the Face of the Upper Wing
    * Filleting
    * Returning the Journal Operator
  * CAATopJournal: Use of the New Class
    * Creating the Geometry Factory
    * Creating the Limiting Bodies
    * Creating the Skin Body to Extrude
    * Running the New Operator
    * Writing the Model and Closes the Container

[Top]
#### CAATopStiffener: a New Class

We first look at the header of the new class.
    
    
     class ExportedByCAATopOperator **CAATopStiffener** 
    {
    public:
    // deletes
       virtual ~CAATopStiffener();
      
    // constructs
      **CAATopStiffener** (CATGeoFactory     * iFactory,
                       CATTopData        * iData,
                       CATBody           * iFirstLimitBody,
                       CATBody           * iSecondLimitBody,
                       CATBody           * iSkinBody,
                       CATMathVector       iDirection,
                       CATCGMJournalList * iJournal=NULL);
    
    // runs
      int **Run**();
     
    // gets the result
      CATBody * **GetResult**() ;
    
    // data
    private : 
      CATGeoFactory     * _piGeomFactory;        _// the factory_
      CATBody           * _piFirstLimitBody;     _// the first relimiting surface_
      CATBody           * _piSecondLimitBody;    _// the second relimiting surface_
      CATBody           * _piSkinBody ;          _// the profile (containing an open shell)_
      CATMathVector       _direction;            _// the stiffener direction_
      CATTopData        * _pData;                _// the journal and configuration_
      CATBody           * _piResultingBody ;     _// the resulting body_ 
    };  
  
---  
  
`CAATopStiffener` uses the general scheme of the topological operators (create, Run, GetResult, delete), but it does not derive from `CATTopOperator`: remember that you must not derive from any CGM operator, as stated by the U1 status of this class. As for a CGM operator also, the journal must be allocated by the caller in order to be filled by the called operator: in fact, if the corresponding pointer is NULL inside the operator data `_pData`, the operator does not fill the journal.

The private data contains the necessary data to run the operator such as the direction of the extrusion, the pointer to the limiting bodies, the pointer to the journal or the pointer to the resulting body.

In the use case, the operator does not have any `SetXxxx` method that tunes it. But one can easily imagine a `SetMeanDirection` method, that computes the normal to the mean plane of `SkinBody` to define the extrusion direction for example.

The constructor simply fills in the private data of the class, except the resulting body, that will be created in the `Run` method.
    
    
    CAATopStiffener::**CAATopStiffener** (CATGeoFactory     * iFactory,
                                      CATTopData        * iData,
                                      CATBody           * iFirstLimitBody,
                                      CATBody           * iSecondLimitBody,
                                      CATBody           * iSkinProfile,
                                      CATMathVector       iDirection,
                                      CATCGMJournalList * iJournal)
    {
      _piGeomFactory    = iFactory;
      _piFirstLimitBody = iFirstLimitBody;
      _piSecondLimitBody= iSecondLimitBody;
      _piSkinBody       = iSkinProfile;
      _direction        = iDirection;
      _pData            = iData;
      _piResultingBody  = NULL;
    }  
  
---  
  
The `GetResult` method returns the pointer to the created body.
    
    
    CATBody * CAATopStiffener::**GetResult**()  
    {
      CATBody * piReturned = _piResultingBody;
      _piResultingBody = NULL;    _// GetResult must only be called once_
      return (piReturned);
    }  
  
---  
  
Notice that once read, the life cycle of the body is taken into account by the caller: the caller must remove it from the factory (`CATICGMContainer::Remove`) if it does not want to keep it. As any topological operator, `GetResult` must be only called once.

The destructor removes the created body, if it is created and never retrieved:
    
    
    CAATopStiffener::**~CAATopStiffener**()
    {
      // if the resulting body is created, and is never retrieved (GetResult), deletes it
      if(NULL != _piResultingBody) _piGeomFactory->**Remove**(_piResultingBody, 
                                                          CATICGMContainer::RemoveDependancies);
      _piResultingBody  = NULL;
      _piGeomFactory    = NULL;
      _piFirstLimitBody = NULL;
      _piSecondLimitBody= NULL;
      _piSkinBody       = NULL;
      _pData            = NULL;
    }  
  
---  
  
We can now concentrate on the important part of the operator: the `Run` method, that performs the following: 

  1. Testing the Inputs
  2. Creating a Prism (`CATTopPrism`) With "Until"Limits
  3. Searching For the Long Side of the Profile
  4. Searching Inside the Journal For the Bottom Face of the Prism
  5. Creating a Circle on the Underlying Surface of the Face
  6. Searching Inside the Journal For the Face of the Upper Wing
  7. Filleting (CATDynFillet)
  8. Returning the Journal Operator

[Top]

  1. _Testing the Inputs_

These inputs have been set by the constructor. One just checks that 
     * The pointer are not null
     * A resulting body has not already been computed
     * The input skin to extrude is really a skin body: from `SkinBody`, one gets only one domain of faces. The use case restricts the shell to have one face.
     * The relimiting bodies must be different.
    
    _// ---------- Avoids to run twice_
      CATBody * piResultingBody = _piResultingBody;
      if (NULL != piResultingBody) return(2);
      
      _// ---------- Tests the null pointers
      //_
      CATGeoFactory * piGeomFactory = _piGeomFactory;
      if (NULL == piGeomFactory ) return (1);
    
      _// ---------- First limit <> Second Limit
      //_
      CATBody *   piFirstLimitBody =_piFirstLimitBody;
      if (NULL == piFirstLimitBody) return (1);
      CATBody *   piSecondLimitBody =_piSecondLimitBody;
      if (NULL == piSecondLimitBody) return (1);
      if (piFirstLimitBody == piSecondLimitBody) return (3); 
      
      _// ---------- Tests whether theinput profile body has one domain, containing one face
      //   
      // The skin body to extrude _
      CATBody * piSkinBody = _piSkinBody; 
      if (NULL == piSkinBody ) return (1);
      if (1!= (piSkinBody->**GetNbDomain****s()** ))  return (1) _//one domain in the body_
      CATDomain* piShell=piSkinBody->**GetDomain**(1);       _//returns the domain_
      if(NULL==piShell) return(1);
      if (**2** != piShell->**GetLowDimension**()) return(4);    _//the domain is made of faces (dim=2)_
      long nbCells = piShell->**GetNbCellUses**();           _//count of faces_
      if (1!=nbCells) { return(4);} 
      CATFace * piFace = (CATFace *) (piShell->GetCell(1)); _// returns the face_
      if (NULL == piFace) return(4);  
  
---  
  
[Top]

  2. _Creating a Prism With "Until" Limits_

A prism operator is first created with the `::CATCreateTopPrism` global function.
         
         _// --------- Creates the operator
           //_
           double offset = 0.;
           CATMathDirection direction (_direction);
         
           _// Journal and configuration_       _// Constructs a topdata from the input_
           **CATTopData** internalTopdata(*_pData);  
                _// Gets the associated configuration_           
           **CATSoftwareConfiguration** * pConfig = internalTopdata.GetSoftwareConfiguration(); 
                _// To use it to create a journal that will be embedded in the created internalTopdata_
           CATCGMJournalList* pJournal = new CATCGMJournalList(**pConfig** ,NULL);
                _// sets the journal for the internal operations_
           internalTopdata.SetJournal(pJournal); 
                         __
           _// and now creates the operator_
           CATTopPrism  *pPrismOp = **::CATCreateTopPrism** (piGeomFactory,
                                                         &internalTopdata, 
                                                         piSkinBody,
                                                         &direction,
                                                         offset, // non significative: the limits are defined later
                                                         offset); // non significative: the limits are defined later
           if (NULL==pPrismOp) return (1);  
  
---  
  
A specific journal is created inside the operator: in fact, this journal is needed by the algorithm of CAATopStiffener, as seen later, but not necessarily asked for by the caller. Moreover, this allows the operator to modify the input journal (if asked for) only when all its algorithm is done. The specific journal is allocated and passed to the `::CATCreateTopPrism` global function within the data `internalTopData`. It is independent on the general input journal of the operator, which is stored in `_pData` at the `CATopStiffener` creation. In fact, if the journal in `_pData` is not null, `pJournal` will be copied inside it to report all the orders of the operators chain.

Notice that the journal is always versioned [6] by a software configuration, retrieved from the input CATTopData.

The geometry factory, the skin body to extrude and the extrusion direction are set at the `CAATopStiffener` creation. In case of "until" limits, the start and end offset are not significative: the limits are in fact tuned by the `SetLimit` method.
         
         _// --------- Sets options
           //
           // Sets the relimiting body_
           pPrismOp->**SetTrim**(piFirstLimitBody);
         
           _// Asks for the Boolean union with the relimiting body_
           pPrismOp->**SetOperation**(CatBoolUnion);
         
           _// Asks to also retrieve the result of the Booleean operation_
           pPrismOp->**SetResultMode**(TRUE);
         
           _// Sets the until limits: first limit_
           pPrismOp->**SetLimit**(CatLimStart,           _// first limit_
                              CatLimUntil,           _// until option_
                              TRUE ,                 _// same orientation as the direction_
                              offset,                _// non significative (until limits)_
                              piFirstLimitBody,      _// the limiting geometry: here a body_
                              piFirstLimitBody,      _// must be the same as the previous one_
                              CatPropagSingle);      _// keep to this value_
           
           _// Sets the until limits: second limit_
           pPrismOp->SetLimit(CatLimEnd,
                              CatLimUntil, 
                              TRUE , 
                              offset, 
                              piSecondLimitBody, 
                              piSecondLimitBody, 
                              CatPropagSingle);  
  
---  
  
The prism must be delimited on one of the limiting bodies (`SetTrim`), and there must be a Boolean union operation between the delimiting body and the computed prism (`SetOperation`). Moreover, we want to recover the result of this Boolean operation (`SetResultMode` set to `TRUE`). `SetLimit` must be called for each limit (`CatLimStart`, `CATLimEnd`), to ask an "until" limit (`CatLimUntil`) on each side. Notice that each limit can have a different behavior: one limit "until", the other defined by an offset from the profile. The prism operator can now be run.
         
         _// --------- Runs_
           **CATTry**
           {
             pPrismOp ->**Run**(); 
           }
           **CATCatch**(CATError,error)
           {
             cout << (error->GetNLSMessage()).ConvertToChar() << endl;
             rc = 20; 
           }
           **CATEndTry**
         
           if (rc!=0) **CAAErrorTopStif1**(rc,pJournal)
             
           _// --------- Gets the resulting body 
           //_
           CATBody * piMainBody1=NULL;
           piMainBody1 = pPrismOp->**GetBooleanResult**();
         
           _// gets the prism before the union_
           CATBody * piWithoutOperation = pPrismOp->**GetResult**();
         
           _// gets the journal of the boolean operation_
           CATCGMJournalList * pBooleanJournal = pPrismOp->**GetBooleanJournal**(); 
           
           if (NULL==piMainBody1 || NULL==pBooleanJournal || NULL==piWithoutOperation)
           {
             rc = 20;
             **CAAErrorTopStif2**(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation)
           }  
  
---  
  
As the `Run` method can throw errors, these are caught by the macros `CATTry`, `CATCatch`, `CATEndTry`. The `CAAErrorTopStifx` macros are defined in the use case to clean the model in case of return: they free the allocations and delete the intermediate created bodies and geometry, but are not detailed in this article.

The `GetResult` method returns the prism before its union with the limiting bodies, while the `GetBooleanResult` returns the body corresponding to the result after the union. In the same way, `pJournal` contains the modifications corresponding to the prism creation, whereas `GetBooleanJournal` returns a new created journal containing the modifications relative to the Boolean operation.

[Top]

  3. _Searching for the Long Side of the Profile_

In order to recover the faces on which circles have been drawn on Fig. 1, we first search the longest edge of the face of `SkinBody`.
         
         _// Creates the boundary iterator on the edge of the initial face (of the skin to extrude)_
           CATBoundaryIterator  *  pBoundaryIt =  piFace->**CreateBoundaryIterator**();
           if (NULL==pBoundaryIt)
           {
         	rc =1;
             CAAErrorTopStif2(...)  
           }
           _// Computes the length of an edge_
           CATSide side;
           CATCell*  piE1 = pBoundaryIt->**Next**(&side,NULL);
           if (NULL==piE1)
           {
             rc =1;
             CAAErrorTopStif3(...)
           }
           double l1= ((CATEdge * )piE1 )->**CalcLength**();
         
           _// Computes the length of the next  edge_
           CATCell*  piE2 = pBoundaryIt->Next(&side,NULL);
           if (NULL==piE2)
           {
             rc =1;
             CAAErrorTopStif3(...)
           }
           double l2=((CATEdge * )piE2)->CalcLength();
         
          _// Defines the width and the height according to l1 and l2 values._  
           double height=0;
           double width=0;  
         
           CATCell * piHeight1 = NULL, *piHeight2 = NULL, *piWidth1 = NULL, *piWidth2 = NULL; 
           if ( l1 < l2 )
           {
             height    = l2;
             piHeight1 = piE2;
             piWidth1  = piE1;
             width     = l1;
             piWidth2  = pBoundaryIt->Next(&side,NULL);
             piHeight2 = pBoundaryIt->Next(&side,NULL);
         
           }
           else
           {
             height    = l1;
             piHeight1 = piE1;
             piWidth1  = piE2;
             width     = l2;
             piHeight2 = pBoundaryIt->Next(&side,NULL); 
             piWidth2  = pBoundaryIt->Next(&side,NULL);
           }
         
           **delete** pBoundaryIt;
           pBoundaryIt=NULL;  
  
---  
  
This edge could also be put as an input argument, or with a `SetXxx` method to the operator! Here, this gives us the opportunity to use a `CATBoundaryIterator` class to retrieve the edges of a face.

The iterator is created by the `CATCell::CreateBoundaryIterator` and skips from one boundary cell to the other one with the `CATBoundaryIterator::Next` method. The approximate length of an edge is computed with the `CATEdge::CalcLength` method. After comparing the lengths of the first two edges, we can easily deduce the two long sides, as the profile is rectangular.

The written code is not generic: by assumption, the face is rectangular.

[Top]

  4. _Searching Inside the Journal For the Bottom Face of the Prism_

The topological journal is made of `CATCGMJournalItem` (unitary order) and `CATCGMJournalList` (list of items). Each item has a type such as 
     * Creation: a new cell appears in the resulting body, built from an (optional) set of cells of the input body
     * Modification: the cell that is used does not appear in the resulting body, and is replaced by a new one
     * Deletion: the cell disappears in the resulting body.

To explore the topological journal, high level methods are provided, such as `FindFirsts` and `FindLasts`, that recursively scan the journal to retrieve: 
     * `FindFirsts`: all the faces at the higher level (the earliest in the journal ) that lead to the definition of a given cell
     * `FindLasts`: all the faces at the lower level (the latest in the journal) which definition depends on a given cell.

These methods can scan along a type of item, or several types (see the `ThroughCreateAndModify` value) 

Example: Let the following journal sequence: `F1 -> F2 -> F3 -> F4 -> F5`
     * `F1` created
     * `F2` modified from `F1`
     * `F3` modified from `F2`
     * `F4` modified from `F3`
     * `F5` modified from `F4`

`FindFirsts` from `F3` gives `F1`, and `FindLasts` from `F3` gives `F5`.
    
    _//  Retrieves all the objects created or modified from piHeight1
      //  first, in pJournal_
      CATLISTP(CATGeometry) pFaces; 
      pJournal->**FindLasts** (piHeight1,pFaces,**ThroughCreateAndModify**);
    
      CATFace * piFromHeight1=NULL;
      int nbresult = pFaces.Size();
    
      _// Retrieves the object that is a face._
      for (int i=1 ; (i <= nbresult) && (piFromHeight1 == NULL) ; i++) 
      {
    	 if (pFaces[i]->IsATypeOf(CATFaceType)) { piFromHeight1=(CATFace *)pFaces[i];}
      }
    
      _//  now, in pBooleanJournal_
      pFaces.**RemoveAll**();                       // voids the list before a new use
      pBooleanJournal->**FindLasts** (piFromHeight1,pFaces,**ThroughModify**);
      CATFace * piBooleanFromHeight1=NULL;
      nbresult = pFaces.Size();
    
      _// Retrieves the object that is a face._
      for (i=1 ; (i <= nbresult) && (piBooleanFromHeight1 == NULL) ; i++) 
      {
    	 if (pFaces[i]->IsATypeOf(CATFaceType))	 { piBooleanFromHeight1=(CATFace *)pFaces[i];}
      }
    
      if (NULL==piBooleanFromHeight1) 
      {
        rc =21;
        CAAErrorTopStif3(...)
      }  
  
---  
Fig. 2: The Journal and Boolean Journal of CATTopPrism ![](images/CAATopJournal2.gif) 
     * In the journal relative to the prism creation, `FindLasts` finds the cell `FromHeight1` resulting from `Height1`. The `ThroughCreateAndModify` option indicates that the search is done among the creation and modification items. At this stage, the cells are already delimited on the limiting body, but not glued.
     * In the journal relative to the Boolean union, `FindLasts` finds the cell `BooleanFromHeight1` from `FromHeight1`. This cell is the cell on which `CAATopStifferner` creates a circle. The `ThroughModify` option indicates that the search is done among the modification items only. After the Boolean operation, the prism and the limiting bodies are glued.  
---|---  
  
[Top]

  5. _Creating a Circle on the Underlying Surface of the Face_
         
         _// Gets the surface of the face_  
           CATOrientation orientation;
           CATSurface * piSurfaceFromHeight = piBooleanFromHeight1->**GetSurface**(&orientation);
           if (NULL==piSurfaceFromHeight) 
           {
             rc =1;
             CAAErrorTopStif3(...)
           }
         
          _// Estimates the center of the face_  
           CATSurParam centerParam;
           piFromHeight1->**EstimateCenterParam** (centerParam);
         
           _// Creates a circle on the surface_
           CATPCircle * piPCircle1 = piGeomFactory -> **CreatePCircle**( height/3.,
                                                                     centerParam, 
                                                                     piSurfaceFromHeight);
           if (NULL==piPCircle1) 
           {
             rc =1;
             CAAErrorTopStif3(...)
           }  
  
---  
  
The surface is retrieved with the `CATFace::GetSurface` method. The center of the circle is put at the "center" of the face, which is only an approximate point. The created circle is a `CATPCircle`, because it is a circle in the space of the surface.

The way to define a circle on the other face is similar and not detailed here.

[Top]

  6. _Searching Inside the Journal For the Face of the Upper Wing_

On must first define one journal of the two operations: the prism creation (`pJournal`) and the Boolean operation (`pBooleanJournal`).
         
         _// Copies in a single journal and deletes the unused body_
           pBooleanJournal-> **Duplicate**(pJournal);
           piGeomFactory->**Remove**(piWithoutOperation,**pJournal**);
           piWithoutOperation=NULL;  
  
---  
  
`pBooleanJournal` is duplicated in `pJournal`. `pBooleanJournal` will be directly deleted at the `CATTopPrism` deletion, while `Journal` now contains all the items of both operations. Then, the prism before union is removed with the `Remove` method of `CATICGMContainer`, with the journal as input: in this case all deletion items will be logged if necessary.

Now, the face of the wing is searched for: this face has been modified by the Boolean operation: a hole is created. The word "modified" is a shorter way to tell that in the resulting body, a new face is created with a hole corresponding to the trace of the prism.
         
         __ CATLISTP(CATCell) listCells;
           piFirstLimitBody->GetAllCells(listCells,2);  _// gets all the faces of FirstlimitBody_
           nbCells = listCells.Size();
           
           CATFace * piFromBody1=NULL;
           int iok=0;
           for (i=1;(i <= nbCells)  ;i++)
           {    
             pFaces.**RemoveAll**();                          _// voids the list_
             pBooleanJournal -> **FindLasts** (listCells[i],pFaces,ThroughModify);
             nbresult = pFaces.Size();
             for (int j=1; (j <= nbresult) && (piFromBody1 == NULL) ; j++)
               
             {
               if (pFaces[j]->IsATypeOf(CATFaceType)     _// searches for a face_
                   && **pFaces[j] != listCells[i]** )        _// different from the initial one_
               { 
                 piFromBody1=(CATFace *)pFaces[j];
                 iok = iok + 1;
               }
             } 
           }
           if (1!=iok) 
           {
             rc=30;
             CAAErrorTopStif5(...) 
           }
         
           _// ---------- Deletes the operator_
           **delete** pPrismOp;
           pPrismOp = NULL;
           
  
---  
Fig. 3: Use Of the Boolean Journal to Recover the Upper Wing ![](images/CAATopJournal3.gif) 
     * All the faces of `FirstLimitBody` are first got. For each face `listCells[i]`, `FindLasts` searches for a cell resulting from a modification of `listCells[i]`. The resulting cells are put in the list `pFaces`, that is first cleaned (`RemoveAll`). `FindLasts` does never return a void `pFaces` list. If it does not find any solution, it returns the initial face `listCells[i]`. It is the reason why the returned solutions must be compared to the initial face.  
---|---  
  
[Top]

  7. _Filleting_

A filleting operation is defined by affecting a (possibly variable) radius to edges: 
     * The definition of the radius law is contained in the `CATDynFilletRadius` object: in the use case, the radius is chosen constant along the edges
     * The definition of the edges to fillet according to a given radius law is called ribbon and managed by the `CATDynFilletRibbon` object: there can be several ribbons in one fillet operation, but in the use case, only one is defined.
    
    __ CATDynFilletRadius * pRadius = new **CATDynFilletRadius**(
              5.,    _// radius value_
              NULL,  _// the cell on which the radius is defined (for variable radius)_
              NULL,  _// The ratio of the edge length defining the point (for variable radius)_
              NULL); _// must be kept to NULL_
      if (NULL==pRadius)
      {
        rc=1;
        CAAErrorTopStif5(...) 
      }
       
      CATLISTP(CATDynFilletRadius)	listRadius;		
      listRadius.Append(pRadius);  
  
---  
  
Now, the ribbon is defined.
    
    _//----first edge to fillet
    ___ listCells.RemoveAll();
      piFromBody1->**GetCommonBorderCells**( piBooleanFromHeight1,     _// the other face_
                                         1,                        _// must be put to 1_
                                         listCells,                _// the common cells_
                                         1);                       _// edge (dimension 1)_     
      if (1!=listCells.Size() )
      {  
        rc=10;
        CAAErrorTopStif6(...) 
      }
      CATLISTP(CATEdge) listEdges;
      listEdges.Append((CATEdge *)(listCells[1]));
    
      _//---- second edge to fillet_
      listCells.RemoveAll();
      piFromBody1->GetCommonBorderCells( piBooleanFromHeight2,     _// the other face_
                                         1,                        _// must be put to 1_
                                         listCells,                _// the common cells_
                                         1);                       _// edge (dimension 1)_    
      if (1!=listCells.Size() )
      {  
        rc=10;
        CAAErrorTopStif6(...) 
      }
      listEdges.Append((CATEdge *)(listCells[1]));
    
      _//---- the ribbon_
      CATDynEdgeFilletRibbon * pRibbon = new **CATDynEdgeFilletRibbon**(listEdges, listRadius);
      if (NULL==pRibbon)
      {  
        rc=1;
        CAAErrorTopStif6(...) 
      }
    
      _//---- trim option_
      pRibbon ->**SetSegmentationMode**(CATDynTrim);  
  
---  
  
The edges to fillet are common (`GetCommonBorderCells`) to the face with hole `FromBody1` and the faces of the prism `BooleanFromHeight1` and `BooleanFromHeight2`. These non connected edges are appended to the list used to define the ribbon. The `CATDynFilletRibbon::SetSegmentationMode` option indicates that the computed ribbon must be delimited on the main body.

The CATDynFillet operator can now be created.
    
    _// ----------- Creates the operator
      //_
      CATDynFillet * pFilletOp = **::CATCreateDynFillet**(piGeomFactory,&internalTopdata,piMainBody1,**pJournal**);
      if (NULL==pFilletOp)
      {  
        rc=1;
        CAAErrorTopStif7(...) 
      }
    
      _//---- Appends the ribbon_
      pFilletOp ->**Append**(pRibbon);
    
      _//---- Runs_
      CATTry
      {
        pFilletOp ->**Run**(); 
      }
      CATCatch(CATError,error)
      {
        cout << (error->GetNLSMessage()).ConvertToChar() << endl; 
        rc=20;
        CAAErrorTopStif7(...) 
      }
      CATEndTry
    
      _//---- Gets the resulting body_
      CATBody * piMainBody2  = pFilletOp->**GetResult**();
    
      if (NULL==piMainBody2)
      {  
        rc=1;
        CAAErrorTopStif7(...) 
      }
    
      _//---- Deletes the operator_
      delete pFilletOp;
      pFilletOp = NULL;
    
      if (NULL != pRadius) delete pRadius;
      pRadius = NULL;
      if (NULL != pRibbon) delete pRibbon;
      pRibbon = NULL;
    
      _//---- Deletes the unused body_
       piGeomFactory->**Remove**(piMainBody1,**pJournal**);
      _piResultingBody = piMainBody2;  
  
---  
  
Notice the general scheme of the operator. To use it: 
     * Create it
     * Set the options: here, the ribbon to fillet
     * Run it
     * Get the result
     * Delete it.

`pJournal` is re-used here, so that the filleting operator directly puts its items inside it: at the end of the operation, `pJournal` contains the items of the prism creation, the Boolean operation and the filleting operation. In the same way, the `GetResult` method retrieves `MainBody2`, the body representing the result of the three operations. `MainBody1` is now useless, and is removed by the factory: the items corresponding to this deletion are put in `pJournal`, as argument of the `Remove` method.

[Top]

  8. _Returning the Journal of the Operator_
         
         _// Fills the output journal if needed_
           CATCGMJournalList * pDataJournal = NULL;
           pDataJournal=_pData->GetJournal();
           if (NULL!= pDataJournal)
           {
             pJournal->Duplicate(pDataJournal);  _// duplicates the internal journal inside the input journal_
           }
           delete pJournal;                      _// deletes the internal journal_  
  
---  
  
As seen in step 2, `pJournal` was internally allocated to contain the items of the prism, Boolean union and filleting operations. If the caller of `CAATopStiffener` operator asks for the report of the modifications, the items must be copied inside the journal allocated by the caller, which address is stored in `_pData`. `pJournal` can then be deallocated.

[Top]
#### CAATopJournal: Use of the New Class

To use the new operator, one must go through the following steps: 

  * Creating the Geometry Factory
  * Creating the Limiting Bodies
  * Creating the Skin Body to Extrude
  * Running the New Operator
  * Writing the Model and Closes the Container

[Top]

  1. _Creating the Geometry Factory_

The geometry factory (`CATGeoFactory`) creates and manages all the `CATICGMObject`: it creates the points, curves, surfaces, and bodies, and removes them [7].

The `CATGeoFactory` creation itself is done by the global function `::CATCreateCGMContainer`.

Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.
         
         CATGeoFactory* piGeomFactory = **::CATCreateCGMContainer**() ;
         if (NULL==piGeomFactory) return (1);  
  
---  
  
[Top]

  2. _Creating the Limiting Bodies_

These bodies are defined as a cylinder skin body extruded along a direction. To create them, one must 
     * Create the geometric cylinder
     * Define a skin body
     * Extrude the skin body.
    
    CATMathDirection z(0.,0.,1.);
    CATMathAxis axis1(CATMathPoint(0.,0.,-120.),
                      CATMathVector(0.,1.,0.),
                      z,
                      CATMathVector(1.,0.,0.));
    double      radius = 140.;
    double      axisStart= -30.;
    double      axisEnd  = 30.;
    double      angleStart = **CATPIBY2** -0.3;
    double      angleEnd = CATPIBY2+0.3;
    CATCylinder * piCylinder1 = piGeomFactory->**CreateCylinder**
                         (axis1,radius,axisStart,axisEnd,angleStart,angleEnd);
    	
    if (NULL == piCylinder1)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }  
  
---  
  
A geometric object as a cylinder is created by the `CATGeoFactory`. `axisStart` and `axisEnd` define the limitation of the surface along the cylinder axis, `angleStart` and `angleEnd` define the limitation around the axis cylinder. The angle are measured in radians, `CATPI` and other related values are defined in `CATMathConstant.h`.
    
    _// Creates a skin body
    //_ _first defines an open configuration for the operator_
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    _// defines the data of the operator: configuration + journal_
    CATTopData topdata(pConfig,NULL);  _// an open configuration and a NULL journal_
    _// defines the limits to take into account_
    CATSurLimits limits;
    piCylinder1->GetLimits(limits);
    _// now creates the operator_
    CATTopSkin * pSkinOp = **::CATCreateTopSkin**(piGeomFactory,&topdata,piCylinder1,&limits);
    if (NULL==pSkinOp)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }
    
    _// Runs_
    pSkinOp->**Run**();
    
    _// Gets the resulting body_
    CATBody * piFirstCylinderBody = pSkinOp->**GetResult**();
    if (NULL==piFirstCylinderBody)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }
        
    _// Deletes the operator_
    **delete** pSkinOp;
    pSkinOp = NULL;			  
  
---  
  
The operator configuration is the level of software you want to use to run this operator. By default, define an open configuration as in this use case to run with the current level. Moreover here, the pointer to the journal is set to `NULL` in the operator data. So that the journal is not filled. The configuration must be released after use. Here, it is released after the call to the last operator. 

`CATTopSkin` can create a skin body from a list a curves on surface, or directly on the boundaries of a surface. Here the surface is the limited cylinder. `CATTopSkin` is invoked according to the general scheme, that: 
     * Creates with the global function `CATCreateTopSkin`
     * Runs
     * Gets the resulting skin body. This body is created in the `CATTopSkin` by the `CATGeoFactory`, that manages the life cycle of the CGM objects: in fact, if you want to delete the created body, call the `CATICGMContainer::Remove` method with the `CATICGMContainer::RemoveDependancies` option.
     * Deletes.

The created `SkinBody` is now extruded to create a prism with `CATTopPrism`.
    
    CATCGMJournalList * pJournal = NULL;
    
    CATTopPrism  *pPrismOp = **::CATCreateTopPrism** (piGeomFactory,
                                                  &topdata,
                                                  piFirstCylinderBody,
                                                  &z,
                                                  0.,               // limit1
                                                  2.,               // limit2
                                                  pJournal);
    if (NULL==pPrismOp)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }
    
    pPrismOp->**Run**();
    CATBody* piFirstLimitBody = pPrismOp->**GetResult**();
    if (NULL==piFirstLimitBody)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }
    **delete** pPrismOp;
    pPrismOp=NULL;  
  
---  
  
Once again, the same steps are used, that: 
     * Creates (with the corresponding `::CATCreateTopPrism` global function) by declaring the body to extrude (`SkinBody`), the direction of the extrusion, the start and end limits of the prism from `SkinBody`
     * Runs
     * Gets the resulting body (`MainBody1`). This body is created in `CATTopPrism` by the `CATGeoFactory`, that manages the life cycle of the CGM objects: in fact, if you want to delete the created body, call the `CATICGMContainer::Remove` method with the `CATICGMContainer::RemoveDependancies` option.
     * Deletes.

As the body to extrude is a skin body, `FirstLimitBody` is a volume body. If the body to extrude were a wire body, the result would be a skin body. Other types of prism operations can be described, especially "until" operations: the limits of the prism are reached when encountering another body. This is detailed in the `CAATopJournal` section.

The other limiting body is created in the same way, and this is not detailed here.

[Top]

  3. _Creating the Skin Body to Extrude_

The cylinder skin body was created using a surface, here the skin body is defined by giving a list of four segments on a geometric plane.
         
         CATPlane * piPlane = piGeomFactory->**CreatePlane**(CATMathOIJ);	_// Geometrical plan_
         if (NULL == piPlane)
         {
           ::CATCloseCGMContainer(piGeomFactory);
           return (1);
         }
         
         CATMathPoint mathOrigin;
         CATMathDirection mathU, mathV;
         
         _// ----------- Retrieves the mathematical definition of the geometrical plane_
         piPlane->GetAxis(mathOrigin,mathU,mathV);
         	
         _// -----------Defines points on the plane
         // Notice that we do not make any assumption on the plane parameterization.
         // The use of GetParam is allowed here, because the 3D points belong to the plane
         // by construction_
         CATSurParam p1, p2, p3, p4;
         
         piPlane->GetParam(mathOrigin - 20*mathU - 5*mathV , p1);
         piPlane->GetParam(mathOrigin + 20*mathU - 5*mathV , p2);
         piPlane->GetParam(mathOrigin + 20*mathU + 5*mathV , p3);
         piPlane->GetParam(mathOrigin - 20*mathU + 5*mathV , p4);
         	
         _// ----------- Defines the curves of the profile_
         const int nbPCurves = 4;
         CATPCurve *  aPCurves[nbPCurves];
         CATCrvLimits aLimits[nbPCurves];
         short        aOrientations[nbPCurves];
         aPCurves[0]=  piGeomFactory->CreatePLine (p1, p2, piPlane );
         aPCurves[0] ->GetLimits(aLimits[0]);
         aPCurves[1]=  piGeomFactory->CreatePLine (p2, p3, piPlane);
         aPCurves[1] ->GetLimits(aLimits[1]);
         
         aPCurves[2]=  piGeomFactory->CreatePLine (p3, p4, piPlane);
         aPCurves[2] ->GetLimits(aLimits[2]);
         aPCurves[3]=  piGeomFactory->CreatePLine (p4, p1, piPlane );
         aPCurves[3] ->GetLimits(aLimits[3]);
         
         for (int i=0; i<nbPCurves; i++)
         {
           if (NULL==aPCurves[i])
           {
             ::CATCloseCGMContainer(piGeomFactory);
             return (1);
           }
         }
         
         _// Defines the orientations of the curves
         // This is needed by the CATTopSkin
         // Notice that in a more general case (use of circle for example), 
         // you must test the start and end as in CAATopOverview._
         	
         aOrientations[0] = 1;
         aOrientations[1] = 1;
         aOrientations[2] = 1;
         aOrientations[3] = 1;  
  
---  
  
No assumption can be done on the parameterization of the geometric objects. The parameters on the plane are evaluated with the `CATSurface::GetParam` method, from 3D points that are known to be on the plane. This method can be called because the plane is a canonical object, and the points are already on it. If one of these conditions were not filled, it would be mandatory to call the `CATProjectionPtSur` geometric operator.

`CATTopSkin` needs 
     * An ordered list of curves: contiguous curves must be contiguous in the list. The limits to take into account for each curve must be detailed. In the `CAATopJournal` case, the intersection between the lines and circles are defined by construction, but if it were not the case, they would be computed with the `CATIntersectionCrvCrv` geometric operator.
     * The orientation of each curve in the profile: the curve must be taken in its natural orientation (increasing parameter, +1 value) or in the opposite orientation (decreasing parameter, -1 value), such that the end (after orientation) of a curve must be linked to the beginning (after orientation) of the next curve. As defined here, all the curves must be taken in their natural orientation. It would not be the case if circles or other curves were used. See an example in the `CAATopOverview` use case [3].
    
    _// Creates the operator_
    pSkinOp = **CATCreateTopSkin** (piGeomFactory, 
                                &topdata,
                                nbPCurves, 
                                aPCurves,
                                aLimits,
                                aOrientations);
    if (NULL==pSkinOp)
    {
       ::CATCloseCGMContainer(piGeomFactory);
       return (1);
    }
    
    _// Runs_
    pSkinOp->**Run**();
    
    _// Gets the resulting body_
    CATBody * piSkinBody = pSkinOp->**GetResult**();
    if (NULL==piSkinBody)
    {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);
    }
        
    _// Deletes the operator_
    delete pSkinOp;
    pSkinOp = NULL;	  
  
---  
  
[Top]

  4. _Running the New Operator_
         
         _//--- Creates the operator_
         CAATopStiffener *pStiffOp = new **CAATopStiffener** (piGeomFactory,
                                                          &topdata,
                                                          piFirstLimitBody,
                                                          piSecondLimitBody,
                                                          piSkinBody,
                                                          z,
                                                          pJournal);
         if (NULL==pStiffOp)
         {
           ::CATCloseCGMContainer(piGeomFactory);
           return (1);
         }
         
         _//--- Runs_
         rc = pStiffOp->**Run**();
         if (NUL!=rc)
         {
           ::CATCloseCGMContainer(piGeomFactory);
           return (rc);
         }
         
         _//--- Gets the resulting body_
         CATBody * piMainBody1=NULL;
         piMainBody1 = pStiffOp->**GetResult**();
         if (NULL==piMainBody1)
         {
           ::CATCloseCGMContainer(piGeomFactory);
           return (1);
         }
         
         _//--- Deletes the operator_
         **delete** pStiffOp;
         pStiffOp = NULL;   
         
         _// Releases the configuration_
             pConfig->**Release**();    
  
---  
  
The new operator is used as a CGM operator with the steps that creates, runs, gets the result, and deletes.

The software configuration is also released, because it is no more used.

[Top]

  5. _Writing the Model and Closing the Factory_

To save the model in a file, the `::CATSaveCGMContainer` global function is used. Notice that in the sample, the save is conditioned by an input parameter representing the file inside which the model must be saved.

The sample ends with the closure of the geometry factory, done by the `::CATCloseCGMContainer` global function.
         
         if(1==toStore)
          {
         #ifdef _WINDOWS_SOURCE
            ofstream filetowrite(pfileName, ios::binary ) ;
         #else
            ofstream filetowrite(pfileName,ios::out,filebuf::openprot) ;
         #endif
         
            **::CATSaveCGMContainer**(piGeomFactory,filetowrite);
            filetowrite.close();
          }	
          _//
          // Closes the container
          //_
          **::CATCloseCGMContainer**(piGeomFactory);  
  
---  

[Top]

* * *
### In Short

The journal follows the topological modification from the input bodies (that are never modified) to the output body. This journal is read to recover topological entities, that can be later used in other topological operations.

New operator classes can be developed, by chaining several topological operations. In this case, the corresponding journal is the concatenation of the journal of each operator. If an intermediate body is removed, this must be declared in the journal.

[Top]

* * *
### References

[1] | [Topology Concepts](../CAATobTechArticles/TopoConcepts.md)  
---|---  
[2] | [The CGM Topological Model](../CAATobTechArticles/TopoModel.md)  
[3] | [Overview of the Topological Operators](CAATopOverview.md)  
[4] | [The CGM Journal](../CAATopTechArticles/TopoJournal.md)  
[5] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)  
[6] | [The versioning of the operators](../CAATopTechArticles/TopoVersioning.md)  
[Top]  
  
* * *
### History

Version: **1.1** [Oct 2000] | Operator configuration  
---|---  
Version: **1** [May 2000] | Document created  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
