#ifndef CAAEVisModelSetOfObject_H
#define CAAEVisModelSetOfObject_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAVisModelSetOfObject component, implementing the  
//  CAAIVisModelSetOfObject interface. 
//
//
//===========================================================================

#include "CATBaseUnknown.h" //  To derive from

class CAAEVisModelSetOfObject : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;	

public :
   
   CAAEVisModelSetOfObject ();
   virtual ~ CAAEVisModelSetOfObject ();

private:

   // Copy constructor, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAAEVisModelSetOfObject(const CAAEVisModelSetOfObject &iObjectToCopy);

   // Assignment operator, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAAEVisModelSetOfObject & operator = (const CAAEVisModelSetOfObject &iObjectToCopy);

};

#endif
