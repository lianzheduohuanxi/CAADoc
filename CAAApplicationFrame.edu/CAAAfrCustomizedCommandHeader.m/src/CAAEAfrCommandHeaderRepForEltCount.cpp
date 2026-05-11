// COPYRIGHT DASSAULT SYSTEMES 2003

// local framework
#include "CAAEAfrCommandHeaderRepForEltCount.h"
#include "CAAAfrEltCountRep.h"

// Standard library
#include <iostream.h>

//----------------------------------------------------------------------------

#include <TIE_CATIAfrCommandHeaderRep.h>
TIE_CATIAfrCommandHeaderRep(CAAEAfrCommandHeaderRepForEltCount);

// To declare that the class CAAEAfrCommandHeaderRepForEltCount
// is a DataExtension of CAAAfrEltCountHeader component
//
CATImplementClass(CAAEAfrCommandHeaderRepForEltCount, 
                  DataExtension,
                  CATBaseUnknown, 
                  CAAAfrEltCountHeader);

//----------------------------------------------------------------------------
CAAEAfrCommandHeaderRepForEltCount::CAAEAfrCommandHeaderRepForEltCount() : 
    CATBaseUnknown()
   
{
   cout <<"CAAEAfrCommandHeaderRepForEltCount::CAAEAfrCommandHeaderRepForEltCount" << endl;
}

//----------------------------------------------------------------------------

CAAEAfrCommandHeaderRepForEltCount::~CAAEAfrCommandHeaderRepForEltCount()
{
   cout <<"CAAEAfrCommandHeaderRepForEltCount::~CAAEAfrCommandHeaderRepForEltCount" << endl;
}

//----------------------------------------------------------------------------

HRESULT CAAEAfrCommandHeaderRepForEltCount::CreateToolbarRep (const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep)
{
   HRESULT rc = E_FAIL ;

   if ( oHdrRep != NULL )
   {
      CATString Name = "CAAAfrEltCountRepId" ;
      CAAAfrEltCountRep * pEltCountRep = new CAAAfrEltCountRep(iParent,Name);

      *oHdrRep = (CATAfrCommandHeaderRep *) pEltCountRep ;
      rc = S_OK ;
   }

   return rc ;
}

//----------------------------------------------------------------------------

HRESULT CAAEAfrCommandHeaderRepForEltCount::CreateMenuRep (const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep)
{
  cout <<" CAAEAfrCommandHeaderRepForEltCount::CreateMenuRep " << endl;

  return E_FAIL;

}

//----------------------------------------------------------------------------

HRESULT CAAEAfrCommandHeaderRepForEltCount::CreateCtxMenuRep (const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep)
{
  return E_FAIL;
}

//----------------------------------------------------------------------------
