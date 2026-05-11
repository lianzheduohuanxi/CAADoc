// -------------------------------------------------------------------
// Copyright Dassault Systemes 2012
//---------------------------------------------------------------------
// Source:   CAAEV5V6ExtMmrMultiMeasureVisProperties.cpp
//---------------------------------------------------------------------
//
//  CAAEV5V6ExtMmrMultiMeasureVisProperties: Implementation of CATIVisProperties for CAAV5V6ExtMmrMultiMeasure
//
// Note :  CAAEV5V6ExtMmrMultiMeasureReplace is the same use case as CAAEV5V6ExtMmrMultiMeasureVisProperties. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//---------------------------------------------------------------------

#include "CATIAV5Level.h"

// Local CAAV5V6MechanicalModeler.edu Framework
#include "CAAEV5V6ExtMmrMultiMeasureVisProperties.h"

// VisualizationInterfaces Framework for V6
// Visualization Framework for V5
#include "CATVisGeomType.h"
#include "CATVisPropertyType.h"

// VisualizationInterfaces Framework for V6
// VisualizationBase Framework for V5
#include "CATPathElement.h"


CATBeginImplementClass(CAAEV5V6ExtMmrMultiMeasureVisProperties,DataExtension,CATIVisProperties,CAAV5V6ExtMmrMultiMeasure);
CATAddExtendedImplementation(CAAV5V6ExtMmrMeasureSet);
CATEndImplementClass(CAAEV5V6ExtMmrMultiMeasureVisProperties);
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIVisProperties.h"
TIE_CATIVisProperties(CAAEV5V6ExtMmrMultiMeasureVisProperties);

// Don't forget to add those lines on Dictionary
// CATPrtCont  CAAIV5V6ExtMmrMultiMeasureFactory    libCAAV5V6ExtMmrMultiMeasure
//
//CAAV5V6ExtMmrMultiMeasure   CATIVisProperties   libV5V6ExtCAAMmrMultiMeasure
//CAAV5V6ExtMmrMeasureSet     CATIVisProperties   libV5V6ExtCAAMmrMultiMeasure

 CAAEV5V6ExtMmrMultiMeasureVisProperties:: CAAEV5V6ExtMmrMultiMeasureVisProperties(): CATExtIVisProperties()
{}

 CAAEV5V6ExtMmrMultiMeasureVisProperties::~ CAAEV5V6ExtMmrMultiMeasureVisProperties()
{}

HRESULT  CAAEV5V6ExtMmrMultiMeasureVisProperties::IsGeomTypeDefined( CATVisGeomType & iGeomType )
{
  HRESULT rc = E_FAIL;
  if (CATVPGlobalType == iGeomType || CATVPLine == iGeomType ||CATVPAsm == iGeomType)
    rc = S_OK;
  
  return rc;
}

HRESULT  CAAEV5V6ExtMmrMultiMeasureVisProperties::GetSubTypeFromPath(CATPathElement & iPathElement,
                                                                          CATVisPropertyType iPropertyType,
                                                                          CATVisGeomType & oGeomType,
                                                                          unsigned int & oPropertyNumber)
{
  HRESULT rc = E_FAIL;

  switch (iPropertyType)
  {
    case CATVPColor:
    case CATVPSymbol:
      oGeomType = CATVPLine;
      rc = S_OK;
      break;
  }
  oPropertyNumber = 0;
  return rc;
}
