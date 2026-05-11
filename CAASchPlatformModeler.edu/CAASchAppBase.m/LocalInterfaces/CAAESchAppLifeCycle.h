// COPYRIGHT DASSAULT SYSTEMES  2004 +
//=============================================================================
#ifndef CAAESchAppLifeCycle_H
#define CAAESchAppLifeCycle_H

// Product Structure
#include "CATSpecLifeCycleObjectExt.h"

class CAAESchAppLifeCycle : public CATSpecLifeCycleObjectExt
{
  public:   

  CATDeclareClass;

  CAAESchAppLifeCycle();
  virtual ~CAAESchAppLifeCycle(); 
  
  virtual void remove( int iForCloseContext=0 );

  private:

    void RemoveComponentExtensionIfNeeded ( int iForCloseContext=0 );

    CAAESchAppLifeCycle (const CAAESchAppLifeCycle &);
    CAAESchAppLifeCycle &operator = (const CAAESchAppLifeCycle &);

};
#endif
