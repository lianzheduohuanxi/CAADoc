#ifndef CAAMmrMultiMeasureStCmd_H
#define CAAMmrMultiMeasureStCmd_H

// COPYRIGHT DASSAULT SYSTEMES 2007

// MechanicalModelerUI Framework
#include "CATMMUIStateCommand.h"   // Needed to derive from CATMMUIStateCmd

class CATPathElementAgent;
class CATDialogAgent;
class CAAIMmrMultiMeasure;

/**
* Class managing the command to create a CAAMmrMultiMeasure.
* 
* refer to programming resources of MechanicalModelerUI framework.
* (consult base class description).
*/
class CAAMmrMultiMeasureStCmd: public CATMMUIStateCommand
{
  CmdDeclareResource(CAAMmrMultiMeasureStCmd,CATMMUIStateCommand);

public:
    CAAMmrMultiMeasureStCmd(CAAIMmrMultiMeasure *piMmrMultiMeasure = NULL); 
    virtual ~CAAMmrMultiMeasureStCmd();

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
	 * ComputeLength
	 */
    CATBoolean ComputeLength( void* data );

    /**
	 * ReplaceInput
	 */
    CATBoolean ReplaceInput( void* data );
    
private:
   
  // Default Constructor, Copy constructor and equal operator, to prevent reimplementation
  // ----------------------------------------------------------------
  CAAMmrMultiMeasureStCmd (CAAMmrMultiMeasureStCmd &);
  CAAMmrMultiMeasureStCmd& operator=(CAAMmrMultiMeasureStCmd&);
  
  CATPathElementAgent	   *_pPathAgent;
  int                    _mode;
  CAAIMmrMultiMeasure    *_piMmrMultiMeasure;
};
#endif
