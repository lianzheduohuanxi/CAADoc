/**
* @quickReview CRE 04:03:02
*/
//
//
#include "CAACheckForPart.h"
//
#include <iostream.h>
#include <stdlib.h>

// Mathematics
#include "CATSoftwareConfiguration.h"  // the software configuration

// GeometricObjects
#include "CATCGMJournalList.h"
#include "CATCGMJournalItem.h"
#include "CATCGMJournalInfo.h"

// NewTopologicalObjects
#include "CATBody.h"                   // body      
#include "CATCell.h"                   // cell
#include "CATTopData.h" 
//
//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
//
CAACheckForPart::CAACheckForPart(CATCGMJournalList*      iReport,
                                 CATBody*                iResult,
                                 const CATUnicodeString* iFeatureName,
                                 ostream*                iErrorVerdictOutput,
                                 ostream*                iErrorWarningOutput,
                                 CATBoolean              iVerdictVerbose)
                                 
{
    _iReport  = iReport;
    _iResult  = iResult;
    _iFeatureName = iFeatureName;
    _iErrorVerdictOutput = iErrorVerdictOutput;
    _iErrorWarningOutput = iErrorWarningOutput;
    _iVerdictVerbose = iVerdictVerbose;
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
//
CAACheckForPart::~CAACheckForPart()
{
    _iReport  = NULL;
    _iResult  = NULL;
    _iFeatureName = NULL;
    _iErrorVerdictOutput=NULL;
    _iErrorWarningOutput=NULL;
}

//-----------------------------------------------------------------------------
// To declare that an input body is in Copy / No Copy Mode
//-----------------------------------------------------------------------------
//
int CAACheckForPart::CAAAddInputBody(CATBody * iInputBody,
                                     CAATopCheckForPartType copyNoCopy)
{
    // 
    // RC = 0 -> OK
    // RC = 1 -> Null pointer
    // RC = 2 -> Type of input body not properly defined
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

// Sub-services 
//
//
// Check the type of cell 
// Cells in a report should be of CATFaceType, CATEdgeType, CATVertexType type
//
int CheckType(CATGeometry* iObj)
{
    if (NULL == iObj) return 2;
    if (!iObj->IsATypeOf(CATFaceType) && !iObj->IsATypeOf(CATEdgeType)
        && !iObj->IsATypeOf(CATVertexType)
        ) 
    { return  0 ;}
    else
        return  1; 
}


// Print a persistent tag 
//
int PrintAPersistentTag  (ostream* myStream, CATULONG32  persTag)
{
    if (NULL == myStream) return 1;
    char strPersTag[256] = "" ;
    sprintf(strPersTag,"%d", persTag);
    myStream->write(strPersTag,strlen(strPersTag));
    return 0;
}

// Print a report item
//
int PrintAJournalItem(ostream* myStream,
                      CATCGMJournalItem * journalItem)
{
    if ( (NULL == myStream) || (NULL == journalItem) ) return 1;
    //
    // Print the parent list
    //
    CATLISTP(CATGeometry) parentList;
    journalItem->GetFirstObjs(parentList);
    int numberParentList = parentList.Size();
    //
    // If no parents - that is "[ ] -> Creation [xx]"  for example
    //
    if (numberParentList == 0) 
    {
        myStream->write("[ ]",strlen("[ ]"));
    }
    //
    // If several parents "[ Edge 1, Vertex 2] -> Modification [xx,yy]" for example
    //
    int i = 1;
for (; i <= numberParentList; i++)
    {
        myStream->write("[",strlen("["));
        char * str1 = " ";
        if ((parentList)[i]->IsATypeOf(CATFaceType)) { str1 = "Face_";   }
        else if ((parentList)[i]->IsATypeOf(CATEdgeType)) {  str1 = "Edge_";   }    
        else if ((parentList)[i]->IsATypeOf(CATVertexType)) {  str1 = "Vertex_";   }
        else  { str1 = "UnauthorizedType_";   }
        myStream->write(str1,strlen(str1));
        
        CATULONG32  persTag = (parentList)[i]->GetPersistentTag() ;
        PrintAPersistentTag(myStream, persTag);
        myStream->write("]",strlen("]"));
        if (i < numberParentList)
        {
            str1 = ",";
            myStream->write(str1,strlen(str1));
        }
    }
    //
    // Print the type
    //
    CATCGMJournal::Type CGMEventType = journalItem->GetType();
    switch (CGMEventType)
    {  
    case CATCGMJournal::Creation:
        {
            myStream->write("->Creation",strlen("->Creation"));
            break;
        }
    case CATCGMJournal::Modification:
        {
            myStream->write("->Modification",strlen("->Modification"));
            break;
        }
    case CATCGMJournal::Subdivision:
        {
            myStream->write("->Subdivision",strlen("->Subdivision"));
            break;
        }
    case CATCGMJournal::Absorption:
        {
            myStream->write("->Absorption",strlen("->Absorption"));
            break;
        }
    case CATCGMJournal::Deletion:
        {
            myStream->write("->Deletion",strlen("->Deletion"));
            break;
        }
    case CATCGMJournal::Keep:
        {
            myStream->write("->Keep",strlen("->Keep"));
            break;
        }
    }
    //
    // Print the children
    //
    CATLISTP(CATGeometry) childrenList;
    journalItem->GetLastObjs(childrenList);
    int numberChildrenList = childrenList.Size();
    
    for (i = 1; i <= numberChildrenList; i++)
    {
        myStream->write("[",strlen("["));
        char * str1 = " ";
        if ((childrenList)[i]->IsATypeOf(CATFaceType)) { str1 = "Face_";   }
        else if ((childrenList)[i]->IsATypeOf(CATEdgeType)) {  str1 = "Edge_";   }    
        else if ((childrenList)[i]->IsATypeOf(CATVertexType)) {  str1 = "Vertex_";   }
        else  { str1 = "UnauthorizedType_";   }
        myStream->write(str1,strlen(str1));
        
        CATULONG32  persTag = (childrenList)[i]->GetPersistentTag() ;
        PrintAPersistentTag(myStream, persTag);
        myStream->write("]",strlen("]"));
        if (i < numberChildrenList)
        {
            str1 = ",";
            myStream->write(str1,strlen(str1));
        }
    }
    
    // Print the infos if any
    //
    const CATCGMJournalInfo * journalInfo = journalItem->GetAssociatedInfo();
    if (journalInfo)
    {
        CATLONG32 infoNumber = journalInfo->GetNumber();
        char strInfo[90] ;
        sprintf(strInfo," Info=%d", infoNumber);
        myStream->write(strInfo,strlen(strInfo));
    }
    myStream->write("\n",strlen("\n"));
    
    return 0;
}

//
// D - Determine whether a cell is a bording cell 
//     Non-bording cells are not backtracked in the report
//
CATBoolean IsABordingCell(CATCell* iCell, CATBody* inBody)
{ 
    if ( (NULL == iCell) || (NULL == inBody) || (!(iCell->IsInside(inBody)))  )return FALSE;  
    
    short iDimCell = iCell->GetDimension();
    switch ( iDimCell )
    {
    case 2: 
        return TRUE;
    case 1: 
    case 0:
        {
            CATBoolean iDifferentiateMatterSide = TRUE;    
            int NumberOfBoundedCells = iCell->GetNbBoundedCells(inBody,iDifferentiateMatterSide);
            return ( NumberOfBoundedCells <= 1 ) ? TRUE : FALSE;
        }
    default:
        return FALSE;
    }
    return FALSE;  
}
// Displays a warning - not bording cells
//
int BordingCellWarning(ostream* myStream, CATCell * iCell, CATCGMJournalItem * iJournalItem)
{
    int rc = 0;
    if ( (NULL == myStream) || (NULL == iCell) || (NULL == iJournalItem) ) rc = 1;
    else 
    {
        myStream->write("WARNING\n", strlen("WARNING\n")); 
        PrintAJournalItem(myStream, iJournalItem); 
        CATULONG32  persTag = iCell->GetPersistentTag(); 
        PrintAPersistentTag(myStream,persTag); 
        char * notBor = " is not a bording cell - The order is ignored"; 
        myStream->write(notBor,strlen(notBor));  
        myStream->write("\n * \n",strlen("\n * \n")); 
        rc = 0 ;
    }
    return rc ;
}

// Displays a warning for the cell type
// 
 
int CellTypeWarning(ostream* myStream, CATICGMObject * iCell, CATCGMJournalItem * iJournalItem)
{
    int rc = 0;
    if ( (NULL == myStream) || (NULL == iCell) || (NULL == iJournalItem) ) rc = 1;
    else 
    {
        myStream->write("WARNING\n", strlen("WARNING\n"));
        PrintAJournalItem(myStream, iJournalItem);
        CATULONG32  persTag = iCell->GetPersistentTag() ;
        PrintAPersistentTag(myStream,persTag);
        char * notCell = " is not a CATFace, a CATEdge or a CATVertex - The order is ignored";
        myStream->write(notCell,strlen(notCell));
        myStream->write("\n * \n",strlen("\n * \n")); 
        rc = 0 ;
    }
    return rc ;
}
//
// To retrieve the list of bording cells in a body
//
int GetBodyCells (CATBody* iBody, CATLISTP(CATCell) & oListOfBodyCells)
{
    int rc = 0;
    if (NULL == iBody) return 1 ;
    CATLISTP(CATCell) bodyCells;
    
    iBody->GetAllCells(bodyCells, -1);  // -1 for all cells
    for (int i = 1; i <= bodyCells.Size(); i++)
    {
        if  (IsABordingCell(bodyCells[i], iBody))
        {
            oListOfBodyCells.Append(bodyCells[i]);
        }  
    }
    return 0;
}

//-----------------------------------------------------------------------------
// CHECKING THE JOURNAL - RETURNS 0 (OK) - 1 (KO)
//-----------------------------------------------------------------------------
int CAACheckForPart::CAACheck()
{
    if ((_iReport==NULL) || (_iResult==NULL))
        return 1;
    
    int rc = 0;
    
    CATCGMJournalList* pWorkingJournal = (CATCGMJournalList*)_iReport->Duplicate(NULL);
    if (!pWorkingJournal) return 1;
    
    // html header
    //
    char * strHead1 = NULL;
    char * strHead2 = NULL;
    char * str = NULL;
    const char *featName = NULL;
    
    strHead1 = "<HTML>\n<HEAD>\n<TITLE>CHECKING THE TOPOLOGICAL JOURNAL - VERDICT</TITLE>\n</HEAD>";
    strHead2 = "<HTML>\n<HEAD>\n<TITLE>CHECKING THE TOPOLOGICAL JOURNAL - VERDICT AND DETAILS</TITLE>\n</HEAD>";   
    str = "\n<BODY bgcolor='#FCBD6A'>\n<p>Checking ";
    
    if(_iErrorVerdictOutput) _iErrorVerdictOutput->write(strHead1,strlen(strHead1));
    if(_iErrorWarningOutput) _iErrorWarningOutput->write(strHead2,strlen(strHead2));
    
    // Start printing in the output files
    //
    
    if (_iFeatureName)
        featName = _iFeatureName->ConvertToChar();
    else
        featName = "Unknown Feature";
    
    char * hrefStr = " <A NAME='" ;
    CATULONG32  hrefStrTag = _iResult->GetPersistentTag() ;
    char * hrefEnd= "'>";
    
    char * strDet = "\nDETAILED LIST OF ERRORS AND WARNINGS\n";
    if (_iErrorVerdictOutput)
    {
        _iErrorVerdictOutput->write(str,strlen(str));
        
        
        _iErrorVerdictOutput->write(hrefStr,strlen(hrefStr));
        PrintAPersistentTag(_iErrorVerdictOutput,hrefStrTag);
        _iErrorVerdictOutput->write(hrefEnd,strlen(hrefEnd));
        
        _iErrorVerdictOutput->write(featName,strlen(featName));
        
        
        _iErrorVerdictOutput->write("</A></p>\n",strlen("</A></p>\n"));
        _iErrorVerdictOutput->write("<xmp>\n",strlen("<xmp>\n"));
        
    }
    if (_iErrorWarningOutput)
    {
        _iErrorWarningOutput->write(str,strlen(str)); 
        _iErrorWarningOutput->write(hrefStr,strlen(hrefStr));
        PrintAPersistentTag(_iErrorWarningOutput,hrefStrTag);
        _iErrorWarningOutput->write(hrefEnd,strlen(hrefEnd));       
        _iErrorWarningOutput->write(featName,strlen(featName));
        _iErrorWarningOutput->write("</A></p>\n",strlen("</A></p>\n"));
        _iErrorWarningOutput->write("<xmp>\n",strlen("<xmp>\n")); 
        _iErrorWarningOutput->write(strDet,strlen(strDet));
        _iErrorWarningOutput->write("\n * \n",strlen("\n * \n"));
    }
    
    // Some definitions
    //
    int checkTypeResult; 
    
    CATLISTP(CATGeometry) listOfCellsOfWrongType; // not CATFace/CATEdge/CATVertex
    CATLISTP(CATGeometry) createdObjects ;        // list of created objects (Creation order)
    CATLISTP(CATGeometry) modifiedObjects ;       // list of modified objects (Modification order)
    CATLISTP(CATCell) listOfNotBordingCells;      // not bording cells
    CATLISTP(CATCell) listOfNotTracedCells;       // not backtracked cells
    CATLISTP(CATCell) listOfCellsInInputBodies;   // in input bodies & bording cells
    CATLISTP(CATCell) listOfCellsInBodyCopy;      // in bodies in Copy mode & bording cells
    CATLISTP(CATCell) listOfCellsInBodyNoCopy;    // in bodies in No Copy mode & bording cells
    CATLISTP(CATCell) listOfKeptCells;            // in Keep orders & bording cells
    CATLISTP(CATCell) listOfDeletedCells;         // in Deletion orders & bording cells
    CATLISTP(CATCell) listOfParentsOfModified;     // the parents of modified cells
    //
    // Get the list of cells belonging to the result body
    //
    CATLISTP(CATCell) listOfCellsInResult;
    GetBodyCells (_iResult,  listOfCellsInResult);
    //
    // Get the list of cells belonging to the input codies in Copy mode
    //     and add it to the listOfCellsInInputBodies list
    //
    int nbBodiesInInputCopy = _InputsCopy.Size();
    listOfCellsInBodyCopy.RemoveAll();
    int i = 1;
for (; i <= nbBodiesInInputCopy; i++)
    {
        GetBodyCells(_InputsCopy[i], listOfCellsInBodyCopy);
        listOfCellsInInputBodies.Append(listOfCellsInBodyCopy);    
    }
    //
    // C - Get the list of cells belonging to the input bodies in No Copy mode
    //     and add it to the listOfCellsInInputBodies list
    //
    int nbBodiesInInputNoCopy = _InputsNoCopy.Size();
    listOfCellsInBodyNoCopy.RemoveAll();
    for (i = 1; i <= nbBodiesInInputNoCopy; i++)
    {  
        GetBodyCells(_InputsNoCopy[i], listOfCellsInBodyNoCopy);
        listOfCellsInInputBodies.Append(listOfCellsInBodyNoCopy);
        
    }
    //
    // Remove the possible duplicates
    // 
    listOfCellsInInputBodies.RemoveDuplicates();
    //
    // Remove the intermediate cells of the journal
    //
    pWorkingJournal->Tass();
    //
    //
    // =========================================================================
    // Scan the journal
    // =========================================================================
    //
    //
    CATCGMJournal* Next = NULL;
    while (Next = pWorkingJournal->Next(Next))
    {
        CATCGMJournalItem* pJournalItem = Next->CastToReportItem();
        if (!pJournalItem) return 1;    
        if (!pJournalItem->GetActiveMode()) continue; // non active report item are not analyzed    	
        CATCGMJournal::Type CGMEventType = pJournalItem->GetType();
        // 
        switch (CGMEventType)
        {  
            // For each constructed item, it is checked whether it is valid:
            // i.e. whether it belongs to a bording cell of the resulting body
            // or whether it is a CATFace/CATEdge/CATVertex
            // Otherwise the order is ignored
            //
        case CATCGMJournal::Creation:
            {
                int IsIgnoredC = 0 ;
                CATICGMObject* newObj = pJournalItem->GetConstructedObject();
                if (NULL == newObj) { return (1); }
                
                CATGeometry * pGeomNewObj = (CATGeometry *)newObj;
                CATCell * pChildCell = (CATCell*)newObj;
                checkTypeResult = CheckType(pGeomNewObj);
                if (checkTypeResult == 0) 
                { 
                    IsIgnoredC = 1 ;
                    if(_iErrorWarningOutput) CellTypeWarning(_iErrorWarningOutput, newObj, pJournalItem);
                    listOfCellsOfWrongType.Append(pGeomNewObj);
                }
                else
                {
                    if (IsABordingCell(pChildCell,_iResult) == FALSE) 
                    {
                        IsIgnoredC = 1 ;
                         if(_iErrorWarningOutput) BordingCellWarning(_iErrorWarningOutput, pChildCell, pJournalItem);
                        listOfNotBordingCells.Append(pChildCell);
                    }
                }
                //
                // For each parent item, it is checked whether it is valid:
                // i.e. whether it belongs to a bording cell of an input body
                // or whether it is a CATFace/CATEdge/CATVertex
                // Otherwise the order is ignored
                //
                const CATLISTP(CATGeometry)* parentObjects =
                    pJournalItem->GetConstructionObjects();
                int numberOfParents = parentObjects->Size();
                //
                for (i = 1; i <= numberOfParents; i++)
                {
                    
                    CATGeometry * pGeom = (*parentObjects)[i];
                    CATCell * pCurrentCell = (CATCell*)pGeom;
                    checkTypeResult = CheckType(pGeom);
                    if (checkTypeResult == 0) 
                    {
                        IsIgnoredC = 1 ;
                        if(_iErrorWarningOutput) CellTypeWarning(_iErrorWarningOutput, pGeom, pJournalItem);
                        listOfCellsOfWrongType.Append(pGeom); 
                    }
                    else
                    {
                        if (!listOfCellsInInputBodies.Locate(pCurrentCell)   )
                        {
                            IsIgnoredC = 1 ;
                             if(_iErrorWarningOutput) BordingCellWarning(_iErrorWarningOutput, pCurrentCell, pJournalItem);
                            listOfNotBordingCells.Append(pCurrentCell);
                        }
                    }
                }
                // If the order is not ignored, the created object is added to the 
                // createdObjects list
                if (IsIgnoredC == 0) createdObjects.Append(pChildCell);
                break;
            }
            // For each kept item, it is checked whether it is valid:
            // i.e. whether it belongs to a bording cell of an input body
            // or whether it is a CATFace/CATEdge/CATVertex
            // Otherwise the order is ignored
            //
        case CATCGMJournal::Keep:
            {
                int IsIgnoredK = 0 ;
                CATGeometry* pGeom = pJournalItem->GetKeptObject();
                CATCell * pCurrentCell = (CATCell *)pGeom;
                if (NULL==pGeom) return 1;
                
                checkTypeResult = CheckType(pGeom);
                if (checkTypeResult == 0) 
                {
                    IsIgnoredK = 1 ;
                     if(_iErrorWarningOutput) CellTypeWarning(_iErrorWarningOutput, pGeom, pJournalItem);
                    listOfCellsOfWrongType.Append(pGeom);
                }
                else
                {
                    if (!listOfCellsInInputBodies.Locate(pCurrentCell)   )
                    {
                        IsIgnoredK = 1 ;
                         if(_iErrorWarningOutput) BordingCellWarning(_iErrorWarningOutput, pCurrentCell, pJournalItem);
                        listOfNotBordingCells.Append(pCurrentCell);
                    }
                }
                
                if ( IsIgnoredK == 0 ) 
                {
                    listOfKeptCells.Append(pCurrentCell);
                    if (listOfCellsInBodyNoCopy.Locate(pCurrentCell) == 0)
                    {
                        // 
                        CATULONG32  persTag = pCurrentCell->GetPersistentTag() ;
                        char * Kept = " does not belong to any input body in No Copy mode";
                        if (_iErrorWarningOutput)
                        {
                            _iErrorWarningOutput->write("WARNING\n", strlen("WARNING\n"));
                            PrintAJournalItem(_iErrorWarningOutput, pJournalItem);
                            PrintAPersistentTag(_iErrorWarningOutput,persTag);
                            _iErrorWarningOutput->write(Kept,strlen(Kept));
                            _iErrorWarningOutput->write("\n * \n",strlen("\n * \n"));
                        }
                    }
                }
                break;
            }
            
            // For each deleted item, it is checked whether it is valid:
            // i.e. whether it belongs to a bording cell of an input body
            // or whether it is a CATFace/CATEdge/CATVertex
            // Otherwise the order is ignored
            //
        case CATCGMJournal::Deletion:
            {
                int IsIgnoredD = 0;
                const CATLISTP(CATGeometry)* oldObjDel = pJournalItem->GetDeletedObjects();
                if (NULL == oldObjDel) {return 1;}
               
                int numberOfOldObjDel = oldObjDel->Size();
                for (i = 1; i <= numberOfOldObjDel ; i++)
                {
                    CATCell * pCurrentCell = (CATCell*)((*oldObjDel)[i]); 
                    CATGeometry * pGeom = (*oldObjDel)[i];
                    checkTypeResult = CheckType(pGeom);
                    if (checkTypeResult == 0) 
                    {
                        IsIgnoredD = 1;
                         if(_iErrorWarningOutput) CellTypeWarning(_iErrorWarningOutput, pGeom, pJournalItem);
                        listOfCellsOfWrongType.Append(pGeom);
                    }
                    else  
                    {
                        if (!listOfCellsInInputBodies.Locate(pCurrentCell)   )
                        {
                            IsIgnoredD = 1 ;
                             if(_iErrorWarningOutput) BordingCellWarning(_iErrorWarningOutput, pCurrentCell, pJournalItem);
                            listOfNotBordingCells.Append(pCurrentCell);
                        }
                        
                    }
                }
                if (IsIgnoredD ==0)
                {
                    for (i = 1; i <= numberOfOldObjDel ; i++)
                    {
                        listOfDeletedCells.Append( (CATCell*)(*oldObjDel)[i]);
                    }
                }
            break;
            }
            
            
        case CATCGMJournal::Modification:
        case CATCGMJournal::Subdivision:
        case CATCGMJournal::Absorption:
            {
            //
            // For each modified item, it is checked whether it is valid:
            // i.e. whether it belongs to a bording cell of the resulting body
            // or whether it is a CATFace/CATEdge/CATVertex
            // Otherwise the order is ignored
            //
                int IsIgnoredM = 0;
                const CATLISTP(CATGeometry)* newObjModif = pJournalItem->GetNewObjects();
                int numberOfNewObjModif = newObjModif->Size();
                for (i = 1; i <= numberOfNewObjModif ; i++)
                {
                    CATGeometry * pGeom = (*newObjModif)[i];
                    checkTypeResult = CheckType(pGeom);
                    if (checkTypeResult == 0)  
                    {
                        IsIgnoredM = 1;
                        if(_iErrorWarningOutput) CellTypeWarning(_iErrorWarningOutput, pGeom, pJournalItem);
                        listOfCellsOfWrongType.Append(pGeom);
                    }
                    else
                    {
                        CATCell * pCurrentCell = (CATCell*)pGeom;
                        if (IsABordingCell(pCurrentCell,_iResult) == FALSE) 
                        {
                            IsIgnoredM = 1; 
                            listOfNotBordingCells.Append(pCurrentCell);
                            if(_iErrorWarningOutput) BordingCellWarning(_iErrorWarningOutput, pCurrentCell, pJournalItem);
                        }
                    }
                }
                 //
            // For each parent of a modified item, it is checked whether it is valid:
            // i.e. whether it belongs to a bording cell of the resulting body
            // or whether it is a CATFace/CATEdge/CATVertex
            // Otherwise the order is ignored
            //
                const CATLISTP(CATGeometry)* oldObjModif = pJournalItem->GetOldObjects();
                
                int numberOfOldObjModif = oldObjModif->Size();
                for (i = 1; i <= numberOfOldObjModif ; i++)
                {
                    CATGeometry * pGeom = (*oldObjModif)[i];
                    checkTypeResult = CheckType(pGeom);
                    if (checkTypeResult == 0) 
                    {
                        IsIgnoredM = 1;
                        if(_iErrorWarningOutput) CellTypeWarning(_iErrorWarningOutput,pGeom, pJournalItem);
                        listOfCellsOfWrongType.Append(pGeom);
                    }
                    else 
                    {
                        
                        CATCell * pCurrentCell = (CATCell*)pGeom;
                        if (! (listOfCellsInInputBodies.Locate(pCurrentCell))  )
                        {
                            IsIgnoredM = 1;
                            listOfNotBordingCells.Append(pCurrentCell);
                            if (_iErrorWarningOutput) BordingCellWarning(_iErrorWarningOutput,pCurrentCell, pJournalItem);
                        }
                    }
                    
                }
                if (IsIgnoredM == 0)
                {
                    for (i = 1; i <= numberOfNewObjModif ; i++)
                    {
                        modifiedObjects.Append((*newObjModif)[i]);
                    }
                    for (i = 1; i <= numberOfOldObjModif ; i++)
                    {
                        listOfParentsOfModified.Append((CATCell*)(*oldObjModif)[i] );
                    }

                }   
                break;
            }
        }
        
    }
    
    // In the resulting body, search for all the cells that created/modified, kept 
    // or in any input body in Copy Mode
    for (i = 1; i <= listOfCellsInResult.Size() ; i++)
    {
        CATGeometry * pCellResult = (listOfCellsInResult)[i];
        CATCell * pCell = (CATCell*)pCellResult;
        
        if ((!createdObjects.Locate(pCell)) 
            && (!modifiedObjects.Locate(pCell)) 
            && (!listOfCellsInBodyCopy.Locate(pCell)) 
            && (!listOfKeptCells.Locate(pCell)) != 0 )
            
        {
            listOfNotTracedCells.Append( (listOfCellsInResult)[i]);
        }
    }
        
        
        // 
        CATCGMJournal *duplJournal =pWorkingJournal->Duplicate(NULL);
        if (NULL == duplJournal) return 1 ;
        CATCGMJournalList * duplJournalList = duplJournal->CastToReportList();
        if (NULL == duplJournalList) return 1; // journal must be tassed
        CATBoolean GenericNamingRule = TRUE;
        CATCGMJournal* pNextJournal = NULL;
        while (pNextJournal = duplJournalList->Next(pNextJournal))
        {
            CATCGMJournalItem* pJournalItem = pNextJournal->CastToReportItem();
            if (!pJournalItem) {return 1 ;}
            
            // Ignoring a deactivated journal item
            //
            if (!pJournalItem->GetActiveMode()) continue;
            
            // Analyse only the orders whereby a cell is created or modified
            //
            CATCGMJournal::Type TopoEventType = pJournalItem->GetType();
            if ((TopoEventType == CATCGMJournal::Subdivision) || (TopoEventType == CATCGMJournal::Absorption))
                TopoEventType = CATCGMJournal::Modification;
            
            if ((TopoEventType == CATCGMJournal::Creation) || (TopoEventType == CATCGMJournal::Modification))
            {
                // case where [x],[y] -> Modification [a], [b]
                
                if (TopoEventType != CATCGMJournal::Creation) // then modification
                {
                    const CATLISTP(CATGeometry)* pNewObjects = pJournalItem->GetNewObjects();
                    if (!pNewObjects) return 1 ;
                    if (pNewObjects->Size() > 1)
                    {
                        int NumObject = 0;
                        int NumFirstObject = 0;
                        
                        // 
                        //
                        CATCell* pFirstCell = NULL;
                        for (NumFirstObject = 1; NumFirstObject < pNewObjects->Size(); NumFirstObject++)
                        {
                            CATGeometry * pLocalGeometry = (*pNewObjects)[NumFirstObject];
                            if (pLocalGeometry->IsATypeOf(CATCellType))
                            {
                                pFirstCell = (CATCell*)(pLocalGeometry);
                                break;
                            }
                        }
                        
                        if (pFirstCell != NULL)
                        {
                            // Compare the first cell founded with the ones coming up
                            for (NumObject = NumFirstObject + 1; NumObject <= pNewObjects->Size(); NumObject++)
                            {
                                CATGeometry * pLocalGeometry = (*pNewObjects)[NumObject];
                                if (pLocalGeometry->IsATypeOf(CATCellType))
                                {
                                    CATCell* pCell = (CATCell*)(pLocalGeometry);
                                    
                                    // if (!pCell) return 1;
                                    
                                    if (pFirstCell->GetDimension() != pCell->GetDimension())
                                    {
                                        
                                        char * messGN ="Cells with same parents and infos must be not of different type";
                                        if ( (listOfCellsInResult.Locate(pCell)) && (listOfCellsInResult.Locate(pFirstCell)) )
                                        {
                                            if (_iErrorWarningOutput)
                                            {
                                                _iErrorWarningOutput->write("ERROR\n", strlen("ERROR\n"));
                                                _iErrorWarningOutput->write("In\n", strlen("In\n"));
                                                PrintAJournalItem(_iErrorWarningOutput, pJournalItem);
                                                
                                                _iErrorWarningOutput->write(messGN,strlen(messGN));
                                                _iErrorWarningOutput->write("\n * \n",strlen("\n * \n"));
                                            }
                                            GenericNamingRule = FALSE;
                                            break;
                                        }
                                    }
                                }
                            } 
                        }  
                    }  
                } 
                
                // Compare with the orders that follow
                // Ex: Compare
                //        [11,12] -> Creation [15] info=1
                // with   [12,11] -> Creation [18] info=1
                
                CATCGMJournal* pNextJournalToCompare = pNextJournal;
                while (pNextJournalToCompare = duplJournalList->Next(pNextJournalToCompare))
                {
                    CATCGMJournalItem* pJournalItemToCompare = pNextJournalToCompare->CastToReportItem();
                    if (!pJournalItemToCompare)
                        return 1 ; // but journal is already tassed - useless
                    
                    if (!pJournalItemToCompare->GetActiveMode()) continue;			
                    CATCGMJournal::Type TopoEventTypeToCompare = pJournalItemToCompare->GetType();
                    
                    if ((TopoEventTypeToCompare == CATCGMJournal::Subdivision) || (TopoEventTypeToCompare == CATCGMJournal::Absorption))
                        TopoEventTypeToCompare = CATCGMJournal::Modification;
                    
                    if ((TopoEventTypeToCompare == CATCGMJournal::Creation) || (TopoEventTypeToCompare == CATCGMJournal::Modification))
                    {
                        if (TopoEventType == TopoEventTypeToCompare)
                        {
                            CATBoolean SameParents = TRUE;
                            
                            // Retrieve the parents
                            //
                            CATLISTP(CATGeometry) ListParents;
                            CATLISTP(CATGeometry) ListParentsToCompare;
                            
                            pJournalItem->GetFirstObjs(ListParents);
                            pJournalItemToCompare->GetFirstObjs(ListParentsToCompare);
                            
                            // Compare both lists
                            if (ListParents.Size() == ListParentsToCompare.Size())
                            {
                                for (int NumParent = 1; NumParent <= ListParents.Size(); NumParent++)
                                {
                                    if (!(ListParentsToCompare.Locate(ListParents[NumParent])))
                                    {
                                        SameParents = FALSE;
                                        break;
                                    }
                                }
                            }
                            else SameParents = FALSE;
                            
                            // do pJournalItem and pJournalItemToCompare bear the same info ?
                            //
                            CATBoolean SameInfo = FALSE;
                            
                            const CATCGMJournalInfo* pInfo = pJournalItem->GetAssociatedInfo();
                            const CATCGMJournalInfo* pInfoToCompare = pJournalItemToCompare->GetAssociatedInfo();
                            
                            if ((!pInfo) && (!pInfoToCompare))
                                SameInfo = TRUE;
                            else
                            {
                                if ((pInfo) && (pInfoToCompare))
                                {
                                    SameInfo = (pInfo->GetNumber() == pInfoToCompare->GetNumber());
                                }
                            }
                            
                            if ((SameParents) && (SameInfo))
                            {
                                // Retrieve the children
                                //
                                CATLISTP(CATGeometry) ListChildren;
                                CATLISTP(CATGeometry) ListChildrenToCompare;
                                
                                pJournalItem->GetLastObjs(ListChildren);
                                pJournalItemToCompare->GetLastObjs(ListChildrenToCompare);
                                
                                int NumChild = 0;
                                int NumChildToCompare = 0;
                                int NumChildToRemove = 0;
                                
                                // Remove what is not of CATCell type
                                // Should not be in the report
                                
                                CATLISTP(CATGeometry) ListGeometryToRemove;
                                for (NumChild = 1; NumChild <= ListChildren.Size(); NumChild++)
                                {
                                    CATGeometry * pLocalGeometry = ListChildren[NumChild];
									if (pLocalGeometry && !(pLocalGeometry->IsATypeOf(CATCellType)))
                                        ListGeometryToRemove.Append(pLocalGeometry);
                                }
                                
                                for (NumChildToRemove = 1; NumChildToRemove <= ListGeometryToRemove.Size(); NumChildToRemove++)
                                {
                                    ListChildren.RemoveValue(ListGeometryToRemove[NumChildToRemove]);
                                }
                                
                                ListGeometryToRemove.RemoveAll(CATCollec::KeepAllocation);
                                
                                for (NumChildToCompare = 1; NumChildToCompare <= ListChildrenToCompare.Size(); NumChildToCompare++)
                                {
									CATGeometry * pLocalGeometry = ListChildrenToCompare[NumChildToCompare];
                                    if (pLocalGeometry && !(pLocalGeometry->IsATypeOf(CATCellType)))
                                        ListGeometryToRemove.Append(pLocalGeometry);
                                }
                                
                                for (NumChildToRemove = 1; NumChildToRemove <= ListGeometryToRemove.Size(); NumChildToRemove++)
                                {
                                    ListChildrenToCompare.RemoveValue(ListGeometryToRemove[NumChildToRemove]);
                                }
                                
                                ListGeometryToRemove.RemoveAll(CATCollec::KeepAllocation);
                                
                                // 
                                CATBoolean SameDimension = TRUE;
                                
                                for (NumChild = 1; NumChild <= ListChildren.Size(); NumChild++)
                                {
                                    CATCell* pCell = (CATCell*)(ListChildren[NumChild]);
                                    
                                    if (!pCell) return 1;
                                    
                                    for (NumChildToCompare = 1; NumChildToCompare <= ListChildrenToCompare.Size(); NumChildToCompare++)
                                    {
                                        CATCell* pCellToCompare = (CATCell*)(ListChildrenToCompare[NumChildToCompare]);
                                        
                                        if (!pCellToCompare) return 1;
                                        
                                        if (pCell->GetDimension() != pCellToCompare->GetDimension())
                                        {
                                            // Test whether both cells are backtracked i.e. bording cells
                                            char * messGN ="Cells with same parents and infos must not be of different type";
                                            if ( (listOfCellsInResult.Locate(pCell)) && (listOfCellsInResult.Locate(pCellToCompare)) )
                                            {
                                                if (_iErrorWarningOutput)
                                                {
                                                    _iErrorWarningOutput->write("ERROR\n", strlen("ERROR\n"));
                                                    _iErrorWarningOutput->write("In\n", strlen("In\n"));
                                                    PrintAJournalItem(_iErrorWarningOutput,pJournalItem);
                                                    _iErrorWarningOutput->write("and\n", strlen("and\n"));
                                                    PrintAJournalItem(_iErrorWarningOutput,pJournalItemToCompare);
                                                    _iErrorWarningOutput->write(messGN,strlen(messGN));
                                                    _iErrorWarningOutput->write("\n * \n",strlen("\n * \n"));
                                                }
                                                SameDimension = FALSE;
                                                GenericNamingRule = FALSE;
                                                break;
                                            }
                                        }
                                    }
                                    
                                    // pJournalItemToCompare 
                                    // deactivated not to be processed later on
                                    //
                                    pJournalItemToCompare->SetActiveMode(0);
                                    
                                    if (!SameDimension) break;
                                    
                                } 
                            } 
            } 
                    } 
                } 
            } 
        } 
        
        // delete the temporary journal
        //
        delete duplJournal;
        duplJournal = NULL;
        
        // -----------------------------------------------------------------------
        // END GENERIC NAMING VALIDATION
        // -----------------------------------------------------------------------
        //
        //
        char * step1 = "\n(1) - Mandatory\n";
        char * step2 = "\n\n(2)\n";
        char * step3 = "\n\n(3)\n";
        char * step4 = "\n\n(4)\n";
        char * step5 = "\n\n(5)\n";
        char * strOK = " OK\n";
        char * strKO = " KO\n";
        
        // --------------------------------------------------------------------------------------
        // A - Writing the warning file and defining the verdict
        //     Warning file is filled in whatever the verbose mode
        // --------------------------------------------------------------------------------------
        //
        CATBoolean verdictCheck = TRUE;  // initializing the verdict
        //
        // ===============================================================================
        // Step 0 - List of cells in Copy mode not in the result and not deleted -> KO 
        // ===============================================================================
        //
        // (a) - Populate the list
        // 
        CATLISTP(CATCell) listOfCellsCopyNotOutputNeiDeleted;
        for (i = 1; i <= listOfCellsInBodyCopy.Size() ; i++)
        {
            CATGeometry * pCellResult = (listOfCellsInBodyCopy)[i];
            CATCell * pCell = (CATCell*)pCellResult;
            
            if  (!listOfCellsInResult.Locate(pCell)) // if not in resulting body
            {
                if  (!listOfParentsOfModified.Locate(pCell)) // if not in modified cells
                {
                    if (!listOfDeletedCells.Locate(pCell))  // if not deleted in the journal
                    {
                        listOfCellsCopyNotOutputNeiDeleted.Append(pCell);
                    }
                }
            } 
        }
        //
        // (b) - Verdict is KO if the list is not empty
        //
        if (listOfCellsCopyNotOutputNeiDeleted.Size() != 0)
        {
            verdictCheck = FALSE ;            
            
            // Print the list in warning file whatever the verbose mode
            // 
            if(_iErrorWarningOutput)
            {
                char * strC = "\nERROR\nCells in Copy mode not in the result body and not deleted\n"; 
                _iErrorWarningOutput->write(strC, strlen(strC));
                
                for (i = 1; i <= listOfCellsCopyNotOutputNeiDeleted.Size(); i++)
                {
					CATCell * pLocalCell = listOfCellsCopyNotOutputNeiDeleted[i];
					if (pLocalCell != NULL)
					{
                       CATULONG32  persTag = pLocalCell->GetPersistentTag() ;
                       char strPersTag[256] = "" ;
                       sprintf(strPersTag,"%d", persTag);
                       _iErrorWarningOutput->write(strPersTag,strlen(strPersTag));
                       _iErrorWarningOutput->write(" ",strlen(" "));
					}
                    
                }
            }
        }
        // Step 0a - List of cells in Copy mode & in the result and deleted -> KO 
        // 
        for (i = 1; i <= listOfCellsInResult.Size() ; i++) // all cells in Copy mode
        {
            CATGeometry * pCellResult = (listOfCellsInResult)[i];
            CATCell * pCell = (CATCell*)pCellResult;
            
            if  (listOfCellsInBodyCopy.Locate(pCell)) // if cell is in resulting body
            {
                if (listOfDeletedCells.Locate(pCell) )
                {
                    
                    {
                        listOfNotTracedCells.Append(pCell); // it is not backtracked
                    }
                }
            } 
        }
        // ==============================================================================
        // Warning: Step 1 - Checking that all cells in the resulting body can be traced back
        // ==============================================================================
        //
        // (a) - Populate the list (already done)
        // 
        // (b) - Verdict is KO if the list is not empty
        //
        listOfNotTracedCells.RemoveDuplicates();
        if ( (listOfNotTracedCells.Size() != 0) )
        {
            verdictCheck = FALSE ;
            
            // Print the list in warning file whatever the verbose mode
            // 
            if(_iErrorWarningOutput)
            {
                _iErrorWarningOutput->write("ERROR\n", strlen("ERROR\n"));
                char * NotTracedCells = "Cells of the result body that cannot be traced back\n" ;
                _iErrorWarningOutput->write(NotTracedCells,strlen(NotTracedCells));
                for (i = 1; i <= listOfNotTracedCells.Size(); i++)
                {
					CATCell * pLocalCell = listOfNotTracedCells[i];
					if (pLocalCell != NULL)
					{
                       CATULONG32  persTag = pLocalCell->GetPersistentTag() ;
                       char strPersTag[256] = "" ;
                       sprintf(strPersTag,"%d", persTag);
                       _iErrorWarningOutput->write(strPersTag,strlen(strPersTag));
                       _iErrorWarningOutput->write(" ",strlen(" "));
					}
                }
            }
        }
        
        // ==============================================================================
        // Warning: Step 2 - Checking that all reported cells are bording cells
        // ==============================================================================
         if (listOfNotBordingCells.Size() != 0)
        {
            // Print the list in warning file whatever the verbose mode
            // 
            if(_iErrorWarningOutput)
            {
                char * strN = "\nWARNING\nThe following cells are not bording cells:\n"; 
                _iErrorWarningOutput->write(strN, strlen(strN));
                
                for (i = 1; i <= listOfNotBordingCells.Size(); i++)
                {
					CATCell * pLocalCell = listOfNotBordingCells[i];
					if ( pLocalCell != NULL)
					{
                       CATULONG32  persTag = pLocalCell->GetPersistentTag() ;
                       char strPersTag[256] = "" ;
                       sprintf(strPersTag,"%d", persTag);
                       _iErrorWarningOutput->write(strPersTag,strlen(strPersTag));
                       _iErrorWarningOutput->write(" ",strlen(" "));
                    }
                }
            }
        }
        // ==============================================================================
        // Warning: Step 3 - Checking that all objects are cells
        // ==============================================================================
        //
        // (a) - Clean the list 
        //
        listOfCellsOfWrongType.RemoveDuplicates();
        //
        // (b) - Verdict not impacted if the list is not empty
        //
        if (listOfCellsOfWrongType.Size() != 0)
        {
            // Print the list in warning file whatever the verbose mode
            // 
            if(_iErrorWarningOutput)
            {
                char * strN = "\nWARNING\nThe following objects are not of CATFace/CATEdge/CATVertex type: \n"; 
                _iErrorWarningOutput->write(strN, strlen(strN));
                
                for (i = 1; i <= listOfCellsOfWrongType.Size(); i++)
                {
					CATGeometry * pLocalGeometry = listOfCellsOfWrongType[i];
					if ( pLocalGeometry != NULL)
					{
                       CATULONG32  persTag = pLocalGeometry->GetPersistentTag() ;
                       char strPersTag[256] = "" ;
                       sprintf(strPersTag,"%d", persTag);
                       _iErrorWarningOutput->write(strPersTag,strlen(strPersTag));
                       _iErrorWarningOutput->write(" ",strlen(" "));
                    }
                }
            }
        }
        // ==============================================================================
        // Warning: Step 4 - Checking the GN rule
        // ==============================================================================
        //
        // (a) - n list
        // (b) - already written in the warning file
        if (GenericNamingRule == FALSE)
        {
            // switched off temporarily
            // verdictCheck = FALSE ; 
        }
        //
        // ====================================================================================
        // A - Print in verbose mode in the verdict file
        // ====================================================================================
        //
        if((_iErrorVerdictOutput) && (_iVerdictVerbose == TRUE) )
        {
            // ==============================================================================
            // Verdict: Step 1 - Checking that all cells can be backtracked
            // ==============================================================================
            //
            char * strTracedCells = "Checking that all cells in result body can be traced back\n " ;
            _iErrorVerdictOutput->write(step1,strlen(step1));
            _iErrorVerdictOutput->write(strTracedCells,strlen(strTracedCells));
            if ((listOfNotTracedCells.Size() == 0 ) && (listOfCellsCopyNotOutputNeiDeleted.Size() == 0))
            {
                _iErrorVerdictOutput->write(strOK,strlen(strOK));
            }
            else
            {
                _iErrorVerdictOutput->write(strKO,strlen(strKO));
                verdictCheck = FALSE ; // already specified  - should be removed
            }  
            
            // ==============================================================================
            // Verdict: Step 2 - Checking that all objects are cells
            // ==============================================================================
            //
            char * cellType = "Checking that all reported cells are of CATFace/CATEdge/CATVertex type\n " ;
            if (_iErrorVerdictOutput)
            {
                _iErrorVerdictOutput->write(step2,strlen(step2));
                _iErrorVerdictOutput->write(cellType,strlen(cellType));
                if (listOfCellsOfWrongType.Size() == 0)
                {
                    _iErrorVerdictOutput->write(strOK,strlen(strOK));
                }
                else
                {
                    _iErrorVerdictOutput->write(strKO,strlen(strKO));
                }
            }
            // ==============================================================================
            // Verdict: Step 3 - Checking that all cells reported as created/modified
            //                   are in the result
            // ==============================================================================
            //
            char * strBorder = "Checking that all reported cells are bording cells\n " ;
            if (_iErrorVerdictOutput)
            {
                _iErrorVerdictOutput->write(step3,strlen(step3));
                _iErrorVerdictOutput->write(strBorder,strlen(strBorder));
                if (listOfNotBordingCells.Size() == 0)
                {
                    _iErrorVerdictOutput->write(strOK,strlen(strOK));
                }
                else
                {
                    _iErrorVerdictOutput->write(strKO,strlen(strKO));
                }
            }
            //
            // ==============================================================================
            // Verdict: Step 4 - Checking the GN rules
            // ==============================================================================
            //
            char * strGN = "Checking that cells with same parents & infos are not of different type\n " ;
            if (_iErrorVerdictOutput)
            {
                _iErrorVerdictOutput->write(step4,strlen(step4));
                _iErrorVerdictOutput->write(strGN,strlen(strGN));
                if (GenericNamingRule == TRUE)
                {
                    _iErrorVerdictOutput->write(strOK,strlen(strOK));
                }
                else
                {
                    _iErrorVerdictOutput->write(strKO,strlen(strKO));
                    // switched off temporarily
                    // verdictCheck = FALSE ; 
                }
            }
            
        }
        
        // End of print in the verdict file in verbose mode
        // =================================================================================
        
        
        // =================================================================================
        // Print the journal at the end of the verdict file when it is invalid
        // =================================================================================
        //
        if (verdictCheck == FALSE)
        {
            if (_iErrorVerdictOutput)
            {
                _iErrorVerdictOutput->write("\n\nTOPOLOGICAL JOURNAL\n",strlen("\n\nTOPOLOGICAL JOURNAL\n"));
               _iReport->Tass();
                while (Next = _iReport->Next(Next))
                {
                    CATCGMJournalItem* pJournalItem = Next->CastToReportItem();
                    if (!pJournalItem) 
                    {   
                        cout << "Tass problem" << endl;
                        return 1;
                    }
                    
                    // Print the journal to be checked - if need be
                    PrintAJournalItem(_iErrorVerdictOutput,pJournalItem);
                }
            }
            
        }
        
        // =================================================================================
        // Print bodies' contents in the warning file
        // =================================================================================
        //
        if(_iErrorWarningOutput)
        {
            char * strCopy = "\n\nList of Bodies in Copy Mode"; 
            _iErrorWarningOutput->write(strCopy, strlen(strCopy));
            CATULONG32  persTagBod = 0;
            CATULONG32  persTagCell = 0;
            CATLISTP(CATCell) listOfCellsInBody;
            listOfCellsInBody.RemoveAll();
            
            // (a) - List of cells in bodies in Copy Mode
            //
            for (i = 1; i <= _InputsCopy.Size(); i++)
            {
				CATBody * pLocalBody = _InputsCopy[i];
				if ( pLocalBody != NULL)
				{
                   persTagBod = pLocalBody->GetPersistentTag() ;
				   _iErrorWarningOutput->write("\nBody ",strlen("\nBody "));
                   PrintAPersistentTag(_iErrorWarningOutput,persTagBod);
                   _iErrorWarningOutput->write(" - List of cells: ",strlen(" - List of cells: "));
                
                   GetBodyCells (pLocalBody,  listOfCellsInBody);
                
                   for (int j = 1; j <= listOfCellsInBody.Size(); j++)
				   {
					   CATCell * pLocalCell = listOfCellsInBody[j];
					   if ( pLocalCell != 0 )
					   {
                           persTagCell = pLocalCell->GetPersistentTag() ;
                           PrintAPersistentTag(_iErrorWarningOutput,persTagCell);
                           _iErrorWarningOutput->write(" ",strlen(" "));
					   }
				   }
                   listOfCellsInBody.RemoveAll();
				}
            }
            
            // (b) - List of cells in bodies in No Copy Mode
            //
            char * strNoCopy = "\n\nList of Bodies in No Copy Mode"; 
            _iErrorWarningOutput->write(strNoCopy, strlen(strNoCopy));
            
            for (int k = 1; k <= _InputsNoCopy.Size(); k++)
            {
				CATBody * pLocalBody = _InputsNoCopy[k];
				if ( pLocalBody != NULL )
				{
                    persTagBod = pLocalBody->GetPersistentTag() ;
                    _iErrorWarningOutput->write("\nBody ",strlen("\nBody "));
                    PrintAPersistentTag(_iErrorWarningOutput,persTagBod);
                    _iErrorWarningOutput->write(" - List of cells: ",strlen(" - List of cells: "));
                
                    GetBodyCells (pLocalBody,  listOfCellsInBody);
                
                    for (int l = 1; l <= listOfCellsInBody.Size(); l++)
					{
						CATCell * pLocalCell = listOfCellsInBody[l];
						if ( pLocalCell != NULL )
						{
                            CATULONG32  persTagCell = pLocalCell->GetPersistentTag() ;
                            PrintAPersistentTag(_iErrorWarningOutput,persTagCell);
                            _iErrorWarningOutput->write(" ",strlen(" "));
						}
					}
                    listOfCellsInBody.RemoveAll();
				}
            }
            
            // (c) - List of cells in the resulting body
            //
            char * strResult = "\n\nBody Result\n"; 
            _iErrorWarningOutput->write(strResult, strlen(strResult));
            
            _iErrorWarningOutput->write("Body ",strlen("Body "));
            persTagBod = _iResult->GetPersistentTag() ;
            PrintAPersistentTag(_iErrorWarningOutput,persTagBod);
            _iErrorWarningOutput->write(" - List of cells: ",strlen(" - List of cells: "));
            
            GetBodyCells (_iResult,  listOfCellsInBody);
            
            for (int m = 1; m <= listOfCellsInBody.Size(); m++)
            {
				CATCell * pLocalCell = listOfCellsInBody[m];
				if ( pLocalCell != NULL  )
				{
                    CATULONG32  persTagCell = pLocalCell->GetPersistentTag() ;
                    PrintAPersistentTag(_iErrorWarningOutput,persTagCell);
                    _iErrorWarningOutput->write(" ",strlen(" "));
				}
            }
            listOfCellsInBody.RemoveAll();
            
        }
        // 
        // End of print
        char * strComp = NULL;
        char * strEnd = NULL;
        char * endHTML= NULL;
        
        
        strComp = " \n</xmp>\n<p><font color='#FF0000'>TOPOLOGICAL JOURNAL FOR FEATURE ";
        strEnd =  " </font>\n</p>\n";
        
        endHTML= "\n</body>\n</html>";
        
        
        char * strSep = "\n----------------------------------------------------------------\n";
        
        if (verdictCheck == FALSE)
        {
            rc = 2;
        }
        else
        {
            rc = 0;
        }
       
        if ((_iErrorVerdictOutput) && (_iErrorWarningOutput))
        {
            _iErrorVerdictOutput->write(strComp,strlen(strComp));
            _iErrorVerdictOutput->write(featName,strlen(featName));
            _iErrorWarningOutput->write(strComp,strlen(strComp));
            _iErrorWarningOutput->write(featName,strlen(featName));
            
            if (verdictCheck == FALSE)
            {
                _iErrorVerdictOutput->write(strKO,strlen(strKO));
                _iErrorWarningOutput->write(strKO,strlen(strKO));
            }
            else
            {
                _iErrorVerdictOutput->write(strOK,strlen(strOK));
                _iErrorWarningOutput->write(strOK,strlen(strOK));
            }
            _iErrorVerdictOutput->write(strEnd,strlen(strEnd));
            _iErrorVerdictOutput->write(strSep,strlen(strSep));
            _iErrorWarningOutput->write(strEnd,strlen(strEnd));
            _iErrorWarningOutput->write(strSep,strlen(strSep));
            
            
            // closing the HTML output
            //
            _iErrorVerdictOutput->write("\n*\n",strlen("\n*\n"));
            _iErrorWarningOutput->write("\n*\n",strlen("\n*\n"));
            _iErrorVerdictOutput->write(endHTML,strlen(endHTML));
            _iErrorWarningOutput->write(endHTML,strlen(endHTML));
        }
        
        delete pWorkingJournal;
        pWorkingJournal = NULL;
        if (rc == 0) 
        {
            return 0;
        }
        else 
            return 1;
}
