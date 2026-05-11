// COPYRIGHT DASSAULT SYSTEMES 2010

//=============================================================================
// Abstract of Use Case "CAAV5V6FmExtUnderstandingSynchro":
// -------------------------------------------
//
// This sample illustrates synchronization of a feature attribute.
// A feature is instantiated from its reference. On instantiation a feature does inherit its
// feature attribute values from its reference. But beyond that any modification in the reference 
// attribute values are reflected on the feature, only on synchronization.
// The UC deals primarily with a component type and a component list type attribute.
//   
// The current UC refers to the following list of the StartUps defined in the catalog 
// CAAFmExtCatalogForUnderstandingSynchro.CATfct, which thus is its prerequisite
// This catalog is provided in the CAAV5V6FeatureModelerExt.edu/CNext/resources/graphic folder,
// which on mkrtv is copied to the Workspace run time view
//
//		StartUp									Attribute
//		-------									---------
//
//		CAAFmExt_A_withCompAttr                 Attr1 (component)
//                                              Attr2 (component)
//                                              Attr3 (component)
//                                              Attr4 (component)
//      CAAFmExt_B
//      CAAFmExt_C
//      CAAFmExt_D
//      CAAFmExt_E
//      CAAFmExt_F
//      CAAFmExt_G
//      CAAFmExt_H
//      CAAFmExt_I
//      CAAFmExt_J
//      CAAFmExt_U
//      CAAFmExt_V
//      CAAFmExt_W
//      CAAFmExt_X
//      CAAFmExt_A_withListCompAttr             Attr1 (component, list)
//                                              Attr2 (component, list)
//                                              Attr3 (component, list)

//      CAAFmExt_Arec                           Attr1 (component)
//      CAAFmExt_Brec                           Attr2 (component, list)


//=============================================================================
//  Steps :
//
// 1- Scenario 1 --> Illustrating Synchronization of feature attribute of type "Component" in a Ref-Inst model
//      1-1- Component aggregated under Feature distinct from that under its Reference
//              1-1-1- Feat A Instantiated
//              1-1-2- Feat B instantiated as an aggregation under Feat A
//              1-1-3- FeatA instantiated to FeatA'
//              1-1-4- Confirm Feat A' aggregates Feat B', an instance distinct from Feat B
//      1-2- Illustrating Synchronization of a feature attribute of type component
//              1-2-1- Feat C Instantiated as an aggregation under Feat A
//              1-2-2- Feat D Instantiated as an aggregation under Feat A
//              1-2-3- Feat E Instantiated as an aggregation under Feat A
//              1-2-4- Synchronize Feat A' Attribute Attr2
//              1-2-5- Retrieve Feat C'
//              1-2-6- Synchronize Feat A' Attribute Attr3
//              1-2-7- Retrieve Feat D'
//              1-2-8- Synchronize Feat A' Attribute Attr4
//              1-2-9- Retrieve Feat E'
//      1-3- Impact of Synchronization on Feature Delete and Replace at Reference and Instance end
//              1-3-1- Feat B under Feat A deleted
//              1-3-2- Feat U replaces Feat D under Feat A
//              1-3-3- Replace Feat D with Feat U under Feat A
//              1-3-4- Feat C' under Feat A' deleted
//              1-3-5- Feat V replaces Feat E' under Feat A'
//              1-3-6- Synchronize attribute Attr1 of Feat A'
//              1-3-7- Feat A' no longer aggregates Feat B'
//              1-3-8- Synchronize attribute Attr2 of Feat A'
//              1-3-9- Feat A' now aggregates an instance of Feat C (Feat C'')
//              1-3-10- Synchronize attribute Attr3 of Feat A
//              1-3-11- Feat A' now aggregates an instance of Feat U (Feat U') post synchro
//              1-3-12- Synchronize attribute Attr4 of Feat A'
//              1-3-13- Feat A' now aggregates an instance of Feat E (Feat E'') post synchro
// 2- Scenario 2 --> Illustrating Synchronization of feature attribute of type "Component List"
//      2-1- Feat A with List Attributes Instantiated
//      2-2- Feat B instantiated as an aggregation under Feat A
//      2-3- Feat C instantiated as an aggregation under Feat A
//      2-4- Feat D instantiated as an aggregation under Feat A
//      2-5- Feat E instantiated as an aggregation under Feat A
//      2-6- Feat F instantiated as an aggregation under Feat A
//      2-7- Feat G instantiated as an aggregation under Feat A
//      2-8- Feat I instantiated as an aggregation under Feat A
//      2-9- Feat J instantiated as an aggregation under Feat A
//      2-10- FeatA instantiated to FeatA'
//      2-11- Feature Model (Reference and Instance) modified as below, an input for the synchronization process
//              2-11-1- Feat U aggregated under Feat A, by valuating its Attr1 attribute
//              2-11-2- Feat V aggregated under Feat A, by valuating its Attr3 attribute
//              2-11-3- Feat W aggregated under Feat A', by valuating its Attr2 attribute
//              2-11-4- Feat X aggregated under Feat A', by valuating its Attr3 attribute
//      2-12- Synchronize Feat A' 
//      2-13- Post-Synchronization Checks
//              2-13-1- Feat A' attribute Attr1 of type component list is of size 3
//              2-13-2- Feat A' attribute Attr1 value at index 3 is Feat U'
//              2-13-3- Feat A' attribute Attr2 of type component list is of size 3
//              2-13-4- Feat A' attribute Attr2 value at index 3 is Feat W
//              2-13-5- Feat A' attribute Attr3 of type component list is of size 4
//              2-13-6- Feat A' attribute Attr3 value at index 3 is Feat V'
//              2-13-7- Feat A' attribute Attr4 of type component list is of size 1. It has only Feat I'
//              2-13-8- Confirm Feat A' attribute Attr4 value at index 1 is Feat I
// 3- Scenario 3 --> Illustrating Synchronization of feature attribute is not recursive
//       3-1- Instantiation is Recursive as illustrated by the model below
//              3-1-1- Instantiate the CAAFmExt_Arec feature
//              3-1-2- Aggregate feature CAAFmExt_Brec under feature CAAFmExt_Arec
//              3-1-3- Aggregate feature CAAFmExt_D and CAAFmExt_E under feature CAAFmExt_Brec.1
//              3-1-4- Instantiate another feature from the existing CAAFmExt_Arec feature
//              3-1-5- Retrieve Feat B' under Feat A'
//              3-1-6- Confirm count of components aggregated under Feat B' is two 
//              3-1-2- Confirm the first of the components aggregated is an instance whose reference is Feat D (sample check)
//      3-2- Confirm Synchronization is not Recursive. It is illustrated by the model depicted below
//              3-2-1- Delete Feat D under Feat B
//              3-2-2- Call Synchronization of attribute Attr1 of Feat A'
//              3-2-3- Confirm Feat D' under Feat B' still exists
//              3-2-4- Call synchronization on attribute Attr2 of Feat B'
//              3-2-5- Confirm count of features aggregated under Feat B' is one
//              3-2-6- Confirm the feature aggregated under Feat B' is an instance of Feat E
// 9- Saves the session
// 10- Closes the session
//
//=============================================================================
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAV5V6FmExtUnderstandingSynchro DocumentStorageName" 
//  where the "DocumentStorageName" is the entire pathname, name and .CATPart extension
//    under which the new document is to be stored. 
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

// FeatureModelerExt  Framework
#include "CATFmFeatureFacade.h"
#include "CATFmContainerFacade.h"
#include "CATFmStartUpFacade.h"
#include "CATFmCredentials.h"
#include "CATFmAttributeName.h"
#include "CATFmAttributeValue.h"
#include "CATFmFeatureModelerID.h"
#include "CATFmAttributeValuationInfo.h"

#include "CATIAV5Level.h"

// Other
#include <iostream.h>

//-------------------------------------------------------------------------
//	Include guards when the Framework is in V6 Environment
//-------------------------------------------------------------------------
#ifdef CATIAR214

//System Framework
#include "CATSysBoolean.h"

// ObjectModelerBase Framework
#include "CATOmbLifeCycleRootsBag.h"

//local Framework
#include "CAAV5V6FmExtCreateRepRef.h"     // to create the Rep ref

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

//=========================================================================================
HRESULT Synchronize(CATFmFeatureFacade & iFeatFacade);

CATFmAttributeName Attr1Name("Attr1");
CATFmAttributeName Attr2Name("Attr2");
CATFmAttributeName Attr3Name("Attr3");
CATFmAttributeName Attr4Name("Attr4");

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
	if (NULL != pDoc) cout << "New document created OK" << endl << flush;
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
	rc = MyCredential.RegisterAsCatalogOwner("CAAFmExtCatalogForUnderstandingSynchro","CAAFmExtUnderstandingSynchroClientId");
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
		cout << "Usage: CAAV5V6FmExtUnderstandingSynchro <Repository> <Server> <User> <Password> <SecurityCtx> <Environment> " ;
		cout <<endl;
		return 1;
	}
	cout << "The CAAV5V6FmExtUnderstandingSynchro main program begins in V6 env...."<< endl << endl;

	//------------------------------------------------------------------
	// 2 - Initializes the PLM session 
	//------------------------------------------------------------------
	HRESULT rc = ::CAAAdpCreateSession(iArgv[1], iArgv[2], iArgv[3], iArgv[4],iArgv[5]);
	if (FAILED(rc))	return 1;

	cout << "   PLM session initialized with the following connection parameters" << endl;
	cout << "      Repository=" << iArgv[1] << endl;
	cout << "      Server="     << iArgv[2] << endl;
	cout << "      UserID="     << iArgv[3] << endl;
	cout << "      UserPasswd=" << iArgv[4] << endl;
	cout << "      SecurityCtx=" << iArgv[5] << endl;

	//---------------------------------------------------------------------------
	// 3- Build Credentials to access the catalog "CAAV5V6FmExtUnderstandingSynchro"
	//---------------------------------------------------------------------------
	CATFmCredentials MyCredential;
	rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
	rc = MyCredential.RegisterAsCatalogOwner("CAAFmExtCatalogForUnderstandingSynchro","CAAFmExtUnderstandingSynchroClientId");
	if (FAILED(rc)) return 1;
	cout << "   Success in creating the credentials V5-V6 compatible code" << endl;

	//------------------------------------------------------------------
	// 4- Creates a Product Representation Reference
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
	// ----------------------------------------------------------------------------------------------------------
	// 1- Scenario 1 --> Illustrating Synchronization of feature attribute of type "Component" in a Ref-Inst model
	// ----------------------------------------------------------------------------------------------------------
	cout << "   ***** Scenario 1 --> Illustrating Synchronization of feature attribute of type Component in a Ref-Inst model" << endl;
	// ----------------------------------------------------------------------------------
	// 1-1- Component aggregated under Feature distinct from that under its Reference
	// ----------------------------------------------------------------------------------
	// Feat A aggregates Feat B, as depicted in the model below
	// Feat A is instantiated resulting in Feat A'
	// Feat A' aggregates Feat B', a feature distinct from Feat B

	/*  Feat A      ----Instantiated to --->  Feat A'
	*                                        *
	|___Feat B (Attr1)                       |___Feat B' (Attr1) 
	*/
	cout << "   *** Component aggregated under Feature distinct from that under its Reference" << endl; 
	// 1-1-1- Feat A Instantiated
	CATUnicodeString AwithCompAttrStartUpType("`CAAFmExt_A_withCompAttr`@`CAAFmExtCatalogForUnderstandingSynchro.CATfct`");
	CATFmStartUpFacade FeatAStartUpFacade(MyCredential, AwithCompAttrStartUpType);
	CATFmFeatureFacade oFeatFacadeOnFeatA (MyCredential);
	rc = FeatAStartUpFacade.InstantiateIn(MyContainerFacade,oFeatFacadeOnFeatA);
	if (FAILED(rc))	return 1;
	cout << "   Feat A instantiated" << endl;

	// 1-1-2- Feat B instantiated as an aggregation under Feat A
	CATUnicodeString BStartUpType("`CAAFmExt_B`@`CAAFmExtCatalogForUnderstandingSynchro.CATfct`");
	CATFmStartUpFacade FeatBStartUpFacade(MyCredential, BStartUpType);
	CATFmFeatureFacade oFeatFacadeOnFeatB (MyCredential);
	rc = FeatBStartUpFacade.InstantiateUnder(MyContainerFacade,oFeatFacadeOnFeatA,Attr1Name,oFeatFacadeOnFeatB);
	if (FAILED(rc))	return 1;
	cout << "   Feat B instantiated as an aggregation under Feat A" << endl;

	// 1-1-3- FeatA instantiated to FeatA'
	CATFmAttributeValue attrValue;
	rc = oFeatFacadeOnFeatA.InstantiateIn(MyContainerFacade,attrValue);
	if (FAILED(rc))	return 1;
	cout << "   Feat A' instantiated from Feat A" << endl;
	CATFmFeatureFacade oFeatFacadeOnFeatAA (MyCredential,attrValue);

	// 1-1-4- Confirm Feat A' aggregates Feat B', an instance distinct from Feat B
	// Retrieve Feat B', a feature aggregated by Attr1 under Feat A'
	CATFmAttributeValue AttrVal;
	rc = oFeatFacadeOnFeatAA.GetValue(Attr1Name,AttrVal);
	if (FAILED(rc))	return 1;

	CATFmFeatureFacade oFeatFacadeOnBB(MyCredential);
	rc = AttrVal.GetFeature(oFeatFacadeOnBB);
	if (FAILED(rc))	return 1;
	cout << "   Retrieved Feat B', a feature aggregated by Attr1 under Feat A'" << endl;

	CATBaseUnknown_var spCBUOnB  = oFeatFacadeOnFeatB.GetFeature();
	CATBaseUnknown_var spCBUOnBB = oFeatFacadeOnBB.GetFeature();

	if (spCBUOnBB->IsEqual(spCBUOnB)) return 1;
	cout << "   Confirmed: Feat B' distinct from Feat B" << endl;

	// ----------------------------------------------------------------------------------
	// 1-2- Illustrating Synchronization of a feature attribute of type component
	// ----------------------------------------------------------------------------------
	cout << "   *** Illustrating Synchronization of a feature attribute of type component" << endl;
	// Feat A instantiated. Feat B,C,D,E instantiated as aggregations under Feat A
	// Feat A
	//    *
	//    |___Feat B (Attr1)
	//    |___Feat C (Attr2)
	//    |___Feat D (Attr3)
	//    |___Feat E (Attr4)

	// On synchronization of all attributes of Feat A' the resulting feature model is as depicted below
	// Feat A            -------------- Instantiated to ----->    Feat A' (On Synchronization)
	//    *                                                        *
	//    |___Feat B (Attr1)                                       |___Feat B' (Attr1)
	//    |___Feat C (Attr2)                                       |___Feat C' (Attr2)
	//    |___Feat D (Attr3)                                       |___Feat D' (Attr3)
	//    |___Feat E (Attr4)                                       |___Feat E' (Attr4)

	// 1-2-1- Feat C Instantiated as an aggregation under Feat A
	CATUnicodeString CStartUpType("`CAAFmExt_C`@`CAAFmExtCatalogForUnderstandingSynchro.CATfct`");
	CATFmStartUpFacade FeatCStartUpFacade(MyCredential, CStartUpType);
	CATFmFeatureFacade oFeatFacadeOnFeatC (MyCredential);
	rc = FeatCStartUpFacade.InstantiateUnder(MyContainerFacade,oFeatFacadeOnFeatA,Attr2Name,oFeatFacadeOnFeatC);
	if (FAILED(rc))	return 1;
	cout << "   Feat C instantiated as an aggregation under Feat A" << endl;

	// 1-2-2- Feat D Instantiated as an aggregation under Feat A
	CATUnicodeString DStartUpType("`CAAFmExt_D`@`CAAFmExtCatalogForUnderstandingSynchro.CATfct`");
	CATFmStartUpFacade FeatDStartUpFacade(MyCredential, DStartUpType);
	CATFmFeatureFacade oFeatFacadeOnFeatD (MyCredential);
	rc = FeatDStartUpFacade.InstantiateUnder(MyContainerFacade,oFeatFacadeOnFeatA,Attr3Name,oFeatFacadeOnFeatD);
	if (FAILED(rc))	return 1;
	cout << "   Feat D instantiated as an aggregation under Feat A" << endl;

	// 1-2-3- Feat E Instantiated as an aggregation under Feat A
	CATUnicodeString EStartUpType("`CAAFmExt_E`@`CAAFmExtCatalogForUnderstandingSynchro.CATfct`");
	CATFmStartUpFacade FeatEStartUpFacade(MyCredential, EStartUpType);
	CATFmFeatureFacade oFeatFacadeOnFeatE (MyCredential);
	rc = FeatEStartUpFacade.InstantiateUnder(MyContainerFacade,oFeatFacadeOnFeatA,Attr4Name,oFeatFacadeOnFeatE);
	if (FAILED(rc))	return 1;
	cout << "   Feat E instantiated as an aggregation under Feat A" << endl;

	// 1-2-4- Synchronize Feat A' Attribute Attr2
	rc = oFeatFacadeOnFeatAA.Synchronize(Attr2Name);
	if (FAILED(rc))	return 1;
	cout << "   Sychronized Feat A' Attribute Attr2" << endl;

	// 1-2-5- Retrieve Feat C'
	rc = oFeatFacadeOnFeatAA.GetValue(Attr2Name,AttrVal);
	if (FAILED(rc))	return 1;

	CATFmFeatureFacade oFeatFacadeOnCC(MyCredential);
	rc = AttrVal.GetFeature(oFeatFacadeOnCC);
	if (FAILED(rc))	return 1;
	cout << "   Retrieved Feat C' aggregated under Feat A'" << endl;

	// 1-2-6- Synchronize Feat A' Attribute Attr3
	rc = oFeatFacadeOnFeatAA.Synchronize(Attr3Name);
	if (FAILED(rc))	return 1;
	cout << "   Sychronized Feat A' Attribute Attr3" << endl;

	// 1-2-7- Retrieve Feat D'
	CATFmFeatureFacade oFeatFacadeOnDD(MyCredential);
	rc = AttrVal.GetFeature(oFeatFacadeOnDD);
	if (FAILED(rc))	return 1;
	cout << "   Retrieved Feat D' aggregated under Feat A'" << endl;

	// 1-2-8- Synchronize Feat A' Attribute Attr4
	rc = oFeatFacadeOnFeatAA.Synchronize(Attr4Name);
	if (FAILED(rc))	return 1;
	cout << "   Sychronized Feat A' Attribute Attr4" << endl;

	// 1-2-9- Retrieve Feat E'
	CATFmFeatureFacade oFeatFacadeOnEE(MyCredential);
	rc = AttrVal.GetFeature(oFeatFacadeOnEE);
	if (FAILED(rc))	return 1;
	cout << "   Retrieved Feat E' aggregated under Feat A'" << endl;

	// -------------------------------------------------------------------------------------------
	// 1-3- Impact of Synchronization on Feature Delete and Replace at Reference and Instance end
	// -------------------------------------------------------------------------------------------
	cout << "   *** Impact of Synchronization on feature Delete and Replace at Reference and Instance end" << endl;
	// Feature Model (Reference and Instance), an input for synchronization is depicted below
	// Feat A            -------------- Instantiated to ----->      Feat A'
	//    *                                                          *
	//    |___       (Attr1) *Deleted                                |___Feat B' (Attr1)
	//    |___Feat C (Attr2)                                         |___        (Attr2)  *Deleted
	//    |___Feat U (Attr3) *Replaced                               |___Feat D' (Attr3)
	//    |___Feat E (Attr4)                                         |___Feat V  (Attr4)  *Replaced


	// Feature Model (Reference and Instance) post-Synchronization results in
	// Feat A            -------------- Instantiated to ----->      Feat A'
	//    *                                                           *
	//    |___       (Attr1) *Deleted                                 |___         (Attr1)
	//    |___Feat C (Attr2)                                          |___Feat C'' (Attr2)
	//    |___Feat U (Attr3) *Replaced                                |___Feat U'  (Attr3)
	//    |___Feat E (Attr4)                                          |___Feat E'' (Attr4)  

	// 1-3-1- Feat B under Feat A deleted
	rc = oFeatFacadeOnFeatB.DeleteSelf();
	if (FAILED(rc))	return 1;
	cout << "   Feat B under Feat A deleted" << endl;

	// 1-3-2- Feat U replaces Feat D under Feat A
	// Feat U Instantiated
	CATUnicodeString UStartUpType("`CAAFmExt_U`@`CAAFmExtCatalogForUnderstandingSynchro.CATfct`");
	CATFmStartUpFacade FeatUStartUpFacade(MyCredential, UStartUpType);
	CATFmFeatureFacade oFeatFacadeOnFeatU (MyCredential);
	rc = FeatUStartUpFacade.InstantiateIn(MyContainerFacade,oFeatFacadeOnFeatU);
	if (FAILED(rc))	return 1;
	cout << "   Feat U instantiated" << endl;

	// 1-3-3- Replace Feat D with Feat U under Feat A
	AttrVal.SetFeature(oFeatFacadeOnFeatU);
	rc = oFeatFacadeOnFeatA.SetValue(Attr3Name,AttrVal);
	if (FAILED(rc))	return 1;
	cout << "   Feat U replaces Feat D under Feat A" << endl;

	// 1-3-4- Feat C' under Feat A' deleted
	CATFmFeatureFacade FeatFacadeOnNullFeat(MyCredential,NULL);
	AttrVal.SetFeature(FeatFacadeOnNullFeat);
	rc = oFeatFacadeOnFeatAA.SetValue(Attr2Name,AttrVal); 
	if (FAILED(rc))	return 1;
	cout << "   Feat C' under Feat A' deleted" << endl;

	// 1-3-5- Feat V replaces Feat E' under Feat A'
	// Feat V Instantiated
	CATUnicodeString VStartUpType("`CAAFmExt_V`@`CAAFmExtCatalogForUnderstandingSynchro.CATfct`");
	CATFmStartUpFacade FeatVStartUpFacade(MyCredential, VStartUpType);
	CATFmFeatureFacade oFeatFacadeOnFeatV (MyCredential);
	rc = FeatVStartUpFacade.InstantiateIn(MyContainerFacade,oFeatFacadeOnFeatV);
	if (FAILED(rc))	return 1;
	cout << "   Feat V instantiated" << endl;

	// Replace Feat E' with Feat V under Feat A'
	AttrVal.SetFeature(oFeatFacadeOnFeatV);
	rc = oFeatFacadeOnFeatAA.SetValue(Attr4Name,AttrVal);
	if (FAILED(rc))	return 1;
	cout << "   Feat V replaces Feat E' under Feat A'" << endl;

	// Synchronizing Feat A' with Feat A, results in Feat A' now aggregating Feat C'',U',E''
	cout << "   Synchronizing all attributes of Feat A'" << endl;

	// 1-3-6- Synchronize attribute Attr1 of Feat A'
	rc = oFeatFacadeOnFeatAA.Synchronize(Attr1Name);
	if (FAILED(rc))	return 1;
	cout << "   Synchronized Attr1 of Feat A'" << endl;

	// 1-3-7- Feat A' no longer aggregates Feat B'
	rc = oFeatFacadeOnFeatAA.GetValue(Attr1Name,AttrVal);
	if (FAILED(rc))	return 1;

	CATFmFeatureFacade oFeatFacade(MyCredential);
	rc = AttrVal.GetFeature(oFeatFacade);
	if (FAILED(rc))	return 1;

	// Feat B' no longer exists
	if (TRUE == oFeatFacade.IsValid()) return 1;
	if (TRUE == oFeatFacadeOnBB.IsValid()) return 1;
	cout << "   Feat A' no longer aggregates Feat B' which stands destroyed" << endl;

	// 1-3-8- Synchronize attribute Attr2 of Feat A'
	rc = oFeatFacadeOnFeatAA.Synchronize(Attr2Name);
	if (FAILED(rc))	return 1;
	cout << "   Synchronized Attr2 of Feat A'" << endl;

	// 1-3-9- Feat A' now aggregates an instance of Feat C (Feat C'')
	rc = oFeatFacadeOnFeatAA.GetValue(Attr2Name,AttrVal);
	if (FAILED(rc))	return 1;

	oFeatFacade.Clear();
	rc = AttrVal.GetFeature(oFeatFacade);
	if (FAILED(rc))	return 1;

	// Confirm if the reference of the feature retrieved is Feat C
	rc =  oFeatFacade.GetReference(AttrVal);
	if (FAILED(rc))	return 1;

	oFeatFacade.Clear();
	rc = AttrVal.GetFeature(oFeatFacade);
	if (FAILED(rc))	return 1;

	CATBaseUnknown_var spCBUOnRef   = oFeatFacade.GetFeature();
	CATBaseUnknown_var spCBUOnFeatC = oFeatFacadeOnFeatC.GetFeature();
	if (!(spCBUOnRef->IsEqual((CATBaseUnknown*)spCBUOnFeatC))) return 1;
	// Feat C' no longer exists
	if (TRUE == oFeatFacadeOnCC.IsValid()) return 1;
	cout << "   Feat A' now aggregates a new instance of Feat C (Feat C'')" << endl;

	// 1-3-10- Synchronize attribute Attr3 of Feat A
	rc = oFeatFacadeOnFeatAA.Synchronize(Attr3Name);
	if (FAILED(rc))	return 1;
	cout << "   Synchronized Attr3 of Feat A'" << endl;

	// 1-3-11- Feat A' now aggregates an instance of Feat U (Feat U') post synchro
	rc = oFeatFacadeOnFeatAA.GetValue(Attr3Name,AttrVal);
	if (FAILED(rc))	return 1;

	oFeatFacade.Clear();
	rc = AttrVal.GetFeature(oFeatFacade);
	if (FAILED(rc))	return 1;

	// Confirm if the reference of the feature retrieved is Feat U
	rc =  oFeatFacade.GetReference(AttrVal);
	if (FAILED(rc))	return 1;

	oFeatFacade.Clear();
	rc = AttrVal.GetFeature(oFeatFacade);
	if (FAILED(rc))	return 1;

	CATBaseUnknown_var spCBUOnRef1   = oFeatFacade.GetFeature();
	CATBaseUnknown_var spCBUOnFeatU = oFeatFacadeOnFeatU.GetFeature();
	if (!(spCBUOnRef1->IsEqual((CATBaseUnknown*)spCBUOnFeatU))) return 1;
	cout << "   Feat A' aggregates a new instance of Feat U (Feat U')" << endl;

	// 1-3-12- Synchronize attribute Attr4 of Feat A'
	rc = oFeatFacadeOnFeatAA.Synchronize(Attr4Name);
	if (FAILED(rc))	return 1;
	cout << "   Sychronized Attr4 of Feat A'" << endl;

	// 1-3-13- Feat A' now aggregates an instance of Feat E (Feat E'') post synchro
	rc = oFeatFacadeOnFeatAA.GetValue(Attr4Name,AttrVal);
	if (FAILED(rc))	return 1;

	oFeatFacade.Clear();
	rc = AttrVal.GetFeature(oFeatFacade);
	if (FAILED(rc))	return 1;

	// Confirm if the reference of the feature retrieved is Feat E
	rc =  oFeatFacade.GetReference(AttrVal);
	if (FAILED(rc))	return 1;

	oFeatFacade.Clear();
	rc = AttrVal.GetFeature(oFeatFacade);
	if (FAILED(rc))	return 1;

	CATBaseUnknown_var spCBUOnRef2   = oFeatFacade.GetFeature();
	CATBaseUnknown_var spCBUOnFeatE = oFeatFacadeOnFeatE.GetFeature();
	if (!(spCBUOnRef2->IsEqual((CATBaseUnknown*)spCBUOnFeatE))) return 1;
	cout << "   Feat A' aggregates a new instance of Feat E (Feat E'') " << endl; 

	// Destroy Feat A, A' before proceeding
	rc = oFeatFacadeOnFeatA.DeleteSelf();
	if (FAILED(rc))	return 1;

	rc = oFeatFacadeOnFeatAA.DeleteSelf();
	if (FAILED(rc))	return 1;

	// ----------------------------------------------------------------------------------------------
	// 2- Scenario 2 --> Illustrating Synchronization of feature attribute of type "Component List"
	// ----------------------------------------------------------------------------------------------
	cout << "   ***** Scenario 2 ---> Illustrating Synchronization of feature attribute of type component list" << endl;
	// Feature Model (Reference and Instance) prior to synchronization is as depicted below
	//   Feat A            
	//    *                         
	//    |___Feat B, C (Attr1 list)
	//    |___Feat D, E (Attr2 list)
	//    |___Feat F, G (Attr3 list)
	//    |___Feat I, J (Attr4 list)

	// 2-1- Feat A with List Attributes Instantiated
	CATUnicodeString AWithListCompAttrStartUp("`CAAFmExt_A_withListCompAttr`@`CAAFmExtCatalogForUnderstandingSynchro.CATfct`");
	CATFmStartUpFacade FeatAWithListAttrStartUpFacade(MyCredential, AWithListCompAttrStartUp);

	CATFmFeatureFacade oFeatFacadeOnFeatAWithListAttr(MyCredential);
	rc = FeatAWithListAttrStartUpFacade.InstantiateIn(MyContainerFacade,oFeatFacadeOnFeatAWithListAttr);
	if (FAILED(rc))	return 1;
	cout << "   Feat A with list attributes instantiated" << endl;

	// 2-2- Feat B instantiated as an aggregation under Feat A
	oFeatFacadeOnFeatB.Clear();
	rc = FeatBStartUpFacade.InstantiateUnder(MyContainerFacade,oFeatFacadeOnFeatAWithListAttr,Attr1Name,oFeatFacadeOnFeatB);
	if (FAILED(rc))	return 1;
	cout << "   Feat B instantiated as an aggregation under Feat A" << endl;

	// 2-3- Feat C instantiated as an aggregation under Feat A
	oFeatFacadeOnFeatC.Clear();
	rc = FeatCStartUpFacade.InstantiateUnder(MyContainerFacade,oFeatFacadeOnFeatAWithListAttr,Attr1Name,oFeatFacadeOnFeatC);
	if (FAILED(rc))	return 1;
	cout << "   Feat C instantiated as an aggregation under Feat A" << endl;

	// 2-4- Feat D instantiated as an aggregation under Feat A
	oFeatFacadeOnFeatD.Clear();
	rc = FeatDStartUpFacade.InstantiateUnder(MyContainerFacade,oFeatFacadeOnFeatAWithListAttr,Attr2Name,oFeatFacadeOnFeatD);
	if (FAILED(rc))	return 1;
	cout << "   Feat D instantiated as an aggregation under Feat A" << endl;

	// 2-5- Feat E instantiated as an aggregation under Feat A
	oFeatFacadeOnFeatE.Clear();
	rc = FeatEStartUpFacade.InstantiateUnder(MyContainerFacade,oFeatFacadeOnFeatAWithListAttr,Attr2Name,oFeatFacadeOnFeatE);
	if (FAILED(rc))	return 1;
	cout << "   Feat E instantiated as an aggregation under Feat A" << endl;

	// 2-6- Feat F instantiated as an aggregation under Feat A
	CATUnicodeString FStartUpType("`CAAFmExt_F`@`CAAFmExtCatalogForUnderstandingSynchro.CATfct`");
    CATFmStartUpFacade FeatFStartUpFacade(MyCredential, FStartUpType);

	CATFmFeatureFacade oFeatFacadeOnFeatF(MyCredential);
	rc = FeatFStartUpFacade.InstantiateUnder(MyContainerFacade,oFeatFacadeOnFeatAWithListAttr,Attr3Name,oFeatFacadeOnFeatF);
	if (FAILED(rc))	return 1;
	cout << "   Feat F instantiated as an aggregation under Feat A" << endl;

	// 2-7- Feat G instantiated as an aggregation under Feat A
	CATUnicodeString GStartUpType("`CAAFmExt_G`@`CAAFmExtCatalogForUnderstandingSynchro.CATfct`");
    CATFmStartUpFacade FeatGStartUpFacade(MyCredential, GStartUpType);
	CATFmFeatureFacade oFeatFacadeOnFeatG(MyCredential);
	rc = FeatGStartUpFacade.InstantiateUnder(MyContainerFacade,oFeatFacadeOnFeatAWithListAttr,Attr3Name,oFeatFacadeOnFeatG);
	if (FAILED(rc))	return 1;
	cout << "   Feat G instantiated as an aggregation under Feat A" << endl;

	// 2-8- Feat I instantiated as an aggregation under Feat A
	CATUnicodeString IStartUpType("`CAAFmExt_I`@`CAAFmExtCatalogForUnderstandingSynchro.CATfct`");
    CATFmStartUpFacade FeatIStartUpFacade(MyCredential, IStartUpType);
	CATFmFeatureFacade oFeatFacadeOnFeatI(MyCredential);
	rc = FeatIStartUpFacade.InstantiateUnder(MyContainerFacade,oFeatFacadeOnFeatAWithListAttr,Attr4Name,oFeatFacadeOnFeatI);
	if (FAILED(rc))	return 1;
	cout << "   Feat I instantiated as an aggregation under Feat A" << endl;

	// 2-9- Feat J instantiated as an aggregation under Feat A
	CATUnicodeString JStartUpType("`CAAFmExt_J`@`CAAFmExtCatalogForUnderstandingSynchro.CATfct`");
    CATFmStartUpFacade FeatJStartUpFacade(MyCredential, JStartUpType);
	CATFmFeatureFacade oFeatFacadeOnFeatJ(MyCredential);
	rc = FeatJStartUpFacade.InstantiateUnder(MyContainerFacade,oFeatFacadeOnFeatAWithListAttr,Attr4Name,oFeatFacadeOnFeatJ);
	if (FAILED(rc))	return 1;
	cout << "   Feat J instantiated as an aggregation under Feat A" << endl;

	// 2-10- FeatA instantiated to FeatA'
	rc = oFeatFacadeOnFeatAWithListAttr.InstantiateIn(MyContainerFacade,attrValue);
	if (FAILED(rc))	return 1;
	cout << "   Feat A instantiated to Feat A'" << endl;
	CATFmFeatureFacade oFeatFacadeOnFeatAAWithListAttr(MyCredential,attrValue);

	// Feature Model (Reference and Instance) that results is as depicted below
	//   Feat A            -------------- Instantiated to ----->    Feat A'
	//    *                                                          *
	//    |___Feat B, C (Attr1 list)                                 |___Feat B', C' (Attr1 list)
	//    |___Feat D, E (Attr2 list)                                 |___Feat D', E' (Attr2 list)
	//    |___Feat F, G (Attr3 list)                                 |___Feat F', G' (Attr3 list)
	//    |___Feat I, J (Attr4 list)                                 |___Feat I', J' (Attr4 list)


	// 2-11- Feature Model (Reference and Instance) modified as below, an input for the synchronization process
	cout << "   *** Feature Model modified, an input for the synchronization process" << endl;
	//   Feat A            -------------- Instantiated to ----->    Feat A'
	//    *                                                          *
	//    |___Feat B, C, U (Attr1 list)                                 |___Feat B', C'    (Attr1 list)
	//    |___Feat D, E    (Attr2 list)                                 |___Feat D', E', W (Attr2 list)
	//    |___Feat F, G, V (Attr3 list)                                 |___Feat F', G', X (Attr3 list)
	//    |___Feat I       (Attr4 list)                                 |___Feat I', J'    (Attr4 list)

	// 2-11-1- Feat U aggregated under Feat A, by valuating its Attr1 attribute
	oFeatFacadeOnFeatU.Clear();
	rc = FeatUStartUpFacade.InstantiateUnder(MyContainerFacade,oFeatFacadeOnFeatAWithListAttr,Attr1Name,oFeatFacadeOnFeatU);
	if (FAILED(rc))	return 1;
	cout << "   Feat U instantiated as an aggregation under Feat A" << endl;

	// 2-11-2- Feat V aggregated under Feat A, by valuating its Attr3 attribute
	oFeatFacadeOnFeatV.Clear();
	rc = FeatVStartUpFacade.InstantiateUnder(MyContainerFacade,oFeatFacadeOnFeatAWithListAttr,Attr3Name,oFeatFacadeOnFeatV);
	if (FAILED(rc))	return 1;
	cout << "   Feat V instantiated as an aggregation under Feat A" << endl;

	// 2-11-3- Feat W aggregated under Feat A', by valuating its Attr2 attribute
	CATUnicodeString WStartUpType("`CAAFmExt_W`@`CAAFmExtCatalogForUnderstandingSynchro.CATfct`");
    CATFmStartUpFacade FeatWStartUpFacade(MyCredential, WStartUpType);
	CATFmFeatureFacade oFeatFacadeOnFeatW(MyCredential);
	rc = FeatWStartUpFacade.InstantiateUnder(MyContainerFacade,oFeatFacadeOnFeatAAWithListAttr,Attr2Name,oFeatFacadeOnFeatW);
	if (FAILED(rc))	return 1;
	cout << "   Feat W instantiated as an aggregation under Feat A'" << endl;

	// 2-11-4- Feat X aggregated under Feat A', by valuating its Attr3 attribute
	CATUnicodeString XStartUpType("`CAAFmExt_X`@`CAAFmExtCatalogForUnderstandingSynchro.CATfct`");
    CATFmStartUpFacade FeatXStartUpFacade(MyCredential, XStartUpType);
	CATFmFeatureFacade oFeatFacadeOnFeatX(MyCredential);
	rc = FeatXStartUpFacade.InstantiateUnder(MyContainerFacade,oFeatFacadeOnFeatAAWithListAttr,Attr3Name,oFeatFacadeOnFeatX);
	if (FAILED(rc))	return 1;
	cout << "   Feat X instantiated as an aggregation under Feat A'" << endl;

	// 2-11-5- Feat J (Attr4 of Feat A) is deleted.
	rc = oFeatFacadeOnFeatAWithListAttr.RemovePosition(Attr4Name,2);
	if (FAILED(rc))	return 1;
	cout << "   Feat J from Feat A is deleted" << endl;

	// 2-12- Synchronize Feat A' 
	rc = Synchronize(oFeatFacadeOnFeatAAWithListAttr);
	cout << "   *** Synchronized the Feat A' with List attributes" << endl;

	// Feature Model (Reference and Instance) post synchronization is as depicted below
	cout << "   *** Confirm the model is updated post-synchronization" << endl;
	//   Feat A            -------------- Instantiated to ----->    Feat A'
	//    *                                                          *
	//    |___Feat B, C, U (Attr1 list)                                 |___Feat B', C', U'     (Attr1 list)
	//    |___Feat D, E    (Attr2 list)                                 |___Feat D', E', W      (Attr2 list)
	//    |___Feat F, G, V (Attr3 list)                                 |___Feat F', G', V', X  (Attr3 list)
	//    |___Feat I       (Attr4 list)                                 |___Feat I',            (Attr4 list)

	// 2-13- Post-Synchronization Checks
	// 2-13-1- Feat A' attribute Attr1 of type component list is of size 3
	CATFmAttributeValuationInfo AttrValuationInfo;
	rc = oFeatFacadeOnFeatAAWithListAttr.GetAttributeValuationInfo(Attr1Name,AttrValuationInfo);
	if (3 != AttrValuationInfo.m_ListSize) return 1;
	cout << "   Confirm Feat A' attribute Attr1 of type component list is of size 3" << endl;

	// 2-13-2- Feat A' attribute Attr1 value at index 3 is Feat U'
	rc = oFeatFacadeOnFeatAAWithListAttr.GetValue(Attr1Name,AttrVal);
	if (FAILED(rc))	return 1;

	CATFmAttributeValue AttrValueAtIndex = AttrVal[3];
	CATFmFeatureFacade oFeatFacadeAtIndex(MyCredential);
	rc = AttrValueAtIndex.GetFeature(oFeatFacadeAtIndex);
	if (FAILED(rc))	return 1;

	rc   = oFeatFacadeAtIndex.GetReference(AttrVal);
	if (FAILED(rc))	return 1;

	CATFmFeatureFacade FeatFacadeOnRef(MyCredential);
	rc = AttrVal.GetFeature(FeatFacadeOnRef);
	if (FAILED(rc))	return 1;
	CATBaseUnknown_var spCBUOnFeatRef = FeatFacadeOnRef.GetFeature();

	CATBaseUnknown_var spCBUOnFeat = oFeatFacadeOnFeatU.GetFeature();
	if (!(spCBUOnFeatRef->IsEqual((CATBaseUnknown*)spCBUOnFeat))) return 1;
	cout << "   Confirm Feat A' attribute Attr1 value at index 3 is Feat U'" << endl;

	// ==========================================================================================================
	// 2-13-3- Feat A' attribute Attr2 of type component list is of size 3
	rc = oFeatFacadeOnFeatAAWithListAttr.GetAttributeValuationInfo(Attr2Name,AttrValuationInfo);
	if (3 != AttrValuationInfo.m_ListSize) return 1;
	cout << "   Confirm Feat A' attribute Attr2 of type component list is of size 3" << endl;

	// 2-13-4- Feat A' attribute Attr2 value at index 3 is Feat W
	rc = oFeatFacadeOnFeatAAWithListAttr.GetValue(Attr2Name,AttrVal);
	if (FAILED(rc))	return 1;

	AttrValueAtIndex = AttrVal[3];
	oFeatFacadeAtIndex.Clear();
	rc = AttrValueAtIndex.GetFeature(oFeatFacadeAtIndex);
	if (FAILED(rc))	return 1;

	CATBaseUnknown_var spCBUOnFeatAtIndex  = oFeatFacadeAtIndex.GetFeature();
	CATBaseUnknown_var spCBUOnFeat1        = oFeatFacadeOnFeatW.GetFeature();
	if (!(spCBUOnFeatAtIndex->IsEqual((CATBaseUnknown*)spCBUOnFeat1))) return 1;  
	cout << "   Confirm Feat A' attribute Attr2 value at index 3 is Feat W" << endl;

	// ==========================================================================================================
	// 2-13-5- Feat A' attribute Attr3 of type component list is of size 4
	rc = oFeatFacadeOnFeatAAWithListAttr.GetAttributeValuationInfo(Attr3Name,AttrValuationInfo);
	if (4 != AttrValuationInfo.m_ListSize) return 1;
	cout << "   Confirm Feat A' attribute Attr3 of type component list is of size 4" << endl;

	// 2-13-6- Feat A' attribute Attr3 value at index 3 is Feat V'
	CATFmAttributeValue AttrValList;
	rc = oFeatFacadeOnFeatAAWithListAttr.GetValue(Attr3Name,AttrValList);
	if (FAILED(rc))	return 1;

	AttrValueAtIndex = AttrValList[3];
	oFeatFacadeAtIndex.Clear();
	rc = AttrValueAtIndex.GetFeature(oFeatFacadeAtIndex);
	if (FAILED(rc))	return 1;

	rc   = oFeatFacadeAtIndex.GetReference(AttrVal);
	if (FAILED(rc))	return 1;

	FeatFacadeOnRef.Clear();
	rc = AttrVal.GetFeature(FeatFacadeOnRef);
	if (FAILED(rc))	return 1;
	spCBUOnFeatRef = FeatFacadeOnRef.GetFeature();

	rc   = oFeatFacadeAtIndex.GetReference(AttrVal);
	if (FAILED(rc))	return 1;

	FeatFacadeOnRef.Clear();
	rc = AttrVal.GetFeature(FeatFacadeOnRef);
	if (FAILED(rc))	return 1;
	spCBUOnFeatRef = FeatFacadeOnRef.GetFeature();

	spCBUOnFeat      = oFeatFacadeOnFeatV.GetFeature();
	if (!(spCBUOnFeatRef->IsEqual((CATBaseUnknown*)spCBUOnFeat))) return 1;
	cout << "   Confirm Feat A' attribute Attr3 value at index 3 is Feat V'" << endl;

	// Feat A' attribute Attr3 value at index 4 is Feat X
	AttrValueAtIndex = AttrValList[4];
	oFeatFacadeAtIndex.Clear();
	rc = AttrValueAtIndex.GetFeature(oFeatFacadeAtIndex);
	if (FAILED(rc))	return 1;

	spCBUOnFeatAtIndex  = oFeatFacadeAtIndex.GetFeature();
	spCBUOnFeat       = oFeatFacadeOnFeatX.GetFeature(); 
	if (!(spCBUOnFeatAtIndex->IsEqual((CATBaseUnknown*)spCBUOnFeat))) return 1; 
	cout << "   Confirm Feat A' attribute Attr3 value at index 4 is Feat X" << endl;

	// ==========================================================================================================
	// 2-13-7- Feat A' attribute Attr4 of type component list is of size 1. It has only Feat I'
	rc = oFeatFacadeOnFeatAAWithListAttr.GetAttributeValuationInfo(Attr4Name,AttrValuationInfo);
	if (1 != AttrValuationInfo.m_ListSize) return 1;  
	cout << "   Confirm Feat A' attribute Attr4 of type component list is of size 1" << endl;

	rc = oFeatFacadeOnFeatAAWithListAttr.GetValue(Attr4Name,AttrValList);
	if (FAILED(rc))	return 1;

	AttrValueAtIndex = AttrValList[1];
	oFeatFacadeAtIndex.Clear();
	rc = AttrValueAtIndex.GetFeature(oFeatFacadeAtIndex);
	if (FAILED(rc))	return 1;

	// 2-13-8- Confirm Feat A' attribute Attr4 value at index 1 is Feat I
	rc   = oFeatFacadeAtIndex.GetReference(AttrVal);
	if (FAILED(rc))	return 1;

	FeatFacadeOnRef.Clear();
	rc = AttrVal.GetFeature(FeatFacadeOnRef);
	if (FAILED(rc))	return 1;

	spCBUOnFeatRef = FeatFacadeOnRef.GetFeature();
	spCBUOnFeat = oFeatFacadeOnFeatI.GetFeature();
	if (!(spCBUOnFeatRef->IsEqual((CATBaseUnknown*)spCBUOnFeat))) return 1;
	cout << "   Confirm Feat A' attribute Attr4 value at index 1 is Feat I" << endl;

	// Destroy Feat A, A' before proceeding
	rc = oFeatFacadeOnFeatAWithListAttr.DeleteSelf();
	if (FAILED(rc))	return 1;

	rc = oFeatFacadeOnFeatAAWithListAttr.DeleteSelf();
	if (FAILED(rc))	return 1;

	// ----------------------------------------------------------------------------------------
	// 3- Scenario 3 --> Illustrating Synchronization of feature attribute is not recursive
	// ----------------------------------------------------------------------------------------
	cout << "   ***** Scenario 3 ---> Illustrating Synchronization of a feature attribute is not recursive" << endl;
	// 3-1- Instantiation is Recursive as illustrated by the model below
	cout << "   *** Instantiation is recursive" << endl;

	// Feat A                   ------ Instantiated to -------->   Feat A'     
	//    *                                                          *
	//    |___Feat B       (Attr1)                                   |___Feat B' (Attr1)
	//          *                                                           *
	//          |___Feat D, E (Attr2)                                       |___Feat D', E' (Attr2)

	// 3-1-1- Instantiate the CAAFmExt_Arec feature
	CATUnicodeString ArecStartUpType("`CAAFmExt_Arec`@`CAAFmExtCatalogForUnderstandingSynchro.CATfct`");
    CATFmStartUpFacade FeatArecStartUpFacade(MyCredential, ArecStartUpType);
	CATFmFeatureFacade oFeatFacadeOnFeatArec (MyCredential);
	rc = FeatArecStartUpFacade.InstantiateIn(MyContainerFacade,oFeatFacadeOnFeatArec);
	if (FAILED(rc))	return 1;
	cout << "   CAAFmExt_Arec instantiated" << endl;

	// 3-1-2- Aggregate feature CAAFmExt_Brec under feature CAAFmExt_Arec
	CATUnicodeString BrecStartUpType("`CAAFmExt_Brec`@`CAAFmExtCatalogForUnderstandingSynchro.CATfct`");
    CATFmStartUpFacade FeatBrecStartUpFacade(MyCredential, BrecStartUpType);
	CATFmFeatureFacade oFeatFacadeOnFeatBrec(MyCredential);
	rc = FeatBrecStartUpFacade.InstantiateUnder(MyContainerFacade,oFeatFacadeOnFeatArec,Attr1Name,oFeatFacadeOnFeatBrec);
	if (FAILED(rc))	return 1;
	cout << "   Feat CAAFmExt_Brec instantiated as an aggregation under Feat CAAFmExt_Arec" << endl;

	// 3-1-3- Aggregate feature CAAFmExt_D and CAAFmExt_E under feature CAAFmExt_Brec.1
	oFeatFacadeOnFeatD.Clear();
	rc = FeatDStartUpFacade.InstantiateUnder(MyContainerFacade,oFeatFacadeOnFeatBrec,Attr2Name,oFeatFacadeOnFeatD);
	if (FAILED(rc))	return 1;
	cout << "   Feat CAAFmExt_D instantiated as an aggregation under Feat CAAFmExt_Brec.1" << endl;

	oFeatFacadeOnFeatE.Clear();
	rc = FeatEStartUpFacade.InstantiateUnder(MyContainerFacade,oFeatFacadeOnFeatBrec,Attr2Name,oFeatFacadeOnFeatE);
	if (FAILED(rc))	return 1;
	cout << "   Feat CAAFmExt_E instantiated as an aggregation under Feat CAAFmExt_Brec.1" << endl;

	// 3-1-4- Instantiate another feature from the existing CAAFmExt_Arec feature
	rc = oFeatFacadeOnFeatArec.InstantiateIn(MyContainerFacade,attrValue);
	if (FAILED(rc))	return 1;
	cout << "   Feat A'rec instantiated from Feat Arec" << endl;
	CATFmFeatureFacade oFeatFacadeOnFeatAArec (MyCredential,attrValue);

	// 3-1-5- Retrieve Feat B' under Feat A'
	rc = oFeatFacadeOnFeatAArec.GetValue(Attr1Name,AttrVal);
	if (FAILED(rc))	return 1;

	CATFmFeatureFacade FeatFacadeOnBB(MyCredential);
	rc = AttrVal.GetFeature(FeatFacadeOnBB);
	if (FAILED(rc))	return 1;
	cout << "   Feat B' aggregated under FeatA'rec retrieved" << endl;

	// 3-1-6- Confirm count of components aggregated under Feat B' is two 
	rc = FeatFacadeOnBB.GetAttributeValuationInfo(Attr2Name,AttrValuationInfo);
	if (2 != AttrValuationInfo.m_ListSize) return 1;
	cout << "   Confirmed count of components aggregated under Feat B' is two" << endl;

	// 3-1-2- Confirm the first of the components aggregated is an instance whose reference is Feat D (sample check)
	rc = FeatFacadeOnBB.GetValue(Attr2Name,AttrValList);
	if (FAILED(rc))	return 1;

	AttrValueAtIndex = AttrValList[1];
	CATFmFeatureFacade oFeatFacadeOnFeatDD(MyCredential);
	rc = AttrValueAtIndex.GetFeature(oFeatFacadeOnFeatDD);
	if (FAILED(rc))	return 1;

	rc = oFeatFacadeOnFeatDD.GetReference(AttrVal);
	if (FAILED(rc))	return 1;

	FeatFacadeOnRef.Clear();
	rc = AttrVal.GetFeature(FeatFacadeOnRef);
	if (FAILED(rc))	return 1;
	spCBUOnFeatRef = FeatFacadeOnRef.GetFeature();

	spCBUOnFeat = oFeatFacadeOnFeatD.GetFeature();
	if (!(spCBUOnFeatRef->IsEqual((CATBaseUnknown*)spCBUOnFeat))) return 1;
	cout << "   Confirmed the first of the components aggregated is an instance whose reference is Feat D (sample check)" << endl;

	// 3-2- Confirm Synchronization is not Recursive. It is illustrated by the model depicted below
	cout << "   *** Confirm Synchronization is not recursive" << endl;
	// Feat D under Feat A deleted. Feat A' attribute Attr1 synchronized. Feat D' under Feat B' still exists

	// Feat A                   ------ Instantiated to -------->   Feat A'     
	//    *                                                          *
	//    |___Feat B       (Attr1)                                   |___Feat B'            (Attr1)
	//          *                                                           *
	//          |___Feat E (Attr2)                                          |___Feat D', E' (Attr2)

	// 3-2-1- Delete Feat D under Feat B
	rc = oFeatFacadeOnFeatD.DeleteSelf();
	if (FAILED(rc))	return 1;
	cout << "   Delete called on Feat D under Feat B" << endl;

	// 3-2-2- Call Synchronization of attribute Attr1 of Feat A'
	rc = oFeatFacadeOnFeatAArec.Synchronize(Attr1Name);

	// 3-2-3- Confirm Feat D' under Feat B' still exists
	if (FALSE == oFeatFacadeOnFeatDD.IsValid()) return 1;
	cout << "   Confirmed Feat D' under Feat B' still exists" << endl;

	// Synchronize attribute Attr2 of Feat B'. It results in the model depicted below. Feat D' under Feat B' is deleted

	// Feat A                   ------ Instantiated to -------->   Feat A'     
	//    *                                                          *
	//    |___Feat B       (Attr1)                                   |___Feat B'        (Attr1)
	//          *                                                           *
	//          |___Feat E (Attr2)                                          |___Feat E' (Attr2)

	// 3-2-4- Call synchronization on attribute Attr2 of Feat B'
	rc = FeatFacadeOnBB.Synchronize(Attr2Name);

	// 3-2-5- Confirm count of features aggregated under Feat B' is one
	rc = FeatFacadeOnBB.GetAttributeValuationInfo(Attr2Name,AttrValuationInfo);
	if (1 != AttrValuationInfo.m_ListSize) return 1;
	cout << "   Confirmed count of components aggregated under Feat B' is two" << endl;

	// 3-2-6- Confirm the feature aggregated under Feat B' is an instance of Feat E
	rc = FeatFacadeOnBB.GetValue(Attr2Name,AttrValList);
	if (FAILED(rc))	return 1;

	AttrValueAtIndex = AttrValList[1];
	CATFmFeatureFacade oFeatFacadeOnFeatEE(MyCredential);
	rc = AttrValueAtIndex.GetFeature(oFeatFacadeOnFeatEE);
	if (FAILED(rc))	return 1;

	rc = oFeatFacadeOnFeatEE.GetReference(AttrVal);
	if (FAILED(rc))	return 1;

	FeatFacadeOnRef.Clear();
	rc = AttrVal.GetFeature(FeatFacadeOnRef);
	if (FAILED(rc))	return 1;
	spCBUOnFeatRef = FeatFacadeOnRef.GetFeature();

	spCBUOnFeat = oFeatFacadeOnFeatE.GetFeature();
	if (!(spCBUOnFeatRef->IsEqual((CATBaseUnknown*)spCBUOnFeat))) return 1;
	cout << "   Confirmed the feature aggregated under Feat B' is an instance of Feat E" << endl;

#ifdef CATIAR214
	//---------------------------------------------------------------------
	// - Saves the session
	//---------------------------------------------------------------------
	CATAdpSaver saver;
	rc = saver.Save();
	if (FAILED(rc))	return 1;
	cout <<"   Save is successful " << endl;

	// Unload components from session
	Bag.RemoveAll();

	pContainer->Release();
	pContainer = NULL ;
	//------------------------------------------------------------------
	// - Closes the session
	//------------------------------------------------------------------
	rc = ::CAAAdpCloseSession();
	if (FAILED(rc) ) return 1;

	cout << endl << "The CAAFmExtUnderstandingSynchro main program ends ...."<< endl << endl;
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


// Synchronizes all attributes of feature input
HRESULT Synchronize(CATFmFeatureFacade & iFeatFacade)
{
	HRESULT rc = iFeatFacade.Synchronize(Attr1Name);
	if (SUCCEEDED(rc))
		rc = iFeatFacade.Synchronize(Attr2Name);
	if (SUCCEEDED(rc))
		rc = iFeatFacade.Synchronize(Attr3Name);
	if (SUCCEEDED(rc))
		rc = iFeatFacade.Synchronize(Attr4Name);

	return rc;
}

