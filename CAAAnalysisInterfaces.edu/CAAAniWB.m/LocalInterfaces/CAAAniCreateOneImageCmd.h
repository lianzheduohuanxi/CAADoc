#ifndef CAAAniCreateOneImageCmd_H
#define CAAAniCreateOneImageCmd_H

#include "CATStateCommand.h"
class CATPathElementAgent;
class CATDialogAgent;

class CAAAniCreateOneImageCmd : public CATStateCommand
{
  CATDeclareClass;
  CmdDeclareResource( CAAAniCreateOneImageCmd , CATStateCommand )
  
  public:

    // constructeurs et destructeur
    CAAAniCreateOneImageCmd ();
    virtual ~CAAAniCreateOneImageCmd();

    // graph management
    void BuildGraph();

  protected:

    CATBoolean FindASolution ( CATDialogAgent * iAgent , void * iData );
    CATBoolean CreateImage ( void * iData );

    CATPathElementAgent * _SolutionFound;
    CATBaseUnknown *      _Solution;
};
#endif
