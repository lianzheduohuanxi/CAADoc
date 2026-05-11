#ifndef CAAEGSMCircleSweepTgBuild_H
#define CAAEGSMCircleSweepTgBuild_H
// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
// CAAEGSMCircleSweepTgBuild.h
// Provide implementation to interface
//    CATIBuild
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//   IMPLEMENTATION
//   TIE: CATIBuild
//===================================================================

#include "CATBaseUnknown.h"
#include "CAAGSMBuildBasic.h" 
//-----------------------------------------------------------------------

/**
 * Implement CATIBuild on CAACircleSweepTg LateType. 
 */
class CAAEGSMCircleSweepTgBuild: public CAAGSMBuildBasic
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAEGSMCircleSweepTgBuild ();
     virtual ~CAAEGSMCircleSweepTgBuild ();

    /**
     * Implements a function from an interface.
     * @see ObjectSpecsModeler.CATIBuild#Build
     */
     HRESULT Build () ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAEGSMCircleSweepTgBuild (CAAEGSMCircleSweepTgBuild &);
  CAAEGSMCircleSweepTgBuild& operator=(CAAEGSMCircleSweepTgBuild&);

};

//-----------------------------------------------------------------------

#endif
