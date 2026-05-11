#ifndef CAASysCollectionEmptyNotif_h
#define CAASysCollectionEmptyNotif_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Notification class.
//  An instance of this class is created and sent by the 
//  the implementation of CAAISysCollection interface whenever it becomes 
//  empty. 
//
//  In the same way, a CAASysCollectionFilledNotif is sent when the 
//  collection becomes not empty.
//
//
//===========================================================================
//  Inheritance:
//  ------------
//         CAASysCollectionNotification ( Local Framework)
//            CATNotification  ( System Framework)
//               CATBaseUnknown (System Framework).
//
//===========================================================================

// Needed to derive from CAASysCollectionNotification
#include "CAASysCollectionNotification.h"  

// Needed to export the class        
#include "CAASysGeoModelInf.h"  


class ExportedByCAASysGeoModelInf CAASysCollectionEmptyNotif : 
             public CAASysCollectionNotification
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;

  public:

    CAASysCollectionEmptyNotif();
    virtual ~CAASysCollectionEmptyNotif();

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysCollectionEmptyNotif(const CAASysCollectionEmptyNotif &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysCollectionEmptyNotif & operator = (const CAASysCollectionEmptyNotif &iObjectToCopy);

    
};

#endif
