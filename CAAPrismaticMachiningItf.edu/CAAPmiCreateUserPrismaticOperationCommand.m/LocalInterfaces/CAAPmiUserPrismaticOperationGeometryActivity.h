//===================================================================
// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
//===================================================================
#ifndef CAAPmiUserPrismaticOperationGeometryActivity_H
#define CAAPmiUserPrismaticOperationGeometryActivity_H

#include "CATBaseUnknown.h"

#include "CATDialog.h"

class CATDlgFrame;


/**
 * Class Class extending the object "UserDrilling".
 * <br>
 * It implements the interfaces :
 *  <ol>
 *  <li>@see ManufacturingInterfaces.CATIMfgGeometryActivity
 *  </ol>
 */
class CAAPmiUserPrismaticOperationGeometryActivity: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAPmiUserPrismaticOperationGeometryActivity ();
     virtual ~CAAPmiUserPrismaticOperationGeometryActivity ();

    /**
     * Implements a function from an interface.
     * @see ManufacturingInterfaces.CATIMfgGeometryActivity#GetMainPanelEditor
     */
     HRESULT GetMainPanelEditor (CATDialog * iFather  , CATDlgFrame*&  oFrame  , CATDlgStyle  iStyle =NULL) ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAPmiUserPrismaticOperationGeometryActivity (CAAPmiUserPrismaticOperationGeometryActivity &);
  CAAPmiUserPrismaticOperationGeometryActivity& operator=(CAAPmiUserPrismaticOperationGeometryActivity&);

};

#endif
