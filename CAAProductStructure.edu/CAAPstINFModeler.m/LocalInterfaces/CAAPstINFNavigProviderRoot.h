// COPYRIGHT DASSAULT SYSTEMES 2002

#ifndef CAAPstINFNavigProviderRoot_H
#define CAAPstINFNavigProviderRoot_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Implementation of the CATINavigProvider interface for a root object, serving as
//  the provider implementation for the inclusion of a user-defined root feature,
//  "CAAPstINFRoot", in the navigation tree under the Product root. 
//
//  Illustrates programming the GetChildren method of the CATINavigProvider interface 
//  of the ProductStructure framework.
//
//  Inheritance:
//  ------------
//            
//  CATBaseUnknown (System Framework)  
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"
#include "CATListOfCATBaseUnknown.h"

class CAAPstINFNavigProviderRoot: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors
  // ------------------------------------
  CAAPstINFNavigProviderRoot ();
  virtual ~CAAPstINFNavigProviderRoot ();

  // Returns a pointer to the "CAAPstINFRoot" feature if the caller is the Product root.
  HRESULT GetChildren(CATBaseUnknown *ipObj, CATLISTP(CATBaseUnknown) **opListChildren); 

  private:

  // Copy constructor and assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  // -----------------------------------
  CAAPstINFNavigProviderRoot (CAAPstINFNavigProviderRoot&);
  CAAPstINFNavigProviderRoot& operator=(CAAPstINFNavigProviderRoot&);
	
};

//-----------------------------------------------------------------------

#endif

