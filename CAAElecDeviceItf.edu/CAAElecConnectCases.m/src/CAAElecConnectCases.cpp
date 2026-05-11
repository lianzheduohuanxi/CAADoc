// =================================
// COPYRIGHT DASSAULT SYSTEMES 2009
// ================================= 

//=============================================================================
//  Abstract of Use Case "CAAElecConnectCases":
//  ---------------------------------------------
//
//  This Use Case illustrates different failure (Non Standard) cases while connecting Electrical Devices with Connect API. 
//
//=============================================================================
//
//  Step by Step :
//  ------------
//
//  1. Prologue :  
//      . Opening the Session and Opening an Existing CATProduct Document in the Case.
//      . Retrieving the Root Product of the CATProduct Document
// 
//  2. Initializing Electrical Environment 
//
//  3. Retrieving all devices under the Root Product 
//
//  4. Connecting the devices(Testing APIs).
//
//  5. removing document from session 
//
//  6. closing the session
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
// 15 - ERROR if input check failed on Connect API.
// 16 - ERROR if GetConnectedDevice API failed.
// 17 - ERROR if Connect between 2 MEs failed.
// 21 - ERROR if disconnect batween single connector and Mounting Equipment2 failed.
// 24 - ERROR if disconnect batween Shell1 and Mounting Equipment2 failed.
// 29 - ERROR the Disconnect between SIC and Equipment failed.
// 36 - ERROR if the Disconnect between BackShell and Shell2 failed.
// 39 - ERROR in removing Doc.
// 40 - ERROR in deleting session.
// 41 - ERROR if input check failed on DisConnect API.
// 18,20,23,26,28,31,33,35,38 - ERROR if check on Connect between 2 devices having over constrained geometry failed.
// 19,22,25,27,30,32,34,37 - ERROR if check on Connect between 2 devices having no geometry failed.
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  mkrun -c "CAAElecConnectCases input N" where the prefix "input" is the 
//  entire pathname of the directory in which the document for different cases is to be found
//  N is the number of the cases to be tested
//
//  You may reference the supplied CATProduct document called "TOP.CATProduct" 
//  found in the 'WS'/'OS'/resources/graphic/CAAElecConnectCases directory if under Unix.
//      In this case, 'OS' can be any of the following: 
//         aix_a for IBM
//         hpux_a for HP
//         irix_a for SGI
//         solaris_a for SUN
//  Under Windows, the path would indicate:  'WS'\intel_a\resources\graphic\CAAElecConnectCases directory. 
//
//
//====================================================================================================

// C++ include ( result display )

//System
#include "CATLib.h"
#include "CATBaseUnknown.h"
#include "CATBoolean.h"
#include <iostream.h>
#include "CATLISTV_CATBaseUnknown.h"
#include "CATUnicodeString.h"

// ObjectModelerBase interfaces
#include "CATSessionServices.h"    // managing session
#include "CATDocumentServices.h"   // managing documents in session
#include "CATDocument.h"           // manipulating documents
#include "CATIDocRoots.h"          // browsing root objects in documents
#include "CATSession.h"

// ElecDeviceItf interfaces 
#include "CATIProduct.h"              // managing products   
#include "CATIElbSingleConnector.h"   // managing a single connector
#include "CATIElbBackShell.h"         // managing a back shell
#include "CATIElbEquipment.h"         // managing an equipemnt
#include "CATIElbMountingEquipment.h" // managing a mounting equipment
#include "CATIElbCavity.h"            // managing a mounting equipment
#include "CATIElbConnectorShell.h"
#include "CATIElbDeviceInstance.h"

// Electrical interfaces
#include "CATIEleDocServices.h"       // initializing electrical environement 


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

  //declaring all variables
  int retCode = 0;
  CATIProduct* piRootProduct = NULL;// piRootProduct is a handle to document root product
  CATIElbSingleConnector * pSingleConnector = NULL;
  CATIElbBackShell * pBackShell = NULL;
  CATIElbBackShell * pBackShell1 = NULL;
  CATIElbConnectorShell * pShell1 = NULL;
  CATIElbConnectorShell * pShell2 = NULL;
  CATIElbConnectorShell * pShell = NULL;
  CATIElbMountingEquipment * pME1 = NULL;
  CATIElbMountingEquipment * pME2 = NULL;
  CATIElbMountingEquipment * pME = NULL;
  CATIElbEquipment * pEquipment = NULL;
  CATIElbEquipment * pEquipment1 = NULL;
  CATIElbCavity * pCavity = NULL;
  CATIElbCavity * pCavity1 = NULL;
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

  //Loop for all the cases-->
  CATUnicodeString sNum(argv[2]);
  int nbOfCases = -1;
  sNum.ConvertToNum(&nbOfCases); 
  if(nbOfCases<1)return -2;

  const CATUnicodeString DocumentPath(argv[1]);
  CATUnicodeString ODT_SLASH = "\\";
  CATUnicodeString sRootPrdName = "TOP.CATProduct";
  
  if((nbOfCases<1) || (nbOfCases>2)){cout<<"Invalid number of cases";return 100; }
  
  for( int iCase = 1; iCase <= nbOfCases; iCase++ )
  {
    CATUnicodeString sIndex;
    CATUnicodeString sTmpDocPath = DocumentPath;
    sIndex.BuildFromNum(iCase);
    sTmpDocPath = sTmpDocPath+sIndex+ODT_SLASH+sRootPrdName;


    // --- Opening an existing document 
    //     The input parameter to this sample program must contain 
    //     the entire path and name of the document that is to be opened.  

    CATDocument *pDoc = NULL; // pDoc is a pointer to the document 

    cout << "> open document :"<< sTmpDocPath.ConvertToChar()<< endl << flush;
    RC = CATDocumentServices::OpenDocument(sTmpDocPath, pDoc);
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
 
    //SIC
    CATListValCATBaseUnknown_var* pListElbSingleConnector = NULL;
    pListElbSingleConnector = piRootProduct->GetAllChildren(CATIElbSingleConnector::ClassName());

    int NumberOfSingleConnector = pListElbSingleConnector?pListElbSingleConnector->Size():0;
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

    CATListValCATBaseUnknown_var* pListElbBackShell = NULL;
    pListElbBackShell = piRootProduct->GetAllChildren(CATIElbBackShell::ClassName());

    int NumberOfBS = pListElbBackShell?pListElbBackShell->Size():0;
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
    CATListValCATBaseUnknown_var* pListShell = NULL;
    pListShell = piRootProduct->GetAllChildren(CATIElbConnectorShell::ClassName());

    int NumberOfShells = pListShell?pListShell->Size():0;
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

    CATListValCATBaseUnknown_var* pListMountingEquip = NULL;
    pListMountingEquip = piRootProduct->GetAllChildren(CATIElbMountingEquipment::ClassName());

    int NumberOfME = pListMountingEquip?pListMountingEquip->Size():0;
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
    CATListValCATBaseUnknown_var* pListEquipments = NULL;
    pListEquipments = piRootProduct->GetAllChildren(CATIElbEquipment::ClassName());

    int NumberOfEquipments = pListEquipments?pListEquipments->Size():0;
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

    int StatusOfGeometricalConstraint = 2;

    //Check when NULL inputs are passed    

    if(1==iCase)
    {
      //Connect on ME
      RC = pME2->Connect(pCavity1,pME,StatusOfGeometricalConstraint);

      if(E_INVALIDARG == RC)
      {
        cout << "> **OK** NULL inputs check successful " <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** NULL inputs check failed. " <<endl << flush;
        retCode = 15;
        goto EscapeWay;
      }

      //Connect on SIC
      RC = pSingleConnector->Connect(pCavity1,pME,StatusOfGeometricalConstraint);
      
      if(E_INVALIDARG == RC)
      {
        cout << "> **OK** NULL inputs check successful " <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** NULL inputs check failed. " <<endl << flush;
        retCode = 15;
        goto EscapeWay;
      }

      //Connect on Shell
      RC = pShell1->Connect(pCavity1,pME,StatusOfGeometricalConstraint);

      if(E_INVALIDARG == RC)
      {
        cout << "> **OK** NULL inputs check successful " <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** NULL inputs check failed. " <<endl << flush;
        retCode = 15;
        goto EscapeWay;
      }

      //Connect on Equipment
      RC = pEquipment->Connect(pCavity1,pME,StatusOfGeometricalConstraint);

      if(E_INVALIDARG == RC)
      {
        cout << "> **OK** NULL inputs check successful " <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** NULL inputs check failed. " <<endl << flush;
        retCode = 15;
        goto EscapeWay;
      }

      //Connect on SIC
      RC = pSingleConnector->Connect(pCavity1,pEquipment1,StatusOfGeometricalConstraint);

      if(E_INVALIDARG == RC)
      {
        cout << "> **OK** NULL inputs check successful " <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** NULL inputs check failed. " <<endl << flush;
        retCode = 15;
        goto EscapeWay;
      }

      //Connect on Shell
      RC = pShell1->Connect(pCavity1,pEquipment1,StatusOfGeometricalConstraint);

      if(E_INVALIDARG == RC)
      {
        cout << "> **OK** NULL inputs check successful " <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** NULL inputs check failed. " <<endl << flush;
        retCode = 15;
        goto EscapeWay;
      }

      //Connect on Shell
      RC = pShell1->Connect(pShell,StatusOfGeometricalConstraint);

      if(E_INVALIDARG == RC)
      {
        cout << "> **OK** NULL inputs check successful " <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** NULL inputs check failed. " <<endl << flush;
        retCode = 15;
        goto EscapeWay;
      }

      //Connect on Shell
      RC = pShell2->Connect(pBackShell1,StatusOfGeometricalConstraint);

      if(E_INVALIDARG == RC)
      {
        cout << "> **OK** NULL inputs check successful " <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** NULL inputs check failed. " <<endl << flush;
        retCode = 15;
        goto EscapeWay;
      }

      //Connect on SIC
      RC = pSingleConnector->Connect(pCavity1,pShell,StatusOfGeometricalConstraint);

      if(E_INVALIDARG == RC)
      {
        cout << "> **OK** NULL inputs check successful " <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** NULL inputs check failed. " <<endl << flush;
        retCode = 15;
        goto EscapeWay;
      }
    }

    RC = pME1->ListCavities(pCavities);

    if((NULL != pCavities) && (pCavities->Size()==1))
    {
      CATBaseUnknown_var hCavity((*pCavities)[1]);

      if(NULL_var!=hCavity)
      {
        RC = hCavity->QueryInterface(IID_CATIElbCavity , (void**)&pCavity);

        RC = hCavity->QueryInterface(IID_CATBaseUnknown , (void**)&pCnctPt);
      }
    }

    // Test GetConnectedDevice on CATIElbDeviceInstance when no device is connected

    if(1==iCase)
    {
      RC = pME2->ListCavityCnctPts(CavityCnctPts);

      if(SUCCEEDED(RC) && (NULL != CavityCnctPts) && (CavityCnctPts->Size()>0))
        hccp = ((*CavityCnctPts)[1]);

      RC = pME1->QueryInterface(IID_CATIElbDeviceInstance, (void **)&pdevinst);

      if((NULL != pdevinst) && (NULL != pCnctPt))
        RC = pdevinst->GetConnectedDevice(pCnctPt,pdevice,pOCnctPt);

      if(1==iCase)
      {
        if(FAILED(RC) && (NULL==pdevice) && (NULL==pOCnctPt))
        {
          cout << "> **OK** No device connected " <<endl << flush;
        }
        else
        {
          cout << "> **** ERROR **** Error in GetConnectedDevice API. " <<endl << flush;
          retCode = 16;
          goto EscapeWay;
        }
      }
    }

    //1. Connect MountingEquipment1 to MountingEquipment2

    if(NULL != pCavity)
    {
      RC = pME2->Connect(pCavity,pME1,StatusOfGeometricalConstraint);
    }

    if(1==iCase)
    {
      if(FAILED(RC) && (2 == StatusOfGeometricalConstraint))
      {
        cout << "> **OK** No Geometrical constraint is defined between the two MEs" <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** Error in Connect API on ME. " <<endl << flush;
        retCode = 17;
        goto EscapeWay;
      }
    }
    else if(2==iCase)
    {
      if(SUCCEEDED(RC) && (1 == StatusOfGeometricalConstraint))
      {
        cout << "> **OK** A geometrical constraint is over constrained " <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** Error in Connect API. " <<endl << flush;
        retCode = 18;
        goto EscapeWay;
      }
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

      if (NULL != pCavity)
      {
        RC = pSingleConnector->Connect(pCavity,pME2,StatusOfGeometricalConstraint);
      }
    }

    if(1==iCase)
    {
      if(FAILED(RC) && (2 == StatusOfGeometricalConstraint))
      {
        cout << "> **OK** No Geometrical constraint is defined on a device" <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** Error in Connect API. " <<endl << flush;
        retCode = 19;
        goto EscapeWay;
      }
    }
    else if(2==iCase)
    {
      if(SUCCEEDED(RC) && (1 == StatusOfGeometricalConstraint))
      {
        cout << "> **OK** A geometrical constraint is over constrained " <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** Error in Connect API. " <<endl << flush;
        retCode = 20;
        goto EscapeWay;
      }
    }

    //3. Disconnect SIC from ME if case 2

    if(2==iCase)
    {
      RC = pSingleConnector->QueryInterface(IID_CATIElbDeviceInstance, (void **)&pDevInst1);

      if(NULL != pDevInst1)
      {
        //NULL Check for Disconnect API
        RC = pDevInst1->Disconnect(pDevInst2);

        if(E_INVALIDARG == RC)
        {
          cout << "> **OK** NULL inputs check successful on Disconnect API" <<endl << flush;
        }
        else
        {
          cout << "> **** ERROR **** NULL inputs check failed on Disconnect API. " <<endl << flush;
          retCode = 41;
          goto EscapeWay;
        }

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
            retCode = 21;
            goto EscapeWay;
          }
        }
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

    if(1==iCase)
    {
      if(FAILED(RC) && (2 == StatusOfGeometricalConstraint))
      {
        cout << "> **OK** No Geometrical constraint is defined on a device" <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** Error in Connect API. " <<endl << flush;
        retCode = 22;
        goto EscapeWay;
      }
    }
    else if(2==iCase)
    {
      if(SUCCEEDED(RC) && (1 == StatusOfGeometricalConstraint))
      {
        cout << "> **OK** A geometrical constraint is over constrained " <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** Error in Connect API. " <<endl << flush;
        retCode = 23;
        goto EscapeWay;
      }
    }

    //5. Disconnect Shell from ME if case 2
    if(2==iCase)
    {
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
          retCode = 24;
          goto EscapeWay;
        }
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

    if(1==iCase)
    {
      if(FAILED(RC) && (2 == StatusOfGeometricalConstraint))
      {
        cout << "> **OK** No Geometrical constraint is defined on a device" <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** Error in Connect API. " <<endl << flush;
        retCode = 25;
        goto EscapeWay;
      }
    }
    else if(2==iCase)
    {
      if(SUCCEEDED(RC) && (1 == StatusOfGeometricalConstraint))
      {
        cout << "> **OK** A geometrical constraint is over constrained " <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** Error in Connect API. " <<endl << flush;
        retCode = 26;
        goto EscapeWay;
      }
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

    if(1==iCase)
    {
      if(FAILED(RC) && (2 == StatusOfGeometricalConstraint))
      {
        cout << "> **OK** No Geometrical constraint is defined on a device" <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** Error in Connect API. " <<endl << flush;
        retCode = 27;
        goto EscapeWay;
      }
    }
    else if(2==iCase)
    {
      if(SUCCEEDED(RC) && (1 == StatusOfGeometricalConstraint))
      {
        cout << "> **OK** A geometrical constraint is over constrained " <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** Error in Connect API. " <<endl << flush;
        retCode = 28;
        goto EscapeWay;
      }
    }

    //8. Disconnect SIC from Equipment
    if(2==iCase)
    {
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
          retCode = 29;
          goto EscapeWay;
        }
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

    if(1==iCase)
    {
      if(FAILED(RC) && (2 == StatusOfGeometricalConstraint))
      {
        cout << "> **OK** No Geometrical constraint is defined on a device" <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** Error in Connect API. " <<endl << flush;
        retCode = 30;
        goto EscapeWay;
      }
    }
    else if(2==iCase)
    {
      if(SUCCEEDED(RC) && (1 == StatusOfGeometricalConstraint))
      {
        cout << "> **OK** A geometrical constraint is over constrained " <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** Error in Connect API. " <<endl << flush;
        retCode = 31;
        goto EscapeWay;
      }
    }

    //10. Connect Shell1 to Shell2

    if ((NULL != pShell1) && (NULL != pShell2))
    {
      RC = pShell1->Connect(pShell2,StatusOfGeometricalConstraint);
    }

    if(1==iCase)
    {
      if(FAILED(RC) && (2 == StatusOfGeometricalConstraint))
      {
        cout << "> **OK** No Geometrical constraint is defined on a device" <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** Error in Connect API. " <<endl << flush;
        retCode = 32;
        goto EscapeWay;
      }
    }
    else if(2==iCase)
    {
      if(SUCCEEDED(RC) && (1 == StatusOfGeometricalConstraint))
      {
        cout << "> **OK** A geometrical constraint is over constrained " <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** Error in Connect API. " <<endl << flush;
        retCode = 33;
        goto EscapeWay;
      }
    }

    //11. Connect BackShell to Shell2

    if ((NULL != pBackShell) && (NULL != pShell2))
    {
      RC = pShell2->Connect(pBackShell,StatusOfGeometricalConstraint);
    }

    if(1==iCase)
    {
      if(FAILED(RC) && (2 == StatusOfGeometricalConstraint))
      {
        cout << "> **OK** No Geometrical constraint is defined on a device" <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** Error in Connect API. " <<endl << flush;
        retCode = 34;
        goto EscapeWay;
      }
    }
    else if(2==iCase)
    {
      if(SUCCEEDED(RC) && (1 == StatusOfGeometricalConstraint))
      {
        cout << "> **OK** A geometrical constraint is over constrained " <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** Error in Connect API. " <<endl << flush;
        retCode = 35;
        goto EscapeWay;
      }
    }

    //12. DisConnect BackShell from Shell2
    if(2==iCase)
    {
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

      if(SUCCEEDED(RC)&&(NULL != pDevInst1))
      {
        RC = pDevInst1->Disconnect(pDevInst2);

        if(SUCCEEDED(RC))
        {
          cout << "> Disconnect BackShell from Shell2 succeeded " <<endl << flush;
        }
        else
        {
          cout << "> **** ERROR **** Disconnect BackShell from Shell2 failed " <<endl << flush;
          retCode = 36;
          goto EscapeWay;
        }
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

    if(1==iCase)
    {
      if(FAILED(RC) && (2 == StatusOfGeometricalConstraint))
      {
        cout << "> **OK** No Geometrical constraint is defined on a device" <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** Error in Connect API. " <<endl << flush;
        retCode = 37;
        goto EscapeWay;
      }
    }
    else if(2==iCase)
    {
      if(SUCCEEDED(RC) && (1 == StatusOfGeometricalConstraint))
      {
        cout << "> **OK** A geometrical constraint is over constrained " <<endl << flush;
      }
      else
      {
        cout << "> **** ERROR **** Error in Connect API. " <<endl << flush;
        retCode = 38;
        goto EscapeWay;
      }
    }

    //--------------------------------------------------------------------
    // 5. removing document from session 
    //--------------------------------------------------------------------
    RC = CATDocumentServices::Remove(*pDoc);
    if (SUCCEEDED(RC))
    {
      cout << "> document removed " << endl << flush;
    }
    else
    {
      cout << "ERROR in removing document" << endl << flush;
      retCode = 39;
      goto EscapeWay;
    }


  }//LOOP for cases closes


  //--------------------------------------------------------------------
  // 6.closing the session
  //--------------------------------------------------------------------
  RC = ::Delete_Session(sessionName);
  if (SUCCEEDED(RC))
    cout << "> session deleted " << endl << flush;
  else
  {
    cout << "ERROR in deleting session" << endl << flush;
    retCode = 40;
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
