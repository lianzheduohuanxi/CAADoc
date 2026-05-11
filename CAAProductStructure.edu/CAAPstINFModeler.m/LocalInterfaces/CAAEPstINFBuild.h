// COPYRIGHT DASSAULT SYSTEMES 2002

#ifndef CAAEPstINFBuild_H
#define CAAEPstINFBuild_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAPstINFLine and CAAPstINFWire components,
//  implementing the CATIBuild interface to enable the re-construction of the line
//  or wire after the modification of any of the two points defining them.
//
//  Illustrates programming the Build of an object by implementing the CATIBuild
//  interface of the ObjectSpecsModeler framework.
//
//===========================================================================
//  Inheritance:
//  ------------
//            
//  CATBaseUnknown (System Framework) 
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"

class CAAEPstINFBuild: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
  CAAEPstINFBuild();
  virtual ~CAAEPstINFBuild();

  // Construct the line's or wire's representation
  HRESULT Build();

  private:
	// Copy constructor and equal operator, not implemented
    // Set as private to prevent the compiler from automatically creating them as public.
    // -------------------------------------------------------------------
    CAAEPstINFBuild (CAAEPstINFBuild &);
    CAAEPstINFBuild& operator=(CAAEPstINFBuild&);
    
};
#endif
