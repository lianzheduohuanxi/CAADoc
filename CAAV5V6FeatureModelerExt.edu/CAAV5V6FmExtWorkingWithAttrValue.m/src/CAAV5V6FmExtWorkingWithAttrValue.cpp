// COPYRIGHT DASSAULT SYSTEMES 2010
//====================================================================================
// Abstract of Use Case "CAAV5V6FmExtWorkingWithAttrValue":
// -----------------------------------------------------------------------------------
// The objective of the current UC is to illustrate working with a CATFmAttributeValue class.
// The UC invokes key APIs of this class and analyses its returns
// User thus gains a better understanding of the context in which these APIs are relevant
// 
// The UC refers to features defined in the Catalog "CAAFmExtDeleteSU"
// An extract of the contents of the CAAFmExtDeleteSU.osm referred by this UC follows
/*
feature CAAFmExtDeleteList #startup {
specobject CAAFmExtListSpecNoArray #list
component  CAAFmExtListCompNoArray #list
specobject CAAFmExtListSpecArray #list #array
component  CAAFmExtListCompArray #list #array
}
feature CAAFmExtDeleteBasic #startup {
string CAAFmExtName
*/
 
//=====================================================================================
//  Steps
//
// 1- Create the feature data model
// 2- CATFmAttributeValue Instantiation with various Constructor calls. Confirmation of the Return Type
// 2-1- Default Constructor. Confirm type is void
// 2-2- Constructor with type int as input. Confirm type as int
// 2-3- Constructor with type double as input. Confirm type as double
// 2-4- Constructor with type CATUnicodeString as input. Confirm type as string
// 3- CATFmAttributeValue Set() calls. Confirmation of the resulting CATFmAttributeValue type
// 3-1- SetBoolean() call and confirm return type
// 3-2- SetByte() call and confirm return type
// 3-3- SetInteger() call and confirm return type
// 3-4- SetDouble() call and confirm type
// 3-5- SetString() call and confirm return type
// 3-6- SetFeature() call with feature input as a CATFmFeatureFacade type and confirm return type
// 3-7- SetFeature() call with feature input as a CATBaseUnknown_var type and confirm return type
// 3-8- GetFeature() call on an Attribute Value created with a default constructor
// 3-9- GetFeature() call on an Attribute Value set with a NULL feature
// 4- Retrieving an Attribute Value equivalent of a feature and confirm its type
// 5- Comparing two Attribute Values with a call to operator ==
// 6- Comparing two Attribute Values with a call to operator !=
// 7- Swap Attribute Values and confirm if types are changed
// 8- BuildFromCArrayOfDouble & ConvertToCArrayOfDouble calls
// 8-1- BuildFromCArrayOfDouble to build a CATFmAttributeValue equivalent of an array of double type
// 8-2- ConvertToCArrayOfDouble call to extract the complete double array from a CATFmAttributeValue type
// 8-3- ConvertToCArrayOfDouble() call returns a part of the double array
// 8-3- ConvertToCArrayOfDouble() call invoked by a CATFmAttributeValue type with positive cardinality and with NULL as input
// 8-4- ConvertToCArrayOfDouble() call invoked by a CATFmAttributeValue type with positive cardinality and with NULL as input, returns E_INVALIDARG
// 9- BuildFromCArrayOfInt & ConvertToCArrayOfInt calls
// 10- BuildFromCArrayOfByte & ConvertToCArrayOfByte calls
// 11- BuildFromCArrayOfBoolean & ConvertToCArrayOfBoolean calls
// 12- BuildFromCArrayOfString & ConvertToCArrayOfString calls
// 13- BuildFromListOfString & ConvertToListOfString calls
// 14- BuildFromListOfDouble & ConvertToListOfDouble calls
// 15- BuildFromListOfInt & ConvertToListOfInt calls
// 15-1- BuildFromListOfInt call to build a CATFmAttributeValue equivalent of a list of int type
// 15-2- ConvertToListOfInt call to extract a list of int types from its CATFmAttributeValue equivalent
// 15-3- BuildFromListOfInt call to build a CATFmAttributeValue equivalent of a list of byte type
// 15-4- ConvertToListOfInt call to extract a list of byte types from its CATFmAttributeValue equivalent
// 15-5- BuildFromListOfInt call to build a CATFmAttributeValue equivalent of a list of boolean type
// 15-6- ConvertToListOfInt call to extract a list of boolean types from its CATFmAttributeValue equivalent
// 16- BuildFromListOfFeatures & ConvertToListOfFeatures calls
// 16-1- BuildFromListOfFeatures call to build a CATFmAttributeValue equivalent of a list of feature type
// 16-2- ConvertToListOfFeatures call to extract a list of feature types from its CATFmAttributeValue equivalent
// 16-3- BuildFromListOfFeatures cal20l to build a CATFmAttributeValue equivalent from a list containing an invalid feature
//       returns E_FMINVALIDFEATURE 
// 16-4- BuildFromListOfFeatures call to build a CATFmAttributeValue equivalent from a list containing features not loaded in session 
//       returns E_FMINVALIDFEATURE
// 22- Closes the session

//=============================================================================
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAV5V6FmExtWorkingWithAttrValue DocumentStorageName" 
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
#include "CATListOfDouble.h" // CATRawColldouble
#include "CATListOfCATUnicodeString.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATListOfInt.h"   // CATRawCollint
#include "CATFmHRESULT.h"
#include "CATError.h"

// FeatureModelerExt 
#include "CATFmFeatureFacade.h"
#include "CATFmFeatureIterator.h"
#include "CATFmContainerFacade.h"
#include "CATFmStartUpFacade.h"
#include "CATFmCredentials.h"
#include "CATFmAttributeName.h"
#include "CATFmAttributeValue.h"
#include "CATFmFeatureModelerID.h"
#include "CATFmAttributeAndValueKind.h"

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

// ==================================================================================================================
// Build the basic Data Model 
HRESULT BuildTheDataModel (CATFmCredentials& MyCredential,
						   CATFmContainerFacade& MyContainerFacade,
						   CATFmFeatureFacade& FeatFacadeOnDeleteList,
						   CATFmFeatureFacade& FeatFacadeOnDeleteBasic1,CATFmFeatureFacade& FeatFacadeOnDeleteBasic2,
						   CATFmFeatureFacade& FeatFacadeOnDeleteBasic3,CATFmFeatureFacade& FeatFacadeOnDeleteBasic4,
						   CATFmFeatureFacade& FeatFacadeOnDeleteBasic5,CATFmFeatureFacade& FeatFacadeOnDeleteBasic6,
						   CATFmFeatureFacade& FeatFacadeOnDeleteBasic7,CATFmFeatureFacade& FeatFacadeOnDeleteBasic8,
						   CATFmFeatureFacade& FeatFacadeOnDeleteBasic9,CATFmFeatureFacade& FeatFacadeOnDeleteBasic10,
						   CATFmAttributeName& AttrNameListSpecNoArray, CATFmAttributeName& AttrNameListCompNoArray,
						   CATFmAttributeName& AttrNameListSpecArray,   CATFmAttributeName& AttrNameListCompArray,
						   int& oFeatCount);

// Scan an Applicative Container for Features. Output the Feature Count. Confirm if an input feature exists
HRESULT ScanAppliContForFeature (CATFmContainerFacade& ContFacade, CATFmCredentials& MyCredential,
								 CATUnicodeString& strFeatName, int& iFeatCount, CATBoolean& bFeatExists);

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
	rc = MyCredential.RegisterAsCatalogOwner("CAAFmExtDeleteSU","CAAFmExtDeleteSU");
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
		cout << "   Usage: CAAV5V6FmExtWorkingWithAttrValue <Repository> <Server> <User> <Password> <SecurityCtx> <Environment> " ;
		cout <<endl;
		return 1;
	}

	cout << "The CAAV5V6FmExtWorkingWithAttrValue main program begins in V5-V6 compatible FW........"<< endl << endl;

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
	rc = MyCredential.RegisterAsCatalogOwner("CAAFmExtDeleteSU","CAAFmExtDeleteSU");
	if (FAILED(rc)) return 1;
	cout << "   Success in creating the credentials" << endl;

	//------------------------------------------------------------------
	// - Creates a Product Representation Reference (Techno Rep)
	//------------------------------------------------------------------
	CATString EnvToUse = iArgv[6];
	CATString Repository = iArgv[1];
	CATUnicodeString NameAndTypeofContainer = "CAAFmExtAppliCont1" ;
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

	// -----------------------------------------
	// 1- Create the feature data model
	// -----------------------------------------
	CATFmFeatureFacade FeatFacadeOnDeleteList(MyCredential),FeatFacadeOnDeleteBasic1(MyCredential),
		FeatFacadeOnDeleteBasic2(MyCredential),FeatFacadeOnDeleteBasic3(MyCredential),
		FeatFacadeOnDeleteBasic4(MyCredential),FeatFacadeOnDeleteBasic5(MyCredential),
		FeatFacadeOnDeleteBasic6(MyCredential),FeatFacadeOnDeleteBasic7(MyCredential),
		FeatFacadeOnDeleteBasic8(MyCredential),FeatFacadeOnDeleteBasic9(MyCredential),
		FeatFacadeOnDeleteBasic10(MyCredential);

	CATFmAttributeName AttrNameListSpecNoArray ("CAAFmExtListSpecNoArray");
	CATFmAttributeName AttrNameListCompNoArray ("CAAFmExtListCompNoArray");
	CATFmAttributeName AttrNameListSpecArray ("CAAFmExtListSpecArray");
	CATFmAttributeName AttrNameListCompArray ("CAAFmExtListCompArray");

	int InitialFeatCount = 0;

	rc = BuildTheDataModel ( MyCredential,MyContainerFacade,
		FeatFacadeOnDeleteList,FeatFacadeOnDeleteBasic1,FeatFacadeOnDeleteBasic2,
		FeatFacadeOnDeleteBasic3,FeatFacadeOnDeleteBasic4,
		FeatFacadeOnDeleteBasic5,FeatFacadeOnDeleteBasic6,
		FeatFacadeOnDeleteBasic7,FeatFacadeOnDeleteBasic8,
		FeatFacadeOnDeleteBasic9,FeatFacadeOnDeleteBasic10,
		AttrNameListSpecNoArray,AttrNameListCompNoArray,
		AttrNameListSpecArray,AttrNameListCompArray,
		InitialFeatCount);

	if (FAILED(rc) || (11 != InitialFeatCount)) return 1;
	cout << "   The feature data model is created"<< endl;

	// -----------------------------------------------------------------------------------------------------------------------------
	// 2- CATFmAttributeValue Instantiation with various Constructor calls. Confirmation of the resulting CATFmAttributeValue type
	// -----------------------------------------------------------------------------------------------------------------------------
	// Instantiating a CATFmAttributeValue of different types
	// 2-1- Default Constructor. Confirm type is void
	CATFmAttributeValue AttrValueWithDefaultConstructor;
	CATFmAttributeAndValueKind AttrValueKind = AttrValueWithDefaultConstructor.Kind();
	if (CATFmKind_void != AttrValueKind) return 1;

	// 2-2- Constructor with type int as input. Confirm type as int
	int i = 90;
	CATFmAttributeValue AttrValueWithCtorTakingInt(i);
	AttrValueKind = AttrValueWithCtorTakingInt.Kind();
	if (CATFmKind_int != AttrValueKind) return 1;

	// 2-3- Constructor with type double as input. Confirm type as double
	double dbl = 90.98;
	CATFmAttributeValue AttrValueWithCtorTakingDouble(dbl);
	AttrValueKind = AttrValueWithCtorTakingDouble.Kind();
	if (CATFmKind_double != AttrValueKind) return 1;

	// 2-4- Constructor with type CATUnicodeString as input. Confirm type as string
	CATUnicodeString str("Ganesh");
	CATFmAttributeValue AttrValueWithCtorTakingCATUnicodeString(str);
	AttrValueKind = AttrValueWithCtorTakingCATUnicodeString.Kind();
	if (CATFmKind_string != AttrValueKind) return 1;

	// -------------------------------------------------------------------------------------------------------
	// 3- CATFmAttributeValue Set() calls. Confirmation of the resulting CATFmAttributeValue type
	// -------------------------------------------------------------------------------------------------------
	// Set() calls and check for corresponding types
	// 3-1- SetBoolean() call and confirm return type
	AttrValueWithDefaultConstructor.SetBoolean(TRUE); 
	AttrValueKind = AttrValueWithDefaultConstructor.Kind();
	if (CATFmKind_boolean != AttrValueKind) return 1;

	CATBoolean test = FALSE ;
	AttrValueWithDefaultConstructor.GetBoolean(test);
	if ( test != TRUE ) return 1;

	// 3-2- SetByte() call and confirm return type
	unsigned char iByte = 3;
	AttrValueWithDefaultConstructor.SetByte(iByte);
	AttrValueKind = AttrValueWithDefaultConstructor.Kind();
	if (CATFmKind_byte != AttrValueKind) return 1;

	unsigned char iByteTest = 0;
	AttrValueWithDefaultConstructor.GetByte(iByteTest);
	if ( iByte != iByteTest ) return 1;

	iByte = 0xEF;
	AttrValueWithDefaultConstructor.SetByte(iByte);
	iByteTest = 0;
	AttrValueWithDefaultConstructor.GetByte(iByteTest);
	if ( iByte != iByteTest ) return 1;

	// 3-3- SetInteger() call and confirm return type
	AttrValueWithDefaultConstructor.SetInteger(i);
	AttrValueKind = AttrValueWithDefaultConstructor.Kind();
	if (CATFmKind_int != AttrValueKind) return 1;

	// 3-4- SetDouble() call and confirm type
	AttrValueWithDefaultConstructor.SetDouble(dbl);
	AttrValueKind = AttrValueWithDefaultConstructor.Kind();
	if (CATFmKind_double != AttrValueKind) return 1;

	// 3-5- SetString() call and confirm return type
	AttrValueWithDefaultConstructor.SetString(str);
	AttrValueKind = AttrValueWithDefaultConstructor.Kind();
	if (CATFmKind_string != AttrValueKind) return 1;

	// 3-6- SetFeature() call with feature input as a CATFmFeatureFacade type and confirm return type
	AttrValueWithDefaultConstructor.SetFeature(FeatFacadeOnDeleteList);
	AttrValueKind = AttrValueWithDefaultConstructor.Kind();
	if (CATFmKind_feature != AttrValueKind) return 1;

	// 3-7- SetFeature() call with feature input as a CATBaseUnknown_var type and confirm return type
	CATFmAttributeValue AttrValue1;
	AttrValue1.SetFeature(FeatFacadeOnDeleteList.GetFeature());
	CATFmAttributeAndValueKind  AttrValueKind1 = AttrValue1.Kind();
	if (CATFmKind_feature != AttrValueKind1) return 1;

	// 3-8- GetFeature() call on an Attribute Value created with a default constructor
	CATFmAttributeValue AttrValueWithDefConst;
	CATFmFeatureFacade oFeatFacade1;
	rc = AttrValueWithDefConst.GetFeature(oFeatFacade1);
	if (E_FMTYPEMISMATCH != rc) return 1;

	// 3-9- GetFeature() call on an Attribute Value set with a NULL feature
	CATFmAttributeValue AttrValueSetWithNullFeat;
	AttrValueSetWithNullFeat.SetFeature(CATFmFeatureFacade(MyCredential,NULL));
	CATFmFeatureFacade oFeatFacade;
	rc = AttrValueSetWithNullFeat.GetFeature(oFeatFacade);
	if (S_FALSE != rc) return 1;

	// ---------------------------------------------------------------------------------
	// 4- Retrieving an Attribute Value equivalent of a feature and confirm its type
	// ---------------------------------------------------------------------------------
	CATFmAttributeValue AttrValue2 = FeatFacadeOnDeleteList.GetFeatureAsValue();
	CATFmAttributeAndValueKind  AttrValueKind2 = AttrValue2.Kind();
	if (CATFmKind_feature != AttrValueKind2) return 1;

	// ------------------------------------------------------------------
	// 5- Comparing two Attribute Values with a call to operator ==
	// ------------------------------------------------------------------
	if (AttrValue1 == AttrValue2) cout << "   The CATFmAttributeValue operator== call is OK" << endl;
	else return 1; 

	// --------------------------------------------------------------
	// 6- Comparing two Attribute Values with a call to operator !=
	// --------------------------------------------------------------
	if (AttrValueWithCtorTakingCATUnicodeString != AttrValue1) cout << "   The CATFmAttributeValue operator != call is OK" << endl;
	else return 1;

	// ---------------------------------------------------------
	// 7- Swap Attribute Values and confirm if types are changed
	// ---------------------------------------------------------
	CATFmAttributeValue::Swap(AttrValueWithCtorTakingCATUnicodeString,AttrValue1);

	CATFmAttributeAndValueKind  AttrValueKind3 = AttrValueWithCtorTakingCATUnicodeString.Kind();
	if (CATFmKind_feature != AttrValueKind3) return 1;

	CATFmAttributeAndValueKind  AttrValueKind4 = AttrValue1.Kind();
	if (CATFmKind_string != AttrValueKind4) return 1;

	// ------------------------------------------------------------
	// 8- BuildFromCArrayOfDouble & ConvertToCArrayOfDouble calls
	// ------------------------------------------------------------
	// 8-1- BuildFromCArrayOfDouble to build a CATFmAttributeValue equivalent of an array of double type
	CATFmAttributeValue AttrValueSample;
	double iArrayOfDouble[5] = {2.4,4.8,6.6,8.3,10.6};
	AttrValueSample.BuildFromCArrayOfDouble(iArrayOfDouble,5);
	cout << "   BuildFromCArrayOfDouble() call OK " << endl;

	AttrValueKind =  AttrValueSample.Kind();
	if (CATFmKind_double != AttrValueKind) return 1;

	// 8-2- ConvertToCArrayOfDouble call to extract the complete double array from a CATFmAttributeValue type
	double oArrayOfDouble [5] ;
	rc = AttrValueSample.ConvertToCArrayOfDouble(oArrayOfDouble,5);
	if (FAILED(rc)) return 1;
	cout << "   ConvertToCArrayOfDouble() call returns *** when Attribute Value of positive cardinality, type double, a valid pointer of type double, and size equal to max input" << endl;
	for (int k=0; k<=4; k++)
		cout << "   Element of Array of Double extracted from an Attribute Value is " << oArrayOfDouble[k] << endl;

	// 8-3- ConvertToCArrayOfDouble() call invoked by an CATFmAttributeValue type with positive cardinality and with NULL as input,
	//       returns E_INVALIDARG
	double* ArrayDoubleNullPtr = NULL;
	rc = AttrValueSample.ConvertToCArrayOfDouble(ArrayDoubleNullPtr,5); 
	if (E_INVALIDARG != rc) return 1; 
	cout << "   ConvertToCArrayOfDouble() call returns E_INVALIDARG when Attribute Value of positive cardinality, type double, a NULL pointer of type double input" << endl;

	// 8-4- ConvertToCArrayOfDouble() call invoked by an CATFmAttributeValue type of type double, 0 cardinality and with valid pointer of type double, as input
	//       returns E_INVALIDARG
	// Attribute Value of type double, cardinality 0, valid pointer input
	CATFmAttributeValue AttrValOfTypeDoubleCardinality0 = CATFmAttributeValue::CreateEmptyList(CATFmKind_double);
	rc = AttrValOfTypeDoubleCardinality0.ConvertToCArrayOfDouble(oArrayOfDouble,5);
	if (E_INVALIDARG != rc) return 1; 
	cout << "   ConvertToCArrayOfDouble() call returns E_INVALIDARG when Attribute Value of cardinality 0, type double, a valid pointer of type double input" << endl;
	for (int l=0; l<=4; l++)
		cout << "   ***Element of Array of Double extracted from an Attribute Value is " << oArrayOfDouble[l] << endl;


	// ------------------------------------------------------------
	// 9- BuildFromCArrayOfInt & ConvertToCArrayOfInt calls
	// ------------------------------------------------------------
	int iArrayOfInt[5] = {2,4,6,8,10};
	AttrValueSample.BuildFromCArrayOfInt(iArrayOfInt,5);

	AttrValueKind =  AttrValueSample.Kind();
	if (CATFmKind_int != AttrValueKind) return 1;

	int oArrayOfInt[5];
	rc = AttrValueSample.ConvertToCArrayOfInt(oArrayOfInt,5);
	if (FAILED(rc)) return 1;
	cout << "   BuildFromCArrayOfInt() and subsequent ConvertToCArrayOfInt() call OK " << endl;
	for (int m=0; m<=4; m++)
		cout << "   Element of Array of Int extracted from an Attribute Value is " << oArrayOfInt[m] << endl;

	// ------------------------------------------------------------
	// 10- BuildFromCArrayOfByte & ConvertToCArrayOfByte calls
	// ------------------------------------------------------------

	unsigned char iArrayOfByte[4] = { 'G', 'a', 3,0x00};
	AttrValueSample.BuildFromCArrayOfByte(iArrayOfByte,4);

	AttrValueKind =  AttrValueSample.Kind();
	if (CATFmKind_byte != AttrValueKind) return 1;

	// modification for removing the errors and memoryleaks
	unsigned char oArrayOfByte[4] ={ 0x00,0x00,0x00,0x00};
	rc = AttrValueSample.ConvertToCArrayOfByte(oArrayOfByte,4);
	if (FAILED(rc)) return 1;
	cout << "   BuildFromCArrayOfByte() and subsequent ConvertToCArrayOfByte() call OK " << endl;
	if(!memcmp(iArrayOfByte,oArrayOfByte,4))
		cout << "   The array of bytes extracted from an Attribute Value is " << oArrayOfByte << endl;
	else  return 1;

	// *** Attribute Value valuated with multiple types, is of kind CATFmKind_any
	CATFmAttributeValue AttrValueListSample;

	// Populate an attribute value with a list of values of varied types
	AttrValueListSample.SetFeature(FeatFacadeOnDeleteBasic1);

	CATUnicodeString str1("Hello World");
	AttrValueSample.SetString(str1);
	AttrValueListSample.Append(AttrValueSample);

	AttrValueKind = AttrValueListSample.Kind();

	if (CATFmKind_any != AttrValueKind)  return 1;
	cout << "  An Attribute Value valuated with various types (string, feature) is of kind CATFmKind_any" << endl;

	// ------------------------------------------------------------
	// 11- BuildFromCArrayOfBoolean & ConvertToCArrayOfBoolean calls
	// ------------------------------------------------------------
	CATBoolean  iArrayOfByte1[] = { TRUE, FALSE, };
	AttrValueSample.BuildFromCArrayOfBoolean(iArrayOfByte1,2);

	AttrValueKind =  AttrValueSample.Kind();
	if (CATFmKind_boolean != AttrValueKind) return 1;

	CATBoolean oArrayOfBool1[2];
	rc = AttrValueSample.ConvertToCArrayOfBoolean(oArrayOfBool1,2); 
	if (FAILED(rc)) return 1;

	if (TRUE != oArrayOfBool1[0]) return 1;  
	if (FALSE != oArrayOfBool1[1]) return 1;
	cout << "   BuildFromCArrayOfBoolean() & ConvertToCArrayOfBoolean() are OK" << endl;

	// ------------------------------------------------------------
	// 12- BuildFromCArrayOfString & ConvertToCArrayOfString calls
	// ------------------------------------------------------------
	CATUnicodeString iArrayOfString[2] ;
	iArrayOfString[0] = "Hello";
	iArrayOfString[1] = "World";

	CATFmAttributeValue AttrValueForAnArrayOfStrings;
	AttrValueForAnArrayOfStrings.BuildFromCArrayOfString(iArrayOfString,2);

	AttrValueKind =  AttrValueForAnArrayOfStrings.Kind();
	if (CATFmKind_string != AttrValueKind) return 1;

	CATUnicodeString oArrayOfString[2];
	rc = AttrValueForAnArrayOfStrings.ConvertToCArrayOfString(oArrayOfString,2);
	if (FAILED(rc)) return 1;
	for (int n=0; n<=1; n++)
		cout << "The value of string is " << oArrayOfString[n].ConvertToChar() << endl;

	cout << "   BuildFromCArrayOfString() & ConvertToCArrayOfString() are OK" << endl;

	// ------------------------------------------------------------
	// 13- BuildFromListOfString & ConvertToListOfString calls
	// ------------------------------------------------------------
	CATListValCATUnicodeString iListOfUnicodeString;

	CATUnicodeString UnicodeStr1("Edwige1");
	iListOfUnicodeString.Append(UnicodeStr1);

	CATUnicodeString UnicodeStr2("Edwige2");
	iListOfUnicodeString.Append(UnicodeStr2);

	CATUnicodeString UnicodeStr3("Edwige3");
	iListOfUnicodeString.Append(UnicodeStr3);

	CATUnicodeString UnicodeStr4("Edwige4");
	iListOfUnicodeString.Append(UnicodeStr4);

	AttrValueSample.BuildFromListOfString(iListOfUnicodeString);

	AttrValueKind =  AttrValueSample.Kind();
	if (CATFmKind_string != AttrValueKind) return 1;

	CATListValCATUnicodeString oListOfUnicodeString;
	rc = AttrValueSample.ConvertToListOfString(oListOfUnicodeString);
	if (FAILED(rc)) return 1;
	int o = 1;
 for (; o<=4; o++)
		cout << "The value of string is " << oListOfUnicodeString[o].ConvertToChar() << endl;
	cout << "   BuildFromListOfString() & ConvertToListOfString() are OK" << endl;

	// Attribute Value built with an array of strings convertedto a list of CATUnicodeStrings
	rc = AttrValueForAnArrayOfStrings.ConvertToListOfString(oListOfUnicodeString);
	if (FAILED(rc)) return 1;
	for (int p=1; p<=oListOfUnicodeString.Size(); p++)
		cout << "The value of string is " << oListOfUnicodeString[p].ConvertToChar() << endl;
	cout << "   Attribute Value built with an array of strings converted to a list of CATUnicodeStrings" << endl;

	// Mem release
	iListOfUnicodeString.RemoveAll();
	oListOfUnicodeString.RemoveAll();

	// ------------------------------------------------------------
	// 14- BuildFromListOfDouble & ConvertToListOfDouble calls
	// ------------------------------------------------------------
	CATRawColldouble iListOfDouble;
	iListOfDouble.Append(1.4);
	iListOfDouble.Append(-3.84);
	iListOfDouble.Append(100.2);

	AttrValueSample.BuildFromListOfDouble(iListOfDouble);

	AttrValueKind =  AttrValueSample.Kind();
	if (CATFmKind_double != AttrValueKind) return 1;

	CATRawColldouble oListOfDouble;
	rc = AttrValueSample.ConvertToListOfDouble(oListOfDouble);
	if (FAILED(rc)) return 1;
	for ( o=1; o<=3; o++)
		cout << "The value of double is " << oListOfDouble[o] << endl;
	cout << "   BuildFromListOfDouble() & ConvertToListOfDouble() are OK" << endl;

	// Mem release
	iListOfDouble.RemoveAll();
	oListOfDouble.RemoveAll();

	// ------------------------------------------------------------
	// 15- BuildFromListOfInt & ConvertToListOfInt calls
	// ------------------------------------------------------------
	// 15-1- BuildFromListOfInt call to build a CATFmAttributeValue equivalent of a list of int type
	CATFmAttributeValue AttrValueBuiltFromListOfInt;
	CATRawCollint iListOfInt;
	iListOfInt.Append(1);
	iListOfInt.Append(0);
	iListOfInt.Append(1);
	iListOfInt.Append(8);
	AttrValueBuiltFromListOfInt.BuildFromListOfInt(iListOfInt,CATFmKind_int);

	AttrValueKind =  AttrValueBuiltFromListOfInt.Kind();
	if (CATFmKind_int != AttrValueKind) return 1;

	// 15-2- ConvertToListOfInt call to extract a list of int types from its CATFmAttributeValue equivalent
	CATRawCollint oListOfInt;
	rc = AttrValueBuiltFromListOfInt.ConvertToListOfInt(oListOfInt);
	if (FAILED(rc)) return 1;
	for (int a=1; a<=4; a++)
		cout << "The value of an element in the list of int is " << oListOfInt[a] << endl;
	cout << "   BuildFromListOfInt() &  ConvertToListOfInt() for a CATFmKind_int type returns OK" << endl;

	// Mem Release
	oListOfInt.RemoveAll();

	// 15-3- BuildFromListOfInt call to build a CATFmAttributeValue equivalent of a list of byte type
	AttrValueBuiltFromListOfInt.BuildFromListOfInt(iListOfInt,CATFmKind_byte);

	AttrValueKind =  AttrValueBuiltFromListOfInt.Kind();
	if (CATFmKind_byte != AttrValueKind) return 1;

	// 15-4- ConvertToListOfInt call to extract a list of byte types from its CATFmAttributeValue equivalent
	rc = AttrValueBuiltFromListOfInt.ConvertToListOfInt(oListOfInt);
	if (FAILED(rc)) return 1;
	for (int q=1; q<=4; q++)
		cout << "The value of an element in the list of int is " << oListOfInt[q] << endl;
	cout << "   BuildFromListOfInt() &  ConvertToListOfInt() for a CATFmKind_byte type returns OK" << endl;

	// Mem Release
	oListOfInt.RemoveAll();

	// 15-5- BuildFromListOfInt call to build a CATFmAttributeValue equivalent of a list of boolean type
	AttrValueBuiltFromListOfInt.BuildFromListOfInt(iListOfInt,CATFmKind_boolean);

	AttrValueKind =  AttrValueBuiltFromListOfInt.Kind();
	if (CATFmKind_boolean != AttrValueKind) return 1;

	// 15-6- ConvertToListOfInt call to extract a list of boolean types from its CATFmAttributeValue equivalent
	rc = AttrValueBuiltFromListOfInt.ConvertToListOfInt(oListOfInt);
	if (FAILED(rc)) return 1;
	for (int r=1; r<=4; r++)
		cout << "The value of an element in the list of int is " << oListOfInt[r] << endl; 
	cout << "   BuildFromListOfInt() &  ConvertToListOfInt() for a CATFmKind_boolean type returns OK" << endl;

	// Mem Release
	oListOfInt.RemoveAll();
	iListOfInt.RemoveAll();

	// ------------------------------------------------------------
	// 16- BuildFromListOfFeatures & ConvertToListOfFeatures calls
	// ------------------------------------------------------------
	// 16-1- BuildFromListOfFeatures call to build a CATFmAttributeValue equivalent of a list of feature type
	CATListValCATBaseUnknown_var iListOfFeature;
	iListOfFeature.Append(FeatFacadeOnDeleteList.GetFeature());
	iListOfFeature.Append(FeatFacadeOnDeleteBasic1.GetFeature());
	iListOfFeature.Append(FeatFacadeOnDeleteBasic2.GetFeature());

	AttrValueSample.BuildFromListOfFeatures(iListOfFeature);
	if (FAILED(rc)) return 1;
	AttrValueKind =  AttrValueSample.Kind();
	if (CATFmKind_feature != AttrValueKind) return 1;

	// 16-2- ConvertToListOfFeatures call to extract a list of feature types from its CATFmAttributeValue equivalent
	CATListValCATBaseUnknown_var oListOfFeature;
	rc = AttrValueSample.ConvertToListOfFeatures(oListOfFeature);

	CATFmFeatureFacade FeatFacade(MyCredential);
	CATUnicodeString strDisplayName;
	for (int s=1; s<=3; s++)
	{
		FeatFacade = oListOfFeature[s];
		rc = FeatFacade.GetDisplayName(strDisplayName);
		if (SUCCEEDED(rc))
			cout << " The display name of feat is " << strDisplayName.ConvertToChar() << endl;
	}

	// Mem Release
	oListOfFeature.RemoveAll(); 

	// 16-3- BuildFromListOfFeatures call to build a CATFmAttributeValue equivalent from a list containing an invalid feature
	//       returns E_FMINVALIDFEATURE 
	CATListValCATBaseUnknown_var iListOfFeature1;
	iListOfFeature1.Append(MyContainerFacade.GetContainer()); 
	iListOfFeature1.Append(NULL_var);

	AttrValueSample.BuildFromListOfFeatures(iListOfFeature1);
	if (FAILED(rc)) return 1;
	AttrValueKind =  AttrValueSample.Kind();
	if (CATFmKind_feature != AttrValueKind) return 1;

	rc = AttrValueSample.ConvertToListOfFeatures(oListOfFeature);
	if (S_OK != rc) return 1;
	if (2 != oListOfFeature.Size()) return 1;

	// Mem Release
	oListOfFeature.RemoveAll();
	iListOfFeature1.RemoveAll();

#ifdef CATIAR214

	// 16-4- BuildFromListOfFeatures call to build a CATFmAttributeValue equivalent from a list containing features not loaded in session 
	//       returns E_FMINVALIDFEATURE

	AttrValueSample.BuildFromListOfFeatures(iListOfFeature);
	if (FAILED(rc)) return 1;

	// Unload features from session
	Bag.RemoveAll();

	rc = AttrValueSample.ConvertToListOfFeatures(oListOfFeature);
	if (E_FMINVALIDFEATURE != rc) return 1;

	cout <<"   The feature are no more is session, ConvertToListOfFeatures fails" << endl;

#endif

	// Mem Release
	oListOfFeature.RemoveAll();
	iListOfFeature.RemoveAll();

#ifdef CATIAR214

	pContainer->Release();
	pContainer = NULL ;

	//--------------------------------------------------------------------------------------
	// - Closes the session
	//--------------------------------------------------------------------------------------
	rc = ::CAAAdpCloseSession();
	if (FAILED(rc) ) return 1;

	cout <<"   PLM session closed" << endl;
	cout << endl << "The CAAFmExtWorkingWithAttrValue main program ends ...."<< endl << endl;

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

//--------------------------------------------------------------------------------------
// Build the Data Model for feature attribute tests
//--------------------------------------------------------------------------------------
HRESULT BuildTheDataModel (CATFmCredentials& MyCredential,
						   CATFmContainerFacade& MyContainerFacade,
						   CATFmFeatureFacade& FeatFacadeOnDeleteList,
						   CATFmFeatureFacade& FeatFacadeOnDeleteBasic1,CATFmFeatureFacade& FeatFacadeOnDeleteBasic2,
						   CATFmFeatureFacade& FeatFacadeOnDeleteBasic3,CATFmFeatureFacade& FeatFacadeOnDeleteBasic4,
						   CATFmFeatureFacade& FeatFacadeOnDeleteBasic5,CATFmFeatureFacade& FeatFacadeOnDeleteBasic6,
						   CATFmFeatureFacade& FeatFacadeOnDeleteBasic7,CATFmFeatureFacade& FeatFacadeOnDeleteBasic8,
						   CATFmFeatureFacade& FeatFacadeOnDeleteBasic9,CATFmFeatureFacade& FeatFacadeOnDeleteBasic10,
						   CATFmAttributeName& AttrNameListSpecNoArray, CATFmAttributeName& AttrNameListCompNoArray,
						   CATFmAttributeName& AttrNameListSpecArray,   CATFmAttributeName& AttrNameListCompArray,
						   int& oFeatCount)
{
	cout << "   Build the Data Model" << endl;
	oFeatCount = 0;
	// -----------------------------
	//  Instantiate the Features
	// -----------------------------
	// Creating the DeleteList feature
	CATUnicodeString DeleteListStartUpType("`CAAFmExtDeleteList`#2@`CAAFmExtDeleteSU.CATfct`");
	CATFmStartUpFacade SUFacadeOnDeleteList(MyCredential,DeleteListStartUpType);
	cout << "   CAAFmExtDeleteList StartUp Facade retrieved OK" << endl << flush;

	HRESULT rc = SUFacadeOnDeleteList.InstantiateIn(MyContainerFacade,FeatFacadeOnDeleteList);
	if (FAILED(rc)) return 1;
	cout << "   DeleteList Feature created OK" << endl;

	// Set CAAFmExtDeleteList as the AutoNumbering Provider for all the subsequent features
	CATFmAttributeValue AttrValueForAutoNbrProv;
	AttrValueForAutoNbrProv.SetFeature(FeatFacadeOnDeleteList);

	// Creating the DeleteBasic feature
	CATUnicodeString DeleteBasicStartUpType("`CAAFmExtDeleteBasic`#3@`CAAFmExtDeleteSU.CATfct`");
	CATFmStartUpFacade SUFacadeOnDeleteBasic(MyCredential,DeleteBasicStartUpType);
	cout << "   CAAFmExtDeleteBasic StartUp Facade retrieved OK" << endl << flush;

	rc = SUFacadeOnDeleteBasic.InstantiateIn(MyContainerFacade,FeatFacadeOnDeleteBasic1);
	if (FAILED(rc)) return 1;
	cout << "   DeleteBasic 1 Feature created OK" << endl;

	rc = FeatFacadeOnDeleteBasic1.SetAutoNumberingProvider(AttrValueForAutoNbrProv);
	if (FAILED(rc)) return 1;

	rc = SUFacadeOnDeleteBasic.InstantiateIn(MyContainerFacade,FeatFacadeOnDeleteBasic2);
	if (FAILED(rc)) return 1;
	cout << "   DeleteBasic 2 Feature created OK" << endl;

	rc = FeatFacadeOnDeleteBasic2.SetAutoNumberingProvider(AttrValueForAutoNbrProv);
	if (FAILED(rc)) return 1;

	rc = SUFacadeOnDeleteBasic.InstantiateIn(MyContainerFacade,FeatFacadeOnDeleteBasic3);
	if (FAILED(rc)) return 1;
	cout << "   DeleteBasic 3 Feature created OK" << endl;

	rc = FeatFacadeOnDeleteBasic3.SetAutoNumberingProvider(AttrValueForAutoNbrProv);
	if (FAILED(rc)) return 1;

	// Valuate CAAFmExtListSpecNoArray attribute (specobject, no array) with features 
	// DeleteBasic3, DeleteBasic2, DeleteBasic1
	CATFmAttributeValue AttrValueList;
	AttrValueList.SetFeature(FeatFacadeOnDeleteBasic1);

	CATFmAttributeValue AttrValue;
	AttrValue.SetFeature(FeatFacadeOnDeleteBasic2);
	AttrValueList.Append(AttrValue);

	AttrValue.SetFeature(FeatFacadeOnDeleteBasic3);
	AttrValueList.Append(AttrValue);

	rc = FeatFacadeOnDeleteList.SetValue(AttrNameListSpecNoArray,AttrValueList);
	if (FAILED(rc)) return 1;

	// Create features DeleteBasic4, DeleteBasic5
	rc = SUFacadeOnDeleteBasic.InstantiateIn(MyContainerFacade,FeatFacadeOnDeleteBasic4);
	if (FAILED(rc)) return 1;
	cout << "   DeleteBasic 4 Feature created OK" << endl;	

	rc = FeatFacadeOnDeleteBasic4.SetAutoNumberingProvider(AttrValueForAutoNbrProv);
	if (FAILED(rc)) return 1;

	rc = SUFacadeOnDeleteBasic.InstantiateIn(MyContainerFacade,FeatFacadeOnDeleteBasic5);
	if (FAILED(rc)) return 1;
	cout << "   DeleteBasic 5 Feature created OK" << endl;

	rc = FeatFacadeOnDeleteBasic5.SetAutoNumberingProvider(AttrValueForAutoNbrProv);
	if (FAILED(rc)) return 1;

	// Valuate CAAFmExtListCompNoArray  attribute (component, no array) with features 
	// DeleteBasic4, DeleteBasic5, DeleteBasic3
	CATFmAttributeValue AttrValueList1;
	AttrValueList1.SetFeature(FeatFacadeOnDeleteBasic4); 

	AttrValue.SetFeature(FeatFacadeOnDeleteBasic5);
	AttrValueList1.Append(AttrValue);

	AttrValue.SetFeature(FeatFacadeOnDeleteBasic3); 
	AttrValueList1.Append(AttrValue);

	FeatFacadeOnDeleteList.SetValue(AttrNameListCompNoArray,AttrValueList1);

	// Create features DeleteBasic6, DeleteBasic7
	rc = SUFacadeOnDeleteBasic.InstantiateIn(MyContainerFacade,FeatFacadeOnDeleteBasic6);
	if (FAILED(rc)) return 1;
	cout << "   DeleteBasic 6 Feature created OK" << endl;

	rc = FeatFacadeOnDeleteBasic6.SetAutoNumberingProvider(AttrValueForAutoNbrProv);
	if (FAILED(rc)) return 1;

	rc = SUFacadeOnDeleteBasic.InstantiateIn(MyContainerFacade,FeatFacadeOnDeleteBasic7);
	if (FAILED(rc)) return 1;
	cout << "   DeleteBasic 7 Feature created OK" << endl;

	rc = FeatFacadeOnDeleteBasic7.SetAutoNumberingProvider(AttrValueForAutoNbrProv);
	if (FAILED(rc)) return 1;

	// Valuate CAAFmExtListSpecArray  attribute (specobject, array) with features 
	// DeleteBasic6, DeleteBasic7
	AttrValue.SetFeature(FeatFacadeOnDeleteBasic6);
	rc = FeatFacadeOnDeleteList.SetValue(AttrNameListSpecArray,AttrValue);

	AttrValue.SetFeature(FeatFacadeOnDeleteBasic7);
	rc = FeatFacadeOnDeleteList.AppendValue(AttrNameListSpecArray,AttrValue);

	// Create features DeleteBasic8, DeleteBasic9, DeleteBasic10
	rc = SUFacadeOnDeleteBasic.InstantiateIn(MyContainerFacade,FeatFacadeOnDeleteBasic8);
	if (FAILED(rc)) return 1;
	cout << "   DeleteBasic 8 Feature created OK" << endl;

	rc = FeatFacadeOnDeleteBasic8.SetAutoNumberingProvider(AttrValueForAutoNbrProv);
	if (FAILED(rc)) return 1;

	rc = SUFacadeOnDeleteBasic.InstantiateIn(MyContainerFacade,FeatFacadeOnDeleteBasic9);
	if (FAILED(rc)) return 1;
	cout << "   DeleteBasic 9 Feature created OK" << endl;

	rc = FeatFacadeOnDeleteBasic9.SetAutoNumberingProvider(AttrValueForAutoNbrProv);
	if (FAILED(rc)) return 1;

	rc = SUFacadeOnDeleteBasic.InstantiateIn(MyContainerFacade,FeatFacadeOnDeleteBasic10);
	if (FAILED(rc)) return 1;
	cout << "   DeleteBasic 10 Feature created OK" << endl;

	rc = FeatFacadeOnDeleteBasic10.SetAutoNumberingProvider(AttrValueForAutoNbrProv);
	if (FAILED(rc)) return 1;

	// Valuate CAAFmExtListCompArray attribute (component, array) with features 
	// DeleteBasic8, DeleteBasic9, DeleteBasic10
	AttrValue.SetFeature(FeatFacadeOnDeleteBasic8);
	rc = FeatFacadeOnDeleteList.InsertValue(AttrNameListCompArray,1,AttrValue);

	AttrValue.SetFeature(FeatFacadeOnDeleteBasic9);
	rc = FeatFacadeOnDeleteList.AppendValue(AttrNameListCompArray,AttrValue);

	AttrValue.SetFeature(FeatFacadeOnDeleteBasic10);
	rc = FeatFacadeOnDeleteList.AppendValue(AttrNameListCompArray,AttrValue);

	// Retrieve the feat count in the Applicative Container
	CATUnicodeString strFeatNameNull("");
	CATBoolean bFeatExists = FALSE;
	rc = ScanAppliContForFeature (MyContainerFacade,MyCredential,strFeatNameNull,oFeatCount,bFeatExists);
	if (FAILED(rc) || (oFeatCount != 11)) return 1;

	return rc;
}

// Scan an Applicative Container for Features. Output the Feature Count. Confirm if an input feature exists
HRESULT ScanAppliContForFeature (CATFmContainerFacade& ContFacade, CATFmCredentials& MyCredential,
								 CATUnicodeString& strFeatName, int& iFeatCount, CATBoolean& bFeatExists)
{
	cout << "   ScanAppliContForFeature() call" << endl;
	iFeatCount = 0;
	CATFmFeatureFacade FeatFacade(MyCredential);
	CATUnicodeString strFeatDisplayName;
	bFeatExists = FALSE;
	CATFmFeatureIterator oFeatIterator;
	HRESULT rc = S_OK;
	HRESULT hr =  ContFacade.ScanFeatures(oFeatIterator);
	while (SUCCEEDED(hr) && SUCCEEDED(rc))
	{
		hr = oFeatIterator.Next(FeatFacade);
		if (SUCCEEDED(hr))
		{
			iFeatCount++;
			rc = FeatFacade.GetDisplayName(strFeatDisplayName);
			cout << " display name is " << strFeatDisplayName.ConvertToChar() << endl;
			if (SUCCEEDED(rc) && (strFeatName == strFeatDisplayName))
			{
				bFeatExists = TRUE;
				cout << "   Input feature exists in the Applicative Container. Its display name is " << strFeatDisplayName.ConvertToChar() << endl;
			}
		}
	}

	return rc;
}

