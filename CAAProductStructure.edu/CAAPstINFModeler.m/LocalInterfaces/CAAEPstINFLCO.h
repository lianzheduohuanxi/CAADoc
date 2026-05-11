// COPYRIGHT Dassault Systemes 2002

#ifndef CAAEPstINFLCO_H
#define CAAEPstINFLCO_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAPstINFLine and CAAPstINFWire components, implementing
//  the LifeCycleObject interface to allow specific treatments to be performed
//  in the remove method.
//
//  This class derives from the CATSpecLifeCycleObjectExt adapter.
//
//  Illustrates programming the remove method for an object by implementing the
//  LifeCycleObject interface of the ObjectModelerBase framework.
//
//===========================================================================
//  Inheritance:
//  ------------
//            
//  CATSpecLifeCycleObjectExt (ObjectSpecsModeler Framework)
//      CATBaseUnknown (System Framework) 
//
//===========================================================================

// ObjectSpecsModeler Framework
#include "CATSpecLifeCycleObjectExt.h"

class CAAEPstINFLCO: public CATSpecLifeCycleObjectExt
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
  CAAEPstINFLCO ();
  virtual ~CAAEPstINFLCO ();

  // Over-rides remove default implementation for "CAAPstINFLine" and "CAAPstINFWire" features.
  void remove (int iForCloseContext=0) ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // Set as private to prevent the compiler from automatically creating them as public.
  // -------------------------------------------------------------------
  CAAEPstINFLCO (CAAEPstINFLCO &);
  CAAEPstINFLCO& operator=(CAAEPstINFLCO&);

};

//-----------------------------------------------------------------------

#endif
