// COPYRIGHT DASSAULT SYSTEMES  2005
//=============================================================================
//
// CAAESchAppObjectFactory
// Implements CATISchAppObjectFactory2
//
//=============================================================================
#ifndef CAAESchAppObjectFactory_H
#define CAAESchAppObjectFactory_H

#include "CATEASchAppObjectFactory2.h"  // This is the adaptor class

class CATISchAppRoute;
class CATDocument;
class CATUnicodeString;

class CAAESchAppObjectFactory : public CATEASchAppObjectFactory2                           
{
  public:

  CATDeclareClass;

    CAAESchAppObjectFactory();
    virtual ~CAAESchAppObjectFactory();
    
  virtual HRESULT AppCreateCompRef (const char *iAppCompClassType,
    const CATDocument *iDoc, IUnknown **oAppComp);

  virtual HRESULT AppCreateRoute2 (const char *iAppRouteClassType,
     const CATDocument *iDoc, const CATUnicodeString *iLogLineID, 
     IUnknown **oAppRoute);

  private:

    // do not implement
    CAAESchAppObjectFactory (const CAAESchAppObjectFactory &);
    CAAESchAppObjectFactory &operator = (const CAAESchAppObjectFactory &);

}; 
#endif
