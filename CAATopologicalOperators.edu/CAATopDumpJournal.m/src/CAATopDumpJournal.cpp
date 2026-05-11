// COPYRIGHT DASSAULT SYSTEMES  2002

#include <iostream.h>

// Mathematics
#include "CATSoftwareConfiguration.h"  // the software configuration

// GeometricObjects
#include "CATCGMJournalList.h"
#include "CATCGMJournalInfo.h"
#include "CATCGMJournalItem.h"
#include "CATCGMJournal.h"

#include "CAADumpJournal.h"

// Displays the journal on the standard output
// Returns 0 OK -
// Returns 1 -> problem has been detected either because there is no
// constructed object in a Creation statement or
// no deleted object in Deletion statement
//
int CAATopDumpJournal(CATCGMJournalList*     iJournal)                                    
{
    if (NULL== iJournal) return 1;
    int rc = 0;
    CATCGMJournal* Next = NULL;
    while (Next = iJournal->Next(Next))
    {
        CATCGMJournalItem* pJournalItem = Next->CastToReportItem();
        
        if (NULL==pJournalItem)
        {
            cout << "You must tass the journal" << endl;
            return (1);
        }
        CATLISTP(CATGeometry) parentList;
        pJournalItem->GetFirstObjs(parentList);
        int numberParentList = parentList.Size();
        //
        // If no parents - that is "[ ] -> Creation [xx]"  for example
        //
        if (numberParentList == 0) 
        {
            cout << "[ ]" ;
        }
        //
        // If several parents "[ Edge 1, Vertex 2] -> Modification [xx,yy]" for example
        //
        int i = 1;
for (; i <= numberParentList; i++)
        {
            cout << "[" ;
            char * str1 = " ";
            if ((parentList)[i]->IsATypeOf(CATFaceType)) { str1 = "Face_";   }
            else if ((parentList)[i]->IsATypeOf(CATEdgeType)) {  str1 = "Edge_";   }    
            else if ((parentList)[i]->IsATypeOf(CATVertexType)) {  str1 = "Vertex_";   }
            else  { str1 = "UnauthorizedType_";   }
            cout << str1 ;
            
            CATULONG32  persTag = (parentList)[i]->GetPersistentTag() ;
            cout << persTag;
            cout << "]" ;
            if (i < numberParentList) cout << ",";
        }
        //
        // Print the type
        //
        CATCGMJournal::Type CGMEventType = pJournalItem->GetType();
        switch (CGMEventType)
        {  
        case CATCGMJournal::Creation:
            {
                cout << "->Creation";
                break;
            }
        case CATCGMJournal::Modification:
            {
                 cout << "->Modification";
                break;
            }
        case CATCGMJournal::Subdivision:
            {
                cout << "->Subdivision";
                break;
            }
        case CATCGMJournal::Absorption:
            {
                 cout << "->Absorption";
                break;
            }
        case CATCGMJournal::Deletion:
            {
                cout << "->Deletion";
                break;
            }
        case CATCGMJournal::Keep:
            {
                cout << "->Keep" ;
                break;
            }
        }
        //
        // Print the children
        //
        CATLISTP(CATGeometry) childrenList;
        pJournalItem->GetLastObjs(childrenList);
        int numberChildrenList = childrenList.Size();
        
        for (i = 1; i <= numberChildrenList; i++)
        {
            cout <<"[";
            char * str1 = " ";
            if ((childrenList)[i]->IsATypeOf(CATFaceType)) { str1 = "Face_";   }
            else if ((childrenList)[i]->IsATypeOf(CATEdgeType)) {  str1 = "Edge_";   }    
            else if ((childrenList)[i]->IsATypeOf(CATVertexType)) {  str1 = "Vertex_";   }
            else  { str1 = "UnauthorizedType_";   }
            cout << str1;
            
            CATULONG32  persTag = (childrenList)[i]->GetPersistentTag() ;
            cout <<  persTag;
            cout << "]" ;
            if (i < numberChildrenList) cout << ",";
        }
        
        // Print the infos if any
        //
        const CATCGMJournalInfo * journalInfo = pJournalItem->GetAssociatedInfo();
        if (journalInfo)
        {
            CATLONG32 infoNumber = journalInfo->GetNumber();
            cout << " Info = " << infoNumber ;
        }
        cout << endl;
    }
    return rc ;
} 
