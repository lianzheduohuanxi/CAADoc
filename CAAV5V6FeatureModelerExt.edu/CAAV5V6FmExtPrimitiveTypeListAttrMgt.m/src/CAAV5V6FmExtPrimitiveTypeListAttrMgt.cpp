// COPYRIGHT DASSAULT SYSTEMES 2010
//=============================================================================
// Abstract of Use Case "CAAV5V6FmExtPrimitiveTypeListAttrMgt":
// ============================================================================

// The Use Case illustrates managing a "list of Primitive Types" attribute associated with a feature.
// A list can be modifed (append, insert, set) only if it is defined locally.
//
// The UC refers to a feature "CAAFmExtLists" defined in the Catalog "CAAFmExtElementCatalog"
// The feature definition follows (an extract of the contents of the CAAFmExtElementCatalog.osm)

/*
document `CAAFmExtElementCatalog.CATfct` {
container RootCont #root {
feature CAAFmExtLists #startup {
int MyListOfInteger #list
string MyListOfString #list 
MyListOfString = ["firststring","secondstring","thirdstring"]
}
}
}
*/
//=============================================================================
//  Steps
//
// 1- Initializing the Variables required for Basic Attribute Checks
// 2- Instantiate a "CAAFmExtLists"  StartUp (referred to as CAAFxExtLists1)

// 3- Working with a "List of Integers" feature attribute
//      3-0- Retrieve the "list of integer" attribute valuation info. Attribute is Inherited
//      3-1- Parse the list to output its contents. List empty
//      3-2- Create a list, and add & remove elements
//             3-2-1- Append "7" to the initial empty list to create a local list
//             3-2-2- Parse the list to output its contents. Outputs 7
//             3-2-3- Check the attribute info - the list is now immediate
//             3-2-4- Change the complete list by a new one with only "5" inside
//             3-2-5- Parse the list to output its contents. Outputs 5
//             3-2-6- Check the attribute info - the list is still immediate
//      3-3-  Add & remove elements of a list
//             3-3-1- Insert "4" at index 1 of List of Integer. Returns SUCCESS
//             3-3-2- Parse the list to output its contents. Output will be (4,5)
//             3-3-3- Insert "3' at index 2 of list of integer. Returns SUCCESS
//             3-3-4- Parse the list to output its contents. Output will be (4,3,5)
//             3-3-5- Insert "2" at index 4 of list of integer. Returns SUCCESS
//             3-3-6- Parse the list to output its contents. Output will be (4,3,5,2)
//             3-3-7- Remove value at index 3 of list of integer. Returns SUCCESS
//             3-3-8- Parse the list to output its contents. Output expected is (4,3,2)
//      3-4- Play with elements of a list
//             3-4-1- Swap Position of values at index 1 and 3 of list of integer. Returns SUCCESS
//             3-4-2- Parse the list to output its contents. Output will be (2,3,4)
//             3-4-3- Move value at index 1 to index 3 of list of integer. Returns SUCCESS
//             3-4-4- Parse the list to output its contents. Output will be (3,4,2)
//             3-4-5- Set value "6" at index 3 of list of integer. It overwrites the current value
//             3-4-6- Parse the list to output its contents. Output will be (3,4,6)
//      3-5- Locate elements in a list
//             3-5-1- Locate value "4" in the list of integers. It is expected to occur at index 2
//             3-5-2- Insert "4" at index 1 of list of integer. Returns SUCCESS
//             3-5-3- Locate value "4" in MyListOfInteger. It is now expected to occur at index 1
//             3-5-4- Parse the list to output its contents. Output will be (4,3,4,6)
//      3-6- Unset a list
//             3-6-1- Unset the list of integer feature attribute
//             3-6-2- Display Info of list of integer attribute. It is immediate 
//             3-6-3- Parse the list to output its contents. Outputs an empty list
//
// 4- Working with the List of String attribute
//      4-1- Display values in list. Since values not explicitly set, list valuated by default settings in the OSM
//      4-2- Retrieve List of String attribute valuation info. It is inherited
//      4-3- Set and Unset list
//            4-3-2- Feature list of string attribute valuated with an empty list. 
//            4-3-3- Retrieve info of the list of string attribute. It is immediate
//            4-3-4- Parse the list to output its contents. Outputs an empty list
//            4-3-5- Add an element in the list 
//            4-3-6- Parse the list to output its contents. Outputs "MyString"
//            4-3-7- Remove Locally Defined Value on the List of String attribute
//            4-3-8- Retrieve the list of string attribute valuation info. It is inherited
//            4-3-9- Parse the list to output its contents. Outputs default values set in the OSM file
//            4-3-10- Unset the list of string attribute
//            4-3-11- Retrieve info of the list of string attribute. It is immediate
//            4-3-12- Parse the list to output its contents. List being unset, outputs an empty list.

// - Saves the Session
// - Closes the Session
//
//=============================================================================
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAV5V6FmExtPrimitiveTypeListAttrMgt DocumentStorageName" 
//  where the "DocumentStorageName" is the entire pathname, name and .CATPart extension
//    under which the new document is to be stored. 
// Return code :
//   0 successful execution
//   1 execution failed
// 
//=============================================================================
//  Note: This Use-Case is compatible in V5 as well as V6 environment. Thus the code in #ifdef
//		  represents the difference in the respective functionality of V5 and V6 for E.g. Session
//		  creation, Applicative Containers concept, Save Services etc.
//		  The code outside the #ifdef is the common code for V5 and V6 and represents the backported
//		  functionalities of V6 to V5.
//		  This Framework is just for testing whether this use-case is working in V6 env or not.
//		  This is FW is not to be packaged hence not available to customer.


// System Framework
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"
#include "CATString.h"

// FeatureModelerExt 
#include "CATFmFeatureFacade.h"
#include "CATFmContainerFacade.h"
#include "CATFmStartUpFacade.h"
#include "CATFmCredentials.h"
#include "CATFmAttributeName.h"
#include "CATFmAttributeValue.h"
#include "CATFmAttributeAndValueKind.h"
#include "CATFmAttributeValuationInfo.h"
#include "CATFmAttributeValuationMode.h"
#include "CATFmFeatureModelerID.h"

#include "CATIAV5Level.h"

// Other
#include <iostream.h>

//-------------------------------------------------------------------------
//	Include guards when the Framework is in V6 Environment
//-------------------------------------------------------------------------
#ifdef CATIAR214

//local Framework
#include "CAAV5V6FmExtCreateRepRef.h"     // to create the Rep ref

//System Framework
#include "CATSysBoolean.h"

// ObjectModelerBase
#include "CATOmbLifeCycleRootsBag.h"

//CAT3DPhysicalRepInterfaces Framework
#include "CATIPsiRepresentationReference.h"  // interface on rep ref

// CATPLMIntegrationUse
#include "CATAdpSaver.h"

// CAAPLMClientAdapter.edu Framework
#include "CAAAdpCreateCloseSession.h"

#endif
/*--------------------------*/

//-------------------------------------------------------------------------
//	Include guards when the Framework is in V5 Environment
//-------------------------------------------------------------------------
#ifdef CATIAV5R23

// ObjectModelerBase Framework
#include "CATSessionServices.h"             // Create_Session and Delete_Session
#include "CATDocumentServices.h"            // New, SaveAs and Remove document
#include "CATInit.h"                        // GetRootContainer
#include "CATDocument.h"                    // Document
#include "CATSession.h"
#include "CATIContainer.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"                 // Instanciate, GetFather, GetName
#include "CATISpecAttrAccess.h"             // GetAttrKey, SetString, SetInteger,
//    SetSpecObject, GetString,
//    GetSpecObject, 
#include "CATISpecAttrKey.h"                // Result of GetAttrKey
#include "CATOsmSUHandler.h"

#endif
//------------------

//=============================================================================
// Global Routines
// Routine to confirm a feature Attribute Valuation Info
HRESULT ConfirmAttributeInfo(CATFmFeatureFacade & iFeatFacadeOnFeat,
							 CATFmAttributeName & iAttrName,
							 CATFmAttributeValuationMode iValuationMode,
							 CATFmAttributeAndValueKind TypeOfListContents);

// Display values in a list by looping through a feature Attribute value of type List
HRESULT DisplayListValues (CATFmFeatureFacade & iFeatFacadeOnFeat,
						   CATFmAttributeName & iAttrName);

//=======================================================================================

int main (int iArgc, char * iArgv[])
{ 
#ifdef CATIAV5R23

	/*--------------------------------------------------------------*/
	/* Open a Session:  this is a necessary step in a batch program */
	/*--------------------------------------------------------------*/

	char *pSessionName = "CAA2_Sample_Session";
	CATSession *pSession = NULL;
	HRESULT rc = ::Create_Session(pSessionName,
		pSession);
	if ((FAILED(rc)) || (NULL == pSession))
	{
		cout << "ERROR in creating session" << endl << flush;
		return 1;
	}

	/*-------------------------------------*/
	/* Create a new document for features. */
	/*-------------------------------------*/

	// We will work with a "CATPart" document. 

	CATDocument *pDoc = NULL;
	rc = CATDocumentServices::New("Part",
		pDoc);
	if (NULL != pDoc) cout << "New document created OK in V5-V6 compatible FW...." << endl << flush;
	else
	{
		cout << "ERROR in creating New document" << endl << flush;
		return 2;
	} 	

	/*----------------------------------------------*/
	/* Retrieve the root container of the document. */
	/*----------------------------------------------*/

	CATInit *piInitOnDoc = NULL;
	rc = pDoc -> QueryInterface(IID_CATInit,
		(void**) &piInitOnDoc);
	if (FAILED(rc)) 
	{
		cout << "ERROR in QueryInterface on CATInit for doc" << endl << flush;
		return 3;
	}

	const CATIdent idCATIContainer = "CATIContainer";
	CATIContainer *piRootContainer = NULL;
	piRootContainer = (CATIContainer*) piInitOnDoc -> GetRootContainer(idCATIContainer);
	piInitOnDoc -> Release();
	if (NULL == piRootContainer)
	{
		cout << "ERROR in GetRootContainer" << endl << flush;
		return 4;
	}
	//-------------------------------------------------------------------------------
	// 3- Build Client Credentials 
	//-------------------------------------------------------------------------------
	CATFmCredentials MyCredential;
	rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
	rc = MyCredential.RegisterAsCatalogOwner("CAAFmExtElementCatalog","CAAFmExtClientId1");
	if (FAILED(rc)) return 1;
	cout << "   Success in creating the credentials" << endl;

	//Create container facade to work with
	CATFmContainerFacade MyContainerFacade(MyCredential,piRootContainer);


#endif

#ifdef CATIAR214

	//---------------------
	// 1- Checks arguments
	//---------------------
	if ( 7 != iArgc )
	{
		cout << endl;
		cout << "   Usage: CAAV5V6FmExtPrimitiveTypeListAttrMgt <Repository> <Server> <User> <Password> <SecurityCtx> <Environment> " ;
		cout <<endl;
		return 1;
	}

	cout << "   The CAAV5V6FmExtPrimitiveTypeListAttrMgt main program begins in V5-V6 compatible FW........"<< endl << endl;

	//------------------------------------------------------------------
	// 2 - Initializes the PLM session 
	//------------------------------------------------------------------
	HRESULT rc = ::CAAAdpCreateSession(iArgv[1], iArgv[2], iArgv[3], iArgv[4],iArgv[5]);
	if (FAILED(rc))	
		return 1;   
	cout << "   PLM session initialized with the following connection parameters" << endl;
	cout << "      Repository=" << iArgv[1] << endl;
	cout << "      Server="     << iArgv[2] << endl;
	cout << "      UserID="     << iArgv[3] << endl;
	cout << "      UserPasswd=" << iArgv[4] << endl;
	cout << "      SecurityCtx=" << iArgv[5] << endl;

	//-------------------------------------------------------------------------------------------------
	// 3- Creating a Credential Object which authorizes client to handle the "CAAFmExtElementCatalog" catalog
	// ------------------------------------------------------------------------------------------------
	CATFmCredentials MyCredential;
	rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
	rc = MyCredential.RegisterAsCatalogOwner("CAAFmExtElementCatalog","CAAFmExtClientId1");
	if (FAILED(rc)) return 1;
	cout << "   Success in creating the credentials in V6 env" << endl;

	//------------------------------------------------------------------
	// 4- Creates a Product Representation Reference (Techno Rep)
	//------------------------------------------------------------------
	CATString EnvToUse = iArgv[6];
	CATString Repository = iArgv[1];
	CATUnicodeString NameAndTypeofContainer = "CAAFmExtAppliCont" ;
	CATIPsiRepresentationReference * pPsiCreatedRepRef= NULL;
	CATBaseUnknown * pContainer = NULL ;
	rc = ::CAAV5V6FmExtCreateRepRef(MyCredential, EnvToUse,Repository,NameAndTypeofContainer,NameAndTypeofContainer,
		IID_CATIPsiRepresentationReference,(void**) &pPsiCreatedRepRef, &pContainer);
	if (FAILED(rc) || (NULL==pPsiCreatedRepRef) || (NULL==pContainer) ) return 1;
	cout <<"   The Product Representation Reference is created in V5 V6 compatible code" << endl;

	// Insert component that is loaded in session, in BAG
	CATOmbLifeCycleRootsBag Bag;
	Bag.InsertRoot(pPsiCreatedRepRef);

	//Create container facade to work with
	CATFmContainerFacade MyContainerFacade(MyCredential,pContainer);

	pPsiCreatedRepRef->Release();
	pPsiCreatedRepRef = NULL;

#endif

	//-----------------------------------------------------------------------------------------------
	// 1- Initializing the Variables required for Basic Attribute Checks
	//-----------------------------------------------------------------------------------------------

	CATFmAttributeName ListOfIntAttrName("MyListOfInteger");
	CATFmAttributeName ListOfStringAttrName("MyListOfString");

	// --------------------------------------------------------------------------------------
	// 2- Instantiate a "CAAFmExtLists"  StartUp (referred as CAAFmExtLists1)
	// --------------------------------------------------------------------------------------
	cout << "   Instantiate a CAAFmExtLists  StartUp (CAAFmExtLists1) "            << endl;
	CATUnicodeString CAAFmExtListsStartUpType("`CAAFmExtLists`@`CAAFmExtElementCatalog.CATfct`");
	CATFmStartUpFacade SUFacadeOnCAAFmExtLists(MyCredential,CAAFmExtListsStartUpType);
	cout << "   CAAFmExtLists StartUp Facade retrieved OK" << endl << flush;

	CATFmFeatureFacade FeatFacadeOnCAAFmExtLists1(MyCredential);
	rc = SUFacadeOnCAAFmExtLists.InstantiateIn(MyContainerFacade,FeatFacadeOnCAAFmExtLists1);
	if (FAILED(rc))	return 1;

	cout << "   Feature Instance CAAFmExtLists1 created OK" << endl;

	// --------------------------------------------------------------------------------------
	// 3- Working with a "List of Integers" feature attribute
	// --------------------------------------------------------------------------------------
	cout << "   ===================================================" << endl;
	cout << "   Working with a list of integers feature attribute" << endl;
	cout << "   ===================================================" << endl;
	// 3-0- Retrieve the "list of integer" attribute valuation info. Attribute is inherited
	cout << "   Retrieve the list of integer CAAFmExtList1 (feature) attribute valuation info" << endl;
	rc = ConfirmAttributeInfo(FeatFacadeOnCAAFmExtLists1,ListOfIntAttrName,CATFmInherited,CATFmKind_int);
	if (FAILED(rc)) return 1;

	cout << "   The list of integer attribute is Inherited" << endl;
	cout << "   -----------------------------------------------------------------" << endl;

	// 3-1- Parse the list to output its contents. List empty
	cout << "   Parse the list to output its contents. List expected empty" << endl;
	rc = DisplayListValues (FeatFacadeOnCAAFmExtLists1,ListOfIntAttrName);
	if (rc != S_FALSE)  return 1;

	cout << "   --------------------------------------------------------------------" << endl;

	// 3-2- Create list

	// 3-2-1- Append 5 to the initial empty list
	cout << "   Create a list of integer with 7 as initial element" << endl;
	int iValue = 7;
	CATFmAttributeValue AttrValueForSet ;
	AttrValueForSet.SetInteger(iValue);
	rc = FeatFacadeOnCAAFmExtLists1.AppendValue(ListOfIntAttrName,AttrValueForSet);
	if (FAILED(rc)) return 1;

	cout << "   Create returned SUCCESS, " << endl;
	cout << "   -------------------------------------------------------" << endl;

	// 3-2-2- Retrieve info of the list of int attribute. It is immediate value
	cout << "   Retrieve info of the list of string attribute" << endl;
	rc = ConfirmAttributeInfo(FeatFacadeOnCAAFmExtLists1,ListOfIntAttrName,CATFmImmediate,CATFmKind_int);
	if (FAILED(rc))  return 1;

	cout << "   List of int attribute IS SET and IS DEFINED LOCALLY" << endl;

	// 3-2-3- Parse the list to output its contents. Outputs 7
	cout << "   Parse the list to output its contents. Output expected is 7" << endl;
	rc = DisplayListValues(FeatFacadeOnCAAFmExtLists1,ListOfIntAttrName);
	if (rc != S_OK)  return 1;

	cout << "   -----------------------------------" << endl;

	// 3-2-4- Replace a list by a new one
	cout << "   Create a list of integer with 5 as initial element" << endl;
	iValue = 5;
	AttrValueForSet.BuildFromCArrayOfInt(&iValue,1);
	rc = FeatFacadeOnCAAFmExtLists1.SetValue(ListOfIntAttrName,AttrValueForSet);
	if (FAILED(rc))  return 1;

	cout << "   Create returned SUCCESS, " << endl;
	cout << "   -------------------------------------------------------" << endl;

	// 3-2-5- Retrieve info of the list of int attribute. It is immediate value.
	cout << "   Retrieve info of the list of string attribute" << endl;
	rc = ConfirmAttributeInfo(FeatFacadeOnCAAFmExtLists1,ListOfIntAttrName,CATFmImmediate,CATFmKind_int);
	if (FAILED(rc))  return 1;

	cout << "   List of int attribute is immediate" << endl;

	// 3-2-6- Parse the list to output its contents. Outputs 5
	cout << "   Parse the list to output its contents. Output expected is 5" << endl;
	rc = DisplayListValues(FeatFacadeOnCAAFmExtLists1,ListOfIntAttrName);
	if (rc != S_OK)  return 1;

	cout << "   -----------------------------------" << endl;

	// 3-3- Add , remove elements in the list

	// 3-3-1- Insert "4" at index 1 of List of Integer. Returns SUCCESS
	cout << "  Insert 4 at index 1 of list of integer" << endl;
	iValue = 4;
	AttrValueForSet.SetInteger(iValue);    
	rc = FeatFacadeOnCAAFmExtLists1.InsertValue(ListOfIntAttrName,1,AttrValueForSet);
	if (FAILED(rc))  return 1;

	cout << "   Insert returned SUCCESS" << endl;
	cout << "   --------------------------" << endl;

	// 3-3-2- Parse the list to output its contents. Output will be (4,5)
	cout << "   Parse the list to output its contents. Output expected is 4,5" << endl;
	rc = DisplayListValues (FeatFacadeOnCAAFmExtLists1,ListOfIntAttrName);
	if (rc != S_OK)  return 1;

	cout << "   -----------------------------------" << endl;

	// 3-3-3- Insert "3' at index 2 of list of integer
	cout << "   Insert 3 at index 2 of the list of integer" << endl;
	iValue = 3;
	AttrValueForSet.SetInteger(iValue);
	rc = FeatFacadeOnCAAFmExtLists1.InsertValue(ListOfIntAttrName,2,AttrValueForSet);
	if (FAILED(rc)) return 1;

	cout << "   Insert retured SUCCESS" << endl;
	cout << "   -----------------------" << endl;

	// 3-3-4- Parse the list to output its contents. Output will be (4,3,5)
	cout << "   Parse the list to output its contents. Output expected is 4,3,5" << endl;
	rc = DisplayListValues(FeatFacadeOnCAAFmExtLists1,ListOfIntAttrName);
	if (rc != S_OK)  return 1;

	cout << "   -----------------------------------" << endl;

	// 3-3-5- Insert "2" at index 4 of list of integer. Returns SUCCESS
	cout << "   Insert 2 at index 4 of the list of integer" << endl;
	iValue = 2;
	AttrValueForSet.SetInteger(iValue);
	rc = FeatFacadeOnCAAFmExtLists1.InsertValue(ListOfIntAttrName,4,AttrValueForSet);
	if (FAILED(rc)) return 1;

	cout << "   Insert returned SUCCESS" << endl;
	cout << "   -----------------------" << endl;

	// 3-3-6- Parse the list to output its contents. Output will be (4,3,5,2)
	cout << "   Parse the list to output its contents. Output expected is 4,3,5,2" << endl;
	rc = DisplayListValues (FeatFacadeOnCAAFmExtLists1,ListOfIntAttrName);
	if (rc != S_OK)  return 1;

	cout << "   -----------------------------------" << endl;

	// 3-3-7- Remove value at index 3 of list of integer. Returns SUCCESS
	cout << "   Remove value at index 3 of list of integer" << endl;
	rc = FeatFacadeOnCAAFmExtLists1.RemovePosition(ListOfIntAttrName,3);
	if (FAILED(rc))  return 1;

	cout << "   Remove value returned SUCCESS" << endl;
	cout << "   ------------------------------" << endl;

	// 3-3-8- Parse the list to output its contents. Output expected is (4,3,2)
	cout << "   Parse the list to output its contents. Output expected is 4,3,2" << endl;
	rc = DisplayListValues(FeatFacadeOnCAAFmExtLists1,ListOfIntAttrName);
	if (rc != S_OK)  return 1;

	cout << "   -----------------------------------" << endl;

	// 3-4- Play with elements of a list

	// 3-4-1- Swap Position of values at index 1 and 3 of list of integer. Returns SUCCESS
	cout << "   Swap position of values at index 1 and 3 of list of integers" << endl;
	rc = FeatFacadeOnCAAFmExtLists1.SwapPositions(ListOfIntAttrName,1,3);
	if (FAILED(rc))  return 1;

	cout << "   Swap position returned SUCCESS" << endl;
	cout << "   ------------------------------" << endl;

	// 3-4-2- Parse the list to output its contents. Output will be (2,3,4)
	cout << "   Parse the list to output its contents. Output will be 2,3,4" << endl;
	rc = DisplayListValues (FeatFacadeOnCAAFmExtLists1,ListOfIntAttrName);
	if (rc != S_OK)  return 1;

	cout << "   -----------------------------------" << endl;

	// 3-4-3- Move value at index 1 to index 3 of list of integer. Returns SUCCESS
	cout << "   Move value at index 1 to index 3 of list of integer" << endl;
	rc = FeatFacadeOnCAAFmExtLists1.MoveInPosition (ListOfIntAttrName,1,3);
	if (FAILED(rc)) return 1;

	cout << "   Move value returned SUCCESS" << endl;
	cout << "   ------------------------------" << endl;

	// 3-4-4- Parse the list to output its contents. Output will be (3,4,2)
	cout << "   Parse the list to output its contents. Output will be 3,4,2" << endl;
	rc = DisplayListValues(FeatFacadeOnCAAFmExtLists1,ListOfIntAttrName);
	if (rc != S_OK)  return 1;

	cout << "   -----------------------------------" << endl;

	// 3-4-5- Set value "6" at index 3 of list of integer. It overwrites the current value
	cout << "   Set value 6 at index 3 of the list of integer. It overwrites the current value" << endl;
	iValue = 6;
	AttrValueForSet.SetInteger(iValue);
	rc = FeatFacadeOnCAAFmExtLists1.ReplaceValueAtIndex(ListOfIntAttrName,3,AttrValueForSet);
	if (FAILED(rc))  return 1;

	cout << "   SET VALUE returned SUCCESS" << endl;
	cout << "   ------------------------------" << endl;

	// 3-4-6- Parse the list to output its contents. Output will be (3,4,6)
	cout << "   Parse the list to output its contents. Output will be 3,4,6" << endl;
	rc = DisplayListValues(FeatFacadeOnCAAFmExtLists1,ListOfIntAttrName);
	if (rc != S_OK)  return 1;

	cout << "   -----------------------------------" << endl;

	// 3-5- Locate elements in a list

	// 3-5-1- Locate value "4" in the list of integers. It is expected to occur at index 2
	cout << "   Locate value 4 in the list of integers. It is expected to occur at index 2" << endl;
	AttrValueForSet.SetInteger(4);
	int oLocateIndex = 0;
	rc = FeatFacadeOnCAAFmExtLists1.LocateValue(ListOfIntAttrName,AttrValueForSet,oLocateIndex,1,0);
	if (2 != oLocateIndex) return 1;

	cout << "   Located value returned SUCCESS. Value 4 occurs at index 2, as expected" << endl;
	cout << "   -----------------------------------------------------------------------" << endl;

	// 3-5-2- Insert "4" at index 1 of list of integer. Returns SUCCESS
	cout << "   Insert 4 at index 1 of list of integer" << endl;
	rc = FeatFacadeOnCAAFmExtLists1.InsertValue(ListOfIntAttrName,1,AttrValueForSet);
	if (FAILED(rc)) return 1;

	cout << "   Insert returns SUCCESS" << endl;
	cout << "   ------------------------------" << endl;

	// 3-5-3- Locate value "4" in MyListOfInteger. It is now expected to occur at index 1
	cout << "   Locate value 4 in the list of integers. It is now expected to occur at index 1" << endl;
	rc = FeatFacadeOnCAAFmExtLists1.LocateValue(ListOfIntAttrName,AttrValueForSet,oLocateIndex,1,0);
	if (FAILED(rc) || (1 != oLocateIndex)) return 1;

	cout << "   Locate Value returns SUCCESS. Value 4 now occurs at index 1" << endl;
	cout << "   ------------------------------------------------------------" << endl;

	// 3-5-4- Parse the list to output its contents. Output will be (4,3,4,2)
	cout << "   Parse the list to output its contents. Output will be 4,3,4,2" << endl;
	rc = DisplayListValues (FeatFacadeOnCAAFmExtLists1,ListOfIntAttrName);
	if (rc != S_OK)  return 1;

	cout << "   -----------------------------------" << endl;

	// 3-6- Unset a list

	// 3-6-1- Unset the list of integer feature attribute
	cout << "   Unset the list of integer feature attribute" << endl;
	rc = FeatFacadeOnCAAFmExtLists1.UnsetValue (ListOfIntAttrName);
	if (FAILED(rc))  return 1;

	cout << "   UnsetValue returns SUCCESS" << endl;
	cout << "   ------------------------------" << endl;

	// 3-6-2- Display Info of list of integer attribute. Its immediate
	cout << "   Retrieve list of integer attribute info" << endl;
	rc = ConfirmAttributeInfo(FeatFacadeOnCAAFmExtLists1,ListOfIntAttrName,CATFmImmediate,CATFmKind_int);
	if (FAILED(rc)) return 1;

	cout << "   The list of integer attribute is immediate value" << endl;  

	// 3-6-3- Parse the list to output its contents. Outputs an empty list
	cout << "   Parse the list to output its contents. Outputs an empty list" << endl;
	rc = DisplayListValues (FeatFacadeOnCAAFmExtLists1,ListOfIntAttrName);
	if (rc != S_FALSE ) return 1;  

	// 4- Working with the List of String attribute
	cout << "   ==================================================" << endl;
	cout << "   Working with a List of String Feature Attribute" << endl;
	cout << "   ==================================================" << endl;

	// 4-1- Retrieve List of String attribute valuation info. It is STRING TYPE, inherited
	cout << "   Retrieve list of string attribute valuation info " << endl;
	rc = ConfirmAttributeInfo(FeatFacadeOnCAAFmExtLists1,ListOfStringAttrName,CATFmInherited,CATFmKind_string);
	if (FAILED(rc))  return 1;

	cout << "   The list of string attribute is inherited" << endl;
	cout << "   ------------------------------------------------------------" << endl;

	// 4-2- Display values in list. Since values not explicitly set, list valuated by default settings in the OSM
	cout << "   Display values in list. Since values not explicitly set, list valuated by default settings in the OSM" << endl;
	rc = DisplayListValues(FeatFacadeOnCAAFmExtLists1,ListOfStringAttrName);
	if (rc != S_OK )  return 1;


	// 4-3- Set and Unset list

	// 4-3-1- Create an empty list of Strings
	cout << "   Create an empty list of Strings" << endl;
	CATFmAttributeValue AttrValueValuatedToEmptyStringList = CATFmAttributeValue::CreateEmptyList(CATFmKind_string);

	// 4-3-2- Feature list of string attribute valuated with an empty list. List now locally defined
	cout << "   Feature List of String attribute valuated with an empty list" << endl;
	rc = FeatFacadeOnCAAFmExtLists1.SetValue(ListOfStringAttrName,AttrValueValuatedToEmptyStringList);
	if (FAILED(rc))  return 1;

	cout << "   Feature List of String attribute now locally defined" << endl;

	// 4-3-3- Retrieve info of the list of string attribute. It is immediate.
	cout << "   Retrieve info of the list of string attribute" << endl;
	rc = ConfirmAttributeInfo(FeatFacadeOnCAAFmExtLists1,ListOfStringAttrName,CATFmImmediate,CATFmKind_string);
	if (FAILED(rc))  return 1;

	cout << "   List of String attribute is immediate value" << endl;

	// 4-3-4- Parse the list to output its contents. Outputs an empty list
	cout << "   Parse the list to output its contents. List expected empty" << endl;
	rc = DisplayListValues (FeatFacadeOnCAAFmExtLists1,ListOfStringAttrName);
	if (rc != S_OK)  return 1;

	// 4-3-5- SUCCESS in APPENDING a value to LIST
	cout << "   SUCCESS in APPENDING a value to LIST" << endl;
	cout << "   APPENDING a STRING to a LIST" << endl;
	CATUnicodeString str1("MyString");
	AttrValueForSet.SetString(str1);
	rc = FeatFacadeOnCAAFmExtLists1.AppendValue(ListOfStringAttrName,AttrValueForSet);
	if (FAILED(rc))  return 1;

	cout << "   SUCCESS in APPENDING a STRING to a LIST" << endl;
	cout << "   -----------------------------------------------------------------------" << endl;

	// 4-3-6- Parse the list to output its contents. Outputs "MyString"
	cout << "   Parse the list to output its contents. Outputs MyString" << endl;
	rc = DisplayListValues(FeatFacadeOnCAAFmExtLists1,ListOfStringAttrName);
	if (rc != S_OK)  return 1;

	// 4-3-7- Remove local value on the List of String attribute
	cout << "   Remove local value on the List of String attribute" << endl;
	rc = FeatFacadeOnCAAFmExtLists1.RestoreInheritance(ListOfStringAttrName);
	if (FAILED(rc)) return 1;

	cout << "   Success in removing the Locally Defined Value" << endl;

	// 4-3-8- Retrieve the list of string attribute valuation info. It is inherited
	rc = ConfirmAttributeInfo(FeatFacadeOnCAAFmExtLists1,ListOfStringAttrName,CATFmInherited,CATFmKind_string);
	if (FAILED(rc)) return 1;

	cout << "   The List of String is inherited" << endl;

	// 4-3-9- Parse the list to output its contents. Outputs default values set in the OSM file
	cout << "   Parse the list to output its contents. Outputs default values set in the OSM file" << endl;
	rc = DisplayListValues(FeatFacadeOnCAAFmExtLists1,ListOfStringAttrName);
	if (rc != S_OK)  return 1;

	// 4-3-10- Unset the list of string attribute
	cout << "   Unset the list of string attribute" << endl;
	rc = FeatFacadeOnCAAFmExtLists1.UnsetValue (ListOfStringAttrName);
	if (FAILED(rc)) return 1;

	cout << "   Unset returns SUCCESS" << endl;

	// 4-3-11- Retrieve info of the list of string attribute. It is immediate
	rc = ConfirmAttributeInfo(FeatFacadeOnCAAFmExtLists1,ListOfStringAttrName,CATFmImmediate,CATFmKind_string);
	if (FAILED(rc)) return 1;
	cout << "   List is UNSET and so , immediate" << endl;

	// 4-3-12- Parse the list to output its contents. List being unset, outputs an empty list.
	cout << "   Parse the list to output its contents. List is empty" << endl;
	rc = DisplayListValues (FeatFacadeOnCAAFmExtLists1,ListOfStringAttrName);
	if (rc != S_FALSE)  return 1;

#ifdef CATIAR214
	//-------------------------------------------------------------------------------------
	// - Save the session
	//-------------------------------------------------------------------------------------
	CATAdpSaver saver;
	rc = saver.Save();
	if ( FAILED(rc)  )return 1;
	cout <<"   Save is successful in V6 env" << endl;

	// Unload components from session
	Bag.RemoveAll();

	pContainer->Release();
	pContainer = NULL ;

	//--------------------------------------------------------------------------------------
	// - Closes the session
	//--------------------------------------------------------------------------------------
	rc = ::CAAAdpCloseSession();
	if (FAILED(rc) )return 1;

	cout <<"   PLM session closed" << endl;
	cout << endl << "The CAAV5V6FmExtPrimitiveTypeListAttrMgt main program ends in V6 env...."<< endl << endl;

	return 0;
#endif

#ifdef CATIAV5R23

	// release the pointer on the container
	piRootContainer -> Release();
	piRootContainer = NULL;
	/*--------------------------------------------------------------------------*/
	/*  Save and remove the document and end the session when in V5 environment */
	/*--------------------------------------------------------------------------*/

	// @CSC-Filter UNER 
	rc = CATDocumentServices::SaveAs(*pDoc,
		iArgv[1]);
	if (FAILED(rc))
	{
		cout << "ERROR in saving document" << endl << flush;
		return 9;
	}

	rc = CATDocumentServices::Remove (*pDoc);
	if (FAILED(rc)) 
	{
		cout << "ERROR in removing document" << endl << flush;
		return 10;
	}

	// Delete session

	rc = ::Delete_Session(pSessionName);
	if (FAILED(rc))
	{
		cout << "ERROR in deleting session" << endl << flush;
		return 11;
	}

	return 0;
#endif
}

//-------------------------------------------------------------------------------------
// Routine to confirm a feature Attribute Valuation Info
//-------------------------------------------------------------------------------------
HRESULT ConfirmAttributeInfo(CATFmFeatureFacade & iFeatFacadeOnFeat,
							 CATFmAttributeName & iAttrName,
							 CATFmAttributeValuationMode iValuationMode,
							 CATFmAttributeAndValueKind TypeOfListContents)
{
	HRESULT rc = E_FAIL;
	CATFmAttributeValuationInfo AttrValuationInfo;
	rc = iFeatFacadeOnFeat.GetAttributeValuationInfo(iAttrName,AttrValuationInfo);

	if (SUCCEEDED(rc))
	{
		if ( FALSE == AttrValuationInfo.m_IsList) rc = E_FAIL;

		// Checks specific to each case
		if ( (AttrValuationInfo.m_ValuationMode != iValuationMode) || 
			(AttrValuationInfo.m_Type          != TypeOfListContents) )  rc = E_FAIL;
	}

	return rc;
}

//-------------------------------------------------------------------------------------
// Display values in a list by looping through a feature Attribute value of type List
//-------------------------------------------------------------------------------------
HRESULT DisplayListValues (CATFmFeatureFacade & iFeatFacadeOnFeat,
						   CATFmAttributeName & iAttrName )
{
	cout << "   Display values of a list by looping through an Attribute type of type List" << endl;
	HRESULT rc = E_FAIL;
	CATFmAttributeValue AttrValueOnTheListValue;
	rc = iFeatFacadeOnFeat.GetValue(iAttrName,AttrValueOnTheListValue);
	if (SUCCEEDED(rc))
	{
		int iListSize = AttrValueOnTheListValue.Size();
		cout << "   List size is " << iListSize << endl;
		CATFmAttributeValue AttrValueOnListElement;
		if (CATFmKind_int == AttrValueOnTheListValue.Kind())
		{
			for (int i=1; i<=iListSize; i++)
			{
				AttrValueOnListElement = AttrValueOnTheListValue[i];
				int iListElement;
				AttrValueOnListElement.GetInteger(iListElement);
				cout << "   " << iListElement << " " ;            
			}

		} else if (CATFmKind_string == AttrValueOnTheListValue.Kind())
		{
			for (int j=1; j<=iListSize; j++)
			{
				AttrValueOnListElement = AttrValueOnTheListValue[j];
				CATUnicodeString strListElement;
				AttrValueOnListElement.GetString(strListElement);
				cout << "   " << strListElement.ConvertToChar() << " " ;
			}
		}
		cout << endl;
	}

	return rc;
}

