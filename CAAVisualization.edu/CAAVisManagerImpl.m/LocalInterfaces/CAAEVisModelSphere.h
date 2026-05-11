#ifndef CAAEVisModelSphere_H
#define CAAEVisModelSphere_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAVisModelSphere component, implementing the  
//  CAAIVisModelSphere interface. 
//
//
//===========================================================================

#include "CATBaseUnknown.h" //  To derive from

// Mathematics Framework
#include "CATMathPointf.h"

class CAAEVisModelSphere : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;	

public :
   
   CAAEVisModelSphere ();
   virtual ~ CAAEVisModelSphere ();

   // CAAIVisModelSphere interface

   virtual HRESULT GetCenter(CATMathPointf & iCenter) const ;
   virtual HRESULT SetCenter(const CATMathPointf & oCenter) ;

   virtual HRESULT GetRadius(float & oRadius) const ;
   virtual HRESULT SetRadius(const float iRadius);

private:

   // Copy constructor, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAAEVisModelSphere(const CAAEVisModelSphere &iObjectToCopy);

   // Assignment operator, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAAEVisModelSphere & operator = (const CAAEVisModelSphere &iObjectToCopy);

private:

   CATMathPointf _Center;
   float         _Radius;


};

#endif
