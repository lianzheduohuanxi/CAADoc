#ifndef CAAEVisModelEvents_H
#define CAAEVisModelEvents_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Application using a new document (CAAGeometry) with its own workshop and 
//  commands.
//   
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the document objects, implementing the
//  CATIModelEvents interface to enable the revisualization of the objects
//  after a modification.
//  This class derives from the CATExtIModelEvents adapter which implements
//  all the interface services.
//
//===========================================================================
//  Inheritance:
//  ------------
//            CATExtIModelEvents ( Visualization Framework) 
//                CATBaseUnknown (System Framework).
//
//===========================================================================

// Visualization Framework 
#include "CATExtIModelEvents.h" // Need to derive from

class CAAEVisModelEvents : public CATExtIModelEvents
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public :

    CAAEVisModelEvents();
    virtual ~CAAEVisModelEvents();

  private :

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVisModelEvents(const CAAEVisModelEvents &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEVisModelEvents & operator = (const CAAEVisModelEvents &iObjectToCopy);
};

#endif 
