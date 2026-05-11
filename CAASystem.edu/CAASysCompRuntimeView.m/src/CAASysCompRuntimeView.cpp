// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of the sample:
//  -----------------------
//
//  Batch to illustrate the Runtime View of a Component. 
//
//
//  What the Batch does :
//     
//
//   1- Creates some components thank to the global function CATInstantiateComponent 
//      1-1 Creates a point and retrieves a CAAISysPoint interface pointer
//      1-2 Creates a line and retrieves a CATBaseUnknown interface pointer
//      1-3 Creates a circle and retrieves a pointer to the CAAISysColorProperties 
//          interface that the circle implements.
//          -->Creation is successful
//      1-4 Creates a circle and retrieves a pointer to the CAAISysPointProperties 
//          interface pointer that the circle doesn't implement.
//          -->Creation failed
//
//   2- Uses QueryInterface to modify object properties 
//      2-1 Modifications of the point
//          2-1-1 Modification of the coordinates
//          2-1-2 Retrieve an interface via an another
//      2-2 Modifications of the line
//          2-2-1 Try to retrieve an interface not implemented
//          2-2-2 Retrieve an interface via the CATBaseUnknown pointer 
//      2-3 Modifications of the circle
//          2-3-1 Retrieve an interface via an another interface pointer
//          --> This interface ( CAAISysTextureProperties ) is implemented by at least 2
//               component. 
//          2-3-2 Retrieve an interface via an another interface pointer
//          --> This interface ( CAAISysCircleCenterProperties ) is implemented 
//              only by the circle.
//
//=============================================================================
//  Usage:
//  ------
//
//  Type:
//    CAASysCompRuntimeView
//  
//  The different traces of the sample appear on the standard output.
//
//  Return Code:
//     0 : OK
//     1 : KO
//
//=============================================================================

// System Framework
#include "CATErrorDef.h"  // for SUCCEEDED & FAILED macros
#include "CATInstantiateComponent.h" 


// Local Framework
#include "CAAISysColorProperties.h"
#include "CAAISysTextureProperties.h"
#include "CAAISysPointProperties.h"
#include "CAAISysCircleCenterProperties.h"
#include "CAAISysPoint.h"

// C++ standard library    
#include <iostream.h>     // To display traces



int main()
{

  cout << "The CAASysCompRuntimeView Sample begins ....."<< endl;

  // ----------------------------------------------------
  // 1- Creates some components 
  // ----------------------------------------------------

  cout << endl << " 1- Component Creation" << endl << endl;

  // -------------------------------------------------------------------------------
  // 1-1 Creates a CAASysPoint component thanks to the global function CATInstantiateComponent 
  //    and retrieves the CAAISysPoint interface pointer
  //    This component must implemented CATICreateInstance. see CAASysGeoModelInf
  // -------------------------------------------------------------------------------

  CAAISysPoint * piSysPointOnPoint = NULL; 
  HRESULT rc = ::CATInstantiateComponent( "CAASysPoint",  
                                         IID_CAAISysPoint,
					  				  (void**)&piSysPointOnPoint); 

  // Uses piSysPointOnPoint
  // ----------------------
  CAAISysPoint * piSysPoint2OnPoint = NULL ;
  if (SUCCEEDED(rc))
  {
     // Keeps piSysPointOnPoint in another pointer 
     piSysPoint2OnPoint = piSysPointOnPoint;

     // An interface pointer created by assignment must be Addref'd 
     piSysPoint2OnPoint->AddRef();

     // piSysPointOnPoint is no longer needed
     piSysPointOnPoint->Release(); 
     piSysPointOnPoint = NULL ;
  }else
  {
     cout << "Creation of a Point unsuccessful"<< endl; 
     return 1 ;
  }

  // -------------------------------------------------------------------
  // 1-2 Creates a line and retrieves a CATBaseUnknown interface pointer
  // -------------------------------------------------------------------
  
  CATBaseUnknown * piBUknOnLine= NULL;
  rc = ::CATInstantiateComponent( "CAASysLine",  
                                         IID_CATBaseUnknown,
					  				  (void**)&piBUknOnLine);
  if ( FAILED(rc) )
  {
     cout << "Creation of a Line unsuccessful"<< endl; 
     return 1 ;
  }

  // --------------------------------------------------------------------------
  // 1-3 Creates a circle and retrieves a pointer to the CAAISysColorProperties 
  // interface that the circle implements.
  // ---------------------------------------------------------------------------
  
   CAAISysColorProperties * piSysColorPropOnCircle = NULL; 
   rc = ::CATInstantiateComponent( "CAASysCircle",  
                                         IID_CAAISysColorProperties,
					  				  (void**)&piSysColorPropOnCircle);
  if (FAILED(rc))
  {
     cout << "Creation of a Circle unsuccessful"<< endl; 
     return 1 ;
  }
  
  // ---------------------------------------------------------------------------
  // 1-4 Creates a circle and retrieves a pointer to the CAAISysPointProperties 
  // interface pointer that the circle doesn't implement.
  // ---------------------------------------------------------------------------

  CAAISysPointProperties * piSysPointPropOnCircle = NULL; 
  rc = ::CATInstantiateComponent( "CAASysCircle",  
                                  IID_CAAISysPointProperties,
					  	    	  (void**)&piSysPointPropOnCircle);

  if (SUCCEEDED(rc))
  {
     cout << "KO, Circle doesn't implement the CAAISysPointProperties interface"<< endl; 
     return 1 ;
  }
  
  // ----------------------------------------------------
  // 2- Uses QueryInterface to modify object properties 
  // ----------------------------------------------------

  cout <<endl <<  " 2- objects Modification" << endl << endl;

  // --------------------------------
  // 2-1 Modifications of the point
  // --------------------------------

  if ( NULL != piSysPoint2OnPoint )
  {
     // ------------------------------------------------
     // 2-1-1 piSysPoint2OnPoint is a CAAISysPoint Interface pointer
     // ------------------------------------------------
     
     float x(1.f) ,y(2.3f) ,z(3.4f);
     rc = piSysPoint2OnPoint->SetCoord(x,y,z);
     if ( SUCCEEDED(rc) )
     {
        // make sure that the coordinates are correctly set.
        x = 0 ; y = 0; z = 0 ;
        rc = piSysPoint2OnPoint->GetCoord(x,y,z);
        if ( FAILED(rc) )
        {
           cout << "CAAISysPoint::GetCoord failed "<< endl; 
           return 1 ;
        }
     }

     // ------------------------------------------------------------
     // 2-1-2 Retrieves the CAAISysPointProperties interface pointer
     // via another interface pointer
     // -------------------------------------------------------------
     
     CAAISysPointProperties * piSysPointPropertiesOnPoint = NULL;                
     rc = piSysPoint2OnPoint->QueryInterface(IID_CAAISysPointProperties, 
                                          (void**)&piSysPointPropertiesOnPoint);
     if ( SUCCEEDED(rc) )
     {
        CAAISysPointProperties::MarkerType type ;
        piSysPointPropertiesOnPoint->GetMarkerType(type);
        switch (type)
        {
           case 0 : cout << "the point type is a dot"<< endl; break;
           case 1 : cout << "the point type is a cross"<< endl;break;
           case 2 : cout << "the point type is a plus"<< endl;break;
           case 3 : cout << "the point type is a star"<< endl;break;
        }
        
        // Pointer not any longer needed 
        piSysPointPropertiesOnPoint->Release();
        piSysPointPropertiesOnPoint = NULL ;
     }
  }

  // --------------------------------
  // 2-2 Modifications of the Line
  // --------------------------------

  if ( NULL != piBUknOnLine)
  {
     // -----------------------------------------------------------------
     // 2-2-1 piBUknOnLine is a CATBaseUnknown Interface pointer 
     // Tries to retrieve a pointer to the CAAISysPointProperties interface 
     // that the Line doen't implement. 
     // -----------------------------------------------------------------

     CAAISysPointProperties * piSysPointPropOnLine = NULL;                
     rc = piBUknOnLine->QueryInterface(IID_CAAISysPointProperties, 
                                          (void**)&piSysPointPropOnLine);
     if ( SUCCEEDED(rc) )
     {
        cout << "KO, the Line should't implement the CAAISysPointProperties interface"<< endl;
        // Pointer not any longer needed 
        piSysPointPropOnLine->Release();
        piSysPointPropOnLine = NULL ;

        return 1 ;
     }
     
     // ------------------------------------------------------------------
     // 2-2-2 piBUknLine is a CATBaseUnknown Interface pointer 
     // Tries to retrieve a pointer to the  CAAISysColorProperties interface 
     // that the Line implements.
     // ------------------------------------------------------------------

     CAAISysColorProperties * piSysColorPropOnLine = NULL;                
     rc = piBUknOnLine->QueryInterface(IID_CAAISysColorProperties, 
                                          (void**)&piSysColorPropOnLine);
     
     if ( SUCCEEDED(rc) )
     {
         // --------------------------
         // Tries to change the color
         // --------------------------

         // With bad values
         rc = piSysColorPropOnLine->SetColor(0,260,0);
         if ( SUCCEEDED(rc) )
         {
            cout << "Invalid RGB color values, not checked by the component"<< endl;  
            return 1 ;
         }

         // With good values
         rc = piSysColorPropOnLine->SetColor(0,120,0);
         if ( FAILED(rc) )
         {
            cout << "KO, the color is valid, bad implementation"<< endl; 
            return 1 ;
         }

         // Pointer not any longer needed 
         piSysColorPropOnLine->Release();
         piSysColorPropOnLine = NULL ;

     }else
     {
        cout << "KO, Line should implement the CAAISysColorProperties interface"<< endl;
        return 1 ;
     }                                                                                                            
  }

  // --------------------------------
  // 2-3 Modifications of the Circle
  // --------------------------------

  if ( NULL != piSysColorPropOnCircle )
  {
     // -------------------------------------------------------------------
     // 2-3-1 piSysColorPropOnCircle is a CAAISysColorProperties Interface pointer 
     // Tries to retrieve a pointer to the CAAISysTextureProperties 
     // interface that the Circle implements. 
     // --------------------------------------------------------------------

     CAAISysTextureProperties * piSysTexturePropOnCircle = NULL;                
     rc = piSysColorPropOnCircle->QueryInterface(IID_CAAISysTextureProperties, 
                                          (void**)&piSysTexturePropOnCircle);
     
     if ( SUCCEEDED(rc) )
     {
         // Tries to change the texture 
         rc = piSysTexturePropOnCircle->SetMetal(0);
         if ( SUCCEEDED(rc) )
         {
             int metal ;
             rc = piSysTexturePropOnCircle->GetMetal(metal);
             if ( SUCCEEDED(rc) )
             {
                if ( 0 == metal )
                {
                   cout << "OK, The Circle is not in metal"<< endl;
                }
             }
         }

         // Pointer not any longer needed 
         piSysTexturePropOnCircle->Release();
         piSysTexturePropOnCircle = NULL ;

     }else
     {
        cout << "KO, Circle should implement the CAAISysTextureProperties interface"<< endl;
        return 1 ;
     }

     // -------------------------------------------------------------------
     // 2-3-2 piSysColorPropOnCircle is a CAAISysColorProperties Interface pointer 
     // Tries to retrieve a pointer to the CAAISysCircleCenterProperties 
     // interface that the Circle implements. 
     // --------------------------------------------------------------------
     
     CAAISysCircleCenterProperties * piSysCircleCenterPropOnCircle = NULL;                
     rc = piSysColorPropOnCircle->QueryInterface(IID_CAAISysCircleCenterProperties, 
                                          (void**)&piSysCircleCenterPropOnCircle);
     
     if ( SUCCEEDED(rc) )
     {
         // Tries to change the Circle Center representation
         rc = piSysCircleCenterPropOnCircle->SetMarkerType(CAAISysCircleCenterProperties::Cross);
         if ( SUCCEEDED(rc) )
         {
             CAAISysCircleCenterProperties::MarkerType type ;
             piSysCircleCenterPropOnCircle->GetMarkerType(type);
             switch (type)
             {
                case 0 : cout << "the Circle center is a dot"  << endl; break;
                case 1 : cout << "the Circle center is a cross"<< endl;break;
                case 2 : cout << "the Circle center is a plus" << endl;break;
                case 3 : cout << "the Circle center is a star" << endl;break;
             }
         }

         // Pointer not any longer needed 
         piSysCircleCenterPropOnCircle->Release();
         piSysCircleCenterPropOnCircle = NULL ;

     }else
     {
        cout << "KO, Circle should implement the CAAISysCircleCenterProperties interface"<< endl;
        return 1 ;
     }
  }

  cout <<endl <<  " 3- objects Destruction" << endl << endl;

  // ------------------
  // 3- Release objets
  // ------------------

  // The Point
  piSysPoint2OnPoint->Release();
  piSysPoint2OnPoint = NULL;

  // The Line
  piBUknOnLine->Release();
  piBUknOnLine = NULL ;

  // The Circle
  piSysColorPropOnCircle->Release();
  piSysColorPropOnCircle = NULL;


  cout << endl << "The CAASysUsingComp Sample is finished."<< endl << endl ;

  return 0;
}
