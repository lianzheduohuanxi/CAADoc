#ifndef CAASysCollectionModifNotif_h
#define CAASysCollectionModifNotif_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Notification class.
//  An instance of this class is created and sent by the 
//  the implementation of CAAISysCollection interface whenever an element
//  is added or removed from the CAAGeometry document
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


class ExportedByCAASysGeoModelInf CAASysCollectionModifNotif : 
             public CAASysCollectionNotification
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;

  public:

    CAASysCollectionModifNotif();
    virtual ~CAASysCollectionModifNotif();

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysCollectionModifNotif(const CAASysCollectionModifNotif &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysCollectionModifNotif & operator = (const CAASysCollectionModifNotif &iObjectToCopy);

    
};

#endif
