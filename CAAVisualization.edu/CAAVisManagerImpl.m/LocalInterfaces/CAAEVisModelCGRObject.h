#ifndef CAAEVisModelCGRObject_H
#define CAAEVisModelCGRObject_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAVisModelCGRObject component, implementing the  
//  CAAIVisModelCGRObject interface. 
//
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h" //  To derive from

// Visualization FrameWork
class CAT3DRep;
class CAT3DBagRep;
class CATRep;

class CAAEVisModelCGRObject : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;	

public :
   
   CAAEVisModelCGRObject ();
   virtual ~ CAAEVisModelCGRObject ();

  // ---------------------------------------------------------------
  // +++  Methods of the CAAIVisModelCGRObject interface ++++++++++++++
  // ---------------------------------------------------------------

   virtual HRESULT GetCGRRep(CATRep      ** oCGRRep) ;
   virtual HRESULT ReadCGRFile(const char * iCGRFileName) ;

private:

   // Copy constructor, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAAEVisModelCGRObject(const CAAEVisModelCGRObject &iObjectToCopy);

   // Assignment operator, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAAEVisModelCGRObject & operator = (const CAAEVisModelCGRObject &iObjectToCopy);

private : 

   CAT3DRep    * _pCGRRep;
   CAT3DBagRep * _pRep;

};

#endif
