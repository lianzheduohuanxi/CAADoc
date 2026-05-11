#include "CAASysComponentFactory.h" // This class declaration

#include "iostream.h" // For output
#include "CATErrorDef.h"
#include "CAASysComponent.h" // The component to create

// OM Implementation
CATImplementClass(CAASysComponentFactory, Implementation, CATBaseUnknown, CATNull);

CAASysComponentFactory::CAASysComponentFactory()
{
    cout << "CAASysComponentFactory::CAASysComponentFactory()" << endl;
}

CAASysComponentFactory::~CAASysComponentFactory()
{
    cout << "CAASysComponentFactory::~CAASysComponentFactory()" << endl;
}

// To declare that CAASysComponentFactory implements IClassFactory insert the following line
// to the interface dictionary
// CAASysComponentFactory IClassFactory libCAASysComponentImpl

// To create the TIE object
#include "TIE_IClassFactory.h"
TIE_IClassFactory( CAASysComponentFactory );

HRESULT __stdcall CAASysComponentFactory::LockServer(int iLock)
{
    return S_OK;
}

HRESULT __stdcall CAASysComponentFactory::CreateInstance(IUnknown * iUnkOuter, const IID &iIid, void ** oObject)
{
    CAASysComponent * pCAASysComponent = new CAASysComponent();
    if(NULL == pCAASysComponent) return E_OUTOFMEMORY;
    
    HRESULT hr = pCAASysComponent->QueryInterface(iIid, oObject);
    
    pCAASysComponent->Release();
    pCAASysComponent = NULL;
    
    return hr;
}
