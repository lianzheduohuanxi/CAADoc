/**
 * @fullreview SPS VEI 05:11:24
 */	
/**
 *
 * @quickReview SPS VEI 06:01:18 // Removed CATSysMacors
 */
// --------------------------------------------------------
// --------------------------------------------------------
// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
//
// Usage notes: Test of the CAA interface in Ehf
//
//===================================================================
//
//  September 2005   VEI
//===================================================================

// --- System ---
#include "CATBaseUnknown.h"
#include "CATLISTV_CATBaseUnknown.h"

// - ObjectModelerBase ---
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATIDocRoots.h"
#include "CATSessionServices.h"
#include "CATSession.h"

// --- ProductStructure Framework ---
#include "CATIProduct.h"

// --- Electrical Interfaces ---
#include "CATIEleDocServices.h"

// --- ElecFlatteningItf ---
#include "CATIEhfFlatteningParameters.h"
#include "CATIEhfEnvironment.h"
#include "CATIEhfFlattenManager.h"


// =============================================================================
// Main
// =============================================================================
/* 
** Return Value   = 0: On Successful Completion of the Sample Code 
**                = 1: If File name of the model doesn't exist in the Input arguments.
**                = 2: If CATSession::Create_Session Failed.
**                = 3: If the File of model doesn't get opened.
**                = 4: If QueryInterface to CATIDocRoots Failed.
**                = 5: If GiveDocRoots() Method Failed on CATIDocRoots.
**                = 6: If number of RootProducts in CATIDocRoots less than equal to zero.
**                = 7: If 1st Root Product in CATIDocRoots is NULL.
**                = 8: If QueryInterface to CATIProduct Failed on RootProduct.
**                = 9: If QueryInterface to CATIEleDocServices Failed.
**                =10: If Initialize() Method of CATIEleDocServices Failed.
**                =11: If QueryInterface to CATIEhfEnvironment Failed.
**                =12: If GetFlatteningParameters() Method of CATIEhfEnvironment Failed.
**                =13: If number of FlatteningPara is less than equal to zero.
**                =14: If Pointer to FlatteningPara is NULL.
**                =15: If QueryInterface to CATIEhfFlatteningParameters Failed.
**                =16: If GetAllChildren on Root Product is NULL.
**                =17: If list of CATIEhiGeoBundle is less than equal to zero.
**                =18: If CATBaseUnknown_var is NULL_var.
**                =19: If QueryInterface to CATBaseUnknown Failed.
**                =20: If QueryInterface to CATIEhfFlattenManager Failed.
**                =21: If FlattenHarness Fails.
*/

int main (int argc, char **argv)
{

  int                             retCode = 0, index = 0 ;
  int                             nbFlatteningPara = 0, nProducts = 0 ;
  HRESULT                         hr                              = E_FAIL ;

  char                          * sessionIdent                    = "Session Elec";

  CATListValCATBaseUnknown_var  * phListFlatteningPara            = NULL ;
  CATListValCATBaseUnknown_var  * pListUnkRootProducts            = NULL ;

  CATSession                    * pSession                        = NULL ; // To be Deleted
  CATDocument                   * pDoc                            = NULL ; // To be Removed by calling CATDocumentServices::Remove()

  CATIEleDocServices            * pIEleDocServices                = NULL ; // To be Released
  CATIDocRoots                  * pIDocRootsOnDoc                 = NULL ; // To be Released
  CATIEhfFlatteningParameters   * pIFlatteningPara                = NULL ; // To be Released
  CATIEhfEnvironment            * pIEhfEnvironment                = NULL ; // To be Released
  CATIProduct                   * pIRootProduct                   = NULL ; // To be Released
  CATIEhfFlattenManager         * pIFlatten                       = NULL ;
  CATBaseUnknown                * pIUnkGBN                        = NULL ;
  CATLISTP(CATBaseUnknown)        ListOfGBNs;
  int                             numGBN                          = -1 ;

  CATListValCATBaseUnknown_var  * phUnkListChildren               = NULL;
  CATBaseUnknown_var              hUnkFlatteningPara ;
  CATBaseUnknown_var              hUnkRootProd ;
  CATBaseUnknown_var              hUnkListElem ;

  //ensure that the input filename exists in the arguments
  if ( 2 > argc ) 
  {
    retCode = 1; 
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Create the session
  // -------------------------------------------------------------------------
  hr = Create_Session(sessionIdent, pSession);

  if ((NULL == pSession) || FAILED(hr))
  {
    retCode = 2; 
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Open the document
  // -------------------------------------------------------------------------
  hr = CATDocumentServices::OpenDocument(argv[1], pDoc);

  if ((NULL == pDoc)|| FAILED(hr))
  {
    retCode = 3; 
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Get Root Product
  // -------------------------------------------------------------------------
  hr = pDoc->QueryInterface(IID_CATIDocRoots, (void**)(&pIDocRootsOnDoc));
  if(FAILED(hr))
  {
    retCode = 4;
    goto EscapeWay;
  }

  // Get the root product which is the first element of root elements
  pListUnkRootProducts = pIDocRootsOnDoc->GiveDocRoots();
  if(NULL == pListUnkRootProducts)
  {
    retCode = 5;
    goto EscapeWay;
  }

  nProducts = pListUnkRootProducts->Size();
  if( 0 == nProducts)
  {
    retCode = 6;
    goto EscapeWay;
  }

  hUnkRootProd = (*pListUnkRootProducts)[1];
  if(NULL_var == hUnkRootProd)
  {
    retCode = 7;
    goto EscapeWay;
  }

  hr = hUnkRootProd->QueryInterface(IID_CATIProduct, (void**)(&pIRootProduct));
  if(FAILED(hr))
  {
    retCode = 8;
    goto EscapeWay;
  }

  // Initialise Electrical Environment
  hr = pDoc->QueryInterface(IID_CATIEleDocServices,(void**)&pIEleDocServices );
  if ( FAILED(hr) )
  {
    retCode = 9; 
    goto EscapeWay;
  }

  hr = pIEleDocServices->Initialize();
  if ( FAILED(hr) )
  {
    retCode = 10; 
    goto EscapeWay;
  }

  hr = pIRootProduct->QueryInterface(IID_CATIEhfEnvironment,(void**)&pIEhfEnvironment);
  if ( FAILED(hr) )
  {
    retCode = 11;
    goto EscapeWay;
  }

  hr = pIEhfEnvironment->GetFlatteningParameters(&phListFlatteningPara);
  if ( ( FAILED(hr) ) || ( NULL == phListFlatteningPara ) )
  {
    retCode = 12;
    goto EscapeWay;
  }

  nbFlatteningPara = phListFlatteningPara->Size();
  if (0 >= nbFlatteningPara)
  {
    retCode = 13;
    goto EscapeWay;
  }

  hUnkFlatteningPara = (*phListFlatteningPara)[1];
  if (NULL_var == hUnkFlatteningPara)
  {
    retCode = 14;
    goto EscapeWay;
  }

  hr = hUnkFlatteningPara->QueryInterface(IID_CATIEhfFlatteningParameters, (void **)&pIFlatteningPara);
  if ( FAILED(hr) )
  {
    retCode = 15;
    goto EscapeWay;
  }

  phUnkListChildren = pIRootProduct->GetAllChildren("CATIEhiGeoBundle");
  if( NULL == phUnkListChildren )
  {
    retCode = 16;
    goto EscapeWay;
  }
  
  numGBN = phUnkListChildren->Size();
  if( 0 >= numGBN )
  {
    retCode = 17;
    goto EscapeWay;    
  }

  hUnkListElem = (*phUnkListChildren)[1] ;
  if( NULL_var == hUnkListElem )
  {
    retCode = 18;
    goto EscapeWay;
  }

  hr = hUnkListElem->QueryInterface(IID_CATBaseUnknown, (void**)&pIUnkGBN) ;
  if( FAILED(hr) )
  {
    retCode = 19;
    goto EscapeWay;    
  }

  ListOfGBNs.Append(pIUnkGBN) ;

  hr = pIRootProduct->QueryInterface(IID_CATIEhfFlattenManager,(void**)&pIFlatten);
  if ( FAILED(hr) )
  {
    retCode = 20;
    goto EscapeWay;
  }

  hr = pIFlatten->FlattenHarness( &ListOfGBNs );
  if (FAILED( hr))
  {
    retCode = 21;
    goto EscapeWay;
  }

  
EscapeWay:

  // Clean Up
  //ReleasePtr
  if (NULL != pIEleDocServices)
  { 
    pIEleDocServices->Release();
    pIEleDocServices = NULL;
  }
  if (NULL != pIDocRootsOnDoc)
  {
    pIDocRootsOnDoc->Release();
    pIDocRootsOnDoc = NULL;
  }
  if (NULL != pIEhfEnvironment)
  {
    pIEhfEnvironment->Release();
    pIEhfEnvironment = NULL;
  }
  if (NULL != pIRootProduct)
  {
    pIRootProduct->Release();
    pIRootProduct = NULL;
  }
  if (NULL != pIFlatteningPara)
  {
    pIFlatteningPara->Release();
    pIFlatteningPara = NULL;
  }
  if (NULL != pIFlatten) 
  {
    pIFlatten->Release();
    pIFlatten = NULL;
  }
  if (NULL != pIUnkGBN) 
  {
    pIUnkGBN->Release(); 
    pIUnkGBN = NULL;
  }

  //DeletePtr
  if (NULL != phUnkListChildren)
  {
    delete phUnkListChildren; 
    phUnkListChildren =0; 
  }
  if (NULL != pListUnkRootProducts)
  {
    delete pListUnkRootProducts; 
    pListUnkRootProducts =0; 
  }
  if (NULL != phListFlatteningPara)
  {
    delete phListFlatteningPara; 
    phListFlatteningPara =0; 
  }

  if( NULL != pDoc )
  {
    CATDocumentServices::Remove(*pDoc) ;
    pDoc = NULL ;
  }
  if ( NULL != pSession )
  {
    //from CATSessionServices
    hr = ::Delete_Session(sessionIdent) ;
  }
  
  return retCode;
}



