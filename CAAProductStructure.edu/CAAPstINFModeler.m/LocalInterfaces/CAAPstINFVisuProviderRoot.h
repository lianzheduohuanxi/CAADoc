// COPYRIGHT DASSAULT SYSTEMES 2002

#ifndef CAAPstINFVisuProviderRoot_H
#define CAAPstINFVisuProviderRoot_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Implementation of the CATI3DVisuProvider interface for a user-defined root object,
//  "CAAPstINFRoot", serving as the provider implementation allowing for the
//  root object's aggregated children to be included in the visualization process.
//
//  Illustrates programming the GetChildren method of the CATI3DVisuProvider interface 
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

class CAAPstINFVisuProviderRoot: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors
  // -------------------------------------
  CAAPstINFVisuProviderRoot ();
  virtual ~CAAPstINFVisuProviderRoot ();

  // Returns a list of pointers to the features aggregated by the "CAAPstINFRoot" feature
  // if the caller is the Product root	
  HRESULT GetChildren(CATBaseUnknown *ipObj, CATLISTP(CATBaseUnknown) **opListChildren); 

  private:

  // Copy constructor and assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  // ---------------------------------------------------------------------
  CAAPstINFVisuProviderRoot (CAAPstINFVisuProviderRoot&);
  CAAPstINFVisuProviderRoot& operator=(CAAPstINFVisuProviderRoot&);

};

//-----------------------------------------------------------------------

#endif

