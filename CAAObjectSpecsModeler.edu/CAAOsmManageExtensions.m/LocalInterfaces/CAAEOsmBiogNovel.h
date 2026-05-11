// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of CAAIBiogNovel Implementation:
//  -----------------------------------------
//
//  This class is an implementation of the CAAIBiogNovel interface for the
//  "CAAOsmBiographicalNovel" extension late-type. It essentially retrieves and
//  valuates the values of the attributes of this extension.This implementation
//  is included in Use Case CAAOsmMainExtensions.m. 
//  
//=============================================================================
//  Main Methods:
//  ------------
//
//  GetEpoch:  Returns the value of the "Epoch" attribute.
//  SetEpoch:  Valuates the "Epoch" attribute.
//  GetDomain: Returns the value of the "Domain" attribute.
//  SetDomain: Valuates the "Domain" attribute.
//=============================================================================

#ifndef CAAEOsmBiogNovel_h
#define CAAEOsmBiogNovel_h

#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"

class CAAEOsmBiogNovel :  public CATBaseUnknown
{
  CATDeclareClass;
  public:
    HRESULT GetEpoch (CATUnicodeString *opEpoch);
    HRESULT SetEpoch (const CATUnicodeString iEpoch);
	HRESULT GetDomain (CATUnicodeString *opDomain);
	HRESULT SetDomain (const CATUnicodeString iDomain);
};

#endif

