// COPYRIGHT DASSAULT SYSTEMES 2000
//===================================================================
#ifndef CAAAniCfg_h
#define CAAAniCfg_h

#include "CATBaseUnknown.h"

#include "CATListPV.h"
class CATCmdWorkbench;


class CAAAniCfg : public CATBaseUnknown
{
  CATDeclareClass;

public:


  CAAAniCfg();
  ~CAAAniCfg();
  
  void CreateCommands();
  CATCmdWorkbench * CreateWorkbench();
  CATClassId GetAddinInterface();
  void GetCustomInterfaces(CATListPV *, CATListPV *);
};

#endif
