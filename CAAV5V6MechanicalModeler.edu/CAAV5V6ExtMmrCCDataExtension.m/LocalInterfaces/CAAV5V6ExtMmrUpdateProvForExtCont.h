#ifndef CAAV5V6ExtMmrUpdateProvForExtCont_H
#define CAAV5V6ExtMmrUpdateProvForExtCont_H

// COPYRIGHT DASSAULT SYSTEMES 2012
//=======================================================================================
//  Abstract of the class:
//  ----------------------
//
//  CAAV5V6ExtMmrUpdateProvForExtCont: CATIUpdateProviderExtension
//  Extends UpdateMechanism to FeatureExtensions Contained in V5V6ExtMmrDataExtensionCont
//=======================================================================================

// ObjectSpecsModeler Framework in V5
// DataCommonProtocolUse Framework in V6
#include "CATIUpdateProvider.h"
#include "CATIAV5Level.h"

class CATBaseUnknown;
class CATIContainer;

class CAAV5V6ExtMmrUpdateProvForExtCont: public CATIUpdateProvider
{
    // Used in conjunction with CATImplementClass in the .cpp file
    CATDeclareClass;

public:
    //////////////////////////////
    // Constructor - Destructor //
    //////////////////////////////
    CAAV5V6ExtMmrUpdateProvForExtCont();
    virtual ~CAAV5V6ExtMmrUpdateProvForExtCont();

  /**  
  * Rebuilds the feature ( generate the result ).
  * <b> Note: </b> The default update mechanism detects all features that have been modified upstream from a 
  * feature, rebuilds all the feature impacting the updated feature, and finally rebuild
  * the final feature.
  * @param iWorkingObj
  *     The base feature object.
  * @param iDomain
  *     The application domain of the update ( not used ).
  */
  int Update(CATBaseUnknown* iWorkingObj, CATBaseUnknown_var iDomain = NULL_var);
  
#ifdef CATIAV5R23
//============================================== 
// V5 only
//==============================================
 /**
  * Returns the status of the object concerning the update mechanism.
  * @param iWorkingObj
  *     The base feature object.
  * @param iDomain
  *     The application domain of the update ( not used ).
  * @return 
  *    TRUE : the object has been updated.
  *    FALSE : the object has to be updated.
  */
  CATBoolean IsUpToDate(CATBaseUnknown* iWorkingObj, CATIDomain_var iDomain=NULL_var) const;
  
  /**
  * Modifies the flag of the updatable object.
  * @param iWorkingObj
  *     The base feature object.
  * @param  iFlag
  *       TRUE : the object has just been updated
  *       FALSE: the object needs to be rebuild
  */
  void SetUpToDate(CATBaseUnknown* iWorkingObj, boolean iFlag );
  
  /**
  * Forces an updatable object to be ignored by the update mechanism.
  * @param iWorkingObj
  *     The base feature object.
  * @return 
  *     0 : default implementation, always active.
  */
  int IsInactive(CATBaseUnknown* iWorkingObj) const;
#endif

private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAV5V6ExtMmrUpdateProvForExtCont (CAAV5V6ExtMmrUpdateProvForExtCont &);
  CAAV5V6ExtMmrUpdateProvForExtCont& operator=(CAAV5V6ExtMmrUpdateProvForExtCont&);

//#ifdef CATIAV5R23
   /**
  * Service to retrieve the Mmr3DDataExtensionCont
  * @param iWorkingObj
  *     The base feature object.
  * @param ioMmrDataCont
  *     The Mmr3DDataContainer.
  * @returns 
  *     S_OK if Container is found
  *     E_FAIL otherwise
  */
  static HRESULT GetMmrDataExtension(CATBaseUnknown* iWorkingObj, CATIContainer ** ioMmrDataCont);
//#endif

};
#endif
