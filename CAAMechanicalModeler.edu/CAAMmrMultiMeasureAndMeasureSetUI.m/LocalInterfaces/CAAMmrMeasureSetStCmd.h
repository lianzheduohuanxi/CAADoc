#ifndef CAAMmrMeasureSetStCmd_H
#define CAAMmrMeasureSetStCmd_H

// COPYRIGHT DASSAULT SYSTEMES 2007

// MechanicalModelerUI Framework
#include "CATMMUIStateCommand.h"   // Needed to derive from CATMMUIStateCmd

class CATPathElementAgent;


/**
* Class managing the command to create a CAAMmrMeasureSet.
* 
* refer to programming resources of MechanicalModelerUI framework.
* (consult base class description).
*/
class CAAMmrMeasureSetStCmd: public CATMMUIStateCommand
{
  CmdDeclareResource(CAAMmrMeasureSetStCmd,CATMMUIStateCommand);


public:
    CAAMmrMeasureSetStCmd(); 
    virtual ~CAAMmrMeasureSetStCmd();

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
