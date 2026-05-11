// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAEPstINFVisPropertiesPoint.h"

// Visualization Framework 
#include "CATIVisProperties.h"

// Others
#include "iostream.h"

//-----------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CATIVisProperties.h"
TIE_CATIVisProperties(CAAEPstINFVisPropertiesPoint);

// To declare that the class is a data extension of CAASysLine
//
CATImplementClass(CAAEPstINFVisPropertiesPoint, DataExtension, CATBaseUnknown, CAAPstINFPoint);
// 
// To declare that CAAEPstINFVisPropertiesPoint implements CATIVisProperties, insert 
// the following line in the interface dictionary:
//
//    CAAPstINFPoint CATIVisProperties  libCAAPstImplementProperties
//

//-----------------------------------------------------------------------------

CAAEPstINFVisPropertiesPoint::CAAEPstINFVisPropertiesPoint()
{
  cout << "CAAEPstINFVisPropertiesPoint::CAAEPstINFVisPropertiesPoint" << endl;
}

CAAEPstINFVisPropertiesPoint::~CAAEPstINFVisPropertiesPoint()
{
  cout << "CAAEPstINFVisPropertiesPoint::~CAAEPstINFVisPropertiesPoint" << endl;
}

//-----------------------------------------------------------------------------

HRESULT CAAEPstINFVisPropertiesPoint::IsGeomTypeDefined(CATVisGeomType & iGeomType)
{
    HRESULT rc = E_FAIL ;

    if ( (CATVPPoint == iGeomType) || (CATVPGlobalType == iGeomType) )
        rc =  S_OK ;
    return rc ;
} 
//-----------------------------------------------------------------------------

HRESULT CAAEPstINFVisPropertiesPoint::GetSubTypeFromPath(CATPathElement & iPathElement,
                                                         CATVisPropertyType        iPropertyType,
                                                         CATVisGeomType          & oGeomType,
                                                         unsigned int            & oPropertyNumber)
{
    HRESULT rc = E_FAIL ;

    switch ( iPropertyType )
    {
    case CATVPColor:
    case CATVPSymbol:
        oGeomType = CATVPPoint ;
        rc = S_OK ;
        break;

    }
    
    // Set always 0
    oPropertyNumber = 0 ;
    
    return rc ;
}


