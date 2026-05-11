// System Framework
#include "IUnknown.h"
#include "CATErrorDef.h"
#include "CATCmpGuid.h"

// This Framework
#include "CAASysComponentFactory.h" // The component factory to create
#include "CAASysComponentCLSID.h" // CLSID declaration of the component

#ifdef _WINDOWS_SOURCE
#define ExportedByCAASysComponentImpl __declspec(dllexport)
#else
#define ExportedByCAASysComponentImpl
#endif

extern "C" HRESULT ExportedByCAASysComponentImpl CATDllGetClassObject(const CLSID & rclsid, const IID & riid, void ** ppv)
{
    HRESULT hr = E_NOTIMPL;
    
    if (CATCmpGuid(&rclsid, &CLSID_CAASysComponent))
    {
        CAASysComponentFactory * pCAASysComponentFactory = new CAASysComponentFactory();
        if(NULL == pCAASysComponentFactory) return E_OUTOFMEMORY;
        
        hr = pCAASysComponentFactory->QueryInterface(riid, ppv);
        
        pCAASysComponentFactory->Release();
        pCAASysComponentFactory = NULL;
    }
    
    return hr;
}
