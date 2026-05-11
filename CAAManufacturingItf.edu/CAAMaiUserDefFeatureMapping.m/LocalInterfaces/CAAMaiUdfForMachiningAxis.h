/* -*-c++-*- */
#ifndef CAAMaiUdfForMachiningAxis_h
#define CAAMaiUdfForMachiningAxis_h
// ===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAMaiUdfForMachiningAxis: implementation of the 
// CATIMfgMappingForMachiningAxis CAA interface for a type of User Defined Features
//
// ===================================================================

#include "CATBaseUnknown.h"

class CAAMaiUdfForMachiningAxis : public CATBaseUnknown
{
  CATDeclareClass;

  public:
 
    CAAMaiUdfForMachiningAxis();
    virtual ~CAAMaiUdfForMachiningAxis();

    HRESULT GetAxisSystem (CATBaseUnknown_var & oAxisSystem);

};
#endif

