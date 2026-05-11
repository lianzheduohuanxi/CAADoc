//
// COPYRIGHT DASSAULT SYSTEMES 2000
//============================================================================================
// Sample code for : Drafting Interfaces
// Mission         : Align a text from a reference text selected in another sheet
//
// Type            : Interactive command
// Inputs          : No input
// Outputs         : No output
// Run command     : Put the command in a test workbench  
//
// Illustrates     : o The multisheet command interface
//============================================================================================
#ifndef CAADrwMultiSheetCmd_H
#define CAADrwMultiSheetCmd_H

// DialogEngine: 
#include "CATStateCommand.h" // needed to create a command
// System
#include "CATBooleanDef.h"   // needed to use boolean type variable
// Visualization
class CATPathElementAgent;   // needed to create an agent dedicated to selection
// Drafting
#include "CATIADrawingSheets.h"  // needed to get drawing Feature

class CAADrwMultiSheetCmd : public CATStateCommand
{
  CmdDeclareResourceFile(CAADraftingInterfaces.eduCmd,CAADrwMultiSheetCmd,CATStateCommand);
  
  public:

  CAADrwMultiSheetCmd();
  virtual ~CAADrwMultiSheetCmd();

  // Builds the state-chart graph
  // ----------------------------
  void BuildGraph();

 

  private:

 // Read the reference text
  // -----------------------
  boolean CheckText(void* iData1=NULL);

  // Modify the text
  // ---------------
  boolean MoveText(void* iData2=NULL);

  // Access to Multi sheet mode
  // --------------------------
  void SetMultiSheetMode(boolean  iMode);
  void GetMultiSheetMode(boolean  &oMode);

  CATIADrawingSheets           *_piSheetsOnDrawing ;
  CATPathElementAgent          *_pObjectAgent;

  // The anchor point of the reference text
  // --------------------------------------
  double                        _Xposition,_Yposition;

  // Memorize the multi sheet mode
  // -----------------------------
    boolean                     _PreviousMode;
};

#endif
