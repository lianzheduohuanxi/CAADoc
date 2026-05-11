// COPYRIGHT Dassault Systemes 2005
//==========================================================================
//
//	Abstract: This sample shows how to import an assembly from file based in ENOVIA vpm V4.
//				The assembly structure is saved in Structure Exploded mode while the CATPart
//				are saved in Publication Exposed mode (black box).
//				NOTE: this use case requires a running ENOVIA vpm V4 installation.
//            
//
//  Steps :
//    1.   Check the argument
//    2.   Opens the session
//    3.   initialise batch communication with VPM server
//    4.   connect to VPM server
//    5.   Load the file based documents in session
//    6.   Set PDM properties on documents
//    7.   Save the documents in session into ENOVIA vpm V4 
//    8.   Remove all the  Documents in session
//    9.   Disconnect from the VPM server 
//   10.   Delete the session
//
//
//==========================================================================
// How to execute :
// 
//   mkrun -c "CAAPsnUSeCase1 rootFilepath hostName user pwd role server "  
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
		cout << "CAAPsnUSeCase1.cpp rootFilepath hostName User Passwd Role Server"<< endl;
		cout << "with	rootFilepath: the full path of the assembly root document (CATProduct)"<< endl;
		cout << "		hostName	: the unix remote VPM server"<< endl;
		cout << "		User		: user name for VPM authentication"<< endl;
		cout << "		Passwd		: password for VPM authentication"<< endl;
		cout << "		Role		: VPM role "<< endl;
		cout << "		Server		: Server name (V5 options setting)"<< endl;
		cout << endl;
		return 1;
	}
	
	CATUnicodeString rootFilepath  = argv[1] ;
	CATUnicodeString hostName  = argv[2] ;
	char * pHostName = argv[2] ;
	CATUnicodeString user  = argv[3] ;
	CATUnicodeString pwd  = argv[4] ;
	CATUnicodeString role  = argv[5] ;
	CATUnicodeString server  = argv[6] ;

    
	cout << "The CAAPsnUSeCase1.cpp main program begins ...."<< endl << endl<<flush;
	

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
	if (FAILED(rc))
	{
		cout << "ERROR establishing communication with ENOVIA vpm" << endl << flush;
		CATError * pError = CATError::CATGetLastError(rc);
		if (pError)	{
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
		cout << "ERROR in server authentication" << endl << flush;
		CATError * pError = CATError::CATGetLastError(rc);
		if (pError){
			cout << "NLS Message : " << pError->GetNLSMessage().ConvertToChar() << endl;
		}

		//Always deleting session before exiting
		::Delete_Session( sessionName );
		return 1;
	}



	//----------------------------------------------
	//5 - Load root asembly document in session assuming
	// that referenced documents are loaded 
	//----------------------------------------------
	CATDocument * pDocRoot = NULL;
	rc = CATDocumentServices::OpenDocument( rootFilepath.ConvertToChar(), pDocRoot);
	if (SUCCEEDED(rc) && (NULL != pDocRoot)) 
	{
		cout << "Document " << rootFilepath.ConvertToChar() << " opened successfully" << endl << flush;
	}
	else
	{
		cout << "ERROR while opening the root document" << endl << flush;
		//Always deleting session before exiting
		::Delete_Session( sessionName );
		return 1;
	}

    
	//----------------------------------------------
	//6 - Setting PDM properties on documents in session
	//----------------------------------------------

	const CATLISTP(CATDocument)* pListDocInSession = ::ListDocuments();
	if (pListDocInSession)
	{
		for (int i=1; i<=pListDocInSession->Size(); i++)
		{
			CATDocument* pDocument  = (*pListDocInSession)[i];
			if  ( NULL  !=  pDocument )  
			{  
				CATUnicodeString docName  = pDocument->storageName();
				
				CATIDocId    *  pIDocId  =  NULL  ; 
				rc =  pDocument->GetDocId(&pIDocId); 
				if  ( SUCCEEDED(rc) ) 
				{  
					CATUnicodeString type  ; 
					pIDocId->GetType(type) ; 
					if  (  CATUnicodeString("CATProduct")  ==  type ) 
					{
						cout << "SetPDMProperties on document " << docName.ConvertToChar() << endl ;
						rc = CATVPMServices::SetPDMProperties( pDocument, CATVPMServices::VPM1, CATVPMServices::VolatileExposed );
					}
					else if (  CATUnicodeString("CATPart")  ==  type ) 
					{
						cout << "SetPDMProperties on document " << docName.ConvertToChar() << endl ;
						rc = CATVPMServices::SetPDMProperties( pDocument, CATVPMServices::VPM1, CATVPMServices::PermanentBlackBox );
					}
					pIDocId->Release(); pIDocId = NULL; 
				}

				if (FAILED(rc))
				{
					cout << "ERROR in setting PDM properties" << endl << flush;
					CATError * pError = CATError::CATGetLastError(rc);
					if (pError)	{
						cout << "NLS Message : " << pError->GetNLSMessage().ConvertToChar() << endl;
					}
					break;
				}
			}
		}
	}

    
	if (FAILED(rc))
	{
		//Always deleting session before exiting
		::Delete_Session(sessionName);
		return 1;

	}


	//----------------------------------------------
	//7 - Save Documents in ENOVIA vpm V4 
	//		and commit transaction
	//----------------------------------------------

	CATBoolean UnloadAfterSave = FALSE;
	rc = ::CATSaveInVPMFromCATIA( pDocRoot, UnloadAfterSave );
	if (FAILED(rc))
	{
		cout << "ERROR while saving documents in ENOVIA vpm" << endl << flush;
		CATError * pError = CATError::CATGetLastError(rc);
		if (pError)	{
			cout << "NLS Message : " << pError->GetNLSMessage().ConvertToChar() << endl;
		}
	}
	else
	{	
		cout << "Commit transaction in ENOVIA vpm" << endl << flush;
		rc = ::CATCommitVPM();
		if (FAILED(rc))
		{
			cout << "ERROR in Commit in ENOVIA vpm" << endl << flush;
			CATError * pError = CATError::CATGetLastError(rc);
			if (pError){
				cout << "NLS Message : " << pError->GetNLSMessage().ConvertToChar() << endl;
			}
		}
	}
	
	
	//----------------------------------------------
	//8- Remove documents from session 
	//----------------------------------------------
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
 

   
   cout <<"The CAAPsnUSeCase1.cpp main program is ended."<< endl << endl;
   return 0 ;   
}
