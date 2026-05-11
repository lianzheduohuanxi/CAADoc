#ifndef CAAV5V6MmrSetShowModeCmd_h
#define CAAV5V6MmrSetShowModeCmd_h

// COPYRIGHT Dassault Systemes 2012
//===================================================================
//
// CAAV5V6MmrSetShowModeCmd.h
// The state chart based command: CAAV5V6MmrSetShowModeCmd
//
//===================================================================
//
// Note : CAAV5V6MmrSetShowModeCmd is the same use case as CAAMmrSetShowModeCmd. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
//===================================================================

#include "CATStateCommand.h"
#include "CATBoolean.h"

class CATPathElementAgent;

//----------------------------------------------------------------------

/**
 * Command that enables to swap show mode of a selected element.
 * <p>
 */
class CAAV5V6MmrSetShowModeCmd: public CATStateCommand
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( CAAV5V6MmrSetShowModeCmd, CATStateCommand )

  public:

	CAAV5V6MmrSetShowModeCmd();
  virtual ~CAAV5V6MmrSetShowModeCmd();  
  
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




