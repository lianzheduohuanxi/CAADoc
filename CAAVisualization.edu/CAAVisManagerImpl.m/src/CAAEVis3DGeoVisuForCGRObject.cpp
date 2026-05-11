// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAAEVis3DGeoVisuForCGRObject.h"
#include "CAAIVisModelCGRObject.h"

// Visualization framework
#include "CATRep.h"

// Standard Library
#include <iostream.h>

//-------------------------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CATI3DGeoVisu.h"

TIE_CATI3DGeoVisu(CAAEVis3DGeoVisuForCGRObject);

// To declare that the class is a data extension of CAAVisModelCGRObject
//
CATImplementClass(CAAEVis3DGeoVisuForCGRObject,DataExtension,CATBaseUnknown,CAAVisModelCGRObject);

// 
// To declare that CAAEVis3DGeoVisuForCGRObject implements CATI3DGeoVisu, insert 
// the following line in the interface dictionary:
//
//    CAAVisModelCGRObject CATI3DGeoVisu  libCAAVisManagerImpl
//
//--------------------------------------------------------------------------------------------

CAAEVis3DGeoVisuForCGRObject::CAAEVis3DGeoVisuForCGRObject()
{
  cout << "CAAEVis3DGeoVisuForCGRObject::CAAEVis3DGeoVisuForCGRObject" << endl;
}

//--------------------------------------------------------------------------------------------

CAAEVis3DGeoVisuForCGRObject::~CAAEVis3DGeoVisuForCGRObject()
{
  cout << "CAAEVis3DGeoVisuForCGRObject::~CAAEVis3DGeoVisuForCGRObject" << endl;
  UnreferenceRep();
}

//--------------------------------------------------------------------------------------------

CATRep * CAAEVis3DGeoVisuForCGRObject::BuildRep()
{

   CATRep * pRepToReturn = NULL ;

   CAAIVisModelCGRObject *pIVisModelCGRObject =NULL;
   HRESULT rc = QueryInterface(IID_CAAIVisModelCGRObject,(void **)&pIVisModelCGRObject);
   if ( SUCCEEDED(rc) )
   {
      CATRep *pRep = NULL ;
      rc = pIVisModelCGRObject->GetCGRRep(&pRep);

      if ( SUCCEEDED(rc) )
      {
         pRepToReturn= pRep ;
      }

      pIVisModelCGRObject->Release();
      pIVisModelCGRObject = NULL ;
   }

   return pRepToReturn ;
}

//-------------------------------------------------------------------------------
CATRep * CAAEVis3DGeoVisuForCGRObject::GetRep()
{
   if ( NULL != _rep)
      return _rep;
   else
   {
      _rep = BuildRep();
      
      if ( NULL != _rep)
      {    
         //  check if default identificator has to be put
         if ( _rep->GetIdentificator() && ( _rep->GetIdentificator()->GetIntId() == 0 ) )
         {
            CATModelIdentificator ident(this);
            _rep->SetNewId(ident);
         }
      }
      return _rep;
   }
}

   

//------------------------------------------------------------------------------------
void CAAEVis3DGeoVisuForCGRObject::UnreferenceRep ()
{
   _rep = NULL;
}





