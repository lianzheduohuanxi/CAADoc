#ifndef CAAICafElementPropertyPageEdtFactory_h
#define CAAICafElementPropertyPageEdtFactory_h
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Interface of a factory that creates an Tools/Options Page Editor 
//  description class. 
//   
//
//===========================================================================
// Needed to derive from CATIGenericFactory
#include <CATIGenericFactory.h>

// Global Unique IDentifier defined in .cpp 
extern IID IID_CAAICafElementPropertyPageEdtFactory;

class CAAICafElementPropertyPageEdtFactory : public CATIGenericFactory
{
  // Used in conjunction with CATImplementInterface in the .cpp file
  CATDeclareInterface;
  public:
};
#endif
