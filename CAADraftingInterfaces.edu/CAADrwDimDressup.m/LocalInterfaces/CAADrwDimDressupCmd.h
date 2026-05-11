// Center-line creation command sample.
// ====================================

// COPYRIGHT DASSAULT SYSTEMES 2000
//============================================================================================
// Sample code for : Drafting Interfaces
// Mission         : Modify the dressup of selected dimensions
//
// Type            : Interactive command
// Inputs          : No input
// Outputs         : No output
// Run command     : Put the command in a test workbench  
//
// Illustrates     : o The dimension interfaces
//============================================================================================
#ifndef CAADrwDimDressupCmd_H
#define CAADrwDimDressupCmd_H

// DialogEngine
#include "CATStateCommand.h"
// System
#include "CATBooleanDef.h"
// Visualization
class CATPathElementAgent;

class CAADrwDimDressupCmd : public CATStateCommand
{
  CmdDeclareResourceFile(CAADraftingInterfaces.eduCmd,CAADrwDimDressupCmd,CATStateCommand);

  public:

  CAADrwDimDressupCmd();
  virtual ~CAADrwDimDressupCmd();

  // Builds the state-chart graph
  // ----------------------------
  void BuildGraph();

  // Modify the dimension dress-up
  // -----------------------------
  boolean DressUp(void* iData=NULL);

  private:

  // The command acquisition agent
  // -----------------------------
  CATPathElementAgent          *_pObjectAgent;

};

#endif
