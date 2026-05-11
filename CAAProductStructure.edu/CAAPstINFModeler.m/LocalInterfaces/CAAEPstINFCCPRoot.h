// COPYRIGHT Dassault Systemes 2002

#ifndef CAAEPstINFCCPRoot_H
#define CAAEPstINFCCPRoot_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAPstINFRoot component, implementing
//  the CATICutAndPastable interface to execute CCP operations on this features.
//
//  This class derives from the ObjectCCP_SPEC adapter.
//
//  Illustrates programming the required methods for a root object by implementing the
//  CATICutAndPastable interface of the ObjectModelerBase framework.
//
//===========================================================================
//  Inheritance:
//  ------------
//            
//  ObjectCCP_SPEC (ObjectSpecsModeler Framework)
//      CATBaseUnknown (System Framework) 
//
//===========================================================================

// ObjectSpecsModeler Framework
#include "ObjectCCP_SPEC.h"

class CAAEPstINFCCPRoot: public ObjectCCP_SPEC
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
  CAAEPstINFCCPRoot ();
  virtual ~CAAEPstINFCCPRoot ();

  // Over-rides BoundaryExtract for "CAAPstINFRoot" feature
  int BoundaryExtract (ListOfVarBaseUnknown &iopObjectsAlreadyInBoundary, const ListOfVarBaseUnknown *ipObjectsToAdd=NULL, const CATFormat *ipAnImposedFormat=NULL) const ;

  // Over-rides BoundaryExtract for "CAAPstINFRoot" feature
  int BoundaryRemove (ListOfVarBaseUnknown &iopObjectsAlreadyInBoundary, const ListOfVarBaseUnknown *ipObjectsToRemove=NULL, const CATFormat *ipAnImposedFormat=NULL) const ;

  // Over-rides BoundaryExtract for "CAAPstINFRoot" feature
  int Remove (ListOfVarBaseUnknown &ipObjectToRemove, const CATFormat *ipAnImposedFormat=NULL) ;


  private:
  // Copy constructor and equal operator, not implemented
  // Set as private to prevent the compiler from automatically creating them as public.
  // -------------------------------------------------------------------
  CAAEPstINFCCPRoot (CAAEPstINFCCPRoot &);
  CAAEPstINFCCPRoot& operator=(CAAEPstINFCCPRoot&);

};

//-----------------------------------------------------------------------

#endif
