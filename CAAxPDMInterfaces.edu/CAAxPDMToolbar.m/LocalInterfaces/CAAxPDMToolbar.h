// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
// CAAxPDMToolbar.h
//
//===================================================================
#ifndef CAAxPDMToolbar_H
#define CAAxPDMToolbar_H

#include "CATBaseUnknown.h"

class CATCmdContainer;

//-----------------------------------------------------------------------
class CAAxPDMToolbar: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAxPDMToolbar ();
     virtual ~CAAxPDMToolbar ();

	void CreateCommands();
	CATCmdContainer* CreateToolbars();

  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAxPDMToolbar (CAAxPDMToolbar &);
  CAAxPDMToolbar& operator=(CAAxPDMToolbar&);

};

//-----------------------------------------------------------------------

#endif
