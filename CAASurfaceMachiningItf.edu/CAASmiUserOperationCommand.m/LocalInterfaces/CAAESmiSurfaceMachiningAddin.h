// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAESmiSurfaceMachiningAddin.h
//
//===================================================================
#ifndef CAAESmiSurfaceMachiningAddin_H
#define CAAESmiSurfaceMachiningAddin_H

#include "CATBaseUnknown.h"
class CATCmdContainer;

class CAAESmiSurfaceMachiningAddin: public CATBaseUnknown
{
  CATDeclareClass;

  public:

     // Standard constructors and destructors for an implementation class
     CAAESmiSurfaceMachiningAddin();
     virtual ~CAAESmiSurfaceMachiningAddin();

	 // Instantiates the command headers.  
	 void CreateCommands ();

     // Creates toolbars containers.
     CATCmdContainer * CreateToolbars();

  private:
     
	 // The copy constructor and the equal operator must not be implemented
     CAAESmiSurfaceMachiningAddin (CAAESmiSurfaceMachiningAddin &);
     CAAESmiSurfaceMachiningAddin& operator=(CAAESmiSurfaceMachiningAddin&);

};

#endif
