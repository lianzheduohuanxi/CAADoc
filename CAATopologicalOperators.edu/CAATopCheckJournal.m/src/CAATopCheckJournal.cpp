/**
* @quickReview CRE 03:07:03
*/

// COPYRIGHT DASSAULT SYSTEMES  2002
//        
//                               WARNING !
//                               WARNING ! 
//                               WARNING !
//                               WARNING !
//
// ----------------------------------------------------------------------------
//        FROM Version 5 Release 12 USE CAATopCheckForPart
// ----------------------------------------------------------------------------
//
#include <iostream.h>

// Mathematics
#include "CATSoftwareConfiguration.h"  // the software configuration

// GeometricObjects
#include "CATCGMJournalList.h"
#include "CATCGMJournalItem.h"

// NewTopologicalObjects
#include "CATBody.h"                   // body      
#include "CATCell.h"                   // cell
#include "CATTopData.h"                // the journal and the configuration 

#include "CAACheckJournal.h"

//---------------------------------------------------------------------------- 
// Destructor
//---------------------------------------------------------------------------- 
CAACheckJournal::~CAACheckJournal()
{
    _iReport  = NULL;
    _iResult  = NULL;
}

//---------------------------------------------------------------------------- 
// Constructor
//---------------------------------------------------------------------------- 
CAACheckJournal::CAACheckJournal (CATCGMJournalList * iReport,
                                  CATBody * iResult)
                                  
{
    cout << "CAACheckJournal constructor " << endl;
    _iReport  = iReport;
    _iResult  = iResult;
}

//
// CAAAddInputBody method
// Specify whether the cell of the input bodies are copied or 
// not copied in the result body. 
//
// If CAATopCheckJournalType = CAATopCheckNoCopy
// - the input body cells are not copied in the result,
//   they can only appear in the journal as the parents of created/modified
//   cells.
// If CAATopCheckJournalType = CAATopCheckCopy
// - the input body cells are copied in the result.
//   If a cell is unmodified, it may not be mentioned in the journal.
// 
int CAACheckJournal::CAAAddInputBody(CATBody * iInputBody,
                                     CAATopCheckJournalType copyNoCopy)
{
    // 
    // RC = 0 -> OK
    // RC = 1 -> Null pointer
    // RC = 2 -> Type of input body not propely defined
    //
    if (NULL == iInputBody) return 1;
    if (copyNoCopy == CAATopCheckNoCopy)
    {
        // Populate the list of input body in NO COPY mode
        //
        _InputsNoCopy.Append(iInputBody);
        return 0;
    }
    else if (copyNoCopy == CAATopCheckCopy)
    {
        // Populate the list of input body in COPY mode
        //
        _InputsCopy.Append(iInputBody);
        return 0;
    }
    else return 2;
}
//
// Global function to check the type of cell 
// Cells in a journal should be of CATFaceType, CATEdgeType, CATVertexType
// CATPLineType or CATPlaneType type
//
int CheckType(CATICGMObject* iObj)
{
    if (NULL == iObj) return 1;
    int rc=0;
    if (!iObj->IsATypeOf(CATFaceType) && !iObj->IsATypeOf(CATEdgeType)
        && !iObj->IsATypeOf(CATVertexType)
        ) 
    {
        // ---------------
        // INVALID JOURNAL
        // ---------------
        cout << iObj->GetPersistentTag() << " has an invalid type " << endl;
        cout << "----------------------------------------" << endl;
        
        return  1 ;  
    }
    else
        return  0;
    
}
//
// Global function to retrieve the list of cells 
// that might potentially appear in a journal
// i.e. all the faces, the side edges and the side vertices
//
int GetBodyCells (CATBody* iBody, CATLISTP(CATCell) & oListOfBodyCells)
{
    int rc = 0;
    if (NULL == iBody) return 1 ;
    //
    //          All the faces are appended
    //
    CATLISTP(CATCell) faces;
    
    iBody->GetAllCells(faces, 2);
    int i = 1;
for (; i <= faces.Size(); i++)
        oListOfBodyCells.Append(faces[i]);
    //
    //          Only the side edges are appended
    //
    CATLISTP(CATCell) edges;
    iBody->GetAllCells(edges,1);
    for (i = edges.Size(); i > 0; i-- )
    {
        CATBoolean iDifferentiateMatterSide1 = TRUE;
        CATCell *iEdgeCell = edges[i];
        if  (NULL == iEdgeCell) return 2;
        
        int nbBounded1 = iEdgeCell->GetNbBoundedCells(iBody,iDifferentiateMatterSide1);
        if ( nbBounded1 < 2 )
            oListOfBodyCells.Append(iEdgeCell);
    }
    //
    //          Only the side vertices are appended
    //
    CATLISTP(CATCell) vertices;
    iBody->GetAllCells(vertices,0);
    for (i = vertices.Size(); i > 0; i-- )
    {
        CATBoolean iDifferentiateMatterSide0 = TRUE;
        CATCell *iVertexCell = vertices[i];
        if  (NULL == iVertexCell) return 2;
        
        int nbBounded0 = iVertexCell->GetNbBoundedCells(iBody,iDifferentiateMatterSide0);
        if ( nbBounded0 < 2 )
            oListOfBodyCells.Append(iVertexCell);
    }
    return 0;
}

//-------------------------------------------------------------------------------------
// The Run method consists in:
//
//    - Tassing the journal in order to remove the intermediate cells
//    - Scanning of the journal -
//        * For the item in creation mode:
//               a) determine whether the constructed object
//               belongs to the result body
//               b) check the object type
//        * For the item in deletion:
//               a) check that the deleted object belongs to 
//                  the input bodies
//               b) check the object type
//        * For the item in modified/absorbed/subdivided item:
//               a) check whether the parents of a modified object
//                  belong to the input bodies
//               b) check the object type
//               c) check whether the modified objects
//                  belong to the result body 
//               d) check the object type
//   - Scanning the list of cells in the result body,
//     check that all the cells in the result body are in the journal
//     as created or modified cells except those that belong to a body
//     in copy mode
//                  
//-------------------------------------------------------------------------------------
int CAACheckJournal::CAACheck()

{
    // cout << "CAACheck ... " << endl;
    int rc=0;           // method return code
    int checkKO = 0;    // 1 KO - 0 OK
    int checkTypeResult;
    //
    // A - Get the list of cells belonging to the result body
    //
    CATLISTP(CATCell) listOfCellsInResult;
    GetBodyCells (_iResult,  listOfCellsInResult);
    //
    // Define the list of cells belonging to the input bodies
    //
    CATLISTP(CATCell) listOfCellsInInputBodies;
    CATLISTP(CATCell) listOfCellsInBodyCopy;
    CATLISTP(CATCell) listOfCellsInBodyNoCopy;
    //
    // B - Get the list of cells belonging to the input codies in Copy mode
    //     and add it to the listOfCellsInInputBodies list
    //
    listOfCellsInBodyCopy.RemoveAll();
    int nbBodiesInInputCopy = _InputsCopy.Size();
    int i = 1;
for (; i <= nbBodiesInInputCopy; i++)
    {
        GetBodyCells(_InputsCopy[i], listOfCellsInBodyCopy);
        listOfCellsInInputBodies.Append(listOfCellsInBodyCopy);
    }
    /*
    cout << "listOfCellsInInputBodies " << endl;
    for (i = 1; i <= listOfCellsInInputBodies.Size() ; i++)
    {
    cout << listOfCellsInInputBodies[i]->GetPersistentTag() << endl;
    } 
    */
    
    // C - Get the list of cells belonging to the input bodies in No Copy mode
    //     and add it to the listOfCellsInInputBodies list
    //
    listOfCellsInBodyNoCopy.RemoveAll();
    int nbBodiesInInputNoCopy = _InputsNoCopy.Size();
    for (i = 1; i <= nbBodiesInInputNoCopy; i++)
    {
        GetBodyCells(_InputsNoCopy[i], listOfCellsInBodyNoCopy);
        listOfCellsInInputBodies.Append(listOfCellsInBodyNoCopy);
    }
    
    // D - Remove the possible duplicates
    // 
    listOfCellsInInputBodies.RemoveDuplicates();
    
    /*
    cout << "input bodies" << endl;
    for (i = 1; i <= listOfCellsInInputBodies.Size(); i++)
    {
    cout << listOfCellsInInputBodies[i]->GetPersistentTag() << endl;
    }
    */  
    //
    // E - Remove the intermediate cells
    //
    _iReport->Tass();
    
    // F - Scan the journal
    //
    CATCGMJournal* Next = NULL;
    CATLISTP(CATICGMObject) UnknownGeoNotInInput;  // list of objects read as parents in
    // the journal but not in input bodies
    CATLISTP(CATICGMObject) UnknownGeoInDeleted;   // list of objects read as deleted objects
    // in the journal but not in input bodies
    CATLISTP(CATICGMObject) UnknownGeoInModif;
    
    // List of objects appearing as constructed or modified objects
    // in the journal
    //
    CATLISTP(CATGeometry) createdAndModifiedObjects = NULL; 
    
    cout << "--------------- "  << endl;
    cout << "JOURNAL ERRORS: " << endl;
    cout << "--------------- " << endl;
    
    while (Next = _iReport->Next(Next))
    {
        CATCGMJournalItem* pJournalItem = Next->CastToReportItem();
        //
        // 1 - Check the number of levels in the journal
        //
        if (!pJournalItem) 
        {  
            // ---------------
            // INVALID JOURNAL
            // ---------------
            cout << "The journal should not have more "       << endl;
            cout << "than one level after the tass operation." << endl;
            cout << "----------------------------------------" << endl;
            checkKO = 1;
        }
        
        if (!pJournalItem->GetActiveMode()) continue;
        //
        // 2 - Scan the journal item by item
        //     	
        CATCGMJournal::Type CGMEventType = pJournalItem->GetType();
        // 
        switch (CGMEventType)
        {  
            // 
            // (Example:      [67] -> Creation [131])
            //
        case CATCGMJournal::Creation:
            {
                //
                // 2.1 - Determine whether the constructed object [131] belongs 
                //       to the result body
                //
                //       a) Retrieve the construction object
                //
                CATICGMObject* newObj = pJournalItem->GetConstructedObject();
                if (NULL == newObj)
                { 
                    // ---------------
                    // INVALID JOURNAL
                    // ---------------
                    cout << "You should get a constructed object " ;
                    cout << "in a creation statement " << endl;
                    cout << "----------------------------------------" << endl;
                    return (1);
                }
                //
                //       b) Add it to the createdAndModifiedObjects list
                //          (required to check the Copy/NoCopy objects)
                //
                CATCell * pCurrentCell = (CATCell*)newObj;
                createdAndModifiedObjects.Append(pCurrentCell);
                //
                //       c) Check the object type
                //
                checkTypeResult = CheckType(newObj);
                if (checkTypeResult == 1) 
                {
                    // ---------------
                    // INVALID JOURNAL
                    // ---------------
                    checkKO = 1;
                }
                //
                //       d) Search for the constructed object 
                //          in the result body 
                //
                if (!listOfCellsInResult.Locate(pCurrentCell)   )
                {
                    // ---------------
                    // INVALID JOURNAL
                    // ---------------
                    cout << newObj->GetPersistentTag() ;
                    cout << " is not in the resulting body" << endl;
                    checkKO = 1;
                    cout << "----------------------------------------" << endl;
                }
                
                //
                // 2.2 - Determine whether the parents of the 
                //       constructed object are in the input bodies
                //
                //       a) Retrieve the list of construction objects
                //
                const CATLISTP(CATGeometry)* parentObjects =
                    pJournalItem->GetConstructionObjects();
                int numberOfParents = parentObjects->Size();
                //
                //       b) Scan the list of construction object
                //          and determine whether they are included 
                //          in the input bodies.
                //
                for (i = 1; i <= numberOfParents; i++)
                {
                    CATGeometry * pParentObj = (*parentObjects)[i];
                    //
                    //   c) Check the object type
                    //
                    checkTypeResult = CheckType(pParentObj);
                    if (checkTypeResult == 1) 
                    {
                        // ---------------
                        // INVALID JOURNAL
                        // ---------------
                        checkKO = 1;
                    }
                    
                    CATCell * pCurrentCell = (CATCell*)pParentObj;
                    //
                    // If the parent object does not belong to 
                    // one of the input body, it populates the UnknownGeoNotInInput
                    // list of objects.
                    // INVALID JOURNAL
                    // when the UnknownGeoNotInInput list size is > 0
                    //
                    if (!listOfCellsInInputBodies.Locate(pCurrentCell)   )
                        UnknownGeoNotInInput.Append( (*parentObjects)[i] );
                }
                break;
            }
            
        case CATCGMJournal::Deletion:
            {
                // Example: [8] -> Deletion
                //
                // 2.3 - Check that the deleted object belongs to the input bodies
                //
                //       a) Get the list of deleted objects
                //
                const CATLISTP(CATGeometry)* oldObjDel = pJournalItem->GetDeletedObjects();
                if (NULL == oldObjDel)
                { 
                    // ---------------
                    // INVALID JOURNAL
                    // ---------------
                    cout << "You should get a list of deleted objects  " ;
                    cout << "in a deletion statement " << endl;
                    cout << "----------------------------------------" << endl;
                    checkKO = 1;
                    return 1;
                }
                
                //       b) Scan the list of deleted objects, 
                //          determine whether 
                //          each deleted object belongs to the input bodies
                //
                int numberOfOldObjDel = oldObjDel->Size();
                for (i = 1; i <= numberOfOldObjDel ; i++)
                {
                    //   c) Check the object type
                    //
                    checkTypeResult = CheckType((*oldObjDel)[i]);
                    if (checkTypeResult == 1) 
                    {
                        // ---------------
                        // INVALID JOURNAL
                        // ---------------
                        checkKO = 1;
                    }
                    
                    CATCell * pCurrentCell = (CATCell*)((*oldObjDel)[i]);
                    //
                    // If the deleted object does not belong to 
                    // one of the input body, it populates the UnknownGeoInDeleted
                    // list of objects.
                    // INVALID JOURNAL
                    // when the UnknownGeoInDeleted list size is > 0
                    //
                    if (!listOfCellsInInputBodies.Locate(pCurrentCell)   )
                    {
                        UnknownGeoInDeleted.Append( (*oldObjDel)[i] );
                    }
                }
                break;
            }
            
            
        case CATCGMJournal::Modification:
        case CATCGMJournal::Subdivision:
        case CATCGMJournal::Absorption:
            {
                //cout << "Start of modification " << endl;
                //
                // 2.4 - Check whether the parents of a modified object
                //           belong to the input bodies
                //
                //       a) Get the list of the parents 
                //          of a modified/subdivided/absorbed item
                //
                const CATLISTP(CATGeometry)* oldObjModif = pJournalItem->GetOldObjects();
                //
                //       b) Scan the list of parent objects, 
                //          determine whether each parent object
                //          belongs to the input bodies
                //
                int numberOfOldObjModif = oldObjModif->Size();
                for (i = 1; i <= numberOfOldObjModif ; i++)
                {
                    CATGeometry * pOldModifObject = (*oldObjModif)[i];
                    
                    //   c) Check the object type
                    //
                    checkTypeResult = CheckType((*oldObjModif)[i]);
                    if (checkTypeResult == 1) 
                    {
                        // ---------------
                        // INVALID JOURNAL
                        // ---------------
                        checkKO = 1;
                    }
                    CATCell * pCurrentCellModif = (CATCell*)pOldModifObject;
                    //
                    // If the parent object does not belong to 
                    // one of the input body, it populates the UnknownGeoNotInInput
                    // list of objects.
                    // INVALID JOURNAL
                    // when the UnknownGeoNotInInput list size is > 0
                    //
                    if (! (listOfCellsInInputBodies.Locate(pCurrentCellModif))  )
                    {
                        UnknownGeoNotInInput.Append( (*oldObjModif)[i] );
                    }
                }
                // 2.5 - Check whether the modified objects
                //       belong to the result body
                // 
                //       a) Get the list of modified/subdivided/absorbed objects
                //
                const CATLISTP(CATGeometry)* newObjModif = pJournalItem->GetNewObjects();
                //
                //       b) Scan the list of modified objects, 
                //          determine whether 
                //          each modified object belongs to the result body
                //
                int numberOfNewObjModif = newObjModif->Size();
                for (i = 1; i <= numberOfNewObjModif ; i++)
                {
                    CATGeometry * pNewModifObject = (*newObjModif)[i];
                    
                    //   c) Check the object type
                    //
                    checkTypeResult = CheckType((*newObjModif)[i]);
                    if (checkTypeResult == 1) 
                    {
                        // ---------------
                        // INVALID JOURNAL
                        // ---------------
                        checkKO = 1;
                    }
                    
                    CATCell * pCurrentCellModif = (CATCell*)pNewModifObject;
                    //
                    //       c) Add each modified objects to the 
                    //           createdAndModifiedObjects list
                    //          (required to check the Copy/NoCopy objects)
                    //
                    createdAndModifiedObjects.Append((*newObjModif)[i]);
                    //
                    // If the modified object does not belong to 
                    // the result body, it populates the UnknownGeoInModif
                    // list of objects.
                    // INVALID JOURNAL
                    // when the UnknownGeoInModif list size is > 0
                    //
                    if (!listOfCellsInResult.Locate(pCurrentCellModif)   )
                    {
                        UnknownGeoInModif.Append( (*newObjModif)[i] );
                    }
                }
                
                break;
            }
            
        }
        
    }
    
    
    // G - Check whether the list of unknown objects are empty
    // 
    if (UnknownGeoInModif.Size() > 0) 
    {
        cout << "There are unknown cells which are parents of " ;
        cout << "modified objects in the journal " ;
        cout << "(cells not belonging to any body in input)" << endl;
        checkKO = 1;
    }
    if (UnknownGeoInDeleted.Size() > 0) 
    {
        cout << "There are unknown cells which are deleted in the journal " ;
        cout << "(cells not belonging to any body in input)" << endl;
        checkKO = 1;
    }
    if (UnknownGeoNotInInput.Size() > 0) 
    {
        cout << "There are unknown cells which are parents of " ;
        cout << "modified objects in the journal " ;
        cout << "(cells not belonging to any body in input)" << endl;
        checkKO = 1;
    }
    
    
    // H - Scan the list of cells in the result body,
    //     check that all the cells in the body result are in the journal
    //     as created or modified cells except those that belong to a body
    //     in copy mode
    //
    for (i = 1; i <= listOfCellsInResult.Size() ; i++)
    {
        CATGeometry * pCellResult = (listOfCellsInResult)[i];
        CATCell * pCell = (CATCell*)pCellResult;
        if ( ( (!createdAndModifiedObjects.Locate(pCell)) && (!listOfCellsInBodyCopy.Locate(pCell)) ) != 0 )
        {
            // For this cell which is not in the result body
            // check that it is in input body copy mode
            // otherwise the journal is not valid.
            cout << "=================================" << endl;
            cout << "=================================" << endl;
            cout << "Journal error                    " << endl;
            cout << "Cell " << ((listOfCellsInResult)[i])->GetPersistentTag();
            cout << " should either be in the journal or" ;
            cout << " in a body in Copy Mode" << endl;
            checkKO = 1;
        }
    }
    //
    //
    cout << "=================================" << endl;
    cout << "=================================" << endl;
    if (checkKO == 1) 
    {
        cout << "Invalid journal " << endl;
        rc = 1;
    }
    else 
    {
        cout << "No errors" << endl;
        cout << "Valid journal " << endl;
        rc = 0;
    }
    cout << "=================================" << endl;
    cout << "=================================" << endl;
    return rc;
}
