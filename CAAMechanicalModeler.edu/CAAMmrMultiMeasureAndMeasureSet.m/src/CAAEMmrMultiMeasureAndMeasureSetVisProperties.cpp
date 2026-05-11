// -------------------------------------------------------------------
// Copyright Dassault Systemes 2007
//---------------------------------------------------------------------
// Source:  CAAEMmrMultiMeasureAndMeasureSetVisProperties.cpp
//---------------------------------------------------------------------
//
// CAAEMmrMultiMeasureAndMeasureSetVisProperties: Implementation of CATIVisProperties for MmrMultiMeasure
//
//---------------------------------------------------------------------

#include "CAAEMmrMultiMeasureAndMeasureSetVisProperties.h"

CATBeginImplementClass(CAAEMmrMultiMeasureAndMeasureSetVisProperties,DataExtension,CATBaseUnknown,CAAMmrMultiMeasure);
CATAddExtendedImplementation(CAAMmrMeasureSet);
CATEndImplementClass(CAAEMmrMultiMeasureAndMeasureSetVisProperties);
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIVisProperties.h"
TIE_CATIVisProperties( CAAEMmrMultiMeasureAndMeasureSetVisProperties);

// Don't forget to add those lines on Dictionary
// CATPrtCont  CAAIMmrMultiMeasureAndMeasureSetFactory    libCAAMmrMultiMeasureAndMeasureSet
//
//CAAMmrMultiMeasure   CATIVisProperties   libCAAMmrMultiMeasureAndMeasureSet
//CAAMmrMeasureSet     CATIVisProperties   libCAAMmrMultiMeasureAndMeasureSet

CAAEMmrMultiMeasureAndMeasureSetVisProperties::CAAEMmrMultiMeasureAndMeasureSetVisProperties(): CATExtIVisProperties()
{}

CAAEMmrMultiMeasureAndMeasureSetVisProperties::~CAAEMmrMultiMeasureAndMeasureSetVisProperties()
{}

HRESULT CAAEMmrMultiMeasureAndMeasureSetVisProperties::IsGeomTypeDefined( CATVisGeomType & iGeomType )
{
  HRESULT rc = E_FAIL;
  if ( CATVPGlobalType == iGeomType || CATVPLine == iGeomType ||CATVPAsm == iGeomType)
  {
    rc = S_OK;
  }
  
  return rc;
}

HRESULT CAAEMmrMultiMeasureAndMeasureSetVisProperties::GetSubTypeFromPath(CATPathElement     & iPathElement,
                                                                CATVisPropertyType   iPropertyType,
                                                                CATVisGeomType     & oGeomType,
                                                                unsigned int       & oPropertyNumber )
{
  HRESULT rc = E_FAIL ;

  switch ( iPropertyType )
  {
    case CATVPColor:
    case CATVPSymbol:
        oGeomType = CATVPLine ;
   
        rc = S_OK ;
        break;
  }
  oPropertyNumber = 0 ;
  return rc ;;
}
