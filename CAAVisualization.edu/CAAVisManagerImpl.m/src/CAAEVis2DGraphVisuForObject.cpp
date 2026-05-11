// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAAEVis2DGraphVisuForObject.h"

// Visualization FrameWork
#include "CAT3x3Matrix.h"
#include "CATVisManager.h"

// Mathematics FrameWork
#include "CATMathVector2Df.h"

// Local FrameWork
#include "CAAVis2DGraphBoxRep.h" // The Graphic Representation 

#include "CAAIVisModelObject.h"  // Interface to access to the data
#include "CAAIVis2DGraphVisu.h"  // Visual Interface

// Standard Library
#include <iostream.h>

//-------------------------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CAAIVis2DGraphVisu.h"
TIE_CAAIVis2DGraphVisu(CAAEVis2DGraphVisuForObject);

// To declare that the class is a data extension of CAAVisModelObject
//
CATImplementClass(CAAEVis2DGraphVisuForObject,DataExtension,CATBaseUnknown,CAAVisModelObject);

// 
// To declare that CAAEVis2DGraphVisuForObject implements CAAIVis2DGraphVisu, insert 
// the following line in the interface dictionary:
//
//    CAAVisModelObject CAAIVis2DGraphVisu  libCAAVisManagerImpl
//
//--------------------------------------------------------------------------------------------


CAAEVis2DGraphVisuForObject::CAAEVis2DGraphVisuForObject()
{
  cout << "CAAEVis2DGraphVisuForObject::CAAEVis2DGraphVisuForObject" << endl;
}

//--------------------------------------------------------------------------------------------

CAAEVis2DGraphVisuForObject::~CAAEVis2DGraphVisuForObject()
{
  cout << "CAAEVis2DGraphVisuForObject::~CAAEVis2DGraphVisuForObject" << endl;
}

//--------------------------------------------------------------------------------------------

CATRep * CAAEVis2DGraphVisuForObject::BuildRep()
{     
   cout << "CAAEVis2DGraphVisuForObject::BuildRep"<< endl;

   // The rep to return 
   CAT2DBagRep * pCurrentObjectBagRep = NULL ;

   
   CAAIVisModelObject *PtrVMO=NULL;
   HRESULT rc = QueryInterface(IID_CAAIVisModelObject,(void **)&PtrVMO);
   if ( SUCCEEDED(rc) )
   {
      // Retrieves the data type
      char * Type = NULL ;
      PtrVMO->GetType(&Type);

      // Builds a box with the name of the current object.
      // Size box : 11 pixels in height and 8 pixels in width
      pCurrentObjectBagRep =  new CAAVis2DGraphBoxRep(Type);

      delete [] Type ;

      // Defines the translation ( horizontal and vertical ) 
      // to apply at it's first child if one. This translation allows to 
      // represent a "tree". At each node there is 10 pixels moved right.
      // Beetween each boxes there is 20 pixels to the top.
      //
      // a) horizontal translation vector
      //
      CATMathVector2Df translatation_v (10.f,0.f);
      _PositioningMat.SetTranslation(translatation_v);

      // b) added to a vertical translation  
      IncrementPositioningMatrix();
   
      // If the current object has at least one parent, it must be moved up and
      // right. The translation is given by its first parent.
      //
      list<CATBaseUnknown> *parents = PtrVMO->GetParents();
      if (NULL != parents)
      {
         // we use the first parent for positionning the current graphical representation.
         CATBaseUnknown *parent = (*parents)[0];
         if (NULL != parent)
         {
            CAAIVis2DGraphVisu * pi2DGraphVisuOnParent = NULL;
            HRESULT rc1 = parent->QueryInterface(IID_CAAIVis2DGraphVisu,
                                                 (void **)&pi2DGraphVisuOnParent);
            if ( SUCCEEDED(rc1) )
            {
               // Retrieves the matrix of the first parent
               CAT3x3Matrix & pos_mat = pi2DGraphVisuOnParent->GetPositioningMatrix();

               // The current object is moved
               pCurrentObjectBagRep->SetMatrix(pos_mat);

               // For the next child, the matrix is moved 20 pixels up .
               pi2DGraphVisuOnParent->IncrementPositioningMatrix();

               pi2DGraphVisuOnParent->Release();
               pi2DGraphVisuOnParent= NULL;
            }
         }
      } 
      
      // we look for its children and ask for their construction.
      list<CATBaseUnknown> * children = PtrVMO->GetChildren();

      // The visu manager controls the Interface to use for the child
      // 
      CATVisManager * pVisuManager = CATVisManager::GetVisManager() ;
      if ( (NULL != children) && ( NULL != pVisuManager) )
      {
         CATBaseUnknown *child = NULL ;
         int ii;
         for (ii=0; child = (*children)[ii];ii++)
         {
            //we create an identifier which holds a pointer to the object we are working on.
            CATModelIdentificator ident(child);

            // we ask to the VisManager to build the visualization
            // of the child object.
            CAT2DBagRep * rep =  (CAT2DBagRep * ) pVisuManager->BuildRep(ident);
            if ( NULL != rep )
            {
               pCurrentObjectBagRep->AddChild( *rep);
            }
         }
      }
      
      // Done with the pointer
      PtrVMO->Release();
      PtrVMO = NULL ;
   }

   return pCurrentObjectBagRep;
}
