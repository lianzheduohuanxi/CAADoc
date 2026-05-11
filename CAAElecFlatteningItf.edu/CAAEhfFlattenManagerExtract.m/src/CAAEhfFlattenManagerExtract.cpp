/**
 * @fullreview SPS VEI 05:11:24
 */	
/**
 *
 * @quickReview SPS VEI 06:01:19 // Removed CATSysMacors
 * @quickReview AKL VEI 06:02:07 // Output params to have reference data type (&)
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
//  October 2005   VEI
//===================================================================

// - System
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATString.h"
#include "CATBoolean.h"

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
#include "CATIEhfFlattenManager.h"


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
**                =11: If New() of CATDocumentServices Failed.
**                =12: If QueryInterface to CATIEleDocServices for New Document Failed.
**                =13: If Initialize() Method of CATIEleDocServices for New Document Failed.
**                =14: If QueryInterface to CATIDocRoots for New Document Failed.
**                =15: If GiveDocRoots() Method for New Document Failed on CATIDocRoots.
**                =16: If number of RootProducts in CATIDocRoots for New Document less than equal to zero.
**                =17: If 1st Root Product in CATIDocRoots for New Document is NULL.
**                =18: If QueryInterface to CATIProduct for New Document Failed on RootProduct.
**                =19: If QueryInterface to CATIEhfEnvironment for New Document Failed.
**                =20: If CreateFlatteningParameters() Method of CATIEhfEnvironment for New Document Failed.
**                =21: If GetFlatteningParameters() Method of CATIEhfEnvironment Failed.
**                =22: If number of FlatteningPara is less than equal to zero.
**                =23: If Pointer to FlatteningPara is NULL.
**                =24: If QueryInterface to CATIEhfFlatteningParameters Failed.
**                =25: If SetName() Method of CATIEhfFlatteningParameters Failed.
**                =26: If SetAlgorithmMode() Method of CATIEhfFlatteningParameters Failed.
**                =27: If SetAngle() Method of CATIEhfFlatteningParameters Failed.
**                =28: If SetBNSTypeScaledDuringSync() Method of CATIEhfFlatteningParameters Failed.
**                =29: If SetMoveIntermediatePtDuringSync() Method of CATIEhfFlatteningParameters Failed.
**                =30: If QueryInterface to CATIEhfFlattenManager Failed.
**                =31: If QueryInterface to CATBaseUnknown on RootProduct Failed.
**                =32: If ExtractHarness of CATIEhfFlattenManager Failed.
*/


int main (int argc, char **argv)
{

  int                             retCode = 0, index = 0, sizeListGBN = 0;
  int                             nbFlatteningPara = 0, nProducts = 0, nNewProducts = 0, size = -1;
  HRESULT                         hr                              = E_FAIL ;

  char                          * sessionIdent                    = "Session Elec";

  CATListValCATBaseUnknown_var  * phListFlatteningPara            = NULL ;
  CATListValCATBaseUnknown_var  * pListUnkRootProducts            = NULL ;
  CATListValCATBaseUnknown_var  * pNewListUnkRootProducts         = NULL ;

  CATSession                    * pSession                        = NULL ; // To be Deleted
  CATDocument                   * pDoc                            = NULL ; // To be Removed by calling CATDocumentServices::Remove()
  CATDocument                   * pNewDoc                         = NULL ; // To be Removed by calling CATDocumentServices::Remove()

  CATIEleDocServices            * pIEleDocServices                = NULL ; // To be Released
  CATIEleDocServices            * pINewEleDocServices             = NULL ; // To be Released
  CATIDocRoots                  * pIDocRootsOnDoc                 = NULL ; // To be Released
  CATIDocRoots                  * pINewDocRootsOnDoc              = NULL ; // To be Released

  CATIProduct                   * pIRootProduct                   = NULL ; // To be Released
  CATIProduct                   * pINewRootProduct                = NULL ; // To be Released

  CATBaseUnknown_var              hUnkFlatteningPara ;
  CATBaseUnknown_var              hUnkRootProd ;
  CATBaseUnknown_var              hUnkNewRootProd ;
  
  CATBaseUnknown                * pIUnkGBN                        = NULL ;  
  CATLISTP(CATBaseUnknown)        ListOfHarnessGBNs;
  CATLISTP(CATBaseUnknown)      * pListOfExtractedGBNs            = NULL ;
  CATString                     * extractOption                   = NULL ; // To be Deleted
  CATIEhfFlatteningParameters   * pIEhfCreateFlattenPara          = NULL ; // To be Released
  CATIEhfFlatteningParameters   * pIFlatteningPara                = NULL ; // To be Released  
  CATIEhfFlattenManager         * pIExtract                       = NULL ;
  CATIEhfEnvironment            * pINewEhfEnvironment             = NULL ; // To be Released
  CATBaseUnknown                * pIUnkListElem                   = NULL ;

  CATString temp = argv[2];
  CATString tempN ("N");
  CATString tempS ("S");

  // For Setting FlatteningParameters
  //---------------------------------
  CATUnicodeString     setName       ("FlattenPara");
  CATString            setAlgoMode   ("Coarse");
  CATString            setAngleMode  ("Regular");
  CATString            setBNSType    ("AllSegments");
  CATBoolean           setMoveIntermediatePt      = TRUE ;

  // For Setting FlatteningParameters
  //---------------------------------

  //ensure that the input filename and the Extract option
  //i.e. 'N': for "ExtractWithNewForm"
  //     'S': for "ExtractWithSynchro"
  //exists in the arguments
  if ( 3 > argc ) 
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
  if( 0 == nProducts)
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

  // --- Creating new Document and flattening parameters
  // -------------------------------------------------------------------------
  // - Open a new document
  // -------------------------------------------------------------------------
  hr = CATDocumentServices::New("Product", pNewDoc);
  if ( ( NULL == pNewDoc )|| ( FAILED(hr) ) )
  {
    retCode = 11; 
    goto EscapeWay;
  }

  hr = pNewDoc->QueryInterface(IID_CATIEleDocServices,(void**)&pINewEleDocServices );
  if ( FAILED(hr) )
  {
    retCode = 12; 
    goto EscapeWay;
  }

  hr = pINewEleDocServices->Initialize();
  if ( FAILED(hr) )
  {
    retCode = 13; 
    goto EscapeWay;
  }

  hr = pNewDoc->QueryInterface(IID_CATIDocRoots, (void**)(&pINewDocRootsOnDoc));
  if(FAILED(hr))
  {
    retCode = 14;
    goto EscapeWay;
  }

  // Get the root product which is the first element of root elements
  pNewListUnkRootProducts = pINewDocRootsOnDoc->GiveDocRoots();
  if(NULL == pNewListUnkRootProducts)
  {
    retCode = 15;
    goto EscapeWay;
  }

  nNewProducts = pNewListUnkRootProducts->Size();
  if( 0 >= nNewProducts)
  {
    retCode = 16;
    goto EscapeWay;
  }

  hUnkNewRootProd = (*pNewListUnkRootProducts)[1];
  if(NULL_var == hUnkNewRootProd)
  {
    retCode = 17;
    goto EscapeWay;
  }

  hr = hUnkNewRootProd->QueryInterface(IID_CATIProduct, (void**)(&pINewRootProduct));
  if(FAILED(hr))
  {
    retCode = 18;
    goto EscapeWay;
  }

  hr = pINewRootProduct->QueryInterface(IID_CATIEhfEnvironment,(void**)&pINewEhfEnvironment);
  if ( FAILED(hr) )
  {
    retCode = 19;
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // -Create FlatteningParameters
  // -------------------------------------------------------------------------
  hr = pINewEhfEnvironment->CreateFlatteningParameters(pIEhfCreateFlattenPara);
  if( ( FAILED(hr) ) || ( NULL == pIEhfCreateFlattenPara ) )
  {
    retCode = 20;
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // -Test if the FlatteningParameters can be successfully retrieved
  // -------------------------------------------------------------------------
  hr = pINewEhfEnvironment->GetFlatteningParameters(&phListFlatteningPara);
  if ( ( FAILED(hr) ) || ( NULL == phListFlatteningPara ) )
  {
    retCode = 21;
    goto EscapeWay;
  }

  nbFlatteningPara = phListFlatteningPara->Size();
  if (0 >= nbFlatteningPara)
  {
    retCode = 22; 
    goto EscapeWay;
  }

  hUnkFlatteningPara = (*phListFlatteningPara)[1];
  if (NULL_var == hUnkFlatteningPara)
  {
    retCode = 23; 
    goto EscapeWay;
  }

  hr = hUnkFlatteningPara->QueryInterface(IID_CATIEhfFlatteningParameters, (void **)&pIFlatteningPara);
  if ( FAILED(hr) )
  {
    retCode = 24; 
    goto EscapeWay;
  }

  //Start of Setting FlatteningParameters 
  //-------------------------------------

  hr = pIFlatteningPara->SetName(&setName);
  if ( FAILED(hr) )
  {
    retCode = 25; 
    goto EscapeWay;
  }

  hr = pIFlatteningPara->SetAlgorithmMode(&setAlgoMode);
  if ( FAILED(hr) )
  {
    retCode = 26; 
    goto EscapeWay;
  }

  hr = pIFlatteningPara->SetAngleMode(&setAngleMode);
  if ( FAILED(hr))
  {
    retCode = 27; 
    goto EscapeWay;
  }

  hr = pIFlatteningPara->SetBNSTypeScaledDuringSync(&setBNSType);
  if ( FAILED(hr))
  {
    retCode = 28; 
    goto EscapeWay;
  }

  hr = pIFlatteningPara->SetMoveIntermediatePtDuringSync(&setMoveIntermediatePt);
  if ( FAILED(hr))
  {
    retCode = 29; 
    goto EscapeWay;
  }

  //End of Setting FlatteningParameters 
  //-------------------------------------


  hr = pINewRootProduct->QueryInterface(IID_CATIEhfFlattenManager,(void**)&pIExtract);
  if ( FAILED(hr) )
  {
    retCode = 30;
    goto EscapeWay;
  }

  hr = pIRootProduct->QueryInterface(IID_CATBaseUnknown, (void**)&pIUnkGBN) ;
  if( FAILED(hr) )
  {
    retCode = 31;
    goto EscapeWay;    
  }

  ListOfHarnessGBNs.Append(pIUnkGBN) ;

  extractOption = new CATString();

  if ( temp == tempN )
  {
    (*extractOption) = ("ExtractWithNewFrom");
  }
  else if ( temp == tempS)
  {
    (*extractOption) = ("ExtractWithSynchro");
  }

  hr = pIExtract->ExtractHarness( extractOption, &ListOfHarnessGBNs, pListOfExtractedGBNs);
  if (FAILED( hr))
  {
    retCode = 32;
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
  if (NULL != pINewEleDocServices)
  {
    pINewEleDocServices->Release();
    pINewEleDocServices = NULL;
  }
  if (NULL != pIDocRootsOnDoc)
  { 
    pIDocRootsOnDoc->Release();
    pIDocRootsOnDoc = NULL;
  }
  if (NULL != pINewDocRootsOnDoc)
  { 
    pINewDocRootsOnDoc->Release();
    pINewDocRootsOnDoc = NULL;
  }
  if (NULL != pINewEhfEnvironment)
  { 
    pINewEhfEnvironment->Release();
    pINewEhfEnvironment = NULL;
  }
  if (NULL != pIRootProduct)
  { 
    pIRootProduct->Release();
    pIRootProduct = NULL;
  }
  if (NULL != pINewRootProduct)
  { 
    pINewRootProduct->Release();
    pINewRootProduct = NULL;
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
  if (NULL != pIExtract)
  { 
    pIExtract->Release();
    pIExtract = NULL;
  }
  if (NULL != pIUnkGBN)
  { 
    pIUnkGBN->Release();
    pIUnkGBN = NULL;
  }
  
  //DeletePtr
  if (NULL != pListUnkRootProducts)
  {
    delete pListUnkRootProducts; 
    pListUnkRootProducts =0; 
  }
  if (NULL != extractOption)
  {
    delete extractOption; 
    extractOption =0; 
  }
  if (NULL != pNewListUnkRootProducts)
  {
    delete pNewListUnkRootProducts; 
    pNewListUnkRootProducts =0; 
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

  if( NULL != pNewDoc )
  {
    CATDocumentServices::Remove(*pNewDoc) ;
    pNewDoc = NULL ;
  }

  if( NULL != pListOfExtractedGBNs )
  {
    sizeListGBN = pListOfExtractedGBNs->Size();
    for (index = 1; index <= sizeListGBN; index++)
    {
      pIUnkListElem = (*pListOfExtractedGBNs)[index] ;
      if (NULL != pIUnkListElem)
      { 
        pIUnkListElem->Release();
        pIUnkListElem = NULL;
      }
    }
    pListOfExtractedGBNs->RemoveAll();

    delete pListOfExtractedGBNs ;
  }

  if ( NULL != pSession )
  {
    //from CATSessionServices
    hr = ::Delete_Session(sessionIdent) ;
  }
  
  return retCode;
}


