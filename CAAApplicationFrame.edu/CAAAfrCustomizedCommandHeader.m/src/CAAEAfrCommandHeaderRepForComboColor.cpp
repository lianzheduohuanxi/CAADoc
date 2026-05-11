// COPYRIGHT DASSAULT SYSTEMES 2003

// local framework
#include "CAAEAfrCommandHeaderRepForComboColor.h"
#include "CAAAfrComboRep.h"

// Standard library
#include <iostream.h>

//----------------------------------------------------------------------------

#include <TIE_CATIAfrCommandHeaderRep.h>
TIE_CATIAfrCommandHeaderRep(CAAEAfrCommandHeaderRepForComboColor);

// To declare that the class CAAEAfrCommandHeaderRepForComboColor
// is a DataExtension of CAAAfrComboColorHeader component
//
CATImplementClass(CAAEAfrCommandHeaderRepForComboColor, 
                  DataExtension,
                  CATBaseUnknown, 
                  CAAAfrComboColorHeader);

//----------------------------------------------------------------------------

CAAEAfrCommandHeaderRepForComboColor::CAAEAfrCommandHeaderRepForComboColor():
        CATBaseUnknown()   
{
   cout <<" CAAEAfrCommandHeaderRepForComboColor::CAAEAfrCommandHeaderRepForComboColor" << endl;
}

//----------------------------------------------------------------------------

CAAEAfrCommandHeaderRepForComboColor::~CAAEAfrCommandHeaderRepForComboColor()
{
    cout <<" CAAEAfrCommandHeaderRepForComboColor::CAAEAfrCommandHeaderRepForComboColor" << endl;
}

//----------------------------------------------------------------------------

HRESULT CAAEAfrCommandHeaderRepForComboColor::CreateToolbarRep (const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep)
{
   cout <<" CAAEAfrCommandHeaderRepForComboColor::CreateToolbarRep" << endl;

   HRESULT rc = E_FAIL ;

   if ( oHdrRep != NULL )
   {
      CATString Name = "CAAAfrComboRepId" ;
      CAAAfrComboRep * pComboRep = new CAAAfrComboRep(iParent,Name);

      *oHdrRep = (CATAfrCommandHeaderRep *) pComboRep ;
      rc = S_OK ;
   }

   return rc ;
}

//----------------------------------------------------------------------------

HRESULT CAAEAfrCommandHeaderRepForComboColor::CreateMenuRep (const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep)
{
  return  E_FAIL ;
}

//----------------------------------------------------------------------------

HRESULT CAAEAfrCommandHeaderRepForComboColor::CreateCtxMenuRep (const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep)
{
  return E_FAIL;
}

//----------------------------------------------------------------------------

