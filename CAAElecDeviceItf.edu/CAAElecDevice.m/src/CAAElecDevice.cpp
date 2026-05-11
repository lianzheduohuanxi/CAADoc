// =================================
// COPYRIGHT DASSAULT SYSTEMES 2002
// ================================= 

//=============================================================================
//  Abstract of Use Case "CAAElecDevice":
//  ---------------------------------------
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
//  3. Retrieving  all electrical object under the Root Product 
//
//  4. Selecting first equipment
//       . Retrieving the list of cavity  of this equipment
//       . Scan each cavity 
//       . Check the parent of each cavity is the equipment part
//       . Get the device plugged in each cavity 
//       . If the device plugged in the cavity  is a single connector.
//             . List the cavities defined in the single connector
//             . List the bundle connection points of the single insert connector.
//             . List the contacts aggregated in the single connector 
//
//       . If  the device plugged in the cavity  is a connector shell.
//             . Retrieve the  cavity list of this connector shell 
//             . Retrieve the cavity of the father equipment used by the connector shell
//
//  5. Selecting the second equipment.
//       . Retrieve the list of bundle connection point defined on the equipment.
//       . Scan the list of bundle connection point 
//  
//
//  6. Epilogue.
//
//  Return Errors:
//  -------------
//  1 - ERROR in creating the session
//  2 - ERROR in opening an existing document.
//  3 - ERROR in getting root product
//  4 - ERROR in electrical environment initialization 
//  5 - ERROR if electrical equipment not found in assembly 
//  6 - ERROR if the first electrical equipment not found
//  7 - ERROR if cavity list of the first electrical equipment is empty
//  8 - ERROR if not retrieving the parent of a cavity
//  9 - ERROR if the cavity is not plugged with a device
// 10 - ERROR if the cavity list of single connector is empty
// 11 - ERROR if the bundle connection point list of single connector is empty
// 12 - ERROR if the contact list aggregated in single connector is empty.
// 13 - ERROR if the cavity list aggregated in the connector shell is empty.
// 14 - ERROR if not retrieve the cavity of the father equipment used by the connector shell
// 15 - ERROR if second electrical equipment not found
// 16 - ERROR if the bundle connection point list defined in the equipment is empty .
// 17 - ERROR in removing document  
// 18 - ERROR in closing session  
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  mkrun -c "CAAElecDevice input.CATProduct" where the prefix "input" is the 
//  entire pathname of the directory in which the document is to be found and the
//  name of the of the document itself.
//
//
//  You may reference the supplied CATProduct document called "CAA_ElecDeviceSample.CATProduct" 
//  found in the 'WS'/'OS'/resources/graphic/CAAElecDevice directory if under Unix.
//      In this case, 'OS' can be any of the following: 
//         aix_a for IBM
//         hpux_a for HP
//         irix_a for SGI
//         solaris_a for SUN
//  Under Windows, the path would indicate:  'WS'\intel_a\resources\graphic\CAAElecDevice directory. 
//
//
//=============================================================================

// C++ include ( result display )
// LRO 08:01:15
#include "CATBaseUnknown.h"
#include "CATISpecObject.h"
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
#include "CATIProduct.h"           // managing products  

// Knowledge interfaces 
#include "CATICkeInst.h"           // managing products  

// Electrical Device Interface
#include "CATIElbEquipment.h"       // browsing geometrical bundles
#include "CATIElbExternalSplice.h"  // browsing bundle segments
#include "CATIElbSingleConnector.h"
#include "CATIElbCavity.h"
#include "CATIElbConnectorShell.h"
#include "CATIElbTermination.h"
#include "CATIElbBundleCnctPt.h"

// Electrical interfaces
#include "CATIEleDocServices.h"    // initializing electrical environement 
#include "CATIElecAttrAccess.h"    // managing electrical attributes 



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
  
  char *sessionName = "CAA_ElbDevice_Session";
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
  // 3. Retrieving all electrical equipment under the root product   
  //--------------------------------------------------------------------
  
  // --- Retrieving all electrical equipment under root product  
  
  CATListValCATBaseUnknown_var* pListElectricalEquipment = NULL;
  pListElectricalEquipment = piRootProduct->GetAllChildren(CATIElbEquipment::ClassName());
  piRootProduct -> Release();
  piRootProduct = NULL ;
  
  int NumberOfEquipment = 0;
  if ( (NULL!=pListElectricalEquipment) && pListElectricalEquipment->Size() ) 
  {
    NumberOfEquipment = pListElectricalEquipment->Size();	
    cout << "> number of equipment part found in assembly : "<< NumberOfEquipment << endl << flush;
  }
  else
  {
    cout << "ERROR : no electrical equipment found in assembly " << endl << flush;
    return 5;
  }
  
  // --- Selecting first  electrical equipment to analyse.
  // -----------------------------------------------------
  
  CATIElbEquipment * piFirstElecEquipment = NULL;
  CATBaseUnknown_var spCBU ((*pListElectricalEquipment)[1]);
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIElbEquipment,(void**) &piFirstElecEquipment);
  
  //     
  if ( SUCCEEDED(rc) && NULL!= piFirstElecEquipment)
  { 
    cout << "> select electrical equipment to analyse " <<endl << flush;
    cout << "   rank in list   :  "<< NumberOfEquipment << endl << flush;
    CATIProduct_var  spFirstElecEquipmentProduct = piFirstElecEquipment ;
    CATUnicodeString InstanceName ;
    if ( NULL_var != spFirstElecEquipmentProduct ) spFirstElecEquipmentProduct->GetPrdInstanceName(InstanceName);		
    cout << "   instance name  :  "<< InstanceName .ConvertToChar() << endl << flush;
  }
  else
  {
    cout << "ERROR : getting electrical equipment failed " << endl << flush;
    delete pListElectricalEquipment;
    pListElectricalEquipment = NULL;

    return 6;
  } 
  
  
  
  // Step1 :Analysing the first electrical Equipment.
  // =========================================
  
  //  Retrieving the list of cavity of the first equipment.
  // ===========================================================
  
  CATListValCATBaseUnknown_var* pListOfCavity = NULL;
  rc = piFirstElecEquipment ->ListCavities(pListOfCavity);
  int nNumberOfCavity = pListOfCavity? pListOfCavity->Size() : 0;
  if ( SUCCEEDED(rc) && (NULL!=pListOfCavity) && nNumberOfCavity > 0 ) 
  {
    cout << "> number of cavity in equipment :"<< pListOfCavity->Size() <<endl << flush;
  }
  else
  {
    cout << "ERROR : no cavity under equipment " << endl << flush;
    piFirstElecEquipment->Release();
    piFirstElecEquipment = NULL;
    delete pListElectricalEquipment;
    pListElectricalEquipment = NULL;
    return 7;
  }

  piFirstElecEquipment->Release();
  piFirstElecEquipment = NULL;
  
  for(int i=1;i<=nNumberOfCavity;i++)
  {
    cout << "                                    " << endl << flush;
    cout << "====================================" << endl << flush;
    cout << "                                    " << endl << flush;
    cout << "   cavity number of  equipment   :  "<< i << endl << flush;
    cout << "                                    " << endl << flush;
    cout << "====================================" << endl << flush;
    cout << "                                    " << endl << flush;
    
    CATIElbCavity * pElecCavity =NULL;
    CATBaseUnknown_var spCBU ((*pListOfCavity)[i]);
    if(NULL_var != spCBU && SUCCEEDED(spCBU->QueryInterface(IID_CATIElbCavity,(void**)& pElecCavity)) && pElecCavity)
    {
      // Retrievieng the parent of cavity
      // ================================
      CATBaseUnknown * pParentOfCavity = NULL;
      rc = pElecCavity->GetParent(pParentOfCavity);
      if(SUCCEEDED(rc) && NULL!=pParentOfCavity)
      {
        CATIProduct_var  spParentOfCavitytProduct = pParentOfCavity ;
        pParentOfCavity->Release();
        pParentOfCavity = NULL;
        
        CATUnicodeString InstanceName ;
        if ( NULL_var != spParentOfCavitytProduct ) spParentOfCavitytProduct->GetPrdInstanceName(InstanceName);		
        cout << "   instance name of the parent of this cavity  :  "<< InstanceName .ConvertToChar() << endl << flush;
        cout << "    " << endl << flush;
      }
      else 
      {
        cout << "ERROR : getting  parent of cavity failed " << endl << flush;
        
        delete pListOfCavity;
        pListOfCavity = NULL;
        delete pListElectricalEquipment;
        pListElectricalEquipment = NULL;
        pElecCavity ->Release();
        pElecCavity = NULL;

        return 8;
      }
      
      // Retrieving the Device plugged in the cavity
      // -------------------------------------------
      CATBaseUnknown * pDevicePluggedInCavity = NULL;
      rc = pElecCavity->GetPluggedInDevice(pDevicePluggedInCavity);
      if(SUCCEEDED(rc) && NULL!=pDevicePluggedInCavity)
      {
        CATIProduct_var  spDevicePluggedInProduct = pDevicePluggedInCavity ;
        CATUnicodeString InstanceName ;
        if ( NULL_var != spDevicePluggedInProduct ) spDevicePluggedInProduct->GetPrdInstanceName(InstanceName);		
        cout << "   instance name of the device plugged in the cavity :  "<< InstanceName .ConvertToChar() << endl << flush;
      }
      else 
      {
        cout << "ERROR : getting  plugged device in cavity failed " << endl << flush;
        
        delete pListOfCavity;
        pListOfCavity = NULL;
        delete pListElectricalEquipment;
        pListElectricalEquipment = NULL;
        pElecCavity ->Release();
        pElecCavity = NULL;

        return 9;
      }
      
      pElecCavity->Release();
      pElecCavity = NULL;
      
      // Checking that the device plugged in cavity is a single insert connector
      // -----------------------------------------------------------------------
      CATIElbSingleConnector * pElecSingleConnector = NULL;
      if(SUCCEEDED(pDevicePluggedInCavity->QueryInterface(IID_CATIElbSingleConnector,(void**)& pElecSingleConnector)) &&pElecSingleConnector )
      {
        
        
        cout << "  The plugged device is a  single connector " << endl << flush;
        cout << "  ==========================================" << endl << flush;
        // Retrieving the list of cavity of this single connector
        // ======================================================
        CATListValCATBaseUnknown_var * pListCavityOfSic = NULL;
        rc = pElecSingleConnector->ListCavities(pListCavityOfSic);
        int NumberOfCavity = pListCavityOfSic?pListCavityOfSic->Size():0;
        
        if(SUCCEEDED(rc) && pListCavityOfSic  && NumberOfCavity>0 )
        {
          cout << "Succeeded : getting  list of cavity in the single connector  " << endl << flush;
        }
        else
        {
          cout << "ERROR : getting  list of cavity in the single connector failed " << endl << flush;
          delete pListElectricalEquipment;
          pListElectricalEquipment = NULL;
          delete pListOfCavity;
          pListOfCavity = NULL;
          pDevicePluggedInCavity->Release();
          pDevicePluggedInCavity = NULL;
          pElecSingleConnector->Release();
          pElecSingleConnector = NULL;

          return 10;
        }
        
        if(pListCavityOfSic) delete pListCavityOfSic;
        pListCavityOfSic = NULL;
        
        // Retrieving the list of bundle connection point
        // ----------------------------------------------
        CATListValCATBaseUnknown_var * pListBundleCnctPtOfSic = NULL;
        rc = pElecSingleConnector->ListCavities(pListBundleCnctPtOfSic);
        int NumberOfBCP = pListBundleCnctPtOfSic?pListBundleCnctPtOfSic->Size():0;
        
        if(SUCCEEDED(rc) && pListBundleCnctPtOfSic  && NumberOfBCP>0 )
        {
          cout << "Succeeded : getting  list of bundle connection point in the single connector  " << endl << flush;
        }
        else
        {
          cout << "ERROR : getting  list of cavity in the single connector failed " << endl << flush;
          
          delete pListElectricalEquipment;
          pListElectricalEquipment = NULL;
          delete pListOfCavity;
          pListOfCavity = NULL;
          pElecSingleConnector->Release();
          pElecSingleConnector = NULL;          
          pDevicePluggedInCavity->Release();
          pDevicePluggedInCavity = NULL;
          
          return 11;
        }
        
        if(pListBundleCnctPtOfSic) delete pListBundleCnctPtOfSic;
        pListBundleCnctPtOfSic = NULL;
        
        // Retrieving the list of Elec Contact aggregated in the single connector
        // ----------------------------------------------------------------------
        CATListValCATBaseUnknown_var * pListDeviceComposition = NULL;
        rc = pElecSingleConnector->ListDeviceComposition(pListDeviceComposition);
        int NumberOfContact = pListDeviceComposition?pListDeviceComposition->Size():0;
        if(SUCCEEDED(rc) && pListDeviceComposition && NumberOfContact>0)
        {
          // 
          for(int j=1;j<=NumberOfContact;j++)
          {
            CATIProduct_var  spContactProduct = (*pListDeviceComposition)[j] ;
            CATUnicodeString InstanceName ;
            if ( NULL_var != spContactProduct ) spContactProduct->GetPrdInstanceName(InstanceName);		
            cout << "   instance name of contact placed in single connector cavity :  "<< InstanceName .ConvertToChar() << endl << flush;
          }
        }
        else 
        {
          cout << "ERROR : getting  the  list contact aggregated in the single connector failed " << endl << flush;
                    delete pListElectricalEquipment;
          pListElectricalEquipment = NULL;
          delete pListOfCavity;
          pListOfCavity = NULL;
          pElecSingleConnector->Release();
          pElecSingleConnector = NULL;
          pDevicePluggedInCavity->Release();
          pDevicePluggedInCavity = NULL;

          return 12;
        }
        
        if(pListDeviceComposition) delete pListDeviceComposition;
        pListDeviceComposition = NULL;
        
        pElecSingleConnector->Release();
        pElecSingleConnector = NULL;
      }// end of query interface to single connector
      
      // Checking that the device plugged in cavity is a connector shell
      // ---------------------------------------------------------------
      CATIElbConnectorShell * pElecConnectorShell = NULL;
      if(SUCCEEDED(pDevicePluggedInCavity->QueryInterface(IID_CATIElbConnectorShell,(void**)& pElecConnectorShell)) && pElecConnectorShell )
      {
        
        cout << "  The plugged device in this cavity of equipment is a  connector shell " << endl << flush;
        cout << "  ==================================================================== " << endl << flush;
        
        // Retrieving the list of cavity defined in the connector shell
        // ============================================================
        CATListValCATBaseUnknown_var * pListCavityInConnectorShell = NULL;
        rc = pElecConnectorShell->ListCavities(pListCavityInConnectorShell); /// a finir .........
        
        int NumberOfShellCavity = pListCavityInConnectorShell?pListCavityInConnectorShell->Size():0;
        
        if(SUCCEEDED(rc) && pListCavityInConnectorShell && NumberOfShellCavity>0)
        {
          for(int k=1;k<=NumberOfShellCavity;k++)
          {
            CATISpecObject_var  spShellCavityFeat = (*pListCavityInConnectorShell)[k] ;
            CATUnicodeString FeatureName ;
            if ( NULL_var != spShellCavityFeat ) FeatureName=spShellCavityFeat->GetName();		
            cout << "  feature  name of the cavity of this connector shell is :  "<< FeatureName .ConvertToChar() << endl << flush;
          }
        }
        else 
        {
          cout << "ERROR : getting  the  list cavity aggregated in the connector shell failed " << endl << flush;
         
          delete pListElectricalEquipment;
          pListElectricalEquipment = NULL;
          delete pListOfCavity;
          pListOfCavity = NULL;
          pElecConnectorShell->Release();
          pElecConnectorShell = NULL;          
          pDevicePluggedInCavity->Release();
          pDevicePluggedInCavity = NULL;

          return 13;
        }
        
        if(pListCavityInConnectorShell) delete pListCavityInConnectorShell;
        pListCavityInConnectorShell = NULL;
        
        // Retrieving the  cavity of the faher equipment used by the connector shell.
        // ==========================================================================
        
        CATIElbCavity * pElecCavityOfFatherEquipment = NULL;
        rc =pElecConnectorShell->GetEquipmentCavity(pElecCavityOfFatherEquipment);
        if(SUCCEEDED(rc) && pElecCavityOfFatherEquipment)
        {
          CATISpecObject_var spCavityOfFatherEquipment = pElecCavityOfFatherEquipment;
          CATUnicodeString InstanceName ;
          if ( NULL_var != spCavityOfFatherEquipment )InstanceName = spCavityOfFatherEquipment->GetName();		
          cout << "   Feature name of the  cavity of the faher equipment used by the connector shell is :  "<< InstanceName .ConvertToChar() << endl << flush;
          
          pElecCavityOfFatherEquipment->Release();
          pElecCavityOfFatherEquipment = NULL;
          
        }
        else 
        {
          cout << "ERROR : getting  the   cavity of the faher equipment used by the connector shell failed " << endl << flush;
          
          delete pListElectricalEquipment;
          pListElectricalEquipment = NULL;
          delete pListOfCavity;
          pListOfCavity = NULL;
          pElecConnectorShell->Release();
          pElecConnectorShell = NULL;
          pDevicePluggedInCavity->Release();
          pDevicePluggedInCavity = NULL;          
          
          return 14;
        }
        pElecConnectorShell->Release();
        pElecConnectorShell = NULL;
        
      }// end of query interface to connector shell
      
      pDevicePluggedInCavity -> Release();
      pDevicePluggedInCavity = NULL;
      
    }
  }// fin du for
  if(pListOfCavity) delete pListOfCavity;
  pListOfCavity = NULL;
  
  
  
  // Step2 : Retrieving the second equipment.
  // ========================================
  
  CATIElbEquipment * piSecondElecEquipment = NULL;
  spCBU = (*pListElectricalEquipment)[2];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIElbEquipment,(void**) &piSecondElecEquipment);
  
  //     
  if ( SUCCEEDED(rc) && NULL!= piSecondElecEquipment)
  { 
    cout << "> select the second  electrical equipment to analyse " <<endl << flush;
    CATIProduct_var  spSecondElecEquipmentProduct = piSecondElecEquipment ;
    CATUnicodeString InstanceName ;
    if ( NULL_var != spSecondElecEquipmentProduct ) spSecondElecEquipmentProduct->GetPrdInstanceName(InstanceName);		
    cout << "   instance name  of the second equipment in my sample:  "<< InstanceName .ConvertToChar() << endl << flush;
  }
  else
  {
    cout << "ERROR : getting electrical equipment failed " << endl << flush;
    delete pListElectricalEquipment;
    pListElectricalEquipment = NULL;
    return 15;
  } 
  
  if ( pListElectricalEquipment ) delete pListElectricalEquipment;
  pListElectricalEquipment=NULL;
  
  // Retrieving the list of bundle connection point defined in my equipment.
  // =======================================================================
  CATListValCATBaseUnknown_var * pListBCPinEquipment = NULL;
  rc = piSecondElecEquipment->ListBundleCnctPts(pListBCPinEquipment);
  
  if(piSecondElecEquipment) piSecondElecEquipment->Release();
  piSecondElecEquipment = NULL;
  
  int tailleListBCP = pListBCPinEquipment ? pListBCPinEquipment->Size() : 0;
  cout << "Size of bundle connection point list defined in the second equipment " << tailleListBCP << endl << flush;

  if (!(SUCCEEDED(rc) && pListBCPinEquipment && tailleListBCP>0))
  {
    cout << "ERROR : getting list of bundle connection point defined in the equiment " << endl << flush;
    return 16;
  } 
  
  if(pListBCPinEquipment) delete pListBCPinEquipment;
  pListBCPinEquipment = NULL;
  
  
  
  
  
  
  //--------------------------------------------------------------------
  // 8. Epilogue  
  //--------------------------------------------------------------------
  
  // --- removing document from session 
  rc = CATDocumentServices::Remove(*pDoc);
  if (SUCCEEDED(rc))
  {
    cout << "> document removed " << endl << flush;
  }
  else
  {
    cout << "ERROR in removing document" << endl << flush;
    return 17;
  }
  // --- closing the session
  rc = ::Delete_Session(sessionName);
  if (SUCCEEDED(rc))
    cout << "> session deleted " << endl << flush;
  else
  {
    cout << "ERROR in deleting session" << endl << flush;
    return 18;
  }
  cout << "----------------------------------------------------------------" << endl << flush;
  cout << endl << flush;
  cout << endl << flush;
  
  //
  return (0);
}
