//===================================================================
// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
//===================================================================
#ifndef CAAPmiUserPrismaticOperationGeometryTabPage_H
#define CAAPmiUserPrismaticOperationGeometryTabPage_H

#include "CATBaseUnknown.h"


/**
 * Class Class extending the object "UserDrilling".
 * <br>
 * It implements the interfaces :
 *  <ol>
 *  <li>@see ManufacturingInterfaces.CATIMfgGeometryTabPage
 *  </ol>
 */
class CAAPmiUserPrismaticOperationGeometryTabPage: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAPmiUserPrismaticOperationGeometryTabPage ();
     virtual ~CAAPmiUserPrismaticOperationGeometryTabPage ();

    /**
     * Implements a function from an interface.
     * @see ManufacturingInterfaces.CATIMfgGeometryTabPage#IsGeometryTabPageAvailable
     */
     HRESULT IsGeometryTabPageAvailable (int & oIsAvailable ) ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAPmiUserPrismaticOperationGeometryTabPage (CAAPmiUserPrismaticOperationGeometryTabPage &);
  CAAPmiUserPrismaticOperationGeometryTabPage& operator=(CAAPmiUserPrismaticOperationGeometryTabPage&);

};

#endif
