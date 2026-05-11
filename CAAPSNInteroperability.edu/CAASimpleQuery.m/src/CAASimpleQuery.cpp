// COPYRIGHT Dassault Systemes 2005
//==========================================================================
//
//  Abstract: This sample shows how to search in ENOVIAVpm V4 databases.
//        You need to specify the search criteria , environment name and the table name
//        in which to perform the query.
//        NOTE: this use case requires a running ENOVIA vpm V4 installation.
//            
//
//  Steps :
//    1 - Open/Creation of the CV5 Session.
//    2 - Initialize communication with VPM server.(Launch VPM)
//    3 - Connect to VPM
//    4 - Call CATSimpleQueryToVPM with Envname,tablename and search criteria
//    5 - Get the output lists and print them
//    6 - Clean the V5 Session(Pointer release to avoid memory leak)
//    7 - Disconnect from VPM Server
//    8 - Terminate V5 Session anf Delete the session

//
//==========================================================================
// How to execute :
// 
//   mkrun -c "CAASimpleQuery hostname server environment user passwd role tablename searchcriteria"  
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
  // Checks arguments 
  //----------------------------------------------

  if ((9 != iArgc) )
  {
    cout << endl;
    cout << "CAASimpleQuery hostname server environment user passwd role tablename searchcriteria"<< endl;
    cout << "with hostname: host on which to start VPM Server"<< endl;
    cout << "   server: Server name (V5 options setting)"<< endl;
    cout << "   environment : Environment name (V5 options setting)"<< endl;
    cout << "   user    : user name for VPM authentication"<< endl;
    cout << "   passwd    : password for VPM authentication"<< endl;
    cout << "   role    : VPM role "<< endl;
    cout << "   tablename   : VPM table name"<< endl;
    cout << "   searchcriteria    : String to search"<< endl;
    cout << endl;
    return 1;
  }

  CATUnicodeString hostName  = argv[1] ;
  char * pHostName = argv[1] ;
  CATUnicodeString server  = argv[2] ;
  CATUnicodeString env  = argv[3] ;
  CATUnicodeString user  = argv[4] ;
  CATUnicodeString pwd  = argv[5] ;
  CATUnicodeString role  = argv[6] ;
  CATUnicodeString table  = argv[7] ;
  CATUnicodeString searchCriteria  = argv[8] ;
  CATListOfCATUnicodeString listofName,listOfCoid,listOfCompid,listOfCaenv,listOfCatab;


  cout << "The CAASimpleQuery main program begins ...."<< endl << endl<<flush;


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
  //1- Create session
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
  //2 - Initializing batch communication with ENOVIA VPM V4
  //----------------------------------------------
#ifdef _WINDOWS_SOURCE
  rc = ::CATInitBatchOnHost( pHostName );
  if (FAILED(rc))
  {
    cout << "ERROR establishing communication with ENOVIA vpm" << endl << flush;
    CATError * pError = CATError::CATGetLastError(rc);
    if (pError) {
      cout << "NLS Message : " << pError->GetNLSMessage().ConvertToChar() << endl;
    }

    //Always deleting session before exiting
    ::Delete_Session(sessionName);
    return 1;
  }
#else
  rc = ::CATInitBatch();
  if (FAILED(rc))
  {
    cout << "ERROR establishing communication with ENOVIA vpm" << endl << flush;
    CATError * pError = CATError::CATGetLastError(rc);
    if (pError) {
      cout << "NLS Message : " << pError->GetNLSMessage().ConvertToChar() << endl;
    }

    //Always deleting session before exiting
    ::Delete_Session(sessionName);
    return 1;
  }
#endif

  //----------------------------------------------
  //3 - connect to VPM server
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

  //------------------------------------------------------------------------------------
  // 4 - Call CATSimpleVpmQuery to get list of Printable Ids and corresponding PDM names
  //------------------------------------------------------------------------------------
  rc = CATSimpleQueryToVPM(env,table,searchCriteria,listofName,listOfCoid,listOfCompid,listOfCaenv,listOfCatab);
  if(FAILED(rc))
  {
    cout << "ERROR Simple Query failed" << endl << flush;
    ::Delete_Session( sessionName );
    return 1;
  }

  //-------------------------------------------
  // 5 - Get the output lists and print them
  //------------------------------------------

  cout << "Number of entries found = " << listofName.Size() << endl << flush;
  for(int cnt=1;cnt<=listofName.Size();cnt++)
  {
    cout << "COID = " << (listOfCoid[cnt]).ConvertToChar() << endl << flush;
    cout << "COMPID = " << (listOfCompid[cnt]).ConvertToChar() << endl << flush;
    cout << "Env Name = " << (listOfCaenv[cnt]).ConvertToChar() << endl << flush;
    cout << "Table Name = " << (listOfCatab[cnt]).ConvertToChar() << endl << flush;
    cout << "PDM Name = " << (listofName[cnt]).ConvertToChar() << endl << flush;
  }

  //------------------------------------------------------
  //6 - Disconnect from the VPM server 
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
  //7 - Deletes session 
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



  cout <<"The CAASimpleQuery main program is ended."<< endl << endl;
  return 0 ;   
}
