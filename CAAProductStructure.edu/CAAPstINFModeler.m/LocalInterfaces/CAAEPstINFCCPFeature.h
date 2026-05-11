// COPYRIGHT Dassault Systemes 2002

#ifndef CAAEPstINFCCPFeature_H
#define CAAEPstINFCCPFeature_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAPstINFLine, CAAPstINFPoint and CAAPstINFWire components,
//  implementing the CATICutAndPastable interface to execute CCP operations on these features.
//
//  This class derives from the ObjectCCP_SPEC adapter.
//
//  Illustrates programming the Update method for an object by implementing the
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

class CAAEPstINFCCPFeature: public ObjectCCP_SPEC
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
  CAAEPstINFCCPFeature ();
  virtual ~CAAEPstINFCCPFeature ();

  // Overrides Update on "CAAPstINFLine", "CAAPstINFPoint" and "CAAPstINFWire" features
  int Update (CATBaseUnknown_Associations &iopAssociationOfObjects, const CATFormat *ipAnImposedFormat=NULL, ListOfVarBaseUnknown *ipToCurObjects=NULL);

  private:
  // Copy constructor and equal operator, not implemented
  // Set as private to prevent the compiler from automatically creating them as public.
  // -------------------------------------------------------------------
  CAAEPstINFCCPFeature (CAAEPstINFCCPFeature &);
  CAAEPstINFCCPFeature& operator=(CAAEPstINFCCPFeature&);

};

//-----------------------------------------------------------------------

#endif
