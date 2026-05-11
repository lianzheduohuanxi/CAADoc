---
```vbscript
title: "Using the Topological Journal"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CAAErrorTopStifx", "CATICGMProjectionPtSur", "CAAErrorTopStif5", "CATICGMContainer", "CATICGMIntersectionCrvCrv", "CAADoc", "CAAGMModelGemBrowser", "CAAErrorTopStif7", "CAAGMOperatorsOverview", "CATICGMDynFillet", "CAAErrorTopStif3", "CATICGMTopPrism", "CATICGMTopSkin", "CAATopStiffener", "CATICGMTopOperator", "CAATopStifferner", "CAATopStiffner", "CAAErrorTopStif2", "CATICGMObject"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopJournal.htm"
converted: "2026-05-11T17:33:49.202401"
```

---
Using the Topological Journal

    ---

    		Use Case

    		Abstract
    		The journal describes the topological modifications brought to the input
    		bodies to get the resulting body during a topological operation. The journal
    		is filled under request by the topological operators.
    		The use case proposes a way to define a topological operator by chaining
    		a sequence of topological operators. In this sequence, data necessary to
    		operations are read in the journal of previous operations. The journal of
    		the global operation is filled.

            * What You Will Learn With This Use Case

            * The Principle

            * The CAAGMOperatorsJournal Use Case

                * What Does CAAGMOperatorsJournal Do

                * How to Launch CAAGMOperatorsJournal

                * Where to Find the CAAGMOperatorsJournal Code

            * Step-by-Step

            * In Short

            * References

    ---

    What You Will Learn With This Use Case
    In this use case, you learn how to create a new topological operator (CAATopStiffner)
    by chaining several GM topological operators. In the sequence:

            * The journal of the GM operators is read to recover data needed to the operations.

            * The journal corresponding to the global operation is created.

    Meanwhile, the use of the some topological operators is detailed such as:

            * The creation of a thin cylinder body.

            * The creation of a skin body.

            * The creation of a prism with "until" limits.

            * The filleting of non connected edges in a single operation.

    See "Overview of the Topological Operators" [3] to
    have the general scheme of the topological operators and other use examples.

See "Overview of the Topological Operators" [3] to
have the general scheme of the topological operators and other use examples.
    The Principle
    A topological operator operates on topological objects to create new topological
    objects. Most of the time, these topological objects are bodies (a body is a set
    of connected (or not) volumes, faces, edges and vertices [1]).
    A topological operator does never modify the input bodies: the resulting body is
    a new one, but it can share cells with the input bodies, if these cells are not
    touched by the operation. This is called the smart concept [2].
    On request, the operator can describe the way to go from the initial objects to
    the resulting body. This information is then put by each operator into a topological
    journal.
    The topological journal [4] records the creation, modification
    and deletion of the faces, free edges and free vertices of topological objects.
    A free edge is an edge bounding at most one face, and a free vertex is a vertex
    bounding at most one edge. In fact, it is sufficient to follow the modifications
    of these cells to know how the whole body is modified. The journal is attached to
    any topological or geometric operator that operates on topological objects.
    This journal is transient. You have to create it before its use and delete it
    when you have finished.
    As said, each topological operator is able to write the journal corresponding
    to its operation. So that the journal of the new operator is the concatenation of
    the journals of each called GM operator, as demonstrated in the use case.

    The CAAGMOperatorsJournal Use Case
    CAAGMOperatorsJournal is a use case of the CAAGMOperatorsInterfaces.edu framework
    that illustrates GMOperatorsInterfaces framework capabilities.

    What Does CAAGMOperatorsJournal Do
    The use case defines a new topological operator CAATopStiffener,
    that follows the general scheme of the topological operators:

            * Create.

            * Run.

            * Get the result.

            * Delete.

    This operator defines a stiffener between two thin cylinder bodies ("wings")
This operator defines a stiffener between two thin cylinder bodies ("wings")
    as displayed on Fig.1.

    	Fig. 1: The Resulting Body

    		![Resulting Body](images/CAACgmTopJournal1.gif)
    		|

            * A rectangular SkinBody is extruded along the
          			z direction to create a prism until FirstCylinderBody
          			and SecondCylinderBody are reached.

            * From the journal of this operation, the large lateral faces of the
z direction to create a prism until FirstCylinderBody
and SecondCylinderBody are reached.
          			prism are retrieved. On these faces, holes could be created, that are
          			only sketched here by circles to lighten the presentation.

            * From the journal, the edges of the intersection between these faces
prism are retrieved. On these faces, holes could be created, that are
only sketched here by circles to lighten the presentation.
          			and FirstCylinderBody are also retrieved.

            * These edges are filleted in a single operation.

            * The journal corresponding to this sequence of operations is filled.

    How to Launch CAAGMOperatorsJournal
    To launch CAAGMOperatorsJournal, you will need to set up the build time environment,
    then compile CAAGMOperatorsJournal.m and CAAGMOperatorsOperatorCreation.m along
    with its prerequisites, set up the run time environment, and then execute the use
```vbscript
    case [5].
    If you simply type CAAGMOperatorsJournal with no argument, the use case executes,
```

    but doesn't save the result in an NCGM file. If you want to save this result, provide
    the full pathname of the NCGM file to create. For example:
    CAAGMOperatorsJournal e/ExJournal.NCGM
    This NCGM file can be displayed using the CAAGMModelGemBrowser use case.

    Where to Find the CAATeopJournal Code
    The CAAGMOperatorsJournal use case is made of a main named CAATopJournal.cpp
    located in the CAAGMOperatorsJournal.m module of the CAAGMOperatorsInterfaces.edu
    framework:
    InstallRootDirectory\CAADoc\CAAGMOperatorsInterfaces.edu\CAAGMOperatorsJournal.m\
    where InstallRootFolder [1] is the
    folder where the API CD-ROM is installed.
    This main uses the new operator class CAATopStiffener, which header is located
    in the ProtectedInterfaces directory of the CAAGMOperatorsInterfaces.edu framework,
    and which source is located in the CAAGMOperatorsOperatorCreation.m module of the
    CAAGMOperatorsInterfaces.edu framework:
    InstallRootFolder\CAADoc\CAAGMOperatorsInterfaces.edu\CAAGMOperatorsOperatorCreation.m\
    where InstallRootFolder [5] is the
    folder where the API CD-ROM is installed.

    Step-by-Step
    The CAATopStiffener header declares the new class, the corresponding code implements
    it and CAATopJournal.cpp is a main to run the new operator.
    The use case is divided into the following steps:

            * CAATopStiffener: a New Class

                * Testing the Inputs

                * Creating a
            		Prism with "Until" Limits

                * Searching for the
            		Long Side of the Profile

                * Searching
            		Inside the Journal for the Bottom Face of the Prism

                * Creating
            		a Circle on the Underlying Surface of the Face

                *
a Circle on the Underlying Surface of the Face
            		Searching
            		Inside the Journal for the Face of the Upper Wing

                * Filleting

                * Returning the Journal Operator

            * CAATopJournal: Use of the
          	New Class

                * Creating the Geometry Factory

                * Creating the Limiting Bodies

                * Creating the Skin Body to
            		Extrude

                * Running the New Operator

                * Writing the Model
            		and Closes the Container

    CAATopStiffener: a New Class
    We first look at the header of the new class.

CAATopStiffener: a New Class
We first look at the header of the new class.
    class ExportedByCAATopOperator **CAATopStiffener**

    {
We first look at the header of the new class.
class ExportedByCAATopOperator **CAATopStiffener**
    public:

    // deletes
class ExportedByCAATopOperator **CAATopStiffener**
public:
       virtual ~CAATopStiffener();

    // constructs
      **CAATopStiffener** (CATGeoFactory     * iFactory,
virtual ~CAATopStiffener();
                       CATTopData        * iData,
                       CATBody           * iFirstLimitBody,
                       CATBody           * iSecondLimitBody,
                       CATBody           * iSkinBody,
                       CATMathVector       iDirection,
                       CATCGMJournalList * iJournal=NULL);

    // runs
CATBody           * iSkinBody,
CATMathVector       iDirection,
CATCGMJournalList * iJournal=NULL);
      int **Run**();

    // gets the result
      CATBody * **GetResult**() ;

    // data
CATBody * **GetResult**() ;
    private :
      CATGeoFactory     * _piGeomFactory;        // the factory
      CATBody           * _piFirstLimitBody;     // the first relimiting surface
      CATBody           * _piSecondLimitBody;    // the second relimiting surface
      CATBody           * _piSkinBody ;          // the profile (containing an open shell)
      CATMathVector       _direction;            // the stiffener direction
      CATTopData        * _pData;                // the journal and configuration
      CATBody           * _piResultingBody ;     // the resulting body

    };

`CAATopStiffener` uses the general scheme of the topological operators (create, Run, GetResult, delete), but it does not derive from `CATICGMTopOperator`: remember that you must not derive from any GM operator, as stated by the U1 status of this class. As for a GM operator also, the journal must be allocated by the caller in order to be filled by the called operator: in fact, if the corresponding pointer is NULL inside the operator data `_pData`, the operator does not fill the journal. The private data contains the necessary data to run the operator such as the direction of the extrusion, the pointer to the limiting bodies, the pointer to the journal or the pointer to the resulting body. In the use case, the operator does not have any `SetXxxx` method that tunes it. But one can easily imagine a `SetMeanDirection` method, that computes the normal to the mean plane of `SkinBody` to define the extrusion direction for example. The constructor simply fills in the private data of the class, except the resulting body, that will be created in the `Run` method.

CATBody           * _piResultingBody ;     // the resulting body
    CAATopStiffener::**CAATopStiffener** (CATGeoFactory     * iFactory,
                                      CATTopData        * iData,
                                      CATBody           * iFirstLimitBody,
                                      CATBody           * iSecondLimitBody,
                                      CATBody           * iSkinProfile,
                                      CATMathVector       iDirection,
                                      CATCGMJournalList * iJournal)

    {
CATBody           * iSecondLimitBody,
CATBody           * iSkinProfile,
CATMathVector       iDirection,
CATCGMJournalList * iJournal)
      _piGeomFactory    = iFactory;
      _piFirstLimitBody = iFirstLimitBody;
      _piSecondLimitBody= iSecondLimitBody;
      _piSkinBody       = iSkinProfile;
      _direction        = iDirection;
      _pData            = iData;
      _piResultingBody  = NULL;

    }

_direction        = iDirection;
_pData            = iData;
_piResultingBody  = NULL;
The `GetResult` method returns the pointer to the created body.

    CATBody * CAATopStiffener::**GetResult**()

    {
The `GetResult` method returns the pointer to the created body.
CATBody * CAATopStiffener::**GetResult**()
      CATBody * piReturned = _piResultingBody;
      _piResultingBody = NULL;    // GetResult must only be called once
      return (piReturned);

    }

CATBody * piReturned = _piResultingBody;
_piResultingBody = NULL;    // GetResult must only be called once
return (piReturned);
Notice that once read, the life cycle of the body is taken into account by the caller: the caller must remove it from the factory (`CATICGMContainer::Remove`) if it does not want to keep it. As any topological operator, `GetResult` must be only called once. The destructor removes the created body, if it is created and never retrieved:

    CAATopStiffener::**~CAATopStiffener**()

    {
      // if the resulting body is created, and is never retrieved (GetResult), deletes it
Notice that once read, the life cycle of the body is taken into account by the caller: the caller must remove it from the factory (`CATICGMContainer::Remove`) if it does not want to keep it. As any topological operator, `GetResult` must be only called once. The destructor removes the created body, if it is created and never retrieved:
CAATopStiffener::**~CAATopStiffener**()
      if(NULL != _piResultingBody) _piGeomFactory->**Remove**(_piResultingBody,
                                                          CATICGMContainer::RemoveDependancies);
      _piResultingBody  = NULL;
      _piGeomFactory    = NULL;
      _piFirstLimitBody = NULL;
      _piSecondLimitBody= NULL;
      _piSkinBody       = NULL;
      _pData            = NULL;

    }

_piSecondLimitBody= NULL;
_piSkinBody       = NULL;
_pData            = NULL;
We can now concentrate on the important part of the operator: the `Run` method, that performs the following:
    1. Testing the Inputs
    2. Creating a Prism with "Until" Limits
    3. Searching for the Long Side of the Profile
    4. Searching Inside the Journal for the Bottom Face of the Prism
    5. Creating a Circle on the Underlying Surface of the Face
    6. Searching Inside the Journal for the Face of the Upper Wing
    7. Filleting
    8. Returning the Journal of the Operator
    1. Testing the Inputs These inputs have been set by the constructor. One just checks that:

       * The pointers are not null.
       * A resulting body has not already been computed.
       * The input skin to extrude is really a skin body: from `SkinBody`, one gets only one domain of faces. The use case restricts the shell to have one face.
       * The relimiting bodies must be different.

    // ---------- Avoids to run twice
      CATBody * piResultingBody = _piResultingBody;
```vbscript
      if (NULL != piResultingBody) return(2);

```

      // ---------- Tests the null pointers
      //
CATBody * piResultingBody = _piResultingBody;
if (NULL != piResultingBody) return(2);
      CATGeoFactory * piGeomFactory = _piGeomFactory;
```vbscript
      if (NULL == piGeomFactory ) return (1);

```

      // ---------- First limit <> Second Limit
      //
CATGeoFactory * piGeomFactory = _piGeomFactory;
if (NULL == piGeomFactory ) return (1);
      CATBody *   piFirstLimitBody =_piFirstLimitBody;
      if (NULL == piFirstLimitBody) return (1);
      CATBody *   piSecondLimitBody =_piSecondLimitBody;
      if (NULL == piSecondLimitBody) return (1);
```vbscript
```vbscript
      if (piFirstLimitBody == piSecondLimitBody) return (3);

```

```

      // ---------- Tests whether the input profile body has one domain, containing one face
      //
      // The skin body to extrude
```vbscript
if (piFirstLimitBody == piSecondLimitBody) return (3);
      CATBody * piSkinBody = _piSkinBody;
      if (NULL == piSkinBody ) return (1);
```vbscript
      if (1!= (piSkinBody->**GetNbDomains()** ))  return (1) //one domain in the body
```

      CATDomain* piShell=piSkinBody->**GetDomain**(1);       //returns the domain
      if(NULL==piShell) return(1);
```vbscript
      if (**2** != piShell->**GetLowDimension**()) return(4);    //the domain is made of faces (dim=2)
```

      long nbCells = piShell->**GetNbCellUses**();           //count of faces
      if (1!=nbCells) { return(4);}
      CATFace * piFace = (CATFace *) (piShell->GetCell(1)); // returns the face
```vbscript
      if (NULL == piFace) return(4);

```

    2. Creating a Prism with "Until" Limits A prism operator is first created with the `::CATCGMCreateTopPrism` global function.

```

           // --------- Creates the operator
             //
2. Creating a Prism with "Until" Limits A prism operator is first created with the `::CATCGMCreateTopPrism` global function.
             double offset = 0.;
             CATMathDirection direction (_direction);

             // Journal and configuration
                  // Constructs a topdata from the input
             **CATTopData** internalTopdata(*_pData);
                  // Gets the associated configuration
             **CATSoftwareConfiguration** * pConfig = internalTopdata.GetSoftwareConfiguration();
                  // To use it to create a journal that will be embedded in the created internalTopdata
             CATCGMJournalList* pJournal = new CATCGMJournalList(**pConfig** ,NULL);
                  // sets the journal for the internal operations
             internalTopdata.SetJournal(pJournal);

             // and now creates the operator
CATCGMJournalList* pJournal = new CATCGMJournalList(**pConfig** ,NULL);
internalTopdata.SetJournal(pJournal);
             CATICGMTopPrism  *pPrismOp = **::CATCGMCreateTopPrism** (piGeomFactory,

                                                           &internalTopdata,
internalTopdata.SetJournal(pJournal);
CATICGMTopPrism  *pPrismOp = **::CATCGMCreateTopPrism** (piGeomFactory,
                                                           piSkinBody,

                                                           &direction,
CATICGMTopPrism  *pPrismOp = **::CATCGMCreateTopPrism** (piGeomFactory,
piSkinBody,
                                                           offset, // non significative: the limits are defined later
                                                           offset); // non significative: the limits are defined later
```vbscript
             if (NULL==pPrismOp) return (1);

```

A specific journal is created inside the operator: in fact, this journal is needed by the algorithm of CAATopStiffener, as seen later, but not necessarily asked for by the caller. Moreover, this allows the operator to modify the input journal (if asked for) only when all its algorithm is done. The specific journal is allocated and passed to the `::CATCGMCreateTopPrism` global function within the data `internalTopData`. It is independent on the general input journal of the operator, which is stored in `_pData` at the `CATopStiffener` creation. In fact, if the journal in `_pData` is not null, `pJournal` will be copied inside it to report all the orders of the operators chain. Notice that the journal is always versioned [6] by a software configuration, retrieved from the input CATTopData. The geometry factory, the skin body to extrude and the extrusion direction are set at the `CAATopStiffener` creation. In case of "until" limits, the start and end offset are not significative: the limits are in fact tuned by the `SetLimit` method.

           // --------- Sets options
             //
             // Sets the relimiting body
             pPrismOp->**SetTrim**(piFirstLimitBody);

             // Asks for the Boolean union with the relimiting body
             pPrismOp->**SetOperation**(CatBoolUnion);

             // Asks to also retrieve the result of the Booleean operation
             pPrismOp->**SetResultMode**(TRUE);

             // Sets the until limits: first limit
pPrismOp->**SetResultMode**(TRUE);
             pPrismOp->**SetLimit**(CatLimStart,           // first limit
                                CatLimUntil,           // until option
                                TRUE ,                 // same orientation as the direction
                                offset,                // non significative (until limits)
                                piFirstLimitBody,      // the limiting geometry: here a body
                                piFirstLimitBody,      // must be the same as the previous one
                                CatPropagSingle);      // keep to this value

             // Sets the until limits: second limit
piFirstLimitBody,      // the limiting geometry: here a body
piFirstLimitBody,      // must be the same as the previous one
CatPropagSingle);      // keep to this value
             pPrismOp->SetLimit(CatLimEnd,
                                CatLimUntil,
                                TRUE ,
                                offset,
                                piSecondLimitBody,
                                piSecondLimitBody,
                                CatPropagSingle);

The prism must be delimited on one of the limiting bodies (`SetTrim`), and there must be a Boolean union operation between the delimiting body and the computed prism (`SetOperation`). Moreover, we want to recover the result of this Boolean operation (`SetResultMode` set to `TRUE`). `SetLimit` must be called for each limit (`CatLimStart`, `CATLimEnd`), to ask an "until" limit (`CatLimUntil`) on each side. Notice that each limit can have a different behavior: one limit "until", the other defined by an offset from the profile. The prism operator can now be run.

           // --------- Runs
             **CATTry**
             {
               pPrismOp ->**Run**();
             }
             **CATCatch**(CATError,error)
             {
pPrismOp ->**Run**();
               cout << (error->GetNLSMessage()).ConvertToChar() << endl;
               rc = 20;

             }
             **CATEndTry**

cout << (error->GetNLSMessage()).ConvertToChar() << endl;
rc = 20;
```vbscript
             if (rc!=0) **CAAErrorTopStif1**(rc,pJournal)

```

             // --------- Gets the resulting body
             //
```vbscript
if (rc!=0) **CAAErrorTopStif1**(rc,pJournal)
             CATBody * piMainBody1=NULL;
```vbscript
             piMainBody1 = pPrismOp->**GetBooleanResult**();

```

```

             // gets the prism before the union
CATBody * piMainBody1=NULL;
piMainBody1 = pPrismOp->**GetBooleanResult**();
             CATBody * piWithoutOperation = pPrismOp->**GetResult**();

             // gets the journal of the boolean operation
CATBody * piWithoutOperation = pPrismOp->**GetResult**();
             CATCGMJournalList * pBooleanJournal = pPrismOp->**GetBooleanJournal**();

             if (NULL==piMainBody1 || NULL==pBooleanJournal || NULL==piWithoutOperation)

             {
CATCGMJournalList * pBooleanJournal = pPrismOp->**GetBooleanJournal**();
if (NULL==piMainBody1 || NULL==pBooleanJournal || NULL==piWithoutOperation)
               rc = 20;

               **CAAErrorTopStif2**(rc,pJournal,piGeomFactory,pPrismOp,piMainBody1,piWithoutOperation)
             }

rc = 20;
As the `Run` method can throw errors, these are caught by the macros `CATTry`, `CATCatch`, `CATEndTry`. The `CAAErrorTopStifx` macros are defined in the use case to clean the model in case of return: they free the allocations and delete the intermediate created bodies and geometry, but are not detailed in this article. The `GetResult` method returns the prism before its union with the limiting bodies, while the `GetBooleanResult` returns the body corresponding to the result after the union. In the same way, `pJournal` contains the modifications corresponding to the prism creation, whereas `GetBooleanJournal` returns a new created journal containing the modifications relative to the Boolean operation.
    3. Searching for the Long Side of the Profile In order to recover the faces on which circles have been drawn on Fig. 1, we first search the longest edge of the face of `SkinBody`.

           // Creates the boundary iterator on the edge of the initial face (of the skin to extrude)
As the `Run` method can throw errors, these are caught by the macros `CATTry`, `CATCatch`, `CATEndTry`. The `CAAErrorTopStifx` macros are defined in the use case to clean the model in case of return: they free the allocations and delete the intermediate created bodies and geometry, but are not detailed in this article. The `GetResult` method returns the prism before its union with the limiting bodies, while the `GetBooleanResult` returns the body corresponding to the result after the union. In the same way, `pJournal` contains the modifications corresponding to the prism creation, whereas `GetBooleanJournal` returns a new created journal containing the modifications relative to the Boolean operation.
3. Searching for the Long Side of the Profile In order to recover the faces on which circles have been drawn on Fig. 1, we first search the longest edge of the face of `SkinBody`.
             CATBoundaryIterator  *  pBoundaryIt =  piFace->**CreateBoundaryIterator**();
```vbscript
             if (NULL==pBoundaryIt)

```

             {
CATBoundaryIterator  *  pBoundaryIt =  piFace->**CreateBoundaryIterator**();
if (NULL==pBoundaryIt)
           	  rc =1;
               CAAErrorTopStif2(...)

             }
             // Computes the length of an edge
rc =1;
CAAErrorTopStif2(...)
             CATSide side;
             CATCell*  piE1 = pBoundaryIt->**Next**(&side,NULL);
```vbscript
             if (NULL==piE1)

```

             {
CATSide side;
CATCell*  piE1 = pBoundaryIt->**Next**(&side,NULL);
if (NULL==piE1)
               rc =1;
               CAAErrorTopStif3(...)

             }
```vbscript
if (NULL==piE1)
rc =1;
CAAErrorTopStif3(...)
             double l1= ((CATEdge * )piE1 )->**CalcLength**();

```

             // Computes the length of the next  edge
```vbscript
CAAErrorTopStif3(...)
double l1= ((CATEdge * )piE1 )->**CalcLength**();
             CATCell*  piE2 = pBoundaryIt->Next(&side,NULL);
             if (NULL==piE2)
```

             {
CATCell*  piE2 = pBoundaryIt->Next(&side,NULL);
if (NULL==piE2)
               rc =1;
               CAAErrorTopStif3(...)

             }
```vbscript
if (NULL==piE2)
rc =1;
CAAErrorTopStif3(...)
             double l2=((CATEdge * )piE2)->CalcLength();

```

             // Defines the width and the height according to l1 and l2 values.
```vbscript
CAAErrorTopStif3(...)
double l2=((CATEdge * )piE2)->CalcLength();
             double height=0;
             double width=0;

             CATCell * piHeight1 = NULL, *piHeight2 = NULL, *piWidth1 = NULL, *piWidth2 = NULL;
             if ( l1 < l2 )
```

             {
double width=0;
CATCell * piHeight1 = NULL, *piHeight2 = NULL, *piWidth1 = NULL, *piWidth2 = NULL;
if ( l1 < l2 )
               height    = l2;
               piHeight1 = piE2;
               piWidth1  = piE1;
               width     = l1;
               piWidth2  = pBoundaryIt->Next(&side,NULL);
```vbscript
```vbscript
               piHeight2 = pBoundaryIt->Next(&side,NULL);

```

```

             }
width     = l1;
piWidth2  = pBoundaryIt->Next(&side,NULL);
```vbscript
piHeight2 = pBoundaryIt->Next(&side,NULL);
```

             else

             {
piHeight2 = pBoundaryIt->Next(&side,NULL);
else
               height    = l1;
               piHeight1 = piE1;
               piWidth1  = piE2;
               width     = l2;
               piHeight2 = pBoundaryIt->Next(&side,NULL);
```vbscript
```vbscript
               piWidth2  = pBoundaryIt->Next(&side,NULL);

```

```

             }

             **delete** pBoundaryIt;
piHeight2 = pBoundaryIt->Next(&side,NULL);
```vbscript
piWidth2  = pBoundaryIt->Next(&side,NULL);
```

             pBoundaryIt=NULL;

This edge could also be put as an input argument, or with a `SetXxx` method to the operator! Here, this gives us the opportunity to use a `CATBoundaryIterator` class to retrieve the edges of a face. The iterator is created by the `CATCell::CreateBoundaryIterator` and skips from one boundary cell to the other one with the `CATBoundaryIterator::Next` method. The approximate length of an edge is computed with the `CATEdge::CalcLength` method. After comparing the lengths of the first two edges, we can easily deduce the two long sides, as the profile is rectangular. The written code is not generic: by assumption, the face is rectangular.
    4. Searching Inside the Journal for the Bottom Face of the Prism The topological journal is made of `CATCGMJournalItem` (unitary order) and `CATCGMJournalList` (list of items). Each item has a type such as:

       * Creation: a new cell appears in the resulting body, built from an (optional) set of cells of the input body.
       * Modification: the cell that is used does not appear in the resulting body, and is replaced by a new one.
       * Deletion: the cell disappears in the resulting body.
This edge could also be put as an input argument, or with a `SetXxx` method to the operator! Here, this gives us the opportunity to use a `CATBoundaryIterator` class to retrieve the edges of a face. The iterator is created by the `CATCell::CreateBoundaryIterator` and skips from one boundary cell to the other one with the `CATBoundaryIterator::Next` method. The approximate length of an edge is computed with the `CATEdge::CalcLength` method. After comparing the lengths of the first two edges, we can easily deduce the two long sides, as the profile is rectangular. The written code is not generic: by assumption, the face is rectangular.
4. Searching Inside the Journal for the Bottom Face of the Prism The topological journal is made of `CATCGMJournalItem` (unitary order) and `CATCGMJournalList` (list of items). Each item has a type such as:
To explore the topological journal, high level methods are provided, such as `FindFirsts` and `FindLasts`, that recursively scan the journal to retrieve:

       * `FindFirsts`: all the faces at the higher level (the earliest in the journal ) that lead to the definition of a given cell.
       * `FindLasts`: all the faces at the lower level (the latest in the journal) which definition depends on a given cell.
These methods can scan along a type of item, or several types (see the `ThroughCreateAndModify` value).  Example: Let the following journal sequence: `F1 -> F2 -> F3 -> F4 -> F5`:
       * `F1` created
       * `F2` modified from `F1`
       * `F3` modified from `F2`
       * `F4` modified from `F3`
       * `F5` modified from `F4`
`FindFirsts` from `F3` gives `F1`, and `FindLasts` from `F3` gives `F5`.

    //  Retrieves all the objects created or modified from piHeight1
      //  first, in pJournal
      CATLISTP(CATGeometry) pFaces;
```vbscript
CATLISTP(CATGeometry) pFaces;
      pJournal->**FindLasts** (piHeight1,pFaces,**ThroughCreateAndModify**);

      CATFace * piFromHeight1=NULL;
      int nbresult = pFaces.Size();

```

      // Retrieves the object that is a face.
CATFace * piFromHeight1=NULL;
int nbresult = pFaces.Size();
```vbscript
      for (int i=1 ; (i <= nbresult) && (piFromHeight1 == NULL) ; i++)

```

      {
int nbresult = pFaces.Size();
for (int i=1 ; (i <= nbresult) && (piFromHeight1 == NULL) ; i++)
```vbscript
```vbscript
    	 if (pFaces[i]->IsATypeOf(CATFaceType)) { piFromHeight1=(CATFace *)pFaces[i];}

```

```

      }

      //  now, in pBooleanJournal
```vbscript
if (pFaces[i]->IsATypeOf(CATFaceType)) { piFromHeight1=(CATFace *)pFaces[i];}
      pFaces.**RemoveAll**();                       // voids the list before a new use
      pBooleanJournal->**FindLasts** (piFromHeight1,pFaces,**ThroughModify**);
      CATFace * piBooleanFromHeight1=NULL;
```vbscript
      nbresult = pFaces.Size();

```

```

      // Retrieves the object that is a face.
pBooleanJournal->**FindLasts** (piFromHeight1,pFaces,**ThroughModify**);
CATFace * piBooleanFromHeight1=NULL;
nbresult = pFaces.Size();
```vbscript
```vbscript
      for (i=1 ; (i <= nbresult) && (piBooleanFromHeight1 == NULL) ; i++)

```

```

      {
```vbscript
nbresult = pFaces.Size();
```vbscript
```vbscript
for (i=1 ; (i <= nbresult) && (piBooleanFromHeight1 == NULL) ; i++)
    	 if (pFaces[i]->IsATypeOf(CATFaceType))	 { piBooleanFromHeight1=(CATFace *)pFaces[i];}
```

```

```

      }

```vbscript
for (i=1 ; (i <= nbresult) && (piBooleanFromHeight1 == NULL) ; i++)
```vbscript
```vbscript
if (pFaces[i]->IsATypeOf(CATFaceType))	 { piBooleanFromHeight1=(CATFace *)pFaces[i];}
      if (NULL==piBooleanFromHeight1)
```

```

```

      {
```vbscript
if (pFaces[i]->IsATypeOf(CATFaceType))	 { piBooleanFromHeight1=(CATFace *)pFaces[i];}
```vbscript
if (NULL==piBooleanFromHeight1)
```

        rc =21;
        CAAErrorTopStif3(...)
```

      }

rc =21;
CAAErrorTopStif3(...)
Fig. 2: The Journal and Boolean Journal of CATICGMTopPrism ![CATICGMTopPrism Journal and Boolean Journal](images/CAACgmTopJournal2.gif)

       * In the journal relative to the prism creation, `FindLasts` finds the cell `FromHeight1` resulting from `Height1`. The `ThroughCreateAndModify` option indicates that the search is done among the creation and modification items. At this stage, the cells are already delimited on the limiting body, but not glued.
       * In the journal relative to the Boolean union, `FindLasts` finds the cell `BooleanFromHeight1` from `FromHeight1`. This cell is the cell on which `CAATopStifferner` creates a circle. The `ThroughModify` option indicates that the search is done among the modification items only. After the Boolean operation, the prism and the limiting bodies are glued.
---|---
    5. Creating a Circle on the Underlying Surface of the Face

           // Gets the surface of the face
5. Creating a Circle on the Underlying Surface of the Face
             CATOrientation orientation;
             CATSurface * piSurfaceFromHeight = piBooleanFromHeight1->**GetSurface**(&orientation);
```vbscript
             if (NULL==piSurfaceFromHeight)

```

             {
CATOrientation orientation;
CATSurface * piSurfaceFromHeight = piBooleanFromHeight1->**GetSurface**(&orientation);
if (NULL==piSurfaceFromHeight)
               rc =1;
               CAAErrorTopStif3(...)

             }

rc =1;
CAAErrorTopStif3(...)
            _// Estimates the center of the face_
             CATSurParam centerParam;
             piFromHeight1->**EstimateCenterParam** (centerParam);

             // Creates a circle on the surface
_// Estimates the center of the face_
CATSurParam centerParam;
piFromHeight1->**EstimateCenterParam** (centerParam);
             CATPCircle * piPCircle1 = piGeomFactory -> **CreatePCircle**( height/3.,
                                                                       centerParam,
                                                                       piSurfaceFromHeight);
```vbscript
             if (NULL==piPCircle1)

```

             {
CATPCircle * piPCircle1 = piGeomFactory -> **CreatePCircle**( height/3.,
centerParam,
piSurfaceFromHeight);
if (NULL==piPCircle1)
               rc =1;
               CAAErrorTopStif3(...)

             }

rc =1;
CAAErrorTopStif3(...)
The surface is retrieved with the `CATFace::GetSurface` method. The center of the circle is put at the "center" of the face, which is only an approximate point. The created circle is a `CATPCircle`, because it is a circle in the space of the surface. The way to define a circle on the other face is similar and not detailed here.
    6. Searching Inside the Journal for the Face of the Upper Wing On must first define one journal of the two operations: the prism creation (`pJournal`) and the Boolean operation (`pBooleanJournal`).

           // Copies in a single journal and deletes the unused body
The surface is retrieved with the `CATFace::GetSurface` method. The center of the circle is put at the "center" of the face, which is only an approximate point. The created circle is a `CATPCircle`, because it is a circle in the space of the surface. The way to define a circle on the other face is similar and not detailed here.
6. Searching Inside the Journal for the Face of the Upper Wing On must first define one journal of the two operations: the prism creation (`pJournal`) and the Boolean operation (`pBooleanJournal`).
             pBooleanJournal-> **Duplicate**(pJournal);
             piGeomFactory->**Remove**(piWithoutOperation,**pJournal**);
             piWithoutOperation=NULL;

`pBooleanJournal` is duplicated in `pJournal`. `pBooleanJournal` will be directly deleted at the `CATICGMTopPrism` deletion, while `Journal` now contains all the items of both operations. Then, the prism before union is removed with the `Remove` method of `CATICGMContainer`, with the journal as input: in this case all deletion items will be logged if necessary. Now, the face of the wing is searched for: this face has been modified by the Boolean operation: a hole is created. The word "modified" is a shorter way to tell that in the resulting body, a new face is created with a hole corresponding to the trace of the prism.

piGeomFactory->**Remove**(piWithoutOperation,**pJournal**);
piWithoutOperation=NULL;
           CATLISTP(CATCell) listCells;
             piFirstLimitBody->GetAllCells(listCells,2);  // gets all the faces of FirstlimitBody
```vbscript
             nbCells = listCells.Size();

```

             CATFace * piFromBody1=NULL;
             int iok=0;
```vbscript
             for (i=1;(i <= nbCells)  ;i++)

```

             {
CATFace * piFromBody1=NULL;
int iok=0;
for (i=1;(i <= nbCells)  ;i++)
               pFaces.**RemoveAll**();                          // voids the list
               pBooleanJournal -> **FindLasts** (listCells[i],pFaces,ThroughModify);
               nbresult = pFaces.Size();
```vbscript
```vbscript
               for (int j=1; (j <= nbresult) && (piFromBody1 == NULL) ; j++)

```

```

               {
pBooleanJournal -> **FindLasts** (listCells[i],pFaces,ThroughModify);
nbresult = pFaces.Size();
```vbscript
```vbscript
for (int j=1; (j <= nbresult) && (piFromBody1 == NULL) ; j++)
                 if (pFaces[j]->IsATypeOf(CATFaceType)     // searches for a face

```

```

                     && **pFaces[j] != listCells[i]** )        // different from the initial one
                 {
```vbscript
if (pFaces[j]->IsATypeOf(CATFaceType)     // searches for a face
                   piFromBody1=(CATFace *)pFaces[j];
                   iok = iok + 1;
```

                 }
               }
             }
piFromBody1=(CATFace *)pFaces[j];
iok = iok + 1;
```vbscript
             if (1!=iok)

```

             {
```vbscript
if (1!=iok)
               rc=30;
               CAAErrorTopStif5(...)
```

             }

             // ---------- Releases the operator
rc=30;
CAAErrorTopStif5(...)
             pPrismOp->Release();
             pPrismOp = NULL;

Fig. 3: Use of the Boolean Journal to Recover the Upper Wing ![Boolean Journal](images/CAACgmTopJournal3.gif)

       * All the faces of `FirstLimitBody` are first got. For each face `listCells[i]`, `FindLasts` searches for a cell resulting from a modification of `listCells[i]`. The resulting cells are put in the list `pFaces`, that is first cleaned (`RemoveAll`). `FindLasts` does never return a void `pFaces` list. If it does not find any solution, it returns the initial face `listCells[i]`. It is the reason why the returned solutions must be compared to the initial face.
---|---
    7. Filleting A filleting operation is defined by affecting a (possibly variable) radius to edges:
       * The definition of the radius law is contained in the `CATDynFilletRadius` object: in the use case, the radius is chosen constant along the edges.
       * The definition of the edges to fillet according to a given radius law is called ribbon and managed by the `CATDynFilletRibbon` object: there can be several ribbons in one fillet operation, but in the use case, only one is defined.

7. Filleting A filleting operation is defined by affecting a (possibly variable) radius to edges:
    CATDynFilletRadius * pRadius = new **CATDynFilletRadius**(
              5.,    // radius value
              NULL,  // the cell on which the radius is defined (for variable radius)
              NULL,  // The ratio of the edge length defining the point (for variable radius)
              NULL); // must be kept to NULL
```vbscript
      if (NULL==pRadius)

```

      {
NULL,  // the cell on which the radius is defined (for variable radius)
NULL,  // The ratio of the edge length defining the point (for variable radius)
NULL); // must be kept to NULL
if (NULL==pRadius)
        rc=1;
        CAAErrorTopStif5(...)

      }

rc=1;
CAAErrorTopStif5(...)
```vbscript
      CATLISTP(CATDynFilletRadius)	listRadius;
```

      listRadius.Append(pRadius);

Now, the ribbon is defined.

    //---- first edge to fillet
listRadius.Append(pRadius);
Now, the ribbon is defined.
      listCells.RemoveAll();
      piFromBody1->**GetCommonBorderCells**( piBooleanFromHeight1,     // the other face
                                         1,                        // must be put to 1
                                         listCells,                // the common cells
                                         1);                       // edge (dimension 1)
```vbscript
      if (1!=listCells.Size() )

```

      {
1,                        // must be put to 1
listCells,                // the common cells
1);                       // edge (dimension 1)
if (1!=listCells.Size() )
        rc=10;
        CAAErrorTopStif6(...)

      }
```vbscript
if (1!=listCells.Size() )
rc=10;
CAAErrorTopStif6(...)
```vbscript
      CATLISTP(CATEdge) listEdges;
```

      listEdges.Append((CATEdge *)(listCells[1]));

```

      //---- second edge to fillet
```vbscript
CATLISTP(CATEdge) listEdges;
listEdges.Append((CATEdge *)(listCells[1]));
      listCells.RemoveAll();
      piFromBody1->GetCommonBorderCells( piBooleanFromHeight2,     // the other face
                                         1,                        // must be put to 1
                                         listCells,                // the common cells
                                         1);                       // edge (dimension 1)
      if (1!=listCells.Size() )
```

      {
1,                        // must be put to 1
listCells,                // the common cells
1);                       // edge (dimension 1)
if (1!=listCells.Size() )
        rc=10;
        CAAErrorTopStif6(...)

      }
```vbscript
if (1!=listCells.Size() )
rc=10;
CAAErrorTopStif6(...)
      listEdges.Append((CATEdge *)(listCells[1]));

```

      //---- the ribbon
```vbscript
CAAErrorTopStif6(...)
listEdges.Append((CATEdge *)(listCells[1]));
      CATDynEdgeFilletRibbon * pRibbon = new **CATDynEdgeFilletRibbon**(listEdges, listRadius);
      if (NULL==pRibbon)
```

      {
CATDynEdgeFilletRibbon * pRibbon = new **CATDynEdgeFilletRibbon**(listEdges, listRadius);
if (NULL==pRibbon)
        rc=1;
        CAAErrorTopStif6(...)

      }

      //---- trim option
rc=1;
CAAErrorTopStif6(...)
      pRibbon ->**SetSegmentationMode**(CATDynTrim);

The edges to fillet are common (`GetCommonBorderCells`) to the face with hole `FromBody1` and the faces of the prism `BooleanFromHeight1` and `BooleanFromHeight2`. These non connected edges are appended to the list used to define the ribbon. The `CATDynFilletRibbon::SetSegmentationMode` option indicates that the computed ribbon must be delimited on the main body. The CATICGMDynFillet operator can now be created.

    // ----------- Creates the operator
      //
The edges to fillet are common (`GetCommonBorderCells`) to the face with hole `FromBody1` and the faces of the prism `BooleanFromHeight1` and `BooleanFromHeight2`. These non connected edges are appended to the list used to define the ribbon. The `CATDynFilletRibbon::SetSegmentationMode` option indicates that the computed ribbon must be delimited on the main body. The CATICGMDynFillet operator can now be created.
      CATICGMDynFillet * pFilletOp = **::CATCGMCreateDynFillet**(piGeomFactory,&internalTopdata,piMainBody1,**pJournal**);
```vbscript
      if (NULL==pFilletOp)

```

      {
CATICGMDynFillet * pFilletOp = **::CATCGMCreateDynFillet**(piGeomFactory,&internalTopdata,piMainBody1,**pJournal**);
if (NULL==pFilletOp)
        rc=1;
        CAAErrorTopStif7(...)

      }

      //---- Appends the ribbon
rc=1;
CAAErrorTopStif7(...)
      pFilletOp ->**Append**(pRibbon);

      //---- Runs
pFilletOp ->**Append**(pRibbon);
      CATTry

      {
pFilletOp ->**Append**(pRibbon);
CATTry
        pFilletOp ->**Run**();

      }
CATTry
pFilletOp ->**Run**();
      CATCatch(CATError,error)

      {
pFilletOp ->**Run**();
CATCatch(CATError,error)
        cout << (error->GetNLSMessage()).ConvertToChar() << endl;
        rc=20;
        CAAErrorTopStif7(...)

      }
cout << (error->GetNLSMessage()).ConvertToChar() << endl;
rc=20;
CAAErrorTopStif7(...)
      CATEndTry

      //---- Gets the resulting body
```vbscript
CAAErrorTopStif7(...)
CATEndTry
      CATBody * piMainBody2  = pFilletOp->**GetResult**();

      if (NULL==piMainBody2)
```

      {
CATBody * piMainBody2  = pFilletOp->**GetResult**();
if (NULL==piMainBody2)
        rc=1;
        CAAErrorTopStif7(...)

      }

      //---- Deletes the operator
rc=1;
CAAErrorTopStif7(...)
      pFilletOp->Release();
      pFilletOp = NULL;

      if (NULL != pRadius) delete pRadius;
      pRadius = NULL;
      if (NULL != pRibbon) delete pRibbon;
      pRibbon = NULL;

      //---- Deletes the unused body
pRadius = NULL;
if (NULL != pRibbon) delete pRibbon;
pRibbon = NULL;
       piGeomFactory->**Remove**(piMainBody1,**pJournal**);
      _piResultingBody = piMainBody2;

Notice the general scheme of the operator. To use it:

       * Create it.
       * Set the options: here, the ribbon to fillet.
       * Run it.
       * Get the result.
       * Delete it.
`pJournal` is re-used here, so that the filleting operator directly puts its items inside it: at the end of the operation, `pJournal` contains the items of the prism creation, the Boolean operation and the filleting operation. In the same way, the `GetResult` method retrieves `MainBody2`, the body representing the result of the three operations. `MainBody1` is now useless, and is removed by the factory: the items corresponding to this deletion are put in `pJournal`, as argument of the `Remove` method.
    8. Returning the Journal of the Operator

           // Fills the output journal if needed
8. Returning the Journal of the Operator
             CATCGMJournalList * pDataJournal = NULL;
             pDataJournal=_pData->GetJournal();
```vbscript
```vbscript
             if (NULL!= pDataJournal)

```

```

             {
CATCGMJournalList * pDataJournal = NULL;
pDataJournal=_pData->GetJournal();
```vbscript
if (NULL!= pDataJournal)
```

               pJournal->Duplicate(pDataJournal);  // duplicates the internal journal inside the input journal

             }
pDataJournal=_pData->GetJournal();
```vbscript
if (NULL!= pDataJournal)
```

pJournal->Duplicate(pDataJournal);  // duplicates the internal journal inside the input journal
             delete pJournal;                      // deletes the internal journal

As seen in step 2, `pJournal` was internally allocated to contain the items of the prism, Boolean union and filleting operations. If the caller of `CAATopStiffener` operator asks for the report of the modifications, the items must be copied inside the journal allocated by the caller, which address is stored in ` _pData`. `pJournal` can then be deallocated.
CAATopJournal: Use of the New Class To use the new operator, one must go through the following steps:

    * Creating the Geometry Factory
    * Creating the Limiting Bodies
    * Creating the Skin Body to Extrude
    * Running the New Operator
    * Writing the Model and Closes the Container
    1. Creating the Geometry Factory The geometry factory (`CATGeoFactory`) creates and manages all the `CATICGMObject`: it creates the points, curves, surfaces, and bodies, and removes them [7]. The `CATGeoFactory` creation itself is done by the global function `::CATCreateCGMContainer`. Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.

1. Creating the Geometry Factory The geometry factory (`CATGeoFactory`) creates and manages all the `CATICGMObject`: it creates the points, curves, surfaces, and bodies, and removes them [7]. The `CATGeoFactory` creation itself is done by the global function `::CATCreateCGMContainer`. Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.
           CATGeoFactory* piGeomFactory = **::CATCreateCGMContainer**() ;
```vbscript
           if (NULL==piGeomFactory) return (1);

```

    2. Creating the Limiting Bodies These bodies are defined as a cylinder skin body extruded along a direction. To create them, one must

       * Create the geometric cylinder.
       * Define a skin body.
       * Extrude the skin body.

2. Creating the Limiting Bodies These bodies are defined as a cylinder skin body extruded along a direction. To create them, one must
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

```vbscript
    if (NULL == piCylinder1)

```

    {
      ::CATCloseCGMContainer(piGeomFactory);
(axis1,radius,axisStart,axisEnd,angleStart,angleEnd);
if (NULL == piCylinder1)
```vbscript
      return (1);

```

    }

A geometric object as a cylinder is created by the `CATGeoFactory`. `axisStart` and `axisEnd` define the limitation of the surface along the cylinder axis, `angleStart` and `angleEnd` define the limitation around the axis cylinder. The angle are measured in radians, `CATPI` and other related values are defined in `CATMathConstant.h`.

    // Creates a skin body
    // first defines an open configuration for the operator
A geometric object as a cylinder is created by the `CATGeoFactory`. `axisStart` and `axisEnd` define the limitation of the surface along the cylinder axis, `angleStart` and `angleEnd` define the limitation around the axis cylinder. The angle are measured in radians, `CATPI` and other related values are defined in `CATMathConstant.h`.
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();

    // defines the data of the operator: configuration + journal
CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    CATTopData topdata(pConfig,NULL);  // an open configuration and a NULL journal

    // defines the limits to take into account
CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
CATTopData topdata(pConfig,NULL);  // an open configuration and a NULL journal
    CATSurLimits limits;
    piCylinder1->GetLimits(limits);

    // now creates the operator
CATTopData topdata(pConfig,NULL);  // an open configuration and a NULL journal
CATSurLimits limits;
piCylinder1->GetLimits(limits);
    CATICGMTopSkin * pSkinOp = **::CATCGMCreateTopSkin**(piGeomFactory,&topdata,piCylinder1,&limits);
```vbscript
    if (NULL==pSkinOp)

```

    {
      ::CATCloseCGMContainer(piGeomFactory);
CATICGMTopSkin * pSkinOp = **::CATCGMCreateTopSkin**(piGeomFactory,&topdata,piCylinder1,&limits);
if (NULL==pSkinOp)
```vbscript
      return (1);

```

    }

    // Runs
    pSkinOp->**Run**();

    // Gets the resulting body
pSkinOp->**Run**();
    CATBody * piFirstCylinderBody = pSkinOp->**GetResult**();
```vbscript
    if (NULL==piFirstCylinderBody)

```

    {
      ::CATCloseCGMContainer(piGeomFactory);
CATBody * piFirstCylinderBody = pSkinOp->**GetResult**();
if (NULL==piFirstCylinderBody)
```vbscript
      return (1);

```

    }

    // Releases the operator
return (1);
      pSkinOp ->Release();
      pSkinOp = NULL;

The operator configuration is the level of software you want to use to run this operator. By default, define an open configuration as in this use case to run with the current level. Moreover here, the pointer to the journal is set to `NULL` in the operator data. So that the journal is not filled. The configuration must be released after use. Here, it is released after the call to the last operator.  `CATICGMTopSkin` can create a skin body from a list a curves on surface, or directly on the boundaries of a surface. Here the surface is the limited cylinder. `CATICGMTopSkin` is invoked according to the general scheme, that:

       * Creates with the global function `CATCGMCreateTopSkin`
       * Runs
       * Gets the resulting skin body. This body is created in the `CATICGMTopSkin` by the `CATGeoFactory`, that manages the life cycle of the CGM objects: in fact, if you want to delete the created body, call the ` CATICGMContainer::Remove` method with the `CATICGMContainer::RemoveDependancies` option.
       * Deletes.
The operator configuration is the level of software you want to use to run this operator. By default, define an open configuration as in this use case to run with the current level. Moreover here, the pointer to the journal is set to `NULL` in the operator data. So that the journal is not filled. The configuration must be released after use. Here, it is released after the call to the last operator.  `CATICGMTopSkin` can create a skin body from a list a curves on surface, or directly on the boundaries of a surface. Here the surface is the limited cylinder. `CATICGMTopSkin` is invoked according to the general scheme, that:
The created `SkinBody` is now extruded to create a prism with `CATICGMTopPrism`.

    CATCGMJournalList * pJournal = NULL;

    CATICGMTopPrism  *pPrismOp = **::CATCGMCreateTopPrism** (piGeomFactory,

                                                  &topdata,
CATCGMJournalList * pJournal = NULL;
CATICGMTopPrism  *pPrismOp = **::CATCGMCreateTopPrism** (piGeomFactory,
                                                  piFirstCylinderBody,

                                                  &z,
CATICGMTopPrism  *pPrismOp = **::CATCGMCreateTopPrism** (piGeomFactory,
piFirstCylinderBody,
                                                  0.,               // limit1
                                                  2.,               // limit2
                                                  pJournal);
```vbscript
    if (NULL==pPrismOp)

```

    {
      ::CATCloseCGMContainer(piGeomFactory);
2.,               // limit2
pJournal);
if (NULL==pPrismOp)
```vbscript
      return (1);

```

    }

return (1);
    pPrismOp->**Run**();
    CATBody* piFirstLimitBody = pPrismOp->**GetResult**();
```vbscript
    if (NULL==piFirstLimitBody)

```

    {
      ::CATCloseCGMContainer(piGeomFactory);
pPrismOp->**Run**();
CATBody* piFirstLimitBody = pPrismOp->**GetResult**();
if (NULL==piFirstLimitBody)
```vbscript
      return (1);

```

    }
```vbscript
if (NULL==piFirstLimitBody)
```vbscript
return (1);
```

      pPrismOp->Release();
      pPrismOp= NULL;

Once again, the same steps are used, that:
```

       * Creates (with the corresponding `::CATCGMCreateTopPrism` global function) by declaring the body to extrude (`SkinBody`), the direction of the extrusion, the start and end limits of the prism from `SkinBody`
       * Runs
       * Gets the resulting body (`MainBody1`). This body is created in `CATICGMTopPrism` by the `CATGeoFactory`, that manages the life cycle of the CGM objects: in fact, if you want to delete the created body, call the `CATICGMContainer::Remove` method with the `CATICGMContainer::RemoveDependancies` option.
       * Releases the operator.
Once again, the same steps are used, that:
As the body to extrude is a skin body, `FirstLimitBody` is a volume body. If the body to extrude were a wire body, the result would be a skin body. Other types of prism operations can be described, especially "until" operations: the limits of the prism are reached when encountering another body. This is detailed in the  `CAAGMOperatorsJournal` section. The other limiting body is created in the same way, and this is not detailed here.
    3. Creating the Skin Body to Extrude The cylinder skin body was created using a surface, here the skin body is defined by giving a list of four segments on a geometric plane.

           CATPlane * piPlane = piGeomFactory->**CreatePlane**(CATMathOIJ);	// Geometrical plan
```vbscript
           if (NULL == piPlane)

```

           {
             ::CATCloseCGMContainer(piGeomFactory);
CATPlane * piPlane = piGeomFactory->**CreatePlane**(CATMathOIJ);	// Geometrical plan
if (NULL == piPlane)
```vbscript
             return (1);

```

           }

return (1);
           CATMathPoint mathOrigin;
           CATMathDirection mathU, mathV;

           // ----------- Retrieves the mathematical definition of the geometrical plane
CATMathPoint mathOrigin;
CATMathDirection mathU, mathV;
           piPlane->GetAxis(mathOrigin,mathU,mathV);

           // ----------- Defines points on the plane
           // Notice that we do not make any assumption on the plane parameterization.
           // The use of GetParam is allowed here, because the 3D points belong to the plane
           // by construction
           CATSurParam p1, p2, p3, p4;

CATSurParam p1, p2, p3, p4;
           piPlane->GetParam(mathOrigin - 20*mathU - 5*mathV , p1);
           piPlane->GetParam(mathOrigin + 20*mathU - 5*mathV , p2);
           piPlane->GetParam(mathOrigin + 20*mathU + 5*mathV , p3);
           piPlane->GetParam(mathOrigin - 20*mathU + 5*mathV , p4);

           // ----------- Defines the curves of the profile
piPlane->GetParam(mathOrigin + 20*mathU - 5*mathV , p2);
piPlane->GetParam(mathOrigin + 20*mathU + 5*mathV , p3);
piPlane->GetParam(mathOrigin - 20*mathU + 5*mathV , p4);
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

```vbscript
           for (int i=0; i<nbPCurves; i++)

```

           {
aPCurves[3]=  piGeomFactory->CreatePLine (p4, p1, piPlane );
aPCurves[3] ->GetLimits(aLimits[3]);
for (int i=0; i<nbPCurves; i++)
```vbscript
```vbscript
             if (NULL==aPCurves[i])

```

```

             {
               ::CATCloseCGMContainer(piGeomFactory);
```vbscript
for (int i=0; i<nbPCurves; i++)
```vbscript
if (NULL==aPCurves[i])
               return (1);
```

```

             }
           }

           // Defines the orientations of the curves
           // This is needed by the CATICGMTopSkin
           // Notice that in a more general case (use of circle for example),
           // you must test the start and end as in CAATopOverview.

           aOrientations[0] = 1;
           aOrientations[1] = 1;
           aOrientations[2] = 1;
           aOrientations[3] = 1;

No assumption can be done on the parameterization of the geometric objects. The parameters on the plane are evaluated with the `CATSurface::GetParam` method, from 3D points that are known to be on the plane. This method can be called because the plane is a canonical object, and the points are already on it. If one of these conditions were not filled, it would be mandatory to call the `CATICGMProjectionPtSur` geometric operator. `CATICGMTopSkin` needs:

       * An ordered list of curves: contiguous curves must be contiguous in the list. The limits to take into account for each curve must be detailed. In the `CAAGMOperatorsJournal` case, the intersection between the lines and circles are defined by construction, but if it were not the case, they would be computed with the `CATICGMIntersectionCrvCrv` geometric operator.
       * The orientation of each curve in the profile: the curve must be taken in its natural orientation (increasing parameter, +1 value) or in the opposite orientation (decreasing parameter, -1 value), such that the end (after orientation) of a curve must be linked to the beginning (after orientation) of the next curve. As defined here, all the curves must be taken in their natural orientation. It would not be the case if circles or other curves were used. See an example in the `CAAGMOperatorsOverview` use case [3].

    // Creates the operator
No assumption can be done on the parameterization of the geometric objects. The parameters on the plane are evaluated with the `CATSurface::GetParam` method, from 3D points that are known to be on the plane. This method can be called because the plane is a canonical object, and the points are already on it. If one of these conditions were not filled, it would be mandatory to call the `CATICGMProjectionPtSur` geometric operator. `CATICGMTopSkin` needs:
```vbscript
    pSkinOp = **CATCGMCreateTopSkin** (piGeomFactory,

```

                                &topdata,
pSkinOp = **CATCGMCreateTopSkin** (piGeomFactory,
                                nbPCurves,
                                aPCurves,
                                aLimits,
                                aOrientations);
```vbscript
    if (NULL==pSkinOp)

```

    {
       ::CATCloseCGMContainer(piGeomFactory);
aLimits,
aOrientations);
if (NULL==pSkinOp)
```vbscript
       return (1);

```

    }

    // Runs
    pSkinOp->**Run**();

    // Gets the resulting body
pSkinOp->**Run**();
    CATBody * piSkinBody = pSkinOp->**GetResult**();
```vbscript
    if (NULL==piSkinBody)

```

    {
      ::CATCloseCGMContainer(piGeomFactory);
CATBody * piSkinBody = pSkinOp->**GetResult**();
if (NULL==piSkinBody)
```vbscript
      return (1);

```

    }

    // Releases the operator
return (1);
    pSkinOp->Release();
    pSkinOp = NULL;

    4. Running the New Operator

           //--- Creates the operator
pSkinOp = NULL;
4. Running the New Operator
           CAATopStiffener *pStiffOp = new **CAATopStiffener** (piGeomFactory,

                                                            &topdata,
4. Running the New Operator
CAATopStiffener *pStiffOp = new **CAATopStiffener** (piGeomFactory,
                                                            piFirstLimitBody,
                                                            piSecondLimitBody,
                                                            piSkinBody,
                                                            z,
                                                            pJournal);
```vbscript
           if (NULL==pStiffOp)

```

           {
             ::CATCloseCGMContainer(piGeomFactory);
z,
pJournal);
if (NULL==pStiffOp)
```vbscript
             return (1);

```

           }

           //--- Runs
return (1);
```vbscript
```vbscript
           rc = pStiffOp->**Run**();
           if (NUL!=rc)

```

```

           {
             ::CATCloseCGMContainer(piGeomFactory);
rc = pStiffOp->**Run**();
```vbscript
if (NUL!=rc)
             return (rc);

```

           }

           //--- Gets the resulting body
return (rc);
           CATBody * piMainBody1=NULL;
           piMainBody1 = pStiffOp->**GetResult**();
```vbscript
```vbscript
           if (NULL==piMainBody1)

```

```

           {
             ::CATCloseCGMContainer(piGeomFactory);
CATBody * piMainBody1=NULL;
piMainBody1 = pStiffOp->**GetResult**();
```vbscript
if (NULL==piMainBody1)
             return (1);

```

           }

           //--- Deletes the operator
           **delete** pStiffOp;
           pStiffOp = NULL;

           // Releases the configuration
pStiffOp = NULL;
               pConfig->**Release**();

The new operator is used as a GM operator with the steps that creates, runs, gets the result, and deletes. The software configuration is also released, because it is no more used.
    5. Writing the Model and Closing the Container To save the model in a file, the `::CATSaveCGMContainer` global function is used. Notice that in the sample, the save is conditioned by an input parameter representing the file inside which the model must be saved. The sample ends with the closure of the geometry factory, done by the `::CATCloseCGMContainer` global function.

           if(1==toStore)

            {
           #ifdef _WINDOWS_SOURCE
5. Writing the Model and Closing the Container To save the model in a file, the `::CATSaveCGMContainer` global function is used. Notice that in the sample, the save is conditioned by an input parameter representing the file inside which the model must be saved. The sample ends with the closure of the geometry factory, done by the `::CATCloseCGMContainer` global function.
if(1==toStore)
              ofstream filetowrite(pfileName, ios::binary ) ;

           #else
```vbscript
if(1==toStore)
ofstream filetowrite(pfileName, ios::binary ) ;
              ofstream filetowrite(pfileName,ios::out,filebuf::openprot) ;
```

           #endif

              **::CATSaveCGMContainer**(piGeomFactory,filetowrite);
              filetowrite.close();
            }
            //
            // Closes the container
            //
            **::CATCloseCGMContainer**(piGeomFactory);

In Short The journal follows the topological modification from the input bodies (that are never modified) to the output body. This journal is read to recover topological entities, that can be later used in other topological operations. New operator classes can be developed, by chaining several topological operations. In this case, the corresponding journal is the concatenation of the journal of each operator. If an intermediate body is removed, this must be declared in the journal. References [1] |  [ Topology Concepts](../CAACgmModel/CAACgmTaTobTopoConcepts.md)
---|---
[2] |  [ The CGM Topological Model](../CAACgmModel/CAACgmTaTobTopoModel.md)
[3] | [Overview of the Topological Operators](CAACgmUcTopOverview.md)
[4] | [Understanding the CGM Journal](CAACgmTaTopJournal.md)
[5] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
[6] | [Understanding the Versioning of the Topological Operators](CAACgmTaTopVersioning.md)
History Version: **1.1** [Oct 2000] | Operator configuration
---|---
Version: **1** [May 2000] | Document created
