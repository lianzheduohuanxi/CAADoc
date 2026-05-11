// COPYRIGHT DASSAULT SYSTEMES  2001 +
//=============================================================================
//
#ifndef CAAESchAppCompVisu_H
#define CAAESchAppCompVisu_H

#include "CATExtIVisu.h"
#include "CATISpecObject.h"
#include "CATISchRoute.h"

class CATRep;

class CAAESchAppCompVisu : public CATExtIVisu                                        
{
  public:

    CATDeclareClass;

    CAAESchAppCompVisu();
    virtual ~CAAESchAppCompVisu();

    virtual CATRep *BuildRep();

  private:

	// do not implement
    CAAESchAppCompVisu (const CAAESchAppCompVisu &);
    CAAESchAppCompVisu &operator = (const CAAESchAppCompVisu &);

};
#endif
