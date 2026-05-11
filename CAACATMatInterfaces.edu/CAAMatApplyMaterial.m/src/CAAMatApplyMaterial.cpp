// COPYRIGHT DASSAULT SYSTEMES 2017
//==========================================================================
//
//	Abstract: This sample shows how to apply a material on a part. 
//
//  Steps :
//    1.   Opens the section 
//    2.   Opens the part document
//    3.   Retrieves the part in the document
//    4.   Opens a material document
//    5.   Retrieves a material to apply to the part
//    5.1. Retrieves the library of families 
//    5.2. Retrieves the first family 
//    5.3. Retrieves the last material in this family
//    6.   Retrieves the material support of the part
//    7.   Applies the material with a link
//    8.   Saves ias the part document which contains only a link on the material
//             -> after the mkrun, open this new document in a CATIA session
//    9.   Applies the material in including it in the part document
//    10.  Saves as the part document which contains inside the material
//             -> after the mkrun, open this new document in a CATIA session
//    11.  Closes document ( Part and Material )
//    12.  Closes the session
//
//
//==========================================================================
// How to execute :
// 
//  CAAMatApplyMaterial Filename InputPath OutPutPath
//
//   with : Filename    : Filename of the part without its suffix CATPart
//          InputPath   : Path where is the Part
//          OutPutPath  : Path to save Parts with the material (embedded and linked)
//         
//
// Example :
//  CAAMatApplyMaterial filename e:\CAA2WS\tmpin\ e:\CAA2WS\tmppout\ 
//
//   The part e:\CAA2WS\tmp\filename.CATPart will be saved in 2 parts:
//   e:\CAA2WS\tmp\filenameWithMatEmbedded.CATPart with a material embedded
//   e:\CAA2WS\tmp\filenameWithMatLinked.CATPart with a material linked
//
//   in CAACATMatInterfaces.edu/CNext/resources/graphic there is the CATSamplePart
//   document.
//
// Return code :
//   0 successful execution
//   1 execution failed
// 
//==========================================================================

//ObjectModelerBase Framework
#include "CATSessionServices.h"          // Create_Session and Delete_Session
#include "CATDocumentServices.h"         // Open, Save 
#include "CATInit.h"                     // To retrieve the root container
#include "CATDocument.h"

//MecModInterfaces Framework
#include "CATIPrtContainer.h"            // The root container 

//ObjectSpecsModeler Framework
#include "CATISpecObject.h"              // To get the part 

// Material Framework
#include "CATMaterialServices.h"         // To apply the material

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
  if (4 != iArgc) 
  {
	  cout << endl;
	  cout << "CAAMatApplyMaterial Part InputPart OutputPart"<< endl;
      cout << "with : Filename    : Filename of the part document without its suffix CATPart "<< endl;
      cout <<"        InputPath   : Directory where is the part document"<< endl;
      cout <<"        OutPutPath  : Directory to save the two part documents with the material "<<endl;
	  cout <<"                      one contains the material inside, and the second has only a link "<< endl ;
	  cout << endl;
	  return 1;
  }

  cout << "The CAAMatApplyMaterial main program begins ..."<< endl << endl;

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

  //-----------------------------------------------------------------------
  //2- Opens the document given in argument of this main
  //-----------------------------------------------------------------------

  CATDocument *pPartDocument = NULL;
  CATString s2 = iArgv[2] ;
  CATString s1 = iArgv[1] ;
  CATString s3 = s2 + Slash + s1 + ".CATPart";
  const char * NamePart = s3.ConvertToChar();
  rc = CATDocumentServices::OpenDocument(NamePart, pPartDocument);
		                           
  if (SUCCEEDED(rc) )
  {
	  cout << "Document "<< NamePart <<" opened OK" << endl ;
  }
  else
  {
      cout << "ERROR in opening the document= "<< NamePart << endl ;
	  return 1;
  }

  //---------------------------------------------------
  // 3- Retrieves the Part of the document
  //---------------------------------------------------
  CATInit *pInit = NULL ;
  rc = pPartDocument->QueryInterface(IID_CATInit,(void **) &pInit);
  if ( FAILED(rc) )
  {
	  cout << "Pb with the CATInit interface"<< endl;
	  return 1 ;
  }

  CATIPrtContainer *pIPrtCont = NULL ;
  pIPrtCont = (CATIPrtContainer*) pInit->GetRootContainer("CATIPrtContainer");

  if ( NULL == pIPrtCont )
  {
	  cout << "The root container is NULL"<< endl;
	  return 1 ;
  }

  // No more need of this interface
  pInit->Release();
  pInit = NULL ;

  CATISpecObject_var spPart = pIPrtCont->GetPart();

  if ( NULL_var == spPart )
  {
	  cout << "The part is NULL"<< endl;
	  return 1 ;
  }

  // No more need of this interface
  pIPrtCont->Release();
  pIPrtCont = NULL ;
  

  //---------------------------------------------------
  // 4- Retrieves a material document
  //    two possiblities :
  //       a) Open a CATMaterial document (Not the case here )
  //       b) Retrieves (and implicitly opens) the sample 
  //          material document.By default this document
  //          is set in the CATStartupPath environment variable
  //          but thanks to Tools Options/Infrastructure/Material Library 
  //          you can concatenate an another path.
  //          
  //---------------------------------------------------

  CATDocument * pMaterialDocument = ::GetCurrentMaterialCatalog();
  CATIMaterialDocument *pIMaterialDoc = NULL ;
  if (pMaterialDocument)
  {
    rc = pMaterialDocument->QueryInterface(IID_CATIMaterialDocument,(void **) &pIMaterialDoc);
    if ( FAILED(rc) )
    {
	    cout << "No material document"<< endl << endl;
	    return 1;
    }
  }
  else
  {
    cout << "No material catalog"<< endl << endl;
    return 1;
  }

  //---------------------------------------------------
  // 5- Retrieves the material to apply to the part
  //---------------------------------------------------

  //---------------------------------------------------
  // 5-1 Retrieves the library of families 
  //---------------------------------------------------
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
  
  // Prints the count of material's family in the library
  int NbFamily = pILibraryFeature->GetFamilyCount();
  cout << "The count of family is="<< NbFamily << endl ;

  if ( 0 == NbFamily )
  {
	  // This case must be impossible, because there is
	  // always at least one family in the library.
	  cout << "There is no family in this catalog"<< endl;
	  return 1 ;
  }

  //---------------------------------------------------
  // 5-2 Retrieves the first family 
  //---------------------------------------------------

  CATIFamilyFeature * pIFamilyFeature = NULL ;
  pIFamilyFeature = pILibraryFeature->GetFamily(1);

  if ( NULL == pIFamilyFeature )
  {
     cout << " The library has no family" << endl ;
     return 1 ;
  }

  //No more need of the library feature
  pILibraryFeature->Release();
  pILibraryFeature = NULL ;

  //Prints the name of the first family
  CATUnicodeString NameOfTheFamily ;
  NameOfTheFamily = pIFamilyFeature->GetLabel() ;
  cout << "The name of the first family is ="<< NameOfTheFamily.ConvertToChar() << endl;

  //Prints the count of material is this family
  int NbMaterial = pIFamilyFeature->GetMaterialCount();
  cout << "The count of material is="<< NbMaterial << endl ;

  if ( 0 == NbMaterial )
  {
	  // This case can be possible 
	  // a family can be empty
	  cout << "There is no material in this catalog"<< endl;
	  return 1 ;
  }
  //---------------------------------------------------
  // 5-3 Retrieves the last material in this family
  //---------------------------------------------------

  CATIMaterialFeature * pIMaterialFeature = NULL ;
  pIMaterialFeature= pIFamilyFeature->GetMaterial(NbMaterial);

  if ( NULL == pIMaterialFeature )
  {
     cout << " The Family has no material" << endl ;
     return 1 ;
  }

  // No more need of the family feature
  pIFamilyFeature->Release();
  pIFamilyFeature = NULL ;

  //Prints the name of the last material
  CATUnicodeString NameOfTheMaterial ;
  NameOfTheMaterial = pIMaterialFeature->GetLabel() ;
  cout << "The name of the last material is =" << NameOfTheMaterial.ConvertToChar() << endl;

  //---------------------------------------------------
  // 6- Retrieves the material support of the part 
  //---------------------------------------------------
  CATIMaterialSupport * pIMaterialSupportOnPart = NULL ;
  rc = spPart->QueryInterface(IID_CATIMaterialSupport,(void**) &pIMaterialSupportOnPart);
  if ( FAILED(rc) )
  {
     cout << "Pb with the CATIMaterialSupport interface "<< endl;
	 return 1 ;
  }

  //---------------------------------------------------
  // 7- Applies the material on the part: 
  //    The document has only a link on the material
  //---------------------------------------------------
  CATBoolean ApplyWithLink = TRUE ;
  int val1 = ::ApplyMaterialOnSupport(pIMaterialFeature, pIMaterialSupportOnPart,ApplyWithLink);

  if ( 0 != val1 )
  {
	  cout << "ApplyMaterialOnSupport with link has the problem="<< val1 << endl;
	  return 1 ;
  }

  //-------------------------------------------------------------
  // 8- Saves the document which contains only a link on the material
  //-------------------------------------------------------------
  CATString s5 = iArgv[3] ;
  CATString s4 = iArgv[1] ;
  CATString s6 = s5 + Slash + s4 + "WithMatLinked.CATPart" ;
  const char * NameSave = s6.ConvertToChar();
  rc = CATDocumentServices::SaveAs (*pPartDocument,NameSave);
  if ( S_OK == rc )
  {
	  cout << "Document "<< NameSave << " is saved OK" << endl ;
  }
  else
  {
      cout << "ERROR in saving document "<< NameSave << endl ;
      return 1;
  }

  //-------------------------------------------------------------
  // 9- Applies the material on the part
  //    The material is embedded in the part document 
  //-------------------------------------------------------------
  ApplyWithLink = FALSE ;
  int val2 = ::ApplyMaterialOnSupport(pIMaterialFeature, pIMaterialSupportOnPart,ApplyWithLink);

  if ( 0 != val2 )
  {
	  cout << "ApplyMaterialOnSupport with no link has the problem ="<< val2 << endl;
	  return 1 ;
  }

  // No more need of these two interfaces
  pIMaterialFeature->Release();
  pIMaterialFeature = NULL ;
  
  pIMaterialSupportOnPart->Release();
  pIMaterialSupportOnPart = NULL ;

  //---------------------------------------------------------
  // 10- Saves the document which now contains the material inside
  //---------------------------------------------------------

  s6 = s5 + Slash + s4 + "WithMatEmbedded.CATPart" ;
  NameSave = s6.ConvertToChar();
  rc = CATDocumentServices::SaveAs (*pPartDocument,NameSave);
  if (S_OK == rc) 
  {
	  cout << "Document "<< NameSave << " is saved OK" << endl ;
  }
  else
  {
      cout << "ERROR in saving document "<< NameSave << endl ;
      return 1;
  }
  
  //---------------------------------------------------
  // 11- Closes documents
  //---------------------------------------------------
 
  // 11-1 The Part Document , explicite Open in the step 2
  rc = CATDocumentServices::Remove (*pPartDocument);
  if (SUCCEEDED(rc)) 
  {
	  cout << "Document "<< NameSave << " is closed OK" << endl ;
  }
  else
  {
      cout << "ERROR in closing document "<< NameSave << endl ;
      return 1;
  }
  pPartDocument = NULL ;

  // 11-2 The Material Document , implicite Open in the step 4
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
  // 12- Delete session
  //-------------------

  rc = ::Delete_Session(pSessionName);
  if (FAILED(rc)) 
  {
      cout << "ERROR in deleting session" << endl ;
      return 1;
  }

  cout << "The CAAMatApplyMaterial main program is endded"<< endl << endl;
	  
  return 0;
}

