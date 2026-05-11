#ifndef CAAMmrUpdateProvForExtCont_H
#define CAAMmrUpdateProvForExtCont_H

// COPYRIGHT DASSAULT SYSTEMES 2007
//=================================================================================
//  Abstract of the class:
//  ----------------------
//
//  CAAMmrUpdateProvForExtCont: CATIUpdateProviderExtension
//  Extends UpdateMechanism to FeatureExtensions Contained in MmrDataExtensionCont
//=================================================================================

#include "CATIUpdateProvider.h"

class CATIContainer;
class CATBaseUnknown;
class CATIDomain;

class CAAMmrUpdateProvForExtCont: public CATIUpdateProvider
{
    // Used in conjunction with CATImplementClass in the .cpp file
    CATDeclareClass;

public:
    //////////////////////////////
    // Constructor - Destructor //
    //////////////////////////////
    CAAMmrUpdateProvForExtCont();
    virtual ~CAAMmrUpdateProvForExtCont();

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
  int Update(CATBaseUnknown* iWorkingObj, CATIDomain_var iDomain = NULL_var);
  
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
  
private:

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
};
#endif
