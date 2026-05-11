#ifndef CAASysCollectionFilledNotif_h
#define CAASysCollectionFilledNotif_h

// COPYRIGHT DASSAULT SYSTEMES 1999
    
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Notification class.
//  An instance of this class is created and sent by the 
//  the implementation of CAAISysCollection interface whenever it becomes 
//  not empty. 
//
//  In the same way, a CAASysCollectionEmptyNotif is sent when the 
//  collection becomes empty.
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


class ExportedByCAASysGeoModelInf CAASysCollectionFilledNotif : 
                  public CAASysCollectionNotification
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;
  
  public:

    CAASysCollectionFilledNotif();
    virtual ~CAASysCollectionFilledNotif();
  
  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysCollectionFilledNotif(const CAASysCollectionFilledNotif &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysCollectionFilledNotif & operator = (const CAASysCollectionFilledNotif &iObjectToCopy);

        
};

#endif
