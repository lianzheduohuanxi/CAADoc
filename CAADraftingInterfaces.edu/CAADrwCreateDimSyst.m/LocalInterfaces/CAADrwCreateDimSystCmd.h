// COPYRIGHT DASSAULT SYSTEMES 2000
//============================================================================================
// Sample code for : Drafting Interfaces
// Mission         : Creates dimensions sytem  on points
//
// Type            : Interactive command
// Inputs          : No input
// Outputs         : No output
// Run command     : Put the command in a test workbench  
//
// Illustrates     : o The dimension system creation 
//                   o The annotation factory
//============================================================================================


#ifndef CAADrwCreateDimSystCmd_H
#define CAADrwCreateDimSystCmd_H

// DialogEngine
#include "CATStateCommand.h"
// System
#include "CATBooleanDef.h"
// Visualization
class CATPathElementAgent;

class CAADrwCreateDimSystCmd : public CATStateCommand
{
  CmdDeclareResourceFile(CAADraftingInterfaces.eduCmd,CAADrwCreateDimSystCmd,CATStateCommand);

  public:

  CAADrwCreateDimSystCmd();
  virtual ~CAADrwCreateDimSystCmd();

  // Builds th state-chart graph
  // ---------------------------
  void BuildGraph();

  // Creates the dimension system
  // ============================
  boolean CreateDimSyst(void* iData=NULL);

  private:

  // The selection agent
  // -------------------
  CATPathElementAgent          *_pObjectAgent;

};

#endif
