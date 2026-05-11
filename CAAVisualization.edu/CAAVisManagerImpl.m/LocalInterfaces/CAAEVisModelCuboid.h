#ifndef CAAEVisModelCuboid_H
#define CAAEVisModelCuboid_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAVisModelCuboid component, implementing the  
//  CAAIVisModelCuboid interface. 
//
//
//===========================================================================

#include "CATBaseUnknown.h" //  To derive from

// Mathematics Framework
#include "CATMathPointf.h"

class CAAEVisModelCuboid : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;	

public :
   
   CAAEVisModelCuboid ();
   virtual ~ CAAEVisModelCuboid ();

   // Interface CAAIVisModelCuboid
   virtual HRESULT GetVertices(float ** oVertices) ;
   virtual HRESULT SetVertices(float  * iVertices) ;

private:

   // Copy constructor, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAAEVisModelCuboid(const CAAEVisModelCuboid &iObjectToCopy);

   // Assignment operator, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAAEVisModelCuboid & operator = (const CAAEVisModelCuboid &iObjectToCopy);

private:

    float *_VerticesTab;


};

#endif
