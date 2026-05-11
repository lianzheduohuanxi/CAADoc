// COPYRIGHT Dassault Systemes 2002

#ifndef CAAEPstINFRoot_H
#define CAAEPstINFRoot_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAPstINFRoot component, implementing
//  the CAAIPstINFRoot interface defined in the CAAProductStructure.edu framework,
//  allowing the adding and retrieving of the root's aggregated children.
//
//  Illustrates programming the adding and retrieving methods necessary for the
//  management of a CAAPstINFRoot feature.
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
#include "CATLISTV_CATBaseUnknown.h"

// ObjectSpecsModeler Framework
class CATISpecObject;
class CATISpecAttrKey;

class CAAEPstINFRoot: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
  CAAEPstINFRoot ();
  virtual ~CAAEPstINFRoot ();

  // Aggregates a new feature under the root.
  HRESULT AddChild (CATISpecObject *ipiFeature);

  // Returns a list of the direct children of the root node.
  HRESULT GetChildren(CATListValCATBaseUnknown_var **opList);
 
  private:
  // Copy constructor and equal operator, not implemented
  // Set as private to prevent the compiler from automatically creating them as public.
  // -------------------------------------------------------------------
  CAAEPstINFRoot (CAAEPstINFRoot &);
  CAAEPstINFRoot& operator=(CAAEPstINFRoot&);

};

//-----------------------------------------------------------------------

#endif
