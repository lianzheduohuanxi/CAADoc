//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
// System Framework
#include "CATUnicodeString.h"

//Local Framework
#include "CAAOsmIllustrateExtensions.h"    

// ObjetModelerBase Framework
#include "CATDocument.h"                 // No method used.
#include "CATDocumentServices.h"         // SaveAs and Remove.
#include "CATAppliContServices.h"        // CATCreateApplicativeContainer,                                

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"              // Instanciate
#include "CATIOsmExtendable.h"           // QueryAllExtensions
#include "CATIOsmExtension.h"            // GetID
#include "CATOsmSUHandler.h"			 // RetrieveSU, Instanciate
#include "CATBaseUnknown.h"				  // For CATIdent interface inclusion
#include "CATIContainer.h"
#include  "sequence_CATBaseUnknown_ptr.h" 

//Note : If you want to instanciate feature from a feature, then as of now you will have to use Instanciate() method of
//       CATISpecObject

// CAAObjectSpecsModeler.edu Framework
#include "CAAIBiogNovel.h"

#include "iostream.h"             

//-------------------------------------------------------------------------
//                Service to import an external component 
//-------------------------------------------------------------------------
int CAAOsmIllustrateExtensions(const char *pExtensionsCatalog1Name,
                               const char *pExtensionsCatalog2Name,
                               const char *pFeatureCatalogName,
                               const char *pDocumentStorageName)
{
    HRESULT rc;
		
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



//-------------------------------------------------------------------------------
// Retrieve CAAOsmNovel StartUp from the Base Feature Catalog and instantiate it
//-------------------------------------------------------------------------------

// Get a handler of CATOsmSUHandler on CAAOsmNovel StartUp

    CATUnicodeString CatalogName = pFeatureCatalogName;
	CATUnicodeString clientId("CAAOsmClientId");
	CATUnicodeString novelSUType("CAAOsmNovel");

	CATOsmSUHandler novelSUHandler(novelSUType, clientId, CatalogName);

// Get a CATISpecObject handle on the CAAOsmNovel StartUp

	CATISpecObject_var spNovelSU = NULL_var;
	rc = novelSUHandler.RetrieveSU(spNovelSU);

	if (SUCCEEDED(rc))
		cout << "CAAOsmNovel SU retrieved OK" << endl << flush;
    else
	{
		cout <<"ERROR in retrieveing CAAOsmNovel SU" << endl << flush;
	    piBaseFeatureAppliCont -> Release();
		return 3;
	}

// Instanciating the CAAOsmNovel StartUp

	CATUnicodeString novel1("CAAOsmNovel1");

	CATISpecObject_var spNovelInst1 = NULL_var;
	rc = novelSUHandler.Instanciate(spNovelInst1, piBaseFeatureAppliCont, novel1);
    if (SUCCEEDED(rc))
		cout << "CAAOsmNovel SU instance 1 created OK" << endl << flush;
    else
	{
		cout <<"ERROR in creating instance 1 of CAAOsmNovel SU" << endl << flush;
	    piBaseFeatureAppliCont -> Release();
		return 3;
	}

// Get a CATIOsmExtendable pointer on the CAAOsmNovel feature

    CATIOsmExtendable *piExtendableOnNovelInst1 = NULL;
    rc = spNovelInst1 -> QueryInterface(IID_CATIOsmExtendable,
                                        (void**) &piExtendableOnNovelInst1);

    if (FAILED(rc)) 
	{
        cout << "ERROR in QueryInterface on CATIOsmExtendable for CAAOsmNovel1" << endl << flush;
        return 4;
	}

//--------------------------------------------------------------------------
// CAAOsmNovel1: Add the two extensions from the first catalog in the
// corresponding applicative container 
//--------------------------------------------------------------------------

    const char *extensionName = "`CAAOsmHistoricalNovel`#2@`CAAOsmExt1Catalog.CATfct`";

    rc = piExtendableOnNovelInst1 -> AddExtension (extensionName);
    if (FAILED(rc))
    {
      cout << "ERROR in AddExtension for HistoricalNovel" << endl << flush;
      piExtendableOnNovelInst1 -> Release();
      piExtendableOnNovelInst1 = NULL;
      return 9;
    }
    else cout << "AddExtension for HistoricalNovel OK" << endl << flush;

    extensionName = "`CAAOsmBiographicalNovel`#3@`CAAOsmExt1Catalog.CATfct`";
 

    rc = piExtendableOnNovelInst1 -> AddExtension (extensionName);
    if (FAILED(rc))
    {
        cout << "ERROR in AddExtension for BiographicalNovel rc = " << rc << endl << flush;
        piExtendableOnNovelInst1 -> Release();
        piExtendableOnNovelInst1 = NULL;
        return 9;
    }
    else cout << "	AddExtension for BiographicalNovel OK" << endl << flush;

//--------------------------------------------------------------------------
// CAAOsmNovel1: Add the extension from the second catalog in the
// corresponding applicative container
//--------------------------------------------------------------------------
	
    extensionName = "`CAAOsmChildrensNovel`#2@`CAAOsmExt2Catalog.CATfct`";
     
    rc = piExtendableOnNovelInst1 -> AddExtension (extensionName);
    if (FAILED(rc))
    {
        cout << "ERROR in AddExtension for ChildrensNovel" << endl << flush;
        piExtendableOnNovelInst1 -> Release();
        piExtendableOnNovelInst1 = NULL;
        return 9;
    }
    else cout << "	AddExtension for ChildrensNovel OK" << endl << flush;

//--------------------------------------------------------------
// CAAOsmNovel1: Verify that the extension is really added
//--------------------------------------------------------------

    CATIOsmExtension *piExtensionOnChildrensNovelInst1 = NULL;
    rc = piExtendableOnNovelInst1 -> QueryExtension (extensionName,
                                                     IID_CATIOsmExtension,
                                                     (void**) &piExtensionOnChildrensNovelInst1);
    if (rc == S_OK) 
    {
        cout << "OK: the extension is loaded." << endl << flush;
        piExtensionOnChildrensNovelInst1 -> Release();
        piExtensionOnChildrensNovelInst1 = NULL;
    }
    else cout << "KO: the extension is not loaded and it should be." << endl << flush;

//------------------------------------------------------------------------------------
// CAAOsmNovel1: Get a pointer to the CAAIBiogNovel interface which is implemented on
// the CAAOsmBiographicalNovel extension. Then, retrieve the
// values of certain attributes of the extension using the interface's methods.
// Note: If you don't know the iExtensionName or the iApplicationId, you may use 
// QueryAllExtension.
//------------------------------------------------------------------------------------


    CAAIBiogNovel *piBiogNovelOnFeatExt = NULL;
    char* BiographicalNovelId = "`CAAOsmBiographicalNovel`#3@`CAAOsmExt1Catalog.CATfct`";

    rc = piExtendableOnNovelInst1 -> QueryExtension(BiographicalNovelId, IID_CAAIBiogNovel,
                                                   (void**) &piBiogNovelOnFeatExt);

    if (FAILED(rc) || ( NULL==piBiogNovelOnFeatExt) ) 
    {
        cout << "ERROR in QueryExtension on CAAIBiogNovel for CAAOsmNovel1" << endl << flush;
        if ( NULL != piBiogNovelOnFeatExt )
        {
             piBiogNovelOnFeatExt->Release(); 
             piBiogNovelOnFeatExt = NULL ;
        }
        piExtendableOnNovelInst1 -> Release();
        piExtendableOnNovelInst1 = NULL;
        
        return 5;
    }
	
    cout << "	QI on CAAIBiogNovel OK" << endl << flush;

// Get the value of the Epoch attribute of the CAAOsmBiographicalNovel extension.
    CATUnicodeString epoch("");
    rc = piBiogNovelOnFeatExt -> GetEpoch(&epoch);
    cout << "Epoch = " << epoch.ConvertToChar() << endl << flush;

// Set a new value to the Epoch attribute
    epoch = "Renaissance";
    rc = piBiogNovelOnFeatExt -> SetEpoch(epoch);
    epoch = "";
    rc = piBiogNovelOnFeatExt -> GetEpoch(&epoch);
    cout << "*** New Epoch = " << epoch.ConvertToChar() << endl << flush;

// Get the value of the Domain attribute of the CAAOsmBiographical Novel extension.
    CATUnicodeString domain("");
    rc = piBiogNovelOnFeatExt -> GetDomain(&domain);
    cout << "Domain = " << domain.ConvertToChar() << endl << flush;

// Set a new value to the Domain attribute
    domain = "Science";
    rc = piBiogNovelOnFeatExt -> SetDomain(domain);
    domain = "";
    rc = piBiogNovelOnFeatExt -> GetDomain(&domain);
    cout << "*** New Domain = " << domain.CastToCharPtr() << endl << flush;

    piBiogNovelOnFeatExt->Release();
    piBiogNovelOnFeatExt = NULL;
    
//------------------------------------------------------------------------------------
// CAAOsmNovel1: Query all extensions of the base feature and for each, get its name.
// We should have three extensions for the CAAOsmNovel1 base feature.
//------------------------------------------------------------------------------------
    CATListPtrCATBaseUnknown *paExtList = NULL;
    piExtendableOnNovelInst1 -> QueryAllExtensions (IID_CATISpecObject,
                                                    &paExtList);
    char* pExtId = NULL;

    int jj = 0;
    CATIOsmExtension *piExtensionOnBase = NULL;

    if (NULL != paExtList)
    {
	        cout << "List size = " << paExtList -> Size() << endl << flush;
	        for (jj=1; jj<=paExtList->Size(); jj++)
           {
              CATBaseUnknown * pInt = (*paExtList)[jj] ;
              if ( NULL != pInt )
              {
                 rc = pInt -> QueryInterface(IID_CATIOsmExtension,
                                               (void**) &piExtensionOnBase);
                 
                 // each non nul element of the paExtList must be released 
                 pInt -> Release();
                 pInt  = NULL ;
                 if (FAILED(rc)) 
                 {
                    cout << "ERROR in QueryInterface on CATIOsmExtension for extension in list" << endl << flush;
                    return 4;
                 }
                 piExtensionOnBase -> GetID(pExtId);
                 
                 if( NULL != pExtId) 
                 {       
                    cout << "	Extension ID = " << pExtId << endl << flush;
                    free(pExtId); pExtId = NULL; 
                 }else 
                 {
                    cout << "	ERROR in GetID " << endl << flush;
                    return 4;
                 }
                 piExtensionOnBase -> Release();
                 piExtensionOnBase = NULL;
              }
           }
	        delete paExtList;
	        paExtList = NULL;
    }
    else
    {
	     cout << "ERROR in QueryAllExtensions of the base feature" << endl << flush;
	     return 4;
    }

//-------------------------------------------------------------------------------------------
// CAAOsmNovel1: Remove all of the extensions from the "CAAOsmApplication1" application
// domain (container). Query all extensions of the base feature and for each, get its
// name.  This time, only the one extension from the "CAAOsmApplication2" application domain
// remain on the Novel1 base feature.
//-------------------------------------------------------------------------------------------

    appliContIdentifier = "CAAOsmApplication1";
    rc = piExtendableOnNovelInst1 -> RemoveApplicativeExtensions (appliContIdentifier);

    if (FAILED(rc)) 
    {
        cout << "ERROR in RemoveApplicativeExtensions on CAAIBiogNovel for CAAOsmNovel1" << endl << flush;
        piExtendableOnNovelInst1 -> Release();
        piExtendableOnNovelInst1 = NULL;
        return 10;
    }
		                            
    paExtList = NULL;
    piExtendableOnNovelInst1 -> QueryAllExtensions (IID_CATISpecObject,&paExtList);
                                                   
    piExtendableOnNovelInst1 -> Release();
    piExtendableOnNovelInst1 = NULL;

    if (NULL != paExtList)
    {
	      cout << "	List size = " << paExtList -> Size() << endl << flush;
      	for (jj=1; jj<=paExtList->Size(); jj++)
         {
           CATBaseUnknown * pInt = (*paExtList)[jj] ;
           if ( NULL !=  pInt )
           {         
		        rc = pInt -> QueryInterface(IID_CATIOsmExtension,
                                               (void**) &piExtensionOnBase);
		        pInt -> Release();
		        pInt = NULL ;
		        if (FAILED(rc)) 
              { 
                   cout << "ERROR in QueryInterface on CATIOsmExtension for extension in list" << endl << flush;
                   return 4;
              }
		        piExtensionOnBase -> GetID( pExtId );
	           
             if( NULL != pExtId) 
             { 
                cout << "	Extension ID = " << pExtId << endl << flush;
                free(pExtId); 
                pExtId = NULL; 
             }else
             {
                cout << "ERROR in GetID" << endl << flush;
                return 4;
             }


		        piExtensionOnBase -> Release();
		        piExtensionOnBase = NULL;
          }
         }
	      delete paExtList;
	      paExtList = NULL;
    }
    else
    {
	     cout << "ERROR in QueryAllExtensions of the base feature" << endl << flush;
	     return 4;
    }


/*---------------------------------------------------*/
/*  Save and remove the document and end the session */
/*---------------------------------------------------*/
    // @CSC-Filter UNER
    rc = CATDocumentServices::SaveAs (*pDoc,
                                      pDocumentStorageName);
    if (FAILED(rc))
    {
        cout << "ERROR in saving document: " << pDocumentStorageName << endl << flush;
        return 11;
    }
		
    rc = CATDocumentServices::Remove (*pDoc);
    if (FAILED(rc)) 
    {
        cout << "ERROR in removing document" << endl << flush;
        return 12;
    }
    pDoc = NULL ;

    return 0; 

}



