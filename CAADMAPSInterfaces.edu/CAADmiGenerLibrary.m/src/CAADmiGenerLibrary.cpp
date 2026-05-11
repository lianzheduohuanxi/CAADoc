/**
 * @fullreview RCI RCI 01:08:31
 *
 * @quickReview KDR KDR 03:07:11
 */
// --------------------------------------------------------
//
// COPYRIGHT DASSAULT SYSTEMES 1999
//

/* 
* ----------------------------------------------------------------------------------------------- 
* Abstract:
* --------
* This sample illustrates creation of a process document.
* 
*		- 1. Creates a .act document.
*		- 2. Gets root element activity.
*		- 3. Define activities
*
* Usage :
* ------
*		To run this sample, you can use the command:
*		mkrun -c "CAADmiGenerLibrary output.act "    
*
* Return Errors:
* -------------
*  1 - ERROR bad argument number
*  2 - ERROR in creating .act document
*  3 - ERROR in searching root elem
*  4 - ERROR in saving document
*  5 - ERROR in removing document
*  6 - ERROR in QueryInterface
* ----------------------------------------------------------------------------------------------- 
* 
* ----------------------------------------------------------------------------------------------- 
*   cre      RCI      ??             Original code
*   mod      KDR      07-11-2003     Replaced the hard-coded strings for couts by Unicodestrings
* ----------------------------------------------------------------------------------------------- 
*/


#include "iostream.h"

// Framework ObjectModelerBase
#include "CATSessionServices.h"           // Create_Session and Delete_Session
#include "CATDocument.h"                  // Document
#include "CATDocumentServices.h"          // New ,SaveAs, Remove document
#include "CATInit.h"                      // GetRootContainer

// Interfaces Process
#include "CATISPPActivityType.h"          // Manage different types of Activities
#include "CATISPPActivityTypeFactory.h"   // Create new Activity Types


// --------------------------------------------------------------------------------------------------------------- 
int main(int argc, char * argv[])
{
	HRESULT rc = E_FAIL;
	/* ------------------------------------*/
	/*  0. Control of arguments number     */
	/* ------------------------------------*/
	 if ( 2 != argc )
	 {
         CATUnicodeString ErrorMsg =  "ERROR : bad number of arguments ";
		 cout << ErrorMsg.ConvertToChar() << argc << endl << flush;
		 return 1;  
	 } 

	/* ---------------------------------------------------- */
	/*  1. Creates a .act document  (library of activities) */
	/* ---------------------------------------------------- */
	CATSession *pSession = NULL;
	rc = ::Create_Session("CAA2_Sample_Session", pSession );
	
	CATDocument *pActDoc = NULL;
	rc = CATDocumentServices::New("ProcessLibrary", pActDoc );
	if ( FAILED(rc) || (NULL==pActDoc) )
		return 2;

	/* ---------------------------------------*/
	/*  2. Get root element of the document   */
	/* ---------------------------------------*/
	CATInit *pInitOnDoc = NULL;
	rc = pActDoc -> QueryInterface (IID_CATInit,
		                            (void**) &pInitOnDoc);
	if (FAILED(rc)) return 6;

    CATISPPActivityTypeFactory *piRootActivity = (CATISPPActivityTypeFactory* )
		pInitOnDoc->GetRootContainer("CATISPPActivityTypeFactory");
	if ( NULL == piRootActivity )
		return 3;

	pInitOnDoc -> Release();
	pInitOnDoc = NULL;
	
	/* ---------------------------------------*/
	/*  3. Define activities                  */
	/* ---------------------------------------*/
	// define two kind of activities :
	// CAAAssembly to assemble objects
	// CAAPlace to place objects 
    CATISPPActivityType_var spAssemblyActvity =
		piRootActivity->CreateActivityType("CAADmiAssembly");
    CATISPPActivityType_var spPlaceActivity = 
		piRootActivity->CreateActivityType("CAADmiPlace");
	piRootActivity -> Release();
	piRootActivity = NULL;

	/* ----------------------------------------- */
	/*  Save the resulting .act                  */
	/* ----------------------------------------- */
    CATUnicodeString SavedMsg = "CAAPpbGenerLibrary.m:	Now we can save the created library in ";
	cout << endl << SavedMsg.ConvertToChar() << argv[1] << endl << flush;
	rc = CATDocumentServices::SaveAs(*pActDoc, argv[1]);
	if (FAILED(rc)) return 4;
	
	/* ----------------------------------------- */
	/*   Ends the session                        */
	/* ----------------------------------------- */
	
	// remove opened document
	rc = CATDocumentServices::Remove (*pActDoc);
	if (!SUCCEEDED(rc)) return 5;

	// delete the session, removes the opened documents also.
	// never forget to delete a creating session after usage.
	rc = ::Delete_Session("CAA2_Sample_Session");


    return rc;
}
