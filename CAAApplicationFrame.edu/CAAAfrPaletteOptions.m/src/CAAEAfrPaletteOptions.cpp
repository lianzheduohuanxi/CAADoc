// COPYRIGHT DASSAULT SYSTEMES 2003

//Local framework
#include "CAAEAfrPaletteOptions.h"
#include "CAAAfrEltCountHeader.h"   // The header to instantiate

// ApplicationFrame framework
#include "CATAfrCommandHeaderServices.h" // To check if the header already exists

//Standard library
#include "iostream.h"

//----------------------------------------------------------------------------
// To create the TIE Object
#include <TIE_CATIAfrPaletteOptions.h>
TIE_CATIAfrPaletteOptions(CAAEAfrPaletteOptions);

// To declare that the class 
// is a DataExtension of (late type) CAAAfrGeoCreationWkb_Palette
//
CATImplementClass(CAAEAfrPaletteOptions, 
                  DataExtension, 
                  CATBaseUnknown, 
                  CAAAfrGeoCreationWkb_Palette);


//----------------------------------------------------------------------------
CAAEAfrPaletteOptions::CAAEAfrPaletteOptions():CATBaseUnknown()
{
    cout <<" CAAEAfrPaletteOptions::CAAEAfrPaletteOptions" << endl;
}

CAAEAfrPaletteOptions::~CAAEAfrPaletteOptions()
{
    cout <<" CAAEAfrPaletteOptions::~CAAEAfrPaletteOptions" << endl;
}

//----------------------------------------------------------------------------

CATLISTP(CATCommandHeader) CAAEAfrPaletteOptions::GetPaletteOptions()
{
    cout <<" CAAEAfrPaletteOptions::GetPaletteOptions" << endl;

    CATLISTP(CATCommandHeader) TheListToReturn ;


    CATCommandHeader *pMyCommand = NULL ;
    HRESULT rc= ::CATAfrGetCommandHeader("CAAAfrEltCountHdr",pMyCommand);

    if ( FAILED(rc) || ( NULL ==pMyCommand) )
    {
        // The command header is created if it does not exist in the 
        // list of command header associated with the current editor
        pMyCommand = new CAAAfrEltCountHeader("CAAAfrEltCountHdr");
    } 

    if ( NULL != pMyCommand)
    {
       TheListToReturn.Append(pMyCommand);
    }

    return TheListToReturn ;
}

