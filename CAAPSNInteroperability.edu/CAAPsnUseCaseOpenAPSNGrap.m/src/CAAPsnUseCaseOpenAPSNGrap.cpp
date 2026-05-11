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
//    5.   Open a PSN file
//    8.   Remove all the  Documents in session
//    9.   Disconnect from the VPM server 
//   10.   Delete the session
//
//
//==========================================================================
// How to execute :
// 
//   mkrun -c "CAAPsnUSeCase4 PSNfilePath
//
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
		cout << "CAAPsnUSeCase4.cpp pathPsn hostName User Passwd Role Server"<< endl;
		cout << "with	pathPsn	: path of PSN file"<< endl;
		cout << "		hostName: the unix remote VPM server"<< endl;
		cout << "		User	: user name for VPM authentication"<< endl;
		cout << "		Passwd	: password for VPM authentication"<< endl;
		cout << "		Role	: VPM role "<< endl;
		cout << "		Server	: Server name (V5 options setting)"<< endl;
		cout << endl;
		return 1;
	}
	
	CATUnicodeString pathPsn  = argv[1] ;
	CATUnicodeString hostName  = argv[2] ;
	char * pHostName = argv[2] ;
	CATUnicodeString user  = argv[3] ;
	CATUnicodeString pwd  = argv[4] ;
	CATUnicodeString role  = argv[5] ;
	CATUnicodeString server  = argv[6] ;

    
	cout << "The CAAPsnUSeCase4.cpp main program begins ...."<< endl << endl<<flush;
	

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
	HRESULT rc = ::Create_Session(sessionName, pSession);
	if ((FAILED(rc)) || (NULL == pSession))
	{
		cout << "ERROR in creating session" << endl << flush;
		return 1;
	}


	//----------------------------------------------
	//3 - Initializing batch communication with ENOVIA VPM V4
	//----------------------------------------------

   rc = ::CATInitBatchOnHost( pHostName );
  //  rc = ::CATInitBatch(  );
	if (FAILED(rc))
	{
		cout << "ERROR establishing communication with ENOVIA vpm" << endl << flush;
		CATError * pError = CATError::CATGetLastError(rc);
		if (pError)
		{
			cout << "NLS Message : " << pError->GetNLSMessage().ConvertToChar() << endl;
		}

		//Always deleting session before exiting
		::Delete_Session(sessionName);
		return 1;
	}


	//----------------------------------------------
	//4 - connect to VPM server
	//----------------------------------------------

	rc = ::CATConnectToVPM(server, user, pwd, role);
	if (FAILED(rc)) 
	{
		CATError * pError = CATError::CATGetLastError(rc);
		if (pError)
		{
			cout << "NLS Message : " << pError->GetNLSMessage().ConvertToChar() << endl;
		}
       	cout << "User		: "<< user.ConvertToChar() << endl;
		cout << "Passwd		: "<< pwd.ConvertToChar() << endl;
		cout << "Role		: "<< role.ConvertToChar() << endl;
		cout << "Server		: "<< server.ConvertToChar() << endl;


		//Always deleting session before exiting
		::Delete_Session( sessionName );
		return 1;
	}


	char* pCAANoCreateDoc=NULL; 
	result = ::CATGetEnvValue("CV5_VPM_NoDocCreation", &pCAANoCreateDoc );
	if ( (CATLibError == result) || ( NULL == pCAANoCreateDoc) )
	{
		cout << "DPD ======> OpenAPSNGraph avec Doc Creation" << endl;
	}
	else
	{
		cout << "DPD ======> OpenAPSNGraph SANS Doc Creation" << endl;
	}



        CATDocument * opDocPsn = NULL;
	cout << "DPD ======> pathPSN=" << pathPsn.ConvertToChar() << "<" << endl;
	rc = ::OpenAPSNGraph(pathPsn, 1, 1, opDocPsn);
	
		
//	if (SUCCEEDED(rc) &&  (NULL  !=  opDocPsn)) 
	if (SUCCEEDED(rc)) 
	{
		cout << "DPD ======> OpenAPSNGraph successfull" << endl;
	}
	else
	{
		cout << "DPD ======> OpenAPSNGraph KO" << endl;
		CATError * pError = CATError::CATGetLastError(rc);
		if (pError)
		{
			cout << "NLS Message : " << pError->GetNLSMessage().ConvertToChar() << endl;
		}
	
	}


	rc = ::CATCloseAssemblyInVPM();
	
	if (SUCCEEDED(rc)) 
	{
		cout << "DPD ======> CATCloseAssemblyInVPM  successfull" << endl;
	}
	else
	{
		cout << "DPD ======> CATCloseAssemblyInVPM  KO" << endl;
		CATError * pError = CATError::CATGetLastError(rc);
		if (pError)
		{
			cout << "NLS Message : " << pError->GetNLSMessage().ConvertToChar() << endl;
		}
	
	}





	
	//----------------------------------------------
	//8- Remove documents from session 
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
    //9- Disconnect from the VPM server 
    //------------------------------------------------------
	cout << "Disconnecting from ENOVIA vpm" << endl << flush;
    rc = ::CATDisconnectFromVPM();
    if (FAILED(rc))
    {
   	   CATError * pError = CATError::CATGetLastError(rc);
		if (pError)
		{
			cout << "NLS Message : " << pError->GetNLSMessage().ConvertToChar() << endl;
		}
   }

   //------------------------------------------------------
   //10- Deletes session 
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
 

   
   cout <<"The CAAPsnUSeCase4.cpp main program is ended."<< endl << endl;

   return 0 ;   
}




