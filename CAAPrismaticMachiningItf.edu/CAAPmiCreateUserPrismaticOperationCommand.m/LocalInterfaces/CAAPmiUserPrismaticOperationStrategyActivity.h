//===================================================================
// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
//===================================================================
#ifndef CAAPmiUserPrismaticOperationStrategyActivity_H
#define CAAPmiUserPrismaticOperationStrategyActivity_H

#include "CATBaseUnknown.h"

#include "CATDialog.h"

class CATDlgFrame;

/**
 * Class Class extending the object "UserDrilling".
 * <br>
 * It implements the interfaces :
 *  <ol>
 *  <li>@see ManufacturingInterfaces.CATIMfgStrategyActivity
 *  </ol>
 */
class CAAPmiUserPrismaticOperationStrategyActivity: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAPmiUserPrismaticOperationStrategyActivity ();
     virtual ~CAAPmiUserPrismaticOperationStrategyActivity ();

    /**
     * Implements a function from an interface.
     * @see ManufacturingInterfaces.CATIMfgStrategyActivity#GetMainPanelEditor
     */
     HRESULT GetMainPanelEditor (CATDialog * iFather  , CATDlgFrame*&  oFrame  , CATDlgStyle  iStyle =NULL) ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAPmiUserPrismaticOperationStrategyActivity (CAAPmiUserPrismaticOperationStrategyActivity &);
  CAAPmiUserPrismaticOperationStrategyActivity& operator=(CAAPmiUserPrismaticOperationStrategyActivity&);

};

#endif
