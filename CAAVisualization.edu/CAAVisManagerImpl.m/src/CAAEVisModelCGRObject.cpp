// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAAEVisModelCGRObject.h"
#include "CAAIVisModelObject.h"

//Visualization FrameWork
#include "CAT3DRep.h"
#include "CAT3DBagRep.h"
#include "CATReadWriteCgr.h"

// System Framework
#include "CATErrorDef.h" // for the SUCCEEDED macro

// Standard Library
#include <iostream.h>

//-------------------------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CAAIVisModelCGRObject.h"
TIE_CAAIVisModelCGRObject(CAAEVisModelCGRObject);

// To declare that the class is a data extension of CAAVisModelCGRObject
//
CATImplementClass(CAAEVisModelCGRObject,DataExtension,CATBaseUnknown,CAAVisModelCGRObject);

// 
// To declare that CAAEVisModelCGRObject implements CAAIVisModelCGRObject, insert 
// the following line in the interface dictionary:
//
//    CAAVisModelCGRObject CAAIVisModelCGRObject  libCAAVisManagerImpl
//
//--------------------------------------------------------------------------------------------


CAAEVisModelCGRObject::CAAEVisModelCGRObject():_pCGRRep(NULL),_pRep(NULL)
{
  cout << "CAAEVisModelCGRObject::CAAEVisModelCGRObject" << endl;
}

//--------------------------------------------------------------------------------------------

CAAEVisModelCGRObject::~CAAEVisModelCGRObject()
{
  cout << "CAAEVisModelCGRObject::~CAAEVisModelCGRObject" << endl;

  if (NULL != _pRep)
  {
      CATModelIdentificator ident ;
      _pCGRRep->SetNewId(ident);
      _pRep->Destroy();
      _pRep = NULL ;
  }
  _pCGRRep = NULL ;

}

//----------------------------------------------------------------------------

HRESULT CAAEVisModelCGRObject::GetCGRRep(CATRep ** oCGRRep)
{
    
    HRESULT rc = E_FAIL ;
    if ( NULL != oCGRRep )
    {
       *oCGRRep =  _pCGRRep;
       rc = S_OK ;
    }
    
    return rc;
}

//----------------------------------------------------------------------------

HRESULT CAAEVisModelCGRObject::ReadCGRFile(const char * iCGRFileName)
{
   HRESULT rc = E_FAIL ;

   if ( (NULL != iCGRFileName) && ( NULL == _pCGRRep) )
   {
      CAAIVisModelObject *pICAAIVisOnCGRObject = NULL ;
      HRESULT rc = QueryInterface(IID_CAAIVisModelObject, (void**)&pICAAIVisOnCGRObject);
      if (SUCCEEDED(rc))
      {
         pICAAIVisOnCGRObject->SetType(iCGRFileName);

         pICAAIVisOnCGRObject->Release();
         pICAAIVisOnCGRObject = NULL ;

         char * cgr_name = (char *) iCGRFileName;
         _pCGRRep = CATReadCgr(cgr_name,USE_LODS_TEXTURE_EDGE);
      
         if (NULL != _pCGRRep)
         {
            _pRep = new CAT3DBagRep();
            _pRep->AddChild( *_pCGRRep);
            CATModelIdentificator ident(GetImpl());
            _pCGRRep->SetNewId(ident);

            rc = S_OK ;
         }
      }
   }

   return rc;
}
