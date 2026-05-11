// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAASysComponent.h"

//C++ standard library
#include "iostream.h"

//------------------------------------------------------------------------------------

// To declare that the class is a component main class 
CATImplementClass(CAASysComponent, Implementation, CATBaseUnknown, CATNull);

//------------------------------------------------------------------------------------

CAASysComponent::CAASysComponent() 
{
  cout << "CAASysComponent::CAASysComponent" << endl;
}

CAASysComponent::~CAASysComponent()
{
  cout << "CAASysComponent::~CAASysComponent" << endl;
}









