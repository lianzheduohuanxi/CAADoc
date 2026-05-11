// =================================
// COPYRIGHT DASSAULT SYSTEMES 2002
// ================================= 

//=============================================================================
//  Abstract of Use Case "CAAElecDeviceFactory":
//  --------------------------------------------
//
//  This Use Case illustrates how extend a product in a electrical single connector 
//  or in a back shell or in a mounting equipment and how connecting  this device between them 
//
//=============================================================================
//
//  Step by Step :
//  ------------
//
//   1. Prologue :  
//      1.1 Checking inputs ( path )
//      1.2 Creating the Session 
//      1.3 Creating new CATProduct Document . 
//      1.5 Retrieving the Root Product of the CATProduct Document.
//   2. Initializing Electrical Environment.
//   3. Importing the part "Back_Shell.CATPart" under the Root Product .
//   4. Defining the BackShell :
//      4.1 Extending this part in type ElecBackShellE.
//   5. Importing the part "SingleConnector.CATPart" under the root product.
//   6. Defining the first Single Connector
//      6.1 Extending this part in Single Connector
//      6.2 Defining two terminations on the single connector
//      6.3 Defining a connector connection point on the first single connector
//   7. Importing the part "Second_SingleConnector.CATPart" under the root product.
//   8. Retrieving the list of geometrical element published on the product.
//   9. Creating three cavities on the second single connector
//  10. Importing the part "MountingEquipment.CATPart" under the root product.
//  11. Defining the mounting equipment
//      11.1 Extending the part in mounting equipment
//      11.2 Defining a cavity on the mounting equipment
//  12. Importing the part "Third_Single_Connector.CATPart" under the root product.
//      11.1 Defining a connector connection point on the third single connector
//  13. Epilogue.
//      13.1 saving documents
//      13.2 closing session
//
//  Return Errors:
//  -------------
//  1  : ERROR if number of inputs is invalid 
//  2  : ERROR in creating session
//  3  : ERROR in creating CATProduct document
//  4  : ERROR if the root product of document not found
//  5  : ERROR if the initialization of electrical environment  failed
//  6  : ERROR if import of the product back shell failed 
//  7  : ERROR if extend the product in type ElecBackshellE failed
//  8  : ERROR if the import of the product  single connector failed
//  9  : ERROR in extend  the product  in type ElecSicConE failed
//  10 : ERROR if reference of single connector is not defined in CATPart Document
//  11 : ERROR if the part of the  single connector was not found
//  12 : ERROR if the Point.1 defined in the OpenBody of the  single connector wasn't found
//  13 : ERROR in  the Point.2 defined in the OpenBody of the  single connector wasn't found
//  14 : ERROR if the product where geometry of the single connector was defined wasn't found
//  15 : ERROR if the representation of the first point of the single connector wasn't found
//  16 : ERROR if the representation of the second point of the single connector wasn't found
//  17 : ERROR if the creation of  first termination failed
//  18 : ERROR if the creation of  second termination failed      
//  19 : ERROR if hSingleConnectorRefer is a null handler 
//  20 : ERROR if import of the second single connector failed
//  21 : ERROR if the reference product of the second single connector wasn't found
//  22 : ERROR if the product where is the geometry of the second single connector  wasn't found
//  23 : ERROR if the geometrical representation of the second single connector  wasn't found.
//  24 : ERROR if the document CATPart where the second single connector is defined wasn't found.
//  25 : ERROR if it is not possible to create a list of CATBaseUnkonwn.
//  26 : ERROR if the single connector reference wasn't found correctly
//  27 : ERROR if the creation of the first cavity on the second single connector has failed
//  28 : ERROR if the second cavity was correctly created on the second single connector.
//  29 : ERROR if the third cavity was correctly created on the second single connector.
//  30 : ERROR in removing document
//  31 : ERROR in deleting session.
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  mkrun -c "CAAElecDeviceFactory  input1 input2 input3 input4 input5 output1 output2 output3
//                                  output4 output5 output6 output7" where :
//      . "input1" is the path of the file where is the part "BACK_SHELL.CATPart"
//      . "input2" is the path of the file where is the part "Single_Connector.CATPart"
//      . "input3" is the path of the file where is the part "Second_SingleConnector.CATPart"
//      . "input4" is the path of the file where is the part "Third_Single_Connector.CATPart"
//      . "input5" is the path of the file where is the part "MountingEquipment.CATPart"
//      . "output1" is the path of the file to save in the document "BACK_SHELL.CATPart".
//      . "output2" is the path of the file to save in the document "Single_Connector.CATPart".
//      . "output3" is the path of the file to save in the document "Second_SingleConnector.CATPart".
//      . "output4" is the path of the file to save in the document "Third_Single_Connector.CATPart".
//      . "output5" is the path of the file to save in the document "MountingEquipment.CATPart".
//      . "output6" is the path of the file to save in the document aggregate under the main document.
//      . "output7" is the path of the file to save in the main document.    
// 
//
//
//  found in the 'WS'/'OS'/resources/graphic/CAAElecDeviceFactory directory if under Unix.
//      In this case, 'OS' can be any of the following: 
//         aix_a for IBM
//         hpux_a for HP
//         irix_a for SGI
//         solaris_a for SUN
//  Under Windows, the path would indicate:  'WS'\intel_a\resources\graphic\CAAElecDeviceFactory directory. 
//
//
//=====================================================================================================

// C++ include ( result display )
// LRO 08:01:15
#include "CATBaseUnknown.h"
#include "CATBoolean.h"
#include "CATIContainer.h"
#include "CATILinkableObject.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATLISTV_CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATSession.h"
#include "CATUnicodeString.h"

#include <iostream.h>
#include "CATLib.h"    
// ObjectModelerBase interfaces
#include "CATSessionServices.h"    // managing session
#include "CATDocumentServices.h"   // managing documents in session
#include "CATDocument.h"           // manipulating documents
#include "CATIDocRoots.h"          // browsing root objects in documents
#include "CATInit.h"

// ProductStructure interfaces 
// ---------------------------
#include "CATIProduct.h"           // managing products  
#include "CATIADocument.h"
#include "CATIPrdObjectPublisher.h"

// Feature modeler
// ---------------
#include "CATISpecObject.h"

// GSM interfaces 
// --------------
#include "CATIGSMPoint.h"
#include "CATIGSMLine.h"

// Part and product interfaces 
// --------------------
#include "CATIAlias.h"
#include "CATIDescendants.h"
#include "CATIAProducts.h"
#include "CATIAProduct.h"
#include "CATIPrtPart.h"
#include "CATIPrtContainer.h"


// Electrical Device Interfaces
// ----------------------------
#include "CATIElbSingleConnector.h"
#include "CATIElbSingleConnectorReference.h"
#include "CATIElbMountingEquipmentReference.h"
#include "CATIElbConnectorCnctPt.h"  
#include "CATIElbBackShell.h"
#include "CATIElbTermination.h"
#include "CATIElbCavity.h"

// Electrical interfaces
// ---------------------
#include "CATIEleDocServices.h"    // initializing electrical environement 
#include "CATIElbFactory.h"

#include "CATIConnector.h"




/***
 *   Method used to import a document from a PATH in session
 *    ihProductTarget : the product of output will be aggregating under the ihProductTarget.
 *    PATH  :  the path of product that we want importing in current session. 
 *    oProduct : the product result was defined under ihProductTarget.
 */
HRESULT Import (const CATIProduct_var& ihProductTarget, const CATUnicodeString& PATH, CATIProduct *& oProduct)
{
  cout << "  ---->  Method Import : " <<  endl;
  HRESULT RC(S_OK);
 
  cout << " Import : " <<  PATH.ConvertToChar() << endl;

  CATDocument* ptDocument = NULL;
  RC = CATDocumentServices::OpenDocument(PATH, ptDocument, TRUE);
  
  if ( FAILED (RC) || !ptDocument ) 
  {
    cout << "  ---->  Method Import : call of services CATDocumentServices::OpenDocument failed he doesnt return ptDocument or return E_FAIL   " <<  endl;
    return RC; // if method failed exit
  } 
  if (ptDocument) 
  {
    cout << "  ---->  Method Import : call of services CATDocumentServices::OpenDocument succeeded   " <<  endl;
    CATIAProducts_var hRootProducts (ihProductTarget);  
    if(NULL_var == hRootProducts) 
    {
      cout << "  ---->  Method Import : cast ihProductTarget in CATIAProducts_var failed   " << endl;
      return RC;
    }
    
    CATIADocument *pCAADocument = NULL;
    RC = ptDocument->QueryInterface(IID_CATIADocument, (void **)&pCAADocument);
    if ( FAILED (RC) || !pCAADocument ) 
    {
      cout << "  ---->  Method Import : cast ptDocument in CATIADocument failed   " <<  endl;
      return RC;
    }
    
    CATIAProduct * pInstantiatedProduct = NULL;
    RC = hRootProducts->AddExternalComponent(pCAADocument, pInstantiatedProduct);
    if ( FAILED (RC) || !pInstantiatedProduct ) 
    {
      cout << "  ---->  Method Import : call of services AddExternalComponent return E_FAIL or return a null pointer  " <<  endl;
      return RC;
    }
    pCAADocument->Release();       
    RC = pInstantiatedProduct->QueryInterface(CATIProduct::ClassId(), (void**)& oProduct);
    if ( FAILED (RC) || !oProduct )
    {
      cout << "  ---->  Method Import : cast of pointer returned by AddExternalComponent in CATIProduct  return E_FAIL or return a null pointer  " << endl;
      return RC;
    }
    pInstantiatedProduct->Release();
  }
  cout << "  <----  Method Import : " << endl;
  return RC;
}



/**
*   Method FindInPart
*   This method return oEntity which is defined in the hPart, with alias value is InstanceName
*   and which adhere on iIID interface
*
*/
HRESULT FindInPart (CATIPrtPart_var& hPart, const IID &iIID, const CATUnicodeString& InstanceName, CATBaseUnknown*& oEntity)
{
  HRESULT RC(S_OK);
  cout << "  ---->  Method FindInPart : " << endl;
  oEntity = NULL;
  if(NULL_var == hPart) 
  {
   cout << "  ---->  Method FindInPart : the input value of the CATIPrtPart_var hPart is null  " << endl;
    return RC;
  }

  // Finding all CATISpecObject children of the part
  // -----------------------------------------------
  CATIDescendants_var hDescendant(hPart);
  CATListValCATISpecObject_var  hElementlist; 
  hDescendant->GetAllChildren(CATISpecObject::ClassName(), hElementlist);
  cout << "  ---->  Method FindInPart : finding all CATISpecObject children of the part  " << endl;
 
  int Taille_ElementList = hElementlist.Size() ;
  cout << "  ---->  Method FindInPart : the size of the list of CATISpecObject children in the part is :   " <<Taille_ElementList << endl;
  
  // if one of the element of the list of CATISpecObject has the same alias that InstanceName we return it
  // -----------------------------------------------------------------------------------------------------
  for (int i=1; i<=Taille_ElementList ; i++)
  {
    CATBaseUnknown * ptInternalPtr = NULL;
    CATIAlias * pAlias = NULL; ;
    CATBaseUnknown_var spCBU (hElementlist[i]);
    if (NULL_var != spCBU && SUCCEEDED(spCBU->QueryInterface(IID_CATIAlias,(void**)&pAlias)) && pAlias) 
    {
      spCBU->QueryInterface (iIID, (void**)& ptInternalPtr);
      if (NULL != ptInternalPtr) 
      {
        if (pAlias->GetAlias() == InstanceName) 
        {
          RC = ptInternalPtr->QueryInterface(CATBaseUnknown::ClassId(), (void**)& oEntity);
          if(SUCCEEDED(RC) && oEntity)
          {
            cout << "  ---->  Method FindInPart SUCCEEDED and return the good entity : " <<  endl;
            ptInternalPtr->Release();
            pAlias->Release();
            break;
          }
          else 
          {
            cout << "  ---->  Method FindInPart FAILED : we find a children in the part wich have the instance name of input but can't return the good entity ???: " << endl;
            RC = E_FAIL;
            ptInternalPtr->Release(); 
            return RC;
          }          
        }
        ptInternalPtr->Release();
        ptInternalPtr=NULL;
      }
      pAlias->Release();
      pAlias= NULL;
    }
  }  
  if (!oEntity) 
  {
    RC = E_FAIL;
    cout << " *** ERROR ***  ---->  Method FindInPart FAILED Element entity not found entity <---- *** ERROR *** " << endl;
  }

  cout << "  <----  Method FindInPart : " <<  endl;
  return RC;
}


int main (int argc, char * argv[] )
{ 

  //--------------------------------------------------------------------
  // 1. Prologue 
  //--------------------------------------------------------------------
  cout << endl << flush;
  cout << endl << flush;
  cout << "----------------------------------------------------------------" << endl << flush;
  cout << endl << flush;
  //
  // 1.1--- Check inputs
  //
  if ( 13 !=argc )
  {
    cout << " ERROR : number of inputs is invalid : " << argc << endl;
    return 1;
  }

  

  // --- initialize part numbers and file names
  // ------------------------------------------
  CATUnicodeString  PATH_Back_Shell (argv[1]);
  CATUnicodeString  PATH_Single_Connector (argv[2]);
  CATUnicodeString  PATH_Second_SIC (argv[3]);
  CATUnicodeString  PATH_Third_SIC (argv[4]);
  CATUnicodeString  PATH_MountingEqt (argv[5]);

  cout << "> input checked " << endl << flush;
  cout << "   + path  BACK SHELL : "<< argv[1] << endl << flush;
  cout << "   + path  SINGLE CONNECTOR : "<< argv[2] << endl << flush;
  cout << "   + path  SECOND SINGLE CONNECTOR : "<< argv[3] << endl << flush;
  cout << "   + path  THIRD SINGLE CONNECTOR : "<< argv[4] << endl << flush;
  cout << "   + path  MOUNTING EQUIPMENT: "<< argv[5] << endl << flush;


   //
  //1.2--- Creating the Session 
  
  CATSession *pSession = NULL;
  
  char *sessionName = "CAA_ElecDeviceFactory_Session";
  HRESULT rc = ::Create_Session(sessionName,pSession);
  if ((SUCCEEDED(rc)) && (NULL != pSession))
  {
    cout << "> session created : " << sessionName <<endl << flush;
  }
  else
  {
    cout << "ERROR in creating session" << sessionName << endl << flush;
    return 2;
  }
  
  // 1.3--- Creating a new CATProduct document :  
  
  CATDocument *pMainPrdDoc = NULL; // pMainPrdDoc is a pointer to the CATProduct document 
  

  rc = CATDocumentServices::New("Product", pMainPrdDoc);
  if (SUCCEEDED(rc) && (NULL != pMainPrdDoc))
  {
    cout << "> document created " << endl << flush;
  }
  else
  {
    cout << "ERROR in creating CATProduct document" << endl << flush;
    return 3;
  }


  // 1.4--- Retrieving root product of the created document 
 
  CATIProduct* piRootProduct = NULL; // piRootProduct is a handle to document root product
  
  CATIDocRoots * pMain_ProductDocRoots = NULL;
  rc = pMainPrdDoc->QueryInterface(IID_CATIDocRoots,(void**) &pMain_ProductDocRoots);
  if ( FAILED(rc) || (NULL==pMain_ProductDocRoots) ) return 4;
  CATListValCATBaseUnknown_var* pListRootProduct = pMain_ProductDocRoots->GiveDocRoots();
  pMain_ProductDocRoots->Release();
  pMain_ProductDocRoots=NULL;
  
  CATBaseUnknown_var spCBU ((*pListRootProduct)[1]);
  if ( pListRootProduct && pListRootProduct->Size() && NULL_var != spCBU)
  {  
    rc = spCBU->QueryInterface(IID_CATIProduct,(void**) &piRootProduct );
    delete pListRootProduct;
    pListRootProduct = NULL;
    //
    if  (SUCCEEDED(rc) && (NULL != piRootProduct))
      cout << "> root product found in document " << endl << flush;
    else
    {
      cout << "ERROR : Root product not found in document " << endl << flush;
      return 5;
    }
  }
  
  //--------------------------------------------------------------------
  // 2. Initializing Electrical Environment 
  //--------------------------------------------------------------------
  
  CATIEleDocServices * piElecDocServices = NULL;
  
  rc = pMainPrdDoc ->QueryInterface(IID_CATIEleDocServices,(void**) &piElecDocServices );
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
    return 6;
  }
  
  if ( NULL != piElecDocServices )
  {
    piElecDocServices->Release();
    piElecDocServices=NULL;
  }

  // 3. Importing the part "Back_Shell.CATPart".
  // -------------------------------------------

  // Adding a level under the root product
  // -------------------------------------
  
  CATIProduct_var hProduct_Level_1 = piRootProduct->AddProduct("Product_Lv1");
  piRootProduct->Release();
  piRootProduct = NULL;

  CATIProduct * pProduct_BackShell = NULL;
  rc = Import(hProduct_Level_1, PATH_Back_Shell,pProduct_BackShell);
  if(SUCCEEDED(rc) && pProduct_BackShell)
  {
    cout << "> import of the product back shell succeeded " << endl << flush;
  }
  else
  {
    cout << "ERROR : import of the product back shell failed " << endl << flush;
    return 7;
  }
  
  // finding document associated on hProduct_Level_1
  // -----------------------------------------------
  
  CATILinkableObject_var hLinkable_Level_1(hProduct_Level_1) ;
  if (NULL_var == hLinkable_Level_1) 
  {
	cout << "ERROR : hLinkable_Level_1 handler is null " << endl << flush;
    return 8;
  }
  CATDocument    * pDoc_Level_1 = hLinkable_Level_1 ->  GetDocument ();

  // 4.  Defining the Back Shell
  // ---------------------------

  // 4.1 Extend the mechanical product pProduct_BackShell in type ElecBackShellE
  // ----------------------------------------------------------------------------

  CATIProduct_var hProduct_BackShell_Ref = pProduct_BackShell->GetReferenceProduct();
  pProduct_BackShell->Release();
  pProduct_BackShell = NULL;
  CATIElbFactory_var hElbFactory(hProduct_BackShell_Ref);
  if (NULL_var == hElbFactory) return 9;
  rc = hElbFactory -> ExtendPrdAsBackShell() ;
  if(SUCCEEDED(rc))
  {
    cout << "> extend  the product pProduct_BackShell in type ElecBackshellE succeeded  " << endl << flush;
  }
  else
  {
    cout << "extend  the product pProduct_BackShell in type ElecBackshellE failed " << endl << flush;
    return 10;
  }

  

  // 5. Importing the part "SingleConnector.CATPart" under the root product.
  // ------------------------------------------------------------------------------

  // Adding a level under the root product
  // -------------------------------------
  CATIProduct * pProduct_Single_Connector = NULL;  
  rc = Import(hProduct_Level_1, PATH_Single_Connector,pProduct_Single_Connector);
  if(SUCCEEDED(rc) && pProduct_Single_Connector)
  {
    cout << "> import of the product  single connector succeeded " << endl << flush;
  }
  else
  {
    cout << "ERROR : import of the product  single connector failed " << endl << flush;
    return 11;
  }
  
  
  //  6. Defining the Single Connector
  //  --------------------------------- 

  //   6.1 Extend the mechanical product pProduct_First_Single_Connector in type ElecSicConE
  //   -------------------------------------------------------------------------------------

  CATIProduct_var hProduct_Single_Connector_Ref = pProduct_Single_Connector->GetReferenceProduct();
  hElbFactory = hProduct_Single_Connector_Ref;
  if (NULL_var == hElbFactory) return 12;
  rc = hElbFactory -> ExtendPrdAsSingleConnector() ;
  if(SUCCEEDED(rc))
  {
    cout << "> extend  the product pProduct_Single_Connector in type ElecSicConE succeeded  " << endl << flush;
  }
  else
  {
    cout << "extend  the product pProduct_Single_Connector in type ElecSicConE failed " << endl << flush;
    return 13;
  }

  //  6.2  Adding a Termination on the single connector
  //  -------------------------------------------------

  // Finding the geometrical element of the single connector
  // -------------------------------------------------------

  
  CATILinkableObject_var hLinkable_SIC (hProduct_Single_Connector_Ref);
  if (NULL_var == hLinkable_SIC) 
  {
	cout << "ERROR : hLinkable_SIC handler is null " << endl << flush;
    return 14;
  }
  CATDocument * pDocOfPart_SIC = hLinkable_SIC->GetDocument();
  if(pDocOfPart_SIC && (pDocOfPart_SIC->IsAKindOf("CATPart")) ) 
  {
    cout << "> geometrical element : Reference hProduct_Single_Connector_Ref is defined in CATPart Document " << endl << flush;
  }
  else 
  {
    cout << "> WARNING geometrical element : Reference hProduct_Single_Connector_Ref is not defined in CATPart Document  " << endl << flush;
    return 15;
  }

  // Finding the root container of the document containing the part Back Shell
  // -------------------------------------------------------------------------
  CATInit_var hInit_SIC (pDocOfPart_SIC);
  CATBaseUnknown * pPart_SIC_RootContainer = hInit_SIC->GetRootContainer(CATIContainer::ClassName());

  // Retrieving the part
  // -------------------
  CATIContainer_var hPart_SIC_RootContainer =pPart_SIC_RootContainer;
  if( pPart_SIC_RootContainer ) pPart_SIC_RootContainer ->Release();
  CATIPrtContainer_var hPartContainer_SIC = hPart_SIC_RootContainer;
  CATIPrtPart_var hPart_SIC = hPartContainer_SIC->GetPart();
  
  if(NULL_var != hPart_SIC)
  {
    cout << "> geometrical element : the part of the single connector was found successfully " << endl << flush;  
  }
  else
  {
    cout << "> geometrical element : the part of the single connector was not found " << endl << flush;  
    return 16;
  }

  // Retrieving the first point "Point.1" defined in the openbody of the part of the single connector
  // ------------------------------------------------------------------------------------------------
  CATBaseUnknown * pPointOnSIC = NULL;
  rc = FindInPart(hPart_SIC,IID_CATIGSMPoint,"Point.1",pPointOnSIC);  
  if(SUCCEEDED(rc) && pPointOnSIC)
  {
    cout << "> geometrical element : the Point.1 defined in the OpenBody of the sic was found successfully " << endl << flush;  
  }
  else
  {
    cout << "> geometrical element : the Point.1 defined in the OpenBody of the sic wasn't found  ....**** ERROR **** " << endl << flush;  
    return 17;
  }
  
  
  // Retrieving the  point "Point.2" defined in the openbody of the part of the single connector
  // -------------------------------------------------------------------------------------------
  CATBaseUnknown * pSecondPointOnSIC = NULL;
  rc = FindInPart(hPart_SIC,IID_CATIGSMPoint,"Point.2",pSecondPointOnSIC);  
  if(SUCCEEDED(rc) && pSecondPointOnSIC)
  {
    cout << "> geometrical element : the Point.2 defined in the OpenBody of the sic was found successfully " << endl << flush;  
  }
  else
  {
    cout << "> geometrical element : the Point.2 defined in the OpenBody of the sic wasn't found  ....**** ERROR **** " << endl << flush;  
    pPointOnSIC->Release();
    pPointOnSIC = NULL;
    return 18;
  }
  
 
  // Finding the Product where graphical representation of the single connector is defined 
  // -------------------------------------------------------------------------------------
  CATIProduct * pGeoDefinition_SIC = NULL;
  rc =hProduct_Single_Connector_Ref-> QueryInterface(IID_CATIProduct,(void**)& pGeoDefinition_SIC);
  if(SUCCEEDED(rc) && pGeoDefinition_SIC)
  {
    cout << "> geometrical element : the GeoDefinition of the single connector is ok " << endl << flush;  
  }
  else
  {
    cout << "> geometrical element : the GeoDefinition of the single connector wasn't ok  ....**** ERROR **** " << endl << flush; 
    pPointOnSIC->Release();
    pPointOnSIC = NULL;
    pSecondPointOnSIC->Release();
    pSecondPointOnSIC = NULL;
    return 19;
  }
  
  // Finding the  point  graphical representation 
  // --------------------------------------------
  CATILinkableObject * ptRepresentationOfSecPoint_SIC = NULL;
  rc = pSecondPointOnSIC->QueryInterface(IID_CATILinkableObject, (void**)& ptRepresentationOfSecPoint_SIC);
  if(SUCCEEDED(rc) && ptRepresentationOfSecPoint_SIC)
  {
    cout << "> geometrical element : the representation of the first point of the single connector is ok " << endl << flush;  
  }
  else
  {
    cout << "> geometrical element : the representation of the first point of the single connector wasn't ok  ....**** ERROR **** " << endl << flush;  
    pPointOnSIC->Release();
    pPointOnSIC = NULL;
    pSecondPointOnSIC->Release();
    pSecondPointOnSIC = NULL;
    pGeoDefinition_SIC->Release();
    pGeoDefinition_SIC = NULL;
    return 20;
  }  
  pSecondPointOnSIC -> Release();
  pSecondPointOnSIC = NULL;

  

  CATILinkableObject * ptRepresentationOfPoint_SIC = NULL;
  rc = pPointOnSIC->QueryInterface(CATILinkableObject::ClassId(), (void**)& ptRepresentationOfPoint_SIC);
  pPointOnSIC ->Release();
  pPointOnSIC = NULL;
  if(SUCCEEDED(rc) && ptRepresentationOfPoint_SIC)
  {
    cout << "> geometrical element : the representation of the second point of the single connector is ok " << endl << flush;  
  }
  else
  {
    cout << "> geometrical element : the representation of the second point of the single connector wasn't ok  ....**** ERROR **** " << endl << flush;  
    pGeoDefinition_SIC->Release();
    pGeoDefinition_SIC = NULL;
    return 21;
  }


  // creation of two terminations on the single connector.
  // -----------------------------------------------------
  CATIElbSingleConnectorReference_var hSingleConnectorRefer(hProduct_Single_Connector_Ref);
  if (NULL_var == hSingleConnectorRefer )
  {
	  cout <<">  hSingleConnectorRefer is a handler null " << endl << flush;
	  pGeoDefinition_SIC->Release();
	  pGeoDefinition_SIC = NULL;
	  ptRepresentationOfPoint_SIC->Release();
	  ptRepresentationOfPoint_SIC = NULL;
	  ptRepresentationOfSecPoint_SIC->Release();
	  ptRepresentationOfSecPoint_SIC=NULL;
	  return 22;
  }
  
  CATUnicodeString Id_Number = "Termination_01";
  int iPositionNumber = 0;
  CATIElbTermination * pElbTermination = NULL;
  rc = hSingleConnectorRefer->AddTermination(Id_Number,
	  iPositionNumber,
	  pGeoDefinition_SIC,
	  ptRepresentationOfPoint_SIC,
	  pElbTermination);
  if(SUCCEEDED(rc) && pElbTermination)
  {
      cout << "> the first termination was created successfully" << endl << flush;  
  }
  else
  {
      cout << "> the creation of first termination failed  ....**** ERROR **** " << endl << flush;  
      pGeoDefinition_SIC->Release();
      pGeoDefinition_SIC = NULL;
      ptRepresentationOfPoint_SIC->Release();
      ptRepresentationOfPoint_SIC = NULL;
      ptRepresentationOfSecPoint_SIC->Release();
      ptRepresentationOfSecPoint_SIC=NULL;
      return 23;
  }
  
  Id_Number = "Termination_02";    
  CATIElbTermination * pElbTermination2 = NULL;
  rc = hSingleConnectorRefer->AddTermination(Id_Number,
	  iPositionNumber,
	  pGeoDefinition_SIC,
	  ptRepresentationOfSecPoint_SIC,
	  pElbTermination2);
  if(SUCCEEDED(rc) && pElbTermination2)
  {
      cout << "> the second termination was created successfully" << endl << flush;  
  }
  else
  {
      cout << "> the creation of second termination failed  ....**** ERROR **** " << endl << flush;  
      pGeoDefinition_SIC->Release();
      pGeoDefinition_SIC = NULL;
      ptRepresentationOfPoint_SIC->Release();
      ptRepresentationOfPoint_SIC = NULL;
      ptRepresentationOfSecPoint_SIC->Release();
      ptRepresentationOfSecPoint_SIC=NULL;
      return 24;
  }   
  
  if(pElbTermination2) pElbTermination2->Release();
  pElbTermination2 = NULL;
  if(pElbTermination ) pElbTermination->Release();
  pElbTermination = NULL;   
  

  // creation of a connector connection point  on the single connector.
  // ------------------------------------------------------------------

  CATListValCATBaseUnknown_var * pListJointReferenceFirstSIC = new CATListValCATBaseUnknown_var();
  if(!pListJointReferenceFirstSIC) 
  {      
      cout << "> PB ! : not possible to create a list of CATBaseUnkonwn ????? <  " << endl << flush;
      return 25;
  }


  CATListValCATUnicodeString * pListOfPublications = NULL;

  int result=0;
  CATIPrdObjectPublisher * pPrdObjectPublisher = NULL;

  rc = pProduct_Single_Connector->QueryInterface(IID_CATIPrdObjectPublisher,(void**)&pPrdObjectPublisher);
  if(SUCCEEDED(rc) && pPrdObjectPublisher ) 
  {
    cout << "> the object publisher was found " << endl << flush;
  }
  else 
  {
    cout << "> WARNING  : the object publisher wasn't found  " << endl << flush;
    return 26;
  }

  int hasPublication = pPrdObjectPublisher->ListPublications(pListOfPublications);
  int SizeListPub = pListOfPublications ? pListOfPublications->Size() : 0;
  cout << "  SizeListPub of first sic="<< SizeListPub << endl << flush;
  if (SizeListPub <= 0)
  {
	  cout << "> WARNING  : the object publisher wasn't found  " << endl << flush;
	  return 27;
  }
  
  cout << "> We found the list of publication of geometry on the first single connector " << endl << flush;

  CATBaseUnknown * P_PublicationGeometrique=NULL;
  CATUnicodeString SubPublication;
  CATILinkableObject * pRepresentation = NULL;

  int i = 1;
  for(;i<=3;i++)
  {
	  cout << "> pub=" << (*pListOfPublications)[i].ConvertToChar() << endl << flush;
      result = pPrdObjectPublisher->GetDirectObject (  (*pListOfPublications)[i],
		  P_PublicationGeometrique,
		  SubPublication);      
      if(P_PublicationGeometrique)
      {
		  CATBaseUnknown_var hUnk_PubGeo(P_PublicationGeometrique);
		  P_PublicationGeometrique -> Release();
		  P_PublicationGeometrique =  NULL;
		  if(NULL_var!=hUnk_PubGeo) pListJointReferenceFirstSIC->Append(hUnk_PubGeo);      
      }
  }

  delete pListOfPublications;
  pListOfPublications=NULL;

  pPrdObjectPublisher->Release();
  pPrdObjectPublisher=NULL;

  // dump of the stack
  SizeListPub = pListJointReferenceFirstSIC?pListJointReferenceFirstSIC->Size() : 0;
  cout << " Size of pListJointReferenceFirstSIC="<< SizeListPub << endl << flush;


  CATIElbSingleConnector * pElbSIC = NULL;
  rc = pProduct_Single_Connector->QueryInterface(IID_CATIElbSingleConnector,(void**) & pElbSIC);

  if(!pElbSIC)
  {
    cout << "ERROR : QI CATIElbSingleConnector on pProduct_Single_Connector is KO " << endl << flush;
    return 28;
  }

  CATUnicodeString JointType = "ConnectorCnctPt";
  Id_Number = "ConnectorCnctPt_01";    
  CATIElbConnectorCnctPt * pElbCntrCnctPt = NULL;

  rc = pElbSIC->AddConnectorCnctPt(Id_Number,
      pProduct_Single_Connector,
	  ptRepresentationOfPoint_SIC,
	  JointType,
	  pListJointReferenceFirstSIC,
	  pElbCntrCnctPt);

  pElbSIC->Release();
  pElbSIC=NULL;

  if (pListJointReferenceFirstSIC)delete pListJointReferenceFirstSIC;
  pListJointReferenceFirstSIC = NULL;

  if(SUCCEEDED(rc) && pElbCntrCnctPt)
  {
      cout << "> the first connector connection point was created successfully" << endl << flush;  
  }
  else
  {
      cout << "> the creation of first connector connection point failed  ....**** ERROR **** " << endl << flush;  
      pGeoDefinition_SIC->Release();
      pGeoDefinition_SIC = NULL;
      ptRepresentationOfPoint_SIC->Release();
      ptRepresentationOfPoint_SIC = NULL;
      ptRepresentationOfSecPoint_SIC->Release();
      ptRepresentationOfSecPoint_SIC=NULL;
      return 29;
  }

  pGeoDefinition_SIC->Release();
  pGeoDefinition_SIC = NULL;
  ptRepresentationOfPoint_SIC->Release();
  ptRepresentationOfPoint_SIC = NULL;
  ptRepresentationOfSecPoint_SIC->Release();
  ptRepresentationOfSecPoint_SIC=NULL;
  if (pElbCntrCnctPt) pElbCntrCnctPt->Release();
  pElbCntrCnctPt=NULL;
  pProduct_Single_Connector->Release();
  pProduct_Single_Connector=NULL;
  
    
  // Import the second single connector to create three cavities
  // -----------------------------------------------------------
  CATIProduct * pProduct_Second_SIC= NULL;  
  rc = Import(hProduct_Level_1, PATH_Second_SIC,pProduct_Second_SIC);
  if(SUCCEEDED(rc) && pProduct_Second_SIC)
  {
    cout << "> import of the product  second single connector succeeded " << endl << flush;
  }
  else
  {
    cout << "ERROR : import of the product  second single connector failed " << endl << flush;
    return 30;
  }
  
  // Retrieving the product vhere the geometry of the second single connector was defined
  // ------------------------------------------------------------------------------------
  CATIProduct_var hProductSecondSICRef = pProduct_Second_SIC->GetReferenceProduct();
  pProduct_Second_SIC -> Release();
  pProduct_Second_SIC = NULL;
  if(NULL_var!= hProductSecondSICRef)
  {
    cout << ">the reference product of the second single connector in context was found " << endl << flush;
  }
  else
  {
    cout << "ERROR : the reference product of the second single connector in context wasn't found " << endl << flush;    
    return 31;
  }

  CATIProduct * pGeoDefinition_SecondSIC = NULL;
  rc = hProductSecondSICRef->QueryInterface(IID_CATIProduct,(void**) & pGeoDefinition_SecondSIC);
  if(SUCCEEDED(rc) && pGeoDefinition_SecondSIC)
  {
    cout << ">the product where the geometry of the second single connector is defined was found " << endl << flush;
  }
  else
  {
    cout << "ERROR : the product where the geometry of the second single connector is defined wasn't found " << endl << flush;
    return 32;
  }
  
  // finding the geometry of the second single connector
  // ---------------------------------------------------
  CATILinkableObject * pRepresentationOfSecSIC = NULL;
  rc = hProductSecondSICRef->QueryInterface(IID_CATILinkableObject,(void**) & pRepresentationOfSecSIC);
  if(SUCCEEDED(rc) && pRepresentationOfSecSIC)
  {
    cout << ">the  the geometrical representation of the second single connector  was found " << endl << flush;
  }
  else
  {
    cout << "ERROR : the geometrical representation of the second single connector  wasn't found " << endl << flush;
    pGeoDefinition_SecondSIC-> Release();
    pGeoDefinition_SecondSIC = NULL;
    return 33;
  }
 
  // finding the document were the part of the second single connector was found
  // ---------------------------------------------------------------------------
  CATDocument * pDocOfPart_SecondSIC = pRepresentationOfSecSIC->GetDocument();
  if(pDocOfPart_SecondSIC && (pDocOfPart_SecondSIC->IsAKindOf("CATPart")) ) 
  {
    cout << "> the document CATPart where the second single connector is defined was found " << endl << flush;
  }
  else 
  {
    cout << "> WARNING  : the document CATPart where the second single connector is defined wasn't found  " << endl << flush;
    pGeoDefinition_SecondSIC -> Release();
    pGeoDefinition_SecondSIC = NULL;
    pRepresentationOfSecSIC -> Release();
    pRepresentationOfSecSIC = NULL;
    return 34;
  }

  // Finding the list of geometry that is published
  // ----------------------------------------------
  
  rc = hProductSecondSICRef->QueryInterface(IID_CATIPrdObjectPublisher,(void**)&pPrdObjectPublisher);
  if(SUCCEEDED(rc) && pPrdObjectPublisher ) 
  {
    cout << "> the object publisher was found " << endl << flush;
  }
  else 
  {
    cout << "> WARNING  : the object publisher wasn't found  " << endl << flush;
    pGeoDefinition_SecondSIC -> Release();
    pGeoDefinition_SecondSIC = NULL;
    pRepresentationOfSecSIC -> Release();
    pRepresentationOfSecSIC = NULL;
    return 35;
  }

  
  hasPublication = pPrdObjectPublisher->ListPublications(pListOfPublications);
  SizeListPub = pListOfPublications ? pListOfPublications->Size() : 0;
  cout << "  SizeListPub="<< SizeListPub << endl << flush;
  if (SizeListPub <= 0)
  {
	  cout << "> WARNING  : the object publisher wasn't found  " << endl << flush;
	  return 36;
  }
  
  cout << "> We found the list of publication of geometry on the second single connector " << endl << flush;
  
  CATListValCATBaseUnknown_var * pListJointReference = new CATListValCATBaseUnknown_var();
  if(!pListJointReference) 
  {
      // lifecycleobject management
      // --------------------------
      cout << "> PB ! : not possible to create a list of CATBaseUnkonwn ????? <  " << endl << flush;
      pGeoDefinition_SecondSIC -> Release();
      pGeoDefinition_SecondSIC = NULL;
      pRepresentationOfSecSIC -> Release();
      pRepresentationOfSecSIC = NULL;
      pPrdObjectPublisher->Release();
      pPrdObjectPublisher = NULL;
      return 37;
  }
  
  // creation of the first cavity
  // ----------------------------

  for (i=1;i<=2;i++)
  { 
	  
      // Retrieving the list of geometry  that represent the first cavity that we would like to create
      // ---------------------------------------------------------------------------------------------
      result = pPrdObjectPublisher->GetDirectObject (  (*pListOfPublications)[i],
		  P_PublicationGeometrique,
		  SubPublication);
      
if(P_PublicationGeometrique)
{
        CATIConnector_var hConnector(P_PublicationGeometrique);
        if(NULL_var != hConnector)
        {
          CATILinkableObject_var hLinkable = hConnector->GiveReferenceObject();
          if(NULL_var != hLinkable)
          {
            P_PublicationGeometrique->Release();
            P_PublicationGeometrique = NULL;
            hLinkable->QueryInterface(IID_CATBaseUnknown,(void **)&P_PublicationGeometrique);
          }
        }
}
	  
      if(P_PublicationGeometrique)
      {
		  // the cavity is represented by the first geometry published in the list
		  // ----------------------------------------------------------------------
		  if(i==1) 
			  P_PublicationGeometrique->QueryInterface(IID_CATILinkableObject,(void**)&pRepresentation);
		  CATBaseUnknown_var hUnk_PubGeo(P_PublicationGeometrique);
		  P_PublicationGeometrique -> Release();
		  P_PublicationGeometrique =  NULL;
		  
		  // we create the list of geometrical element that defined the cavity
		  // -----------------------------------------------------------------
		  if(NULL_var!=hUnk_PubGeo) pListJointReference->Append(hUnk_PubGeo);      
      }
  }
  
  
  CATIElbSingleConnectorReference * pElecRefSecondSIC = NULL;
  rc = hProductSecondSICRef->QueryInterface(IID_CATIElbSingleConnectorReference,(void**) &pElecRefSecondSIC);
  if(SUCCEEDED(rc) && pElecRefSecondSIC )
  {
      cout << ">the single connector reference was found correctly" << endl << flush;
  }
  else
  {
      cout << " WARNING > the single connector reference wasn't found correctly" << endl << flush;
      pGeoDefinition_SecondSIC -> Release();
      pGeoDefinition_SecondSIC = NULL;
      pRepresentationOfSecSIC -> Release();
      pRepresentationOfSecSIC = NULL;
      pPrdObjectPublisher->Release();
      pPrdObjectPublisher = NULL;
      if(P_PublicationGeometrique) P_PublicationGeometrique->Release();
      P_PublicationGeometrique = NULL;
      return 38;
  }
  
  // creation of the first cavity on the single connector
  // -----------------------------------------------------
  // Id_Number : this parameter define the string that define the cavity
  // Number    : this parameter define the position of the cavity on the single connector.
  // ------------------------------------------------------------------------------------
  Id_Number = "First_Cavity";
  int Number = 0;
  CATIElbCavity * pElbCavity = NULL;
  rc = pElecRefSecondSIC->AddCavity(Id_Number, Number, pGeoDefinition_SecondSIC,pRepresentation,pListJointReference,pElbCavity);    
  if(SUCCEEDED(rc) && pElbCavity)
  {
      cout << "the first cavity was correctly created on the second single connector" << endl << flush;
  }
  else
  {
      cout<<"WARNING : a problem on the creation of the first cavity on the second single connector"<<endl<<flush;
	  
      pGeoDefinition_SecondSIC -> Release();
      pGeoDefinition_SecondSIC = NULL;
      pRepresentationOfSecSIC -> Release();
      pRepresentationOfSecSIC = NULL;
      pPrdObjectPublisher->Release();
      pPrdObjectPublisher = NULL;
      if(P_PublicationGeometrique) P_PublicationGeometrique->Release();
      P_PublicationGeometrique = NULL;
      delete pListJointReference;
      pListJointReference = NULL;
      if(pElbCavity) pElbCavity->Release();
      pElbCavity = NULL;
      if(pRepresentation) pRepresentation->Release();
      pRepresentation = NULL;	  
      return 39;
  }
  
  delete pListJointReference;
  pListJointReference = NULL;
  if(pElbCavity) pElbCavity->Release();
  pElbCavity = NULL;
  if(pRepresentation) pRepresentation->Release();
  pRepresentation = NULL;
  
  // Creation of the second cavity
  // -----------------------------
  
  CATListValCATBaseUnknown_var * pListJointReferenceSecCav = new CATListValCATBaseUnknown_var();
  if(!pListJointReferenceSecCav) 
  {
      cout << "> PB ! : not possible to create a list of CATBaseUnkonwn ????? <  " << endl << flush;
      return 40;
  }
  
  for( i=3;i<=4;i++)
  {
      // Retrieving the list of geometry  that represent the first cavity that we would like to create
      // ---------------------------------------------------------------------------------------------
      result = pPrdObjectPublisher->GetDirectObject (  (*pListOfPublications)[i],
		  P_PublicationGeometrique,
		  SubPublication);

if(P_PublicationGeometrique)
{
        CATIConnector_var hConnector(P_PublicationGeometrique);
        if(NULL_var != hConnector)
        {
          CATILinkableObject_var hLinkable = hConnector->GiveReferenceObject();
          if(NULL_var != hLinkable)
          {
            P_PublicationGeometrique->Release();
            P_PublicationGeometrique = NULL;
            hLinkable->QueryInterface(IID_CATBaseUnknown,(void **)&P_PublicationGeometrique);
          }
        }	 
}
      
      if(P_PublicationGeometrique)
      {      
		  // the cavity is represented by the third geometry published in the list
		  // ----------------------------------------------------------------------
		  if(i==3) 
			  P_PublicationGeometrique->QueryInterface(IID_CATILinkableObject,(void**)&pRepresentation);
		  CATBaseUnknown_var hUnk_PubGeo(P_PublicationGeometrique);
		  P_PublicationGeometrique -> Release();
		  P_PublicationGeometrique =  NULL;
		  if(NULL_var!=hUnk_PubGeo) pListJointReferenceSecCav->Append(hUnk_PubGeo);      
      }
  }
  
  
  // creation of the second cavity on the single connector
  // -----------------------------------------------------
  // ID_NUMBER : this parameter define the string that define the second cavity
  // --------------------------------------------------------------------------
  Id_Number= "Second_Cavity";
  rc = pElecRefSecondSIC->AddCavity(Id_Number, Number, pGeoDefinition_SecondSIC,pRepresentation,pListJointReferenceSecCav,pElbCavity);
  
  if(SUCCEEDED(rc) && pElbCavity)
  {
      cout << "the second cavity was correctly created on the second single connector" << endl << flush;
  }
  else
  {
      cout<<"WARNING : a problem on the creation of the second cavity on the second single connector"<<endl<<flush;
      pGeoDefinition_SecondSIC -> Release();
      pGeoDefinition_SecondSIC = NULL;
      pRepresentationOfSecSIC -> Release();
      pRepresentationOfSecSIC = NULL;
      pPrdObjectPublisher->Release();
      pPrdObjectPublisher = NULL;
      if(P_PublicationGeometrique) P_PublicationGeometrique->Release();
      P_PublicationGeometrique = NULL;
      delete pListJointReferenceSecCav;
      pListJointReferenceSecCav = NULL;
      if(pElbCavity) pElbCavity->Release();
      pElbCavity = NULL;
      if(pRepresentation) pRepresentation->Release();
      pRepresentation = NULL;
      return 41;
  }
  delete pListJointReferenceSecCav;
  pListJointReferenceSecCav = NULL;
  if(pElbCavity) pElbCavity->Release();
  pElbCavity = NULL;
  if(pRepresentation) pRepresentation->Release();
  pRepresentation = NULL;

  
  // Creation of the Third cavity as like we create the first and the second cavity
  // -------------------------------------------------------------------------------
  
  CATListValCATBaseUnknown_var * pListJointReferenceThirdCav = new CATListValCATBaseUnknown_var();
  if(!pListJointReferenceThirdCav) 
  {     
      cout << "> PB ! : not possible to create a list of CATBaseUnkonwn ????? <  " << endl << flush;
      return 42;
  }
  
  for( i=5;i<=6;i++)
  {
      result = pPrdObjectPublisher->GetDirectObject (  (*pListOfPublications)[i],
		  P_PublicationGeometrique,
		  SubPublication);      
if(P_PublicationGeometrique)
{
        CATIConnector_var hConnector(P_PublicationGeometrique);
        if(NULL_var != hConnector)
        {
          CATILinkableObject_var hLinkable = hConnector->GiveReferenceObject();
          if(NULL_var != hLinkable)
          {
            P_PublicationGeometrique->Release();
            P_PublicationGeometrique = NULL;
            hLinkable->QueryInterface(IID_CATBaseUnknown,(void **)&P_PublicationGeometrique);
          }
        }
}
      if(P_PublicationGeometrique)
      {
		  if(i==5) 
			  P_PublicationGeometrique->QueryInterface(IID_CATILinkableObject,(void**)&pRepresentation);
		  CATBaseUnknown_var hUnk_PubGeo(P_PublicationGeometrique);
		  P_PublicationGeometrique -> Release();
		  P_PublicationGeometrique =  NULL;
		  if(NULL_var!=hUnk_PubGeo) pListJointReferenceThirdCav->Append(hUnk_PubGeo);      
      }
  }
  
  // creation of the third cavity
  // ----------------------------  
  Id_Number = "Third_Cavity";
  rc = pElecRefSecondSIC->AddCavity(Id_Number, Number, pGeoDefinition_SecondSIC,pRepresentation,pListJointReferenceThirdCav,pElbCavity);
  
  if(SUCCEEDED(rc) && pElbCavity)
  {
      cout << "the third cavity was correctly created on the second single connector" << endl << flush;
  }
  else
  {
      // trace
      cout<<"WARNING : a problem on the creation of the third cavity on the second single connector"<<endl<<flush;
	  
      // lifecycle object management
      pGeoDefinition_SecondSIC -> Release();
      pGeoDefinition_SecondSIC = NULL;
      pRepresentationOfSecSIC -> Release();
      pRepresentationOfSecSIC = NULL;
      pPrdObjectPublisher->Release();
      pPrdObjectPublisher = NULL;
      if(P_PublicationGeometrique) P_PublicationGeometrique->Release();
      P_PublicationGeometrique = NULL;
      delete pListJointReferenceThirdCav;
      pListJointReferenceThirdCav = NULL;
      if(pElbCavity) pElbCavity->Release();
      pElbCavity = NULL;
      if(pRepresentation) pRepresentation->Release();
      pRepresentation = NULL;	  
      return 43;
  }

  delete pListJointReferenceThirdCav;
  pListJointReferenceThirdCav = NULL;
  if(pElbCavity) pElbCavity->Release();
  pElbCavity = NULL;
  if(pRepresentation) pRepresentation->Release();
  pRepresentation = NULL;
  if(pElecRefSecondSIC) pElecRefSecondSIC-> Release();
  pElecRefSecondSIC = NULL;
  if (pPrdObjectPublisher) pPrdObjectPublisher->Release();
  pPrdObjectPublisher = NULL;
  
  
  delete pListOfPublications;
  pListOfPublications=NULL;
  
  pGeoDefinition_SecondSIC->Release();
  pGeoDefinition_SecondSIC = NULL;
  
  if (pRepresentationOfSecSIC) pRepresentationOfSecSIC->Release();
  pRepresentationOfSecSIC = NULL;
  

  
  // 5. Importing the part "MountingEquipment.CATPart" under the root product.
  // -------------------------------------------------------------------------

  // Adding a level under the root product
  // -------------------------------------
  CATIProduct * pProduct_MountingEqt = NULL;  
  rc = Import(hProduct_Level_1, PATH_MountingEqt,pProduct_MountingEqt);
  if(SUCCEEDED(rc) && pProduct_MountingEqt)
  {
    cout << "> import of the product mounting equipment succeeded " << endl << flush;
  }
  else
  {
    cout << "ERROR : import of the product mounting equipment failed " << endl << flush;
    return 44;
  }
  
  
  //  6. Defining the mounting equipment
  //  ----------------------------------

  //   6.1 Extend the mechanical product pProduct_MountingEqt in type ElecMountingEquipmentE
  //   -------------------------------------------------------------------------------------

  CATIProduct_var hProduct_MountingEqt_Ref = pProduct_MountingEqt->GetReferenceProduct();
  pProduct_MountingEqt->Release();
  pProduct_MountingEqt = NULL;
  hElbFactory = hProduct_MountingEqt_Ref;
  if (NULL_var == hElbFactory) return 45;
  rc = hElbFactory -> ExtendPrdAsMountingEquipment() ;
  if(SUCCEEDED(rc))
  {
    cout << "> extend the product pProduct_MountingEqt in type ElecMountingEquipmentE succeeded  " << endl << flush;
  }
  else
  {
    cout << "extend the product pProduct_MountingEqt in type ElecMountingEquipmentE failed " << endl << flush;
    return 46;
  }


  CATILinkableObject_var hLinkable_MountingEqt(hProduct_MountingEqt_Ref);
  if (NULL_var == hLinkable_MountingEqt) 
  {
	cout << "ERROR : hLinkable_MountingEqt handler is null " << endl << flush;
    return 47;
  }
  CATDocument * pDocOfPart_MountingEqt = hLinkable_MountingEqt->GetDocument();
  
  if(pDocOfPart_MountingEqt && (pDocOfPart_MountingEqt->IsAKindOf("CATPart")) ) 
  {
    cout << "> geometrical element : Reference hProduct_MountingEqt_Ref is defined in CATPart Document " << endl << flush;
  }
  else 
  {
    cout << "> WARNING geometrical element : Reference hProduct_MountingEqt_Ref is not defined in CATPart Document  " << endl << flush;
    return 48;
  }

  // Finding the Product where graphical representation of the mounting equipment is defined 
  // ----------------------------------------------------------------------------------------
  CATIProduct * pGeoDefinition_MountingEqt = NULL;
  rc = hProduct_MountingEqt_Ref->QueryInterface(IID_CATIProduct,(void**) & pGeoDefinition_MountingEqt);
  if(pGeoDefinition_MountingEqt)
  {
    cout << ">the product where the geometry of the mounting equipment is defined was found " << endl << flush;
  }
  else
  {
    cout << "ERROR : the product where the geometry of mounting equipment is defined wasn't found " << endl << flush;
    return 49;
  }

  // Finding the list of geometry that is published
  // ----------------------------------------------
  rc = hProduct_MountingEqt_Ref->QueryInterface(IID_CATIPrdObjectPublisher,(void**)&pPrdObjectPublisher);
  if(SUCCEEDED(rc) && pPrdObjectPublisher ) 
  {
    cout << "> the object publisher was found " << endl << flush;
  }
  else 
  {
    cout << "> WARNING  : the object publisher wasn't found  " << endl << flush;
    pGeoDefinition_MountingEqt->Release();
    pGeoDefinition_MountingEqt = NULL;
    if (pRepresentationOfSecSIC) pRepresentationOfSecSIC -> Release();
    pRepresentationOfSecSIC = NULL;
    return 50;
  }

  hasPublication = pPrdObjectPublisher->ListPublications(pListOfPublications);
  SizeListPub = pListOfPublications ? pListOfPublications->Size() : 0;
  if(3 == SizeListPub )
  {
	  cout << "> We found the list of publication of geometry  on the second single connector  " << endl << flush;
  }
  else
  {
	  return 51;
  }

  pListJointReference = new CATListValCATBaseUnknown_var();
  if(!pListJointReference) 
  {
      cout << "> PB ! : not possible to create a list of CATBaseUnkonwn ????? <  " << endl << flush;
      return 52;
  }

  
  P_PublicationGeometrique=NULL;
  
  result = 0;
  for( i=1;i<=2;i++)
  { 
	  
      // Retrieving the list of geometry  that represent the first cavity that we would like to create
      // ---------------------------------------------------------------------------------------------
      result = pPrdObjectPublisher->GetDirectObject (  (*pListOfPublications)[i],
		  P_PublicationGeometrique,
		  SubPublication);
 if(P_PublicationGeometrique)
{     
        CATIConnector_var hConnector(P_PublicationGeometrique);
        if(NULL_var != hConnector)
        {
          CATILinkableObject_var hLinkable = hConnector->GiveReferenceObject();
          if(NULL_var != hLinkable)
          {
            P_PublicationGeometrique->Release();
            P_PublicationGeometrique = NULL;
            hLinkable->QueryInterface(IID_CATBaseUnknown,(void **)&P_PublicationGeometrique);
          }
        }
}
	  
      if(P_PublicationGeometrique)
      {
		  // the cavity is represented by the first geometry published in the list
		  // ----------------------------------------------------------------------
		  if(i==1) 
			  P_PublicationGeometrique->QueryInterface(IID_CATILinkableObject,(void**)&pRepresentation);
		  CATBaseUnknown_var hUnk_PubGeo(P_PublicationGeometrique);
		  P_PublicationGeometrique -> Release();
		  P_PublicationGeometrique =  NULL;
		  
		  // we create the list of geometrical element that defined the cavity
		  // -----------------------------------------------------------------
		  if(NULL_var!=hUnk_PubGeo) pListJointReference->Append(hUnk_PubGeo);      
      }
  }

  delete pListOfPublications;
  pListOfPublications=NULL;


  // creation of a cavity on the mounting equipment
  // -----------------------------------------------------
  // ID_NUMBER : this parameter define the string that define the cavity
  // Number    : this parameter define the position of the cavity on the single connector.
  // ------------------------------------------------------------------------------------

  CATIElbMountingEquipmentReference * pElecRefMountingEqt = NULL;
  rc = hProduct_MountingEqt_Ref->QueryInterface(IID_CATIElbMountingEquipmentReference,(void**) &pElecRefMountingEqt);
  if(SUCCEEDED(rc) && pElecRefMountingEqt)
  {
      cout << ">the mounting equipment reference was found correctly" << endl << flush;
  }
  else
  {
      cout << " WARNING > the mounting equipment reference wasn't found correctly" << endl << flush;
      pGeoDefinition_MountingEqt -> Release();
      pGeoDefinition_MountingEqt = NULL;
      if (pRepresentationOfSecSIC) pRepresentationOfSecSIC -> Release();
      pRepresentationOfSecSIC = NULL;
      pPrdObjectPublisher->Release();
      pPrdObjectPublisher = NULL;
      if(P_PublicationGeometrique) P_PublicationGeometrique->Release();
      P_PublicationGeometrique = NULL;
      return 53;
  }

  // dump of the stack
  SizeListPub = pListJointReference?pListJointReference->Size() : 0;
  cout << " SizeListPub="<< SizeListPub << endl << flush;
  if(2 == SizeListPub )
  {
	  cout << "> We found the list of publication of geometry  on the second single connector  " << endl << flush;
  }
  else
  {
	  return 54;
  }

  Id_Number = "First_Cavity";
  JointType="Cavity";
  Number = 0;

  rc = pElecRefMountingEqt->AddCavity(Id_Number, Number, pGeoDefinition_MountingEqt,pRepresentation,JointType,pListJointReference,pElbCavity); 
  pElecRefMountingEqt->Release();
  pElecRefMountingEqt=NULL;
  delete pListJointReference;
  pListJointReference = NULL;

  if(SUCCEEDED(rc) && pElbCavity)
  {
      cout << "the cavity was correctly created on the mounting equipment" << endl << flush;
  }
  else
  {
      cout<<"WARNING : a problem on the creation of the cavity on the mounting equipment"<<endl<<flush;	  
      pGeoDefinition_MountingEqt->Release();
      pGeoDefinition_MountingEqt = NULL;
      pPrdObjectPublisher->Release();
      pPrdObjectPublisher = NULL;
      if(P_PublicationGeometrique) P_PublicationGeometrique->Release();
      P_PublicationGeometrique = NULL;
      if(pRepresentation) pRepresentation->Release();
      pRepresentation = NULL;	  
      return 55;
  }

  pGeoDefinition_MountingEqt->Release();
  pGeoDefinition_MountingEqt = NULL;

  if (pElbCavity) pElbCavity->Release();
  pElbCavity=NULL;

  if (pRepresentation) pRepresentation->Release();
  pRepresentation=NULL;



  // Import the third single connector 
  // ---------------------------------
  CATIProduct * pProduct_Third_SIC= NULL;  
  rc = Import(hProduct_Level_1, PATH_Third_SIC,pProduct_Third_SIC);
  if(SUCCEEDED(rc) && pProduct_Third_SIC)
  {
    cout << "> import of the product third single connector succeeded " << endl << flush;
  }
  else
  {
    cout << "ERROR : import of the product third single connector failed " << endl << flush;
    return 56;
  }

  // Retrieving the product vhere the geometry of the third single connector was defined
  // ------------------------------------------------------------------------------------
  CATIProduct_var hProductThirdSICRef = pProduct_Third_SIC->GetReferenceProduct();

  if(NULL_var!= hProductThirdSICRef)
  {
    cout << ">the reference product of the third single connector in context was found " << endl << flush;
  }
  else
  {
    cout << "ERROR : the reference product of the third single connector in context wasn't found " << endl << flush;    
    return 57;
  }


  //==============================================
  // creation of a connector connection point 
  //==============================================
  
  // Finding the list of geometry that is published
  // ----------------------------------------------
  
  rc = hProductThirdSICRef->QueryInterface(IID_CATIPrdObjectPublisher,(void**)&pPrdObjectPublisher);
  if(SUCCEEDED(rc) && pPrdObjectPublisher ) 
  {
    cout << "> the object publisher was found " << endl << flush;
  }
  else 
  {
    cout << "> WARNING  : the object publisher wasn't found  " << endl << flush;
    return 58;
  }

  hasPublication = pPrdObjectPublisher->ListPublications(pListOfPublications);
  SizeListPub = pListOfPublications ? pListOfPublications->Size() : 0;
  cout << "  SizeListPub of third SIC="<< SizeListPub << endl << flush;
  if (5 != SizeListPub)
  {
	  cout << "> ERROR : wrong number of publications  " << endl << flush;
	  return 59;
  }
  
  cout << "> We found the list of publication of geometry on the third single connector  " << endl << flush;

  CATListValCATBaseUnknown_var * pListJointReferenceThirdSIC = new CATListValCATBaseUnknown_var();
  if(!pListJointReferenceThirdSIC) 
  {      
      cout << "> PB ! : not possible to create a list of CATBaseUnkonwn ????? <  " << endl << flush;
      return 60;
  }
  
  for( i=4;i<=5;i++)
  {
	  cout << "> pub=" << (*pListOfPublications)[i].ConvertToChar() << endl << flush;
      result = pPrdObjectPublisher->GetDirectObject (  (*pListOfPublications)[i],
		  P_PublicationGeometrique,
		  SubPublication);      
      if(P_PublicationGeometrique)
      {
		  if(i==4) 
			  P_PublicationGeometrique->QueryInterface(IID_CATILinkableObject,(void**)&pRepresentation);
		  
		  P_PublicationGeometrique -> Release();
		  P_PublicationGeometrique =  NULL;     
      }
  }

  pPrdObjectPublisher->Release();
  pPrdObjectPublisher = NULL;

  if (!pRepresentation)
	  { cout << "> ERROR :  pRepresentation is NULL" << endl << flush ;return 61;}

  // dump of the stack
  SizeListPub = pListJointReferenceThirdSIC?pListJointReferenceThirdSIC->Size() : 0;
  cout << " Size of pListJointReferenceThirdSIC="<< SizeListPub << endl << flush;

  delete pListOfPublications;
  pListOfPublications=NULL;


  // creation of a connector connection point on the third single connector
  // ----------------------------------------------------------------------
  // ID_NUMBER : this parameter define the string that define the connector connection point
  // ---------------------------------------------------------------------------------------

  CATIElbSingleConnector * pElbThirdSIC = NULL;
  rc = pProduct_Third_SIC->QueryInterface(IID_CATIElbSingleConnector,(void**) & pElbThirdSIC);

  if(!pElbThirdSIC)
  {
    cout << "ERROR : QI CATIElbSingleConnector on pProduct_Third_SIC is KO " << endl << flush;
    return 62;
  }

  Id_Number = "First_ConnectorCnctPt";
  JointType="ConnectorCnctPt";
  CATIElbConnectorCnctPt * pElbConnectorCnctPt = NULL;
  rc = pElbThirdSIC->AddConnectorCnctPt(Id_Number, pProduct_Third_SIC,pRepresentation,JointType,pListJointReferenceThirdSIC,pElbConnectorCnctPt);    
  if(SUCCEEDED(rc) && pElbConnectorCnctPt)
  {
      cout << "the connector connection point was correctly created on the third single connector" << endl << flush;
  }
  else
  {
      cout<<"WARNING : a problem occured during the creation of the connector connection point on the third single connector"<<endl<<flush;
      return 63;
  }	

  pElbConnectorCnctPt->Release();
  pElbConnectorCnctPt=NULL;

  delete pListJointReferenceThirdSIC;
  pListJointReferenceThirdSIC=NULL;

  pElbThirdSIC->Release();
  pElbThirdSIC=NULL;

  pRepresentation->Release();
  pRepresentation=NULL; 

  pProduct_Third_SIC -> Release();
  pProduct_Third_SIC = NULL;


  // finding the document were the part of the second single connector was found
  // ---------------------------------------------------------------------------

  // finding the geometry of the third single connector
  // ---------------------------------------------------
  CATILinkableObject * pRepresentationOfThirdSIC = NULL;
  rc = hProductThirdSICRef->QueryInterface(IID_CATILinkableObject,(void**) & pRepresentationOfThirdSIC);
  if(pRepresentationOfThirdSIC)
  {
    cout << ">the geometrical representation of the third single connector was found " << endl << flush;
  }
  else
  {
    cout << "ERROR : the geometrical representation of the third single connector  wasn't found " << endl << flush;
    return 64;
  }

  // finding the document 
  // --------------------
  CATDocument * pDocOfPart_ThirdSIC = pRepresentationOfThirdSIC->GetDocument();
  if(pDocOfPart_ThirdSIC && (pDocOfPart_ThirdSIC->IsAKindOf("CATPart")) ) 
  {
    cout << "> the document CATPart where the third single connector is defined was found " << endl << flush;
  }
  else 
  {
    cout << "> WARNING  : the document CATPart where the third single connector is defined wasn't found  " << endl << flush;
    return 65;
  }


  pRepresentationOfThirdSIC->Release();
  pRepresentationOfThirdSIC=NULL;


    
    
  //--------------------------------------------------------------------
  // 8. Epilogue  
  //--------------------------------------------------------------------
 
  // save the model.
  // --------------
  CATBoolean iSavePointedIfNecessary = TRUE;
  CATILinkableObject_var hLinkable_BackShell (hProduct_BackShell_Ref);
  if (NULL_var == hLinkable_BackShell) 
  {
	cout << "ERROR : hLinkable_BackShell handler is null " << endl << flush;
    return 66;
  }
  CATDocument * pDocOfPart_BackShell = hLinkable_BackShell->GetDocument();
  rc = CATDocumentServices::SaveAs ( *pDocOfPart_BackShell,argv[6],"CATPart",iSavePointedIfNecessary );
  rc = CATDocumentServices::SaveAs ( *pDocOfPart_SIC,argv[7],"CATPart",iSavePointedIfNecessary );
  rc = CATDocumentServices::SaveAs ( *pDocOfPart_SecondSIC,argv[8],"CATPart",iSavePointedIfNecessary );
  rc = CATDocumentServices::SaveAs ( *pDocOfPart_ThirdSIC,argv[9],"CATPart",iSavePointedIfNecessary );
  rc = CATDocumentServices::SaveAs ( *pDocOfPart_MountingEqt,argv[10],"CATPart",iSavePointedIfNecessary );
  rc = CATDocumentServices::SaveAs ( *pDoc_Level_1,argv[11],"CATProduct",iSavePointedIfNecessary );
  rc = CATDocumentServices::SaveAs ( *pMainPrdDoc,argv[12],"CATProduct",iSavePointedIfNecessary );
  
  // --- removing document from session 
  rc  =  CATDocumentServices::Remove(*pDocOfPart_BackShell);
  rc  =  CATDocumentServices::Remove(*pDocOfPart_SIC);
  rc  =  CATDocumentServices::Remove(*pDocOfPart_SecondSIC);
  rc  =  CATDocumentServices::Remove(*pDocOfPart_ThirdSIC);
  rc  =  CATDocumentServices::Remove(*pDocOfPart_MountingEqt);
  rc  =  CATDocumentServices::Remove(*pDoc_Level_1);
  rc  =  CATDocumentServices::Remove(*pMainPrdDoc);
  if (SUCCEEDED(rc))
  {
    cout << "> document removed " << endl << flush;
  }
  else
  {
    cout << "ERROR in removing document" << endl << flush;
    return 67;
  }
  // --- closing the session
  rc = ::Delete_Session(sessionName);
  if (SUCCEEDED(rc))
    cout << "> session deleted " << endl << flush;
  else
  {
    cout << "ERROR in deleting session" << endl << flush;
    return 68;
  }
  cout << "----------------------------------------------------------------" << endl << flush;
  cout << endl << flush;
  cout << endl << flush;
  
  //
  return (0);
}
