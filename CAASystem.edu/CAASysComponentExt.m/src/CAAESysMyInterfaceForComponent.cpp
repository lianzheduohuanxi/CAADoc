// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysMyInterfaceForComponent.h"

//C++ standard library
#include "iostream.h"

//-----------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CAAISysMyInterface.h"
TIE_CAAISysMyInterface(CAAESysMyInterfaceForComponent);

// To declare that the class is a Data extension of CAASysComponent
//
CATImplementClass(CAAESysMyInterfaceForComponent, DataExtension, CATBaseUnknown, CAASysComponent);
// 
// To declare that CAAESysMyInterfaceForComponent implements CAAISysMyInterface, insert 
// the following line in the interface dictionary:
//
//    CAASysComponent CAAISysMyInterface  libCAASysComponentExt
//
//------------------------------------------------------------------------------------

CAAESysMyInterfaceForComponent::CAAESysMyInterfaceForComponent() 
{
  cout << "CAAESysMyInterfaceForComponent::CAAESysMyInterfaceForComponent" << endl;
}

//------------------------------------------------------------------------------------

CAAESysMyInterfaceForComponent::~CAAESysMyInterfaceForComponent()
{
  cout << "CAAESysMyInterfaceForComponent::~CAAESysMyInterfaceForComponent" << endl;
}

//------------------------------------------------------------------------------------

HRESULT  CAAESysMyInterfaceForComponent::Print()
{
   cout << "CAAESysMyInterfaceForComponent::Print"<< endl; 
   return(S_OK);
}







