// COPYRIGHT DASSAULT SYSTEMES 2000
//============================================================================================
// Sample code for : Drafting Interfaces
// Mission         : Creates centerLines on interactive and generative circles
//
// Type            : Interactive command
// Inputs          : No input
// Outputs         : No output
// Run command     : Put the command in a test workbench  
//
// Illustrates     : o The center line annotation 
//                   o The annotation factory
//                   o Generative/Interactive geometry 
//============================================================================================


#ifndef CAADrwCenterLineCmd_H
#define CAADrwCenterLineCmd_H

// DialogEngine
#include "CATStateCommand.h"
// System
#include "CATBooleanDef.h"
// Visualization
class CATPathElementAgent;

class CAADrwCenterLineCmd : public CATStateCommand
{
  CmdDeclareResourceFile(CAADraftingInterfaces.eduCmd,CAADrwCenterLineCmd,CATStateCommand);
  
  public:

  CAADrwCenterLineCmd();
  virtual ~CAADrwCenterLineCmd();

  // Builds th state-chart graph
  // ---------------------------
  void BuildGraph();

  // Creates the center-line
  // =======================
  boolean CreateCtrLine(void* iData=NULL);

  private:

  // The selection agent
  // -------------------
  CATPathElementAgent          *_pObjectAgent;

};

#endif
