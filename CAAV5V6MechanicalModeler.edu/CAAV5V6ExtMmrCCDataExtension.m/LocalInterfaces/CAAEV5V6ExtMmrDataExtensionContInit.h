#ifndef CAAEV5V6ExtMmrDataExtensionContInit_H
#define CAAEV5V6ExtMmrDataExtensionContInit_H
// COPYRIGHT DASSAULT SYSTEMES 2012

#include "CATInit.h"

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  CATInit implementation for CAAV5V6ExtMmrDataExtensionCont
//
//===========================================================================
//===========================================================================

class CATBaseUnknown;

class CAAEV5V6ExtMmrDataExtensionContInit: public CATInit
{
    // Used in conjunction with CATImplementClass in the .cpp file
    CATDeclareClass;

public:
    //////////////////////////////
    // Constructor - Destructor //
    //////////////////////////////
    CAAEV5V6ExtMmrDataExtensionContInit();
    virtual ~CAAEV5V6ExtMmrDataExtensionContInit();

    // CATInit interface methods
    void Init (CATBoolean  iDestroyExistingData ) ;
    CATBaseUnknown* GetRootContainer (const CATIdent  iInterfaceID ) ;

private:

    CAAEV5V6ExtMmrDataExtensionContInit (CAAEV5V6ExtMmrDataExtensionContInit &);
    CAAEV5V6ExtMmrDataExtensionContInit& operator=(CAAEV5V6ExtMmrDataExtensionContInit&);

};
#endif
