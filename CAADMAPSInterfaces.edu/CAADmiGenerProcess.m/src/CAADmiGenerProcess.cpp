
/**
 * @quickReview GDU GDU 04:04:20 OpenDocument instead of Open on CATDocumentServices 
 * @quickReview KDR KDR 03:07:11
 */


/**
 * @fullreview RCI RCI 01:08:31
 * @error UNH Y err_1 spActivityRoot not tested before use
 * @error UNH Y err_2 spActivityRoot not tested before use
 * @error UNH Y err_3 spAssemblyProcess not tested before use
 * @error UNH Y err_4 spPlaceActivity1 not tested before use
 * @error UNH Y err_5 spPlaceActivity2 not tested before use
 * @error UNH Y err_6 spAssemblyProcess not tested before use
 * @error UNH Y err_7 spRootProduct not tested before use
 * @error UNH Y err_8 spItem not tested before use
 * @error UNH Y err_9 spAssemblyProcess not tested before use
 * @error UNH y err_10 spPlaceActivity1 not tested before use
 * @error UNH Y err_11 spPlaceActivity2 not tested before use
 * @error UNH Y err_12 spRoot not tested before use
 * @error UNH Y err_13 spResource not tested before use
 * @error UNH Y err_14 spAssemblyProcess not tested before use
 */
// --------------------------------------------------------
//
// COPYRIGHT DASSAULT SYSTEMES 1999
//

/* 
* ----------------------------------------------------------------------------------------------- 
* Abstract:
* --------
* This sample illustrates the creation of a process document.
* 
*		- 1. Creates a CATProcess document.
*		- 2. Gets root activity.
*		- 3. Sets a user name ( label ) on the root activity.
*		- 4. Instantiates activities from a library of activities.
*		- 5. Manages control flow between those activities.
*       - 6. Sets an item to an activity.
*		- 7. Adds resources on activities. 
*       - 8. Saves the resulting process          
*       - 9. Ends the session 
*
*	item = what will be done
*   activity = how it wil be done
*	resource = with what it will be done.
* 
* Usage :
* ------
*		To run this sample, you can use the command:
*		mkrun -c "CAADmiGenerProcess input.act inputItem.CATProduct inputResource.CATProduct
*                                    output.CATProcess "   
*		where     - input.act : path to library file of activities. Here we use the 
*                       one generated in CAAGenerLibrary sample.
*				  - inputItem.CATProduct : path to product defining items. It may be an another
*                       kind of document. The sample illustrates here the case of items defined
*                       in CATProducts. See the one in:
*                       CAADMAPSInterfaces.edu/CNext/Resources/Graphic/CAADmiItem.CATProduct
*				  - inputRessource.CATProduct :path to product defining items. It may be another
*                       kind of document. The sample illustrates here the case of items defined
*                       in CATProducts. See the one in:
*                       CAADMAPSInterfaces.edu/CNext/Resources/CAADmiResource.CATProduct
*				  - output.CATProcess : resulting process
*
* Return Errors:
* -------------
*  1 - ERROR bad argument number
*  2 - ERROR in creating process document
*  3 - ERROR in searching root element
*  4 - ERROR in getting processes
*  5 - ERROR in QueryInterface
*  6 - ERROR in Opening document containing items
*  7 - ERROR in Opening document containing resources
*  8 - ERROR in saving CATProcess document
*  9 - ERROR in removing CATProcess document
*
* ----------------------------------------------------------------------------------------------- 
*/

#include "iostream.h"

// Framework ProductStructure
#include "CATIProduct.h"                  // To navigate in the product document

// Framework ObjectModelerBase
#include "CATSessionServices.h"           // Create_Session and Delete_Session
#include "CATDocument.h"                  // Document
#include "CATSession.h"					  // Session
#include "CATDocumentServices.h"          // New, SaveAs, Remove document
#include "CATIDocRoots.h"                 // root element of a CATProduct
#include "CATInit.h"                      // root container of process document.

// Framework DMAPSInterfaces
#include "CATISPPFlowMgt.h"               // to manage flows between activities
#include "CATISPPActivityRoot.h"          // root activity
#include "CATISPPItemMgt.h"               // to manage association of Items with Activity 
#include "CATISPPChildManagement.h"       // Interface to manage Hierarchy, relationship 
                                          //   Father - Son
#include "CATISPPAbstractActivity.h"      // to manage label on an activity
#include "CATISPPProcessContainer.h"      // to manage process container
#include "CATISPPResourceManagement.h"    // to manage resources
#include "CATISPPConfig.h"                // to manage libraries difining activities.

// --------------------------------------------------------------------------------------------------------------- 
int main(int argc, char * argv[])
{
	HRESULT rc = E_FAIL;
	
	/* ------------------------------------*/
	/*  0. Control of arguments number     */
	/* ------------------------------------*/
	 if ( 5 != argc )
	 {
         CATUnicodeString ErrorMsg = "ERROR : bad number of arguments ";
		 cout << ErrorMsg.ConvertToChar()  << argc << endl << flush;
		 return 1;  
	 } 

	/* -------------------------------------*/
	/*  1. Creates a CATProcess document    */
	/* -------------------------------------*/
	CATSession *pSession = NULL;
	rc = ::Create_Session("CAA2_Sample_Session", pSession );

	CATListOfCATUnicodeString ActivityLibrariesList;
	ActivityLibrariesList.Append(argv[1]);
	CATISPPConfig *piConfigSession = NULL;
        if (pSession)
	  rc = pSession -> QueryInterface(IID_CATISPPConfig,
		                            (void**) &piConfigSession);
	if (FAILED(rc) ) return 5;

	piConfigSession->SetListOfLibraryFilePath(ActivityLibrariesList);
	piConfigSession->Release();
	piConfigSession = NULL;


	CATDocument *pNewDoc = NULL;
	rc = CATDocumentServices::New("Process", pNewDoc );
	if ( FAILED(rc) || (NULL==pNewDoc))	return 2;

	CATInit *piInitOnDoc = NULL;
	rc = pNewDoc -> QueryInterface(IID_CATInit,
		                            (void**) &piInitOnDoc);
	if (FAILED(rc) ) return 5;


	/* -------------------------------------*/
	/*  2. Gets root activity               */
	/* -------------------------------------*/
	// Get all processes
	CATISPPProcessContainer *piProcessCont = NULL;
	piProcessCont = (CATISPPProcessContainer* )
		piInitOnDoc->GetRootContainer(CATISPPProcessContainer::ClassName());
	if ( NULL == piProcessCont ) return 3;
	piInitOnDoc -> Release();
	piInitOnDoc = NULL;
	
	CATLISTV(CATBaseUnknown_var) *pProcessList = NULL;
	pProcessList = piProcessCont->GetAllProcess();
	if ((NULL == pProcessList) || ((*pProcessList).Size() < 1))
	{ 
        CATUnicodeString EmptyProcMsg = "** ERROR empty list of process ";
		cout << EmptyProcMsg.ConvertToChar()  << endl;
       		if ((*pProcessList).Size() > 0) delete pProcessList;
		return 4;
	}

    CATUnicodeString ProcCountMsg = "Number of processes : ";
	cout << ProcCountMsg.ConvertToChar() << (*pProcessList).Size() << endl << flush;
	piProcessCont -> Release();
	piProcessCont = NULL;


	// root activity is the first of the list of processes.
	CATISPPActivityRoot_var spActivityRoot = (*pProcessList)[1];
	delete pProcessList;
	pProcessList=NULL;

	CATISPPChildManagement *piChildManagOnActivity = NULL;
/** @anchor err_1 spActivityRoot not tested before use */ 
	if ( NULL_var ==  spActivityRoot ) return 4;
	rc = spActivityRoot -> QueryInterface(IID_CATISPPChildManagement, 
		                                  (void**) &piChildManagOnActivity);
	if (FAILED(rc))	return 5;

	CATISPPAbstractActivity *piActivityOnActivity = NULL;
/** @anchor err_2 spActivityRoot not tested before use */ 
	rc = spActivityRoot -> QueryInterface(IID_CATISPPAbstractActivity, 
		                                  (void**) &piActivityOnActivity);
	if (FAILED(rc)) return 5;

	/* ---------------------------------------*/
	/*  3. Sets a label on the root activity  */
	/* ---------------------------------------*/
	piActivityOnActivity->SetLabel("MainProcess");
	piActivityOnActivity -> Release();
	piActivityOnActivity = NULL;

	/* ------------------------------------ */
	/*     Creates children processes       */
	/*  4. Instanciation of process defined */
	/*     in library of activities.        */
	/* ------------------------------------ */
    CATUnicodeString InstMsg =  "Instanciation of activities from ";
    CATUnicodeString LibStrMsg = " library of activities " ;
	cout << InstMsg.ConvertToChar() << argv[1] << LibStrMsg.ConvertToChar() << endl << flush;
	// instanciate the "CAAAssembly" process
	// ( defined in the library of activities ).
	CATISPPAbstractActivity_var spAssemblyProcess = 
		piChildManagOnActivity->AddChild("CAADmiAssembly");  
/** @anchor err_3 spAssemblyProcess not tested before use */ 
	if ( NULL_var ==  spAssemblyProcess ) return 4;
	spAssemblyProcess->SetLabel("Assembly ( sheet + screw)");
   
	// instanciate the "CAAPlace " process 
	// ( defined in the library of activities ).
	CATISPPAbstractActivity_var spPlaceActivity1 =
		piChildManagOnActivity->AddChild("CAADmiPlace");
	CATISPPAbstractActivity_var spPlaceActivity2 = 
		piChildManagOnActivity->AddChild("CAADmiPlace");

	// defines a first sequence between "Start" and "Stop" activities.
    CATListValCATBaseUnknown_var* pListStartChild = piChildManagOnActivity->GetChild("Start");
    CATISPPFlowMgt_var spRootStartFlow = (*pListStartChild)[1];
    if (NULL!=pListStartChild) {delete pListStartChild;pListStartChild=NULL;}
    
    CATListValCATBaseUnknown_var* pListStopChild = piChildManagOnActivity->GetChild("Stop");
    CATISPPFlowMgt_var spRootStopFlow  = (*pListStopChild)[1];
    if (NULL!=pListStopChild) {delete pListStopChild;pListStopChild=NULL;}
	
	piChildManagOnActivity -> Release();
	piChildManagOnActivity = NULL;
	
	/* --------------------------------------------- */
	/*   5. If those activities need to be ordered.  */
	/*    order them using control flow between      */
	/*    activities to order.                       */
	/* --------------------------------------------- */
    CATUnicodeString CFMsg = "Control flows between those activities ";
	cout << CFMsg.ConvertToChar()  << endl << flush;
	// adds a control flow between "start" activity and "Place" one.
	CATISPPFlowMgt *piRootStartOnFlow = NULL;
	rc = spRootStartFlow -> QueryInterface(IID_CATISPPFlowMgt,
		                                   (void**) &piRootStartOnFlow);
	if (FAILED(rc) ) return 5;

	piRootStartOnFlow->AddControlFlow(spPlaceActivity1);
	piRootStartOnFlow->Release();
	piRootStartOnFlow = NULL;

	// adds a control flow between activities "place".
	CATISPPFlowMgt *piPlaceOnFlow1 = NULL;
/** @anchor err_4 spPlaceActivity1 not tested before use */ 
	if ( NULL_var ==  spPlaceActivity1 ) return 4;
	rc = spPlaceActivity1 -> QueryInterface(IID_CATISPPFlowMgt,
		                                    (void**) &piPlaceOnFlow1);
	if (FAILED(rc) ) return 5;

	piPlaceOnFlow1->AddControlFlow(spPlaceActivity2);
	piPlaceOnFlow1->Release();
	piPlaceOnFlow1 = NULL;

	// adds a control flow between activity "place" and "assembly"
	CATISPPFlowMgt *piPlaceOnFlow2 = NULL;
/** @anchor err_5 spPlaceActivity2 not tested before use */ 
	if ( NULL_var == spPlaceActivity2 ) return 4;
	rc = spPlaceActivity2 -> QueryInterface(IID_CATISPPFlowMgt,
		                                    (void**) &piPlaceOnFlow2);

	if (FAILED(rc) ) return 5;

	piPlaceOnFlow2->AddControlFlow(spAssemblyProcess);
	piPlaceOnFlow2->Release();
	piPlaceOnFlow2 = NULL;

	// adds a control flow between "Assembly" and "Stop" one.
	CATISPPFlowMgt *piAssemblyProcessOnFlow = NULL;
/** @anchor err_6 spAssemblyProcess not tested before use */ 
	if ( NULL_var ==  spAssemblyProcess ) return 4;
	rc = spAssemblyProcess -> QueryInterface(IID_CATISPPFlowMgt,
		                                     (void**) &piAssemblyProcessOnFlow);
	if (FAILED(rc) ) return 5;

	piAssemblyProcessOnFlow->AddControlFlow(spRootStopFlow);
	piAssemblyProcessOnFlow->Release();
	piAssemblyProcessOnFlow = NULL;

	/* ---------------------------------*/
	/*   6.Sets an item on an activity  */
	/* -------------------------------- */
	// load product document.
	CATDocument *pItemDoc = NULL;
	rc = CATDocumentServices::OpenDocument(argv[2],pItemDoc);
	if ( FAILED(rc) || (NULL==pItemDoc)) return 6;

    CATUnicodeString ProdMsg = "CAAPmiGenerProcess.m:	product document opened : ";
	cout << endl << ProdMsg.ConvertToChar() << argv[2] << endl << flush;

	CATIDocRoots* piDocRootsOnDoc = NULL;
	rc = pItemDoc->QueryInterface(IID_CATIDocRoots,
		                          (void**) &piDocRootsOnDoc);

 	if (FAILED(rc) ) return 6;

	CATListValCATBaseUnknown_var* pRootProducts = 
		piDocRootsOnDoc->GiveDocRoots();

	piDocRootsOnDoc->Release();
	piDocRootsOnDoc=NULL;

	CATIProduct_var spRootProduct = NULL_var;
	if (pRootProducts && pRootProducts->Size())
	{  
		spRootProduct = (*pRootProducts)[1];
		delete pRootProducts;
		pRootProducts = NULL;
	}
	CATIProduct *piProductOnRoot = NULL;
/** @anchor err_7 spRootProduct not tested before use */ 
	if ( NULL_var ==  spRootProduct ) return 4;
	rc = spRootProduct->QueryInterface(IID_CATIProduct, 
		                               (void**) &piProductOnRoot);
	if (FAILED(rc) ) return 6;

	// get items in the product document
	// associate them to activity.
	CATListValCATBaseUnknown_var *ListItems = 
		piProductOnRoot -> GetAllChildren();
	piProductOnRoot->Release();
	piProductOnRoot=NULL;
	
	CATIProduct_var spItem = NULL_var;
	CATUnicodeString itemName (" ");

	// first item associate to Place activity and to Assembly activity.	
	spItem = (*ListItems)[1];
/** @anchor err_8 spItem not tested before use */ 
	if ( NULL_var ==  spItem ) 
    {
        
       if( NULL != ListItems )
       {
          delete ListItems;
          ListItems = NULL;
       }
       
       return 4;
    }
	rc = spItem -> GetPrdInstanceName ( itemName ) ;

    CATUnicodeString ItemNameMsg = "First itemName : ";
	cout << ItemNameMsg.ConvertToChar() << itemName.CastToCharPtr() << endl << flush;

	CATISPPItemMgt *piAssemblyOnItem = NULL;
/** @anchor err_9 spAssemblyProcess not tested before use */ 
	rc = spAssemblyProcess -> QueryInterface(IID_CATISPPItemMgt,
		                                (void**) &piAssemblyOnItem);
	if (FAILED(rc) ) 
   {
       
       if( NULL != ListItems )
       {
          delete ListItems;
          ListItems = NULL;
       }
       
      return 6;
   }

	piAssemblyOnItem->AddItem(spItem);

	CATISPPItemMgt *piPlaceOnItem1 = NULL;
/** @anchor err_10 spPlaceActivity1 not tested before use */ 
	rc = spPlaceActivity1 -> QueryInterface(IID_CATISPPItemMgt,
		                               (void**) &piPlaceOnItem1);
	if (FAILED(rc) ) 
   {
       if( NULL != ListItems )
       {
          delete ListItems;
          ListItems = NULL;
       }
       return 6;
   }

	piPlaceOnItem1->AddItem(spItem);
	piPlaceOnItem1->Release();
	piPlaceOnItem1=NULL;

	// second associate to Place activity and to Assembly activity.	
	spItem = (*ListItems)[2];

   // We are done with the ListItems, lets delete them
   if( ListItems )
   {
      delete ListItems;
      ListItems = NULL;
   }

	if ( NULL_var ==  spItem ) return 4;
	rc = spItem -> GetPrdInstanceName ( itemName ) ;

    CATUnicodeString SecondMsg = "Second itemName : ";
	cout << SecondMsg.ConvertToChar() << itemName.CastToCharPtr() << endl << flush;

	piAssemblyOnItem->AddItem(spItem);

	CATISPPItemMgt *piPlaceOnItem2 = NULL;
/** @anchor err_11 spPlaceActivity2 not tested before use */ 
	rc = spPlaceActivity2 -> QueryInterface(IID_CATISPPItemMgt,
		                               (void**) &piPlaceOnItem2);
	if (FAILED(rc) ) return 6;

	piPlaceOnItem2->AddItem(spItem);
	piPlaceOnItem2->Release();
	piPlaceOnItem2 = NULL;

	piAssemblyOnItem->Release();
	piAssemblyOnItem = NULL;
	
	/* --------------------------------- */
	/*  7. Adds resource on an activity  */
	/* --------------------------------- */
	// load product document.
	CATDocument* pResourceDoc = NULL;
	rc = CATDocumentServices::OpenDocument(argv[3],pResourceDoc);
	if ( FAILED(rc) || (NULL==pResourceDoc) ) return 7;

    CATUnicodeString ResMsg = "CAAPmiGenerProcess.m:	product document opened :";
	cout << endl << ResMsg.ConvertToChar() << argv[3] << endl << flush;

	CATIDocRoots* piDocRootsOnDoc2 = NULL;
	rc = pResourceDoc->QueryInterface(IID_CATIDocRoots,
		                              (void**) &piDocRootsOnDoc2);
	if (FAILED(rc) ) return 7;

	CATListValCATBaseUnknown_var* pRoots = 
		piDocRootsOnDoc2->GiveDocRoots();
	CATIProduct_var spRoot = NULL_var;
	if (pRoots && pRoots->Size())
	{  
		spRoot = (*pRoots)[1];
		delete pRoots;
		pRoots = NULL;
	}
	CATIProduct *piProductOnRoot2 = NULL;
/** @anchor err_12 spRoot not tested before use */ 
	if ( NULL_var ==  spRoot ) return 4;
	rc = spRoot->QueryInterface(IID_CATIProduct,
		                        (void**) &piProductOnRoot2);
	if (FAILED(rc) ) return 7;

	// get resources in the product document
	// associate them to activity.
	CATListValCATBaseUnknown_var *ListResources = 
		piProductOnRoot2 -> GetAllChildren();

	piDocRootsOnDoc2->Release();
	piDocRootsOnDoc2=NULL;
	piProductOnRoot2->Release();
	piProductOnRoot2=NULL;

	CATIProduct_var spResource = NULL_var;
	CATUnicodeString resourceName (" ");

	spResource = (*ListResources)[1];

   if( NULL != ListResources )
   {
      delete ListResources;
      ListResources = NULL;
   }
/** @anchor err_13 spResource not tested before use */ 
	if ( NULL_var ==  spResource ) return 4;
	rc = spResource -> GetPrdInstanceName ( resourceName ) ;

    CATUnicodeString ResName = "ResourceName : ";
	cout << ResName.ConvertToChar() << resourceName.CastToCharPtr() << endl << flush;

	CATISPPResourceManagement *piAssemblyOnResource = NULL;
/** @anchor err_14 spAssemblyProcess not tested before use */ 
	rc = spAssemblyProcess -> QueryInterface(IID_CATISPPResourceManagement, 
		                                     (void**) &piAssemblyOnResource);
	if (FAILED(rc) ) return 7;

	piAssemblyOnResource->AddResource(spResource);
	piAssemblyOnResource->Release();
	piAssemblyOnResource=NULL;

	/* ----------------------------------------- */
	/*   8. Saves the resulting process          */
	/* ----------------------------------------- */
    CATUnicodeString SaveMsg =  "CAAPpbGenerProcess.m: Now we can save the created and modified CATProcess in ";
	cout << endl << SaveMsg.ConvertToChar() << argv[4] << endl << flush;
	rc = CATDocumentServices::SaveAs(*pNewDoc, argv[4]);

	if ( FAILED(rc)  ) return 8;
	
	/* ----------------------------------------- */
	/*   9. Ends the session                     */
	/* ----------------------------------------- */
	
	// remove opened document
	rc = CATDocumentServices::Remove (*pNewDoc);
	if (FAILED(rc)) return 9;

	// delete the session, removes the opened documents also.
	// never forget to delete a creating session after usage.
	rc = ::Delete_Session("CAA2_Sample_Session");
	return rc;
}
