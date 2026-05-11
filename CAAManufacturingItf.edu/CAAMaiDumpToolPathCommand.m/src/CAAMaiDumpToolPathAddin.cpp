// COPYRIGHT DASSAULT SYSTEMES 2003
// ===================================================================
//
// CAAMaiDumpToolPathAddin :
//
// Creation of an add-in in Prismatic Machining Product in order to use
//   CAAMaiDumpToolPathCommand 
//                   
//=============================================================================

#include "CAAMaiDumpToolPathAddin.h"

// ApplicationFrame Framework 
#include <CATCreateWorkshop.h>    // To use NewAccess - SetAccess - SetAccessChild ...

// Declaration of a new Command Header Class 
#include "CATCommandHeader.h"        
MacDeclareHeader(CAAMaiDumpToolPathHeader);

// Implement the interface CATIManufacturingProgramAddin to create an add-in in the Prismatic Machining Workbench
CATImplementBOA (CATIManufacturingProgramAddin, CAAMaiDumpToolPathAddin);

CATImplementClass(CAAMaiDumpToolPathAddin, DataExtension, CATIManufacturingProgramAddin, CAAMaiDumpToolPathAdn);


CAAMaiDumpToolPathAddin::CAAMaiDumpToolPathAddin()
{}

CAAMaiDumpToolPathAddin::~CAAMaiDumpToolPathAddin()
{}

void CAAMaiDumpToolPathAddin::CreateCommands()
{
  static CATString DumpToolPath ("DumpToolPath");
  new CAAMaiDumpToolPathHeader ( "DumpToolPath","CAAMaiDumpToolPathCommand","CAAMaiDumpToolPathCommand",(void *)&DumpToolPath); 
}

CATCmdContainer * CAAMaiDumpToolPathAddin::CreateToolbars()
{
  NewAccess(CATCmdContainer,PaletteDumpTPMain,ManufacturingDumpTPMain);
  SetAccessTitle(PaletteDumpTPMain,"Manufacturing Dump TP");
  SetAccessCustomerName(PaletteDumpTPMain,"ManufacturingDumpTPMain");
  AddToolbarView(PaletteDumpTPMain,1,Right);
  
  NewAccess(CATCmdStarter,DumpToolPath,DumpToolPath);
  SetAccessCommand(DumpToolPath,"DumpToolPath");
  SetAccessChild(PaletteDumpTPMain,DumpToolPath);
  
  return PaletteDumpTPMain;
}

