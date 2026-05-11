#ifndef CAAVisModelEModelEventsForObject_H
#define CAAVisModelEModelEventsForObject_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAVisModelObject component, implementing the
//  CATIModelEvents interface to enable the revisualization of the objects
//  after a modification.
//  This class derives from the CATExtIModelEvents adapter which implements
//  all the interface services.
//
//===========================================================================

#include "CATExtIModelEvents.h" // To derive from


class CAAEVisModelEventsForObject : public CATExtIModelEvents
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;	

  public :

  CAAEVisModelEventsForObject();
  virtual ~CAAEVisModelEventsForObject();

  private:

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVisModelEventsForObject(const CAAEVisModelEventsForObject &iObjectToCopy);

  // Assignment operator , not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVisModelEventsForObject & operator = (const CAAEVisModelEventsForObject &iObjectToCopy);
};

#endif
