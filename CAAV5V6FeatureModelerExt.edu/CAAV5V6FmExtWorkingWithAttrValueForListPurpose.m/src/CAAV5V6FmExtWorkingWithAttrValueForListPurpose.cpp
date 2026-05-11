// COPYRIGHT DASSAULT SYSTEMES 2010
//====================================================================================
// Abstract of Use Case "CAAV5V6FmExtWorkingWithAttrValueForListPurpose":
// -----------------------------------------------------------------------------------
// The objective of the current UC is to illustrate working with a CATFmAttributeValue class 
// A CATFmAttributeValue class is infact equivalent to a list 
// 
// The UC refers to features defined in the Catalog "CAAFmExtElementCatalog"
// An extract of the contents of the CAAFmExtElementCatalog.osm referred by this UC follows
/*
feature CAAFmExtPoint2D #startup {
double x
x = -1
double y
}

feature CAAFmExtLists #startup {
int MyListOfInteger #list
string MyListOfString #list 
MyListOfString = ["firststring","secondstring","thirdstring"]
}
*/

//=====================================================================================
//  Steps
//

// 1-  Instantiate the features

// 2-  Scenario 1: Check the # element of each list, default valuated
//      2-1- Retrieve list of int attribute value, currently empty, since it is not default valuated
//      2-2- Retrieve list of string attribute value, default valuated with 3 strings

// 3-  Scenario 2: CATFmAttributeValue with one value is a list of 1 element 
//      3-1- Attribute Value valuated with a single string value is equivalent to a list of size 1
//      3-2- Attribute Value valuated with a single int value is equivalent to a list of size 1

// 4  Scenario 3:  Create the list with CATFmAttributeValue  (for string) – initially empty
//      4-1- Set an empty list of string to the Attribute Value
//      4-2- Modify the list of string by invoking Append, Insert, Swap, Remove
//      4-3- Set the list to the feature

// 5- Scenario 4: Working with a List of Integers (Get/Set methods)
//      5-1- Build an Attribute Value initialized with a list of int
//      5-2- Use Get/Set of CATFmAttributeValue to Modify/Check list 
//      5-3- Set the list of int to the feature

// 6- Scenario 5: Working with a list of int (Insert, Append, Set, Remove)
//      6-1- Get the int list from MyLists feature 
//      6-2- List of Int modified with calls to Append, Insert, Set, Remove)
//      6-3- Set the new list to MyLists  
// - Saves the session
// - Closes the session

//=============================================================================
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAV5V6FmExtWorkingWithAttrValueForListPurpose DocumentStorageName" 
//  where the "DocumentStorageName" is the entire pathname, name and .CATPart extension
//    under which the new document is to be stored. 
//
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

// System Framework
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"
#include "CATString.h"
#include "CATListOfCATUnicodeString.h"
#include "CATListOfInt.h"
#include "CATFmHRESULT.h"

// FeatureModelerExt 
#include "CATFmFeatureFacade.h"
#include "CATFmFeatureIterator.h"
#include "CATFmContainerFacade.h"
#include "CATFmStartUpFacade.h"
#include "CATFmCredentials.h"
#include "CATFmAttributeName.h"
#include "CATFmAttributeValue.h"
#include "CATFmFeatureModelerID.h"

// Other
#include <iostream.h>
#include "CATIAV5Level.h"
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

// ===================================================================
// Parsing the Attribute Value for strings within
HRESULT ParseAttrValueContentForStrings(CATFmAttributeValue & AV);
HRESULT ParseAttrValueContentForInt(CATFmAttributeValue & AV);

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
	// - Checks arguments
	//---------------------
	if ( 7 != iArgc )
	{
		cout << endl;
		cout << "   Usage: CAAV5V6FmExtWorkingWithAttrValueForListPurpose <Repository> <Server> <User> <Password> <SecurityCtx> <Environment>  " ;
		cout <<endl;
		return 1;
	}

	cout << "The CAAV5V6FmExtWorkingWithAttrValueForListPurpose main program begins ...."<< endl << endl;

	//------------------------------------------------------------------
	//  - Initializes the PLM session 
	//------------------------------------------------------------------
	HRESULT rc = ::CAAAdpCreateSession(iArgv[1], iArgv[2], iArgv[3], iArgv[4],iArgv[5]);
	if (FAILED(rc))	 return 1;   

	cout << "   PLM session initialized with the following connection parameters" << endl;
	cout << "      Repository=" << iArgv[1] << endl;
	cout << "      Server="     << iArgv[2] << endl;
	cout << "      UserID="     << iArgv[3] << endl;
	cout << "      UserPasswd=" << iArgv[4] << endl;
	cout << "      SecurityCtx=" << iArgv[5] << endl;

	//-----------------------------------------------------------------
	// - Creating a Credential Object for client authorization
	// ----------------------------------------------------------------

	CATFmCredentials MyCredential;
	rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
	rc = MyCredential.RegisterAsCatalogOwner("CAAFmExtElementCatalog","CAAFmExtClientId1");
	if (FAILED(rc)) return 1;
	cout << "   Success in creating the credentials" << endl;

	//------------------------------------------------------------------
	// - Creates a Product Representation Reference (Techno Rep)
	//------------------------------------------------------------------
	CATString EnvToUse = iArgv[6];
	CATString Repository = iArgv[1];
	CATUnicodeString NameAndTypeofContainer = "CAAFmExtAppliCont" ;
	CATIPsiRepresentationReference * pPsiCreatedRepRef= NULL;
	CATBaseUnknown * pContainer = NULL ;
	rc = ::CAAV5V6FmExtCreateRepRef(MyCredential, EnvToUse,Repository,NameAndTypeofContainer,NameAndTypeofContainer,
		IID_CATIPsiRepresentationReference,(void**) &pPsiCreatedRepRef, &pContainer);
	if (FAILED(rc) || (NULL==pPsiCreatedRepRef) || (NULL==pContainer) ) return 1;
	cout <<"   The Product Representation Reference is created" << endl;

	// Insert component that is loaded in session, in BAG
	CATOmbLifeCycleRootsBag Bag;
	Bag.InsertRoot(pPsiCreatedRepRef);

	//Create container facade to work with
	CATFmContainerFacade MyContainerFacade(MyCredential,pContainer);

	pPsiCreatedRepRef->Release();
	pPsiCreatedRepRef = NULL;


#endif
	// -----------------------------
	// 1- Instantiate the Features
	// -----------------------------
	// Creating the CAAFmExtLists feature
	CATUnicodeString ListStartUpType("`CAAFmExtLists`#4@`CAAFmExtElementCatalog.CATfct`");
	CATFmStartUpFacade SUFacadeOnList(MyCredential,ListStartUpType);
	cout << "   CAAFmExtLists StartUp Facade retrieved OK" << endl << flush;

	CATFmFeatureFacade FeatFacadeOnList(MyCredential);
	rc = SUFacadeOnList.InstantiateIn(MyContainerFacade,FeatFacadeOnList);
	if (FAILED(rc)) return 1;
	cout << "   CAAFmExtLists feature created OK" << endl;

	// ---------------------------------------------------------------------
	// 2- Scenario 1: Check the # element of each list, default valuated
	// ---------------------------------------------------------------------
	CATFmAttributeName AttrNameMyListOfInt("MyListOfInteger"), AttrNameMyListOfString("MyListOfString");

	// 2-1- Retrieve list of int attribute value, currently empty, since it is not default valuated
	CATFmAttributeValue AttrValue;
	rc = FeatFacadeOnList.GetValue(AttrNameMyListOfInt,AttrValue);
	if ((S_FALSE != rc) || (0 != AttrValue.Size())) return 1;
	cout << "   The size of an a list of int, not default valuated is 0" <<  endl;

	// 2-2- Retrieve list of string attribute value, default valuated with 3 strings
	rc = FeatFacadeOnList.GetValue(AttrNameMyListOfString,AttrValue);
	if ((S_OK != rc) || (3 != AttrValue.Size())) return 1;   
	cout << "   The size of an a list of string, default valuated with 3 strings is 3" <<  endl;

	// ----------------------------------------------------------------------------
	// 3- Scenario 2: CATFmAttributeValue with one value is a list of 1 element 
	// ----------------------------------------------------------------------------
	// 3-1- Attribute Value valuated with a single string value is equivalent to a list of size 1
	CATUnicodeString str1("Ganesh");
	CATFmAttributeValue AV1(str1);
	rc = FeatFacadeOnList.SetValue(AttrNameMyListOfString,AV1);
	if (FAILED(rc)) return 1;
	cout << "   A feature attribute of type string list can be valuated with an Attribute Value set with a single string value  " << endl;
	cout << "   An Attribute value set with a single string value is thus equivalent to a list of size 1   " << endl;

	// 3-2- Attribute Value valuated with a single int value is equivalent to a list of size 1
	int int1 = 10;
	CATFmAttributeValue AV2(int1);
	rc = FeatFacadeOnList.SetValue(AttrNameMyListOfInt,AV2);
	if (FAILED(rc)) return 1;
	cout << "   A feature attribute of type int list  can be valuated with an Attribute Value set with a single int value  " << endl;
	cout << "   An Attribute value set with a single int value is thus equivalent to a list of size 1   " << endl;

	// -------------------------------------------------------------------------------------------
	// 4- Scenario 3:  Working with a List of Strings
	// -------------------------------------------------------------------------------------------
	// 4-1- Set an empty list of string to the Attribute Value
	CATFmAttributeValue AV3 = CATFmAttributeValue::CreateEmptyList(CATFmKind_string);
	if (0 != AV3.Size()) return 1;
	cout << "   Confirmed empty list size is 0" << endl;

	// 4-2- Modify the list of string by invoking Append, Insert, Swap, Remove .....
	CATUnicodeString str4("Rohit");
	CATFmAttributeValue AV4(str4);
	AV3.Append(AV4);
	if (FAILED(rc)) return 1;

	CATUnicodeString str5("Mohit Chauhan");
	CATFmAttributeValue AV5(str5);
	rc = AV3.Insert(2,AV5);
	if (FAILED(rc)) return 1;
	rc = ParseAttrValueContentForStrings(AV3);
	cout << "   ************************* " << endl;

	CATFmAttributeValue::Swap(AV4,AV5);
	rc = AV3.Set(1,AV4);
	if (FAILED(rc)) return 1;
	rc = ParseAttrValueContentForStrings(AV3);
	cout << "   ************************* " << endl;

	rc = AV3.Set(2,AV5);
	if (FAILED(rc)) return 1;
	rc = ParseAttrValueContentForStrings(AV3);
	cout << "   ************************* " << endl;

	rc = AV3.Remove(2);
	if (FAILED(rc)) return 1;
	rc = ParseAttrValueContentForStrings(AV3);
	cout << " ************************* " << endl;

	// 4-3- Set the list to the feature
	rc = FeatFacadeOnList.SetValue(AttrNameMyListOfString,AV3);
	if (FAILED(rc)) return 1;

	// -------------------------------------------------------------------
	// 5- Scenario 4: Working with a List of Integers (Get/Set methods)
	// -------------------------------------------------------------------
	// 5-1- Build an Attribute Value initialized with a list of int
	CATFmAttributeValue AV8;
	int iArrayOfInteger[5] = {2,4,6,8,10};
	int iSize = 5;
	AV8.BuildFromCArrayOfInt(iArrayOfInteger,iSize);

	// 5-2- Use Get/Set of CATFmAttributeValue to Modify/Check list 
	CATFmAttributeValue AV6;
	rc = AV8.Get(3,AV6);
	if (FAILED(rc)) return 1;

	int m = 0;
	rc = AV6.GetInteger(m);
	if (FAILED(rc)) return 1;
	cout << "   The value at the 3rd index expected is 6. It is " << m << endl;

	CATFmAttributeValue AV7;
	int l = 7;
	AV7.SetInteger(l);
	rc = AV8.Set(3,AV7);
	if (FAILED(rc)) return 1;

	rc = ParseAttrValueContentForInt(AV8);
	if (FAILED(rc)) return 1;
	cout << "   The value at the 3rd index set is 7. Plz check the list contents above " << endl;

	// 5-3- Set the list of int to the feature
	rc = FeatFacadeOnList.SetValue(AttrNameMyListOfInt,AV8);
	if (FAILED(rc)) return 1;
	cout << "   Set the list of int attribute to the feature " << endl;

	// --------------------------------------------------------------------------   
	// 6- Scenario 5: Working with a list of int (Insert, Append, Set, Remove)
	// -------------------------------------------------------------------------- 
	// 6-1- Get the int list from MyLists feature 
	CATFmAttributeValue AV9;
	rc = FeatFacadeOnList.GetValue(AttrNameMyListOfInt,AV9);
	if (FAILED(rc)) return 1;

	// 6-2- List of Int modified with calls to Append, Insert, Set, Remove)
	// Append
	AV9.Append(20);
	cout << "   List appended with 20" << endl;
	// Display lists
	rc = ParseAttrValueContentForInt(AV9);
	cout << "   List of Ints above appended with 20. Confirm" << endl;

	// Insert
	AV9.Insert(2,25);
	cout << "   Insert 25 at index 2" << endl;
	// Display lists
	rc = ParseAttrValueContentForInt(AV9);
	cout << "   List of Ints has 25 at index 2. Confirm" << endl;

	// Set
	AV9.Set(4,35);
	cout << "   Set 35 at index 4" << endl;
	// Display lists
	rc = ParseAttrValueContentForInt(AV9);
	cout << "   List of Ints above has 35 at index 4. Confirm" << endl;

	// Remove
	AV9.Remove(2);
	cout << "   Remove value at index 2" << endl;
	// Display lists
	rc = ParseAttrValueContentForInt(AV9);
	cout << "   List of Ints has its value at index 2, removed. Confirm" << endl;

	// 6-3- Set the new list to MyLists  
	rc = FeatFacadeOnList.SetValue(AttrNameMyListOfInt,AV9);
	if (FAILED(rc)) return 1;
	cout << "   Set the list of int attribute to the feature " << endl;

#ifdef CATIAR214
	//-------------------------------------------------------------------------------------
	// - Save the session
	//-------------------------------------------------------------------------------------
	CATAdpSaver saver;
	rc = saver.Save();
	if ( FAILED(rc)  ) return 1;
	cout <<"   Save is successful " << endl;

	// Unload components from session
	Bag.RemoveAll();

	pContainer->Release();
	pContainer = NULL ;

	//--------------------------------------------------------------------------------------
	// - Closes the session
	//--------------------------------------------------------------------------------------
	rc = ::CAAAdpCloseSession();
	if (FAILED(rc) ) return 1;

	cout <<"   PLM session closed" << endl;
	cout << endl << "The CAAV5V6FmExtWorkingWithAttrValueForListPurpose main program ends ...."<< endl << endl;

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

HRESULT ParseAttrValueContentForStrings(CATFmAttributeValue & AV)
{
	cout << "Parsing the Attribute Value list of string contents" << endl;
	HRESULT rc = E_FAIL;
	for (int i=1; i<=AV.Size(); i++)
	{
		CATFmAttributeValue AV1 = AV[i];
		CATUnicodeString CUStr;
		rc = AV1.GetString(CUStr);
		if (SUCCEEDED(rc))
			cout << "The string list content is " << CUStr.ConvertToChar() << endl;
	}

	return rc;
}

HRESULT ParseAttrValueContentForInt(CATFmAttributeValue & AV)
{
	cout << "Parsing the Attribute Value list of int contents" << endl;
	HRESULT rc = E_FAIL;
	for (int i=1; i<=AV.Size(); i++)
	{
		CATFmAttributeValue AV1 = AV[i];
		int k;
		rc = AV1.GetInteger(k);
		if (SUCCEEDED(rc))
			cout << "The int list content is " << k << endl;
	}

	return rc;
}
