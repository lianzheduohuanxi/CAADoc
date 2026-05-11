// COPYRIGHT Dassault Systemes 2005
//==========================================================================
//
//
//	Abstract: This sample shows how to create a CATProduct Black Box (Publication Exposed mode) 
//			 from an assembly (Structure exploded) stored in ENOVIA vpm V4. 
//			 The CATProduct Black Box  is saved on the Root part of the assembly.
//				NOTE: this use case requires a running ENOVIA vpm V4 installation.
//			This UseCase uses VPMENV 
//            
//
//  Steps :
//    1.   Check the argument
//    2.   Opens the session
//    3.   initialise batch communication with VPM server
//    4.   connect to VPM server
//    5.   Load the assembly (Structure Exploded) from ENOVIA vpm 
//    6.   Set PDM properties on documents
//    7.   Create the CATProduct Black Box (Publication Exposed mode) document into ENOVIA vpm V4 
//	  8.   Close the assembly (Structure Exploded)
//	  9.   Updating twice the same CATProduct in ENOVIA vpm V4 
//   10.   Close the assembly and remove all documents in session
//   11.   Disconnect from the VPM server 
//   12.   Delete the session
//
//
//==========================================================================
// How to execute :
// 
//   mkrun -c "CAAPsnUSeCase4 Coid  hostName user pwd role server "  
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
		cout << "CAAPsnUSeCase4.cpp Coid hostName User Passwd Role Server"<< endl;
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
	HRESULT rc = ::Create_Session ( sessionName, pSession );
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
	//6 - Setting PermanentBlackBox properties CATProduct document
	//----------------------------------------------

    CATLISTP(CATDocument)*  ToResetDocuments  =  NULL;  
	CATLISTP(CATDocument)*  ResetDocuments  =  NULL;  
 
	ToResetDocuments  =  new  CATLISTP(CATDocument);  
	ToResetDocuments->Append(pDocRoot);  
	
	//
	//First, You must reset the PDM property on the CATProduct
	//
	rc  =  CATPDMServices::ResetPDMDocuments ( ToResetDocuments,  ResetDocuments );  
  
	if  (NULL  !=  ToResetDocuments) {  
		ToResetDocuments->RemoveAll(); delete  ToResetDocuments; ToResetDocuments  =  NULL;  
	}
	
	if  (NULL  !=  ResetDocuments)  {  
		ResetDocuments->RemoveAll(); delete  ResetDocuments; ResetDocuments  =  NULL;  
	}  

	if (SUCCEEDED(rc) )
	{
		//
		//Then You set PermanentBlackBox property on the CATProduct
		//
		rc = CATVPMServices::SetPDMProperties ( pDocRoot, 
											CATVPMServices::VPM1,
											CATVPMServices::PermanentBlackBox );
	}

	if (FAILED(rc))
	{
		cout << "ERROR in Setting PDM properties" << endl << flush;
		CATError * pError = CATError::CATGetLastError(rc);
		if (pError){
			cout << "NLS Message : " << pError->GetNLSMessage().ConvertToChar() << endl;
		}
		//Always deleting session before exiting
		::Delete_Session(sessionName);
		return 1;
	}
	

	//----------------------------------------------
	//7 - Save Documents in ENOVIA vpm V4 
	//----------------------------------------------

	CATBoolean UnloadAfterSave = FALSE;
	rc = ::CATSaveInVPMFromCATIA( pDocRoot, UnloadAfterSave );
	if (FAILED(rc))
	{
		cout << "ERROR while saving document in ENOVIA vpm" << endl << flush;
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
	//8 - Close the Structure Exploded assembly  
	//----------------------------------------------

	rc = ::CATCloseAssemblyInVPM();





	//----------------------------------------------
	//9 - Updating the same CATProduct in ENOVIA vpm V4 twice
	//		and commit transaction
	//----------------------------------------------
	
	CATUnicodeString printableId;
	CATBaseUnknown *  pDocUnknown = pDocRoot ;
	rc = CATPDMServices::GetPrintableId ( pDocUnknown, printableId );

	CATUnicodeString UpdateCoid = printableId.SubString(0,16);
	CATUnicodeString UpdateCompid = printableId.SubString(16,16);
	CATUnicodeString UpdateEnv = printableId.SubString(32,8);
	CATUnicodeString UpdateTable = printableId.SubString(40,18);

	cout << "GetPrintableId UpdateCoid " << UpdateCoid.ConvertToChar() << endl ;
	cout << "GetPrintableId UpdateCompid " << UpdateCompid.ConvertToChar() << endl;
	cout << "GetPrintableId UpdateEnv " << UpdateEnv.ConvertToChar() << endl ;
	cout << "GetPrintableId UpdateTable " << UpdateTable.ConvertToChar() << endl << flush;


	CATVPMServices::SaveAsMode iMod = CATVPMServices::KeepModified;
	rc= CATVPMServices::SaveAsInVPM(  pDocRoot,
                                    UpdateCoid,
									UpdateCompid,
									UpdateEnv,
									UpdateTable,
									server,
									iMod); 

	if (SUCCEEDED(rc))
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
	else
	{	
		cout << "ERROR while Updating document in ENOVIA vpm" << endl << flush;
		CATError * pError = CATError::CATGetLastError(rc);
		if (pError)	{
			cout << "NLS Message : " << pError->GetNLSMessage().ConvertToChar() << endl;
		}
	}
	

	
	//----------------------------------------------
	//10- Remove documents from session 
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
    //11- Disconnect from the VPM server 
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
   //12- Deletes session 
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




