#ifndef CAAISysTextureProperties_h
#define CAAISysTextureProperties_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Interface to manage texture property .
//
//===========================================================================
//  Usage:
//  ------
//  In the edit properties 
//
//===========================================================================
//  Inheritance:
//  ------------
//               CATBaseUnknown (System Framework).
//
//===========================================================================
//  Main Methods:
//  -------------
//
//  GetMetal     
//  SetMetal 
//  GetRough
//  SetRough
// 
//===========================================================================

// System Framework
#include <CATBaseUnknown.h>           //Needed to derive from CATBaseUnknown

// Local Framework
#include <CAASysGeoModelInf.h>        //Needed to export the IID

// Global Unique IDentifier defined in .cpp 
// exported by CAASysGeoModelInf
extern ExportedByCAASysGeoModelInf IID IID_CAAISysTextureProperties;

class ExportedByCAASysGeoModelInf CAAISysTextureProperties : public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public:

    // Texture properties are:
    //------------------------

    // A metal property  
    // ----------------
    // 0 : the object is not metallic 
    // 1 : the object is metallic

    virtual HRESULT GetMetal(int & oIsMetal)  = 0;
    virtual HRESULT SetMetal(const int iIsMetal)  = 0;

    // A Roughness property  
    // --------------------
    // 0 : The object is smooth
    // 1 : The object is rough

    virtual HRESULT GetRough(int & oIsMetal)  = 0;
    virtual HRESULT SetRough(const int iIsMetal)  = 0;
};


#endif
