#ifndef CAAEGSMCircleSweepTg_H
#define CAAEGSMCircleSweepTg_H
// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
// CAAEGSMCircleSweepTg.h
// Provide implementation to interface
//    CAAIGSMCircleSweepTg
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//   IMPLEMENTATION
//   TIE: CAAIGSMCircleSweepTg
//===================================================================


#include "CATBaseUnknown.h"
#include "CATISpecObject.h"

//-----------------------------------------------------------------------

/**
 * Implement CAAIGSMCircleSweepTg on CAACircleSweepTg LateType. 
 */
class CAAEGSMCircleSweepTg: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAEGSMCircleSweepTg ();
     virtual ~CAAEGSMCircleSweepTg ();

    /**
     * Implements a function from an interface.
     * @see CAAGSMFeatureSpl.tst.CAAIGSMCircleSweepTg#SetCurveRef
     */
     HRESULT SetCurveRef (const CATISpecObject_var  ipCurveRef  ) ;

    /**
     * Implements a function from an interface.
     * @see CAAGSMFeatureSpl.tst.CAAIGSMCircleSweepTg#GetCurveRef
     */
     HRESULT GetCurveRef (CATISpecObject_var & ipCurveRef  ) ;

    /**
     * Implements a function from an interface.
     * @see CAAGSMFeatureSpl.tst.CAAIGSMCircleSweepTg#SetSurfaceSupport
     */
     HRESULT SetSurfaceSupport (const CATISpecObject_var  ipSupport  ) ;

    /**
     * Implements a function from an interface.
     * @see CAAGSMFeatureSpl.tst.CAAIGSMCircleSweepTg#GetSurfaceSupport
     */
     HRESULT GetSurfaceSupport (CATISpecObject_var & ipSupport  ) ;

    /**
     * Implements a function from an interface.
     * @see CAAGSMFeatureSpl.tst.CAAIGSMCircleSweepTg#SetRadius
     */
     HRESULT SetRadius (const double  iRadius ) ;

    /**
     * Implements a function from an interface.
     * @see CAAGSMFeatureSpl.tst.CAAIGSMCircleSweepTg#GetRadius
     */
     HRESULT GetRadius (double &  oRadius ) ;

    /**
     * Implements a function from an interface.
     * @see CAAGSMFeatureSpl.tst.CAAIGSMCircleSweepTg#SetSolution
     */
     HRESULT SetSolution (const int  iSolution ) ;

    /**
     * Implements a function from an interface.
     * @see CAAGSMFeatureSpl.tst.CAAIGSMCircleSweepTg#GetSolution
     */
     HRESULT GetSolution (int &  oSolution ) ;

 /**
     * Implements a function from an interface.
     * @see CAAGSMFeatureSpl.tst.CAAIGSMCircleSweepTg#SetTrimMode
     */
     HRESULT SetTrimMode (const int  iTrimMode ) ;

    /**
     * Implements a function from an interface.
     * @see CAAGSMFeatureSpl.tst.CAAIGSMCircleSweepTg#GetTrimMode
     */
     HRESULT GetTrimMode (int &  oTrimMode ) ;

  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAEGSMCircleSweepTg (CAAEGSMCircleSweepTg &);
  CAAEGSMCircleSweepTg& operator=(CAAEGSMCircleSweepTg&);

};

//-----------------------------------------------------------------------

#endif
