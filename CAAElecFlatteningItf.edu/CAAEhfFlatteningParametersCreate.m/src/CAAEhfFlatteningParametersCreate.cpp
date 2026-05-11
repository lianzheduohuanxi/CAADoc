/**
 * @fullreview AKL VEI 05:09:29
 * @error MISC Y
 * @error BCMM Y
 */
/**
 *
 * @quickReview VEI AKL 05:09:30 // R17 H/L
 * @quickReview SPS VEI 05:10:27 // Correction of Unix compile error
 * @quickReview SPS VEI 06:01:18 // Removed CATSysMacors
 * @quickReview AKL VEI 06:02:07 // Output params to have reference data type (&)
 */
// --------------------------------------------------------

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

// - System
#include "CATBaseUnknown.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATString.h"

// - ObjectModelerBase
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATIDocRoots.h"
#include "CATSessionServices.h"
#include "CATSession.h"

// --- ProductStructure Framework
#include "CATIProduct.h"

// Electrical Interfaces
#include "CATIEleDocServices.h"

// ElecFlatteningItf
#include "CATIEhfFlatteningParameters.h"
#include "CATIEhfEnvironment.h"


// =============================================================================
// Main
// =============================================================================
/* 
** Return Value   = 0: On Successful Completion of the Sample Code 
**                = 1: If File name of the model doesn't exist in the Input arguments.
**                = 2: If CATSession::Create_Session Failed.
**                = 3: If the File of model doesn't get opened.
**                = 4: If QueryInterface to CATIEleDocServices Failed.
**                = 5: If Initialize() Method of CATIEleDocServices Failed.
**                = 6: If QueryInterface to CATIDocRoots Failed.
**                = 7: If GiveDocRoots() Method Failed on CATIDocRoots.
**                = 8: If number of RootProducts in CATIDocRoots less than equal to zero.
**                = 9: If 1st Root Product in CATIDocRoots is NULL.
**                =10: If QueryInterface to CATIProduct Failed on RootProduct.
**                =11: If QueryInterface to CATIEhfEnvironment Failed.
**                =12: If GetFlatteningParameters() Method of CATIEhfEnvironment Failed.
**                =13: If number of FlatteningPara is less than equal to zero.
**                =14: If Pointer to FlatteningPara is NULL.
**                =15: If QueryInterface to CATIEhfFlatteningParameters Failed.
**                =16: If CreateFlatteningParameters() Method of CATIEhfEnvironment Failed.
**                =17: If SetAlgorithmMode() Method of CATIEhfFlatteningParameters Failed.
**                =18: If GetAlgorithmMode() Method of CATIEhfFlatteningParameters Failed.
**                =19: If CreateFlatteningParameters() Method of CATIEhfEnvironment is created once again.
*/
int main (int argc, char **argv)
{

  int                             retCode = 0, index = 0 ;
  int                             nbFlatteningPara = 0, nProducts = 0 ;
  int                             compareAlgo = -1;
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
  CATIEhfFlatteningParameters   * pIEhfCreateFlattenPara          = NULL ; // To be Released
  CATIProduct                   * pIRootProduct                   = NULL ; // To be Released
  CATString                     * setpAlgoMode                    = NULL ; // To be Deleted
  CATString                       getAlgoMode ;

  CATBaseUnknown_var              hUnkFlatteningPara ;
  CATBaseUnknown_var              hUnkRootProd ;

  // -------------------------------------------------------------------------
  // - Create the session
  // -------------------------------------------------------------------------
  hr = Create_Session(sessionIdent, pSession);
  if ( (NULL == pSession) || ( FAILED(hr) ) )
  {
    retCode = 2; 
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Open a new document
  // -------------------------------------------------------------------------
  hr = CATDocumentServices::New("Product", pDoc);
  if ( ( NULL == pDoc )|| ( FAILED(hr) ) )
  {
    retCode = 3; 
    goto EscapeWay;
  }

  hr = pDoc->QueryInterface(IID_CATIEleDocServices,(void**)&pIEleDocServices );
  if ( FAILED(hr) )
  {
    retCode = 4; 
    goto EscapeWay;
  }

  hr = pIEleDocServices->Initialize();
  if ( FAILED(hr) )
  {
    retCode = 5; 
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Get Root Product
  // -------------------------------------------------------------------------
  hr = pDoc->QueryInterface(IID_CATIDocRoots, (void**)(&pIDocRootsOnDoc));
  if(FAILED(hr))
  {
    retCode = 6;
    goto EscapeWay;
  }

  // Get the root product which is the first element of root elements
  pListUnkRootProducts = pIDocRootsOnDoc->GiveDocRoots();
  if(NULL == pListUnkRootProducts)
  {
    retCode = 7;
    goto EscapeWay;
  }

  nProducts = pListUnkRootProducts->Size();
  if( 0 >= nProducts)
  {
    retCode = 8;
    goto EscapeWay;
  }

  hUnkRootProd = (*pListUnkRootProducts)[1];
  if(NULL_var == hUnkRootProd)
  {
    retCode = 9;
    goto EscapeWay;
  }

  hr = hUnkRootProd->QueryInterface(IID_CATIProduct, (void**)(&pIRootProduct));
  if(FAILED(hr))
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

  // -------------------------------------------------------------------------
  // -Create FlatteningParameters
  // -------------------------------------------------------------------------
  hr = pIEhfEnvironment->CreateFlatteningParameters(pIEhfCreateFlattenPara);
  if( ( FAILED(hr) ) || ( NULL == pIEhfCreateFlattenPara ) )
  {
    retCode = 12;
    goto EscapeWay;
  }

  hr = pIEhfEnvironment->GetFlatteningParameters(&phListFlatteningPara);
  if ( ( FAILED(hr) ) || ( NULL == phListFlatteningPara ) )
  {
    retCode = 13;
    goto EscapeWay;
  }

  nbFlatteningPara = phListFlatteningPara->Size();
  if (0 >= nbFlatteningPara)
  {
    retCode = 14; 
    goto EscapeWay;
  }

  hUnkFlatteningPara = (*phListFlatteningPara)[1];
  if (NULL_var == hUnkFlatteningPara)
  {
    retCode = 15; 
    goto EscapeWay;
  }

  hr = hUnkFlatteningPara->QueryInterface(IID_CATIEhfFlatteningParameters, (void **)&pIFlatteningPara);
  if ( FAILED(hr) )
  {
    retCode = 16; 
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Set Algorithm Mode
  // -------------------------------------------------------------------------
  setpAlgoMode = new CATString();
  (*setpAlgoMode) = ("Coarse");

  hr = pIFlatteningPara->SetAlgorithmMode(setpAlgoMode);
  if ( ( FAILED(hr) ) || ( NULL == setpAlgoMode ) )
  {
    retCode = 17; 
    goto EscapeWay;
  }  

  // -------------------------------------------------------------------------
  // - Get Algorithm Mode
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->GetAlgorithmMode(getAlgoMode);
  compareAlgo = getAlgoMode.Compare("Coarse");
  
  if ( ( FAILED(hr) ) || ( 0 != compareAlgo ) )
  {
    retCode = 18; 
    goto EscapeWay;
  }


  // -------------------------------------------------------------------------
  // - Test for CreateFlatteningParameters second set
  // -------------------------------------------------------------------------    
  if (NULL != pIEhfCreateFlattenPara)
  {
    pIEhfCreateFlattenPara->Release();
    pIEhfCreateFlattenPara = NULL;
  }

  hr = pIEhfEnvironment->CreateFlatteningParameters(pIEhfCreateFlattenPara);
  if( ( SUCCEEDED(hr) ) && ( NULL != pIEhfCreateFlattenPara ) )
  {
    retCode = 19;
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
  if (NULL != pIEhfCreateFlattenPara)
  {
    pIEhfCreateFlattenPara->Release();
    pIEhfCreateFlattenPara = NULL;
  }
  
  //DeletePtr
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
  if (NULL != setpAlgoMode)
  {
    delete setpAlgoMode; 
    setpAlgoMode =0; 
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



