#ifndef CAAMmrSetShowModeCmd_h
#define CAAMmrSetShowModeCmd_h

// COPYRIGHT Dassault Systemes 2011
//===================================================================
//
// CAAMmrSetShowModeCmd.h
// The state chart based command: CAAMmrSetShowModeCmd
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  Aug 2011  Creation: ADS
//===================================================================

#include "CATStateCommand.h"
#include "CATBoolean.h"

class CATPathElementAgent;

//----------------------------------------------------------------------

/**
 * Command that enables to swap show mode of a selected element.
 * <p>
 */
class CAAMmrSetShowModeCmd: public CATStateCommand
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( CAAMmrSetShowModeCmd, CATStateCommand )

  public:

	CAAMmrSetShowModeCmd();
  virtual ~CAAMmrSetShowModeCmd();  
  
 /**
  * Implements the statechart. 
  */
  virtual void BuildGraph();

	/**
  * Swaps Hide/Show mode. 
  */
   CATBoolean SwapShowMode(void* iData);

  private:
	  CATPathElementAgent* _daObjectToSelect;
};

//----------------------------------------------------------------------

#endif




