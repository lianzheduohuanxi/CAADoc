// =================================
// COPYRIGHT DASSAULT SYSTEMES 2002
// ================================= 

//=============================================================================
//  Abstract of Use Case "CAAElecConnectDevices":
//  ---------------------------------------------
//
//  This Use Case illustrates how retrieve and analyse Electrical Device 
//
//=============================================================================
//
//  Step by Step :
//  ------------
//
//  1. Prologue :  
//      . Opening the Session and Opening an Existing CATProduct Document
//      . Retrieving the Root Product of the CATProduct Document
// 
//  2. Initializing Electrical Environment 
//
//  3. Retrieving all electrical single connector and all electrical back shell under the 
//     Root Product 
//
//  4. Selecting first single connector
//       4.1. Retrieve the list of back shell connection point defined on the single connector
//       4.2. Connect the single connector with the second back shell.
//
//  5. Selecting the second single connector
//       5.1. Retrieve the list of back shell connection point defined on the single connector
//       5.2. Connect the second single connector with the first back shell.
//       5.3. Retrieve the list of connector connection point defined on the single connector.
//       5.4. Connect the first single connector with the second single connector  
//
//  6. Retrieving all electrical equipment and all electrical mounting equipment under the 
//     Root Product 
//
//  7. Connect the third single connector with the first mounting equipment
//
//  8. Connect the first equipment with the second mounting equipment. 
//
//  9. Epilogue.
//
//  Return Errors:
//  -------------
//  1 - ERROR in creating the session
//  2 - ERROR in opening an existing document.
//  3 - ERROR in getting root product
//  4 - ERROR in electrical environment initialization 
//  5 - ERROR if electrical single connector and back shell not found in assembly 
//  6 - ERROR if the first electrical single connector not retrieved
//  7 - ERROR if the list of back shell connection point on first single connector wasn't correctly retrieved
//  8 - ERROR if first back shell connection point not found.
//  9 - ERROR if the second back shell not found.
// 10 - ERROR if the connection between the first single connector and the second back shell failed.
// 11 - ERROR if the second single connector not found.
// 12 - ERROR if the list of back shell connection point of second single connector wasn't correctly retrieved.
// 13 - ERROR if the first back shell connection point not found..
// 14 - ERROR if not getting the first back shell .
// 15 - ERROR if the connection between the second single connector and the first back shell failed.
// 16 - ERROR if the connector connection point defined on the first single connector is not found.
// 17 - ERROR if the connection of the first single connector with the second single connector failed.
// 18 - ERROR if saving document 
// 19 - ERROR in removing document  
// 20 - ERROR in closing session  
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  mkrun -c "CAAElecConnectDevice input.CATProduct output.CATProduct" where the prefix "input" is the 
//  entire pathname of the directory in which the document is to be found and the
//  name of the document itself.
//  output.CATProduct - the path of the file to save in the main document.
//
//
//  You may reference the supplied CATProduct document called "MAIN_PRODUCT.CATProduct" 
//  found in the 'WS'/'OS'/resources/graphic/CAAElecDeviceConnection directory if under Unix.
//      In this case, 'OS' can be any of the following: 
//         aix_a for IBM
//         hpux_a for HP
//         irix_a for SGI
//         solaris_a for SUN
//  Under Windows, the path would indicate:  'WS'\intel_a\resources\graphic\CAAElecDeviceConnection directory. 
//
//
//====================================================================================================

// C++ include ( result display )
// LRO 08:01:15
#include "CATBaseUnknown.h"
#include "CATBoolean.h"
#include "CATILinkableObject.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATSession.h"
#include "CATUnicodeString.h"

#include <iostream.h>

// ObjectModelerBase interfaces
#include "CATSessionServices.h"    // managing session
#include "CATDocumentServices.h"   // managing documents in session
#include "CATDocument.h"           // manipulating documents
#include "CATIDocRoots.h"          // browsing root objects in documents

// ProductStructure interfaces 
#include "CATIProduct.h"             // managing products   
#include "CATIElbSingleConnector.h"  // managing a single connector
#include "CATIElbBackShell.h"        // managing a back shell
#include "CATIElbBackShellCnctPt.h"  // managing a back shell connection point.
#include "CATIElbConnectorCnctPt.h"  // managing a connector connection point
#include "CATIElbEquipment.h"        // managing an equipemnt
#include "CATIElbMountingEquipment.h"  // managing a mounting equipment
#include "CATIElbCavity.h"  // managing a mounting equipment

// Electrical interfaces
#include "CATIEleDocServices.h"    // initializing electrical environement 



int main (int argc, char * argv[] )
{ 
  //--------------------------------------------------------------------
  // 1. Prologue 
  //--------------------------------------------------------------------
  cout << endl << flush;
  cout << endl << flush;
  cout << "----------------------------------------------------------------" << endl << flush;
  cout << endl << flush;
  
  // --- Creating the Session:  A session must always be created in a batch
  
  CATSession *pSession = NULL;
  
  char *sessionName = "CAA_ElbConnectDevice_Session";
  HRESULT rc = ::Create_Session(sessionName,pSession);
  if ((SUCCEEDED(rc)) && (NULL != pSession))
  {
    cout << "> session created : " << sessionName <<endl << flush;
  }
  else
  {
    cout << "ERROR in creating session" << sessionName << endl << flush;
    return 1;
  }
  
  // --- Opening an existing document 
  //     The input parameter to this sample program must contain 
  //     the entire path and name of the document that is to be opened.  
  
  CATDocument *pDoc = NULL; // pDoc is a pointer to the document 
  
  cout << "> open document :"<< argv[1] << endl << flush;
  rc = CATDocumentServices::OpenDocument(argv[1], pDoc);
  if (SUCCEEDED(rc) && (NULL != pDoc))
  {
    cout << "> document opened " << endl << flush;
  }
  else
  {
    cout << "ERROR in opening document" << endl << flush;
    return 2;
  }
  
  // --- Retrieving root product of the opened document 
  
  CATIProduct* piRootProduct = NULL;// piRootProduct is a handle to document root product
  
  CATIDocRoots * pDocRoots = NULL;
  rc = pDoc->QueryInterface(IID_CATIDocRoots,(void**) &pDocRoots);
  if ( FAILED(rc) || (NULL==pDocRoots) ) return 3;
  CATListValCATBaseUnknown_var* pListRootProduct = pDocRoots->GiveDocRoots();
  pDocRoots->Release();
  pDocRoots=NULL;
  
  if ( pListRootProduct && pListRootProduct->Size() )
  {  
    CATBaseUnknown_var spCBU ((*pListRootProduct)[1]);
    if (NULL_var != spCBU)
      rc = spCBU->QueryInterface(IID_CATIProduct,(void**) &piRootProduct );
    if (pListRootProduct) delete pListRootProduct;
    pListRootProduct = NULL;
    //
    if  (SUCCEEDED(rc) && (NULL != piRootProduct))
      cout << "> root product found in document " << endl << flush;
    else
    {
      cout << "ERROR : Root product not found in document " << endl << flush;
      return 3;
    }
  }
  
  //--------------------------------------------------------------------
  // 2. Initializing Electrical Environment 
  //--------------------------------------------------------------------
  
  CATIEleDocServices * piElecDocServices = NULL;
  
  rc = pDoc->QueryInterface(IID_CATIEleDocServices,(void**) &piElecDocServices );
  if ( SUCCEEDED(rc) && piElecDocServices )
  {
    rc = piElecDocServices->Initialize();
  }
  
  if (SUCCEEDED(rc) )
  {
    cout << "> electrical environment initialized " << endl << flush;
  }
  else
  {
    cout << "ERROR : electrical environment initialization failed " << endl << flush;
    return 4;
  }
  
  if ( NULL != piElecDocServices )
  {
    piElecDocServices->Release();
    piElecDocServices=NULL;
  }
  
  //--------------------------------------------------------------------
  // 3. Retrieving all electrical object under the root product   
  //--------------------------------------------------------------------
  
  // --- Retrieving all electrical single connector and all electrical back shell
  //     under root product  
  //     -------------------------------------------------------------------------
  CATListValCATBaseUnknown_var* pListElbSingleConnector = NULL;
  pListElbSingleConnector = piRootProduct->GetAllChildren(CATIElbSingleConnector::ClassName());
    
  int NumberOfSingleConnector = pListElbSingleConnector?pListElbSingleConnector->Size():0;
  if ( 3 == NumberOfSingleConnector ) 
  {
    cout << "> number of single connector part found : "<< NumberOfSingleConnector << endl << flush;
  }
  else
  {
    cout << "ERROR : no electrical single connector found  " << endl << flush;
    return 5;
  }
  
  CATListValCATBaseUnknown_var* pListElbBackShell = NULL;
  pListElbBackShell = piRootProduct->GetAllChildren(CATIElbBackShell::ClassName());
  
  int NumberOfBackShell = pListElbBackShell?pListElbBackShell->Size():0;

  if ( 0 < NumberOfBackShell ) 
  {
    cout << "> number of back shell part found : "<< NumberOfBackShell << endl << flush;
  }
  else
  {
    cout << "ERROR : no electrical back shell found  " << endl << flush;
    return 5;
  }

  
  // selecting the Single connector : "First_SingleConnector"
  // --------------------------------------------------------  
  CATIElbSingleConnector * pFirst_SingleConnector = NULL;
  CATBaseUnknown_var spCBU ((*pListElbSingleConnector)[2]);
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIElbSingleConnector,(void**) &pFirst_SingleConnector);
  
  //     
  if ( SUCCEEDED(rc) && (NULL != pFirst_SingleConnector))
  { 
    cout << "> select electrical single connector " <<endl << flush;
    cout << "   rank in list   :  "<< NumberOfSingleConnector << endl << flush;
    CATIProduct_var  spFirstElecSICProduct = pFirst_SingleConnector ;
    CATUnicodeString InstanceName;
    if ( NULL_var != spFirstElecSICProduct ) spFirstElecSICProduct->GetPrdInstanceName(InstanceName);		
    cout << "   instance name  :  "<< InstanceName.ConvertToChar() << endl << flush;
  }
  else
  {
    cout << "ERROR : getting electrical single connector failed " << endl << flush;
    delete pListElbSingleConnector;
    pListElbSingleConnector = NULL;
    return 6;
  } 
  

  // Retrieving the  back shell connection point defined on the single connector
  // ----------------------------------------------------------------------------------
  CATListValCATBaseUnknown_var * pListBackShellCnctPt = NULL;
  rc = pFirst_SingleConnector->ListBackShellCnctPts(pListBackShellCnctPt);
  int SizeBackShellCnctPt = pListBackShellCnctPt ? pListBackShellCnctPt->Size() :0;
   
  if( SUCCEEDED(rc) && (1==SizeBackShellCnctPt) )
  {
    cout << "> the list of back shell connection point was correctly retrieved " <<endl << flush;
  }
  else 
  {
    cout << "> **** ERROR *** the list of back shell connection point wasn't correctly retrieved " <<endl << flush;  
    return 7;
  }

  CATIElbBackShellCnctPt * pElbBackShellCnctPt = NULL;
  spCBU = (*pListBackShellCnctPt)[1];
  if (NULL_var != spCBU)
    rc = spCBU-> QueryInterface(IID_CATIElbBackShellCnctPt ,(void**) & pElbBackShellCnctPt);
  if ( SUCCEEDED(rc) && NULL!= pElbBackShellCnctPt)
  { 
    cout << "> electrical back shell connection point OK " <<endl << flush;
  }
  else
  {
    cout << "ERROR : getting back shell connection point  failed " << endl << flush;
    return 8;
  } 

  delete pListBackShellCnctPt;
  pListBackShellCnctPt = NULL;


  // retrieving the representation of the back shell connection point
  // ----------------------------------------------------------------
  
  CATILinkableObject* pRepresentation=NULL;
  rc = pElbBackShellCnctPt->GetRepresentation(pRepresentation);
  if( SUCCEEDED(rc) && pRepresentation)
  {
	  cout << "> the representation of back shell connection point was correctly retrieved " <<endl << flush;
  }
  else 
  {
	  cout << "> **** ERROR *** the representation of back shell connection point wasn't correctly retrieved " <<endl << flush;  
	  return 7;
  }
  
  pRepresentation->Release();
  pRepresentation=NULL;


  // selecting the back shell : "Second_BackShell"
  // ----------------------------------------------
  CATIElbBackShell * pSecond_BackShell = NULL;
  spCBU = (*pListElbBackShell)[2];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIElbBackShell,(void**)& pSecond_BackShell) ;
    //     
  if ( SUCCEEDED(rc) && pSecond_BackShell)
  { 
    cout << "> select second electrical back shell " <<endl << flush;
    CATIProduct_var  spSecondElecBackShellProduct = pSecond_BackShell ;
    CATUnicodeString InstanceName;
    if ( NULL_var != spSecondElecBackShellProduct ) spSecondElecBackShellProduct->GetPrdInstanceName(InstanceName);		
    cout << "   instance name  :  "<< InstanceName.ConvertToChar() << endl << flush;
  }
  else
  {
    cout << "ERROR : getting second back shell failed " << endl << flush;
    delete pListElbBackShell;
    pListElbBackShell = NULL;

    return 9;
  } 
  
  // Connecting the first single connector with the second back shell
  // ---------------------------------------------------------------
  int  StatusOfGeometricalConstraint= 0;
  rc = pFirst_SingleConnector->ConnectBackShell(pElbBackShellCnctPt	,pSecond_BackShell,  StatusOfGeometricalConstraint);
  
  if(SUCCEEDED(rc) && StatusOfGeometricalConstraint==0 )
  {
    cout << "> connect first single connector with second back shell succeeded " <<endl << flush;
  }
  else 
  {
    cout << "> **** ERROR **** connect first single connector with second back shell failed " <<endl << flush;
    return 10;

  }

  pElbBackShellCnctPt->Release();
  pElbBackShellCnctPt = NULL;
  pSecond_BackShell->Release();
  pSecond_BackShell = NULL;

  
  // selecting the Single connector : "Second_SingleConnector"
  // --------------------------------------------------------  
  CATIElbSingleConnector * pSecond_SingleConnector = NULL;
  spCBU = (*pListElbSingleConnector)[1];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIElbSingleConnector,(void**) &pSecond_SingleConnector);
       
  if ( SUCCEEDED(rc) && NULL!= pSecond_SingleConnector)
  { 
    cout << "> select second electrical single connector " <<endl << flush;
    CATUnicodeString InstanceName;
    CATIProduct_var  spSecondElecSICProduct = pSecond_SingleConnector ;
    if ( NULL_var != spSecondElecSICProduct ) spSecondElecSICProduct->GetPrdInstanceName(InstanceName);		
    cout << "   instance name  :  "<< InstanceName.ConvertToChar() << endl << flush;
  }
  else
  {
    cout << "ERROR : getting electrical second single connector failed " << endl << flush;
    return 11;
  } 



  // Retrieving the  back shell connection point defined on the second single connector
  // ----------------------------------------------------------------------------------
  rc = pSecond_SingleConnector->ListBackShellCnctPts(pListBackShellCnctPt);
  SizeBackShellCnctPt = pListBackShellCnctPt ? pListBackShellCnctPt->Size() :0;
   
  if( SUCCEEDED(rc) && (1==SizeBackShellCnctPt) )
  {
    cout << "> the list of back shell connection point was correctly retrieved " <<endl << flush;
  }
  else 
  {
    cout << "> **** ERROR *** the list of back shell connection point wasn't correctly retrieved " <<endl << flush;  
    return 12;
  }

  spCBU = (*pListBackShellCnctPt)[1];
  if (NULL_var != spCBU)
    rc = spCBU-> QueryInterface(IID_CATIElbBackShellCnctPt ,(void**) & pElbBackShellCnctPt);
  delete pListBackShellCnctPt;
  pListBackShellCnctPt = NULL;

  if ( SUCCEEDED(rc) && NULL!= pElbBackShellCnctPt)
  { 
    cout << "> electrical back shell connection point OK " <<endl << flush;
  }
  else
  {
    cout << "ERROR : getting back shell connection point  failed " << endl << flush;
    return 13;
  } 


  // selecting the back shell : "First_BackShell"
  // ----------------------------------------------
  CATIElbBackShell * pFirst_BackShell = NULL;
  spCBU = (*pListElbBackShell)[1];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIElbBackShell,(void**) & pFirst_BackShell) ;

  delete pListElbBackShell;
  pListElbBackShell = NULL;
   
  if ( SUCCEEDED(rc) && pFirst_BackShell)
  { 
    cout << "> select first electrical back shell " <<endl << flush;
    CATUnicodeString InstanceName;
    CATIProduct_var  spFirstElecBackShellProduct = pFirst_BackShell  ;
    if ( NULL_var != spFirstElecBackShellProduct ) spFirstElecBackShellProduct->GetPrdInstanceName(InstanceName);		
    cout << "   instance name  :  "<< InstanceName.ConvertToChar() << endl << flush;
  }
  else
  {
    cout << "ERROR : getting first back shell failed " << endl << flush;
    return 14;
  } 

  // list the back shell connection points of the back shell
  CATListValCATBaseUnknown_var * pListBSCnctPt = NULL;
  rc = pFirst_BackShell->ListBackShellCnctPts(pListBSCnctPt);
  int SizeBSCnctPt = pListBSCnctPt ? pListBSCnctPt->Size() :0;
   
  if( SUCCEEDED(rc) && (1==SizeBSCnctPt) )
  {
    cout << "> the list of back shell connection point was correctly retrieved " <<endl << flush;
  }
  else 
  {
    cout << "> **** ERROR *** the list of back shell connection point wasn't correctly retrieved " <<endl << flush;  
    return 14;
  }

  delete pListBSCnctPt;
  pListBSCnctPt=NULL;
 
  
  // Connecting the second single connector with the first back shell
  // ---------------------------------------------------------------
  rc = pSecond_SingleConnector->ConnectBackShell(pElbBackShellCnctPt ,pFirst_BackShell, StatusOfGeometricalConstraint);
  if(SUCCEEDED(rc) && StatusOfGeometricalConstraint==0 )
  {
    cout << "> connect second single connector with first back shell succeeded " <<endl << flush;
  }
  else 
  {
    cout << "> **** ERROR **** connect first single connector with second back shell failed " <<endl << flush;
    return 15;

  }

  pElbBackShellCnctPt->Release();
  pElbBackShellCnctPt = NULL;
  pFirst_BackShell->Release();
  pFirst_BackShell = NULL;

  
  // connecting the first single connector with the second single connector
  // -----------------------------------------------------------------------

  // Retrieving the connector connection point defined on the first single connector
  // -------------------------------------------------------------------------------
  CATListValCATBaseUnknown_var * pListConnectorCnctPt = NULL;
  rc = pFirst_SingleConnector->ListConnectorCnctPts(pListConnectorCnctPt);
  int SizeListConnectorCnctPt = pListConnectorCnctPt  ? pListConnectorCnctPt ->Size() : 0;
  if(SUCCEEDED(rc) && (1 == SizeListConnectorCnctPt) )
  {
    cout << "> finding the connector connection point defined on the first single connector  succeeded " <<endl << flush;    
  }
  else
  {
    cout << ">****ERROR **** finding the connector connection point defined on the first single connector  Failed " <<endl << flush;
    return 16;    
  }

  CATIElbConnectorCnctPt * pElecConnectorCnctPt = NULL;
  spCBU = (*pListConnectorCnctPt)[1];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIElbConnectorCnctPt,(void **) & pElecConnectorCnctPt) ;
  delete pListConnectorCnctPt;
  pListConnectorCnctPt = NULL;
  if(SUCCEEDED(rc) && pElecConnectorCnctPt )
  {
    cout << "> first connector connection point ok " <<endl << flush;
  }
  else 
  {
    cout << "> **** ERROR **** first connector connection point pb query interface " <<endl << flush;
    return 17;   
  }
  
 
  rc = pFirst_SingleConnector->ConnectSingleConnector(pElecConnectorCnctPt,pSecond_SingleConnector,StatusOfGeometricalConstraint);
  if(SUCCEEDED(rc) && StatusOfGeometricalConstraint==0 )
  {
    cout << "> connect first single connector with second single connector succeeded " <<endl << flush;
  }
  else 
  {
    cout << "> **** ERROR **** connect first single connector with second single connector failed " <<endl << flush;
    return 17;    
  }  

  pElecConnectorCnctPt ->Release();
  pElecConnectorCnctPt = NULL;
  pFirst_SingleConnector->Release();
  pFirst_SingleConnector = NULL;
  pSecond_SingleConnector->Release();
  pSecond_SingleConnector = NULL;


  // --- Retrieving all equipments under the root product
  //     --------------------------------------------------
  CATListValCATBaseUnknown_var* pListElbEquipment = NULL;
  pListElbEquipment = piRootProduct->GetAllChildren(CATIElbEquipment::ClassName());
    
  int NumberOfEquipment = pListElbEquipment?pListElbEquipment->Size():0;
  if ( 0 < NumberOfEquipment ) 
  {
    cout << "> number of equipment : "<< NumberOfEquipment << endl << flush;
  }
  else
  {
    cout << "ERROR : no electrical equipment found  " << endl << flush;
    return 18;
  }

  // selecting the first equipment : "First_Equipment"
  // ------------------------------------------------------------ 
  CATIElbEquipment * pFirst_Equipment= NULL;
  spCBU = (*pListElbEquipment)[1];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIElbEquipment,(void**) &pFirst_Equipment);

  delete pListElbEquipment;
  pListElbEquipment=NULL;
  
  //     
  if ( SUCCEEDED(rc) && (NULL != pFirst_Equipment) )
  { 
    cout << "> select electrical equipment " <<endl << flush;
    CATIProduct_var  spFirstElecProduct = pFirst_Equipment ;
    CATUnicodeString InstanceName;
    if ( NULL_var != spFirstElecProduct ) spFirstElecProduct->GetPrdInstanceName(InstanceName);		
    cout << "   instance name  :  "<< InstanceName.ConvertToChar() << endl << flush;
  }
  else
  {
    cout << "ERROR : getting electrical equipment failed " << endl << flush;
    return 6;
  } 

  // --- Retrieving all mounting equipments under the root product
  //     ----------------------------------------------------------
  CATListValCATBaseUnknown_var* pListElbMountingEquipment = NULL;
  pListElbMountingEquipment = piRootProduct->GetAllChildren(CATIElbMountingEquipment::ClassName());
    
  int NumberOfMountingEquipment = pListElbMountingEquipment?pListElbMountingEquipment->Size():0;
  if ( 0 < NumberOfMountingEquipment ) 
  {
    cout << "> number of mounting equipment : "<< NumberOfMountingEquipment << endl << flush;
  }
  else
  {
    cout << "ERROR : no electrical mounting equipment found  " << endl << flush;
    return 18;
  }

  // selecting the mounting equipment : "First_MountingEquipment"
  // ------------------------------------------------------------ 
  CATIElbMountingEquipment * pFirst_MountingEquipment= NULL;
  spCBU = (*pListElbMountingEquipment)[1];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIElbMountingEquipment,(void**) &pFirst_MountingEquipment);
  
  //     
  if ( SUCCEEDED(rc) && (NULL != pFirst_MountingEquipment) )
  { 
    cout << "> select first electrical mounting equipment " <<endl << flush;
    CATIProduct_var  spFirstElecProduct = pFirst_MountingEquipment ;
    CATUnicodeString InstanceName;
    if ( NULL_var != spFirstElecProduct ) spFirstElecProduct->GetPrdInstanceName(InstanceName);		
    cout << "   instance name  :  "<< InstanceName.ConvertToChar() << endl << flush;
  }
  else
  {
    cout << "ERROR : getting electrical mounting equipment failed " << endl << flush;
    return 6;
  } 

    
  // selecting the Single connector : Third_SingleConnector"
  // --------------------------------------------------------  
  CATIElbSingleConnector * pThird_SingleConnector = NULL;
  spCBU = (*pListElbSingleConnector)[3];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIElbSingleConnector,(void**) &pThird_SingleConnector);
  
  delete pListElbSingleConnector;
  pListElbSingleConnector = NULL;
       
  if ( SUCCEEDED(rc) && NULL!= pThird_SingleConnector)
  { 
    cout << "> select third electrical third connector " <<endl << flush;
    CATUnicodeString InstanceName;
    CATIProduct_var  spThirdElecProduct = pThird_SingleConnector ;
    if ( NULL_var != spThirdElecProduct ) spThirdElecProduct->GetPrdInstanceName(InstanceName);		
    cout << "   instance name  :  "<< InstanceName.ConvertToChar() << endl << flush;
  }
  else
  {
    cout << "ERROR : getting electrical third single connector failed " << endl << flush;
    return 11;
  } 


  // connecting the third single connector with the first mounting equipment
  // -----------------------------------------------------------------------

  // Retrieving the cavity defined on the first mounting equipment
  // -------------------------------------------------------------
  CATListValCATBaseUnknown_var * pListCavities = NULL;
  rc = pFirst_MountingEquipment->ListCavities(pListCavities);
  int SizeListCavities = pListCavities  ? pListCavities->Size() : 0;
  if(SUCCEEDED(rc) && (1 == SizeListCavities) )
  {
    cout << "> finding the cavity defined on the first mounting equipment succeeded " <<endl << flush;    
  }
  else
  {
    cout << ">****ERROR **** finding the cavity defined on the first mounting equipment failed " <<endl << flush;
    return 16;   
  }

  CATIElbCavity * pElecCavity = NULL;
  spCBU = (*pListCavities)[1];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIElbCavity,(void **) & pElecCavity) ;

  delete pListCavities;
  pListCavities = NULL;

  if(SUCCEEDED(rc) && pElecCavity )
  {
    cout << "> query interface on first cavity ok " <<endl << flush;
  }
  else 
  {
    cout << "> **** ERROR **** pb query interface on first cavity " <<endl << flush;
    return 17;
    
  }

  // search a CATBaseUnknown on the connector

  CATBaseUnknown * pUnkOfConnector = NULL;
  rc = pThird_SingleConnector->QueryInterface(IID_CATBaseUnknown,(void**) &pUnkOfConnector);
       
  if ( FAILED(rc) || (NULL == pUnkOfConnector))  
  {
    cout << "ERROR : getting a CATBaseUnknow on the third single connector failed " << endl << flush;
    return 17;
  }

  pThird_SingleConnector->Release();
  pThird_SingleConnector=NULL;

  //
  // connecting the first mounting equipment and the third single connector

  rc = pFirst_MountingEquipment->AddDevice(pElecCavity,pUnkOfConnector,StatusOfGeometricalConstraint);
  if(SUCCEEDED(rc) && StatusOfGeometricalConstraint==0 )
  {
    cout << "> connect first mounting equipment with third single connector succeeded " <<endl << flush;
  }
  else 
  {
    cout << "> **** ERROR **** connect first mounting equipment with third single connector failed " <<endl << flush;
    return 17;    
  } 


  // release on pointers

  pFirst_MountingEquipment->Release();
  pFirst_MountingEquipment=NULL;

  pElecCavity->Release();
  pElecCavity=NULL;

  pUnkOfConnector->Release();
  pUnkOfConnector=NULL;


  //
  //=================================================================================================
  // connecting the first equipment with the second mounting equipment
  //=================================================================================================
  //

  // selecting the mounting equipment : "Second_MountingEquipment"
  // ------------------------------------------------------------- 
  CATIElbMountingEquipment * pSecond_MountingEquipment= NULL;
  spCBU = (*pListElbMountingEquipment)[2];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIElbMountingEquipment,(void**) &pSecond_MountingEquipment);

  delete pListElbMountingEquipment;
  pListElbMountingEquipment=NULL;

  //     
  if ( SUCCEEDED(rc) && (NULL != pSecond_MountingEquipment) )
  { 
    cout << "> select second electrical mounting equipment " <<endl << flush;
    CATIProduct_var  spFirstElecProduct = pSecond_MountingEquipment ;
    CATUnicodeString InstanceName;
    if ( NULL_var != spFirstElecProduct ) spFirstElecProduct->GetPrdInstanceName(InstanceName);		
    cout << "   instance name  :  "<< InstanceName.ConvertToChar() << endl << flush;
  }
  else
  {
    cout << "ERROR : getting electrical mounting equipment failed " << endl << flush;
    return 6;
  }

  // Retrieving the cavity defined on the second mounting equipment
  // --------------------------------------------------------------
  
  rc = pSecond_MountingEquipment->ListCavities(pListCavities);
  SizeListCavities = pListCavities  ? pListCavities->Size() : 0;
  if(SUCCEEDED(rc) && (1 == SizeListCavities) )
  {
    cout << "> finding the cavity defined on the first equipment succeeded " <<endl << flush;    
  }
  else
  {
    cout << ">****ERROR **** finding the cavity defined on the first equipment failed " <<endl << flush;
    return 16;    
  }

  spCBU = (*pListCavities)[1];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIElbCavity,(void **) & pElecCavity) ;

  delete pListCavities;
  pListCavities = NULL;

  if(SUCCEEDED(rc) && pElecCavity )
  {
    cout << "> query interface on first cavity ok " <<endl << flush;
  }
  else 
  {
    cout << "> **** ERROR **** pb query interface on first cavity " <<endl << flush;
    return 17;   
  }


  // search a CATBaseUnknown on the first equipment

  CATBaseUnknown * pUnkOfEquipment = NULL;
  rc = pFirst_Equipment->QueryInterface(IID_CATBaseUnknown,(void**) &pUnkOfEquipment);
       
  if ( FAILED(rc) || (NULL == pUnkOfEquipment))  
  {
    cout << "ERROR : getting a CATBaseUnknow on the first equipment failed " << endl << flush;
    return 17;
  }

  pFirst_Equipment->Release();
  pFirst_Equipment=NULL;


  //
  // connecting the first equipment and the second mounting equipment 

  rc = pSecond_MountingEquipment->AddDevice(pElecCavity,pUnkOfEquipment,StatusOfGeometricalConstraint);
  if(SUCCEEDED(rc) && StatusOfGeometricalConstraint==0 )
  {
    cout << "> connect first mounting equipment with third single connector succeeded " <<endl << flush;
  }
  else 
  {
    cout << "> **** ERROR **** connect first mounting equipment with third single connector failed " <<endl << flush;
    return 17;    
  }

  if(pElecCavity ) pElecCavity ->Release();
  pElecCavity  = NULL;


  pSecond_MountingEquipment->Release();
  pSecond_MountingEquipment=NULL;

  pUnkOfEquipment->Release();
  pUnkOfEquipment=NULL;

  piRootProduct -> Release();
  piRootProduct = NULL ;


  //--------------------------------------------------------------------
  // 8. Epilogue  
  //--------------------------------------------------------------------
  CATBoolean iSavePointedIfNecessary = TRUE;  
  rc = CATDocumentServices::SaveAs ( *pDoc,argv[2],"CATProduct",iSavePointedIfNecessary );
  if (SUCCEEDED(rc))
  {
    cout << "> document saved " << endl << flush;
  }
  else
  {
    cout << "ERROR in save document" << endl << flush;
    return 18;
  }

  // --- removing document from session 
  rc = CATDocumentServices::Remove(*pDoc);
  if (SUCCEEDED(rc))
  {
    cout << "> document removed " << endl << flush;
  }
  else
  {
    cout << "ERROR in removing document" << endl << flush;
    return 19;
  }

  // --- closing the session
  rc = ::Delete_Session(sessionName);
  if (SUCCEEDED(rc))
    cout << "> session deleted " << endl << flush;
  else
  {
    cout << "ERROR in deleting session" << endl << flush;
    return 20;
  }
  cout << "----------------------------------------------------------------" << endl << flush;
  cout << endl << flush;
  cout << endl << flush;
  
  //
  return (0);
}
