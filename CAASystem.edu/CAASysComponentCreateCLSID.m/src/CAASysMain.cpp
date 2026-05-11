// COPYRIGHT DASSAULT SYSTEMES 2003

//=============================================================================
//  Abstract of the sample:
//  -----------------------
//
//  Sample to illustrate the instantiation of a component by its CLSID.
//
//  Creates a CAASysComponent component thanks to the global function 
//  CATCreateInstance. 
//
//  The CLSID of the CAASysComponent component is the first argument of this global function.
//
//  The second and third argument of the CATCreateInstance global function must
//  always be NULL and 0 respectively.
//
//  The fourth and fifth argument of the CATCreateInstance global function 
//  allows you to retrieve a given interface on your component:
//      -> See in ProtectedInterfaces 
//           the CAAISysMyInterface is defined
//      -> See in CAASysComponentInt.m
//           the CAAISysMyInterface is created
//      -> See in CAASysComponentExt.m 
//           CAASysComponent implements this interface
//
//  In CAASystem.edu/Cnext/code/dictionary/CAASystem.edu.clsid we have :
//  # component CLSID     component name      component implementation library
//
//    {*-*-GUID-*-*}      CAASysComponent     CAASysComponentImpl
//  
//=============================================================================
//  Usage:
//  ------
//
//  Type:
//    CAASysComponentCreateCLSID
//  
//  The different traces of the sample appear on the standard output.
//
//  Return Code:
//     0 : OK
//     1 : KO
//
//=============================================================================

// System Framework
#include "CATErrorDef.h"              // For the FAILED macro
#include "CATCreateInstance.h"        // For the global function to create the component by CLSID

// This componennt Framework
#include "CAAISysMyInterface.h"       // An interface implemented by the component
#include "CAASysComponentCLSID.h"     // For the CLSID of the component

// C++ standard library    
#include <iostream.h>     // To display traces

int main()
{

  cout << "The CAASysComponentCreateCLSID Sample begins ....."<< endl;

 
  // -------------------------------------------------------------------------------
  // Creates the component and retrieves a CAAISysMyInterface interface pointer
  // -------------------------------------------------------------------------------

  CAAISysMyInterface * piSysMyInterfaceOnComponent = NULL; 
  HRESULT rc = ::CATCreateInstance( CLSID_CAASysComponent, NULL, 0, 
                                         IID_CAAISysMyInterface,
                                         (void**)&piSysMyInterfaceOnComponent);   
                                          
  if ( FAILED (rc) )
  {
       cout << " Problem in the component Creation"<< endl;
       return 1 ;
  }

  //-----------------------------------------------------------------------
  //The component is created, and we can use the returned interface pointer 
  //-----------------------------------------------------------------------
  piSysMyInterfaceOnComponent->Print();

  //-----------------------------
  // Pointer no any longer needed
  //-----------------------------
  piSysMyInterfaceOnComponent->Release();
  piSysMyInterfaceOnComponent = NULL;


  cout << endl << "The CAASysComponentCreateCLSID Sample is finished."<< endl << endl ;

  return 0 ;
}
