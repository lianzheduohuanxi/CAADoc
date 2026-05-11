// COPYRIGHT DASSAULT SYSTEMES 2002

#ifndef CAAEPstINFInitCont_h
#define CAAEPstINFInitCont_h

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAPstINFCont component, implementing
//  the CATInit interface to allow specific treatments to be executed during
//  the initialization of the applicative container.
//
//  Illustrates programming the Init method of the CATInit interface of the 
//  ObjectModelerBase framework, for an applicative container containing
//  objects whose integration in the Product document is dependent on the declaration
//  of its provider implementations.
//
//===========================================================================
//  Inheritance:
//  ------------
//            
//  CATBaseUnknown (System Framework) 
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"
#include "CATBoolean.h"

class CAAEPstINFInitCont : public CATBaseUnknown
{

  CATDeclareKindOf;

public:
 
  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
  CAAEPstINFInitCont();
  virtual ~CAAEPstINFInitCont();

  // Initializes the "CAAPstINFCont" applicative container.
  void Init (CATBoolean iDestroyExistingData) ;

  // Empty implementation.
  CATBaseUnknown* GetRootContainer (const CATIdent iInterfaceID);

  private:
  // Copy constructor and equal operator, not implemented
  // Set as private to prevent the compiler from automatically creating them as public.
  // -------------------------------------------------------------------
  CAAEPstINFInitCont (CAAEPstINFInitCont &);
  CAAEPstINFInitCont& operator=(CAAEPstINFInitCont&);
    

};

#endif


