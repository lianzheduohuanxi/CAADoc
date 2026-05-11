#ifndef CAAEGSMFeaturesSplFactory_H
#define CAAEGSMFeaturesSplFactory_H
// COPYRIGHT Dassault Systemes 2006
//===================================================================
//
// CAAEGSMFeaturesSplFactory.h
// Provide implementation to interface
//    CAAIGSMFeaturesSplFactory
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//   IMPLEMENTATION
//   TIE: CAAIGSMFeaturesSplFactory
//
//===================================================================

#include "CATBaseUnknown.h"

class CAAIGSMSewSkinBasic ; 
class CAAIGSMCircleSweepTg; 
class CATISpecObject;
//-----------------------------------------------------------------------

/**
 * Implement CAAIGSMFeaturesSplFactory on FeatCont.
 */

 class CAAEGSMFeaturesSplFactory: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAEGSMFeaturesSplFactory ();
     virtual ~CAAEGSMFeaturesSplFactory ();

    /**
     * Implements a function from an interface.
     * @see CAATestFw.CAAISewSkinFactory#CreateCombinedCurve
     */
   CAAIGSMSewSkinBasic  *  CreateSewSkinBasic  (CATISpecObject * ipSurfaceToSew  , CATISpecObject * ipSurfaceSupport ) ;

     /**
   * Creates a SewSkin 
   * param ipSurfaceToSew       : the first input Surface
   * param ipSurfaceSupport     : the second  input Surface
   */
    CAAIGSMCircleSweepTg *  CreateCircleSweepTg (  CATISpecObject *ipCurveRef  , CATISpecObject *ipSurfaceSupport , double radius );



  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAEGSMFeaturesSplFactory (CAAEGSMFeaturesSplFactory &);
  CAAEGSMFeaturesSplFactory& operator=(CAAEGSMFeaturesSplFactory&);

};

//-----------------------------------------------------------------------

#endif
