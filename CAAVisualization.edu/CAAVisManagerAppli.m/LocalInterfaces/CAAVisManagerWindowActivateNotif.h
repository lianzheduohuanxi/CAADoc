#ifndef CAAVisManagerWindowActivateNotif_H
#define CAAVisManagerWindowActivateNotif_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Window Activated notification class.
//
//===========================================================================
//  Inheritance:
//  ------------
//            CATNotification  ( System Framework)
//               CATBaseUnknown (System Framework).
//
//===========================================================================

// System Framework 
#include "CATNotification.h" // to derive from 

class CAAVisManagerWindowActivateNotif : public  CATNotification
{
   // Used in conjunction with CATImplementClass in the .cpp file 
   CATDeclareClass;
public :
   
   CAAVisManagerWindowActivateNotif () ;
   virtual ~CAAVisManagerWindowActivateNotif();
   
private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerWindowActivateNotif(const CAAVisManagerWindowActivateNotif &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerWindowActivateNotif & operator = (const CAAVisManagerWindowActivateNotif &iObjectToCopy);

};


#endif
