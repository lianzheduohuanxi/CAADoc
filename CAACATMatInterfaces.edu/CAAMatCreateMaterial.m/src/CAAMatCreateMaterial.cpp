// COPYRIGHT DASSAULT SYSTEMES  2000
//==========================================================================
//
//	Abstract: Creating new material and Setting in a material document.
//
//  Steps :
//    1.   Opens the section 
//    2.   Opens a material document
//    3.   Retrieves the library of families in this material document
//    4.   Creates two materials in the opened material document
//    5.   Retrieves the last family of the library
//    6.   Sets the material in the last family (as a replace)
//    7.   Checks the positionning 
//    8.   Sets the material in the last family (for an adding)
//    9.   Checks the positionning 
//    10.  Releases pointers
//    11.  Saves as the material document which contains new materials
//            --> After mkrun, open this new document in a CATIA Session
//    12.  Closes material document 
//    13.  Closes the session
//
//
//==========================================================================
// How to execute :
// 
// First case  : CAAMatCreateMaterial [outputpath]
//
//   We open the material document provided by DS. This document is set
//   into the directory given by the CATStartupPath environment variable or
//   into in the directory set in the Tools/Options/Infrastructure/Library Material
//   Page. 
//   We create a new material into this document and a new document is created
//   in the outputpath directory of localy if this argument is not valuated
//   
// Second case :
//
//   CAAMatCreateMaterial Filename InputPath OutPutPath
//
//   with : Filename    Filename of the material document without its extention
//          InputPath   Path where is the material document
//          OutPutPath  Path to save a new material document
//        
//   The Inputpath/FileName.CATMaterial document is saved as in the 
//   OutPutPath/FileNameWithNewMat.CATMaterial document. 
//
//
//   in CAACATMatInterfaces.edu/CNext/resources/graphic there is a material model
//
// Return code :
//   0 successful execution
//   1 execution failed
// 
//==========================================================================

//ObjectModelerBase Framework
#include "CATSessionServices.h"          // Create_Session and Delete_Session
#include "CATDocumentServices.h"         // Open, Save 
#include "CATDocument.h"

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
	  cout << "First usage:"<< endl;
	  cout << "CAAMatCreateMaterial " << endl;
	  cout << " The document DocumentWithNewMat.CATMaterial is created locally"<<endl;
	  cout << " This document contains the new material created"<< endl;
	  cout << endl << endl;
	  cout << "Second usage:"<< endl;
	  cout << "CAAMatCreateMaterial OutputPath" << endl;
	  cout << " The document DocumentWithNewMat.CATMaterial is created in the OutpuPath repertory"<<endl;
	  cout << " This document contains the new material created"<< endl;
    cout << ""<< endl;
	  cout << endl << endl;
	  cout << "third usage:"<< endl;
	  cout << "CAAMatCreateMaterial Filename InputPath OutputPath" << endl;
	  cout << "  Filename ->Is the name of a CATMaterial document (without suffix)"<<endl;
	  cout << "  InputPath-> The repertory of this material document"<<endl; 
	  cout << "  OutputPath->The repertory of the new material document"<< endl;
	  cout << "              This new document is FilenameWithNewMat.CATMaterial"<<endl;
	  cout << "              and it contains the new material created "<< endl;
    cout << ""<< endl << endl;
	  return 1;
  }

  cout << "The CAAMatCreateMaterial main program begins ..."<< endl << endl;

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

  //-------------------------------
  //2- Opens the material document 
  //-------------------------------

  CATDocument * pMaterialDocument = NULL ;

  if ( (iArgc == 1) || ( iArgc == 2) )
  {
	  // Opens the DS material document
    pMaterialDocument = ::GetCurrentMaterialCatalog();
	  if (  NULL == pMaterialDocument )
	  {
      cout << "ERROR in opening the sample document= "<< endl ;
	    return 1;
	  }
  }
  else
  {
    // Opens the user material document
    CATString s2 = iArgv[2] ;
    CATString s1 = iArgv[1] ;
    CATString s3 = s2 + Slash + s1 + ".CATMaterial";
    const char * NameMaterial = s3.ConvertToChar();
    rc = CATDocumentServices::OpenDocument(NameMaterial, pMaterialDocument);
		                           
    if (SUCCEEDED(rc) )
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

  //---------------------------------------------------------------
  // 3- Retrieves the library of families of the material document
  //---------------------------------------------------------------

  CATILibraryFeature  *pILibraryFeature = NULL ;
  rc = pIMaterialDoc->GetMaterialLibrary(&pILibraryFeature);

  if ( FAILED(rc) )
  {
	  cout << "Pb with GetMaterialLibrary method "<< endl;
	  return 1 ;
  }

  // No more need of this interface pointer
  pIMaterialDoc->Release();
  pIMaterialDoc= NULL ;

  //------------------------------------------------------------
  // 4- Creates two materials in the opened material document
  //------------------------------------------------------------
  CATUnicodeString MaterialName1 = "MyFirstCAANewMaterial";
  CATIMaterialFeature *pIMaterialFeature1 = NULL ;
  int val1 = ::CreateNewMaterial(MaterialName1,pMaterialDocument,&pIMaterialFeature1);
  
  CATUnicodeString MaterialName2 = "MySecondCAANewMaterial";
  CATIMaterialFeature *pIMaterialFeature2 = NULL ;
  int val2 = ::CreateNewMaterial(MaterialName2,pMaterialDocument,&pIMaterialFeature2);

  if ( ( 0!= val1 ) || (pIMaterialFeature1 == NULL) )
  {
    cout << "Pb to create materials first="<< val1 << endl;
    return 1 ;
  }
  if ( ( 0 != val2 )|| (pIMaterialFeature2 == NULL) )
  {
    cout << "Pb to create materials second="<< val2 << endl;
    return 1 ;
  }

  // ----------------------------------------------------
  // 5- Retrieves the last family of the library
  // ----------------------------------------------------

  int NbFamily = pILibraryFeature->GetFamilyCount();

  CATIFamilyFeature * pIFamilyFeatureOnLast = NULL ;
  pIFamilyFeatureOnLast = pILibraryFeature->GetFamily(NbFamily);

  if ( NULL == pIFamilyFeatureOnLast )
  {
    cout << " the library must containt at least one family" << endl;
    return 1 ;
  }

  // No more need of this pointer
  pILibraryFeature->Release();
  pILibraryFeature = NULL ;

  //Retrieves the name of the last family
  CATUnicodeString NameOfTheLastFamily ;
  NameOfTheLastFamily = pIFamilyFeatureOnLast->GetLabel() ;

  // Retrieves the count of material before the first set in this family
  int NbMatInLastFamilyBeforeSet = pIFamilyFeatureOnLast->GetMaterialCount() ;

  cout << "There is "<< NbMatInLastFamilyBeforeSet ;
  cout << " material in the "<< NameOfTheLastFamily.ConvertToChar();
  cout << " family before the first SetMaterial "<< endl;

  //------------------------------------------------------------------
  // 6- Sets the first material in the last family at the first position
  //    It's a replace if the last family has at least one material.
  //------------------------------------------------------------------
 
  pIFamilyFeatureOnLast->SetMaterial(pIMaterialFeature1,1);

  // No more need of this pointer
  pIMaterialFeature1->Release();
  pIMaterialFeature1 = NULL ;

  //----------------------------
  // 7- Checks the positionning
  //----------------------------
  
  // If before the SetMaterial the last family was empty, this test is not valid
  // while in this case the SetMaterial is an adding not a replace
  if ( NbMatInLastFamilyBeforeSet > 0 )
  {
    if ( NbMatInLastFamilyBeforeSet != pIFamilyFeatureOnLast->GetMaterialCount() )
	  {
	    cout << "Pb with the first SetMaterial"<< endl;
	    return 1 ;
	  }
  }

  // Verify the Name of the first material of this last family
  CATIMaterialFeature * pIMaterialFeature = pIFamilyFeatureOnLast->GetMaterial(1);
  if ( NULL == pIMaterialFeature )
  {
	  cout << "This family must contains at least one material "<<endl;
	  return 1 ;
  }

  if ( MaterialName1 != pIMaterialFeature->GetLabel() )
  {
	  cout << "The first SetMaterial is incorrect"<<endl;
	  return 1 ;
  }

  pIMaterialFeature ->Release();
  pIMaterialFeature = NULL ; 

  cout << "We have set the material "<< MaterialName1.ConvertToChar() << " in the " ;
  cout << NameOfTheLastFamily.ConvertToChar() <<"family at the first place" << endl;
  if ( NbMatInLastFamilyBeforeSet > 0 )
  {
    cout << "There is always "<< pIFamilyFeatureOnLast->GetMaterialCount() ;
  }
  else
  {
	  cout << "There is now 1 ";
  }
  cout << " material in this family "<< endl;
  

  //------------------------------------------------------------------
  // 8- Sets the second material at the end of the last family
  //    It's a new material in the family.
  //------------------------------------------------------------------

  NbMatInLastFamilyBeforeSet  = pIFamilyFeatureOnLast->GetMaterialCount() ;

  pIFamilyFeatureOnLast->SetMaterial(pIMaterialFeature2,0);

  // No more need of this pointer
  pIMaterialFeature2->Release();
  pIMaterialFeature2 = NULL ;

  //----------------------------
  // 9- Checks the positionning
  //----------------------------
  
  // The count of material after the  SetMaterial in the last family
  int NbMaterial =  pIFamilyFeatureOnLast->GetMaterialCount() ;

  if ( (NbMatInLastFamilyBeforeSet+1) != NbMaterial )
  {
	  cout << "The Set should be an adding of material "<< endl;
	  return 1 ;
  }

  // Verify the name of the last material of this last family
  pIMaterialFeature = pIFamilyFeatureOnLast->GetMaterial(NbMaterial);

  if ( NULL == pIMaterialFeature )
  {
	  cout << "This family must contains at least one material "<<endl;
	  return 1 ;
  }
  
  if ( MaterialName2 != pIMaterialFeature->GetLabel() )
  {
	  cout << "The second SetMaterial is incorrect"<<endl;
	  return 1 ;
  }

  // No more need of this interface pointer 
  pIMaterialFeature->Release();
  pIMaterialFeature = NULL ; 

  cout << "We have add the material "<<MaterialName2.ConvertToChar() << " in the " ;
  cout << NameOfTheLastFamily.ConvertToChar() <<" family at the last place" << endl;
  cout << "There is now "<< NbMaterial << " material in this family "<< endl;

  // ----------------------------------
  // 10- No more need of these pointers
  // -----------------------------------

  pIFamilyFeatureOnLast->Release();
  pIFamilyFeatureOnLast = NULL ;


  //---------------------------------
  // 11- Saves the material document 
  //---------------------------------
  CATString NameSave ;
  if ( iArgc == 1 )
  {
	  // We save the new material document where is launched the main
    NameSave =  "DocumentWithNewMat.CATMaterial" ;
  }
  else if ( iArgc == 2) 
  {
	  // We save the new material document in the repertory given in argument
	  CATString s1 = iArgv[1] ;
    NameSave = s1 + Slash + "DocumentWithNewMat.CATMaterial" ;
  }
  else
  {
	  // we save the new material in the repertory given in argument and
	  // with a given name
    CATString s3 = iArgv[3] ;
    CATString s1 = iArgv[1] ;
    NameSave = s3 + Slash + s1 + "WithNewMat.CATMaterial" ;
  }

  rc = CATDocumentServices::SaveAs (*pMaterialDocument, NameSave.ConvertToChar());
  if ( rc == S_OK ) 
  {
	  cout << "Document " << NameSave.ConvertToChar() << " is saved OK" << endl ;
  }
  else
  {
    cout << "ERROR in saving document " << NameSave.ConvertToChar() << endl ;
    return 1;
  }
  
  //----------------------
  // 12- Closes documents
  //----------------------

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


  //--------------------
  // 13- Deletes session
  //--------------------

  rc = ::Delete_Session(pSessionName);
  if (FAILED(rc)) 
  {
    cout << "ERROR in deleting session" << endl ;
    return 1;
  }

  cout << "The CAAMatCreateMaterial main program is endded"<< endl << endl;
	  
  return 0;
}

