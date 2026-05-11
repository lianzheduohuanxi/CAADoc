// COPYRIGHT DASSAULT SYSTEMES 2003

// local framework
#include "CAAEAfrCommandHeaderRepForMRU.h"
#include "CAAAfrMRURep.h"

// Standard library
#include <iostream.h>
#include <CATUnicodeString.h>

//----------------------------------------------------------------------------

#include <TIE_CATIAfrCommandHeaderRep.h>
TIE_CATIAfrCommandHeaderRep(CAAEAfrCommandHeaderRepForMRU);

// To declare that the class CAAEAfrCommandHeaderRepForMRU
// is a DataExtension of CAAAfrMRUHeader component
//
CATImplementClass(CAAEAfrCommandHeaderRepForMRU, 
                  DataExtension,
                  CATBaseUnknown, 
                  CAAAfrMRUHeader);

//----------------------------------------------------------------------------
CAAEAfrCommandHeaderRepForMRU::CAAEAfrCommandHeaderRepForMRU() : 
    CATBaseUnknown()
   
{
   cout <<"CAAEAfrCommandHeaderRepForMRU::CAAEAfrCommandHeaderRepForMRU" << endl;
}

//----------------------------------------------------------------------------

CAAEAfrCommandHeaderRepForMRU::~CAAEAfrCommandHeaderRepForMRU()
{
   cout <<"CAAEAfrCommandHeaderRepForMRU::~CAAEAfrCommandHeaderRepForMRU" << endl;
}

//----------------------------------------------------------------------------

HRESULT CAAEAfrCommandHeaderRepForMRU::CreateToolbarRep (const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep)
{
  return E_FAIL;
}

//----------------------------------------------------------------------------

HRESULT CAAEAfrCommandHeaderRepForMRU::CreateMenuRep (const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep)
{
  cout <<" CAAEAfrCommandHeaderRepForMRU::CreateMenuRep " << endl;

   HRESULT rc = E_FAIL ;

   if ( oHdrRep != NULL )
   {
      CATString Name = "CAAAfrMRURepId"  ;
      CAAAfrMRURep * pMRURep = new CAAAfrMRURep(iParent,Name);

      *oHdrRep = (CATAfrCommandHeaderRep *) pMRURep ;
      rc = S_OK ;
   }

   return rc ;
}

//----------------------------------------------------------------------------

HRESULT CAAEAfrCommandHeaderRepForMRU::CreateCtxMenuRep (const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep)
{
  return E_FAIL;
}

//----------------------------------------------------------------------------
