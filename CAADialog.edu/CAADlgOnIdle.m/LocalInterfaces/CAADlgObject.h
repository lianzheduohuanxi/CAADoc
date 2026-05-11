#ifndef CAADlgObject_H
#define CAADlgObject_H

// COPYRIGHT DASSAULT DlgTEMES 2000

// ==================================================================================
// Abstract class
// -------------
// Class which publishes an event
//
// ==================================================================================

// System Framework
#include "CATBaseUnknown.h"

class CAADlgObject: public CATBaseUnknown 
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;
  
  public:
  
    // Constructor
    CAADlgObject(char * iObjectName);

    // Destructor
    virtual ~CAADlgObject();

    // StartRinging
    // -------------
    // Send a notification to state that the object has changed
    //
    void Modification();

    // GetName
    // --------------
    // Returns the name of the object.
    //
    char *GetName();

  private:

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgObject ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgObject(const CAADlgObject &iObjectToCopy);
  
    // Assignment operator , not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgObject & operator = (const CAADlgObject &iObjectToCopy);
  
  private:

    // The name of the object
    char                        * _pObjectName;


};

#endif
