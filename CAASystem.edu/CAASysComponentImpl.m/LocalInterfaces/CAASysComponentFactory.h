// COPYRIGHT DASSAULT SYSTEMES 2003
#ifndef CAASysComponentFactory_H
#define CAASysComponentFactory_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  By implementing IClassFactory interface,
//  this class allows you to create the component CAASysComponent.
//
//  See the CAASysComponentCreateCLSID module which contains a sample to use this fonctionality.
// 
//===========================================================================

// System Framework
#include "CATBaseUnknown.h" // Needed to derive from CATBaseUnknown

class CAASysComponentFactory : public CATBaseUnknown
{
    // Used in conjunction with CATImplementClass in the .cpp file
    CATDeclareClass;
    
    public:
    
    CAASysComponentFactory();
    virtual ~CAASysComponentFactory();
    
    virtual HRESULT __stdcall CreateInstance(IUnknown * iUnkOuter, const IID &iIid, void ** oObject);
    virtual HRESULT __stdcall LockServer(int iLock);
    
    private:
    
    // Not implemented
    CAASysComponentFactory(const CAASysComponentFactory &);
    // Not implemented
    CAASysComponentFactory & operator = (const CAASysComponentFactory &);
};

#endif
