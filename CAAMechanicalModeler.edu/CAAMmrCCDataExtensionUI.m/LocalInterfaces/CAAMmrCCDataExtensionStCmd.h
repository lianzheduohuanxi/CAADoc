#ifndef CAAMmrCCDataExtensionStCmd_H
#define CAAMmrCCDataExtensionStCmd_H

// COPYRIGHT DASSAULT SYSTEMES 2007

// MechanicalModelerUI Framework
#include "CATMMUIStateCommand.h"   // Needed to derive from CATMMUIStateCmd

class CAAIMmrCCDataExtensionFactory;
class CAAIMmrCCDataExtensionFactory;
class CATPathElementAgent;
class CATDialogAgent;

/**
* Class managing the command to create a MmrCCDataExtension.
* 
* refer to programming resources of MechanicalModelerUI framework.
* (consult base class description).
*/
class CAAMmrCCDataExtensionStCmd: public CATMMUIStateCommand
{

	CmdDeclareResource(CAAMmrCCDataExtensionStCmd,CATMMUIStateCommand);

public:
    CAAMmrCCDataExtensionStCmd(); 
    virtual ~CAAMmrCCDataExtensionStCmd();

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
  
  HRESULT ExtendOrBuildFeature(CATBaseUnknown *iObjectToExtend, CAAIMmrCCDataExtensionFactory *iMmrFactory);
  
  CATPathElementAgent	   *_pPathAgent;
  CATDialogAgent         *_pDACancel;
};
#endif
