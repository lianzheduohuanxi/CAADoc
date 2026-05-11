
/**
 * @quickReview GDU GDU 04:04:20 OpenDocument instead of Open on CATDocumentServices 
 * @quickReview KDR KDR 03:07:11
 */

/**
 * @fullreview RCI RCI 01:08:31
 * @error UDOO Y err_1 pProcessList not set to NULL after delete
 * @error UNH Y err_3 spActivityRoot not tested before use
 * @error UNH Y err_4 spAssemblyActivity not tested before use
 * @error UNH Y err_5 spFirstItem not tested before use
 */

// --------------------------------------------------------
//
// COPYRIGHT DASSAULT SYSTEMES 1999
//

/* 
* ----------------------------------------------------------------------------------------------- 
* Abstract:
* --------
* This sample illustrates navigating in an existing process document.
* 
*		- 1. Load an existing CATProcess document
*		- 2. Retrieve root activity
*		- 3. Browse items
*		- 4. Get their label and types.
*
* Usage :
* ------
*		To run this sample, you can use the command:
*		mkrun -c "CAADmiBrowse input.CATProcess ActivityType"
*		where input.CATProcess is an existing process document (note that the associated
*		.act has to be in the same directory as the document to browse)
*		and ActivityType is the kind of activity that we want to filter.  
*       For example, you can enter "CAADmiPlace" for an activity type defined
*       in the .act file created in use case "CAADmiGenerLibrary".
*
* Return Errors:
* -------------
*  1 - ERROR bad argument number
*  2 - ERROR in loading existing CATProcess
*  3 - ERROR in retrieving process container
*  4 - ERROR in searching children process
*  5 - ERROR in Query Interface
*  6 - ERROR in removing document
*
* ----------------------------------------------------------------------------------------------- 
*  mod      KDR       07-11-2003      Replaced the hard-coded strings in cout by CATUnicodeStrings
* ----------------------------------------------------------------------------------------------- 
*/
#include "iostream.h"

// Framework ObjectModelerBase
#include "CATInit.h"
#include "CATSessionServices.h"
#include "CATDocumentServices.h"
#include "CATDocument.h"

// Framework System
#include "CATUnicodeString.h"

// Framework DMAPSInterfaces
#include "CATISPPProcessContainer.h"
#include "CATISPPActivityRoot.h"
#include "CATISPPChildManagement.h"
#include "CATISPPItemMgt.h"
#include "CATISPPItem.h"


/* ---------------------------------------------------------------------------------------------- */

int main(int argc, char * argv[] )
{ 

	HRESULT rc = E_FAIL;
	/* ------------------------------------*/
	/*  0. Control of arguments number     */
	/* ------------------------------------*/
	if ( 3 != argc )
	{
        CATUnicodeString ErrorArguements = "ERROR : bad number of arguments  " ;
		cout << ErrorArguements.ConvertToChar() << argc << endl << flush;
		return 1;  
	} 
	
	/* -----------------------------------------*/
	/*  1. Load an existing CATProcess document */
	/* -----------------------------------------*/
	CATSession* pSession = NULL;
	rc = ::Create_Session("CAA2_Sample_Session", pSession);

	CATDocument* pProcessDoc = NULL;
	rc = CATDocumentServices::OpenDocument(argv[1],pProcessDoc);
	if ( FAILED(rc) || (NULL==pProcessDoc)) return 2;

    CATUnicodeString DocOpenedMsg = "CAAPpbBrowse.m:	Process document opened : ";
	cout << endl << DocOpenedMsg.ConvertToChar() << argv[1] << endl << flush;

	CATInit *piInitOnDoc = NULL;
	rc = pProcessDoc -> QueryInterface(IID_CATInit,
		                               (void**) &piInitOnDoc);
	if (FAILED(rc) ) return 5;

	/* ----------------------------------------------*/
	/*   2. get activity root of CATProcess document */
	/* ----------------------------------------------*/
	// get all processes 
    CATISPPProcessContainer *piProcessCont = (CATISPPProcessContainer* )
		piInitOnDoc -> GetRootContainer("CATISPPProcessContainer");
	if ( NULL == piProcessCont ) return 3;
	piInitOnDoc -> Release();
	piInitOnDoc = NULL;
    
    CATLISTV(CATBaseUnknown_var) *pProcessList = 
		piProcessCont->GetAllProcess();
	piProcessCont -> Release();
	piProcessCont = NULL;
    if ((NULL == pProcessList) || ((*pProcessList).Size() < 1))
    { 
        CATUnicodeString EmptyListMsg = "** ERROR empty list of process ";
		cout << EmptyListMsg.ConvertToChar()  << endl;
/** @anchor err_1 pProcessList not set to NULL after delete */ 
        if ((*pProcessList).Size() > 0)
			{
				delete pProcessList;
				pProcessList = NULL;
			}
		return 4;
    }
    CATUnicodeString NoProcMsg = "Number of processes in the document : "; 
	cout << NoProcMsg.ConvertToChar() << (*pProcessList).Size() << endl << flush;

	// root activity is the first of the list of processes.
    CATISPPActivityRoot_var spActivityRoot = (*pProcessList)[1];
    delete pProcessList;
	pProcessList=NULL;
    

	/* --------------------------------------------*/
	/*   3. Browse items                           */
	/* --------------------------------------------*/
	
	// handle on CATISPPChildManagement on the process.    
    CATISPPChildManagement *piChildMgtOnActivity = NULL;
/** @anchor err_3 spActivityRoot not tested before use */ 
	if ( NULL_var == spActivityRoot ) return 4;
	rc = spActivityRoot -> QueryInterface(IID_CATISPPChildManagement,
		                                  (void**) &piChildMgtOnActivity);
    if (FAILED(rc)) return 5;
    
	// get activities children of type given in argument.
    CATUnicodeString NoChildMsg = "Number of children under root activity : ";
	cout << NoChildMsg.ConvertToChar() << piChildMgtOnActivity -> GetNumberOfChild() << endl << flush;

    CATUnicodeString SameFiltMsg = "Same, but filtered with given type: ";
    CATUnicodeString ColonMsg = " : ";
	cout << SameFiltMsg.ConvertToChar() << argv[2] << ColonMsg.ConvertToChar() << 
		piChildMgtOnActivity -> GetNumberOfChild(argv[2]) << endl << flush;

	if (0 != piChildMgtOnActivity -> GetNumberOfChild(argv[2]))
	{
		CATListValCATBaseUnknown_var *pListChildren = 
			piChildMgtOnActivity->GetChild();
				
		if ((NULL != pListChildren ) && (0 != (*pListChildren).Size()))
		{
			CATBaseUnknown_var spAssemblyActivity = (*pListChildren)[1];
			delete pListChildren;
			pListChildren=NULL;
			
			// get list of items concerned by activity.
			CATISPPItemMgt	*piItemMgtOnActivity = NULL;
/** @anchor err_4 spAssemblyActivity not tested before use */ 
			if ( NULL_var ==  spAssemblyActivity ) return 4;
			rc = spAssemblyActivity -> QueryInterface(IID_CATISPPItemMgt,
				                                      (void**) &piItemMgtOnActivity);
			if (FAILED(rc)) return 5;
			
            CATUnicodeString ItemAssoMsg =  "Number of items associated to root activity : ";
			cout << ItemAssoMsg.ConvertToChar() << piItemMgtOnActivity->GetNumberOfItems() << endl << flush;
			CATListValCATBaseUnknown_var *pItemsLists =
				piItemMgtOnActivity->GetItems();
			piItemMgtOnActivity->Release();
			piItemMgtOnActivity = NULL;
			if ((NULL != pItemsLists) && (0 != (*pItemsLists).Size())) 
			{		
				CATBaseUnknown_var spFirstItem = (*pItemsLists)[1];
				delete pItemsLists;
				pItemsLists = NULL;
				
				/* ----------------------------------------------*/
				/*   4. Informations on items  ( label & Typem ) */
				/* ----------------------------------------------*/
				// Informations on items
				CATISPPItem *piItemOnItem = NULL;
/** @anchor err_5 spFirstItem not tested before use */ 
				if ( NULL_var == spFirstItem ) return 4;
				rc = spFirstItem -> QueryInterface(IID_CATISPPItem,
					(void**) &piItemOnItem);
				if (FAILED(rc)) return 5;
				
				CATUnicodeString LabelItem = piItemOnItem->GetLabel();
				cout << " - Label \"" << LabelItem.CastToCharPtr() << "\"."
					<< endl << "    - Type : " << (piItemOnItem->GetType()).CastToCharPtr()
					<< endl << flush;;
				piItemOnItem->Release();
				piItemOnItem=NULL;
			}
			
		}
	}
    piChildMgtOnActivity->Release();
    piChildMgtOnActivity=NULL;
	/* ----------------------------------- */
	/*    ends session                      */
	/* ----------------------------------- */
	// remove opened document
	rc = CATDocumentServices::Remove (*pProcessDoc);
	if (!SUCCEEDED(rc)) return 6;
	
	// delete the session, removes the opened documents also.
	// never forget to delete a creating session after usage.
	
	rc = ::Delete_Session("CAA2_Sample_Session"); 
    
	return rc;
}
