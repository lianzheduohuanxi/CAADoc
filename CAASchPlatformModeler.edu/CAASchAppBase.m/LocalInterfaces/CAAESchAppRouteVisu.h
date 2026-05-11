// COPYRIGHT DASSAULT SYSTEMES  2001 +
//=============================================================================
//
#ifndef CAAESchAppRouteVisu_H
#define CAAESchAppRouteVisu_H

#include "CATExtIVisu.h"
#include "CATISpecObject.h"
#include "CATISchRoute.h"
#include "CATPathElement.h"
#include "CATRepPath.h"

class CATRep;

class CAAESchAppRouteVisu : public CATExtIVisu                                        
{
  public:

    CATDeclareClass;

    CAAESchAppRouteVisu();
    virtual ~CAAESchAppRouteVisu();

    virtual CATRep *BuildRep();

    virtual HRESULT BuildHighlightLook (
      const CATPathElement &modelPath, CATRepPath &repPath);    

  private:

	// do not implement
    CAAESchAppRouteVisu (const CAAESchAppRouteVisu &);
    CAAESchAppRouteVisu &operator = (const CAAESchAppRouteVisu &);

};
#endif
