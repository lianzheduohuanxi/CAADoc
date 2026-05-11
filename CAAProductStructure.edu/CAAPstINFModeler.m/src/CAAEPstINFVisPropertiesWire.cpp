// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAEPstINFVisPropertiesWire.h"


// Visualization Framework 
#include "CATIVisProperties.h"

// Others
#include "iostream.h"
#include "CATIModelEvents.h"


//-----------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CATIVisProperties.h"
TIE_CATIVisProperties(CAAEPstINFVisPropertiesWire);

// To declare that the class is a data extension of CAASysLine
//
CATImplementClass(CAAEPstINFVisPropertiesWire, DataExtension, CATBaseUnknown, CAAPstINFWire);
// 
// To declare that CAAEPstINFVisPropertiesWire implements CATIVisProperties, insert 
// the following line in the interface dictionary:
//
//    CAAPstINFWire CATIVisProperties  libCAAPstImplementProperties
//

//-----------------------------------------------------------------------------

CAAEPstINFVisPropertiesWire::CAAEPstINFVisPropertiesWire()
{
  cout << "CAAEPstINFVisPropertiesWire::CAAEPstINFVisPropertiesWire" << endl;
}

CAAEPstINFVisPropertiesWire::~CAAEPstINFVisPropertiesWire()
{
  cout << "CAAEPstINFVisPropertiesWire::~CAAEPstINFVisPropertiesWire" << endl;
}

//-----------------------------------------------------------------------------

HRESULT CAAEPstINFVisPropertiesWire::IsGeomTypeDefined(CATVisGeomType & iGeomType)
{
    HRESULT rc = E_FAIL ;

    if ( (CATVPLine == iGeomType) || (CATVPPoint == iGeomType) || (CATVPGlobalType == iGeomType) )
        rc =  S_OK ;

    return rc ;
} 
//-----------------------------------------------------------------------------

HRESULT CAAEPstINFVisPropertiesWire::GetSubTypeFromPath(CATPathElement & iPathElement,
                                                     CATVisPropertyType           iPropertyType,
                                                     CATVisGeomType             & oGeomType,
                                                     unsigned int               & oPropertyNumber)
{

    HRESULT rc = E_FAIL ;

    switch ( iPropertyType )
    {
    // the color is for the line
    case CATVPColor:
    case CATVPLineType:
    case CATVPWidth:
        oGeomType = CATVPLine ;
        rc = S_OK ;
        break;

    case CATVPSymbol:
        oGeomType = CATVPPoint ; 
        rc = S_OK ;
        break;
    }
    
    // Set always zero 
    oPropertyNumber = 0 ;

    return rc ;
}
