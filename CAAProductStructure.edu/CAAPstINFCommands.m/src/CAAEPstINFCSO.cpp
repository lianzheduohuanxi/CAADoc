// COPYRIGHT Dassault Systemes 2002

// Local Framework
#include "CAAEPstINFCSO.h"

// ApplicationFrame Framework
#include "CATICSOFilter.h"

// Others
#include "iostream.h"
 
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATICSOFilter.h"
TIE_CATICSOFilter( CAAEPstINFCSO);

// To declare that the class is a data extension of CAAPstINFLine, CAAPstINFPoint and
// CAAPstINFWire
//
CATBeginImplementClass( CAAEPstINFCSO,
                        DataExtension,
                        CATBaseUnknown,
                        CAAPstINFPoint );
CATAddClassExtension(CAAPstINFLine);
CATAddClassExtension(CAAPstINFWire);
CATEndImplementClass(CAAEPstINFCSO); 

// To declare that CAAEPstINFCSO implements CATICSOFilter for the
// CAAPstINFPoint, CAAPstINFLine and CAAPstINFWire components,
// insert the following lines in the interface dictionary:
//
//    CAAPstINFPoint CATICSOFilter libCAAINFCommands
//    CAAPstINFLine  CATICSOFilter libCAAINFCommands
//    CAAPstINFWire  CATICSOFilter libCAAINFCommands
//

//-----------------------------------------------------------------------------
// CAAEPstINFCSO : constructor
//-----------------------------------------------------------------------------
CAAEPstINFCSO::CAAEPstINFCSO():
    CATBaseUnknown()
{
}
 
//-----------------------------------------------------------------------------
// CAAEPstINFCSO : destructor
//-----------------------------------------------------------------------------
CAAEPstINFCSO::~CAAEPstINFCSO()
{
}
 
//-----------------------------------------------------------------------------
// Implements CATICSOFilter::CommandIsAvailable
// All of the commands are to be made available.
//-----------------------------------------------------------------------------
HRESULT CAAEPstINFCSO::CommandIsAvailable (const char *pHeaderID, const CATCSO *pCSO)
{
	cout << "******CAAEPstINFCSO::CommandIsAvailable" << endl;
    return S_OK;
}

//-----------------------------------------------------------------------------
// Implements CATICSOFilter::AvailableElements
//-----------------------------------------------------------------------------
HRESULT CAAEPstINFCSO::AvailableElements (const char *pHeaderID , const CATCSO *pCSO, CATListValCATBaseUnknown_var **spAvailableElements)
{
	cout << "******CAAEPstINFCSO::AvailableElements" << endl;
    return S_OK;
}

