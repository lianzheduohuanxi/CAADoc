// COPYRIGHT DASSAULT SYSTEMES 2010
//===============================================
// Abstract of Use Case "CAAV5V6FmExtWorkingWithFeatureFacade"
// ----------------------------------------------
//	The Use Case illustrates working with a Feature Facade using its various methods
//
//=============================================================================
//  Steps :
//
//   1- Check facade not yet bound to a valid feature
//   2- Instantiate the "CAAFmExtLibrary" feature 
//   3- Check facade after instantiation (facade bound to a valid feature)
//   4- Instantiate another Book feature, from an existing Book feature
//   5- Operator = copy feature and credential 
//  6- Comparison between Feature Facades 
//  7- Check facade after Clear(), since it is not bound to a valid feature
//  8- Use methods to retrieve the feature underlying the facade
//      8-1- QueryInterfaceOnFeature() call on a feature facade to retrieve an Interface pointer on the underlying feature
//      8-2- GetFeature() call to retrieve a handler on the feature underlying the feature facade
//  9- Confirm feature type is always the StartUp Name
//      9-1-  Retrieve type of feature instantiated from a StartUp
//      9-2-  Retrieve type of feature instantiated from an existing feature
//  10- Retrieve StartUp Facade from a feature
//      10-1- Retrieve the StartUp facade from a feature instantiated from a StartUp
//            Confirm it is the same as the one created earlier during feature instantiation
//      10-2- Retrieve the StartUp facade from a feature instantiated from an existing feature
//            Confirm it is the same as the one created earlier during feature instantiation
//  11- Retrieve Reference of a feature
//      11-1- Confirm feature instantiated from a StartUp is not associated with a Reference
//      11-2- Confirm feature instantiated from another feature has the latter feature, as its Reference
//  12- Retrieve the Container Facade from a feature. Confirm it is the same, as created earlier during feature instantiation
//  13- Retrieve the feature parent (aggregating feature)
//      13-1- Aggregate the Book feature under the Library feature
//      13-2- Retrieve the parent of the Book feature. It is the Library feature
//      13-3- Retrieve the Root Parent of the Book feature. It is again the Library feature
//  14- Feature Facade Methods return failure when it is not bound to a valid feature 
//      14-1- Confirm success in displaying the name of the Book feature
//      14-2- Clear the Book feature. It is no longer bound to a valid feature now 
//      14-3- Illustrate GetValue() call fails 
//      14-4- Illustrate GetDisplayName() call fails 
//      14-5- Illustrate QueryInterfaceOnFeature() call fails 
//  - Saves the Session
//  - Closes the Session
//
//=============================================================================
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAV5V6FmExtWorkingWithFeatureFacade DocumentStorageName" 
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

// FeatureModelerExt Framework
#include "CATFmFeatureFacade.h" 
#include "CATFmContainerFacade.h"
#include "CATFmStartUpFacade.h"
#include "CATFmCredentials.h"
#include "CATFmAttributeName.h"
#include "CATFmContainerServices.h"
#include "CATFmFeatureModelerID.h"
#include "CATFmAttributeValue.h"

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

//ObjectModelerBase Framework
#include "CATOmbLifeCycleRootsBag.h"

//CAT3DPhysicalRepInterfaces Framework
#include "CATIPsiRepresentationReference.h"  // interface on rep ref

// CATPLMIdentificationAccess
#include "CATIPLMComponent.h"
#include "CATIAdpPLMIdentificator.h"

// CATPLMComponentInterfaces
#include "CATPLMComponentInterfacesServices.h"

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

//=================================================================
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
	// Append your identity as the owner of the "CAAFmExtBaseCatalogForCredential" catalog
	CATUnicodeString clientId("CAAFmExtCatalogForCredential");
	CATUnicodeString iCatalogName("CAAFmExtBaseCatalogForCredential");

	// Append credentials authorizing client to work with the Applicative Container
	rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
	rc = MyCredential.RegisterAsCatalogOwner(iCatalogName,clientId);
	if (FAILED(rc)) return 1;
	cout << "   Success in building our accreditation as owner of the CAAFmExtBaseCatalogForCredential feature catalog " << endl;

	cout << "   Success in building our credential object to work with Appli Cont" << endl;

	//Create container facade to work with
	CATFmContainerFacade ContFacadeOnAppliCont(MyCredential,piRootContainer);


#endif

#ifdef CATIAR214

	//---------------------
	// 1- Checks arguments
	//---------------------
	if ( 7 != iArgc )
	{
		cout << endl;
		cout << "Usage: CAAV5V6FmExtWorkingWithFeatureFacade <Repository> <Server> <User> <Password> <SecurityCtx> <Environment>" ;
		cout <<endl;
		return 1;
	}
	cout << "The CAAV5V6FmExtWorkingWithFeatureFacade main program begins ...."<< endl << endl;

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
	cout << "      SecurityCtx="<< iArgv[5] << endl;

	//-------------------------------------------------
	// 3- Build Client accreditations : who I am ?
	//-------------------------------------------------
	CATFmCredentials MyCredential;
	// Append your identity as the owner of the "CAAFmExtBaseCatalogForCredential" catalog
	CATUnicodeString clientId("CAAFmExtCatalogForCredential");
	CATUnicodeString iCatalogName("CAAFmExtBaseCatalogForCredential");

	// Append credentials authorizing client to work with the Applicative Container
	rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
	rc = MyCredential.RegisterAsCatalogOwner(iCatalogName,clientId);
	if (FAILED(rc)) return 1;
	cout << "   Success in building our accreditation as owner of the CAAFmExtBaseCatalogForCredential feature catalog " << endl;

	cout << "   Success in building our credential object to work with Appli Cont" << endl;

	//--------------------------------
	// 4- Creating the Techno Rep
	//--------------------------------
	CATString EnvToUse = iArgv[6];
	CATString Repository = iArgv[1];
	CATUnicodeString NameofAppliCont = "MyAppliCont";
	CATUnicodeString TypeofAppliCont = "CATFeatCont" ;
	CATIPsiRepresentationReference * pPsiCreatedRepRef= NULL;
	CATBaseUnknown * pContainer = NULL ;
	rc = ::CAAV5V6FmExtCreateRepRef(MyCredential, EnvToUse,Repository,TypeofAppliCont,NameofAppliCont,
		IID_CATIPsiRepresentationReference,(void**) &pPsiCreatedRepRef, &pContainer);
	if (FAILED(rc) || (NULL==pPsiCreatedRepRef) || (NULL==pContainer) ) return 1;
	cout <<"   The Product Representation Reference is created" << endl;

	// Insert component that is loaded in session, in BAG
	CATOmbLifeCycleRootsBag Bag;
	Bag.InsertRoot(pPsiCreatedRepRef);

	//Create container facade to work with
	CATFmContainerFacade ContFacadeOnAppliCont(MyCredential,pContainer);

#endif
	//--------------------------------------------------------------------------------------------------------------------------
	// 1- Check facade is not yet bound to a valid feature
	//--------------------------------------------------------------------------------------------------------------------------
	CATFmFeatureFacade oFeatFacadeOnLibrary(MyCredential);
	if ( TRUE == oFeatFacadeOnLibrary.IsValid()) return 1 ;
	cout << "   IsValid returns FALSE when invoked on a Feature Facade not bound to a feature entity" << endl;

	//-----------------------------------------------
	// 2- Instantiate the "CAAFmExtLibrary" feature 
	//-----------------------------------------------
	// 2-1- Creates a "CAAFmExtLibrary" StartUp Facade
	CATUnicodeString LibraryStartUpIdentity("`CAAFmExtLibrary`@`CAAFmExtBaseCatalogForCredential.CATfct`");
	CATFmStartUpFacade LibraryStartUpFacade(MyCredential,LibraryStartUpIdentity);

	// 2-2- Instantiates the "CAAFmExtLibrary" StartUp
	rc = LibraryStartUpFacade.InstantiateIn(ContFacadeOnAppliCont,oFeatFacadeOnLibrary);
	if ( FAILED(rc) ) return 1;
	cout << "   Success in instantiating the Library feature" << endl;

	//-----------------------------------------------------------------------------------------------------------------
	// - Check facade is bound to a valid feature
	//-----------------------------------------------------------------------------------------------------------------
	if ( FALSE == oFeatFacadeOnLibrary.IsValid() ) return 1 ;
	cout << "   IsValid returns TRUE when invoked on a Feature Facade bound to a valid feature entity" << endl;

	//----------------------------------------------------------------
	// 3- Instantiate the "CAAFmExtLibBook" feature from its StartUp
	//----------------------------------------------------------------
	// 3-1- Creates a "CAAFmExtLibBook" StartUp Facade
	CATUnicodeString BookStartUpIdentity("`CAAFmExtLibBook`@`CAAFmExtBaseCatalogForCredential.CATfct`");
	CATFmStartUpFacade BookStartUpFacade(MyCredential,BookStartUpIdentity);

	// 3-2- Instantiates the "CAAFmExtLibBook" StartUp
	CATFmFeatureFacade oFeatFacadeOnBookFromSU(MyCredential);
	rc = BookStartUpFacade.InstantiateIn(ContFacadeOnAppliCont,oFeatFacadeOnBookFromSU);
	if ( FAILED(rc) ) return 1;
	cout << "   Success in instantiating the Book feature from its StartUp" << endl;

	//---------------------------------------------------------------------
	// 4- Instantiate another Book feature, from an existing Book feature
	//---------------------------------------------------------------------
	CATFmAttributeValue attrValue;
	rc = oFeatFacadeOnBookFromSU.InstantiateIn(ContFacadeOnAppliCont,attrValue);
	if (FAILED(rc)) return 1;
	cout << "   Success in instantiating a Book feature from an existing Book feature " << endl;
	CATFmFeatureFacade oFeatFacadeOnBookFromBookFeat(MyCredential,attrValue);

	// -------------------------------------------------------------------------------------
	// 5- Operator = copy feature and credential 
	// -------------------------------------------------------------------------------------
	CATFmFeatureFacade FeatFacadeOnBook1 ;
	FeatFacadeOnBook1 = oFeatFacadeOnBookFromSU.GetFeature();
	CATUnicodeString Name ;
	rc = FeatFacadeOnBook1.GetDisplayName(Name);
	if (SUCCEEDED(rc)) return 1;   
	cout << "   Without credential, the displayname cannot be displayed" << endl;

	FeatFacadeOnBook1 = oFeatFacadeOnBookFromSU ;
	rc = FeatFacadeOnBook1.GetDisplayName(Name);
	if (FAILED(rc)) return 1;
	cout << "   With credential, success in retrieving the display name of the book:" << Name.CastToCharPtr() << endl;

	// -------------------------------------------------------------------------------------
	// 6- Comparison between Feature Facades ( Credentials not taken into account )
	// -------------------------------------------------------------------------------------
	CATFmFeatureFacade FeatFacadeOnBookCopy = oFeatFacadeOnBookFromSU;  // feature and credential are copied
	if ( FALSE == FeatFacadeOnBookCopy.CompareFeatureWith(oFeatFacadeOnBookFromSU) ) return 1 ; // only feature are compared
	cout << "   Two facades are equal when bound to the same feature entity" << endl;

	if ( TRUE == oFeatFacadeOnLibrary.CompareFeatureWith(oFeatFacadeOnBookFromSU) )return 1 ;
	cout << "   Two facades are not equal when bound to different feature entities" << endl;

	// -----------------------------------------------------------------------------------------------------------------
	// 7- Check Feature facade after a clear() since it is not bound to a valid feature
	// -----------------------------------------------------------------------------------------------------------------
	// Call to Clear() on the Book feature facade
	FeatFacadeOnBookCopy.Clear();

	if (FeatFacadeOnBookCopy.IsValid()) return 1 ; 
	cout << "   IsValid invoked on a feature facade subsequent to Clear, returns TRUE , implying it is not bound to a valid feature" << endl;

	// -----------------------------------------------------------------
	// 8- Use methods to retrieve the feature underlying the facade
	// -----------------------------------------------------------------
	// 8-1- QueryInterfaceOnFeature() call on a feature facade to retrieve an Interface pointer on the underlying feature
	CATBaseUnknown* poCBUOnBook = NULL;
	rc = oFeatFacadeOnBookFromSU.QueryInterfaceOnFeature(IID_CATBaseUnknown,(void**)&poCBUOnBook);
	if (NULL == poCBUOnBook) return 1;
	cout << "   Success in retrieving an Interface on the feature underlying the facade with the QueryInterfaceOnFeature() call" << endl;

	poCBUOnBook->Release();
	poCBUOnBook = NULL;

	// 8-2- GetFeature() call to retrieve a handler on the feature underlying the feature facade
	CATBaseUnknown_var spCBUOnBook = oFeatFacadeOnBookFromSU.GetFeature();
	if (NULL_var == spCBUOnBook) return 1;
	cout << "   Success in retrieving a handler to the feature underlying the feature facade with the GetFeature() call" << endl;

	// ------------------------------------------------------
	// 9- Confirm feature type is always the StartUp Name
	// ------------------------------------------------------
	// 9-1-  Retrieve type of feature instantiated from a StartUp
	CATUnicodeString strBookSU("CAAFmExtLibBook");
	CATUnicodeString strBookFromSUType;
	rc = oFeatFacadeOnBookFromSU.GetType(strBookFromSUType);
	if (FAILED(rc) || (strBookSU != strBookFromSUType)) return 1;
	cout << "   The Book feature instantiated from StartUp is of type CAAFmExtLibBook, the name of the StartUp" << endl;

	// 9-2-  Retrieve type of feature instantiated from an existing feature
	CATUnicodeString strBookFromFeatType;
	rc = oFeatFacadeOnBookFromBookFeat.GetType(strBookFromFeatType);
	if (FAILED(rc) || (strBookSU != strBookFromFeatType)) return 1;
	cout << "   The Book feature instantiated from an existing Book feature is also of type CAAFmExtLibBook, the name of the StartUp" << endl;

	// ------------------------------------------------------
	// 10- Retrieve StartUp Facade from a feature
	// ------------------------------------------------------
	// 10-1- Retrieve the StartUp facade from a feature instantiated from a StartUp
	//       Confirm it is the same as the one created earlier during feature instantiation
	CATFmStartUpFacade oStartUpFacade(MyCredential);
	rc = oFeatFacadeOnBookFromSU.GetStartUpFacade(oStartUpFacade);
	if (FAILED(rc) || (! oStartUpFacade.IsValid() ) || (! BookStartUpFacade.CompareStartUpWith(oStartUpFacade) )) return 1;
	cout << "   Success in retrieving the StartUp Facade from a Book feature instantiated from a StartUp" << endl;

	CATUnicodeString strRetrievedSUTypeName;
	rc = oStartUpFacade.GetTypeName(strRetrievedSUTypeName);
	if (FAILED(rc)) return 1;

	if (strBookSU != strRetrievedSUTypeName) return 1;
	cout << "   The StartUp facade retrieved is the same as the one created earlier while instantiating the features" << endl;

	// 10-2- Retrieve the StartUp facade from a feature instantiated from an existing feature
	//       Confirm it is the same as the one created earlier during feature instantiation
	oStartUpFacade.Clear();
	rc = oFeatFacadeOnBookFromBookFeat.GetStartUpFacade(oStartUpFacade);
	if (FAILED(rc) || (!oStartUpFacade.IsValid())) return 1;
	cout << "   Success in retrieving the StartUp Facade from a Book feature instantiated from an existing feature" << endl;

	rc = oStartUpFacade.GetTypeName(strRetrievedSUTypeName);
	if (FAILED(rc)) return 1;

	if (strBookSU != strRetrievedSUTypeName) return 1;
	cout << "   The StartUp facade retrieved is the same as the one created earlier while instantiating the features" << endl;

	// --------------------------------------	
	// 11- Retrieve Reference of a feature
	// --------------------------------------	
	// 11-1- Confirm feature instantiated from a StartUp is not associated with a Reference
	CATFmAttributeValue oAttrValue;
	rc = oFeatFacadeOnBookFromSU.GetReference(oAttrValue);
	if (FAILED(rc)) return 1; 

	CATFmFeatureFacade oFeatFacadeOnRef(MyCredential);
	rc = oAttrValue.GetFeature(oFeatFacadeOnRef);
	if (FAILED(rc) || (oFeatFacadeOnRef.IsValid())) return 1;
	cout << "   There is no Reference associated with a feature instantiated from a StartUp" << endl;

	// 11-2- Confirm feature instantiated from another feature has the latter feature, as its Reference
	rc = oFeatFacadeOnBookFromBookFeat.GetReference(oAttrValue);
	if (FAILED(rc)) return 1;
	rc = oAttrValue.GetFeature(oFeatFacadeOnRef);
	if (FAILED(rc) || (! oFeatFacadeOnRef.CompareFeatureWith(oFeatFacadeOnBookFromSU) )) return 1;
	cout << "   The Reference of a feature instantiated from another feature is the other feature" << endl;

	// --------------------------------------------------------------------------------------------------------------------------
	// 12- Retrieve the Container Facade from a feature. Confirm it is the same, as created earlier during feature instantiation
	// --------------------------------------------------------------------------------------------------------------------------
	CATFmContainerFacade ContFacadeFromFeat(MyCredential);
	rc = oFeatFacadeOnBookFromBookFeat.GetContainerFacade(ContFacadeFromFeat);
	if (FAILED(rc) || (!ContFacadeOnAppliCont.CompareContainerWith(ContFacadeFromFeat)) ) return 1;  
	cout << "   Success in retrieving the Container Facade from a feature" << endl;
	cout << "   The Container facade retrieved is the same as the one created earlier while instantiating the features" << endl;

	//-------------------------------------------------------
	// 13 Retrieve the feature parent (aggregating feature)
	//-------------------------------------------------------
	// 13-1- Aggregate the Book feature under the Library feature
	CATFmAttributeName LibBooksAttrName("LibraryBooks");
	oAttrValue.SetFeature(oFeatFacadeOnBookFromSU);
	rc = oFeatFacadeOnLibrary.SetValue(LibBooksAttrName,oAttrValue);
	if (FAILED(rc)) return 1;
	cout << "   Success in aggregating the Book feature under the Library feature" << endl;

	// 13-2- Retrieve the parent of the Book feature. It is the Library feature
	rc = oFeatFacadeOnBookFromSU.GetParentFeature(oAttrValue);
	if (FAILED(rc)) return 1;
	CATFmFeatureFacade oFeatFacadeOfParent(MyCredential);
	rc = oAttrValue.GetFeature(oFeatFacadeOfParent);
	if (FAILED(rc) || (! oFeatFacadeOfParent.CompareFeatureWith(oFeatFacadeOnLibrary) )) return 1;
	cout << "   The parent of the Book feature is the Libary feature" << endl;

	// 13-3- Retrieve the Root Parent of the Book feature. It is again the Library feature
	rc = oFeatFacadeOnBookFromSU.GetRootParentFeature(oAttrValue);
	if (FAILED(rc)) return 1;
	rc = oAttrValue.GetFeature(oFeatFacadeOfParent);
	if (FAILED(rc) || (! oFeatFacadeOfParent.CompareFeatureWith(oFeatFacadeOnLibrary))) return 1;
	cout << "   The root parent of the Book feature is the Libary feature" << endl;

	// -----------------------------------------------------------------------------------
	// 14- Feature Facade Methods return failure when it is not bound to a valid feature 
	// -----------------------------------------------------------------------------------
	// 14-1- Confirm success in displaying the name of the Book feature
	CATUnicodeString BookDisplayName;
	rc = oFeatFacadeOnBookFromSU.GetDisplayName(BookDisplayName);
	if (FAILED(rc)) return 1;
	cout << "   Success in retrieving the display name of the book feature, prior to Clear(). It is " << BookDisplayName.ConvertToChar() << endl;

	// 14-2- Clear the Book feature. It is no longer bound to a valid feature now 
	oFeatFacadeOnBookFromSU.Clear();

	// 14-3- Illustrate GetValue() call fails 
	CATFmAttributeName AttrKey("Title");
	rc = oFeatFacadeOnBookFromSU.GetValue(AttrKey,oAttrValue);
	if (SUCCEEDED(rc)) return 1;
	cout << "   Confirm GetValue() returns FAILURE, after Clear() since feature facade not bound to a valid feature entity" << endl;

	// 14-4- Illustrate GetDisplayName() call fails 
	rc = oFeatFacadeOnBookFromSU.GetDisplayName(BookDisplayName);
	if (SUCCEEDED(rc)) return 1;
	cout << "   Failure in retrieving the display name of the book feature, after Clear()" << endl;

	// 14-5- Illustrate QueryInterfaceOnFeature() call fails 
	rc = oFeatFacadeOnBookFromSU.QueryInterfaceOnFeature(IID_CATBaseUnknown,(void**)&poCBUOnBook);
	if ((SUCCEEDED(rc)) || (NULL!=poCBUOnBook)) return 1;
	cout << "   Failure in retrieving an Interface on the feature underlying the facade, subsequent to the call to Clear()" << endl;

#ifdef CATIAR214
	//---------------------------------------------------------------------
	// 21- Saves the Session
	//---------------------------------------------------------------------
	CATAdpSaver saver;
	rc = saver.Save();
	if ( FAILED(rc)) return 1;
	cout <<"   Save is successful " << endl;

	// Unload components from session
	Bag.RemoveAll();

	pContainer->Release();
	pContainer = NULL ;
	//------------------------------------------------------------------
	// 22- Closes the session
	//------------------------------------------------------------------
	rc = ::CAAAdpCloseSession();
	if (FAILED(rc) ) return 1;

	cout <<"   Close is successful " << endl;
	cout << endl << "The CAAFmExtWorkingWithFeatureFacade main program ends ...."<< endl << endl;

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

