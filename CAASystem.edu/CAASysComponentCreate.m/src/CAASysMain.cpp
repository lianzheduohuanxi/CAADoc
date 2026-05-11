// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of the sample:
//  -----------------------
//
//  Sample to illustrate the instantiation of a component.
//
//  Creates a CAASysComponent component thanks to the global function 
//  CATInstantiateComponent. 
//
//  The component CAASysComponent, the first argument of this global function,
//  must implement the CATICreateInstance interface.
//      -> See in CAASysComponentImpl.m module
//         * We have defined in this module the Code extension  
//  
//  The second and third argument of the CATICreateInstance global function 
//  allows you to retrieve a given interface on your component:
//      -> See in ProtectedInterface 
//           the CAAISysMyInterface is defined
//      -> See in CAASysComponentInt.m
//           the CAAISysMyInterface is created
//      -> See in CAASysComponentExt.m 
//           CAASysComponent implements this interface
//
//  In CAASystem.eu/Cnext/code/dictionary/CAASystem.edu..dico we have added:
//  
//  CAASysComponent CATICreateInstance CAASysComponentImpl
//  CAASysComponent CAAISysMyInterface CAASysComponentExt
//  
//=============================================================================
//  Usage:
//  ------
//
//  Type:
//    CAASysComponentCreate
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
#include "CATInstantiateComponent.h"  // For the global function to create the component
#include "CAAISysMyInterface.h"       // an interface implemented by the component

// C++ standard library    
#include <iostream.h>     // To display traces

int main()
{

  cout << "The CAASysComponentCreate Sample begins ....."<< endl;

 
  // -------------------------------------------------------------------------------
  // Creates the component and retrieves a CAAISysMyInterface interface pointer
  // -------------------------------------------------------------------------------

  CAAISysMyInterface * piSysMyInterfaceOnComponent = NULL; 
  HRESULT rc = ::CATInstantiateComponent( "CAASysComponent",  
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


  cout << endl << "The CAASysComponentCreate Sample is finished."<< endl << endl ;

  return 0 ;
}
