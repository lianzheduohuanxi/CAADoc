// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of the sample:
//  -----------------------
//
//  This Sample illustrates the Object Modeler derivation. 
//
//  -----------------------
//  |                     |-o CATICreateInstance 
//  | CAASysSurface       |-o CAAISysSurfaceProperties, via CAAESysSurfaceProperties
//  |                     |
//  | impl                |-o CAAISysSurfaceArea , via CAAESysSurfaceArea   
//  ---+-----------------+-
//     |                 |
//     | C++ Derivation  | OM Derivation 
//     | of the          | of the component
//     | implementation  |
//     |                 |
//     |                 |
//     |                 |
//  ---^-----------------^---
//  | impl                  |-o CATICreateInstance 
//  |                       |-o CAAISysRevolAxis ,via CAAESysRevolAxis
//  |                       |
//  |  CAASysRevolSurface   |-o CAAISysSurfaceArea , via CAAESysRevolSurfaceArea     
//  |                       |
//  -------------------------
//
//
//  The CAASysSurface component implements by extension 3 interfaces:
//    - CATICreateInstance       (code extension)
//    - CAAISysSurfaceProperties (data extension)
//    - CAAISysSurfaceArea       (data extension)
//
//  The CAASysRevolSurface component which OM derives from CAASysSurface 
//  implements :
//    - CATICreateInstance       (code extension)
//    - by data extension the CAAISysRevolAxis interface
//    - by OM derivation, the CAAISysSurfaceProperties interface
//    - by data extension redefines the CAAISysSurfaceArea interface. 
//
//  The goal of this sample: 
//     - When you create a CAASysRevolSurface component, you don't create a 
//       CAASysSurface component, but you create extension dedicated
//         >> See QI on CAAISysSurfaceProperties
//       to the interface implemented by CAASysSurface.
//     - With any interface pointer of a component you get always the good
//       interface pointer.  
//         >> See the 2 QI on CAAISysSurfaceArea
//
//=============================================================================
//  Usage:
//  ------
//
//  Type:
//    CAASysDerivationOM
//  
//  The different traces of the sample appears on the standard output.
//
//  Return Code:
//     0 : OK
//     1 : KO
//
//=============================================================================

// System Framework
#include "CATBaseUnknown.h" 
#include "CATInstantiateComponent.h" 
#include "CATErrorDef.h" // For SUCCEEDED/FAILED macro

// Local Framework
#include "CAAISysSurfaceProperties.h"
#include "CAAISysSurfaceArea.h"
#include "CAAISysRevolAxis.h"

// C++ standard library    
#include <iostream.h>     // To display traces

int main()
{
  int ReturnCode = 0;
 
  cout << ">>> BeginApplication"<< endl;
  cout << endl;

  // ------------------------------------------------------------------------
  // 1- Creation, manipulation and deletion of a CAASysRevolSurface component 
  // ------------------------------------------------------------------------

  CATBaseUnknown * pBUnkRevolSurface = NULL;
  HRESULT rcRevolSurface = ::CATInstantiateComponent("CAASysRevolSurface",
	                                    IID_CATBaseUnknown, (void**)&pBUnkRevolSurface);
                                      
  if ( SUCCEEDED(rcRevolSurface) )
  {

     // -----------------------------------------------------------------
     // 2-1 CAASysRevolSurface implements the CAAISysRevolAxis interface 
     // -----------------------------------------------------------------
     cout << endl;
     cout << "   I ask the CAAISysRevolAxis for CAASysRevolSurface"<< endl;
        
     CAAISysRevolAxis * pCAAISysRevolAxis = NULL ;
     HRESULT rc = pBUnkRevolSurface->QueryInterface(IID_CAAISysRevolAxis,
                                                    (void**)&pCAAISysRevolAxis);

     if ( SUCCEEDED(rc) )
     {
        rc = pCAAISysRevolAxis->SetAxis(0.f,1.f,0.f);
        if ( SUCCEEDED(rc) ) 
        {
           float x = 0.f ; 
           float y = 0.f ; 
           float z = 0.f;
           rc = pCAAISysRevolAxis->GetAxis(x,y,z);
           if ( SUCCEEDED(rc) ) 
           {
              cout << "Axis X="<< x << " Y="<< y <<" Z="<< z << endl;
           }
        }

        pCAAISysRevolAxis->Release();
        pCAAISysRevolAxis= NULL ;
     }

     //-------------------------------------------------------------------
     // 1-2 CAASysRevolSurface implements the CAAISysSurfaceArea interface
     //     but implemented by the CAASysSurface too. 
     //-------------------------------------------------------------------
     cout << endl;
     cout << "   I ask the CAAISysSurfaceArea for CAASysRevolSurface"<< endl;

     CAAISysSurfaceArea * pCAAISysSurfaceArea = NULL ;
     rc = pBUnkRevolSurface->QueryInterface(IID_CAAISysSurfaceArea,
                                                    (void**)&pCAAISysSurfaceArea);
     if ( SUCCEEDED(rc) )
     {
        float area = 0.f ;
        rc = pCAAISysSurfaceArea->ComputeArea(area);
        if ( SUCCEEDED(rc) ) 
        {
           cout << "Area de la surface de revolution="<< area << endl;
        }

        pCAAISysSurfaceArea->Release();
        pCAAISysSurfaceArea= NULL ;
     }

     //-------------------------------------------------------------------
     // 1-3 CAASysRevolSurface implements the CAAISysSurfaceProperties 
     //     interface via the CAASysSurface component whose it derives .
     //-------------------------------------------------------------------
     cout << endl;
     cout << "   I ask the CAAISysSurfaceProperties for CAASysRevolSurface"<< endl;

     CAAISysSurfaceProperties * pCAAISysSurfaceProperties = NULL ;
     rc = pBUnkRevolSurface->QueryInterface(IID_CAAISysSurfaceProperties,
                                                    (void**)&pCAAISysSurfaceProperties);
     if ( SUCCEEDED(rc) )
     {
        float area = 0.f ;
        rc = pCAAISysSurfaceProperties->SetColor(0,123,45);
        if ( SUCCEEDED(rc) ) 
        {
           int red   = 0 ; 
           int blue  = 0  ; 
           int green = 0 ;
           rc = pCAAISysSurfaceProperties->GetColor(red,green,blue);
           if ( SUCCEEDED(rc) ) 
           {
              cout << "Color Surface Red="<< red << " Green="<< green <<" Blue="<< blue << endl;
           }
        }

        // ----------------------------------------------------------------
        // 1-4  With the pointer on the CAAISysSurfaceProperties interface
        // I ask the surface area interface 
        // ----------------------------------------------------------------
        cout << endl;
        cout << "   I ask the CAAISysSurfaceArea for CAASysRevolSurface" ;
        cout << " from a CAAISysSurfaceProperties pointer"<< endl;

        CAAISysSurfaceArea * pCAAISysSurfaceArea = NULL ;
        rc = pCAAISysSurfaceProperties->QueryInterface(IID_CAAISysSurfaceArea,
                                                    (void**)&pCAAISysSurfaceArea);
        if ( SUCCEEDED(rc) )
        {
           float area = 0.f ;
           rc = pCAAISysSurfaceArea->ComputeArea(area);
           if ( SUCCEEDED(rc) ) 
           {
              cout << "Area de la surface de revolution"<< area << endl;
           }

           pCAAISysSurfaceArea->Release();
           pCAAISysSurfaceArea= NULL ;
        }

        pCAAISysSurfaceProperties->Release();
        pCAAISysSurfaceProperties= NULL ;
     }

     cout << endl;
     cout << "Deletion of the component CAASysRevolSurface:"<< endl;

     pBUnkRevolSurface->Release();
     pBUnkRevolSurface = NULL;
  }else
  {
     ReturnCode = 1 ;
  }
        
  // -------------------------------------------------------------------
  // 2- Creation, manipulation and deletion of a CAASysSurface component 
  // -------------------------------------------------------------------

  cout << endl;
  CATBaseUnknown * pBUnkSurface = NULL;
  HRESULT rcSurface = ::CATInstantiateComponent("CAASysSurface",
	                                                   IID_CATBaseUnknown,
	                                                  (void**)&pBUnkSurface);

  if ( SUCCEEDED(rcSurface) )
  {
     // -------------------------------------------------------------------
     // 2-1 CAASysSurface implements the CAAISysSurfaceArea and CAASysRevolSurface too.
     // -------------------------------------------------------------------
     cout << endl;
     cout << "   I ask the CAAISysSurfaceArea for CAASysSurface"<< endl;

     CAAISysSurfaceArea * pCAAISysSurfaceArea2 = NULL ;
     HRESULT rc = pBUnkSurface->QueryInterface(IID_CAAISysSurfaceArea,
                                                    (void**)&pCAAISysSurfaceArea2);
     if ( SUCCEEDED(rc) )
     {
        float area = 0.f ;
        rc = pCAAISysSurfaceArea2->ComputeArea(area);
        if ( SUCCEEDED(rc) ) 
        {
           cout << "Area de la surface="<< area << endl;
        }

        pCAAISysSurfaceArea2->Release();
        pCAAISysSurfaceArea2= NULL ;
     }
     
     // ------------------------------------------------------
     // 2-2 CAASysSurface doesn't implement the CAAISysRevolAxis
     // ------------------------------------------------------
     cout << endl;
     cout << "   I ask the CAAISysRevolAxis for CAASysSurface"<< endl;

     CAAISysRevolAxis * pCAAISysRevolAxis = NULL ;
     rc = pBUnkSurface->QueryInterface(IID_CAAISysRevolAxis,
                                                    (void**)&pCAAISysRevolAxis);
     if ( SUCCEEDED(rc) )
     {
        pCAAISysRevolAxis->Release();
        pCAAISysRevolAxis= NULL ;

        ReturnCode = 1 ;
     }else
     {
        cout << "No implementation of this interface for CAASysSurface"<< endl;
     }

     cout << endl;
     cout << "Deletion of the component CAASysSurface:"<< endl;

     pBUnkSurface->Release();
     pBUnkSurface = NULL;

     
  }else
  {
     ReturnCode = 1 ;
  }

  cout << endl;
  cout << ">>> EndApplication"<< endl;

  return ReturnCode;
}
