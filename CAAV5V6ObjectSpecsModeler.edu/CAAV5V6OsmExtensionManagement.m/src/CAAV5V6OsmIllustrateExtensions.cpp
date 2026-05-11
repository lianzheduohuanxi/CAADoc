//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
//  Steps
//	1- Create a Credential Object
//			1-1- Instantiate Credential object 
//          1-2- Register as owner of the "CAAOsmCatalogSU", "CAAOsmExt1Catalog"  and "CAAOsmExt2Catalog" catalogs
//			1-3- Register as an application based on Feature modeler.
//	2- Create a new Product representation reference (Techno Rep)
//	3- Create a new applicative container (CAAFmExtBaseFeatureCont) in the Techno Rep.  
//
//	4- Instantiate CAAOsmNovel StartUp (inside CAAFmExtBaseFeatureCont ) 
//			4-1- Instantiate the "CAAOsmNovel" StartUp Facade
//			4-3- Instantiate "CAAOsmNovel" feature  (Novel)
//
//	5- Add feature extensions to Novel feature
//          5-1 HistoricalNovel, BiographicalNovel within CAAFmExtApplication1 
//          5-2 ChildrensNovel within CAAFmExtApplication2
//	    
//	6- Retrieve the ChildrensNovel extension
//          6-1 Retrieve the ChildrensNovel extension from the Novel feature (base)
//          6-2 Get/Set its AgeGroup attribute
//	7- Retrieve the Biographical Novel extension
//			7-1- Retrieve the BiographicalNovel extension from the Novel feature (base)
//			7-2- Retrieve the ExtensionID of BiographicalNovel extension
//			7-3- Retrieve the "Epoch" attribute and display its default value
//			7-4- Change the value of the "Epoch" attribute and display
//			7-5- Retrieve the "Domain" attribute and display its default value
//			7-6- Change the value of the "Domain" attribute and display
//  8- Retrieve the Base Feature (CAAOsmNovel) 
//  9- Scan extensions of the base feature within "CAAFmExtApplication1" (Count expected is 2)  
// 10- Remove extensions contained within the "CAAFmExtApplication1" applicative container 
// 11- Scan extensions of the base feature whatever the applicative container  (Count expected is 1)
//	    
// 12- Saves in repository
//==================================================================================================
//
// The current UC refers to the following list of the StartUps 
//
//		CAAOsmCatalogSU.CATfct
//
//		StartUp									Attribute
//		-------									---------
//
//		CAAOsmBook								Title (string)
//												BookPublisher (specObject)
//
//		CAAOsmNovel (derived from CAAOsmBook)   Author (string)
//												NovelChapter (Component)
//
//
//		CAAOsmExt1Catalog.CATfct (contains features extending CAAOsmNovel)
//
//		StartUp									Attribute
//		-------									---------
//
//		CAAOsmHistoricalNovel 					Epoch (string)
//
//		CAAOsmBiographicalNovel					Domain (string)
//		(derived from CAAOsmHistoricalNovel)
//										
//
//		CAAOsmExt2Catalog.CATfct (contains features extending CAAOsmNovel)
//
//		StartUp									Attribute
//		-------									---------
//
//		CAAOsmChildrensNovel					AgeGroup (int)
//
// These catalogs exist in the CAAFeatureModelerExt.edu/CNext/resources/graphic folder
// which on mkrtv is copied to the Workspace run time view
// 
//==================================================================================================

#include "CAAV5V6OsmIllustrateExtensions.h"
// System Framework
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"
#include "CATIAV5Level.h"
#include "CATString.h"

// FeatureModelerExt 
#include "CATFmFeatureFacade.h"
#include "CATFmContainerFacade.h"
#include "CATFmAttributeValue.h"
#include "CATFmAttributeName.h"
#include "CATFmStartUpFacade.h"
#include "CATFmCredentials.h"
#include "CATFmFeatureIterator.h"
#include "CATFmFeatureModelerID.h"

// Other
#include <iostream.h>

//-------------------------------------------------------------------------
//	Include guards when the Framework is in V6 Environment
//-------------------------------------------------------------------------
#ifdef CATIAR214

// CAAFeatureModelerExt.edu Framework


#include "CAAV5V6FmExtCreateRepRef.h"     // to create the Rep ref

//CAT3DPhysicalRepInterfaces Framework
#include "CATIPsiRepresentationReference.h"  // interface on rep ref

// CATPLMIntegrationUse
#include "CATAdpSaver.h"

//ObjectModelerBase Framework
#include "CATOmbLifeCycleRootsBag.h"

//#include "CAAIFmExtBiogNovel.h"
//#include "CAAIFmExtNovel.h"
//#include "CAAIFmExtHistNovel.h"
#endif

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
#include "CATAppliContServices.h"        // CATCreateApplicativeContainer, 

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"                 // Instanciate, GetFather, GetName
#include "CATISpecAttrAccess.h"             // GetAttrKey, SetString, SetInteger,
											//    SetSpecObject, GetString,
											//    GetSpecObject, 
#include "CATISpecAttrKey.h"                // Result of GetAttrKey
#include "CATOsmSUHandler.h"
#include "CATIOsmExtendable.h"           // QueryAllExtensions
#include "CATIOsmExtension.h"            // GetID


#endif
//------------------             

//-------------------------------------------------------------------------
//                Service to import an external component 
//-------------------------------------------------------------------------
int CAAV5V6OsmIllustrateExtensions(const char *pExtensionsCatalog1Name,
									const char *pExtensionsCatalog2Name,
									const char *pFeatureCatalogName,
									const char *pDocumentStorageName)
{
    HRESULT rc;
#ifdef CATIAV5R23
		
//-------------------------------------
// Create a new CATPart document 
//-------------------------------------
	
    CATDocument *pDoc = NULL;
    rc = CATDocumentServices::New("Part",
                                  pDoc);
    if (NULL != pDoc) cout << "New document created OK" << endl << flush;
    else
	{
        cout << "ERROR in creating New document" << endl << flush;
        return 2;
	} 	

//-------------------------------------------------------------------------
// Create a new applicative container within the document for Base Feature
//-------------------------------------------------------------------------

    CATIdent idAppliCont = "CATFeatCont";
    CATIdent iContSU = NULL;

    CATUnicodeString appliContIdentifier("CAAOsmBaseFeature");
    CATBaseUnknown *pBaseFeatureAppliCont = NULL;
    rc = ::CATCreateApplicativeContainer(&pBaseFeatureAppliCont,   // appli cont created
                                         pDoc,                     // document 
                                         idAppliCont,              // type of appli cont
                                         IID_CATIContainer,        // interface type of appli cont
                                         iContSU,                  // supertype of appli cont 
                                         appliContIdentifier);     // name of appli cont
    if (SUCCEEDED(rc)) cout << "Base Feature applicative container created OK" << endl << flush;
    else
	{
        cout << "ERROR in creating Base Feature applicative container" << endl << flush;
        return 3;
	}

    // Gets a CATIContainer handle on the applicative container
    CATIContainer *piBaseFeatureAppliCont = (CATIContainer*) pBaseFeatureAppliCont;

    /*
    // Declares the container to the Undo/redo mechanism
    // only in interactive code otherwise the method return E_FAIL 
    // because, there is no undo/redo management
    
    rc = ::CATOmbPerformAfterContainerCreation( piBaseFeatureAppliCont );
    if ( FAILED(rc) )
    {
       cout <<" Error in declaring the container to the Undo/redo mechanism" << endl;
       return 1 ;
    }
    */

//-------------------------------------------------------------------------------------
// Create a new applicative container within the document for first catalog extensions
//-------------------------------------------------------------------------------------

    appliContIdentifier = "CAAOsmApplication1";
    CATBaseUnknown *pFirstExtAppliCont = NULL;
    rc = ::CATCreateApplicativeContainer(&pFirstExtAppliCont,      // appli cont created
                                         pDoc,                     // document 
                                         idAppliCont,              // type of appli cont
                                         IID_CATIContainer,        // interface type of appli cont
                                         "",                       // supertype of appli cont 
                                         appliContIdentifier);     // name of appli cont
    if (SUCCEEDED(rc)) cout << "First extension applicative container created OK" << endl << flush;
    else
	{
        cout << "ERROR in creating first extension applicative container" << endl << flush;
        pBaseFeatureAppliCont -> Release();
        return 3;
	}
	
// Get a CATIContainer handle on the applicative container

    CATIContainer *piFirstExtAppliCont = (CATIContainer*) pFirstExtAppliCont;

//--------------------------------------------------------------------------------------
// Create a new applicative container within the document for second catalog extensions
//--------------------------------------------------------------------------------------

    appliContIdentifier = "CAAOsmApplication2";
    CATBaseUnknown *pSecondExtAppliCont = NULL;
    rc = ::CATCreateApplicativeContainer(&pSecondExtAppliCont,     // appli cont created
                                         pDoc,                     // document  
                                         idAppliCont,              // type of appli cont
                                         IID_CATIContainer,        // interface type of appli cont
                                         "",                       // supertype of appli cont 
                                         appliContIdentifier);     // name of appli cont
    if (SUCCEEDED(rc)) cout << "Second extension applicative container created OK" << endl << flush;
    else
	{
        cout << "ERROR in creating second extension applicative container" << endl << flush;
        pBaseFeatureAppliCont -> Release();
        pFirstExtAppliCont -> Release();
        return 3;
	}
	
// Get a CATIContainer handle on the applicative container

    CATIContainer *piSecondExtAppliCont = (CATIContainer*) pSecondExtAppliCont;

	//--------------------------------------------------------------------------------------------------
// 1- Build Credentials to access features in the catalog CAAOsmCatalogSU, CAAOsmExt1Catalog, CAAOsmExt2Catalog
//--------------------------------------------------------------------------------------------------

	CATFmCredentials MyCredential;
	rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
    rc = MyCredential.RegisterAsCatalogOwner("CAAOsmCatalogSU","CAAOsmClientId");
	if (FAILED(rc)) return 1;
	rc = MyCredential.RegisterAsCatalogOwner("CAAOsmExt1Catalog","CAAOsmClientId1");
	if (FAILED(rc)) return 1;
	rc = MyCredential.RegisterAsCatalogOwner("CAAOsmExt2Catalog","CAAOsmClientId2");
	if (FAILED(rc)) return 1;
	cout << "   Success in creating the credentials" << endl ;
		//Create container facade to work with
	CATFmContainerFacade MyContFacade(MyCredential,piBaseFeatureAppliCont);

#endif

#ifdef CATIAR214

//--------------------------------------------------------------------------------------------------
// 1- Build Credentials to access features in the catalog CAAOsmCatalogSU, CAAOsmExt1Catalog, CAAOsmExt2Catalog
//--------------------------------------------------------------------------------------------------

	CATFmCredentials MyCredential;
	rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
    rc = MyCredential.RegisterAsCatalogOwner("CAAOsmCatalogSU","CAAOsmClientId");
	if (FAILED(rc)) return 1;
	rc = MyCredential.RegisterAsCatalogOwner("CAAOsmExt1Catalog","CAAOsmClientId1");
	if (FAILED(rc)) return 1;
	rc = MyCredential.RegisterAsCatalogOwner("CAAOsmExt2Catalog","CAAOsmClientId2");
	if (FAILED(rc)) return 1;
	cout << "   Success in creating the credentials" << endl ;

//-----------------------------------------------------
// 2- Create a new Product representation reference 
//-----------------------------------------------------

	CATUnicodeString NameAndTypeofContainer = "CAAFmExtBaseFeatureCont" ;
	CATIPsiRepresentationReference * pPsiCreatedRepRef= NULL;
	CATBaseUnknown * pContainer = NULL ;
	CATString EnvToUse;
	CATString Repository;
	rc = ::CAAV5V6FmExtCreateRepRef(MyCredential, EnvToUse,Repository,NameAndTypeofContainer,NameAndTypeofContainer,
		                        IID_CATIPsiRepresentationReference,(void**) &pPsiCreatedRepRef, &pContainer);
	if (FAILED(rc) || (NULL==pPsiCreatedRepRef) || (NULL==pContainer) ) return 1;
	cout <<"   The Product Representation Reference is created" << endl;

	// Insert component that is loaded in session, in BAG
	CATOmbLifeCycleRootsBag Bag;
	Bag.InsertRoot(pPsiCreatedRepRef);

	//Create container facade to work with
	CATFmContainerFacade MyContFacade(MyCredential,pContainer);

    pPsiCreatedRepRef->Release();
	pPsiCreatedRepRef = NULL;

#endif
//-------------------------------------------------------------------------------
// 4- Instantiate CAAOsmNovel StartUp from the Base Feature Catalog (within CAAFmExtBaseFeatureCont container)
//	  Credential set allows the base feature creation ( base feature catalog)
//-------------------------------------------------------------------------------
	// 4-1- Instantiate a StartUp Facade for "CAAOsmNovel"
	CATUnicodeString MyStartUpType("`CAAOsmNovel`@`CAAOsmCatalogSU.CATfct`");
	CATFmStartUpFacade MyStartUpFacade(MyCredential,MyStartUpType);

	// 4-2- Instantiate "CAAOsmNovel" (base feature)
	CATFmFeatureFacade FeatFacadeOnNovelInstBaseFeat(MyCredential);
	rc = MyStartUpFacade.InstantiateIn(MyContFacade,FeatFacadeOnNovelInstBaseFeat);
	if (FAILED(rc)) return 1;
		
	cout << "   Success in instantiating CAAOsmNovel"<<endl;

//---------------------------------------------------------------------------------------------------------
// 5- Add feature extensions to Novel feature
//	  Credential set allows the features extension creation (the feature extension catalogs)
//---------------------------------------------------------------------------------------------------------
	// 5-1- Instantiate the Historical Novel Extension
	CATString strHistoricExtNovel("`CAAOsmHistoricalNovel`@`CAAOsmExt1Catalog.CATfct`");
	CATFmAttributeValue attrValue;
	rc =  FeatFacadeOnNovelInstBaseFeat.AddExtension(strHistoricExtNovel,attrValue);
	if (FAILED(rc)) return 0;
	cout << "   AddExtension for " << strHistoricExtNovel.CastToCharPtr() << " OK" << endl;
    CATFmFeatureFacade FeatFacadeOnHistNovelExtn(MyCredential,attrValue);

	// 5-2- Instantiate the Biographical Novel Extension
	CATString strBiographicalExtNovel("`CAAOsmBiographicalNovel`@`CAAOsmExt1Catalog.CATfct`");
	rc =  FeatFacadeOnNovelInstBaseFeat.AddExtension(strBiographicalExtNovel,attrValue);
	if (FAILED(rc)) return 1;
	cout << "   AddExtension for " << strBiographicalExtNovel.CastToCharPtr() << " OK" << endl;
    CATFmFeatureFacade FeatFacadeOnBiogNovelExtn(MyCredential,attrValue);
	
	// 5-3- Instantiate the Childrens Novel Extension
	CATString strChildrensExtNovel("CAAOsmChildrensNovel");
	rc =  FeatFacadeOnNovelInstBaseFeat.AddExtension(strChildrensExtNovel,attrValue);
	if (FAILED(rc)) return 1;
	cout << "   AddExtension for " << strChildrensExtNovel.CastToCharPtr() << " OK" << endl;
    CATFmFeatureFacade FeatFacadeOnChildrensNovelExtn(MyCredential,attrValue);

//---------------------------------------------------------------------------------------
// 6- Retrieve the Childrens Novel extension
//    The credential set allows to retrieve an extension (only base is possible, with the extension catalog it is good too)
//---------------------------------------------------------------------------------------
	rc = FeatFacadeOnNovelInstBaseFeat.GetExtension(strChildrensExtNovel, attrValue);
	if (FAILED(rc) ) return 1;
	cout << "   OK: the chidrens novel extension is retrieved." << endl << flush;
    CATFmFeatureFacade FeatFacadeOnChildrenNovelExt(MyCredential,attrValue);

    CATString IdExt;
    rc = FeatFacadeOnChildrenNovelExt.GetExtensionId(IdExt);
	if (FAILED(rc) ) return 1;

	if ( strcmp(IdExt.CastToCharPtr(),strChildrensExtNovel.CastToCharPtr()  )) return 1 ;

	cout << "   OK: Its identifier is " << IdExt.CastToCharPtr()  << endl << flush;

	CATFmAttributeName AgeGroupAsName("AgeGroup");
	CATFmAttributeValue AgeGroupAsValue ;
    rc = FeatFacadeOnChildrenNovelExt.GetValue(AgeGroupAsName,AgeGroupAsValue);
	if (FAILED(rc)) return 1;
	int AgeGroup = 0 ;
	AgeGroupAsValue.GetInteger(AgeGroup);
   
    cout << "   AgeGroup = " << AgeGroup << endl << flush;

//-------------------------------------------------------------------------
// 7-  Retrieve the Biographical Novel extension
//-------------------------------------------------------------------------
	// 7-1- Retrieve the BiographicalNovel extension from the Novel feature (base)
	CATString iExtIdForBiogNovel("CAAOsmBiographicalNovel");
	rc = FeatFacadeOnNovelInstBaseFeat.GetExtension(iExtIdForBiogNovel,attrValue);
	if (FAILED(rc)) return 1;
	cout << "   OK: the biographical novel extension is retrieved." << endl << flush;
    CATFmFeatureFacade FeatFacadeOnBiogNovelExt;
    FeatFacadeOnBiogNovelExt = attrValue;

	//7-2- Retrieve the ExtensionID of BiographicalNovel extension
    rc = FeatFacadeOnBiogNovelExtn.GetExtensionId(IdExt);
	if (FAILED(rc) ) return 1;

	if ( strcmp(IdExt.CastToCharPtr(),iExtIdForBiogNovel.CastToCharPtr()  )) return 1 ;
	cout << "   OK: Its identifier is " << IdExt.CastToCharPtr()  << endl << flush;

	//7-3- Retrieve the "Epoch" attribute and display its default value
	CATFmAttributeName EpochAttr("Epoch");
	CATFmAttributeValue EpochAsValue ;
    rc = FeatFacadeOnBiogNovelExtn.GetValue(EpochAttr,EpochAsValue);
	if (FAILED(rc)) return 1;
	CATUnicodeString EpochName = NULL ;
	EpochAsValue.GetString(EpochName);
    cout << "   Epoch = " << EpochName.CastToCharPtr() << endl << flush;

	//7-4- Change the value of the "Epoch" attribute and display
	EpochName = "Bolt";
	EpochAsValue.SetString(EpochName);
    cout << "   Epoch = " << EpochName.CastToCharPtr() << endl << flush;

	//7-5- Retrieve the "Domain" attribute and display its default value
	CATFmAttributeName DomainAttr("Domain");
	CATFmAttributeValue DomainAsValue ;
    rc = FeatFacadeOnBiogNovelExtn.GetValue(DomainAttr,DomainAsValue);
	if (FAILED(rc)) return 1;
	CATUnicodeString DomainName = NULL ;
	DomainAsValue.GetString(DomainName);
    cout << "   Domain = " << DomainName.CastToCharPtr() << endl << flush;

	//7-6- Change the value of the "Domain" attribute and display
	DomainName = "Sports" ;
	DomainAsValue.SetString(DomainName);
    cout << "   Domain = " << DomainName.CastToCharPtr() << endl << flush;

//-------------------------------------------------------------------------
// 8-  Retrieve the base feature  
//     The credential set must contain the extension catalog - you introspect a feature
//-------------------------------------------------------------------------
   //8-1 Bad credential
   CATFmAttributeValue TheBaseFeatureAsValue ; 
   rc = FeatFacadeOnBiogNovelExt.GetBaseFeature(TheBaseFeatureAsValue);
   if ( SUCCEEDED(rc) ) return 1 ;
   cout << "   OK, you cannot get the base feature without the right credential " << endl ;

   //8-2 Good credential
   TheBaseFeatureAsValue.Clear();
   rc = FeatFacadeOnChildrenNovelExt.GetBaseFeature(TheBaseFeatureAsValue);
   if ( FAILED(rc) ) return 1 ;
   cout << "   OK, you can get the base feature with the right credential " << endl ;

   //8-3 Check result
   CATBaseUnknown_var MyBaseFeatureAsFeature = TheBaseFeatureAsValue.GetFeature() ;
   if ( NULL_var == MyBaseFeatureAsFeature  ) return 1 ;

//---------------------------------------------------------------------------------------------------
// 9- Scan extensions of the base feature inside the Applicative Container "CAAFmExtApplication1" 
//    as owner of the base feature you got all extensions, otherwise only those authorized by credentials
//---------------------------------------------------------------------------------------------------
	CATFmFeatureIterator oExtensionsIterator;
	CATString CAAFmExtApplication1ID ("CAAOsmApplication1");
	rc =  FeatFacadeOnNovelInstBaseFeat.ScanExtensionsInContainer(CAAFmExtApplication1ID,oExtensionsIterator);
	if (FAILED(rc)) return 1;
	
	cout << "   Success in retrieving an iterator on the feature extensions in the Applicative Container CAAOsmApplication1" << endl;

	int iCountOfExtns = 0;
	CATFmFeatureFacade FeatFacadeOnExtn(MyCredential);
	rc =  oExtensionsIterator.Next(FeatFacadeOnExtn);
	while (SUCCEEDED(rc))
	{
		CATUnicodeString oDisplayName;
		rc = FeatFacadeOnExtn.GetDisplayName(oDisplayName);
		if ( SUCCEEDED(rc) )
		{
		   cout << "   Extension = " << oDisplayName.ConvertToChar() << endl << flush;
		   iCountOfExtns++;
		   rc = oExtensionsIterator.Next(FeatFacadeOnExtn);
		}
	}

	if (2 != iCountOfExtns) return 1;
		
	cout << "   Initial Count of feature extensions in the Appli Cont CAAOsmApplication1 is " << iCountOfExtns << endl;
//	
////-------------------------------------------------------------------------------------------
//// 10- Remove  extensions, contained within the "CAAFmExtApplication1" applicative container
////		rule : As owner of the base feature you can delete all its extension, otherwise you will delete only
////      those for which you are granted.
////      here the credential set allows base feature use.
////-------------------------------------------------------------------------------------------
	CATFmFeatureIterator ListExtensionToDelete;
	rc = FeatFacadeOnNovelInstBaseFeat.ScanExtensionsInContainer(CAAFmExtApplication1ID,ListExtensionToDelete);
	if (FAILED(rc)) return 1;
	cout <<"   We got the Feature iterator " << endl;
	CATFmFeatureFacade FeatFacadeOnExtensionToDelete;  
	while ( SUCCEEDED(rc) && SUCCEEDED(ListExtensionToDelete.Next(FeatFacadeOnExtensionToDelete)) )
	{
	   // You have the right to delete all ext of Basefeat since FeatFacadeOnNovelInstBaseFeat
	   // contains the right to access the base feature. so FeatFacadeOnExtensionToDelete can be without credentials
	   //
       rc = FeatFacadeOnNovelInstBaseFeat.RemoveExtension(FeatFacadeOnExtensionToDelete.GetFeatureAsValue());
	}
	if (FAILED(rc)) return 1;
	cout << "   Success in removing all extensions within the CAAOsmApplication1 container" << endl;
//
////-------------------------------------------------------------------------------------------
//// 11- Scan extensions of the base feature whatever the applicative container
////    as owner of the base feature you got all extensions, otherwise only those authorized by credentials
////    here only those extensions contained within the "CAAFmExtApplication2" applicative container remain (count 1)
////-------------------------------------------------------------------------------------------
	CATFmFeatureIterator oExtensionsIterator1;
	rc =  FeatFacadeOnNovelInstBaseFeat.ScanExtensions(oExtensionsIterator1);
	if (FAILED(rc)) return 1;
		
	cout << "   Success in retrieving all feature extensions" << endl;

	iCountOfExtns = 0;
	CATFmFeatureFacade FeatFacadeOnExtn1 (MyCredential);
	rc =  oExtensionsIterator1.Next(FeatFacadeOnExtn1);
	while (SUCCEEDED(rc))
	{
		CATUnicodeString oDisplayName1;
		rc = FeatFacadeOnExtn1.GetDisplayName(oDisplayName1);
		if ( SUCCEEDED(rc) )
		{
		   cout << "   Extension = " << oDisplayName1.ConvertToChar() << endl << flush;
		   iCountOfExtns++;
		   rc = oExtensionsIterator1.Next(FeatFacadeOnExtn1);
		}
	}
	
	if (1 != iCountOfExtns) return 1;
		
	cout << "   Final Count of feature extensions, as expected is " << iCountOfExtns << endl;

#ifdef CATIAR214
//---------------------------------------------------------------------
// 12- Saves in repository
//---------------------------------------------------------------------
	CATAdpSaver saver;
    rc = saver.Save();
	if ( FAILED(rc)  ) return 1;
		

	pContainer->Release() ;
	pContainer = NULL ;
	
	cout <<"   Save is successful " << endl;

	return 0; 
#endif

#ifdef CATIAV5R23
/*--------------------------------------------------------------------------*/
/*  Save and remove the document and end the session when in V5 environment */
/*--------------------------------------------------------------------------*/

		// @CSC-Filter UNER 
		rc = CATDocumentServices::SaveAs(*pDoc,
			"CAAOsmExt1Catalog.CATfct");
		if (FAILED(rc))
		{
			cout << "ERROR in saving document" << endl << flush;
			return 9;
		}
		return 0; 
#endif

}
