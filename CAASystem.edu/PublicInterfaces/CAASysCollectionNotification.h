#ifndef CAASysCollectionNotification_h
#define CAASysCollectionNotification_h

// COPYRIGHT DASSAULT SYSTEMES 1999
//   
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Notification base class.
//  An instance of a derived class is created and sent by the 
//  the implementation of CAAISysCollection interface whenever it becomes 
//  empty or filled.
//
//
//===========================================================================
//  Inheritance:
//  ------------
//            CATNotification  ( System Framework)
//               CATBaseUnknown (System Framework).
//
//===========================================================================

// System Framework
#include "CATNotification.h"    // Needed to derive from CATNotification

// Local Framework
#include "CAASysGeoModelInf.h"  // Needed to export the class  

class ExportedByCAASysGeoModelInf CAASysCollectionNotification : public CATNotification
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;
  
  public:

    CAASysCollectionNotification();
    virtual ~CAASysCollectionNotification();

  private:
    
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysCollectionNotification(const CAASysCollectionNotification &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysCollectionNotification & operator = (const CAASysCollectionNotification &iObjectToCopy);

};

#endif
