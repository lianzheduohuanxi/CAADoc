// =================================
// COPYRIGHT DASSAULT SYSTEMES 2009
// ================================= 

//=============================================================================
//  Abstract of Use Case "CAAElecConnect":
//  ---------------------------------------------
//
//  This Use Case illustrates how to connect Electrical Devices with Connect API. 
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
//  3. Retrieving all devices under the Root Product 
//
//  4. Connecting the devices.
//
//  5. Saving the final document
//
//  6. removing document from session 
//
//  7. closing the session
//
//  Return Errors:
//  -------------
//  1 - ERROR in creating the session
//  2 - ERROR in opening an existing document.
//  3 - ERROR in getting root product
//  4 - ERROR in electrical environment initialization 
//  5 - ERROR if electrical single connector not found in assembly 
//  6 - ERROR if failed to get SIC
//  7 - ERROR if backshell not found in assembly 
//  8 - ERROR if failed to get backshell
//  9 - ERROR if Shells not found in assembly 
// 10 - ERROR if failed to get Shells
// 11 - ERROR if Mounting Equipments not found in assembly 
// 12 - ERROR if failed to get Mounting Equipments
// 13 - ERROR if Equipment not found in assembly 
// 14 - ERROR if failed to get Equipment.
// 15 - ERROR if the connection between the Mounting Equipments failed.
// 16 - ERROR if the connection between single connector and Mounting Equipment2 failed.
// 17 - ERROR if disconnect batween single connector and Mounting Equipment2 failed.
// 18 - ERROR if the connection between Shell1 and Mounting Equipment2 failed.
// 19 - ERROR if disconnect batween Shell1 and Mounting Equipment2 failed.
// 20 - ERROR if the connection between Equipment and Mounting Equipment2 failed.
// 21 - ERROR if the connection between SIC and Equipment failed.
// 22 - ERROR if the Disconnect between SIC and Equipment failed.
// 23 - ERROR if the connection between Shell1 and Equipment failed.
// 24 - ERROR if the connection between Shell1 and Shell2 failed.
// 25 - ERROR if the connection between BackShell and Shell2 failed.
// 26 - ERROR if the Disconnect between BackShell and Shell2 failed.
// 27 - ERROR if the connection between SIC and Shell2 failed.
// 28 - ERROR in Save document.
// 29 - ERROR in removing document.
// 30 - ERROR in deleting session.
// 31 - ERROR if GetConnectedDevice failed.
// 32-40 - ERROR if Check on already connected devices failed.
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  mkrun -c "CAAElecConnect input.CATProduct output.CATProduct" where the prefix "input" is the 
//  entire pathname of the directory in which the document is to be found and the
//  name of the document itself.
//  output.CATProduct - the path of the file to save in the main document.
//
//
//  You may reference the supplied CATProduct document called "TOP.CATProduct" 
//  found in the 'WS'/'OS'/resources/graphic/CAAElecConnect directory if under Unix.
//      In this case, 'OS' can be any of the following: 
//         aix_a for IBM
//         hpux_a for HP
//         irix_a for SGI
//         solaris_a for SUN
//  Under Windows, the path would indicate:  'WS'\intel_a\resources\graphic\CAAElecConnect directory. 
//
//
//====================================================================================================

// C++ include ( result display )

//System
#include "CATBaseUnknown.h"
#include "CATBoolean.h"
#include <iostream.h>
#include "CATLISTV_CATBaseUnknown.h"

// ObjectModelerBase interfaces
#include "CATSessionServices.h"    // managing session
#include "CATDocumentServices.h"   // managing documents in session
#include "CATDocument.h"           // manipulating documents
#include "CATIDocRoots.h"          // browsing root objects in documents
#include "CATSession.h"

// ElecDeviceItf interfaces 
#include "CATIProduct.h"             // managing products   
#include "CATIElbSingleConnector.h"  // managing a single connector
#include "CATIElbBackShell.h"        // managing a back shell
#include "CATIElbEquipment.h"        // managing an equipemnt
#include "CATIElbMountingEquipment.h"  // managing a mounting equipment
#include "CATIElbCavity.h"  // managing a mounting equipment
#include "CATIElbConnectorShell.h"
#include "CATIElbDeviceInstance.h"

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
  HRESULT RC = ::Create_Session(sessionName,pSession);
  if ((SUCCEEDED(RC)) && (NULL != pSession))
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
  RC = CATDocumentServices::OpenDocument(argv[1], pDoc);
  if (SUCCEEDED(RC) && (NULL != pDoc))
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
  RC = pDoc->QueryInterface(IID_CATIDocRoots,(void**) &pDocRoots);
  if ( FAILED(RC) || (NULL==pDocRoots) ) return 3;
  CATListValCATBaseUnknown_var* pListRootProduct = pDocRoots->GiveDocRoots();
  pDocRoots->Release();
  pDocRoots=NULL;
  
  if ( pListRootProduct && pListRootProduct->Size() )
  {  
    CATBaseUnknown_var spCBU ((*pListRootProduct)[1]);
    if (NULL_var != spCBU)
      RC = spCBU->QueryInterface(IID_CATIProduct,(void**) &piRootProduct );
    if (pListRootProduct) delete pListRootProduct;
    pListRootProduct = NULL;
    //
    if  (SUCCEEDED(RC) && (NULL != piRootProduct))
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
  
  RC = pDoc->QueryInterface(IID_CATIEleDocServices,(void**) &piElecDocServices );
  if ( SUCCEEDED(RC) && piElecDocServices )
  {
    RC = piElecDocServices->Initialize();
  }
  
  if (SUCCEEDED(RC) )
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
  // 3. Retrieving all electrical Devices under the root product   
  //--------------------------------------------------------------------

  CATIElbSingleConnector * pSingleConnector = NULL;
  CATIElbBackShell * pBackShell = NULL;
  CATIElbConnectorShell * pShell1 = NULL;
  CATIElbConnectorShell * pShell2 = NULL;
  CATIElbMountingEquipment * pME1 = NULL;
  CATIElbMountingEquipment * pME2 = NULL;
  CATIElbEquipment * pEquipment = NULL;
  CATIElbCavity * pCavity = NULL;
  CATListValCATBaseUnknown_var* pCavities = NULL;  
  CATIElbDeviceInstance * pDevInst1 = NULL;
  CATIElbDeviceInstance * pDevInst2 = NULL;
  CATBaseUnknown_var spCBU = NULL_var;
  CATBaseUnknown * pCnctPt = NULL;
  CATIElbDeviceInstance * pdevinst = NULL;
  CATBaseUnknown * pdevice = NULL;
  CATBaseUnknown * pOCnctPt = NULL;
  CATListValCATBaseUnknown_var * CavityCnctPts = NULL;    
  CATBaseUnknown_var hccp = NULL_var;
  CATBaseUnknown_var hconn2 = NULL_var;
  CATIProduct_var hPrd1;
  CATIProduct_var hPrd2;
  CATIProduct_var hRootInstPrd1;
  CATIProduct_var hRootInstPrd2;

  int retCode = 0;
  CATBoolean iSavePointedIfNecessary = TRUE;
  int StatusOfGeometricalConstraint = 2;
  int NumberOfBS = 0;
  int NumberOfSingleConnector = 0;
  int NumberOfShells = 0;
  int NumberOfME = 0;
  int NumberOfEquipments = 0;
  CATListValCATBaseUnknown_var* pListElbSingleConnector = NULL;
  CATListValCATBaseUnknown_var* pListElbBackShell = NULL;
  CATListValCATBaseUnknown_var* pListShell = NULL;
  CATListValCATBaseUnknown_var* pListMountingEquip = NULL;
  CATListValCATBaseUnknown_var* pListEquipments = NULL;

  //SIC
  pListElbSingleConnector = piRootProduct->GetAllChildren(CATIElbSingleConnector::ClassName());
  
  NumberOfSingleConnector = pListElbSingleConnector?pListElbSingleConnector->Size():0;
  if ( 0 < NumberOfSingleConnector ) 
  {
    cout << "> number of single connector part found : "<< NumberOfSingleConnector << endl << flush;
  }
  else
  {
    cout << "ERROR : no electrical single connector found  " << endl << flush;
    retCode = 5;
    goto EscapeWay;
  }

  // selecting the Single connector 
  // --------------------------------------------------------  
  spCBU = ((*pListElbSingleConnector)[1]);
  if (NULL_var != spCBU)
    RC = spCBU->QueryInterface(IID_CATIElbSingleConnector,(void**) &pSingleConnector);

  if (SUCCEEDED(RC) && (NULL != pSingleConnector))
  { 
    cout << "> SIC found. " <<endl << flush;  
  }
  else
  {
    cout << "ERROR : getting SIC failed " << endl << flush;
    delete pListElbSingleConnector;
    pListElbSingleConnector = NULL;
    retCode = 6;
    goto EscapeWay;
  }
  delete pListElbSingleConnector;
  pListElbSingleConnector = NULL;

  //BackShell
  pListElbBackShell = piRootProduct->GetAllChildren(CATIElbBackShell::ClassName());
  
  NumberOfBS = pListElbBackShell?pListElbBackShell->Size():0;
  if ( 0 < NumberOfBS ) 
  {
    cout << "> number of BackShell parts found : "<< NumberOfBS<< endl << flush;
  }
  else
  {
    cout << "ERROR : no BackShell found  " << endl << flush;
    retCode = 7;
    goto EscapeWay;
  }

  // selecting the BackShell 
  // --------------------------------------------------------    
  spCBU = ((*pListElbBackShell)[1]);
  if (NULL_var != spCBU)
    RC = spCBU->QueryInterface(IID_CATIElbBackShell,(void**) &pBackShell);

  if (SUCCEEDED(RC) && (NULL != pBackShell))
  { 
    cout << "> BackShell found. " <<endl << flush;  
  }
  else
  {
    cout << "ERROR : getting BackShell failed " << endl << flush;
    delete pListElbBackShell;
    pListElbBackShell = NULL;
    retCode = 8;
    goto EscapeWay;
  }
  delete pListElbBackShell;
  pListElbBackShell = NULL;

  //Shells
  pListShell = piRootProduct->GetAllChildren(CATIElbConnectorShell::ClassName());
  
  NumberOfShells = pListShell?pListShell->Size():0;
  if ( 2 == NumberOfShells ) 
  {
    cout << "> number of Shell part found : "<< NumberOfShells<< endl << flush;
  }
  else
  {
    cout << "ERROR : no Shell found  " << endl << flush;
    retCode = 9;
    goto EscapeWay;
  }

  // selecting the Shells
  // --------------------------------------------------------  
  spCBU = ((*pListShell)[1]);
  if (NULL_var != spCBU)
    RC = spCBU->QueryInterface(IID_CATIElbConnectorShell,(void**) &pShell1);

  spCBU = ((*pListShell)[2]);
  if (NULL_var != spCBU)
    RC = spCBU->QueryInterface(IID_CATIElbConnectorShell,(void**) &pShell2);

  if (SUCCEEDED(RC) && (NULL != pShell1) && (NULL != pShell2))
  { 
    cout << "> Shells found. " <<endl << flush;  
  }
  else
  {
    cout << "ERROR : getting Shells failed " << endl << flush;
    delete pListShell;
    pListShell = NULL;
    retCode = 10;
    goto EscapeWay;
  }
  delete pListShell;
  pListShell = NULL;

  //Mounting Equipments
  pListMountingEquip = piRootProduct->GetAllChildren(CATIElbMountingEquipment::ClassName());
  
  NumberOfME = pListMountingEquip?pListMountingEquip->Size():0;
  if ( 2 == NumberOfME ) 
  {
    cout << "> number of Mounting Equipments part found : "<< NumberOfME<< endl << flush;
  }
  else
  {
    cout << "ERROR : no Mounting Equipments found  " << endl << flush;
    retCode = 11;
    goto EscapeWay;
  }

  // selecting the Mounting Equipments
  // --------------------------------------------------------  
  spCBU = ((*pListMountingEquip)[1]);
  if (NULL_var != spCBU)
    RC = spCBU->QueryInterface(IID_CATIElbMountingEquipment,(void**) &pME1);

  spCBU = ((*pListMountingEquip)[2]);
  if (NULL_var != spCBU)
    RC = spCBU->QueryInterface(IID_CATIElbMountingEquipment,(void**) &pME2);

  if (SUCCEEDED(RC) && (NULL != pME1) && (NULL != pME2))
  { 
    cout << "> Mounting Equipments found. " <<endl << flush;  
  }
  else
  {
    cout << "ERROR : getting Mounting Equipments failed " << endl << flush;
    delete pListMountingEquip;
    pListMountingEquip = NULL;
    retCode = 12;
    goto EscapeWay;
  }
  delete pListMountingEquip;
  pListMountingEquip = NULL;

  //Equipment
  pListEquipments = piRootProduct->GetAllChildren(CATIElbEquipment::ClassName());
  
  NumberOfEquipments = pListEquipments?pListEquipments->Size():0;
  if ( 0 < NumberOfEquipments ) 
  {
    cout << "> number of Equipment part found : "<< NumberOfEquipments<< endl << flush;
  }
  else
  {
    cout << "ERROR : no Equipments found  " << endl << flush;
    retCode = 13;
    goto EscapeWay;
  }

  // selecting the Equipment
  // --------------------------------------------------------  
  spCBU = ((*pListEquipments)[1]);
  if (NULL_var != spCBU)
    RC = spCBU->QueryInterface(IID_CATIElbEquipment,(void**) &pEquipment);

  if (SUCCEEDED(RC) && (NULL != pEquipment))
  { 
    cout << "> Equipment found. " <<endl << flush;  
  }
  else
  {
    cout << "ERROR : getting Equipment failed " << endl << flush;
    delete pListEquipments;
    pListEquipments = NULL;
    retCode = 14;
    goto EscapeWay;
  }
  delete pListEquipments;
  pListEquipments = NULL;
  
  //--------------------------------------------------------------------
  // 4. Connecting the devices 
  //--------------------------------------------------------------------
  //1. Connect MountingEquipment1 to MountingEquipment2
  StatusOfGeometricalConstraint = 2;
  
  RC = pME1->ListCavities(pCavities);

  if((NULL != pCavities) && (pCavities->Size()==1))
  {
    CATBaseUnknown_var hCavity((*pCavities)[1]);

    if(NULL_var != hCavity)
    {
      RC = hCavity->QueryInterface(IID_CATIElbCavity , (void**)&pCavity);

      RC = hCavity->QueryInterface(IID_CATBaseUnknown , (void**)&pCnctPt);
    }

    if ((NULL != pME1) && (NULL != pCavity) && (NULL != pME2))
    {
      RC = pME2->Connect(pCavity,pME1,StatusOfGeometricalConstraint);
    }
  }

  if(SUCCEEDED(RC) && (0 == StatusOfGeometricalConstraint))
  {
    cout << "> connect MountingEquipment1 with MountingEquipment2 succeeded " <<endl << flush;
  }
  else
  {
    cout << "> **** ERROR **** connect MountingEquipment1 with MountingEquipment2 failed " <<endl << flush;
    retCode = 15;
    goto EscapeWay;
  }

  //When the devices are already connected

  if (NULL != pCavity)
  {
    RC = pME2->Connect(pCavity,pME1,StatusOfGeometricalConstraint);
  }

  if(S_FALSE == RC)
  {
    cout << "> **OK** Devices are already connected " <<endl << flush;
  }
  else
  {
    cout << "> **** ERROR **** Check on already connected devices failed " <<endl << flush;
    retCode = 32;
    goto EscapeWay;
  }

  // Test GetConnectedDevice on CATIElbDeviceInstance

  RC = pME2->ListCavityCnctPts(CavityCnctPts);

  if(SUCCEEDED(RC) && (NULL != CavityCnctPts) && (CavityCnctPts->Size()>0))
    hccp = ((*CavityCnctPts)[1]);

  RC = pME1->QueryInterface(IID_CATIElbDeviceInstance, (void **)&pdevinst);

  if((NULL != pdevinst) && (NULL != pCnctPt))
    RC = pdevinst->GetConnectedDevice(pCnctPt,pdevice,pOCnctPt);

  if(NULL != pOCnctPt)
    hconn2 = pOCnctPt;

  hPrd1 = pdevice;
  hPrd2 = pME2;

  if( NULL != piRootProduct && NULL_var != hPrd1 && NULL_var != hPrd2)
  {
    hRootInstPrd1 = hPrd1 ->FindInstance(piRootProduct);
    hRootInstPrd2 = hPrd2->FindInstance(piRootProduct);
  }

  if(SUCCEEDED(RC) && (NULL_var != hRootInstPrd1) && (NULL_var != hconn2) && (hRootInstPrd1->IsEqual(hRootInstPrd2) && (hconn2->IsEqual(hccp))))
  {
    cout << "> GetConnectedDevice succeeded " <<endl << flush;
  }
  else
  {
    cout << "> **** ERROR **** GetConnectedDevice failed " <<endl << flush;
    retCode = 31;
    goto EscapeWay;
  }

  //2. Connect SIC to ME
  if(NULL != pCavities)
  {
    delete pCavities;
    pCavities = NULL;
  }

  RC = pME2->ListCavities(pCavities);

  if((NULL != pCavities) && (pCavities->Size()==1))
  {
    CATBaseUnknown_var hCavity((*pCavities)[1]);

    if(NULL != pCavity)
    {
      pCavity -> Release();
      pCavity = NULL ;
    }

    if(NULL_var!=hCavity)
      RC = hCavity->QueryInterface(IID_CATIElbCavity , (void**)&pCavity);

    if ((NULL != pSingleConnector) && (NULL != pCavity) && (NULL !=pME2))
    {
      RC = pSingleConnector->Connect(pCavity,pME2,StatusOfGeometricalConstraint);
    }
  }

  if(SUCCEEDED(RC) && (0 == StatusOfGeometricalConstraint))
  {
    cout << "> connect single connector with MountingEquipment2 succeeded " <<endl << flush;
  }
  else
  {
    cout << "> **** ERROR **** connect single connector with MountingEquipment2 failed " <<endl << flush;
    retCode = 16;
    goto EscapeWay;
  }

  //When the devices are already connected

  if (NULL != pCavity)
  {
    RC = pSingleConnector->Connect(pCavity,pME2,StatusOfGeometricalConstraint);
  }

  if(S_FALSE == RC)
  {
    cout << "> **OK** Devices are already connected " <<endl << flush;
  }
  else
  {
    cout << "> **** ERROR **** Check on already connected devices failed " <<endl << flush;
    retCode = 33;
    goto EscapeWay;
  }

  //3. Disconnect SIC from ME

  RC = pSingleConnector->QueryInterface(IID_CATIElbDeviceInstance, (void **)&pDevInst1);

  RC = pME2->QueryInterface(IID_CATIElbDeviceInstance, (void **)&pDevInst2);

  if(SUCCEEDED(RC))
  {
    RC = pDevInst1->Disconnect(pDevInst2);

    if(SUCCEEDED(RC))
    {
      cout << "> Disconnect single connector from MountingEquipment2 succeeded " <<endl << flush;
    }
    else
    {
      cout << "> **** ERROR **** Disconnect single connector from MountingEquipment2 failed " <<endl << flush;
      retCode = 17;
      goto EscapeWay;
    }
  }

  //4. Connect Shell to ME
  if(NULL != pCavities)
  {
    delete pCavities;
    pCavities = NULL;
  }

  RC = pME2->ListCavities(pCavities);

  if((NULL != pCavities) && (pCavities->Size()==1))
  {
    CATBaseUnknown_var hCavity((*pCavities)[1]);

    if(NULL != pCavity)
    {
      pCavity -> Release();
      pCavity = NULL ;
    }

    if(NULL_var!=hCavity)
      RC = hCavity->QueryInterface(IID_CATIElbCavity , (void**)&pCavity);

    if ((NULL != pShell1) && (NULL != pCavity) && (NULL !=pME2))
    {
      RC = pShell1->Connect(pCavity,pME2,StatusOfGeometricalConstraint);
    }
  }

  if(SUCCEEDED(RC) && (0 == StatusOfGeometricalConstraint))
  {
    cout << "> connect Shell1 with MountingEquipment2 succeeded " <<endl << flush;
  }
  else
  {
    cout << "> **** ERROR **** connect Shell1 with MountingEquipment2 failed " <<endl << flush;
    retCode = 18;
    goto EscapeWay;
  }

  //When the devices are already connected

  if (NULL != pCavity)
  {
    RC = pShell1->Connect(pCavity,pME2,StatusOfGeometricalConstraint);
  }

  if(S_FALSE == RC)
  {
    cout << "> **OK** Devices are already connected " <<endl << flush;
  }
  else
  {
    cout << "> **** ERROR **** Check on already connected devices failed " <<endl << flush;
    retCode = 34;
    goto EscapeWay;
  }

  //5. Disconnect Shell from ME
  if(NULL != pDevInst1)
  {
    pDevInst1 -> Release();
    pDevInst1 = NULL ;
  }
  
  RC = pShell1->QueryInterface(IID_CATIElbDeviceInstance, (void **)&pDevInst1);  

  if(SUCCEEDED(RC))
  {
    RC = pDevInst1->Disconnect(pDevInst2);

    if(SUCCEEDED(RC))
    {
      cout << "> Disconnect Shell1 with MountingEquipment2 succeeded " <<endl << flush;
    }
    else
    {
      cout << "> **** ERROR **** Disconnect Shell1 with MountingEquipment2 failed " <<endl << flush;
      retCode = 19;
      goto EscapeWay;
    }
  }

  //6. Connect Equipment to ME
  if(NULL != pCavities)
  {
    delete pCavities;
    pCavities = NULL;
  }
  
  RC = pME2->ListCavities(pCavities);

  if((NULL != pCavities) && (pCavities->Size()==1))
  {
    CATBaseUnknown_var hCavity((*pCavities)[1]);

    if(NULL != pCavity)
    {
      pCavity -> Release();
      pCavity = NULL ;
    }   

    if(NULL_var!=hCavity)
      RC = hCavity->QueryInterface(IID_CATIElbCavity , (void**)&pCavity);

    if ((NULL != pEquipment) && (NULL != pCavity) && (NULL !=pME2))
    {
      RC = pEquipment->Connect(pCavity,pME2,StatusOfGeometricalConstraint);
    }
  }

  if(SUCCEEDED(RC) && (0 == StatusOfGeometricalConstraint))
  {
    cout << "> connect Equipment with MountingEquipment2 succeeded " <<endl << flush;
  }
  else
  {
    cout << "> **** ERROR **** connect Equipment with MountingEquipment2 failed " <<endl << flush;
    retCode = 20;
    goto EscapeWay;
  }

  //When the devices are already connected

  if (NULL != pCavity)
  {
    RC = pEquipment->Connect(pCavity,pME2,StatusOfGeometricalConstraint);
  }

  if(S_FALSE == RC)
  {
    cout << "> **OK** Devices are already connected " <<endl << flush;
  }
  else
  {
    cout << "> **** ERROR **** Check on already connected devices failed " <<endl << flush;
    retCode = 35;
    goto EscapeWay;
  }

  //7. Connect SIC to Equipment
  if(NULL != pCavities)
  {
    delete pCavities;
    pCavities = NULL;
  }
  
  RC = pEquipment->ListCavities(pCavities);

  if((NULL != pCavities) && (pCavities->Size()==1))
  {
    CATBaseUnknown_var hCavity((*pCavities)[1]);

    if(NULL != pCavity)
    {
      pCavity -> Release();
      pCavity = NULL ;
    }

    if(NULL_var!=hCavity)
      RC = hCavity->QueryInterface(IID_CATIElbCavity , (void**)&pCavity);

    if ((NULL != pEquipment) && (NULL != pCavity) && (NULL !=pME2))
    {
      RC = pSingleConnector->Connect(pCavity,pEquipment,StatusOfGeometricalConstraint);
    }
  }

  if(SUCCEEDED(RC) && (0 == StatusOfGeometricalConstraint))
  {
    cout << "> connect single connector with Equipment succeeded " <<endl << flush;
  }
  else
  {
    cout << "> **** ERROR **** connect single connector with Equipment failed " <<endl << flush;
    retCode = 21;
    goto EscapeWay;
  }

  //When the devices are already connected

  if (NULL != pCavity)
  {
    RC = pSingleConnector->Connect(pCavity,pEquipment,StatusOfGeometricalConstraint);
  }

  if(S_FALSE == RC)
  {
    cout << "> **OK** Devices are already connected " <<endl << flush;
  }
  else
  {
    cout << "> **** ERROR **** Check on already connected devices failed " <<endl << flush;
    retCode = 36;
    goto EscapeWay;
  }

  //8. Disconnect SIC from Equipment
  if(NULL != pDevInst1)
  {
    pDevInst1 -> Release();
    pDevInst1 = NULL ;
  }
  if(NULL != pDevInst2)
  {
    pDevInst2 -> Release();
    pDevInst2 = NULL ;
  }
  
  RC = pSingleConnector->QueryInterface(IID_CATIElbDeviceInstance, (void **)&pDevInst1);  

  RC = pEquipment->QueryInterface(IID_CATIElbDeviceInstance, (void **)&pDevInst2);

  if(SUCCEEDED(RC))
  {
    RC = pDevInst1->Disconnect(pDevInst2);

    if(SUCCEEDED(RC))
    {
      cout << "> Disconnect single connector from Equipment succeeded " <<endl << flush;
    }
    else
    {
      cout << "> **** ERROR **** Disconnect single connector from Equipment failed " <<endl << flush;
      retCode = 22;
      goto EscapeWay;
    }
  }

  //9. Connect Shell to Equipment
  if(NULL != pCavities)
  {
    delete pCavities;
    pCavities = NULL;
  }

  RC = pEquipment->ListCavities(pCavities);

  if((NULL != pCavities) && (pCavities->Size()==1))
  {
    CATBaseUnknown_var hCavity((*pCavities)[1]);

    if(NULL != pCavity)
    {
      pCavity -> Release();
      pCavity = NULL ;
    }

    if(NULL_var!=hCavity)
      RC = hCavity->QueryInterface(IID_CATIElbCavity , (void**)&pCavity);

    if ((NULL != pShell1) && (NULL != pCavity) && (NULL !=pME2))
    {
      RC = pShell1->Connect(pCavity,pEquipment,StatusOfGeometricalConstraint);
    }
  }

  if(SUCCEEDED(RC) && (0 == StatusOfGeometricalConstraint))
  {
    cout << "> connect Shell1 with Equipment succeeded " <<endl << flush;
  }
  else
  {
    cout << "> **** ERROR **** connect Shell1 with Equipment failed " <<endl << flush;
    retCode = 23;
    goto EscapeWay;
  }

  //When the devices are already connected

  if (NULL != pCavity)
  {
    RC = pShell1->Connect(pCavity,pEquipment,StatusOfGeometricalConstraint);
  }

  if(S_FALSE == RC)
  {
    cout << "> **OK** Devices are already connected " <<endl << flush;
  }
  else
  {
    cout << "> **** ERROR **** Check on already connected devices failed " <<endl << flush;
    retCode = 37;
    goto EscapeWay;
  }

  //10. Connect Shell1 to Shell2

  if ((NULL != pShell1) && (NULL != pShell2))
  {
    RC = pShell1->Connect(pShell2,StatusOfGeometricalConstraint);
  }

  if(SUCCEEDED(RC) && (0 == StatusOfGeometricalConstraint))
  {
    cout << "> connect Shell1 with Shell2 succeeded " <<endl << flush;
  }
  else
  {
    cout << "> **** ERROR **** connect Shell1 with Shell2 failed " <<endl << flush;
    retCode =24;
    goto EscapeWay;
  }

  //When the devices are already connected

  RC = pShell1->Connect(pShell2,StatusOfGeometricalConstraint); 

  if(S_FALSE == RC)
  {
    cout << "> **OK** Devices are already connected " <<endl << flush;
  }
  else
  {
    cout << "> **** ERROR **** Check on already connected devices failed " <<endl << flush;
    retCode = 38;
    goto EscapeWay;
  }

  //11. Connect BackShell to Shell2

  if ((NULL != pBackShell) && (NULL != pShell2))
  {
    RC = pShell2->Connect(pBackShell,StatusOfGeometricalConstraint);
  }

  if(SUCCEEDED(RC) && (0 == StatusOfGeometricalConstraint))
  {
    cout << "> connect BackShell with Shell2 succeeded " <<endl << flush;
  }
  else
  {
    cout << "> **** ERROR **** connect BackShell with Shell2 failed " <<endl << flush;
    retCode = 25;
    goto EscapeWay;
  }

  //When the devices are already connected

  RC = pShell2->Connect(pBackShell,StatusOfGeometricalConstraint);

  if(S_FALSE == RC)
  {
    cout << "> **OK** Devices are already connected " <<endl << flush;
  }
  else
  {
    cout << "> **** ERROR **** Check on already connected devices failed " <<endl << flush;
    retCode = 39;
    goto EscapeWay;
  }

  //12. DisConnect BackShell from Shell2
  if(NULL != pDevInst1)
  {
    pDevInst1 -> Release();
    pDevInst1 = NULL ;
  }
  if(NULL != pDevInst2)
  {
    pDevInst2 -> Release();
    pDevInst2 = NULL ;
  }

  RC = pBackShell->QueryInterface(IID_CATIElbDeviceInstance, (void **)&pDevInst1);  

  RC = pShell2->QueryInterface(IID_CATIElbDeviceInstance, (void **)&pDevInst2);

  if(SUCCEEDED(RC) && (NULL != pDevInst1))
  {
    RC = pDevInst1->Disconnect(pDevInst2);

    if(SUCCEEDED(RC))
    {
      cout << "> Disconnect BackShell from Shell2 succeeded " <<endl << flush;
    }
    else
    {
      cout << "> **** ERROR **** Disconnect BackShell from Shell2 failed " <<endl << flush;
      retCode = 26;
      goto EscapeWay;
    }
  }

  //13. Connect SIC to Shell

  if(NULL != pCavities)
  {
    delete pCavities;
    pCavities = NULL;
  }

  RC = pShell2->ListCavities(pCavities);

  if((NULL != pCavities) && (pCavities->Size()==1))
  {
    CATBaseUnknown_var hCavity((*pCavities)[1]);

    if(NULL != pCavity)
    {
      pCavity -> Release();
      pCavity = NULL ;
    }

    if(NULL_var!=hCavity)
      RC = hCavity->QueryInterface(IID_CATIElbCavity , (void**)&pCavity);

    if ((NULL != pShell1) && (NULL != pCavity) && (NULL !=pME2))
    {
      RC = pSingleConnector->Connect(pCavity,pShell2,StatusOfGeometricalConstraint);
    }
  }

  if(SUCCEEDED(RC) && (0 == StatusOfGeometricalConstraint))
  {
    cout << "> connect single connector with Shell2 succeeded " <<endl << flush;
  }
  else
  {
    cout << "> **** ERROR **** connect single connector with Shell2 failed " <<endl << flush;
    retCode =27;
    goto EscapeWay;
  }

  //When the devices are already connected

  if (NULL != pCavity)
  {
    RC = pSingleConnector->Connect(pCavity,pShell2,StatusOfGeometricalConstraint);
  }

  if(S_FALSE == RC)
  {
    cout << "> **OK** Devices are already connected " <<endl << flush;
  }
  else
  {
    cout << "> **** ERROR **** Check on already connected devices failed " <<endl << flush;
    retCode = 40;
    goto EscapeWay;
  }

  //--------------------------------------------------------------------
  // 5. Saving the final document
  //--------------------------------------------------------------------
  RC = CATDocumentServices::SaveAs ( *pDoc,argv[2],"CATProduct",iSavePointedIfNecessary );
  if (SUCCEEDED(RC))
  {
    cout << "> document saved " << endl << flush;
  }
  else
  {
    cout << "ERROR in save document" << endl << flush;
    retCode = 28;
    goto EscapeWay;
  }

  //--------------------------------------------------------------------
  // 6. removing document from session 
  //--------------------------------------------------------------------
  RC = CATDocumentServices::Remove(*pDoc);
  if (SUCCEEDED(RC))
  {
    cout << "> document removed " << endl << flush;
  }
  else
  {
    cout << "ERROR in removing document" << endl << flush;
    retCode = 29;
    goto EscapeWay;
  }

  //--------------------------------------------------------------------
  // 7.closing the session
  //--------------------------------------------------------------------
  RC = ::Delete_Session(sessionName);
  if (SUCCEEDED(RC))
    cout << "> session deleted " << endl << flush;
  else
  {
    cout << "ERROR in deleting session" << endl << flush;
    retCode = 30;
    goto EscapeWay;
  }
  cout << "----------------------------------------------------------------" << endl << flush;
  cout << endl << flush;
  cout << endl << flush;

EscapeWay:

  if(NULL != pSingleConnector)
  {
    pSingleConnector -> Release();
    pSingleConnector = NULL ;
  }
  if(NULL != pBackShell)
  {
    pBackShell -> Release();
    pBackShell = NULL ;
  }
  if(NULL != pShell1)
  {
    pShell1 -> Release();
    pShell1 = NULL ;
  }
  if(NULL != pShell2)
  {
    pShell2 -> Release();
    pShell2 = NULL ;
  }
  if(NULL != pME1)
  {
    pME1 -> Release();
    pME1 = NULL ;
  }
  if(NULL != pME2)
  {
    pME2 -> Release();
    pME2 = NULL ;
  }
  if(NULL != pEquipment)
  {
    pEquipment -> Release();
    pEquipment = NULL ;
  }
  if(NULL != pCavity)
  {
    pCavity -> Release();
    pCavity = NULL ;
  }
  if(NULL != pCnctPt)   
  {
    pCnctPt -> Release();
    pCnctPt = NULL ;
  }
  if(NULL != pdevinst)   
  {
    pdevinst -> Release();
    pdevinst = NULL ;
  }
  if(NULL != pdevice)   
  {
    pdevice -> Release();
    pdevice = NULL ;
  }
  if(NULL != pOCnctPt)   
  {
    pOCnctPt -> Release();
    pOCnctPt = NULL ;
  }
  if(NULL != CavityCnctPts)
  {
    delete CavityCnctPts;
    CavityCnctPts = NULL;
  }
  if(NULL != pCavities)
  {
    delete pCavities;
    pCavities = NULL;
  }
  if(NULL != pDevInst1)
  {
    pDevInst1 -> Release();
    pDevInst1 = NULL ;
  }
  if(NULL != pDevInst2)
  {
    pDevInst2 -> Release();
    pDevInst2 = NULL ;
  }
  if(NULL != piRootProduct)
  {
    piRootProduct -> Release();
    piRootProduct = NULL ;  
  }
  //
  return retCode;
}
