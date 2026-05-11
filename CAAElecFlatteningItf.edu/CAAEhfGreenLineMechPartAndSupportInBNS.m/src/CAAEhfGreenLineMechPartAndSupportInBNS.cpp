/**
 * @fullreview DJH VEI 07:01:15
 */

 /**
 * @quickReview GLY 07:01:25
 */

// --------------------------------------------------------
// --------------------------------------------------------
// COPYRIGHT Dassault Systemes 2007
//===================================================================
//
//
// Usage notes: Test of the CAA interface in Ehf
//
//===================================================================
//
//  January 2007   VEI
//===================================================================

// --- ObjectModelerBase ---
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
#include "CATIEhfBundleSegmentLink.h"

// --- ElecHarnessItf ---
/*
#include "CATIEhiGeoBundle.h"
#include "CATIEhiBundleSegment.h"
*/

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
**                =19: If QueryInterface to CATIEhiGeoBundle Failed.
**                =20: If ListBundleSegments of CATIEhiGeoBundle Failed.
**                =21: If list of ListBundleSegments is less than equal to zero.
**                =22: If CATBaseUnknown_var is NULL_var.
**                =23: If QueryInterface to CATIEhiBundleSegment Failed.
**                =24: If QueryInterface to CATIEhfBundleSegmentLink Failed.
**                =25: If ListLinkedMechanicalParts of CATIEhfBundleSegmentLink Failed.
**                =26: If CATBaseUnknown_var is NULL_var.
**                =27: If QueryInterface to CATIEhiBundleSegment Failed.
**                =28: If QueryInterface to CATIEhfBundleSegmentLink Failed.
**                =29: If ListLinkedMechanicalParts of CATIEhfBundleSegmentLink Failed.
**                =30: If CATBaseUnknown_var is NULL_var.
**                =31: If QueryInterface to CATIEhiBundleSegment Failed.
**                =32: If QueryInterface to CATIEhfBundleSegmentLink Failed.
**                =33: If ListLinkedSupports of CATIEhfBundleSegmentLink Failed.
*/

int main (int argc, char **argv)
{

  HRESULT                         hr                              = E_FAIL ;

  int                             retCode          = 0 ;
  int                             nbFlatteningPara = 0, nProducts = 0 ;
  int                             numGBN                          = -1 ;
  int                             numBNS                          = -1 ;  
  
/*
  char                          * sessionIdent                    = "Session Elec";

  CATListValCATBaseUnknown_var  * phListFlatteningPara             = NULL ;
  CATListValCATBaseUnknown_var  * phListUnkRootProducts            = NULL ;

  CATSession                    * pSession                        = NULL ;
  CATDocument                   * pDoc                            = NULL ; // To be Removed by calling CATDocumentServices::Remove()

  CATIEleDocServices            * pIEleDocServices                = NULL ;
  CATIDocRoots                  * pIDocRootsOnDoc                 = NULL ;
  CATIEhfFlatteningParameters   * pIFlatteningPara                = NULL ;
  CATIEhfEnvironment            * pIEhfEnvironment                = NULL ;
  CATIProduct                   * pIRootProduct                   = NULL ;
 

  CATIEhiGeoBundle              * pIEhiGBN                        = NULL ;
  CATIEhiBundleSegment          * pIEhiBNS                        = NULL ;
  CATIEhfBundleSegmentLink      * pIEhfBundleSegmentLink          = NULL ;

  CATListValCATBaseUnknown_var  * phUnkListChildren               = NULL ;
  CATListValCATBaseUnknown_var  * phUnkListBNS                    = NULL ;
  CATListValCATBaseUnknown_var  * phUnkListGreenLineOneMechParts  = NULL ;
  CATListValCATBaseUnknown_var  * phUnkListGreenLineTwoMechParts  = NULL ;
  CATListValCATBaseUnknown_var  * phUnkListGreenLineSupports      = NULL ;

  CATBaseUnknown_var              hUnkFlatteningPara ;
  CATBaseUnknown_var              hUnkRootProd ;
  CATBaseUnknown_var              hUnkListElem ;
  CATBaseUnknown_var              hUnkBNSWithOneMechPart ;
  CATBaseUnknown_var              hUnkBNSWithTwoMechPart ;
  CATBaseUnknown_var              hUnkBNSWithOneSupport ;

  //Model:-
  //The model contains one Extracted Root Product("Extract") Which contains a GBN("Geometrical Bundle1_Ehf.1")
  //The MultiBranchble has 2 Branchables viz:-
  //Branchable.1
  //     |
  //      ->Bundle Segment.1 (Contains ONE Mech Part with Green Lines)
  //     |
  //      ->Bundle Segment.4 (Contains ONE Support with Green Lines)
  //     |
  //      ->Bundle Segment.2 (Contains NO Support or Mech Parts with Green Lines)
  //Branchable.2
  //     |
  //      ->Bundle Segment.3 (Contains TWO Mech Parts with Green Lines)



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

  // -------------------------------------------------------------------------
  // - Get the root product which is the first element of root elements
  // -------------------------------------------------------------------------
  phListUnkRootProducts = pIDocRootsOnDoc->GiveDocRoots();
  if(NULL == phListUnkRootProducts)
  {
    retCode = 5;
    goto EscapeWay;
  }

  nProducts = phListUnkRootProducts->Size();
  if( 0 == nProducts)
  {
    retCode = 6;
    goto EscapeWay;
  }

  hUnkRootProd = (*phListUnkRootProducts)[1];
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

  // -------------------------------------------------------------------------
  // - Initialise Electrical Environment
  // -------------------------------------------------------------------------
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

  // -------------------------------------------------------------------------
  // - QI for CATIEhfEnvironment
  // -------------------------------------------------------------------------
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

  // -------------------------------------------------------------------------
  // - QI for CATIEhfFlatteningParameters
  // -------------------------------------------------------------------------
  hr = hUnkFlatteningPara->QueryInterface(IID_CATIEhfFlatteningParameters, (void **)&pIFlatteningPara);
  if ( FAILED(hr) )
  {
    retCode = 15;
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Get All "CATIEhiGeoBundle"
  // -------------------------------------------------------------------------
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

  // -------------------------------------------------------------------------
  // - QI for CATIEhiGeoBundle
  // -------------------------------------------------------------------------
  hr = hUnkListElem->QueryInterface(IID_CATIEhiGeoBundle, (void**)(&pIEhiGBN));
  if(FAILED(hr))
  {
    retCode = 19;
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - List All BNS in the GBN
  // -------------------------------------------------------------------------
  hr = pIEhiGBN->ListBundleSegments(&phUnkListBNS);
  if( NULL == phUnkListBNS )
  {
    retCode = 20;
    goto EscapeWay;
  }

  numBNS = phUnkListBNS->Size();
  if( 0 >= numBNS )
  {
    retCode = 21;
    goto EscapeWay;    
  }

  // -------------------------------------------------------------------------
  // - Test for BNS with One Green Line MechPart "Bundle Segment.1"
  // -------------------------------------------------------------------------
  hUnkBNSWithOneMechPart = (*phUnkListBNS)[1] ;
  if( NULL_var == hUnkBNSWithOneMechPart )
  {
    retCode = 22;
    goto EscapeWay;
  }

  hr = hUnkBNSWithOneMechPart->QueryInterface(IID_CATIEhiBundleSegment, (void**)(&pIEhiBNS));
  if(FAILED(hr))
  {
    retCode = 23;
    goto EscapeWay;
  }

  hr = pIEhiBNS->QueryInterface(IID_CATIEhfBundleSegmentLink, (void**)(&pIEhfBundleSegmentLink));
  if(FAILED(hr))
  {
    retCode = 24;
    goto EscapeWay;
  }

  hr = pIEhfBundleSegmentLink->ListLinkedMechanicalParts(phUnkListGreenLineOneMechParts);
  if( ( FAILED(hr) ) || ( NULL == phUnkListGreenLineOneMechParts ) || ( 1 != phUnkListGreenLineOneMechParts->Size() ) )
  {
    retCode = 25;
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Test for BNS with Two Green Line MechParts "Bundle Segment.3"
  // -------------------------------------------------------------------------
  hUnkBNSWithTwoMechPart = (*phUnkListBNS)[4] ;
  if( NULL_var == hUnkBNSWithTwoMechPart )
  {
    retCode = 26;
    goto EscapeWay;
  }

  if (NULL != pIEhiBNS)
  { 
    pIEhiBNS->Release();
    pIEhiBNS = NULL;
  }

  hr = hUnkBNSWithTwoMechPart->QueryInterface(IID_CATIEhiBundleSegment, (void**)(&pIEhiBNS));
  if(FAILED(hr))
  {
    retCode = 27;
    goto EscapeWay;
  }

  if (NULL != pIEhfBundleSegmentLink)
  { 
    pIEhfBundleSegmentLink->Release();
    pIEhfBundleSegmentLink = NULL;
  }

  hr = pIEhiBNS->QueryInterface(IID_CATIEhfBundleSegmentLink, (void**)(&pIEhfBundleSegmentLink));
  if(FAILED(hr))
  {
    retCode = 28;
    goto EscapeWay;
  }

  hr = pIEhfBundleSegmentLink->ListLinkedMechanicalParts(phUnkListGreenLineTwoMechParts);
  if( ( FAILED(hr) ) || ( NULL == phUnkListGreenLineTwoMechParts ) || ( 2 != phUnkListGreenLineTwoMechParts->Size() ) )
  {
    retCode = 29;
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Test for BNS with one Green Line Support "Bundle Segment.4"
  // -------------------------------------------------------------------------
  hUnkBNSWithOneSupport = (*phUnkListBNS)[2] ;
  if( NULL_var == hUnkBNSWithOneSupport )
  {
    retCode = 30;
    goto EscapeWay;
  }

  if (NULL != pIEhiBNS)
  { 
    pIEhiBNS->Release();
    pIEhiBNS = NULL;
  }

  hr = hUnkBNSWithOneSupport->QueryInterface(IID_CATIEhiBundleSegment, (void**)(&pIEhiBNS));
  if(FAILED(hr))
  {
    retCode = 31;
    goto EscapeWay;
  }

  if (NULL != pIEhfBundleSegmentLink)
  { 
    pIEhfBundleSegmentLink->Release();
    pIEhfBundleSegmentLink = NULL;
  }

  hr = pIEhiBNS->QueryInterface(IID_CATIEhfBundleSegmentLink, (void**)(&pIEhfBundleSegmentLink));
  if(FAILED(hr))
  {
    retCode = 32;
    goto EscapeWay;
  }

  hr = pIEhfBundleSegmentLink->ListLinkedSupports(phUnkListGreenLineSupports);
  if( ( FAILED(hr) ) || ( NULL == phUnkListGreenLineSupports ) || ( 1 != phUnkListGreenLineSupports->Size() ) )
  {
    retCode = 33;
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
  if (NULL != pIEhiGBN)
  { 
    pIEhiGBN->Release();
    pIEhiGBN = NULL;
  }
  if (NULL != pIEhiBNS)
  { 
    pIEhiBNS->Release();
    pIEhiBNS = NULL;
  }
  if (NULL != pIEhfBundleSegmentLink)
  { 
    pIEhfBundleSegmentLink->Release();
    pIEhfBundleSegmentLink = NULL;
  }
  if (NULL != pIFlatteningPara)
  { 
    pIFlatteningPara->Release();
    pIFlatteningPara = NULL;
  }

  //DeletePtr
  if (NULL != phUnkListChildren)
  {
    delete phUnkListChildren; 
    phUnkListChildren =0; 
  }
  if (NULL != phUnkListBNS)
  {
    delete phUnkListBNS; 
    phUnkListBNS =0; 
  }
  if (NULL != phListUnkRootProducts)
  {
    delete phListUnkRootProducts; 
    phListUnkRootProducts =0; 
  }
  if (NULL != phListFlatteningPara)
  {
    delete phListFlatteningPara; 
    phListFlatteningPara =0; 
  }
  if (NULL != phUnkListGreenLineOneMechParts)
  {
    delete phUnkListGreenLineOneMechParts; 
    phUnkListGreenLineOneMechParts =0; 
  }
  if (NULL != phUnkListGreenLineTwoMechParts)
  {
    delete phUnkListGreenLineTwoMechParts; 
    phUnkListGreenLineTwoMechParts =0; 
  }
  if (NULL != phUnkListGreenLineSupports)
  {
    delete phUnkListGreenLineSupports; 
    phUnkListGreenLineSupports =0; 
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
  */

  return retCode;
}



