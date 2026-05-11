//===================================================================
// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
//===================================================================
#ifndef CAAPmiUserPrismaticOperationFeedAndSpeedTabPage_H
#define CAAPmiUserPrismaticOperationFeedAndSpeedTabPage_H

#include "CATBaseUnknown.h"


/**
 * Class Class extending the object "UserDrilling".
 * <br>
 * It implements the interfaces :
 *  <ol>
 *  <li>@see ManufacturingInterfaces.CATIMfgFeedAndSpeedTabPage
 *  </ol>
 */
class CAAPmiUserPrismaticOperationFeedAndSpeedTabPage: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAPmiUserPrismaticOperationFeedAndSpeedTabPage ();
     virtual ~CAAPmiUserPrismaticOperationFeedAndSpeedTabPage ();

    /**
     * Implements a function from an interface.
     * @see ManufacturingInterfaces.CATIMfgFeedAndSpeedTabPage#IsFeedAndSpeedTabPageAvailable
     */
     HRESULT IsFeedRateTabPageAvailable (int & oIsAvailable ) ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAPmiUserPrismaticOperationFeedAndSpeedTabPage (CAAPmiUserPrismaticOperationFeedAndSpeedTabPage &);
  CAAPmiUserPrismaticOperationFeedAndSpeedTabPage& operator=(CAAPmiUserPrismaticOperationFeedAndSpeedTabPage&);

};


#endif
