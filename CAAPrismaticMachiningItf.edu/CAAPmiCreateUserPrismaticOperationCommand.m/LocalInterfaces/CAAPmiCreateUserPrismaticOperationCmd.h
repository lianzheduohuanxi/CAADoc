// COPYRIGHT DASSAULT SYSTEMES 2004
#ifndef CAAPmiCreateUserPrismaticOperationCmd_H
#define CAAPmiCreateUserPrismaticOperationCmd_H
//=============================================================================
//
// Class CAAPmiCreateUserPrismaticOperationCmd:
// User defined drilling cration command
//
//=============================================================================

#include "CATStateCommand.h"

class CATPathElementAgent;
class CATDialogState;

class CAAPmiCreateUserPrismaticOperationCmd : public CATStateCommand
{
   public:
   
      DeclareResource (CAAPmiCreateUserPrismaticOperationCmd,CATStateCommand)
    
      CAAPmiCreateUserPrismaticOperationCmd (CATString* argument);
      virtual ~CAAPmiCreateUserPrismaticOperationCmd();
      void BuildGraph();

   private:

	   // Create the setup
      boolean ManageChildActivityAndSequence(void *);

      CATPathElementAgent*     _ActAcq;
      CATDialogState*          _InitState;

      CATUnicodeString         _TypeToCreate;
};
#endif
