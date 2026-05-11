#ifndef CAAEGSMSewSkinBasicMf3DBehavior_H
#define CAAEGSMSewSkinBasicMf3DBehavior_H
// COPYRIGHT Dassault Systemes 2003
//===================================================================
//
// CAAEGSMSewSkinBasicMf3DBehavior.h
// Provide implementation to interface
//    CATIMf3DBehavior CATIMf3DBehavior2 
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//   IMPLEMENTATION
//   TIE: CATIMf3DBehavior CATIMf3DBehavior2 
//===================================================================


#include "CATBaseUnknown.h"

/**
 * Implement CATIMf3DBehavior and CATIMf3DBehavior2  on CAASewSkinBasic LateType. 
 */
class CAAEGSMSewSkinBasicMf3DBehavior: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAEGSMSewSkinBasicMf3DBehavior ();
     virtual ~CAAEGSMSewSkinBasicMf3DBehavior ();

    /**
     * Implements a function from an interface.
     * @see MechanicalModeler.CATIMf3DBehavior#IsASolid
     */
     HRESULT IsASolid () const ;

    /**
     * Implements a function from an interface.
     * @see MechanicalModeler.CATIMf3DBehavior#IsAShape
     */
     HRESULT IsAShape () const ;

    /**
     * Implements a function from an interface.
     * @see MechanicalModeler.CATIMf3DBehavior#IsADatum
     */
     HRESULT IsADatum () const ;

    /**
     * Implements a function from an interface.
     * @see MechanicalModeler.CATIMf3DBehavior2#IsAVolume
     */
     HRESULT IsAVolume () const ;

  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAEGSMSewSkinBasicMf3DBehavior (CAAEGSMSewSkinBasicMf3DBehavior &);
  CAAEGSMSewSkinBasicMf3DBehavior& operator=(CAAEGSMSewSkinBasicMf3DBehavior&);

};

//-----------------------------------------------------------------------

#endif
