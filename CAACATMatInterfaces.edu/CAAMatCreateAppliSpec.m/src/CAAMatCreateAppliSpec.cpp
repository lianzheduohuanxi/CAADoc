// COPYRIGHT DASSAULT SYSTEMES  2000
//==========================================================================
//
//  Abstract: 
//	
//  Steps :
//    1.   Opens the section 
//    2.   Opens or Creates a material document
//    3.   Retrieves a material or creates one
//    4.   Adds appicative spec to the material
//
//      4-1 Verification if the spec exist
//
//      4-2 Just for the use case, the catalog is created here
//      4-3 Just for the use case, a startup is created
//
//      4-4 Create the applicative container in the document
//      4-5 Instantiates a feature from the startup
//      4-6 Adds the new feature in the document
//
//    5.   Saves the current document 
//    6.   Closes material document 
//    7.   Closes the session
//
//
//==========================================================================
// How to execute :
// 
// First case  : mkrun CAAMatCreateAppliSpec [outputpath]
//
//   We create a new material document and this document contains a new 
//   material. We add an applicative spec to this new material.
//   The new document is saved in the outputpath directory or localy if 
//   this argument is not given
//   
// Second case :
//
//   mkrun CAAMatCreateAppliSpec Filename InputPath OutPutPath
//
//   with : Filename    Filename of the material document without its extention
//          InputPath   Path where is the material document
//          OutPutPath  Path to save a new material document
//        
//   The Inputpath/FileName.CATMaterial document is opened. We add an 
//   applicative spec to first material of the first family. (If the 
//   material document is empty we create a new material). 
//   The  current document is saved in the 
//   OutPutPath/FileNameWithNewMat.CATMaterial document. 
//
//   in CAACATMatInterfaces.edu/CNext/resources/graphic there is a material model
//
// Return code :
//   0 successful execution
//   1 execution failed
// 
//==========================================================================

//ObjectModelerBase Framework
#include "CATSessionServices.h"     // Create_Session and Delete_Session
#include "CATDocumentServices.h"    // Open, Save 
#include "CATDocument.h"
#include "CATAppliContServices.h"   // CATCreateApplicativeContainer

//ObjectSpecsModeler Framework
#include "CATISpecObject.h"
#include "CATOsmSUHandler.h"

// Material Framework
#include "CATMaterialServices.h"

// CATMatInterfaces Framework
#include "CATIMaterialDocument.h" 
#include "CATIMaterialSupport.h" 
#include "CATILibraryFeature.h" 
#include "CATIMaterialFeature.h" 
#include "CATIFamilyFeature.h"

// System Framework
#include "CATString.h"

// C++ Standard Library
#include <iostream.h>  

// To manage path names for both UNIX and Windows
#ifdef _WINDOWS_SOURCE
#define Slash     "\\"
#else
#define Slash     "/"
#endif

int main(int iArgc, char *iArgv[])        
		    
{

  //---------------------
  // 0- Checks arguments
  //---------------------
  if ( (iArgc != 1) && (4 != iArgc) && (2 != iArgc) )
  {
	  cout << "CAAMatCreateAppliSpec Material" ;
    cout << "PathOfTheMaterial PathOfTheSavedMaterial"<< endl;
	  return 1;
  }

  cout << "The CAAMatCreateAppliSpec main program begins ..."<< endl << endl;

  //------------------------------------------------------------------
  //1 - Creates Session
  // A session must always be created in a batch
  // environment.  Deleting the session at the end of the program is
  // also necessary.
  //------------------------------------------------------------------

  char * pSessionName = "CAA2_Sample_Session";
  CATSession *pSession = NULL;
  HRESULT rc = ::Create_Session(pSessionName,pSession);
		                          
  if (FAILED(rc) )
  {
    cout << "ERROR in creating session" << endl ;
    return 1;
  }

  //-----------------------------------------
  //2- Opens or Creates the material document 
  //-----------------------------------------
  CATDocument * pMaterialDocument = NULL ;

  if ( (iArgc == 1) || ( iArgc == 2) )
  {
    // Creation case
    rc = CATDocumentServices::New("CATMaterial", pMaterialDocument);
		                           
    if (SUCCEEDED(rc) )
    {
	    cout << "A new material is created"<< endl;
    }
    else
    {
      cout << "ERROR in creating a CATMaterial document"<< endl;
	    return 1;
    } 
  }
  else
  {
    // Open case
    CATString s2 = iArgv[2] ;
    CATString s1 = iArgv[1] ;
    CATString s3 = s2 + Slash + s1 + ".CATMaterial";
    const char * NameMaterial = s3.ConvertToChar();
    rc = CATDocumentServices::OpenDocument(NameMaterial, pMaterialDocument);
		                           
    if (SUCCEEDED(rc))
    { 
	    cout << "Document "<< NameMaterial <<" opened OK" << endl ;
    } 
    else
    { 
      cout << "ERROR in opening the document= "<< NameMaterial << endl ;
	    return 1;
    } 
  } 

  // Retrieves the CATIMaterialDocument interface

  CATIMaterialDocument *pIMaterialDoc = NULL ;
  rc = pMaterialDocument->QueryInterface(IID_CATIMaterialDocument,(void **) &pIMaterialDoc);
  if ( FAILED(rc) )
  {
	  cout << "No material document"<< endl << endl;
	  return 1;
  }

  //----------------------------
  // 3- Retrieves the  material 
  //-----------------------------

  // ------------------------------------------
  // We choosen a material in the first family
  // ------------------------------------------
  CATILibraryFeature  *pILibraryFeature = NULL ;
  rc = pIMaterialDoc->GetMaterialLibrary(&pILibraryFeature);

  if ( FAILED(rc) )
  {
	  cout << "Pb with the GetMaterialLibrary method "<< endl;
	  return 1 ;
  }

  // No more need of this interface pointer
  pIMaterialDoc->Release();
  pIMaterialDoc= NULL ;
  
  // There is always at least one family in a material document
  CATIFamilyFeature * pIFamilyFeature = NULL ;
  pIFamilyFeature = pILibraryFeature->GetFamily(1);

  if ( NULL == pIFamilyFeature )
  {
    cout << " Library without at least one family, it's a mistake " << endl;
    return 1 ;
  }

  //No more need of the library feature
  pILibraryFeature->Release();
  pILibraryFeature = NULL ;

  // Retrieves the first material ( if exist ) of the first family
  CATIMaterialFeature * pIMaterialFeature = NULL ;
  pIMaterialFeature = pIFamilyFeature->GetMaterial(1) ;

  if ( NULL == pIMaterialFeature )
  {
	  //------------------------------------------------------------
    // Creates the new material in the opened material document
    //------------------------------------------------------------
    CATUnicodeString MaterialName = "MyMaterial";

    int val = ::CreateNewMaterial(MaterialName,
                                  pMaterialDocument,
                                  &pIMaterialFeature);

    if ( 0 != val  )
    {
      cout << "Pb to create the material"<< val << endl;
      return 1 ;
    }
    else
    {
      cout << "Ok for the material creation"<< endl;
    }
  }

  // No more need of the family feature
  pIFamilyFeature->Release();
  pIFamilyFeature = NULL ;

  if (pIMaterialFeature == NULL)
  {
    cout << "Pb in retrieving or creating the material"<< endl;
    return 1;
  }

  //---------------------------------
  // 4- Creates a new applicative spec 
  //---------------------------------

  //---------------------------------
  // 4-1 Verification if the spec exist
  //---------------------------------
  CATUnicodeString NameApplicativeSpec = "CAASampleApplicative";
  
  CATISpecObject * pISpecObject =  NULL ;
  pISpecObject = pIMaterialFeature->GetApplicativeSpec(NameApplicativeSpec);

  if ( NULL != pISpecObject )
  {
    cout << "Pbme in the GetApplicativeSpec method"<< endl;
    return 1;
  }
  else
  {
    cout << "The Applicative spec=" << NameApplicativeSpec.ConvertToChar();
    cout << " doesn't exist" << endl; 
  }


  //-------------------------------------------------------
  // 4-2 Just for the use case, the catalog is created here
	//-------------------------------------------------------
	//BK2 : Remplacer par :
	// CATfctEditorAssistant -create-new-catalog -catalog-name CAAOsmCatalogSU -with-client-id CAAOsmClientId -into-directory $PWD/OS_directory/resouces/graphic
	// CATfctEditorAssistant -update-catalog CAAOsmCatalogSU -with-client-id CAAOsmClientId -with-osm $PWD -into-directory $PWD

  /*CATICatalog *piCatalog = NULL;
  CATUnicodeString storageName = "CatalogMaterial";
  rc = ::CreateCatalog(&storageName, &piCatalog);
		                 
  if (FAILED(rc)) 
  {
    cout << "ERROR in creating Catalog" << endl ;
    return 1;
  }
  else cout << "Catalog created OK" << endl ;	
  
  // Add a client identification to the catalog (mandatory step)
  CATUnicodeString clientId("CAAMatClientId");
  rc = piCatalog -> SetClientId(&clientId);
  if (FAILED(rc)) 
  {
    cout << "ERROR in setting ClientID" << endl ;
    return 1 ;
  }*/

	CATUnicodeString  catalogName("CatalogMaterial.CATfct");
	CATUnicodeString  clientId("CAAMatClientId");
	CATUnicodeString  mySUType("CAAMatMyMaterial");
	CATOsmSUHandler   mySUHandler(mySUType, clientId, catalogName);
	CATISpecObject_var spMySU = NULL_var;
	rc = mySUHandler.RetrieveSU(spMySU);
  if (FAILED(rc) || NULL_var == spMySU ) 
  {
    cout << "ERROR in setting RetrieveSU" << endl ;
    return 1 ;
	}
	else cout << "CAAMatMyMaterial Startup retrieveSU OK" << endl ;

	CATISpecObject *piSpecObjectOnNewStartup = NULL ;
	rc = spMySU -> QueryInterface(IID_CATISpecObject,
		(void**)&piSpecObjectOnNewStartup);
	if ( FAILED(rc) )
	{
		cout << "pb in QY on CATISpecObject"<< endl;
		return 1;
	}
	/*
  //-------------------------------------------------------
  // 4-3 Just for the use case, a startup is created
  //-------------------------------------------------------
  CATBaseUnknown *pNewStartup = NULL; 
  CATUnicodeString pubSUName("CAAMatMyMaterial");
  CATUnicodeString pubSUType("CAAMatMyMaterial");
  rc = piCatalog -> CreateSUInCatalog (&pNewStartup,
                                       &pubSUName,
                                       &pubSUType,
                                       "CATISpecObject");
  if (FAILED(rc)) 
  {
    cout << "ERROR in creating CAAMatMyMaterial StartUp" << endl ;
    return 1;
  }
  else cout << "CAAMatMyMaterial Startup created OK" << endl ;

  CATISpecObject *piSpecObjectOnNewStartup = NULL ;
  rc = pNewStartup->QueryInterface(IID_CATISpecObject,
                              (void**)&piSpecObjectOnNewStartup);
  if ( FAILED(rc) )
  {
    cout << "pb in QY on CATISpecObject"<< endl;
    return 1;
  }
  pNewStartup->Release();
  pNewStartup = NULL ;

  piCatalog->Release();
  piCatalog = NULL;
	*/
  //-------------------------------------------------------
  // 4-4 Create the applicative container in the document
  //-------------------------------------------------------
  CATIdent idAppliCont = "CATFeatCont";
  CATUnicodeString appliContIdentifier("CAAMatAppliCont");
  CATBaseUnknown *pAppliContainer = NULL;
  rc = ::CATCreateApplicativeContainer(&pAppliContainer, 
                                        pMaterialDocument,     
                                        idAppliCont,  
                                        IID_CATIContainer,      
                                        "", 
                                        appliContIdentifier);  
  if (SUCCEEDED(rc)) 
  {
    cout << "Applicative container created OK" << endl ;
  }
  else
  {
    cout << "ERROR in creating applicative container" << endl ;
    return 1;
  }

  CATIContainer *piContainerOnAppliContainer = NULL ;
  rc = pAppliContainer->QueryInterface(IID_CATIContainer,
                                  (void**)&piContainerOnAppliContainer);
  if ( FAILED(rc) )
  {
    cout << "pb in QY on CATIContainer"<< endl;
    return 1;
  }

  // Declares this new container to the Undo/Redo mechanism
  // only in interactive code otherwise the method return E_FAIL, 
  // because there is no undo/redo management in batch mode
  /*
  rc = ::CATOmbPerformAfterContainerCreation( piContainerOnAppliContainer );
  if ( FAILED(rc) )
  {
      cout <<" Error in declaring the applicative container to the Undo/Redo mechanism" << endl;
      return 1 ;
  }
  */

  pAppliContainer->Release();
  pAppliContainer = NULL ;


  //-------------------------------------------------------
  // 4-5 Instantiates the Startup to create a new feature
  //-------------------------------------------------------

  CATISpecObject *piSpecObjectOnInstance = piSpecObjectOnNewStartup -> 
		Instanciate(CATUnicodeString("CAAMatMyMaterial1"),
                            piContainerOnAppliContainer);

  if ( NULL == piSpecObjectOnInstance )
  {
    cout << "Pbme to instance"<< endl;
    return 1 ;
  }
  piSpecObjectOnNewStartup -> Release();
  piSpecObjectOnNewStartup = NULL;

  piContainerOnAppliContainer->Release();
  piContainerOnAppliContainer = NULL ;

  //-------------------------------------------------------
  // 4-6  Adds the new feature in the document
  //-------------------------------------------------------
  pIMaterialFeature->AddApplicativeSpec(NameApplicativeSpec,
                                        piSpecObjectOnInstance);

  piSpecObjectOnInstance->Release();
  piSpecObjectOnInstance= NULL ;

  CATISpecObject *pISpecObjectOnVerify = NULL ;
  pISpecObjectOnVerify = pIMaterialFeature->GetApplicativeSpec(NameApplicativeSpec);

  // No more need of the material feature
  pIMaterialFeature->Release();
  pIMaterialFeature = NULL ;

  if ( NULL == pISpecObjectOnVerify )
  {
    cout << "Pbme in the AddApplicativeSpec method"<< endl;
    return 1;
  }
  else
  {
    cout << "Now the applicative spec=" ;
    cout <<  NameApplicativeSpec.ConvertToChar();     
    cout << "  exists" << endl << endl; 
  }
  pISpecObjectOnVerify->Release();
  pISpecObjectOnVerify = NULL ;
  
  //---------------------------------
  // 5- Saves the material document 
  //---------------------------------
  CATString NameSave ;
  if ( (iArgc == 1 ) || ( iArgc == 2) )
  {
    NameSave =  "DocumentWithNewSpec.CATMaterial" ;
    if ( iArgc == 2 )
    {	 
      CATString s1 = iArgv[1] ;
      NameSave = s1 + Slash + NameSave ;
    }
  }
  else
  {
    // we save the new material in the repertory given in argument and
    // with a given name
    CATString s3 = iArgv[3] ;
    CATString s1 = iArgv[1] ;
    NameSave = s3 + Slash + s1 + "WithNewSpec.CATMaterial" ;
  }

  rc = CATDocumentServices::SaveAs (*pMaterialDocument,
                                     NameSave.ConvertToChar());
  if ( rc == S_OK ) 
  {
    cout << "Document " << NameSave.ConvertToChar() << " is saved OK" <<endl;
  }
  else
  {
    cout << "ERROR in saving document " << NameSave.ConvertToChar() << endl;
    return 1;
  }
  
  //---------------------------------------------------
  // 6- Closes documents
  //---------------------------------------------------

  rc = CATDocumentServices::Remove (*pMaterialDocument);
  if (SUCCEEDED(rc)) 
  {
	  cout << "The material document is closed " << endl ;
  }
  else
  {
    cout << "ERROR in closing material document " << endl ;
    return 1;
  }
  pMaterialDocument = NULL ;


  //-------------------
  // 7- Delete session
  //-------------------

  rc = ::Delete_Session(pSessionName);
  if (FAILED(rc)) 
  {
    cout << "ERROR in deleting session" << endl ;
    return 1;
  }

  cout << "The CAAMatCreateAppliSpec main program is endded"<< endl << endl;
	  
  return 0;
}

