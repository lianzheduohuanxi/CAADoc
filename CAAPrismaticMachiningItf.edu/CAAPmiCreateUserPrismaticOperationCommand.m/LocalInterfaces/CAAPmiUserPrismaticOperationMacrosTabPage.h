//===================================================================
// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
//===================================================================
#ifndef CAAPmiUserPrismaticOperationMacrosTabPage_H
#define CAAPmiUserPrismaticOperationMacrosTabPage_H

#include "CATBaseUnknown.h"


/**
 * Class Class extending the object "UserDrilling".
 * <br>
 * It implements the interfaces :
 *  <ol>
 *  <li>@see ManufacturingInterfaces.CATIMfgMacrosTabPage
 *  </ol>
 */
class CAAPmiUserPrismaticOperationMacrosTabPage: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAPmiUserPrismaticOperationMacrosTabPage ();
     virtual ~CAAPmiUserPrismaticOperationMacrosTabPage ();

    /**
     * Implements a function from an interface.
     * @see ManufacturingInterfaces.CATIMfgMacrosTabPage#IsMacrosTabPageAvailable
     */
     HRESULT IsMacrosTabPageAvailable (int & oIsAvailable ) ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAPmiUserPrismaticOperationMacrosTabPage (CAAPmiUserPrismaticOperationMacrosTabPage &);
  CAAPmiUserPrismaticOperationMacrosTabPage& operator=(CAAPmiUserPrismaticOperationMacrosTabPage&);

};

#endif
