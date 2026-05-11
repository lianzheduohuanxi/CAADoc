// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CAAVisManagerDefaultDocument.h"

//Local FrameWork

// 1) Components
#include "CAAVisModelSetOfObject.h"
#include "CAAVisModelSphere.h"
#include "CAAVisModelCuboid.h"

// 2) Interface to acceed to these components
#include "CAAIVisModelObject.h"
#include "CAAIVisModelSphere.h"
#include "CAAIVisModelCuboid.h"

// System Framework
#include "CATErrorDef.h"  // for the SUCCEEDED macro

// Visu Framework
#include "CATMathPointf.h" 

#include <iostream.h>

//-------------------------------------------------------------------------------
CAAVisManagerDefaultDocument::CAAVisManagerDefaultDocument () : 
                               CAAVisManagerDocument("CAAVisManagerDefaultDocument")
{
    CreateModel();
}

//-------------------------------------------------------------------------------

CAAVisManagerDefaultDocument::~CAAVisManagerDefaultDocument()
{
}

//-------------------------------------------------------------------------------

void CAAVisManagerDefaultDocument::CreateModel()
{
  // The Model is:
  // a Set which contains :
  //   - a blue cuboid 
  //   - a white sphere
  //
   _pRootContainer = new CAAVisModelSetOfObject();

   CAAIVisModelObject *PtrToObject= NULL;
   HRESULT rc  = _pRootContainer->QueryInterface(IID_CAAIVisModelObject,(void **)&PtrToObject);
   if ( SUCCEEDED(rc))
   {
      CAAVisModelSphere * pSphere = new CAAVisModelSphere();

      CAAIVisModelSphere *piVisModelOnSphere = NULL ;
      HRESULT rc = pSphere->QueryInterface(IID_CAAIVisModelSphere, (void**)&piVisModelOnSphere);
      if (SUCCEEDED(rc))
      {
         piVisModelOnSphere->SetCenter(CATMathPointf(0.f,0.f,0.f));
         piVisModelOnSphere->SetRadius(30.f);

         // New Object in the Set 
         PtrToObject->AddChild (pSphere);
     
         pSphere->Release();
         pSphere = NULL ;

         piVisModelOnSphere->Release();
         piVisModelOnSphere = NULL ;
      }

      CAAVisModelCuboid * pCuboid = new CAAVisModelCuboid();

      CAAIVisModelCuboid *piVisModelOnCuboid = NULL ;
      rc = pCuboid->QueryInterface(IID_CAAIVisModelCuboid, (void**)&piVisModelOnCuboid);
      if (SUCCEEDED(rc))
      {
         // vertices array for building a cuboid.
         float tab[3*8] = { 0.f,0.f,0.f,
                            100.f,0.f,0.f,
                            100.f,0.f,-100.f,
                            0.f,0.f,-100.f,
                            0.f,100.f,-100.f,
                            0.f,100.f,0.f,
                            100.f,100.f,0.f,
                            100.f,100.f,-100.f}; 

         piVisModelOnCuboid->SetVertices(tab);

         // New Object in the Set 
         PtrToObject->AddChild (pCuboid);

         pCuboid->Release();
         pCuboid = NULL ;

         piVisModelOnCuboid->Release();
         piVisModelOnCuboid = NULL ;
      }

      PtrToObject->Release();
      PtrToObject = NULL ;
   }
 
}

//-------------------------------------------------------------------------------
