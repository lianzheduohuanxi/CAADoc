#ifndef CAAEMmrDataExtensionContInit_H
#define CAAEMmrDataExtensionContInit_H
// COPYRIGHT DASSAULT SYSTEMES 2007

#include "CATInit.h"

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  CATInit implementation for MmrDataExtensionCont
//
//===========================================================================
//===========================================================================

class CATBaseUnknown;

class CAAEMmrDataExtensionContInit: public CATInit
{
    // Used in conjunction with CATImplementClass in the .cpp file
    CATDeclareClass;

public:
    //////////////////////////////
    // Constructor - Destructor //
    //////////////////////////////
    CAAEMmrDataExtensionContInit();
    virtual ~CAAEMmrDataExtensionContInit();

    // CATInit interface methods
    void Init (CATBoolean  iDestroyExistingData ) ;
    CATBaseUnknown* GetRootContainer (const CATIdent  iInterfaceID ) ;

private:

    CAAEMmrDataExtensionContInit (CAAEMmrDataExtensionContInit &);
    CAAEMmrDataExtensionContInit& operator=(CAAEMmrDataExtensionContInit&);

};
#endif
