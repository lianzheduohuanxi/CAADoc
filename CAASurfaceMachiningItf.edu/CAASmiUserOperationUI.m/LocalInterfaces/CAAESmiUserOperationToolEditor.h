// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAESmiUserOperationToolEditor.h
//
//===================================================================
#ifndef CAAESmiUserOperationToolEditor_H
#define CAAESmiUserOperationToolEditor_H

#include "CATIMfgToolActivity.h"
#include "CATListOfCATUnicodeString.h"

class CAAESmiUserOperationToolEditor: public CATIMfgToolActivity
{
  CATDeclareClass;

  public:

     // Standard constructors and destructors for an implementation class
     CAAESmiUserOperationToolEditor ();
     virtual ~CAAESmiUserOperationToolEditor ();

     // Gives informations relative to tools on the Activity.
	 HRESULT GetAuthorizedToolTypeList (CATListOfCATUnicodeString & oToolTypeList) ;

     // Creates default tool for an Activity.
     HRESULT CreateDefaultTool (CATBaseUnknown_var & oTool) ;

     // Useless
	 HRESULT GetFirstToolCompensation (int & oFirstNumber) ;
     HRESULT GetSecondToolCompensation (int & oSecondNumber) ;


  private:
     
	 // The copy constructor and the equal operator must not be implemented
	 CAAESmiUserOperationToolEditor (CAAESmiUserOperationToolEditor &);
	 CAAESmiUserOperationToolEditor& operator=(CAAESmiUserOperationToolEditor&);

};

#endif
