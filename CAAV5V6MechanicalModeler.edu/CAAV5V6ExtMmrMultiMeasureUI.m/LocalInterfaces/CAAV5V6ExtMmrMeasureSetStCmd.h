#ifndef CAAV5V6ExtMmrMeasureSetStCmd_H
#define CAAV5V6ExtMmrMeasureSetStCmd_H

// COPYRIGHT DASSAULT SYSTEMES 2012

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
// CATMecModUIExtendItf Framework
#include "CATMmrPanelStateCmd.h"   // Needed to derive from 
#else
//============================================== 
// V5 only
//============================================== 
// MechanicalModelerUI Framework
#include "CATMMUIStateCommand.h"   // Needed to derive from
#endif

class CATPathElementAgent;

/**
* Class managing the command to create a CAAV5V6ExtMmrMeasureSet.
* 
* refer to programming resources of MechanicalModelerUI framework.
* (consult base class description).
*/
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
class CAAV5V6ExtMmrMeasureSetStCmd: public CATMmrStateCommand 
{
	CmdDeclareResource(CAAV5V6ExtMmrMeasureSetStCmd,CATMmrStateCommand);

#else
//============================================== 
// V5 only
//============================================== 
class CAAV5V6ExtMmrMeasureSetStCmd: public CATMMUIStateCommand
{
	CmdDeclareResource(CAAV5V6ExtMmrMeasureSetStCmd,CATStateCommand);

#endif
	
public:
    CAAV5V6ExtMmrMeasureSetStCmd(); 
    virtual ~CAAV5V6ExtMmrMeasureSetStCmd();

    /**
     * Defines the command automata.
     * <br>
     * <i>(states, transitions and agents)</i>
     */
    virtual void     BuildGraph();
    
    /**
	  * Select Feature
	  */
    CATBoolean InstantiateNewMechanicalSet( void* data );

};
#endif
