#ifndef CAAEVisModelObject_H
#define CAAEVisModelObject_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAVisModelObject component, implementing the  
//  CAAIVisModelObject interface. 
//
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h" //  To derive from

// Visualization Framework
#include "list.h"

// Mathematics Framework
#include "CATMathPointf.h"

class CAAEVisModelObject : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;	

public :
   
   CAAEVisModelObject ();
   virtual ~ CAAEVisModelObject ();

  // ---------------------------------------------------------------
  // +++  Methods of the CAAIVisModelObject interface ++++++++++++++
  // ---------------------------------------------------------------

  // Adds an object to the current model
  HRESULT AddChild(CATBaseUnknown *iObject);

  //Remove an object to the current model
  HRESULT RemChild(CATBaseUnknown *iObject);

  // Add a parent to the current object
  HRESULT AddParent(CATBaseUnknown *iObject);

  // Remove a parent from the current object.
  HRESULT RemParent(CATBaseUnknown *iObject);

  //Get back the list of children
  list<CATBaseUnknown> *GetChildren();

  //Get back the list of parents
  list<CATBaseUnknown> *GetParents();

  // Get the type of object
  virtual HRESULT GetType(char ** oType);
  virtual HRESULT SetType(const char * iType);



private:

   // Copy constructor, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAAEVisModelObject(const CAAEVisModelObject &iObjectToCopy);

   // Assignment operator , not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAAEVisModelObject & operator = (const CAAEVisModelObject &iObjectToCopy);

private:

  list<CATBaseUnknown> _Parents;
  list<CATBaseUnknown> _Children;

  //type of object. 
  char * _Type;

};

#endif
