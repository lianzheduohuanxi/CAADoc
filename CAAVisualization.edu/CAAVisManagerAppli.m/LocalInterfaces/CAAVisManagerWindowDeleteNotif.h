#ifndef CAAVisManagerWindowDeleteNotif_H
#define CAAVisManagerWindowDeleteNotif_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Window deleted Notification class. 
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

class CAAVisManagerWindowDeleteNotif : public  CATNotification
{
   // Used in conjunction with CATImplementClass in the .cpp file 
   CATDeclareClass;

public :
   
   CAAVisManagerWindowDeleteNotif () ;
   virtual ~CAAVisManagerWindowDeleteNotif();

private:
    
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerWindowDeleteNotif(const CAAVisManagerWindowDeleteNotif &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerWindowDeleteNotif & operator = (const CAAVisManagerWindowDeleteNotif &iObjectToCopy);

};


#endif
