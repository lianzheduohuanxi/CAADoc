#ifndef CAAV5V6ExtMmrCCDataExtensionStCmd_H
#define CAAV5V6ExtMmrCCDataExtensionStCmd_H

// COPYRIGHT DASSAULT SYSTEMES 2012

#include "CATIAV5Level.h"


#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
// CATMecModUIExtendItf Framework
#include "CATMmrStateCommand.h"     // Needed to derive from    
#else
//============================================== 
// V5 only
//============================================== 
// MechanicalModelerUI Framework
#include "CATMMUIStateCommand.h"   // Needed to derive from
#endif

class CATPathElementAgent;
class CATDialogAgent;

/**
* Class managing the command to create a MmrCCDataExtension.
* 
* refer to programming resources of MechanicalModelerUI framework.
* (consult base class description).
*/
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
class CAAV5V6ExtMmrCCDataExtensionStCmd: public CATMmrStateCommand
{
	CmdDeclareResource(CAAV5V6ExtMmrCCDataExtensionStCmd,CATMmrStateCommand);
#else
//============================================== 
// V5 only
//============================================== 
class CAAV5V6ExtMmrCCDataExtensionStCmd: public CATMMUIStateCommand
{
	CmdDeclareResource(CAAV5V6ExtMmrCCDataExtensionStCmd,CATMMUIStateCommand);
#endif

public:
    CAAV5V6ExtMmrCCDataExtensionStCmd(); 
    virtual ~CAAV5V6ExtMmrCCDataExtensionStCmd();

    /**
     * Defines the command automata.
     * <br>
     * <i>(states, transitions and agents)</i>
     */
    virtual void     BuildGraph();

    /**
     * Action associated to state transitions.
     */
    virtual CATBoolean  OkAction(void * data);

	/**
	 * Cancel Action
	 */
    virtual CATBoolean  Cancel(void * data);
    
	 /**
	 * Select Feature
	 */
    CATBoolean SelectFeatureAndExtend( void* data );

private:
  
  CATPathElementAgent	   *_pPathAgent;
  CATDialogAgent         *_pDACancel;
};
#endif
