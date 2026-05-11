// COPYRIGHT DASSAULT SYSTEMES 2003

//=============================================================================
//  Abstract of the sample:
//  -----------------------
//
//  Sample to illustrate the instantiation of a component that implements an interface using the BOA.
//
//  Creates a CAASysComponentBOA component thanks to the global function 
//  CATInstantiateComponent. 
//
//  The component CAASysComponentBOA, the first argument of this global function,
//  must implement the CATICreateInstance interface.
//      -> See in CAASysComponentBOA.m module
//         * We have defined in this module the Code extension  
//  
//  The second and third arguments of the CATICreateInstance global function 
//  allow you to retrieve a given interface on your component:
//      -> See in ProtectedInterfaces
//           the CAAISysInterface is defined
//      -> See in CAASysInterface.m
//           the CAAISysInterface is created
//      -> See in CAASysComponentBOA.m 
//           CAASysComponentBOA implements this interface using the BOA
//
//  In CAASystem.edu/Cnext/code/dictionary/CAASystem.edu.dico we have added:
//  
//  CAASysComponentBOA CATICreateInstance libCAASysComponentBOA
//  CAASysComponentBOA CAAISysInterface   libCAASysComponentBOA
//  
//=============================================================================
//  Usage:
//  ------
//
//  Type:
//    CAASysUseBOA
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
#include "CAAISysInterface.h"         // an interface implemented by the component using the BOA

// C++ standard library    
#include <iostream.h>     // To display traces

int main()
{

  cout << "The CAASysUseBOA Sample begins ....."<< endl;

 
  // -------------------------------------------------------------------------------
  // Creates the component and retrieves a CAAISysInterface interface pointer
  // -------------------------------------------------------------------------------

  CAAISysInterface *piSysInterface = NULL; 
  HRESULT rc = ::CATInstantiateComponent( "CAASysComponentBOA",  
                                         IID_CAAISysInterface,
                                         (void**)&piSysInterface);   
                                          
  if ( FAILED (rc) )
  {
       cout << " Problem in the component Creation"<< endl;
       return 1 ;
  }

  //-----------------------------------------------------------------------
  //The component is created, and we can use the returned interface pointer 
  //-----------------------------------------------------------------------
  piSysInterface->ToString();

  //-----------------------------
  // Pointer no any longer needed
  //-----------------------------
  piSysInterface->Release();
  piSysInterface = NULL;

  cout << endl << "The CAASysUseBOA Sample is finished."<< endl << endl ;

  return 0 ;
}
