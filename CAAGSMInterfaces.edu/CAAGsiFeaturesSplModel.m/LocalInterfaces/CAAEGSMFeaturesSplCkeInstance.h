#ifndef CAAEGSMFeaturesSplCkeInstance_H
#define CAAEGSMFeaturesSplCkeInstance_H
// COPYRIGHT Dassault Systemes 2006
//===================================================================
//
// CAAEGSMFeaturesSplCkeInstance.h
// Provide implementation to interface
//    CATIInstance and CATICkeFeature
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//   IMPLEMENTATION
//   TIE:  CATICkeFeature
//
//===================================================================
#include "CATKweInstanceAdapter.h"
#include "CATICkeType.h"

//-----------------------------------------------------------------------

/**
 * Implement CATIInstance et CATICkeFeature on CAASewskinBasic and CAACircleSweepTg LateType. 
 */
class CAAEGSMFeaturesSplCkeInstance: public CATKweInstanceAdapter

{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAEGSMFeaturesSplCkeInstance ();
     virtual ~CAAEGSMFeaturesSplCkeInstance ();


     /**
     * Implements a function from an interface.
     * @href CATICkeFeature#GetType
     */
     CATICkeType_var  GetType( ) const ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAEGSMFeaturesSplCkeInstance (CAAEGSMFeaturesSplCkeInstance &);
  CAAEGSMFeaturesSplCkeInstance& operator=(CAAEGSMFeaturesSplCkeInstance&);

};

//-----------------------------------------------------------------------

#endif
