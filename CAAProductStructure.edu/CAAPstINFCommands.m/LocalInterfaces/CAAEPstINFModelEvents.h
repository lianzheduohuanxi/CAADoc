// COPYRIGHT DASSAULT SYSTEMES 2002

#ifndef CAAEPstINFModelEvents_H
#define CAAEPstINFModelEvents_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CATProduct feature objects, implementing the
//  CATIModelEvents interface to enable the revisualization of the objects
//  after a modification.
//
//  Illustrates programming the sending of events on the modification of an object
//  by implementing the CATIModelEvents interface of the Visualization framework.
//
//  This class derives from the CATExtIModelEvents adapter which implements
//  all the interface services.
//
//===========================================================================
//  Inheritance:
//  ------------
//
//  CATExtIModelEvents (Visualization Framework) 
//      CATBaseUnknown (System Framework)
//
//===========================================================================

// Visualization Framework 
#include "CATExtIModelEvents.h" // Need to derive from

class CAAEPstINFModelEvents : public CATExtIModelEvents
{
  CATDeclareClass;

  public :

    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEPstINFModelEvents();
    virtual ~CAAEPstINFModelEvents();

  private :

  // Copy constructor and assignment operator, not implemented
  // Set as private to prevent the compile from automatically creating them as public.
  //----------------------------------------------------------------------------------
  CAAEPstINFModelEvents(const CAAEPstINFModelEvents &iObjectToCopy);
  CAAEPstINFModelEvents & operator = (const CAAEPstINFModelEvents &iObjectToCopy);
};

#endif 
