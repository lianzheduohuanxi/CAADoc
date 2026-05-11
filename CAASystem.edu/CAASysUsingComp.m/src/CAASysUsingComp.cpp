// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of the sample:
//  -----------------------
//
//  Sample to illustrate:
//
//     - The instantiation of a component 
//     - Querying for interfaces
//     - Using interface pointer
//     - Managing component life cycle    
//
//  What the Sample does:
//     
//   1- Creates the component using the global function CATInstantiateComponent 
//
//   2- Uses QueryInterface to modify the Circle component
//
//      2-1 Initializes the Circle via the CAAISysCircle interface pointer
//
//      2-2 Retrieves a CAAISysColorProperties interface pointer, interface
//          that the Circle implements 
//
//      2-3 Tries to Retrieve a CAAISysPointProperties interface pointer, 
//          interface that the Circle doesn't implement 
//
//=============================================================================
//  Usage:
//  ------
//
//  Type:
//    CAASysUsingComp
//  
//  The different traces of the sample appear on the standard output.
//
//  Return Code:
//     0 : OK
//     1 : KO
//
//=============================================================================

// System Framework
#include "CATErrorDef.h"    // for SUCCEEDED macro
#include "CATInstantiateComponent.h"  

// Local Framework
#include "CAAISysColorProperties.h"
#include "CAAISysPointProperties.h"
#include "CAAISysCircle.h"

//  Visualization Framework
#include "CATMathVector.h"

// C++ standard library    
#include <iostream.h>     // To display traces

int main()
{

  cout << "The CAASysUsingComp Sample begins ....."<< endl;

  int ReturnCode = 0;
 
  // -------------------------------------------------------------------------------
  // 1- Creates a CAASysCircle component thanks to the global function CATInstantiateComponent 
  //    and retrieves the CAAISysCircle interface pointer
  //    This component must implemented CATICreateInstance. see CAASysGeoModelInf
  // -------------------------------------------------------------------------------

  cout << endl << " 1- Component Creation" << endl << endl;

  CAAISysCircle * piSysCircleOnCircle = NULL; 
  HRESULT rc = ::CATInstantiateComponent( "CAASysCircle",  
                                         IID_CAAISysCircle,
					  				  (void**)&piSysCircleOnCircle);   
                                          
  if ( FAILED (rc) )
  {
       cout << " Problem in the component Creation"<< endl;
       return 1 ;
  }else
  {

  // ----------------------------------------------------
  // 2- Uses QueryInterface to modify the Circle component
  // ----------------------------------------------------

     cout <<endl <<  " 2- Circle Access" << endl << endl;

     // --------------------------
     // 2-1 Initializes the Circle
     // --------------------------

     // 2-1-1 The Center 
     // ----------------

     CATMathPoint Center(-4.f,0.f,0.f);
     rc = piSysCircleOnCircle->SetCenter(Center);
     if ( SUCCEEDED(rc) )
     {
         CATMathPoint RetrievedCenter(0.f,0.f,0.f) ;
         rc = piSysCircleOnCircle->GetCenter(RetrievedCenter);
         if ( SUCCEEDED(rc) )
         {
            cout << "Position of the  Circle is " ;
            cout << " X=" << RetrievedCenter.GetX() ;
            cout << " Y=" << RetrievedCenter.GetY() ;
            cout << " Z=" << RetrievedCenter.GetZ() << endl;
         }else 
         {
            cout << "Reading the Circle Center fails"<< endl;
            ReturnCode = 1 ;
         }
     }else
     {
        cout << "Setting the Circle Center fails"<< endl; 
        ReturnCode = 1 ;
     }

     // 2-1-2 The Radius 
     // ----------------

     float Radius = 10.f ;
     rc = piSysCircleOnCircle->SetRadius(Radius);
     if ( SUCCEEDED(rc) )
     {
         float RetrievedRadius(0.f);
         rc = piSysCircleOnCircle->GetRadius(RetrievedRadius);
         if ( SUCCEEDED(rc) )
         {
            cout << "The Radius of the Circle is="<< RetrievedRadius << endl;
         }else
         {
            cout << "Reading the Circle Radius fails"<< endl; 
            ReturnCode = 1 ;
         }

     }else
     {
        cout << "Setting the Circle Radius fails"<< endl; 
        ReturnCode = 1 ;
     }

     // 2-1-3 The Plane 
     // ----------------

     CATMathVector Normal(1.f,0.f,0.f) ;
     CATMathVector Axis (0.f,1.f,0.f)  ;
     rc = piSysCircleOnCircle->SetPlanar(Normal,Axis);
     if ( SUCCEEDED(rc) )
     {
         CATMathVector RetrievedNormal(0.f,0.f,0.f) ;
         CATMathVector RetrievedAxis (0.f,0.f,0.f)  ;
         rc = piSysCircleOnCircle->GetPlanar(RetrievedNormal, RetrievedAxis);
         if ( SUCCEEDED(rc) )
         {
            cout << "The Circle is in the Plane defined by the Normal:" ;
            cout << " X=" << RetrievedNormal.GetX() ;
            cout << " Y=" << RetrievedNormal.GetY() ;
            cout << " Z=" << RetrievedNormal.GetZ() << endl ;

            cout << "The Circle is defined by the Axis:" ;
            cout << " X=" << RetrievedAxis.GetX() ;
            cout << " Y=" << RetrievedAxis.GetY() ;
            cout << " Z=" << RetrievedAxis.GetZ() << endl << endl;
         }else
         {
            cout << "Reading the Circle Plane fails"<< endl; 
            ReturnCode = 1 ;
         }
     }else
     {
        cout << "Setting the Circle Plane fails"<< endl; 
        ReturnCode = 1 ;
     }


     // -------------------------------------------------------------------
     // 2-2 Tries to retrieve a pointer to the CAAISysColorProperties 
     // interface that the Circle implements.
     // --------------------------------------------------------------------

     CAAISysColorProperties * piSysColorPropOnCircle = NULL;                
     rc = piSysCircleOnCircle->QueryInterface(IID_CAAISysColorProperties, 
                                          (void**)&piSysColorPropOnCircle);
     
     if ( SUCCEEDED(rc) )
     {
         rc = piSysColorPropOnCircle->SetColor(100,100,100);
         if ( SUCCEEDED(rc) )
         {
            // Verification
            int r(0) ;
            int g(0) ;
            int b(0) ;
            rc = piSysColorPropOnCircle->GetColor(r,g,b);
            if ( SUCCEEDED(rc) )
            {
               cout << "Color of the Circle is r=" << r << " g="<< g <<" b="<< b << endl;
            }else
            {
               cout << "Reading The Circle Color fails"<< endl;
               ReturnCode = 1 ;
            }

         }else
         { 
            cout << "Setting The Circle Color fails"<< endl ;
            ReturnCode = 1 ;
         }

         // Pointer not any longer needed 
         piSysColorPropOnCircle->Release();
         piSysColorPropOnCircle = NULL ;

     }else
     {
        cout << "KO,The Circle should implement the CAAISysColorProperties interface"<< endl;
        ReturnCode = 1 ;
     }

     // -------------------------------------------------------------------
     // 2-3 Tries to retrieve a pointer to the CAAISysPointProperties 
     // interface that the Circle doesn't implement.
     // --------------------------------------------------------------------
     
     CAAISysPointProperties * piSysPointPropOnCircle = NULL;                
     rc = piSysCircleOnCircle->QueryInterface(IID_CAAISysPointProperties, 
                                          (void**)&piSysPointPropOnCircle);
     
     if ( SUCCEEDED(rc) )
     {
        cout << "KO,the Circle should'nt implement the CAAISysPointProperties interface"<< endl;
        ReturnCode = 1 ;

        // Pointer not any longer needed 
        piSysPointPropOnCircle->Release();
        piSysPointPropOnCircle = NULL ;

     }else
     {
        cout << "OK,The Circle doen't implement the CAAISysPointProperties interface"<< endl;
     }
  }

  cout <<endl <<  " 4- Circle Destruction" << endl << endl;

  // Pointer no any longer needed
  piSysCircleOnCircle->Release();
  piSysCircleOnCircle = NULL;


  cout << endl << "The CAASysUsingComp Sample is finished."<< endl << endl ;

  return ReturnCode;
}
