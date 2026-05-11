#ifndef CAADlgTessellation_H
#define CAADlgTessellation_H

// COPYRIGHT DASSAULT DlgTEMES 2000

// ==================================================================================
// Abstract class
// -------------
//
// Class which subscribes to an event 
//
// ==================================================================================

// System Framework
#include "CATBaseUnknown.h"
#include "CATEventSubscriber.h"

class CAADlgObject;

class CAADlgTessellation: public CATBaseUnknown
{
  public:

    // Constructor 
    CAADlgTessellation(char * iTessellationType);

    // Destructor 
    virtual ~CAADlgTessellation();

    // Approch
    // -------
    // Sets Callback to be prevent when the Object is modified
    //
    void Init          (CAADlgObject *iObjectToTesselate);


    // RunAway
    // -------
    // It's the callback to tesselate the object
    //
    void Tessellate       (CATCallbackEvent  iEventObject,
                           void             *iObject,
                           CATNotification  *iNotifObject,
                           CATSubscriberData iUsefulData,
                           CATCallback       iCallBack );


  private:

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgTessellation ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgTessellation(const CAADlgTessellation &iObjectToCopy);
  
    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgTessellation & operator = (const CAADlgTessellation &iObjectToCopy);
  
  private:

    //The Object to tesselate
    CAADlgObject * _pObject;

    // The type of Tessellation ( Rought, fine ... )
    char        * _pTessellationType ;
};

#endif
