#ifndef CAAESysTextureProperties_H
#define CAAESysTextureProperties_H

// COPYRIGHT DASSAULT SYSTEMES 2000
//
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension implementing the CAAITextureProperties interface. 
//
//===========================================================================
//  Inheritance:
//  ------------
//              CATBaseUnknown (System Framework)
//         
//===========================================================================

#include "CATBaseUnknown.h"   // to derive from  CATBaseUnknown


class CAAESysTextureProperties: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysTextureProperties();
    virtual ~CAAESysTextureProperties();

    // Texture properties are:
    //------------------------

    // A metal property  
    // ----------------
    // 0 : the object is not metallic 
    // 1 : the object is metallic
    //
    virtual HRESULT GetMetal(int & oIsMetal)   ;
    virtual HRESULT SetMetal(const int iIsMetal )  ; 

    // A Roughness property  
    // --------------------
    // 0 : The object is smooth
    // 1 : The object is rough
    virtual HRESULT GetRough(int & oIsRough)   ;
    virtual HRESULT SetRough(const int iIsRough)  ; 

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysTextureProperties(const CAAESysTextureProperties &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysTextureProperties & operator = (const CAAESysTextureProperties &iObjectToCopy);

  private:

    int _IsMetal ;
    int _IsRough ;
	
};
#endif
