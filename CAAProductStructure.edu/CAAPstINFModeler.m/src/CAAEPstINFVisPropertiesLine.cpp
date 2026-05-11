// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAEPstINFVisPropertiesLine.h"

// Visualization Framework 
#include "CATIVisProperties.h"

// Others
#include "iostream.h"


//-----------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CATIVisProperties.h"
TIE_CATIVisProperties(CAAEPstINFVisPropertiesLine);

// To declare that the class is a data extension of CAASysLine
//
CATImplementClass(CAAEPstINFVisPropertiesLine, DataExtension, CATBaseUnknown, CAAPstINFLine);
// 
// To declare that CAAEPstINFVisPropertiesLine implements CATIVisProperties, insert 
// the following line in the interface dictionary:
//
//    CAAPstINFLine CATIVisProperties  libCAAPstImplementProperties
//

//-----------------------------------------------------------------------------

CAAEPstINFVisPropertiesLine::CAAEPstINFVisPropertiesLine()
{
  cout << "CAAEPstINFVisPropertiesLine::CAAEPstINFVisPropertiesLine" << endl;
}

CAAEPstINFVisPropertiesLine::~CAAEPstINFVisPropertiesLine()
{
  cout << "CAAEPstINFVisPropertiesLine::~CAAEPstINFVisPropertiesLine" << endl;
}

//-----------------------------------------------------------------------------

HRESULT CAAEPstINFVisPropertiesLine::IsGeomTypeDefined(CATVisGeomType & iGeomType)
{
    HRESULT rc = E_FAIL ;

    if ( (CATVPLine == iGeomType) || (CATVPGlobalType == iGeomType) )
        rc =  S_OK ;

    return rc ;
} 
//-----------------------------------------------------------------------------

HRESULT CAAEPstINFVisPropertiesLine::GetSubTypeFromPath(CATPathElement & iPathElement,
                                                     CATVisPropertyType           iPropertyType,
                                                     CATVisGeomType             & oGeomType,
                                                     unsigned int               & oPropertyNumber)
{
    HRESULT rc = E_FAIL ;

    switch ( iPropertyType )
    {
    case CATVPColor:
    case CATVPLineType:
    case CATVPWidth:
        oGeomType = CATVPLine ;
        rc = S_OK ;
        break;

    }

	// Set always 0
    oPropertyNumber = 0 ;
    
	return rc ;
}
