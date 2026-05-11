// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAESmiUserOperationWithMAMacros.h
//
//===================================================================
#ifndef CAAESmiUserOperationWithMAMacros_H
#define CAAESmiUserOperationWithMAMacros_H

#include "CATIMfgMacrosTabPage.h"

class CAAESmiUserOperationWithMAMacros: public CATIMfgMacrosTabPage
{
  CATDeclareClass;

  public:

	 // Standard constructors and destructors for an implementation class
     CAAESmiUserOperationWithMAMacros ();
     virtual ~CAAESmiUserOperationWithMAMacros ();

     // To hide the macros tab page
     HRESULT IsMacrosTabPageAvailable( int&  oIsAvailable);


  private:
  
	// The copy constructor and the equal operator must not be implemented
    CAAESmiUserOperationWithMAMacros (CAAESmiUserOperationWithMAMacros &);
    CAAESmiUserOperationWithMAMacros& operator=(CAAESmiUserOperationWithMAMacros&);

};

#endif
