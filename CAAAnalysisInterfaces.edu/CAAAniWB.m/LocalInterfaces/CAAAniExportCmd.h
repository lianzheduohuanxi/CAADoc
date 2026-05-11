#ifndef CAAAniExportCmd_H
#define CAAAniExportCmd_H

#include "CATStateCommand.h"

class CATPathElementAgent;
class CATDialogAgent;
class CATISamAnalysisCase;

class CAAAniExportCmd : public CATStateCommand
{
  CATDeclareClass;
  CmdDeclareResource( CAAAniExportCmd , CATStateCommand )
  
  public:

    // constructeurs et destructeur
    CAAAniExportCmd ();
    virtual ~CAAAniExportCmd();

    // graph management
    void BuildGraph();

  protected:

    CATBoolean FindACase ( CATDialogAgent * iAgent , void * iData );
    CATBoolean Export ( void * iData );

    CATPathElementAgent * _CaseFound;
    CATISamAnalysisCase   * _Case;
};
#endif
