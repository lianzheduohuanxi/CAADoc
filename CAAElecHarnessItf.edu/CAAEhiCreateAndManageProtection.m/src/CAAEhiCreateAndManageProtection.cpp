// COPYRIGHT DASSAULT SYSTEMES 2003

//===============================================================================
//  Abstract of Use Case "CAAEhiCreateAndManageProtection":
//  --------------------------------------------------------
//
//  This Use Case illustrates how to create and manage protections
//
//===============================================================================
//
//  Step by Step :
//  ------------
//
//  1. Prologue :  
//      . Opening the Session and Opening an Existing CATProduct Document
//      . Retrieving the Root Product of the CATProduct Document
//      . Opening the document containing the protection (CATPart)
//      . Retrieving the Root Product of the protection document 
//  2. Initializing Electrical Environment. 
//  3. Retrieving the electrical geometrical bundle 
//  4. Retrieving the bundle segment to protect
//  5. Adding the protection on a bundle segment 
//  6. Managing the created protection
//      . modifying the protection extremities
//      . get the protection extremities
//  7. Epilogue.
//      7.1 saving documents
//      7.2 closing session
//
//  Return Errors:
//  -------------
// 
//  1 - ERROR in creating the session
//  2 - ERROR in opening the main document
//  3 - ERROR in retrieving root product of main document.
//  4 - ERROR in opening the protection document
//  5 - ERROR in retrieving root product of protection document.
//  6 - ERROR in initializing electrical environment. 
//  7 - ERROR in retrieving the products under the root product
//  8 - ERROR in retrieving the geometrical bundle
//  9 - ERROR in retrieving the bundle segments
// 10 - ERROR in creating the list of bundle segments to protect
// 11 - ERROR in adding the protection on the bundle segment
// 12 - ERROR in managing the created protection
// 13 - ERROR in saving the protection document
// 14 - ERROR in saving the geometrical bundle document
// 15 - ERROR in saving the document under the main document
// 16 - ERROR in saving the main document
// 17 - ERROR in removing documents
// 18 - ERROR in closing session  
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  mkrun -c "CAAEhiCreateAndManageProtection InDir OutDir MainName ProtName" where :
//      . "InDir" is the pathname of the file where the input documents are read
//      . "OutDir" is the pathname of the file where the output documents are saved
//        "MainName" is the name of the main document
//      . "ProtName" is the name of the protection document    
// 
//
//  You may reference the supplied CATProduct document called "FlatteningAssembly.CATProduct" 
//  found in the 'WS'/'OS'/resources/graphic/CAA_EHIMultiBranchableSample directory if under Unix.
//      In this case, 'OS' can be any of the following: 
//         aix_a for IBM
//         hpux_a for HP
//         irix_a for SGI
//         solaris_a for SUN
//  Under Windows, the path would indicate:'WS'\intel_a\resources\graphic\CAA_EHIMultiBranchableSample
//  directory.            
//
//=======================================================================================

// C++ include ( result display )
// LRO 08:01:15
#include "CATBaseUnknown.h"
#include "CATILinkableObject.h"
#include "CATISpecObject.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATSession.h"
#include "CATUnicodeString.h"

#include <iostream.h>

// System interfaces
#include "CATLib.h"                      // managing files
// ObjectModelerBase interfaces
#include "CATSessionServices.h"          // managing session
#include "CATDocumentServices.h"         // managing documents in session
#include "CATDocument.h"                 // manipulating documents
#include "CATIDocRoots.h"                // browsing root objects in documents


// ProductStructure interfaces 
#include "CATIProduct.h"                 // managing products  


// Electrical Harness interfaces
#include "CATIEhiGeoBundle.h"            // managing geometrical bundles
#include "CATIEhiProtection.h"           // managing protections of bundle segments


// Electrical interfaces
#include "CATIEleDocServices.h"          // initializing electrical environment 
 


//=========================================================================================================
// Main - sample 
// 
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
  //1.1--- Creating the Session 
  
  CATSession *pSession = NULL;
  
  char *sessionName = "CAA_EhiCreateAndManageProtection_Session";
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

  //
  // 1.2--- Opening the main document 
  //       The input parameter of this sample program must contain 
  //       the entire path and name of the document that is to be opened.    
  
  CATUnicodeString PathInput ( argv[1] ); // input path 
  CATUnicodeString PathOutput ( argv[2] ); // output path 

  // --- initialize part numbers and file names
  CATUnicodeString MainPartNum  ( argv[3] ); // Part number of main product
  CATUnicodeString ProtPartNum ( argv[4] ); // Part number of protection

  CATUnicodeString  doc_part = ".CATPart";
  CATUnicodeString  doc_product = ".CATProduct";

  CATUnicodeString  MainFile = MainPartNum + doc_product;
  CATUnicodeString  ProtFile = ProtPartNum + doc_part;

  
  CATDocument *pMainDoc = NULL; // pMainDoc is a pointer to the document 
  
  rc = CATDocumentServices::OpenDocument(PathInput+MainFile, pMainDoc);
  if (SUCCEEDED(rc) && (NULL != pMainDoc))
  {
    cout << "> main document opened " << endl << flush;
  }
  else
  {
    cout << "ERROR in opening main document" << endl << flush;
    return 2;
  }
  
  
  // 1.3--- Retrieving root product of the main document 
  
  CATIProduct* piRootProduct = NULL;// piRootProduct is a handle to document root product
  
  CATIDocRoots * pDocRoots = NULL;
  rc = pMainDoc->QueryInterface(IID_CATIDocRoots,(void**) &pDocRoots);
  if ( FAILED(rc) || (NULL==pDocRoots) ) return 3;
  CATListValCATBaseUnknown_var* pListRootProduct = pDocRoots->GiveDocRoots();
  pDocRoots->Release();
  pDocRoots=NULL;
  
  CATBaseUnknown_var spCBU ((*pListRootProduct)[1]);
  if ( pListRootProduct && pListRootProduct->Size() && spCBU)
  {  
	  rc = spCBU->QueryInterface(IID_CATIProduct,(void**) &piRootProduct );
	  
	  //
	  if  (SUCCEEDED(rc) && (NULL != piRootProduct))
		  cout << "> root product found in document " << endl << flush;
	  else
	  {
		  cout << "ERROR : Root product not found in document " << endl << flush;
		  return 3;
	  }
  }

  delete pListRootProduct;
  pListRootProduct = NULL;



  // 1.4--- Opening the protection document 
  //       The input parameter to this sample program must contain 
  //       the entire path and name of the document that is to be opened.  
  
  CATDocument *pProtDoc = NULL; // pProtDoc is a pointer to the document 
  
  rc = CATDocumentServices::OpenDocument(PathInput+ProtFile, pProtDoc);
  if (SUCCEEDED(rc) && (NULL != pProtDoc))
  {
    cout << "> protection document opened " << endl << flush;
  }
  else
  {
    cout << "ERROR in opening protection document" << endl << flush;
    return 4;
  }

  // 1.5--- Retrieving root product of the protection document 
  
  CATIProduct* piProtRootProduct = NULL;// piProtRootProduct is a handle to document root product
  
  rc = pProtDoc->QueryInterface(IID_CATIDocRoots,(void**) &pDocRoots);
  if ( FAILED(rc) || (NULL==pDocRoots) ) return 5;
  pListRootProduct = pDocRoots->GiveDocRoots();
  pDocRoots->Release();
  pDocRoots=NULL;
  
  spCBU = (*pListRootProduct)[1];
  if ( pListRootProduct && pListRootProduct->Size() && spCBU)
  {  
	  rc = spCBU->QueryInterface(IID_CATIProduct,(void**) &piProtRootProduct );
	  
	  //
	  if  (SUCCEEDED(rc) && (NULL != piProtRootProduct))
		  cout << "> root product found in document " << endl << flush;
	  else
	  {
		  cout << "ERROR : Root product not found in document " << endl << flush;
		  return 5;
	  }
  }

  delete pListRootProduct;
  pListRootProduct = NULL;

  if  (NULL == piProtRootProduct) return 5;

  
  //--------------------------------------------------------------------
  // 2. Initializing Electrical Environment 
  //--------------------------------------------------------------------
  
  CATIEleDocServices * piElecDocServices = NULL;
  
  rc = pMainDoc->QueryInterface(IID_CATIEleDocServices,(void**) &piElecDocServices );
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


  //--------------------------------------------------------------------
  // 3. Retrieving the geometrical bundle
  //    
  //--------------------------------------------------------------------

  // 1) Retrieving all products under the root product 

  CATListValCATBaseUnknown_var* pListProduct = NULL;
  pListProduct = piRootProduct->GetAllChildren(CATIProduct::ClassName());

  int NumberOfProduct = pListProduct?pListProduct->Size():0;

  if ( 0 == NumberOfProduct) 
  {	
	  cout << "ERROR : no product found under the root product " << endl << flush;
	  return 7;
  }
  
  
  // < display instance names >
  CATIProduct* piInstanceProduct = NULL;
  CATUnicodeString InstanceName = "unknown";
  
  cout << "> number of products under the root : "<< NumberOfProduct << endl << flush;
  int i = 1;
  for ( ; i<=NumberOfProduct; i++ )
  {
    CATBaseUnknown_var spCBU ((*pListProduct)[i]);
	  if (NULL_var != spCBU)
	  {
		  rc = spCBU->QueryInterface(IID_CATIProduct,(void**) &piInstanceProduct);
		  if (SUCCEEDED(rc) && ( NULL != piInstanceProduct )) 
          {		  			  
			  piInstanceProduct->GetPrdInstanceName(InstanceName);	
			  cout << "     "<<i<<" instance name :  "<<InstanceName.ConvertToChar()<<endl<< flush;			  
		  }
		  if ( NULL != piInstanceProduct ) piInstanceProduct->Release();		
		  piInstanceProduct = NULL;
		  InstanceName = "unknown";
	  }
  }



  //
  // 2) Retrieving all geometrical bundles under the root product 
  //    and selecting one geometrical bundle  
  
  // 2.1) Retrieving all geometric bundles under root product  

  CATListValCATBaseUnknown_var* pListGeoBundle=new CATLISTV(CATBaseUnknown_var);
  if (NULL == pListGeoBundle) return 8;


  CATIEhiGeoBundle* pEhiGbn=NULL;
  
  for ( i =1; i<=NumberOfProduct; i++ )
  { 	  
    CATBaseUnknown_var spCBU ((*pListProduct)[i]);
	  if (NULL_var != spCBU)
	  {
		  spCBU->QueryInterface(IID_CATIEhiGeoBundle,(void**) &pEhiGbn);
		  if ( NULL != pEhiGbn) 
		  {
            CATBaseUnknown_var hUnk=pEhiGbn;
			pListGeoBundle->Append(hUnk);
		  }
		  if ( NULL != pEhiGbn ) pEhiGbn->Release();		
		  pEhiGbn = NULL;

	  }
	  
  }

  delete pListProduct;
  pListProduct=NULL;

  int NumberOfGeoBundle = pListGeoBundle?pListGeoBundle->Size():0;
  cout << "> number of geometrical bundle found in assembly : "<< NumberOfGeoBundle << endl << flush;

  if (1 != NumberOfGeoBundle)
  {
	  cout << "ERROR : invalid number of geometrical bundle found in assembly " << endl << flush;
	  return 8;
  }
	
  // 2.2) Selecting one geometrical bundle 
  
  CATIEhiGeoBundle * piGeoBundle = NULL;
  spCBU = (*pListGeoBundle)[1];
  if (NULL_var != spCBU)
    rc = spCBU->QueryInterface(IID_CATIEhiGeoBundle,(void**) &piGeoBundle);
  
  delete pListGeoBundle;
  pListGeoBundle=NULL;
     
  if ( SUCCEEDED(rc) && NULL!= piGeoBundle)
  { 
    cout << "> select geometrical bundle to analyse " <<endl << flush;
    cout << "   rank in list   :  "<< NumberOfGeoBundle << endl << flush;
    CATIProduct_var  spGeoBundleProduct = piGeoBundle ;
    CATUnicodeString InstanceName ;
    if ( NULL_var != spGeoBundleProduct ) spGeoBundleProduct->GetPrdInstanceName(InstanceName);		
    cout << "   instance name  :  "<< InstanceName .ConvertToChar() << endl << flush;
  }
  else
  {
    cout << "ERROR : getting to geometrical bundle segment failed " << endl << flush;
    return 8;
  }



  //--------------------------------------------------------------------
  // 4. Retrieving the bundle segment to protect 
  //--------------------------------------------------------------------

  
  // --- Retrieving all bundle segments under the geometrical bundle

  CATListValCATBaseUnknown_var* pListBundleSegments=new CATLISTV(CATBaseUnknown_var);
  if (NULL == pListBundleSegments) return 9;

  rc = piGeoBundle->ListBundleSegments(&pListBundleSegments);

  int NumberOfBundleSegments = pListBundleSegments?pListBundleSegments->Size():0;
  cout << "> number of bundle segments found in assembly : "<< NumberOfBundleSegments<< endl << flush;
  if (9 != NumberOfBundleSegments) return 9;  // LVP - Added a new branch with a segment, so changed no. 8 by 9 


  
  //--------------------------------------------------------------------
  // 5. Instanciate the protection on the bundle segment  
  //--------------------------------------------------------------------

  CATListValCATBaseUnknown_var* pListBnsToProtect = new CATLISTV(CATBaseUnknown_var);

  if ( NULL == pListBnsToProtect ) 
  {
    cout << "ERROR : creation of list of bns to protect has failed " << endl << flush;
    return 10;
  }

  // we fill the stack
  pListBnsToProtect->Append((*pListBundleSegments)[7]);

  delete pListBundleSegments;
  pListBundleSegments=NULL;


  CATIEhiProtection * piProtection = NULL;
  double L1 = 0.1;
  double L2 = 0.8;
  rc = piGeoBundle->InstanciateProtection(piProtRootProduct,pListBnsToProtect,L1,L2,piProtection);

  delete pListBnsToProtect;
  pListBnsToProtect=NULL;

  if (FAILED(rc) || (NULL == piProtection)) return 11;



  //--------------------------------------------------------------------
  // 6. Managing the protection of the bundle segment  
  //--------------------------------------------------------------------

  // --- Modifying the protection of the bundle segment 

  L1 = 0.1;
  L2 = 0.1;
  rc = piProtection->SetProtectionExtremities(L1,L2);

  if (FAILED(rc)) return 12;


  // --- Retrieving the extremities of the protection 
  
  CATISpecObject* pProtExt1=NULL;
  CATISpecObject* pProtExt2=NULL;
  rc = piProtection->GetProtectionExtremities(pProtExt1,pProtExt2);
  if (FAILED(rc)) return 12;
  if (pProtExt1) pProtExt1->Release();
  pProtExt1=NULL;
  if (pProtExt2) pProtExt2->Release();
  pProtExt1=NULL;


  //--------------------------------------------------------------------
  // 7. Epilogue  
  //--------------------------------------------------------------------

  
  // 7.1-- Saving the documents


  // --- saving protection document

  rc = CATDocumentServices::SaveAs (*pProtDoc , PathOutput+ProtFile);
  if (SUCCEEDED(rc))
  {
    cout << "> protection document saved " << endl << flush;
  }
  else
  {
    cout << "ERROR in saving document" << endl << flush;
    return 13;
  }
 
  // --- saving geometrical bundle document

  CATIProduct_var hProdGbn=piGeoBundle ;
  CATAssert(!!hProdGbn);
  CATIProduct_var hProdGbnRef = hProdGbn->GetReferenceProduct();
  CATAssert(!!hProdGbnRef);
  
  CATILinkableObject_var hLinkable=hProdGbnRef;
  CATAssert(!!hLinkable);
  
  CATDocument * pGbnDoc = hLinkable->GetDocument();

  if ( !pGbnDoc )
  {
    cout << "ERROR in retrieving gbn document" << endl << flush;
    return 14;
  }

  CATUnicodeString GbnFile = "GeometricalBundle11"+doc_product; 
  rc = CATDocumentServices::SaveAs (*pGbnDoc , PathOutput+GbnFile);
  if (SUCCEEDED(rc))
  {
    cout << "> protection document saved " << endl << flush;
  }
  else
  {
    cout << "ERROR in saving document" << endl << flush;
    return 14;
  }


  // --- saving the first document under the root product

  CATListValCATBaseUnknown_var* pListSubProduct = NULL;
  pListSubProduct = piRootProduct->GetChildren(CATIProduct::ClassName());

  int nbprod = pListSubProduct?pListSubProduct->Size():0;
  cout << "> nbprod= "<< nbprod << endl << flush;

  if ( 1 != nbprod) 
  {	
	  cout << "ERROR : no product found under the root product " << endl << flush;
	  return 15;
  }

  CATIProduct_var hProd = (*pListSubProduct)[1];
  CATAssert(!!hProd);
  CATIProduct_var hProdRef = hProd->GetReferenceProduct();
  CATAssert(!!hProdRef);
  
  hLinkable=hProdRef;
  CATAssert(!!hLinkable);
  
  CATDocument * pSubProdDoc = hLinkable->GetDocument();  
  
  if ( !pSubProdDoc )
  {
    cout << "ERROR in retrieving bundle segment 1 CATPart document" << endl << flush;
    return 15;
  }

  delete pListSubProduct;
  pListSubProduct=NULL;

  CATUnicodeString SubProdFile = "3D-Install-Harness1"+doc_product; 

  rc = CATDocumentServices::SaveAs (*pSubProdDoc , PathOutput+SubProdFile );
  if (SUCCEEDED(rc))
  {
    cout << "> bundle segment 1 CATPart document saved " << endl << flush;
  }
  else
  {
    cout << "ERROR in saving bundle segment 1 CATPart document" << endl << flush;
    return 15;
  }


  // --- saving main document

  CATUnicodeString oFileRoot(argv[3]);
  rc = CATDocumentServices::SaveAs (*pMainDoc , PathOutput+MainFile );

  if (SUCCEEDED(rc))
  {
    cout << "> main document saved " << endl << flush;
  }
  else
  {
    cout << "ERROR in saving document" << endl << flush;
    return 16;
  }
  

  // 7.2-- releasing pointers to interface
  //
  piRootProduct->Release(); 
  piProtRootProduct->Release(); 
  piProtection->Release();
  piGeoBundle->Release();
  
  // --- always reset pointer value to NULL after release
  piRootProduct=NULL; 
  piProtRootProduct=NULL; 
  piProtection=NULL; 
  piGeoBundle=NULL;
 

  //
  // 7.3-- removing document from session 
  rc = CATDocumentServices::Remove(*pMainDoc);
  if (SUCCEEDED(rc))
  {
    cout << "> document removed " << endl << flush;
  }
  else
  {
    cout << "ERROR in removing document" << endl << flush;
    return 17;
  }

  // 7.4-- closing the session
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





