/**
 * @fullreview MUJ SUW 03:08:22
 * @error MISC Y
 * @error MISC Y
 * @error MISC Y
 * @error UNH Y
 */	
/**
 *
 * @quickReview MHQ SUW 03:09:02
 * @quickReview SPS SUW 03:09:17
 * @quickReview SPS SUW 03:10:14
 * @quickReview SPS SUW 04:09:28
 * @quickReview MYY AKL 04:12:30 // MINC error correction
 * @quickReview VEI AKL 05:09:30 // R17 H/L
 * @quickReview SPS VEI 05:10:27 // Correction of Unix compile error
 * @quickReview SPS VEI 06:01:18 // Removed CATSysMacors
 * @quickReview AKL VEI 06:02:07 // Output params to have reference data type (&)
 * @quickReview AKL DJH 06:06:28 // Test Case for Unit Problem in case of Default Value (CAA MF RIs 542178 542182 542184)
 */

// --------------------------------------------------------
// --------------------------------------------------------
// COPYRIGHT Dassault Systemes 2003
//===================================================================
//
//
// Usage notes: Test of the CAA interface in Ehf
//
//===================================================================
//
//  Aug 2003   SUW
//===================================================================

// - System
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATString.h"
#include "CATBoolean.h"

// --- Mathematics framework
#include "CATMathPlane.h"

// --- KnowledgeInterfaces Framework ---
#include "CATICkeInst.h"

// - ObjectModelerBase
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATIDocRoots.h"
#include "CATSessionServices.h"
#include "CATSession.h"
#include "CATILinkableObject.h"

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

**                =16: If SetPlane() Method of CATIEhfFlatteningParameters Failed.
**                =17: If SetName() Method of CATIEhfFlatteningParameters Failed.
**                =18: If SetAlgorithmMode() Method of CATIEhfFlatteningParameters Failed.
**                =19: If SetAngleMode() Method of CATIEhfFlatteningParameters Failed.
**                =20: If SetMinAngleBetweenBranches() Method of CATIEhfFlatteningParameters Failed.
**                =21: If SetKeepTangents() Method of CATIEhfFlatteningParameters Failed.
**                =22: If SetExtractOnlySupportsInsideGBN() Method of CATIEhfFlatteningParameters Failed.
**                =23: If SetDeviceOrientation() Method of CATIEhfFlatteningParameters Failed.
**                =24: If SetSupportOrientation() Method of CATIEhfFlatteningParameters Failed.
**                =25: If SetApplyScaling() Method of CATIEhfFlatteningParameters Failed.
**                =26: If SetMinNumberOfBNSToApplyScaling() Method of CATIEhfFlatteningParameters Failed.
**                =27: If SetScaleBNSProportionally() Method of CATIEhfFlatteningParameters Failed.
**                =28: If SetLimitedLength() Method of CATIEhfFlatteningParameters Failed.
**                =29: If SetReductionFactor() Method of CATIEhfFlatteningParameters Failed.
**                =30: If SetApplyReductionFactorToWholeBNS() Method of CATIEhfFlatteningParameters Failed.
**                =31: If SetFixedLength() Method of CATIEhfFlatteningParameters Failed.
**                =32: If SetBNSTypeScaledDuringSync() Method of CATIEhfFlatteningParameters Failed.
**                =33: If SetMoveIntermediatePtDuringSync() Method of CATIEhfFlatteningParameters Failed.

**                =34: If GetPlane() Method of CATIEhfFlatteningParameters Failed.
**                =35: If GetName() Method of CATIEhfFlatteningParameters Failed.
**                =36: If GetAlgorithmMode() Method of CATIEhfFlatteningParameters Failed.
**                =37: If GetAngleMode() Method of CATIEhfFlatteningParameters Failed.
**                =38: If GetMinAngleBetweenBranches() Method of CATIEhfFlatteningParameters Failed.
**                =39: If GetKeepTangents() Method of CATIEhfFlatteningParameters Failed.
**                =40: If GetExtractOnlySupportsInsideGBN() Method of CATIEhfFlatteningParameters Failed.
**                =41: If GetDeviceOrientation() Method of CATIEhfFlatteningParameters Failed.
**                =42: If GetSupportOrientation() Method of CATIEhfFlatteningParameters Failed.
**                =43: If GetApplyScaling() Method of CATIEhfFlatteningParameters Failed.
**                =44: If GetMinNumberOfBNSToApplyScaling() Method of CATIEhfFlatteningParameters Failed.
**                =45: If GetScaleBNSProportionally() Method of CATIEhfFlatteningParameters Failed.
**                =46: If GetLimitedLength() Method of CATIEhfFlatteningParameters Failed.
**                =47: If GetReductionFactor() Method of CATIEhfFlatteningParameters Failed.
**                =48: If GetApplyReductionFactorToWholeBNS() Method of CATIEhfFlatteningParameters Failed.
**                =49: If GetFixedLength() Method of CATIEhfFlatteningParameters Failed.
**                =50: If GetBNSTypeScaledDuringSync() Method of CATIEhfFlatteningParameters Failed.
**                =51: If GetMoveIntermediatePtDuringSync() Method of CATIEhfFlatteningParameters Failed.
**                =52: If Default value of LimitedLength is not returned by GetLimitedLength() method.
**                =53: If Default value of FixedLength is not returned by GetFixedLength() method.
**                =54: If Default value of Minimum Angle is not returned by GetMinAngleBetweenBranches() method.

*/
int main (int argc, char **argv)
{

  int                             retCode = 0, index = 0 ;
  int                             nbFlatteningPara = 0, nProducts = 0 ;
  int                             compareBNSType = -1;
  HRESULT                         hr                              = E_FAIL ;

  char                          * sessionIdent                    = "Session Elec";

  CATListValCATBaseUnknown_var  * phListFlatteningPara            = NULL ;
  CATListValCATBaseUnknown_var  * pListUnkRootProducts            = NULL ;

  CATSession                    * pSession                        = NULL ; // To be Deleted
  CATDocument                   * pDoc                            = NULL ; // To be Removed by calling CATDocumentServices::Remove()

  CATIEleDocServices            * pIEleDocServices                = NULL ; // To be Released
  CATIDocRoots                  * pIDocRootsOnDoc                 = NULL ; // To be Released

  CATIProduct                   * pIRootProduct                   = NULL ; // To be Released

  CATBaseUnknown_var              hUnkFlatteningPara ;
  CATBaseUnknown_var              hUnkRootProd ;

  CATIEhfFlatteningParameters   * pIFlatteningPara                = NULL ; // To be Released
  CATIEhfEnvironment            * pIEhfEnvironment                = NULL ; // To be Released

  //FOR SET METHODS
  //CATILinkableObject            * setpActivePlane                 = NULL ; // To be Deleted
  CATUnicodeString              * setpName                        = NULL ; // To be Deleted 
  CATString                     * setpAlgoMode                    = NULL ; // To be Deleted
  CATString                     * setpAngleMode                   = NULL ; // To be Deleted 
  CATBoolean                      setTangentKept                  = TRUE ;
  CATBoolean                      setOnlySupportsInsideGBNExtracted = TRUE ;
  CATString                     * setpDeviceOrientation           = NULL ; // To be Deleted 
  CATString                     * setpSupportOrientation          = NULL ; // To be Deleted
  CATBoolean                      setScalingApplied               = TRUE ;
  CATBoolean                      setBNSScaledProportionally      = TRUE ;
  CATBoolean                      setReductionFactorAppliedToWholeBNS = TRUE ;
  CATString                     * setpBNSType                     = NULL ; // To be Deleted 
  CATBoolean                      setMoveIntermediatePt           = TRUE ;

  //FOR GET METHODS
  CATMathPlane                    getActivePlane ;
  CATUnicodeString                getName ;
  CATString                       getAlgoMode ;
  CATString                       getAngleMode ;
  CATICkeInst                   * getpICkeInstMinAngle            = NULL ; // To be Released
  CATICkeInst                   * getforsetpICkeInstMinAngle      = NULL ; // To be Released
  CATUnicodeString                minAngleDefault;
  CATBoolean                      getTangentKept                  = TRUE ;
  CATBoolean                      getOnlySupportsInsideGBNExtracted = TRUE ;
  CATString                       getDeviceOrientation ;
  CATString                       getSupportOrientation ;
  CATBoolean                      getScalingApplied               = TRUE ;
  CATBoolean                      getBNSScaledProportionally      = TRUE ;
  CATICkeInst                   * getpICkeInstLimitedLength       = NULL ; // To be Released
  CATICkeInst                   * getforsetpICkeInstLimitedLength = NULL ; // To be Released
  CATUnicodeString                limitedLengthDefault;
  CATBoolean                      getReductionFactorAppliedToWholeBNS = TRUE ;
  double                          setReductionFactor              = 0.1 ;
  double                          getReductionFactor              = 0.0 ;
  CATICkeInst                   * getpICkeInstFixedLength         = NULL ; // To be Released
  CATICkeInst                   * getforsetpICkeInstFixedLength   = NULL ; // To be Released
  CATUnicodeString                fixedLengthDefault;
  CATString                       getBNSType ;
  CATBoolean                      getMoveIntermediatePt           = TRUE ;
  int                             setMinNumberOfBNS               = 5 ; 
  int                             getMinNumberOfBNS               = 0 ; 

  int compareName = -1; 
  int compareAlgo = -1;
  int compareAngle = -1;
  int compareDevice = -1;
  int compareOrientation = -1;


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

  /*
  // -------------------------------------------------------------------------
  // - Set an Active Plane
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->SetPlane(setpActivePlane);
  if ( ( FAILED(hr) ) || ( NULL == setpActivePlane ) )
  {
    retCode = 16; 
    goto EscapeWay;
  }*/

  // -------------------------------------------------------------------------
  // - Get an Active Plane
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->GetPlane(getActivePlane);
  if ( FAILED(hr) )
  {
    retCode = 34; 
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Set Name of the flattening parameters
  // -------------------------------------------------------------------------
  setpName = new CATUnicodeString();
  (*setpName) = ("My_FlatPara");

  hr = pIFlatteningPara->SetName(setpName);
  if ( ( FAILED(hr) ) || ( NULL == setpName ) )
  {
    retCode = 17; 
    goto EscapeWay;
  }  

  // -------------------------------------------------------------------------
  // - Get Name of the flattening parameters
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->GetName(getName);
  compareName = getName.Compare("My_FlatPara");

  if( ( FAILED(hr) ) || ( 2 != compareName ) )
  {
    retCode = 35;
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
    retCode = 18; 
    goto EscapeWay;
  }  

  // -------------------------------------------------------------------------
  // - Get Algorithm Mode
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->GetAlgorithmMode(getAlgoMode);
  compareAlgo = getAlgoMode.Compare("Coarse");

  if ( ( FAILED(hr) ) || ( 0 != compareAlgo ) )
  {
    retCode = 36; 
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Set Angle Mode
  // -------------------------------------------------------------------------
  setpAngleMode = new CATString();
  (*setpAngleMode) = ("Regular");

  hr = pIFlatteningPara->SetAngleMode(setpAngleMode);
  if ( ( FAILED(hr) ) || ( NULL == setpAngleMode ) )
  {
    retCode = 19; 
    goto EscapeWay;
  }  

  // -------------------------------------------------------------------------
  // - Get Angle Mode
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->GetAngleMode(getAngleMode);
  compareAngle = getAngleMode.Compare("Regular");

  if ( ( FAILED(hr) ) || ( 0 != compareAngle ))
  {
    retCode = 37; 
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Get Minimum Angle Between Branches
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->GetMinAngleBetweenBranches(getpICkeInstMinAngle);
  if ( ( FAILED(hr) ) || ( NULL == getpICkeInstMinAngle ) )
  {
    retCode = 38; 
    goto EscapeWay;
  }
  else
  {
    minAngleDefault = getpICkeInstMinAngle->Show();
    if( 0 == minAngleDefault.Compare("5deg") )
    {
      retCode = 54;
      goto EscapeWay;
    }
  }


  // -------------------------------------------------------------------------
  // - Set Minimum Angle Between Branches
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->GetMinAngleBetweenBranches(getforsetpICkeInstMinAngle);
  hr = pIFlatteningPara->SetMinAngleBetweenBranches(getforsetpICkeInstMinAngle);
  if( FAILED(hr) )
  {
    retCode = 20; 
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Set whether to keep existing tangents
  // -------------------------------------------------------------------------
  setTangentKept = FALSE;

  hr = pIFlatteningPara->SetKeepTangents(&setTangentKept);
  if ( FAILED(hr))
  {
    retCode = 21; 
    goto EscapeWay;
  }  

  // -------------------------------------------------------------------------
  // - Get whether to keep existing tangents
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->GetKeepTangents(getTangentKept);
  if ( FAILED(hr) || ( setTangentKept != getTangentKept))
  {
    retCode = 39; 
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Set whether to extract supports inside GBN
  // -------------------------------------------------------------------------
  setOnlySupportsInsideGBNExtracted = TRUE;

  hr = pIFlatteningPara->SetExtractOnlySupportsInsideGBN(&setOnlySupportsInsideGBNExtracted);
  if ( FAILED(hr) )
  {
    retCode = 22; 
    goto EscapeWay;
  }  

  // -------------------------------------------------------------------------
  // - Get whether to extract supports inside GBN
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->GetExtractOnlySupportsInsideGBN(getOnlySupportsInsideGBNExtracted);
  if ( FAILED(hr) || ( setOnlySupportsInsideGBNExtracted != getOnlySupportsInsideGBNExtracted ))
  {
    retCode = 40; 
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Set device orientation
  // -------------------------------------------------------------------------
  setpDeviceOrientation = new CATString();
  (*setpDeviceOrientation) = ("Without_Orientation");

  hr = pIFlatteningPara->SetDeviceOrientation(setpDeviceOrientation);
  if ( ( FAILED(hr) ) || ( NULL == setpDeviceOrientation ) )
  {
    retCode = 23; 
    goto EscapeWay;
  } 

  // -------------------------------------------------------------------------
  // - Get device orientation
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->GetDeviceOrientation(getDeviceOrientation);
  compareDevice = getDeviceOrientation.Compare("Without_Orientation");

  if ( ( FAILED(hr) ) || ( 0 != compareDevice ))
  {
    retCode = 41; 
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Set support orientation
  // -------------------------------------------------------------------------
  setpSupportOrientation = new CATString();
  (*setpSupportOrientation) = ("Regular_angle");

  hr = pIFlatteningPara->SetSupportOrientation(setpSupportOrientation);
  if ( ( FAILED(hr) ) || ( NULL == setpSupportOrientation ) )
  {
    retCode = 24; 
    goto EscapeWay;
  }  

  // -------------------------------------------------------------------------
  // - Get support orientation
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->GetSupportOrientation(getSupportOrientation);
  compareOrientation = (getSupportOrientation).Compare("Regular_angle");

  if ( ( FAILED(hr) ) || ( 0 != compareOrientation ))
  {
    retCode = 42; 
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Set is scaling applied
  // -------------------------------------------------------------------------
  setScalingApplied = TRUE;

  hr = pIFlatteningPara->SetApplyScaling(&setScalingApplied);
  if ( FAILED(hr) )
  {
    retCode = 25; 
    goto EscapeWay;
  }  

  // -------------------------------------------------------------------------
  // - Get is scaling applied
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->GetApplyScaling(getScalingApplied);

  if ( FAILED(hr) || ( setScalingApplied != getScalingApplied ))
  {
    retCode = 43; 
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Set minumum number of bundle segments required to apply scaling
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->SetMinNumberOfBNSToApplyScaling(setMinNumberOfBNS);
  if  ( FAILED(hr) ) 
  {
    retCode = 26; 
    goto EscapeWay;
  }  

  // -------------------------------------------------------------------------
  // - Get minumum number of bundle segments required to apply scaling
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->GetMinNumberOfBNSToApplyScaling(getMinNumberOfBNS);
  if  ( FAILED(hr) || ( setMinNumberOfBNS != getMinNumberOfBNS ) ) 
  {
    retCode = 44; 
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Set if bundle segment is scaled proportionally
  // -------------------------------------------------------------------------
  setBNSScaledProportionally = TRUE;

  hr = pIFlatteningPara->SetScaleBNSProportionally(&setBNSScaledProportionally);
  if ( FAILED(hr))
  {
    retCode = 27; 
    goto EscapeWay;
  }  

  // -------------------------------------------------------------------------
  // - Get if bundle segment is scaled proportionally
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->GetScaleBNSProportionally(getBNSScaledProportionally);
  if ( FAILED(hr) || ( setBNSScaledProportionally != getBNSScaledProportionally ))
  {
    retCode = 45; 
    goto EscapeWay;
  }
  
  // -------------------------------------------------------------------------
  // - Set the limited length
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->GetLimitedLength(getforsetpICkeInstLimitedLength);
  hr = pIFlatteningPara->SetLimitedLength(getforsetpICkeInstLimitedLength);
  if ( FAILED(hr) )
  {
    retCode = 28; 
    goto EscapeWay;
  }  
  
  // -------------------------------------------------------------------------
  // - Get the limited length
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->GetLimitedLength(getpICkeInstLimitedLength);
  if ( ( FAILED(hr) ) || ( NULL == getpICkeInstLimitedLength ) )
  {
    retCode = 46; 
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Default value of limited length
  // -------------------------------------------------------------------------
  limitedLengthDefault = getpICkeInstLimitedLength ->Show();
  if( 0 == limitedLengthDefault.Compare("100mm") )
  {
    retCode = 52;
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Set reduction factor
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->SetReductionFactor(setReductionFactor);
  if  ( FAILED(hr) )
  {
    retCode = 29; 
    goto EscapeWay;
  } 

  // -------------------------------------------------------------------------
  // - Get reduction factor
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->GetReductionFactor(getReductionFactor);
  if  ( FAILED(hr) || ( setReductionFactor != getReductionFactor ) )
  {
    retCode = 47; 
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Set if reduction factor is applied to the whole bundle segment
  // -------------------------------------------------------------------------
  setReductionFactorAppliedToWholeBNS = FALSE;

  hr = pIFlatteningPara->SetApplyReductionFactorToWholeBNS(&setReductionFactorAppliedToWholeBNS);
  if( FAILED(hr) )
  {
    retCode = 30;
    goto EscapeWay;
  } 

  // -------------------------------------------------------------------------
  // - Get if reduction factor is applied to the whole bundle segment
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->GetApplyReductionFactorToWholeBNS(getReductionFactorAppliedToWholeBNS);
  if( FAILED(hr) || ( setReductionFactorAppliedToWholeBNS != getReductionFactorAppliedToWholeBNS ))
  {
    retCode = 48; 
    goto EscapeWay;
  }
  
  // -------------------------------------------------------------------------
  // - Set the fixed length
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->GetFixedLength(getforsetpICkeInstFixedLength);
  hr = pIFlatteningPara->SetFixedLength(getforsetpICkeInstFixedLength);
  if ( FAILED(hr) )
  {
    retCode = 31; 
    goto EscapeWay;
  }  
  
  // -------------------------------------------------------------------------
  // - Get the fixed length
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->GetFixedLength(getpICkeInstFixedLength);
  if ( ( FAILED(hr) ) || ( NULL == getpICkeInstFixedLength ) )
  {
    retCode = 49; 
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Default value of fixed length
  // -------------------------------------------------------------------------
  fixedLengthDefault = getpICkeInstFixedLength ->Show();
  if( 0 == fixedLengthDefault.Compare("100mm") )
  {
    retCode = 53; 
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Set bundle segment scaled during sync
  // -------------------------------------------------------------------------
  setpBNSType = new CATString();
  (*setpBNSType) = ("AllSegments");

  hr = pIFlatteningPara->SetBNSTypeScaledDuringSync(setpBNSType);
  if ( ( FAILED(hr) ) || ( NULL == setpBNSType ) )
  {
    retCode = 32; 
    goto EscapeWay;
  }  

  // -------------------------------------------------------------------------
  // - Get bundle segment scaled during sync
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->GetBNSTypeScaledDuringSync(getBNSType);
  compareBNSType = getBNSType.Compare("AllSegments");

  if ( ( FAILED(hr) ) || ( 0 != compareBNSType ))
  {
    retCode = 50; 
    goto EscapeWay;
  }

  // -------------------------------------------------------------------------
  // - Set if intermediate points are moved during sync
  // -------------------------------------------------------------------------
  setMoveIntermediatePt = TRUE;

  hr = pIFlatteningPara->SetMoveIntermediatePtDuringSync(&setMoveIntermediatePt);
  if ( FAILED(hr) )
  {
    retCode = 33; 
    goto EscapeWay;
  }  

  // -------------------------------------------------------------------------
  // - Get if intermediate points are moved during sync
  // -------------------------------------------------------------------------
  hr = pIFlatteningPara->GetMoveIntermediatePtDuringSync(getMoveIntermediatePt);
  if ( FAILED(hr) || ( setMoveIntermediatePt != getMoveIntermediatePt ) )
  {
    retCode = 51; 
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
  if (NULL != getpICkeInstMinAngle)
  {
    getpICkeInstMinAngle->Release();
    getpICkeInstMinAngle = NULL;
  }
  if (NULL != getpICkeInstLimitedLength)
  {
    getpICkeInstLimitedLength->Release();
    getpICkeInstLimitedLength = NULL;
  }
  if (NULL != getpICkeInstFixedLength)
  {
    getpICkeInstFixedLength->Release();
    getpICkeInstFixedLength = NULL;
  }
  if (NULL != getforsetpICkeInstMinAngle)
  {
    getforsetpICkeInstMinAngle->Release();
    getforsetpICkeInstMinAngle = NULL;
  }
  if (NULL != getforsetpICkeInstLimitedLength)
  {
    getforsetpICkeInstLimitedLength->Release();
    getforsetpICkeInstLimitedLength = NULL;
  }
  if (NULL != getforsetpICkeInstFixedLength)
  {
    getforsetpICkeInstFixedLength->Release();
    getforsetpICkeInstFixedLength = NULL;
  }

  //DeletePtr
  /*if (setpActivePlane)
  {
    delete setpActivePlane; 
    setpActivePlane =0; 
  }*/
  if (NULL != setpName)
  {
    delete setpName; 
    setpName =0; 
  }
  if (NULL != setpAlgoMode)
  {
    delete setpAlgoMode; 
    setpAlgoMode =0; 
  }
  if (NULL != setpAngleMode)
  {
    delete setpAngleMode; 
    setpAngleMode =0; 
  }
  if (NULL != setpDeviceOrientation)
  {
    delete setpDeviceOrientation; 
    setpDeviceOrientation =0; 
  }
  if (NULL != setpSupportOrientation)
  {
    delete setpSupportOrientation; 
    setpSupportOrientation =0; 
  }
  if (NULL != setpBNSType)
  {
    delete setpBNSType; 
    setpBNSType =0; 
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



