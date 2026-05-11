// ===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2008
//===================================================================
//
// CAAMaiAddinCmd.h
// Header definition of CAAMaiAddinCmd
//
//===================================================================
//
// Usage notes: Sample toolbars to launch instantiation of machining processes
//              from catalog components
//
//===================================================================
#ifndef CAAMaiAddinCmd_H
#define CAAMaiAddinCmd_H

#include "CATBaseUnknown.h"

class CATCmdContainer;

//-----------------------------------------------------------------------

class CAAMaiAddinCmd: public CATBaseUnknown
{
	CATDeclareClass;

	public:

		CAAMaiAddinCmd ();
		virtual ~CAAMaiAddinCmd ();

		CATCmdContainer* CreateToolbars();
		void CreateCommands();

};

//-----------------------------------------------------------------------

#endif
