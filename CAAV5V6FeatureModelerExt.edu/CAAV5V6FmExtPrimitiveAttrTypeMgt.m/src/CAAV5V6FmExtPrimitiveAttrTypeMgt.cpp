// COPYRIGHT DASSAULT SYSTEMES 2010
//=============================================================================
// Abstract of Use Case "CAAV5V6FmExtPrimitiveAttrTypeMgt":
// ----------------------------------------------
// The Use Case illustrates managing a simple attribute type associated with a feature (StartUp, feature instances)
// A feature attribute value could either be inherited from its StartUp or from its feature reference or
// overridden by an explicitly assigned value locally
// 
// The UC refers to a feature "CAAFmExtPoint2D" defined in the Catalog "CAAFmExtElementCatalog"
// The feature definition follows (the contents of the CAAFmExtElementCatalog.osm)

/*
document `CAAFmExtElementCatalog.CATfct` {
container RootCont #root {
feature CAAFmExtPoint2D #startup {
double x
x = -1
double y
}
}
}
*/

//=============================================================================
//  Steps
//
// 1- Initializing or declaring the Variables required for this main
// 2- Attribute Valuation of a feature instantiated from a StartUp (read from OSM file)
//  2-1- Instantiate a "CAAFmExtPoint2D"  StartUp (referred as Point2D1)
// 	2-2- Confirm the Point2D1 "X" attribute is set and inherited
// 	2-3- Also confirm the Point2D1 "X" attribute value is set to -1, the default value set in the OSM file
// 	2-4- Confirm the Point2D1 "Y" attribute is unset and inherited
// 	2-5- Also confirm the Y attribute value is 0 

// 3- Attribute Valuation of a feature by Inheritance (Valuation by Reference)
//	3-1- Instantiate a CAAFmExtPoint2D (referred as Point2D2) from Point2D1
//	3-2- Confirm the Point2D2 "X" attribute is set and inherited
//	3-3- Also confirm the Point2D2  "X" attribute value is -1, that inherited from Reference
// 	3-4- Confirm the Point2D2 "Y" attribute is unset and inherited
// 	3-5- Also confirm the Y attribute value is 0, that inherited from its reference Point2D1
// 	3-6- Set the Point2D1 "X" attribute value to 5
// 	3-7- Retrieve the Point2D2 "X" attribute value. The value is 5 inherited from the feature reference
//  3-8- Set the Point2D2 "X" attribute value to 7
//  3-9- Set the Point2D1 "X" attribute value to 8
// 3-10- Retrieve the Point2D2 "X" attribute value. Value still 7. Not overridden by 8 (value of Reference)

// 4- Unset an Attribute Value
//	4-1- Unset the Point2D1 "X" attribute value
// 	4-2- Confirm the Point2D1 "X" attribute is Unset and locally
//  4-3- Also confirm Point2D1 X attribute is valuated to 0 and
// 	     the CATFmFeatureFacade::GetValue call returns S_FALSE, for an unset attribute

// 5- Set an Attribute Value to 0, distinct from UNSET
// 5-1- Set the Point2D1 "Y" attribute value to 0
// 5-2- Confirm the Point2D1 Y attribute is defined locally and set
// 5-3- Confirm the Point2D1 Y attribute is valuated to 0, and the return of the CATFmFeatureFacade::GetValue()

// 6- Remove the Locally Defined Attribute Value
//	6-1- Remove Locally Defined Value assigned to the Point2D2 "X" attribute
// 	6-2- Confirm the Point2D2 "X" attribute is Unset and inherited
// 	6-3- Confirm the Point2D2 "X" attribute is valuated to 0, that of its reference Point2D1 and GetValue() call returns S_FALSE
//	6-4- Remove Locally Defined Value assigned to the Point2D1 "X" attribute
// 	6-5- Retrieve the Point2D2 "X" attribute value. It is -1, the default value set in the OSM file

// - Saves the Session
// - Closes the Session
//
//=============================================================================
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAV5V6FmExtPrimitiveAttrTypeMgt DocumentStorageName" 
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

// FeatureModelerExt 
#include "CATFmFeatureFacade.h"
#include "CATFmContainerFacade.h"
#include "CATFmStartUpFacade.h"
#include "CATFmCredentials.h"
#include "CATFmAttributeName.h"
#include "CATFmAttributeValue.h"
#include "CATFmAttributeAndValueKind.h"
#include "CATFmAttributeValuationInfo.h"
#include "CATFmFeatureModelerID.h"
#include "CATFmAttributeValuationMode.h"

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

// ObjectModelerBase Framework
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

//=======================================================================================
// Sub function confirming the feature  attribute info 
HRESULT ConfirmAttributeInfo (CATFmFeatureFacade & iFeatFacadeOnFeat,
							  CATFmAttributeName  & iAttrKey,
							  CATFmAttributeValuationMode iValuationMode);

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
	cout << "   Success in creating the credentials in V5 env" << endl;

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
		cout << "   Usage: CAAV5V6FmExtPrimitiveAttrTypeMgt <Repository> <Server> <User> <Password> <SecurityCtx> <Environment> " ;
		cout <<endl;
		return 1;
	}

	cout << "   The CAAV5V6FmExtPrimitiveAttrTypeMgt main program begins in V5-V6 compatible FW........"<< endl << endl;

	//------------------------------------------------------------------
	// 2 - Initializes the PLM session 
	//------------------------------------------------------------------
	HRESULT rc = ::CAAAdpCreateSession(iArgv[1], iArgv[2], iArgv[3], iArgv[4],iArgv[5]);
	if (FAILED(rc))	 return 1;   

	cout << "   PLM session initialized with the following connection parameters" << endl;
	cout << "      Repository=" << iArgv[1] << endl;
	cout << "      Server="     << iArgv[2] << endl;
	cout << "      UserID="     << iArgv[3] << endl;
	cout << "      UserPasswd=" << iArgv[4] << endl;
	cout << "      SecurityCtx=" << iArgv[5] << endl;

	//-------------------------------------------------------------------------------------------------
	// 3- Creating a Credential Object which authorizes client to handle the "CAAFmExtPoint2D" feature
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
	cout <<"   The Product Representation Reference is created" << endl;

	// Insert component that is loaded in session, in BAG
	CATOmbLifeCycleRootsBag Bag;
	Bag.InsertRoot(pPsiCreatedRepRef);

	//Create container facade to work with
	CATFmContainerFacade MyContainerFacade(MyCredential,pContainer);

	pPsiCreatedRepRef->Release();
	pPsiCreatedRepRef = NULL;


#endif

	//-----------------------------------------------------------------------------------------------
	// 1- Initializing or declaring the Variables required for this main
	//-----------------------------------------------------------------------------------------------

	CATFmAttributeName XAttrKey("x");
	CATFmAttributeName YAttrKey("y");

	CATFmAttributeValue AttrValueSet;
	double val = 0 ; 
	// -----------------------------------------------------------------------
	//  2- Feature Attribute Values inherited from the StartUp OSM File
	// -----------------------------------------------------------------------
	// 	2-1- Instantiate a "CAAFmExtPoint2D"  StartUp (referred as Point2D1)
	cout << "   ============================================================== " << endl;
	cout << "   Attribute Value inherited from the StartUp OSM File "            << endl;
	cout << "   ============================================================== " << endl;
	CATUnicodeString Point2DStartUpType("`CAAFmExtPoint2D`@`CAAFmExtElementCatalog.CATfct`");
	CATFmStartUpFacade SUFacadeOnPoint2D(MyCredential,Point2DStartUpType);
	cout << "   CAAFmExtPoint2D StartUp Facade retrieved OK" << endl << flush;

	CATFmFeatureFacade FeatFacadeOnPoint2D1(MyCredential);
	rc = SUFacadeOnPoint2D.InstantiateIn(MyContainerFacade,FeatFacadeOnPoint2D1);
	if (FAILED(rc)) return 1;
	cout << "   Feature Instance Point2D1 created OK" << endl;

	cout << "   --------------------------------------------------" << endl;
	cout << "   Retrieve the Point2D1 X Attribute Info and Value" << endl;
	// 2-2- Confirm the Point2D1 X attribute is inherited 
	rc = ConfirmAttributeInfo(FeatFacadeOnPoint2D1,XAttrKey,CATFmInherited);
	if (FAILED(rc)) return 1;  

	cout << "   The Point2D1 X attribute is INHERITED" << endl;

	// 2-3- Confirm the Point2D1 X attribute is valuated to -1, the default value set in the OSM
	rc = FeatFacadeOnPoint2D1.GetValue(XAttrKey,AttrValueSet);
	if (rc != S_OK) return 1;  
	AttrValueSet.GetDouble(val);
	if ( val != -1) return 1; 

	cout << "   The Point2D1 X attribute is set to -1, the default value set in the OSM file " << endl;

	// 2-4- Confirm the Point2D1 Y attribute is inherited
	cout << "   Retrieve the Point2D1 Y Attribute Info and Value" << endl;
	rc = ConfirmAttributeInfo (FeatFacadeOnPoint2D1,YAttrKey,CATFmInherited);
	if (FAILED(rc))  return 1;

	cout << "   The Point2D1 Y attribute is INHERITED" << endl;

	// 2-5- Confirm the Point2D1 Y attribute is valuated to 0, since its not set, as yet
	rc = FeatFacadeOnPoint2D1.GetValue(YAttrKey,AttrValueSet);
	if (rc != S_FALSE) return 1; 

	AttrValueSet.GetDouble(val);
	if ( val != 0) return 1; 
	cout << "   The Point2D1 Y attribute value is 0. Any attribute which is NOT SET, is by default valuated to 0 " << endl;

	// -------------------------------------------------------------------------------------
	// 3- Attribute Valuation of a feature by Inheritance(Valuation by Reference)
	// -------------------------------------------------------------------------------------
	cout << "   ============================================================================ " << endl;
	cout << "   Attribute Value of a Feature inherited from that of its Feature Reference "    << endl;
	cout << "   ============================================================================ " << endl;
	// 3-1- Instantiate a second CAAFmExtPoint2D feature (referred as Point2D2) with Point2D1 as reference
	cout << "   Instantiate Point2D2 from Point2D1" << endl;
	CATFmAttributeValue attrValue;
	rc = FeatFacadeOnPoint2D1.InstantiateIn(MyContainerFacade,attrValue);
	if (FAILED(rc)) return 1; 
	CATFmFeatureFacade FeatFacadeOnPoint2D2(MyCredential,attrValue);

	cout << "   -------------------------------------------------" << endl;
	cout << "   Retrieve the Point2D2 X Attribute Info and Value" << endl;
	// 3-2- Confirm the Point2D2 X attribute is inherited
	rc = ConfirmAttributeInfo(FeatFacadeOnPoint2D2,XAttrKey,CATFmInherited);
	if (FAILED(rc)) return 1;

	cout << "   -------------------------------------------------------------" << endl;
	cout << "   The Point2D2 X attribute is INHERITED" << endl;

	// 3-3- Confirm the Point2D2 X attribute is valuated to -1, the value inherited from its reference (and ultimately from the OSM file)
	rc = FeatFacadeOnPoint2D2.GetValue(XAttrKey,AttrValueSet);
	if (rc != S_OK) return 1; 

	AttrValueSet.GetDouble(val);
	if ( val != -1) return 1; 

	cout << "   The Point2D2 X attribute is set to -1, the value inherited from Point2D1, its feature reference " << endl;
	cout << "   -------------------------------------------------------------------------------------------------" << endl;

	cout << "   Retrieve the Point2D2 Y Attribute Info and Value" << endl;
	// 3-4- Confirm the Point2D2 Y attribute is inherited 
	rc = ConfirmAttributeInfo(FeatFacadeOnPoint2D2,YAttrKey,CATFmInherited);
	if (FAILED(rc))  return 1; 

	cout << "   The Point2D2 Y attribute is INHERITED" << endl;

	// 3-5- Confirm the Point2D2 Y attribute is valuated to 0, the value inherited from its reference
	rc = FeatFacadeOnPoint2D2.GetValue(YAttrKey,AttrValueSet);
	if (rc != S_FALSE) return 1; 

	AttrValueSet.GetDouble(val);
	if ( val != 0) return 1; 

	cout << "   The Point2D2 Y attribute value is 0. An attribute not yet set, is by default valuated to 0" << endl;
	cout << "   -------------------------------------------------------------------------------------------" << endl;

	// 3-6- Set the Point2D1 "X" attribute value to 5
	cout << "   Set the Point2D1 X attribute value to 5" << endl;
	AttrValueSet.SetDouble(5);
	rc = FeatFacadeOnPoint2D1.SetValue(XAttrKey,AttrValueSet);
	if (FAILED(rc)) return 1;
	cout << "   The Point2D1 X attribute is set to 5" << endl;

	// 3-7- Retrieve the Point2D2 "X" attribute value. The value is 5 inherited from the feature reference
	cout << "   Retrieve the Point2D2 X attribute value." << endl;
	rc = FeatFacadeOnPoint2D2.GetValue(XAttrKey,AttrValueSet);
	if (rc != S_OK) return 1; 
	AttrValueSet.GetDouble(val);
	if ( val != 5) return 1; 
	cout << "   Confirmed: The Point2D2 X attribute value is 5, that inherited from that of Point2D1" << endl;
	cout << "   -------------------------------------------------------------------------------------" << endl;

	// 3-8- Set the Point2D2 "X" attribute value to 7
	cout << "   Set the Point2D2 X attribute value to 7" << endl;
	AttrValueSet.SetDouble(7);
	rc = FeatFacadeOnPoint2D2.SetValue(XAttrKey,AttrValueSet);
	if (FAILED(rc)) return 1;

	cout << "   The Point2D2 X attribute is set to 7" << endl;
	cout << "   -------------------------------------" << endl;

	// 3-9- Set the Point2D1 "X" attribute value to 8
	cout << "   Set the Point2D1 X attribute value to 8" << endl;
	AttrValueSet.SetDouble(8);
	rc = FeatFacadeOnPoint2D1.SetValue(XAttrKey,AttrValueSet);
	if (FAILED(rc))return 1;

	cout << "   The Point2D1 X attribute value is set to 8" << endl;
	cout << "   --------------------------------------------" << endl;

	// 3-10- Retrieve the Point2D2 "X" attribute value. Value still 7. Not overridden by 8 (value of Reference)
	cout << "   Retrieve the Point2D2 X attribute value." << endl;
	rc = FeatFacadeOnPoint2D2.GetValue(XAttrKey,AttrValueSet);
	if (rc != S_OK) return 1; 
	AttrValueSet.GetDouble(val);
	if ( val != 7) return 1; 

	cout << "   Confirmed: The Point2D2 X attribute value is still 7, not overridden by that of its feature reference " << endl;

	// --------------------------------------
	// 4- Unset a Feature Attribute Value
	// --------------------------------------
	cout << "   ===================================== " << endl;
	cout << "   Unset a Feature Attribute Value "    << endl;
	cout << "   ===================================== " << endl;
	//	4-1- Unset the Point2D1 "X" attribute value
	cout << "   Unset the Point2D1 X attribute" << endl;
	rc = FeatFacadeOnPoint2D1.UnsetValue(XAttrKey);
	if (FAILED(rc))return 1;

	// 4-2- Confirm the Point2D1 X attribute is immediate
	cout << "   Retrieve the Point2D1 X Attribute Info and Value" << endl;
	rc = ConfirmAttributeInfo(FeatFacadeOnPoint2D1,XAttrKey,CATFmImmediate);
	if (FAILED(rc)) return 1; 
	cout << "   The Point2D1 X attribute is IMMEDIATE" << endl;

	// 4-3- Confirm the Point2D1 X attribute is valuated to 0 (unset value)
	rc = FeatFacadeOnPoint2D1.GetValue(XAttrKey,AttrValueSet);
	if (rc != S_FALSE) return 1; 
	AttrValueSet.GetDouble(val);
	if ( val != 0) return 1; 

	cout << "   The CATFmFeatureFacade::GetValue call on Point2D1 returns S_FALSE, since call is on an UNSET attribute" << endl;
	cout << "   The Point2D1 X attribute value is 0. Any UNSET attribute, is by default valuated to 0" << endl;

	// -----------------------------------------------------------------
	// 5- Set a Feature Attribute Value to 0 distinct from UNSET
	// -----------------------------------------------------------------
	cout << "   ============================================================= " << endl;
	cout << "   Set a Feature Attribute Value to 0 distinct from UNSET "    << endl;
	cout << "   ============================================================= " << endl;
	// 5-1- Set the Point2D1 "Y" attribute value to 0
	cout << "   Set the Point2D1 Y attribute value to 0" << endl;
	AttrValueSet.SetDouble(0);
	rc = FeatFacadeOnPoint2D1.SetValue(YAttrKey,AttrValueSet);
	if (FAILED(rc))return 1;

	cout << "   The Point2D1 Y attribute value is set to 0" << endl;
	cout << "   --------------------------------------------" << endl;

	// 5-2- Confirm the Point2D1 Y attribute is immediate
	cout << "   Retrieve the Point2D1 Y Attribute Info and Value" << endl;
	rc = ConfirmAttributeInfo(FeatFacadeOnPoint2D1,YAttrKey,CATFmImmediate);
	if (FAILED(rc))return 1; 

	cout << "   The Point2D1 Y attribute is IMMEDIATE" << endl;

	// 5-3- Confirm the Point2D1 Y attribute is valuated to 0, and the return of the CATFmFeatureFacade::GetValue()
	//      call is S_OK (Not S_FALSE, making it thus distinct from the UNSET case)
	rc = FeatFacadeOnPoint2D1.GetValue(YAttrKey,AttrValueSet);
	if (rc != S_OK) return 1; 
	AttrValueSet.GetDouble(val);
	if ( val != 0) return 1; 

	cout << "   The CATFmFeatureFacade::GetValue call on Point2D1 returns S_OK, distinct from the UNSET case, which returns S_FALSE " << endl;
	cout << "   The Point2D1 Y attribute value is 0" << endl;

	// ----------------------------------------------------
	// 6- Remove the Locally Defined Attribute Value
	// ----------------------------------------------------
	cout << "   ========================================= " << endl;
	cout << "   Remove a Locally Defined Attribute Value "    << endl;
	cout << "   ========================================= " << endl;
	// 6-1- Remove local Value assigned to the Point2D2 "X" attribute
	cout << "   Remove the local Value for the Point2D2 X attribute" << endl;
	rc = FeatFacadeOnPoint2D2.RestoreInheritance(XAttrKey);
	if (FAILED(rc)) return 1; 

	cout << "   Success in removing the locally defined value for the Point2D2 X attribute" << endl;

	// 6-2- Confirm the Point2D2 X attribute is INHERITED
	cout << "   Retrieve the Point2D2 X Attribute Info and Value" << endl;
	rc = ConfirmAttributeInfo(FeatFacadeOnPoint2D2,XAttrKey,CATFmInherited);
	if (FAILED(rc)) return 1; 
	cout << "   The Point2D2 X attribute is INHERITED" << endl;

	// 6-3- Confirm the Point2D2 X attribute is valuated to 0
	rc = FeatFacadeOnPoint2D2.GetValue(XAttrKey,AttrValueSet);
	if (rc != S_FALSE) return 1; 
	AttrValueSet.GetDouble(val);
	if ( val != 0) return 1; 

	cout << "   The Point2D2 X attribute value is 0. Its the value inherited from the Point2D1 Feature reference (Unset)" << endl;

	//	6-4- Remove Locally Defined Value assigned to the Point2D1 "X" attribute
	cout << "   Remove the Locally Defined Value for the Point2D1 X attribute" << endl;
	rc = FeatFacadeOnPoint2D1.RestoreInheritance(XAttrKey);
	if (FAILED(rc)) return 1;

	cout << "   Success in removing the locally defined value for the X attribute of Point2D1" << endl;

	cout << "   Retrieve the Point2D2 X Attribute Info and Value" << endl;

	// 	6-5- Retrieve the Point2D2 "X" attribute value. It is -1, the default value set in the OSM file
	rc = FeatFacadeOnPoint2D2.GetValue(XAttrKey,AttrValueSet);
	if (rc != S_OK) return 1; 
	AttrValueSet.GetDouble(val);
	if ( val != -1) return 1; 

	cout << "   The Point2D2 X attribute value is -1. Its the default value of the attribute defined in the OSM file" << endl;
	cout << "   ------------------------------------------------------------------------------------------------------" << endl;

#ifdef CATIAR214
	//-------------------------------------------------------------------------------------
	// 12- Save the session
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
	//13- Closes the session
	//--------------------------------------------------------------------------------------
	rc = ::CAAAdpCloseSession();
	if (FAILED(rc) ) return 1;

	cout <<"   PLM session closed" << endl;
	cout << endl << "The CAAV5V6FmExtSimpleAttrTypeManagement main program ends in V6 env...."<< endl << endl;

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

//-----------------------------------------------------------------------------------------
// sub function checking the  attribute info and Value of a feature attribute
//-----------------------------------------------------------------------------------------
HRESULT ConfirmAttributeInfo(CATFmFeatureFacade & iFeatFacadeOnFeat,
							 CATFmAttributeName & iAttrKey,
							 CATFmAttributeValuationMode iValuationMode )

{
	HRESULT rc = E_FAIL;

	CATFmAttributeValuationInfo AttrValuationInfo;
	rc = iFeatFacadeOnFeat.GetAttributeValuationInfo(iAttrKey,AttrValuationInfo);

	if (SUCCEEDED(rc))
	{
		// Confirmed checks for our attributes
		if ((CATFmKind_double != AttrValuationInfo.m_Type) || (TRUE == AttrValuationInfo.m_IsList) ) rc = E_FAIL;

		// Checks specific to each case
		if ( AttrValuationInfo.m_ValuationMode != iValuationMode ) rc = E_FAIL;

	}

	return rc;
}
