// COPYRIGHT Dassault Systemes 2002

#ifndef CAAEPstINFLCOPoint_H
#define CAAEPstINFLCOPoint_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAPstINFPoint component, implementing
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

class CAAEPstINFLCOPoint: public CATSpecLifeCycleObjectExt
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
  CAAEPstINFLCOPoint ();
  virtual ~CAAEPstINFLCOPoint ();

  // Over-rides remove default implementation for "CAAPstINFPoint" feature.
  void remove (int iForCloseContext=0) ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // Set as private to prevent the compiler from automatically creating them as public.
  // -------------------------------------------------------------------
  CAAEPstINFLCOPoint (CAAEPstINFLCOPoint &);
  CAAEPstINFLCOPoint& operator=(CAAEPstINFLCOPoint&);

};

//-----------------------------------------------------------------------

#endif
