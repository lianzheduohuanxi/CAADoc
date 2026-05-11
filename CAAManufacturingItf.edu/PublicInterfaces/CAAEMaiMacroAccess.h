// COPYRIGHT DASSAULT SYSTEMES 2001
// ===================================================================
//
// CAAEMaiMacroAccess:
//
// Sample code for : Manufacturing macro tool path access
// Mission         : Sample of Macro access on an activity
//
// ===================================================================

#ifndef CAAEMaiMacroAccess_h
#define CAAEMaiMacroAccess_h

// System Framework
#include "CAAMaiMacroEnv.h"
#include "CATIMfgActivityMacroMotion.h"
#include "CATIMfgActivity.h"


class ExportedByCAAMaiMacroEnv CAAEMaiMacroAccess 
{

  public: 
    
	// Constructor and Destructor
	//------------------------------------------------
	CAAEMaiMacroAccess(const CATIMfgActivity_var   &iActivity);
	virtual ~CAAEMaiMacroAccess();

	
	// This method is a sample  of CAA macro Interfaces use.
	//----------------------------------------------------------------------
	 HRESULT GetMacroDatas  ();

	// This method is a sample  of CAA macro Interfaces use on each kind of macro elementary motion.

	 HRESULT ReadElementaryMotionDatas  (const int &iTypeMacro, CATIMfgActivityMacroMotion_var& MacroMotion);

	


  private:

     CATIMfgActivity_var _iActivity;



	
	// Copy constructor
	//-------------------------------------------------------------------------
      CAAEMaiMacroAccess(const CAAEMaiMacroAccess &iObjectToCopy);
    
	
	
};

#endif


