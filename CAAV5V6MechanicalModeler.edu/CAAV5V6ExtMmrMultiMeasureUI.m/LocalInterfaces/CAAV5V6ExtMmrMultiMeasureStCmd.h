#ifndef CAAV5V6ExtMmrMultiMeasureStCmd_H
#define CAAV5V6ExtMmrMultiMeasureStCmd_H

// COPYRIGHT DASSAULT SYSTEMES 2012

#include "CATIAV5Level.h"

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
// CATMecModUIExtendItf Framework   
#include "CATMmrStateCommand.h"    // Needed to derive from 
#else
//============================================== 
// V5 only
//============================================== 
// MechanicalModelerUI Framework
#include "CATMMUIStateCommand.h"   // Needed to derive from
#endif

class CATPathElementAgent;
class CATDialogAgent;
class CAAIV5V6ExtMmrMultiMeasure;

/**
* Class managing the command to create a CAAV5V6ExtMmrMultiMeasure.
* 
* refer to programming resources of MechanicalModelerUI framework.
* (consult base class description).
*/
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
class CAAV5V6ExtMmrMultiMeasureStCmd: public CATMmrStateCommand
{
	CmdDeclareResource(CAAV5V6ExtMmrMultiMeasureStCmd,CATMmrStateCommand);
#else
//============================================== 
// V5 only
//============================================== 
class  CAAV5V6ExtMmrMultiMeasureStCmd: public  CATMMUIStateCommand
{
	CmdDeclareResource(CAAV5V6ExtMmrMultiMeasureStCmd,CATMMUIStateCommand);
#endif

public:
    CAAV5V6ExtMmrMultiMeasureStCmd(CAAIV5V6ExtMmrMultiMeasure *piMmrMultiMeasure = NULL); 
    virtual ~CAAV5V6ExtMmrMultiMeasureStCmd();

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
  CAAV5V6ExtMmrMultiMeasureStCmd (CAAV5V6ExtMmrMultiMeasureStCmd &);
  CAAV5V6ExtMmrMultiMeasureStCmd& operator=(CAAV5V6ExtMmrMultiMeasureStCmd&);
  
  CATPathElementAgent	   *_pPathAgent;
  int                    _mode;
  CAAIV5V6ExtMmrMultiMeasure    *_piMmrMultiMeasure;
};
#endif
