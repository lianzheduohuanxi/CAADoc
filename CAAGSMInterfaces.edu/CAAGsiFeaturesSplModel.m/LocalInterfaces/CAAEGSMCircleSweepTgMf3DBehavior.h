#ifndef CAAEGSMCircleSweepTgMf3DBehavior_H
#define CAAEGSMCircleSweepTgMf3DBehavior_H
// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
// CAAEGSMCircleSweepTgMf3DBehavior.h
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

//-----------------------------------------------------------------------

/**
 * Implement CATIMf3DBehavior and CATIMf3DBehavior2  in CAACircleSweepTg Late type 
 */
class CAAEGSMCircleSweepTgMf3DBehavior: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAEGSMCircleSweepTgMf3DBehavior ();
     virtual ~CAAEGSMCircleSweepTgMf3DBehavior ();

    /**
     * Implements a function from an interface.
     * @see MecModInterfaces.CATIMf3DBehavior#IsASolid
     */
     HRESULT IsASolid () const ;

    /**
     * Implements a function from an interface.
     * @see MecModInterfaces.CATIMf3DBehavior#IsAShape
     */
     HRESULT IsAShape () const ;

    /**
     * Implements a function from an interface.
     * @see MecModInterfaces.CATIMf3DBehavior#IsADatum
     */
     HRESULT IsADatum () const ;

    /**
     * Implements a function from an interface.
     * @see MecModInterfaces.CATIMf3DBehavior#IsADatum
     */
     HRESULT IsAVolume () const ;



  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAEGSMCircleSweepTgMf3DBehavior (CAAEGSMCircleSweepTgMf3DBehavior &);
  CAAEGSMCircleSweepTgMf3DBehavior& operator=(CAAEGSMCircleSweepTgMf3DBehavior&);

};

//-----------------------------------------------------------------------

#endif
