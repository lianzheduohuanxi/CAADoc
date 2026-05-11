//===================================================================
// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
//===================================================================
#ifndef CAAPmiUserPrismaticOperationMacroEditorActivity_H
#define CAAPmiUserPrismaticOperationMacroEditorActivity_H

#include "CATBaseUnknown.h"

#include "CATDialog.h"

class CATDlgFrame;

/**
 * Class Class extending the object "UserDrilling".
 * <br>
 * It implements the interfaces :
 *  <ol>
 *  <li>@see ManufacturingInterfaces.CATIMfgMacroEditorActivity
 *  </ol>
 */
class CAAPmiUserPrismaticOperationMacroEditorActivity: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAPmiUserPrismaticOperationMacroEditorActivity ();
     virtual ~CAAPmiUserPrismaticOperationMacroEditorActivity ();

    /**
     * Implements a function from an interface.
     * @see ManufacturingInterfaces.CATIMfgMacroEditorActivity#GetMainPanelEditor
     */
     HRESULT GetMainPanelEditor (CATDialog * iFather  , CATDlgFrame*&  oFrame  , CATDlgStyle  iStyle =NULL) ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAPmiUserPrismaticOperationMacroEditorActivity (CAAPmiUserPrismaticOperationMacroEditorActivity &);
  CAAPmiUserPrismaticOperationMacroEditorActivity& operator=(CAAPmiUserPrismaticOperationMacroEditorActivity&);

};

#endif
