// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAAEVis3DGeoVisuForSet.h"
#include "CAAIVisModelObject.h"

// Visualization framework
#include "CAT3DBagRep.h"
#include "CATVisManager.h"

// Standard Library
#include <iostream.h>

//-------------------------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CATI3DGeoVisu.h"
TIE_CATI3DGeoVisu(CAAEVis3DGeoVisuForSet);

// To declare that the class is a data extension of CAAVisModelSetOfObject
//
CATImplementClass(CAAEVis3DGeoVisuForSet,DataExtension,CATBaseUnknown,CAAVisModelSetOfObject);

// 
// To declare that CAAEVis3DGeoVisuForSet implements CATI3DGeoVisu, insert 
// the following line in the interface dictionary:
//
//    CAAVisModelSetOfObject CATI3DGeoVisu  libCAAVisManagerImpl
//
//--------------------------------------------------------------------------------------------

CAAEVis3DGeoVisuForSet::CAAEVis3DGeoVisuForSet()
{
  cout << "CAAEVis3DGeoVisuForSet::CAAEVis3DGeoVisuForSet" << endl;
}

//--------------------------------------------------------------------------------------------

CAAEVis3DGeoVisuForSet::~CAAEVis3DGeoVisuForSet()
{
  cout << "CAAEVis3DGeoVisuForSet::~CAAEVis3DGeoVisuForSet" << endl;
}

//--------------------------------------------------------------------------------------------

CATRep * CAAEVis3DGeoVisuForSet::BuildRep()
{
   CAT3DBagRep * bag = new CAT3DBagRep();

   CAAIVisModelObject *pO=NULL;
   HRESULT rc = QueryInterface(IID_CAAIVisModelObject,(void **)&pO);

   list<CATBaseUnknown> * children=NULL;
   if ( SUCCEEDED(rc) )
   {
      children =  pO->GetChildren();
      pO->Release();
      pO = NULL ;
   }

   if (NULL != children)
   {
      CATVisManager *vm = CATVisManager::GetVisManager();
      CATBaseUnknown *g = NULL ;
      int ii;
      for (ii=0; g=(*children)[ii];ii++)
      {
          CATModelIdentificator ident(g);
          CATRep * rep = vm->BuildRep(ident);
          if (NULL != rep)
          {
             bag->AddChild( *((CAT3DRep*)rep) );
          }
      }
   }

   return bag;
}
