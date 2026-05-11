#ifndef CAAEGSMSewSkinBasicBuild_H
#define CAAEGSMSewSkinBasicBuild_H
// COPYRIGHT Dassault Systemes 2006
//===================================================================
//
// CAAEGSMSewSkinBasicBuild.h
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
 * Implement CATIBuild on CAASewSkinBasic LateType. 
 */
class CAAEGSMSewSkinBasicBuild: public CAAGSMBuildBasic
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAEGSMSewSkinBasicBuild ();
     virtual ~CAAEGSMSewSkinBasicBuild ();

    /**
     * Implements a function from an interface.
     * @see ObjectSpecsModeler.CATIBuild#Build
     */
     HRESULT Build () ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAEGSMSewSkinBasicBuild (CAAEGSMSewSkinBasicBuild &);
  CAAEGSMSewSkinBasicBuild& operator=(CAAEGSMSewSkinBasicBuild&);

};

//-----------------------------------------------------------------------

#endif
