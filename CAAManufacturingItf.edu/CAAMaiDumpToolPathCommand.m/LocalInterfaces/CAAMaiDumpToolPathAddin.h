// COPYRIGHT DASSAULT SYSTEMES 2003
// ===================================================================
//
// CAAMaiDumpToolPathAddin :
//
// Creation of an add-in in Prismatic Machining Product in order to use
//   CAAMaiDumpToolPathCommand 
//                   
//=============================================================================

#include "CATIManufacturingProgramAddin.h"

class CATCmdContainer;

class CAAMaiDumpToolPathAddin : public CATIManufacturingProgramAddin
{
  CATDeclareClass;

  public:
    CAAMaiDumpToolPathAddin();
    virtual ~CAAMaiDumpToolPathAddin();

    void CreateCommands();
    CATCmdContainer * CreateToolbars();
};
