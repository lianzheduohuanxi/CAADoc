// COPYRIGHT DASSAULT SYSTEMES  2001 +
//=============================================================================
//
#ifndef CAAESchAppCntrVisu_H
#define CAAESchAppCntrVisu_H

#include "CATExtIVisu.h"
#include "CATISpecObject.h"
#include "CATISchRoute.h"

class CATRep;

class CAAESchAppCntrVisu : public CATExtIVisu                                        
{
  public:

    CATDeclareClass;

    CAAESchAppCntrVisu();
    virtual ~CAAESchAppCntrVisu();

    virtual CATRep *BuildRep();

  private:

	// do not implement
    CAAESchAppCntrVisu (const CAAESchAppCntrVisu &);
    CAAESchAppCntrVisu &operator = (const CAAESchAppCntrVisu &);

};
#endif
