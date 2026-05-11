// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Abstract of Use Case "CAAV5V6OsmBuildUpdate":
// -------------------------------------------
//
// This sample program illustrates the Build/Update mechanism of the Feature Modeler 
// The UC refers to two features namely. CAAOsmAdd and CAAOsmSquare (details listed below)
// The "Sum" attribute of "CAAOsmAdd" is its : Attribute "First" + Attribute "Second"
// The "Num" attribute of "CAAOsmSquare" points to "Sum" attribute of "CAAOsmAdd"
// Owing to that reference link, at runtime value of "Num" updates so that it always equals 
// value of "Sum", if the latter is modified
// The Use Case valuates the "First" and "Second" attributes of "CAAOsmAdd"
// It then triggers an Update on the CAAOsmSquare feature
// CAAEV5V6OsmBehaviorCustomizationSquare::Update() detects CAAOsmAdd as a feature modified upstream, owing to the 
// referencing link that exists from "Num" to "Sum". 
// The CAAEV5V6OsmBehaviorCustomizationAdd::Update() is triggered which launches the CAAEV5V6OsmBehaviorCustomizationAdd:Build()
// The "Sum" attribute is computed. 
// The referencing "Num" attribute is updated on the run, triggered owing to a difference in the 
// update time stamps on the two attributes
// Once "Num", an sp_IN attribute of CAAOsmSquare is updated, it triggers the CAAEV5V6OsmBehaviorCustomizationSquare::Build() 
// The CAAEV5V6OsmBehaviorCustomizationSquare::Build() computes the "Square" attribute, by squaring "Num"
// The CATIFmFeatureBehaviorCustomization::Build() implementation on CAAOsmAdd and CAAOsmSquare 
// computes their "Sum" and "Square" attributes (sp_Out) respectively
//
// The "CAAOsmAdd" and "CAAOsmSquare" StartUps are defined in the "CAAOsmCatalogSU" Catalog
// The catalog is provided in the directory CAAFeatureModelerExt.edu\CNext\resources\graphic 
// and is accessible from your WS RTV, eventually. 
// The catalog is generated in the "CAAOsmCatalogSU" Use Case. 
// Here is the definition of the StartUps:
//
//		StartUp						Attribute
//		-------						---------
//      CAAOsmAdd                   First  (sp_In)
//                                  Second (sp_In)
//                                  Sum    (sp_Out)
//												|
//											   /|\												
//												|
//											   /|\
//												|
//      CAAOsmSquare                Num    (sp_In)
//                                  Square (sp_Out)
//=============================================================================
//  Steps :
//	The Session creation and Save Services code is different for V5 and V6 environment.
//	The crux of this use case is to study how the V5 FeatureModeler scenario is done using
//	V6 APIs

//   1- Retrieve Keys to Attributes associated with the features to be instantiated
//		1-1 Retrieve the key to the "First" Attribute (int, sp_IN)
//		1-2 Retrieve the key to the "Second" Attribute (int, sp_IN)
//		1-3 Retrieve the key to the "Sum" Attribute (int, sp_Out)
//		1-4 Retrieve the key to the "Num" Attribute (int, sp_In)
//		1-5 Retrieve the key to the "Square" Attribute (int, sp_Out)
//   2- Instantiating the "CAAOsmAdd" StartUp 
//			2-1- Retrieve "CAAOsmAdd" StartUp facade
//			2-2- Instantiate the CAAOsmAdd feature 
//			2-3- Valuate "First" attribute to 3. "Second" attribute valuated to 4
//	  3- Instantiate the "CAAOsmSquare" StartUp
//			3-1- Retrieve "CAAOsmSquare" StartUp facade
//			3-2- Instantiate the CAAOsmSquare feature
//			3-3- Set "Num",the sp_IN attribute of "CAAOsmSquare" to "Sum", the sp_Out attribute of "CAAOsmAdd"
//	  4- Launch an Update on the "CAAOsmSquare" instance and verify its validity 
//		 Crux of the UC lies in this sub-step. It illustrates the execution flow when an update on a feature is invoked
//		 Users are advised to study the following implementations to precisely understand the update-build mechanism in features
//			9-1- CAAEV5V6OsmBehaviorCustomizationSquare::Update() triggers the CAAEV5V6OsmBehaviorCustomizationAdd::Build()
//			9-2- CAAEV5V6OsmBehaviorCustomizationAdd::Build() which in turn triggers CAAEV5V6OsmBehaviorCustomizationSquare::Build()
//   5- Confirm the Update valuates the CAAOsmSquare instance "Num" attribute to 49
//   6- Modify the "CAAOsmAdd" instance "First" attribute. It is now valuated to 5
//   7- Relaunch Update of the "CAAOsmSquare" instance 
//   8- Confirm the Update valuates the "Num" attribute of CAAOsmSquare instance to 81
//
//=============================================================================
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAV5V6OsmBuildUpdate CatalogName DocumentStorageName" 
//  where the .CATfct extension (without the path) of the
//     catalog created by the CAAOsmCatalogSU use case and found under the
//     "Ws" + "Os" + resources + graphic directory, and
//  where the "DocumentStorageName" is the entire pathname, name and .CATPart extension
//    under which the new document is to be stored. 
//
//=============================================================================


// System Framework
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"
#include "CATIAV5Level.h"
#include "CATError.h"
#include "CATErrorMacros.h"
//#include "CATLISTP_CATBaseUnknown.h"

// FeatureModelerExt 
#include "CATFmFeatureFacade.h"
#include "CATFmContainerFacade.h"
#include "CATFmStartUpFacade.h"
#include "CATFmCredentials.h"
#include "CATFmAttributeName.h"
#include "CATFmAttributeValue.h"
#include "CATFmFeatureModelerID.h"

// Other
#include <iostream.h>

//-------------------------------------------------------------------------
//	Include guards when the Framework is in V6 Environment
//-------------------------------------------------------------------------
#ifdef CATIAR214

//local Framework
#include "CAAFmExtCreateRepRef.h"     // to create the Rep ref

//System Framework
#include "CATUnicodeString.h"
#include "CATString.h"
#include "CATBaseUnknown.h"

// ObjectModelerBase
#include "CATOmbLifeCycleRootsBag.h"

//CAT3DPhysicalRepInterfaces Framework
#include "CATIPsiRepresentationReference.h"  // interface on rep ref

// CATPLMIntegrationUse
#include "CATAdpSaver.h"

// CAAPLMClientAdapter.edu Framework
#include "CAAAdpCreateCloseSession.h"

#endif
//----------------

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

//=====================================================================================
 
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
	if (NULL != pDoc) cout << "New document created OK in V5 env" << endl << flush;
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
//------------------------------------------------------------------
//3- Build Credentials to access the catalog "CAAOsmCatalogSU"
//------------------------------------------------------------------
    
	CATFmCredentials MyCredential;
	rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
    rc = MyCredential.RegisterAsCatalogOwner("CAAOsmCatalogSU","CAAOsmClientId");
	if (FAILED(rc)) return 1;
	cout << "   Success in creating the credentials (IN V5 env )" << endl;

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
		cout << "Usage: CAAV5V6OsmBuildUpdate <Repository> <Server> <User> <Password> <SecurityCtx> <Environment> " ;
		cout <<endl;
		return 1;
	}

	cout << "The CAAV5V6OsmBuildUpdate main program begins ...."<< endl << endl;
  
//------------------------------------------------------------------
// - Initializes the PLM session 
//------------------------------------------------------------------
	HRESULT rc = ::CAAAdpCreateSession(iArgv[1], iArgv[2], iArgv[3], iArgv[4],iArgv[5]);
	if (FAILED(rc)) return 1;
		

	cout << "   PLM session initialized with the following connection parameters" << endl;
	cout << "      Repository=" << iArgv[1] << endl;
	cout << "      Server="     << iArgv[2] << endl;
	cout << "      UserID="     << iArgv[3] << endl;
	cout << "      UserPasswd=" << iArgv[4] << endl;
	cout << "      SecurityCtx=" << iArgv[5] << endl;

//-------------------------------------------------------------------------------
//- Build credential Object
//-------------------------------------------------------------------------------
	CATFmCredentials MyCredential;
	rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
    rc = MyCredential.RegisterAsCatalogOwner("CAAOsmCatalogSU","CAAOsmClientId");
	if (FAILED(rc)) return 1;
	cout << "   Success in creating the credentials" << endl;
	
//------------------------------------------------------------------
//- Creates a Product Representation Reference  
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

// =======================================================================================
// 1- Retrieve Keys to Attributes associated with the features to be instantiated
// =======================================================================================
	// 1-1 Retrieve the key to the "First" Attribute (int, sp_IN)
	CATFmAttributeName AddFirstAttrKey("First");
	// 1-2 Retrieve the key to the "Second" Attribute (int, sp_IN)
	CATFmAttributeName AddSecndAttrKey("Second");
	// 1-3 Retrieve the key to the "Sum" Attribute (int, sp_Out)
	CATFmAttributeName AddSumAttrKey("Sum");
	// 1-4 Retrieve the key to the "Num" Attribute (int, sp_In)
	CATFmAttributeName SqrNumAttrKey("Num");
	// 1-5 Retrieve the key to the "Square" Attribute (int, sp_Out)
	CATFmAttributeName SqrSqrAttrKey("Square");

//------------------------------------------------------------------------------------------------------------
//2- Instantiating the "CAAOsmAdd" StartUp 
//	 "First" attribute valuated to 3. "Second" attribute valuated to 4
//------------------------------------------------------------------------------------------------------------
	// 2-1- Retrieve "CAAOsmAdd" StartUp facade
	CATUnicodeString AddStartUpType("`CAAOsmAdd`@`CAAOsmCatalogSU.CATfct`");
	CATFmStartUpFacade AddStartUpFacade(MyCredential,AddStartUpType);
	cout << "   CAAOsmAdd StartUp Facade retrieved OK" << endl << flush;

	// 2-2- Instantiate the CAAOsmAdd feature
	CATFmFeatureFacade oFeatFacadeOnAddInst (MyCredential);
	rc = AddStartUpFacade.InstantiateIn(MyContainerFacade,oFeatFacadeOnAddInst);
	if (FAILED(rc)) 	return 1;
	
	cout << "   CAAOsmAdd SU Instance created OK**" << endl;

   // 2-3- Valuate the sp_IN attributes of the "CAAOsmAdd" instance
	CATFmAttributeValue FmAttrValue(3);
	rc = oFeatFacadeOnAddInst.SetValue(AddFirstAttrKey,FmAttrValue);
	if (FAILED(rc)) return 1;
		
	cout << "   Set the First attribute of CAAOsmAdd to 3" << endl;

	FmAttrValue.SetInteger(4);
	rc = oFeatFacadeOnAddInst.SetValue(AddSecndAttrKey,FmAttrValue);
	if (FAILED(rc)) return 1;
		
	cout << "   Set the Second attribute of CAAOsmAdd to 4" << endl;

//---------------------------------------------------------------------------------------------------
// 3- Instantiate the "CAAOsmSquare" StartUp
//---------------------------------------------------------------------------------------------------
	// 3-1- Retrieve "CAAOsmSquare" StartUp facade
	CATUnicodeString SquareStartUpType("`CAAOsmSquare`@`CAAOsmCatalogSU.CATfct`");
	CATFmStartUpFacade SquareStartUpFacade(MyCredential,SquareStartUpType);
	cout << "   CAAOsmSquare StartUp Facade retrieved OK" << endl << flush;

	// 3-2- Instantiate the CAAOsmSquare feature
	CATFmFeatureFacade oFeatFacadeOnSquareInst(MyCredential);
	rc = SquareStartUpFacade.InstantiateIn(MyContainerFacade,oFeatFacadeOnSquareInst);
	if (FAILED(rc)) 	return 1;
	
	cout << "   CAAOsmSquare SU Instance created OK" << endl;
	
	// 3-3- Set "Num", a sp_IN attribute of "CAAOsmSquare" instance with a link to "Sum", a sp_Out attribute of "CAAOsmAdd" instance
	// Set the reditected feature (CAAOsmAdd Instance) facade as a CATFmAttributeValue
	FmAttrValue.SetFeature(oFeatFacadeOnAddInst);
	rc = oFeatFacadeOnSquareInst.SetRedirectedValuation(SqrNumAttrKey,FmAttrValue,AddSumAttrKey);
	if (FAILED(rc)) return 1;
		
	cout << "   Success in setting Num, a sp_IN attribute of CAAOsmSquare instance with a link to Sum, a sp_Out attribute of CAAOsmAdd instance" << endl;

// ---------------------------------------------------------------------------------
// 4- Launch an Update on the "CAAOsmSquare" instance and verify its validity 
// ---------------------------------------------------------------------------------
	rc = oFeatFacadeOnSquareInst.Update();
	if (FAILED(rc)) return 1;
		 
	cout << "   Success in the 1st Update of CAAOsmSquare" << endl;

// ----------------------------------------------------------------------------------
// 5- Confirm the Update valuates the CAAOsmSquare instance "Num" attribute to 49
// ----------------------------------------------------------------------------------
	int sqVal = 0;
	FmAttrValue.Clear();
	oFeatFacadeOnSquareInst.GetValue(SqrSqrAttrKey,FmAttrValue);
	
	rc = FmAttrValue.GetInteger(sqVal);
	if (FAILED(rc)) return 1;
	
	cout << "   CAAOsmSquare Square attribute valuated to 49 as expected: " << sqVal << endl << flush;
	if ( 49 != sqVal )  return 1 ;
		

// --------------------------------------------------------------------------------
// 6- Modify the "CAAOsmAdd" instance "First" attribute. It is now valuated to 5
// --------------------------------------------------------------------------------
	FmAttrValue.SetInteger(5);
	rc = oFeatFacadeOnAddInst.SetValue(AddFirstAttrKey,FmAttrValue);
	if (FAILED(rc)) return 1;
		
	cout << "   Modified the First attribute of CAAOsmAdd to 5" << endl;

// ----------------------------------------------------
// 7- Relaunch Update of the "CAAOsmSquare" instance 
// ----------------------------------------------------
	rc = oFeatFacadeOnSquareInst.Update();
	if (FAILED(rc)) return 1;
		 
	cout << "   Success in the 2nd Update of CAAOsmSquare" << endl;

// ----------------------------------------------------------------------------------
// 8- Confirm the Update valuates the CAAOsmSquare instance "Num" attribute to 81
// ----------------------------------------------------------------------------------
	FmAttrValue.Clear();
	oFeatFacadeOnSquareInst.GetValue(SqrSqrAttrKey,FmAttrValue);
	rc = FmAttrValue.GetInteger(sqVal);
	if (FAILED(rc)) return 1;
	
	cout << "   CAAOsmSquare Square attribute valuated to 81 as expected: " << sqVal << endl << flush;
	if ( 81 != sqVal )  return 1 ;
				
#ifdef CATIAR214
//---------------------------------------------------------------------
// - Saves the Session
//---------------------------------------------------------------------
	CATAdpSaver saver;
    rc = saver.Save();
   	if (FAILED(rc)) 	return 1;
	cout <<"   Save is successful " << endl;

	// Unload components from session
	Bag.RemoveAll();
	
	// remove once no more used
	pContainer->Release();
	pContainer = NULL ;

//------------------------------------------------------------------
// - Closes the session
//------------------------------------------------------------------
	rc = ::CAAAdpCloseSession();
	if (FAILED(rc) ) return 1;
		
	cout <<"   Close is successful" <<endl;
	cout << endl << "The CAAV5V6OsmBuildUpdate main program ends ...."<< endl << endl;
	return 0;

#endif

#ifdef CATIAV5R23
/*--------------------------------------------------------------------------*/
/*  Save and remove the document and end the session when in V5 environment */
/*--------------------------------------------------------------------------*/

	piRootContainer->Release();
	piRootContainer = NULL;

		// @CSC-Filter UNER 
		rc = CATDocumentServices::SaveAs(*pDoc,
			iArgv[2]);
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

