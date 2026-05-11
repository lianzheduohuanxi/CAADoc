
// COPYRIGHT Dassault Systemes 2005
//==========================================================================
//
//
//
//  Steps :
//    1.   Check the argument
//    2.   Opens the session
//    3.   initialise batch communication with VPM server
//    4.   connect to VPM server
//    5.   Load the assembly (Structure Exploded) from ENOVIA vpm 
//    6.   Get The PrintableId From The Document
//    7.   CATAnalyseDocIdFromVPM
//    8.   CATCloseAssemblyInVPM 
//    9.    Close the assembly and remove all documents in session
//   10.   Disconnect from the VPM server 
//   11.   Delete the session
//
//
//==========================================================================
// How to execute :
// 
//   mkrun -c "CAAPsnUseCaseAnalysePrintableId Coid  hostName user pwd role server "  
//e.g.         CAAPsnUseCaseAnalysePrintableId 41419be22d212fa4 bldsunkarnaplb ""  "" VPMADMIN SAMPLE 
//          
// Return code :
//   0 successful execution 
//   1 otherwise
//
//
//===================================================================

// System Framework 
#include "CATError.h"
#include "CATGetEnvValue.h"
#include "CATUnicodeString.h"


// ObjectModelerBase Framework
#include "CATSessionServices.h"          // Create_Session and Delete_Session
#include "CATDocumentServices.h"
#include "CATIDocId.h"



// PSNInteroperability Framework
#include "CATBatchServices.h"
#include "CATBatchServices2.h"
#include "CATVPMServices.h"

// CATPDMBase  Framework
#include "CATPDMServices.h"

// C++ Standard Library
#include <iostream.h>  



//-----------------------------------------------------------------------------
int main(int iArgc, char *argv[])        
{
  //----------------------------------------------
  //1- Checks arguments 
  //----------------------------------------------
	
  if ((7 != iArgc) )
    {
      cout << endl;
      cout << "CAAPsnUseCaseAnalysePrintableId.cpp Coid hostName User Passwd Role Server"<< endl;
      cout << "with	Coid	: Coid of root part assembly"<< endl;
      cout << "		hostName: the unix remote VPM server"<< endl;
      cout << "		User	: user name for VPM authentication"<< endl;
      cout << "		Passwd	: password for VPM authentication"<< endl;
      cout << "		Role	: VPM role "<< endl;
      cout << "		Server	: Server name (V5 options setting)"<< endl;
      cout << endl;
      return 1;
    }
	
  CATUnicodeString Coid  = argv[1] ;
  CATUnicodeString hostName  = argv[2] ;
  char * pHostName = argv[2] ;
  CATUnicodeString user  = argv[3] ;
  CATUnicodeString pwd  = argv[4] ;
  CATUnicodeString role  = argv[5] ;
  CATUnicodeString server  = argv[6] ;

    
  cout << "The CAAPsnUseCaseAnalysePrintableId.cpp main program begins ...."<< endl << endl<<flush;
	

  //----------------------------------------------
  //- Checking environment variable CV5VpmStart. 
  // It Must be set with the full unix path of the 
  // shell script to launch VX0SERV application.
  //----------------------------------------------

  char* pCAAPathToShell=NULL; 
  CATLibStatus result = ::CATGetEnvValue("CV5VpmStart", &pCAAPathToShell);
  if ( (CATLibError == result) || ( NULL == pCAAPathToShell) )
    {
      cout << "CV5VpmStart environment variable is not set" << endl << flush;
      return 1;
    }
  cout << " The unix shell script is " << pCAAPathToShell << " on host " << hostName.ConvertToChar() << endl;

    
	//----------------------------------------------
	//2- Create session
	//----------------------------------------------

  char *sessionName = "CAA2_Sample_Session";
  CATSession *pSession = NULL;
  HRESULT rc = ::Create_Session ( sessionName, pSession );
  if ((FAILED(rc)) || (NULL == pSession))
    {
      cout << "ERROR in creating session" << endl << flush;
      return 1;
    }


  //----------------------------------------------
  //3 - Initializing batch communication with ENOVIA VPM V4
  //----------------------------------------------

#ifndef _WINDOWS_SOURCE
  rc = ::CATInitBatch();
#else
  rc = ::CATInitBatchOnHost( pHostName );
#endif
 if (FAILED(rc))
    {
      cout << "ERROR establishing communication with ENOVIA vpm" << endl << flush;
      CATError * pError = CATError::CATGetLastError(rc);
      if (pError){
	cout << "NLS Message : " << pError->GetNLSMessage().ConvertToChar() << endl;
      }

      //Always deleting session before exiting
      ::Delete_Session(sessionName);
      return 1;
    }


  //----------------------------------------------
  //4 - connect to VPM server
  //----------------------------------------------

  rc = ::CATConnectToVPM ( server, user, pwd, role );
  if (FAILED(rc)) 
    {
      cout << "ERROR in server authentication" << endl << flush;
      CATError * pError = CATError::CATGetLastError(rc);
      if (pError)	{
	cout << "NLS Message : " << pError->GetNLSMessage().ConvertToChar() << endl;
      }
      //Always deleting session before exiting
      ::Delete_Session( sessionName );
      return 1;
    }



  //----------------------------------------------
  //5 - Open the ENOVIA vpm assembly in session 
  //----------------------------------------------

	//You are using the default VPM environment
  CATUnicodeString CompId = "3030303030303030";
  CATUnicodeString Env = "VPMENV  "; 
  CATUnicodeString Table = "PART_LIST         ";
  CATLISTV(CATUnicodeString)*  lvConfiguration  =  NULL; 
  CATDocument *  pDocRoot  =  NULL;

  //First, you must perform the assembly expand in VPM server memory
  rc = ::CATOpenConfiguredAssemblyInVPM ( lvConfiguration,
					  Coid,
					  CompId,
					  Env,
					  Table,
					  server);


  if (SUCCEEDED(rc)) 
    {
      // New CATProduct Document to receive Root part
      rc  =  ::CATCreateVPMSession ( pDocRoot, Coid, CompId, Env, Table, server );  
		
      if (SUCCEEDED(rc) &&  (NULL  !=  pDocRoot)) 
	{
	  // Load ALL children from Root part
	  int nbLevel = 0;
	  rc = ::CATLoadChildrenFromVPM ( pDocRoot, nbLevel );
			
	  // Retrieve ALL application data for the whole assembly
	  if (SUCCEEDED(rc)) 
	    {
	      rc = ::CATCompleteSessionFromVPM ( pDocRoot );
	    }
	}
    }
	
  if (FAILED(rc) )
    {
      cout << "ERROR  in  opening the assembly from ENOVIA vpm" << endl << flush;
      CATError * pError = CATError::CATGetLastError(rc);
      if (pError){
	cout << "NLS Message : " << pError->GetNLSMessage().ConvertToChar() << endl;
      }
      //Always deleting session before exiting
      ::Delete_Session(sessionName);
      return 1;
    }
	
  //----------------------------------------------
  //6 i) - Get The PrintableId From The Document 
  //----------------------------------------------
	
  CATUnicodeString printableId;
  CATBaseUnknown *  pDocUnknown = pDocRoot ;
  rc = CATPDMServices::GetPrintableId ( pDocUnknown, printableId );
  cout<<"Origional PrintableId="<<printableId.ConvertToChar()<<endl;


	//ENK START

  
  //----------------------------------------------------------------------
  //6 - CATAnalysePrintableIDFromVPM
  //----------------------------------------------------------------------

  cout<<"Get The Parameters From PrintableId"<<endl;
  
  int i,LinkSize;
  CATUnicodeString oCoid;
  CATUnicodeString oCompid;
  CATUnicodeString oCaenv;
  CATUnicodeString oCatab;
  CATUnicodeString expectedPrintableId="";
  CATListOfCATUnicodeString oClink;
  rc=CATPDMServices::CATAnalysePrintableIDFromVPM (printableId,oCoid,oCompid,oCaenv,oCatab,oClink);
  if(FAILED(rc))
    {
      cout<<"Failed To Get The Parameters From PrintableId"<<endl;
      rc=E_FAIL;
    
    }
 
  CATUnicodeString expectedPDMId="";
  expectedPDMId.Append(oCoid);
  expectedPDMId.Append(oCompid);
  expectedPDMId.Append(oCaenv);
  expectedPDMId.Append(oCatab);
  LinkSize=oClink.Size();
   
  for(i=0;i<LinkSize;i++)
    {
      CATUnicodeString string=oClink[i];
      expectedPDMId.Append(string);
    }
  cout<<"EXPECTED Printable Id:   "<< expectedPDMId.ConvertToChar()<<endl;
  //-----------------------------------
  // Check the PrintableIdId got from product
  // and the one expected are equal
  //-----------------------------------
  if(0 ==printableId.Compare(expectedPDMId))
    {
      cout<<"Retrieved PrintableId is not correct"<<endl;
      rc=E_FAIL;
     
    }
  else 
    {
      cout<<"IT IS OK"<<endl;
    }


  //----------------------------------------------
  //8 - Close the Structure Exploded assembly  
  //----------------------------------------------

  rc = ::CATCloseAssemblyInVPM();


  //----------------------------------------------
  //9- Remove documents from session 
  //----------------------------------------------
  const CATLISTP(CATDocument)* pListDocInSession = ::ListDocuments();
  if(pListDocInSession)
    {
      for (int j=1; j <= pListDocInSession->Size(); j++)
	{
	  CATDocument* pDocument  = (*pListDocInSession)[j];
	  CATDocumentServices::Remove( *pDocument );
	}
    }


  //------------------------------------------------------
  //10- Disconnect from the VPM server 
  //------------------------------------------------------

  cout << "Disconnecting from ENOVIA vpm" << endl << flush;
  rc = ::CATDisconnectFromVPM();
  if (FAILED(rc))
    {
      CATError * pError = CATError::CATGetLastError(rc);
      if (pError)	{
	cout << "NLS Message : " << pError->GetNLSMessage().ConvertToChar() << endl;
      }
    }


  //------------------------------------------------------
  //11- Deletes session 
  //------------------------------------------------------
  rc = ::CATTerminateBatch();
  if (FAILED(rc))
    {
      CATError * pError = CATError::CATGetLastError(rc);
      if (pError){
	cout << "NLS Message : " << pError->GetNLSMessage().ConvertToChar() << endl;
      }
    }

  rc = ::Delete_Session( sessionName );
  if (FAILED(rc))
    return 1;
 

   
  cout <<"The CAAPsnUseCaseAnalysePrintableId.cpp main program is ended."<< endl << endl;

  return 0 ;   
}

