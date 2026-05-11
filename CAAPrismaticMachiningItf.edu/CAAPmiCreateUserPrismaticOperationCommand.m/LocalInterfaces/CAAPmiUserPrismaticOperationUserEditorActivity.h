//===================================================================
// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
//===================================================================
#ifndef CAAPmiUserPrismaticOperationUserEditorActivity_H
#define CAAPmiUserPrismaticOperationUserEditorActivity_H

#include "CATBaseUnknown.h"

#include "CATDialog.h"

class CATDlgFrame;

/**
 * Class Class extending the object "UserDrilling".
 * <br>
 * It implements the interfaces :
 *  <ol>
 *  <li>@see ManufacturingInterfaces.CATIMfgUserEditorActivity
 *  </ol>
 */
class CAAPmiUserPrismaticOperationUserEditorActivity: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAPmiUserPrismaticOperationUserEditorActivity ();
     virtual ~CAAPmiUserPrismaticOperationUserEditorActivity ();

    /**
     * Implements a function from an interface.
     * @see ManufacturingInterfaces.CATIMfgUserEditorActivity#GetMainPanelEditor
     */
     HRESULT GetMainPanelEditor (CATDialog * iFather  , CATDlgFrame*&  oFrame  , CATDlgStyle  iStyle =NULL) ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAPmiUserPrismaticOperationUserEditorActivity (CAAPmiUserPrismaticOperationUserEditorActivity &);
  CAAPmiUserPrismaticOperationUserEditorActivity& operator=(CAAPmiUserPrismaticOperationUserEditorActivity&);

};

#endif
