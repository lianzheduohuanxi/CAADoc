// COPYRIGHT DASSAULT SYSTEMES 2003

//===============================================================================
//  Abstract of Use Case "CAAEhiCreateAndManageSupport":
//  --------------------------------------------------------
//
//  This Use Case illustrates how to create and manage supports
//
//===============================================================================
//
//  Step by Step :
//  ------------
//
//  1. Prologue :  
//      . Opening the Session and Opening an Existing CATProduct Document
//      . Retrieving the Root Product of the CATProduct Document
//  2. Initializing Electrical Environment. 
//  3. Retrieving the electrical geometrical bundle 
//  4. Retrieving the bundle segment to link with the support
//  5. Retrieving the support to link with the bundle segment
//  6. Adding the support on the bundle segment 
//  7. Updating the bundle segment
//  8. Epilogue.
//      8.1 saving documents
//      8.2 closing session
//
//  Return Errors:
//  -------------
//  
//  1 - ERROR in creating the session
//  2 - ERROR in opening the main document
//  3 - ERROR in retrieving root product of main document.
//  4 - ERROR in initializing electrical environment. 
//  5 - ERROR in retrieving the products under the root product
//  6 - ERROR in retrieving the first document under the root product
//  7 - ERROR in retrieving the geometrical bundle
//  8 - ERROR in retrieving the document of the geometrical bundle
//  9 - ERROR in retrieving the multi branchable bundle segments
// 10 - ERROR in retrieving the bundle segments of the multi branchable
// 11 - ERROR in retrieving the support 
// 12 - ERROR in adding the support on the bundle segment
// 13 - ERROR in updating the multi branchable
// 14 - ERROR in saving the first multi branchable
// 15 - ERROR in saving the second multi branchable
// 16 - ERROR in saving the third multi branchable
// 17 - ERROR in saving the fourth multi branchable
// 18 - ERROR in saving the geometrical bundle document
// 19 - ERROR in saving the document under the main document
// 20 - ERROR in saving the main document
// 21 - ERROR in removing documents
// 22 - ERROR in closing session  
// 26 - ERROR - Retainer not found  // LVP :- Added return error for retainer
// 27 - ERROR in InsertSupport for retainer  // LVP :- Added return error for retainer
// 28 - ERROR in GetLinkedSupportSection  for retainer  // LVP :- Added return error for retainer
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  mkrun -c "CAAEhiCreateAndManageSupport InDir OutDir MainName" where :
//      . "InDir" is the pathname of the file where the input documents are read
//      . "OutDir" is the pathname of the file where the output documents are saved
//        "MainName" is the name of the main document
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
//
//===================================================================================================

// C++ include ( result display )
// LRO 08:01:15
#include "CATBaseUnknown.h"
#include "CATILinkableObject.h"
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
#include "CATIEhiBundleSegment.h"        // managing bundle segments
#include "CATIEhiMultiBranchable.h"      // managing multi branchable bundle segments
#include "CATIEhiBranchable.h"           // managing branchable bundle segments
#include "CATIEhiGeoBundle.h"            // managing geometrical bundles
#include "CATEhiBundleSegmentDef.h"      // managing options for support insertion


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
  
  char *sessionName = "CAA_EhiCreateAndManageSupport_Session";
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
  CATUnicodeString MainPartNum  ( argv[3] ); // Part number of Geometrical Bundle

  //
  CATUnicodeString  doc_part = ".CATPart";
  CATUnicodeString  doc_product = ".CATProduct";
  CATUnicodeString MainFile  = MainPartNum  + doc_product;  // Main file
  CATUnicodeString SubProdFile = "3D-Install-Harness1"+doc_product; 
  CATUnicodeString GbnFile = "GeometricalBundle11"+doc_product; 
  CATUnicodeString MultiBns1File = "BranchableBundleSegment11" + doc_part; 
  CATUnicodeString MultiBns2File = "BranchableBundleSegment21" + doc_part; 
  CATUnicodeString MultiBns3File = "BranchableBundleSegment31" + doc_part; 
  CATUnicodeString MultiBns4File = "BranchableBundleSegment41" + doc_part;

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
  
  if ( pListRootProduct && pListRootProduct->Size() )
  {  
	  CATBaseUnknown_var spRootProduct = (*pListRootProduct)[1];
	  if (NULL_var != spRootProduct)
	  {
		  rc = spRootProduct->QueryInterface(IID_CATIProduct,(void**) &piRootProduct );
		  
		  if  (SUCCEEDED(rc) && (NULL != piRootProduct))
			  cout << "> root product found in document " << endl << flush;
		  else
		  {
			  cout << "ERROR : Root product not found in document " << endl << flush;
			  return 3;
		  }
	  }
  }
  
  delete pListRootProduct;
  pListRootProduct = NULL;

  
  
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
    return 4;
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
	  return 5;
  }
  
  
  // < display instance names >
  CATIProduct* piInstanceProduct = NULL;
  CATUnicodeString InstanceName = "unknown";
  
  cout << "> number of products under the root : "<< NumberOfProduct << endl << flush;
  int i = 1;
  for ( ; i<=NumberOfProduct; i++ )
  {
	  CATBaseUnknown_var spProduct = (*pListProduct)[i];
	  if (NULL_var != spProduct)
	  {
		  rc = spProduct->QueryInterface(IID_CATIProduct,(void**) &piInstanceProduct);
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



  // 2) retrieving the first document under the root product 
  //    (necessary for saving the documents at the end)
  CATListValCATBaseUnknown_var* pListSubProduct = NULL;
  pListSubProduct = piRootProduct->GetChildren(CATIProduct::ClassName());

  int nbprod = pListSubProduct?pListSubProduct->Size():0;
  cout << "> nbprod= "<< nbprod << endl << flush;

  if ( 1 != nbprod) 
  {	
	  cout << "ERROR : no product found under the root product " << endl << flush;
	  return 6;
  }

  CATIProduct_var hProd = (*pListSubProduct)[1];
  CATAssert(!!hProd);
  CATIProduct_var hProdRef = hProd->GetReferenceProduct();
  CATAssert(!!hProdRef);
  
  CATILinkableObject_var hLinkable=hProdRef;
  CATAssert(!!hLinkable);
  
  CATDocument * pSubProdDoc = hLinkable->GetDocument();  
  
  if ( !pSubProdDoc )
  {
    cout << "ERROR in retrieving bundle segment 1 CATPart document" << endl << flush;
    return 6;
  }
  delete pListSubProduct;
  pListSubProduct=NULL;


  // 3) retrieving the geometrical bundle

  CATListValCATBaseUnknown_var* pListGeoBundle=new CATLISTV(CATBaseUnknown_var);
  if (NULL == pListGeoBundle) return 7;

  CATIEhiGeoBundle* piEhiGbn=NULL;
  
  for ( i =1; i<=NumberOfProduct; i++ )
  { 
	  CATBaseUnknown_var spProduct = (*pListProduct)[i];
	  if (NULL_var != spProduct)
	  {
		  spProduct->QueryInterface(IID_CATIEhiGeoBundle,(void**) &piEhiGbn);
		  if ( NULL != piEhiGbn) 
		  {
            CATBaseUnknown_var hUnk=piEhiGbn;
		    piEhiGbn->Release();		
		    piEhiGbn = NULL;
			if (NULL_var != hUnk) pListGeoBundle->Append(hUnk);
		  }

	  }
	  
  }

  int NumberOfGeoBundle = pListGeoBundle?pListGeoBundle->Size():0;
  cout << "> number of geometrical bundle found in assembly : "<< NumberOfGeoBundle << endl << flush;

  if (1 != NumberOfGeoBundle)
  {
	  cout << "ERROR : invalid number of geometrical bundle found in assembly " << endl << flush;
	  return 7;
  }

  CATIProduct_var hProdGbn= (*pListGeoBundle)[1];
  CATAssert(!!hProdGbn);
  CATIProduct_var hProdGbnRef = hProdGbn->GetReferenceProduct();
  CATAssert(!!hProdGbnRef);
  
  hLinkable=hProdGbnRef;
  CATAssert(!!hLinkable);
  
  CATDocument * pGbnDoc = hLinkable->GetDocument();

  if ( !pGbnDoc )
  {
    cout << "ERROR in retrieving gbn document" << endl << flush;
    return 8;
  }

  // we keep the geometrical bundle
  CATBaseUnknown_var spGeoBundle = (*pListGeoBundle)[1];
  if (NULL_var != spGeoBundle)
  {
	  spGeoBundle->QueryInterface(IID_CATIEhiGeoBundle,(void**) &piEhiGbn);
  }

  if (NULL == piEhiGbn) return 7;


  delete pListGeoBundle;
  pListGeoBundle=NULL;




  //--------------------------------------------------------------------
  // 4. Retrieving the bundle segment to link with the support
  //--------------------------------------------------------------------

  // --- Retrieving all multi branchables under root product  

  CATListValCATBaseUnknown_var* pListMultiBns = new CATLISTV(CATBaseUnknown_var);
  if (NULL == pListMultiBns) return 9;

  CATIEhiMultiBranchable* pMultiBns=NULL;
  
  for ( i =1; i<=NumberOfProduct; i++ )
  { 
	  CATBaseUnknown_var spProduct = (*pListProduct)[i];
	  if (NULL_var != spProduct)
	  {
		  spProduct->QueryInterface(IID_CATIEhiMultiBranchable,(void**) &pMultiBns);
		  if ( NULL != pMultiBns) 
		  {
            CATBaseUnknown_var hUnk=pMultiBns;
			pListMultiBns->Append(hUnk);
		  }
		  if ( NULL != pMultiBns ) pMultiBns->Release();		
		  pMultiBns = NULL;

	  }
	  
  }

  int NumberOfMultiBns = pListMultiBns?pListMultiBns->Size():0;
  cout << "> number of multi branchable found in assembly : "<< NumberOfMultiBns << endl << flush;

  if (5 != NumberOfMultiBns)
  {
	  cout << "ERROR : bad number of multi branchable found in assembly " << endl << flush;
	  return 9;
  }

  // < display instance names >
  for ( i =1; i<=NumberOfMultiBns; i++ )
  {
	  CATBaseUnknown_var spMultiBNS = (*pListMultiBns)[i];
	  if (NULL_var != spMultiBNS)
	  {
		  rc = spMultiBNS->QueryInterface(IID_CATIProduct,(void**) &piInstanceProduct);
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

  CATIEhiMultiBranchable * piMultiBranchable1 = NULL;  // the multi branchable choosen 
  CATIEhiMultiBranchable * piMultiBranchable2 = NULL; 
  CATIEhiMultiBranchable * piMultiBranchable3 = NULL; 
  CATIEhiMultiBranchable * piMultiBranchable4 = NULL; 

  CATBaseUnknown_var spMultiBNS = (*pListMultiBns)[1];
  if (NULL_var != spMultiBNS) 
  {
    spMultiBNS->QueryInterface(IID_CATIEhiMultiBranchable,(void**) &piMultiBranchable1);  
  }
  spMultiBNS = (*pListMultiBns)[2];
  if (NULL_var != spMultiBNS) 
  {
    spMultiBNS->QueryInterface(IID_CATIEhiMultiBranchable,(void**) &piMultiBranchable2);  
  }
  spMultiBNS = (*pListMultiBns)[3];
  if (NULL_var != spMultiBNS) 
  {
    spMultiBNS->QueryInterface(IID_CATIEhiMultiBranchable,(void**) &piMultiBranchable3);  
  }
  spMultiBNS = (*pListMultiBns)[4];
  if (NULL_var != spMultiBNS) 
  {
    spMultiBNS->QueryInterface(IID_CATIEhiMultiBranchable,(void**) &piMultiBranchable4);  
  }

  if (NULL == piMultiBranchable1) return 9;
  if (NULL == piMultiBranchable2) return 9;
  if (NULL == piMultiBranchable3) return 9;
  if (NULL == piMultiBranchable4) return 9;



  // --- Retrieving all bns under the multi branchable

  CATListValCATBaseUnknown_var* pListBns= NULL; 
  rc = piMultiBranchable4->ListBundleSegments(&pListBns);
  int nbBns=pListBns?pListBns->Size():0;

  cout << "> nbBns="<< nbBns << endl << flush;

  if (SUCCEEDED(rc) && (NULL!=pListBns) && (1 == pListBns->Size()))
  {
    cout << "> list bns ok " << endl << flush;
  }
  else
  {
    cout << "ERROR : pb in ListBns " << endl << flush;
    return 10;
  }


  CATIEhiBundleSegment * piEhiBns = NULL;  // the multi branchable choosen  

  CATBaseUnknown_var spBNS = (*pListBns)[1];
  if (NULL_var != spBNS) 
  {
    spBNS->QueryInterface(IID_CATIEhiBundleSegment,(void**) &piEhiBns);  
  }
  if (NULL == piEhiBns) return 10;

  delete pListBns;
  pListBns=NULL; 


  //--------------------------------------------------------------------
  // 5. Retrieving the support to link with the bundle segment
  //--------------------------------------------------------------------

  CATIProduct* piSupport = NULL;
  
  for ( i =1; i<=NumberOfProduct; i++ )
  { 
	  CATBaseUnknown_var spProduct = (*pListProduct)[i];
	  if (NULL_var != spProduct)
	  {
		  spProduct->QueryInterface(IID_CATIProduct,(void**) &piInstanceProduct);
		  if ( NULL != piInstanceProduct ) 
		  {
			  piInstanceProduct->GetPrdInstanceName(InstanceName);	
			  
			  if (2 == InstanceName.Compare("Support-3"))
			  {
				  piSupport =  piInstanceProduct; 
				  piSupport->AddRef();
			  }
		  }
		  if ( NULL != piInstanceProduct ) piInstanceProduct->Release();		
		  piInstanceProduct = NULL;
		  InstanceName = "unknown";
	  }
	  
  }

  if (NULL == piSupport) return 11;
  
  //--------------------------------------------------------------------
  // 6. Add support to bns
  //--------------------------------------------------------------------

  int num=1;

  rc = piEhiBns->AddSupport(piSupport,catEhiInvertMode,&num,catEhiInsertAfter);
  
  if (SUCCEEDED(rc))
  {
    cout << "> Add support is ok " << endl << flush;
  }
  else
  {
    cout << "ERROR : pb in AddSupport " << endl << flush;
    return 12;
  }
 
  //UOK START
  //--------------------------------------------------------------------
  // Test InsertSupport on CATIEhiBranchable
  //--------------------------------------------------------------------
  CATListValCATBaseUnknown_var * pListOfBranchables = NULL;
  CATIEhiMultiBranchable * piMBNS = NULL;
  CATIEhiBranchable * piBranch = NULL;
  CATIEhiBranchable * piBranchForRetainer = NULL;

  CATBaseUnknown_var hMBNS = (*pListMultiBns)[5];
  
  if(NULL_var != hMBNS)
  {
    rc = hMBNS->QueryInterface(IID_CATIEhiMultiBranchable,(void**) &piMBNS);

    if(SUCCEEDED(rc) && (NULL != piMBNS))
    {
      rc = piMBNS->ListBranchables(&pListOfBranchables);

      if(SUCCEEDED(rc) && (NULL != pListOfBranchables) && (2 == pListOfBranchables->Size()))
      {
        CATBaseUnknown_var hBranchable = (*pListOfBranchables)[1];

        if(NULL_var != hBranchable)
          rc = hBranchable->QueryInterface(IID_CATIEhiBranchable,(void**) &piBranch);

        // LVP Start :- Handling of retainer case 
        CATBaseUnknown_var hBranchableForRetainer = (*pListOfBranchables)[2];
        if(NULL_var != hBranchableForRetainer)
          rc = hBranchableForRetainer->QueryInterface(IID_CATIEhiBranchable,(void**) &piBranchForRetainer);
        // LVP End :- Handling of retainer case 
      }
    }
  }

  //get multisupport
  CATIProduct* piMultiSupport = NULL;
  
  for ( i =1; i<=NumberOfProduct; i++ )
  { 
	  CATBaseUnknown_var spProduct = (*pListProduct)[i];
	  if (NULL_var != spProduct)
	  {
		  spProduct->QueryInterface(IID_CATIProduct,(void**) &piInstanceProduct);
		  if ( NULL != piInstanceProduct ) 
		  {
			  piInstanceProduct->GetPrdInstanceName(InstanceName);	
			  
			  if (2 == InstanceName.Compare("MultiSupport"))
			  {
				  piMultiSupport =  piInstanceProduct;
				  piMultiSupport->AddRef();
          break;
			  }
		  }
		  if ( NULL != piInstanceProduct ) piInstanceProduct->Release();		
		  piInstanceProduct = NULL;
		  InstanceName = "unknown";
	  }	  
  }

  // LVP Start :- Handling of retainer case 
  // Get the retainer
  CATIProduct* piPrdRetainer = NULL;
  
  for ( i =1; i<=NumberOfProduct; i++ )
  { 
	  CATBaseUnknown_var spProduct = (*pListProduct)[i];
	  if (NULL_var != spProduct)
	  {
		  spProduct->QueryInterface(IID_CATIProduct,(void**) &piInstanceProduct);
		  if ( NULL != piInstanceProduct ) 
		  {
			  piInstanceProduct->GetPrdInstanceName(InstanceName);	
			  
			  if (2 == InstanceName.Compare("R19_Spt_MultipleSectionsWithBasePlanes.1"))
			  {
				  piPrdRetainer =  piInstanceProduct;
				  piPrdRetainer->AddRef();
          break;
			  }
		  }
		  if ( NULL != piInstanceProduct ) piInstanceProduct->Release();		
		  piInstanceProduct = NULL;
		  InstanceName = "unknown";
	  }
  }
  // LVP End :- Handling of retainer case 
  if (NULL == piMultiSupport)
    return 23;
  if (NULL == piPrdRetainer)
    return 26; // Retainer not found

  if(NULL != piBranch)
    rc = piBranch->InsertSupport(piMultiSupport,catEhiDirectMode,1,catEhiInsertAfter,2);
  
  if (SUCCEEDED(rc))
  {
    cout << "> Insert support on CATIEhiBranchable is ok " << endl << flush;
  }
  else
  {
    cout << "ERROR : Insert support on CATIEhiBranchable failed " << endl << flush;
    return 24;
  }
  // LVP Start :- Handling of retainer case 
  if(NULL != piBranchForRetainer)
    rc = piBranchForRetainer->InsertSupport(piPrdRetainer,catEhiDirectMode,1,catEhiInsertAfter,3);

  if (SUCCEEDED(rc))
  {
    cout << "> Insert retainer support on CATIEhiBranchable is ok " << endl << flush;
  }
  else
  {
    cout << "ERROR : Insert retainer support on CATIEhiBranchable failed " << endl << flush;
    return 27;
  }
  // LVP End :- Handling of retainer case 

  //--------------------------------------------------------------------
  // Test GetLinkedSupportSection on CATIEhiBundleSegment
  //--------------------------------------------------------------------
  CATListValCATBaseUnknown_var * pListOfSegments = NULL;
  CATIEhiBundleSegment_var hSegment = NULL_var;

  if(NULL != piBranch)
    rc = piBranch-> ListBundleSegments(&pListOfSegments);

  if (SUCCEEDED(rc) && (NULL != pListOfSegments))
  {
    hSegment = ((*pListOfSegments)[1]);
  }

  CATListValCATBaseUnknown_var* pListSupports = NULL;
  CATBaseUnknown * ipLinkedSupport= NULL;
  int section_number;

  if(NULL_var != hSegment)
    rc = hSegment->ListLinkedSupports(&pListSupports);

  if(SUCCEEDED(rc) && (NULL != pListSupports) && (pListSupports->Size()>0))
  {
    CATBaseUnknown_var hsupp((*pListSupports)[1]);

    if(NULL_var != hsupp)
      rc = hsupp->QueryInterface(IID_CATBaseUnknown , (void**)&ipLinkedSupport);
  }

  if((NULL_var != hSegment) && (NULL != ipLinkedSupport))
    rc = hSegment->GetLinkedSupportSection(ipLinkedSupport,section_number);

  if (SUCCEEDED(rc) && (2 == section_number))
  {
    cout << "> GetLinkedSupportSection on CATIEhiBundleSegment is ok " << endl << flush;
  }
  else
  {
    cout << "ERROR : GetLinkedSupportSection on CATIEhiBundleSegment failed " << endl << flush;
    return 25;
  }

  if(NULL != pListOfSegments)
  {
    delete pListOfSegments;
    pListOfSegments = NULL;
  }
  if(NULL != pListSupports)
  {
    delete pListSupports;
    pListSupports = NULL;
  }
  if(NULL != ipLinkedSupport)
  {
    ipLinkedSupport->Release();
    ipLinkedSupport = NULL;
  }

  // LVP Start :- Handling of retainer case 
  pListOfSegments = NULL;
  hSegment = NULL_var;

  if(NULL != piBranchForRetainer)
    rc = piBranchForRetainer-> ListBundleSegments(&pListOfSegments);

  if (SUCCEEDED(rc) && (NULL != pListOfSegments))
  {
    hSegment = ((*pListOfSegments)[1]);
  }

  pListSupports = NULL;
  ipLinkedSupport= NULL;
  int section_number_retainer;

  if(NULL_var != hSegment)
    rc = hSegment->ListLinkedSupports(&pListSupports);

  if(SUCCEEDED(rc) && (NULL != pListSupports) && (pListSupports->Size()>0))
  {
    CATBaseUnknown_var hsupp((*pListSupports)[1]);

    if(NULL_var != hsupp)
      rc = hsupp->QueryInterface(IID_CATBaseUnknown , (void**)&ipLinkedSupport);
  }

  if((NULL_var != hSegment) && (NULL != ipLinkedSupport))
    rc = hSegment->GetLinkedSupportSection(ipLinkedSupport,section_number_retainer);

  if (SUCCEEDED(rc) && (3 == section_number_retainer))
  {
    cout << "> GetLinkedSupportSection on CATIEhiBundleSegment is ok for retainer " << endl << flush;
  }
  else
  {
    cout << "ERROR : GetLinkedSupportSection on CATIEhiBundleSegment failed for retainer " << endl << flush;
    return 28;
  }
// LVP End :- Handling of retainer case 
  if(NULL != piMBNS)
  {
    piMBNS->Release();
    piMBNS = NULL;
  }

  if(NULL != pListOfBranchables)
  {
    delete pListOfBranchables;
    pListOfBranchables = NULL;
  }

  if(NULL != pListOfSegments)
  {
    delete pListOfSegments;
    pListOfSegments = NULL;
  }

  if(NULL != pListSupports)
  {
    delete pListSupports;
    pListSupports = NULL;
  }

  if(NULL != ipLinkedSupport)
  {
    ipLinkedSupport->Release();
    ipLinkedSupport = NULL;
  }

  if(NULL != piMultiSupport)
  {
    piMultiSupport->Release();
    piMultiSupport = NULL;
  }

  if(NULL != piBranch)
  {
    piBranch->Release();
    piBranch = NULL;
  }
  if(NULL != piBranchForRetainer)
  {
    piBranchForRetainer->Release();
    piBranchForRetainer = NULL;
  }

  if(NULL != pListMultiBns)
  {
    delete pListMultiBns;
    pListMultiBns=NULL;
  } 

  if(NULL != piInstanceProduct)
  {
    piInstanceProduct->Release();
    piInstanceProduct = NULL;
  }

  if(NULL != pListProduct)
  {
    delete pListProduct;
    pListProduct=NULL;  
  }

  //UOK END

  //---------------------------------------------------------------------------
  // 7. Update the multi branchable
  //---------------------------------------------------------------------------

  rc = piEhiGbn->ComputeMultiBranchable(piMultiBranchable4);
  if (SUCCEEDED(rc))
  {
    cout << "> ComputeMultiBranchable is OK " << endl << flush;
  }
  else
  {
    cout << "ERROR : pb in ComputeMultiBranchable " << endl << flush;
    return 13;
  }


  //-------------------------------------------------------------------------
  // 8. Saving the documents
  //-------------------------------------------------------------------------

  // -- saving the first bundle segment

  CATIProduct_var spMultiBranchableI = piMultiBranchable1;
  CATAssert(!!spMultiBranchableI);
  CATIProduct_var spMultiBranchableR = spMultiBranchableI->GetReferenceProduct();
  CATAssert(!!spMultiBranchableR);
  
  CATILinkableObject_var spLinkable=spMultiBranchableR;
  CATAssert(!!spLinkable);
  
  CATDocument * pMultiBns1PartDoc = spLinkable->GetDocument();  
  
  if ( !pMultiBns1PartDoc )
  {
    cout << "ERROR in retrieving bundle segment 1 CATPart document" << endl << flush;
    return 14;
  }

  rc = CATDocumentServices::SaveAs (*pMultiBns1PartDoc , PathOutput+MultiBns1File );
  if (SUCCEEDED(rc))
  {
    cout << "> bundle segment 1 CATPart document saved " << endl << flush;
  }
  else
  {
    cout << "ERROR in saving bundle segment 1 CATPart document" << endl << flush;
    return 14;
  }

  // -- saving the second bundle segment

  spMultiBranchableI = piMultiBranchable2;
  CATAssert(!!spMultiBranchableI);
  spMultiBranchableR = spMultiBranchableI->GetReferenceProduct();
  CATAssert(!!spMultiBranchableR);
  
  spLinkable=spMultiBranchableR;
  CATAssert(!!spLinkable);
  
  CATDocument * pMultiBns2PartDoc = spLinkable->GetDocument();  
  
  if ( !pMultiBns2PartDoc )
  {
    cout << "ERROR in retrieving bundle segment 2 CATPart document" << endl << flush;
    return 15;
  }

  rc = CATDocumentServices::SaveAs (*pMultiBns2PartDoc , PathOutput+MultiBns2File );
  if (SUCCEEDED(rc))
  {
    cout << "> bundle segment 2 CATPart document saved " << endl << flush;
  }
  else
  {
    cout << "ERROR in saving bundle segment 2 CATPart document" << endl << flush;
    return 15;
  }

  // -- saving the third bundle segment

  spMultiBranchableI = piMultiBranchable3;
  CATAssert(!!spMultiBranchableI);
  spMultiBranchableR = spMultiBranchableI->GetReferenceProduct();
  CATAssert(!!spMultiBranchableR);
  
  spLinkable=spMultiBranchableR;
  CATAssert(!!spLinkable);
  
  CATDocument * pMultiBns3PartDoc = spLinkable->GetDocument();  
  
  if ( !pMultiBns3PartDoc )
  {
    cout << "ERROR in retrieving bundle segment 3 CATPart document" << endl << flush;
    return 16;
  }

  rc = CATDocumentServices::SaveAs (*pMultiBns3PartDoc , PathOutput+MultiBns3File );
  if (SUCCEEDED(rc))
  {
    cout << "> bundle segment 3 CATPart document saved " << endl << flush;
  }
  else
  {
    cout << "ERROR in saving bundle segment 3 CATPart document" << endl << flush;
    return 16;
  }

  // -- saving the fourth bundle segment

  spMultiBranchableI = piMultiBranchable4;
  CATAssert(!!spMultiBranchableI);
  spMultiBranchableR = spMultiBranchableI->GetReferenceProduct();
  CATAssert(!!spMultiBranchableR);
  
  spLinkable=spMultiBranchableR;
  CATAssert(!!spLinkable);
  
  CATDocument * pMultiBns4PartDoc = spLinkable->GetDocument();  
  
  if ( !pMultiBns4PartDoc )
  {
    cout << "ERROR in retrieving bundle segment 4 CATPart document" << endl << flush;
    return 17;
  }

  rc = CATDocumentServices::SaveAs (*pMultiBns4PartDoc , PathOutput+MultiBns4File );
  if (SUCCEEDED(rc))
  {
    cout << "> bundle segment 4 CATPart document saved " << endl << flush;
  }
  else
  {
    cout << "ERROR in saving bundle segment 4 CATPart document" << endl << flush;
    return 17;
  }


  // -- saving the geometrical bundle

  rc = CATDocumentServices::SaveAs (*pGbnDoc , PathOutput+GbnFile );
  if (SUCCEEDED(rc))
  {
    cout << "> geometrical bundle document saved " << endl << flush;
  }
  else
  {
    cout << "ERROR in saving geometrical bundle document" << endl << flush;
    return 18;
  }

  // -- saving the sub document

  rc = CATDocumentServices::SaveAs (*pSubProdDoc , PathOutput+SubProdFile );
  if (SUCCEEDED(rc))
  {
    cout << "> sub document saved " << endl << flush;
  }
  else
  {
    cout << "ERROR in saving sub document" << endl << flush;
    return 19;
  }

  // --- saving main document

  rc = CATDocumentServices::SaveAs (*pMainDoc , PathOutput+MainFile );
  if (SUCCEEDED(rc))
  {
    cout << "> main document saved " << endl << flush;
  }
  else
  {
    cout << "ERROR in saving document" << endl << flush;
    return 20;
  }


  //--------------------------------------------------------------------
  // 9. Epilogue  
  //--------------------------------------------------------------------
  
  // 9.1-- releasing pointers to interface
  //
  
  piRootProduct->Release(); 
  piMultiBranchable1->Release(); 
  piMultiBranchable2->Release();
  piMultiBranchable3->Release();  
  piMultiBranchable4->Release(); 
  piSupport->Release(); 
  piEhiBns->Release(); 
  piEhiGbn->Release(); 

  
  // --- always reset pointer value to NULL after release
  piRootProduct=NULL;
  piMultiBranchable1=NULL; 
  piMultiBranchable2=NULL; 
  piMultiBranchable3=NULL; 
  piMultiBranchable4=NULL; 
  piSupport=NULL;
  piEhiBns=NULL;  
  piEhiGbn=NULL;  
 

  //
  // 9.2-- removing document from session 
  rc = CATDocumentServices::Remove(*pMainDoc);
  if (SUCCEEDED(rc))
  {
    cout << "> document removed " << endl << flush;
  }
  else
  {
    cout << "ERROR in removing document" << endl << flush;
    return 21;
  }

  // 9.3-- closing the session
  rc = ::Delete_Session(sessionName);
  if (SUCCEEDED(rc))
    cout << "> session deleted " << endl << flush;
  else
  {
    cout << "ERROR in deleting session" << endl << flush;
    return 22;
  }
  cout << "----------------------------------------------------------------" << endl << flush;
  cout << endl << flush;
  cout << endl << flush;
  
  //
  return 0;
}

