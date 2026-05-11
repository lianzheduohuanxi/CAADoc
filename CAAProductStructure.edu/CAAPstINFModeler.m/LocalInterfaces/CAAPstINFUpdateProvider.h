// COPYRIGHT DASSAULT SYSTEMES 2002

#ifndef CAAPstINFUpdateProvider_H
#define CAAPstINFUpdateProvider_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Implementation of the CATIUpdateProvider interface for a line or wire object,
//  serving as the provider implementation for the inclusion of a user-defined line
//  or wire feature, "CAAPstINFLine" or "CAAPstINFWire", in the update process of the
//  Product root. 
//
//  Illustrates programming the Update method of the CATIUpdateProvider interface 
//  of the ObjectSpecsModeler framework.
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

// ObjectModelerBase Framework
#include "CATIDomain.h"

class CAAPstINFUpdateProvider: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors
  // -------------------------------------
  CAAPstINFUpdateProvider ();
  virtual ~CAAPstINFUpdateProvider ();

  // Updates the "CAAPstINFLine" or "CAAPstINFWire" feature. 
  int Update(CATBaseUnknown *ipObj, CATIDomain_var ispDomain = NULL_var); 

  // Not implemented.
  CATBoolean IsUpToDate(CATBaseUnknown *ipObj, CATIDomain_var ispDomain = NULL_var);

  // Not implemented.
  void SetUpToDate(CATBaseUnknown *ipObj, CATBoolean iFlag);

  // Not implemented.
  int IsInactive(CATBaseUnknown *ipObj); 

  private:

  // Copy constructor and assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAPstINFUpdateProvider (CAAPstINFUpdateProvider&);
  CAAPstINFUpdateProvider& operator=(CAAPstINFUpdateProvider&);
	
};

//-----------------------------------------------------------------------

#endif

