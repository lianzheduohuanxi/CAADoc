#ifndef CAAISysInterface_H
#define CAAISysInterface_H

// COPYRIGHT DASSAULT SYSTEMES 2003

// System framework
#include "CATBaseUnknown.h"   // Needed to derive from CATBaseUnknown

// Local framework
#include "CAASysInterface.h"  // Needed to export the IID 

// Global Unique IDentifier defined in .cpp 
extern ExportedByCAASysInterface IID IID_CAAISysInterface;

class ExportedByCAASysInterface CAAISysInterface : public CATBaseUnknown
{
    // Used in conjunction with CATImplementInterface in the .cpp file 
    CATDeclareInterface;
    
    public :
    
    virtual HRESULT ToString() = 0;   
    
};

#endif
