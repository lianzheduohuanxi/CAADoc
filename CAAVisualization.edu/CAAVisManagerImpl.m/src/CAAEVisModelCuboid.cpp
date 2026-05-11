// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAAEVisModelCuboid.h"

// Visualization Framework
#include "CATMathPointf.h"

// System Framework
#include "CATErrorDef.h" // for the SUCCEEDED macro

// Standard Library
#include <iostream.h>

//-------------------------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CAAIVisModelCuboid.h"
TIE_CAAIVisModelCuboid(CAAEVisModelCuboid);

// To declare that the class is a data extension of CAAVisModelCuboid
//
CATImplementClass(CAAEVisModelCuboid,DataExtension,CATBaseUnknown,CAAVisModelCuboid);

// 
// To declare that CAAEVisModelCuboid implements CAAIVisModelCuboid, insert 
// the following line in the interface dictionary:
//
//    CAAVisModelCuboid CAAIVisModelCuboid  libCAAVisManagerImpl
//
//--------------------------------------------------------------------------------------------


CAAEVisModelCuboid::CAAEVisModelCuboid():_VerticesTab(NULL)
{
  cout << "CAAEVisModelCuboid::CAAEVisModelCuboid" << endl;
}

//--------------------------------------------------------------------------------------------

CAAEVisModelCuboid::~CAAEVisModelCuboid()
{
  cout << "CAAEVisModelCuboid::~CAAEVisModelCuboid" << endl;

  if ( NULL !=  _VerticesTab )
  {
     delete [] _VerticesTab ;
     _VerticesTab = NULL ;
  }

}

//----------------------------------------------------------------------------

HRESULT CAAEVisModelCuboid::GetVertices(float ** oVertices) 
{
   HRESULT rc = E_FAIL ;

   if ( NULL != oVertices )
   {
      *oVertices = _VerticesTab ;
   }
   return rc ;
}

//----------------------------------------------------------------------------

HRESULT CAAEVisModelCuboid::SetVertices(float * iVerticesTab) 
{

   if ( NULL !=  _VerticesTab )
   {
      delete [] _VerticesTab ;
      _VerticesTab = NULL ;
   }
    
   if ( NULL !=  iVerticesTab )
   {
      _VerticesTab = new float [3*8];
      _VerticesTab = (float *) memcpy(_VerticesTab,iVerticesTab,3*8*sizeof(float));
   }

   return S_OK  ;

}
