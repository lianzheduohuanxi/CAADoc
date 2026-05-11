// COPYRIGHT DASSAULT SYSTEMES 2009
//===============================================
// Abstract of Use Case "CAAV5V6OsmAppliCont" 
// ----------------------------------------------
//
//	This sample illustrates how to work with applicative container:
//     - creating, retrieving, scanning an applicative container 
//
//  If the use case makes instantiation inside this applicative container, 
//  to have something to retrieve, it is not the crux of this use case. 
//   
//
//=============================================================================
//  Steps :
//
//   1- Checks Arguments
//   2- Initializes the PLM session
//   3- Builds Client accreditations 
//   4- Creates a Product Representation Reference (Techno Rep)
//   6- Retrieves the applicative container associated to this Techno Rep.  
//		6-1- Retrieve the Applicative Container by its name  
//		6-2- Create a Facade to this Applicative Container
//   7- Instantiates "Novel" feature
//		7-1- Creates a Facade to the CAAOsmNovel StartUp
//		7-2- Instantiates "Novel" from its StartUp
//   8- Instantiates a "Chapter" feature, and aggregates it under the "Novel" instance
//		8-1- Creates a Facade on the CAAOsmChapter StartUp
//		8-2- Creates a key to the Novel attribute, NovelChapter , a list of "component" 
//		8-3- Instantiate the Chapter. (The new Instance is appended to the list of Components under the Novel)
//   9- Retrieves all features existing inside the applicative container (according to my accreditation)
//		9-1- Retrieves only the Root features contained within, meaning only Novel (aggregating)
//		9-2- Retrieves all features contained within, meaning Novel (aggregating) and Chapters (aggregated)
//  10- Check IsValid and Clear methods
//  11- Saves the Session
//  12- Closes the Session
//
//=============================================================================
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAV5V6OsmAppliCont CatalogName DocumentStorageName" 
//  where the "CatalogName" is the name and .CATfct extension (without the path) of the
//     catalog found under the
//     "Ws" + "Os" + resources + graphic directory, and
//  where the "DocumentStorageName" is the entire pathname, name and .CATPart extension
//    under which the new document is to be stored. 
// 
//=============================================================================
//***********************
//Note: The code written outside the #ifdef is the common code which is compatible in V5 as
//		well as V6 environment. It is the illustration of V5 scenario of the 
//		CAAOsmAppliCont usecase using V6 APIs.
//***********************


// System Framework
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"
#include "CATIAV5Level.h"

//FeatureModelerExt Framework
#include "CATFmFeatureFacade.h"
#include "CATFmContainerFacade.h"
#include "CATFmStartUpFacade.h"
#include "CATFmCredentials.h"
#include "CATFmAttributeName.h"
#include "CATFmAttributeValue.h"
#include "CATFmFeatureModelerID.h"
#include "CATFmFeatureIterator.h"
// Other
#include <iostream.h>
#include "CATString.h"
#include "CATIAV5Level.h"

//-------------------------------------------------------------------------
//	Include guards when the Framework is in V6 Environment
//-------------------------------------------------------------------------

#ifdef CATIAR214
//local Framework
#include "CAAV5V6FmExtCreateRepRef.h"     // to create the Rep ref

//ObjectModelerBase Framework
#include "CATOmbLifeCycleRootsBag.h"

//CATPLMComponentInterfaces Framework
#include "CATIPLMNavRepReference.h"

// CATPLMIntegrationUse
#include "CATAdpSaver.h"

// CAAPLMClientAdapter.edu Framework
#include "CAAAdpCreateCloseSession.h"
#include "CATSysBoolean.h"

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

#ifdef CATIAR214
//---------------------
// 1- Checks arguments
//---------------------
  if (7 != iArgc )
  {
    cout << endl;
    cout << "Usage: CAAV5V6OsmAppliCont <Repository> <Server> <User> <Password> <SecurityCtx> <Environment>" ;
    cout <<endl;
    return 1;
  }
  cout << "The CAAV5V6OsmAppliCont main program begins ...."<< endl << endl;
  
//------------------------------------------------------------------
//2 - Initializes the PLM session 
//------------------------------------------------------------------
  HRESULT rc = ::CAAAdpCreateSession(iArgv[1], iArgv[2], iArgv[3], iArgv[4],iArgv[5]);
  if (FAILED(rc))	 return 1;   
    
  cout << "   PLM session initialized with the following connection parameters" << endl;
  cout << "      Repository=" << iArgv[1] << endl;
  cout << "      Server="     << iArgv[2] << endl;
  cout << "      UserID="     << iArgv[3] << endl;
  cout << "      UserPasswd=" << iArgv[4] << endl;
  cout << "      SecurityCtx="<< iArgv[5] << endl;

//-------------------------------------------------------------------------------
// 3- Build Client accreditations : who I am ?
//-------------------------------------------------------------------------------

  CATFmCredentials MyCredential;
  rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
  if (FAILED(rc)) return 1;
    rc = MyCredential.RegisterAsCatalogOwner("CAAOsmCatalogSU","CAAOsmClientId");
  if (FAILED(rc)) return 1;
  cout << "   Success in creating the credentials for CAAV5V6OsmAppliCont in V6" << endl;

//-----------------------------------------------------------
// 4- Creates a Product Representation Reference (Techno Rep)
//-----------------------------------------------------------
  CATString EnvToUse = iArgv[6];
  CATString Repository = iArgv[1];
  CATIPLMNavRepReference * pNavRepRefOnCreatedRepRef= NULL;
  CATUnicodeString NameofContainer = "CAAFmExtAppliCont" ;
  CATUnicodeString TypeofContainer = "CAAFmExtAppliCont" ;
  CATBaseUnknown * pContainer = NULL ;
  rc = ::CAAV5V6FmExtCreateRepRef(MyCredential,EnvToUse,Repository,TypeofContainer,NameofContainer,
             IID_CATIPLMNavRepReference,(void**) &pNavRepRefOnCreatedRepRef, &pContainer);
  if (FAILED(rc) || (NULL==pNavRepRefOnCreatedRepRef) || (NULL==pContainer) ) return 1;
  cout <<"   The Product Representation Reference is created" << endl;

  // Insert component that is loaded in session, in BAG
  CATOmbLifeCycleRootsBag Bag;
  Bag.InsertRoot(pNavRepRefOnCreatedRepRef);

    //Useless 
  pContainer->Release();
  pContainer = NULL ;

//-------------------------------------------------------------------------------------
// 5- Retrieves the applicative container from this Techno Rep.
//-------------------------------------------------------------------------------------
  // 6-1- Retrieve the Applicative Container
  CATBaseUnknown * piApplicativeContainer = NULL ;
  rc = pNavRepRefOnCreatedRepRef->RetrieveApplicativeContainer(NameofContainer,
              IID_CATBaseUnknown,
              (void **)&piApplicativeContainer);
  
  if ( FAILED(rc) || (NULL == piApplicativeContainer)  ) return 1;
    
  cout << "   The applicative container has been retrieved"<< endl;
  
  pNavRepRefOnCreatedRepRef->Release();
  pNavRepRefOnCreatedRepRef = NULL ;

  // 6-2- Create a Facade to this Applicative Container
  CATFmContainerFacade MyContainerFacade(MyCredential,piApplicativeContainer);

#endif

#ifdef CATIAV5R23

  /*--------------------------------------------------------------*/
  /*1- Open a Session:  this is a necessary step in a batch program */
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
  /* 2- Create a new document for features. */
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
  /* 3- Retrieve the root container of the document. */
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
  piInitOnDoc = NULL;
  if (NULL == piRootContainer)
  {
    cout << "ERROR in GetRootContainer" << endl << flush;
    return 4;
  }
  
//-------------------------------------------------------------------------------
//  4- Build Client accreditations : who I am ?
//-------------------------------------------------------------------------------

  CATFmCredentials MyCredential;
  rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
  if (FAILED(rc)) return 1;
    rc = MyCredential.RegisterAsCatalogOwner("CAAOsmCatalogSU","CAAOsmClientId");
  if (FAILED(rc)) return 1;
  cout << "   Success in creating the credentials (in V5 env)" << endl;

//  Create a Facade to this Applicative Container
  CATFmContainerFacade MyContainerFacade(MyCredential,piRootContainer);

//Note: The above declared Credentials concept is of V6 and it has been included inside
//		the #ifdef for both environments (V5 & V6)

#endif



//--------------------------------------------------------------
// 1- Instantiates a Novel feature from its "CAAOsmNovel" StartUp
//--------------------------------------------------------------
  // 2-1- Creates a Novel StartUp Facade
  CATUnicodeString NovelStartUpType("`CAAOsmNovel`@`CAAOsmCatalogSU.CATfct`");
  CATFmStartUpFacade MyStartUpNovelFacade(MyCredential, NovelStartUpType);

  // 2-2- Instantiates a Novel Feature from its "CAAOsmNovel" StartUp
  CATFmFeatureFacade oInstanceNovelFromStartUp(MyCredential);
  rc = MyStartUpNovelFacade.InstantiateIn(MyContainerFacade,oInstanceNovelFromStartUp);
  if ( FAILED(rc) ) return 1;
    
  //2-3 Displays its external name
  CATUnicodeString NovelInstFromSUName;
  oInstanceNovelFromStartUp.GetDisplayName(NovelInstFromSUName);
    cout << "   Success in instantiating a Novel from its StartUp" << NovelInstFromSUName.ConvertToChar() << " from its CAAOsmNovel StartUp" << endl;

//---------------------------------------------------------
// 2- Instantiates a Chapter as an aggregates under the Novel
//---------------------------------------------------------
  // 2-1- Creates a Chapter StartUp Facade
  CATUnicodeString ChapterStartUpType("`CAAOsmChapter`@`CAAOsmCatalogSU.CATfct`");
  CATFmStartUpFacade MyStartUpChapterFacade(MyCredential, ChapterStartUpType);

  // 2-2- Creates a key to the Novel attribute of type list of "component"
  CATFmAttributeName MyKeyNovelChapter("NovelChapter");

  // 2-3- Instantiates a Chapter. The new Instance is appended to the list of Components under the Novel
  CATFmFeatureFacade oInstanceChapterFromStartUp(MyCredential);		
  rc = MyStartUpChapterFacade.InstantiateUnder (MyContainerFacade,oInstanceNovelFromStartUp,
                                        MyKeyNovelChapter,oInstanceChapterFromStartUp); 

  if ( FAILED(rc) ) return 1;
    
  CATUnicodeString ChptInstName;
  oInstanceChapterFromStartUp.GetDisplayName(ChptInstName);
  cout << "   Success in instantiating a Chapter from its StartUp" << ChptInstName.ConvertToChar()  << " aggregated under a Novel " 
                                               << NovelInstFromSUName.ConvertToChar()   << endl;


//---------------------------------------------------------------------------------------
// 3- Retrieves features from the Applicative Container according to your accreditations
//--------------------------------------------------------------------------------------
  // 3-1- Retrieves only the Root features,those stand alone, (not aggregated)
  //       for which you are declared as the StartUp owner.
  CATFmFeatureIterator oIteratorForRootFeats;
  rc = MyContainerFacade.ScanRootFeatures(oIteratorForRootFeats);
  if (FAILED(rc)) return 1;
    
  cout << "   Only the Root features retrieved from the Container" << endl << flush;

  int RootFeatCount = 0;
  CATFmFeatureFacade oRootFeat(MyCredential);
  rc =oIteratorForRootFeats.Next(oRootFeat);
  while(SUCCEEDED(rc))
  {
    CATUnicodeString oNameRootFeat;
    oRootFeat.GetDisplayName(oNameRootFeat);
    cout << "      The display name of root feature is " << oNameRootFeat.ConvertToChar() << endl;
    RootFeatCount++;
    rc =  oIteratorForRootFeats.Next(oRootFeat);
  }

  cout << "   Number of root members (from CAAOsmCatalogSU) in applicative container are: " << RootFeatCount << endl << flush;

  // 3-2- Retrieves all the features according  for which you are declared as the StartUp owner.
  //      
  CATFmFeatureIterator oIteratorOnAllFeats;
  rc = MyContainerFacade.ScanFeatures(oIteratorOnAllFeats);
  if (FAILED(rc)) return 1;
    
  cout << "   All features retrieved from the Container" << endl << flush;

  int featcount = 0;
  CATFmFeatureFacade oFeat(MyCredential);;
  rc =  oIteratorOnAllFeats.Next(oFeat);
  while(SUCCEEDED(rc))
  {
    CATUnicodeString oNameFeat;
    oFeat.GetDisplayName(oNameFeat);
    cout << "      The display name of feature is " << oNameFeat.ConvertToChar() << endl;
    featcount++;
    rc =  oIteratorOnAllFeats.Next(oFeat);
  }

  cout << "   Total members (from CAAOsmCatalogSU) in applicative container are: " << featcount << endl << flush;

  
//---------------------------------------------------------------------
//4- Check Isvalid and clear
//---------------------------------------------------------------------
  CATBoolean IsValidContainer = MyContainerFacade.IsValid();
  if ( FALSE == IsValidContainer ) return 1;
    
  cout <<"   A container is bound to the container facade " << endl;

  MyContainerFacade.Clear();

  IsValidContainer = MyContainerFacade.IsValid();
  if ( TRUE == IsValidContainer ) return 1;

  cout <<"   After a Clear, the container facade is unbound" << endl;



#ifdef CATIAR214

// release the pointer on the container
  piApplicativeContainer -> Release();
  piApplicativeContainer = NULL;
//---------------------------------------------------------------------
//- Saves the Session
//---------------------------------------------------------------------
  CATAdpSaver saver;
    rc = saver.Save();
  if ( FAILED(rc)  ) return 1;
    
  cout <<"   Save is successful " << endl;

    // Unload components from session
  Bag.RemoveAll();

//------------------------------------------------------------------
//- Closes the session
//------------------------------------------------------------------
  rc = ::CAAAdpCloseSession();
  if (FAILED(rc) ) return 1;
    
  cout <<"   Close is successful " << endl;
  cout << endl << "The CAAV5V6OsmAppliCont main program ends ...."<< endl << endl;
  
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
