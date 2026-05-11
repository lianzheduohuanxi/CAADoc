#ifndef CAAAniCataProvider_H
#define CAAAniCataProvider_H
// COPYRIGHT Dassault Systemes 2000
//===================================================================
//
// CAAAniCataProvider.h
// Provide implementation to interface CATISamCatalogProvider
// 
//===================================================================

#include "CATBaseUnknown.h"
#include "CATUnicodeString.h" 
class CATIContainer;

//-----------------------------------------------------------------------

class CAAAniCataProvider: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
    CAAAniCataProvider ();
    virtual ~CAAAniCataProvider ();

	  HRESULT AssociateCatalog(CATUnicodeString iName,const CATIContainer* ipiContainer);

  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAAniCataProvider (CAAAniCataProvider &);
  CAAAniCataProvider& operator=(CAAAniCataProvider&);

};

//-----------------------------------------------------------------------

#endif


